#pragma once
#include "../../sdk/host_abi.h"
#include <windows.h>
#include <cstdint>

namespace uwcn::adapter::native_raster {
// The caller has identified the supported game image and retired the former
// Host pixel hooks. It owns the native main surface at image + 61BBB10, whose
// 800 x 600 logical domain has physical dimensions of at least 800 x 600.
// Installation/removal occur while the native drawing thread cannot advance.
// No invocation of these synchronous primitives may be active during removal.
Status install_raster_patches(std::uintptr_t image_base,HMODULE sdl);
// Restore every installed instruction before unloading this adapter DLL.
// A non-ok result must prevent unloading; it does not authorize leaving a
// branch into an unloaded module. No hooks are installed by static init.
Status remove_raster_patches();
}
