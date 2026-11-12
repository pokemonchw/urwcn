// Windows 3.89.1: 12BFD0 selects HITOPT_DEATHBLOW / HITOPT_BUTCHERING
// and FFC60 copies that accepted English help into 61A88B8. 1002B0 parses
// the same complete help once to measure it and once to paint it. This shared
// command window also owns the recipe graphic preview's native title panel.
namespace windows_combat_help {
enum Hook:u32 { words_measure=0x18C00,words_paint,paragraph_measure,paragraph_paint,
    preview_panel_first=0x18C10,preview_panel_second };

constexpr const char* deathblow=
    "A deathblow is possible. You try to execute a carefully aimed strike to finish this unconscious victim.";
constexpr const char* butchering=
    "Butchering is possible. You try to execute a carefully aimed butchering blow to quickly stun or kill this leashed creature.";

void append_hooks(std::vector<HookSpec>& hooks) {
    if(!windows_build::is_3891()) return;
    hooks.push_back(call(words_measure,0x100367,0x162300,0));
    hooks.push_back(call(words_paint,0x100547,0x162300,0));
    hooks.push_back(call(paragraph_measure,0x100381,0x10EB40,4));
    hooks.push_back(call(paragraph_paint,0x100586,0x10EB40,4));
    hooks.push_back(call(preview_panel_first,0x1004C8,0x115E70,4));
    hooks.push_back(call(preview_panel_second,0x100682,0x115E70,4));
}

Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    const bool preview=event.id==preview_panel_first || event.id==preview_panel_second;
    handled=windows_build::is_3891() &&
        ((event.id>=words_measure && event.id<=paragraph_paint) || preview);
    if(!handled) return Status::ok;
    const bool paragraph=event.id==paragraph_measure || event.id==paragraph_paint;
    if(event.phase==NativePhase::after) {
        if(paragraph || preview) native_component_binding::end_native_owner();
        return Status::ok;
    }
    if(preview) {
        native_component_binding::begin_native_owner();
        return windows_inventory::consume_source(event,native_text_resource::from_request(
            {TextComponent::message_value,ptr<const char>(event.arguments[2]),"menu.label"}),
            2,Scope::titled_panel);
    }
    if(!paragraph) {
        // These two complete resource texts are the finite 12BFD0 branches.
        // All other command help keeps the parser's original source.
        const auto* original=ptr<const char>(event.frame->edx);
        const char* key=nullptr;
        if(std::strcmp(original,deathblow)==0) key="HITOPT_DEATHBLOW";
        else if(std::strcmp(original,butchering)==0) key="HITOPT_BUTCHERING";
        if(key) native_component_binding::bind_source(event,native_text_resource::from_request(
            {TextComponent::message_template,original,key}));
        return Status::ok;
    }
    // Both complete 10EB40 invocations own their actual width, line breaks
    // and return height. 100389/10038C use the measured return value to size
    // the native Menu; 100568..100578 derive its eventual help origin.
    // The existing paragraph width/advance and 10EF87 -> 10E5A0 glyph path
    // consume these parser inputs on the native 61BBB10 output surface.
    native_component_binding::begin_native_owner();
    begin(event,Scope::paragraph,event.arguments[3]);
    return Status::ok;
}
}
