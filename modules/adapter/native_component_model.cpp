#include "native_component_model.h"
#include "native_component_calls.h"
#include "native_paragraph.h"
#include "native_menu_model.h"
#include "native_menu_component.h"
#include <algorithm>
#include <cstring>
#include <map>
#include <utility>

namespace uwcn::adapter::native_component_model {
namespace {
std::uintptr_t base{};
Handle next_handle=1;
struct Version { u32 references;Component component; };
std::map<Handle,Version> models;
std::map<SourceKey,Handle> current_sources;
std::vector<SourceBinding> bindings;
const HudStatusSummaryInputs* summary_paint_source{};

struct Writer {
    std::vector<std::uint8_t> bytes;
    template<class T> void scalar(T value) {
        const auto* p=reinterpret_cast<const std::uint8_t*>(&value);
        bytes.insert(bytes.end(),p,p+sizeof(value));
    }
    void string(const std::string& value) {
        scalar(static_cast<u32>(value.size()));
        bytes.insert(bytes.end(),value.begin(),value.end());
    }
    void key(SourceKey value) { scalar(value.owner);scalar(value.native_source);scalar(value.field); }
    void text(const TextSource& value) {
        scalar(static_cast<u32>(value.component));string(value.original);string(value.value);
        scalar(value.has_value?1u:0u);scalar(static_cast<u32>(value.policy));
        string(value.prefix);string(value.suffix);
    }
    void layout(const LayoutValue& value) {
        scalar(static_cast<u32>(value.source));scalar(value.input);scalar(value.rva);
    }
    void anchor(const NativeAnchor& value) { layout(value.x);layout(value.y); }
    void style(const native_component_style::PanelStyle& value) {
        scalar(value.background_mode);scalar(value.title_fill_color);
    }
    void style(const native_component_style::ButtonStyle& value) {
        scalar(value.suffix_color);scalar(value.suffix_outline);
    }
    void inputs(const PanelInputs& value) {
        anchor(value.origin);layout(value.width);layout(value.height);scalar(value.flags);scalar(value.color);style(value.style);
    }
    void inputs(const LegacyPanelInputs& value) {
        anchor(value.origin);layout(value.width);layout(value.height);scalar(value.flags);style(value.style);
    }
    void inputs(const ButtonInputs& value) { anchor(value.origin);scalar(value.outline);style(value.style); }
    void inputs(const ParagraphInputs& value) {
        anchor(value.origin);layout(value.width);layout(value.height);scalar(value.color);scalar(value.outline);
    }
    void inputs(const CenteredTextInputs& value) {
        anchor(value.origin);layout(value.width);scalar(value.color);scalar(value.outline);
    }
    void inputs(const TextBlockInputs& value) { anchor(value.anchor);scalar(value.color);scalar(value.outline); }
    void inputs(const StatisticLabelInputs& value) { layout(value.y);scalar(value.value); }
    void inputs(const ActionButtonInputs& value) {
        scalar(value.menu);scalar(value.action);scalar(static_cast<u32>(value.locator));scalar(value.row_id);anchor(value.origin);style(value.style);
    }
    void inputs(const NativeHeadingInputs& value) { style(value.style); }
    void inputs(const CompoundHintInputs& value) { anchor(value.origin);scalar(value.color);style(value.style); }
    void inputs(const TitleStripInputs& value) { anchor(value.origin);layout(value.width);scalar(value.mode);style(value.style); }
    void inputs(const ScaleRulerInputs& value) { anchor(value.origin);layout(value.line_length); }
    void inputs(const WorldMapInputs& value) {
        scalar(value.world_x);scalar(value.world_y);scalar(value.step);scalar(value.mode);scalar(value.large_tiles);
    }
    void inputs(const WorldMapMarkerInputs& value) {
        scalar(value.step);scalar(value.selected_x);scalar(value.selected_y);scalar(value.view_x);scalar(value.view_y);
    }
    void inputs(const WorldMapControlsInputs& value) { scalar(value.step);scalar(value.color); }
    void inputs(const HudStatusCellInputs& value) {
        scalar(value.column);scalar(value.row);scalar(value.label_color);scalar(value.native_record);
        scalar(value.frame_color);scalar(value.shade_color);text(value.value);
        scalar(static_cast<u32>(value.display));text(value.current_value);scalar(value.value_color);
        scalar(value.amount);scalar(value.maximum);
    }
    void inputs(const HudStatusSummaryInputs& value) {
        scalar(value.layout);scalar(value.nutrition);scalar(value.hunger);scalar(value.thirst);
        scalar(value.vigour);scalar(value.warmth_bits);scalar(value.frame_color);scalar(value.shade_color);style(value.panel);
    }
};
struct Reader {
    const std::uint8_t* cursor;
    template<class T> T scalar() {
        T value;std::memcpy(&value,cursor,sizeof(value));cursor+=sizeof(value);return value;
    }
    std::string string() {
        const auto size=scalar<u32>();
        std::string value(reinterpret_cast<const char*>(cursor),size);cursor+=size;return value;
    }
    SourceKey key() {
        const auto owner=scalar<u64>(),source=scalar<u64>();const auto field=scalar<u32>();
        return {owner,source,field};
    }
    TextSource text() {
        const auto component=static_cast<TextComponent>(scalar<u32>());
        auto original=string(),value=string();
        const bool has_value=scalar<u32>()!=0;
        const auto policy=static_cast<native_text_resource::TextPolicy>(scalar<u32>());
        auto prefix=string(),suffix=string();
        return {component,std::move(original),std::move(value),has_value,policy,std::move(prefix),std::move(suffix)};
    }
    LayoutValue layout() {
        const auto source=static_cast<LayoutSource>(scalar<u32>());
        const auto input=scalar<std::int32_t>();const auto rva=scalar<u32>();return {source,input,rva};
    }
    NativeAnchor anchor() { const auto x=layout(),y=layout();return {x,y}; }
    native_component_style::PanelStyle panel_style() {
        const auto background=scalar<u32>(),title=scalar<u32>();return {background,title};
    }
    native_component_style::ButtonStyle button_style() {
        const auto color=scalar<u32>(),outline=scalar<u32>();return {color,outline};
    }
    Inputs inputs(Kind kind) {
        using Decode=Inputs (*)(Reader&);
        static const Decode decoders[]{
            [](Reader& input)->Inputs {
                const auto origin=input.anchor();const auto width=input.layout(),height=input.layout();
                const auto flags=input.scalar<u32>(),color=input.scalar<u32>();
                return PanelInputs{origin,width,height,flags,color,input.panel_style()};
            },
            [](Reader& input)->Inputs {
                const auto origin=input.anchor();const auto width=input.layout(),height=input.layout();
                const auto flags=input.scalar<u32>();
                return LegacyPanelInputs{origin,width,height,flags,input.panel_style()};
            },
            [](Reader& input)->Inputs {
                const auto origin=input.anchor();const auto outline=input.scalar<u32>();
                return ButtonInputs{origin,outline,input.button_style()};
            },
            [](Reader& input)->Inputs {
                const auto origin=input.anchor();const auto width=input.layout(),height=input.layout();
                const auto color=input.scalar<u32>(),outline=input.scalar<u32>();
                return ParagraphInputs{origin,width,height,color,outline};
            },
            [](Reader& input)->Inputs {
                const auto origin=input.anchor();const auto width=input.layout();
                const auto color=input.scalar<u32>(),outline=input.scalar<u32>();
                return CenteredTextInputs{origin,width,color,outline};
            },
            [](Reader& input)->Inputs {
                const auto position=input.anchor();const auto color=input.scalar<u32>(),outline=input.scalar<u32>();
                return TextBlockInputs{position,color,outline};
            },
            [](Reader& input)->Inputs {
                const auto y=input.layout();const auto value=input.scalar<std::int32_t>();
                return StatisticLabelInputs{y,value};
            },
            [](Reader& input)->Inputs {
                const auto menu=input.scalar<u32>(),action=input.scalar<u32>();
                const auto locator=static_cast<ActionLocator>(input.scalar<u32>());const auto row=input.scalar<u32>();
                const auto position=input.anchor();return ActionButtonInputs{menu,action,locator,row,position,input.button_style()};
            },
            [](Reader& input)->Inputs { return NativeHeadingInputs{input.panel_style()}; },
            [](Reader& input)->Inputs { return NativeHeadingInputs{input.panel_style()}; },
            [](Reader& input)->Inputs {
                const auto position=input.anchor();const auto color=input.scalar<u32>();
                return CompoundHintInputs{position,color,input.button_style()};
            },
            [](Reader& input)->Inputs {
                const auto position=input.anchor();const auto width=input.layout();const auto mode=input.scalar<u32>();
                return TitleStripInputs{position,width,mode,input.panel_style()};
            },
            [](Reader& input)->Inputs {
                const auto position=input.anchor();return ScaleRulerInputs{position,input.layout()};
            },
            [](Reader& input)->Inputs {
                const auto x=input.scalar<std::int32_t>(),y=input.scalar<std::int32_t>();
                const auto step=input.scalar<u32>(),mode=input.scalar<u32>(),large=input.scalar<u32>();
                return WorldMapInputs{x,y,step,mode,large};
            },
            [](Reader& input)->Inputs {
                const auto step=input.scalar<u32>();
                const auto x=input.scalar<std::int32_t>(),y=input.scalar<std::int32_t>();
                const auto vx=input.scalar<std::int32_t>(),vy=input.scalar<std::int32_t>();
                return WorldMapMarkerInputs{step,x,y,vx,vy};
            },
            [](Reader& input)->Inputs {
                const auto step=input.scalar<u32>(),color=input.scalar<u32>();return WorldMapControlsInputs{step,color};
            },
            [](Reader& input)->Inputs {
                const auto column=input.scalar<std::int32_t>(),row=input.scalar<std::int32_t>();
                const auto color=input.scalar<u32>(),record=input.scalar<u32>(),frame=input.scalar<u32>(),shade=input.scalar<u32>();
                auto value=input.text();const auto display=static_cast<HudStatusValue>(input.scalar<u32>());
                auto current=input.text();const auto value_color=input.scalar<u32>();
                const auto amount=input.scalar<std::int32_t>(),maximum=input.scalar<std::int32_t>();
                return HudStatusCellInputs{column,row,color,record,frame,shade,std::move(value),display,
                    std::move(current),value_color,amount,maximum};
            },
            [](Reader& input)->Inputs {
                const auto layout=input.scalar<u32>(),nutrition=input.scalar<u32>(),hunger=input.scalar<u32>(),thirst=input.scalar<u32>();
                const auto vigour=input.scalar<u32>(),warmth=input.scalar<u32>(),frame=input.scalar<u32>(),shade=input.scalar<u32>();
                return HudStatusSummaryInputs{layout,nutrition,hunger,thirst,vigour,warmth,frame,shade,input.panel_style()};
            }
        };
        return decoders[static_cast<u32>(kind)](*this);
    }
};

void retain_input_owner(const Component& component) {
    if(component.kind==Kind::action_button)
        native_menu_model::retain(std::get<ActionButtonInputs>(component.inputs).menu);
}
void release_input_owner(const Component& component) {
    if(component.kind==Kind::action_button)
        native_menu_model::release(std::get<ActionButtonInputs>(component.inputs).menu);
}
Handle upsert(Component component) {
    retain_input_owner(component);
    const auto source=current_sources.find(component.source);
    if(source!=current_sources.end()) {
        auto& current=models.find(source->second)->second;
        if(current.references==1) {
            release_input_owner(current.component);
            current.component=std::move(component);
            return source->second;
        }
        const auto previous=source->second;
        const auto handle=next_handle++;
        models.emplace(handle,Version{1,std::move(component)});
        source->second=handle;
        release(previous);
        return handle;
    }
    const auto handle=next_handle++;
    const auto key=component.source;
    models.emplace(handle,Version{1,std::move(component)});
    current_sources.emplace(key,handle);
    return handle;
}
std::int32_t value(const LayoutValue& input,std::int32_t text_width=0) {
    using Evaluate=std::int32_t (*)(const LayoutValue&,std::int32_t);
    static const Evaluate evaluators[]{
        [](const LayoutValue& v,std::int32_t){return v.input;},
        [](const LayoutValue& v,std::int32_t){return *reinterpret_cast<const std::int32_t*>(base+v.rva);},
        [](const LayoutValue& v,std::int32_t width){return v.input-width/2;},
        [](const LayoutValue& v,std::int32_t width){return *reinterpret_cast<const std::int32_t*>(base+v.rva)-width/2;},
        [](const LayoutValue& v,std::int32_t width){return v.input-width;},
        [](const LayoutValue& v,std::int32_t width){return *reinterpret_cast<const std::int32_t*>(base+v.rva)-width;}
    };
    return evaluators[static_cast<u32>(input.source)](input,text_width);
}
bool measured(const LayoutValue& input) {
    return input.source==LayoutSource::center_input || input.source==LayoutSource::center_native_i32 ||
        input.source==LayoutSource::right_input || input.source==LayoutSource::right_native_i32;
}
u32 outline(const Component& component) {
    switch(component.kind) {
    case Kind::panel:case Kind::legacy_panel:case Kind::native_heading_band:
    case Kind::native_identity_heading:case Kind::compound_hint:case Kind::title_strip:
    case Kind::scale_ruler:case Kind::hud_status_cell:case Kind::hud_status_summary:return 1;
    case Kind::button:return std::get<ButtonInputs>(component.inputs).outline;
    case Kind::paragraph:return std::get<ParagraphInputs>(component.inputs).outline;
    case Kind::centered_text:return std::get<CenteredTextInputs>(component.inputs).outline;
    case Kind::text_block:return std::get<TextBlockInputs>(component.inputs).outline;
    case Kind::statistic_label:return 0;
    case Kind::world_map:case Kind::world_map_marker:case Kind::world_map_controls:return 0;
    case Kind::action_button:return std::get<ActionButtonInputs>(component.inputs).style.suffix_outline;
    }
    return 0;
}
Status resolve_text(const TextSource& text,const PaintServices& services,std::vector<char>& encoded) {
    return native_text_resource::resolve_source(text,services.resolve,services.encode_original,encoded);
}
u32 action_row(u32 action) {
    // This method consumes the action of an already constructed row in the
    // selected, live Menu owner. The producer's unique native action is its
    // identity; output positions and construction order are not identities.
    u32 index=0;
    while(*reinterpret_cast<const u32*>(base+0x5F4EF10+
        index*native_menu_model::row_stride+0xC8)!=action) ++index;
    return index;
}
void paint_action(const ActionButtonInputs& input,const TextSource& source,const char* label) {
    const auto previous=native_menu_model::active();
    if(previous) native_menu_model::retain(previous);
    native_menu_model::activate(input.menu);
    auto& count=*reinterpret_cast<u32*>(base+0x5F54A34);
    auto& duplicate_mode=*reinterpret_cast<u32*>(base+0x5F549B0);
    auto& suffix_color=*reinterpret_cast<u32*>(base+0x5F54A30);
    auto& suffix_outline=*reinterpret_cast<u32*>(base+0x5F54A9C);
    const auto total=count;
    const auto previous_mode=duplicate_mode;
    const auto previous_color=suffix_color,previous_outline=suffix_outline;
    const auto row=input.locator==ActionLocator::native_row ? input.row_id : action_row(input.action);
    count=row;
    duplicate_mode=input.locator==ActionLocator::native_row ? 1u : 0u;
    suffix_color=input.style.suffix_color;suffix_outline=input.style.suffix_outline;
    // The row being updated is outside CFAF0's [0,count) duplicate scan. Its
    // complete native write branch therefore replaces that same row and owns
    // both current-language dimensions and input/hit fields.
    const native_component_calls::ActionButtonCall call{static_cast<u32>(base+0xCFAF0),
        input.action,value(input.origin.x),value(input.origin.y),label};
    native_component_calls::uwcn_component_action_button(&call);
    count=total;duplicate_mode=previous_mode;suffix_color=previous_color;suffix_outline=previous_outline;
    native_menu_component::commit_row(input.menu,row,source);
    native_menu_model::capture_into(input.menu);
    if(previous) {
        native_menu_model::activate(previous);native_menu_model::release(previous);
    } else native_menu_model::deactivate();
}
}

void initialize(std::uintptr_t image_base) {
    base=image_base;next_handle=1;models.clear();current_sources.clear();bindings.clear();
    native_component_style::initialize(image_base);
    summary_paint_source=nullptr;
}
void push_source(u64 token,SourceKey key,const TextSource& text) { bindings.push_back({token,key,text}); }
void pop_source(u64 token) {
    bindings.erase(std::remove_if(bindings.begin(),bindings.end(),
        [token](const SourceBinding& binding){return binding.token==token;}),bindings.end());
}
const SourceBinding& source() { return bindings.back(); }
Handle upsert_panel(SourceKey source,const PanelInputs& inputs,const TextSource& text) {
    return upsert({source,Kind::panel,inputs,text,{}});
}
Handle upsert_legacy_panel(SourceKey source,const LegacyPanelInputs& inputs,const TextSource& text) {
    return upsert({source,Kind::legacy_panel,inputs,text,{}});
}
Handle upsert_button(SourceKey source,const ButtonInputs& inputs,const TextSource& text) {
    return upsert({source,Kind::button,inputs,text,{}});
}
Handle upsert_paragraph(SourceKey source,const ParagraphInputs& inputs,const ParagraphSource& paragraph) {
    return upsert({source,Kind::paragraph,inputs,native_text_resource::original_text(""),paragraph});
}
Handle upsert_centered_text(SourceKey source,const CenteredTextInputs& inputs,const TextSource& text) {
    return upsert({source,Kind::centered_text,inputs,text,{}});
}
Handle upsert_text_block(SourceKey source,const TextBlockInputs& inputs,const TextSource& text) {
    return upsert({source,Kind::text_block,inputs,text,{}});
}
Handle upsert_statistic_label(SourceKey source,const StatisticLabelInputs& inputs,const TextSource& text) {
    return upsert({source,Kind::statistic_label,inputs,text,{}});
}
Handle upsert_action_button(SourceKey source,const ActionButtonInputs& inputs,const TextSource& text) {
    return upsert({source,Kind::action_button,inputs,text,{}});
}
Handle upsert_native_heading(SourceKey source,bool identity,const NativeHeadingInputs& inputs,const TextSource& text) {
    return upsert({source,identity?Kind::native_identity_heading:Kind::native_heading_band,inputs,text,{}});
}
Handle upsert_compound_hint(SourceKey source,const CompoundHintInputs& inputs,const TextSource& text) {
    return upsert({source,Kind::compound_hint,inputs,text,{}});
}
Handle upsert_title_strip(SourceKey source,const TitleStripInputs& inputs,const TextSource& text) {
    return upsert({source,Kind::title_strip,inputs,text,{}});
}
Handle upsert_scale_ruler(SourceKey source,const ScaleRulerInputs& inputs,const TextSource& text) {
    return upsert({source,Kind::scale_ruler,inputs,text,{}});
}
Handle upsert_world_map(SourceKey source,const WorldMapInputs& inputs) {
    return upsert({source,Kind::world_map,inputs,native_text_resource::original_text(""),{}});
}
Handle upsert_world_map_marker(SourceKey source,const WorldMapMarkerInputs& inputs) {
    return upsert({source,Kind::world_map_marker,inputs,native_text_resource::original_text(""),{}});
}
Handle upsert_world_map_controls(SourceKey source,const WorldMapControlsInputs& inputs) {
    return upsert({source,Kind::world_map_controls,inputs,native_text_resource::original_text(""),{}});
}
Handle upsert_hud_status_cell(SourceKey source,const HudStatusCellInputs& inputs,const TextSource& label) {
    return upsert({source,Kind::hud_status_cell,inputs,label,{}});
}
Handle update_hud_status_text(SourceKey source,const TextSource& text,u32 color) {
    auto component=get(current(source));auto& input=std::get<HudStatusCellInputs>(component.inputs);
    input.display=HudStatusValue::text;input.current_value=text;input.value_color=color;
    return upsert(std::move(component));
}
Handle update_hud_status_bar(SourceKey source,std::int32_t amount,std::int32_t maximum) {
    auto component=get(current(source));auto& input=std::get<HudStatusCellInputs>(component.inputs);
    input.display=HudStatusValue::bar;input.amount=amount;input.maximum=maximum;
    return upsert(std::move(component));
}
Handle upsert_hud_status_summary(SourceKey source,const HudStatusSummaryInputs& inputs) {
    return upsert({source,Kind::hud_status_summary,inputs,native_text_resource::original_text(""),{}});
}
const HudStatusSummaryInputs* painting_hud_status_summary() {return summary_paint_source;}
u32 menu_owner(Handle handle) {
    const auto& component=get(handle);
    return component.kind==Kind::action_button ? std::get<ActionButtonInputs>(component.inputs).menu : 0;
}
Handle snapshot(Handle handle,u32 menu) {
    auto component=get(handle);
    if(component.kind==Kind::action_button) {
        auto& input=std::get<ActionButtonInputs>(component.inputs);
        input.menu=menu;
        const auto source=input.locator==ActionLocator::native_row
            ? 0x5F4EF10+input.row_id*native_menu_model::row_stride : input.action;
        component.source.native_source=(static_cast<u64>(menu)<<32)|source;
    }
    retain_input_owner(component);
    const auto copy=next_handle++;models.emplace(copy,Version{1,std::move(component)});return copy;
}
Handle snapshot_menu_owner(Handle handle,u32 menu) {
    return snapshot(handle,menu);
}
void parse_prepared_paragraph(const ParagraphSource& source,const std::vector<std::vector<char>>& fragments) {
    using Reset=void (UWCN_CALL *)();using Parse=void (__fastcall *)(u32,const char*);
    using Grammar=void (__fastcall *)(u32,u32);using Compose=const char* (UWCN_CALL *)();
    reinterpret_cast<Reset>(base+0x1620C0)();
    const auto parse=reinterpret_cast<Parse>(base+0x162300);
    const auto grammar=reinterpret_cast<Grammar>(base+0x161E90);
    std::vector<u32> counts(fragments.size()+1);
    const auto phases=[&](std::size_t boundary) {
        for(const auto& node:source.grammar) if(node.after_fragments==boundary) {
            switch(node.operation) {
            case ParagraphOperation::grammar:grammar(counts[node.first_fragment],node.comma_count);break;
            case ParagraphOperation::count_zero:*reinterpret_cast<u32*>(base+0xA225314)=0;break;
            case ParagraphOperation::compose:reinterpret_cast<Compose>(base+0x162100)();break;
            }
        }
    };
    phases(0);
    for(std::size_t index=0;index<fragments.size();++index) {
        if(!fragments[index].empty()) parse(0,fragments[index].data());
        counts[index+1]=*reinterpret_cast<const u32*>(base+0xA225314);
        phases(index+1);
    }
}
bool prepare_paragraph_fragment(const TextSource& source,std::vector<char>& encoded) {
    if((source.component==TextComponent::skills_help_record || source.component==TextComponent::spells_help_record) &&
        encoded.size()==1 && encoded.front()==0) { encoded.clear();return false; }
    return true;
}
const Component& get(Handle handle) { return models.find(handle)->second.component; }
u32 paint_outline(Handle handle) { return outline(get(handle)); }
Handle current(SourceKey source) { return current_sources.at(source); }
void retain(Handle handle) { ++models.find(handle)->second.references; }
void release(Handle handle) {
    const auto model=models.find(handle);
    if(--model->second.references==0) {
        release_input_owner(model->second.component);models.erase(model);
    }
}
void remove(Handle handle) {
    const auto current=current_sources.find(get(handle).source);
    if(current!=current_sources.end() && current->second==handle) {
        current_sources.erase(current);release(handle);
    }
}
void remove_owner(u64 owner) {
    for(auto source=current_sources.begin();source!=current_sources.end();) {
        if(source->first.owner==owner) {
            const auto handle=source->second;source=current_sources.erase(source);release(handle);
        } else ++source;
    }
}
Status prepare(Handle handle,const PaintServices& services,PreparedText& prepared) {
    const auto& component=get(handle);
    prepared.fragments.clear();
    if(component.kind==Kind::paragraph) {
        for(const auto& fragment:component.paragraph.fragments) {
            prepared.fragments.emplace_back();
            auto status=resolve_text(fragment,services,prepared.fragments.back());
            if(status!=Status::ok) return status;
            if(!prepare_paragraph_fragment(fragment,prepared.fragments.back())) continue;
            status=services.paragraph_words(prepared.fragments.back());
            if(status!=Status::ok) return status;
        }
    } else {
        prepared.fragments.emplace_back();
        auto status=resolve_text(component.text,services,prepared.fragments.back());
        if(status!=Status::ok) return status;
        if(component.kind==Kind::hud_status_cell) {
            prepared.fragments.emplace_back();
            const auto& input=std::get<HudStatusCellInputs>(component.inputs);
            status=resolve_text(input.value,services,prepared.fragments.back());
            if(status!=Status::ok) return status;
            if(input.display==HudStatusValue::text) {
                prepared.fragments.emplace_back();
                status=resolve_text(input.current_value,services,prepared.fragments.back());
            }
        }
        return status;
    }
    return Status::ok;
}
Status paint(Handle handle,const PaintServices& services) {
    PreparedText prepared;
    auto status=prepare(handle,services,prepared);
    if(status!=Status::ok) return status;
    const auto& component=get(handle);
    services.enter(handle,component.kind,outline(component));
    using namespace native_component_calls;
    switch(component.kind) {
    case Kind::panel: {
        const auto& input=std::get<PanelInputs>(component.inputs);
        const native_component_style::PanelScope style(input.style);
        const PanelCall call{static_cast<u32>(base+0x116270),value(input.origin.x),value(input.origin.y),
            value(input.width),value(input.height),prepared.fragments.front().data(),input.flags,input.color};
        uwcn_component_panel(&call);break;
    }
    case Kind::legacy_panel: {
        const auto& input=std::get<LegacyPanelInputs>(component.inputs);
        const native_component_style::PanelScope style(input.style);
        const LegacyPanelCall call{static_cast<u32>(base+0x115E70),value(input.origin.x),value(input.origin.y),
            value(input.width),value(input.height),prepared.fragments.front().data(),input.flags};
        uwcn_component_legacy_panel(&call);break;
    }
    case Kind::button: {
        const auto& input=std::get<ButtonInputs>(component.inputs);
        const native_component_style::ButtonScope style(input.style);
        const ButtonCall call{static_cast<u32>(base+0x114680),value(input.origin.x),value(input.origin.y),
            prepared.fragments.front().data()};
        uwcn_component_button(&call);break;
    }
    case Kind::paragraph: {
        parse_prepared_paragraph(component.paragraph,prepared.fragments);
        const auto& input=std::get<ParagraphInputs>(component.inputs);
        const NativeParagraphCall call{static_cast<u32>(base+0x10EB40),value(input.origin.x),value(input.origin.y),
            value(input.width),value(input.height),input.color,input.outline};
        uwcn_draw_native_paragraph(&call);break;
    }
    case Kind::centered_text: {
        const auto& input=std::get<CenteredTextInputs>(component.inputs);
        const CenteredTextCall call{static_cast<u32>(base+0x10E910),value(input.origin.x),value(input.origin.y),
            value(input.width),prepared.fragments.front().data(),input.color,input.outline};
        uwcn_component_centered_text(&call);break;
    }
    case Kind::text_block: {
        const auto& input=std::get<TextBlockInputs>(component.inputs);
        std::int32_t width{};
        if(measured(input.anchor.x)) {
            status=services.measure(prepared.fragments.front().data(),width);
            if(status!=Status::ok) { services.leave(handle,component.kind);return status; }
        }
        const TextBlockCall call{static_cast<u32>(base+0x10E5A0),value(input.anchor.x,width),value(input.anchor.y),
            prepared.fragments.front().data(),input.color,input.outline};
        uwcn_component_text_block(&call);break;
    }
    case Kind::statistic_label: {
        const auto& input=std::get<StatisticLabelInputs>(component.inputs);
        const StatisticLabelCall call{static_cast<u32>(base+0xE10F0),value(input.y),
            prepared.fragments.front().data(),input.value};
        uwcn_component_statistic_label(&call);break;
    }
    case Kind::action_button: {
        const auto& input=std::get<ActionButtonInputs>(component.inputs);
        paint_action(input,component.text,prepared.fragments.front().data());break;
    }
    case Kind::native_heading_band:case Kind::native_identity_heading: {
        const auto& input=std::get<NativeHeadingInputs>(component.inputs);
        const native_component_style::PanelScope style(input.style);
        const NativeHeadingCall call{static_cast<u32>(base+
            (component.kind==Kind::native_heading_band?0xF8F80:0xF9030)),prepared.fragments.front().data()};
        uwcn_component_native_heading(&call);break;
    }
    case Kind::compound_hint: {
        const auto& input=std::get<CompoundHintInputs>(component.inputs);
        const native_component_style::ButtonScope style(input.style);
        const CompoundHintCall call{static_cast<u32>(base+0x10E720),value(input.origin.x),value(input.origin.y),
            prepared.fragments.front().data(),input.color};
        uwcn_component_compound_hint(&call);break;
    }
    case Kind::title_strip: {
        const auto& input=std::get<TitleStripInputs>(component.inputs);
        const native_component_style::PanelScope style(input.style);
        const TitleStripCall call{static_cast<u32>(base+0x1157B0),value(input.origin.x),value(input.origin.y),
            value(input.width),prepared.fragments.front().data(),input.mode};
        uwcn_component_title_strip(&call);break;
    }
    case Kind::scale_ruler: {
        const auto& input=std::get<ScaleRulerInputs>(component.inputs);
        const ScaleRulerCall call{static_cast<u32>(base+0x8FE90),value(input.origin.x),value(input.origin.y),
            value(input.line_length),prepared.fragments.front().data()};
        uwcn_component_scale_ruler(&call);break;
    }
    case Kind::world_map: {
        const auto& input=std::get<WorldMapInputs>(component.inputs);
        auto& large=*reinterpret_cast<std::uint8_t*>(base+0x2F7FD3);const auto previous=large;
        large=static_cast<std::uint8_t>(input.large_tiles);
        const WorldMapCall call{static_cast<u32>(base+0x605B0),input.world_x,input.world_y,input.step,input.mode};
        uwcn_component_world_map(&call);large=previous;break;
    }
    case Kind::world_map_marker: {
        const auto& input=std::get<WorldMapMarkerInputs>(component.inputs);
        const u32 fields[]{0x1E2C10,0x1E2C14,0xEFA84C,0x14FBC58};
        const std::int32_t values[]{input.selected_x,input.selected_y,input.view_x,input.view_y};
        std::int32_t previous[4];
        for(u32 i=0;i<4;++i) {auto& value=*reinterpret_cast<std::int32_t*>(base+fields[i]);previous[i]=value;value=values[i];}
        const WorldMapMarkerCall call{static_cast<u32>(base+0x60360),input.step};
        uwcn_component_world_map_marker(&call);
        for(u32 i=0;i<4;++i) *reinterpret_cast<std::int32_t*>(base+fields[i])=previous[i];
        break;
    }
    case Kind::world_map_controls: {
        const auto& input=std::get<WorldMapControlsInputs>(component.inputs);
        auto& step=*reinterpret_cast<std::uint8_t*>(base+0x2EEC17);const auto previous_step=step;
        auto& color=*reinterpret_cast<u32*>(base+0xA211068);const auto previous_color=color;
        step=static_cast<std::uint8_t>(input.step);color=input.color;
        const NoArgumentCall call{static_cast<u32>(base+0x60450)};uwcn_component_no_argument(&call);
        step=previous_step;color=previous_color;break;
    }
    case Kind::hud_status_cell: {
        const auto& input=std::get<HudStatusCellInputs>(component.inputs);
        auto& frame=*reinterpret_cast<u32*>(base+0x61BBCEC);const auto previous_frame=frame;
        auto& shade=*reinterpret_cast<u32*>(base+0xA1C0EBC);const auto previous_shade=shade;
        frame=input.frame_color;shade=input.shade_color;
        const HudStatusCellCall call{static_cast<u32>(base+0xF8E20),input.column,input.row,
            prepared.fragments[0].data(),prepared.fragments[1].data(),input.label_color,input.native_record};
        uwcn_component_hud_status_cell(&call);frame=previous_frame;shade=previous_shade;
        // The complete constructor has just published this record's native
        // geometry. Updates consume those actual original fields, not a Mod
        // layout or a saved old-language final text position.
        const auto x=*reinterpret_cast<const std::int32_t*>(base+0xA3FF21C+input.native_record*4u);
        const auto y=*reinterpret_cast<const std::int32_t*>(base+0xA40EB30+input.native_record*4u);
        if(input.display==HudStatusValue::text) {
            const CompoundHintCall update{static_cast<u32>(base+0xFEE50),x,y,
                prepared.fragments[2].data(),input.value_color};
            uwcn_component_compound_hint(&update);
        } else if(input.display==HudStatusValue::bar) {
            const HudStatusBarCall update{static_cast<u32>(base+0xFEF00),x,y,input.amount,input.maximum};
            uwcn_component_hud_status_bar(&update);
        }
        break;
    }
    case Kind::hud_status_summary: {
        const auto& input=std::get<HudStatusSummaryInputs>(component.inputs);
        const native_component_style::PanelScope panel(input.panel);
        auto& frame=*reinterpret_cast<u32*>(base+0x61BBCEC);const auto previous_frame=frame;
        auto& shade=*reinterpret_cast<u32*>(base+0xA1C0EBC);const auto previous_shade=shade;
        frame=input.frame_color;shade=input.shade_color;summary_paint_source=&input;
        // Original mode zero is this UI object's complete constructor; mode
        // one is its ordinary update phase. Reconstruct the complete object.
        const NoArgumentCall call{static_cast<u32>(base+0xF9910)};uwcn_component_no_argument(&call);
        summary_paint_source=nullptr;frame=previous_frame;shade=previous_shade;break;
    }
    }
    services.leave(handle,component.kind);
    return Status::ok;
}
std::vector<std::uint8_t> save() {
    Writer output;
    output.scalar(next_handle);output.scalar(static_cast<u32>(models.size()));
    output.scalar(static_cast<u32>(current_sources.size()));
    for(const auto& [handle,version]:models) {
        output.scalar(handle);output.scalar(version.references);
        const auto& component=version.component;
        output.key(component.source);output.scalar(static_cast<u32>(component.kind));
        std::visit([&output](const auto& inputs){output.inputs(inputs);},component.inputs);
        output.text(component.text);output.scalar(static_cast<u32>(component.paragraph.fragments.size()));
        for(const auto& fragment:component.paragraph.fragments) output.text(fragment);
        output.scalar(static_cast<u32>(component.paragraph.grammar.size()));
        for(const auto& node:component.paragraph.grammar) {
            output.scalar(node.after_fragments);output.scalar(node.first_fragment);output.scalar(node.comma_count);
            output.scalar(static_cast<u32>(node.operation));
        }
    }
    for(const auto& [source,handle]:current_sources) { output.key(source);output.scalar(handle); }
    return std::move(output.bytes);
}
void restore(const void* payload) {
    Reader input{static_cast<const std::uint8_t*>(payload)};
    next_handle=input.scalar<u32>();const auto count=input.scalar<u32>(),sources=input.scalar<u32>();
    models.clear();current_sources.clear();bindings.clear();
    for(u32 i=0;i<count;++i) {
        const auto handle=input.scalar<u32>(),references=input.scalar<u32>();
        const auto source=input.key();const auto kind=static_cast<Kind>(input.scalar<u32>());
        auto inputs=input.inputs(kind);auto text=input.text();ParagraphSource paragraph;
        const auto fragments=input.scalar<u32>();
        for(u32 j=0;j<fragments;++j) paragraph.fragments.push_back(input.text());
        const auto grammar=input.scalar<u32>();
        for(u32 j=0;j<grammar;++j) {
            const auto after=input.scalar<u32>(),first=input.scalar<u32>(),commas=input.scalar<u32>();
            const auto operation=static_cast<ParagraphOperation>(input.scalar<u32>());
            paragraph.grammar.push_back({after,first,commas,operation});
        }
        models.emplace(handle,Version{references,{source,kind,std::move(inputs),std::move(text),std::move(paragraph)}});
    }
    for(u32 i=0;i<sources;++i) {
        const auto source=input.key();const auto handle=input.scalar<u32>();current_sources.emplace(source,handle);
    }
}
}
