#include "native_renderer_component_binding.h"
#include "native_component_binding.h"
#include "native_root_component.h"
#include "native_targets.h"
#include "native_ui_scene.h"
#include "native_hud_icons.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <map>
#include <optional>
#include <utility>

namespace uwcn::adapter::native_renderer_component_binding {
namespace {
namespace model=native_renderer_component_model;
using native_text_resource::SourceKey;
using native_text_resource::TextSource;
using native_component_model::native_input;
using native_component_model::native_center;
constexpr u32 main_renderer=0xA2110CC,magic_owner=0x5F8FAB8,infobox_owner=0x61BB644;
constexpr u32 hud_surface=0x61BBB04,hud_renderer=0x61BBB0C,hud_overlay=0x61BBAF4;
constexpr u32 known_map_owner=0x5F937B0;
enum Hook:u32 { magic_created=0x7D90,infobox_created,magic_background,
    magic_panel_first,magic_panel_second,infobox_panel,footer_panel,
    hud_frame_begin,hud_frame_end,hud_overlay_begin,map_factory,map_created,map_title,map_help,
    map_consumer_first,map_consumer_cultures,map_consumer_indicators,hud_copy,hud_copy_previous };
enum class Background:u32 { native_surface,native_panel,native_hud_frame,native_overlay_clear,native_known_map };
struct Constructor { u32 format;std::int32_t access,width,height; };
// E3D90 is a complete native UI resource constructor. The first paragraph's
// return value feeds the original panel and second paragraph directly; no
// derived height or final geometry is retained in this source.
struct MapInputs {
    native_component_style::PanelStyle panel;
    u32 secondary_color;
    TextSource title;
    model::ParagraphSource help;
    bool consumed;
    std::array<std::uint8_t,2> visibility;
};
struct Owner {
    SourceKey key;model::TargetSource target;Constructor constructor;
    Background background;u32 surface_owner;std::int32_t background_width,background_height;
    bool initialized;
    MenuHandle menu;
    std::vector<model::Handle> children;
    native_targets::SurfaceSource software_constructor{};
    std::vector<native_hud_icons::Handle> icons;
    MapInputs map;
    bool copied{};
    u32 copied_slot{};
};
struct Version { u32 references;Owner owner; };
struct EventInput { u64 token;u32 id,ecx,edx;std::array<u32,6> arguments; };
struct Borrow { model::Handle component;u32 owner;model::PreparedText text;bool entered; };
std::uintptr_t base{};
model::PaintServices services{};
native_culture_legend::Services resource_services{};
u32 next_handle=1;
u64 next_lifetime=1;
std::map<Handle,Version> owners;
std::map<u32,Handle> current_owners;
std::map<u32,u32> native_resources;
std::map<u32,HookSpec> metadata;
std::vector<EventInput> events;
std::map<u64,Borrow> borrows;
bool painting{},preparing{};
enum class BackgroundPaint:u32 { none,hud_frame,overlay };
BackgroundPaint background_paint{};
std::optional<MapInputs> ordinary_map;
u64 ordinary_map_scope{};
const Owner* map_paint_source{};
std::map<u64,std::vector<char>> map_title_borrows;
struct CacheResource {
    bool hud;
    u32 field,previous,replacement,renderer,caller_target;
    std::vector<std::pair<u32,u32>> aliases;
    native_targets::HudTarget previous_hud{},replacement_hud{};
};
std::vector<std::vector<CacheResource>> cache_resources;
struct HeadingCopy {bool building;u32 previous;};
HeadingCopy heading_copy{};

template<class T> T& native(u32 rva) { return *reinterpret_cast<T*>(base+rva); }
template<class T> T* pointer(u32 value) { return reinterpret_cast<T*>(static_cast<std::uintptr_t>(value)); }
u32 address(const void* value) { return static_cast<u32>(reinterpret_cast<std::uintptr_t>(value)); }
std::int32_t number(u32 value) {return static_cast<std::int32_t>(value);}
HookSpec call(u32 id,u32 site,u32 target,u32 count) {
    HookSpec value{id,HookKind::call,site,target,count,5,{0xE8}};
    const auto relative=target-site-5;std::memcpy(value.expected+1,&relative,sizeof(relative));return value;
}
u32 owner_field(const Owner& owner) {
    return owner.target.kind==model::TargetKind::software_surface ?
        owner.target.surface_owner_rva : owner.target.texture_owner_rva;
}
void retain_children(const Owner& owner) {
    for(const auto child:owner.children) model::retain(child);
    for(const auto icon:owner.icons) native_hud_icons::retain(icon);
}
void release_children(const Owner& owner) {
    for(const auto child:owner.children) model::release(child);
    for(const auto icon:owner.icons) native_hud_icons::release(icon);
}
void retire_current(u32 field) {
    const auto current=current_owners.find(field);
    if(current!=current_owners.end()) {
        const auto previous=current->second;
        const auto life=owners.find(previous)->second.owner.target.lifetime;
        model::remove_owner(life);native_hud_icons::remove_owner(life);
        native_ui_scene::renderer_retired(source(previous));
        current_owners.erase(current);release(previous);
    }
}
void begin_hud() {
    const auto constructor=native_targets::component_surface_source(pointer<void>(native<u32>(hud_surface)));
    retire_current(hud_surface);
    const auto handle=next_handle++;const auto life=next_lifetime++;
    Owner owner{{native_root_component::current(),hud_surface,0},
        {life,hud_renderer,0,model::TargetKind::software_surface,hud_surface},
        {0,0,constructor.width,constructor.height},Background::native_hud_frame,0,0,0,false,0,{}};
    owner.software_constructor=constructor;
    owners.emplace(handle,Version{1,std::move(owner)});current_owners.emplace(hud_surface,handle);
    native_resources.insert_or_assign(hud_surface,native<u32>(hud_surface));
}
Status begin_overlay() {
    native_targets::TextureSource constructor;
    const auto status=native_targets::component_texture_source(native<u32>(hud_overlay),constructor);
    if(status!=Status::ok) return status;
    retire_current(hud_overlay);
    const auto handle=next_handle++;const auto life=next_lifetime++;
    Owner owner{{native_root_component::current(),hud_overlay,0},{life,main_renderer,hud_overlay},
        {constructor.format,constructor.access,constructor.width,constructor.height},
        Background::native_overlay_clear,0,0,0,true,0,{}};
    owners.emplace(handle,Version{1,std::move(owner)});current_owners.emplace(hud_overlay,handle);
    native_resources.insert_or_assign(hud_overlay,native<u32>(hud_overlay));return Status::ok;
}
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
    if(background==Background::native_known_map) owner.map=*ordinary_map;
    owners.emplace(handle,Version{1,std::move(owner)});
    const auto old=current_owners.find(field);
    if(old!=current_owners.end()) {const auto previous=old->second;old->second=handle;release(previous);}
    else current_owners.emplace(field,handle);
    native_resources.insert_or_assign(field,event.frame->eax);
}
MapInputs map_inputs() {
    return {native_component_style::capture_panel(),native<u32>(0xA3849F4),
        {},{},false,{native<std::uint8_t>(0x1EBCAC),native<std::uint8_t>(0x1EBCAD)}};
}
struct MapConstruction {
    native_component_style::PanelScope panel;
    u32 secondary;
    std::array<std::uint8_t,2> visibility;
    u64 revision;
    MapConstruction(const Owner& owner):panel(owner.map.panel),secondary(native<u32>(0xA3849F4)),
        visibility{native<std::uint8_t>(0x1EBCAC),native<std::uint8_t>(0x1EBCAD)},revision(owner.target.lifetime) {
        native<u32>(0xA3849F4)=owner.map.secondary_color;
        native<std::uint8_t>(0x1EBCAC)=owner.map.visibility[0];native<std::uint8_t>(0x1EBCAD)=owner.map.visibility[1];
        resource_services.enter(revision);
    }
    ~MapConstruction() {
        resource_services.leave(revision);native<u32>(0xA3849F4)=secondary;
        native<std::uint8_t>(0x1EBCAC)=visibility[0];native<std::uint8_t>(0x1EBCAD)=visibility[1];
    }
};
Status prepare_map_title(const NativeEvent& event,const TextSource& text) {
    auto& borrowed=map_title_borrows[event.token];
    native_component_binding::begin_source_resolution();
    const auto status=native_text_resource::resolve_source(text,services.resolve,services.encode_original,borrowed);
    native_component_binding::end_source_resolution();
    if(status==Status::ok) event.frame->edx=address(borrowed.data());
    return status;
}
u32 owner_field(const HookSpec& hook) {
    switch(hook.site_rva) {
    case 0xFAC9C:case 0xFACF2:case 0xFAE38:case 0xFAEFF:return hud_surface;
    case 0xDFD10:case 0xDFCEF:return infobox_owner;
    default:return magic_owner;
    }
}
bool semantic_component_site(u32 site) {
    switch(site) {
    case 0xFAC9C:case 0xFACF2:case 0xFAE38:case 0xFAEFF:
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
    case 0x111560: {
        const model::LabelBoxInputs inputs{origin,native_input(number(args[1])),args[3]};
        component=model::upsert_label_box(component_key(owner,hook,input,text->component),owner.target,inputs,*text);
        text_argument=2;break;
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
    services.enter(component,model::get(component).kind,model::display_style(component));borrowed.entered=true;
    if(hook.target_rva==0x10EFD0) {
        // Install this identical neutral paragraph through the shared parser
        // protocol. Its own synchronous parser observer does not record output.
        return native_component_binding::consume_paragraph_source(model::get(component).paragraph);
    }
    const auto text_address=address(borrowed.text.fragments.front().data());
    if(hook.target_rva==0x113430) event.frame->edx=text_address;
    else event.arguments[text_argument]=text_address;
    return Status::ok;
}
struct BackgroundCall {u32 function,surface,texture;std::int32_t width,height;};
struct HudFrameCall {u32 function,color_import;};
extern "C" __attribute__((naked)) void UWCN_CALL renderer_hud_frame(const HudFrameCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t" "movl 8(%esp),%eax\n\t"
        "movl 4(%eax),%ebx\n\t" "call *(%eax)\n\t"
        "popl %ebx\n\t" "ret\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL renderer_hud_frame_return() {
    __asm__ __volatile__("addl $8,%esp\n\tret\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL renderer_overlay_body() {
    __asm__ __volatile__("subl $32,%esp\n\tjmp *%eax\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL renderer_overlay_background(u32) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%eax\n\tcall _renderer_overlay_body\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL renderer_overlay_return() {
    __asm__ __volatile__("ret\n\t");
}
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
    void string(const std::string& v) {value(static_cast<u32>(v.size()));bytes.insert(bytes.end(),v.begin(),v.end());}
    void text(const TextSource& v) {
        value(static_cast<u32>(v.component));string(v.original);string(v.value);value(v.has_value?1u:0u);
        value(static_cast<u32>(v.policy));string(v.prefix);string(v.suffix);
    }
    void paragraph(const model::ParagraphSource& v) {
        value(static_cast<u32>(v.fragments.size()));for(const auto& fragment:v.fragments) text(fragment);
        value(static_cast<u32>(v.grammar.size()));for(const auto& boundary:v.grammar) {
            value(boundary.after_fragments);value(boundary.first_fragment);value(boundary.comma_count);value(static_cast<u32>(boundary.operation));
        }
    }
};
struct Reader {
    const std::uint8_t* cursor;
    template<class T> T value() {T v;std::memcpy(&v,cursor,sizeof(v));cursor+=sizeof(v);return v;}
    SourceKey key() {const auto owner=value<u64>(),id=value<u64>();const auto field=value<u32>();return {owner,id,field};}
    std::string string() {const auto size=value<u32>();std::string result(reinterpret_cast<const char*>(cursor),size);cursor+=size;return result;}
    TextSource text() {
        TextSource result{};result.component=static_cast<TextComponent>(value<u32>());result.original=string();result.value=string();
        result.has_value=value<u32>()!=0;result.policy=static_cast<native_text_resource::TextPolicy>(value<u32>());
        result.prefix=string();result.suffix=string();return result;
    }
    model::ParagraphSource paragraph() {
        model::ParagraphSource result;const auto fragments=value<u32>();
        for(u32 index=0;index<fragments;++index) result.fragments.push_back(text());
        const auto grammar=value<u32>();for(u32 index=0;index<grammar;++index) {
            const auto after=value<u32>(),first=value<u32>(),commas=value<u32>();
            const auto operation=static_cast<native_component_model::ParagraphOperation>(value<u32>());
            result.grammar.push_back({after,first,commas,operation});
        }
        return result;
    }
};
}

void configure(std::uintptr_t image_base,const model::PaintServices& paint_services) {
    base=image_base;services=paint_services;next_handle=1;next_lifetime=1;
    owners.clear();current_owners.clear();native_resources.clear();metadata.clear();events.clear();borrows.clear();painting=false;preparing=false;
    native_targets::observe_component_texture_retirement(native_texture_destroying);
    native_targets::observe_component_surface_retirement(native_surface_destroying);
    native_hud_icons::configure(base,target_source,hud_icon_constructed);
    background_paint=BackgroundPaint::none;ordinary_map.reset();map_paint_source=nullptr;map_title_borrows.clear();cache_resources.clear();heading_copy={};
}
void configure_resource_services(const native_culture_legend::Services& callbacks) {resource_services=callbacks;}
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
    hooks.push_back({hud_frame_begin,HookKind::inline_code,0xFAA53,0,0,5,{0x68,0xFF,0,0,0}});
    HookSpec frame{hud_frame_end,HookKind::inline_code,0xFAAA4,0,0,7,{0x66,0x8B,0x0D}};
    const auto first_label=static_cast<u32>(base+0x1AA314);std::memcpy(frame.expected+3,&first_label,4);hooks.push_back(frame);
    HookSpec overlay{hud_overlay_begin,HookKind::inline_code,0xFB00D,0,0,6,{0xFF,0x35}};
    const auto renderer=static_cast<u32>(base+main_renderer);std::memcpy(overlay.expected+2,&renderer,4);hooks.push_back(overlay);
    hooks.push_back(call(map_factory,0xE5ACA,0xE3D90,0));
    HookSpec map{map_created,HookKind::inline_code,0xE3DD2,0,0,7,{0x0F,0x28,0x05}};
    const auto map_rect=static_cast<u32>(base+0x1DDAB0);std::memcpy(map.expected+3,&map_rect,4);hooks.push_back(map);
    hooks.push_back(call(map_title,0xE3E22,0x113430,0));
    hooks.push_back(call(map_help,0xE3E2C,0x162530,0));
    hooks.push_back(call(map_consumer_first,0xE5ACF,0xE3EE0,0));
    hooks.push_back(call(map_consumer_cultures,0xE61F1,0xE3EE0,0));
    hooks.push_back(call(map_consumer_indicators,0xE6209,0xE3EE0,0));
    hooks.push_back(call(hud_copy,0xFB242,0x116E20,0));
    HookSpec copy_previous{hud_copy_previous,HookKind::inline_code,0x116EA3,0,0,6,{0x8B,0x80}};
    const auto image_slots=static_cast<u32>(base+0xA3849F8);std::memcpy(copy_previous.expected+2,&image_slots,4);hooks.push_back(copy_previous);
    native_hud_icons::append_hooks(hooks);
    metadata.clear();for(const auto& hook:hooks) metadata.emplace(hook.id,hook);
}
void begin_event(const NativeEvent& event) {
    EventInput input{event.token,event.id,event.frame->ecx,event.frame->edx,{}};
    const auto hook=metadata.find(event.id);
    if(hook!=metadata.end() && hook->second.kind==HookKind::call)
        std::copy_n(event.arguments,std::min<u32>(event.argument_count,static_cast<u32>(input.arguments.size())),input.arguments.begin());
    events.push_back(input);
}
Status finish_event(const NativeEvent& event,DispatchResult& result,Status status) {
    const auto input=events.back();events.pop_back();
    if(finish_overlay_background(event,result)) return status;
    if(event.id==hud_frame_end && background_paint==BackgroundPaint::hud_frame) {
        result.resume_rva=address(reinterpret_cast<const void*>(&renderer_hud_frame_return))-static_cast<u32>(base);
        return status;
    }
    bool icon_handled{};const auto icon_status=native_hud_icons::dispatch(event,result,icon_handled);
    if(icon_handled) return status==Status::ok?icon_status:status;
    if(event.id==hud_copy_previous) {
        if(heading_copy.building) {
            auto& texture=native<u32>(0xA3849F8+event.frame->eax);
            heading_copy.previous=texture;texture=0;
        }
        return status;
    }
    if(event.id==hud_copy) {
        if(status!=Status::ok) return status;
        const auto handle=writable(hud_overlay);auto& owner=owners.find(handle)->second.owner;
        if(event.phase==NativePhase::before) {
            owner.copied=true;
            // The complete original copy constructor reads the same target
            // owner as the canonical overlay component's normal consumer.
            native<u32>(hud_overlay)=native<u32>(owner.target.texture_owner_rva);
        } else if(event.phase==NativePhase::after) {
            owner.copied_slot=event.frame->eax;native_ui_scene::renderer_constructed(handle);
        }
        return status;
    }
    if(event.id==map_title) {
        if(event.phase==NativePhase::after) {map_title_borrows.erase(event.token);return status;}
        if(status!=Status::ok) return status;
        if(map_paint_source) return prepare_map_title(event,map_paint_source->map.title);
        auto& owner=owners.find(writable(known_map_owner))->second.owner;
        owner.map.title=native_text_resource::from_request({TextComponent::culture_text,
            pointer<const char>(input.edx),"map.known_areas_title"});
        return prepare_map_title(event,owner.map.title);
    }
    if(event.id==map_help) {
        if(map_paint_source && event.phase==NativePhase::before) {
            result.skip_original=1;
            return native_component_binding::consume_paragraph_source(map_paint_source->map.help);
        }
        if(!painting && event.phase==NativePhase::after && status==Status::ok)
            owners.find(writable(known_map_owner))->second.owner.map.help=native_component_binding::current_paragraph_source();
        return status;
    }
    if(event.id==map_factory) {
        if(event.phase==NativePhase::before && status==Status::ok) {
            ordinary_map=map_inputs();ordinary_map_scope=next_lifetime;resource_services.enter(ordinary_map_scope);
        } else if(event.phase==NativePhase::after) {
            resource_services.leave(ordinary_map_scope);ordinary_map.reset();
            if(status==Status::ok) {
                const auto handle=writable(known_map_owner);owners.find(handle)->second.owner.initialized=true;
                native_ui_scene::renderer_constructed(handle);
            }
        }
        return status;
    }
    if(event.id==map_consumer_first || event.id==map_consumer_cultures || event.id==map_consumer_indicators) {
        if(!painting && status==Status::ok) {
            const auto handle=writable(known_map_owner);auto& owner=owners.find(handle)->second.owner;
            if(event.phase==NativePhase::before) {
                owner.map.consumed=true;
                owner.map.visibility={native<std::uint8_t>(0x1EBCAC),native<std::uint8_t>(0x1EBCAD)};
                // Ordinary native composition consumes these exact canonical
                // flags, just as materialization of this resource does.
                native<std::uint8_t>(0x1EBCAC)=owner.map.visibility[0];native<std::uint8_t>(0x1EBCAD)=owner.map.visibility[1];
            } else if(event.phase==NativePhase::after) native_ui_scene::renderer_constructed(handle);
        }
        return status;
    }
    if(event.phase==NativePhase::after) {
        const auto borrow=borrows.find(event.token);
        if(borrow!=borrows.end()) {
            if(borrow->second.entered) services.leave(borrow->second.component,model::get(borrow->second.component).kind);
            if(status==Status::ok) {
                if(event.id==infobox_panel) owners.find(writable(borrow->second.owner))->second.owner.initialized=true;
                if(model::get(borrow->second.component).kind==model::Kind::marked_button)
                    model::commit_native_row(borrow->second.component);
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
    if(event.id==hud_frame_begin) {begin_hud();return Status::ok;}
    if(event.id==hud_frame_end) {owners.find(writable(hud_surface))->second.owner.initialized=true;return Status::ok;}
    if(event.id==hud_overlay_begin) return begin_overlay();
    if(event.id==magic_created) {created(event,magic_owner,Background::native_surface);return Status::ok;}
    if(event.id==infobox_created) {created(event,infobox_owner,Background::native_panel);return Status::ok;}
    if(event.id==map_created) {created(event,known_map_owner,Background::native_known_map);return Status::ok;}
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
    case 0x113430:case 0x10EFD0:case 0x1166C0:case 0x10E260:case 0xCFD10:case 0x111560:
        return construct(event,hook->second,input);
    default:return Status::ok;
    }
}
const SourceKey& source(Handle handle) {return owners.find(handle)->second.owner.key;}
model::TargetSource target_source(u32 field) {return owners.find(current_owners.find(field)->second)->second.owner.target;}
void hud_icon_constructed(u32 field,u32 handle) {
    const auto current=writable(field);auto& owner=owners.find(current)->second.owner;
    const auto& key=native_hud_icons::source(handle);
    const auto previous=std::find_if(owner.icons.begin(),owner.icons.end(),
        [&](u32 icon){return native_hud_icons::source(icon)==key;});
    native_hud_icons::retain(handle);
    if(previous==owner.icons.end()) owner.icons.push_back(handle);
    else {native_hud_icons::release(*previous);*previous=handle;}
    native_ui_scene::renderer_constructed(current);
}
bool finish_overlay_background(const NativeEvent& event,DispatchResult& result) {
    if(background_paint!=BackgroundPaint::overlay || event.phase!=NativePhase::inline_before) return false;
    const auto hook=metadata.find(event.id);
    if(hook==metadata.end() || hook->second.site_rva!=0xFB01C) return false;
    result.resume_rva=address(reinterpret_cast<const void*>(&renderer_overlay_return))-static_cast<u32>(base);
    return true;
}
MenuHandle menu_owner(Handle handle) {return owners.find(handle)->second.owner.menu;}
void retain(Handle handle) {++owners.find(handle)->second.references;}
void release(Handle handle) {
    const auto owner=owners.find(handle);if(--owner->second.references==0) {release_children(owner->second.owner);owners.erase(owner);}
}
Handle snapshot(Handle handle,MenuHandle menu) {
    auto copy=owners.find(handle)->second.owner;copy.menu=menu;
    for(auto& child:copy.children) child=model::snapshot(child,copy.target,menu);
    for(auto& icon:copy.icons) icon=native_hud_icons::snapshot(icon,copy.target);
    const auto result=next_handle++;owners.emplace(result,Version{1,std::move(copy)});return result;
}
Status paint_hud(const Owner& owner,PaintDestination destination) {
    native_targets::HudTarget replacement;
    const auto created=native_targets::create_component_hud_target(owner.software_constructor,replacement);
    if(created!=Status::ok) return created;
    const native_targets::HudTarget previous{native<u32>(hud_surface),native<u32>(hud_renderer),
        native<u32>(0x61BBAD8),native<u32>(0x61BBB38)};
    native<u32>(hud_surface)=replacement.surface;native<u32>(hud_renderer)=replacement.renderer;
    native<u32>(0x61BBAD8)=replacement.direction;native<u32>(0x61BBB38)=replacement.marker;
    painting=true;background_paint=BackgroundPaint::hud_frame;
    const HudFrameCall frame{static_cast<u32>(base+0xFAA53),native<u32>(0x18C1E4)};
    renderer_hud_frame(&frame);background_paint=BackgroundPaint::none;
    Status status=Status::ok;
    for(const auto child:owner.children) {status=model::paint(child,services);if(status!=Status::ok) break;}
    if(status==Status::ok)
        for(const auto icon:owner.icons) {status=native_hud_icons::paint(icon);if(status!=Status::ok) break;}
    if(status==Status::ok) status=native_targets::copy_hud_component(replacement.surface);
    if(status==Status::ok && destination==PaintDestination::native_surface_cache) {
        CacheResource resource{};resource.hud=true;resource.previous_hud=previous;resource.replacement_hud=replacement;
        cache_resources.back().push_back(std::move(resource));
    } else if(status!=Status::ok) {
        native<u32>(hud_surface)=previous.surface;native<u32>(hud_renderer)=previous.renderer;
        native<u32>(0x61BBAD8)=previous.direction;native<u32>(0x61BBB38)=previous.marker;
        native_targets::destroy_component_hud_target(replacement);
    } else {
        native_resources.insert_or_assign(hud_surface,replacement.surface);
        native_targets::destroy_component_hud_target(previous);
    }
    painting=false;return status;
}
Status paint_known_map(const Owner& owner,PaintDestination destination) {
    using GetTarget=u32 (__cdecl *)(u32);
    using SetTarget=int (__cdecl *)(u32,u32);
    using NativeFactory=void (UWCN_CALL *)();
    const auto renderer=native<u32>(main_renderer),previous=native<u32>(known_map_owner);
    const auto caller_target=native<GetTarget>(0x18C26C)(renderer);
    const auto set_target=native<SetTarget>(0x18C288);
    const MapConstruction inputs(owner);
    // The original constructor owns allocation, background, title, measure,
    // dependent panel/paragraph layout and final target reset. Give it its new
    // owner slot; the caller's old resource remains owned until commit below.
    native<u32>(known_map_owner)=0;painting=true;map_paint_source=&owner;
    reinterpret_cast<NativeFactory>(base+0xE3D90)();
    const auto replacement=native<u32>(known_map_owner);
    if(owner.map.consumed) reinterpret_cast<NativeFactory>(base+0xE3EE0)();
    map_paint_source=nullptr;
    const auto status=native_component_binding::restore_paragraph_builder();
    std::vector<std::pair<u32,u32>> aliases;
    for(const auto alias:{0x5F4EB08u,0xA1C1CBCu})
        if(native<u32>(alias)==previous) {aliases.push_back({alias,previous});native<u32>(alias)=replacement;}
    if(status==Status::ok && destination==PaintDestination::native_surface_cache) {
        cache_resources.back().push_back({false,known_map_owner,previous,replacement,renderer,caller_target,std::move(aliases)});
        set_target(renderer,caller_target);
    } else if(status!=Status::ok) {
        native<u32>(known_map_owner)=previous;for(const auto [alias,value]:aliases) native<u32>(alias)=value;
        set_target(renderer,caller_target);native_targets::destroy_component_texture(replacement);
    } else {
        native_resources.insert_or_assign(known_map_owner,replacement);
        set_target(renderer,previous && caller_target==previous?replacement:caller_target);
        if(previous) native_targets::destroy_component_texture(previous);
    }
    painting=false;
    return status==Status::ok && !replacement?Status::failed:status;
}
void paint_heading_copy(PaintDestination destination,u32 renderer,u32& caller_target) {
    // The native factory finds its own 'headingicons' record by the original
    // literal. Its selected existing slot, rather than a remembered ordinal,
    // supplies the old resource at the confirmed 116EA3 owner read.
    using Copy=u32 (UWCN_CALL *)();
    heading_copy={true,0};const auto slot=reinterpret_cast<Copy>(base+0x116E20)();heading_copy.building=false;
    const auto field=0xA3849F8+slot*0xC48;const auto replacement=native<u32>(field);
    if(destination==PaintDestination::native_surface_cache)
        cache_resources.back().push_back({false,field,heading_copy.previous,replacement,renderer,caller_target,{}});
    else if(heading_copy.previous) {
        if(caller_target==heading_copy.previous) caller_target=replacement;
        native_targets::destroy_component_texture(heading_copy.previous);
    }
    // The copy constructor does not modify this original record's native HUD
    // rectangle. FB250..FB279 owns that rectangle through current HUD globals.
}
Status paint(Handle handle,PaintDestination destination) {
    const auto& owner=owners.find(handle)->second.owner;
    if(owner.target.kind==model::TargetKind::software_surface) return paint_hud(owner,destination);
    if(owner.background==Background::native_known_map) return paint_known_map(owner,destination);
    const auto field=owner.target.texture_owner_rva;const auto previous=native<u32>(field);
    const auto renderer=native<u32>(owner.target.renderer_owner_rva);
    using GetTarget=u32 (__cdecl *)(u32);
    using SetTarget=int (__cdecl *)(u32,u32);
    auto caller_target=native<GetTarget>(0x18C26C)(renderer);
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
    } else if(owner.background==Background::native_overlay_clear) {
        background_paint=BackgroundPaint::overlay;
        renderer_overlay_background(static_cast<u32>(base+0xFAFE2));
        background_paint=BackgroundPaint::none;
    }
    Status status=Status::ok;
    for(const auto child:owner.children) {status=model::paint(child,services);if(status!=Status::ok) break;}
    if(status==Status::ok)
        for(const auto icon:owner.icons) {status=native_hud_icons::paint(icon);if(status!=Status::ok) break;}
    if(status==Status::ok && owner.copied) paint_heading_copy(destination,renderer,caller_target);
    if(status==Status::ok && destination==PaintDestination::native_surface_cache) {
        cache_resources.back().push_back({false,field,previous,texture,renderer,caller_target,std::move(aliases)});
        set_target(renderer,caller_target);
    } else if(status!=Status::ok) {
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
void begin_native_cache_resources() {cache_resources.emplace_back();}
void end_native_cache_resources() {
    const auto resources=std::move(cache_resources.back());cache_resources.pop_back();
    painting=true;
    for(auto resource=resources.rbegin();resource!=resources.rend();++resource) {
        if(resource->hud) {
            native<u32>(hud_surface)=resource->previous_hud.surface;native<u32>(hud_renderer)=resource->previous_hud.renderer;
            native<u32>(0x61BBAD8)=resource->previous_hud.direction;native<u32>(0x61BBB38)=resource->previous_hud.marker;
            native_targets::destroy_component_hud_target(resource->replacement_hud);
        } else {
            native<u32>(resource->field)=resource->previous;
            for(const auto [field,value]:resource->aliases) native<u32>(field)=value;
            using SetTarget=int (__cdecl *)(u32,u32);
            native<SetTarget>(0x18C288)(resource->renderer,resource->caller_target);
            native_targets::destroy_component_texture(resource->replacement);
        }
    }
    painting=false;
}
void activate(Handle handle) {
    const auto field=owner_field(owners.find(handle)->second.owner);
    const auto current=current_owners.find(field);
    retain(handle);
    if(current!=current_owners.end()) {const auto previous=current->second;current->second=handle;release(previous);}
    else current_owners.emplace(field,handle);
}
void native_texture_destroying(u32 texture) {
    native_culture_legend::native_texture_destroying(texture);
    if(painting) return;
    for(auto resource=native_resources.begin();resource!=native_resources.end();) {
        if(resource->second==texture) {
            const auto field=resource->first;const auto owner=current_owners.find(field);
            if(owners.find(owner->second)->second.owner.target.kind==model::TargetKind::software_surface) {++resource;continue;}
            model::remove_owner(owners.find(owner->second)->second.owner.target.lifetime);
            native_hud_icons::remove_owner(owners.find(owner->second)->second.owner.target.lifetime);
            native_ui_scene::renderer_retired(source(owner->second));
            const auto previous=owner->second;current_owners.erase(owner);release(previous);
            resource=native_resources.erase(resource);
        } else ++resource;
    }
}
void native_surface_destroying(u32 surface) {
    if(painting) return;
    const auto resource=native_resources.find(hud_surface);
    if(resource!=native_resources.end() && resource->second==surface) {
        retire_current(hud_surface);native_resources.erase(resource);
    }
}
void menu_retired(Handle handle,MenuHandle menu) {
    const auto field=owner_field(owners.find(handle)->second.owner);
    const auto next=writable(field);auto& owner=owners.find(next)->second.owner;
    for(auto child=owner.children.begin();child!=owner.children.end();) {
        const auto& component=model::get(*child);
        if(component.kind==model::Kind::marked_button &&
            native_menu_model::input_owner(std::get<model::MarkedButtonInputs>(component.inputs).row.owner)==
                native_menu_model::input_owner(menu)) {
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
        out.value(static_cast<u32>(v.target.kind));out.value(v.target.surface_owner_rva);
        out.value(v.constructor.format);out.value(v.constructor.access);out.value(v.constructor.width);out.value(v.constructor.height);
        out.value(static_cast<u32>(v.background));out.value(v.surface_owner);out.value(v.background_width);out.value(v.background_height);
        out.value(v.initialized?1u:0u);out.value(v.menu);out.value(static_cast<u32>(v.children.size()));for(const auto child:v.children) out.value(child);
        out.value(v.software_constructor.flags);out.value(v.software_constructor.width);out.value(v.software_constructor.height);
        out.value(v.software_constructor.depth);out.value(v.software_constructor.red_mask);out.value(v.software_constructor.green_mask);
        out.value(v.software_constructor.blue_mask);out.value(v.software_constructor.alpha_mask);
        out.value(static_cast<u32>(v.icons.size()));for(const auto icon:v.icons) out.value(icon);
        if(v.background==Background::native_known_map) {
            out.value(v.map.panel.background_mode);out.value(v.map.panel.title_fill_color);
            out.value(v.map.secondary_color);out.text(v.map.title);out.paragraph(v.map.help);
            out.value(v.map.consumed?1u:0u);for(const auto flag:v.map.visibility) out.value(flag);
        }
        out.value(v.copied?1u:0u);out.value(v.copied_slot);
    }
    for(const auto [field,handle]:current_owners) {out.value(field);out.value(handle);}
    for(const auto [field,texture]:native_resources) {out.value(field);out.value(texture);}
    return std::move(out.bytes);
}
void restore(const void* payload) {
    Reader in{static_cast<const std::uint8_t*>(payload)};next_handle=in.value<u32>();next_lifetime=in.value<u64>();
    const auto count=in.value<u32>(),current=in.value<u32>(),resources=in.value<u32>();
    owners.clear();current_owners.clear();native_resources.clear();events.clear();borrows.clear();painting=false;preparing=false;
    ordinary_map.reset();map_paint_source=nullptr;map_title_borrows.clear();background_paint=BackgroundPaint::none;cache_resources.clear();heading_copy={};
    for(u32 index=0;index<count;++index) {
        const auto handle=in.value<u32>(),references=in.value<u32>();Owner v{};v.key=in.key();
        v.target.lifetime=in.value<u64>();v.target.renderer_owner_rva=in.value<u32>();v.target.texture_owner_rva=in.value<u32>();
        v.target.kind=static_cast<model::TargetKind>(in.value<u32>());v.target.surface_owner_rva=in.value<u32>();
        v.constructor.format=in.value<u32>();v.constructor.access=in.value<std::int32_t>();
        v.constructor.width=in.value<std::int32_t>();v.constructor.height=in.value<std::int32_t>();
        v.background=static_cast<Background>(in.value<u32>());v.surface_owner=in.value<u32>();
        v.background_width=in.value<std::int32_t>();v.background_height=in.value<std::int32_t>();v.initialized=in.value<u32>()!=0;
        v.menu=in.value<u32>();const auto children=in.value<u32>();for(u32 child=0;child<children;++child) v.children.push_back(in.value<u32>());
        v.software_constructor.flags=in.value<u32>();v.software_constructor.width=in.value<std::int32_t>();
        v.software_constructor.height=in.value<std::int32_t>();v.software_constructor.depth=in.value<std::int32_t>();
        v.software_constructor.red_mask=in.value<u32>();v.software_constructor.green_mask=in.value<u32>();
        v.software_constructor.blue_mask=in.value<u32>();v.software_constructor.alpha_mask=in.value<u32>();
        const auto icons=in.value<u32>();for(u32 icon=0;icon<icons;++icon) v.icons.push_back(in.value<u32>());
        if(v.background==Background::native_known_map) {
            v.map.panel.background_mode=in.value<u32>();v.map.panel.title_fill_color=in.value<u32>();
            v.map.secondary_color=in.value<u32>();v.map.title=in.text();v.map.help=in.paragraph();
            v.map.consumed=in.value<u32>()!=0;for(auto& flag:v.map.visibility) flag=in.value<std::uint8_t>();
        }
        v.copied=in.value<u32>()!=0;v.copied_slot=in.value<u32>();
        owners.emplace(handle,Version{references,std::move(v)});
    }
    for(u32 index=0;index<current;++index) {const auto field=in.value<u32>();current_owners.emplace(field,in.value<u32>());}
    for(u32 index=0;index<resources;++index) {const auto field=in.value<u32>();native_resources.emplace(field,in.value<u32>());}
}
void shutdown() {
    native_targets::observe_component_texture_retirement(nullptr);
    native_targets::observe_component_surface_retirement(nullptr);
    for(const auto& [handle,version]:owners) {(void)handle;release_children(version.owner);}
    owners.clear();current_owners.clear();native_resources.clear();metadata.clear();events.clear();borrows.clear();
    ordinary_map.reset();map_paint_source=nullptr;map_title_borrows.clear();cache_resources.clear();heading_copy={};services={};resource_services={};base=0;
}
}
