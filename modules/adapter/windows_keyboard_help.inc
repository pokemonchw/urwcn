// 103A30 owns this entire scrollable reference, its two native drawing
// targets, cached body, viewport and input loop. These are text CALL identities,
// not screen rows. No page content, positions or drawing sequence is retained.
namespace windows_keyboard_help {
using View=native_language_redraw::View;
// The message-format range starts at B600 and contains 900+ source records.
// Keep this page's resident Hook identities outside that existing range.
enum Hook:u32 { text_first=0x18000,construction_begin=0x18100,body_cache,
    construction_end,input_result,footer_panel,footer_width,footer_height,section_first=0x18110 };
enum class Kind { text,words,dot,period,alternatives,bracket,scroll,direction,direction_dot,section_text };
constexpr u32 section_panels[]{0x103CC0,0x1046DC,0x1048C5,0x104A9F};
constexpr const char* section_keys[]{"movement","looking","picking","inventory"};
extern "C" {
std::uintptr_t uwcn_keyboard_help_construct_target{};
}
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_keyboard_help_reconstruct() {
    // 103AA2 is entered with the four completed 103A97 blit arguments still
    // on the stack. 103AC4 removes them together with the new SDL arguments.
    // The balanced 10539B input continuation must establish that same depth.
    __asm__ __volatile__("subl $16,%esp\n\tjmp *_uwcn_keyboard_help_construct_target\n\t");
}
struct TextCall {u32 site,target;const char* key;Kind kind;};
constexpr TextCall text_calls[]{
    {0x103B37,0x114D20,"scroll",Kind::scroll},
    {0x103B52,0x114D20,"exit",Kind::bracket},
    {0x103C37,0x162300,"introduction.1",Kind::words},
    {0x103C43,0x162300,"introduction.2",Kind::words},
    {0x103CDB,0x10E260,"movement",Kind::section_text},
    {0x103D4F,0x10E260,"north",Kind::direction},
    {0x103E04,0x10E260,"northwest",Kind::direction},
    {0x103E9C,0x10E260,"west",Kind::direction},
    {0x103F51,0x10E260,"southwest",Kind::direction},
    {0x103FE2,0x10E260,"south",Kind::direction},
    {0x104064,0x114D20,"northeast",Kind::direction_dot},
    {0x1040FE,0x114D20,"east",Kind::direction_dot},
    {0x104158,0x114D20,"southeast",Kind::direction_dot},
    {0x104175,0x114D20,"strafe",Kind::text},
    {0x104193,0x162300,"movement.keys",Kind::words},
    {0x10419F,0x162300,"movement.keys",Kind::words},
    {0x1041AB,0x162300,"movement.facing",Kind::words},
    {0x1041B7,0x162300,"movement.switch",Kind::words},
    {0x10427F,0x114D20,"map_switch",Kind::dot},
    {0x104313,0x114D20,"wait_turn",Kind::period},
    {0x104334,0x114D20,"movement_actions",Kind::alternatives},
    {0x104396,0x10E260,"movement.hotkeys",Kind::text},
    {0x10442F,0x114D20,"run",Kind::dot},
    {0x1044BF,0x114D20,"hide",Kind::dot},
    {0x10454F,0x114D20,"posture",Kind::dot},
    {0x1045E2,0x114D20,"rest",Kind::dot},
    {0x1045FB,0x114D20,"rest_fatigue",Kind::bracket},
    {0x104691,0x114D20,"sleep",Kind::dot},
    {0x1046F8,0x10E260,"looking",Kind::section_text},
    {0x10471D,0x114D20,"look_selected",Kind::alternatives},
    {0x1047AF,0x114D20,"look_direction",Kind::dot},
    {0x104842,0x114D20,"look_current",Kind::dot},
    {0x10485F,0x10E260,"zoom_hint",Kind::text},
    {0x104877,0x114D20,"zoom_keys",Kind::text},
    {0x1048E3,0x10E260,"picking",Kind::section_text},
    {0x104904,0x114D20,"pick_up",Kind::alternatives},
    {0x104925,0x114D20,"pick_adjacent",Kind::alternatives},
    {0x1049BF,0x114D20,"haul",Kind::dot},
    {0x104A51,0x114D20,"push_pack",Kind::dot},
    {0x104AB8,0x10E260,"inventory",Kind::section_text},
    {0x104B4F,0x114D20,"inventory_view",Kind::dot},
    {0x104BDF,0x114D20,"drop",Kind::dot},
    {0x104C71,0x114D20,"wield",Kind::dot},
    {0x104D00,0x114D20,"wear",Kind::dot},
    {0x104D97,0x114D20,"apply",Kind::dot},
    {0x104DB5,0x114D20,"take_off",Kind::dot},
    {0x104DD6,0x114D20,"eat",Kind::dot},
    {0x104DF4,0x114D20,"drink",Kind::dot},
    {0x104E10,0x115AD0,"interacting",Kind::text},
    {0x104E31,0x114D20,"skills",Kind::dot},
    {0x104E4F,0x114D20,"craft",Kind::alternatives},
    {0x104E70,0x114D20,"repeat_action",Kind::dot},
    {0x104E8E,0x114D20,"modded_craft",Kind::dot},
    {0x104EAF,0x114D20,"open",Kind::dot},
    {0x104ECD,0x114D20,"close",Kind::dot},
    {0x104EEE,0x114D20,"fire",Kind::dot},
    {0x104F0C,0x114D20,"butcher",Kind::dot},
    {0x104F2D,0x114D20,"chat",Kind::dot},
    {0x104F4B,0x114D20,"command",Kind::dot},
    {0x104F67,0x115AD0,"combat",Kind::text},
    {0x104F88,0x114D20,"attack_first",Kind::dot},
    {0x104FA6,0x114D20,"attack_second",Kind::dot},
    {0x104FC4,0x114D20,"repeat_attack",Kind::dot},
    {0x104FE5,0x114D20,"kick",Kind::dot},
    {0x105003,0x114D20,"punch",Kind::dot},
    {0x105021,0x114D20,"exchange_weapons",Kind::dot},
    {0x105042,0x114D20,"throw_shoot",Kind::dot},
    {0x10505E,0x115AD0,"information",Kind::text},
    {0x10507F,0x114D20,"encyclopedia",Kind::dot},
    {0x1050A0,0x114D20,"quest_journal",Kind::dot},
    {0x1050BE,0x114D20,"look_distant",Kind::dot},
    {0x1050DF,0x114D20,"spells",Kind::dot},
    {0x1050FD,0x114D20,"game_course",Kind::dot},
    {0x10511E,0x114D20,"armour",Kind::dot},
    {0x10513C,0x114D20,"profile",Kind::dot},
    {0x10515D,0x114D20,"injuries",Kind::dot},
    {0x105179,0x115AD0,"options",Kind::text},
    {0x10519A,0x114D20,"options",Kind::dot},
    {0x1051D8,0x10E260,"options.hotkeys",Kind::text},
    {0x1051F9,0x114D20,"encyclopedia",Kind::dot},
    {0x10520E,0x114D20,"keyboard_list",Kind::dot},
    {0x105238,0x114D20,"save",Kind::bracket},
    {0x105256,0x114D20,"quit",Kind::dot},
    {0x105265,0x162300,"conclusion",Kind::words}
};

Status localized(const char* original,const std::string& key,std::vector<char>& encoded) {
    return resolve_display_text(TextComponent::keyboard_help_text,original,key.c_str(),encoded);
}
Status text(const NativeEvent& e,const TextCall& call) {
    auto& destination=call.kind==Kind::words ? e.frame->edx :
        e.arguments[call.target==0x115AD0 ? 2 : 1];
    if(!chinese_enabled) return Status::ok;
    const std::string original=ptr<char>(destination);
    std::string key=call.key;
    if(call.kind==Kind::direction || call.kind==Kind::direction_dot)
        key=std::string(*at<unsigned char>(0x5F5AE67) ? "traditional." : "facing.")+key;
    if(call.site==0x1041B7 && *at<unsigned char>(0x5F5AE67)) key="movement.switch_facing";
    std::vector<char> encoded;
    auto status=localized(original.c_str(),key,encoded);
    if(status!=Status::ok) return status;
    switch(call.kind) {
    case Kind::period:
        // 114D81..114DA5 explicitly preserves the leading ".." key grammar.
        encoded.insert(encoded.begin(),original.begin(),original.begin()+2);break;
    case Kind::dot:case Kind::direction_dot: {
        const auto end=original.find('.')+1;
        encoded.insert(encoded.begin(),original.begin(),original.begin()+end);break;
    }
    case Kind::alternatives: {
        // 165340 emits two original ASCII keycaps, joined by " or ".
        // Translate that conjunction while retaining both native key tokens.
        const auto split=original.find(" or "),end=original.rfind(']')+1;
        std::vector<char> conjunction;
        status=localized(" or ","or",conjunction);
        if(status!=Status::ok) return status;
        std::vector<char> prefix(original.begin(),original.begin()+split);
        prefix.insert(prefix.end(),conjunction.begin(),conjunction.end()-1);
        prefix.insert(prefix.end(),original.begin()+split+4,original.begin()+end);
        encoded.insert(encoded.begin(),prefix.begin(),prefix.end());break;
    }
    case Kind::bracket: {
        const auto end=original.rfind(']')+1;
        encoded.insert(encoded.begin(),original.begin(),original.begin()+end);break;
    }
    case Kind::scroll:
        encoded.insert(encoded.end()-1,original.begin()+original.find('['),original.end());break;
    case Kind::words: {
        const auto words=native_paragraph_words(encoded.data());
        encoded.assign(words.begin(),words.end());encoded.push_back(0);break;
    }
    default:break;
    }
    // ASCII keycaps retain the original bitmap and byte-count geometry.
    // Only transported Chinese fragments enter the existing glyph/width ABI.
    return lend_text(e,encoded,destination,Scope::allocation);
}

void invalidate_body() {
    // This is 103BC9's original movement-mode cache discriminator and its
    // actual texture owner. Retire pixels through SDL; retain no shadow copy.
    if(const auto texture=*at<u32>(0xA44B798)) native_targets::destroy_component_texture(texture);
    *at<u32>(0xA44B798)=0;
    *at<u32>(0x1EBCB0)=0xFFFFFFFFu;
}
Status rebuild(const NativeEvent& e,DispatchResult& result) {
    // 105396 has returned: the main renderer is unbound, EBX is the viewport,
    // EDI is the optional body renderer and [EBP-43C] its optional surface.
    // Release exactly the resources released by 1054BA..1054EC, then let the
    // original construction and scrolling loop run again in this same frame.
    native_targets::destroy_component_texture(e.frame->ebx);
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x113400)();
    if(e.frame->edi) (*at<void (__cdecl *)(void*)>(0x18C218))(ptr<void>(e.frame->edi));
    if(const auto surface=*ptr<u32>(e.frame->ebp-0x43C)) native_targets::destroy_component_surface(surface);
    *ptr<u32>(e.frame->ebp-0x43C)=0;
    *at<u32>(0xA44B794)=*ptr<u32>(e.frame->ebp-0x414);
    *at<u32>(0x5F55634)=*ptr<u32>(e.frame->ebp-0x438);
    // Re-establish the original 103A43..103A6A color locals. 1052E2 saves
    // the unchanged game-speed value again after the native drawing phase.
    *ptr<u32>(e.frame->ebp-0x438)=*at<u32>(0x18EF5C);
    e.frame->edi=*at<u32>(0x1E87A4);
    *ptr<u32>(e.frame->ebp-0x434)=e.frame->edi;
    result.resume_rva=static_cast<u32>(
        reinterpret_cast<std::uintptr_t>(&uwcn_keyboard_help_reconstruct)-host->image_base);
    return Status::ok;
}
void append_hooks(std::vector<HookSpec>& hooks) {
    uwcn_keyboard_help_construct_target=host->image_base+0x103AA2;
    for(u32 i=0;i<std::size(text_calls);++i) {
        const auto& c=text_calls[i];
        hooks.push_back(call(text_first+i,c.site,c.target,
            c.target==0x162300 ? 0 : 4));
    }
    for(u32 i=0;i<std::size(section_panels);++i)
        hooks.push_back(call(section_first+i,section_panels[i],0x1166C0,6));
    hooks.push_back(inline_hook(construction_begin,0x103AA2,{0x6A,0,0x6A,0,0x6A,0}));
    auto cache=inline_hook(body_cache,0x103BBF,{0x0F,0xB6,0x05,0,0,0,0});
    const auto movement=address(at<void>(0x5F5AE67));std::memcpy(cache.expected+3,&movement,4);hooks.push_back(cache);
    auto end=inline_hook(construction_end,0x1052D0,{0xA1,0,0,0,0});
    const auto scroll=address(at<void>(0xA44B794));std::memcpy(end.expected+1,&scroll,4);hooks.push_back(end);
    hooks.push_back(inline_hook(input_result,0x10539B,{0x8B,0xD0,0x83,0xFA,0xD6}));
    hooks.push_back(call(footer_panel,0x103B05,0x1166C0,6));
    auto width=inline_hook(footer_width,0x103B97,{0xA3,0,0,0,0});
    auto height=inline_hook(footer_height,0x103BB4,{0xA3,0,0,0,0});
    const auto native_width=address(at<void>(0xA2110E8)),native_height=address(at<void>(0xA2110EC));
    std::memcpy(width.expected+1,&native_width,4);std::memcpy(height.expected+1,&native_height,4);
    hooks.push_back(width);hooks.push_back(height);
}
Status dispatch(const NativeEvent& e,DispatchResult& result,bool& handled) {
    handled=true;
    if(e.id>=text_first && e.id<text_first+std::size(text_calls)) {
        const auto& call=text_calls[e.id-text_first];
        if(e.phase==NativePhase::after) return Status::ok;
        if(call.kind==Kind::section_text) {result.skip_original=chinese_enabled ? 1u : 0u;return Status::ok;}
        return text(e,call);
    }
    if(e.phase==NativePhase::after) {handled=false;return Status::ok;}
    if(e.id>=section_first && e.id<section_first+std::size(section_panels)) {
        if(!chinese_enabled) return Status::ok;
        std::vector<char> title;
        const auto status=localized("",section_keys[e.id-section_first],title);
        if(status!=Status::ok) return status;
        // Use the same complete native centered section constructor already
        // used by the lower four sections, with this actual bar's own inputs.
        const native_renderer_component_calls::SectionCall section{
            static_cast<u32>(host->image_base+0x115AD0),e.frame->ecx,
            static_cast<std::int32_t>(e.frame->edx),static_cast<std::int32_t>(e.arguments[0]),
            static_cast<std::int32_t>(e.arguments[1]),title.data(),5};
        native_renderer_component_calls::uwcn_renderer_section(&section);
        result.skip_original=1;return Status::ok;
    }
    switch(e.id) {
    case construction_begin:native_component_binding::begin_parser_owner();return Status::ok;
    case body_cache:
        if(native_language_redraw::pending(View::keyboard_help)) invalidate_body();
        return Status::ok;
    case construction_end:
        native_component_binding::end_parser_owner();
        native_language_redraw::completed(View::keyboard_help);return Status::ok;
    case input_result:
        if(native_language_redraw::pending(View::keyboard_help)) return rebuild(e,result);
        return Status::ok;
    case footer_panel: {
        const auto* surface=ptr<render::Surface>(e.frame->ebx);
        const auto source=native_targets::component_surface_source(surface);
        // Preserve the native panel's actual inset, measured before this CALL.
        e.arguments[1]=source.width;
        e.arguments[2]=source.height-(surface->h-static_cast<std::int32_t>(e.arguments[2]));
        return Status::ok;
    }
    case footer_width:case footer_height: {
        const auto source=native_targets::component_surface_source(ptr<void>(e.frame->ebx));
        e.frame->eax=e.id==footer_width ? source.width : source.height;return Status::ok;
    }
    default:handled=false;return Status::ok;
    }
}
}
