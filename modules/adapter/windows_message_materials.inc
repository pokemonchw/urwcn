// PE 3.89 material names used by 4367E0 and 46D3E0. These observers follow
// actual native branches and copies; descriptors and naming modes stay English.
namespace windows_message_materials {
enum Hook:u32 { base=0xe800,unknown,flora,full_name,material,
    special_item,unknown_item,meat_cut,original_name,last_word,first_word };
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    auto absolute=[&](u32 id,u32 site,std::initializer_list<unsigned char> bytes,
                      u32 offset,u32 rva) {
        auto hook=instruction(id,site,bytes);const auto value=address(at<char>(rva));
        std::memcpy(hook.expected+offset,&value,4);hooks.push_back(hook);
    };
    hooks.push_back(instruction(base,0x516a1,{0x80,0xbd,0x50,0xff,0xff,0xff,0x0b}));
    absolute(unknown,0x516f8,{0xa1,0,0,0,0},1,0x1940d4);
    absolute(flora,0x5173d,{0xba,0,0,0,0},1,0xa489a28);
    hooks.push_back(instruction(full_name,0x67aad,{0x8d,0x95,0xf4,0xfb,0xff,0xff}));
    absolute(material,0x67ae7,{0xba,0,0,0,0},1,0x1d30878);
    // Use the loop head itself: its backward branch must still reach a hook
    // boundary, not an overwritten instruction inside a larger hook span.
    hooks.push_back(instruction(special_item,0x67b10,{0x8a,0x84,0x0d,0xf4,0xfb,0xff,0xff}));
    hooks.push_back(instruction(unknown_item,0x67b61,{0x33,0xc9,0x0f,0x1f,0x40,0}));
    // 467BE4 is a shared branch target, so observe the preceding complete
    // indirect call rather than spanning its three-byte stack cleanup.
    absolute(meat_cut,0x67bdb,{0xff,0x15,0,0,0,0},2,0x18c4f0);
    hooks.push_back(instruction(original_name,0x67be9,{0x33,0xd2,0x0f,0x1f,0x44,0,0}));
    absolute(last_word,0x67c16,{0xba,0,0,0,0},1,0x1d30878);
    absolute(first_word,0x67c3f,{0xba,0,0,0,0},1,0x1d30878);
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=base && event.id<=first_word;
    if(!handled || event.phase!=NativePhase::inline_before)return Status::ok;
    const auto* result=ptr<char>(event.frame->eax);
    switch(event.id) {
    case base:
        message_bind_source(at<char>(0xa489a28),message_source_lookup("material.field",at<char>(0xa489a28)));break;
    case unknown:
        message_bind_copy(at<char>(0xa489a28),at<char>(0x1940d4),message_source_lookup("material.field",at<char>(0x1940d4)));break;
    case flora:
        message_bind_copy(at<char>(0xa489a28),result,message_source_bound(result));break;
    case full_name:
        message_bind_copy(ptr<char>(event.frame->ebp-0x40c),result,message_source_bound(result));break;
    case material:
        message_bind_copy(at<char>(0x1d30878),result,message_source_bound(result));break;
    case special_item:case unknown_item:case original_name: {
        if(event.id==special_item && event.frame->ecx!=0)break;
        const auto* full=ptr<char>(event.frame->ebp-0x40c);
        message_bind_copy(at<char>(0x1d30878),full,message_source_bound(full));break;
    }
    case meat_cut: {
        // The native length is exactly strstr(full," cut")-full, therefore
        // strncpy copies this prefix without adding a terminator. Preserve
        // the old material tail in the source identity of the pending copy.
        auto* destination=ptr<char>(*ptr<u32>(event.frame->esp));
        const auto* source=ptr<char>(*ptr<u32>(event.frame->esp+4));
        const auto length=*ptr<u32>(event.frame->esp+8);
        const std::string prefix(source,length);
        const std::string native=prefix+std::string(destination+length);
        auto selected=native_message_source::concat({message_source_lookup("material.cut",prefix.c_str())});
        message_bind_copy(destination,native.c_str(),std::move(selected));break;
    }
    case last_word:case first_word:
        // 4D4140/4D4190 have already selected the actual English word.
        message_bind_copy(at<char>(0x1d30878),result,message_source_lookup("material.word",result));break;
    }
    return Status::ok;
}
}
