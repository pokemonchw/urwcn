// F7820 owns the target dialog, direction keycaps, input and named background.
// Translate only its confirmed complete text calls; retain no page or layout.
namespace windows_target_help {
enum Hook:u32 { title=0x18500,exit,select,mouse,cursor };

void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(call(title,0xF7918,0x116270,5));
    hooks.push_back(call(exit,0xF7A88,0x114680,1));
    hooks.push_back(call(select,0xF7AA5,0x114680,1));
    hooks.push_back(call(mouse,0xF7B61,0x162300,0));
    hooks.push_back(call(cursor,0xF7B6D,0x162300,0));
}

Status dispatch(const NativeEvent& e,DispatchResult&,bool& handled) {
    handled=true;
    const char* key;
    u32* destination;
    Scope scope=Scope::allocation;
    switch(e.id) {
    case title:
        if(e.phase==NativePhase::after) return Status::ok;
        // F78C4 selects this literal only for the original mode's bit 0.
        // The other branch supplies a caller-owned action heading.
        if(e.arguments[2]!=*at<u32>(0xF78DC)) return Status::ok;
        key="title";destination=&e.arguments[2];scope=Scope::titled_panel;break;
    case exit:key="exit";destination=&e.arguments[0];break;
    case select:key="select";destination=&e.arguments[0];break;
    case mouse:key="mouse";destination=&e.frame->edx;break;
    case cursor:key="cursor";destination=&e.frame->edx;break;
    default:handled=false;return Status::ok;
    }
    if(e.phase==NativePhase::after) return Status::ok;
    std::vector<char> encoded;
    const auto status=translate(TextComponent::target_help_text,ptr<char>(*destination),key,encoded);
    if(status!=Status::ok) return status;
    if(e.id==mouse || e.id==cursor) {
        // The original 162300 tokenizer and 10EB40 paragraph keep ownership
        // of wrapping. Existing width/advance hooks consume whole glyphs.
        const auto words=native_paragraph_words(encoded.data());
        encoded.assign(words.begin(),words.end());encoded.push_back(0);
    }
    // ESC./ENTER. remain the native keycap grammar; only their suffix changes.
    return lend_text(e,encoded,*destination,scope);
}
}
