#include "native_language_redraw.h"
#include <cstring>

namespace uwcn::adapter::native_language_redraw {
namespace {
std::uintptr_t base{};
State state{};
constexpr u32 native_menu_input_result=0x5100;
constexpr u32 ancestors_input_result=0x5103,ancestors_capacity=0x5104,
    ancestors_index_load=0x5105,ancestors_index_ready=0x5106,native_event_result=0x5107;
}
void initialize(std::uintptr_t image_base) {base=image_base;state={};}
void request() {state.pending=7;}
bool input_return(u32 caller_return_rva) {
    // D1C8E's PollEvent and D1CF8's WaitEvent feed the same D1D69 boundary.
    // Keep this decision with the saved/reloadable native reconstruction state.
    return (state.pending&4u) &&
        (caller_return_rva==0xD1C94 || caller_return_rva==0xD1CFA);
}
void append_hooks(std::vector<HookSpec>& hooks) {
    // This is the common D1120 input protocol, shared by every native Menu.
    hooks.push_back({native_menu_input_result,HookKind::inline_code,0xD12B4,0,0,8,
        {0x8B,0xF8,0x8D,0x85,0xF8,0xFB,0xFF,0xFF}});
    hooks.push_back({ancestors_input_result,HookKind::inline_code,0xDF187,0,0,5,
        {0x8B,0xD0,0x83,0xFA,0xFF}});
    HookSpec capacity{ancestors_capacity,HookKind::inline_code,0xDEB84,0,0,8,
        {0x66,0x0F,0x6E,0x05}};
    const auto font_height=static_cast<u32>(base+0x1E6ABC);
    std::memcpy(capacity.expected+4,&font_height,4);hooks.push_back(capacity);
    hooks.push_back({ancestors_index_load,HookKind::call,0xDEBC3,0xDDA70,0,5,
        {0xE8,0xA8,0xEE,0xFF,0xFF}});
    HookSpec index{ancestors_index_ready,HookKind::inline_code,0xDEBC8,0,0,6,{0x8B,0x15}};
    const auto records=static_cast<u32>(base+0x5F5ACA0);
    std::memcpy(index.expected+2,&records,4);hooks.push_back(index);
    HookSpec event{native_event_result,HookKind::inline_code,0xD1D69,0,0,5,{0xA1}};
    const auto native_event=static_cast<u32>(base+0x5F555F8);
    std::memcpy(event.expected+1,&native_event,4);hooks.push_back(event);
}
bool dispatch(const NativeEvent& event,DispatchResult& result) {
    if(event.id==native_event_result) {
        // D1D01 has cleared the original event type after SDL returned zero.
        // D2083 is D1C00's existing balanced non-key return (-2).
        if((state.pending&4u) && *reinterpret_cast<const u32*>(base+0x5F555F8)==0) {
            state.pending&=~4u;result.resume_rva=0xD2083;
        }
        return true;
    }
    // Confirmed DE990 continuation: rebuild through the original constructors,
    // without reloading its index or changing its live sort/page locals.
    if(event.id==ancestors_input_result) {
        if(state.rebuilding) {
            *reinterpret_cast<u32*>(event.frame->ebp-0x5AC)=
                *reinterpret_cast<const u32*>(base+0x5F54AB0);
            event.frame->esi=static_cast<u32>(-1);result.resume_rva=0xDE9DE;
        }
        return true;
    }
    if(event.id==ancestors_capacity) {
        state.pending&=~2u;
        if(state.rebuilding) {
            event.frame->eax=*reinterpret_cast<const u32*>(event.frame->ebp-0x5A4);
            result.resume_rva=0xDEBB1;
        }
        return true;
    }
    if(event.id==ancestors_index_load) {
        if(state.rebuilding) result.skip_original=1;
        return true;
    }
    if(event.id==ancestors_index_ready) {
        if(state.rebuilding) {state.rebuilding=0;result.resume_rva=0xDEC33;}
        return true;
    }
    if(event.id!=native_menu_input_result) return false;
    if(event.frame->eax==static_cast<u32>(-2)) state.pending&=~4u;
    if((state.pending&2u) && event.frame->eax==static_cast<u32>(-2) &&
        *reinterpret_cast<const u32*>(event.frame->ebp+4)==base+0xDF187) {
        state.rebuilding=1;state.pending&=~2u;result.resume_rva=0xD19B3;
    }
    if(state.pending&1u) {
        // The source rebuild can reindex native link rows while preserving
        // their English action identity. D1120's previous-selection local and
        // its own repaint flag must consume the resulting real selection.
        *reinterpret_cast<u32*>(event.frame->ebp-0x430)=
            *reinterpret_cast<const u32*>(base+0x5F54AB0);
        *reinterpret_cast<u32*>(event.frame->ebp-0x41C)=1;
        state.pending&=~1u;
    }
    return true;
}
State save() {return state;}
void restore(const State& value) {state=value;}
}
