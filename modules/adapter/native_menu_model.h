#pragma once
#include "../../sdk/host_abi.h"
#include "native_text_resource.h"
#include "native_component_style.h"
#include <array>
#include <string>
#include <vector>

namespace uwcn::adapter::native_menu_model {
using Handle=u32;
inline constexpr u32 header_bytes=0x190;
inline constexpr u32 rows_bytes=0x5AA0;
inline constexpr u32 row_stride=0xE8;
inline constexpr u32 row_capacity=100;

// The game itself saves/restores these two ranges through fwrite/fread:
// 5F54A20 +190h and 5F4EF10 +5AA0h (100 native E8h menu records).
// They retain original English data, actions and native layout/input fields.
// No borrowed source pointers, callbacks or drawing commands are added.
struct MenuModel {
    std::array<std::uint8_t,header_bytes> header;
    std::array<std::uint8_t,rows_bytes> rows;
};
struct PaintStyle {
    native_component_style::PanelStyle panel;
    native_component_style::ButtonStyle button;
};
struct TextBinding {
    bool bound=false;
    native_text_resource::SourceKey key{};
    native_text_resource::TextSource source{};
    // The native action-key prefix and '.' are syntax, not translated text.
    std::string prefix;
};

void initialize(std::uintptr_t image_base);

// The caller deactivates the previous instance before CF790 overwrites the
// shared native ranges. After that normal construction, create the current
// instance; subsequent native construction/consumption uses this same model.
Handle create_from_native();
// Copy only this native input/source model into a detached instance. The
// returned handle owns one reference; the receiving cache adopts that reference.
// No pixels, renderer output or native paint calls are copied or performed.
Handle snapshot(Handle handle);
void capture_into(Handle handle);
// Ordinary CFFB0 construction captures ambient panel inputs. Button inputs
// come from the same captured native header consumed at D030F/D031A, since
// CFFB0 itself replaces the ambient button globals before 114680 consumes them.
// Locale materialization installs these values and never recaptures ambient.
void capture_style(Handle handle);
const PaintStyle& style(Handle handle);
// External root/cache owners retain and release their own references. The
// active native view has an independent reference released by deactivate().
void retain(Handle handle);
void release(Handle handle);

// Always capture the current native instance before installing another one,
// including activation of the same handle. Live selection/scroll/input fields
// must never be replaced by an earlier captured copy of the active instance.
void activate(Handle handle);
void deactivate();
void destroy(Handle handle);
Handle active();

void bind_title(Handle handle,const native_text_resource::TextSource& source);
void bind_row(Handle handle,u32 index,const native_text_resource::TextSource& source,
    const std::string& prefix);
const TextBinding& title(Handle handle);
const TextBinding& row(Handle handle,u32 index);

// Serialized u32 metadata and original model bytes, ordered by handle. No
// module-owned allocations or code pointers cross a business-module reload.
// restore accepts exactly the payload returned by save and does not write the
// game's active ranges; the resident transaction has not advanced that state.
// Handles passed to the other methods are valid, previously created handles;
// zero denotes no active instance and is not an instance handle.
std::vector<std::uint8_t> save();
void restore(const void* payload);
}
