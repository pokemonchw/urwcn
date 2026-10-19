// PE 3.89: the actual terrain-entry and eating-message append boundaries.
// Native code has already selected both operands. No gameplay condition is
// re-evaluated, and every original English copy/append still executes.
namespace windows_message_appended {
enum Hook:u32 { terrain_look=0xeb00,terrain_encounter,eating_copy,eating_append };
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    hooks.push_back(instruction(terrain_look,0x2dffc,{0xb9,0x09,0,0,0}));
    hooks.push_back(instruction(terrain_encounter,0x2e01c,{0xb9,0x06,0,0,0}));
    hooks.push_back(instruction(eating_copy,0x35336,{0x8d,0x94,0x24,0x08,0x06,0,0}));
    hooks.push_back(instruction(eating_append,0x35619,{0x8b,0xca,0xc1,0xe9,0x02}));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=terrain_look && event.id<=eating_append;
    if(!handled || event.phase!=NativePhase::inline_before) return Status::ok;
    if(event.id==eating_copy) {
        const auto* source=ptr<char>(event.frame->eax);
        message_bind_copy(ptr<char>(event.frame->esp+0x608),source,message_source_bound(source));
        return Status::ok;
    }
    const auto* body=ptr<char>(event.id==eating_append ? event.frame->esp+0x608 : event.frame->ebp-0x4d8);
    const auto* suffix=event.id==eating_append ? ptr<char>(event.frame->esi) :
        at<char>(event.id==terrain_look ? 0x19280c : 0x192834);
    auto ending=event.id==eating_append ? message_source_lookup("eating-suffix",suffix) :
        message_source_bound(suffix);
    auto source=native_message_source::concat({message_source_bound(body),std::move(ending)});
    // The following native instructions append exactly these English bytes,
    // including their NUL, with no intervening call. Bind their resulting
    // identity now; no translated snapshot or unfinished append frame exists.
    const std::string original=std::string(body)+suffix;
    message_bind_copy(body,original.c_str(),std::move(source));
    return Status::ok;
}
}
