#pragma once
#include "font_engine.h"

namespace uwcn::render {
// The native resource owner supplies the physical/logical scale of its actual
// destination. This call neither retains the request nor owns a UI resource.
Status surface_text(FontEngine&, const TextRequest&, double density_x,
                    double density_y, bool draw, Metrics&);
}
