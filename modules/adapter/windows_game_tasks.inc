// Windows 3.89.1: 15DC70 reads the game's unchanged taskdata.urw records;
// 15D770 consumes their title, four objective/completion records and key hints.
// These are complete native text calls, with no retained page or geometry.
namespace windows_game_tasks {
enum Hook:u32 { text_first=0x18A00,words_first=0x18A20,paragraph_first=0x18A40,
    row=0x18A50,command,bonus_button_first=0x18A60 };
struct TextCall {u32 site,target,argument;};
constexpr TextCall texts[]{
    {0x15DDC5,0xF8F80,0},
    {0x15DDE7,0x116270,2},
    {0x15D836,0x10E5A0,0},
    {0x15D857,0x115E70,2},
    {0x15D8D3,0x115E70,2},
    {0x15DAF5,0x10E5A0,0},
    {0x15DB16,0x115E70,2},
    {0x15D3AB,0x115E70,2},
    {0x15D6F5,0x115E70,2},
    {0x15DA44,0x114680,0},
    {0x15DC3B,0x114680,0}
};
constexpr u32 words[]{0x15D869,0x15D877,0x15D9A8,0x15D9B4,0x15D9C0,
    0x15D9CC,0x15D9D8,0x15D9E4,0x15D9F0,0x15D9FC,0x15DA08,
    0x15DB28,0x15DB36,0x15DBA9,0x15D3BD,0x15D3C9,0x15D707,0x15D713};
constexpr u32 paragraphs[]{0x15D8A0,0x15DA7F,0x15DB7A,0x15DBE1,0x15D407,0x15D74B};
constexpr u32 bonus_buttons[]{0x15D49C,0x15D4B3,0x15D4CA};

void append_hooks(std::vector<HookSpec>& hooks) {
    if(!windows_build::is_3891()) return;
    for(u32 i=0;i<std::size(texts);++i) {
        const auto& c=texts[i];
        hooks.push_back(call(text_first+i,c.site,c.target,
            c.target==0xF8F80 ? 0 : c.target==0x116270 ? 5 :
            c.target==0x115E70 ? 4 : c.target==0x114680 ? 1 : 3));
    }
    for(u32 i=0;i<std::size(words);++i) hooks.push_back(call(words_first+i,words[i],0x162300,0));
    for(u32 i=0;i<std::size(paragraphs);++i) hooks.push_back(call(paragraph_first+i,paragraphs[i],0x10EB40,4));
    hooks.push_back(call(row,0x15DEDB,0x114680,1));
    hooks.push_back(call(command,0x15D948,0x114680,1));
    for(u32 i=0;i<std::size(bonus_buttons);++i)
        hooks.push_back(call(bonus_button_first+i,bonus_buttons[i],0xCFAF0,2));
    // 15D936 -> 10E720 is already owned by binding's 5507 complete CALL.
}

native_text_resource::TextSource source(const char* original,const char* domain) {
    return native_text_resource::from_request({TextComponent::message_value,original,domain});
}
Status display(const NativeEvent& e,u32& destination,const char* domain,Scope scope,bool key=false) {
    const auto* original=ptr<const char>(destination);
    const auto* suffix=key ? std::strchr(original,'.')+1 : original;
    std::string neutral;
    auto status=decode_parser_original(suffix,neutral);
    if(status!=Status::ok) return status;
    auto text=source(neutral.c_str(),domain);
    if(key) text.prefix.assign(original,suffix);
    native_component_binding::bind_source(e,text);
    if(scope==Scope::setup_exit) native_menu_component::bind_constructor_row(e.token,text);
    if(!chinese_enabled) return Status::ok;
    std::vector<char> encoded;
    status=native_text_resource::resolve_source(text,resolve_display_text,encode_component_original,encoded);
    return status==Status::ok ? lend_text(e,encoded,destination,scope,
        scope==Scope::text ? e.arguments[2] : 0) : status;
}
Status compound(const NativeEvent& e) {
    // 165340's actual alternatives are [key] or [key] plus a command.
    // Keep both accepted key tokens. 10E720 still parses, positions and
    // advances its keycaps and complete text leaves using their real widths.
    const std::string original=ptr<const char>(e.arguments[0]);
    const auto first=original.find(']')+1;
    const auto second=original.find('[',first);
    const auto last=original.find(']',second)+1;
    const auto description=original.find_first_not_of(' ',last);
    const auto expression=native_message_source::concat({
        native_message_source::original(original.substr(0,first)),
        message_source_lookup("game_task.command",original.substr(first,second-first).c_str()),
        native_message_source::original(original.substr(second,description-second)),
        message_source_lookup("hud.command",original.c_str()+description)});
    native_component_binding::bind_source(e,windows_inventory::expression(original.c_str(),expression));
    if(!chinese_enabled) return Status::ok;
    std::string utf8;auto status=message_project_source(expression,true,utf8);
    if(status!=Status::ok) return status;
    std::vector<char> encoded;status=encode_component_original(utf8.c_str(),encoded);
    return status==Status::ok ? lend_text(e,encoded,e.arguments[0],Scope::ancestors_select) : status;
}
Status dispatch(const NativeEvent& e,DispatchResult&,bool& handled) {
    const bool compound_call=e.id==0x5507;
    const bool text_call=e.id>=text_first && e.id<text_first+std::size(texts);
    const bool parser=e.id>=words_first && e.id<words_first+std::size(words);
    const bool paragraph=e.id>=paragraph_first && e.id<paragraph_first+std::size(paragraphs);
    const bool bonus=e.id>=bonus_button_first && e.id<bonus_button_first+std::size(bonus_buttons);
    handled=windows_build::is_3891() && (compound_call || text_call || parser || paragraph || bonus || e.id==row || e.id==command);
    if(!handled) return Status::ok;
    if(e.phase==NativePhase::after) {
        if(!parser) native_component_binding::end_native_owner();
        return Status::ok;
    }
    if(parser) {
        std::string original;auto status=decode_parser_original(ptr<const char>(e.frame->edx),original);
        if(status==Status::ok) native_component_binding::bind_source(e,source(original.c_str(),"game_task.text"));
        return status;
    }
    native_component_binding::begin_native_owner();
    if(paragraph) {begin(e,Scope::paragraph,e.arguments[3]);return Status::ok;}
    if(compound_call) return compound(e);
    if(e.id==row || e.id==command || bonus)
        return display(e,e.arguments[bonus ? 1 : 0],e.id==command ? "hud.command" : "game_task.text",
            bonus ? Scope::setup_exit : Scope::plain_button,true);
    const auto& c=texts[e.id-text_first];
    auto& destination=c.target==0xF8F80 ? e.frame->ecx : e.arguments[c.argument];
    return display(e,destination,"game_task.text",c.target==0x10E5A0 ? Scope::text :
        c.target==0x114680 ? Scope::plain_button : Scope::titled_panel,c.target==0x114680);
}
}
