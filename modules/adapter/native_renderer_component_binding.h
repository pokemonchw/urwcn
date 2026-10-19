#pragma once
#include "native_renderer_component_model.h"
#include "native_culture_legend.h"
#include <vector>

namespace uwcn::adapter::native_renderer_component_binding {
using Handle=u32;
using MenuHandle=native_menu_model::Handle;
enum class PaintDestination:u32 { active_native_owner,native_surface_cache };

void configure(std::uintptr_t image_base,const native_renderer_component_model::PaintServices&);
// Complete native factories use a glyph/metric gate without overriding the
// outline/style of their individual original primitives.
void configure_resource_services(const native_culture_legend::Services&);
// Register after the existing semantic hooks. The original metadata is shared;
// no second Hook is installed at an already owned semantic CALL boundary.
void register_hooks(std::vector<HookSpec>&);
// Root dispatch order: component_binding::begin_event, this begin_event,
// semantic dispatch, this finish_event, component_binding::finish_event.
// The shared source is synchronously borrowed before that final source pop.
void begin_event(const NativeEvent&);
Status finish_event(const NativeEvent&,DispatchResult&,Status dispatch_status=Status::ok);

const native_text_resource::SourceKey& source(Handle);
MenuHandle menu_owner(Handle);
void retain(Handle);
void release(Handle);
// The source snapshot owns typed component versions and the supplied frozen
// native Menu. No SDL target, translated output or old target pixels is saved.
Handle snapshot(Handle,MenuHandle frozen_menu);
Status paint(Handle,PaintDestination);
// One original software-cache materialization owns these temporary native
// resources until all following native Menu/Flow consumers have used them.
void begin_native_cache_resources();
void end_native_cache_resources();
void activate(Handle);
// Called by the native_targets destruction gateway, for resource lifecycle
// identity only. It does not read or retain SDL/pixel contents.
void native_texture_destroying(u32 texture);
void native_surface_destroying(u32 surface);
native_renderer_component_model::TargetSource target_source(u32 native_owner_field);
void hud_icon_constructed(u32 native_owner_field,u32 icon_handle);
// Shared original FB01C boundary: before an ordinary icon constructor it is
// the successful native overlay-clear end. During complete background paint
// it returns through the new native component's synchronous ABI wrapper.
bool finish_overlay_background(const NativeEvent&,DispatchResult&);
void menu_retired(Handle native_owner,MenuHandle);
std::vector<std::uint8_t> save();
void restore(const void*);
void shutdown();
}
