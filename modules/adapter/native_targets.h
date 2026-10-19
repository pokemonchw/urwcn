#pragma once
#include "../../sdk/host_abi.h"
#include "abi1_hook_retirement.h"
#include "../render/sdl_api.h"
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
using SurfaceDestroying=void (*)(u32 surface);
void observe_component_surface_retirement(SurfaceDestroying);
struct TextureSource {u32 format;std::int32_t access,width,height;};
Status component_texture_source(u32 native_texture,TextureSource&);
// Neutral constructor inputs of the actual native cache surface. This
// descriptor contains no pixels; converted surfaces keep their original
// logical extent and their native destination pixel format.
struct SurfaceSource {
    u32 flags;
    std::int32_t width,height,depth;
    u32 red_mask,green_mask,blue_mask,alpha_mask;
};
SurfaceSource component_surface_source(const void* native_surface);
u32 create_component_surface(const SurfaceSource&);
void destroy_component_surface(u32 native_surface);
struct HudTarget {u32 surface,renderer,direction,marker;};
Status create_component_hud_target(const SurfaceSource&,HudTarget&);
void destroy_component_hud_target(const HudTarget&);
Status copy_hud_component(u32 native_surface);
Status copy_cache_component(u32 native_surface,const render::Rect* source,
    render::Rect* destination);
std::vector<std::uint8_t> save();
// Host calls this immediately after initialize/install, before game execution
// resumes. Restores saved gateways and frees the unpublished temporary page.
Status restore(const void*,u32);
void forget();
}
