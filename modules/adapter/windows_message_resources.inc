// Windows 3.89 resource-message semantic companions.
// Evidence: docs/evidence/settlement-text-builders-ghidra.c,
// settlement-message-helpers-ghidra.c, settlement-dynamic-values-ghidra.c,
// settlement-message-builders-disassembly.txt and settlement-chat-disassembly.txt.
// The game alone selects resource branches and expands original English text.
// This observes those same operations. It stores no UI position or layout and
// never calls a native builder again or writes an original game text buffer.
namespace windows_message_values {
void observe_value(u32,u32,const char*,const MessageText&);
}

namespace windows_message_resources {
enum Hook : u32 {
    build_begin=0xb500,initial_lookup,tag_value,hear_lookup,body_lookup,
    hear_format,build_finish,chat_selected,chat_expand,chat_finish,chat_enter,
    lookup_plain_selected,lookup_branch_selected,lookup_debug_selector,
    lookup_diagnostic,lookup_hear_selected,herbal_effect_name
};

enum class LookupOrigin : u32 { key_reference,selected_template,debug_selector,diagnostic };

struct Text {
    u32 owner{};
    std::string key;
    MessageText source;
    std::string query;
    Status status=Status::ok;
    bool present{};
};
struct Build {
    bool active{};
    u32 callsite{};
    Text body;
    Text hear;
    LookupOrigin lookup_origin=LookupOrigin::key_reference;
    bool lookup_hear{};
};
// A native item tag can enter 451770 -> 4AE750 -> 4AECB0 -> 561B00.
// These are synchronous native construction frames, not completed messages.
std::vector<Build> builds;
struct Chat {
    bool active{};
    Text body;
};
std::vector<Chat> chats;

void save_text(std::vector<unsigned char>& state,const Text& text) {
    message_state_write(state,text.owner);
    message_state_string(state,text.key);
    native_message_source::write(state,text.source);
    message_state_string(state,text.query);
    message_state_write(state,text.status);
    message_state_write(state,text.present);
}

void restore_text(const unsigned char*& state,Text& text) {
    message_state_read(state,text.owner);
    message_state_string(state,text.key);
    text.source=native_message_source::read(state);
    message_state_string(state,text.query);
    message_state_read(state,text.status);
    message_state_read(state,text.present);
}

// Native calls can be suspended in a nested message wait while the business
// module is replaced. Preserve only their unfinished semantic companions.
void save(std::vector<unsigned char>& state) {
    message_state_write(state,static_cast<u32>(builds.size()));
    for(const auto& build:builds) {
        message_state_write(state,build.active);
        message_state_write(state,build.callsite);
        save_text(state,build.body);
        save_text(state,build.hear);
        message_state_write(state,build.lookup_origin);
        message_state_write(state,build.lookup_hear);
    }
    message_state_write(state,static_cast<u32>(chats.size()));
    for(const auto& chat:chats) {
        message_state_write(state,chat.active);
        save_text(state,chat.body);
    }
}

void restore(const unsigned char*& state) {
    u32 count{};
    message_state_read(state,count);
    builds.resize(count);
    for(auto& build:builds) {
        message_state_read(state,build.active);
        message_state_read(state,build.callsite);
        restore_text(state,build.body);
        restore_text(state,build.hear);
        message_state_read(state,build.lookup_origin);
        message_state_read(state,build.lookup_hear);
    }
    message_state_read(state,count);
    chats.resize(count);
    for(auto& chat:chats) {
        message_state_read(state,chat.active);
        restore_text(state,chat.body);
    }
}

void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    using native_name_input::native_call;
    hooks.push_back(native_call(build_begin,0x161b9b,0x161330,0));
    hooks.push_back(native_call(initial_lookup,0x161ba7,0x160cb0,0));
    hooks.push_back(native_call(tag_value,0x1613d4,0x1601c0,0));
    hooks.push_back(native_call(hear_lookup,0x161c79,0x160cb0,0));
    hooks.push_back(native_call(body_lookup,0x161d7a,0x160cb0,0));
    hooks.push_back(native_call(hear_format,0x161e42,0x10d0,3));
    auto finish=instruction(build_finish,0x161e74,{0xb8,0,0,0,0});
    const auto body=address(at<char>(0xa224eb0));
    std::memcpy(finish.expected+1,&body,4);
    hooks.push_back(finish);
    // This LEA is reached only after the native .KEY. comparison succeeds.
    // Seven mood slots and the native selected-default slot remain untouched.
    hooks.push_back(instruction(chat_selected,0x1616c4,{0x8d,0x85,0xf8,0xfb,0xff,0xff}));
    hooks.push_back(native_call(chat_expand,0x16168d,0x161330,0));
    hooks.push_back(instruction(chat_finish,0x1616b1,{0x8b,0x4d,0xfc,0x8b,0xc6}));
    hooks.push_back(instruction(chat_enter,0x161483,{0xb8,0x1c,0x38,0,0}));
    hooks.push_back(instruction(lookup_plain_selected,0x161056,{0xbf,1,0,0,0}));
    hooks.push_back(instruction(lookup_branch_selected,0x16110e,{0xbf,1,0,0,0}));
    // This copy instruction is confined to the native debug-selector branch.
    // Its loop target is 561160, outside the replaced instruction bytes.
    auto debug_selector=instruction(lookup_debug_selector,0x16116a,{0x88,0x88,0,0,0,0});
    const auto selector_owner=address(at<char>(0xa2d0497));
    std::memcpy(debug_selector.expected+2,&selector_owner,4);
    hooks.push_back(debug_selector);
    hooks.push_back(instruction(lookup_diagnostic,0x1612e6,{0x8d,0x85,0xf8,0xeb,0xff,0xff}));
    auto hear_selected=instruction(lookup_hear_selected,0x161281,{0xb9,0,0,0,0});
    const auto hear=address(at<char>(0xa2248b8));
    std::memcpy(hear_selected.expected+1,&hear,4);
    hooks.push_back(hear_selected);
    hooks.push_back(native_call(herbal_effect_name,0x3c802,0xf6510,0));
}

