#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "sdk/host_abi.h"
#include <string>

namespace uwcn::host {
extern HMODULE self;
extern HostApi api;
Status UWCN_CALL invoke(ModuleId,u32,const void*,u32,void*,u32*);
Status UWCN_CALL install_hooks(const HookSpec*,u32);
Status UWCN_CALL native_fragment(u32,u32);
void dispatch(NativeEvent&,DispatchResult&);
void service_control();
bool install_control_imports();
void UWCN_CALL log(const wchar_t*);
bool initialize_modules();
void start_control_server();
}
