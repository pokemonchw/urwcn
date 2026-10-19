#pragma once
#include "font_engine.h"

namespace uwcn::render {
// One complete native renderer-text call. The current SDL target, viewport,
// clip and scale remain owned by the native component.
Status renderer_text(FontEngine&,const TextRequest&,bool draw,Metrics&);
}
