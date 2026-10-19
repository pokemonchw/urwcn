#pragma once
#include "../../sdk/host_abi.h"

namespace uwcn::adapter {
// 10EB40 uses ECX/EDX plus four caller-cleaned stack arguments.
struct NativeParagraphCall {
    u32 target;
    std::int32_t x,y,width,height;
    u32 color,outline;
};
extern "C" void UWCN_CALL uwcn_draw_native_paragraph(const NativeParagraphCall*);
}
