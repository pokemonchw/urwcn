// Windows 3.89.1: the four combat selectors all enter 1002B0. Its 10042B
// copies each accepted 20C-byte upper row, in order, into CF990's E8-byte
// records. This binds those native sources; it does not construct a row list.
// Evidence: docs/evidence/20261111-combat-menu-native.md.
Status bind_combat_commands_menu(native_menu_component::Handle menu,const char* original_title) {
    const auto& records=native_menu_model::paint_records(menu);
    const auto* title=reinterpret_cast<const char*>(records.header.data()+0x18);
    native_menu_model::bind_title(menu,windows_inventory::expression(title,
        message_source_lookup("menu.title",original_title)));
    u32 count{};std::memcpy(&count,records.header.data()+0x14,sizeof(count));
    for(u32 index=0;index<count;++index) {
        const auto* record=records.rows.data()+index*native_menu_model::row_stride;
        const auto* label=reinterpret_cast<const char*>(record);
        // 10048C adds an empty separator; the defense builder also supplies
        // its own empty label. Neither is a semantic text consumer.
        if(!*label) continue;
        const auto* suffix=std::strchr(label,'.')+1;
        u32 action{};std::memcpy(&action,record+0xC8,sizeof(action));
        if(action==27) {
            // 10049B creates ESC.Cancel independently of the upper records.
            native_menu_model::bind_row(menu,index,native_text_resource::from_request(
                {TextComponent::message_value,suffix,"menu.label"}),std::string(label,suffix));
            continue;
        }
        const auto owner=address(at<char>(0x619F988))+index*0x20C;
        const auto& row=windows_message_menu_echo::rows.at(owner);
        auto source=row.source;
        if(row.clipped) {
            // The producer has already cut this exact English caption at
            // its native 34-byte bound. Preserve that accepted '..' branch
            // using the same typed prefix expression as the message echo.
            const std::string caption=suffix;
            const auto* full=row.native.c_str()+row.native.find('.')+1;
            const auto prefix=windows_message_menu_echo::native_visible_prefix(full,caption.size()-2);
            MessageText visible;
            const auto status=windows_message_menu_echo::visible_prefix(source,prefix.size(),visible);
            if(status!=Status::ok) return status;
            source=native_message_source::concat({std::move(visible),native_message_source::original("..")});
        }
        // CFA29/CFA5E split the actual '|' into label and annotation. Keep
        // both consumers on that native split, including the empty suffix.
        source=native_message_source::before_separator(std::move(source),'|');
        native_menu_model::bind_row(menu,index,windows_inventory::expression(suffix,source),
            std::string(label,suffix));
        const auto* annotation=reinterpret_cast<const char*>(record+0x64);
        if(*annotation)
            native_menu_model::bind_annotation(menu,index,native_text_resource::from_request(
                {TextComponent::message_value,annotation,"menu.aim-annotation"}));
    }
    return Status::ok;
}
