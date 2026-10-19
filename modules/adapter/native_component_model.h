#pragma once
#include "native_text_resource.h"
#include "native_component_style.h"
#include <variant>

namespace uwcn::adapter::native_component_model {
using native_text_resource::SourceKey;
using native_text_resource::TextSource;
using Handle=u32;
enum class Kind : u32 { panel,legacy_panel,button,paragraph,centered_text,text_block,
    statistic_label,action_button,native_heading_band,native_identity_heading,compound_hint,title_strip,scale_ruler,
    world_map,world_map_marker,world_map_controls,hud_status_cell,hud_status_summary };

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
struct ActionButtonInputs {
    u32 menu,action;ActionLocator locator;u32 row_id;NativeAnchor origin;
    native_component_style::ButtonStyle style;
};
struct NativeHeadingInputs { native_component_style::PanelStyle style; };
// 10E720 consumes the whole before/[KEY]/after string and owns keycap layout.
struct CompoundHintInputs { NativeAnchor origin;u32 color;native_component_style::ButtonStyle style; };
struct TitleStripInputs { NativeAnchor origin;LayoutValue width;u32 mode;native_component_style::PanelStyle style; };
struct ScaleRulerInputs { NativeAnchor origin;LayoutValue line_length; };
// These are original world-data/view inputs of the complete native painters.
// The original map arrays remain their native owners; no map raster is saved.
struct WorldMapInputs { std::int32_t world_x,world_y;u32 step,mode,large_tiles; };
struct WorldMapMarkerInputs { u32 step;std::int32_t selected_x,selected_y,view_x,view_y; };
struct WorldMapControlsInputs { u32 step,color; };
// F8E20 owns the cell-to-native geometry, complete frame, value and native
// cached input record. The original cache index is the widget's identity.
enum class HudStatusValue:u32 { initial,text,bar };
struct HudStatusCellInputs {
    std::int32_t column,row;u32 label_color,native_record,frame_color,shade_color;
    TextSource value;
    HudStatusValue display=HudStatusValue::initial;
    TextSource current_value=native_text_resource::original_text("");
    u32 value_color{};
    std::int32_t amount{},maximum{};
};
// Accepted raw player/status inputs of F9910's original UI constructor/update
// protocol. Operand hooks lend them to native UI reads; game fields stay put.
struct HudStatusSummaryInputs {
    u32 layout,nutrition,hunger,thirst,vigour,warmth_bits,frame_color,shade_color;
    native_component_style::PanelStyle panel;
};
using Inputs=std::variant<PanelInputs,LegacyPanelInputs,ButtonInputs,ParagraphInputs,
    CenteredTextInputs,TextBlockInputs,StatisticLabelInputs,ActionButtonInputs,NativeHeadingInputs,CompoundHintInputs,TitleStripInputs,ScaleRulerInputs,
    WorldMapInputs,WorldMapMarkerInputs,WorldMapControlsInputs,HudStatusCellInputs,HudStatusSummaryInputs>;

// Paragraph fragments are the neutral input records of one native paragraph,
// including its own markup. They are not output lines or text draw operations.
enum class ParagraphOperation:u32 { grammar,count_zero,compose };
// Ordered parser source phases at a fragment boundary. Compose/count reset
// belong to the native word builder; these are inputs, never encoded words.
struct GrammarBoundary {
    // first_fragment names the parser input boundary at which the native
    // caller read its start count. Materialization obtains that count again
    // from the new language's original parser, rather than freezing tokens.
    u32 after_fragments,first_fragment,comma_count;
    ParagraphOperation operation=ParagraphOperation::grammar;
};
struct ParagraphSource { std::vector<TextSource> fragments;std::vector<GrammarBoundary> grammar; };
// Rebuild through the original parser reset/append/English grammar functions.
// Empty input is a real native record, not the reset operation.
void parse_prepared_paragraph(const ParagraphSource&,const std::vector<std::vector<char>>&);
// These two help-record source components explicitly project later file
// records to no native input. A real original empty/control record remains.
bool prepare_paragraph_fragment(const TextSource&,std::vector<char>&);
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
Handle upsert_compound_hint(SourceKey,const CompoundHintInputs&,const TextSource&);
Handle upsert_title_strip(SourceKey,const TitleStripInputs&,const TextSource&);
Handle upsert_scale_ruler(SourceKey,const ScaleRulerInputs&,const TextSource&);
Handle upsert_world_map(SourceKey,const WorldMapInputs&);
Handle upsert_world_map_marker(SourceKey,const WorldMapMarkerInputs&);
Handle upsert_world_map_controls(SourceKey,const WorldMapControlsInputs&);
Handle upsert_hud_status_cell(SourceKey,const HudStatusCellInputs&,const TextSource& label);
Handle update_hud_status_text(SourceKey,const TextSource&,u32 color);
Handle update_hud_status_bar(SourceKey,std::int32_t amount,std::int32_t maximum);
Handle upsert_hud_status_summary(SourceKey,const HudStatusSummaryInputs&);
const HudStatusSummaryInputs* painting_hud_status_summary();
// A native cache snapshots its Menu and passes the matching new owner here.
// The detached component owns one reference, adopted by that cache container.
// It is not installed into the live source map or the active native menu.
Handle snapshot_menu_owner(Handle action_button,u32 snapshot_menu);
u32 menu_owner(Handle);
Handle snapshot(Handle,u32 frozen_menu);
// Upsert returns the source map's borrowed handle. Native Scene/cache owners
// retain their own references and release them at their real retirement.
const Component& get(Handle);
u32 paint_outline(Handle);
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
