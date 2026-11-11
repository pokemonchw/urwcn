#pragma once
#include "internal.h"

namespace urwcn::host::crash_report {
Status initialize(const std::wstring& package);
void native_event(const NativeEvent&);
bool dispatch(const NativeEvent&);
}
