#pragma once
#include "../../sdk/host_abi.h"
#include <vector>

namespace urwcn::adapter::native_language_redraw {
// Shared input synchronization and confirmed native drawing continuations.
// State retains pending flags and the reconstruction phase. During E66B0
// reconstruction, rebuilding's high bits retain the actual Menu selection;
// no page content, layout or native frame pointer is retained. Pending bits:
// menu selection, ancestors, native zero-event exit, setup, profile, culture,
// followed by the confirmed View construction requests. No component list
// supplies pixels for these continuations.
struct State {u32 pending;u32 rebuilding;};
enum class View:u32 { ancestors=1,setup=3,attributes=4,culture=5,
    main=6,about,credits,creation,scenario_selection,scenario_confirmation,
    game_course,world,skills=15,spells,encyclopedia,profile,load,
    story,creation_complete,farewell,startup,intro,hud,map,messages,keyboard_help };
using MenuRebuild=Status (*)(const NativeEvent&,bool& rebuilt,u32& selection);
void initialize(const HostApi*,MenuRebuild);
void request(bool main_menu);
bool pending(View);
void completed(View);
bool input_return(u32 caller_return_rva);
void append_hooks(std::vector<HookSpec>&);
Status dispatch(const NativeEvent&,DispatchResult&,bool& handled);
State save();
void restore(const State&);
}
