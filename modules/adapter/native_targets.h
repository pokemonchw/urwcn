#pragma once
#include "../../sdk/host_abi.h"
#include "abi1_hook_retirement.h"
#include <vector>

namespace uwcn::adapter::native_targets {
Status initialize(std::uintptr_t image_base, HMODULE sdl);
// IAT values are process-lifetime E9 gateways. Game frames may cache them.
Status install();
// Retarget the gateways to original SDL and restore original IAT values before
// the business DLL is unloaded; cached gateway addresses remain executable.
Status remove();
std::vector<abi1_retirement::RouteBinding> routes();
// Called only at the statically verified native main-menu construction point.
// It replaces the native owners' resources, not a second UI or shadow cache.
Status promote();
// FAA4B precedes the portrait component's first renderer use and full clear.
// Enlarges its native surface/renderer and reconstructs its native image assets.
Status promote_hud();
// Complete native target constructor extension. Inputs are taken from the
// original owner's constructor; the shared implementation uses its current
// real output density and registers the result with the same native owners.
u32 create_component_texture(u32 renderer,u32 format,std::int32_t access,
    std::int32_t logical_width,std::int32_t logical_height);
void destroy_component_texture(u32 texture);
using TextureDestroying=void (*)(u32 texture);
void observe_component_texture_retirement(TextureDestroying);
std::vector<std::uint8_t> save();
// Host calls this immediately after initialize/install, before game execution
// resumes. Restores saved gateways and frees the unpublished temporary page.
Status restore(const void*,u32);
void forget();
}
