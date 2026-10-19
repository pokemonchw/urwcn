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

namespace uwcn::adapter::native_ui_scene {
using Revision=u64;
using Slot=u32;

// A root contains native component instances. It contains no glyph calls,
// encoded display strings, pixel samples or a second layout engine. Native
// cache components retain their own original copy-input rectangles.
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

// The native cache owner freezes this source revision at its successful save.
// The native cache still owns its SDL resource, rectangle and actual copy.
void cache_saved(Slot);
void cache_retired(Slot);
Status materialize_cache(Slot,void* native_surface);
Status prepare_cache_restore(Slot,const native_ui_cache_owners::RestoreInput&,
    native_ui_cache_owners::PreparedRestore&);
Status cache_restored(Slot,const native_ui_cache_owners::PreparedRestore&,int native_result);
Status repaint();
Status language_changed();
Status prepare_cache(Slot,void* native_surface);

std::vector<std::uint8_t> save();
void restore(const void* payload);
void shutdown();
}
