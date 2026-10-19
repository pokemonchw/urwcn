// Linux 3.89 game_course: complete native display calls. No page geometry,
// task state, English source data or input actions are owned by this adapter.
extern "C" void uwcn_linux_redraw_game_course_fragment(std::uintptr_t);
extern "C" void uwcn_linux_redraw_game_course_return();

bool game_course_refresh=true;
bool game_course_chinese;
bool rebuilding_game_course;

struct GameCourseBinding {
    u32 site,target;
    const char* key;
    unsigned argument;
    unsigned arguments=6;
};
const GameCourseBinding game_course_bindings[]{
    {0x1d618,0x1d030,"title",0},
    {0x1d648,0x1471a0,"title",4,7},
    {0x1d690,0x1afe00,"free.1",1},
    {0x1d69e,0x1afe00,"free.2",1},
    {0x1d6ac,0x1afe00,"free.3",1},
    {0x1d70d,0x1afe00,"wild.1",1},
    {0x1d71b,0x1afe00,"wild.2",1},
    {0x1d729,0x1afe00,"wild.3",1},
    {0x1da26,0x1afe00,"advanced.1",1},
    {0x1da34,0x1afe00,"advanced.2",1},
    {0x1da42,0x1afe00,"advanced.3",1},
    {0x1d7d1,0xf4f50,"name.free",3},
    {0x1d96e,0xf4f50,"name.free",3},
    {0x1d807,0xf4f50,"name.wild",3},
    {0x1d8e6,0xf4f50,"name.tutorial",3},
    {0x1da8e,0xf4f50,"name.advanced",3},
    {0x1d9ad,0x13e8b0,"completed.wild",2},
    {0x1d927,0x13e8b0,"completed.advanced",2},
    {0x1d840,0x1afe00,"help.1",1},
    {0x1d84e,0x1afe00,"help.2",1},
    {0x1d85c,0x1afe00,"help.3",1},
    {0x1d94a,0x1afe00,"help.completed",1},
};
void game_course_display(Frame& frame) {
    const auto site=frame.resume-host->image_base-5;
    for(const auto& binding:game_course_bindings) {
        if(binding.site!=site) continue;
        Frame arguments=frame;
        std::string display;
        if(chinese) {
            display=translated(C::game_course_text,"",binding.key);
            if(binding.target==0x1afe00) display=native_paragraph_words(display);
            if(binding.target==0xf4f50) {
                // Every inspected label uses ESC./A./B. keycap syntax. The
                // complete borrowed label feeds native drawing AND hit width.
                const auto* original=reinterpret_cast<const char*>(frame.rcx);
                display=std::string(original,std::strchr(original,'.')+1)+display;
            }
            argument(arguments,binding.argument)=reinterpret_cast<std::uintptr_t>(display.c_str());
        }
        frame.rax=call(arguments,binding.target,binding.arguments,frame);
        return;
    }
}
void game_course_draw(Frame& frame) {
    frame.rax=call(frame,0xf5570);
    game_course_refresh=false;
    game_course_chinese=chinese;
    // End the display-only fragment before LIST_Go and the A/B/ESC actions.
    if(rebuilding_game_course)
        frame.resume=reinterpret_cast<std::uintptr_t>(uwcn_linux_redraw_game_course_return);
}
void game_course_input_return(std::uintptr_t caller) {
    // LIST_Go's unchanged native return identity includes already-open pages.
    if(caller==host->image_base+0x1d872 &&
       (game_course_refresh || game_course_chinese!=chinese)) {
        const auto selection=native<int (*)()>(0xf6100)();
        rebuilding_game_course=true;
        // Begin after grabscr and the player-name copy. The native background,
        // images, current completion branches, buttons and footer rebuild;
        // the saved pre-page screen and task creation are never re-entered.
        uwcn_linux_redraw_game_course_fragment(host->image_base+0x1d5e3);
        rebuilding_game_course=false;
        native<void (*)(int)>(0xf6110)(selection);
        native<void (*)()>(0x13d5a0)();
        native<void (*)(int,int)>(0xf3f80)(selection,0);
        native<void (*)()>(0x13fe50)();
    }
}
void install_game_course() {
    for(const auto& binding:game_course_bindings)
        hooks->instruction(binding.site,5,game_course_display);
    hooks->instruction(0x1d868,5,game_course_draw);
}
