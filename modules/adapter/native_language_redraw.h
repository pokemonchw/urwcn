#pragma once
#include "../../sdk/host_abi.h"
#include <vector>

namespace uwcn::adapter::native_language_redraw {
// Shared native input synchronization only. Language materialization belongs
// to the native UI source containers; no page reentry is scheduled here.
struct State {u32 pending;u32 rebuilding;};
void initialize(std::uintptr_t image_base);
void request();
void append_hooks(std::vector<HookSpec>&);
bool dispatch(const NativeEvent&,DispatchResult&);
State save();
void restore(const State&);
}