// Remaining direct buffer operands in the >=4D0000 shared-message audit.
// These observe the completed native selection or its immediate copy;
// there are no additional construction frames or serialized state fields.
namespace windows_message_late_sources {
enum Hook:u32 { terrain_copy=0xfa00,herbal_bits,network_input };
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;using native_name_input::native_call;
    // 494BC0's actual return is copied into EBP-40C before 508627.
    hooks.push_back(instruction(terrain_copy,0x108602,{0x8d,0x95,0xf4,0xfb,0xff,0xff}));
    hooks.push_back(native_call(herbal_bits,0xd8cab,0xf6510,0));
    hooks.push_back(native_call(network_input,0xd32bd,0xf6510,0));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=terrain_copy && event.id<=network_input;
    if(!handled)return Status::ok;
    if(event.id==terrain_copy) {
        if(event.phase!=NativePhase::inline_before)return Status::ok;
        const auto* native=ptr<char>(event.frame->eax);
        message_bind_copy(ptr<char>(event.frame->ebp-0x40c),native,message_source_bound(native));
        return Status::ok;
    }
    if(event.phase!=NativePhase::before)return Status::ok;
    const auto* native=ptr<char>(event.frame->ecx);
    if(event.id==herbal_bits) {
        // 4D8C3C/4D8C59 copy the 15-byte label; 4D8C66..4D8CA3 appends
        // the 32 actual binary digits, without natural-language operands.
        message_bind_source(native,native_message_source::concat({
            message_source_lookup("message.debug.label",at<char>(0x1a578c)),
            message_source_identity(native+15)}));
    } else {
        // 581520 receives external UDP bytes, copied by 4D1CA0's caller
        // into 6354DF8. 4D2720 echoes the unmatched bracketed input;
        // these are original protocol/user data, not generated prose.
        message_bind_source(native,message_source_identity(native));
    }
    return Status::ok;
}
}
