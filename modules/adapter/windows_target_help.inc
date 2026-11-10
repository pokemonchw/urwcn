// F7820 owns the target dialog, direction keycaps, input and named background.
// Translate only its confirmed complete text calls; retain no page or layout.
namespace windows_target_help {
enum Hook:u32 {
    title=0x18500,exit,select,mouse,cursor,action_prompt,action_keys,
    creature_text,creature_width
};

// 114A20's sole input is the original literal [+]Next, or [-]Previous
// creature. Its own tokenizer exposes exactly these two non-keycap atoms.
struct CreatureAtom {const char* original;const char* key;};
constexpr CreatureAtom creature_atoms[]{
    {"Next, or ","creature.next"},{"Previous creature","creature.previous"}
};
const char* creature_key(const char* original) {
    return std::find_if(std::begin(creature_atoms),std::end(creature_atoms),
        [original](const auto& atom){return std::strcmp(original,atom.original)==0;})->key;
}

// D3DB0 makes an uppercase display copy for F7918. All 37 nonempty
// accepted headings are ASCII; identify the same complete source in either
// case without changing that native copy or the caller's English input.
std::string source_key(const char* prefix,const char* original) {
    std::string key=prefix;
    for(const auto* p=original;*p;++p)
        key+=*p>='A' && *p<='Z' ? static_cast<char>(*p-'A'+'a') : *p;
    return key;
}

void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(call(title,0xF7918,0x116270,5));
    hooks.push_back(call(exit,0xF7A88,0x114680,1));
    hooks.push_back(call(select,0xF7AA5,0x114680,1));
    hooks.push_back(call(mouse,0xF7B61,0x162300,0));
    hooks.push_back(call(cursor,0xF7B6D,0x162300,0));
    // The mode-bit-1 branch has its own complete sprintf result and suffix.
    hooks.push_back(call(action_prompt,0xF7AEF,0x162300,0));
    hooks.push_back(call(action_keys,0xF7AFB,0x162300,0));
    hooks.push_back(call(creature_text,0x114B64,0x10E5A0,3));
    hooks.push_back(inline_hook(creature_width,0x114B7C,{0x2B,0xCA,0x8D,0x1C,0xCB}));
}

Status dispatch(const NativeEvent& e,DispatchResult& result,bool& handled) {
    handled=true;
    std::string key;
    u32* destination;
    Scope scope=Scope::allocation;
    switch(e.id) {
    case title:
        if(e.phase==NativePhase::after) return Status::ok;
        // F78C4 chooses the fixed heading or D3DB0's caller-owned heading.
        // Three mode-4 debug callers explicitly supply an empty heading.
        if(!*ptr<const char>(e.arguments[2])) return Status::ok;
        key=e.arguments[2]==*at<u32>(0xF78DC) ? "title" :
            source_key("heading.",ptr<const char>(e.arguments[2]));
        destination=&e.arguments[2];scope=Scope::titled_panel;break;
    case exit:key="exit";destination=&e.arguments[0];break;
    case select:key="select";destination=&e.arguments[0];break;
    case mouse:key="mouse";destination=&e.frame->edx;break;
    case cursor:key="cursor";destination=&e.frame->edx;break;
    case action_prompt:
        if(e.phase==NativePhase::after) return Status::ok;
        key=source_key("prompt.",ptr<const char>(e.frame->edx));destination=&e.frame->edx;break;
    case action_keys:key="action_keys";destination=&e.frame->edx;break;
    case creature_text:
        if(e.phase==NativePhase::after) return Status::ok;
        key=creature_key(ptr<const char>(e.arguments[0]));
        // This is the original tokenizer's atom identity (2 or 4), rather
        // than a draw ordinal. Both atoms share the same native text CALL.
        native_component_binding::note_native_field(e,*at<u32>(0x5F54BB0));
        destination=&e.arguments[0];scope=Scope::text;break;
    case creature_width: {
        if(!chinese_enabled) return Status::ok;
        // 114B7C..114B7E is SUB ECX,EDX / LEA EBX,[EBX+ECX*8].
        // Keep the original byte-count result in ECX, and extend only the
        // width operand in its original current-X advance. The following
        // native stores and all +/- keycap geometry execute unchanged.
        const auto* original=ptr<const char>(e.frame->ebp-0x40C);
        std::vector<char> encoded;
        auto status=resolve_display_text(TextComponent::target_help_text,original,
            creature_key(original),encoded);
        if(status!=Status::ok) return status;
        render::Metrics measured{};status=metrics_at_outline(encoded.data(),0,measured);
        if(status!=Status::ok) return status;
        e.frame->ecx-=e.frame->edx;
        e.frame->ebx+=static_cast<u32>(measured.logical_width);
        result.skip_original=1;
        return Status::ok;
    }
    default:handled=false;return Status::ok;
    }
    if(e.phase==NativePhase::after) return Status::ok;
    std::vector<char> encoded;
    const auto status=translate(TextComponent::target_help_text,ptr<char>(*destination),key.c_str(),encoded);
    if(status!=Status::ok) return status;
    if(e.id==mouse || e.id==cursor || e.id==action_prompt || e.id==action_keys) {
        // The original 162300 tokenizer and 10EB40 paragraph keep ownership
        // of wrapping. Existing width/advance hooks consume whole glyphs.
        const auto words=native_paragraph_words(encoded.data());
        encoded.assign(words.begin(),words.end());encoded.push_back(0);
    }
    // ESC./ENTER. remain the native keycap grammar; only their suffix changes.
    return lend_text(e,encoded,*destination,scope);
}
}
