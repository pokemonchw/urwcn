// Linux 3.89 TaitoRuutu / NaytaOptioRuutu display boundaries.
// Native skill records, option accounting, actions and UI geometry stay native.
std::string skills_text(const std::string& key) {
    return translated(C::skills_text,"",key.c_str());
}
struct SkillsBinding {
    u32 site,target;
    const char* key;
    unsigned argument,arguments=6;
};
const SkillsBinding skills_bindings[]{
    {0x107ea8,0x1224c0,"title",0},
    {0x108325,0x1224c0,"title",0},
    {0x107f72,0x1471a0,"lore",4,7},
    {0x10808f,0x1471a0,"physical",4,7},
    {0x1081aa,0x1471a0,"combat",4,7},
    {0x1e647,0x13e8b0,"remaining",2},
    {0x1e723,0x144fb0,"improve",2},
    {0x1e739,0x144fb0,"degrade",2},
};
void skills_bound(Frame& frame) {
    const auto site=frame.resume-host->image_base-5;
    const SkillsBinding* binding=nullptr;
    for(const auto& entry:skills_bindings) if(entry.site==site) { binding=&entry; break; }
    Frame arguments=frame;
    std::string display;
    if(chinese) {
        display=skills_text(binding->key);
        if(binding->target==0x144fb0) {
            const auto* original=reinterpret_cast<const char*>(frame.rdx);
            display=std::string(original,std::strchr(original,'.')-original+1)+display;
        }
        argument(arguments,binding->argument)=reinterpret_cast<std::uintptr_t>(display.c_str());
    }
    frame.rax=call(arguments,binding->target,binding->arguments,frame);
}
void skills_name(Frame& frame) {
    Frame arguments=frame;
    std::string display;
    if(chinese) {
        // AsetaTaito has already resolved the keycap and TEXTILECRAFT label.
        // Borrow the complete LIST_ButtonSpotEntry argument so its native
        // draw, textwidth, selection and hit area all consume the same text.
        const auto* original=reinterpret_cast<const char*>(frame.rcx);
        const auto prefix=std::strchr(original,'.')-original+1;
        display=std::string(original,prefix)+skills_text(std::string("name.")+(original+prefix));
        arguments.rcx=reinterpret_cast<std::uintptr_t>(display.c_str());
    }
    frame.rax=call(arguments,0xf4f50);
}
void skills_mastery(Frame& frame) {
    // The original taitoteksti_perus call selected the descriptor; keep its
    // thresholds and original (%s) format, replacing only this display value.
    const auto* original=reinterpret_cast<const char*>(frame.r8);
    const auto display=chinese ? skills_text(std::string("level.")+original) : std::string(original);
    using Format=int (*)(char*,int,std::size_t,const char*,...);
    frame.rax=native<Format>(0x8f80)(reinterpret_cast<char*>(frame.rdi),frame.rsi,frame.rdx,
        reinterpret_cast<const char*>(frame.rcx),display.c_str());
}
void skills_help(Frame& frame) {
    frame.rax=call(frame,0x1b0130);
    if(chinese) {
        const auto site=frame.resume-host->image_base-5;
        const auto words=native_paragraph_words(skills_text(site==0x1087ab ? "help.initial" : "help.general"));
        native<void (*)(int,const char*)>(0x1afe00)(1,words.c_str());
    }
}
void skills_limit(Frame& frame) {
    Frame arguments=frame;
    std::string words;
    if(chinese) {
        const bool improve=frame.resume-host->image_base-5==0x1e6a5;
        auto display=skills_text(improve ? "limit.improve" : "limit.degrade");
        const auto count=*at<unsigned char>(improve ? 0x6691e14 : 0x6691e15);
        display.replace(display.find("{value}"),7,std::to_string(count));
        words=native_paragraph_words(display);
        arguments.rsi=reinterpret_cast<std::uintptr_t>(words.c_str());
    }
    frame.rax=call(arguments,0x1afe00);
}
void software_paragraph_space(Frame& frame) {
    // 13EF06 has copied the complete word and its NUL. Chinese tokenizer
    // separators must not become visible Western spaces in measure or draw.
    if(token(reinterpret_cast<const unsigned char*>(frame.rbp))) frame.rax=frame.rdi;
    else frame.rax=call(frame,0x86c0);
}
void install_skills() {
    for(const auto& binding:skills_bindings) hooks->instruction(binding.site,5,skills_bound);
    hooks->instruction(0x107db2,5,skills_name);
    hooks->instruction(0x107bc9,5,skills_mastery);
    for(auto site:{0x10856au,0x1087abu}) hooks->instruction(site,5,skills_help);
    for(auto site:{0x1e6a5u,0x1e790u}) hooks->instruction(site,5,skills_limit);
    hooks->instruction(0x13ef3d,5,software_paragraph_space);
    // Existing encyclopedia preview consumers translate title, synopsis and
    // F1 caption. GameInfo_Hotspot still receives the native English keyword.
    hooks->around(0x1084cb,culture_preview_scope,false);
}
