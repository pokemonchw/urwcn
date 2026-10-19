// Included inside windows_message_values. Every entry is a native construction
// call or a selected native branch, never a second text-layout operation.
constexpr u32 first_format=0xc600;
struct ValueFormat {u32 site,producer,words;const char* domain;const char* arguments[5];};
const ValueFormat value_formats[]={
    {0x8493d,0x846c0,3,"identity",{"identity"}},
    {0x84a1b,0x846c0,3,"identity",{"identity"}},
    {0x84a47,0x846c0,3,"identity",{"identity"}},
    {0x84abe,0x846c0,3,"identity",{"identity"}},
    {0x84ad9,0x846c0,3,"identity",{"identity"}},
    {0x84b28,0x846c0,3,"identity",{"identity"}},
    {0x84b6d,0x846c0,3,"identity",{"identity"}},
    {0x84bb0,0x846c0,3,"identity",{"identity"}},
    {0x84c8e,0x846c0,3,"identity",{"proper"}},
    {0x84cdb,0x846c0,3,"identity",{"proper"}},
    {0x84d07,0x846c0,3,"identity",{"identity"}},
    {0x1018b0,0x101790,4,"work",{"work","bound"}},
    {0xd73f5,0xd71b0,3,"injury",{"bound"}},
    {0xadc4f,0xadbc0,3,"corpse",{"resource:ADJ:SMALL"}},
    {0xadc86,0xadbc0,3,"corpse",{"resource:ADJ:BIG"}},
    {0xadd6e,0xadca0,4,"corpse",{"bound","bound"}},
    {0xaddb6,0xadca0,3,"corpse",{"resource:ACTIVITY_PROFILE:UNCONSCIOUS"}},
    {0xaddd6,0xadca0,3,"corpse",{"bound"}},
    {0xade27,0xadca0,3,"corpse",{"resource:ACTIVITY_PROFILE:AGGRESSIVE"}},
    {0xade49,0xadca0,3,"corpse",{"resource:ACTIVITY_PROFILE:ESCAPING"}},
    {0xadea7,0xadca0,3,"corpse",{"bound"}},
    {0xae0a5,0xadca0,3,"corpse",{"bound"}},
    {0xae0ec,0xadca0,3,"corpse",{"bound"}},
    {0xae120,0xadca0,3,"corpse",{"bound"}},
    {0xae38e,0xadca0,3,"corpse",{"control"}},
    {0xae81b,0xae750,3,"corpse",{"bound"}},
    {0xaeaff,0xae750,7,"corpse",{"double","double","signed"}},
    {0xaeb85,0xae750,3,"corpse",{"unsigned"}},
};
struct FormatPending {u32 owner;Status status;std::string translated;};
std::vector<FormatPending> value_format_pending;
enum ExtraHook:u32 {identity_proper=0xc700,identity_proper_random,identity_culture_gender,
    injury_selected,injury_side,corpse_select_eaten_low,corpse_select_eaten_med,
    corpse_select_eaten_high,corpse_select_eaten_great,corpse_select_cut_low,
    corpse_select_cut_med,corpse_select_cut_high,corpse_select_cut_great,
    corpse_select_damage_slight,corpse_select_damage_low,corpse_select_damage_med,
    corpse_select_damage_high,corpse_select_damage_great};

