#include "native_renderer_component_model.h"
#include "native_renderer_component_calls.h"
#include <cstring>
#include <map>
#include <utility>

namespace uwcn::adapter::native_renderer_component_model {
namespace {
std::uintptr_t base{};
Handle next_handle=1;
struct Version { u32 references;Component component; };
std::map<Handle,Version> models;
std::map<SourceKey,Handle> current_sources;
constexpr u32 marked_update_hook=0x7D80;
constexpr u32 native_count=0x5F54A34;
constexpr u32 native_action=0x5F4EFD8;
struct MarkedUpdate { u32 index,total; };
std::vector<MarkedUpdate> marked_updates;

template<class T> T& global(u32 rva) { return *reinterpret_cast<T*>(base+rva); }
void acquire(const Component& component) {
    if(component.kind==Kind::marked_button)
        native_menu_model::retain(std::get<MarkedButtonInputs>(component.inputs).row.owner);
}
void dispose(const Component& component) {
    if(component.kind==Kind::marked_button)
        native_menu_model::release(std::get<MarkedButtonInputs>(component.inputs).row.owner);
}
Handle upsert(Component component) {
    acquire(component);
    const auto source=current_sources.find(component.source);
    if(source!=current_sources.end()) {
        auto& current=models.find(source->second)->second;
        if(current.references==1) {
            dispose(current.component);current.component=std::move(component);
            return source->second;
        }
        const auto old=source->second,handle=next_handle++;
        models.emplace(handle,Version{1,std::move(component)});source->second=handle;
        release(old);return handle;
    }
    const auto key=component.source;const auto handle=next_handle++;
    models.emplace(handle,Version{1,std::move(component)});current_sources.emplace(key,handle);
    return handle;
}
bool measured(const LayoutValue& value) {
    using native_component_model::LayoutSource;
    return value.source==LayoutSource::center_input || value.source==LayoutSource::center_native_i32 ||
        value.source==LayoutSource::right_input || value.source==LayoutSource::right_native_i32;
}
std::int32_t evaluate(const LayoutValue& value,std::int32_t width=0) {
    using Evaluate=std::int32_t (*)(const LayoutValue&,std::int32_t);
    static const Evaluate expressions[]{
        [](const LayoutValue& v,std::int32_t){return v.input;},
        [](const LayoutValue& v,std::int32_t){return global<std::int32_t>(v.rva);},
        [](const LayoutValue& v,std::int32_t w){return v.input-w/2;},
        [](const LayoutValue& v,std::int32_t w){return global<std::int32_t>(v.rva)-w/2;},
        [](const LayoutValue& v,std::int32_t w){return v.input-w;},
        [](const LayoutValue& v,std::int32_t w){return global<std::int32_t>(v.rva)-w;}
    };
    return expressions[static_cast<u32>(value.source)](value,width);
}
u32 text_style(const Component& component) {
    using Read=u32 (*)(const Component&);
    static const Read readers[]{
        [](const Component&)->u32{return 1;},
        [](const Component& c){return std::get<ParagraphInputs>(c.inputs).style;},
        [](const Component& c){return std::get<TextBlockInputs>(c.inputs).style;},
        [](const Component&)->u32{return 1;},
        [](const Component&)->u32{return global<u32>(0x5F54BA0)|2;}
    };
    return readers[static_cast<u32>(component.kind)](component);
}
Status resolve_text(const TextSource& text,const PaintServices& services,std::vector<char>& encoded) {
    return native_text_resource::resolve_source(text,services.resolve,services.encode_original,encoded);
}

// These calls go through the game's currently installed IAT gateways. The
// native target density extension consequently sees the real target selection.
struct TargetScope {
    using Get=u32 (__cdecl *)(u32);
    using Set=int (__cdecl *)(u32,u32);
    u32 renderer,previous;
    Set set;
    explicit TargetScope(NativeTarget target):renderer(target.renderer),
        previous(global<Get>(0x18C26C)(renderer)),set(global<Set>(0x18C288)) {
        set(renderer,target.texture);
    }
    ~TargetScope() { set(renderer,previous); }
};
struct MenuScope {
    native_menu_model::Handle owner,previous;
    explicit MenuScope(native_menu_model::Handle target):owner(target),previous(native_menu_model::active()) {
        if(previous) native_menu_model::retain(previous);
        native_menu_model::activate(owner);
    }
    ~MenuScope() {
        native_menu_model::capture_into(owner);
        if(previous) {
            native_menu_model::activate(previous);native_menu_model::release(previous);
        } else native_menu_model::deactivate();
    }
};
struct MarkedLayoutScope {
    explicit MarkedLayoutScope(u32 action) {
        const auto count=global<u32>(native_count);
        std::map<u32,u32> rows;
        for(u32 index=0;index<count;++index)
            rows.emplace(global<u32>(native_action+index*native_menu_model::row_stride),index);
        marked_updates.push_back({rows.at(action),count});
    }
    ~MarkedLayoutScope() {
        global<u32>(native_count)=marked_updates.back().total;marked_updates.pop_back();
    }
};

struct Writer {
    std::vector<std::uint8_t> bytes;
    template<class T> void scalar(T value) {
        const auto* p=reinterpret_cast<const std::uint8_t*>(&value);
        bytes.insert(bytes.end(),p,p+sizeof(value));
    }
    void string(const std::string& value) {
        scalar(static_cast<u32>(value.size()));bytes.insert(bytes.end(),value.begin(),value.end());
    }
    void key(SourceKey value) { scalar(value.owner);scalar(value.native_source);scalar(value.field); }
    void target(TargetSource value) { scalar(value.lifetime);scalar(value.renderer_owner_rva);scalar(value.texture_owner_rva); }
    void text(const TextSource& value) {
        scalar(static_cast<u32>(value.component));string(value.original);string(value.value);
        scalar(value.has_value?1u:0u);scalar(static_cast<u32>(value.policy));string(value.prefix);string(value.suffix);
    }
    void layout(LayoutValue value) { scalar(static_cast<u32>(value.source));scalar(value.input);scalar(value.rva); }
    void anchor(NativeAnchor value) { layout(value.x);layout(value.y); }
    void inputs(const PanelInputs& v) {
        anchor(v.origin);layout(v.width);layout(v.height);scalar(v.flags);scalar(v.color);
        scalar(v.style.background_mode);scalar(v.style.title_fill_color);
    }
    void inputs(const ParagraphInputs& v) { anchor(v.origin);layout(v.width);layout(v.height);scalar(v.color);scalar(v.style); }
    void inputs(const TextBlockInputs& v) { anchor(v.anchor);scalar(v.color);scalar(v.style); }
    void inputs(const HeadingInputs&) {}
    void inputs(const MarkedButtonInputs& v) { anchor(v.origin);scalar(v.row.owner);scalar(v.row.action); }
};
struct Reader {
    const std::uint8_t* cursor;
    template<class T> T scalar() { T v;std::memcpy(&v,cursor,sizeof(v));cursor+=sizeof(v);return v; }
    std::string string() {
        const auto size=scalar<u32>();std::string v(reinterpret_cast<const char*>(cursor),size);cursor+=size;return v;
    }
    SourceKey key() { const auto owner=scalar<u64>(),source=scalar<u64>();const auto field=scalar<u32>();return {owner,source,field}; }
    TargetSource target() { const auto life=scalar<u64>();const auto renderer=scalar<u32>(),texture=scalar<u32>();return {life,renderer,texture}; }
    TextSource text() {
        const auto component=static_cast<TextComponent>(scalar<u32>());auto original=string(),value=string();
        const bool has=scalar<u32>()!=0;const auto policy=static_cast<native_text_resource::TextPolicy>(scalar<u32>());
        auto prefix=string(),suffix=string();
        return {component,std::move(original),std::move(value),has,policy,std::move(prefix),std::move(suffix)};
    }
    LayoutValue layout() {
        const auto source=static_cast<native_component_model::LayoutSource>(scalar<u32>());
        const auto value=scalar<std::int32_t>();const auto rva=scalar<u32>();return {source,value,rva};
    }
    NativeAnchor anchor() { const auto x=layout(),y=layout();return {x,y}; }
    Inputs inputs(Kind kind) {
        using Decode=Inputs (*)(Reader&);
        static const Decode readers[]{
            [](Reader& in)->Inputs {
                const auto origin=in.anchor();const auto width=in.layout(),height=in.layout();
                const auto flags=in.scalar<u32>(),color=in.scalar<u32>();
                const auto background=in.scalar<u32>(),title=in.scalar<u32>();
                return PanelInputs{origin,width,height,flags,color,{background,title}};
            },
            [](Reader& in)->Inputs {
                const auto origin=in.anchor();const auto width=in.layout(),height=in.layout();
                const auto color=in.scalar<u32>(),style=in.scalar<u32>();return ParagraphInputs{origin,width,height,color,style};
            },
            [](Reader& in)->Inputs {
                const auto anchor=in.anchor();const auto color=in.scalar<u32>(),style=in.scalar<u32>();
                return TextBlockInputs{anchor,color,style};
            },
            [](Reader&)->Inputs {return HeadingInputs{};},
            [](Reader& in)->Inputs {
                const auto origin=in.anchor();const auto owner=in.scalar<u32>(),action=in.scalar<u32>();
                return MarkedButtonInputs{origin,{owner,action}};
            }
        };
        return readers[static_cast<u32>(kind)](*this);
    }
};
}

void initialize(std::uintptr_t image_base) {
    base=image_base;next_handle=1;models.clear();current_sources.clear();marked_updates.clear();
    native_component_style::initialize(image_base);
}
Handle upsert_panel(SourceKey key,TargetSource target,const PanelInputs& inputs,const TextSource& text) {
    return upsert({key,target,Kind::panel,inputs,text,{}});
}
Handle upsert_paragraph(SourceKey key,TargetSource target,const ParagraphInputs& inputs,const ParagraphSource& paragraph) {
    return upsert({key,target,Kind::paragraph,inputs,native_text_resource::original_text(""),paragraph});
}
Handle upsert_text_block(SourceKey key,TargetSource target,const TextBlockInputs& inputs,const TextSource& text) {
    return upsert({key,target,Kind::text_block,inputs,text,{}});
}
Handle upsert_heading(SourceKey key,TargetSource target,const TextSource& text) {
    return upsert({key,target,Kind::heading,HeadingInputs{},text,{}});
}
Handle upsert_marked_button(SourceKey key,TargetSource target,const MarkedButtonInputs& inputs,const TextSource& text) {
    return upsert({key,target,Kind::marked_button,inputs,text,{}});
}
const Component& get(Handle handle) { return models.find(handle)->second.component; }
NativeTarget resolve_target(TargetSource target) {
    return {global<u32>(target.renderer_owner_rva),global<u32>(target.texture_owner_rva)};
}
void retain(Handle handle) { ++models.find(handle)->second.references; }
void release(Handle handle) {
    const auto version=models.find(handle);
    if(--version->second.references==0) { dispose(version->second.component);models.erase(version); }
}
void remove(Handle handle) {
    const auto current=current_sources.find(get(handle).source);
    if(current!=current_sources.end() && current->second==handle) { current_sources.erase(current);release(handle); }
}
void remove_owner(u64 owner) {
    for(auto source=current_sources.begin();source!=current_sources.end();) {
        if(source->first.owner==owner) {
            const auto handle=source->second;source=current_sources.erase(source);release(handle);
        } else ++source;
    }
}
Handle snapshot(Handle handle,TargetSource target,native_menu_model::Handle menu) {
    auto component=get(handle);component.target=target;
    if(component.kind==Kind::marked_button) std::get<MarkedButtonInputs>(component.inputs).row.owner=menu;
    acquire(component);const auto copy=next_handle++;
    models.emplace(copy,Version{1,std::move(component)});return copy;
}
Status prepare(Handle handle,const PaintServices& services,PreparedText& prepared) {
    prepared.fragments.clear();const auto& component=get(handle);
    if(component.kind==Kind::paragraph) {
        for(const auto& text:component.paragraph.fragments) {
            prepared.fragments.emplace_back();auto status=resolve_text(text,services,prepared.fragments.back());
            if(status!=Status::ok) return status;
            status=services.paragraph_words(prepared.fragments.back());if(status!=Status::ok) return status;
        }
    } else {
        prepared.fragments.emplace_back();return resolve_text(component.text,services,prepared.fragments.back());
    }
    return Status::ok;
}
Status paint(Handle handle,const PaintServices& services) {
    PreparedText prepared;auto status=prepare(handle,services,prepared);if(status!=Status::ok) return status;
    const auto& component=get(handle);const auto target=resolve_target(component.target);
    const TargetScope target_scope(target);
    using namespace native_renderer_component_calls;
    if(component.kind==Kind::marked_button) {
        const auto& input=std::get<MarkedButtonInputs>(component.inputs);
        const MenuScope menu(input.row.owner);const MarkedLayoutScope layout(input.row.action);
        services.enter(handle,component.kind,text_style(component));
        const MarkedButtonCall call{static_cast<u32>(base+0xCFD10),target.texture,input.row.action,
            evaluate(input.origin.x),evaluate(input.origin.y),prepared.fragments.front().data()};
        uwcn_renderer_marked_button(&call);services.leave(handle,component.kind);return Status::ok;
    }
    services.enter(handle,component.kind,text_style(component));
    switch(component.kind) {
    case Kind::panel: {
        const auto& input=std::get<PanelInputs>(component.inputs);
        const native_component_style::PanelScope style(input.style);
        const PanelCall call{static_cast<u32>(base+0x1166C0),target.renderer,
            evaluate(input.origin.x),evaluate(input.origin.y),evaluate(input.width),evaluate(input.height),
            prepared.fragments.front().data(),input.flags,input.color};
        uwcn_renderer_panel(&call);break;
    }
    case Kind::paragraph: {
        using Parse=void (__fastcall *)(u32,const char*);const auto parse=reinterpret_cast<Parse>(base+0x162300);
        parse(1,"");for(const auto& fragment:prepared.fragments) parse(0,fragment.data());
        const auto& input=std::get<ParagraphInputs>(component.inputs);
        const ParagraphCall call{static_cast<u32>(base+0x10EFD0),target.renderer,
            evaluate(input.origin.x),evaluate(input.origin.y),evaluate(input.width),evaluate(input.height),input.color,input.style};
        uwcn_renderer_paragraph(&call);break;
    }
    case Kind::text_block: {
        const auto& input=std::get<TextBlockInputs>(component.inputs);std::int32_t width{};
        if(measured(input.anchor.x)) {
            status=services.measure(prepared.fragments.front().data(),width);
            if(status!=Status::ok) {services.leave(handle,component.kind);return status;}
        }
        const TextBlockCall call{static_cast<u32>(base+0x10E260),target.renderer,
            evaluate(input.anchor.x,width),evaluate(input.anchor.y),prepared.fragments.front().data(),input.color,input.style};
        uwcn_renderer_text_block(&call);break;
    }
    case Kind::heading: {
        const HeadingCall call{static_cast<u32>(base+0x113430),target.texture,prepared.fragments.front().data()};
        uwcn_renderer_heading(&call);break;
    }
    case Kind::marked_button: break;
    }
    services.leave(handle,component.kind);return Status::ok;
}
void append_hooks(std::vector<HookSpec>& hooks) {
    // MOV [61BBAC4],0 is replayable and preserves flags. It precedes the
    // native TEST ESI/JNE; the branch itself remains completely unmodified.
    HookSpec hook{marked_update_hook,HookKind::inline_code,0xCFE08,0,0,10,{0xC7,0x05}};
    const auto destination=static_cast<u32>(base+0x61BBAC4);
    std::memcpy(hook.expected+2,&destination,sizeof(destination));hooks.push_back(hook);
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id==marked_update_hook;
    if(handled && !marked_updates.empty()) {
        global<u32>(native_count)=marked_updates.back().index;event.frame->esi=0;
    }
    return Status::ok;
}
std::vector<std::uint8_t> save() {
    Writer output;output.scalar(next_handle);output.scalar(static_cast<u32>(models.size()));
    output.scalar(static_cast<u32>(current_sources.size()));
    for(const auto& [handle,version]:models) {
        output.scalar(handle);output.scalar(version.references);const auto& component=version.component;
        output.key(component.source);output.target(component.target);output.scalar(static_cast<u32>(component.kind));
        std::visit([&output](const auto& input){output.inputs(input);},component.inputs);output.text(component.text);
        output.scalar(static_cast<u32>(component.paragraph.fragments.size()));
        for(const auto& fragment:component.paragraph.fragments) output.text(fragment);
    }
    for(const auto& [key,handle]:current_sources) {output.key(key);output.scalar(handle);}
    return std::move(output.bytes);
}
void restore(const void* payload) {
    Reader input{static_cast<const std::uint8_t*>(payload)};next_handle=input.scalar<u32>();
    const auto count=input.scalar<u32>(),sources=input.scalar<u32>();models.clear();current_sources.clear();marked_updates.clear();
    for(u32 index=0;index<count;++index) {
        const auto handle=input.scalar<u32>(),references=input.scalar<u32>();const auto key=input.key();const auto target=input.target();
        const auto kind=static_cast<Kind>(input.scalar<u32>());auto inputs=input.inputs(kind);auto text=input.text();ParagraphSource paragraph;
        const auto fragments=input.scalar<u32>();for(u32 j=0;j<fragments;++j) paragraph.fragments.push_back(input.text());
        // Menu reference ownership was serialized by native_menu_model. It is
        // restored once there, rather than acquired for a second time here.
        models.emplace(handle,Version{references,{key,target,kind,std::move(inputs),std::move(text),std::move(paragraph)}});
    }
    for(u32 index=0;index<sources;++index) {const auto key=input.key();const auto handle=input.scalar<u32>();current_sources.emplace(key,handle);}
}
void shutdown() {
    for(const auto& [handle,version]:models) { (void)handle;dispose(version.component); }
    models.clear();current_sources.clear();marked_updates.clear();
}
}
