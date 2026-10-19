// Main-menu Mod credit is one neutral native footer resource. Its layout
// dependencies are the objects constructed by the actual 1250E0 invocation.
u64 footer_component_token(native_footer_component::Handle handle) {
    return 0xFFFFFFFD00000000ull|handle;
}
Status paint_footer_sprite(std::int32_t x,std::int32_t y) {
    const render::SpriteRequest sprite{*at<void*>(0x61BBB10),x,y,800,600};
    return host->invoke(ModuleId::render,render::op::sprite,&sprite,sizeof(sprite),nullptr,nullptr);
}
void enter_footer_component(native_footer_component::Handle handle,u32 outline) {
    active.push_back({footer_component_token(handle),Scope::paragraph,0,0,0,0,outline});
    native_component_binding::begin_parser_owner();
}
Status leave_footer_component(native_footer_component::Handle handle) {
    native_component_binding::end_parser_owner();
    end(footer_component_token(handle));
    // The original 1250E0 returns with its authors paragraph in the native
    // tokenizer. This additional sibling uses scratch inputs synchronously.
    return native_component_binding::restore_paragraph_builder();
}
native_footer_component::Services footer_services() {
    return {resolve_display_text,encode_component_original,measure_component_text,
        encode_component_words,paint_footer_sprite,enter_footer_component,leave_footer_component};
}
void footer_native_panel(const NativeEvent& e) {
    native_component_binding::note_original_for_consumer(e,ptr<char>(e.arguments[2]));
}
Status complete_native_footer() {
    const auto root=native_root_component::current();
    using native_text_resource::from_request;
    const native_footer_component::Source source{
        {root,0x1250E0,static_cast<u32>(TextComponent::translation_credit)},
        native_component_model::current({root,0x12510E,static_cast<u32>(TextComponent::load_character)}),
        native_component_model::current({root,0x125173,static_cast<u32>(TextComponent::production)}),
        native_image_component::current({root,0x125125,0}),
        from_request({TextComponent::translation_credit,"",nullptr}),
        from_request({TextComponent::translation_version,"",nullptr})};
    const auto handle=native_footer_component::upsert(source);
    native_ui_scene::footer_constructed(handle);
    return native_footer_component::paint(handle);
}
