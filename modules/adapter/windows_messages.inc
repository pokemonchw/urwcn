// PE 3.89: neutral semantic expressions and the F6510 native display borrow.
// No UI positions, layout, surfaces, pixels or delayed draw requests live here.
Status message_translate_value(const char*,const char*,std::string&);
using MessageText=native_message_source::Text;
namespace windows_message_values {
MessageText source(const char*,const char*);
MessageText tag_source(const char*,const char*);
}

template<class T> void message_state_write(std::vector<unsigned char>& output,const T& value) {
    const auto* data=reinterpret_cast<const unsigned char*>(&value);
    output.insert(output.end(),data,data+sizeof(value));
}
template<class T> void message_state_read(const unsigned char*& input,T& value) {
    std::memcpy(&value,input,sizeof(value));input+=sizeof(value);
}
void message_state_string(std::vector<unsigned char>& output,const std::string& value) {
    message_state_write(output,static_cast<u32>(value.size()));
    output.insert(output.end(),value.begin(),value.end());
}
void message_state_string(const unsigned char*& input,std::string& value) {
    u32 bytes;message_state_read(input,bytes);
    value.assign(reinterpret_cast<const char*>(input),bytes);input+=bytes;
}

namespace windows_messages {
struct Value { std::string source;MessageText text; };
// One semantic result per actual native producer buffer. Its English value is
// part of its identity: reused addresses do not identify previous results.
std::map<u32,Value> values;
// Only the unfinished actual F6510 invocation owns these source expressions.
// A persistent MessageFlow will adopt its source through the native owner API.
std::map<u32,MessageText> display_sources;
std::map<u32,std::string> display_inputs;
enum Hook : u32 { capture=0xb400,borrow,restore_source,history,finish,alert_colour,
    source_space,source_previous_space,source_character,source_length,
    word_append,word_length,word_history_source,word_advance_source,
    tail_length,tail_history_source,tail_advance_source,word_history_target,tail_history_target };
enum FlowHook:u32 { flow_input=0x5900,flow_accept,flow_gradient,flow_wait,
    flow_acknowledge,flow_complete_scroll,flow_cache_cleanup,flow_scrolled,flow_clear,flow_panel };
#include "native_message_counter_writers.inc"
u32 generated_waits{};
Status generated_status=Status::ok;
extern "C" std::uintptr_t uwcn_message_finish_target{};
// Used only during synchronous materialization, which never enters native
// input. The suspended ordinary game wait retains executable game addresses.
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_message_stop_wait() {
    __asm__ __volatile__("addl $8,%esp\n\tjmp *_uwcn_message_finish_target\n\t");
}
struct Display {
    u32 frame;
    u32 capacity;
    char english[0x400];
    // Three same-sized text regions follow: encoded source, native word and
    // native history assembly. The native loop owns all writes and boundaries.
};
Active* current(u32 frame) {
    for(auto i=active.rbegin();i!=active.rend();++i) {
        if((i->kind==Scope::message_pending || i->kind==Scope::message_body) &&
           ptr<Display>(i->allocation)->frame==frame) return &*i;
    }
    return nullptr;
}
char* source(Display* display) {return reinterpret_cast<char*>(display+1);}
char* word(Display* display) {return source(display)+display->capacity;}
char* history_text(Display* display) {return word(display)+display->capacity;}
Display* display(u32 frame) {return ptr<Display>(current(frame)->allocation);}
Status lookup(TextComponent component,const char* source,const char* domain,std::string& output) {
    const TextRequest request{component,source,domain};
    std::vector<char> text;
    const auto status=service_text(ModuleId::semantic,text_op::translate,&request,sizeof(request),text);
    if(status==Status::ok) output.assign(text.data());
    return status;
}
void save(std::vector<unsigned char>& output) {
    message_state_write(output,static_cast<u32>(values.size()));
    for(const auto& [owner,value]:values) {
        message_state_write(output,owner);
        message_state_string(output,value.source);
        native_message_source::write(output,value.text);
    }
    message_state_write(output,static_cast<u32>(display_sources.size()));
    for(const auto& [frame,source]:display_sources) {message_state_write(output,frame);native_message_source::write(output,source);}
    message_state_write(output,static_cast<u32>(display_inputs.size()));
    for(const auto& [frame,source]:display_inputs) {message_state_write(output,frame);message_state_string(output,source);}
}
void restore(const unsigned char*& input) {
    u32 count;message_state_read(input,count);
    values.clear();
    for(u32 i=0;i<count;++i) {
        u32 owner;message_state_read(input,owner);
        auto& value=values[owner];
        message_state_string(input,value.source);
        value.text=native_message_source::read(input);
    }
    message_state_read(input,count);display_sources.clear();
    for(u32 i=0;i<count;++i) {u32 frame;message_state_read(input,frame);display_sources.emplace(frame,native_message_source::read(input));}
    message_state_read(input,count);display_inputs.clear();
    for(u32 i=0;i<count;++i) {u32 frame;message_state_read(input,frame);message_state_string(input,display_inputs[frame]);}
}

void transfer_display(u32 generated_frame,u32 ordinary_frame) {
    // Display is a Host allocation, not a vector in this DLL. Its three native
    // working buffers can therefore remain in the real suspended F6510 call
    // across module publication. The generated call does not retain a loan.
    u64 token=0xFFFFFFFC00000000ull|ordinary_frame;
    if(const auto* previous=current(ordinary_frame)) {token=previous->token;end(token);}
    const auto generated=std::find_if(active.begin(),active.end(),[&](const Active& value) {
        return (value.kind==Scope::message_body || value.kind==Scope::message_pending) &&
            ptr<Display>(value.allocation)->frame==generated_frame;
    });
    if(generated!=active.end()) {
        auto adopted=*generated;active.erase(generated);adopted.token=token;
        ptr<Display>(adopted.allocation)->frame=ordinary_frame;active.push_back(adopted);
    }
}
Status consume_flow(native_message_flow::Handle,const native_message_flow::Record& record) {
    generated_waits=0;generated_status=Status::ok;
    uwcn_message_finish_target=reinterpret_cast<std::uintptr_t>(at<void>(0xf6ebb));
    using NativeMessage=void (__fastcall *)(const char*);
    reinterpret_cast<NativeMessage>(at<void>(0xf6510))(record.native_input.c_str());
    return generated_status;
}
native_message_flow::Services flow_services() {return {consume_flow};}
}

