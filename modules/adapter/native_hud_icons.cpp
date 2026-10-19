#include "native_hud_icons.h"
#include "native_renderer_component_binding.h"
#include "../render/sdl_api.h"
#include <algorithm>
#include <cstring>
#include <map>
#include <optional>

// These entry points execute the original game's pure icon constructor spans.
// Geometry is still calculated by those original instructions, including their
// native direction switch and current HUD owner dimensions. No rectangle,
// native output pixels or SDL drawing contribution is retained by this model.
extern "C" {
uwcn::u32 uwcn_hud_direction_native_entry{};
uwcn::u32 uwcn_hud_activity_native_entry{};
__attribute__((naked)) void __cdecl uwcn_hud_direction_body() {
    __asm__ __volatile__("subl $24,%esp\n\tjmp *_uwcn_hud_direction_native_entry\n\t");
}
__attribute__((naked)) void __cdecl uwcn_hud_activity_body() {
    __asm__ __volatile__("jmp *_uwcn_hud_activity_native_entry\n\t");
}
__attribute__((naked)) void __cdecl uwcn_hud_invoke_direction() {
    __asm__ __volatile__(
        "pushl %ebp\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edi\n\t"
        "subl $96,%esp\n\tcall _uwcn_hud_direction_body\n\taddl $96,%esp\n\t"
        "popl %edi\n\tpopl %esi\n\tpopl %ebx\n\tpopl %ebp\n\tret\n\t");
}
__attribute__((naked)) void __cdecl uwcn_hud_invoke_activity(uwcn::u32) {
    __asm__ __volatile__(
        "pushl %ebp\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edi\n\t"
        "movl 20(%esp),%esi\n\tsubl $1280,%esp\n\tcall _uwcn_hud_activity_body\n\taddl $1280,%esp\n\t"
        "popl %edi\n\tpopl %esi\n\tpopl %ebx\n\tpopl %ebp\n\tret\n\t");
}
__attribute__((naked)) void __cdecl uwcn_hud_direction_return() {
    __asm__ __volatile__("addl $32,%esp\n\tret\n\t");
}
__attribute__((naked)) void __cdecl uwcn_hud_overlay_return() {
    __asm__ __volatile__("ret\n\t");
}
__attribute__((naked)) void __cdecl uwcn_hud_activity_return() {
    __asm__ __volatile__("addl $8,%esp\n\tret\n\t");
}
}

