// Linux 3.89 get_camp's display-only fragment. The original story file,
// native button construction, Y/N actions and current selection stay native.
extern "C" void uwcn_linux_redraw_scenario_fragment(std::uintptr_t);
extern "C" void uwcn_linux_redraw_scenario_return();

bool scenario_confirmation_refresh=true;
bool scenario_confirmation_chinese;
bool rebuilding_scenario_confirmation;

void scenario_confirmation_question(Frame& frame) {
    Frame arguments=frame;
    std::string display;
    if(chinese) {
        display=scenario_confirmation_text("question");
        arguments.rdx=reinterpret_cast<std::uintptr_t>(display.c_str());
    }
    frame.rax=call(arguments,0x13e8b0);
}
void scenario_confirmation_button(Frame& frame) {
    const bool last=frame.resume-host->image_base-5==0x1cf79;
    Frame arguments=frame;
    std::string display;
    if(chinese) {
        // <Y>es / <N>o retain their highlighted ASCII shortcut; the same
        // complete label feeds native drawing, textwidth and hit geometry.
        const auto* original=reinterpret_cast<const char*>(frame.rcx);
        display=std::string(original,3)+scenario_confirmation_text(last ? "no" : "yes");
        arguments.rcx=reinterpret_cast<std::uintptr_t>(display.c_str());
    }
    frame.rax=call(arguments,0xf4f50);
    if(last) {
        scenario_confirmation_refresh=false;
        scenario_confirmation_chinese=chinese;
        if(rebuilding_scenario_confirmation)
            frame.resume=reinterpret_cast<std::uintptr_t>(uwcn_linux_redraw_scenario_return);
    }
}
void scenario_confirmation_input_return(std::uintptr_t caller) {
    // LIST_Go's original caller, including a page opened before hot reload.
    // The 1CFD0 call stays unhooked, preserving its native return identity.
    if(caller==host->image_base+0x1cfd5 &&
       (scenario_confirmation_refresh || scenario_confirmation_chinese!=chinese)) {
        const auto selection=native<int (*)()>(0xf6100)();
        rebuilding_scenario_confirmation=true;
        // 1CEFC..1CF7E reads/draws the story and builds native controls only.
        // It excludes story creation, the input wait and selection handling.
        uwcn_linux_redraw_scenario_fragment(host->image_base+0x1cefc);
        rebuilding_scenario_confirmation=false;
        native<void (*)(int)>(0xf6110)(selection);
        native<void (*)()>(0x13d5a0)();
        native<void (*)(int,int)>(0xf3f80)(selection,0);
        native<void (*)()>(0x13fe50)();
    }
}
void install_scenario_confirmation() {
    hooks->instruction(0x1cf17,5,scenario_confirmation_question);
    hooks->instruction(0x1cf5e,5,scenario_confirmation_button);
    hooks->instruction(0x1cf79,5,scenario_confirmation_button);
}
