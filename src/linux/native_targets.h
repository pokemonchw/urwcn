#pragma once
#include "hooks.h"

namespace uwcn::linux_targets {
// Install at startup, before initgr creates any native drawing resources.
void install(const linux_host::Hooks&);
// Only the confirmed main-menu construction/input boundaries may retire the
// existing owners. Returns whether their output density changed.
bool synchronize_main_menu();
}
