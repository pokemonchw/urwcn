#pragma once
#include "../../sdk/host_abi.h"

namespace uwcn::adapter::native_component_style {
// Values are captured while the ordinary native constructor consumes them.
// These are raw, native-mapped color/style values, never UI geometry or pixels.
struct ButtonStyle {
    u32 suffix_color;   // 61BBAC4 -> 1149E8 -> 10E5A0 color.
    u32 suffix_outline; // 61BBA54 -> 1149D9 -> 10E5A0 outline.
};
struct PanelStyle {
    u32 background_mode; // 61BBAC8, read by 116270 and 115E70.
    u32 title_fill_color; // A211070 -> 1157B0 -> 10D900 mapped color.
};

void initialize(std::uintptr_t image_base);
ButtonStyle capture_button();
PanelStyle capture_panel();

// A locale paint installs its own construction-time native style only during
// the complete original component call, then restores the caller's globals.
// Normal construction captures style and continues its existing native call.
class ButtonScope {
    ButtonStyle previous;
public:
    explicit ButtonScope(const ButtonStyle& style);
    ~ButtonScope();
    ButtonScope(const ButtonScope&)=delete;
    ButtonScope& operator=(const ButtonScope&)=delete;
};
class PanelScope {
    PanelStyle previous;
public:
    explicit PanelScope(const PanelStyle& style);
    ~PanelScope();
    PanelScope(const PanelScope&)=delete;
    PanelScope& operator=(const PanelScope&)=delete;
};
}
