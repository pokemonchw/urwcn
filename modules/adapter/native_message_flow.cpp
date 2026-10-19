#include "native_message_flow.h"
#include "native_component_calls.h"
#include <algorithm>
#include <cstring>
#include <map>
#include <utility>

namespace uwcn::adapter::native_message_flow {
namespace {
struct LinePhase {u64 last_scroll;bool complete;};
struct Instance {
    u32 references;Source source;Handle input_owner;NativeState state;
    std::uint8_t observed_counter;
    u64 counter_generation=0;
    u64 scroll_distance=0;
    std::map<u64,LinePhase> line_phases;
};
struct Call {
    Handle source;
    u64 record;
    Waiting wait;
    Continuation continuation;
    bool has_continuation;
};
std::uintptr_t base{};
Services services{};
Handle next_handle=1,painting{};
u64 next_record=1;
u64 counter_generation{};
const Record* painting_source{};
u64 generated_scroll{};
std::map<u64,LinePhase> generated_lines;
bool installed_continuation{};
std::map<Handle,Instance> instances;
std::map<SourceKey,Handle> current_sources;
std::map<u32,Call> calls;
u32& native(u32 rva) { return *reinterpret_cast<u32*>(base+rva); }
std::uint8_t& counter() {return *reinterpret_cast<std::uint8_t*>(base+0x478E0E9);}
NativeState capture() {
    return {native(0x61A8CB8),native(0x61A968C),native(0xA1C1CB4),native(0x61BBB3C),
        native(0xA211068),native(0xA3840E8),native(0xA3840C4),counter()};
}
void install(const NativeState& state) {
    native(0x61A8CB8)=state.message_x;native(0x61A968C)=state.message_y;
    native(0xA1C1CB4)=state.cursor_x;native(0x61BBB3C)=state.cursor_y;
    native(0xA211068)=state.color;native(0xA3840E8)=state.completed_x;
    native(0xA3840C4)=state.completed_y;counter()=state.counter;
}
PaginationSeed seed(const NativeState& state) {return {state.cursor_x,state.cursor_y,state.color,state.counter};}
void install(PaginationSeed state) {
    native(0xA1C1CB4)=state.cursor_x;native(0x61BBB3C)=state.cursor_y;
    native(0xA211068)=state.color;counter()=state.counter;
}
Handle owner(Handle handle) {return instances.find(handle)->second.input_owner;}
const Record& find_record(const Call& call) {
    const auto& records=get(call.source).records;
    return *std::find_if(records.begin(),records.end(),[&](const Record& value){return value.identity==call.record;});
}
Call* target() {
    if(!painting_source) return nullptr;
    for(auto& [frame,call]:calls)
        if(call.wait.wait_frame && call.record==painting_source->identity && owner(call.source)==owner(painting) &&
            (!get(painting).ends_at_wait || get(painting).wait_ordinal==call.wait.acknowledged)) return &call;
    return nullptr;
}
struct Writer {
    std::vector<std::uint8_t> bytes;
    template<class T> void value(const T& value) {
        const auto* first=reinterpret_cast<const std::uint8_t*>(&value);bytes.insert(bytes.end(),first,first+sizeof(value));
    }
    void string(const std::string& value) {this->value(static_cast<u32>(value.size()));bytes.insert(bytes.end(),value.begin(),value.end());}
    void state(const NativeState& s) {
        value(s.message_x);value(s.message_y);value(s.cursor_x);value(s.cursor_y);value(s.color);
        value(s.completed_x);value(s.completed_y);value(s.counter);
    }
    void seed(PaginationSeed s) {value(s.cursor_x);value(s.cursor_y);value(s.color);value(s.counter);}
};
struct Reader {
    const std::uint8_t* cursor;
    template<class T> T value() {T value;std::memcpy(&value,cursor,sizeof(value));cursor+=sizeof(value);return value;}
    std::string string() {const auto bytes=value<u32>();std::string value(reinterpret_cast<const char*>(cursor),bytes);cursor+=bytes;return value;}
    NativeState state() {
        const auto x=value<u32>(),y=value<u32>(),cx=value<u32>(),cy=value<u32>(),color=value<u32>(),
            completed_x=value<u32>(),completed_y=value<u32>();const auto count=value<std::uint8_t>();
        return {x,y,cx,cy,color,completed_x,completed_y,count};
    }
    PaginationSeed seed() {
        const auto x=value<u32>(),y=value<u32>(),color=value<u32>();const auto count=value<std::uint8_t>();return {x,y,color,count};
    }
};
}
void initialize(std::uintptr_t image_base) {
    base=image_base;services={};next_handle=1;next_record=1;counter_generation=0;painting=0;painting_source=nullptr;
    instances.clear();current_sources.clear();calls.clear();generated_lines.clear();generated_scroll=0;installed_continuation=false;
}
void configure(const Services& value) {services=value;}
Handle construct_background(SourceKey key,const PanelSource& panel) {
    Source source;source.key=key;source.panel=panel;source.line_height=native(0x1E6ABC);source.origin=seed(capture());
    std::memcpy(source.rectangle.data(),reinterpret_cast<const void*>(base+0x61A8CE4),sizeof(source.rectangle));
    const auto handle=next_handle++;
    instances.emplace(handle,Instance{1,std::move(source),handle,capture(),counter(),counter_generation,0,{}});
    const auto current=current_sources.find(key);
    if(current==current_sources.end()) current_sources.emplace(key,handle);
    else {const auto previous=current->second;current->second=handle;release(previous);}
    return handle;
}
Status paint_background(Handle handle) {
    const auto& panel=get(handle).panel;
    native_component_style::PanelScope style(panel.style);
    const native_component_calls::PanelCall call{static_cast<u32>(base)+0x116270,
        panel.x,panel.y,panel.width,panel.height,panel.native_title.c_str(),panel.flags,panel.color};
    native_component_calls::uwcn_component_panel(&call);return Status::ok;
}
Handle append(SourceKey key,u32 frame,const char* input,const char* english,bool sound,const native_message_source::Text& text) {
    const auto prior=current_sources.find(key);
    auto state=capture();
    Source source=get(prior->second);
    const Handle input_owner=owner(prior->second);
    bool counter_input=false;
    {
        auto& input=instances.find(input_owner)->second;
        counter_input=counter_generation!=input.counter_generation;
        if(!counter_input) {state.counter=input.state.counter;counter()=state.counter;}
        // F6020 copies [top+5+lineHeight, top+height-5) upwards by that
        // actual native lineHeight. A completed record's final whole line
        // has left this native viewport after height-10 further scroll units.
        const auto interior=static_cast<u64>(source.rectangle[3]-10);
        const auto first=std::find_if(source.records.begin(),source.records.end(),[&](const Record& record) {
            const auto& phase=input.line_phases.find(record.identity)->second;
            return !phase.complete || input.scroll_distance-phase.last_scroll<interior;
        });
        for(auto retired=source.records.begin();retired!=first;++retired) input.line_phases.erase(retired->identity);
        source.records.erase(source.records.begin(),first);
        source.origin=source.records.empty()?seed(state):source.records.front().entry;
        source.ends_at_wait=false;
    }
    const auto identity=next_record++;
    source.records.push_back({identity,input,english,text,sound,counter_input,state.counter,seed(state)});
    const auto handle=next_handle++;
    retain(input_owner);
    instances.emplace(handle,Instance{1,std::move(source),input_owner,state,state.counter,counter_generation,0,{}});
    instances.find(input_owner)->second.state=state;
    auto& input_model=instances.find(input_owner)->second;
    input_model.observed_counter=state.counter;input_model.counter_generation=counter_generation;
    input_model.line_phases.emplace(identity,LinePhase{input_model.scroll_distance,false});
    const auto old=prior->second;prior->second=handle;release(old);
    retain(handle);calls.emplace(frame,Call{handle,identity,{frame,0,0},{},false});
    return handle;
}
const Source& get(Handle handle) {return instances.find(handle)->second.source;}
const Record& record(u32 frame) {return find_record(calls.find(frame)->second);}
Handle live_source(u32 frame) {return calls.find(frame)->second.source;}
Handle clear(SourceKey key) {
    const auto current=current_sources.find(key);
    Source source;source.key=key;source.panel=get(current->second).panel;
    source.line_height=native(0x1E6ABC);source.origin=seed(capture());
    std::memcpy(source.rectangle.data(),reinterpret_cast<const void*>(base+0x61A8CE4),sizeof(source.rectangle));
    const auto handle=next_handle++;
    instances.emplace(handle,Instance{1,std::move(source),handle,capture(),counter(),counter_generation,0,{}});
    const auto previous=current->second;current->second=handle;release(previous);
    return handle;
}
void scrolled(u32 frame,u32 line_height) {
    if(painting) {
        generated_scroll+=line_height;generated_lines.find(painting_source->identity)->second.last_scroll=generated_scroll;return;
    }
    const auto& call=calls.find(frame)->second;auto& input=instances.find(owner(call.source))->second;
    input.scroll_distance+=line_height;input.line_phases.find(call.record)->second.last_scroll=input.scroll_distance;
}
void counter_written() {++counter_generation;}
bool owns_frame(u32 frame) {return calls.find(frame)!=calls.end();}
void ui_finished(u32 frame) {
    const auto& call=calls.find(frame)->second;auto& input=instances.find(owner(call.source))->second;
    input.state=capture();input.observed_counter=counter();input.line_phases.find(call.record)->second.complete=true;
}
void finished(u32 frame) {const auto call=calls.find(frame);const auto source=call->second.source;calls.erase(call);release(source);}
void waiting(u32 frame,u32 wait_frame) {
    auto& call=calls.find(frame)->second;call.wait.wait_frame=wait_frame;call.has_continuation=false;
}
bool owns_wait(u32 wait_frame) {
    return std::any_of(calls.begin(),calls.end(),[&](const auto& value){return value.second.wait.wait_frame==wait_frame;});
}
void acknowledged(u32 wait_frame,NativeFrame& frame) {
    auto& call=std::find_if(calls.begin(),calls.end(),[&](const auto& value){return value.second.wait.wait_frame==wait_frame;})->second;
    if(call.has_continuation) {
        frame.ebx=call.continuation.cursor_x;frame.edi=call.continuation.wait_color;
        *reinterpret_cast<u32*>(wait_frame-0x18)=call.continuation.cursor_y;
    }
    ++call.wait.acknowledged;call.wait.wait_frame=0;
    if(call.has_continuation && !call.continuation.complete)call.has_continuation=false;
}
const Waiting* target_wait() {const auto* call=target();return call?&call->wait:nullptr;}
bool frozen_wait(u32 ordinal) {
    const auto& source=get(painting);
    return source.ends_at_wait && painting_source->identity==source.records.back().identity && source.wait_ordinal==ordinal;
}
void install_continuation(const Continuation& continuation) {
    installed_continuation=true;
    auto& call=*target();call.continuation=continuation;call.has_continuation=true;
    // All three F6510 call sites reserve eight bytes before calling F5B00.
    // The native wait prologue saves its parent's EBX at EBP-20h.
    *reinterpret_cast<u32*>(call.wait.wait_frame-0x20)=continuation.index;
    *reinterpret_cast<u32*>(call.wait.wait_frame+16+0x14)=continuation.color;
    *reinterpret_cast<u32*>(call.wait.wait_frame+4)=static_cast<u32>(base)+continuation.return_rva;
}
bool complete_resume(u32 frame) {
    const auto call=calls.find(frame);return call!=calls.end() && call->second.has_continuation && call->second.continuation.complete;
}
void complete_resumed(u32 frame) {calls.find(frame)->second.has_continuation=false;}
bool materializing() {return painting!=0;}
const Record& painting_record() {return *painting_source;}
void retain(Handle handle) {++instances.find(handle)->second.references;}
void release(Handle handle) {
    auto instance=instances.find(handle);
    if(--instance->second.references==0) {
        const auto input_owner=instance->second.input_owner;instances.erase(instance);
        if(input_owner!=handle) release(input_owner);
    }
}
Handle snapshot(Handle handle) {
    const auto& source=instances.find(handle)->second;const auto input_owner=source.input_owner;retain(input_owner);
    auto frozen=source.source;
    for(const auto& [frame,call]:calls)
        if(call.wait.wait_frame && owner(call.source)==input_owner && !frozen.records.empty() && call.record==frozen.records.back().identity) {
            frozen.ends_at_wait=true;frozen.wait_ordinal=call.wait.acknowledged;
        }
    const auto copy=next_handle++;
    instances.emplace(copy,Instance{1,std::move(frozen),input_owner,source.state,source.observed_counter,source.counter_generation,0,{}});return copy;
}
void remove_owner(u64 root) {
    for(auto source=current_sources.begin();source!=current_sources.end();) {
        if(source->first.owner==root) {const auto handle=source->second;source=current_sources.erase(source);release(handle);}else ++source;
    }
}
Status paint(Handle handle) {
    const auto& source=get(handle);
    const auto previous=capture();const auto previous_line=native(0x1E6ABC);
    std::array<u32,4> rectangle;std::memcpy(rectangle.data(),reinterpret_cast<const void*>(base+0x61A8CE4),sizeof(rectangle));
    const auto suppress=*reinterpret_cast<std::uint8_t*>(base+0x4D8F4F2);const auto skip=native(0x619F958);
    std::array<char,0x400> original,word;
    std::memcpy(original.data(),reinterpret_cast<const void*>(base+0x61A84B8),original.size());
    std::memcpy(word.data(),reinterpret_cast<const void*>(base+0x61A96A0),word.size());
    std::memcpy(reinterpret_cast<void*>(base+0x61A8CE4),source.rectangle.data(),sizeof(source.rectangle));
    native(0x1E6ABC)=source.line_height;
    *reinterpret_cast<std::uint8_t*>(base+0x4D8F4F2)=0;native(0x619F958)=0;
    painting=handle;generated_scroll=0;generated_lines.clear();installed_continuation=false;
    Status status=paint_background(handle);
    install(source.origin);
    for(const auto& record:source.records) {
        painting_source=&record;if(record.counter_input) counter()=record.counter;
        generated_lines.emplace(record.identity,LinePhase{generated_scroll,false});
        status=services.consume(handle,record);if(status!=Status::ok) break;
        generated_lines.find(record.identity)->second.complete=target()==nullptr;
        // This record's actual native wait is the visible input boundary. The
        // source revision cannot display records beyond the current input.
        if(target()) break;
    }
    const auto result=capture();const bool updates_wait=installed_continuation;painting_source=nullptr;painting=0;
    const auto current=current_sources.find(source.key);
    const bool actual_source=current!=current_sources.end() &&
        !source.records.empty() && !get(current->second).records.empty() &&
        get(current->second).records.back().identity==source.records.back().identity && (!source.ends_at_wait || updates_wait);
    // Cache source materialization never installs a cached general cursor or
    // pagination input. A real suspended message wait receives its newly
    // generated native continuation; other calls keep their caller's inputs.
    install(previous);
    if(updates_wait && status==Status::ok) {
        native(0x61A8CB8)=result.message_x;native(0x61A968C)=result.message_y;
        native(0xA3840E8)=result.completed_x;native(0xA3840C4)=result.completed_y;counter()=result.counter;
    }
    if(actual_source && status==Status::ok) {
        auto& input=instances.find(owner(handle))->second;input.state=result;
        input.scroll_distance=generated_scroll;input.line_phases=std::move(generated_lines);
        if(updates_wait) input.observed_counter=result.counter;
    }
    native(0x1E6ABC)=previous_line;std::memcpy(reinterpret_cast<void*>(base+0x61A8CE4),rectangle.data(),sizeof(rectangle));
    *reinterpret_cast<std::uint8_t*>(base+0x4D8F4F2)=suppress;native(0x619F958)=skip;
    std::memcpy(reinterpret_cast<void*>(base+0x61A84B8),original.data(),original.size());
    std::memcpy(reinterpret_cast<void*>(base+0x61A96A0),word.data(),word.size());
    return status;
}
std::vector<std::uint8_t> save() {
    Writer out;out.value(next_handle);out.value(next_record);out.value(counter_generation);out.value(static_cast<u32>(instances.size()));
    for(const auto& [handle,instance]:instances) {
        out.value(handle);out.value(instance.references);out.value(instance.input_owner);out.state(instance.state);
        out.value(instance.observed_counter);out.value(instance.counter_generation);out.value(instance.scroll_distance);
        out.value(static_cast<u32>(instance.line_phases.size()));
        for(const auto& [record,phase]:instance.line_phases) {out.value(record);out.value(phase.last_scroll);out.value(phase.complete?1u:0u);}
        const auto& source=instance.source;out.value(source.key.owner);out.value(source.key.native_source);out.value(source.key.field);
        const auto& panel=source.panel;out.value(panel.x);out.value(panel.y);out.value(panel.width);out.value(panel.height);
        out.value(panel.flags);out.value(panel.color);out.value(panel.style.background_mode);out.value(panel.style.title_fill_color);
        out.string(panel.native_title);
        for(const auto value:source.rectangle)out.value(value);out.value(source.line_height);out.seed(source.origin);
        out.value(source.ends_at_wait?1u:0u);out.value(source.wait_ordinal);out.value(static_cast<u32>(source.records.size()));
        for(const auto& record:source.records) {
            out.value(record.identity);out.string(record.native_input);out.string(record.english);
            native_message_source::write(out.bytes,record.text);out.value(record.sound_field?1u:0u);
            out.value(record.counter_input?1u:0u);out.value(record.counter);out.seed(record.entry);
        }
    }
    out.value(static_cast<u32>(current_sources.size()));
    for(const auto& [key,handle]:current_sources) {out.value(key.owner);out.value(key.native_source);out.value(key.field);out.value(handle);}
    out.value(static_cast<u32>(calls.size()));
    for(const auto& [frame,call]:calls) {
        out.value(frame);out.value(call.source);out.value(call.record);out.value(call.wait.parent_frame);
        out.value(call.wait.wait_frame);out.value(call.wait.acknowledged);out.value(call.has_continuation?1u:0u);
        const auto& c=call.continuation;out.value(c.return_rva);out.value(c.index);out.value(c.color);
        out.value(c.cursor_x);out.value(c.cursor_y);out.value(c.wait_color);out.value(c.complete?1u:0u);
    }
    return std::move(out.bytes);
}
void restore(const void* payload) {
    Reader in{static_cast<const std::uint8_t*>(payload)};next_handle=in.value<u32>();next_record=in.value<u64>();counter_generation=in.value<u64>();
    instances.clear();current_sources.clear();calls.clear();painting=0;painting_source=nullptr;
    const auto count=in.value<u32>();
    for(u32 index=0;index<count;++index) {
        const auto handle=in.value<u32>(),references=in.value<u32>(),input_owner=in.value<u32>();auto state=in.state();
        const auto observed=in.value<std::uint8_t>();const auto generation=in.value<u64>(),distance=in.value<u64>();const auto phases=in.value<u32>();
        std::map<u64,LinePhase> line_phases;
        for(u32 index=0;index<phases;++index) {
            const auto record=in.value<u64>(),last_scroll=in.value<u64>();const auto complete=in.value<u32>()!=0;
            line_phases.emplace(record,LinePhase{last_scroll,complete});
        }
        Source source;source.key.owner=in.value<u64>();source.key.native_source=in.value<u64>();source.key.field=in.value<u32>();
        auto& panel=source.panel;panel.x=in.value<std::int32_t>();panel.y=in.value<std::int32_t>();
        panel.width=in.value<std::int32_t>();panel.height=in.value<std::int32_t>();panel.flags=in.value<u32>();panel.color=in.value<u32>();
        panel.style.background_mode=in.value<u32>();panel.style.title_fill_color=in.value<u32>();panel.native_title=in.string();
        for(auto& value:source.rectangle)value=in.value<u32>();source.line_height=in.value<u32>();source.origin=in.seed();
        source.ends_at_wait=in.value<u32>()!=0;source.wait_ordinal=in.value<u32>();const auto records=in.value<u32>();
        for(u32 index=0;index<records;++index) {
            Record record;record.identity=in.value<u64>();record.native_input=in.string();record.english=in.string();
            record.text=native_message_source::read(in.cursor);record.sound_field=in.value<u32>()!=0;
            record.counter_input=in.value<u32>()!=0;record.counter=in.value<std::uint8_t>();record.entry=in.seed();source.records.push_back(std::move(record));
        }
        instances.emplace(handle,Instance{references,std::move(source),input_owner,state,observed,generation,distance,std::move(line_phases)});
    }
    const auto sources=in.value<u32>();
    for(u32 index=0;index<sources;++index) {
        const auto root=in.value<u64>(),native_source=in.value<u64>();const auto field=in.value<u32>(),handle=in.value<u32>();
        current_sources.emplace(SourceKey{root,native_source,field},handle);
    }
    const auto frames=in.value<u32>();
    for(u32 index=0;index<frames;++index) {
        const auto frame=in.value<u32>();Call call;call.source=in.value<u32>();call.record=in.value<u64>();
        call.wait.parent_frame=in.value<u32>();call.wait.wait_frame=in.value<u32>();call.wait.acknowledged=in.value<u32>();
        call.has_continuation=in.value<u32>()!=0;auto& c=call.continuation;
        c.return_rva=in.value<u32>();c.index=in.value<u32>();c.color=in.value<u32>();
        c.cursor_x=in.value<u32>();c.cursor_y=in.value<u32>();c.wait_color=in.value<u32>();c.complete=in.value<u32>()!=0;
        calls.emplace(frame,std::move(call));
    }
}
void shutdown() {
    instances.clear();current_sources.clear();calls.clear();generated_lines.clear();
    painting=0;painting_source=nullptr;generated_scroll=0;installed_continuation=false;services={};base=0;
}
}
