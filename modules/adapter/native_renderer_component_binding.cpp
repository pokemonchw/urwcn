#include "native_renderer_component_binding.h"
#include "native_component_binding.h"
#include "native_root_component.h"
#include "native_targets.h"
#include "native_ui_scene.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <map>
#include <utility>

namespace uwcn::adapter::native_renderer_component_binding {
namespace {
namespace model=native_renderer_component_model;
using native_text_resource::SourceKey;
using native_text_resource::TextSource;
using native_component_model::native_input;
using native_component_model::native_center;
constexpr u32 main_renderer=0xA2110CC,magic_owner=0x5F8FAB8,infobox_owner=0x61BB644;
enum Hook:u32 { magic_created=0x7D90,infobox_created,magic_background,
    magic_panel_first,magic_panel_second,infobox_panel,footer_panel };
enum class Background:u32 { native_surface,native_panel };
struct Constructor { u32 format;std::int32_t access,width,height; };
struct Owner {
    SourceKey key;model::TargetSource target;Constructor constructor;
    Background background;u32 surface_owner;std::int32_t background_width,background_height;
    bool initialized;
    MenuHandle menu;
    std::vector<model::Handle> children;
};
struct Version { u32 references;Owner owner; };
struct EventInput { u64 token;u32 id,ecx,edx;std::array<u32,6> arguments; };
struct Borrow { model::Handle component;u32 owner;model::PreparedText text; };
std::uintptr_t base{};
model::PaintServices services{};
u32 next_handle=1;
u64 next_lifetime=1;
std::map<Handle,Version> owners;
std::map<u32,Handle> current_owners;
std::map<u32,u32> native_resources;
std::map<u32,HookSpec> metadata;
std::vector<EventInput> events;
std::map<u64,Borrow> borrows;
bool painting{},preparing{};

template<class T> T& native(u32 rva) { return *reinterpret_cast<T*>(base+rva); }
template<class T> T* pointer(u32 value) { return reinterpret_cast<T*>(static_cast<std::uintptr_t>(value)); }
u32 address(const void* value) { return static_cast<u32>(reinterpret_cast<std::uintptr_t>(value)); }
std::int32_t number(u32 value) {return static_cast<std::int32_t>(value);}
HookSpec call(u32 id,u32 site,u32 target,u32 count) {
    HookSpec value{id,HookKind::call,site,target,count,5,{0xE8}};
    const auto relative=target-site-5;std::memcpy(value.expected+1,&relative,sizeof(relative));return value;
}
void retain_children(const Owner& owner) { for(const auto child:owner.children) model::retain(child); }
void release_children(const Owner& owner) { for(const auto child:owner.children) model::release(child); }
Handle writable(u32 field) {
    auto& current=current_owners.find(field)->second;
    if(owners.find(current)->second.references>1) {
        auto copy=owners.find(current)->second.owner;retain_children(copy);
        const auto previous=current;current=next_handle++;
        owners.emplace(current,Version{1,std::move(copy)});release(previous);
    }
    return current;
}
void adopt(u32 field,model::Handle component) {
    const auto handle=writable(field);auto& owner=owners.find(handle)->second.owner;
    const auto& key=model::get(component).source;
    const auto previous=std::find_if(owner.children.begin(),owner.children.end(),
        [&](model::Handle child){return model::get(child).source==key;});
    model::retain(component);
    if(previous==owner.children.end()) owner.children.push_back(component);
    else {model::release(*previous);*previous=component;}
    if(model::get(component).kind==model::Kind::marked_button)
        owner.menu=std::get<model::MarkedButtonInputs>(model::get(component).inputs).row.owner;
    if(owner.initialized) native_ui_scene::renderer_constructed(handle);
}
void created(const NativeEvent& event,u32 field,Background background) {
    const auto* args=pointer<const u32>(event.frame->esp);
    // These are the original cdecl SDL_CreateTexture arguments still on the
    // native stack immediately after DF98F/DFC75, before caller cleanup.
    const Constructor constructor{args[1],number(args[2]),number(args[3]),number(args[4])};
    const auto life=next_lifetime++;
    const auto handle=next_handle++;
    Owner owner{{native_root_component::current(),field,0},
        {life,main_renderer,field},constructor,background,0,0,0,false,0,{}};
    owners.emplace(handle,Version{1,std::move(owner)});
    const auto old=current_owners.find(field);
    if(old!=current_owners.end()) {const auto previous=old->second;old->second=handle;release(previous);}
    else current_owners.emplace(field,handle);
    native_resources.insert_or_assign(field,event.frame->eax);
}
u32 owner_field(const HookSpec& hook) {
    switch(hook.site_rva) {
    case 0xDFD10:case 0xDFCEF:return infobox_owner;
    default:return magic_owner;
    }
}
bool semantic_component_site(u32 site) {
    switch(site) {
    case 0xDF9C1:case 0xDFAA6:case 0xDFB4B:case 0xDFD10:
    case 0xDF9FB:case 0xDFA3F:case 0xDFCEF:case 0x3CDED:
    case 0xDFF85:case 0xDFFEC:case 0x3CFA8:case 0x3CE45:case 0x3CF2F:return true;
    default:return false;
    }
}
SourceKey component_key(const Owner& owner,const HookSpec& hook,const EventInput& input,TextComponent field) {
    u64 identity=hook.site_rva;
    if(hook.target_rva==0xCFD10) identity=(identity<<32)|input.edx;
    u32 record;
    if(native_component_binding::current_event_record(record)) identity=(static_cast<u64>(hook.site_rva)<<32)|record;
    return {owner.target.lifetime,identity,static_cast<u32>(field)};
}
TextComponent paragraph_field(const model::ParagraphSource& paragraph) {
    const auto semantic=std::find_if(paragraph.fragments.begin(),paragraph.fragments.end(),
        [](const TextSource& text){return text.policy==native_text_resource::TextPolicy::semantic;});
    return semantic==paragraph.fragments.end()?TextComponent::load_character:semantic->component;
}
Status construct(const NativeEvent& event,const HookSpec& hook,const EventInput& input) {
    const auto field=owner_field(hook);
    const auto& owner=owners.find(current_owners.find(field)->second)->second.owner;
    const auto& args=input.arguments;
    const auto* text=native_component_binding::current_event_source();
    TextSource panel_title;
    if(hook.target_rva==0x1166C0 && !text) {
        panel_title=native_text_resource::original_text(pointer<const char>(args[3]));text=&panel_title;
    }
    // Only already connected semantic producers are adopted. Internal leaf
    // renderer calls do not synthesize an owner or a new semantic resource.
    if(hook.target_rva!=0x10EFD0 && !text) return Status::ok;
    model::Handle component{};u32 text_argument{};
    const native_component_model::NativeAnchor origin{native_input(number(input.edx)),native_input(number(args[0]))};
    switch(hook.target_rva) {
    case 0x1166C0: {
        const model::PanelInputs inputs{origin,native_input(number(args[1])),native_input(number(args[2])),
            args[4],args[5],native_component_style::capture_panel()};
        component=model::upsert_panel(component_key(owner,hook,input,text->component),owner.target,inputs,*text);
        text_argument=3;break;
    }
    case 0x10EFD0: {
        const auto& paragraph=native_component_binding::current_paragraph_source();
        const model::ParagraphInputs inputs{origin,native_input(number(args[1])),native_input(number(args[2])),args[3],args[4]};
        component=model::upsert_paragraph(component_key(owner,hook,input,paragraph_field(paragraph)),owner.target,inputs,paragraph);break;
    }
    case 0x10E260: {
        auto anchor=origin;std::int32_t center;
        if(native_component_binding::current_event_center(center)) anchor.x=native_center(center);
        const model::TextBlockInputs inputs{anchor,args[2],args[3]};
        component=model::upsert_text_block(component_key(owner,hook,input,text->component),owner.target,inputs,*text);
        text_argument=1;break;
    }
    case 0x113430:
        component=model::upsert_heading(component_key(owner,hook,input,text->component),owner.target,*text);break;
    case 0xCFD10: {
        const model::MarkedButtonInputs inputs{{native_input(number(args[0])),native_input(number(args[1]))},
            {native_menu_model::active(),input.edx}};
        component=model::upsert_marked_button(component_key(owner,hook,input,text->component),owner.target,inputs,*text);
        text_argument=2;break;
    }
    }
    model::retain(component);auto& borrowed=borrows[event.token];borrowed.component=component;borrowed.owner=field;
    preparing=true;native_component_binding::begin_source_resolution();
    const auto status=model::prepare(component,services,borrowed.text);
    native_component_binding::end_source_resolution();preparing=false;
    if(status!=Status::ok) return status;
    if(hook.target_rva==0x10EFD0) {
        // Install this identical neutral paragraph through the shared parser
        // protocol. Its own synchronous parser observer does not record output.
        return native_component_binding::replace_paragraph_builder(model::get(component).paragraph);
    }
    const auto text_address=address(borrowed.text.fragments.front().data());
    if(hook.target_rva==0x113430) event.frame->edx=text_address;
    else event.arguments[text_argument]=text_address;
    return Status::ok;
}
struct BackgroundCall {u32 function,surface,texture;std::int32_t width,height;};
extern "C" __attribute__((naked)) void UWCN_CALL renderer_background(const BackgroundCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t" "movl 8(%esp),%ebx\n\t"
        "pushl 16(%ebx)\n\t" "pushl 12(%ebx)\n\t"
        "pushl $0\n\t" "pushl $0\n\t" "pushl 8(%ebx)\n\t"
        "xorl %ecx,%ecx\n\t" "movl 4(%ebx),%edx\n\t"
        "call *(%ebx)\n\t" "addl $20,%esp\n\t" "popl %ebx\n\t" "ret\n\t");
}
struct Writer {
    std::vector<std::uint8_t> bytes;
    template<class T> void value(T v) {
        const auto* p=reinterpret_cast<const std::uint8_t*>(&v);bytes.insert(bytes.end(),p,p+sizeof(v));
    }
    void key(SourceKey v) {value(v.owner);value(v.native_source);value(v.field);}
};
struct Reader {
    const std::uint8_t* cursor;
    template<class T> T value() {T v;std::memcpy(&v,cursor,sizeof(v));cursor+=sizeof(v);return v;}
    SourceKey key() {const auto owner=value<u64>(),id=value<u64>();const auto field=value<u32>();return {owner,id,field};}
};
}

