// PE 3.89: two resource alternatives converge with a copied fixed literal
// at 44CB1F. The separate 44CB93 printf branch instead reaches 44CBAA.
namespace windows_message_audit_copies {
enum Hook:u32 { plant_growing=0xf800,plant_status };
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    for(const auto pair:{std::pair<u32,u32>{plant_growing,0x4cabe},
                         {plant_status,0x4cb4d}})
        hooks.push_back(instruction(pair.first,pair.second,{0x8d,0x95,0xf8,0xfb,0xff,0xff}));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id==plant_growing || event.id==plant_status;
    if(!handled || event.phase!=NativePhase::inline_before)return Status::ok;
    const auto* selected=ptr<char>(event.frame->ecx);
    message_bind_copy(ptr<char>(event.frame->ebp-0x408),selected,message_source_bound(selected));
    return Status::ok;
}
}
