#pragma once
#include "../../sdk/host_abi.h"
#include "native_menu_model.h"
#include "native_text_resource.h"
#include <vector>

namespace uwcn::adapter::native_menu_component {
// Native CF790 creates a menu instance; CFFB0 consumes that same instance.
// These hooks extend the shared native API, not its callers' page functions.
void initialize(std::uintptr_t image_base);
enum class Consumer : u32 { title_panel,plain_title,plain_row,button_row,annotation };
using Enter=void (*)(const NativeEvent&,Consumer);
using Leave=void (*)(u64 token);
using DecodeOriginal=Status (*)(const char*,std::string&);
using BeforeConsume=Status (*)(const NativeEvent&,Consumer);
using Measure=Status (*)(const char*,std::int32_t& logical_width);
// Callbacks belong to this loaded generation and are rebound at initialize;
// no callback/code pointer is included in the component's saved state.
void configure(const HostApi* host,native_text_resource::Resolve resolve,
    native_text_resource::EncodeOriginal encode_original,DecodeOriginal decode_original,
    BeforeConsume before_consume,Enter enter,Leave leave);
void configure_measure(Measure);
void append_hooks(std::vector<HookSpec>& hooks);
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled);

using Handle=native_menu_model::Handle;
Handle active();
Handle snapshot(Handle handle);
Handle input_owner(Handle handle);
void retain(Handle handle);
void release(Handle handle);
void activate(Handle handle);
void deactivate();
bool consuming();

// The original CF790/CF990 constructor keeps its English input. A semantic
// producer lends this neutral resource only until that same CALL's After; the
// common commit binds it to the actual Menu/title or newly written native row.
void bind_constructor_title(u64 token,const native_text_resource::TextSource&);
void bind_constructor_row(u64 token,const native_text_resource::TextSource&);
void unbind_constructor_source(u64 token);

// Bind at the confirmed semantic producer, before its ordinary display call.
// native_record is the original CFFB0 ESI row, not a translated text pointer.
// original is its actual translatable source (UTF-8 after the existing culture
// conversion); action_suffix preserves the row's original key and '.' prefix.
void bind_title(TextComponent component,const char* original,const char* value=nullptr);
void bind_row(u32 native_record,TextComponent component,const char* original,
    const char* value=nullptr,bool action_suffix=false);
Status resolve_title(std::vector<char>& encoded);
Status resolve_row(u32 native_record,std::vector<char>& encoded);
// Complete Action/MarkedButton constructors bypass CF990. Their exact native
// row is already installed here; bind the constructor's neutral label to its
// real InputOwner and accept the original annotation from that same record.
// A frozen source handle is normalized; its frozen bindings are not changed.
void commit_row(Handle native_menu,u32 native_row_index,const native_text_resource::TextSource&);

// Run the same complete CFFB0 consumer used by normal construction. The native
// root owns background restoration and presentation; this call performs neither.
// Its temporary model activation restores the original live input instance.
// Frozen resources resolve through their source handle while the complete
// consumer writes layout and selection into its actual logical input owner.
// Normal CFFB0 captures its current native style inputs; paint holds a local
// materialization flag so its hooks consume stored source style instead.
// The flag is synchronous call state and does not belong to persisted models.
Status paint(Handle handle);
std::vector<std::uint8_t> save();
void restore(const void* payload);
void shutdown();
}
