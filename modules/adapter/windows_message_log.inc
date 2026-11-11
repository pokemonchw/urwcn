// Windows 3.89.1 FE2B0 reads msglog.txt and owns its 70 native records,
// pagination, paragraphs, Menu and note editor. No translated rows are saved.
namespace windows_message_log {
enum Hook:u32 { panel=0x18B00,counter_format,exit_button,note_button,note_prompt,
    body=native_generic_menu_language::history_append,
    paragraph=native_generic_menu_language::history_paragraph,
    record_width=native_generic_menu_language::history_line_width,
    counter_draw=native_generic_menu_language::history_footer };

void append_hooks(std::vector<HookSpec>& hooks) {
    if(!windows_build::is_3891()) return;
    hooks.push_back(call(panel,0xFE478,0x116270,5));
    // The four history hooks already installed by generic_menu retain their
    // IDs and sites. Their complete text handling is dispatched below.
    hooks.push_back(call(counter_format,0xFEA0B,0x10D0,5));
    hooks.push_back(call(exit_button,0xFEB38,0xCFAF0,2));
    hooks.push_back(call(note_button,0xFEB66,0xCFAF0,2));
    hooks.push_back(call(note_prompt,0xFEC95,0x10E5A0,3));
}

native_text_resource::TextSource source(const char* original,const char* domain) {
    return native_text_resource::from_request({TextComponent::message_value,original,domain});
}
Status display(const NativeEvent& e,u32& destination,Scope scope) {
    const auto* original=ptr<const char>(destination);
    const bool button=e.id==exit_button || e.id==note_button;
    // CFAF0 keeps its original key token and action. Only the suffix is text.
    const auto* suffix=button ? std::strchr(original,'.')+1 : original;
    auto text=source(suffix,"message.log.ui");
    if(button) text.prefix.assign(original,suffix);
    native_component_binding::bind_source(e,text);
    if(button) native_menu_component::bind_constructor_row(e.token,text);
    if(!chinese_enabled) return Status::ok;
    std::vector<char> encoded;
    const auto status=native_text_resource::resolve_source(text,resolve_display_text,
        encode_component_original,encoded);
    return status==Status::ok ? lend_text(e,encoded,destination,scope) : status;
}
Status dispatch(const NativeEvent& e,DispatchResult& result,bool& handled) {
    handled=windows_build::is_3891() && ((e.id>=panel && e.id<=note_prompt) ||
        e.id==body || e.id==paragraph || e.id==record_width || e.id==counter_draw);
    if(!handled) return Status::ok;
    if(e.id==record_width) {
        if(e.phase==NativePhase::after) return Status::ok;
        // FE5C0 copies this exact English input into the native ring record.
        // Extend the same width operand before the game's 780-pixel compare;
        // its one/two-line flag and page selection remain native decisions.
        const auto* original=ptr<const char>(e.frame->esp+0x950);
        const native_name_input::UnicodeMeasure unicode(original);
        std::vector<char> encoded;
        auto status=native_text_resource::resolve_source(windows_message_history::source(original),
            resolve_display_text,encode_component_original,encoded);
        if(status!=Status::ok) return status;
        render::Metrics measured{};status=metrics_at_outline(encoded.data(),0,measured);
        if(status!=Status::ok) return status;
        e.frame->ecx-=e.frame->edx;
        e.frame->eax=static_cast<u32>(measured.logical_width);
        result.skip_original=1;
        return Status::ok;
    }
    if(e.id==body) {
        if(e.phase==NativePhase::after) return Status::ok;
        std::string original;
        const auto status=decode_parser_original(ptr<const char>(e.frame->edx),original);
        if(status==Status::ok)
            native_component_binding::bind_source(e,windows_message_history::source(original.c_str()));
        return status;
    }
    if(e.id==counter_format) {
        if(e.phase==NativePhase::after) return Status::ok;
        return display(e,e.arguments[1],Scope::allocation);
    }
    if(e.phase==NativePhase::after) {
        native_component_binding::end_native_owner();
        return Status::ok;
    }
    // These actual component calls paint immediately into the native target.
    // Do not register their positions as another set of redraw components.
    native_component_binding::begin_native_owner();
    if(e.id==paragraph) {begin(e,Scope::paragraph,e.arguments[3]);return Status::ok;}
    if(e.id==counter_draw) {begin(e,Scope::text,e.arguments[2]);return Status::ok;}
    auto& destination=e.arguments[e.id==panel ? 2 :
        e.id==exit_button || e.id==note_button ? 1 : 0];
    return display(e,destination,e.id==panel ? Scope::titled_panel :
        e.id==note_prompt ? Scope::text : Scope::setup_exit);
}
}
