// 56FE30 shared-message operands that are not sprintf products. Each source
// class is established from its actual writer; user input, query tags and
// binary digits remain native data. No debug action is repeated here.
namespace windows_message_debug_sources {
enum Hook:u32 { input=0xf600,query_first,query_second,herbal,plant,
    creature_record,bits32,bits16,protection,direction_copy,distance_copy };
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::native_call;using native_name_input::instruction;
    const u32 calls[]={0x1701a9,0x17288e,0x172aee,0x173eee,0x177d8e,
        0x178e69,0x179ba9,0x179c7a,0x17c584};
    for(u32 i=0;i<std::size(calls);++i)hooks.push_back(native_call(input+i,calls[i],
        input+i==creature_record ? 0xf56a0 : 0xf6510,input+i==creature_record ? 2 : 0));
    hooks.push_back(instruction(direction_copy,0x1730e4,{0x8d,0x94,0x24,0x34,0x0b,0x02,0x00}));
    hooks.push_back(instruction(distance_copy,0x176c19,{0x8b,0xf1,0x2b,0xf0,0x0f,0x1f,0x00}));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=input && event.id<=distance_copy;
    if(!handled)return Status::ok;
    if(event.id==direction_copy || event.id==distance_copy) {
        if(event.phase!=NativePhase::inline_before)return Status::ok;
        const auto* source=ptr<char>(event.frame->eax);
        const auto destination=event.id==direction_copy ? event.frame->esp+0x20b34 : event.frame->ecx;
        message_bind_copy(ptr<char>(destination),source,message_source_bound(source));
        return Status::ok;
    }
    if(event.id==creature_record) {
        if(event.phase!=NativePhase::after)return Status::ok;
        const auto* native=ptr<char>(event.arguments[1]+8);
        // 4F56F4 writes the actual record (including its native empty case).
        // 4F5736 returns zero without writing it; the debug caller still
        // prints those prior stack bytes. Preserve that raw diagnostic data
        // instead of assigning the unwritten bytes a creature-name meaning.
        message_bind_source(native,event.frame->eax!=0 ? message_source_value("npc",native) :
            message_source_identity(native));
        return Status::ok;
    }
    if(event.phase!=NativePhase::before)return Status::ok;
    const auto* native=ptr<char>(event.frame->ecx);
    MessageText source;
    switch(event.id) {
    case herbal:source=message_source_value("herbal.effect",native);break;
    case plant:source=message_source_value("item",native);break;
    case protection:
        // 57C420/57C42E write the five-byte literal "prot:"; the three
        // following loops append only 0/1 digits and native separators.
        source=native_message_source::concat({message_source_lookup("debug.label","prot:"),
            message_source_identity(native+5)});break;
    default:source=message_source_identity(native);break;
    }
    message_bind_source(native,std::move(source));return Status::ok;
}
}
