// 3.89.1: 143CAA -> 1002B0 -> CF790/CF990 -> CFFB0.
// Bind the accepted command Menu's original records, without rebuilding the
// animal command list or repeating any animal business actions.
void bind_animal_commands_menu(native_menu_component::Handle menu) {
    const auto& records=native_menu_model::paint_records(menu);
    const auto* title=reinterpret_cast<const char*>(records.header.data()+0x18);
    // The suspended 143CAA call already owns this complete title expression.
    // 143C64 captures AD4F0(actor,0)'s typed descriptor/proper-name operands;
    // the group branch instead owns its literal menu.title source.
    native_menu_model::bind_title(menu,windows_inventory::expression(
        title,windows_message_menu_echo::echoes.back().title));
    u32 count{};std::memcpy(&count,records.header.data()+0x14,sizeof(count));
    for(u32 row=0;row<count;++row) {
        const auto* label=reinterpret_cast<const char*>(records.rows.data()+row*native_menu_model::row_stride);
        // 10048C installs the actual empty separator before ESC.Cancel.
        if(!*label) continue;
        const auto* suffix=std::strchr(label,'.')+1;
        native_menu_model::bind_row(menu,row,native_text_resource::from_request(
            {TextComponent::message_value,suffix,"menu.label"}),std::string(label,suffix));
    }
}
