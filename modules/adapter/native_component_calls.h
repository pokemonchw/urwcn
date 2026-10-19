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
extern "C" void UWCN_CALL uwcn_component_panel(const PanelCall*);
extern "C" void UWCN_CALL uwcn_component_legacy_panel(const LegacyPanelCall*);
extern "C" void UWCN_CALL uwcn_component_button(const ButtonCall*);
extern "C" void UWCN_CALL uwcn_component_centered_text(const CenteredTextCall*);
extern "C" void UWCN_CALL uwcn_component_text_block(const TextBlockCall*);
extern "C" void UWCN_CALL uwcn_component_statistic_label(const StatisticLabelCall*);
extern "C" void UWCN_CALL uwcn_component_action_button(const ActionButtonCall*);
extern "C" void UWCN_CALL uwcn_component_native_heading(const NativeHeadingCall*);
}
