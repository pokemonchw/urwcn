#pragma once
#include "../../sdk/host_abi.h"
#include "../render/render_api.h"
#include <cstring>
#include <string>

namespace uwcn::adapter::native_button {
// These extensions apply inside confirmed translated, unmarked button labels
// (About, Credits and Scenario). Native 114680 keeps its cap/tile blits and flow.
// Evidence: docs/evidence/credits-button-disassembly.txt.
template<class T> inline T* pointer(u32 address) {
    return reinterpret_cast<T*>(static_cast<std::uintptr_t>(address));
}

inline const char* label(const NativeEvent& event) {
    return pointer<char>(*pointer<u32>(event.frame->ebp-0xA4));
}

inline u32 character_bytes(const char* character) {
    // layout.cpp's native transport uses one ASCII byte or one two-byte token.
    return static_cast<unsigned char>(*character)<0x80 ? 1u : 2u;
}

template<class Measure>
inline Status width(const NativeEvent& event,DispatchResult& result,Measure measure) {
    render::Metrics measured{};
    const auto status=measure(label(event),measured);
    if(status!=Status::ok) return status;
    // 1146DD: MOV [EBP-98],ESI. The original background repeats an eight-unit
    // tile ESI times and places its right cap from this same native count.
    event.frame->esi=static_cast<u32>((measured.logical_width+7)/8);
    *pointer<u32>(event.frame->ebp-0x98)=event.frame->esi;
    result.skip_original=1;
    return Status::ok;
}

inline Status character(const NativeEvent& event) {
    // AFTER 1148E9's sprintf("%c"): retain its native local destination, but
    // replace the single transport byte with the complete encoded character.
    const auto* source=label(event)+event.frame->ebx;
    const auto bytes=character_bytes(source);
    auto* destination=pointer<char>(event.arguments[0]);
    std::memcpy(destination,source,bytes);
    destination[bytes]='\0';
    event.frame->eax=bytes;
    return Status::ok;
}

template<class Measure>
inline Status advance(const NativeEvent& event,DispatchResult& result,Measure measure) {
    const auto* source=label(event);
    const auto index=event.frame->ebx;
    const auto next=index+character_bytes(source+index);
    const std::string before(source,index),through(source,next);
    render::Metrics previous{},current{};
    auto status=measure(before.c_str(),previous);
    if(status!=Status::ok) return status;
    status=measure(through.c_str(),current);
    if(status!=Status::ok) return status;
    // 11498A..114990: MOV EDX,[EBP-A4]; INC EBX. The translated unmarked
    // label has already passed ADD ESI,8 at 114987. Replace that advance with
    // the complete-prefix width difference, including density rounding.
    // 1AAE20 is "<>"; spaces follow this same advancing/drawing branch.
    // Start the hook at 11498A, the native markup-skip branch target, so
    // unrelated buttons retain their original entry at this instruction.
    event.frame->esi+=static_cast<u32>(current.logical_width-previous.logical_width-8);
    event.frame->edx=*pointer<u32>(event.frame->ebp-0xA4);
    event.frame->ebx=next;
    result.skip_original=1;
    return Status::ok;
}
}
