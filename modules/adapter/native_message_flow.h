#pragma once
#include "native_message_source.h"
#include "native_text_resource.h"
#include "native_component_style.h"
#include <array>

namespace uwcn::adapter::native_message_flow {
using Handle=u32;
using SourceKey=native_text_resource::SourceKey;
struct NativeState {
    u32 message_x,message_y,cursor_x,cursor_y,color,completed_x,completed_y;
    std::uint8_t counter;
};
// Original F5B00 caller context. Message x/y are deliberately absent: complete
// F6020 establishes the new native bottom-line anchor before any word paints.
struct PaginationSeed {u32 cursor_x,cursor_y,color;std::uint8_t counter;};
// Complete original FA33F -> 116270 constructor inputs, captured before the
// normal consumer. This opaque parent belongs to this same message owner.
struct PanelSource {
    std::int32_t x,y,width,height;
    u32 flags,color;
    native_component_style::PanelStyle style;
    std::string native_title;
};
// F6510's accepted, original English producer expressions. These are message
// records, never rendered words, translated output, positions or pixel data.
struct Record {
    u64 identity;
    std::string native_input,english;
    native_message_source::Text text;
    bool sound_field;
    bool counter_input;
    std::uint8_t counter;
    PaginationSeed entry;
};
struct Source {
    SourceKey key;
    PanelSource panel;
    std::array<u32,4> rectangle;
    u32 line_height;
    PaginationSeed origin;
    std::vector<Record> records;
    bool ends_at_wait=false;
    u32 wait_ordinal=0;
};
// Only actual game frames are named here. No Mod code address is retained.
struct Waiting { u32 parent_frame,wait_frame,acknowledged; };
struct Continuation {
    u32 return_rva,index,color,cursor_x,cursor_y,wait_color;
    bool complete;
};
struct Services { Status (*consume)(Handle,const Record&); };
void initialize(std::uintptr_t image_base);
void configure(const Services&);
Handle construct_background(SourceKey,const PanelSource&);
Status paint_background(Handle);
// Called solely at F67C3, after native sound/case/repeat acceptance. Each
// append creates a new immutable source revision; actual input has one owner.
// The actual complete native message-panel constructor establishes that owner
// before append. There is no synthesized default background.
Handle append(SourceKey,u32 native_frame,const char* native_input,
    const char* accepted_english,bool sound_field,const native_message_source::Text&);
const Source& get(Handle);
const Record& record(u32 native_frame);
Handle live_source(u32 native_frame);
// FA347 follows the actual whole native message-panel clear. F6164 is the
// complete F6020 scroll's new-line assignment; no SDL pixels are observed.
Handle clear(SourceKey);
void scrolled(u32 native_frame,u32 line_height);
// Ordinary writes of the shared original pagination input, including writes
// whose value equals its previous value, retain their native control meaning.
void counter_written();
bool owns_frame(u32 native_frame);
void ui_finished(u32 native_frame);
void finished(u32 native_frame);
// F5B7F and F5C13 are the actual native pagination state transitions.
void waiting(u32 native_frame,u32 wait_frame);
bool owns_wait(u32 wait_frame);
void acknowledged(u32 wait_frame,NativeFrame&);
// Only the currently materialized neutral record can select an existing live
// wait. A frozen cache from before that record cannot restore an old input.
const Waiting* target_wait();
bool frozen_wait(u32 generated_wait_ordinal);
void install_continuation(const Continuation&);
bool complete_resume(u32 native_frame);
void complete_resumed(u32 native_frame);
bool materializing();
const Record& painting_record();
void retain(Handle);
void release(Handle);
Handle snapshot(Handle);
void remove_owner(u64 root);
Status paint(Handle);
std::vector<std::uint8_t> save();
void restore(const void*);
void shutdown();
}
