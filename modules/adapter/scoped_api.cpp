#include "scoped_api.h"
#include <algorithm>
#include <cmath>
#include <cstdint>

// Logical clipping below is adapted from SDL 2.30.0 SDL_surface.c and
// SDL_rect_impl.h. It is altered code: only rectangle calculations are kept;
// actual pixel copying is performed by the game's SDL exports.
// https://github.com/libsdl-org/SDL/tree/release-2.30.0/src/video
/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2024 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:
  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

namespace uwcn::adapter::scoped {
namespace {
int edge(int value,int numerator,int denominator) {
    const auto product=static_cast<std::int64_t>(value)*numerator;
    return static_cast<int>(product<0
        ? -((-product+denominator/2)/denominator)
        : (product+denominator/2)/denominator);
}
Rect map_rect(const Rect& r,int xn,int xd,int yn,int yd) {
    const int x=edge(r.x,xn,xd),y=edge(r.y,yn,yd);
    return {x,y,edge(r.x+r.w,xn,xd)-x,edge(r.y+r.h,yn,yd)-y};
}
bool intersect(Rect a,Rect b,Rect& result) {
    // SDL preserves result.x/y for an already empty input rectangle, and
    // permits negative extents in the result of disjoint nonempty inputs.
    if(a.w<=0 || a.h<=0 || b.w<=0 || b.h<=0) {
        result.w=result.h=0;
        return false;
    }
    const int left=(std::max)(a.x,b.x),top=(std::max)(a.y,b.y);
    result={left,top,(std::min)(a.x+a.w,b.x+b.w)-left,
                     (std::min)(a.y+a.h,b.y+b.h)-top};
    return result.w>0 && result.h>0;
}
struct Clipped {
    Rect source,target;
    bool copy;
};
Clipped clip_plain(Rect source_bounds,const Rect* source,Rect destination,
                   Rect destination_clip) {
    const Rect empty_output{destination.x,destination.y,0,0};
    Rect from=source_bounds;
    if(source) {
        Rect clipped{};
        if(!intersect(*source,source_bounds,clipped))
            return {from,empty_output,false};
        destination.x+=clipped.x-source->x;
        destination.y+=clipped.y-source->y;
        from=clipped;
    }
    destination.w=from.w;
    destination.h=from.h;
    Rect clipped{};
    if(!intersect(destination,destination_clip,clipped))
        return {from,empty_output,false};
    from.x+=clipped.x-destination.x;
    from.y+=clipped.y-destination.y;
    from.w=clipped.w;
    from.h=clipped.h;
    return {from,clipped,true};
}
struct Axis { double source_begin,source_end,target_begin,target_end; };
Axis clip_axis(int source_begin,int source_length,int source_bound,
               int target_begin,int target_length,int clip_begin,int clip_length,
               bool explicit_source) {
    Axis a{static_cast<double>(source_begin),
           static_cast<double>(source_begin)+source_length,
           static_cast<double>(target_begin),
           static_cast<double>(target_begin)+target_length};
    const double factor=static_cast<double>(target_length)/source_length;
    if(explicit_source) {
        if(a.source_begin<0) {
            a.target_begin-=a.source_begin*factor;
            a.source_begin=0;
        }
        if(a.source_end>source_bound) {
            a.target_end-=(a.source_end-source_bound)*factor;
            a.source_end=source_bound;
        }
    }
    a.target_begin-=clip_begin;
    a.target_end-=clip_begin;
    if(a.target_begin<0) {
        a.source_begin-=a.target_begin/factor;
        a.target_begin=0;
    }
    if(a.target_end>clip_length) {
        a.source_end-=(a.target_end-clip_length)/factor;
        a.target_end=clip_length;
    }
    a.target_begin+=clip_begin;
    a.target_end+=clip_begin;
    return a;
}
int rounded(double value) { return static_cast<int>(std::lround(value)); }
Clipped clip_scaled(Rect source_bounds,const Rect* source,Rect destination,
                    Rect destination_clip) {
    const Rect from=source?*source:source_bounds;
    if(from.w==destination.w && from.h==destination.h)
        return clip_plain(source_bounds,source,destination,destination_clip);
    const auto x=clip_axis(from.x,from.w,source_bounds.w,
                          destination.x,destination.w,destination_clip.x,
                          destination_clip.w,source!=nullptr);
    const auto y=clip_axis(from.y,from.h,source_bounds.h,
                          destination.y,destination.h,destination_clip.y,
                          destination_clip.h,source!=nullptr);
    Rect clipped_source{rounded(x.source_begin),rounded(y.source_begin),
                        rounded(x.source_end-x.source_begin),
                        rounded(y.source_end-y.source_begin)};
    Rect clipped_target{rounded(x.target_begin),rounded(y.target_begin),
                        rounded(x.target_end-x.target_begin),
                        rounded(y.target_end-y.target_begin)};
    intersect(source_bounds,clipped_source,clipped_source);
    intersect(destination_clip,clipped_target,clipped_target);
    const bool copy=clipped_target.w!=0 && clipped_target.h!=0 &&
                    clipped_source.w>0 && clipped_source.h>0;
    return {clipped_source,clipped_target,copy};
}
}

Rect physical_rect(const Rect& rect,const SurfaceScale* scale) {
    return scale?map_rect(rect,scale->physical_width,scale->logical_width,
                              scale->physical_height,scale->logical_height):rect;
}
Rect logical_rect(const Rect& rect,const SurfaceScale* scale) {
    return scale?map_rect(rect,scale->logical_width,scale->physical_width,
                              scale->logical_height,scale->physical_height):rect;
}

int blit(const NativeSdl& api,Surface* src,const Rect* src_rect,
         const SurfaceScale* src_scale,Surface* dst,Rect* dst_rect,
         const SurfaceScale* dst_scale,bool scaled) {
    const auto original=scaled?api.UpperBlitScaled:api.UpperBlit;
    if(!src_scale && !dst_scale)
        return original(src,src_rect,dst,dst_rect);
    // SDL 2.30 checks these before clipping or writing dst_rect. Forward the
    // original call so its documented error/result semantics remain SDL's.
    if(!src || !dst || src->locked || dst->locked)
        return original(src,src_rect,dst,dst_rect);

    const Rect source_bounds=logical_rect({0,0,src->w,src->h},src_scale);
    const Rect destination_bounds=logical_rect({0,0,dst->w,dst->h},dst_scale);
    const Rect destination=dst_rect?*dst_rect:destination_bounds;
    const Rect destination_clip=logical_rect(dst->clip,dst_scale);
    const auto clipped=scaled
        ? clip_scaled(source_bounds,src_rect,destination,destination_clip)
        : clip_plain(source_bounds,src_rect,destination,destination_clip);
    // Inputs may alias (10D900 supplies the same native rectangle twice).
    // All input calculations finish before copying the logical result back.
    if(dst_rect) *dst_rect=clipped.target;
    if(!clipped.copy) return 0;

    const Rect physical_source=physical_rect(clipped.source,src_scale);
    Rect physical_target=physical_rect(clipped.target,dst_scale);
    const auto copy=(physical_source.w==physical_target.w &&
                     physical_source.h==physical_target.h)
        ? api.UpperBlit:api.UpperBlitScaled;
    return copy(src,&physical_source,dst,&physical_target);
}

int fill(const NativeSdl& api,Surface* dst,const Rect* rect,
         const SurfaceScale* dst_scale,std::uint32_t color) {
    if(!rect || !dst_scale) return api.FillRect(dst,rect,color);
    const Rect physical=physical_rect(*rect,dst_scale);
    return api.FillRect(dst,&physical,color);
}
}