std::string message_source_utf8(const char* native) {
    std::string text;decode_parser_original(native,text);return text;
}
MessageText message_source_identity(const char* original) {
    return native_message_source::original(message_source_utf8(original));
}
MessageText message_source_lookup(const char* domain,const char* original) {
    return native_message_source::lookup(TextComponent::message_value,message_source_utf8(original),domain);
}
MessageText message_source_template(const char* key,const char* original) {
    return native_message_source::lookup(TextComponent::message_template,message_source_utf8(original),key);
}
MessageText message_source_bound(const char* original) {
    // Native composition wrappers pass an actual empty string for absent
    // prefix/suffix operands (for example 57A575 -> 4F6F40). It has no words.
    if(*original=='\0')return native_message_source::original("");
    const auto found=windows_messages::values.find(address(original));
    if(found!=windows_messages::values.end() && found->second.source==original) return found->second.text;
    // The other confirmed source class is the original embedded literal.
    return native_message_source::lookup(TextComponent::message_literal,message_source_utf8(original));
}
MessageText message_source_value(const char* domain,const char* original) {
    return windows_message_values::source(domain,original);
}
MessageText message_source_tag(const char* tag,const char* original) {
    return windows_message_values::tag_source(tag,original);
}
void message_bind_source(const char* original,MessageText source) {
    source.original=message_source_utf8(original);
    windows_messages::values[address(original)]={original,std::move(source)};
}
void message_bind_copy(const char* destination,const char* original_source,MessageText source) {
    // Called only at individually recovered, unconditional native text-copy
    // boundaries with no intervening call. The game performs that same copy.
    source.original=message_source_utf8(original_source);
    windows_messages::values[address(destination)]={original_source,std::move(source)};
}
Status message_project_source(const MessageText& source,bool chinese,std::string& output) {
    return native_message_source::project(source,windows_messages::lookup,chinese,output);
}
Status message_translate_bound(const char* original,std::string& output) {
    return message_project_source(message_source_bound(original),true,output);
}
Status message_translate_template(const char* key,const char* source,std::string& output) {
    return windows_messages::lookup(TextComponent::message_template,source,key,output);
}
Status message_identity_value(const char* source,std::string& output) {
    std::vector<char> encoded,utf8;
    auto status=native_name_input::display(source,encoded);
    if(status!=Status::ok) return status;
    status=codec(layout_op::decode_native,encoded.data(),utf8);
    if(status==Status::ok) output.assign(utf8.data());
    return status;
}
Status message_lookup_value(const char* domain,const char* source,std::string& output) {
    std::string utf8;
    const auto status=message_identity_value(source,utf8);
    if(status!=Status::ok) return status;
    return windows_messages::lookup(TextComponent::message_value,utf8.c_str(),domain,output);
}

