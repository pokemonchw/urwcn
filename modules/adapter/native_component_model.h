#pragma once
#include "native_text_resource.h"
#include "native_component_style.h"
#include <variant>

namespace uwcn::adapter::native_component_model {
using native_text_resource::SourceKey;
using native_text_resource::TextSource;
using Handle=u32;
enum class Kind : u32 { panel,legacy_panel,button,paragraph,centered_text,text_block,
    statistic_label,action_button,native_heading_band,native_identity_heading };

enum class LayoutSource : u32 {
    native_input,native_i32,center_input,center_native_i32,right_input,right_native_i32
};
struct LayoutValue {
    LayoutSource source;
    std::int32_t input;
    u32 rva;
};
inline LayoutValue native_input(std::int32_t value) { return {LayoutSource::native_input,value,0}; }
inline LayoutValue native_i32(u32 rva) { return {LayoutSource::native_i32,0,rva}; }
// The producer supplies the center/right operand before the original native
// width subtraction. These expressions use the same current native metrics.
inline LayoutValue native_center(std::int32_t center) { return {LayoutSource::center_input,center,0}; }
inline LayoutValue native_center_i32(u32 rva) { return {LayoutSource::center_native_i32,0,rva}; }
inline LayoutValue native_right(std::int32_t right) { return {LayoutSource::right_input,right,0}; }
inline LayoutValue native_right_i32(u32 rva) { return {LayoutSource::right_native_i32,0,rva}; }
// A producer binds the original component anchor or a confirmed native layout
// dependency. A final 10E5A0 x computed from an old text width is not an anchor.
struct NativeAnchor { LayoutValue x,y; };
struct PanelInputs {
    NativeAnchor origin;LayoutValue width,height;u32 flags,color;
    native_component_style::PanelStyle style;
};
struct LegacyPanelInputs {
    NativeAnchor origin;LayoutValue width,height;u32 flags;
    native_component_style::PanelStyle style;
};
struct ButtonInputs {
    NativeAnchor origin;u32 outline;
    native_component_style::ButtonStyle style;
};
struct ParagraphInputs { NativeAnchor origin;LayoutValue width,height;u32 color,outline; };
struct CenteredTextInputs { NativeAnchor origin;LayoutValue width;u32 color,outline; };
struct TextBlockInputs { NativeAnchor anchor;u32 color,outline; };
// E10F0 owns its own fixed label/bar origins. Only y and the actual native
// statistic value are caller inputs; the complete native function draws both.
struct StatisticLabelInputs { LayoutValue y;std::int32_t value; };
// CFAF0's action identifies one row in this actual native Menu instance. Its
// original constructor remains responsible for all row geometry and hit data.
enum class ActionLocator:u32 { action,native_row };
struct ActionButtonInputs { u32 menu,action;ActionLocator locator;u32 row_id;NativeAnchor origin; };
struct NativeHeadingInputs { native_component_style::PanelStyle style; };
using Inputs=std::variant<PanelInputs,LegacyPanelInputs,ButtonInputs,ParagraphInputs,
    CenteredTextInputs,TextBlockInputs,StatisticLabelInputs,ActionButtonInputs,NativeHeadingInputs>;

// Paragraph fragments are the neutral input records of one native paragraph,
// including its own markup. They are not output lines or text draw operations.
struct GrammarBoundary { u32 after_fragments,first_word,comma_count; };
struct ParagraphSource { std::vector<TextSource> fragments;std::vector<GrammarBoundary> grammar; };
// Rebuild through the original parser reset/append/English grammar functions.
// Empty input is a real native record, not the reset operation.
void parse_prepared_paragraph(const ParagraphSource&,const std::vector<std::vector<char>>&);
struct Component {
    SourceKey source;
    Kind kind;
    Inputs inputs;
    TextSource text;
    ParagraphSource paragraph;
};
struct SourceBinding { u64 token;SourceKey source;TextSource text; };
void push_source(u64 token,SourceKey,const TextSource&);
void pop_source(u64 token);
const SourceBinding& source();

void initialize(std::uintptr_t image_base);
Handle upsert_panel(SourceKey,const PanelInputs&,const TextSource&);
Handle upsert_legacy_panel(SourceKey,const LegacyPanelInputs&,const TextSource&);
Handle upsert_button(SourceKey,const ButtonInputs&,const TextSource&);
Handle upsert_paragraph(SourceKey,const ParagraphInputs&,const ParagraphSource&);
Handle upsert_centered_text(SourceKey,const CenteredTextInputs&,const TextSource&);
Handle upsert_text_block(SourceKey,const TextBlockInputs&,const TextSource&);
Handle upsert_statistic_label(SourceKey,const StatisticLabelInputs&,const TextSource&);
Handle upsert_action_button(SourceKey,const ActionButtonInputs&,const TextSource&);
Handle upsert_native_heading(SourceKey,bool identity,const NativeHeadingInputs&,const TextSource&);
// A native cache snapshots its Menu and passes the matching new owner here.
// The detached component owns one reference, adopted by that cache container.
// It is not installed into the live source map or the active native menu.
Handle snapshot_menu_owner(Handle action_button,u32 snapshot_menu);
u32 menu_owner(Handle);
Handle snapshot(Handle,u32 frozen_menu);
// Upsert returns the source map's borrowed handle. Native Scene/cache owners
// retain their own references and release them at their real retirement.
const Component& get(Handle);
// Producer-only lookup of an already constructed canonical native source.
Handle current(SourceKey);
void retain(Handle);
void release(Handle);
void remove(Handle);
void remove_owner(u64 owner);

// Services are synchronous borrowed interfaces. No callback/code address is
// stored in an object or serialized across module replacement.
struct PaintServices {
    native_text_resource::Resolve resolve;
    Status (*encode_original)(const char*,std::vector<char>&);
    Status (*paragraph_words)(std::vector<char>&);
    Status (*measure)(const char*,std::int32_t& width);
    void (*enter)(Handle,Kind,u32 outline);
    void (*leave)(Handle,Kind);
};
struct PreparedText { std::vector<std::vector<char>> fragments; };
Status prepare(Handle,const PaintServices&,PreparedText&);
Status paint(Handle,const PaintServices&);
std::vector<std::uint8_t> save();
// Reference counts include the current-source map and native scene/cache
// owners. Their restored handle fields do not acquire those references twice.
void restore(const void* payload);
}
