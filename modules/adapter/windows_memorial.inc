// Windows 3.89.1: 4DD400's complete memorial, and 4DE990's death footer.
// Source grammar: 4DDC60 -> 4DCF10 / 48E4F0 / 49B040, including persisted ANC.
// Native construction, paragraphs, line advances, controls and caches remain
// with those functions. No page, coordinates or translated drawing is saved.
namespace windows_memorial {
enum Hook:u32 { title_panel=0x18900,title_text,dead_text,death_button,detail_button,
    append_first=0x18910,paragraph_first=0x18920 };
constexpr u32 appends[]{0xDD8DE,0xDD93A,0xDD9A3,0xDEAE2,0xDEAEE};
constexpr u32 paragraphs[]{0xDD900,0xDD9CE,0xDEB40};

void append_hooks(std::vector<HookSpec>& hooks) {
    if(!windows_build::is_3891()) return;
    hooks.push_back(call(title_panel,0xDD596,0x115E70,4));
    hooks.push_back(call(title_text,0xDD5AD,0x10E5A0,3));
    hooks.push_back(call(dead_text,0xDEA82,0x10E5A0,3));
    hooks.push_back(call(death_button,0xDEB72,0x114680,1));
    hooks.push_back(call(detail_button,0xDF3F2,0x114680,1));
    for(u32 i=0;i<std::size(appends);++i)
        hooks.push_back(call(append_first+i,appends[i],0x162300,0));
    for(u32 i=0;i<std::size(paragraphs);++i)
        hooks.push_back(call(paragraph_first+i,paragraphs[i],0x10EB40,4));
}

Status sentence(const NativeEvent& event,const char* original,MessageText& text) {
    const auto status=windows_conversation_sources::source(original,text);
    if(status!=Status::ok) return status;
    return windows_inventory::bind_expression(event,original,text);
}
Status title(const NativeEvent& event) {
    // The exact native mode-5 heading calls the same 115E70 band, with the
    // same x/y/width and its own 16-pixel height/color, then centers the title.
    // 115849's existing width extension feeds that native centering formula.
    std::vector<char> encoded;
    auto status=translate(TextComponent::message_value,at<char>(0x1A629C),
        "memorial.form.t",encoded);
    if(status!=Status::ok) return status;
    const native_component_calls::TitleStripCall heading{
        address(at<void>(0x1157B0)),static_cast<std::int32_t>(event.frame->ecx),
        static_cast<std::int32_t>(event.frame->edx),
        static_cast<std::int32_t>(event.arguments[0]),encoded.data(),5};
    begin(event,Scope::titled_panel,1);
    native_component_binding::begin_native_owner();
    native_component_calls::uwcn_component_title_strip(&heading);
    native_component_binding::end_native_owner();
    end(event.token);
    return Status::ok;
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    const bool identity=event.id==native_full_language::ancestor_name_text;
    const bool summary=event.id==native_full_language::ancestor_death_text;
    const bool statistics=(event.id==ancestors_lived_text || event.id==ancestors_distance_text) &&
        !in(Scope::ancestors_row);
    handled=windows_build::is_3891() && (identity || summary || statistics ||
        (event.id>=title_panel && event.id<=detail_button) ||
        (event.id>=append_first && event.id<append_first+std::size(appends)) ||
        (event.id>=paragraph_first && event.id<paragraph_first+std::size(paragraphs)));
    if(!handled) return Status::ok;
    if(event.phase==NativePhase::after) {
        if(identity || summary || statistics || event.id==dead_text ||
           event.id==death_button || event.id==detail_button ||
           (event.id>=paragraph_first && event.id<paragraph_first+std::size(paragraphs)))
            native_component_binding::end_native_owner();
        return Status::ok;
    }
    if(event.id==title_panel) {
        if(!chinese_enabled) return Status::ok;
        const auto status=title(event);
        if(status==Status::ok) result.skip_original=1;
        return status;
    }
    if(event.id==title_text) {
        if(chinese_enabled) result.skip_original=1;
        return Status::ok;
    }
    if(event.id>=paragraph_first && event.id<paragraph_first+std::size(paragraphs)) {
        native_component_binding::begin_native_owner();
        begin(event,Scope::paragraph,event.arguments[3]);return Status::ok;
    }
    if(event.id>=append_first && event.id<append_first+std::size(appends)) {
        MessageText text;
        // finish_event lends the source to this actual 162300 call and keeps
        // only the native parser's current neutral inputs, with no page copy.
        return sentence(event,ptr<char>(event.frame->edx),text);
    }
    const auto* original=ptr<char>(event.arguments[0]);
    MessageText text;
    if(identity) {
        // DD51A..DD543 installs this very ancestor's original character data.
        // 55DFC0 uses precisely name/culture; DDA4A restores the live player.
        const auto culture=static_cast<TextComponent>(static_cast<u32>(TextComponent::profile_culture_0)+
            *at<unsigned char>(0xA32A6F5));
        text=native_message_source::concat({message_source_identity(at<char>(0xA32A6E8)),
            native_message_source::original(" "),
            native_message_source::lookup(culture,message_source_utf8(at<char>(0xA32A6F6)))});
    } else {
        const auto status=windows_conversation_sources::source(original,text);
        if(status!=Status::ok) return status;
    }
    const auto scope=event.id==death_button || event.id==detail_button ? Scope::plain_button : Scope::text;
    native_component_binding::begin_native_owner();
    return windows_inventory::consume_source(event,windows_inventory::expression(original,text),0,scope);
}
}
