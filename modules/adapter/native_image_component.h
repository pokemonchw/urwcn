#pragma once
#include "native_text_resource.h"

namespace uwcn::adapter::native_image_component {
using Handle=u32;
using native_text_resource::SourceKey;
// The entire neutral 112980 image descriptor remains native input. The native
// function parses its optional size suffix and owns loading, scaling, border
// construction, immediate submission and disposal of the temporary image.
struct ImageSource {
    SourceKey source;
    std::string descriptor;
    std::int32_t x,y;
    u32 border;
};
struct Inputs {
    std::string descriptor;
    std::int32_t x,y;
    u32 border;
};
struct PreparedSource {
    const char* descriptor;
    std::int32_t x,y;
    u32 border;
};
void initialize(std::uintptr_t image_base);
void append_hooks(std::vector<HookSpec>&);
Status dispatch(const NativeEvent&,DispatchResult&,bool& handled);
// Called only for a confirmed 112980 semantic asset producer. The producer
// supplies the stable field/record identity; this function does not infer one
// from filenames, call tokens, geometry, draw order or surface pixels.
Inputs capture(const NativeEvent&);
Handle upsert(SourceKey,const Inputs&);
// The confirmed producer requests an already constructed native source.
Handle current(SourceKey);
const ImageSource& get(Handle);
PreparedSource prepare(Handle);
void retain(Handle);
void release(Handle);
void remove(Handle);
void remove_owner(u64 owner);
// Status reports completion of the native invocation. IMG_Load failure keeps
// the original 112260 error/report/return behavior; no image is substituted.
Status paint(Handle);
std::vector<std::uint8_t> save();
// Restored Scene/cache handles already own their serialized references.
void restore(const void* payload);
void shutdown();
}
