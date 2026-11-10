#pragma once
#include "../../sdk/host_abi.h"
#include <vector>

namespace uwcn::adapter::native_language_redraw {
// Shared input synchronization and the statically confirmed DE990 page
// continuation. State retains only pending/rebuilding flags, never UI content.
// Pending bits: menu selection, ancestor reconstruction, native zero-event exit.
struct State {u32 pending;u32 rebuilding;};
void initialize(std::uintptr_t image_base);
void request();
bool input_return(u32 caller_return_rva);
void append_hooks(std::vector<HookSpec>&);
bool dispatch(const NativeEvent&,DispatchResult&);
State save();
void restore(const State&);
}
