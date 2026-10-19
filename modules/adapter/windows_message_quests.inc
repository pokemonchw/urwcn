// 548740 builds treasure descriptions in real game-owned fields. Its random
// placement, cave/chasm decisions, item generation and English data stay native.
// Evidence: settlement-data-source-producers-ghidra.c and native disassembly.
namespace windows_message_quests {
enum Hook : u32 { island=0xe100,chasm,origin,title,origin_complete,place_copy,complete };
struct Pending {u32 owner;std::string translated;Status status;};
std::vector<Pending> pending;
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::native_call;
    using native_name_input::instruction;
    hooks.push_back(native_call(island,0x1489aa,0x10d0,3));
    hooks.push_back(native_call(chasm,0x148d52,0x10d0,3));
    hooks.push_back(native_call(origin,0x148e3c,0x10d0,3));
    hooks.push_back(native_call(title,0x148ec9,0x10d0,4));
    hooks.push_back(instruction(origin_complete,0x148e7c,{0x25,0xff,0x03,0,0x80}));
    hooks.push_back(instruction(place_copy,0x148ef2,{0x8b,0x85,0x98,0xfa,0xff,0xff}));
    hooks.push_back(instruction(complete,0x148f0f,{0x8b,0x4d,0xf8,0x8b,0xd7}));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=island && event.id<=complete;
    if(!handled) return Status::ok;
    if(event.id>=origin_complete) {
        if(event.phase==NativePhase::after) return Status::ok;
        std::string text;
        if(event.id==origin_complete) {
            auto status=message_translate_bound(ptr<char>(event.frame->ebp-0x554),text);
            if(status!=Status::ok) return status;
            std::string prefix;
            status=message_lookup_value("treasure","casual wealth",prefix);
            if(status==Status::ok) message_bind_value(at<char>(0xa220ef8),prefix+text);
            return status;
        }
        if(event.id==place_copy) {
            auto* target=at<char>(0xa221028);
            const auto* source=ptr<char>(event.frame->ecx-static_cast<u32>(std::strlen(target))-1);
            const auto status=message_translate_bound(source,text);
            if(status==Status::ok) message_bind_value(target,text);
            return status;
        }
        // These are exactly the recovered inline-copy branches. The other
        // two alternatives have already been bound at their real sprintf.
        const auto* location=at<char>(0xa221b60);
        if(std::strcmp(location,"in a cave")==0 || std::strcmp(location,"on a cliff")==0) {
            const auto status=message_lookup_value("treasure",location,text);
            if(status!=Status::ok) return status;
            message_bind_value(location,text);
        }
        auto* placement=at<char>(0xa220e90);
        auto status=message_lookup_value("treasure",placement,text);
        if(status!=Status::ok) return status;
        message_bind_value(placement,text);
        const auto* cover=at<char>(0xa220f90);
        if(std::strcmp(cover,"somewhere inside there")==0 ||
           std::strcmp(cover,"in the center of three adjacent boulders forming a triangle")==0) {
            status=message_lookup_value("treasure",cover,text);
            if(status==Status::ok) message_bind_value(cover,text);
        }
        return status;
    }
    if(event.phase==NativePhase::after) {
        auto value=std::move(pending.back());pending.pop_back();
        if(value.status==Status::ok) message_bind_value(ptr<char>(value.owner),value.translated);
        return value.status;
    }
    const char* keys[]={"format.005b7b1c","format.005b7bdc","format.005b7c18","format.005b7c28"};
    std::string format,value;
    auto status=message_translate_template(keys[event.id-island],ptr<char>(event.arguments[1]),format);
    if(status==Status::ok) {
        status=event.id==origin ? message_lookup_value("culture.native",ptr<char>(event.arguments[2]),value) :
            message_translate_bound(ptr<char>(event.arguments[2]),value);
    }
    if(status==Status::ok) {
        const auto position=format.find("%s");format.replace(position,2,value);
        if(event.id==title) {
            const auto next=position+value.size();
            status=message_lookup_value("treasure",ptr<char>(event.arguments[3]),value);
            if(status==Status::ok) format.replace(format.find("%s",next),2,value);
        }
    }
    pending.push_back({event.arguments[0],std::move(format),status});return status;
}
}
