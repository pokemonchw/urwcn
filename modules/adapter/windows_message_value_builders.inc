// Included inside windows_message_values. Every entry is a native construction
// call or a selected native branch, never a second text-layout operation.
constexpr u32 first_format=0xc600;
struct ValueFormat {u32 site,producer,words;const char* domain;const char* arguments[5];};
const ValueFormat value_formats[]={
    {0x64b12,0x64730,4,"requirement-msg",{"bound","unsigned"}},
    {0x64b39,0x64730,3,"requirement-msg",{"unsigned"}},
    {0x64bba,0x64730,4,"requirement-msg",{"bound","bound"}},
    {0x64c04,0x64730,4,"requirement-msg",{"bound","bound"}},
    {0x64c57,0x64730,4,"requirement-msg",{"bound","bound"}},
    {0x64caa,0x64730,4,"requirement-msg",{"bound","bound"}},
    {0x64d1b,0x64730,4,"requirement-msg",{"bound","bound"}},
    {0x64dc8,0x64730,5,"requirement-msg",{"bound","bound","unsigned"}},
    {0x64e1f,0x64730,5,"requirement-msg",{"bound","bound","unsigned"}},
    {0x64e85,0x64730,4,"requirement-msg",{"bound","bound"}},
    {0x64ebb,0x64730,3,"requirement-msg",{"bound"}},
    {0x64eff,0x64730,4,"requirement-msg",{"bound","unsigned"}},
    {0x6505c,0x64730,3,"requirement-msg",{"signed"}},
    {0x65180,0x64730,3,"requirement-msg",{"bound"}},
    {0x651be,0x64730,3,"requirement-msg",{"bound"}},
    {0x651e4,0x64730,3,"requirement-msg",{"bound"}},
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
    // 4AECB0's two diagnostics reach 4F6510 before the separate profile
    // component lowercases and appends the same local buffer.
    {0xaf533,0xaecb0,4,"npc-debug",{"bound","signed"}},
    {0xaf732,0xaecb0,6,"npc-debug",{"bound","signed","signed","signed"}},
    {0x40cdf,0x40b20,4,"craft",{"signed","bound"}},
    {0x40d3b,0x40b20,4,"craft",{"bound","bound"}},
    {0x40e09,0x40b20,4,"craft",{"unsigned","bound"}},
    {0x3665,0x3550,3,"flora",{"signed"}},
    {0x48e3d,0x48d50,3,"bowstring",{"bowstring"}},
    {0x48ed0,0x48d50,3,"bowstring",{"bowstring"}},
    {0x197f5,0x19610,3,"time",{"time"}},
    {0x19a15,0x199b0,3,"time",{"signed"}},
    {0x19b1f,0x199b0,3,"time",{"signed"}},
    {0x19b86,0x199b0,3,"time",{"time"}},
    {0x19bac,0x199b0,2,"time",{}},
    {0x4b3cb,0x4b2f0,4,"unit",{"native_real"}},
    {0x4b3f2,0x4b2f0,4,"unit",{"native_real"}},
    {0x4b431,0x4b2f0,4,"unit",{"native_real"}},
    {0x4b458,0x4b2f0,4,"unit",{"native_real"}},
    {0x4b47b,0x4b2f0,4,"unit",{"native_real"}},
    {0x4b64e,0x4b2f0,4,"unit",{"native_real"}},
    {0x4b676,0x4b2f0,4,"unit",{"native_real"}},
    {0x4b6eb,0x4b2f0,4,"unit",{"native_real"}},
    {0x4b8e9,0x4b800,4,"unit",{"native_real"}},
    {0x4b910,0x4b800,4,"unit",{"native_real"}},
    {0x4b94f,0x4b800,4,"unit",{"native_real"}},
    {0x4b972,0x4b800,4,"unit",{"native_real"}},
    {0x4ba29,0x4b800,4,"unit",{"native_real"}},
    {0x4ba67,0x4b800,4,"unit",{"native_real"}},
    {0x4bac0,0x4b800,4,"unit",{"native_real"}},
};
struct FormatPending {u32 owner;MessageText text;};
std::vector<FormatPending> value_format_pending;
enum ExtraHook:u32 {identity_proper=0xc700,identity_proper_random,identity_culture_gender,
    injury_selected,injury_side,corpse_select_eaten_low,corpse_select_eaten_med,
    corpse_select_eaten_high,corpse_select_eaten_great,corpse_select_cut_low,
    corpse_select_cut_med,corpse_select_cut_high,corpse_select_cut_great,
    corpse_select_damage_slight,corpse_select_damage_low,corpse_select_damage_med,
    corpse_select_damage_high,corpse_select_damage_great};
