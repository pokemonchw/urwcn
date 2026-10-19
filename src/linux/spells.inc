// Linux 3.89 MagicProfile display consumers. Native spell IDs, actions,
// list geometry, texture ownership and input remain unchanged.
std::string spell_text(const std::string& key) {
    return translated(C::spells_text,"",key.c_str());
}
std::string native_paragraph_words(const std::string& text) {
    // SANATAULUKKO's space separator supplies Chinese scalar word units.
    // The native paragraph decides every wrap and line advance.
    std::string words;
    for(auto* p=reinterpret_cast<const unsigned char*>(text.c_str());*p;) {
        if(token(p)) {
            // '>' already advances the native word slot; an extra separator
            // there would create an empty word and terminate paragraph reading.
            if(!words.empty() && words.back()!=' ' && words.back()!='>') words+=' ';
            words.append(reinterpret_cast<const char*>(p),2);
            words+=' ';
            p+=2;
        } else words.push_back(*p++);
    }
    return words;
}
int renderer_text_width(render::Renderer* renderer,const char* text) {
    const auto display=native_display(text);
    int result=0;
    for(auto* p=reinterpret_cast<const unsigned char*>(display.c_str());*p;) {
        if(auto* glyph=token(p)) {
            auto request=glyph_request(*glyph,0,0,0xffffffff);
            request.renderer=renderer;
            render::Metrics metrics{};
            u32 bytes=sizeof(metrics);
            require(host->invoke(ModuleId::render,render::op::measure_renderer,
                                 &request,sizeof(request),&metrics,&bytes));
            result+=metrics.logical_width;
            p+=2;
        } else { result+=8; ++p; }
    }
    return result;
}
void renderer_paragraph_width(Frame& frame) {
    auto* renderer=*reinterpret_cast<render::Renderer**>(frame.stack()+0x30);
    frame.rdx=std::uint32_t(frame.r12)+renderer_text_width(renderer,reinterpret_cast<const char*>(frame.r14));
    frame.rax=std::uint32_t(frame.rax+frame.rbx);
}
void renderer_paragraph_advance(Frame& frame) {
    auto* renderer=*reinterpret_cast<render::Renderer**>(frame.stack()+0x30);
    frame.rdx-=frame.rbx;
    frame.r12=std::uint32_t(frame.r12)+renderer_text_width(renderer,reinterpret_cast<const char*>(frame.rbx));
}
void renderer_paragraph_space(Frame& frame) {
    // The native buffer already ends in NUL. Chinese word separators are
    // tokenizer syntax; do not append a visible Western word space.
    if(token(reinterpret_cast<const unsigned char*>(frame.r14))) frame.rax=frame.rdi;
    else frame.rax=call(frame,0x86c0);
}
void renderer_title_width(Frame& frame) {
    frame.rax=renderer_text_width(reinterpret_cast<render::Renderer*>(frame.r12),
                                 reinterpret_cast<const char*>(frame.r14));
    frame.r13=std::uint32_t(frame.r11);
}
void renderer_button_advance(Frame& frame) {
    frame.rdx-=frame.r12;
    frame.r14=std::uint32_t(frame.r14)+renderer_text_width(
        reinterpret_cast<render::Renderer*>(frame.rbp),reinterpret_cast<const char*>(frame.r12));
}
void texture_button_width(Frame& frame) {
    frame.rax=renderer_text_width(*at<render::Renderer*>(0xa916ed0),
                                 reinterpret_cast<const char*>(frame.rdi));
}
void spell_heading(Frame& frame) {
    Frame arguments=frame;
    std::string text;
    if(chinese) {
        text=spell_text("title");
        arguments.rsi=reinterpret_cast<std::uintptr_t>(text.c_str());
    }
    frame.rax=call(arguments,0x147f10);
}
void spell_help(Frame& frame) {
    frame.rax=call(frame,0x1b0130);
    if(chinese) {
        const auto site=frame.resume-host->image_base-5;
        const auto* key=site==0x106834 ? "help.general" :
            site==0x106870 ? "help.instant" : "help.initial";
        const auto words=native_paragraph_words(spell_text(key));
        native<void (*)(int,const char*)>(0x1afe00)(1,words.c_str());
    }
}
void spell_button(Frame& frame) {
    Frame arguments=frame;
    std::string text;
    if(chinese) {
        const auto* original=reinterpret_cast<const char*>(frame.r8);
        const auto prefix=std::strchr(original,'.')-original+1;
        const auto key=frame.rsi==27 ? std::string("exit") :
            "name."+std::to_string(at<int>(0x6692660)[frame.rsi-'a']);
        text=std::string(original,prefix)+spell_text(key);
        arguments.r8=reinterpret_cast<std::uintptr_t>(text.c_str());
    }
    frame.rax=call(arguments,0xf5200);
}
void spell_description(Frame& frame) {
    Frame arguments=frame;
    std::string words;
    if(chinese) {
        const auto id=at<int>(0x6692660)[frame.rbx];
        words=native_paragraph_words(spell_text("description."+std::to_string(id)));
        arguments.rsi=reinterpret_cast<std::uintptr_t>(words.c_str());
    }
    frame.rax=call(arguments,0x1afe00);
}
bool spell_footer_active;
void spell_footer(Frame& frame) {
    // This builder only draws and registers its hotspot; it never waits.
    spell_footer_active=true;
    frame.rax=call(frame,0x50110);
    spell_footer_active=false;
}
void spell_footer_text(Frame& frame) {
    Frame arguments=frame;
    const auto site=frame.resume-host->image_base-5;
    const bool button=site==0x5030c;
    std::string text;
    if(chinese && spell_footer_active) {
        const auto* key=button ? "encyclopedia" : site==0x501cb ? "footer.title" : "footer.summary";
        text=spell_text(key);
        if(button) {
            const auto* original=reinterpret_cast<const char*>(frame.r8);
            text=std::string(original,std::strchr(original,'.')-original+1)+text;
        }
        argument(arguments,button?4:3)=reinterpret_cast<std::uintptr_t>(text.c_str());
    }
    frame.rax=call(arguments,button?0xf5200:0x13e4a0);
}
void install_spells() {
    hooks->instruction(0x106777,5,spell_heading);
    for(auto site:{0x106834u,0x106870u,0x1068b7u}) hooks->instruction(site,5,spell_help);
    for(auto site:{0x106cd8u,0x106d38u}) hooks->instruction(site,5,spell_button);
    hooks->instruction(0x106a9d,5,spell_description);
    hooks->instruction(0x106d03,5,spell_footer);
    for(auto site:{0x501cbu,0x502b9u,0x5030cu}) hooks->instruction(site,5,spell_footer_text);
    // Replace only the native byte-derived measures, retaining its branches,
    // native string byte lengths, line height, colors and cursor storage.
    hooks->instruction(0x13f3d8,6,renderer_paragraph_width);
    hooks->instruction(0x13f51a,7,renderer_paragraph_advance);
    hooks->instruction(0x13f44a,5,renderer_paragraph_space);
    for(auto site:{0x147d93u,0x147eacu}) hooks->instruction(site,6,renderer_title_width);
    hooks->instruction(0x145cba,7,renderer_button_advance);
    for(auto site:{0xf5392u,0xf53b2u}) hooks->instruction(site,5,texture_button_width);
}
