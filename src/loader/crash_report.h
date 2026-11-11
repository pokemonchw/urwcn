#pragma once
#include "internal.h"

namespace uwcn::host::crash_report {
Status initialize(const std::wstring& package);
void native_event(const NativeEvent&);
bool dispatch(const NativeEvent&);
}