MessageText identity_source(const Pending& call,const char* original) {
    if(call.input=="proper") return message_source_identity(at<char>(0xa32a6e8));
    if(call.input=="culture_gender") {
        const auto index=*at<unsigned char>(0xa32a6f5);
        return pattern("identity",*at<unsigned char>(0xa32b1a9)==1 ? "%s man":"%s woman",
            {message_source_lookup("identity",ptr<char>(at<u32>(0x18e38c)[index]))});
    }
    for(auto i=call.children.rbegin();i!=call.children.rend();++i)
        if(i->producer==0x846c0 && i->original==original) return i->text;
    return message_source_lookup("identity",original);
}
MessageText injury_source(const Pending& call,const char* original) {
    if(call.input.empty()) return message_source_lookup("injury",original);
    MessageText part;
    for(const auto& child:call.children) if(child.producer==0xd4600) part=child.text;
    const auto side=call.input=="none" ? native_message_source::original(""):
        message_source_lookup("injury",call.input.c_str());
    auto text=pattern("injury","%s in %s",{call.text,native_message_source::concat({side,part})});
    for(const auto& child:call.children) if(child.site==0xd73f5) text=native_message_source::concat({text,child.text});
    return text;
}
MessageText control_source(const char* original) {
    // Exactly the append sources selected by 4ADCA0: escortee or PARTY/PARTNER,
    // followed by LEASHED and TIED. Other resource calls in this frame are not control text.
    std::vector<MessageText> parts;
    if(std::strncmp(original,"escortee",8)==0) parts.push_back(message_source_lookup("corpse","escortee"));
    for(const auto& child:pending.back().children)
        if(child.producer==0x161b00 && (child.site==0xadfe5 || child.site==0xae00f ||
           child.site==0xae1ac || child.site==0xae1e9)) parts.push_back(child.text);
    return native_message_source::concat(std::move(parts));
}
#include "windows_message_value_chains.inc"
#include "windows_message_value_copies.inc"
#include "windows_message_requirement_value.inc"
constexpr u32 first_unit_append=0xc940;
struct UnitAppend {u32 site,literal;bool word;};
const UnitAppend unit_appends[]={
    {0x4b73b,0x198528,false},{0x4b75a,0x19852c,false},
    {0x4b77f,0x198534,false},{0x4b7ba,0x198538,false},
    {0x4b7da,0x19853c,true},{0x4bafa,0x198544,false},
    {0x4bb1a,0x198548,false},{0x4bb4e,0x19854c,true},
    {0x4bb7a,0x198550,false}
};
void append_unit_hooks(std::vector<HookSpec>& hooks) {
    for(u32 index=0;index<sizeof(unit_appends)/sizeof(unit_appends[0]);++index) {
        const auto& source=unit_appends[index];
        auto hook=source.word ? native_name_input::instruction(first_unit_append+index,source.site,{0x66,0xA1,0,0,0,0}):
            native_name_input::instruction(first_unit_append+index,source.site,{0xA1,0,0,0,0});
        const auto literal=address(at<char>(source.literal));std::memcpy(hook.expected+(source.word?2:1),&literal,4);
        hooks.push_back(hook);
    }
}
Status dispatch_unit(const NativeEvent& event,bool& handled) {
    handled=event.id>=first_unit_append && event.id<first_unit_append+sizeof(unit_appends)/sizeof(unit_appends[0]);
    if(!handled || event.phase!=NativePhase::inline_before) return Status::ok;
    // Each hook precedes one literal strcat in 44B2F0/44B800. ESI is the
    // actual native ring resource, already bound by its last scalar sprintf.
    const auto* owner=ptr<char>(event.frame->esi);
    const auto* suffix=at<char>(unit_appends[event.id-first_unit_append].literal);
    const auto text=native_message_source::concat({message_source_bound(owner),message_source_lookup("unit",suffix)});
    const std::string original=std::string(owner)+suffix;
    message_bind_copy(owner,original.c_str(),text);return Status::ok;
}
void append_builder_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    for(u32 i=0;i<sizeof(value_formats)/sizeof(value_formats[0]);++i)
        hooks.push_back(native_name_input::native_call(first_format+i,value_formats[i].site,0x10d0,value_formats[i].words));
    const auto absolute=[&](u32 id,u32 site,u32 rva,unsigned char opcode) {
        auto hook=instruction(id,site,{opcode,0,0,0,0});const auto value=address(at<char>(rva));
        std::memcpy(hook.expected+1,&value,4);hooks.push_back(hook);
    };
    absolute(identity_proper,0x8497d,0xa32a6e8,0xb9);absolute(identity_proper_random,0x84ca9,0xa32a6e8,0xb9);
    hooks.push_back(instruction(identity_culture_gender,0x849ab,{0x8d,0x8d,0x28,0xff,0xff,0xff}));
    hooks.push_back(instruction(injury_selected,0xd72e7,{0x0f,0xb6,0xc3,0x03,0xc1}));
    hooks.push_back(instruction(injury_side,0xd739d,{0x0f,0xb6,0x4d,0x8a,0x8b,0xd6}));
    absolute(corpse_select_eaten_low,0xae5f6,0xa2227e4,0xb9);absolute(corpse_select_eaten_med,0xae612,0xa220ff4,0xb9);
    absolute(corpse_select_eaten_high,0xae632,0xa2227b0,0xb9);absolute(corpse_select_eaten_great,0xae652,0xa221bc4,0xba);
    absolute(corpse_select_cut_low,0xae578,0xa222818,0xb9);absolute(corpse_select_cut_med,0xae592,0xa22108c,0xb9);
    absolute(corpse_select_cut_high,0xae5b2,0xa220f5c,0xb9);absolute(corpse_select_cut_great,0xae5d6,0xa221b2c,0xb9);
    absolute(corpse_select_damage_slight,0xd70b5,0xa2d0a90,0xb9);absolute(corpse_select_damage_low,0xd70d2,0xa2d0b60,0xb9);
    absolute(corpse_select_damage_med,0xd70f2,0xa2d0bc8,0xb9);absolute(corpse_select_damage_high,0xd7112,0xa2d0a28,0xb9);
    absolute(corpse_select_damage_great,0xd7132,0xa2d0af8,0xba);append_chain_hooks(hooks);append_value_copy_hooks(hooks);append_unit_hooks(hooks);append_requirement_hooks(hooks);
}
Status dispatch_builder(const NativeEvent& event,bool& handled) {
    const auto requirement=dispatch_requirement(event,handled);if(handled) return requirement;
    const auto unit=dispatch_unit(event,handled);if(handled) return unit;
    const auto copy=dispatch_value_copy(event,handled);if(handled) return copy;
    const auto chain=dispatch_chain(event,handled);if(handled) return chain;
    handled=(event.id>=first_format && event.id<first_format+sizeof(value_formats)/sizeof(value_formats[0])) ||
        (event.id>=identity_proper && event.id<=corpse_select_damage_great);
    if(!handled) return Status::ok;
    if(event.id>=identity_proper) {
        if(event.phase==NativePhase::after) return Status::ok;
        auto& call=pending.back();
        if(event.id==identity_proper || event.id==identity_proper_random) call.input="proper";
        else if(event.id==identity_culture_gender) call.input="culture_gender";
        else if(event.id==injury_selected) call.text=message_source_lookup("injury",ptr<char>(event.frame->edx));
        else if(event.id==injury_side) {
            const auto side=*ptr<unsigned char>(event.frame->ebp-0x73);
            call.input=side==0 || side==2 ? "left ":side==1 ? "right ":"none";
        } else {
            const char* keys[]={"CARCASS_EATEN:LOW","CARCASS_EATEN:MED","CARCASS_EATEN:HIGH","CARCASS_EATEN:GREAT",
                "CARCASS_CUT:LOW","CARCASS_CUT:MED","CARCASS_CUT:HIGH","CARCASS_CUT:GREAT",
                "CARCASS_DAMAGE:SLIGHT","CARCASS_DAMAGE:LOW","CARCASS_DAMAGE:MED","CARCASS_DAMAGE:HIGH","CARCASS_DAMAGE:GREAT"};
            call.input=keys[event.id-corpse_select_eaten_low];
        }
        return Status::ok;
    }
    const auto& entry=value_formats[event.id-first_format];
    if(event.phase==NativePhase::after) {
        auto call=std::move(value_format_pending.back());value_format_pending.pop_back();
        call.text.original=message_source_utf8(ptr<char>(call.owner));
        message_bind_source(ptr<char>(call.owner),call.text);observe_value(entry.site,entry.producer,ptr<char>(call.owner),call.text);
        return Status::ok;
    }
    FormatPending call{event.arguments[0],{}};
    if(entry.site==0x3665) {
        pending.back().input="flora-debug";
        pending.back().detail=message_source_lookup("status",ptr<char>(event.frame->ebp-0x408));
    }
    if(entry.producer==0x48d50) pending.back().input="formatted";
    const auto* native_format=ptr<char>(event.arguments[1]);
    std::vector<MessageText> values;std::vector<std::string> conversions;u32 word=2;
    for(const auto* type:entry.arguments) {
        if(!type) break;MessageText value;std::string conversion="%s";
        if(std::strcmp(type,"proper")==0) value=message_source_identity(ptr<char>(event.arguments[word++]));
        else if(std::strcmp(type,"bound")==0) value=source("bound",ptr<char>(event.arguments[word++]));
        else if(std::strcmp(type,"control")==0) value=control_source(ptr<char>(event.arguments[word++]));
        else if(std::strncmp(type,"resource:",9)==0) value=message_source_template(type+9,ptr<char>(event.arguments[word++]));
        else if(std::strcmp(type,"signed")==0) {
            conversion="%d";value=native_message_source::scalar(native_message_source::Scalar::signed32,event.arguments[word++],conversion);
        } else if(std::strcmp(type,"unsigned")==0) {
            conversion="%u";value=native_message_source::scalar(native_message_source::Scalar::unsigned32,event.arguments[word++],conversion);
        } else if(std::strcmp(type,"double")==0) {
            conversion="%.2f";u64 bits;std::memcpy(&bits,event.arguments+word,sizeof(bits));word+=2;
            value=native_message_source::scalar(native_message_source::Scalar::real64,bits,conversion);
        } else if(std::strcmp(type,"native_real")==0) {
            conversion=native_format;u64 bits;std::memcpy(&bits,event.arguments+word,sizeof(bits));word+=2;
            value=native_message_source::scalar(native_message_source::Scalar::real64,bits,conversion);
        } else value=message_source_lookup(type,ptr<char>(event.arguments[word++]));
        values.push_back(std::move(value));conversions.push_back(std::move(conversion));
    }
    call.text=native_message_source::format(message_source_lookup(entry.domain,native_format),std::move(values),std::move(conversions));
    if(entry.producer==0x846c0) pending.back().input.clear();
    value_format_pending.push_back(std::move(call));return Status::ok;
}
void save_builders(std::vector<unsigned char>& output) {
    message_state_write(output,static_cast<u32>(value_format_pending.size()));
    for(const auto& call:value_format_pending) {message_state_write(output,call.owner);native_message_source::write(output,call.text);}
    save_chains(output);
}
void restore_builders(const unsigned char*& input) {
    u32 count;message_state_read(input,count);value_format_pending.resize(count);
    for(auto& call:value_format_pending) {message_state_read(input,call.owner);call.text=native_message_source::read(input);}
    restore_chains(input);
}
