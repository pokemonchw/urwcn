#pragma once
#include "../../sdk/host_abi.h"
#include "../render/render_api.h"
#include <cstring>
#include <string>

namespace uwcn::adapter::native_button {
// Native 114680 keeps its cap/tile blits, highlight markup and flow. Extend
// its complete glyphs for translated plain and <Y>/<N> query button labels.
// Evidence: credits-button-disassembly.txt and 20261110-inventory-all-text.asm.
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

inline std::string visible_text(const char* text,std::size_t bytes) {
    std::string result;
    for(std::size_t i=0;i<bytes;) {
        const auto count=character_bytes(text+i);
        if(text[i]!='<' && text[i]!='>') result.append(text+i,count);
        i+=count;
    }
    return result;
}

template<class Measure>
inline Status width(const NativeEvent& event,DispatchResult& result,Measure measure) {
    render::Metrics measured{};
    const auto* source=label(event);
    const auto visible=visible_text(source,std::strlen(source));
    const auto status=measure(visible.c_str(),measured);
    if(status!=Status::ok) return status;
    // 1146DD: MOV [EBP-98],ESI. The original background repeats an eight-unit
    // tile ESI times and places its right cap from this same native count.
    // 1146EC..114703 subsequently subtracts the two native highlight
    // delimiters. Keep those two pending cells in its own input count.
    const u32 markers=std::strchr(source,'<') && std::strchr(source,'>') ? 2u : 0u;
    event.frame->esi=static_cast<u32>((measured.logical_width+7)/8)+markers;
    *pointer<u32>(event.frame->ebp-0x98)=event.frame->esi;
    result.skip_original=1;
    return Status::ok;
}

inline void center(const NativeEvent& event,std::int32_t center_x) {
    // 1146DD has committed the native eight-unit tile count. The left and
    // right caps each occupy seven units (114740 and 1147FE). 114716 reloads
    // this original x local before any cap, tile or label is drawn.
    const auto tiles=*pointer<std::int32_t>(event.frame->ebp-0x98);
    *pointer<std::int32_t>(event.frame->ebp-0xA0)=center_x-(tiles*8+14)/2;
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
inline Status unmarked_row_width(const NativeEvent& event,DispatchResult& result,Measure measure) {
    const auto* source=pointer<char>(event.frame->edi);
    const auto visible=visible_text(source,std::strlen(source));
    render::Metrics measured{};
    const auto status=measure(visible.c_str(),measured);
    if(status!=Status::ok) return status;
    // CFAF0's two LEAs include the original ten-unit margin. CFC7A..CFC8B
    // subsequently removes sixteen units when native highlight markup exists.
    event.frame->eax=static_cast<u32>(measured.logical_width+10+(std::strchr(source,'<') ? 16 : 0));
    result.skip_original=1;
    return Status::ok;
}

template<class Measure>
inline Status advance(const NativeEvent& event,DispatchResult& result,Measure measure) {
    const auto* source=label(event);
    const auto index=event.frame->ebx;
    const auto next=index+character_bytes(source+index);
    const auto before=visible_text(source,index),through=visible_text(source,next);
    render::Metrics previous{},current{};
    auto status=measure(before.c_str(),previous);
    if(status!=Status::ok) return status;
    status=measure(through.c_str(),current);
    if(status!=Status::ok) return status;
    // 11498A..114990: MOV EDX,[EBP-A4]; INC EBX. Visible glyphs pass the
    // ADD ESI,8 at 114987; 1148CF sends highlight delimiters directly here.
    // Extend each actual branch by its complete visible-prefix width delta.
    // 1AAE20 is "<>"; spaces follow this same advancing/drawing branch.
    // Start the hook at 11498A, the native markup-skip branch target, so
    // unrelated buttons retain their original entry at this instruction.
    const auto original_advance=source[index]=='<' || source[index]=='>' ? 0 : 8;
    event.frame->esi+=static_cast<u32>(current.logical_width-previous.logical_width-original_advance);
    event.frame->edx=*pointer<u32>(event.frame->ebp-0xA4);
    event.frame->ebx=next;
    result.skip_original=1;
    return Status::ok;
}
}
