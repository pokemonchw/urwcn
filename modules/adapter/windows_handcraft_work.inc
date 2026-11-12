// Complete native requirement-window and work-progress consumers. Their
// original owners retain layout, work state, timing, input and cached pixels.
// Evidence: docs/evidence/20261112-handcraft-business-native.md.
namespace windows_handcraft_work {
enum Hook:u32 { text_first=0x18D00,words=0x18D20,paragraph };
enum class Source { ui,activity,work_title,effort,duration,requirement };
struct TextCall {u32 site,target;Source source;};
constexpr TextCall texts[]{
    {0x88FC8,0x116270,Source::work_title},
    {0x89000,0x10E5A0,Source::ui},
    {0x89055,0x10E5A0,Source::ui},
    {0x89083,0x10E5A0,Source::ui},
    {0x890ED,0x10E5A0,Source::effort},
    {0x89138,0x10E5A0,Source::ui},
    {0x89585,0x10E5A0,Source::duration},
    {0x89796,0x10E5A0,Source::ui},
    {0x64785,0x116270,Source::activity},
    {0x65006,0x10E5A0,Source::requirement}
};
void append_hooks(std::vector<HookSpec>& hooks) {
    if(!windows_build::is_3891()) return;
    for(u32 i=0;i<std::size(texts);++i)
        hooks.push_back(call(text_first+i,texts[i].site,texts[i].target,
            texts[i].target==0x116270 ? 5 : 3));
    hooks.push_back(call(words,0x64797,0x162300,0));
    hooks.push_back(call(paragraph,0x647B1,0x10EB40,4));
}
MessageText duration(const char* native) {
    // 893A3..894CB constructs only numbers, native separators, hour/hours,
    // minutes/seconds and the optional numeric debug suffix. Retain numeric
    // values and punctuation from this actual complete native display input.
    const std::string input=message_source_utf8(native);
    std::vector<MessageText> parts;
    for(std::size_t i=0;i<input.size();) {
        const auto start=i;
        const bool unit=input[i]>='a' && input[i]<='z';
        do {++i;} while(i<input.size() &&
            (input[i]>='a' && input[i]<='z')==unit);
        const auto value=input.substr(start,i-start);
        parts.push_back(unit ? message_source_lookup("handcraft.work.unit",value.c_str()) :
            native_message_source::original(value));
    }
    return native_message_source::concat(std::move(parts));
}
MessageText activity(const char* original) {
    // 4439C4's repair branch supplies this one real title grammar. Its
    // item operand is the original native net name, uppercased for display.
    constexpr const char* repair="REPAIR WORN-OUT ";
    if(std::strncmp(original,repair,std::strlen(repair))==0)
        return native_message_source::format(message_source_lookup("handcraft.work.format","REPAIR WORN-OUT %s"),
            {message_source_lookup("handcraft.work.item",original+std::strlen(repair))},{"%s"});
    return message_source_lookup("handcraft.work.activity",original);
}
Status dispatch(const NativeEvent& e,DispatchResult&,bool& handled) {
    const bool text=e.id>=text_first && e.id<text_first+std::size(texts);
    handled=windows_build::is_3891() && (text || e.id==words || e.id==paragraph);
    if(!handled) return Status::ok;
    if(e.phase==NativePhase::after) {
        if(e.id!=words) native_component_binding::end_native_owner();
        return Status::ok;
    }
    if(e.id==words) {
        native_component_binding::bind_source(e,native_text_resource::from_request(
            {TextComponent::message_value,ptr<const char>(e.frame->edx),"handcraft.ui"}));
        return Status::ok;
    }
    native_component_binding::begin_native_owner();
    if(e.id==paragraph) {begin(e,Scope::paragraph,e.arguments[3]);return Status::ok;}
    const auto& c=texts[e.id-text_first];
    const auto argument=c.target==0x116270 ? 2u : 0u;
    const auto* original=ptr<const char>(e.arguments[argument]);
    MessageText source;
    switch(c.source) {
    case Source::work_title: {
        // 88F9F's actual format is "%s ..."; D3DB0 already uppercased
        // its display-only activity copy. No native task data is replaced.
        const std::string heading(original,std::strlen(original)-4);
        source=native_message_source::format(message_source_lookup("handcraft.work.format","%s ..."),
            {activity(heading.c_str())},{"%s"});break;
    }
    case Source::activity:source=activity(original);break;
    case Source::effort:source=message_source_lookup("handcraft.work.effort",original);break;
    case Source::duration:source=duration(original);break;
    case Source::requirement:source=message_source_bound(original);break;
    case Source::ui:source=message_source_lookup("handcraft.ui",original);break;
    }
    return windows_inventory::consume_source(e,windows_inventory::expression(original,source),argument,
        c.target==0x116270 ? Scope::titled_panel : Scope::text);
}
}
