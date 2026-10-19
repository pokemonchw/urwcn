#include "native_targets.h"
#include "native_root_component.h"
#include "native_ui_cache_owners.h"
#include "scoped_api.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <unordered_map>

// 10BBE0 receives x/y in ECX/EDX and the native image surface on the stack;
// unlike compiler fastcall, its caller removes that stack argument.
extern "C" __attribute__((naked)) uwcn::u32 __cdecl uwcn_hud_image_key(
    uwcn::u32,uwcn::render::Surface*) {
    __asm__ __volatile__(
        "movl 4(%esp),%eax\n\t"
        "pushl 8(%esp)\n\t"
        "xorl %ecx,%ecx\n\t"
        "xorl %edx,%edx\n\t"
        "call *%eax\n\t"
        "addl $4,%esp\n\t"
        "ret\n\t");
}

namespace uwcn::adapter::native_targets {
namespace {
using namespace render;
using Scale=scoped::SurfaceScale;
std::uintptr_t base{};
Scale canvas{800,600,800,600};
std::unordered_map<Surface*,Scale> surfaces;
std::unordered_map<Texture*,Scale> textures;
std::unordered_map<Surface*,SurfaceSource> surface_sources;
TextureDestroying component_texture_retirement{};
SurfaceDestroying component_surface_retirement{};
struct Api : scoped::NativeSdl {
    Surface* (__cdecl *CreateRGBSurface)(u32,int,int,int,u32,u32,u32,u32);
    Surface* (__cdecl *ConvertSurface)(Surface*,const PixelFormat*,u32);
    void (__cdecl *FreeSurface)(Surface*);
    int (__cdecl *GetSurfaceBlendMode)(Surface*,int*);
    int (__cdecl *SetSurfaceBlendMode)(Surface*,int);
    int (__cdecl *GetSurfaceAlphaMod)(Surface*,std::uint8_t*);
    int (__cdecl *SetSurfaceAlphaMod)(Surface*,std::uint8_t);
    int (__cdecl *GetSurfaceColorMod)(Surface*,std::uint8_t*,std::uint8_t*,std::uint8_t*);
    int (__cdecl *SetSurfaceColorMod)(Surface*,std::uint8_t,std::uint8_t,std::uint8_t);
    int (__cdecl *HasColorKey)(Surface*);
    int (__cdecl *GetColorKey)(Surface*,u32*);
    int (__cdecl *SetColorKey)(Surface*,int,u32);
    int (__cdecl *SetSurfaceRLE)(Surface*,int);
    Renderer* (__cdecl *CreateSoftwareRenderer)(Surface*);
    void (__cdecl *DestroyRenderer)(Renderer*);
    Texture* (__cdecl *CreateTexture)(Renderer*,u32,int,int,int);
    Texture* (__cdecl *CreateTextureFromSurface)(Renderer*,Surface*);
    void (__cdecl *DestroyTexture)(Texture*);
    int (__cdecl *QueryTexture)(Texture*,u32*,int*,int*,int*);
    int (__cdecl *GetTextureBlendMode)(Texture*,int*);
    int (__cdecl *SetTextureBlendMode)(Texture*,int);
    int (__cdecl *GetTextureAlphaMod)(Texture*,std::uint8_t*);
    int (__cdecl *SetTextureAlphaMod)(Texture*,std::uint8_t);
    int (__cdecl *GetTextureColorMod)(Texture*,std::uint8_t*,std::uint8_t*,std::uint8_t*);
    int (__cdecl *SetTextureColorMod)(Texture*,std::uint8_t,std::uint8_t,std::uint8_t);
    int (__cdecl *GetTextureScaleMode)(Texture*,int*);
    int (__cdecl *SetTextureScaleMode)(Texture*,int);
    int (__cdecl *RenderCopy)(Renderer*,Texture*,const Rect*,const Rect*);
    Texture* (__cdecl *GetRenderTarget)(Renderer*);
    int (__cdecl *SetRenderTarget)(Renderer*,Texture*);
    void (__cdecl *RenderGetScale)(Renderer*,float*,float*);
    int (__cdecl *RenderSetScale)(Renderer*,float,float);
    void (__cdecl *RenderGetViewport)(Renderer*,Rect*);
    int (__cdecl *RenderSetViewport)(Renderer*,const Rect*);
    void (__cdecl *RenderGetClipRect)(Renderer*,Rect*);
    int (__cdecl *RenderSetClipRect)(Renderer*,const Rect*);
    int (__cdecl *RenderIsClipEnabled)(Renderer*);
} api{};
template<class T> T& global(u32 rva) { return *reinterpret_cast<T*>(base+rva); }
u32 address(const void* p) { return static_cast<u32>(reinterpret_cast<std::uintptr_t>(p)); }
const Scale* scale(Surface* s) {
    const auto found=surfaces.find(s);
    return found==surfaces.end()?nullptr:&found->second;
}
const Scale* scale(Texture* t) {
    const auto found=textures.find(t);
    return found==textures.end()?nullptr:&found->second;
}
Status output_scale() {
    auto* renderer=global<Renderer*>(0xA2110CC);
    auto* target=api.GetRenderTarget(renderer);
    float sx{},sy{}; api.RenderGetScale(renderer,&sx,&sy);
    if(api.RenderSetScale(renderer,1,1)!=0) return Status::failed;
    Rect viewport{},clip{};
    api.RenderGetViewport(renderer,&viewport);
    const bool clipped=api.RenderIsClipEnabled(renderer)!=0;
    if(clipped) api.RenderGetClipRect(renderer,&clip);
    if(api.RenderSetScale(renderer,sx,sy)!=0) return Status::failed;
    if(target && api.SetRenderTarget(renderer,nullptr)!=0) return Status::failed;
    float wx{},wy{}; api.RenderGetScale(renderer,&wx,&wy);
    if(api.RenderSetScale(renderer,1,1)!=0) return Status::failed;
    Rect window{}; api.RenderGetViewport(renderer,&window);
    if(api.RenderSetScale(renderer,wx,wy)!=0) return Status::failed;
    if(target) {
        if(api.SetRenderTarget(renderer,target)!=0 || api.RenderSetScale(renderer,1,1)!=0 ||
           api.RenderSetViewport(renderer,&viewport)!=0 || api.RenderSetClipRect(renderer,clipped?&clip:nullptr)!=0 ||
           api.RenderSetScale(renderer,sx,sy)!=0) return Status::failed;
    }
    // The native 800x600 canvas remains the minimum raster domain. A smaller
    // window downsamples it; a larger one receives physical-resolution glyphs.
    canvas={800,600,std::max(800,window.w),std::max(600,window.h)};
    return Status::ok;
}

Surface* __cdecl create_surface(u32 flags,int w,int h,int depth,u32 r,u32 g,u32 b,u32 a) {
    const auto site=static_cast<u32>(reinterpret_cast<std::uintptr_t>(__builtin_return_address(0))-base);
    const bool canvas_owner=site==0x1179BF || site==0x10C180 || site==0x10C206 ||
        site==0x10C289 || site==0x10C48A || site==0x10C628 || site==0x10C3B1;
    const bool fade_owner=site==0x10D5E8 || site==0x10D65B;
    const bool culture_owner=site==0xE3A6F;
    const SurfaceSource neutral{flags,w,h,depth,r,g,b,a};
    const Scale component_scale{w,h,
        scoped::physical_rect({0,0,w,h},&canvas).w,
        scoped::physical_rect({0,0,w,h},&canvas).h};
    if(canvas_owner) {
        const Rect physical=scoped::physical_rect({0,0,w,h},&canvas);
        w=physical.w; h=physical.h;
    }
    if(culture_owner) { w=component_scale.physical_width;h=component_scale.physical_height; }
    auto* result=api.CreateRGBSurface(flags,w,h,depth,r,g,b,a);
    if(result && (canvas_owner || fade_owner)) surfaces.emplace(result,canvas);
    if(result && culture_owner) surfaces.emplace(result,component_scale);
    if(result && canvas_owner) surface_sources.emplace(result,neutral);
    return result;
}
Renderer* __cdecl create_software_renderer(Surface* surface) {
    auto* renderer=api.CreateSoftwareRenderer(surface);
    const auto* surface_scale=scale(surface);
    if(renderer && surface_scale) api.RenderSetScale(renderer,
        float(surface_scale->physical_width)/surface_scale->logical_width,
        float(surface_scale->physical_height)/surface_scale->logical_height);
    return renderer;
}
Surface* __cdecl convert_surface(Surface* source,const PixelFormat* format,u32 flags) {
    auto* result=api.ConvertSurface(source,format,flags);
    const auto* source_scale=scale(source);
    if(result && source_scale) surfaces.emplace(result,*source_scale);
    const auto constructor=surface_sources.find(source);
    if(result && constructor!=surface_sources.end()) {
        auto neutral=constructor->second;
        neutral.flags=flags;neutral.depth=format->bits;
        neutral.red_mask=format->rmask;neutral.green_mask=format->gmask;
        neutral.blue_mask=format->bmask;neutral.alpha_mask=format->amask;
        surface_sources.emplace(result,neutral);
    }
    return result;
}
void __cdecl free_surface(Surface* surface) {
    if(component_surface_retirement) component_surface_retirement(address(surface));
    surfaces.erase(surface);
    surface_sources.erase(surface);
    api.FreeSurface(surface);
}
int __cdecl blit(Surface* source,const Rect* src,Surface* destination,Rect* dst) {
    const auto caller_return=static_cast<u32>(
        reinterpret_cast<std::uintptr_t>(__builtin_return_address(0))-base);
    native_ui_cache_owners::BlitPreparation prepared;
    const auto status=native_ui_cache_owners::before_blit(caller_return,source,destination,src,dst,prepared);
    if(status!=Status::ok) return -1;
    const auto* from=prepared.restoring && prepared.restore.has_source ? &prepared.restore.source : src;
    auto* to=prepared.restoring && prepared.restore.has_destination ? &prepared.restore.destination : dst;
    const int result=scoped::blit(api,source,from,scale(source),destination,to,scale(destination),false);
    if(prepared.restoring && dst) *dst=prepared.restore.destination;
    native_ui_cache_owners::after_blit(caller_return,source,destination,prepared,result);
    return result;
}
int __cdecl blit_scaled(Surface* source,const Rect* src,Surface* destination,Rect* dst) {
    return scoped::blit(api,source,src,scale(source),destination,dst,scale(destination),true);
}
int __cdecl fill(Surface* destination,const Rect* rect,u32 color) {
    const auto caller_return=static_cast<u32>(
        reinterpret_cast<std::uintptr_t>(__builtin_return_address(0))-base);
    const int result=scoped::fill(api,destination,rect,scale(destination),color);
    native_root_component::native_clear_filled(caller_return,destination,result);
    return result;
}
Texture* make_component_texture(Renderer* renderer,u32 format,int access,int w,int h) {
    if(output_scale()!=Status::ok) return nullptr;
    const Scale component_scale{w,h,
        scoped::physical_rect({0,0,w,h},&canvas).w,
        scoped::physical_rect({0,0,w,h},&canvas).h};
    auto* result=api.CreateTexture(renderer,format,access,
        component_scale.physical_width,component_scale.physical_height);
    if(result) textures.emplace(result,component_scale);
    return result;
}
Texture* __cdecl create_texture(Renderer* renderer,u32 format,int access,int w,int h) {
    const auto site=static_cast<u32>(reinterpret_cast<std::uintptr_t>(__builtin_return_address(0))-base);
    const bool upload=site==0x117973;
    // MagicProfile's native page and CompileInfoboxRitualList's description.
    // Both are native render targets; their logical rectangles remain native.
    const bool component=site==0xDF995 || site==0xDFC7B || site==0xE3DD2 || site==0x116EF2;
    if(component) return make_component_texture(renderer,format,access,w,h);
    if(upload) {
        if(output_scale()!=Status::ok) return nullptr;
        w=canvas.physical_width; h=canvas.physical_height;
    }
    auto* result=api.CreateTexture(renderer,format,access,w,h);
    if(result && upload) textures.emplace(result,canvas);
    return result;
}
int __cdecl set_render_target(Renderer* renderer,Texture* target) {
    const auto status=api.SetRenderTarget(renderer,target);
    if(status!=0) return status;
    const auto* target_scale=scale(target);
    if(target_scale) return api.RenderSetScale(renderer,
        float(target_scale->physical_width)/target_scale->logical_width,
        float(target_scale->physical_height)/target_scale->logical_height);
    return status;
}
int __cdecl query_texture(Texture* texture,u32* format,int* access,int* width,int* height) {
    const auto status=api.QueryTexture(texture,format,access,width,height);
    const auto* texture_scale=scale(texture);
    if(status==0 && texture_scale) {
        if(width) *width=texture_scale->logical_width;
        if(height) *height=texture_scale->logical_height;
    }
    return status;
}
Texture* __cdecl texture_from_surface(Renderer* renderer,Surface* surface) {
    auto* result=api.CreateTextureFromSurface(renderer,surface);
    const auto* source_scale=scale(surface);
    if(result && source_scale) textures.emplace(result,*source_scale);
    return result;
}
void __cdecl destroy_texture(Texture* texture) {
    if(component_texture_retirement) component_texture_retirement(address(texture));
    textures.erase(texture);
    api.DestroyTexture(texture);
}
int __cdecl copy_texture(Renderer* renderer,Texture* texture,const Rect* src,const Rect* dst) {
    const auto* source_scale=scale(texture);
    if(!src || !source_scale) return api.RenderCopy(renderer,texture,src,dst);
    const Rect physical=scoped::physical_rect(*src,source_scale);
    return api.RenderCopy(renderer,texture,&physical,dst);
}
struct Import { u32 rva,id,original,replacement; };
std::array<Import,13> imports{};
inline constexpr u32 gateway_stride=16;
inline constexpr u32 gateway_bytes=13*gateway_stride;
std::uint8_t* gateways{};
bool installed{};
u32 gateway(std::size_t index) { return address(gateways+index*gateway_stride); }
Status bind_gateways(bool enable) {
    DWORD previous{},ignored{};
    if(!VirtualProtect(gateways,gateway_bytes,PAGE_EXECUTE_READWRITE,&previous)) return Status::failed;
    for(std::size_t i=0;i<imports.size();++i) {
        auto* code=gateways+i*gateway_stride;
        const u32 target=enable?imports[i].replacement:imports[i].original;
        const u32 displacement=target-address(code)-5;
        code[0]=0xE9;
        std::memcpy(code+1,&displacement,sizeof(displacement));
    }
    const bool flushed=FlushInstructionCache(GetCurrentProcess(),gateways,gateway_bytes)!=0;
    const bool restored=VirtualProtect(gateways,gateway_bytes,previous,&ignored)!=0;
    return flushed && restored?Status::ok:Status::failed;
}
Status write_import(u32 rva,u32 value) {
    auto* destination=reinterpret_cast<volatile LONG*>(base+rva);
    DWORD old{},ignored{};
    if(!VirtualProtect(const_cast<LONG*>(destination),4,PAGE_READWRITE,&old)) return Status::failed;
    InterlockedExchange(destination,static_cast<LONG>(value));
    return VirtualProtect(const_cast<LONG*>(destination),4,old,&ignored)?Status::ok:Status::failed;
}
struct SurfaceProperties {
    int blend{}; std::uint8_t alpha{},red{},green{},blue{}; int keyed{}; u32 key{};
};
Status properties(Surface* surface,SurfaceProperties& p) {
    p.keyed=api.HasColorKey(surface);
    if(api.GetSurfaceBlendMode(surface,&p.blend)!=0 || api.GetSurfaceAlphaMod(surface,&p.alpha)!=0 ||
       api.GetSurfaceColorMod(surface,&p.red,&p.green,&p.blue)!=0 ||
       (p.keyed && api.GetColorKey(surface,&p.key)!=0)) return Status::failed;
    return Status::ok;
}
Status apply(Surface* surface,const SurfaceProperties& p) {
    if(api.SetSurfaceBlendMode(surface,p.blend)!=0 || api.SetSurfaceAlphaMod(surface,p.alpha)!=0 ||
       api.SetSurfaceColorMod(surface,p.red,p.green,p.blue)!=0 || api.SetColorKey(surface,p.keyed,p.key)!=0)
        return Status::failed;
    return Status::ok;
}
Status replace_surface(u32 slot,int logical_width) {
    auto* old=global<Surface*>(slot);
    SurfaceProperties original{};
    if(properties(old,original)!=Status::ok) return Status::failed;
    const auto* format=old->format;
    const Rect extent=scoped::physical_rect({0,0,logical_width,600},&canvas);
    auto* replacement=api.CreateRGBSurface(0,extent.w,extent.h,32,format->rmask,format->gmask,format->bmask,format->amask);
    if(!replacement) return Status::failed;
    // Transfer the native owner's existing bitmap once. This uses its ordinary
    // SDL copy operation; no content is read, retained or interpreted by Mod.
    const SurfaceProperties raw{0,255,255,255,255,0,0};
    if(apply(old,raw)!=Status::ok) return Status::failed;
    Rect destination{0,0,extent.w,extent.h};
    const int copied=api.UpperBlitScaled(old,nullptr,replacement,&destination);
    const auto restored=apply(old,original);
    if(copied!=0 || restored!=Status::ok || apply(replacement,original)!=Status::ok) return Status::failed;
    global<Surface*>(slot)=replacement;
    surfaces.erase(old); surfaces.emplace(replacement,canvas);
    surface_sources.erase(old);
    surface_sources.emplace(replacement,SurfaceSource{0,logical_width,600,32,
        format->rmask,format->gmask,format->bmask,format->amask});
    api.FreeSurface(old);
    return Status::ok;
}

Status hud_image(Renderer* renderer,u32 filename,Texture*& result) {
    // 1154EA..115531 and 115547..11558E build these renderer-owned native
    // images from the original asset names. Use the same native image loader
    // and first-pixel color-key helper; no target pixels are inspected.
    using LoadImage=Surface* (__cdecl *)(const char*);
    const auto load=global<LoadImage>(0x18C294);
    auto* image=load(reinterpret_cast<const char*>(base+filename));
    if(!image) return Status::failed;
    const auto key=uwcn_hud_image_key(static_cast<u32>(base+0x10BBE0),image);
    const int keyed=api.SetColorKey(image,1,key);
    result=keyed==0 ? api.CreateTextureFromSurface(renderer,image) : nullptr;
    api.FreeSurface(image);
    return result ? Status::ok : Status::failed;
}
template<class T> void append(std::vector<std::uint8_t>& data,const T& value) {
    const auto* begin=reinterpret_cast<const std::uint8_t*>(&value);
    data.insert(data.end(),begin,begin+sizeof(value));
}
struct Record { u32 handle; Scale scale; };
struct SurfaceRecord {u32 handle;SurfaceSource source;};
}

u32 create_component_texture(u32 renderer,u32 format,std::int32_t access,
    std::int32_t width,std::int32_t height) {
    return address(make_component_texture(reinterpret_cast<Renderer*>(static_cast<std::uintptr_t>(renderer)),
        format,access,width,height));
}
void destroy_component_texture(u32 texture) {
    destroy_texture(reinterpret_cast<Texture*>(static_cast<std::uintptr_t>(texture)));
}
void observe_component_texture_retirement(TextureDestroying observer) {
    component_texture_retirement=observer;
}
void observe_component_surface_retirement(SurfaceDestroying observer) {component_surface_retirement=observer;}
Status component_texture_source(u32 texture,TextureSource& source) {
    auto* native_texture=reinterpret_cast<Texture*>(static_cast<std::uintptr_t>(texture));
    if(api.QueryTexture(native_texture,&source.format,&source.access,&source.width,&source.height)!=0)
        return Status::failed;
    const auto* native_scale=scale(native_texture);
    if(native_scale) {source.width=native_scale->logical_width;source.height=native_scale->logical_height;}
    return Status::ok;
}
SurfaceSource component_surface_source(const void* surface) {
    return surface_sources.find(const_cast<Surface*>(static_cast<const Surface*>(surface)))->second;
}
u32 create_component_surface(const SurfaceSource& source) {
    if(output_scale()!=Status::ok) return 0;
    const auto extent=scoped::physical_rect({0,0,source.width,source.height},&canvas);
    auto* surface=api.CreateRGBSurface(source.flags,extent.w,extent.h,source.depth,
        source.red_mask,source.green_mask,source.blue_mask,source.alpha_mask);
    if(surface) {surfaces.emplace(surface,canvas);surface_sources.emplace(surface,source);}
    return address(surface);
}
void destroy_component_surface(u32 surface) {
    free_surface(reinterpret_cast<Surface*>(static_cast<std::uintptr_t>(surface)));
}
Status create_component_hud_target(const SurfaceSource& source,HudTarget& target) {
    target.surface=create_component_surface(source);
    if(!target.surface) return Status::failed;
    auto* surface=reinterpret_cast<Surface*>(static_cast<std::uintptr_t>(target.surface));
    if(api.SetSurfaceRLE(surface,1)!=0) {destroy_component_surface(target.surface);return Status::failed;}
    auto* renderer=create_software_renderer(surface);
    if(!renderer) {destroy_component_surface(target.surface);return Status::failed;}
    target.renderer=address(renderer);
    Texture* direction{};Texture* marker{};
    if(hud_image(renderer,0x1ACAB8,direction)!=Status::ok ||
        hud_image(renderer,0x1ACAD0,marker)!=Status::ok) {
        api.DestroyRenderer(renderer);destroy_component_surface(target.surface);return Status::failed;
    }
    target.direction=address(direction);target.marker=address(marker);return Status::ok;
}
void destroy_component_hud_target(const HudTarget& target) {
    api.DestroyRenderer(reinterpret_cast<Renderer*>(static_cast<std::uintptr_t>(target.renderer)));
    destroy_component_surface(target.surface);
}
Status copy_hud_component(u32 surface) {
    // FB202..FB239 obtains this complete native output rectangle from these
    // four fields. Native SDL owns clipping and the actual surface transfer.
    Rect destination{global<std::int32_t>(0x619F974),global<std::int32_t>(0x619F978),
        global<std::int32_t>(0x619F97C),global<std::int32_t>(0x619F980)};
    return copy_cache_component(surface,nullptr,&destination);
}
Status copy_cache_component(u32 surface,const Rect* source,Rect* destination) {
    auto* input=reinterpret_cast<Surface*>(static_cast<std::uintptr_t>(surface));
    auto* output=global<Surface*>(0x61BBB10);
    return scoped::blit(api,input,source,scale(input),output,destination,scale(output),false)==0
        ? Status::ok : Status::failed;
}
Status initialize(std::uintptr_t image_base,HMODULE sdl) {
    base=image_base;
#define BIND(name) api.name=reinterpret_cast<decltype(api.name)>(GetProcAddress(sdl,"SDL_" #name)); if(!api.name) return Status::unavailable
    BIND(UpperBlit); BIND(UpperBlitScaled); BIND(FillRect);
    BIND(CreateRGBSurface); BIND(ConvertSurface); BIND(FreeSurface);
    BIND(GetSurfaceBlendMode); BIND(SetSurfaceBlendMode); BIND(GetSurfaceAlphaMod); BIND(SetSurfaceAlphaMod);
    BIND(GetSurfaceColorMod); BIND(SetSurfaceColorMod); BIND(HasColorKey); BIND(GetColorKey); BIND(SetColorKey);
    BIND(SetSurfaceRLE); BIND(CreateSoftwareRenderer); BIND(DestroyRenderer);
    BIND(CreateTexture); BIND(CreateTextureFromSurface); BIND(DestroyTexture); BIND(QueryTexture);
    BIND(GetTextureBlendMode); BIND(SetTextureBlendMode); BIND(GetTextureAlphaMod); BIND(SetTextureAlphaMod);
    BIND(GetTextureColorMod); BIND(SetTextureColorMod); BIND(GetTextureScaleMode); BIND(SetTextureScaleMode);
    BIND(RenderCopy); BIND(GetRenderTarget); BIND(SetRenderTarget); BIND(RenderGetScale); BIND(RenderSetScale);
    BIND(RenderGetViewport); BIND(RenderSetViewport); BIND(RenderGetClipRect); BIND(RenderSetClipRect); BIND(RenderIsClipEnabled);
#undef BIND
#define ENTRY(rva,id,name,bridge) Import{rva,id,address(reinterpret_cast<void*>(api.name)),address(reinterpret_cast<void*>(&bridge))}
    imports={{
        ENTRY(0x18C204,0x4000,UpperBlit,blit),
        ENTRY(0x18C17C,0x400C,UpperBlitScaled,blit_scaled),
        ENTRY(0x18C1E8,0x4001,FillRect,fill),
        ENTRY(0x18C1F0,0x400A,CreateRGBSurface,create_surface),
        ENTRY(0x18C178,0,ConvertSurface,convert_surface),
        ENTRY(0x18C1F4,0x4002,FreeSurface,free_surface),
        ENTRY(0x18C208,0x400B,CreateTexture,create_texture),
        ENTRY(0x18C1E0,0x4003,CreateTextureFromSurface,texture_from_surface),
        ENTRY(0x18C22C,0x4006,DestroyTexture,destroy_texture),
        ENTRY(0x18C228,0x4005,RenderCopy,copy_texture),
        ENTRY(0x18C288,0,SetRenderTarget,set_render_target),
        ENTRY(0x18C18C,0,QueryTexture,query_texture),
        ENTRY(0x18C220,0,CreateSoftwareRenderer,create_software_renderer)
    }};
#undef ENTRY
    return Status::ok;
}
Status install() {
    for(const auto& entry:imports) if(global<u32>(entry.rva)!=entry.original) return Status::invalid;
    // Game frames cache IAT values (125B79 keeps UpperBlit in ESI across its
    // input wait). Publish only process-lifetime code, never a DLL address.
    gateways=static_cast<std::uint8_t*>(VirtualAlloc(nullptr,gateway_bytes,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READ));
    if(!gateways) return Status::failed;
    auto status=bind_gateways(true);
    if(status!=Status::ok) return status;
    installed=true;
    for(std::size_t i=0;i<imports.size();++i) {
        status=write_import(imports[i].rva,gateway(i));
        if(status!=Status::ok) return status;
    }
    return Status::ok;
}
Status remove() {
    if(!installed) return Status::ok;
    auto status=bind_gateways(false);
    if(status!=Status::ok) return status;
    for(const auto& entry:imports) {
        status=write_import(entry.rva,entry.original);
        if(status!=Status::ok) return status;
    }
    installed=false;
    return Status::ok;
}
std::vector<abi1_retirement::RouteBinding> routes() {
    std::vector<abi1_retirement::RouteBinding> result;
    for(std::size_t i=0;i<imports.size();++i) if(imports[i].id) result.push_back({imports[i].id,gateway(i)});
    return result;
}
Status promote() {
    auto status=output_scale();
    if(status!=Status::ok) return status;
    auto* main=global<Surface*>(0x61BBB10);
    if(scale(main) && main->w==canvas.physical_width && main->h==canvas.physical_height) return Status::ok;
    // These are native owner fields, not a geometry table. Screenshot export
    // A1C1C98 and the image atlas A1C2028 deliberately keep native pixel units.
    for(u32 slot:{0x61BBB10u,0xA1BBD20u,0xA1C2014u,0xA1BBD24u,0xA1C1CE0u}) {
        status=replace_surface(slot,800);
        if(status!=Status::ok) return status;
    }
    for(u32 i=0;i<4;++i) {
        const u32 slot=0xA1C1CC4+i*4;
        // 10C51A clears the native 100-byte name before 10C526 frees its
        // surface; the pointer slot deliberately retains the retired address.
        // 10C558..10C569 uses the name to identify a live named background.
        if(global<char>(0xA1C1AC0+i*100)!='\0') {
            status=replace_surface(slot,799);
            if(status!=Status::ok) return status;
        }
    }
    auto* old=global<Texture*>(0xA1C2020);
    u32 format{}; int access{},w{},h{},blend{},filter{};
    std::uint8_t alpha{},r{},g{},b{};
    if(api.QueryTexture(old,&format,&access,&w,&h)!=0 || api.GetTextureBlendMode(old,&blend)!=0 ||
       api.GetTextureAlphaMod(old,&alpha)!=0 || api.GetTextureColorMod(old,&r,&g,&b)!=0 ||
       api.GetTextureScaleMode(old,&filter)!=0) return Status::failed;
    auto* replacement=api.CreateTexture(global<Renderer*>(0xA2110CC),format,access,canvas.physical_width,canvas.physical_height);
    if(!replacement) return Status::failed;
    if(api.SetTextureBlendMode(replacement,blend)!=0 || api.SetTextureAlphaMod(replacement,alpha)!=0 ||
       api.SetTextureColorMod(replacement,r,g,b)!=0 || api.SetTextureScaleMode(replacement,filter)!=0) return Status::failed;
    global<Texture*>(0xA1C2020)=replacement;
    textures.erase(old); textures.emplace(replacement,canvas);
    api.DestroyTexture(old);
    return Status::ok;
}
Status promote_hud() {
    // Called at FAA4B, before FAA67 first borrows the renderer. FAA7A fills
    // its whole native surface, so this boundary requires no bitmap transfer.
    auto* old_surface=global<Surface*>(0x61BBB04);
    auto* old_renderer=global<Renderer*>(0x61BBB0C);
    const int width=global<int>(0x619F97C),height=global<int>(0x619F980);
    const Rect extent=scoped::physical_rect({0,0,width,height},&canvas);
    const float sx=float(canvas.physical_width)/canvas.logical_width;
    const float sy=float(canvas.physical_height)/canvas.logical_height;
    const auto* source_format=old_surface->format;
    const SurfaceSource neutral{0,width,height,32,source_format->rmask,source_format->gmask,
        source_format->bmask,source_format->amask};
    if(scale(old_surface) && old_surface->w==extent.w && old_surface->h==extent.h) {
        surface_sources.insert_or_assign(old_surface,neutral);
        return api.RenderSetScale(old_renderer,sx,sy)==0 ? Status::ok : Status::failed;
    }

    SurfaceProperties original{};
    if(properties(old_surface,original)!=Status::ok) return Status::failed;
    const auto* format=old_surface->format;
    auto* replacement=api.CreateRGBSurface(0,extent.w,extent.h,32,
        format->rmask,format->gmask,format->bmask,format->amask);
    if(!replacement) return Status::failed;
    if(apply(replacement,original)!=Status::ok || api.SetSurfaceRLE(replacement,1)!=0) {
        api.FreeSurface(replacement);
        return Status::failed;
    }
    auto* renderer=api.CreateSoftwareRenderer(replacement);
    if(!renderer) { api.FreeSurface(replacement); return Status::failed; }
    Texture* direction{};
    Texture* marker{};
    if(api.RenderSetScale(renderer,sx,sy)!=0 ||
       hud_image(renderer,0x1ACAB8,direction)!=Status::ok ||
       hud_image(renderer,0x1ACAD0,marker)!=Status::ok) {
        api.DestroyRenderer(renderer);
        api.FreeSurface(replacement);
        return Status::failed;
    }
    // Every permanent texture constructed with 61BBB0C is recreated above.
    // SDL owns their lifetime and destroys the old renderer's textures here.
    global<Surface*>(0x61BBB04)=replacement;
    global<Renderer*>(0x61BBB0C)=renderer;
    global<Texture*>(0x61BBAD8)=direction;
    global<Texture*>(0x61BBB38)=marker;
    api.DestroyRenderer(old_renderer);
    surfaces.erase(old_surface);
    surfaces.emplace(replacement,canvas);
    surface_sources.erase(old_surface);surface_sources.emplace(replacement,neutral);
    api.FreeSurface(old_surface);
    return Status::ok;
}
std::vector<std::uint8_t> save() {
    std::vector<std::uint8_t> result;
    append(result,u32{0x3254474E}); // NGT2: identity, scale and neutral constructors.
    append(result,canvas);
    append(result,address(gateways));
    append(result,static_cast<u32>(surfaces.size()));
    append(result,static_cast<u32>(textures.size()));
    append(result,static_cast<u32>(surface_sources.size()));
    for(const auto& [handle,s]:surfaces) append(result,Record{address(handle),s});
    for(const auto& [handle,s]:textures) append(result,Record{address(handle),s});
    for(const auto& [handle,source]:surface_sources) append(result,SurfaceRecord{address(handle),source});
    return result;
}
Status restore(const void* input,u32 bytes) {
    constexpr u32 header=sizeof(u32)+sizeof(Scale)+4*sizeof(u32);
    if(!input || bytes<sizeof(u32)) return Status::invalid;
    const auto* data=static_cast<const std::uint8_t*>(input);
    u32 magic{},saved_gateways{},surface_count{},texture_count{},source_count{};
    std::memcpy(&magic,data,4);
    // NGT1 contains no neutral native constructors and cannot reconstruct
    // the new component owners from its former bitmap/scale identities.
    if(magic==0x3154474E) return Status::unavailable;
    if(bytes<header) return Status::invalid;
    std::memcpy(&saved_gateways,data+4+sizeof(Scale),4);
    std::memcpy(&surface_count,data+8+sizeof(Scale),4);
    std::memcpy(&texture_count,data+12+sizeof(Scale),4);
    std::memcpy(&source_count,data+16+sizeof(Scale),4);
    if(magic!=0x3254474E || bytes!=header+(std::size_t(surface_count)+texture_count)*sizeof(Record)+
        std::size_t(source_count)*sizeof(SurfaceRecord)) return Status::invalid;
    std::memcpy(&canvas,data+4,sizeof(canvas));
    surfaces.clear(); textures.clear();surface_sources.clear();
    const auto* records=data+header;
    for(u32 i=0;i<surface_count+texture_count;++i) {
        Record record{}; std::memcpy(&record,records+i*sizeof(Record),sizeof(record));
        if(i<surface_count) surfaces.emplace(reinterpret_cast<Surface*>(record.handle),record.scale);
        else textures.emplace(reinterpret_cast<Texture*>(record.handle),record.scale);
    }
    const auto* constructors=records+(std::size_t(surface_count)+texture_count)*sizeof(Record);
    for(u32 i=0;i<source_count;++i) {
        SurfaceRecord record;std::memcpy(&record,constructors+i*sizeof(record),sizeof(record));
        surface_sources.emplace(reinterpret_cast<Surface*>(record.handle),record.source);
    }
    // Host runs initialize and restore without advancing a native game frame.
    // Its temporary page has therefore never escaped into a cached game call.
    // Reuse the saved page before freeing that unpublished initialization page.
    auto* initialization_gateways=gateways;
    gateways=reinterpret_cast<std::uint8_t*>(static_cast<std::uintptr_t>(saved_gateways));
    auto status=bind_gateways(true);
    if(status!=Status::ok) return status;
    for(std::size_t i=0;i<imports.size();++i) {
        status=write_import(imports[i].rva,gateway(i));
        if(status!=Status::ok) return status;
    }
    if(!VirtualFree(initialization_gateways,0,MEM_RELEASE)) return Status::failed;
    return Status::ok;
}
void forget() {
    component_texture_retirement=nullptr;
    component_surface_retirement=nullptr;
    surfaces.clear(); textures.clear();surface_sources.clear(); base=0;
    // Cached native aliases continue to name the retired page, now bound to
    // original SDL. Its address is retained by the saved adapter state.
    gateways=nullptr;
    canvas={800,600,800,600};
}
}
