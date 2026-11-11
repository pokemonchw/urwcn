// Complete native construction transactions. Only original drawing code runs;
// no page fields, coordinates, pixels or component sequences are retained here.
namespace native_full_language {
using View=native_language_redraw::View;
enum class Construction { none,about,credits,selection,confirmation,course,world,skills,spells,encyclopedia,
    profile_frame,completed_culture,completed_sex,sex,completed_name,portrait,completed_portrait,season,load_empty,
    active_name,ancestor_record,ancestor_detail_base,ancestor_detail,encyclopedia_keyword,attributes };
Construction constructing{};
u32 world_legend{},preview_selection{};
struct Portrait {u32 index,current,next;};
Portrait portrait{};
enum Hook:u32 { skills_entry=0x5120,skills_classify,skills_save,skills_input,skills_result,
    input_entry,retired_spells_music_operand,spells_select,spells_result,
    encyclopedia_entry,encyclopedia_exit,encyclopedia_history,encyclopedia_select,encyclopedia_cruise,
    culture_save,sex_drawn,sex_action,profile_frame_end,name_initial,name_result,
    portrait_initial,portrait_result,season_initial,season_input,season_result,load_wait,
    spells_music=0x5140,name_footer_tint=0x5160,name_input_result,ancestor_cursor,ancestor_wait,ancestor_finished,name_text,
    ancestor_mode,ancestor_detail_end,ancestor_detail_wait,ancestor_name_text,ancestor_death_text,keyword_prompt_end,
    attributes_wait };
struct BorrowedFrame {u32 target,frame;};
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_full_language_frame(const BorrowedFrame*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%ebx\n\tmovl 4(%ebx),%ebp\n\tcall *(%ebx)\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t");
}
struct KeywordFragment {u32 target,map_rgb;};
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_full_keyword_prompt(const KeywordFragment*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%eax\n\tmovl 4(%eax),%ebx\n\tcall *(%eax)\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t");
}

void append_hooks(std::vector<HookSpec>& hooks) {
    auto skills=inline_hook(skills_entry,0xE0B6E,{0xB9,0,0,0,0});
    const auto overlays=address(at<void>(0xA38522C));
    std::memcpy(skills.expected+1,&overlays,4);hooks.push_back(skills);
    hooks.push_back(call(skills_classify,0xE0BCA,0xE0220,0));
    auto saved=inline_hook(skills_save,0xE0DE6,{0x85,0xDB,0x75,0x16,0xA1,0,0,0,0});
    const auto skill_selection=address(at<void>(0x5F5D144));
    std::memcpy(saved.expected+5,&skill_selection,4);hooks.push_back(saved);
    hooks.push_back(call(skills_input,0xE0ED2,0xD1120,0));
    // Both branches are continued explicitly below, so the relative JE is
    // never copied into the resident replay trampoline.
    hooks.push_back(inline_hook(skills_result,0xE0ED7,
        {0x83,0xF8,0xFF,0x0F,0x84,0x91,0x01,0,0}));
    hooks.push_back(inline_hook(input_entry,0xD1159,{0x89,0x9D,0xE4,0xFB,0xFF,0xFF}));
    hooks.push_back(call(spells_music,0xDFD73,0xC000,0));
    hooks.push_back(inline_hook(spells_select,0xDFFFA,{0x33,0xFF,0x89,0xBD,0xF4,0xFB,0xFF,0xFF}));
    hooks.push_back(inline_hook(spells_result,0xE003B,{0x8B,0xD8,0x83,0xFB,0xD6}));
    hooks.push_back(inline_hook(encyclopedia_entry,0x3E697,{0x8B,0xF9,0x33,0xC0,0x0F,0x1F,0x44,0,0}));
    auto finish=inline_hook(encyclopedia_exit,0x3E820,{0xA3,0,0,0,0});
    const auto flip=address(at<void>(0x61BBA5C));
    std::memcpy(finish.expected+1,&flip,4);hooks.push_back(finish);
    hooks.push_back(call(encyclopedia_history,0x3DF0F,0x3C820,0));
    auto chosen_link=inline_hook(encyclopedia_select,0x3E1EF,{0x8B,0x0D,0,0,0,0});
    const auto chosen_row=address(at<void>(0x5F54AB0));
    std::memcpy(chosen_link.expected+2,&chosen_row,4);hooks.push_back(chosen_link);
    hooks.push_back(inline_hook(encyclopedia_cruise,0x3E4CF,{0x8B,0xC8,0x8D,0x54,0x24,0x10}));
    auto culture=inline_hook(culture_save,0xF623,{0xA1,0,0,0,0});
    const auto count=address(at<void>(0x5F54A34));
    std::memcpy(culture.expected+1,&count,4);hooks.push_back(culture);
    auto sex=inline_hook(sex_drawn,0xF37C,{0x83,0x3D,0,0,0,0,1});
    const auto creation_mode=address(at<void>(0x217ABC));
    std::memcpy(sex.expected+2,&creation_mode,4);hooks.push_back(sex);
    // This JE is also fully continued, never replayed with an old displacement.
    hooks.push_back(inline_hook(sex_action,0xF44F,{0x83,0xF8,0x1B,0x74,0x3F}));
    auto profile=inline_hook(profile_frame_end,0x12F2E,{0x83,0x3D,0,0,0,0,0});
    const auto display=address(at<void>(0x61BBCD8));
    std::memcpy(profile.expected+2,&display,4);hooks.push_back(profile);
    hooks.push_back(inline_hook(name_initial,0x1189C,{0x6A,0x64,0x6A,0,0x68,0,0,0,0}));
    const auto initial_name=address(at<void>(0x61BBA60));
    std::memcpy(hooks.back().expected+5,&initial_name,4);
    auto name=inline_hook(name_result,0x119B0,{0xBA,0,0,0,0});
    const auto player_name=address(at<void>(0xA32A6E8));
    std::memcpy(name.expected+1,&player_name,4);hooks.push_back(name);
    hooks.push_back(inline_hook(portrait_initial,0x12644,{0x89,0x9D,0xF4,0xFB,0xFF,0xFF}));
    hooks.push_back(inline_hook(portrait_result,0x1283F,{0x83,0xF8,0x64,0x7C,0x04}));
    auto season=inline_hook(season_initial,0xFB10,{0x83,0x3D,0,0,0,0,1});
    std::memcpy(season.expected+2,&creation_mode,4);hooks.push_back(season);
    hooks.push_back(call(season_input,0xFB3B,0xD1120,0));
    hooks.push_back(inline_hook(season_result,0xFB40,{0x83,0xF8,0x64,0x7C,0x04}));
    hooks.push_back(call(load_wait,0x12505C,0xD3C80,0));
    hooks.push_back(inline_hook(name_footer_tint,0xF24A,{0x83,0x7D,0xFC,2,0x8D,0x42,0x0F}));
    hooks.push_back(inline_hook(name_input_result,0x10F71E,{0x6A,0x64,0x8B,0xD8,0x8D,0x45,0x90}));
    hooks.push_back(call(ancestor_cursor,0xDE9D9,0x10D9A0,0));
    hooks.push_back(call(ancestor_wait,0xDEB7A,0xD3C80,0));
    hooks.push_back(inline_hook(ancestor_finished,0xDEB7F,{0xE9,0xC3,8,0,0}));
    hooks.push_back(call(name_text,0x10F6AC,0x10E5A0,3));
    hooks.push_back(inline_hook(ancestor_mode,0xDEA21,{0x83,0xFE,0xFF,0x0F,0x84,0x5A,1,0,0}));
    auto detail=inline_hook(ancestor_detail_end,0xDF377,{0xC7,0x05,0,0,0,0,0,0,0,0});
    std::memcpy(detail.expected+2,&flip,4);hooks.push_back(detail);
    hooks.push_back(call(ancestor_detail_wait,0xDF3FA,0xD3C80,0));
    hooks.push_back(call(ancestor_name_text,0xDD7AF,0x10E5A0,3));
    hooks.push_back(call(ancestor_death_text,0xDD82B,0x10E5A0,3));
    hooks.push_back(inline_hook(keyword_prompt_end,0x3E582,{0xBA,0x1E,0,0,0}));
    hooks.push_back(call(attributes_wait,0xE6B9F,0xD3C80,0));
}

Status construct_skills(u32 mode,u32 preview) {
    preview_selection=preview;
    constructing=Construction::skills;
    reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0xE0B40)(mode);
    constructing=Construction::none;
    return Status::ok;
}

