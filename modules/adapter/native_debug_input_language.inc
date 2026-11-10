// These native debug prefixes and the qlogger 0/1 input already use zero as
// their idle result. A consumed language action must not become a prefix key.
namespace native_debug_input_language {
enum Hook:u32 { prefix_first=0x5280,prefix_second,prefix_third,logger_first,logger_second };
void append_hooks(std::vector<HookSpec>& hooks) {
    for(const auto [id,site]:{std::pair{prefix_first,0x16FE50u},std::pair{prefix_second,0x16FE62u},
            std::pair{prefix_third,0x16FE74u},std::pair{logger_first,0x175248u},
            std::pair{logger_second,0x175251u}})
        hooks.push_back(call(id,site,0xD3BF0,0));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=prefix_first && event.id<=logger_second;
    if(!handled || event.phase!=NativePhase::after || event.frame->eax!=static_cast<u32>(-2) ||
       !native_language_redraw::pending(native_language_redraw::View::hud)) return Status::ok;
    const auto status=native_parent_cache_language::game_parent();
    if(status!=Status::ok) return status;
    native_language_redraw::completed(native_language_redraw::View::hud);
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x10B720)();
    event.frame->eax=0;
    return Status::ok;
}
}
