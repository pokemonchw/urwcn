// Included after windows_inventory.inc for its neutral expression encoding.
// E6610 owns the three English age/day results. E67AF alone constructs the
// displayed profile sentence; no player values or native branches are changed.
Status bind_profile_life_age(const NativeEvent& event,bool days) {
    std::vector<MessageText> values{
        native_message_source::scalar(native_message_source::Scalar::signed32,event.arguments[2],"%d")};
    std::vector<std::string> conversions{"%d"};
    if(days) {
        values.push_back(native_message_source::scalar(
            native_message_source::Scalar::signed32,event.arguments[3],"%d"));
        conversions.emplace_back("%d");
    }
    message_bind_source(ptr<char>(event.arguments[0]),native_message_source::format(
        message_source_lookup("profile.age",ptr<char>(event.arguments[1])),
        std::move(values),std::move(conversions)));
    return Status::ok;
}

Status format_profile_current_age(const NativeEvent& event) {
    auto* display=ptr<char>(event.arguments[0]);
    const auto sentence=native_message_source::format(
        message_source_lookup("profile.age",ptr<char>(event.arguments[1])),
        {message_source_bound(ptr<char>(event.arguments[2]))},{"%s"});
    const auto source=windows_inventory::expression(display,sentence,TextComponent::profile_current_age);
    native_component_binding::bind_source(event,source);
    std::vector<char> encoded;
    const auto status=native_text_resource::resolve_source(source,
        resolve_display_text,encode_component_original,encoded);
    if(status!=Status::ok) return status;
    // E67AF's original 0x400-byte display array is followed immediately by
    // its native width/center/text consumers. The shared E6610 ring is intact.
    std::memcpy(display,encoded.data(),encoded.size());
    event.frame->eax=static_cast<u32>(encoded.size()-1);
    return Status::ok;
}