Status resource_value(const char* key,const char* source,std::string& translated) {
    return message_translate_template(key,source,translated);
}
Status identity_value(const Pending& call,const char* source,std::string& translated) {
    if(call.input=="proper") return message_identity_value(at<char>(0xa32a6e8),translated);
    if(call.input=="culture_gender") {
        const auto index=*at<unsigned char>(0xa32a6f5);
        std::string culture;
        auto status=message_lookup_value("identity",ptr<char>(at<u32>(0x18e38c)[index]),culture);
        return status==Status::ok ? pattern("identity",*at<unsigned char>(0xa32b1a9)==1 ?
            "%s man":"%s woman",{culture},translated):status;
    }
    for(auto i=call.children.rbegin();i!=call.children.rend();++i)
        if(i->producer==0x846c0 && i->source==source) {
            translated=i->translated;return Status::ok;
        }
    // A later literal write can replace an earlier formatted salutation.
    // These are the native stranger/visitor/friend switch branches.
    return message_lookup_value("identity",source,translated);
}
Status injury_value(const Pending& call,const char* source,std::string& translated) {
    if(call.input.empty()) return message_lookup_value("injury",source,translated);
    if(call.status!=Status::ok) return call.status;
    std::string part;
    for(const auto& child:call.children)
        if(child.producer==0xd4600) part=child.translated;
    std::string side;
    if(call.input!="none") {
        const auto status=message_lookup_value("injury",call.input.c_str(),side);
        if(status!=Status::ok) return status;
    }
    auto status=pattern("injury","%s in %s",{call.translated,side+part},translated);
    for(const auto& child:call.children)
        if(child.site==0xd73f5) translated+=child.translated;
    return status;
}
Status control_value(const char* source,std::string& output) {
    // 4ADCA0 appends the selected companion-control resource values in this
    // native frame. Escortee is its sole directly written control word.
    if(std::strcmp(source,"escortee")==0)
        return message_lookup_value("corpse",source,output);
    output.clear();std::string remaining=source;
    for(const auto& child:pending.back().children) {
        if(child.producer!=0x161b00 || child.source.empty()) continue;
        if(remaining.compare(0,child.source.size(),child.source)==0) {
            output+=child.translated;remaining.erase(0,child.source.size());
        }
    }
    return remaining.empty() ? Status::ok:Status::unavailable;
}
void append_builder_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    for(u32 i=0;i<sizeof(value_formats)/sizeof(value_formats[0]);++i)
        hooks.push_back(native_name_input::native_call(first_format+i,value_formats[i].site,
            0x10d0,value_formats[i].words));
    const auto absolute=[&](u32 id,u32 site,u32 rva,unsigned char opcode) {
        auto hook=instruction(id,site,{opcode,0,0,0,0});
        const auto address_value=address(at<char>(rva));
        std::memcpy(hook.expected+1,&address_value,4);hooks.push_back(hook);
    };
    absolute(identity_proper,0x8497d,0xa32a6e8,0xb9);
    absolute(identity_proper_random,0x84ca9,0xa32a6e8,0xb9);
    hooks.push_back(instruction(identity_culture_gender,0x849ab,{0x8d,0x8d,0x28,0xff,0xff,0xff}));
    hooks.push_back(instruction(injury_selected,0xd72e7,{0x0f,0xb6,0xc3,0x03,0xc1}));
    hooks.push_back(instruction(injury_side,0xd739d,{0x0f,0xb6,0x4d,0x8a,0x8b,0xd6}));
    absolute(corpse_select_eaten_low,0xae5f6,0xa2227e4,0xb9);
    absolute(corpse_select_eaten_med,0xae612,0xa220ff4,0xb9);
    absolute(corpse_select_eaten_high,0xae632,0xa2227b0,0xb9);
    absolute(corpse_select_eaten_great,0xae652,0xa221bc4,0xba);
    absolute(corpse_select_cut_low,0xae578,0xa222818,0xb9);
    absolute(corpse_select_cut_med,0xae592,0xa22108c,0xb9);
    absolute(corpse_select_cut_high,0xae5b2,0xa220f5c,0xb9);
    absolute(corpse_select_cut_great,0xae5d2,0xa221b2c,0xba);
    absolute(corpse_select_damage_slight,0xd70b5,0xa2d0a90,0xb9);
    absolute(corpse_select_damage_low,0xd70d2,0xa2d0b60,0xb9);
    absolute(corpse_select_damage_med,0xd70f2,0xa2d0bc8,0xb9);
    absolute(corpse_select_damage_high,0xd7112,0xa2d0a28,0xb9);
    absolute(corpse_select_damage_great,0xd7132,0xa2d0af8,0xba);
}
Status dispatch_builder(const NativeEvent& event,bool& handled) {
    handled=(event.id>=first_format && event.id<first_format+sizeof(value_formats)/sizeof(value_formats[0])) ||
        (event.id>=identity_proper && event.id<=corpse_select_damage_great);
    if(!handled) return Status::ok;
    if(event.id>=identity_proper) {
        auto& call=pending.back();
        if(event.id==identity_proper || event.id==identity_proper_random) call.input="proper";
        else if(event.id==identity_culture_gender) call.input="culture_gender";
        else if(event.id==injury_selected)
            call.status=message_lookup_value("injury",ptr<char>(event.frame->edx),call.translated);
        else if(event.id==injury_side) {
            const auto side=*ptr<unsigned char>(event.frame->ebp-0x73);
            call.input=side==0 || side==2 ? "left ":side==1 ? "right ":"none";
        } else {
            const char* keys[]={"CARCASS_EATEN:LOW","CARCASS_EATEN:MED","CARCASS_EATEN:HIGH",
                "CARCASS_EATEN:GREAT","CARCASS_CUT:LOW","CARCASS_CUT:MED","CARCASS_CUT:HIGH",
                "CARCASS_CUT:GREAT","CARCASS_DAMAGE:SLIGHT","CARCASS_DAMAGE:LOW","CARCASS_DAMAGE:MED",
                "CARCASS_DAMAGE:HIGH","CARCASS_DAMAGE:GREAT"};
            call.input=keys[event.id-corpse_select_eaten_low];
        }
        return call.status;
    }
    const auto& entry=value_formats[event.id-first_format];
    if(event.phase==NativePhase::after) {
        auto call=std::move(value_format_pending.back());value_format_pending.pop_back();
        if(call.status==Status::ok) {
            message_bind_value(ptr<char>(call.owner),call.translated);
            observe_value(entry.site,entry.producer,ptr<char>(call.owner),call.translated);
        }
        return call.status;
    }
    FormatPending call{event.arguments[0],Status::ok,{}};
    const auto* native_format=ptr<char>(event.arguments[1]);
    call.status=message_lookup_value(entry.domain,native_format,call.translated);
    std::size_t translated_at=0;
    u32 word=2;
    for(const auto* type:entry.arguments) {
        if(!type || call.status!=Status::ok) break;
        std::string value;const char* specifier="%s";
        if(std::strcmp(type,"proper")==0)
            call.status=message_identity_value(ptr<char>(event.arguments[word++]),value);
        else if(std::strcmp(type,"bound")==0)
            call.status=name_value(ptr<char>(event.arguments[word++]),value);
        else if(std::strcmp(type,"control")==0)
            call.status=control_value(ptr<char>(event.arguments[word++]),value);
        else if(std::strncmp(type,"resource:",9)==0)
            call.status=resource_value(type+9,ptr<char>(event.arguments[word++]),value);
        else if(std::strcmp(type,"signed")==0) {
            specifier="%d";value=std::to_string(static_cast<std::int32_t>(event.arguments[word++]));
        } else if(std::strcmp(type,"unsigned")==0) {
            specifier="%u";value=std::to_string(event.arguments[word++]);
        } else if(std::strcmp(type,"double")==0) {
            specifier="%.2f";double number;std::memcpy(&number,event.arguments+word,sizeof(number));word+=2;
            char buffer[128];std::snprintf(buffer,sizeof(buffer),"%.2f",number);value=buffer;
        } else call.status=message_lookup_value(type,ptr<char>(event.arguments[word++]),value);
        if(call.status==Status::ok) {
            const auto position=call.translated.find(specifier,translated_at);
            call.translated.replace(position,std::strlen(specifier),value);
            translated_at=position+value.size();
        }
    }
    if(entry.producer==0x846c0) pending.back().input.clear();
    value_format_pending.push_back(std::move(call));
    return value_format_pending.back().status;
}
void save_builders(std::vector<unsigned char>& output) {
    message_state_write(output,static_cast<u32>(value_format_pending.size()));
    for(const auto& call:value_format_pending) {
        message_state_write(output,call.owner);message_state_write(output,call.status);
        message_state_string(output,call.translated);
    }
}
void restore_builders(const unsigned char*& input) {
    u32 count;message_state_read(input,count);value_format_pending.resize(count);
    for(auto& call:value_format_pending) {
        message_state_read(input,call.owner);message_state_read(input,call.status);
        message_state_string(input,call.translated);
    }
}
