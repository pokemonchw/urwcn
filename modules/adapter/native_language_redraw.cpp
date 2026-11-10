#include "native_language_redraw.h"
#include <cstring>

namespace uwcn::adapter::native_language_redraw {
namespace {
std::uintptr_t base{};
const HostApi* host{};
MenuRebuild rebuild_menu{};
State state{};
constexpr u32 native_menu_input_result=0x5100;
constexpr u32 setup_input_result=0x5101,setup_initialization=0x5102;
constexpr u32 ancestors_input_result=0x5103,ancestors_capacity=0x5104,
    ancestors_index_load=0x5105,ancestors_index_ready=0x5106,native_event_result=0x5107;
constexpr u32 profile_return=0x5108,profile_display_ready=0x5109,profile_selection=0x510A;
constexpr u32 culture_input_result=0x510B,culture_frame_upload=0x510C,culture_menu_ready=0x510D;
constexpr u32 menu_selection_pending=1,ancestors_pending=2,input_exit_pending=4,setup_pending=8,profile_pending=16;
constexpr u32 culture_pending=32,main_menu_pending=64;
constexpr u32 ancestors_rebuilding=1,setup_rebuilding=2,profile_rebuilding=3,culture_rebuilding=4;
constexpr u32 phase_mask=0xFF,selection_shift=8;
bool rebuilding_profile() {return (state.rebuilding&phase_mask)==profile_rebuilding;}
}
void initialize(const HostApi* api,MenuRebuild menu) {host=api;base=api->image_base;rebuild_menu=menu;state={};}
void request(bool main_menu) {
    state.pending=menu_selection_pending|ancestors_pending|input_exit_pending|setup_pending|profile_pending|culture_pending;
    for(const auto view:{View::about,View::credits,View::creation,View::scenario_selection,
            View::scenario_confirmation,View::game_course,View::world,View::skills,
            View::spells,View::encyclopedia,View::profile,View::load,View::story,
            View::creation_complete,View::farewell,View::startup,View::intro,
            View::hud,View::map,View::messages,View::keyboard_help})
        state.pending|=1u<<static_cast<u32>(view);
    if(main_menu) state.pending|=main_menu_pending;
}
bool pending(View view) {return (state.pending&(1u<<static_cast<u32>(view)))!=0;}
void completed(View view) {state.pending&=~((1u<<static_cast<u32>(view))|input_exit_pending);}
bool input_return(u32 caller_return_rva) {
    // D1C8E's PollEvent and D1CF8's WaitEvent feed the same D1D69 boundary.
    // Keep this decision with the saved/reloadable native reconstruction state.
    return (state.pending&input_exit_pending) &&
        (caller_return_rva==0xD1C94 || caller_return_rva==0xD1CFA);
}
void append_hooks(std::vector<HookSpec>& hooks) {
    // This is the common D1120 input protocol, shared by every native Menu.
    hooks.push_back({native_menu_input_result,HookKind::inline_code,0xD12B4,0,0,8,
        {0x8B,0xF8,0x8D,0x85,0xF8,0xFB,0xFF,0xFF}});
    // 106B20 remains the native CALL, preserving D1120's real return address.
    hooks.push_back({setup_input_result,HookKind::inline_code,0x106B25,0,0,5,
        {0x8B,0xF0,0x83,0xFE,0x64}});
    hooks.push_back({setup_initialization,HookKind::inline_code,0x1057E2,0,0,6,
        {0xC6,0x45,0x8A,0x00,0x33,0xF6}});
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
    // The negative Menu result reaches this cookie load before any POP. Its
    // stack is the same balanced drawing frame as E66CD; no branch is replayed.
    hooks.push_back({profile_return,HookKind::inline_code,0xE6D03,0,0,7,
        {0x8B,0x8C,0x24,0x7C,0x04,0x00,0x00}});
    HookSpec display{profile_display_ready,HookKind::inline_code,0xE6ADA,0,0,10,
        {0xC7,0x05,0,0,0,0,0,0,0,0}};
    const auto disable_flip=static_cast<u32>(base+0x61BBA5C);
    std::memcpy(display.expected+2,&disable_flip,4);hooks.push_back(display);
    HookSpec selection{profile_selection,HookKind::inline_code,0xE6CA6,0,0,5,{0xA1}};
    const auto reroll_position=static_cast<u32>(base+0x217A70);
    std::memcpy(selection.expected+1,&reroll_position,4);hooks.push_back(selection);
    hooks.push_back({culture_input_result,HookKind::inline_code,0xF8D4,0,0,5,
        {0x8B,0xD8,0x83,0xFB,0x64}});
    HookSpec culture{culture_menu_ready,HookKind::inline_code,0xF67D,0,0,5,{0xA1}};
    const auto current_selection=static_cast<u32>(base+0x5F54AB0);
    std::memcpy(culture.expected+1,&current_selection,4);hooks.push_back(culture);
    // A balanced original heading fragment ends at this resident CALL return.
    // Its only presentation is skipped during the culture reconstruction;
    // the new native Menu input presents the complete page afterwards.
    hooks.push_back({culture_frame_upload,HookKind::call,0x12F29,0x10AF90,0,5,
        {0xE8,0x62,0x80,0x0F,0x00}});
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=true;
    if(event.id==culture_menu_ready) {
        state.pending&=~culture_pending;
        return Status::ok;
    }
    if(event.id==culture_frame_upload) {
        if(state.rebuilding==culture_rebuilding) result.skip_original=1;
        return Status::ok;
    }
    if(event.id==culture_input_result) {
        if(state.rebuilding==culture_rebuilding) {
            // 12EEC..12F2E constructs the original enclosing heading panel.
            // All five native arguments are balanced before its final call.
            const auto status=host->native_fragment(0x12EEC,0x12F2E);
            state.rebuilding=0;
            if(status!=Status::ok) return status;
            // F675 restores the page's own EBX local, then CFFB0 and 3CA90
            // rebuild the culture Menu and complete preview, including its
            // background. D1120 then saves and presents the native pixels.
            result.resume_rva=0xF675;
        }
        return Status::ok;
    }
    if(event.phase==NativePhase::after) {handled=false;return Status::ok;}
    if(event.id==profile_return) {
        if(rebuilding_profile()) {
            // E66CD pushes the original mode as part of the background call.
            // Keep this existing frame, its cookie and saved registers intact.
            event.frame->ecx=event.frame->edi;result.resume_rva=0xE66CD;
        }
        return Status::ok;
    }
    if(event.id==profile_display_ready) {
        if(rebuilding_profile()) {
            *reinterpret_cast<u32*>(base+0x61BBA5C)=0;
            // The new native Menu input presents the complete page. Skip the
            // initial partial upload, fade-state changes and cursor operation.
            result.resume_rva=0xE6B26;
        }
        return Status::ok;
    }
    if(event.id==profile_selection) {
        state.pending&=~profile_pending;
        if(rebuilding_profile()) {
            event.frame->eax=state.rebuilding>>selection_shift;
            state.rebuilding=0;result.skip_original=1;
            // E6CAB stores this selection; REROLL_POS remains untouched.
        }
        return Status::ok;
    }
    if(event.id==native_event_result) {
        // D1D01 has cleared the original event type after SDL returned zero.
        // D2083 is D1C00's existing balanced non-key return (-2).
        if((state.pending&input_exit_pending) && *reinterpret_cast<const u32*>(base+0x5F555F8)==0) {
            state.pending&=~input_exit_pending;result.resume_rva=0xD2083;
        }
        return Status::ok;
    }
    if(event.id==setup_input_result) {
        if(state.rebuilding==setup_rebuilding) {
            // The existing setup frame carries the option state. ESI is the
            // real selection, later restored by the original 106B0E store.
            event.frame->esi=*reinterpret_cast<const u32*>(base+0x5F54AB0);
            result.resume_rva=0x105716;
        }
        return Status::ok;
    }
    if(event.id==setup_initialization) {
        state.pending&=~setup_pending;
        if(state.rebuilding==setup_rebuilding) {
            state.rebuilding=0;
            // Skip initial local/selection resets, config reload and audio
            // fade. Native footer, cwd, setupscr and body constructors follow.
            result.resume_rva=0x10580D;
        }
        return Status::ok;
    }
    // Confirmed DE990 continuation: rebuild through the original constructors,
    // without reloading its index or changing its live sort/page locals.
    if(event.id==ancestors_input_result) {
        if(state.rebuilding==ancestors_rebuilding) {
            *reinterpret_cast<u32*>(event.frame->ebp-0x5AC)=
                *reinterpret_cast<const u32*>(base+0x5F54AB0);
            event.frame->esi=static_cast<u32>(-1);result.resume_rva=0xDE9DE;
        }
        return Status::ok;
    }
    if(event.id==ancestors_capacity) {
        state.pending&=~ancestors_pending;
        if(state.rebuilding==ancestors_rebuilding) {
            event.frame->eax=*reinterpret_cast<const u32*>(event.frame->ebp-0x5A4);
            result.resume_rva=0xDEBB1;
        }
        return Status::ok;
    }
    if(event.id==ancestors_index_load) {
        if(state.rebuilding==ancestors_rebuilding) result.skip_original=1;
        return Status::ok;
    }
    if(event.id==ancestors_index_ready) {
        if(state.rebuilding==ancestors_rebuilding) {state.rebuilding=0;result.resume_rva=0xDEC33;}
        return Status::ok;
    }
    if(event.id!=native_menu_input_result) {handled=false;return Status::ok;}
    if(event.frame->eax==static_cast<u32>(-2)) state.pending&=~input_exit_pending;
    if(event.frame->eax==static_cast<u32>(-2)) {
        auto selection=*reinterpret_cast<const u32*>(base+0x5F54AB0);
        bool rebuilt{};
        const auto status=rebuild_menu(event,rebuilt,selection);
        if(status!=Status::ok) return status;
        if(rebuilt) {
            *reinterpret_cast<u32*>(base+0x5F54AB0)=selection;
            *reinterpret_cast<u32*>(event.frame->ebp-0x430)=selection;
            *reinterpret_cast<u32*>(event.frame->ebp-0x41C)=1;
            event.frame->ebx=1;
            state.pending&=~menu_selection_pending;
            result.resume_rva=0xD1167;
            return Status::ok;
        }
    }
    if((state.pending&culture_pending) && event.frame->eax==static_cast<u32>(-2) &&
        *reinterpret_cast<const u32*>(event.frame->ebp+4)==base+0xF8D4) {
        state.rebuilding=culture_rebuilding;
        state.pending&=~culture_pending;
        result.resume_rva=0xD19B3;
    }
    if((state.pending&setup_pending) && event.frame->eax==static_cast<u32>(-2) &&
        *reinterpret_cast<const u32*>(event.frame->ebp+4)==base+0x106B25) {
        state.rebuilding=setup_rebuilding;state.pending&=~setup_pending;result.resume_rva=0xD19B3;
    }
    if((state.pending&ancestors_pending) && event.frame->eax==static_cast<u32>(-2) &&
        *reinterpret_cast<const u32*>(event.frame->ebp+4)==base+0xDF187) {
        state.rebuilding=ancestors_rebuilding;state.pending&=~ancestors_pending;result.resume_rva=0xD19B3;
    }
    if((state.pending&profile_pending) && event.frame->eax==static_cast<u32>(-2) &&
        *reinterpret_cast<const u32*>(event.frame->ebp+4)==base+0xE6CB5) {
        state.rebuilding=profile_rebuilding|
            (*reinterpret_cast<const u32*>(base+0x5F54AB0)<<selection_shift);
        state.pending&=~profile_pending;result.resume_rva=0xD19B3;
    }
    if(state.pending&menu_selection_pending) {
        // Synchronize only the game's current selection and native repaint
        // flag. No retained component list changes the input rows or geometry.
        *reinterpret_cast<u32*>(event.frame->ebp-0x430)=
            *reinterpret_cast<const u32*>(base+0x5F54AB0);
        *reinterpret_cast<u32*>(event.frame->ebp-0x41C)=1;
        state.pending&=~menu_selection_pending;
    }
    return Status::ok;
}
State save() {return state;}
void restore(const State& value) {state=value;}
}
