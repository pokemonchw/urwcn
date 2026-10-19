#include "immediate_text.h"
#include <cmath>

namespace uwcn::render {
namespace {
int edge(double value) { return static_cast<int>(std::lround(value)); }
}

Status surface_text(FontEngine& engine, const TextRequest& request,
                    double density_x, double density_y, bool draw,
                    Metrics& metrics) {
    auto* font=engine.font(density_y,request.native_line_height,
                           request.ink_height,request.outline);
    if(!font || !engine.measure(*font,request.utf8,density_x,metrics))
        return Status::failed;
    if(!draw || !*request.utf8) return Status::ok;

    Raster raster;
    if(!engine.raster(*font,request.utf8,request.color,raster))
        return Status::failed;
    if(!raster.image.w || !raster.image.h) return Status::ok;

    const int top=edge(request.y*density_y);
    const int bottom=edge((request.y+request.native_line_height)*density_y);
    const int baseline=top+(bottom-top-(font->bottom-font->top))/2-font->top;
    const int left=request.centered
        ? edge(request.center_x*density_x)-raster.width/2
        : edge(request.x*density_x);
    Rect destination{left+raster.crop_x,
                     baseline-raster.baseline+raster.crop_y,
                     raster.image.w,raster.image.h};

    auto& api=engine.api;
    auto* glyphs=api.CreateRGBSurfaceWithFormatFrom(
        raster.image.pixels.data(),raster.image.w,raster.image.h,
        32,raster.image.w*4,rgba32);
    if(!glyphs) return Status::failed;
    const int blend=api.SetSurfaceBlendMode(glyphs,1);
    const int drawn=blend==0
        ? api.UpperBlit(glyphs,nullptr,static_cast<Surface*>(request.surface),&destination)
        : blend;
    api.FreeSurface(glyphs);
    return drawn==0 ? Status::ok : Status::failed;
}
}
