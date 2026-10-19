#pragma once
#include "native_component_style.h"
#include <array>
#include <vector>

namespace uwcn::adapter::native_culture_legend {
// This complete native resource constructor has no caller parameters. Its
// original E3A50 template owns the panel, eleven literal culture resources,
// their layout and its local software target. Only actual native style inputs
// are retained; the temporary EDI renderer is never a persistent owner.
struct Source {
    u64 revision;
    native_component_style::PanelStyle panel;
    u32 panel_color;
    std::array<u32,3> palette;
};
struct Services {void (*enter)(u64 revision);void (*leave)(u64 revision);};
void initialize(std::uintptr_t image_base,const Services&);
void append_hooks(std::vector<HookSpec>&);
Status dispatch(const NativeEvent&,DispatchResult&,bool& handled);
// Unified resource invalidation reconstructs the original 5F8FA78 owner before
// any dependent native map/container paints it. It never copies an old bitmap.
Status language_changed();
void native_texture_destroying(u32 texture);
bool constructed();
const Source& source();
std::vector<std::uint8_t> save();
void restore(const void*);
void shutdown();
}
