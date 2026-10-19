#include "native_raster.h"

// The project's required compiler is i686 MinGW GCC. These target options also
// prevent integer loops from being vectorized through FP/SIMD registers. The
// parent integration must statically inspect the compiled instructions before
// using these kernels from a native bridge without an FP-state save.
#define UWCN_INTEGER_RASTER __attribute__((target("no-sse,no-sse2,no-mmx")))

namespace uwcn::adapter::native_raster {
namespace {
UWCN_INTEGER_RASTER int edge(int coordinate,int physical,int logical) noexcept {
    // Calls use nonnegative, in-range edges. Adding floor(logical/2) implements
    // round-to-nearest with positive halves rounded up, without floating point.
    const auto numerator=std::int64_t(coordinate)*physical+logical/2;
    return static_cast<int>(numerator/logical);
}
UWCN_INTEGER_RASTER int sample_center(int coordinate,int physical,int logical) noexcept {
    // Exact logical-cell center, evaluated in integers. With physical >=
    // logical it belongs to [edge(x),edge(x+1)), unlike a truncated 16.16
    // reverse-scaling increment, which can sample a neighbouring write cell.
    const auto numerator=(std::uint64_t(coordinate)*2+1)*static_cast<unsigned>(physical);
    return static_cast<int>(numerator/(std::uint64_t(logical)*2));
}
UWCN_INTEGER_RASTER u32* row(render::Surface* surface,int y) noexcept {
    return reinterpret_cast<u32*>(static_cast<std::uint8_t*>(surface->pixels)+std::size_t(y)*surface->pitch);
}
UWCN_INTEGER_RASTER bool in_bounds(Target target,int x,int y) noexcept {
    return x>=0 && y>=0 && x<target.logical_width && y<target.logical_height;
}
}

UWCN_INTEGER_RASTER void pixel(Target target,int x,int y,u32 packed) noexcept {
    // Original 10BAB0 rejects logical coordinates outside the 800 x 600 domain.
    if(!in_bounds(target,x,y)) return;
    const int left=edge(x,target.surface->w,target.logical_width);
    const int right=edge(x+1,target.surface->w,target.logical_width);
    const int top=edge(y,target.surface->h,target.logical_height);
    const int bottom=edge(y+1,target.surface->h,target.logical_height);
    for(int py=top;py<bottom;++py) {
        auto* destination=row(target.surface,py);
        for(int px=left;px<right;++px) destination[px]=packed;
    }
}

UWCN_INTEGER_RASTER u32 read_pixel(Target target,int x,int y) noexcept {
    // Original 10BC90 returns packed zero for an out-of-range coordinate.
    if(!in_bounds(target,x,y)) return 0;
    const int px=sample_center(x,target.surface->w,target.logical_width);
    const int py=sample_center(y,target.surface->h,target.logical_height);
    return row(target.surface,py)[px];
}

UWCN_INTEGER_RASTER void line(Target target,int x1,int y1,int x2,int y2,u32 packed) noexcept {
    // 11434C..11439C rejects endpoints; it does not clip the supplied line.
    if(!in_bounds(target,x1,y1) || !in_bounds(target,x2,y2)) return;
    const int dx=x2>=x1?x2-x1:x1-x2;
    const int dy=y2>=y1?y2-y1:y1-y2;
    int minor_x=x2>=x1?1:-1;
    int major_x=minor_x;
    int minor_y=y2>=y1?1:-1;
    int major_y=minor_y;
    int major,minor;
    // Match the original dx >= dy branch, including equal endpoints.
    if(dx>=dy) {
        minor_x=0;
        major_y=0;
        major=dx;
        minor=dy;
    } else {
        major_x=0;
        minor_y=0;
        major=dy;
        minor=dx;
    }
    int error=major/2;
    int remaining=major+1;
    do {
        // 114445..11445D uses y % 600 and x % 800 before its point call.
        pixel(target,x1%target.logical_width,y1%target.logical_height,packed);
        error+=minor;
        if(error>=major) {
            x1+=minor_x;
            y1+=minor_y;
            error-=major;
        }
        x1+=major_x;
        y1+=major_y;
    } while(--remaining);
}

UWCN_INTEGER_RASTER void glyph(Target target,int x,int y,const std::uint8_t* native_80_mask,u32 packed) noexcept {
    for(int gy=0;gy<10;++gy) {
        for(int gx=0;gx<8;++gx) {
            if(native_80_mask[gy*8+gx]==1) pixel(target,x+gx,y+gy,packed);
        }
    }
}
}

#undef UWCN_INTEGER_RASTER