namespace uwcn::adapter::native_hud_icons {
namespace {
constexpr u32 hud_surface=0x61BBB04,overlay_texture=0x61BBAF4;
constexpr u32 direction_field=0xA384110,activity_records=0x61A8CC4;
enum Hook:u32 { direction_begin=0x5A00,direction_branch,direction_end,
    overlay_begin,overlay_end,activity_age,activity_alpha,activity_end };
struct Version {u32 references;IconSource source;};
std::uintptr_t base{};
OwnerSource owner_source{};Constructed constructed{};
Handle next_handle=1,direction_current{},overlay_current{},activity_current{};
std::map<Handle,Version> icons;
std::map<SourceKey,Handle> current_sources;
std::optional<Handle> painting;
template<class T> T& native(u32 rva) {return *reinterpret_cast<T*>(base+rva);}
u32 address(const void* value) {return static_cast<u32>(reinterpret_cast<std::uintptr_t>(value));}
u32 exit_rva(void (*exit)()) {return address(reinterpret_cast<const void*>(exit))-static_cast<u32>(base);}
Handle upsert(IconSource source) {
    const auto found=current_sources.find(source.key);
    if(found!=current_sources.end()) {
        auto& version=icons.find(found->second)->second;
        if(version.references==1) {version.source=std::move(source);return found->second;}
        const auto previous=found->second,handle=next_handle++;
        icons.emplace(handle,Version{1,std::move(source)});found->second=handle;release(previous);return handle;
    }
    const auto handle=next_handle++;current_sources.emplace(source.key,handle);
    icons.emplace(handle,Version{1,std::move(source)});return handle;
}
Handle construct(Kind kind,u32 record,u32 alpha) {
    const auto field=kind==Kind::direction ? hud_surface:overlay_texture;
    const auto target=owner_source(field);
    const SourceKey key{target.lifetime,kind==Kind::activity ? activity_records+record*4u:direction_field,
        static_cast<u32>(kind)};
    return upsert({key,target,kind,record,alpha});
}
HookSpec instruction(u32 id,u32 rva,std::initializer_list<std::uint8_t> bytes) {
    HookSpec hook{id,HookKind::inline_code,rva,0,0,static_cast<u32>(bytes.size()),{}};
    std::copy(bytes.begin(),bytes.end(),hook.expected);return hook;
}
void absolute(std::vector<HookSpec>& hooks,u32 id,u32 site,std::initializer_list<std::uint8_t> bytes,u32 offset,u32 field) {
    auto hook=instruction(id,site,bytes);const auto value=static_cast<u32>(base+field);
    std::memcpy(hook.expected+offset,&value,4);hooks.push_back(hook);
}
template<class T> void append(std::vector<std::uint8_t>& output,T value) {
    const auto* data=reinterpret_cast<const std::uint8_t*>(&value);output.insert(output.end(),data,data+sizeof(value));
}
template<class T> T read(const std::uint8_t*& input) {T value;std::memcpy(&value,input,sizeof(value));input+=sizeof(value);return value;}
void write_source(std::vector<std::uint8_t>& output,const IconSource& source) {
    append(output,source.key.owner);append(output,source.key.native_source);append(output,source.key.field);
    append(output,source.target.lifetime);append(output,source.target.renderer_owner_rva);append(output,source.target.texture_owner_rva);
    append(output,source.target.kind);append(output,source.target.surface_owner_rva);
    append(output,source.kind);append(output,source.native_record);append(output,source.alpha);
}
IconSource read_source(const std::uint8_t*& input) {
    const auto owner=read<u64>(input),native_source=read<u64>(input);const auto field=read<u32>(input);
    const auto lifetime=read<u64>(input);const auto renderer=read<u32>(input),texture=read<u32>(input);
    const auto target_kind=read<native_renderer_component_model::TargetKind>(input);const auto surface=read<u32>(input);
    const auto kind=read<Kind>(input);const auto record=read<u32>(input),alpha=read<u32>(input);
    return {{owner,native_source,field},{lifetime,renderer,texture,target_kind,surface},kind,record,alpha};
}
}
void configure(std::uintptr_t image_base,OwnerSource owner,Constructed callback) {
    base=image_base;owner_source=owner;constructed=callback;next_handle=1;
    icons.clear();current_sources.clear();painting.reset();direction_current=overlay_current=activity_current=0;
    uwcn_hud_direction_native_entry=static_cast<u32>(base+0xFAF04);
    uwcn_hud_activity_native_entry=static_cast<u32>(base+0xFB06F);
}
void append_hooks(std::vector<HookSpec>& hooks) {
    absolute(hooks,direction_begin,0xFAF04,{0xA1,0,0,0,0},1,0x619F97C);
    absolute(hooks,direction_branch,0xFAFB3,{0x8B,0x1D,0,0,0,0},2,0x18C1D0);
    absolute(hooks,direction_end,0xFAFE2,{0xFF,0x35,0,0,0,0},2,overlay_texture);
    hooks.push_back(instruction(overlay_begin,0xFB01C,{0x66,0x0F,0x6E,0xC6,0xF3,0x0F,0xE6,0xC0}));
    hooks.push_back(instruction(overlay_end,0xFB052,{0x33,0xF6,0x0F,0x1F,0x40,0}));
    absolute(hooks,activity_age,0xFB115,{0xA1,0,0,0,0},1,0xA32B180);
    absolute(hooks,activity_alpha,0xFB166,{0xFF,0x35,0,0,0,0},2,0x61BBAF8);
    absolute(hooks,activity_end,0xFB1EB,{0x6A,0,0xFF,0x35,0,0,0,0},4,0xA2110CC);
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=event.id>=direction_begin && event.id<=activity_end;
    if(!handled || event.phase!=NativePhase::inline_before) return Status::ok;
    if(event.id==overlay_begin && native_renderer_component_binding::finish_overlay_background(event,result))
        return Status::ok;
    if(painting) {
        const auto& value=get(*painting);
        if(event.id==direction_branch && value.kind==Kind::overlay_direction) {
            event.frame->ebx=native<u32>(0x18C1D0);event.frame->edi=native<u32>(0x18C288);
            result.resume_rva=0xFB01C;
        }
        else if(event.id==direction_end && value.kind==Kind::direction)
            result.resume_rva=exit_rva(uwcn_hud_direction_return);
        else if(event.id==overlay_end && value.kind==Kind::overlay_direction)
            result.resume_rva=exit_rva(uwcn_hud_overlay_return);
        else if(event.id==activity_age && value.kind==Kind::activity) {
            // FB115..FB133 consumes/clears business ages. The accepted alpha
            // has already become this icon's source in its ordinary constructor.
            event.frame->eax=value.alpha;result.resume_rva=0xFB15E;
        } else if(event.id==activity_end && value.kind==Kind::activity)
            result.resume_rva=exit_rva(uwcn_hud_activity_return);
        return Status::ok;
    }
    switch(event.id) {
    case direction_begin:
        direction_current=construct(Kind::direction,native<u32>(direction_field),255);
        native<u32>(direction_field)=prepare(direction_current).native_record;break;
    case direction_end:constructed(hud_surface,direction_current);break;
    case overlay_begin:
        overlay_current=construct(Kind::overlay_direction,native<u32>(direction_field),255);
        native<u32>(direction_field)=prepare(overlay_current).native_record;break;
    case overlay_end:constructed(overlay_texture,overlay_current);break;
    case activity_alpha: {
        const auto alpha=*reinterpret_cast<const u32*>(static_cast<std::uintptr_t>(event.frame->esp));
        activity_current=construct(Kind::activity,event.frame->esi,alpha);
        const auto input=prepare(activity_current);event.frame->esi=input.native_record;
        *reinterpret_cast<u32*>(static_cast<std::uintptr_t>(event.frame->esp))=input.alpha;break;
    }
    case activity_end:constructed(overlay_texture,activity_current);break;
    case direction_branch:case activity_age:break;
    }
    return Status::ok;
}
const SourceKey& source(Handle handle) {return get(handle).key;}
const IconSource& get(Handle handle) {return icons.find(handle)->second.source;}
PreparedIcon prepare(Handle handle) {const auto& value=get(handle);return {value.native_record,value.alpha};}
void retain(Handle handle) {++icons.find(handle)->second.references;}
void release(Handle handle) {const auto value=icons.find(handle);if(--value->second.references==0) icons.erase(value);}
Handle snapshot(Handle handle,TargetSource target) {
    auto value=get(handle);value.target=target;value.key.owner=target.lifetime;
    const auto copy=next_handle++;icons.emplace(copy,Version{1,std::move(value)});return copy;
}
Status paint(Handle handle) {
    const auto& value=get(handle);const auto target=native_renderer_component_model::resolve_target(value.target);
    auto* renderer=reinterpret_cast<render::Renderer*>(static_cast<std::uintptr_t>(target.renderer));
    using GetTarget=render::Texture* (__cdecl *)(render::Renderer*);
    using SetTarget=int (__cdecl *)(render::Renderer*,render::Texture*);
    using SetBlend=int (__cdecl *)(render::Texture*,int);
    using GetBlend=int (__cdecl *)(render::Texture*,int*);
    using GetAlpha=int (__cdecl *)(render::Texture*,std::uint8_t*);
    using SetAlpha=int (__cdecl *)(render::Texture*,std::uint8_t);
    const auto sdl=GetModuleHandleW(L"SDL2.dll");
    const auto get_target=native<GetTarget>(0x18C26C);
    const auto set_target=native<SetTarget>(0x18C288);
    const auto set_blend=reinterpret_cast<SetBlend>(GetProcAddress(sdl,"SDL_SetTextureBlendMode"));
    const auto get_blend=reinterpret_cast<GetBlend>(GetProcAddress(sdl,"SDL_GetTextureBlendMode"));
    const auto get_alpha=reinterpret_cast<GetAlpha>(GetProcAddress(sdl,"SDL_GetTextureAlphaMod"));
    const auto set_alpha=reinterpret_cast<SetAlpha>(GetProcAddress(sdl,"SDL_SetTextureAlphaMod"));
    const bool texture=target.kind==native_renderer_component_model::TargetKind::texture;
    auto* previous_target=texture ? get_target(renderer):nullptr;
    if(texture &&
        set_target(renderer,reinterpret_cast<render::Texture*>(static_cast<std::uintptr_t>(target.texture)))!=0) return Status::failed;
    painting=handle;
    if(value.kind==Kind::activity) {
        auto* image=native<render::Texture*>(0x61BBAF8);int previous_blend;std::uint8_t previous_alpha;
        if(get_blend(image,&previous_blend)!=0 || get_alpha(image,&previous_alpha)!=0 || set_blend(image,1)!=0) {
            painting.reset();set_target(renderer,previous_target);return Status::failed;
        }
        uwcn_hud_invoke_activity(value.native_record);
        if(set_blend(image,previous_blend)!=0 || set_alpha(image,previous_alpha)!=0) {
            painting.reset();set_target(renderer,previous_target);return Status::failed;
        }
    } else {
        auto& direction=native<u32>(direction_field);const auto previous=direction;direction=value.native_record;
        uwcn_hud_invoke_direction();direction=previous;
    }
    painting.reset();
    return !texture || set_target(renderer,previous_target)==0 ? Status::ok:Status::failed;
}
void remove_owner(u64 owner) {
    for(auto entry=current_sources.begin();entry!=current_sources.end();) {
        if(entry->first.owner==owner) {const auto handle=entry->second;entry=current_sources.erase(entry);release(handle);}
        else ++entry;
    }
}
std::vector<std::uint8_t> save() {
    std::vector<std::uint8_t> output;append(output,next_handle);append(output,static_cast<u32>(icons.size()));
    append(output,static_cast<u32>(current_sources.size()));
    for(const auto& [handle,version]:icons) {append(output,handle);append(output,version.references);write_source(output,version.source);}
    for(const auto& [key,handle]:current_sources) {append(output,key.owner);append(output,key.native_source);append(output,key.field);append(output,handle);}
    return output;
}
void restore(const void* payload) {
    auto* input=static_cast<const std::uint8_t*>(payload);next_handle=read<u32>(input);
    const auto count=read<u32>(input),sources=read<u32>(input);icons.clear();current_sources.clear();painting.reset();
    for(u32 i=0;i<count;++i) {const auto handle=read<u32>(input),references=read<u32>(input);icons.emplace(handle,Version{references,read_source(input)});}
    for(u32 i=0;i<sources;++i) {const auto owner=read<u64>(input),native_source=read<u64>(input);const auto field=read<u32>(input),handle=read<u32>(input);
        current_sources.emplace(SourceKey{owner,native_source,field},handle);}
}
void shutdown() {icons.clear();current_sources.clear();painting.reset();base=0;owner_source=nullptr;constructed=nullptr;}
}
