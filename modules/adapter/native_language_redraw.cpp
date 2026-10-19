#include "native_language_redraw.h"
#include <cstring>

namespace uwcn::adapter::native_language_redraw {
namespace {
std::uintptr_t base{};
State state{};
constexpr u32 native_menu_input_result=0x5100;
}
void initialize(std::uintptr_t image_base) {base=image_base;state={};}
void request() {state.pending=1;}
void append_hooks(std::vector<HookSpec>& hooks) {
    // This is the common D1120 input protocol, shared by every native Menu.
    hooks.push_back({native_menu_input_result,HookKind::inline_code,0xD12B4,0,0,8,
        {0x8B,0xF8,0x8D,0x85,0xF8,0xFB,0xFF,0xFF}});
}
bool dispatch(const NativeEvent& event,DispatchResult&) {
    if(event.id!=native_menu_input_result) return false;
    if(state.pending) {
        // The source rebuild can reindex native link rows while preserving
        // their English action identity. D1120's previous-selection local and
        // its own repaint flag must consume the resulting real selection.
        *reinterpret_cast<u32*>(event.frame->ebp-0x430)=
            *reinterpret_cast<const u32*>(base+0x5F54AB0);
        *reinterpret_cast<u32*>(event.frame->ebp-0x41C)=1;
        state.pending=0;
    }
    return true;
}
State save() {return state;}
void restore(const State& value) {state=value;}
}