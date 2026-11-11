// Complete native wait/animation construction, invoked synchronously at the
// same native input protocol. No text, geometry, pixels or draw list is saved.
namespace native_wait_language {
using View=native_language_redraw::View;
constexpr auto story_view=static_cast<View>(20),complete_view=static_cast<View>(21),
    farewell_view=static_cast<View>(22),startup_view=static_cast<View>(23),intro_view=static_cast<View>(24);
enum class Construction { none,story,complete,farewell,startup_frame,startup_progress,intro };
enum class IntroStage { opening,north_fade,north_wait,role_fade,role_wait,background,version,story,done };
Construction constructing{};
IntroStage intro_stage{};
u32 intro_counter{};
enum Hook:u32 {
    story_entry=0x5200,story_tail,complete_wait,farewell_music,farewell_fade,
    farewell_return,farewell_finished,startup_fade,startup_frame_finished,startup_progress_finished,
    intro_transition_fade,intro_delay_opening,intro_delay_north,intro_delay_role,
    intro_wait_north,intro_wait_role,intro_wait_background,intro_wait_version,
    intro_story_fade,intro_story_wait,intro_final_wait,intro_background_fade,
    intro_poll_first=0x5220
};
struct Poll {u32 site;IntroStage stage;};
constexpr Poll polls[]{
    {0x1255A2,IntroStage::opening},{0x125642,IntroStage::north_fade},
    {0x125663,IntroStage::north_wait},{0x12567B,IntroStage::north_wait},
    {0x12571C,IntroStage::role_fade},{0x125737,IntroStage::role_wait},
    {0x12574F,IntroStage::role_wait},{0x1257F5,IntroStage::background},
    {0x12580D,IntroStage::background},{0x12587F,IntroStage::version},
    {0x12589B,IntroStage::version},{0x125451,IntroStage::story},
    {0x12546B,IntroStage::story}
};
u32 counter(const NativeEvent& event,IntroStage stage) {
    if(stage==IntroStage::opening) return event.frame->esi;
    if(stage==IntroStage::north_fade || stage==IntroStage::role_fade) return event.frame->ebx;
    if(stage==IntroStage::story) return event.frame->edi;
    return 0;
}
u32 component_return() {
    return static_cast<u32>(reinterpret_cast<std::uintptr_t>(native_component_calls::uwcn_component_fragment_return)-host->image_base);
}
// E6E90 has a noreturn business tail rather than an epilogue. At E71CC all
// native arguments are balanced and ESI is the sole saved register; this
// synchronous construction return unwinds exactly that confirmed fresh frame.
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_wait_farewell_return() {
    __asm__ __volatile__("popl %esi\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tret\n\t");
}
void append_hooks(std::vector<HookSpec>& hooks) {
    auto story=inline_hook(story_entry,0xFB7D1,{0x8B,0x35,0,0,0,0});
    const auto scenario=address(at<void>(0xA32B0C8));
    std::memcpy(story.expected+2,&scenario,4);hooks.push_back(story);
    // Always continue this original relative JMP explicitly.
    hooks.push_back(inline_hook(story_tail,0xFB868,{0xE9,0x13,0x84,0xFD,0xFF}));
    hooks.push_back(call(complete_wait,0x1333C,0xD3C80,0));
    hooks.push_back(call(farewell_music,0xE6EA9,0xC000,0));
    hooks.push_back(call(farewell_fade,0xE6F08,0x10D5B0,2));
    hooks.push_back(inline_hook(farewell_return,0xE71D1,{0xB9,1,0,0,0}));
    auto finished=inline_hook(farewell_finished,0xE7181,{0x83,0x3D,0,0,0,0,0});
    const auto disable_flip=address(at<void>(0x61BBA5C));
    std::memcpy(finished.expected+2,&disable_flip,4);hooks.push_back(finished);
    hooks.push_back(call(startup_fade,0x18085D,0x10D5B0,2));
    auto frame=inline_hook(startup_frame_finished,0x18089C,{0x83,0x3D,0,0,0,0,0});
    std::memcpy(frame.expected+2,&disable_flip,4);hooks.push_back(frame);
    auto progress=inline_hook(startup_progress_finished,0x123E75,{0x83,0x3D,0,0,0,0,0});
    std::memcpy(progress.expected+2,&disable_flip,4);hooks.push_back(progress);
    hooks.push_back(call(intro_transition_fade,0x1257B6,0x10D5B0,2));
    hooks.push_back(call(intro_background_fade,0x1257E9,0x10D5B0,2));
    hooks.push_back(inline_hook(intro_delay_opening,0x12559B,{0x6A,1,0xFF,0xD3,0x83,0xC4,4}));
    hooks.push_back(inline_hook(intro_delay_north,0x12563B,{0x6A,1,0xFF,0xD6,0x83,0xC4,4}));
    auto delay=inline_hook(intro_delay_role,0x125711,{0x6A,1,0xFF,0x15,0,0,0,0,0x83,0xC4,4});
    const auto sdl_delay=address(at<void>(0x18C268));
    std::memcpy(delay.expected+4,&sdl_delay,4);hooks.push_back(delay);
    hooks.push_back(inline_hook(intro_wait_north,0x125674,{0x3D,0xB8,0x0B,0,0,0x7F,0x1A}));
    hooks.push_back(inline_hook(intro_wait_role,0x125748,{0x3D,0xD0,7,0,0,0x7F,0x1A}));
    hooks.push_back(inline_hook(intro_wait_background,0x125806,{0x3D,0xB8,0x0B,0,0,0x7F,0x1A}));
    hooks.push_back(inline_hook(intro_wait_version,0x125894,{0x3D,0xB8,0x0B,0,0,0x7F,0x1A}));
    // 1252DF loops to 125260 after each fade step. Patch the shared MOV/SHL
    // entry so that the loop cannot enter the displacement of an inline JMP.
    hooks.push_back(inline_hook(intro_story_fade,0x125260,{0x8A,0xC3,0xC0,0xE0,2}));
    hooks.push_back(inline_hook(intro_story_wait,0x125464,{0x3D,0xB8,0x0B,0,0,0x7F,0x1C}));
    hooks.push_back(call(intro_final_wait,0x125905,0xD3C80,0));
    for(u32 i=0;i<std::size(polls);++i)
        hooks.push_back(call(intro_poll_first+i,polls[i].site,0xD25E0,0));
}
void present() {reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x10B720)();}
Status startup_page(u64 token) {
    constructing=Construction::startup_frame;
    const native_component_calls::NoArgumentCall frame{address(at<void>(0x180842))};
    native_component_calls::uwcn_component_skill_help(&frame);
    constructing=Construction::none;
    // 1808F8 -> 18094B is the original audio-disabled path: no progress
    // constructor has run. This dedicated source then retains its real
    // zero-initialized identity; every accepted progress constructor assigns
    // one of 201h..205h. The absent component must not become a menu label.
    if(startup_progress_source.component==TextComponent::load_character) {
        native_language_redraw::completed(startup_view);return Status::ok;
    }
    std::vector<char> encoded;
    const auto status=native_text_resource::resolve_source(startup_progress_source,
        resolve_display_text,encode_component_original,encoded);
    if(status!=Status::ok) return status;
    auto* borrowed=host->allocate(static_cast<u32>(encoded.size()));
    std::memcpy(borrowed,encoded.data(),encoded.size());
    active.push_back({token,Scope::startup_progress,address(borrowed),0,0,0,0});
    // 123DF0's original truncation may write its ECX input; use the same
    // accepted English input in this synchronous native constructor copy.
    std::vector<char> original(startup_progress_source.original.begin(),startup_progress_source.original.end());
    original.push_back(0);
    constructing=Construction::startup_progress;
    reinterpret_cast<void (__fastcall *)(char*)>(host->image_base+0x123DF0)(original.data());
    constructing=Construction::none;
    end(token);
    native_language_redraw::completed(startup_view);
    return Status::ok;
}
Status intro(const NativeEvent& event,IntroStage stage,u32 position) {
    const auto flip=*at<u32>(0x61BBA5C);
    *at<u32>(0x61BBA5C)=1;
    auto status=startup_page(event.token);
    if(status==Status::ok) {
        intro_stage=stage;intro_counter=position;
        constructing=Construction::intro;
        reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x1254C0)();
        constructing=Construction::none;
        intro_stage={};intro_counter=0;
    }
    *at<u32>(0x61BBA5C)=flip;
    if(status!=Status::ok) return status;
    native_language_redraw::completed(intro_view);
    present();
    return Status::ok;
}
Status wait(const NativeEvent& event) {
    if(event.phase!=NativePhase::before) return Status::ok;
    const auto caller=*ptr<const u32>(event.frame->ebp+4)-static_cast<u32>(host->image_base);
    if(native_language_redraw::pending(intro_view) && caller==0x12590A)
        return intro(event,IntroStage::done,0);
    if(native_language_redraw::pending(startup_view) && (caller==0xB020 || caller==0x18094B)) {
        const auto flip=*at<u32>(0x61BBA5C);
        *at<u32>(0x61BBA5C)=1;
        const auto status=startup_page(event.token);
        *at<u32>(0x61BBA5C)=flip;
        if(status!=Status::ok) return status;
        present();return Status::ok;
    }
    Construction kind=Construction::none;
    View view{};
    u32 target{};
    if(native_language_redraw::pending(story_view) && caller==0x17E86A) {
        kind=Construction::story;view=story_view;target=0xFB7D0;
    }
    if(native_language_redraw::pending(complete_view) && caller==0x13341) {
        kind=Construction::complete;view=complete_view;target=0x12F80;
    }
    if(native_language_redraw::pending(farewell_view) && caller==0xE71D1) {
        kind=Construction::farewell;view=farewell_view;target=0xE6E90;
    }
    if(kind==Construction::none) return Status::ok;
    const auto flip=*at<u32>(0x61BBA5C);
    *at<u32>(0x61BBA5C)=1;
    constructing=kind;
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+target)();
    constructing=Construction::none;
    *at<u32>(0x61BBA5C)=flip;
    native_language_redraw::completed(view);
    present();
    return Status::ok;
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=false;
    if(event.id>=intro_poll_first && event.id<intro_poll_first+std::size(polls)) {
        const auto stage=polls[event.id-intro_poll_first].stage;
        if(event.phase==NativePhase::before && constructing==Construction::intro) {
            event.frame->eax=stage==intro_stage && counter(event,stage)==intro_counter ? 1u : 0u;
            result.skip_original=1;handled=true;return Status::ok;
        }
        if(event.phase==NativePhase::after && constructing==Construction::none &&
           native_language_redraw::pending(intro_view)) {
            handled=true;return intro(event,stage,counter(event,stage));
        }
        return Status::ok;
    }
    if(event.phase==NativePhase::after) return Status::ok;
    switch(event.id) {
    case story_entry:
        if(constructing==Construction::story) {
            event.frame->esi=*at<u32>(0xA32B0C8);result.resume_rva=0xFB7FD;
        }
        break;
    case story_tail:
        result.resume_rva=constructing==Construction::story ? component_return() : 0xD3C80;
        break;
    case creation_complete_entry:
        if(constructing==Construction::complete) result.resume_rva=0x13187;
        break;
    case creation_complete_exit:
        if(constructing==Construction::complete) result.resume_rva=0x133C1;
        break;
    case complete_wait:
        if(constructing==Construction::complete) {result.skip_original=1;handled=true;return Status::ok;}
        break;
    case farewell_music:case farewell_fade:
        if(constructing==Construction::farewell) {result.skip_original=1;handled=true;return Status::ok;}
        break;
    case farewell_finished:
        if(constructing==Construction::farewell) result.resume_rva=0xE71D1;
        break;
    case farewell_return:
        if(constructing==Construction::farewell) {
            result.resume_rva=static_cast<u32>(reinterpret_cast<std::uintptr_t>(uwcn_wait_farewell_return)-host->image_base);
        }
        break;
    case startup_fade:
        if(constructing==Construction::startup_frame) {result.skip_original=1;handled=true;return Status::ok;}
        break;
    case startup_frame_finished:
        if(constructing==Construction::startup_frame) result.resume_rva=component_return();
        break;
    case startup_progress_finished:
        if(constructing==Construction::startup_progress) {
            event.frame->ecx=*ptr<u32>(event.frame->ebp-4);result.resume_rva=0x123EF1;
        }
        break;
    case intro_transition_fade:case intro_background_fade:
        if(constructing==Construction::intro) {result.skip_original=1;handled=true;return Status::ok;}
        break;
    case intro_delay_opening:
        if(constructing==Construction::intro) result.resume_rva=0x1255A2;
        break;
    case intro_delay_north:
        if(constructing==Construction::intro) result.resume_rva=0x125642;
        break;
    case intro_delay_role:
        if(constructing==Construction::intro) result.resume_rva=0x12571C;
        break;
    case intro_wait_north:
        result.resume_rva=constructing==Construction::intro || static_cast<std::int32_t>(event.frame->eax)>3000 ? 0x125695 : 0x12567B;
        break;
    case intro_wait_role:
        result.resume_rva=constructing==Construction::intro || static_cast<std::int32_t>(event.frame->eax)>2000 ? 0x125769 : 0x12574F;
        break;
    case intro_wait_background:
        result.resume_rva=constructing==Construction::intro || static_cast<std::int32_t>(event.frame->eax)>3000 ? 0x125827 : 0x12580D;
        break;
    case intro_wait_version:
        result.resume_rva=constructing==Construction::intro || static_cast<std::int32_t>(event.frame->eax)>3000 ? 0x1258B5 : 0x12589B;
        break;
    case intro_story_fade:
        if(constructing==Construction::intro) result.resume_rva=0x1252E5;
        break;
    case intro_story_wait:
        result.resume_rva=constructing==Construction::intro || static_cast<std::int32_t>(event.frame->eax)>3000 ? 0x125487 : 0x12546B;
        break;
    case intro_final_wait:
        if(constructing==Construction::intro) {result.skip_original=1;handled=true;return Status::ok;}
        break;
    }
    handled=result.resume_rva!=0;
    return Status::ok;
}
}
