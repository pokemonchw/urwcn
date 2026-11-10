// Windows 3.89.1 D79F0 / FDB00 own this complete native wounds screen.
// Evidence: docs/evidence/20261110-wounds-native.md. These are text CALLs,
// with no retained positions, page fields, pixels or delayed drawing.
namespace windows_wounds {
enum Hook:u32 { frame=0x18700,title,row_format,debug_format,row_text,exit,paragraph,
    label_first=0x18710 };
struct Label {u32 site;const char* key;};
constexpr Label labels[]{
    {0xFDB7A,"wounds.header"},{0xFDC20,"wounds.critical"},
    {0xFDC54,"wounds.serious"},{0xFDC88,"wounds.minor"},
    {0xD794A,"wounds.empty"},{0xD766A,"wounds.bleeding"}
};
void append_hooks(std::vector<HookSpec>& hooks) {
    if(!windows_build::is_3891()) return;
    hooks.push_back(call(frame,0xD7A71,0xFDB00,0));
    // FC676 is shared with other screens; its source belongs to FDB00 only
    // during the synchronous frame call above.
    hooks.push_back(call(title,0xFC676,0xF8F80,0));
    hooks.push_back(call(row_format,0xD75B2,0x10D0,3));
    hooks.push_back(call(debug_format,0xD75E7,0x10D0,6));
    hooks.push_back(call(row_text,0xD7634,0x10E5A0,3));
    hooks.push_back(call(exit,0xD7B6E,0xCFAF0,2));
    hooks.push_back(call(paragraph,0xFDBDC,0x10EB40,4));
    for(u32 i=0;i<std::size(labels);++i)
        hooks.push_back(call(label_first+i,labels[i].site,0x10E5A0,3));
}
Status dispatch(const NativeEvent& e,DispatchResult&,bool& handled) {
    handled=(e.id>=frame && e.id<=paragraph) ||
        (e.id>=label_first && e.id<label_first+std::size(labels));
    if(!handled) return Status::ok;
    if(e.id==row_format || e.id==debug_format) {
        if(e.phase==NativePhase::after) {
            // D71B0's existing producer supplies the actual injury/body-part
            // expression. The native sprintf and debug scalars stay intact.
            MessageText source;
            if(e.id==row_format) source=message_source_bound(ptr<char>(e.arguments[2]));
            else source=native_message_source::format(
                native_message_source::original(ptr<char>(e.arguments[1])),{
                    native_message_source::scalar(native_message_source::Scalar::signed32,e.arguments[2],"%d"),
                    message_source_bound(ptr<char>(e.arguments[3])),
                    native_message_source::scalar(native_message_source::Scalar::signed32,e.arguments[4],"%d"),
                    native_message_source::scalar(native_message_source::Scalar::signed32,e.arguments[5],"%d")
                },{"%d","%s","%d","%d"});
            message_bind_source(ptr<char>(e.arguments[0]),std::move(source));
        }
        return Status::ok;
    }
    if(e.phase==NativePhase::after) return Status::ok;
    if(e.id==frame) {begin(e,Scope::wounds_frame);return Status::ok;}
    if(e.id==paragraph) {begin(e,Scope::paragraph,e.arguments[3]);return Status::ok;}
    if(e.id==title) {
        if(in(Scope::wounds_frame))
            return windows_culture_lend(e,"wounds.title",e.frame->ecx,Scope::titled_panel);
        return Status::ok;
    }
    if(e.id>=label_first && e.id<label_first+std::size(labels))
        return windows_culture_lend(e,labels[e.id-label_first].key,e.arguments[0],Scope::text);
    if(e.id==row_text) {
        const auto* original=ptr<char>(e.arguments[0]);
        native_component_binding::note_native_record(e,e.frame->edi);
        return windows_inventory::consume_source(e,windows_inventory::expression(
            original,message_source_bound(original)),0,Scope::text);
    }
    // CFAF0 retains the original ESC keycap and action. Bind its translated
    // suffix to the same original Menu row for native reconstruction.
    const auto* original=ptr<char>(e.arguments[1]);
    const auto* suffix=std::strchr(original,'.')+1;
    auto source=native_text_resource::from_request({TextComponent::culture_text,suffix,"ui.exit"});
    source.prefix.assign(original,suffix);
    return windows_inventory::consume_source(e,source,1,Scope::setup_exit);
}
}
