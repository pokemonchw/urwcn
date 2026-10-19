#include "native_language_input.h"
#include <cstring>

namespace uwcn::adapter::native_language_input {
namespace {
constexpr u32 normal_input=0x5000,animation_input=0x5001;
constexpr u32 native_event_rva=0x5F555F8;
constexpr u32 key_down=0x300,key_up=0x301,window_event=0x200;
constexpr u32 f10_key=0x40000043;
constexpr unsigned short shift_mod=0x0003,other_mod=0x0FC0;
State state;

template<class T> T read(const unsigned char* event,u32 offset) {
    T value;
    std::memcpy(&value,event+offset,sizeof(value));
    return value;
}
struct Action { bool consume; bool toggle; };
Action key(const unsigned char* event) {
    const auto type=read<u32>(event,0);
    if(type==window_event) {
        // SDL_WINDOWEVENT_FOCUS_LOST; the original event still reaches URW.
        if(event[12]==13) state.f10_consumed=0;
        return {};
    }
    if(type!=key_down && type!=key_up) return {};
    if(read<u32>(event,20)!=f10_key) return {};
    if(type==key_up) {
        const bool consumed=state.f10_consumed!=0;
        state.f10_consumed=0;
        return {consumed,false};
    }
    // Once the chord owns this press, releasing Shift first must not leak its
    // remaining F10 repeats into the game's command or animation-skip path.
    // URW's documented drain/FlushEvents paths can discard KEYUP. SDL repeat=0
    // identifies the next physical press independently of that discarded event.
    const bool repeat=event[13]!=0;
    if(!repeat) state.f10_consumed=0;
    else if(state.f10_consumed) return {true,false};
    const auto modifiers=read<unsigned short>(event,24);
    if(!(modifiers&shift_mod) || (modifiers&other_mod)) return {};
    state.f10_consumed=1;
    return {true,!repeat};
}
}

void append_hooks(std::uintptr_t image_base,std::vector<HookSpec>& hooks) {
    // Both ordinary Poll/Wait results reach D1CD4 before native key handling.
    HookSpec normal{normal_input,HookKind::inline_code,0xD1CD4,0,0,10,
        {0x81,0x3D,0,0,0,0,0x00,0x03,0x00,0x00}};
    // The animation's D25E0 poll reaches D26AB only after a real event.
    HookSpec animation{animation_input,HookKind::inline_code,0xD26AB,0,0,5,
        {0xA1,0,0,0,0}};
    const u32 event_address=static_cast<u32>(image_base+native_event_rva);
    std::memcpy(normal.expected+2,&event_address,4);
    std::memcpy(animation.expected+1,&event_address,4);
    hooks.push_back(normal);
    hooks.push_back(animation);
}

Result dispatch(const NativeEvent& event,DispatchResult& result,std::uintptr_t image_base) {
    if(event.id!=normal_input && event.id!=animation_input)
        return {false,false};
    const auto* input=reinterpret_cast<const unsigned char*>(image_base+native_event_rva);
    const auto action=key(input);
    if(action.consume) {
        // Native wake/zero-return continuations preserve stack,
        // original event buffers and all unrelated game input semantics.
        // D2083 returns the existing non-key wake result (-2). D3BF0 returns
        // it directly without reading the unused keysym output; native outer
        // loops can then rebuild their own active components on the next tick.
        result.resume_rva=event.id==normal_input ? 0xD2083 : 0xD269B;
    }
    return {true,action.toggle};
}
State save() { return state; }
void restore(State value) { state=value; }
}
