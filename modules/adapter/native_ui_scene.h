#pragma once
#include "native_component_model.h"
#include "native_menu_component.h"
#include "native_image_component.h"
#include "native_root_component.h"
#include "native_link_flow_component.h"
#include "native_renderer_component_binding.h"
#include "native_footer_component.h"
#include "native_ui_cache_owners.h"
#include "native_message_flow.h"
#include <vector>

namespace urwcn::adapter::native_ui_scene {
using Revision=u64;
using Slot=u32;

// Legacy component/source lifetime registry, retained for HDA7 handover.
// It cannot repaint a page or materialize a cache. Complete native drawing
// continuations and original cache operations exclusively own those pixels.
void initialize(std::uintptr_t image_base,const native_component_model::PaintServices&);
void synchronize_root();
void component_constructed(native_component_model::Handle);
void menu_constructed(native_menu_component::Handle);
void menu_retired(native_menu_component::Handle);
void image_constructed(native_image_component::Handle);
void flow_constructed(native_link_flow_component::Handle);
void renderer_constructed(native_renderer_component_binding::Handle);
void renderer_retired(native_text_resource::SourceKey);
void footer_constructed(native_footer_component::Handle);
void message_constructed(native_message_flow::Handle);
Revision current();
bool materializing();
// Observe native cache ownership without replacing pixels or rectangles.
void cache_saved(Slot);
void cache_retired(Slot);
// Borrow the actual Menu input retained by this native background cache.
// This reads only the original CF790/CF990 model; it does not paint a Scene.
native_menu_component::Handle saved_menu(Slot);
native_root_component::RootRevision saved_background(Slot);
// A native save records the current language revision. Complete native
// owners consume this marker before restoring their original cache.
bool cache_needs_language(Slot);
Status prepare_cache_restore(Slot,const native_ui_cache_owners::RestoreInput&,
    native_ui_cache_owners::PreparedRestore&);
Status cache_restored(Slot,const native_ui_cache_owners::PreparedRestore&,int native_result);
// Invalidate language resources only; do not repaint this registry.
Status language_changed();

std::vector<std::uint8_t> save();
void restore(const void* payload);
void shutdown();
}
