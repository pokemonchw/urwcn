#pragma once
#include "../../sdk/host_abi.h"
#include <vector>

namespace uwcn::adapter::native_language_redraw {
// Only redraw-control bit flags cross module replacement. Bit 0 retains the
// published setup state; bit 1 belongs to the ancestor list. No native frame,
// text, geometry or rendered content is retained.
struct State {
    u32 pending;
    u32 rebuilding;
};

void initialize(std::uintptr_t image_base);
void request();
void request_ancestors();
void append_hooks(std::vector<HookSpec>& hooks);
bool menu_input(const NativeEvent& event,u32 caller_return_rva);
bool menu_input_tick(const NativeEvent& event);
bool dispatch(const NativeEvent& event,DispatchResult& result);
State save();
void restore(const State& state);
}
