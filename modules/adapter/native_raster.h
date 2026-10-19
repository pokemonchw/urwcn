#pragma once
#include "../../sdk/host_abi.h"
#include "../render/sdl_api.h"

namespace uwcn::adapter::native_raster {
// The caller owns the native surface and supplies its original logical extent.
// It is a valid 32-bit surface whose physical dimensions are at least the
// positive logical dimensions. The caller has already performed any SDL lock
// required by this surface and keeps it locked for the entire operation.
// No SDL flags, ownership, clipping state or resource lifecycle are changed.
struct Target {
    render::Surface* surface;
    int logical_width,logical_height;
};

// Packed values retain the native surface's format; no color conversion occurs.
// A logical pixel writes its complete rounded physical cell. Reads sample its
// exact integer center, floor((2*x+1)*physical/(2*logical)), on each axis.
// Native out-of-range reads return 0.
void pixel(Target,int x,int y,u32 packed) noexcept;
u32 read_pixel(Target,int x,int y) noexcept;

// 114340: reject the entire line if either logical endpoint is out of range;
// retain its original inclusive endpoint, modulo and integer stepping rules.
void line(Target,int x1,int y1,int x2,int y2,u32 packed) noexcept;

// 10BD90: row-major 8 x 10 native mask; only bytes exactly equal to 1 draw.
// Out-of-range logical glyph pixels are omitted, as in the original routine.
void glyph(Target,int x,int y,const std::uint8_t* native_80_mask,u32 packed) noexcept;
}