void begin_lookup(Build& build) {
    // 560CB0 initially constructs the native key/selector diagnostic. Its
    // selected-body and missing-file paths below replace that actual origin.
    build.lookup_origin=LookupOrigin::key_reference;
    build.lookup_hear=false;
}

MessageText lookup_source(const Build& build,const char* key,const char* original) {
    switch(build.lookup_origin) {
    case LookupOrigin::selected_template:return message_source_template(key,original);
    case LookupOrigin::diagnostic:return message_source_bound(original);
    case LookupOrigin::key_reference:
    case LookupOrigin::debug_selector:return message_source_identity(original);
    }
    return {};
}
Text* expanding_text(u32 owner) {
    // 561330 is also called for business keys and unrelated text. Only these
    // buffers inside their already-entered native resource scopes qualify.
    for(auto i=builds.rbegin();i!=builds.rend();++i) {
        auto& build=*i;
        if(build.body.owner==owner) return &build.body;
        if(build.hear.owner==owner && build.hear.present) return &build.hear;
    }
    for(auto i=chats.rbegin();i!=chats.rend();++i) {
        auto& chat=*i;
        if(chat.active && chat.body.present && chat.body.owner==owner) return &chat.body;
    }
    return nullptr;
}

bool enclosed(const std::string& text,std::size_t position,char open,char close) {
    const auto left=text.rfind(open,position);
    const auto right=text.rfind(close,position);
    return left!=std::string::npos && (right==std::string::npos || left>right);
}

Status expand_observed_tag(Text& text,const char* tag,const char* value) {
    const std::string token=std::string("<")+tag+">";
    const auto position=text.source.original.find(token);
    const bool control=enclosed(text.source.original,position,'[',']') ||
                       enclosed(text.source.original,position,'{','}');
    auto replacement=control ? message_source_identity(value) : message_source_tag(tag,value);
    text.source=native_message_source::replace_first(std::move(text.source),token,std::move(replacement));
    return text.status;
}

