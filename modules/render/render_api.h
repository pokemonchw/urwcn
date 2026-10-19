#pragma once
#include "../../sdk/host_abi.h"

namespace uwcn::render {
namespace op {
inline constexpr u32 measure=1, draw=2, sprite=3;
inline constexpr u32 measure_renderer=4, draw_renderer=5;
}
// Each request represents one complete native text call. Coordinates and
// clipping remain native. Surface operations use the actual native surface;
// renderer operations use the renderer's current target and actual scale.
struct TextRequest {
    const char* utf8;
    void* surface;
    void* renderer;
    std::int32_t x,y;
    u32 color; // RGBA packed as R | G<<8 | B<<16 | A<<24, not native pixel bits.
    std::int32_t native_line_height;
    std::int32_t ink_height;
    // Native centering may supply the original center rather than a rounded
    // left position for this invocation.
    u32 centered;
    std::int32_t center_x;
    u32 outline; // Native +/-1 shadow calls; calibration only, no extra drawing.
    std::int32_t logical_width,logical_height; // Confirmed native target domain.
};
struct Metrics {
    std::int32_t logical_width;
    std::int32_t pixel_width;
    std::int32_t point_size;
    std::int32_t ascent,descent,height,line_top,line_bottom;
    double density_x,density_y;
};
// One native component draw invocation; the 34-by-34 source pixels retain
// their logical size while the native target supplies the output density.
struct SpriteRequest {
    void* surface;
    std::int32_t x,y;
    std::int32_t logical_width,logical_height;
};
}
