#pragma once
#include "../../sdk/host_abi.h"
#include <vector>

namespace uwcn::adapter::native_language_redraw {
// Shared input synchronization and confirmed setup/DE990 page continuations.
// State retains only pending/rebuilding flags, never UI content. Pending bits:
// menu selection, ancestors, native zero-event exit, setup reconstruction.
struct State {u32 pending;u32 rebuilding;};
void initialize(std::uintptr_t image_base);
void request();
bool input_return(u32 caller_return_rva);
void append_hooks(std::vector<HookSpec>&);
bool dispatch(const NativeEvent&,DispatchResult&);
State save();
void restore(const State&);
}
