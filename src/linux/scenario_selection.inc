// Linux 3.89 SelectCampaign. RNDCAMP files, scenario indices, LIST_SpotEntry
// geometry and input remain native; only the confirmed display calls borrow text.
std::string scenario_selection_text(const std::string& key) {
    return translated(C::scenario_selection_text,"",key.c_str());
}

bool scenario_selection_refresh=true;
bool scenario_selection_chinese;
bool rebuilding_scenario_selection;

void scenario_selection_title(Frame& frame) {
    Frame arguments=frame;
    std::string display;
    if(chinese) {
        display=scenario_selection_text("title");
        arguments.rdi=reinterpret_cast<std::uintptr_t>(display.c_str());
    }
    frame.rax=call(arguments,0x1d030);
}
void scenario_selection_name(Frame& frame) {
    Frame arguments=frame;
    std::string display;
    if(chinese) {
        // R12D is the native RNDCAMP file index, incremented at 1D20B
        // before reading its title. It identifies source records, not UI rows.
        display=scenario_selection_text("name."+std::to_string(static_cast<u32>(frame.r12)-1));
        arguments.rdx=reinterpret_cast<std::uintptr_t>(display.c_str());
    }
    frame.rax=call(arguments,0x13e8b0);
}
void scenario_selection_paragraph(Frame& frame) {
    Frame arguments=frame;
    std::string words;
    if(chinese) {
        const auto site=frame.resume-host->image_base-5;
        const auto key=site==0x1d271 ? "summary."+std::to_string(static_cast<u32>(frame.r12)-1) :
            std::string(site==0x1d2f5 ? "help.1" : "help.2");
        words=native_paragraph_words(scenario_selection_text(key));
        arguments.rsi=reinterpret_cast<std::uintptr_t>(words.c_str());
    }
    // Preserve the native reset/append flag and all native word-table ownership.
    frame.rax=call(arguments,0x1afe00);
}
void scenario_selection_footer_random(Frame& frame) {
    // crtplr_info(0) ignores random(20)'s result. Its original call remains
    // on normal entry; a pure redraw must not consume another random value.
    if(!rebuilding_scenario_selection) frame.rax=call(frame,0xf4870);
}
void scenario_selection_footer(Frame& frame) {
    frame.rax=call(frame,0x1bbf0);
    scenario_selection_refresh=false;
    scenario_selection_chinese=chinese;
    // SelectCampaign's original frame/canary epilogue; skip its input loop,
    // selected-scenario write and get_camp story-file generation on redraw.
    if(rebuilding_scenario_selection) frame.resume=host->image_base+0x1d332;
}
void scenario_selection_input_return(Frame& frame) {
    // LIST_Go saves six registers and allocates 0x428 bytes. Its original
    // caller at [RSP+0x458] also identifies a page opened before this reload.
    // Keep 1D360 -> LIST_Go unhooked so that native return identity is stable.
    const auto caller=*reinterpret_cast<const std::uintptr_t*>(frame.stack()+0x458);
    scenario_confirmation_input_return(caller);
    if(caller==host->image_base+0x1d365 &&
       (scenario_selection_refresh || scenario_selection_chinese!=chinese)) {
        const auto selection=native<int (*)()>(0xf6100)();
        rebuilding_scenario_selection=true;
        native<const char* (*)()>(0x1d100)();
        rebuilding_scenario_selection=false;
        native<void (*)(int)>(0xf6110)(selection);
        // Same native cache-before-highlight order as LIST_Go F866B/F8700.
        native<void (*)()>(0x13d5a0)();
        native<void (*)(int,int)>(0xf3f80)(selection,0);
        native<void (*)()>(0x13fe50)();
    }
    frame.rsi=1; // Covered F871F MOV ESI,1; RAX keeps the actual input result.
}
void install_scenario_selection() {
    hooks->instruction(0x1d17b,5,scenario_selection_title);
    hooks->instruction(0x1d23a,5,scenario_selection_name);
    for(auto site:{0x1d271u,0x1d2f5u,0x1d303u})
        hooks->instruction(site,5,scenario_selection_paragraph);
    hooks->instruction(0x1bbfc,5,scenario_selection_footer_random);
    hooks->instruction(0x1d30a,5,scenario_selection_footer);
    hooks->instruction(0xf871f,5,scenario_selection_input_return);
}
