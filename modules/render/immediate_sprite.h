#pragma once
#include "render_api.h"
#include "sdl_api.h"

namespace uwcn::render {
// Rasterize and submit within this native component invocation. The temporary
// image carries no UI state beyond the return of this call.
Status surface_sprite(Sdl&,const SpriteRequest&);
}
