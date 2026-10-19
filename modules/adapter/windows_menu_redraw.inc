// UrW_Start's complete original background fragment. Its startup assignments
// do not belong to a language redraw; the actual native drawing calls do.
enum WindowsMenuBackgroundHook : u32 {
    wb_character_state=0x7500,wb_start_state,wb_no_present,wb_present,
    wb_background_call,wb_cache_retire
};
Status dispatch_windows_menu_background(const NativeEvent& e,DispatchResult& result,bool& handled) {
    handled=true;
    switch(e.id) {
    case wb_character_state:case wb_start_state:case wb_no_present:case wb_present:
        if(rebuilding_main_background) result.resume_rva=
            e.id==wb_character_state ? 0x125ABE : e.id==wb_start_state ? 0x125ACA :
            e.id==wb_no_present ? 0x125AD9 : 0x125AEB;
        return Status::ok;
    case wb_background_call:case wb_cache_retire:return Status::ok;
    default:handled=false;return Status::ok;
    }
}
void append_windows_menu_background_hooks(std::vector<HookSpec>& hooks) {
    constexpr u32 sites[]{0x125AB4,0x125AC0,0x125ACF,0x125AE1};
    constexpr u32 globals[]{0xA2D0BC4,0x1E2C94,0x61BBA5C,0x61BBA5C};
    for(u32 i=0;i<std::size(sites);++i) {
        auto spec=inline_hook(wb_character_state+i,sites[i],{0xC7,0x05,0,0,0,0,0,0,0,0});
        const auto destination=address(at<void>(globals[i]));
        std::memcpy(spec.expected+2,&destination,4);
        spec.expected[6]=(i==1 || i==2) ? 1 : 0;
        hooks.push_back(spec);
    }
    hooks.push_back(call(wb_background_call,0x125AD9,0x1127C0,5));
    hooks.push_back(call(wb_cache_retire,0x125AF0,0x10B250,0));
}