namespace windows_messages {
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    using native_name_input::native_call;
    auto enter=instruction(capture,0xf65e8,{0xba,0,0,0,0});
    const auto sound_delimiters=address(at<char>(0x1a9f08));
    std::memcpy(enter.expected+1,&sound_delimiters,4);hooks.push_back(enter);
    auto display=instruction(borrow,0xf6a45,{0xb9,0,0,0,0});
    const auto text=address(at<char>(0x61a84b8));
    std::memcpy(display.expected+1,&text,4);hooks.push_back(display);
    auto leave=instruction(restore_source,0xf6d8a,{0x8d,0x4c,0x24,0x48,0xa3,0,0,0,0});
    const auto cursor=address(at<u32>(0xa3840e8));
    std::memcpy(leave.expected+5,&cursor,4);hooks.push_back(leave);
    hooks.push_back(native_call(history,0xf6eb3,0xf6280,3));
    hooks.push_back(instruction(finish,0xf6ebb,{0x8b,0x8c,0x24,0xb4,0x08,0,0}));
    auto colour=instruction(alert_colour,0xf6e09,{0x80,0xb9,0,0,0,0,0x21});
    const auto last_byte=address(at<char>(0x61a84b7));
    std::memcpy(colour.expected+2,&last_byte,4);hooks.push_back(colour);
    auto operand=[&](u32 id,u32 site,std::initializer_list<unsigned char> bytes,u32 offset,u32 rva) {
        auto hook=instruction(id,site,bytes);const auto pointer=address(at<char>(rva));
        std::memcpy(hook.expected+offset,&pointer,4);hooks.push_back(hook);
    };
    operand(source_space,0xf6a6d,{0x80,0xbb,0,0,0,0,0x20},2,0x61a84b8);
    operand(source_previous_space,0xf6a76,{0x80,0xbb,0,0,0,0,0x20},2,0x61a84b7);
    operand(source_character,0xf6a80,{0x8a,0x8b,0,0,0,0},2,0x61a84b8);
    operand(source_length,0xf6cce,{0xb9,0,0,0,0},1,0x61a84b8);
    operand(word_append,0xf6bf7,{0xbf,0,0,0,0},1,0x61a96a0);
    operand(word_length,0xf6c21,{0xb9,0,0,0,0},1,0x61a96a0);
    operand(word_history_source,0xf6c5c,{0xba,0,0,0,0},1,0x61a96a0);
    operand(word_advance_source,0xf6ca6,{0xb9,0,0,0,0},1,0x61a96a0);
    operand(tail_length,0xf6cec,{0xb9,0,0,0,0},1,0x61a96a0);
    operand(tail_history_source,0xf6d1e,{0xba,0,0,0,0},1,0x61a96a0);
    operand(tail_advance_source,0xf6d69,{0xb9,0,0,0,0},1,0x61a96a0);
    hooks.push_back(instruction(word_history_target,0xf6c6a,{0x8d,0xbc,0x24,0xb0,0,0,0}));
    hooks.push_back(instruction(tail_history_target,0xf6d2c,{0x8d,0xbc,0x24,0xb0,0,0,0}));
    hooks.push_back(instruction(flow_input,0xf65c2,{0x80,0x3b,0x2a,0x75,0x0d}));
    auto accept=instruction(flow_accept,0xf67c3,{0x0f,0xb6,0x05,0,0,0,0});
    const auto body=address(at<char>(0x61a84b8));std::memcpy(accept.expected+3,&body,4);hooks.push_back(accept);
    auto gradient=instruction(flow_gradient,0xf67dd,{0x33,0xff,0x80,0x3d,0,0,0,0,0});
    const auto gradient_flag=address(at<char>(0x5f5ae66));std::memcpy(gradient.expected+4,&gradient_flag,4);hooks.push_back(gradient);
    auto wait=instruction(flow_wait,0xf5b7f,{0x8d,0x55,0xec,0xb9,0,0,0,0});
    const auto more=address(at<char>(0x1a9d88));std::memcpy(wait.expected+4,&more,4);hooks.push_back(wait);
    auto acknowledge=instruction(flow_acknowledge,0xf5c13,{0x8b,0x45,0xe8,0x89,0x3d,0,0,0,0});
    const auto color=address(at<u32>(0xa211068));std::memcpy(acknowledge.expected+5,&color,4);hooks.push_back(acknowledge);
    hooks.push_back(native_call(flow_complete_scroll,0xf6d19,0xf6020,0));
    auto cleanup=instruction(flow_cache_cleanup,0xf5c31,{0xb9,0,0,0,0});
    std::memcpy(cleanup.expected+1,&more,4);hooks.push_back(cleanup);
    auto scrolled=instruction(flow_scrolled,0xf6164,{0xa3,0,0,0,0});
    const auto message_y=address(at<u32>(0x61a968c));std::memcpy(scrolled.expected+1,&message_y,4);hooks.push_back(scrolled);
    auto clear=instruction(flow_clear,0xfa347,{0xc6,0x05,0,0,0,0,0});
    const auto count=address(at<unsigned char>(0x478e0e9));std::memcpy(clear.expected+2,&count,4);hooks.push_back(clear);
    hooks.push_back(native_call(flow_panel,0xfa33f,0x116270,5));
    for(u32 index=0;index<std::size(counter_writers);++index) {
        const auto& writer=counter_writers[index];
        auto hook=writer.opcode==0xc6 ? instruction(counter_writer_begin+index,writer.site,
            {writer.opcode,writer.mode,0,0,0,0,writer.value}) :
            instruction(counter_writer_begin+index,writer.site,{writer.opcode,writer.mode,0,0,0,0});
        std::memcpy(hook.expected+2,&count,4);hooks.push_back(hook);
    }
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=(event.id>=capture && event.id<=tail_history_target) ||
        (event.id>=flow_input && event.id<=flow_panel) ||
        (event.id>=counter_writer_begin && event.id<counter_writer_begin+std::size(counter_writers));
    if(!handled || event.phase==NativePhase::after) return Status::ok;
    const bool painting=native_message_flow::materializing();
    if(event.id>=counter_writer_begin && event.id<counter_writer_begin+std::size(counter_writers)) {
        const auto site=counter_writers[event.id-counter_writer_begin].site;
        const bool inside_pagination=site==0xf5b3d || site==0xf5bae || site==0xf5c2b;
        const bool current_record=inside_pagination && native_message_flow::owns_frame(*ptr<u32>(event.frame->ebp));
        if(!painting && !native_ui_scene::materializing() && !current_record) native_message_flow::counter_written();
        return Status::ok;
    }
    if(event.id>=flow_input && event.id<=flow_panel) {
        switch(event.id) {
        case flow_input:
            if(painting) {
                const auto& record=native_message_flow::painting_record();
                std::memcpy(at<char>(0x61a84b8),record.english.c_str(),record.english.size()+1);
                result.resume_rva=0xf65e8;
            } else result.resume_rva=*ptr<char>(event.frame->ebx)=='*'?0xf65c7:0xf65d4;
            break;
        case flow_accept:
            if(!painting) {
                const auto root=native_root_component::current();
                const auto handle=native_message_flow::append(
                    {root,0x61A8CE4,static_cast<u32>(TextComponent::message_literal)},event.frame->ebp,
                    display_inputs.at(event.frame->ebp).c_str(),at<char>(0x61a84b8),
                    *ptr<char>(event.frame->esp+0x48)!=0,display_sources.at(event.frame->ebp));
                native_ui_scene::message_constructed(handle);
            }
            break;
        case flow_gradient:
            if(painting) {event.frame->edi=0;result.resume_rva=0xf6a22;}
            break;
        case flow_wait: {
            const auto wait_frame=event.frame->ebp;
            const auto parent=*ptr<u32>(wait_frame),return_rva=*ptr<u32>(wait_frame+4)-static_cast<u32>(host->image_base);
            // F5B00 also has independent native callers. Only these three
            // exact F6510 parent phases own a MessageFlow continuation.
            const bool message_call=return_rva==0xf6a3d || return_rva==0xf6c54 || return_rva==0xf6d16;
            if(!message_call) break;
            if(painting) {
                *at<unsigned char>(0x478e0e9)=0;
                const auto* waiting=native_message_flow::target_wait();
                const bool current_wait=waiting && generated_waits==waiting->acknowledged;
                if(current_wait || native_message_flow::frozen_wait(generated_waits)) {
                    if(current_wait) {
                    const native_message_flow::Continuation continuation{
                        return_rva,return_rva==0xf6a3d?0u:*ptr<u32>(wait_frame-0x20),
                        return_rva==0xf6a3d?0u:*ptr<u32>(wait_frame+16+0x14),
                        event.frame->ebx,*ptr<u32>(wait_frame-0x18),event.frame->edi,false};
                    transfer_display(parent,waiting->parent_frame);
                    native_message_flow::install_continuation(continuation);
                    }
                    *ptr<u32>(wait_frame+4)=address(reinterpret_cast<const void*>(&uwcn_message_stop_wait));
                }
                ++generated_waits;result.resume_rva=0xf5c3b;
            } else if(native_message_flow::owns_frame(parent)) native_message_flow::waiting(parent,wait_frame);
            break;
        }
        case flow_acknowledge:
            if(!painting && native_message_flow::owns_wait(event.frame->ebp)) {
                const auto parent=*ptr<u32>(event.frame->ebp);
                native_message_flow::acknowledged(event.frame->ebp,*event.frame);
                native_ui_scene::message_constructed(native_message_flow::live_source(parent));
            }
            break;
        case flow_complete_scroll:
            if(native_message_flow::complete_resume(event.frame->ebp)) result.skip_original=1;
            break;
        case flow_cache_cleanup:
            if(painting) result.resume_rva=0xf5c3b;
            break;
        case flow_scrolled: {
            const auto parent=*ptr<u32>(event.frame->ebp);
            if(painting || native_message_flow::owns_frame(parent)) native_message_flow::scrolled(parent,*at<u32>(0x1e6abc));
            break;
        }
        case flow_clear:
            if(!painting && !native_ui_scene::materializing()) {
                *at<unsigned char>(0x478e0e9)=0;
                const auto root=native_root_component::current();
                const auto handle=native_message_flow::clear({root,0x61A8CE4,static_cast<u32>(TextComponent::message_literal)});
                native_ui_scene::message_constructed(handle);result.resume_rva=0xfa34e;
            }
            break;
        case flow_panel: {
            const auto root=native_root_component::current();
            const native_message_flow::PanelSource source{
                static_cast<std::int32_t>(event.frame->ecx),static_cast<std::int32_t>(event.frame->edx),
                static_cast<std::int32_t>(event.arguments[0]),static_cast<std::int32_t>(event.arguments[1]),
                event.arguments[3],event.arguments[4],native_component_style::capture_panel(),ptr<char>(event.arguments[2])};
            const auto handle=native_message_flow::construct_background(
                {root,0x61A8CE4,static_cast<u32>(TextComponent::message_literal)},source);
            const auto status=native_message_flow::paint_background(handle);result.skip_original=1;return status;
        }
        }
        return Status::ok;
    }
    if(event.id==alert_colour) {
        auto* scope=current(event.frame->ebp);
        if(!scope) return Status::ok;
        const auto* english=ptr<Display>(scope->allocation)->english;
        // This native '&' branch is a control decision on the original last
        // byte. Chinese punctuation does not change its two native successors.
        result.resume_rva=english[std::strlen(english)-1]=='!' ? 0xf6e16 : 0xf6be8;
        return Status::ok;
    }
    if(event.id==capture) {
        if(painting) {
            display_sources.insert_or_assign(event.frame->ebp,native_message_flow::painting_record().text);
            result.resume_rva=0xf67c3;return Status::ok;
        }
        const auto* original=ptr<char>(event.frame->ebx);
        // Both languages bind the same completed English producer graph.
        // F6510 still performs its original sound/case/repeat decisions before
        // the accepted message reaches the actual display-consumer boundary.
        display_sources.insert_or_assign(event.frame->ebp,
            message_source_bound(*original=='*' ? at<char>(0x61a84b8) : original));
        display_inputs.insert_or_assign(event.frame->ebp,at<char>(0x61a84b8));
        return Status::ok;
    }
    if(event.id==borrow) {
        const auto& neutral=painting ? native_message_flow::painting_record().text :
            native_message_flow::record(event.frame->ebp).text;
        std::string projected;
        auto status=chinese_enabled ? message_project_source(neutral,true,projected) :
            decode_parser_original(at<char>(0x61a84b8),projected);
        if(status!=Status::ok) {
            if(painting) {generated_status=status;result.resume_rva=0xf6ebb;return Status::ok;}
            return status;
        }
        std::vector<char> encoded;
        status=codec(layout_op::encode_native,projected.c_str(),encoded);
        if(status!=Status::ok) {
            if(painting) {generated_status=status;result.resume_rva=0xf6ebb;return Status::ok;}
            return status;
        }
        // The original English buffer has already lost its sound field. The
        // semantic Chinese expression retains that native syntax until this
        // exact consumer, so remove only the actually consumed sound field.
        const bool sound=painting ? native_message_flow::painting_record().sound_field :
            native_message_flow::record(event.frame->ebp).sound_field;
        if(chinese_enabled && sound) {
            const auto* body=std::strchr(encoded.data(),'}')+1;
            encoded.erase(encoded.begin(),encoded.begin()+(body-encoded.data()));
        }
        auto* record=static_cast<Display*>(host->allocate(sizeof(Display)+3*encoded.size()));
        record->frame=event.frame->ebp;record->capacity=static_cast<u32>(encoded.size());
        std::memcpy(record->english,at<char>(0x61a84b8),sizeof(record->english));
        std::memcpy(source(record),encoded.data(),encoded.size());
        *word(record)=0;*history_text(record)=0;
        active.push_back({event.token,Scope::message_body,address(record),0,0,0,0});
        event.frame->ecx=address(source(record));result.resume_rva=0xf6a4a;
        return Status::ok;
    }
    if(event.id==finish) {
        display_sources.erase(event.frame->ebp);
        display_inputs.erase(event.frame->ebp);
        if(!painting && native_message_flow::owns_frame(event.frame->ebp)) {
            native_message_flow::ui_finished(event.frame->ebp);native_message_flow::finished(event.frame->ebp);
        }
        if(auto* scope=current(event.frame->ebp)) end(scope->token);
        return Status::ok;
    }
    auto* scope=current(event.frame->ebp);
    // Empty and suppressed messages take F6EBB without entering display.
    if(!scope) return Status::ok;
    auto* record=ptr<Display>(scope->allocation);
    if(event.id==restore_source) {
        if(painting) {
            if(const auto* waiting=native_message_flow::target_wait()) {
                const native_message_flow::Continuation continuation{0xf6d16,event.frame->ebx,
                    *ptr<u32>(event.frame->esp+0x14),*at<u32>(0xa1c1cb4),*at<u32>(0x61bbb3c),event.frame->ebx,true};
                transfer_display(event.frame->ebp,waiting->parent_frame);
                native_message_flow::install_continuation(continuation);
            }
            *at<u32>(0xa3840e8)=event.frame->eax;*at<u32>(0xa3840c4)=*at<u32>(0x61a968c);
            result.resume_rva=0xf6ebb;return Status::ok;
        }
        scope->kind=Scope::message_pending;
    } else if(event.id==history) {
        // F6280 receives the English body. The native text loop omits colour
        // markers and @ and skips the second space at its F6A68 branch.
        std::string body;
        const auto* original=record->english;
        const auto length=std::strlen(original);
        for(std::size_t i=0;i<length;++i) {
            if(i>1 && original[i]==' ' && original[i-1]==' ') ++i;
            // F6CD6..F6CE6 compares the advanced index with strlen; a skipped
            // final space reaches the NUL and contributes no visible byte.
            if(i==length) break;
            if((i==0 && std::strchr("!#&+:=>?_",original[i])) || original[i]=='@') continue;
            body+=original[i];
        }
        auto* text=static_cast<char*>(host->allocate(body.size()+1));
        std::memcpy(text,body.c_str(),body.size()+1);
        active.push_back({event.token,Scope::allocation,address(text),0,0,0,0});
        event.arguments[2]=address(text);
    } else {
        // Only replace the exact text operand of the original instruction.
        // Native branches, concatenation, wrapping and drawing still execute.
        switch(event.id) {
        case source_space:
            result.resume_rva=source(record)[event.frame->ebx]==' ' ? 0xf6a76:0xf6a80;break;
        case source_previous_space:
            result.resume_rva=source(record)[event.frame->ebx-1]==' ' ? 0xf6a7f:0xf6a80;break;
        case source_character:
            event.frame->ecx=(event.frame->ecx&0xffffff00u)|static_cast<unsigned char>(source(record)[event.frame->ebx]);
            result.resume_rva=0xf6a86;break;
        case source_length:event.frame->ecx=address(source(record));result.resume_rva=0xf6cd3;break;
        case word_append:event.frame->edi=address(word(record));result.resume_rva=0xf6bfc;break;
        case word_length:event.frame->ecx=address(word(record));result.resume_rva=0xf6c26;break;
        case word_history_source:event.frame->edx=address(word(record));result.resume_rva=0xf6c61;break;
        case word_advance_source:event.frame->ecx=address(word(record));result.resume_rva=0xf6cab;break;
        case tail_length:event.frame->ecx=address(word(record));result.resume_rva=0xf6cf1;break;
        case tail_history_source:
            if(native_message_flow::complete_resume(event.frame->ebp)) {
                native_message_flow::complete_resumed(event.frame->ebp);
                event.frame->eax=*at<u32>(0x61a8cb8);result.resume_rva=0xf6d8a;
            } else {event.frame->edx=address(word(record));result.resume_rva=0xf6d23;}
            break;
        case tail_advance_source:event.frame->ecx=address(word(record));result.resume_rva=0xf6d6e;break;
        case word_history_target:event.frame->edi=address(history_text(record));result.resume_rva=0xf6c71;break;
        case tail_history_target:event.frame->edi=address(history_text(record));result.resume_rva=0xf6d33;break;
        default:break;
        }
    }
    return Status::ok;
}
}
