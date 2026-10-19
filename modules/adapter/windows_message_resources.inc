// Windows 3.89 resource-message semantic companions.
// Evidence: docs/evidence/settlement-text-builders-ghidra.c,
// settlement-message-helpers-ghidra.c, settlement-dynamic-values-ghidra.c,
// settlement-message-builders-disassembly.txt and settlement-chat-disassembly.txt.
// The game alone selects resource branches and expands original English text.
// This observes those same operations. It stores no UI position or layout and
// never calls a native builder again or writes an original game text buffer.
Status message_translate_template(const char* key,const char* source,std::string& output);
Status message_translate_value(const char* tag,const char* value,std::string& output);
Status message_translate_bound(const char* original,std::string& output);
Status message_identity_value(const char* original,std::string& output);
void message_bind_value(const char* original,const std::string& translated);
namespace windows_message_values {
void observe_value(u32,u32,const char*,const std::string&);
}

namespace windows_message_resources {
enum Hook : u32 {
    build_begin=0xb500,initial_lookup,tag_value,hear_lookup,body_lookup,
    hear_format,build_finish,chat_selected,chat_expand,chat_finish,chat_enter,
    lookup_plain_selected,lookup_branch_selected,lookup_debug_selector,
    lookup_diagnostic,lookup_hear_selected
};

enum class LookupOrigin : u32 { key_reference,selected_template,debug_selector,diagnostic };

struct Text {
    u32 owner{};
    std::string key;
    std::string translated;
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
    message_state_string(state,text.translated);
    message_state_string(state,text.query);
    message_state_write(state,text.status);
    message_state_write(state,text.present);
}

void restore_text(const unsigned char*& state,Text& text) {
    message_state_read(state,text.owner);
    message_state_string(state,text.key);
    message_state_string(state,text.translated);
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
    hooks.push_back(instruction(chat_selected,0x1616c4,{0x8d,0x8d,0xf8,0xfb,0xff,0xff}));
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
}

void begin_lookup(Build& build) {
    // 560CB0 initially constructs the native key/selector diagnostic. Its
    // selected-body and missing-file paths below replace that actual origin.
    build.lookup_origin=LookupOrigin::key_reference;
    build.lookup_hear=false;
}

Status lookup_translation(const Build& build,const char* key,const char* source,
                          std::string& output) {
    switch(build.lookup_origin) {
    case LookupOrigin::selected_template:
        return message_translate_template(key,source,output);
    case LookupOrigin::diagnostic:
        return message_translate_bound(source,output);
    case LookupOrigin::key_reference:
    case LookupOrigin::debug_selector:
        // These proven native branches expose the business identifier itself.
        return message_identity_value(source,output);
    }
    return Status::ok;
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
    if(text.status!=Status::ok) return text.status;
    const std::string token=std::string("<")+tag+">";
    const auto position=text.translated.find(token);
    std::string replacement;
    if(enclosed(text.translated,position,'[',']') ||
       enclosed(text.translated,position,'{','}')) {
        // These actual tag values are native sublookup selectors or sound
        // sample names. Translation happens only after the corresponding
        // native [] lookup has chosen its display value.
        replacement=value;
    } else {
        text.status=message_translate_value(tag,value,replacement);
        if(text.status!=Status::ok) return text.status;
    }
    text.translated.replace(position,token.size(),replacement);
    return Status::ok;
}

Status selected_subvalue(Text& text,const NativeEvent& event) {
    if(event.phase==NativePhase::before) {
        begin_lookup(builds.back());
        text.query=ptr<char>(event.frame->ecx);
        return text.status;
    }
    if(text.status!=Status::ok) return text.status;
    std::string selected;
    text.status=lookup_translation(builds.back(),text.query.c_str(),
        ptr<char>(event.frame->eax),selected);
    if(text.status!=Status::ok) return text.status;
    const auto token=std::string("[")+text.query+"]";
    // Chinese can put this same selected macro elsewhere in the sentence.
    // We replace its identity, never reproduce the native branch decision.
    text.translated.replace(text.translated.find(token),token.size(),selected);
    text.query.clear();
    return Status::ok;
}

Status finish_build() {
    auto& build=builds.back();
    const auto status=build.body.status!=Status::ok ? build.body.status : build.hear.status;
    if(status==Status::ok) {
        message_bind_value(ptr<char>(build.body.owner),build.body.translated);
        windows_message_values::observe_value(build.callsite,0x161b00,
            ptr<char>(build.body.owner),build.body.translated);
        if(build.hear.present)
            message_bind_value(ptr<char>(build.hear.owner),build.hear.translated);
    }
    // The caller's native owner now carries the semantic association through
    // message_bind_value. No completed message is retained in this observer.
    builds.pop_back();
    return status;
}

Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=build_begin && event.id<=lookup_hear_selected;
    if(!handled) return Status::ok;
    switch(event.id) {
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
        build.body.status=lookup_translation(build,build.body.key.c_str(),
            ptr<char>(event.frame->eax),build.body.translated);
        build.hear.present=build.lookup_hear;
        if(build.hear.present)
            build.hear.status=message_translate_template(build.hear.key.c_str(),
                ptr<char>(build.hear.owner),build.hear.translated);
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
            std::string argument;
            build.hear.status=message_translate_value("%s",
                ptr<char>(event.arguments[2]),argument);
            if(build.hear.status!=Status::ok) return build.hear.status;
            const auto position=build.hear.translated.find("%s");
            build.hear.translated.replace(position,2,argument);
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
                chat.body.status=message_translate_template(chat.body.key.c_str(),
                    source,chat.body.translated);
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
            message_bind_value(ptr<char>(chat.body.owner),chat.body.translated);
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
