// Windows 3.89 skills and MagicProfile display consumers. The native records,
// IDs, selected actions, point accounting and resource ownership stay native.
enum WindowsSkillsHook : u32 {
    ws_heading_first=0x7600,ws_panel_first=0x7610,ws_remaining=0x7620,
    ws_improve,ws_degrade,ws_limit_improve,ws_limit_degrade,ws_limit_paragraph,
    ws_name,ws_mastery,ws_help,ws_help_paragraph,ws_confirm_first=0x7640,
    ws_heading_width=0x7650,ws_heading_text,
    wm_heading=0x7700,wm_help_first=0x7710,wm_description=0x7714,wm_button,wm_exit,
    wm_heading_text,wm_paragraph_first=0x7720
};
Status windows_skill_lend(const NativeEvent& e,TextComponent component,const std::string& key,
                         u32& destination,Scope kind,bool prefix=false,bool words=false,u32 outline=0) {
    const auto* original=ptr<char>(destination);
    const auto* suffix=prefix ? std::strchr(original,'.')+1 : original;
    std::vector<char> encoded;
    const auto status=translate(component,suffix,key.c_str(),encoded);
    if(status!=Status::ok) return status;
    if(prefix) {
        encoded.insert(encoded.begin(),original,suffix);
    }
    if(words) {
        const auto display=native_paragraph_words(encoded.data());
        encoded.assign(display.begin(),display.end());encoded.push_back(0);
    }
    return lend_text(e,encoded,destination,kind,outline);
}
Status windows_skill_help(TextComponent component,const char* key) {
    if(!chinese_enabled) return Status::ok;
    std::vector<char> encoded;
    const auto status=translate(component,"",key,encoded);
    if(status!=Status::ok) return status;
    const auto words=native_paragraph_words(encoded.data());
    using Parse=void (__fastcall *)(u32,const char*);
    reinterpret_cast<Parse>(host->image_base+0x162300)(1,words.c_str());
    return Status::ok;
}
Status dispatch_windows_skills(const NativeEvent& e,DispatchResult& result,bool& handled) {
    handled=true;
    if(e.phase==NativePhase::after) {
        if(e.id==ws_help)
            return windows_skill_help(TextComponent::skills_text,e.frame->ebx==1 ? "help.initial" : "help.general");
        if(e.id>=wm_help_first && e.id<wm_help_first+3) {
            constexpr const char* keys[]{"help.general","help.instant","help.initial"};
            return windows_skill_help(TextComponent::spells_text,keys[e.id-wm_help_first]);
        }
        handled=false;return Status::ok;
    }
    if(e.id>=ws_heading_first && e.id<ws_heading_first+2)
        return windows_skill_lend(e,TextComponent::skills_text,"title",e.frame->ecx,Scope::titled_panel);
    if(e.id>=ws_panel_first && e.id<ws_panel_first+3) {
        constexpr const char* keys[]{"lore","physical","combat"};
        return windows_skill_lend(e,TextComponent::skills_text,keys[e.id-ws_panel_first],e.arguments[2],Scope::profile_panel);
    }
    if(e.id>=ws_confirm_first && e.id<ws_confirm_first+4) {
        constexpr const char* keys[]{"confirm.title","confirm.question","confirm.yes","confirm.no"};
        return windows_skill_lend(e,TextComponent::skills_text,keys[e.id-ws_confirm_first],e.frame->edx,
            Scope::allocation,e.id>=ws_confirm_first+2);
    }
    if(e.id>=wm_paragraph_first && e.id<wm_paragraph_first+3) {
        begin(e,Scope::hud_renderer_text,e.arguments[4]&1u);return Status::ok;
    }
    switch(e.id) {
    case ws_remaining:
        return windows_skill_lend(e,TextComponent::skills_text,"remaining",e.arguments[0],Scope::text);
    case ws_improve:case ws_degrade:
        return windows_skill_lend(e,TextComponent::skills_text,e.id==ws_improve ? "improve" : "degrade",
            e.arguments[0],Scope::setup_exit,true,false,*at<u32>(0x61BBA54)&1u);
    case ws_limit_improve:case ws_limit_degrade: {
        if(!chinese_enabled) return Status::ok;
        const bool improve=e.id==ws_limit_improve;
        std::vector<char> encoded;
        auto status=translate(TextComponent::skills_text,"",improve ? "limit.improve" : "limit.degrade",encoded);
        if(status!=Status::ok) return status;
        std::string display(encoded.data());
        display.replace(display.find("{value}"),7,std::to_string(*at<unsigned char>(improve ? 0x1D7F451 : 0x1D7F452)));
        const auto words=native_paragraph_words(display.c_str());
        encoded.assign(words.begin(),words.end());encoded.push_back(0);
        return lend_text(e,encoded,e.frame->edx,Scope::allocation);
    }
    case ws_limit_paragraph:case ws_help_paragraph:
        begin(e,Scope::paragraph,e.arguments[3]);return Status::ok;
    case ws_name: {
        const auto* label=ptr<char>(e.arguments[1]);
        return windows_skill_lend(e,TextComponent::skills_text,std::string("name.")+(std::strchr(label,'.')+1),
            e.arguments[1],Scope::setup_exit,true,false,*at<u32>(0x5F54A9C)&1u);
    }
    case ws_mastery:
        return windows_skill_lend(e,TextComponent::skills_text,std::string("level.")+ptr<char>(e.arguments[2]),
            e.arguments[2],Scope::allocation);
    case ws_heading_width:
        if(native_name_input::contains_display(ptr<char>(e.frame->edi))) {
            render::Metrics measured{};
            const auto status=metrics(ptr<char>(e.frame->edi),measured);
            if(status!=Status::ok) return status;
            e.frame->eax=static_cast<u32>(measured.logical_width);
            e.frame->edx=static_cast<std::int32_t>(e.frame->eax)<0 ? 0xffffffffu : 0;
            result.skip_original=1;
        }
        return Status::ok;
    case ws_heading_text:
        if(native_name_input::contains_display(ptr<char>(e.arguments[0]))) return centered_text(e);
        return Status::ok;
    case wm_heading:
        return windows_skill_lend(e,TextComponent::spells_text,"title",e.frame->edx,Scope::allocation);
    case wm_description:
        return windows_skill_lend(e,TextComponent::spells_text,
            "description."+std::to_string(at<u32>(0x5F5CD48)[e.frame->esi]),
            e.frame->edx,Scope::allocation,false,true);
    case wm_button:
        return windows_skill_lend(e,TextComponent::spells_text,
            "name."+std::to_string(at<u32>(0x5F5CD48)[e.frame->ebx]),
            e.arguments[2],Scope::allocation,true);
    case wm_exit:
        return windows_skill_lend(e,TextComponent::spells_text,"exit",e.arguments[2],Scope::allocation,true);
    case wm_heading_text:
        begin(e,Scope::hud_renderer_text,e.arguments[3]&1u);return Status::ok;
    case ws_help:
        return Status::ok;
    default:
        if(e.id>=wm_help_first && e.id<wm_help_first+3) return Status::ok;
        break;
    }
    handled=false;return Status::ok;
}
void append_windows_skills_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(call(ws_heading_first,0xE0789,0xF8F80,0));
    hooks.push_back(call(ws_heading_first+1,0xE0BC5,0xF8F80,0));
    constexpr u32 panels[]{0xE0882,0xE09A1,0xE0AD3};
    for(u32 i=0;i<std::size(panels);++i) hooks.push_back(call(ws_panel_first+i,panels[i],0x116270,5));
    hooks.push_back(call(ws_remaining,0x11DA2,0x10E5A0,3));
    hooks.push_back(call(ws_improve,0x11EC3,0x114680,1));
    hooks.push_back(call(ws_degrade,0x11ED8,0x114680,1));
    hooks.push_back(call(ws_limit_improve,0x11E2C,0x162300,0));
    hooks.push_back(call(ws_limit_degrade,0x11E54,0x162300,0));
    hooks.push_back(call(ws_limit_paragraph,0x11E89,0x10EB40,4));
    hooks.push_back(call(ws_name,0xE06A7,0xCFAF0,2));
    hooks.push_back(call(ws_mastery,0xE0523,0x10D0,3));
    hooks.push_back(call(ws_help,0xE0CA4,0x162530,0));
    hooks.push_back(call(ws_help_paragraph,0xE0CBE,0x10EB40,4));
    constexpr u32 confirmations[]{0x121F5,0x12205,0x12220,0x12239};
    for(u32 i=0;i<std::size(confirmations);++i)
        hooks.push_back(call(ws_confirm_first+i,confirmations[i],i ? 0xCF990 : 0xCF790,i ? 0 : 5));
    hooks.push_back(inline_hook(ws_heading_width,0xF9006,{0xC1,0xE0,0x03,0x99,0x2B,0xC2}));
    hooks.push_back(call(ws_heading_text,0xF9019,0x10E5A0,3));
    hooks.push_back(call(wm_heading,0xDF9C1,0x113430,0));
    constexpr u32 help[]{0xDFA5E,0xDFABC,0xDFB03};
    for(u32 i=0;i<std::size(help);++i) hooks.push_back(call(wm_help_first+i,help[i],0x162530,0));
    hooks.push_back(call(wm_description,0xDFCB8,0x162300,0));
    hooks.push_back(call(wm_button,0xDFF85,0xCFD10,3));
    hooks.push_back(call(wm_exit,0xDFFEC,0xCFD10,3));
    constexpr u32 paragraphs[]{0xDFAA6,0xDFB4B,0xDFD10};
    for(u32 i=0;i<std::size(paragraphs);++i) hooks.push_back(call(wm_paragraph_first+i,paragraphs[i],0x10EFD0,5));
}