Status encyclopedia(u32& selection) {
    const auto action=*at<u32>(0x5F4EF10+selection*0xE8+0xC8);
    const std::string link=action ? "" : at<char>(0x2CBB18+(selection+2)*200);
    const std::string topic=at<char>(0x2EA820);
    constructing=Construction::encyclopedia;
    reinterpret_cast<void (__fastcall *)(const char*)>(host->image_base+0x3E680)(topic.c_str());
    constructing=Construction::none;
    for(u32 row=0;row<*at<u32>(0x5F54A34);++row) {
        const auto current=*at<u32>(0x5F4EF10+row*0xE8+0xC8);
        if(current==action && (action || link==at<char>(0x2CBB18+(row+2)*200))) {
            selection=row;break;
        }
    }
    return Status::ok;
}

Status main(native_root_component::RootRevision root=native_root_component::current()) {
    const auto background=native_root_component::paint_background(root);
    if(background!=Status::ok) return background;
    return host->native_fragment(0x125BA3,0x125BE1);
}
Status parent_main() {
    const auto current=native_menu_component::active();
    const auto current_root=native_root_component::current();
    const auto parent_root=native_ui_scene::saved_background(static_cast<u32>(native_ui_cache_owners::Slot::first));
    const auto parent=native_ui_scene::saved_menu(static_cast<u32>(native_ui_cache_owners::Slot::first));
    native_menu_component::retain(current);native_menu_component::retain(parent);
    native_menu_component::activate(parent);
    const auto status=main(parent_root);
    if(status==Status::ok) {
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0xD0650)(*at<u32>(0x5F54AB0),0);
        reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0x10DA10)();
    }
    native_menu_component::activate(current);
    native_root_component::activate(current_root);
    native_menu_component::release(parent);native_menu_component::release(current);
    return status;
}
Status profile_before_sex() {
    constructing=Construction::profile_frame;
    // This page's hut is the complete original 12980 image construction,
    // distinct from the 1127C0 root that preceded character creation. Begin
    // after the unused PUSH ECX local and stop before uploads/cursor handling.
    const native_component_calls::NoArgumentCall frame{address(at<void>(0x12ED1))};
    native_component_calls::urwcn_component_skill_help(&frame);
    constructing=Construction::none;
    constructing=Construction::completed_culture;
    reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0xF4F0)();
    constructing=Construction::none;
    return Status::ok;
}
Status profile_before_portrait() {
    const auto status=profile_before_sex();
    if(status!=Status::ok) return status;
    constructing=Construction::completed_sex;
    reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0xF300)();
    constructing=Construction::completed_name;
    reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0x11870)();
    constructing=Construction::none;
    return Status::ok;
}
Status profile_before_season() {
    const auto status=profile_before_portrait();
    if(status!=Status::ok) return status;
    u32 index=0;
    // Choose_Portrait's accepted filename remains the original Plr field.
    // Its original 100-byte filename records supply this native constructor.
    while(std::strcmp(at<char>(0x217AC0+index*100),at<char>(0xA32AC1D))!=0) ++index;
    portrait={index,address(at<void>(0x217AC0+index*100)),address(at<void>(0x217B24+index*100))};
    constructing=Construction::completed_portrait;
    reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0x125D0)();
    constructing=Construction::none;
    return Status::ok;
}
Status popup(Construction kind) {
    using Native=void (URWCN_CALL *)();
    // The original About/Credits caller owns this exact first background.
    auto status=parent_main();
    if(status!=Status::ok) return status;
    constructing=kind;
    reinterpret_cast<Native>(host->image_base+(kind==Construction::about ? 0x1247C0 : 0x1244F0))();
    constructing=Construction::none;
    native_language_redraw::completed(kind==Construction::about ? View::about : View::credits);
    reinterpret_cast<Native>(host->image_base+0x10B720)();
    return Status::ok;
}
Status wait(const NativeEvent& event) {
    if(event.phase!=NativePhase::before) return Status::ok;
    const auto caller=*ptr<const u32>(event.frame->ebp+4)-static_cast<u32>(host->image_base);
    if(native_language_redraw::pending(View::attributes) &&
       (caller==0xE6BA4 || caller==0x1039EF)) {
        const auto flip=*at<u32>(0x61BBA5C);
        constructing=Construction::attributes;
        reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0xE66B0)(caller==0xE6BA4 ? 2 : 0);
        constructing=Construction::none;
        *at<u32>(0x61BBA5C)=flip;
        native_language_redraw::completed(View::attributes);
        reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0x10B720)();
        return Status::ok;
    }
    if(native_language_redraw::pending(View::hud) &&
       (caller==0x174A75 || caller==0x177948)) {
        const auto status=native_parent_cache_language::game_parent();
        if(status!=Status::ok) return status;
        native_language_redraw::completed(View::hud);
        reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0x10B720)();
        return Status::ok;
    }
    if(native_language_redraw::pending(View::about) && in(Scope::about)) return popup(Construction::about);
    if(native_language_redraw::pending(View::credits) && in(Scope::credits)) return popup(Construction::credits);
    if(native_language_redraw::pending(View::ancestors) &&
       *ptr<const u32>(event.frame->ebp+4)==host->image_base+0xDF3FF) {
        auto status=parent_main();
        if(status!=Status::ok) return status;
        const auto flip=*at<u32>(0x61BBA5C);*at<u32>(0x61BBA5C)=1;
        constructing=Construction::ancestor_detail_base;
        const native_component_calls::NoArgumentCall background{address(at<void>(0xDE9DE))};
        native_component_calls::urwcn_component_skill_help(&background);
        // DEBB3's original MOV operand identifies this exact native named
        // background. No Menu or detail text belongs to that cache.
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0x10C540)(*at<u32>(0xDEBB4),0);
        constructing=Construction::ancestor_detail;
        const BorrowedFrame detail{address(at<void>(0xDF360)),*ptr<const u32>(event.frame->ebp)};
        urwcn_full_language_frame(&detail);
        status=host->native_fragment(0xDF3C3,0xDF3FF);
        constructing=Construction::none;*at<u32>(0x61BBA5C)=flip;
        if(status!=Status::ok) return status;
        native_language_redraw::completed(View::ancestors);
        reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0x10B720)();
        return Status::ok;
    }
    if(native_language_redraw::pending(View::ancestors) &&
       *ptr<const u32>(event.frame->ebp+4)==host->image_base+0xDEB7F) {
        const auto page=*ptr<const u32>(event.frame->ebp);
        // E754D supplies ECX=ESI. DE990 saves that actual enclosing ESI
        // before its own UI code reuses the register for the color mapper.
        const auto record=*ptr<const u32>(page-0x5BC);
        constructing=Construction::ancestor_record;
        reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0xDE990)(record);
        constructing=Construction::none;
        native_language_redraw::completed(View::ancestors);
        reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0x10B720)();
        return Status::ok;
    }
    if(native_language_redraw::pending(View::load) && *ptr<const u32>(event.frame->ebp+4)==host->image_base+0x125061) {
        auto status=parent_main();
        if(status!=Status::ok) return status;
        constructing=Construction::load_empty;
        status=host->native_fragment(0x124FE7,0x125061);
        constructing=Construction::none;
        if(status!=Status::ok) return status;
        native_language_redraw::completed(View::load);
        reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0x10B720)();
        return Status::ok;
    }
    return Status::ok;
}
Status menu(const NativeEvent& event,bool& rebuilt,u32& selection_index) {
    const auto caller=*ptr<const u32>(event.frame->ebp+4)-static_cast<u32>(host->image_base);
    using Native=void (URWCN_CALL *)();
    if((native_language_redraw::pending(View::setup) && caller==0x106B25) ||
       (native_language_redraw::pending(View::ancestors) && caller==0xDF187)) {
        const auto status=parent_main();
        if(status!=Status::ok) return status;
        // The existing real-frame continuation below constructs this current
        // window after its own parent cache has been renewed.
        return Status::ok;
    }
    if(native_language_redraw::pending(View::main) && in(Scope::menu_input)) {
        const auto status=main();
        if(status!=Status::ok) return status;
        native_language_redraw::completed(View::main);rebuilt=true;return Status::ok;
    }
    if(native_language_redraw::pending(View::creation) && caller==0x125D05) {
        auto status=parent_main();
        if(status!=Status::ok) return status;
        status=host->native_fragment(0x125CFB,0x125D00);
        if(status!=Status::ok) return status;
        native_language_redraw::completed(View::creation);rebuilt=true;return Status::ok;
    }
    if(native_language_redraw::pending(View::load) && caller==0x125097) {
        auto status=parent_main();
        if(status!=Status::ok) return status;
        status=host->native_fragment(0x12508D,0x125092);
        if(status!=Status::ok) return status;
        native_language_redraw::completed(View::load);rebuilt=true;return Status::ok;
    }
    if(native_language_redraw::pending(View::scenario_selection) && caller==0x10B89) {
        constructing=Construction::selection;
        reinterpret_cast<Native>(host->image_base+0x108A0)();
        constructing=Construction::none;
        native_language_redraw::completed(View::scenario_selection);rebuilt=true;return Status::ok;
    }
    if(native_language_redraw::pending(View::scenario_confirmation) && caller==0x1077E) {
        constructing=Construction::confirmation;
        reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0x105C0)(0);
        constructing=Construction::none;
        native_language_redraw::completed(View::scenario_confirmation);rebuilt=true;return Status::ok;
    }
    if(native_language_redraw::pending(View::game_course) && caller==0x110C5) {
        constructing=Construction::course;
        reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0x10D40)(0);
        constructing=Construction::none;
        native_language_redraw::completed(View::game_course);rebuilt=true;return Status::ok;
    }
    if(native_language_redraw::pending(View::world) && caller==0x60EA8) {
        // D1120's original PUSH EDI preserved the caller's actual legend flag.
        world_legend=*ptr<const u32>(event.frame->ebp-0x440);
        constructing=Construction::world;
        reinterpret_cast<Native>(host->image_base+0x60B60)();
        constructing=Construction::none;
        native_language_redraw::completed(View::world);rebuilt=true;return Status::ok;
    }
    if(native_language_redraw::pending(View::skills) && (in(Scope::skills_input) || caller==0xE0ED7)) {
        const auto preview=*ptr<const u32>(event.frame->ebp-0x440);
        // D1138 saved the enclosing skill page's original mode in EBX.
        const auto mode=*ptr<const u32>(event.frame->ebp-0x438);
        const auto status=construct_skills(mode,preview);
        if(status!=Status::ok) return status;
        native_language_redraw::completed(View::skills);rebuilt=true;return Status::ok;
    }
    if(native_language_redraw::pending(View::spells) && caller==0xE003B) {
        const auto page_frame=*ptr<const u32>(event.frame->ebp);
        preview_selection=*ptr<const u32>(page_frame-0x40C);
        const auto mode=*ptr<const u32>(page_frame-0x410);
        constructing=Construction::spells;
        reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0xDFD40)(mode);
        constructing=Construction::none;
        native_language_redraw::completed(View::spells);rebuilt=true;return Status::ok;
    }
    if(native_language_redraw::pending(View::encyclopedia) && in(Scope::encyclopedia_input)) {
        const auto status=encyclopedia(selection_index);if(status!=Status::ok) return status;
        native_language_redraw::completed(View::encyclopedia);rebuilt=true;return Status::ok;
    }
    if(native_language_redraw::pending(View::profile) && caller==0xF43A) {
        const auto status=profile_before_sex();
        if(status!=Status::ok) return status;
        constructing=Construction::sex;
        reinterpret_cast<Native>(host->image_base+0xF300)();
        constructing=Construction::none;
        native_language_redraw::completed(View::profile);rebuilt=true;return Status::ok;
    }
    if(native_language_redraw::pending(View::profile) && caller==0x1283F) {
        const Portrait current{*ptr<const u32>(event.frame->ebp-0x438),
            *ptr<const u32>(event.frame->ebp-0x440),*ptr<const u32>(event.frame->ebp-0x43C)};
        const auto status=profile_before_portrait();
        if(status!=Status::ok) return status;
        portrait=current;
        constructing=Construction::portrait;
        reinterpret_cast<Native>(host->image_base+0x125D0)();
        constructing=Construction::none;
        native_language_redraw::completed(View::profile);rebuilt=true;return Status::ok;
    }
    if(native_language_redraw::pending(View::profile) && caller==0xFB40) {
        const auto status=profile_before_season();
        if(status!=Status::ok) return status;
        constructing=Construction::season;
        reinterpret_cast<Native>(host->image_base+0xFA40)();
        constructing=Construction::none;
        native_language_redraw::completed(View::profile);rebuilt=true;return Status::ok;
    }
    return Status::ok;
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=false;
    if(event.phase==NativePhase::after) {
        if(event.id==skills_input) {end(event.token);handled=true;}
        if(event.id==name_text) {end(event.token);handled=true;}
        if(event.id==native_name_input::scope &&
           (constructing==Construction::completed_name || constructing==Construction::active_name))
            {end(event.token);handled=true;}
        return Status::ok;
    }
    if(event.id==attributes_wait && constructing==Construction::attributes) {
        result.skip_original=1;handled=true;return Status::ok;
    }
    if(event.id==0x5109 && constructing==Construction::attributes) {
        // Keep the pure constructor's no-presentation flip. Mode 2 builds
        // its complete information panel after this original display tail.
        result.resume_rva=0xE6B26;handled=true;return Status::ok;
    }
    if(event.id==name_text) {
        if(!chinese_enabled && native_name_input::contains_utf8(ptr<char>(event.arguments[0])))
            begin(event,Scope::profile_identity_unicode);
        handled=true;return Status::ok;
    }
    if(event.id==keyword_prompt_end && constructing==Construction::encyclopedia_keyword) {
        result.resume_rva=static_cast<u32>(reinterpret_cast<std::uintptr_t>(
            native_component_calls::urwcn_component_fragment_return)-host->image_base);
        handled=true;return Status::ok;
    }
    if(event.id==name_input_result && native_language_redraw::pending(View::encyclopedia) &&
       event.frame->eax==static_cast<u32>(-2) && !native_name_input::state.committed &&
       *ptr<const u32>(event.frame->ebp+4)==host->image_base+0x3E58E) {
        const auto flip=*at<u32>(0x61BBA5C);
        auto selection=*at<u32>(0x5F54AB0);
        const auto status=encyclopedia(selection);if(status!=Status::ok) return status;
        *at<u32>(0x5F54AB0)=selection;
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0xD0650)(selection,0);
        constructing=Construction::encyclopedia_keyword;
        // The original prompt fragment has no enclosing local reads. Its
        // EBX is exactly the original SDL_MapRGB import loaded at 3E2F5.
        const KeywordFragment prompt{address(at<void>(0x3E4F0)),*at<u32>(0x18C1F8)};
        urwcn_full_keyword_prompt(&prompt);
        constructing=Construction::none;
        *at<u32>(0x61BBA5C)=flip;
        event.frame->esi=*ptr<u32>(event.frame->ebp-0xA4);
        event.frame->edi=*ptr<u32>(event.frame->ebp-0xB8);
        event.frame->ebx=*ptr<u32>(event.frame->ebp-0xAC);
        native_language_redraw::completed(View::encyclopedia);
        result.resume_rva=0x10F6A0;handled=true;return Status::ok;
    }
    if(event.id==profile_name_footer && constructing==Construction::none) {
        windows_profile_error_source.footer_mode=event.frame->ecx;
        windows_profile_error_source.footer_tint=0;
    }
    if(event.id==name_footer_tint && constructing==Construction::none &&
       *ptr<const u32>(event.frame->ebp+4)==host->image_base+0x11909)
        windows_profile_error_source.footer_tint=event.frame->edx;
    if(event.id==name_input_result && native_language_redraw::pending(View::profile) &&
       event.frame->eax==static_cast<u32>(-2) && !native_name_input::state.committed &&
       *ptr<const u32>(event.frame->ebp+4)==host->image_base+0x119B0) {
        auto status=profile_before_sex();
        if(status!=Status::ok) return status;
        constructing=Construction::completed_sex;
        reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0xF300)();
        constructing=Construction::active_name;
        reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0x11870)();
        constructing=Construction::none;
        // Resume the real getst frame at its own complete text/cursor draw,
        // retaining the original buffer, byte capacity, IME and continuation.
        event.frame->esi=*ptr<u32>(event.frame->ebp-0xA4);
        event.frame->edi=*ptr<u32>(event.frame->ebp-0xB8);
        event.frame->ebx=*ptr<u32>(event.frame->ebp-0xAC);
        native_language_redraw::completed(View::profile);
        result.resume_rva=0x10F6A0;handled=true;return Status::ok;
    }
    // Generation 4 installed this operand hook in the resident host. Its
    // original MOV still replays until that native process ends; the new
    // music CALL boundary below supplies the construction-only skip.
    if(event.id==retired_spells_music_operand) {handled=true;return Status::ok;}
    if(event.id==load_saved_empty_panel && constructing==Construction::load_empty) {
        event.frame->edi=0;
        return Status::ok; // The ordinary complete CFFB0 scope still runs.
    }
    if(event.id==load_wait && constructing==Construction::load_empty) {
        result.skip_original=1;handled=true;return Status::ok;
    }
    if(event.id==native_name_input::scope && constructing==Construction::completed_name) {
        if(!chinese_enabled && native_name_input::contains_utf8(at<char>(0xA32A6E8)))
            begin(event,Scope::profile_identity_unicode);
        begin(event,Scope::text);
        std::vector<char> name;
        const auto status=native_name_input::display(at<char>(0xA32A6E8),name);
        if(status!=Status::ok) return status;
        // These are Choose_Name's own input origin and color, established by
        // 1196B..119A9 immediately before this actual native input boundary.
        const native_component_calls::TextBlockCall text{address(at<void>(0x10E5A0)),
            *at<std::int32_t>(0xA1C1CB4),*at<std::int32_t>(0x61BBB3C),name.data(),event.frame->ecx,0};
        native_component_calls::urwcn_component_text_block(&text);
        // This is getst's confirmed normal-return write at 10F930, paired
        // with Choose_Name's input flag setup at 1197F.
        *at<u32>(0x61BBA58)=0;
        result.skip_original=1;handled=true;return Status::ok;
    }
    if(event.id==native_name_input::scope && constructing==Construction::active_name) {
        result.skip_original=1;handled=true;return Status::ok;
    }
    if(event.id==season_input && constructing==Construction::season) {
        result.skip_original=1;handled=true;return Status::ok;
    }
    if(event.id==0x510C && constructing==Construction::profile_frame) {
        result.skip_original=1;handled=true;return Status::ok;
    }
    if(event.id==0x510D && constructing==Construction::completed_culture) {
        result.resume_rva=0xF8CF;handled=true;return Status::ok;
    }
    if(event.id==0x510B && constructing==Construction::completed_culture) {
        result.resume_rva=0xF9FD;handled=true;return Status::ok;
    }
    if(event.id==skills_input) {
        if(constructing==Construction::skills) result.skip_original=1;
        else begin(event,Scope::skills_input);
        handled=true;return Status::ok;
    }
    if(event.id==skills_result) {
        result.resume_rva=constructing==Construction::skills ? 0xE10A9 :
            event.frame->eax==static_cast<u32>(-1) ? 0xE1071 : 0xE0EE0;
        handled=true;return Status::ok;
    }
    if((event.id==about_wait && constructing==Construction::about) ||
       (event.id==credits_wait && constructing==Construction::credits)) {
        result.skip_original=1;handled=true;return Status::ok;
    }
    switch(event.id) {
    case ancestor_mode:
        result.resume_rva=constructing==Construction::ancestor_detail_base ?
            static_cast<u32>(reinterpret_cast<std::uintptr_t>(native_component_calls::urwcn_component_fragment_return)-host->image_base) :
            event.frame->esi==static_cast<u32>(-1) ? 0xDEB84 : 0xDEA2A;
        break;
    case ancestor_detail_end:
        if(constructing==Construction::ancestor_detail)
            result.resume_rva=static_cast<u32>(reinterpret_cast<std::uintptr_t>(native_component_calls::urwcn_component_fragment_return)-host->image_base);
        break;
    case ancestor_detail_wait:
        if(constructing==Construction::ancestor_detail) {result.skip_original=1;handled=true;return Status::ok;}
        break;
    case ancestor_cursor:case ancestor_wait:
        if(constructing==Construction::ancestor_record) {result.skip_original=1;handled=true;return Status::ok;}
        break;
    case ancestor_finished:
        result.resume_rva=constructing==Construction::ancestor_record ? 0xDF451 : 0xDF447;
        break;
    case name_initial:
        if(constructing==Construction::completed_name) result.resume_rva=0x118B3;
        if(constructing==Construction::active_name) {
            if(windows_profile_error_source.footer_mode==2)
                std::strcpy(ptr<char>(event.frame->ebp-0x408),at<char>(windows_profile_error_source.native_source_rva));
            result.resume_rva=0x118B3;
        }
        break;
    case name_result:
        if(constructing==Construction::completed_name) result.resume_rva=0x11C25;
        if(constructing==Construction::active_name) result.resume_rva=0x11C5D;
        break;
    case portrait_initial:
        if(constructing==Construction::portrait || constructing==Construction::completed_portrait) {
            event.frame->ebx=portrait.index;event.frame->edi=portrait.current;event.frame->esi=portrait.next;
            event.frame->edx=0;
            *ptr<u32>(event.frame->ebp-0x40C)=portrait.current;
            *ptr<u32>(event.frame->ebp-0x410)=27;
            result.resume_rva=0x12680;
        }
        break;
    case portrait_result:
        if(constructing==Construction::portrait) result.resume_rva=0x12921;
        else if(constructing==Construction::completed_portrait) result.resume_rva=0x128CC;
        else result.resume_rva=static_cast<std::int32_t>(event.frame->eax)<100 ? 0x12848 : 0x12844;
        break;
    case season_initial:
        if(constructing==Construction::season) result.resume_rva=0xFB36;
        break;
    case season_result:
        result.resume_rva=constructing==Construction::season ? 0xFB81 :
            static_cast<std::int32_t>(event.frame->eax)<100 ? 0xFB49 : 0xFB45;
        break;
    case profile_frame_end:
        if(constructing==Construction::profile_frame)
            result.resume_rva=static_cast<u32>(reinterpret_cast<std::uintptr_t>(
                native_component_calls::urwcn_component_fragment_return)-host->image_base);
        break;
    case culture_save:
        if(constructing==Construction::completed_culture) {
            *at<u32>(0x5F54ABC)=*at<u32>(0x5F54A34);
            *at<u32>(0x5F54AB0)=*at<unsigned char>(0xA32A6F5);
            result.resume_rva=0xF678;
        }
        break;
    case sex_drawn:
        if(constructing==Construction::sex) result.resume_rva=0xF4C7;
        if(constructing==Construction::completed_sex) {
            *at<u32>(0x5F54AB0)=*at<unsigned char>(0xA32B1A9)-1;
            result.resume_rva=0xF435;
        }
        break;
    case sex_action:
        result.resume_rva=constructing==Construction::completed_sex ? 0xF4C7 :
            event.frame->eax==27 ? 0xF493 : 0xF454;
        break;
    case encyclopedia_entry:
        if(constructing==Construction::encyclopedia) {
            event.frame->edi=event.frame->ecx;event.frame->eax=0;result.resume_rva=0x3E6D1;
        }
        break;
    case encyclopedia_exit:
        if(constructing==Construction::encyclopedia) result.resume_rva=0x3E942;
        break;
    case encyclopedia_history:
        if(constructing==Construction::encyclopedia) {result.skip_original=1;handled=true;return Status::ok;}
        break;
    case encyclopedia_select:
        if(constructing==Construction::encyclopedia) {
            event.frame->eax=address(at<char>(windows_build::rdata_rva(0x18C616)));result.resume_rva=0x3E22C;
        }
        break;
    case encyclopedia_cruise:
        if(constructing==Construction::encyclopedia) {event.frame->eax=0;result.resume_rva=0x3E3F2;}
        break;
    case input_entry:
        if(constructing==Construction::spells || constructing==Construction::encyclopedia ||
           constructing==Construction::portrait || constructing==Construction::completed_portrait)
            result.resume_rva=0xD19B3;
        if(constructing==Construction::completed_culture || constructing==Construction::completed_sex)
            result.resume_rva=0xD18E5;
        break;
    case spells_music:
        if(constructing==Construction::spells) {result.skip_original=1;handled=true;return Status::ok;}
        break;
    case spells_select:
        if(constructing==Construction::spells) {
            // The highlighted row can be F1/Exit while the last real ritual's
            // native infobox remains visible. Rebuild that same actual view;
            // the enclosing D1120 restores the independent current selection.
            *at<u32>(0x5F54AB0)=preview_selection;
            event.frame->edi=0;
            *ptr<u32>(event.frame->ebp-0x40C)=0;
            *ptr<u32>(event.frame->ebp-0x414)=0;
            result.resume_rva=0xE001C;
        }
        break;
    case spells_result:
        if(constructing==Construction::spells) result.resume_rva=0xE0203;
        break;
    case skills_entry:
        if(constructing==Construction::skills) result.resume_rva=0xE0B98;
        break;
    case skills_classify:
        if(constructing==Construction::skills) {result.skip_original=1;handled=true;return Status::ok;}
        break;
    case skills_save:
        if(constructing==Construction::skills) {
            *at<u32>(0x5F54AB0)=preview_selection;
            event.frame->edi=preview_selection;
            event.frame->esi=0;
            result.resume_rva=0xE0E08;
        } else if(event.frame->ebx) result.resume_rva=0xE0E00;
        else {event.frame->eax=*at<u32>(0x5F5D144);result.resume_rva=0xE0DEF;}
        break;
    case creation_select_exit:
        if(constructing==Construction::selection) result.resume_rva=0x10BAF;
        break;
    case creation_confirmation_entry:
        if(constructing==Construction::confirmation) result.resume_rva=0x10707;
        break;
    case creation_confirmation_exit:
        if(constructing==Construction::confirmation) result.resume_rva=0x10797;
        break;
    case creation_course_entry:
        if(constructing==Construction::course) result.resume_rva=0x10D60;
        break;
    case creation_course_exit:
        if(constructing==Construction::course) result.resume_rva=0x11135;
        break;
    case creation_footer_rng:
        if(constructing==Construction::active_name) {
            *ptr<u32>(event.frame->ebp-4)=windows_profile_error_source.footer_mode;
            event.frame->edi=0;event.frame->edx=windows_profile_error_source.footer_tint;
            result.resume_rva=0xF24A;
        }
        if(constructing==Construction::selection || constructing==Construction::course ||
           constructing==Construction::sex || constructing==Construction::completed_sex ||
           constructing==Construction::completed_name || constructing==Construction::portrait ||
           constructing==Construction::completed_portrait || constructing==Construction::season) {
            event.frame->esi=*at<u32>(0x18C1F8);result.resume_rva=0xF293;
        }
        break;
    case creation_world_entry:
        if(constructing==Construction::world) {event.frame->edi=world_legend;result.resume_rva=0x60BB8;}
        break;
    case creation_world_after_title:
        if(constructing==Construction::world) {*at<u32>(0x61BBAC8)=0;result.resume_rva=0x6109F;}
        break;
    case creation_world_after_map:
        if(constructing==Construction::world) {event.frame->ebx=0;result.resume_rva=0x60CC2;}
        break;
    case creation_world_exit:
        if(constructing==Construction::world) result.resume_rva=0x6113D;
        break;
    }
    handled=result.resume_rva!=0;
    return Status::ok;
}
}
