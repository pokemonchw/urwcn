#include "native_component_style.h"

namespace uwcn::adapter::native_component_style {
namespace {
std::uintptr_t base{};
constexpr u32 button_suffix_color=0x61BBAC4;
constexpr u32 button_suffix_outline=0x61BBA54;
constexpr u32 panel_background_mode=0x61BBAC8;
constexpr u32 panel_title_fill_color=0xA211070;

u32& native(u32 rva) { return *reinterpret_cast<u32*>(base+rva); }
void install(const ButtonStyle& style) {
    native(button_suffix_color)=style.suffix_color;
    native(button_suffix_outline)=style.suffix_outline;
}
void install(const PanelStyle& style) {
    native(panel_background_mode)=style.background_mode;
    native(panel_title_fill_color)=style.title_fill_color;
}
}

void initialize(std::uintptr_t image_base) { base=image_base; }

ButtonStyle capture_button() {
    return {native(button_suffix_color),native(button_suffix_outline)};
}
PanelStyle capture_panel() {
    return {native(panel_background_mode),native(panel_title_fill_color)};
}

ButtonScope::ButtonScope(const ButtonStyle& style):previous(capture_button()) { install(style); }
ButtonScope::~ButtonScope() { install(previous); }
PanelScope::PanelScope(const PanelStyle& style):previous(capture_panel()) { install(style); }
PanelScope::~PanelScope() { install(previous); }
}
