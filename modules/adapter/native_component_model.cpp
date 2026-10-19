#include "native_component_model.h"
#include "native_component_calls.h"
#include "native_paragraph.h"
#include "native_menu_model.h"
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
        scalar(value.menu);scalar(value.action);scalar(static_cast<u32>(value.locator));scalar(value.row_id);anchor(value.origin);
    }
    void inputs(const NativeHeadingInputs& value) { style(value.style); }
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
                const auto position=input.anchor();return ActionButtonInputs{menu,action,locator,row,position};
            },
            [](Reader& input)->Inputs { return NativeHeadingInputs{input.panel_style()}; },
            [](Reader& input)->Inputs { return NativeHeadingInputs{input.panel_style()};
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
    using Outline=u32 (*)(const Component&);
    static const Outline readers[]{
        [](const Component&)->u32{return 1;},
        [](const Component&)->u32{return 1;},
        [](const Component& c){return std::get<ButtonInputs>(c.inputs).outline;},
        [](const Component& c){return std::get<ParagraphInputs>(c.inputs).outline;},
        [](const Component& c){return std::get<CenteredTextInputs>(c.inputs).outline;},
        [](const Component& c){return std::get<TextBlockInputs>(c.inputs).outline;},
        [](const Component&)->u32{return 0;},
        [](const Component&)->u32{return 0;},
        [](const Component&)->u32{return 1;},
        [](const Component&)->u32{return 1;}
    };
    return readers[static_cast<u32>(component.kind)](component);
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
void paint_action(const ActionButtonInputs& input,const char* label) {
    const auto previous=native_menu_model::active();
    if(previous) native_menu_model::retain(previous);
    native_menu_model::activate(input.menu);
    auto& count=*reinterpret_cast<u32*>(base+0x5F54A34);
    auto& duplicate_mode=*reinterpret_cast<u32*>(base+0x5F549B0);
    const auto total=count;
    const auto previous_mode=duplicate_mode;
    count=input.locator==ActionLocator::native_row ? input.row_id : action_row(input.action);
    duplicate_mode=input.locator==ActionLocator::native_row ? 1u : 0u;
    // The row being updated is outside CFAF0's [0,count) duplicate scan. Its
    // complete native write branch therefore replaces that same row and owns
    // both current-language dimensions and input/hit fields.
    const native_component_calls::ActionButtonCall call{static_cast<u32>(base+0xCFAF0),
        input.action,value(input.origin.x),value(input.origin.y),label};
    native_component_calls::uwcn_component_action_button(&call);
    count=total;duplicate_mode=previous_mode;
    native_menu_model::capture_into(input.menu);
    if(previous) {
        native_menu_model::activate(previous);native_menu_model::release(previous);
    } else native_menu_model::deactivate();
}
}

void initialize(std::uintptr_t image_base) {
    base=image_base;next_handle=1;models.clear();current_sources.clear();bindings.clear();
    native_component_style::initialize(image_base);
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
    using Grammar=void (__fastcall *)(u32,u32);
    reinterpret_cast<Reset>(base+0x1620C0)();
    const auto parse=reinterpret_cast<Parse>(base+0x162300);
    const auto grammar=reinterpret_cast<Grammar>(base+0x161E90);
    for(const auto& node:source.grammar) if(node.after_fragments==0) grammar(node.first_word,node.comma_count);
    for(std::size_t index=0;index<fragments.size();++index) {
        parse(0,fragments[index].data());
        for(const auto& node:source.grammar)
            if(node.after_fragments==index+1) grammar(node.first_word,node.comma_count);
    }
}
const Component& get(Handle handle) { return models.find(handle)->second.component; }
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
            status=services.paragraph_words(prepared.fragments.back());
            if(status!=Status::ok) return status;
        }
    } else {
        prepared.fragments.emplace_back();
        return resolve_text(component.text,services,prepared.fragments.back());
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
        paint_action(input,prepared.fragments.front().data());break;
    }
    case Kind::native_heading_band:case Kind::native_identity_heading: {
        const auto& input=std::get<NativeHeadingInputs>(component.inputs);
        const native_component_style::PanelScope style(input.style);
        const NativeHeadingCall call{static_cast<u32>(base+
            (component.kind==Kind::native_heading_band?0xF8F80:0xF9030)),prepared.fragments.front().data()};
        uwcn_component_native_heading(&call);break;
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
            output.scalar(node.after_fragments);output.scalar(node.first_word);output.scalar(node.comma_count);
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
            paragraph.grammar.push_back({after,first,commas});
        }
        models.emplace(handle,Version{references,{source,kind,std::move(inputs),std::move(text),std::move(paragraph)}});
    }
    for(u32 i=0;i<sources;++i) {
        const auto source=input.key();const auto handle=input.scalar<u32>();current_sources.emplace(source,handle);
    }
}
}
