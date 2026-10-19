// PE 3.89: synchronous semantic values and the F6510 native display borrow.
// No UI positions, layout, surfaces, pixels or delayed draw requests live here.
Status message_translate_value(const char*,const char*,std::string&);

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
struct Value { std::string source,translated; };
// One semantic result per actual native producer buffer. Its English value is
// part of its identity: reused addresses do not identify previous results.
std::map<u32,Value> values;
enum Hook : u32 { capture=0xb400,borrow,restore_source,history,finish,alert_colour };
struct Display {
    u32 frame;
    u32 borrowed;
    char english[0x400];
    // The encoded translation follows this header in the host allocation.
};
Active* current(u32 frame) {
    for(auto i=active.rbegin();i!=active.rend();++i) {
        if((i->kind==Scope::message_pending || i->kind==Scope::message_body) &&
           ptr<Display>(i->allocation)->frame==frame) return &*i;
    }
    return nullptr;
}
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
        message_state_string(output,value.translated);
    }
}
void restore(const unsigned char*& input) {
    u32 count;message_state_read(input,count);
    values.clear();
    for(u32 i=0;i<count;++i) {
        u32 owner;message_state_read(input,owner);
        auto& value=values[owner];
        message_state_string(input,value.source);
        message_state_string(input,value.translated);
    }
}
}

void message_bind_value(const char* original,const std::string& translated) {
    windows_messages::values[address(original)]={original,translated};
}
void message_bind_copy(const char* destination,const char* original_source,const std::string& translated) {
    // Called only at individually recovered, unconditional native text-copy
    // boundaries with no intervening call. The game performs that same copy.
    windows_messages::values[address(destination)]={original_source,translated};
}
Status message_translate_bound(const char* original,std::string& output) {
    const auto found=windows_messages::values.find(address(original));
    if(found!=windows_messages::values.end() && found->second.source==original) {
        output=found->second.translated;
        return Status::ok;
    }
    // The other source class at these confirmed consumers is an embedded
    // literal. This is an exact literal catalog lookup, not pattern matching.
    return windows_messages::lookup(TextComponent::message_literal,original,nullptr,output);
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
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=event.id>=capture && event.id<=alert_colour;
    if(!handled || event.phase==NativePhase::after) return Status::ok;
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
        if(!chinese_enabled) return Status::ok;
        const auto* original=ptr<char>(event.frame->ebx);
        std::string translated;
        const auto status=message_translate_bound(*original=='*' ? at<char>(0x61a84b8) : original,translated);
        if(status!=Status::ok) return status;
        std::vector<char> encoded;
        const auto encoding=codec(layout_op::encode_native,translated.c_str(),encoded);
        if(encoding!=Status::ok) return encoding;
        auto* record=static_cast<Display*>(host->allocate(sizeof(Display)+encoded.size()));
        record->frame=event.frame->ebp;record->borrowed=0;
        std::memcpy(record+1,encoded.data(),encoded.size());
        active.push_back({event.token,Scope::message_pending,address(record),0,0,0,0});
        return Status::ok;
    }
    auto* scope=current(event.frame->ebp);
    // Empty and suppressed messages take F6EBB without reaching F65E8;
    // English messages likewise do not enter the Chinese display scope.
    if(!scope) return Status::ok;
    auto* record=ptr<Display>(scope->allocation);
    if(event.id==borrow) {
        std::memcpy(record->english,at<char>(0x61a84b8),sizeof(record->english));
        const auto* display=reinterpret_cast<const char*>(record+1);
        // F65F2 already selected this exact sound field. F662A strips through
        // its closing brace. The display copy follows that same consumed field.
        if(*ptr<char>(event.frame->esp+0x48)) display=std::strchr(display,'}')+1;
        std::strcpy(at<char>(0x61a84b8),display);
        record->borrowed=1;scope->kind=Scope::message_body;
    } else if(event.id==restore_source) {
        std::memcpy(at<char>(0x61a84b8),record->english,sizeof(record->english));
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
    } else if(event.id==finish) {
        end(scope->token);
    }
    return Status::ok;
}
}
