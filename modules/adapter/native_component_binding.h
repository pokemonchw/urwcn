#pragma once
#include "native_component_model.h"
#include <string>
#include <vector>

namespace uwcn::adapter::native_component_binding {
using native_text_resource::TextSource;
using native_component_model::ParagraphSource;
using DecodeParserSource=Status (*)(const char*,std::string&);
using EncodeParserSource=Status (*)(const char*,std::vector<char>&);

void configure(std::uintptr_t image_base,const native_component_model::PaintServices&);
// This decoder consumes the original game's byte encoding. Semantic producer
// bindings supply their owned neutral source before any translated native call.
void set_parser_source_decoder(DecodeParserSource);
void set_parser_source_encoder(EncodeParserSource);
void register_hooks(std::vector<HookSpec>&);

// Each dispatch is synchronous. No NativeEvent, frame, argument pointer or
// borrowed display buffer survives finish_event. Ordinary CALL display buffers
// remain owned only until that same CALL's After notification.
void begin_event(const NativeEvent&);
void note_source(const TextRequest&);
void bind_source(const NativeEvent&,const TextSource&);
void note_source_for_consumer(const NativeEvent&,TextComponent);
void note_original_for_consumer(const NativeEvent&,const char* original);
void note_prefix(const NativeEvent&,const char* original_utf8_prefix);
void note_suffix(const NativeEvent&,const char* original_utf8_suffix);
void note_center(const NativeEvent&,std::int32_t original_native_center_operand);
// Repeated native records need an explicit identity from their producer. The
// ordinary fixed-field contract otherwise uses its semantic CALL site RVA.
void note_native_record(const NativeEvent&,u32 original_native_record);
void note_native_field(const NativeEvent&,u32 actual_native_field);
const TextSource* current_source();
const TextSource& field_source(TextComponent);
const TextSource* current_event_source();
const ParagraphSource& current_paragraph_source();
bool current_event_center(std::int32_t&);
bool current_event_record(u32&);
bool consuming_component();
bool parser_owned();
void begin_source_resolution();
void end_source_resolution();
Status finish_event(const NativeEvent&,DispatchResult&,Status native_dispatch_status=Status::ok);

// A translated producer that calls 162300 itself binds its neutral input for
// exactly that complete native invocation. These contexts are transient, not
// component identities or persisted native pointers.
void bind_parser_source(u64 token,const TextSource&);
void unbind_parser_source(u64 token);
// A complete native component such as the NFO reader owns its parser scratch
// inputs while this synchronous scope is active. They are not separate global
// paragraph resources and are materialized by that component's own model.
void begin_parser_owner();
void end_parser_owner();
bool has_paragraph_builder();
void clear_paragraph_builder();
Status restore_paragraph_builder();
Status replace_paragraph_builder(const ParagraphSource&);
// Borrow a paragraph as native parser input without replacing the canonical
// current builder or its original count/composition source operations.
Status consume_paragraph_source(const ParagraphSource&);

// Root text fields and the native parser's current source are pure resources.
// They contain no encoded word table, output lines, UI pixels or draw history.
void retire_root(u64 owner);
std::vector<std::uint8_t> save();
void restore(const void* payload);
void shutdown();
}
