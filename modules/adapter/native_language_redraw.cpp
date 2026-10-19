#include "native_language_redraw.h"
#include <algorithm>
#include <cstring>
#include <initializer_list>

namespace uwcn::adapter::native_language_redraw {
namespace {
std::uintptr_t base{};
State state{};
constexpr u32 setup=1,ancestors=2;
enum Hook : u32 {
    setup_input_result=0x5100,
    setup_rebuild_begin,
    setup_initialization,
    ancestors_rebuild_begin,
    ancestors_initialization,
    ancestors_index_load,
    ancestors_index_loaded
};

HookSpec inline_hook(u32 id,u32 site,std::initializer_list<std::uint8_t> bytes) {
    HookSpec spec{id,HookKind::inline_code,site,0,0,static_cast<u32>(bytes.size()),{}};
    std::copy(bytes.begin(),bytes.end(),spec.expected);
    return spec;
}
}

void initialize(std::uintptr_t image_base) {
    base=image_base;
    state={};
}
void request() { state.pending|=setup|ancestors; }
void request_ancestors() { state.pending|=ancestors; }

void append_hooks(std::vector<HookSpec>& hooks) {
    // D12B4 follows D1120's native D3BF0 input call. Unlike D12AA's relative
    // CALL, these two complete instructions are position-independent replay.
    hooks.push_back(inline_hook(setup_input_result,0xD12B4,
        {0x8B,0xF8,0x8D,0x85,0xF8,0xFB,0xFF,0xFF}));
    hooks.push_back(inline_hook(setup_rebuild_begin,0x106B25,
        {0x8B,0xF0,0x83,0xFE,0x64}));
    hooks.push_back(inline_hook(setup_initialization,0x1057E2,
        {0xC6,0x45,0x8A,0x00,0x33,0xF6}));
    // DF182's CALL stays native: D1120 can identify this original return.
    hooks.push_back(inline_hook(ancestors_rebuild_begin,0xDF187,
        {0x8B,0xD0,0x83,0xFA,0xFF}));
    auto initial=inline_hook(ancestors_initialization,0xDEB84,
        {0x66,0x0F,0x6E,0x05,0,0,0,0});
    const u32 font_height=static_cast<u32>(base+0x1E6ABC);
    std::memcpy(initial.expected+4,&font_height,4);
    hooks.push_back(initial);
    hooks.push_back({ancestors_index_load,HookKind::call,0xDEBC3,0xDDA70,0,5,
        {0xE8,0xA8,0xEE,0xFF,0xFF}});
    auto loaded=inline_hook(ancestors_index_loaded,0xDEBC8,
        {0x8B,0x15,0,0,0,0});
    const u32 latest_ancestor=static_cast<u32>(base+0x5F5ACA0);
    std::memcpy(loaded.expected+2,&latest_ancestor,4);
    hooks.push_back(loaded);
}

bool menu_input_tick(const NativeEvent& event) {
    return event.id==setup_input_result && event.phase==NativePhase::inline_before;
}
bool menu_input(const NativeEvent& event,u32 caller_return_rva) {
    // These D1120 calls stay unhooked: EBP+4 identifies the actual menu caller.
    // Reuse the existing post-input hook without changing its returned action.
    return menu_input_tick(event)
        && *reinterpret_cast<const u32*>(event.frame->ebp+4)==base+caller_return_rva;
}

bool dispatch(const NativeEvent& event,DispatchResult& result) {
    switch(event.id) {
    case setup_input_result:
        // 106B20 itself remains unhooked, so D1120's own EBP+4 still contains
        // this exact original caller return. No enclosing frame is retained.
        if((state.pending&setup) && event.frame->eax==static_cast<u32>(-2)
            && *reinterpret_cast<const u32*>(event.frame->ebp+4)==base+0x106B25) {
            state.pending&=~setup;
            state.rebuilding|=setup;
            // Native -1 exit clears menu_input_active and balances D1120.
            // D19A9 is deliberately not used: it also changes input mode.
            result.resume_rva=0xD19B3;
        }
        if((state.pending&ancestors) && event.frame->eax==static_cast<u32>(-2)
            && *reinterpret_cast<const u32*>(event.frame->ebp+4)==base+0xDF187) {
            state.pending&=~ancestors;
            state.rebuilding|=ancestors;
            result.resume_rva=0xD19B3;
        }
        return true;
    case setup_rebuild_begin:
        if(state.rebuilding&setup) {
            // D1120 may have changed the current native selection since this
            // setup frame last drew. Preserve that real index, not EAX=-1.
            event.frame->esi=*reinterpret_cast<const u32*>(base+0x5F54AB0);
            result.resume_rva=0x105716;
        }
        return true;
    case setup_initialization:
        if(state.rebuilding&setup) {
            state.rebuilding&=~setup;
            // Keep the original setup locals and selection; skip only its
            // initial resets, configuration reread and audio fade. Native
            // footer construction, named-cache replacement and body follow.
            result.resume_rva=0x10580D;
        } else {
            // A newly entered setup page already draws the selected language.
            // A request made on another page does not schedule a second draw.
            state.pending&=~setup;
        }
        return true;
    case ancestors_rebuild_begin:
        if(state.rebuilding&ancestors) {
            // This is the native ancestor frame. Its existing restoration
            // local is also used when returning from a memorial page.
            *reinterpret_cast<u32*>(event.frame->ebp-0x5AC)=
                *reinterpret_cast<const u32*>(base+0x5F54AB0);
            // The title and DEA21 list/death branch consume original ECX=-1
            // through ESI. DEC33 later restores ESI to native SDL_MapRGB.
            event.frame->esi=static_cast<u32>(-1);
            result.resume_rva=0xDE9DE;
        }
        return true;
    case ancestors_initialization:
        if(state.rebuilding&ancestors) {
            // Preserve native capacity, row spacing, page offset and both
            // order arrays. DEBB1..DEBBE replaces the game's named background
            // cache after its own background, title and footer were redrawn.
            event.frame->eax=*reinterpret_cast<const u32*>(event.frame->ebp-0x5A4);
            result.resume_rva=0xDEBB1;
        } else {
            state.pending&=~ancestors;
        }
        return true;
    case ancestors_index_load:
        if(event.phase==NativePhase::before && (state.rebuilding&ancestors))
            result.skip_original=1;
        return true;
    case ancestors_index_loaded:
        if(state.rebuilding&ancestors) {
            state.rebuilding&=~ancestors;
            // Skip only first-entry record enumeration/order initialization.
            // The original DEC33 loop redraws rows, controls and page count;
            // DF169 then restores the selection from the native local above.
            result.resume_rva=0xDEC33;
        }
        return true;
    default:
        return false;
    }
}

State save() { return state; }
void restore(const State& saved) { state=saved; }
}
