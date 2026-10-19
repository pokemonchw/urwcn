// Native aggregate expressions. These preserve the selected source arguments,
// not token positions, measured widths or the native word-cache contents.
enum ChainHook:u32 {corpse_injury_append=0xc800,corpse_age_append,corpse_burn_append,
    corpse_details_prefix,corpse_skinned,corpse_part_skinned,list_added,list_incremented,
    count_item,count_and,count_comma,count_more_plural,count_more_single,
    trap_copy,article_copy,injury_copy,craft_plain_copy,flora_status_capture,flora_format,
    profile_begin,profile_diving,profile_escortee,message_wrapper,
    receipt_single_copy,receipt_many_copy,receipt_single_copy2,receipt_many_copy2,
    receipt_append,receipt_append2,receipt_appended,receipt_appended2,
    injury_label_noun,injury_label_side};
constexpr u32 first_part=0xc840;
struct PartCall {u32 site,target;};
const PartCall part_calls[]={
    {0x40e5a,0x162300},{0xae2ab,0x162300},{0xae2d3,0x162300},{0xae2f4,0x162300},
    {0xae315,0x162300},{0xae32e,0x162300},{0xae35b,0x162300},{0xae39e,0x162300},
    {0x40e78,0x161e90},{0xae33a,0x161e90}
};
struct Copy {u32 hook,owner;MessageText text;};
std::vector<Copy> copies;
MessageText join_text(MessageText left,MessageText right,const char* separator="") {
    return native_message_source::concat({std::move(left),native_message_source::original(separator),std::move(right)});
}
MessageText list_separator(const char* separator) {return message_source_lookup("list",separator);}
void observe_chain_value(u32 site,u32,const char*,const MessageText& text) {
    if(pending.empty()) return;
    auto& call=pending.back();
    if(call.kind==Kind::corpse) {
        if(site==0xae7d8) call.detail=text;
        else if(site==0xae81b) call.text=text;
        else if(site==0xaeaff || site==0xaeb85) call.text=join_text(call.text,text);
    }
    if(call.kind==Kind::craft && call.input=="list" && site==0x40f87) call.text=join_text(call.text,text," ");
    if(call.kind==Kind::flora && site==0x3665) call.detail=join_text(call.detail,text);
}
void capture_copy(const Site& site,const NativeEvent& event,const MessageText& text) {
    if(site.site==0x63a3) copies.push_back({trap_copy,event.frame->ebp-0x70,text});
    else if(site.site==0x6964) copies.push_back({article_copy,event.frame->ebp-0x13c,text});
    else if(site.site==0xd8c15) copies.push_back({injury_copy,event.frame->ebp-0x70,text});
}
void prepare_chain_call(Pending& call,const Site& site,const NativeEvent&) {
    if(call.kind==Kind::list_add || call.kind==Kind::comma_list || call.kind==Kind::or_list) {
        call.input=ptr<char>(call.ecx);call.text=source("bound",ptr<char>(call.ecx));
    }
}
void collect_list_parts(const MessageText& text,std::vector<MessageText>& parts) {
    // 5627A0 callers bind the actual append sequence as concat(item, ", ", ...).
    if(text.kind==native_message_source::Kind::concat) {
        std::vector<MessageText> item;
        for(const auto& child:text.children) {
            if(child.kind==native_message_source::Kind::original && child.original==", ") {
                parts.push_back(native_message_source::concat(std::move(item)));item.clear();
            } else item.push_back(child);
        }
        if(!item.empty()) parts.push_back(native_message_source::concat(std::move(item)));
    } else if(!text.original.empty()) parts.push_back(text);
}
MessageText comma_list_source(const Pending& call,const char* original) {
    if(call.input.size()>1000) return message_source_lookup("list","text buffer overflow");
    std::vector<MessageText> parts;collect_list_parts(call.text,parts);std::vector<MessageText> result;
    for(std::size_t i=0;i<parts.size();++i) {
        if(i) result.push_back(list_separator(i+1==parts.size() ? (call.kind==Kind::or_list ? " or ":" and "):", "));
        result.push_back(parts[i]);
    }
    auto text=native_message_source::concat(std::move(result));text.original=message_source_utf8(original);return text;
}
void selected_part(Pending& call,u32 site,const char* original) {
    auto text=site==0xae35b && std::strcmp(original,"(diving)")==0 ?
        message_source_lookup("corpse",original):source("bound",original);
    const auto length=std::strlen(original);const bool comma=length && original[length-1]==',';
    if(comma) {
        // Both recovered producers append a comma through these exact formats.
        if(site==0x40e5a)
            text=native_message_source::format(message_source_lookup("list","%u %s"),
                {text.children[1],text.children[2]},{"%u","%s"});
        else text=text.children[1];
    }
    if(call.input=="normalized") call.text=join_text(call.text,text," ");
    else call.parts.push_back({std::move(text),comma});
    if(call.kind==Kind::profile && call.input.empty()) call.input="normal";
    if(call.kind==Kind::craft) call.input="list";
}
void normalize_parts(Pending& call,u32 threshold) {
    std::size_t count=0,last=0,previous=0;
    for(std::size_t i=0;i<call.parts.size();++i) if(call.parts[i].comma) {previous=last;last=i;++count;}
    std::vector<MessageText> parts;
    for(std::size_t i=0;i<call.parts.size();++i) {
        if(i) parts.push_back(native_message_source::original(" "));
        parts.push_back(call.parts[i].text);
        if(call.parts[i].comma && i!=last)
            parts.push_back(list_separator(count>=threshold && i==previous ? " and":","));
    }
    call.text=native_message_source::concat(std::move(parts));call.parts.clear();
    call.input=call.kind==Kind::craft ? "list":"normalized";
}
void append_chain_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;using native_name_input::native_call;
    for(u32 i=0;i<sizeof(part_calls)/sizeof(part_calls[0]);++i)
        hooks.push_back(native_call(first_part+i,part_calls[i].site,part_calls[i].target,0));
    hooks.push_back(instruction(corpse_injury_append,0xae8f1,{0x8d,0x94,0x24,0xd0,0x0b,0,0}));
    hooks.push_back(instruction(corpse_age_append,0xae99d,{0x8d,0x94,0x24,0xd0,0x0b,0,0}));
    hooks.push_back(instruction(corpse_burn_append,0xaea09,{0x8d,0x54,0x24,0x30,0x8b,0xf2}));
    hooks.push_back(instruction(corpse_details_prefix,0xaea99,{0x8d,0x8c,0x24,0x68,0x0b,0,0}));
    const auto absolute=[&](u32 id,u32 site,std::initializer_list<unsigned char> bytes,u32 offset,u32 rva) {
        auto hook=instruction(id,site,bytes);const auto value=address(at<char>(rva));
        std::memcpy(hook.expected+offset,&value,4);hooks.push_back(hook);
    };
    absolute(corpse_skinned,0xaec01,{0x8b,0x0d,0,0,0,0},2,0x1a0534);
    absolute(corpse_part_skinned,0xaec6a,{0xa1,0,0,0,0},1,0x1a0540);
    absolute(list_added,0x162eaf,{0xc7,0x04,0x9d,0,0,0,0,1,0,0,0},3,0xa2d0898);
    absolute(list_incremented,0x162ebf,{0xff,0x04,0x9d,0,0,0,0},3,0xa2d0898);
    hooks.push_back(instruction(count_item,0x163046,{0x8b,0xb5,0xf4,0xfb,0xff,0xff}));
    absolute(count_and,0x16308a,{0xa1,0,0,0,0},1,0x192c74);
    absolute(count_comma,0x1630c0,{0x66,0xa1,0,0,0,0},2,0x19149c);
    absolute(count_more_plural,0x16311a,{0x8b,0x0d,0,0,0,0},2,0x1d8288);
    absolute(count_more_single,0x16315a,{0xa1,0,0,0,0},1,0x1d8288);
    hooks.push_back(native_call(trap_copy,0x63c6,0x62d0,0));
    hooks.push_back(instruction(article_copy,0x697e,{0x8d,0x85,0xc4,0xfe,0xff,0xff}));
    absolute(injury_copy,0xd8c2e,{0x83,0x3d,0,0,0,0,0},2,0xa2d28a0);
    hooks.push_back(native_call(craft_plain_copy,0x40cac,0x10d0,2));
    absolute(flora_status_capture,0x3794,{0xa1,0,0,0,0},1,0x551525c);
    hooks.push_back(native_call(flora_format,0x37c6,0x10d0,2));
    absolute(message_wrapper,0xf6f70,{0xba,0,0,0,0},1,0x61a8cf8);
    hooks.push_back(instruction(receipt_single_copy,0x2fa13,{0x8d,0x95,0xf4,0xfb,0xff,0xff}));
    hooks.push_back(instruction(receipt_many_copy,0x2fa36,{0x8d,0x95,0xf4,0xfb,0xff,0xff}));
    hooks.push_back(instruction(receipt_single_copy2,0x2fe03,{0x8d,0x95,0xf4,0xfb,0xff,0xff}));
    hooks.push_back(instruction(receipt_many_copy2,0x2fe26,{0x8d,0x95,0xf4,0xfb,0xff,0xff}));
    hooks.push_back(instruction(receipt_append,0x2fa4e,{0x8d,0x95,0xf4,0xfb,0xff,0xff}));
    hooks.push_back(instruction(receipt_append2,0x2fe3e,{0x8d,0x95,0xf4,0xfb,0xff,0xff}));
    hooks.push_back(instruction(receipt_appended,0x2fab7,{0xb9,1,0,0,0}));
    hooks.push_back(instruction(receipt_appended2,0x2fea7,{0xb9,1,0,0,0}));
    absolute(injury_label_noun,0xd5054,{0xbf,0,0,0,0},1,0x5f5cbb8);
    hooks.push_back(instruction(injury_label_side,0xd50cb,{0x83,0xca,0xff,0x8b,0xcb}));
}
Status dispatch_chain(const NativeEvent& event,bool& handled) {
    handled=(event.id>=corpse_injury_append && event.id<=flora_format) ||
        (event.id>=message_wrapper && event.id<=injury_label_side) ||
        (event.id>=first_part && event.id<first_part+sizeof(part_calls)/sizeof(part_calls[0]));
    if(!handled) return Status::ok;
    if(event.id==craft_plain_copy || event.id==flora_format) {
        if(event.phase==NativePhase::before)
            copies.push_back({event.id,event.arguments[0],source("bound",ptr<char>(event.arguments[1]))});
        else {auto copy=std::move(copies.back());copies.pop_back();copy.text.original=message_source_utf8(ptr<char>(copy.owner));message_bind_source(ptr<char>(copy.owner),copy.text);
            observe_value(event.id==craft_plain_copy ? 0x40cac:0x37c6,
                event.id==craft_plain_copy ? 0x40b20:0x3550,ptr<char>(copy.owner),copy.text);}
        return Status::ok;
    }
    if(event.phase==NativePhase::after) return Status::ok;
    if(event.id==message_wrapper) {
        const auto* input=ptr<char>(event.frame->ecx);
        message_bind_copy(at<char>(0x61a8cf8),input,source("bound",input));return Status::ok;
    }
    if(event.id>=receipt_single_copy && event.id<=receipt_many_copy2) {
        const auto* input=ptr<char>(event.frame->eax);
        message_bind_copy(ptr<char>(event.frame->ebp-0x40c),input,source("bound",input));return Status::ok;
    }
    if(event.id==receipt_append || event.id==receipt_append2) {
        const auto* destination=ptr<char>(event.frame->ebp-0x80c);
        std::vector<MessageText> parts;
        // The native function initializes this exact accumulator to empty before
        // the receipt loop; subsequent iterations have the preceding append graph.
        if(*destination) parts=source("bound",destination).children;
        parts.push_back(source("bound",ptr<char>(event.frame->ebp-0x40c)));
        parts.push_back(native_message_source::original(", "));
        copies.push_back({event.id,event.frame->ebp-0x80c,native_message_source::concat(std::move(parts))});
        return Status::ok;
    }
    if(event.id==receipt_appended || event.id==receipt_appended2) {
        auto copy=std::move(copies.back());copies.pop_back();
        message_bind_source(ptr<char>(copy.owner),std::move(copy.text));return Status::ok;
    }
    if(event.id==trap_copy || event.id==article_copy || event.id==injury_copy) {
        auto copy=std::move(copies.back());copies.pop_back();message_bind_source(ptr<char>(copy.owner),copy.text);return Status::ok;
    }
    auto& call=pending.back();
    if(event.id==injury_label_noun) {
        call.input="compound";call.text=message_source_lookup("injury",at<char>(0x5f5cbb8));return Status::ok;
    }
    if(event.id==injury_label_side) {
        const auto side=*ptr<u32>(event.frame->ebp+0xc);
        call.detail=side==0 ? message_source_lookup("injury","left "):
            side==1 ? message_source_lookup("injury","right "):native_message_source::original("");return Status::ok;
    }
    if(event.id==flora_status_capture) {
        const auto* original=at<char>(0x1e9b08);
        auto text=call.input=="flora-debug" ? call.detail:message_source_lookup("status",original);
        message_bind_source(original,text);observe_value(0x3794,0x3550,original,text);return Status::ok;
    }
    if(event.id>=first_part) {
        const auto& part=part_calls[event.id-first_part];
        if(part.target==0x162300) selected_part(call,part.site,ptr<char>(event.frame->edx));
        else normalize_parts(call,event.frame->edx);
        return Status::ok;
    }
    if(event.id==list_added || event.id==list_incremented) {
        message_bind_source(at<char>(0xa2c4228+event.frame->ebx*100),call.text);return Status::ok;
    }
    if(event.id==count_item) {
        const auto owner=*ptr<u32>(event.frame->ebp-0x40c);
        const auto count=*ptr<u32>(*ptr<u32>(event.frame->ebp-0x408));
        auto item=source("bound",ptr<char>(owner));
        if(count>1) item=native_message_source::format(message_source_lookup("list","%u %s"),
            {native_message_source::scalar(native_message_source::Scalar::unsigned32,count,"%u"),item},{"%u","%s"});
        call.text=join_text(call.text,item);return Status::ok;
    }
    if(event.id==count_and || event.id==count_comma || event.id==count_more_plural || event.id==count_more_single) {
        const char* separator=event.id==count_and ? " and ":event.id==count_comma ? ", ":"and more";
        call.text=join_text(call.text,list_separator(separator));return Status::ok;
    }
    if(event.id==corpse_details_prefix) {
        call.text=join_text(call.detail,call.text," ");return Status::ok;
    }
    if(event.id==corpse_skinned || event.id==corpse_part_skinned) {
        call.text=join_text(call.text,message_source_lookup("corpse",event.id==corpse_skinned ?
            " (skinned)":" (partially skinned)"));return Status::ok;
    }
    const auto* original=ptr<char>(event.frame->esp+(event.id==corpse_burn_append ? 0x30:0xbd0));
    const auto value=source("corpse",original);
    if(call.detail.original.empty()) call.detail=value;
    else call.detail=native_message_source::concat({call.detail,list_separator(", "),value});
    return Status::ok;
}
void save_chains(std::vector<unsigned char>& output) {
    message_state_write(output,static_cast<u32>(copies.size()));
    for(const auto& copy:copies) {message_state_write(output,copy.hook);message_state_write(output,copy.owner);native_message_source::write(output,copy.text);}
}
void restore_chains(const unsigned char*& input) {
    u32 count;message_state_read(input,count);copies.resize(count);
    for(auto& copy:copies) {message_state_read(input,copy.hook);message_state_read(input,copy.owner);copy.text=native_message_source::read(input);}
}