void configure(std::uintptr_t image_base,const model::PaintServices& paint_services) {
    base=image_base;services=paint_services;next_handle=1;next_lifetime=1;
    owners.clear();current_owners.clear();native_resources.clear();metadata.clear();events.clear();borrows.clear();painting=false;preparing=false;
    native_targets::observe_component_texture_retirement(native_texture_destroying);
}
void register_hooks(std::vector<HookSpec>& hooks) {
    HookSpec magic{magic_created,HookKind::inline_code,0xDF995,0,0,6,{0x8B,0x15}};
    const auto surface=static_cast<u32>(base+0x61BB648);std::memcpy(magic.expected+2,&surface,4);hooks.push_back(magic);
    HookSpec infobox{infobox_created,HookKind::inline_code,0xDFC7B,0,0,7,{0x8B,0x0C,0xB5}};
    const auto rituals=static_cast<u32>(base+0x5F5CD48);std::memcpy(infobox.expected+3,&rituals,4);hooks.push_back(infobox);
    hooks.push_back(call(magic_background,0xDF9B1,0x113090,5));
    hooks.push_back(call(magic_panel_first,0xDF9FB,0x1166C0,6));
    hooks.push_back(call(magic_panel_second,0xDFA3F,0x1166C0,6));
    hooks.push_back(call(infobox_panel,0xDFCEF,0x1166C0,6));
    hooks.push_back(call(footer_panel,0x3CDED,0x1166C0,6));
    metadata.clear();for(const auto& hook:hooks) metadata.emplace(hook.id,hook);
}
void begin_event(const NativeEvent& event) {
    EventInput input{event.token,event.id,event.frame->ecx,event.frame->edx,{}};
    const auto hook=metadata.find(event.id);
    if(hook!=metadata.end() && hook->second.kind==HookKind::call)
        std::copy_n(event.arguments,std::min<u32>(event.argument_count,static_cast<u32>(input.arguments.size())),input.arguments.begin());
    events.push_back(input);
}
Status finish_event(const NativeEvent& event,DispatchResult&,Status status) {
    const auto input=events.back();events.pop_back();
    if(event.phase==NativePhase::after) {
        const auto borrow=borrows.find(event.token);
        if(borrow!=borrows.end()) {
            if(status==Status::ok) {
                if(event.id==infobox_panel) owners.find(writable(borrow->second.owner))->second.owner.initialized=true;
                adopt(borrow->second.owner,borrow->second.component);
            }
            model::release(borrow->second.component);borrows.erase(borrow);
        }
        if(event.id==magic_background && status==Status::ok && !painting) {
            const auto handle=writable(magic_owner);owners.find(handle)->second.owner.initialized=true;
            native_ui_scene::renderer_constructed(handle);
        }
        return status;
    }
    if(status!=Status::ok || painting || preparing || native_ui_scene::materializing()) return status;
    if(event.id==magic_created) {created(event,magic_owner,Background::native_surface);return Status::ok;}
    if(event.id==infobox_created) {created(event,infobox_owner,Background::native_panel);return Status::ok;}
    if(event.id==magic_background) {
        auto& owner=owners.find(writable(magic_owner))->second.owner;
        owner.surface_owner=0x61BB648;owner.background_width=number(input.arguments[3]);owner.background_height=number(input.arguments[4]);
        event.frame->edx=native<u32>(owner.surface_owner);return Status::ok;
    }
    const auto hook=metadata.find(event.id);
    if(hook==metadata.end() || hook->second.kind!=HookKind::call) return Status::ok;
    if(!semantic_component_site(hook->second.site_rva)) return Status::ok;
    if(native_component_binding::consuming_component() || native_component_binding::parser_owned()) return Status::ok;
    switch(hook->second.target_rva) {
    case 0x113430:case 0x10EFD0:case 0x1166C0:case 0x10E260:case 0xCFD10:
        return construct(event,hook->second,input);
    default:return Status::ok;
    }
}
const SourceKey& source(Handle handle) {return owners.find(handle)->second.owner.key;}
MenuHandle menu_owner(Handle handle) {return owners.find(handle)->second.owner.menu;}
void retain(Handle handle) {++owners.find(handle)->second.references;}
void release(Handle handle) {
    const auto owner=owners.find(handle);if(--owner->second.references==0) {release_children(owner->second.owner);owners.erase(owner);}
}
Handle snapshot(Handle handle,MenuHandle menu) {
    auto copy=owners.find(handle)->second.owner;copy.menu=menu;
    for(auto& child:copy.children) child=model::snapshot(child,copy.target,menu);
    const auto result=next_handle++;owners.emplace(result,Version{1,std::move(copy)});return result;
}
Status paint(Handle handle,PaintDestination destination) {
    const auto& owner=owners.find(handle)->second.owner;
    const auto field=owner.target.texture_owner_rva;const auto previous=native<u32>(field);
    const auto renderer=native<u32>(owner.target.renderer_owner_rva);
    using GetTarget=u32 (__cdecl *)(u32);
    using SetTarget=int (__cdecl *)(u32,u32);
    const auto caller_target=native<GetTarget>(0x18C26C)(renderer);
    const auto set_target=native<SetTarget>(0x18C288);
    const auto& ctor=owner.constructor;
    const auto texture=native_targets::create_component_texture(renderer,ctor.format,ctor.access,ctor.width,ctor.height);
    if(!texture) return Status::failed;
    std::vector<std::pair<u32,u32>> aliases;
    if(field==magic_owner) {
        for(const auto alias:{0x5F4EB08u,0xA1C1CBCu})
            if(native<u32>(alias)==previous) {aliases.push_back({alias,previous});native<u32>(alias)=texture;}
    }
    native<u32>(field)=texture;painting=true;
    if(owner.background==Background::native_surface) {
        const BackgroundCall call{static_cast<u32>(base+0x113090),native<u32>(owner.surface_owner),texture,
            owner.background_width,owner.background_height};renderer_background(&call);
    }
    Status status=Status::ok;
    for(const auto child:owner.children) {status=model::paint(child,services);if(status!=Status::ok) break;}
    if(destination==PaintDestination::native_surface_cache || status!=Status::ok) {
        native<u32>(field)=previous;for(const auto [alias,value]:aliases) native<u32>(alias)=value;
        set_target(renderer,caller_target);
        native_targets::destroy_component_texture(texture);
    } else {
        native_resources.insert_or_assign(field,texture);
        set_target(renderer,previous && caller_target==previous?texture:caller_target);
        if(previous) native_targets::destroy_component_texture(previous);
    }
    painting=false;return status;
}
void activate(Handle handle) {
    const auto field=owners.find(handle)->second.owner.target.texture_owner_rva;
    const auto current=current_owners.find(field);
    retain(handle);
    if(current!=current_owners.end()) {const auto previous=current->second;current->second=handle;release(previous);}
    else current_owners.emplace(field,handle);
}
void native_texture_destroying(u32 texture) {
    if(painting) return;
    for(auto resource=native_resources.begin();resource!=native_resources.end();) {
        if(resource->second==texture) {
            const auto field=resource->first;const auto owner=current_owners.find(field);
            model::remove_owner(owners.find(owner->second)->second.owner.target.lifetime);
            native_ui_scene::renderer_retired(source(owner->second));
            const auto previous=owner->second;current_owners.erase(owner);release(previous);
            resource=native_resources.erase(resource);
        } else ++resource;
    }
}
void menu_retired(Handle handle,MenuHandle menu) {
    const auto field=owners.find(handle)->second.owner.target.texture_owner_rva;
    const auto next=writable(field);auto& owner=owners.find(next)->second.owner;
    for(auto child=owner.children.begin();child!=owner.children.end();) {
        const auto& component=model::get(*child);
        if(component.kind==model::Kind::marked_button && std::get<model::MarkedButtonInputs>(component.inputs).row.owner==menu) {
            const auto previous=*child;child=owner.children.erase(child);model::remove(previous);model::release(previous);
        } else ++child;
    }
    owner.menu=0;native_ui_scene::renderer_constructed(next);
}
std::vector<std::uint8_t> save() {
    Writer out;out.value(next_handle);out.value(next_lifetime);out.value(static_cast<u32>(owners.size()));
    out.value(static_cast<u32>(current_owners.size()));out.value(static_cast<u32>(native_resources.size()));
    for(const auto& [handle,version]:owners) {
        out.value(handle);out.value(version.references);const auto& v=version.owner;
        out.key(v.key);out.value(v.target.lifetime);out.value(v.target.renderer_owner_rva);out.value(v.target.texture_owner_rva);
        out.value(v.constructor.format);out.value(v.constructor.access);out.value(v.constructor.width);out.value(v.constructor.height);
        out.value(static_cast<u32>(v.background));out.value(v.surface_owner);out.value(v.background_width);out.value(v.background_height);
        out.value(v.initialized?1u:0u);out.value(v.menu);out.value(static_cast<u32>(v.children.size()));for(const auto child:v.children) out.value(child);
    }
    for(const auto [field,handle]:current_owners) {out.value(field);out.value(handle);}
    for(const auto [field,texture]:native_resources) {out.value(field);out.value(texture);}
    return std::move(out.bytes);
}
void restore(const void* payload) {
    Reader in{static_cast<const std::uint8_t*>(payload)};next_handle=in.value<u32>();next_lifetime=in.value<u64>();
    const auto count=in.value<u32>(),current=in.value<u32>(),resources=in.value<u32>();
    owners.clear();current_owners.clear();native_resources.clear();events.clear();borrows.clear();painting=false;preparing=false;
    for(u32 index=0;index<count;++index) {
        const auto handle=in.value<u32>(),references=in.value<u32>();Owner v{};v.key=in.key();
        v.target.lifetime=in.value<u64>();v.target.renderer_owner_rva=in.value<u32>();v.target.texture_owner_rva=in.value<u32>();
        v.constructor.format=in.value<u32>();v.constructor.access=in.value<std::int32_t>();
        v.constructor.width=in.value<std::int32_t>();v.constructor.height=in.value<std::int32_t>();
        v.background=static_cast<Background>(in.value<u32>());v.surface_owner=in.value<u32>();
        v.background_width=in.value<std::int32_t>();v.background_height=in.value<std::int32_t>();v.initialized=in.value<u32>()!=0;
        v.menu=in.value<u32>();const auto children=in.value<u32>();for(u32 child=0;child<children;++child) v.children.push_back(in.value<u32>());
        owners.emplace(handle,Version{references,std::move(v)});
    }
    for(u32 index=0;index<current;++index) {const auto field=in.value<u32>();current_owners.emplace(field,in.value<u32>());}
    for(u32 index=0;index<resources;++index) {const auto field=in.value<u32>();native_resources.emplace(field,in.value<u32>());}
}
void shutdown() {
    native_targets::observe_component_texture_retirement(nullptr);
    for(const auto& [handle,version]:owners) {(void)handle;release_children(version.owner);}
    owners.clear();current_owners.clear();native_resources.clear();metadata.clear();events.clear();borrows.clear();services={};base=0;
}
}
