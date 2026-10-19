#include "immediate_sprite.h"
#include "byayoi_sprite.h"
#include <algorithm>
#include <cmath>
#include <vector>

namespace uwcn::render {
namespace {
int edge(double value) { return static_cast<int>(std::lround(value)); }
}

Status surface_sprite(Sdl& api,const SpriteRequest& request) {
    auto* target=static_cast<Surface*>(request.surface);
    const double density_x=double(target->w)/request.logical_width;
    const double density_y=double(target->h)/request.logical_height;
    const int left=edge(request.x*density_x);
    const int top=edge(request.y*density_y);
    const int width=edge((request.x+byayoi_sprite::width)*density_x)-left;
    const int height=edge((request.y+byayoi_sprite::height)*density_y)-top;
    std::vector<std::uint32_t> pixels(static_cast<std::size_t>(width)*height);
    for(int y=0;y<byayoi_sprite::height;++y) {
        const int cell_top=edge((request.y+y)*density_y)-top;
        const int cell_bottom=edge((request.y+y+1)*density_y)-top;
        for(int x=0;x<byayoi_sprite::width;++x) {
            const auto& color=byayoi_sprite::palette[byayoi_sprite::pixels[y][x]];
            if(!color.a) continue;
            const auto rgba=std::uint32_t(color.r) | (std::uint32_t(color.g)<<8) |
                            (std::uint32_t(color.b)<<16) | (std::uint32_t(color.a)<<24);
            const int cell_left=edge((request.x+x)*density_x)-left;
            const int cell_right=edge((request.x+x+1)*density_x)-left;
            for(int row=cell_top;row<cell_bottom;++row) {
                auto first=pixels.begin()+static_cast<std::size_t>(row)*width;
                std::fill(first+cell_left,first+cell_right,rgba);
            }
        }
    }

    auto* sprite=api.CreateRGBSurfaceWithFormatFrom(
        pixels.data(),width,height,32,width*4,rgba32);
    if(!sprite) return Status::failed;
    Rect destination{left,top,width,height};
    const int blend=api.SetSurfaceBlendMode(sprite,1);
    const int drawn=blend==0 ? api.UpperBlit(sprite,nullptr,target,&destination) : blend;
    api.FreeSurface(sprite);
    return drawn==0 ? Status::ok : Status::failed;
}
}
