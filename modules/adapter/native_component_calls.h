#pragma once
#include "../../sdk/host_abi.h"
#include <cstdint>

namespace uwcn::adapter::native_component_calls {
// These are the complete, confirmed x86 native function ABIs. All origins and
// extents are native component inputs, before that component lays out text.
struct PanelCall {
    u32 target;
    std::int32_t x,y,width,height;
    const char* title;
    u32 flags,color;
};
struct LegacyPanelCall {
    u32 target;
    std::int32_t x,y,width,height;
    const char* title;
    u32 flags;
};
struct ButtonCall { u32 target;std::int32_t x,y;const char* label; };
struct CenteredTextCall {
    u32 target;
    std::int32_t x,y,width;
    const char* text;
    u32 color,outline;
};
struct TextBlockCall {
    u32 target;
    std::int32_t x,y;
    const char* text;
    u32 color,outline;
};
struct StatisticLabelCall {
    u32 target;std::int32_t y;const char* label;std::int32_t value;
};
struct ActionButtonCall {
    u32 target,action;std::int32_t x,y;const char* label;
};
struct NativeHeadingCall { u32 target;const char* text; };
struct CompoundHintCall { u32 target;std::int32_t x,y;const char* text;u32 color; };
struct TitleStripCall { u32 target;std::int32_t x,y,width;const char* text;u32 mode; };
struct SelectorRendererCall { u32 target,selection; };
struct ScaleRulerCall { u32 target;std::int32_t x,y,line_length;const char* text; };
struct WorldMapCall { u32 target;std::int32_t world_x,world_y;u32 step,mode; };
struct WorldMapMarkerCall { u32 target,step; };
struct NoArgumentCall { u32 target; };
struct HudStatusCellCall {
    u32 target;std::int32_t column,row;const char* label;const char* value;
    u32 label_color,native_record;
};
struct HudStatusBarCall {u32 target;std::int32_t x,y,amount,maximum;};
extern "C" void UWCN_CALL uwcn_component_panel(const PanelCall*);
extern "C" void UWCN_CALL uwcn_component_legacy_panel(const LegacyPanelCall*);
extern "C" void UWCN_CALL uwcn_component_button(const ButtonCall*);
extern "C" void UWCN_CALL uwcn_component_centered_text(const CenteredTextCall*);
extern "C" void UWCN_CALL uwcn_component_text_block(const TextBlockCall*);
extern "C" void UWCN_CALL uwcn_component_statistic_label(const StatisticLabelCall*);
extern "C" void UWCN_CALL uwcn_component_action_button(const ActionButtonCall*);
extern "C" void UWCN_CALL uwcn_component_native_heading(const NativeHeadingCall*);
extern "C" void UWCN_CALL uwcn_component_compound_hint(const CompoundHintCall*);
extern "C" void UWCN_CALL uwcn_component_title_strip(const TitleStripCall*);
extern "C" void UWCN_CALL uwcn_component_selector_renderer(const SelectorRendererCall*);
extern "C" void UWCN_CALL uwcn_component_scale_ruler(const ScaleRulerCall*);
extern "C" void UWCN_CALL uwcn_component_world_map(const WorldMapCall*);
extern "C" void UWCN_CALL uwcn_component_world_map_marker(const WorldMapMarkerCall*);
extern "C" void UWCN_CALL uwcn_component_no_argument(const NoArgumentCall*);
extern "C" void UWCN_CALL uwcn_component_hud_status_cell(const HudStatusCellCall*);
extern "C" void UWCN_CALL uwcn_component_hud_status_bar(const HudStatusBarCall*);
}
