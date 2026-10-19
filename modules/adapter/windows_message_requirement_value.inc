// 464730 builds the selected craft requirement for 46522E -> 4F6510.
// Sources: settlement-carcass-descriptor-ghidra.c and
// settlement-material-requirement-helper-ghidra.c. The native sprintf,
// append and selected-row copy remain responsible for every branch.
enum RequirementHook:u32 {requirement_of_count=0xc950,requirement_or,
    requirement_or_name,requirement_by_hand,requirement_selected,
    requirement_need,requirement_optional,requirement_subject,
    requirement_period,requirement_suffix,requirement_name_first,
    requirement_name_second,requirement_trees_begin,requirement_tree_append,
    requirement_trees_copy};
void append_requirement_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    const auto literal=[&](u32 id,u32 site,u32 source) {
        auto hook=instruction(id,site,{0xa1,0,0,0,0});
        const auto absolute=address(at<char>(source));std::memcpy(hook.expected+1,&absolute,4);hooks.push_back(hook);
    };
    hooks.push_back(instruction(requirement_of_count,0x64b68,{0x8b,0xca,0xc1,0xe9,0x02}));
    literal(requirement_or,0x64d3a,0x19a108);
    hooks.push_back(instruction(requirement_or_name,0x64d6e,{0x8b,0xca,0xc1,0xe9,0x02}));
    literal(requirement_by_hand,0x64f72,0x19a130);
    // The backedge enters the complete MOV; only ECX == 0 starts the copy.
    hooks.push_back(instruction(requirement_selected,0x64fb4,{0x8a,0x84,0x0d,0xf8,0xfb,0xff,0xff}));
    literal(requirement_need,0x65100,0x19a174);
    literal(requirement_optional,0x650ba,0x19a180);
    hooks.push_back(instruction(requirement_subject,0x65140,{0x8b,0xca,0xc1,0xe9,0x02}));
    hooks.push_back(instruction(requirement_period,0x651ee,{0xb8,0x2e,0,0,0}));
    hooks.push_back(instruction(requirement_suffix,0x6521a,{0x8b,0xca,0xc1,0xe9,0x02}));
    hooks.push_back(native_name_input::native_call(requirement_name_first,0x64cd8,0x6c8b0,0));
    hooks.push_back(native_name_input::native_call(requirement_name_second,0x65160,0x6c8b0,0));
    hooks.push_back(instruction(requirement_trees_begin,0x15e420,{0x89,0x85,0xf8,0xfb,0xff,0xff}));
    hooks.push_back(instruction(requirement_tree_append,0x15e44d,{0x8b,0xca,0x8d,0x85,0xfc,0xfb,0xff,0xff}));
    hooks.push_back(instruction(requirement_trees_copy,0x15e4a4,{0x8b,0xb5,0xf0,0xfb,0xff,0xff}));
}
Status dispatch_requirement(const NativeEvent& event,bool& handled) {
    handled=event.id>=requirement_of_count && event.id<=requirement_trees_copy;
    if(!handled) return Status::ok;
    if(event.id==requirement_name_first || event.id==requirement_name_second) {
        if(event.phase==NativePhase::after) {
            const auto* owner=ptr<char>(event.frame->eax);
            message_bind_source(owner,message_source_lookup("craft-requirement",owner));
        }
        return Status::ok;
    }
    if(event.phase!=NativePhase::inline_before) return Status::ok;
    const auto frame=event.frame->ebp;
    if(event.id==requirement_selected) {
        if(event.frame->ecx==0) {
            const auto* row=ptr<char>(frame-0x408);
            message_bind_copy(ptr<char>(frame-0x7f8),row,message_source_bound(row));
        }
        return Status::ok;
    }
    if(event.id==requirement_trees_begin) {
        message_bind_source(ptr<char>(frame-0x404),native_message_source::concat({}));return Status::ok;
    }
    if(event.id==requirement_trees_copy) {
        const auto* input=ptr<char>(event.frame->eax);
        message_bind_copy(ptr<char>(*ptr<u32>(frame-0x410)),input,message_source_bound(input));return Status::ok;
    }
    if(event.id==requirement_period) {
        message_bind_copy(ptr<char>(frame-0x600),".",message_source_lookup("requirement-msg","."));return Status::ok;
    }
    const auto* owner=ptr<char>(frame-(event.id==requirement_tree_append ? 0x404 : 0x408));
    const char* addition=nullptr;MessageText part;
    switch(event.id) {
    case requirement_or:addition=at<char>(0x19a108);break;
    case requirement_by_hand:addition=at<char>(0x19a130);break;
    case requirement_need:addition=at<char>(0x19a174);break;
    case requirement_optional:addition=at<char>(0x19a180);break;
    default:addition=ptr<char>(event.frame->esi);part=message_source_bound(addition);break;
    }
    if(event.id==requirement_or || event.id==requirement_by_hand ||
       event.id==requirement_need || event.id==requirement_optional)
        part=message_source_lookup("requirement-msg",addition);
    auto prior=message_source_bound(owner);
    std::string original=std::string(owner)+addition;
    if(event.id==requirement_tree_append) {
        // 55E46C appends the literal comma immediately after this same copy.
        // Keep the actual selected tree nodes flat for 562930's list grammar.
        auto parts=std::move(prior.children);parts.push_back(std::move(part));
        parts.push_back(native_message_source::original(", "));original+=", ";
        message_bind_copy(owner,original.c_str(),native_message_source::concat(std::move(parts)));
    } else message_bind_copy(owner,original.c_str(),native_message_source::concat({std::move(prior),std::move(part)}));
    return Status::ok;
}
