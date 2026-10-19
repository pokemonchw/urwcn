#pragma once
#include "../../sdk/host_abi.h"
#include <vector>

namespace uwcn::adapter::native_language_input {
// This is only the current keyboard press, not UI or translated text state.
struct State { u32 f10_consumed{}; };
struct Result { bool handled; bool toggle; };
void append_hooks(std::uintptr_t image_base,std::vector<HookSpec>& hooks);
Result dispatch(const NativeEvent& event,DispatchResult& result,std::uintptr_t image_base);
State save();
void restore(State state);
}
