#pragma once
#include "native_renderer_component_model.h"

namespace uwcn::adapter::native_hud_icons {
using Handle=u32;
using TargetSource=native_renderer_component_model::TargetSource;
using SourceKey=native_text_resource::SourceKey;
enum class Kind:u32 { direction,overlay_direction,activity };
struct IconSource {
    SourceKey key;TargetSource target;Kind kind;
    u32 native_record,alpha;
};
struct PreparedIcon {u32 native_record,alpha;};
using OwnerSource=TargetSource (*)(u32 native_owner_field);
using Constructed=void (*)(u32 native_owner_field,Handle);
void configure(std::uintptr_t image_base,OwnerSource,Constructed);
void append_hooks(std::vector<HookSpec>&);
Status dispatch(const NativeEvent&,DispatchResult&,bool& handled);
const SourceKey& source(Handle);
const IconSource& get(Handle);
PreparedIcon prepare(Handle);
void retain(Handle);
void release(Handle);
Handle snapshot(Handle,TargetSource);
Status paint(Handle);
void remove_owner(u64 native_owner_lifetime);
std::vector<std::uint8_t> save();
void restore(const void*);
void shutdown();
}
