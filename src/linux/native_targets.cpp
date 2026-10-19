#include "native_targets.h"
#include "modules/adapter/scoped_api.h"
#include "modules/adapter/native_raster.h"
#include <dlfcn.h>
#include <algorithm>
#include <cmath>
#include <unordered_map>

namespace uwcn::linux_targets {
namespace {
using namespace render;
namespace scoped=adapter::scoped;
namespace raster=adapter::native_raster;
using Scale=scoped::SurfaceScale;
std::uintptr_t base;
const linux_host::Hooks* resident;
Scale canvas;
Scale mapview_canvas;
bool building_mapview;
// Resource metadata only. Native owners retain their surfaces, pixels and
// cache lifetimes. No text, UI positions or paint operations are retained.
std::unordered_map<Surface*,Scale> surfaces;
struct TextureOwner { Scale ratio; Renderer* renderer; };
std::unordered_map<Texture*,TextureOwner> textures;
struct Api : scoped::NativeSdl {
    Surface* (*CreateRGBSurface)(u32,int,int,int,u32,u32,u32,u32);
    Surface* (*ConvertSurface)(Surface*,const PixelFormat*,u32);
    void (*FreeSurface)(Surface*);
    Renderer* (*CreateSoftwareRenderer)(Surface*);
    void (*DestroyRenderer)(Renderer*);
    Texture* (*CreateTexture)(Renderer*,u32,int,int,int);
    Texture* (*CreateTextureFromSurface)(Renderer*,Surface*);
    void (*DestroyTexture)(Texture*);
    int (*QueryTexture)(Texture*,u32*,int*,int*,int*);
    int (*RenderCopy)(Renderer*,Texture*,const Rect*,const Rect*);
    int (*SetRenderTarget)(Renderer*,Texture*);
    void (*RenderGetScale)(Renderer*,float*,float*);
    int (*RenderSetScale)(Renderer*,float,float);
    void (*RenderGetLogicalSize)(Renderer*,int*,int*);
    int (*GetRendererOutputSize)(Renderer*,int*,int*);
    int (*GetSurfaceBlendMode)(Surface*,int*);
    int (*SetSurfaceBlendMode)(Surface*,int);
    int (*GetSurfaceAlphaMod)(Surface*,std::uint8_t*);
    int (*SetSurfaceAlphaMod)(Surface*,std::uint8_t);
    int (*GetSurfaceColorMod)(Surface*,std::uint8_t*,std::uint8_t*,std::uint8_t*);
    int (*SetSurfaceColorMod)(Surface*,std::uint8_t,std::uint8_t,std::uint8_t);
    int (*HasColorKey)(Surface*);
    int (*GetColorKey)(Surface*,u32*);
    int (*SetColorKey)(Surface*,int,u32);
    int (*HasSurfaceRLE)(Surface*);
    int (*SetSurfaceRLE)(Surface*,int);
    int (*LockSurface)(Surface*);
    void (*UnlockSurface)(Surface*);
} api;
template<class T> T& global(u32 rva) { return *reinterpret_cast<T*>(base+rva); }
template<class T> const Scale* scale(T* resource,const std::unordered_map<T*,Scale>& owners) {
    const auto entry=owners.find(resource);
    return entry==owners.end() ? nullptr : &entry->second;
}
const Scale* scale(Surface* resource) { return scale(resource,surfaces); }
const Scale* scale(Texture* resource) {
    const auto entry=textures.find(resource);
    return entry==textures.end() ? nullptr : &entry->second.ratio;
}

Scale output_scale(Renderer* renderer) {
    // initgr: 148C2D runs after renderer creation and optional logical-size
    // setup, before screen/caches exist. Its target is the window. Native
    // initgr leaves the user scale at 1. SDL2-compat 2.32.72 GetScale includes
    // SDL3's logical presentation ratio, whereas SetScale sets user scale
    // only; setting 1 and restoring GetScale would compound that ratio.
    int w,h,logical_w,logical_h;
    api.RenderGetLogicalSize(renderer,&logical_w,&logical_h);
    if(logical_w && logical_h) {
        float sx,sy;
        api.RenderGetScale(renderer,&sx,&sy);
        w=std::lround(logical_w*double(sx));
        h=std::lround(logical_h*double(sy));
    } else {
        api.GetRendererOutputSize(renderer,&w,&h);
    }
    const int native_w=global<int>(0x26dc68),native_h=global<int>(0x26dc64);
    // Preserve initgr's original raster domain when the window is smaller.
    // Larger output gets actual-density glyphs; smaller output downsamples
    // the same native canvas, as it did before this extension.
    return {native_w,native_h,std::max(native_w,w),std::max(native_h,h)};
}
Surface* create_surface(u32 flags,int w,int h,int depth,u32 r,u32 g,u32 b,u32 a) {
    linux_host::BusinessCall lease(*resident);
    const auto site=reinterpret_cast<std::uintptr_t>(__builtin_return_address(0))-base;
    // Return addresses of inspected native creations, not page coordinates.
    // fontsurface, tmpCharSurf, PELIGRAFIIKKA, maps and asset surfaces remain
    // in their native image-pixel domains.
    const bool logical=site==0x148c65 || site==0x13bacf || site==0x13bb81 ||
        site==0x13bbd8 || site==0x13bc2f || site==0x13beca ||
        site==0x13c114 || site==0x13bdba || site==0x10ac3b;
    // fade constructs its two temporary surfaces from screen->w/h already.
    const bool physical=site==0x13cf53 || site==0x13d165;
    const auto& ratio=building_mapview?mapview_canvas:canvas;
    if(logical) {
        const auto extent=scoped::physical_rect({0,0,w,h},&ratio);
        w=extent.w; h=extent.h;
    }
    auto* result=api.CreateRGBSurface(flags,w,h,depth,r,g,b,a);
    if(result && (logical || physical)) surfaces.emplace(result,ratio);
    return result;
}
Surface* convert_surface(Surface* source,const PixelFormat* format,u32 flags) {
    linux_host::BusinessCall lease(*resident);
    auto* result=api.ConvertSurface(source,format,flags);
    if(const auto* ratio=scale(source); result && ratio) surfaces.emplace(result,*ratio);
    return result;
}
void free_surface(Surface* surface) {
    linux_host::BusinessCall lease(*resident);
    surfaces.erase(surface);
    api.FreeSurface(surface);
}
int blit(Surface* source,const Rect* src,Surface* destination,Rect* dst) {
    linux_host::BusinessCall lease(*resident);
    return scoped::blit(api,source,src,scale(source),destination,dst,scale(destination),false);
}
int blit_scaled(Surface* source,const Rect* src,Surface* destination,Rect* dst) {
    linux_host::BusinessCall lease(*resident);
    return scoped::blit(api,source,src,scale(source),destination,dst,scale(destination),true);
}
int fill(Surface* surface,const Rect* rect,u32 color) {
    linux_host::BusinessCall lease(*resident);
    return scoped::fill(api,surface,rect,scale(surface),color);
}
Renderer* software_renderer(Surface* surface) {
    linux_host::BusinessCall lease(*resident);
    auto* renderer=api.CreateSoftwareRenderer(surface);
    if(const auto* ratio=scale(surface); renderer && ratio)
        api.RenderSetScale(renderer,float(ratio->physical_width)/ratio->logical_width,
                           float(ratio->physical_height)/ratio->logical_height);
    return renderer;
}
void destroy_renderer(Renderer* renderer) {
    linux_host::BusinessCall lease(*resident);
    // SDL_DestroyRenderer destroys every texture it owns internally, without
    // returning through the game's SDL_DestroyTexture PLT entry.
    std::erase_if(textures,[renderer](const auto& entry) { return entry.second.renderer==renderer; });
    api.DestroyRenderer(renderer);
}
Texture* create_texture(Renderer* renderer,u32 format,int access,int w,int h) {
    linux_host::BusinessCall lease(*resident);
    const auto site=reinterpret_cast<std::uintptr_t>(__builtin_return_address(0))-base;
    const bool upload=site==0x148c32;
    if(upload) {
        canvas=output_scale(renderer);
        w=canvas.physical_width; h=canvas.physical_height;
    } else if(building_mapview) {
        // CreateGamesizeTex tail-calls SDL_CreateTexture. This scope is its
        // inspected MapviewMainTex owner, not every gamesize texture caller.
        const auto extent=scoped::physical_rect({0,0,w,h},&mapview_canvas);
        w=extent.w; h=extent.h;
    }
    auto* texture=api.CreateTexture(renderer,format,access,w,h);
    if(texture && upload) textures.emplace(texture,TextureOwner{canvas,renderer});
    else if(texture && building_mapview) textures.emplace(texture,TextureOwner{mapview_canvas,renderer});
    return texture;
}
void mapview_target(linux_host::Frame& frame) {
    // MapView 10C8A1 selects the window before CompileMapviewSubscreen.
    // That owner has destroyed its old target at 10B0C1, and no legend copy
    // is borrowed here. Re-enter the game's full legend builder to consume
    // the current language and window density before its native target is
    // created. The builder owns replacing CultureDialogTexture itself.
    mapview_canvas=output_scale(global<Renderer*>(0xa916ed0));
    building_mapview=true;
    reinterpret_cast<void (*)()>(base+0x10ac10)();
    frame.rax=reinterpret_cast<std::uintptr_t>(reinterpret_cast<Texture* (*)()>(base+0x13c3b0)());
    building_mapview=false;
}
Texture* texture_from_surface(Renderer* renderer,Surface* surface) {
    linux_host::BusinessCall lease(*resident);
    auto* texture=api.CreateTextureFromSurface(renderer,surface);
    if(const auto* ratio=scale(surface); texture && ratio) textures.emplace(texture,TextureOwner{*ratio,renderer});
    return texture;
}
void destroy_texture(Texture* texture) {
    linux_host::BusinessCall lease(*resident);
    textures.erase(texture);
    api.DestroyTexture(texture);
}
int query_texture(Texture* texture,u32* format,int* access,int* w,int* h) {
    linux_host::BusinessCall lease(*resident);
    const int result=api.QueryTexture(texture,format,access,w,h);
    if(result==0) if(const auto* ratio=scale(texture)) {
        // TexToMainRen and the native image-size consumers still lay out in
        // logical units. The SDL implementation and font module use real SDL.
        const auto logical=scoped::logical_rect({0,0,w?*w:0,h?*h:0},ratio);
        if(w) *w=logical.w;
        if(h) *h=logical.h;
    }
    return result;
}
int copy_texture(Renderer* renderer,Texture* texture,const Rect* src,const Rect* dst) {
    linux_host::BusinessCall lease(*resident);
    const auto* ratio=scale(texture);
    if(!src || !ratio) return api.RenderCopy(renderer,texture,src,dst);
    const auto physical=scoped::physical_rect(*src,ratio);
    return api.RenderCopy(renderer,texture,&physical,dst);
}
int set_render_target(Renderer* renderer,Texture* texture) {
    linux_host::BusinessCall lease(*resident);
    const int result=api.SetRenderTarget(renderer,texture);
    // SDL2-compat resets a texture target's scale to 1 on each selection.
    // Reapply only this native resource's recorded output density. Switching
    // to NULL restores SDL3's main_view, including its window presentation;
    // no GetScale value is written back as an additional window scale.
    if(const auto* ratio=scale(texture))
        api.RenderSetScale(renderer,float(ratio->physical_width)/ratio->logical_width,
                           float(ratio->physical_height)/ratio->logical_height);
    return result;
}
raster::Target lock_screen() {
    auto* screen=global<Surface*>(0xa916ea0);
    if(screen->flags&2u) {
        api.LockSurface(screen);
        screen=global<Surface*>(0xa916ea0);
    }
    return {screen,global<int>(0x26dc68),global<int>(0x26dc64)};
}
void unlock_screen(raster::Target target) {
    if(target.surface->flags&2u) api.UnlockSurface(target.surface);
}
void putpixel(int x,int y,u32 color) {
    linux_host::BusinessCall lease(*resident);
    // putpix's original unsigned 799/599 checks, before any lock.
    if(unsigned(x)>799 || unsigned(y)>599) return;
    const auto target=lock_screen();
    raster::pixel(target,x,y,color);
    unlock_screen(target);
}
u32 getpixel(int x,int y) {
    linux_host::BusinessCall lease(*resident);
    // getpix rejects against RESOLUTION_X/Y and returns zero out of range.
    if(x<0 || y<0 || x>=global<int>(0x26dc68) || y>=global<int>(0x26dc64)) return 0;
    const auto target=lock_screen();
    const auto color=raster::read_pixel(target,x,y);
    unlock_screen(target);
    return color;
}
void putasc(int x,int y,unsigned char code) {
    linux_host::BusinessCall lease(*resident);
    const auto* mask=reinterpret_cast<const std::uint8_t*>(base+0xa979780)+unsigned(code)*80;
    const auto target=lock_screen();
    raster::glyph(target,x,y,mask,global<u32>(0xa916104));
    unlock_screen(target);
}
void draw_line(int x1,int y1,int x2,int y2,u32 color) {
    linux_host::BusinessCall lease(*resident);
    if(unsigned(x1)>799 || unsigned(x2)>799 || unsigned(y1)>599 || unsigned(y2)>599) return;
    const auto target=lock_screen();
    raster::line(target,x1,y1,x2,y2,color);
    unlock_screen(target);
}
void replace_surface(u32 owner,int logical_w,int logical_h) {
    auto* old=global<Surface*>(owner);
    int blend;
    std::uint8_t alpha,r,g,b;
    const int keyed=api.HasColorKey(old),rle=api.HasSurfaceRLE(old);
    u32 key=0;
    api.GetSurfaceBlendMode(old,&blend);
    api.GetSurfaceAlphaMod(old,&alpha);
    api.GetSurfaceColorMod(old,&r,&g,&b);
    if(keyed) api.GetColorKey(old,&key);
    const auto extent=scoped::physical_rect({0,0,logical_w,logical_h},&canvas);
    const auto* format=old->format;
    auto* replacement=api.CreateRGBSurface(0,extent.w,extent.h,32,
        format->rmask,format->gmask,format->bmask,format->amask);
    // Transfer this native bitmap once. The main-menu caller then executes
    // the game's own complete reconstruction, generating new-density glyphs.
    api.SetSurfaceBlendMode(old,0);
    api.SetSurfaceAlphaMod(old,255);
    api.SetSurfaceColorMod(old,255,255,255);
    api.SetColorKey(old,0,0);
    Rect destination{0,0,extent.w,extent.h};
    api.UpperBlitScaled(old,nullptr,replacement,&destination);
    api.SetSurfaceBlendMode(replacement,blend);
    api.SetSurfaceAlphaMod(replacement,alpha);
    api.SetSurfaceColorMod(replacement,r,g,b);
    api.SetColorKey(replacement,keyed,key);
    api.SetSurfaceRLE(replacement,rle);
    global<Surface*>(owner)=replacement;
    surfaces.emplace(replacement,canvas);
    free_surface(old);
}
Texture* heading_image(Renderer* renderer,u32 filename) {
    // The two persistent HeadingBoxSoftRen textures are created by the
    // native asset-loading sequence 1461C3..146295, with this color-key rule.
    const auto load=reinterpret_cast<Surface* (*)(const char*)>(base+0x8590);
    const auto pixel=reinterpret_cast<u32 (*)(int,int,Surface*)>(base+0x13b000);
    auto* image=load(reinterpret_cast<const char*>(base+filename));
    api.SetColorKey(image,1,pixel(0,0,image));
    auto* texture=api.CreateTextureFromSurface(renderer,image);
    api.FreeSurface(image);
    return texture;
}
}
bool synchronize_main_menu() {
    const auto previous=canvas;
    auto* renderer=global<Renderer*>(0xa916ed0);
    canvas=output_scale(renderer);
    if(previous.physical_width==canvas.physical_width &&
       previous.physical_height==canvas.physical_height) return false;

    // LIST_Go -> getkey -> key_event holds list/input state here, not borrowed
    // screen pixels. fade and non-menu input paths do not enter this boundary.
    for(const u32 owner:{0xa916ea0u,0xa916e88u,0xa916df0u,0xa916de8u,0xa916de0u,0xa916e80u})
        replace_surface(owner,canvas.logical_width,canvas.logical_height);
    for(u32 index=0;index<4;++index) {
        // Native freescr marks the 100-byte name empty; the pointer can remain
        // retired. The name is the native live-owner discriminator.
        if(global<char>(0xa8c3f00+index*100)) replace_surface(0xa8c40a0+index*8,799,600);
    }
    auto* old=global<Texture*>(0xa916ec8);
    u32 format;
    int access;
    api.QueryTexture(old,&format,&access,nullptr,nullptr);
    auto* replacement=api.CreateTexture(renderer,format,access,canvas.physical_width,canvas.physical_height);
    global<Texture*>(0xa916ec8)=replacement;
    textures.emplace(replacement,TextureOwner{canvas,renderer});
    destroy_texture(old);

    // Heading clears and reconstructs its surface on the next native call.
    // Its two persistent software-renderer textures must follow that owner.
    destroy_renderer(global<Renderer*>(0xa9796e8));
    replace_surface(0xa9796f0,global<int>(0x68c1ef8),global<int>(0x68c1efc));
    auto* heading=software_renderer(global<Surface*>(0xa9796f0));
    global<Renderer*>(0xa9796e8)=heading;
    global<Texture*>(0x68c3228)=heading_image(heading,0x1feec4);
    global<Texture*>(0x68c3218)=heading_image(heading,0x1feedb);
    return true;
}
void save(linux_host::StateWriter& state) {
    state.put(canvas);
    state.put(mapview_canvas);
    state.put(static_cast<u32>(surfaces.size()));
    for(const auto& [surface,ratio]:surfaces) { state.put(surface); state.put(ratio); }
    state.put(static_cast<u32>(textures.size()));
    for(const auto& [texture,owner]:textures) {
        state.put(texture); state.put(owner.ratio); state.put(owner.renderer);
    }
}
void restore(linux_host::StateReader& state) {
    canvas=state.get<Scale>();
    mapview_canvas=state.get<Scale>();
    surfaces.clear(); textures.clear();
    const auto surface_count=state.get<u32>();
    for(u32 i=0;i<surface_count;++i) {
        auto* surface=state.get<Surface*>();
        surfaces.emplace(surface,state.get<Scale>());
    }
    const auto texture_count=state.get<u32>();
    for(u32 i=0;i<texture_count;++i) {
        auto* texture=state.get<Texture*>();
        const auto ratio=state.get<Scale>();
        textures.emplace(texture,TextureOwner{ratio,state.get<Renderer*>()});
    }
}
void install(const linux_host::Hooks& hooks) {
    base=hooks.base;
    resident=&hooks;
#define BIND(name) api.name=reinterpret_cast<decltype(api.name)>(dlsym(RTLD_DEFAULT,"SDL_" #name))
    BIND(UpperBlit); BIND(UpperBlitScaled); BIND(FillRect);
    BIND(CreateRGBSurface); BIND(ConvertSurface); BIND(FreeSurface);
    BIND(CreateSoftwareRenderer); BIND(DestroyRenderer); BIND(CreateTexture); BIND(CreateTextureFromSurface);
    BIND(DestroyTexture); BIND(QueryTexture); BIND(RenderCopy); BIND(SetRenderTarget);
    BIND(RenderGetScale); BIND(RenderSetScale); BIND(RenderGetLogicalSize); BIND(GetRendererOutputSize);
    BIND(GetSurfaceBlendMode); BIND(SetSurfaceBlendMode); BIND(GetSurfaceAlphaMod); BIND(SetSurfaceAlphaMod);
    BIND(GetSurfaceColorMod); BIND(SetSurfaceColorMod); BIND(HasColorKey); BIND(GetColorKey); BIND(SetColorKey);
    BIND(HasSurfaceRLE); BIND(SetSurfaceRLE);
    BIND(LockSurface); BIND(UnlockSurface);
#undef BIND
    // Main ELF PLT entries: preserve ENDBR64 and replace the seven-byte BND
    // JMP. dlsym above binds actual SDL exports, so font drawing bypasses the
    // game's logical-coordinate adapters. No SDL library code is patched.
#define IMPORT(rva,fn) hooks.replace(rva+4,7,reinterpret_cast<void*>(fn))
    IMPORT(0x8b20,create_surface); IMPORT(0x8f10,convert_surface);
    IMPORT(0x83f0,free_surface); IMPORT(0x8ac0,blit);
    IMPORT(0x88a0,blit_scaled); IMPORT(0x8260,fill);
    IMPORT(0x81a0,software_renderer); IMPORT(0x8490,create_texture);
    IMPORT(0x8760,destroy_renderer);
    IMPORT(0x88f0,texture_from_surface); IMPORT(0x8970,destroy_texture);
    IMPORT(0x88d0,query_texture); IMPORT(0x8100,copy_texture);
    IMPORT(0x8e10,set_render_target);
#undef IMPORT
    hooks.replace(0x13af40,10,reinterpret_cast<void*>(putpixel));
    hooks.replace(0x13b190,6,reinterpret_cast<void*>(getpixel));
    hooks.replace(0x13b6c0,6,reinterpret_cast<void*>(putasc));
    hooks.replace(0x143c20,10,reinterpret_cast<void*>(draw_line));
    hooks.instruction(0x10b0c6,5,mapview_target);
}
}
