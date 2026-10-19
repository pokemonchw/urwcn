// 4E9320's three fixed incantations, observed only at their actual shared-
// message calls. The native function selects the ritual, constructs each
// complete line and controls its order, quotes and waiting behaviour.
namespace windows_message_prayers {
enum Hook:u32 { introduction=0xea00,verse };
void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(native_name_input::native_call(introduction,0xe9900,0xf6510,0));
    hooks.push_back(native_name_input::native_call(verse,0xe9a30,0xf6510,0));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id==introduction || event.id==verse;
    if(!handled || event.phase!=NativePhase::before)return Status::ok;
    const auto* owner=ptr<char>(event.frame->ecx);
    message_bind_source(owner,message_source_lookup("prayer.message",owner));
    return Status::ok;
}
}
