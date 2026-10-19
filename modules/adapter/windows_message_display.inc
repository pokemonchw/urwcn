// Windows 3.89 F6510 message display and F5B00 continuation controls.
// Evidence: docs/evidence/settlement-ghidra.c and build/windows-text-disassembly.txt.
// The native message loop owns wrapping, scrolling, pagination and its pixels.
namespace windows_message_display {
enum Hook : u32 {
    character=0xb300,word_fit,tail_fit,word_advance,tail_advance,
    word_draw,tail_draw,continuation
};

void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    using native_name_input::native_call;
    hooks.push_back(instruction(character,0xf6be0,
        {0x89,0x44,0x24,0x18,0x88,0x44,0x24,0x1c}));
    hooks.push_back(instruction(word_fit,0xf6c3c,{0x2b,0xca,0x8d,0x04,0xc8}));
    hooks.push_back(instruction(tail_fit,0xf6d00,{0x2b,0xce,0x8d,0x04,0xc8}));
    // The native word is cleared at F6CBF, before its old strlen*8 advance.
    // Measure at F6CB8 while the complete native word is still available.
    auto advance=instruction(word_advance,0xf6cb8,{0xa1,0,0,0,0,0x2b,0xca});
    const auto native_x=address(at<u32>(0x61a8cb8));
    std::memcpy(advance.expected+1,&native_x,4);
    hooks.push_back(advance);
    hooks.push_back(instruction(tail_advance,0xf6d80,{0x2b,0xca,0x8d,0x04,0xc8}));
    hooks.push_back(native_call(word_draw,0xf6ca1,0x10e5a0,3));
    hooks.push_back(native_call(tail_draw,0xf6d64,0x10e5a0,3));
    hooks.push_back(native_call(continuation,0xf5ba9,0x114680,1));
}

Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=event.id>=character && event.id<=continuation;
    if(!handled || event.phase==NativePhase::after) return Status::ok;
    if(event.id==continuation) {
        // F5B9B selects precisely these two original labels: counter 100
        // requests acknowledgement; the other branch offers more/skip.
        const auto component=event.arguments[0]==address(at<char>(0x1a9d94)) ?
            TextComponent::message_continue : TextComponent::message_more;
        std::vector<char> encoded;
        const auto status=translate(component,ptr<char>(event.arguments[0]),nullptr,encoded);
        if(status!=Status::ok) return status;
        return lend_text(event,encoded,event.arguments[0],Scope::plain_button);
    }
    const auto* message=windows_messages::current(event.frame->ebp);
    if(!message || message->kind!=Scope::message_body) return Status::ok;
    if(event.id==word_draw || event.id==tail_draw) {
        // Both projected languages use the same native word, metrics and
        // immediate native-surface glyph consumer, including ASCII words.
        event.arguments[0]=address(windows_messages::word(windows_messages::display(event.frame->ebp)));
        begin(event,Scope::text,event.arguments[2]);
        return Status::ok;
    }
    if(event.id==character) {
        const auto* source=reinterpret_cast<const unsigned char*>(windows_messages::source(
            windows_messages::display(event.frame->ebp)))+event.frame->ebx;
        auto* single=ptr<unsigned char>(event.frame->esp+0x1c);
        auto* boundary=ptr<u32>(event.frame->esp+0x18);
        if(native_name_input::transport(source)) {
            single[0]=source[0];single[1]=source[1];single[2]=0;
            ++event.frame->ebx;
            // F6C14 consumes this flag after copying the complete character
            // into the native word. It takes the existing word boundary
            // branch without inserting a visible or recorded space.
            *boundary=' ';
        } else {
            // EAX already holds the native colour-marker/@ suppression.
            *boundary=event.frame->eax;
            single[0]=static_cast<unsigned char>(event.frame->eax);
            single[1]=0;
        }
        result.resume_rva=0xf6be8;
        return Status::ok;
    }
    render::Metrics measured{};
    auto* word=windows_messages::word(windows_messages::display(event.frame->ebp));
    const auto status=metrics_at_outline(word,0,measured);
    if(status!=Status::ok) return status;
    const auto width=static_cast<u32>(measured.logical_width);
    switch(event.id) {
    case word_fit:
        event.frame->ecx-=event.frame->edx;
        event.frame->eax+=width;
        result.resume_rva=0xf6c41;
        break;
    case tail_fit:
        event.frame->ecx-=event.frame->esi;
        event.frame->eax+=width;
        result.resume_rva=0xf6d05;
        break;
    case word_advance:
        event.frame->ecx-=event.frame->edx;
        event.frame->eax=*at<u32>(0x61a8cb8)+width;
        *word=0;
        // Rejoin the original MOV [message_x],EAX after implementing its
        // word clear and replacing only the byte-based width expression.
        result.resume_rva=0xf6cc9;
        break;
    case tail_advance:
        event.frame->ecx-=event.frame->edx;
        event.frame->eax+=width;
        result.resume_rva=0xf6d85;
        break;
    default: break;
    }
    return Status::ok;
}
}
