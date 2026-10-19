#pragma once
#include "../render/sdl_api.h"

namespace uwcn::adapter::scoped {
using Rect = render::Rect;
using Surface = render::Surface;

// This is the master logical canvas ratio, not the individual surface's size.
// A native 799-wide cache uses the same ratio as its 800-wide main canvas.
// Owners provide positive ratios and actual surfaces at least logical density.
struct SurfaceScale {
    int logical_width, logical_height;
    int physical_width, physical_height;
};
struct NativeSdl {
    int (__cdecl *UpperBlit)(Surface*, const Rect*, Surface*, Rect*);
    int (__cdecl *UpperBlitScaled)(Surface*, const Rect*, Surface*, Rect*);
    int (__cdecl *FillRect)(Surface*, const Rect*, std::uint32_t);
};

// A null scale denotes the original image's pixel coordinate space.
// Rectangles are call-local values; these functions retain no resource/content.
Rect physical_rect(const Rect&, const SurfaceScale*);
Rect logical_rect(const Rect&, const SurfaceScale*);
int blit(const NativeSdl&, Surface* src, const Rect* src_rect,
         const SurfaceScale* src_scale, Surface* dst, Rect* dst_rect,
         const SurfaceScale* dst_scale, bool scaled);
int fill(const NativeSdl&, Surface* dst, const Rect* rect,
         const SurfaceScale* dst_scale, std::uint32_t color);
}