Status selected_subvalue(Text& text,const NativeEvent& event) {
    if(event.phase==NativePhase::before) {
        begin_lookup(builds.back());text.query=ptr<char>(event.frame->ecx);return text.status;
    }
    auto selected=lookup_source(builds.back(),text.query.c_str(),ptr<char>(event.frame->eax));
    const auto token=std::string("[")+message_source_utf8(text.query.c_str())+"]";
    text.source=native_message_source::replace_first(std::move(text.source),token,std::move(selected));
    text.query.clear();return text.status;
}
Status finish_build() {
    auto& build=builds.back();
    const auto status=build.body.status!=Status::ok ? build.body.status : build.hear.status;
    if(status==Status::ok) {
        message_bind_source(ptr<char>(build.body.owner),build.body.source);
        windows_message_values::observe_value(build.callsite,0x161b00,
            ptr<char>(build.body.owner),build.body.source);
        if(build.hear.present)
            message_bind_source(ptr<char>(build.hear.owner),build.hear.source);
    }
    // The caller's native owner now carries the semantic association through
    // message_bind_source. No completed message is retained in this observer.
    builds.pop_back();
    return status;
}

Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=build_begin && event.id<=herbal_effect_name;
    if(!handled) return Status::ok;
    switch(event.id) {
    case herbal_effect_name:
        // 43B9D0's final loop passes each record's +1 name field (CCB stride).
        if(event.phase==NativePhase::before) {
            const auto* native=ptr<char>(event.frame->ecx);
            message_bind_source(native,message_source_lookup("herbal.effect",native));
        }
        return Status::ok;
    case build_begin:
        if(event.phase==NativePhase::before) {
            builds.emplace_back();
            auto& build=builds.back();
            build.active=true;
            build.callsite=*ptr<u32>(event.frame->ebp+4)-address(at<char>(0))-5;
            build.body.owner=address(at<char>(0xa224eb0));
            build.hear.owner=address(at<char>(0xa2248b8));
        }
        return Status::ok;
    case initial_lookup: {
        auto& build=builds.back();
        if(event.phase==NativePhase::before) {
            begin_lookup(build);
            // The preceding 561330 has already expanded parameters in KEY.
            build.body.key=ptr<char>(event.frame->ecx);
            build.hear.key=build.body.key;
            return Status::ok;
        }
        build.body.present=true;
        build.body.source=lookup_source(build,build.body.key.c_str(),ptr<char>(event.frame->eax));
        build.hear.present=build.lookup_hear;
        if(build.hear.present)
            build.hear.source=message_source_template(build.hear.key.c_str(),ptr<char>(build.hear.owner));
        return build.body.status!=Status::ok ? build.body.status : build.hear.status;
    }
    case tag_value:
        if(event.phase==NativePhase::after) {
            auto* text=expanding_text(event.frame->ebx);
            if(text) {
                // 561330's EBP-68 local contains the exact tag passed in ECX
                // at 5613D4; 5601C0 reads it without modifying it. EBX remains
                // that caller's original buffer and EAX is its actual value.
                return expand_observed_tag(*text,ptr<char>(event.frame->ebp-0x68),
                    ptr<char>(event.frame->eax));
            }
        }
        return Status::ok;
    case hear_lookup:
        return selected_subvalue(builds.back().hear,event);
    case body_lookup:
        return selected_subvalue(builds.back().body,event);
    case hear_format: {
        auto& build=builds.back();
        // Only the actual 561E42 branch consumes A622A50, and only for HEAR.
        // The main body keeps its %s for its caller's separate native sprintf.
        if(event.phase==NativePhase::before) {
            if(build.hear.status!=Status::ok) return build.hear.status;
            auto argument=message_source_tag("%s",ptr<char>(event.arguments[2]));
            build.hear.source=native_message_source::replace_first(
                std::move(build.hear.source),"%s",std::move(argument));
        }
        return build.hear.status;
    }
    case build_finish:
        return finish_build();
    case chat_enter:
        chats.emplace_back();
        chats.back().body.key=ptr<char>(event.frame->ecx);
        return Status::ok;
    case chat_selected: {
        auto& chat=chats.back();
        chat.active=true;
        chat.body.owner=*ptr<u32>(event.frame->ebp-0x3814);
        return Status::ok;
    }
    case chat_expand: {
        auto& chat=chats.back();
        if(chat.active && event.phase==NativePhase::before) {
            const auto* source=ptr<char>(chat.body.owner);
            // An empty native selection has no body to translate. The game
            // subsequently constructs its own diagnostic at 5616A9.
            chat.body.present=*source!='\0';
            if(chat.body.present)
                chat.body.source=message_source_template(chat.body.key.c_str(),source);
        }
        if(chat.active && event.phase==NativePhase::after) {
            // 56169E tests the length of this just-expanded native result.
            // Empty output selects 5616A9's native diagnostic, including when
            // a previously nonempty template consisted entirely of tags.
            chat.body.present=*ptr<char>(chat.body.owner)!='\0';
        }
        return chat.body.status;
    }
    case chat_finish: {
        auto& chat=chats.back();
        const auto status=chat.body.status;
        if(chat.active && chat.body.present && status==Status::ok)
            message_bind_source(ptr<char>(chat.body.owner),chat.body.source);
        chats.pop_back();
        return status;
    }
    case lookup_plain_selected:
    case lookup_branch_selected:
        builds.back().lookup_origin=LookupOrigin::selected_template;
        return Status::ok;
    case lookup_debug_selector:
        builds.back().lookup_origin=LookupOrigin::debug_selector;
        return Status::ok;
    case lookup_diagnostic:
        builds.back().lookup_origin=LookupOrigin::diagnostic;
        return Status::ok;
    case lookup_hear_selected:
        builds.back().lookup_hear=true;
        return Status::ok;
    default: return Status::ok;
    }
}
}
