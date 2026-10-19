#pragma once
#include "native_component_model.h"
#include "native_image_component.h"

namespace uwcn::adapter::native_footer_component {
using Handle=u32;
using native_text_resource::SourceKey;
using native_text_resource::TextSource;
// These are references to the actual native footer constructors, not copies
// of their output. The native Panel and image supply the layout dependency;
// the production paragraph supplies its original color and outline inputs.
struct Source {
    SourceKey source;
    native_component_model::Handle panel,production;
    native_image_component::Handle logo;
    TextSource credit,version;
};
struct Services {
    native_text_resource::Resolve resolve;
    native_text_resource::EncodeOriginal encode_original;
    Status (*measure)(const char*,std::int32_t&);
    Status (*paragraph_words)(std::vector<char>&);
    Status (*sprite)(std::int32_t x,std::int32_t y);
    void (*enter)(Handle,u32 outline);
    Status (*leave)(Handle);
};
void initialize(std::uintptr_t image_base);
void configure(const Services&);
// Invoked only after the complete native 1250E0 footer has constructed all
// three dependencies. The live source map owns the returned borrowed handle.
Handle upsert(const Source&);
const Source& get(Handle);
void retain(Handle);
void release(Handle);
void remove_owner(u64);
// Ordinary construction and locale materialization invoke this same method.
Status paint(Handle);
std::vector<std::uint8_t> save();
// Restored dependencies already include their serialized owning references.
void restore(const void* payload);
void shutdown();
}
