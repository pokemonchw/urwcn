#include "immediate_renderer.h"
#include <cmath>
#include <string>

namespace uwcn::render {
namespace {
int edge(double value) { return static_cast<int>(std::lround(value)); }
}

Status renderer_text(FontEngine& engine,const TextRequest& request,bool draw,
                     Metrics& metrics) {
    auto& api=engine.api;
    auto* renderer=static_cast<Renderer*>(request.renderer);
    float sx{},sy{};
    api.RenderGetScale(renderer,&sx,&sy);

    // The confirmed HUD call sites supply one complete, single-line string.
    const std::string text(request.utf8);
    auto* font=engine.font(sy,request.native_line_height,request.ink_height,request.outline);
    if(!font || !engine.measure(*font,text,sx,metrics)) return Status::failed;
    if(!draw || text.empty()) return Status::ok;

    Raster raster;
    if(!engine.raster(*font,text,request.color,raster)) return Status::failed;
    if(!raster.image.w || !raster.image.h) return Status::ok;
    const int top=edge(request.y*double(sy));
    const int bottom=edge((request.y+request.native_line_height)*double(sy));
    const int baseline=top+(bottom-top-(font->bottom-font->top))/2-font->top;
    const int left=request.centered
        ? edge(request.center_x*double(sx))-raster.width/2
        : edge(request.x*double(sx));
    // SDL_RenderCopyF multiplies this rectangle by the current native scale.
    // Dividing the final raster dimensions preserves one glyph pixel per
    // output pixel, including a fractional native scale. SDL retains clipping.
    const FRect destination{
        float(left+raster.crop_x)/sx,
        float(baseline-raster.baseline+raster.crop_y)/sy,
        float(raster.image.w)/sx,float(raster.image.h)/sy};
    auto* surface=api.CreateRGBSurfaceWithFormatFrom(
        raster.image.pixels.data(),raster.image.w,raster.image.h,
        32,raster.image.w*4,rgba32);
    if(!surface) return Status::failed;
    auto* texture=api.CreateTextureFromSurface(renderer,surface);
    api.FreeSurface(surface);
    if(!texture) return Status::failed;
    const int blend=api.SetTextureBlendMode(texture,1);
    const int filter=api.SetTextureScaleMode(texture,0);
    const int drawn=blend==0 && filter==0
        ? api.RenderCopyF(renderer,texture,nullptr,&destination) : -1;
    // SDL flushes commands referencing this texture before destroying it.
    // The native target receives this call's pixels now; no UI request survives.
    api.DestroyTexture(texture);
    return drawn==0 ? Status::ok : Status::failed;
}
}
