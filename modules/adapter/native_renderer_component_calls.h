#pragma once
#include "../../sdk/host_abi.h"
#include <cstdint>

namespace uwcn::adapter::native_renderer_component_calls {
// Complete native component entry points. These functions use register
// arguments and caller-cleaned stack arguments, rather than C++ fastcall.
struct ParagraphCall {
    u32 function,renderer;
    std::int32_t x,y,width,height;
    u32 color,style;
};
struct PanelCall {
    u32 function,renderer;
    std::int32_t x,y,width,height;
    const char* title;
    u32 flags,color;
};
struct TextBlockCall {
    u32 function,renderer;
    std::int32_t x,y;
    const char* text;
    u32 color,style;
};
// 111560 owns its fill, four shaded borders and its nested 10E260 text.
// ECX=renderer, EDX=x; y,width,text,color are caller-cleaned stack inputs.
struct LabelBoxCall {
    u32 function,renderer;
    std::int32_t x,y,width;
    const char* text;
    u32 color;
};
// 113430 has no stack arguments: ECX is the native target texture and EDX
// is its heading. Its own native body selects A2110CC and paints the title.
struct HeadingCall { u32 function,texture;const char* title; };
struct MarkedButtonCall {
    u32 function,texture,action;
    std::int32_t x,y;
    const char* text;
};
extern "C" void UWCN_CALL uwcn_renderer_paragraph(const ParagraphCall*);
extern "C" void UWCN_CALL uwcn_renderer_panel(const PanelCall*);
extern "C" void UWCN_CALL uwcn_renderer_text_block(const TextBlockCall*);
extern "C" void UWCN_CALL uwcn_renderer_label_box(const LabelBoxCall*);
extern "C" void UWCN_CALL uwcn_renderer_heading(const HeadingCall*);
extern "C" void UWCN_CALL uwcn_renderer_marked_button(const MarkedButtonCall*);
}
