// Native message-return helpers: 562D40/562D90/562DE0.
// Their exact sprintf arguments are display actions and movement postures.
// Native ring allocation, resource selection and English results are untouched.
namespace windows_message_helpers {
enum Hook : u32 { out_of_items=0xe000,cannot_while,cannot,
    skill_begin,skill_finish,skill_tier_0,skill_tier_1,skill_tier_2,skill_tier_3,skill_tier_4,
    skill_prefix,skill_cause,cause_begin,cause_one,cause_mostly,cause_pair,cause_finish,
    debug_map_identifier,debug_attack_value,debug_block_value };
using Text=native_message_source::Text;
struct Pending {u32 owner;Text source;};
std::vector<Pending> pending;
struct Skill {Text prefix,suffix,cause;u32 prefix_bytes{};};
std::vector<Skill> skills;
std::vector<Text> causes;
void save(std::vector<unsigned char>& output) {
    message_state_write(output,static_cast<u32>(pending.size()));
    for(const auto& value:pending) {message_state_write(output,value.owner);native_message_source::write(output,value.source);}
    message_state_write(output,static_cast<u32>(skills.size()));
    for(const auto& value:skills) {
        native_message_source::write(output,value.prefix);native_message_source::write(output,value.suffix);
        native_message_source::write(output,value.cause);message_state_write(output,value.prefix_bytes);
    }
    message_state_write(output,static_cast<u32>(causes.size()));
    for(const auto& value:causes) native_message_source::write(output,value);
}
void restore(const unsigned char*& input) {
    u32 count;message_state_read(input,count);pending.clear();
    for(u32 index=0;index<count;++index) {u32 owner;message_state_read(input,owner);pending.push_back({owner,native_message_source::read(input)});}
    message_state_read(input,count);skills.clear();
    for(u32 index=0;index<count;++index) {
        auto prefix=native_message_source::read(input),suffix=native_message_source::read(input),cause=native_message_source::read(input);
        u32 bytes;message_state_read(input,bytes);skills.push_back({std::move(prefix),std::move(suffix),std::move(cause),bytes});
    }
    message_state_read(input,count);causes.clear();
    for(u32 index=0;index<count;++index) causes.push_back(native_message_source::read(input));
}
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::native_call;
    using native_name_input::instruction;
    hooks.push_back(native_call(out_of_items,0x162d83,0x10d0,3));
    hooks.push_back(native_call(cannot_while,0x162dce,0x10d0,4));
    hooks.push_back(native_call(cannot,0x162e1a,0x10d0,3));
    hooks.push_back(instruction(skill_begin,0x1239d3,{0x89,0x84,0x24,0xd8,0,0,0}));
    hooks.push_back(instruction(skill_finish,0x123d88,{0x8b,0x8c,0x24,0xe4,0,0,0}));
    const u32 tiers[]={0x123a82,0x123aad,0x123ad8,0x123b03,0x123b1f};
    for(u32 i=0;i<5;++i) hooks.push_back(native_call(skill_tier_0+i,tiers[i],0x10d0,3));
    hooks.push_back(native_call(skill_prefix,0x123b36,0x10d0,3));
    hooks.push_back(native_call(skill_cause,0x123d1c,0x123410,0));
    hooks.push_back(instruction(cause_begin,0x123423,{0x89,0x84,0x24,0xb0,0x02,0,0}));
    hooks.push_back(native_call(cause_one,0x1238f8,0x10d0,3));
    hooks.push_back(native_call(cause_mostly,0x12391c,0x10d0,3));
    hooks.push_back(native_call(cause_pair,0x12394f,0x10d0,4));
    hooks.push_back(instruction(cause_finish,0x123974,{0x8b,0x8c,0x24,0xbc,0x02,0,0}));
    auto map=instruction(debug_map_identifier,0x17afc0,{0xb9,0,0,0,0});
    const auto map_name=address(at<char>(0xa32b055));
    std::memcpy(map.expected+1,&map_name,4);hooks.push_back(map);
    hooks.push_back(native_call(debug_attack_value,0x17894e,0x15fc00,1));
    hooks.push_back(native_call(debug_block_value,0x17896e,0x15fc00,1));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    using namespace native_message_source;
    handled=event.id>=out_of_items && event.id<=debug_block_value;
    if(!handled) return Status::ok;
    if(event.id==debug_attack_value || event.id==debug_block_value) {
        // The wpdam command prints the actual [AD:...] / [BD:...] operands
        // extracted from its input (or the native literal "0" default).
        if(event.phase==NativePhase::after) {
            const auto* value=ptr<char>(event.frame->eax);
            message_bind_source(value,message_source_identity(value));
        }
        return Status::ok;
    }
    if(event.id==debug_map_identifier) {
        // 4112AC/42E3C6/42F1CA/42F535 select the actual map-file identifier
        // (BIGMAP/ZOOMMAP); 57AFC5 prints that identifier for debugging.
        if(event.phase==NativePhase::inline_before)
            message_bind_source(at<char>(0xa32b055),message_source_identity(at<char>(0xa32b055)));
        return Status::ok;
    }
    if(event.id==skill_begin) {if(event.phase==NativePhase::inline_before) skills.emplace_back();return Status::ok;}
    if(event.id==cause_begin) {if(event.phase==NativePhase::inline_before) causes.emplace_back();return Status::ok;}
    if(event.id==skill_finish) {
        if(event.phase==NativePhase::after) return Status::ok;
        const auto* english=at<char>(0xa211100);
        auto value=std::move(skills.back());skills.pop_back();
        // The two real native suppression branches produce an empty resource.
        auto source=*english ? concat({std::move(value.prefix),std::move(value.suffix),
            std::move(value.cause),original(std::string(1,english[std::strlen(english)-1]))}) : original("");
        message_bind_source(english,std::move(source));return Status::ok;
    }
    if(event.id==cause_finish) {
        if(event.phase==NativePhase::after) return Status::ok;
        message_bind_source(at<char>(0xa211230),std::move(causes.back()));causes.pop_back();return Status::ok;
    }
    if(event.id==skill_cause) {
        auto& value=skills.back();
        if(event.phase==NativePhase::before)
            value.suffix=message_source_value("skill.penalty",at<char>(0xa211100)+value.prefix_bytes);
        else value.cause=message_source_bound(ptr<char>(event.frame->eax));
        return Status::ok;
    }
    if(event.phase==NativePhase::after) {
        auto result=std::move(pending.back());pending.pop_back();
        message_bind_source(ptr<char>(result.owner),result.source);
        if(event.id==skill_prefix) {
            skills.back().prefix=result.source;
            skills.back().prefix_bytes=static_cast<u32>(std::strlen(ptr<char>(result.owner)));
        }
        if(event.id>=cause_one && event.id<=cause_pair) causes.back()=std::move(result.source);
        return Status::ok;
    }
    if(event.id>=skill_tier_0) {
        const char* key=nullptr;const char* domain=nullptr;
        switch(event.id) {
        case skill_tier_0:key="format.005af160";domain="skill";break;
        case skill_tier_1:key="format.005af180";domain="skill";break;
        case skill_tier_2:key="format.005af18c";domain="skill";break;
        case skill_tier_3:key="format.005af19c";domain="skill";break;
        case skill_tier_4:key="format.005af1ac";domain="skill";break;
        case skill_prefix:key="format.005af1bc";break;
        case cause_one:key="format.005af104";domain="skill.cause";break;
        case cause_mostly:key="format.005af110";domain="skill.cause";break;
        case cause_pair:key=event.arguments[1]==address(at<char>(0x1af124)) ? "format.005af124" : "format.005af138";
            domain="skill.cause";break;
        default:break;
        }
        std::vector<Text> values{domain ? message_source_value(domain,ptr<char>(event.arguments[2])) :
            message_source_bound(ptr<char>(event.arguments[2]))};
        if(event.id==cause_pair) values.push_back(message_source_value(domain,ptr<char>(event.arguments[3])));
        std::vector<std::string> conversions(values.size(),"%s");
        pending.push_back({event.arguments[0],format(message_source_template(key,ptr<char>(event.arguments[1])),
            std::move(values),std::move(conversions))});return Status::ok;
    }
    auto pattern=event.id==out_of_items ? message_source_bound(ptr<char>(event.arguments[1])) :
        message_source_template(event.id==cannot_while ? "format.005d8258" : "format.005d8270",ptr<char>(event.arguments[1]));
    std::vector<Text> values{message_source_value("action",ptr<char>(event.arguments[2]))};
    if(event.id==cannot_while) values.push_back(message_source_value("posture",ptr<char>(event.arguments[3])));
    std::vector<std::string> conversions(values.size(),"%s");
    pending.push_back({event.arguments[0],format(std::move(pattern),std::move(values),std::move(conversions))});
    return Status::ok;
}
}
