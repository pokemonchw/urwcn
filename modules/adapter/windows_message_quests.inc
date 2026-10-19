// 548740 builds treasure descriptions in real game-owned fields. Its random
// placement, cave/chasm decisions, item generation and English data stay native.
// Evidence: settlement-data-source-producers-ghidra.c and native disassembly.
#include "windows_message_quest_records.inc"
namespace windows_message_quests {
enum Hook : u32 { island=0xe100,chasm,origin,title,origin_complete,place_copy,complete };
using Text=native_message_source::Text;
struct Pending {u32 owner;Text source;};
std::vector<Pending> pending;
void save(std::vector<unsigned char>& output) {
    message_state_write(output,static_cast<u32>(pending.size()));
    for(const auto& value:pending) {message_state_write(output,value.owner);native_message_source::write(output,value.source);}
    windows_message_quest_records::save(output);
}
void restore(const unsigned char*& input) {
    u32 count;message_state_read(input,count);pending.clear();
    for(u32 index=0;index<count;++index) {u32 owner;message_state_read(input,owner);pending.push_back({owner,native_message_source::read(input)});}
    windows_message_quest_records::restore(input);
}
void append_hooks(std::vector<HookSpec>& hooks) {
    windows_message_quest_records::append_hooks(hooks);
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
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    const auto records=windows_message_quest_records::dispatch(event,result,handled);
    if(handled)return records;
    using namespace native_message_source;
    handled=event.id>=island && event.id<=complete;
    if(!handled) return Status::ok;
    if(event.id>=origin_complete) {
        if(event.phase==NativePhase::after) return Status::ok;
        if(event.id==origin_complete) {
            message_bind_source(at<char>(0xa220ef8),concat({message_source_lookup("treasure","casual wealth"),
                message_source_bound(ptr<char>(event.frame->ebp-0x554))}));return Status::ok;
        }
        if(event.id==place_copy) {
            auto* target=at<char>(0xa221028);
            const auto* source=ptr<char>(event.frame->ecx-static_cast<u32>(std::strlen(target))-1);
            message_bind_source(target,message_source_bound(source));return Status::ok;
        }
        const auto* location=at<char>(0xa221b60);
        if(std::strcmp(location,"in a cave")==0 || std::strcmp(location,"on a cliff")==0)
            message_bind_source(location,message_source_lookup("treasure",location));
        auto* placement=at<char>(0xa220e90);
        message_bind_source(placement,message_source_lookup("treasure",placement));
        const auto* cover=at<char>(0xa220f90);
        if(std::strcmp(cover,"somewhere inside there")==0 ||
           std::strcmp(cover,"in the center of three adjacent boulders forming a triangle")==0)
            message_bind_source(cover,message_source_lookup("treasure",cover));
        return Status::ok;
    }
    if(event.phase==NativePhase::after) {
        auto value=std::move(pending.back());pending.pop_back();
        message_bind_source(ptr<char>(value.owner),std::move(value.source));return Status::ok;
    }
    const char* keys[]={"format.005b7b1c","format.005b7bdc","format.005b7c18","format.005b7c28"};
    std::vector<Text> values{event.id==origin ? message_source_value("culture.native",ptr<char>(event.arguments[2])) :
        message_source_bound(ptr<char>(event.arguments[2]))};
    if(event.id==title) values.push_back(message_source_lookup("treasure",ptr<char>(event.arguments[3])));
    std::vector<std::string> conversions(values.size(),"%s");
    pending.push_back({event.arguments[0],format(message_source_template(keys[event.id-island],
        ptr<char>(event.arguments[1])),std::move(values),std::move(conversions))});return Status::ok;
}
}
