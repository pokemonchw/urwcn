#pragma once
#include <windows.h>
#include <cstdint>

// Public SDL 2.30.0 ABI declarations. No SDL implementation or private TTF
// layout is copied; symbols bind to the game's already loaded SDL instance.
namespace uwcn::render {
struct Rect { int x,y,w,h; };
struct FRect { float x,y,w,h; };
struct Color { std::uint8_t r,g,b,a; };
struct Version { std::uint8_t major,minor,patch; };
struct PixelFormat {
    std::uint32_t format; void* palette;
    std::uint8_t bits,bytes,padding[2];
    std::uint32_t rmask,gmask,bmask,amask;
    std::uint8_t rloss,gloss,bloss,aloss,rshift,gshift,bshift,ashift;
    int refcount; PixelFormat* next;
};
struct Surface {
    std::uint32_t flags; PixelFormat* format; int w,h,pitch; void* pixels;
    void* userdata; int locked; void* blit_map; Rect clip; void* map; int refcount;
};
struct Renderer;
struct Texture;
struct Font;
constexpr std::uint32_t rgba32=0x16762004; // ABGR8888 on little endian x86.
// Font/glyph operations only. Native UI resource operations belong to adapter.
struct Sdl {
    HMODULE sdl{},ttf{};
    bool ttf_reference{};
    void (__cdecl *GetVersion)(Version*);
    int (__cdecl *LockSurface)(Surface*);
    void (__cdecl *UnlockSurface)(Surface*);
    void (__cdecl *FreeSurface)(Surface*);
    Surface* (__cdecl *CreateRGBSurfaceWithFormatFrom)(void*,int,int,int,int,std::uint32_t);
    int (__cdecl *UpperBlit)(Surface*,const Rect*,Surface*,Rect*);
    int (__cdecl *SetSurfaceBlendMode)(Surface*,int);
    void (__cdecl *RenderGetScale)(Renderer*,float*,float*);
    Texture* (__cdecl *CreateTextureFromSurface)(Renderer*,Surface*);
    int (__cdecl *SetTextureBlendMode)(Texture*,int);
    int (__cdecl *SetTextureScaleMode)(Texture*,int);
    int (__cdecl *RenderCopyF)(Renderer*,Texture*,const Rect*,const FRect*);
    void (__cdecl *DestroyTexture)(Texture*);
    void (__cdecl *GetRGBA)(std::uint32_t,const PixelFormat*,std::uint8_t*,std::uint8_t*,std::uint8_t*,std::uint8_t*);
    const Version* (__cdecl *LinkedVersion)();
    int (__cdecl *Init)();
    void (__cdecl *Quit)();
    Font* (__cdecl *OpenFontIndex)(const char*,int,long);
    void (__cdecl *CloseFont)(Font*);
    void (__cdecl *SetFontStyle)(Font*,int);
    void (__cdecl *SetFontHinting)(Font*,int);
    int (__cdecl *FontAscent)(const Font*);
    int (__cdecl *FontDescent)(const Font*);
    int (__cdecl *FontHeight)(const Font*);
    int (__cdecl *GlyphMetrics32)(Font*,std::uint32_t,int*,int*,int*,int*,int*);
    int (__cdecl *GlyphIsProvided32)(Font*,std::uint32_t);
    int (__cdecl *SizeUTF8)(Font*,const char*,int*,int*);
    Surface* (__cdecl *RenderUTF8_Blended)(Font*,const char*,Color);
    bool initialize();
    void shutdown();
};
}
