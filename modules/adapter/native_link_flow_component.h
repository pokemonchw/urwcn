#pragma once
#include "native_menu_component.h"
#include "native_text_resource.h"
#include <string>
#include <vector>

namespace uwcn::adapter::native_link_flow_component {
using Handle=u32;
using MenuHandle=native_menu_component::Handle;

struct Record {
    u64 native_record;
    native_text_resource::TextSource text;
    // Exact original GAME.NFO bytes consumed by the English keyword matcher.
    // The UTF-8 semantic original above expresses the same neutral content.
    std::string native_original;
    // The original GAME.NFO topic header passed in EDX to 3D820. 3D300 uses
    // its English aliases to exclude links back to this same topic.
    std::string exclusions;
};
struct Source {
    native_text_resource::SourceKey key;
    std::string topic;
    std::vector<Record> records;
};
struct Services {
    // Returns complete, NUL-terminated native-input fragments in
    // string storage, each within 3D820's confirmed 200-byte input contract.
    // These are temporary arguments, never retained by the component model.
    // An explicitly empty semantic catalog value has no fragments; a native
    // blank/control record has one original empty fragment and runs 3D820.
    Status (*prepare)(const Record&,std::vector<std::string>&);
    void (*enter)(Handle,const Record&);
    void (*leave)(Handle);
};

void initialize(std::uintptr_t image_base);
void configure(const Services&);
// Called after the original 3DF74 store has completed. The original builder
// has initialized its native link table, menu, origin and underline context.
// The active construction owns one reference; the returned handle is borrowed.
Handle begin(native_text_resource::SourceKey,const char* topic);
Handle active();
// An actual native cache/view restore installs the matching owned menu and
// English link table together. The caller supplies the real owner handle.
void activate(Handle);
void deactivate();
std::size_t append(Handle,u64 native_record,const native_text_resource::TextSource&,
    const char* native_original,const char* exclusions);
// Both ordinary 3E054 construction and locale paint consume these same owned
// neutral records through the complete original 3D820, including 3D300 links.
Status consume(Handle,std::size_t record,u32& native_return);
void capture(Handle);
// Seal at 3E1DE Before, after the original CFAF0 navigation constructors. This
// captures their independent nonzero-action native records; no link rectangle
// is copied into the source. The typed button source retains the full labels.
void seal(Handle);
const Source& source(Handle);
MenuHandle menu_owner(Handle);
// Resolve an action against the actual owned native row model after Flow has
// rebuilt its link rows. Callers use this instead of a former row ordinal.
u32 action_row(Handle,u32 action);

void retain(Handle);
void release(Handle);
// A frozen cache adopts this new handle's single reference. Its owned native
// Menu is independently snapshotted, including the latest live input fields.
Handle snapshot(Handle);
Status paint(Handle);

std::vector<std::uint8_t> save();
void restore(const void* payload);
void shutdown();
}
