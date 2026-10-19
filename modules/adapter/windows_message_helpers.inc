// Native message-return helpers: 562D40/562D90/562DE0.
// Their exact sprintf arguments are display actions and movement postures.
// Native ring allocation, resource selection and English results are untouched.
namespace windows_message_helpers {
enum Hook : u32 { out_of_items=0xe000,cannot_while,cannot,
    skill_begin,skill_finish,skill_tier_0,skill_tier_1,skill_tier_2,skill_tier_3,skill_tier_4,
    skill_prefix,skill_cause,cause_begin,cause_one,cause_mostly,cause_pair,cause_finish };
struct Pending { u32 owner;std::string text;Status status; };
std::vector<Pending> pending;
struct Skill {std::string prefix,suffix,cause;u32 prefix_bytes{};};
std::vector<Skill> skills;
std::vector<std::string> causes;
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
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=out_of_items && event.id<=cause_finish;
    if(!handled) return Status::ok;
    if(event.id==skill_begin) {if(event.phase==NativePhase::before) skills.emplace_back();return Status::ok;}
    if(event.id==cause_begin) {if(event.phase==NativePhase::before) causes.emplace_back();return Status::ok;}
    if(event.id==skill_finish) {
        if(event.phase==NativePhase::after) return Status::ok;
        const auto* original=at<char>(0xa211100);
        auto value=std::move(skills.back());skills.pop_back();
        // The two native suppression paths really leave this buffer empty.
        std::string text;
        if(*original) text=value.prefix+value.suffix+value.cause+original[std::strlen(original)-1];
        message_bind_value(original,text);return Status::ok;
    }
    if(event.id==cause_finish) {
        if(event.phase==NativePhase::after) return Status::ok;
        message_bind_value(at<char>(0xa211230),causes.back());causes.pop_back();return Status::ok;
    }
    if(event.id==skill_cause) {
        auto& value=skills.back();
        if(event.phase==NativePhase::before)
            return message_lookup_value("skill.penalty",at<char>(0xa211100)+value.prefix_bytes,value.suffix);
        return message_translate_bound(ptr<char>(event.frame->eax),value.cause);
    }
    if(event.phase==NativePhase::after) {
        auto result=std::move(pending.back());pending.pop_back();
        if(result.status==Status::ok) {
            message_bind_value(ptr<char>(result.owner),result.text);
            if(event.id==skill_prefix) {
                skills.back().prefix=result.text;
                skills.back().prefix_bytes=static_cast<u32>(std::strlen(ptr<char>(result.owner)));
            }
            if(event.id>=cause_one && event.id<=cause_pair) causes.back()=result.text;
        }
        return result.status;
    }
    if(event.id>=skill_tier_0) {
        const char* key=nullptr;
        const char* domain=nullptr;
        switch(event.id) {
        case skill_tier_0:key="format.005af160";domain="skill";break;
        case skill_tier_1:key="format.005af180";domain="skill";break;
        case skill_tier_2:key="format.005af18c";domain="skill";break;
        case skill_tier_3:key="format.005af19c";domain="skill";break;
        case skill_tier_4:key="format.005af1ac";domain="skill";break;
        case skill_prefix:key="format.005af1bc";break;
        case cause_one:key="format.005af104";domain="skill.cause";break;
        case cause_mostly:key="format.005af110";domain="skill.cause";break;
        case cause_pair:
            key=event.arguments[1]==address(at<char>(0x1af124)) ? "format.005af124" : "format.005af138";
            domain="skill.cause";break;
        default:break;
        }
        std::string format,value;
        auto status=message_translate_template(key,ptr<char>(event.arguments[1]),format);
        if(status==Status::ok) status=domain ? message_lookup_value(domain,ptr<char>(event.arguments[2]),value) :
            message_translate_bound(ptr<char>(event.arguments[2]),value);
        if(status==Status::ok) {
            const auto position=format.find("%s");format.replace(position,2,value);
            if(event.id==cause_pair) {
                const auto next=position+value.size();
                status=message_lookup_value(domain,ptr<char>(event.arguments[3]),value);
                if(status==Status::ok) format.replace(format.find("%s",next),2,value);
            }
        }
        pending.push_back({event.arguments[0],std::move(format),status});return status;
    }
    std::string format,action;
    auto status=event.id==out_of_items ?
        message_translate_bound(ptr<char>(event.arguments[1]),format) :
        message_translate_template(event.id==cannot_while ? "format.005d8258" : "format.005d8270",
            ptr<char>(event.arguments[1]),format);
    if(status==Status::ok) status=message_lookup_value("action",ptr<char>(event.arguments[2]),action);
    if(status==Status::ok) {
        const auto position=format.find("%s");
        format.replace(position,2,action);
        if(event.id==cannot_while) {
            std::string posture;
            status=message_lookup_value("posture",ptr<char>(event.arguments[3]),posture);
            if(status==Status::ok) format.replace(format.find("%s",position+action.size()),2,posture);
        }
    }
    pending.push_back({event.arguments[0],std::move(format),status});
    return status;
}
}
