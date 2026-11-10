// F9200: consume the native held-item name and its selected shield suffixes.
// Evidence: docs/evidence/20261110-hud-wielded-items-native.md.
namespace windows_wielded {
enum Hook:u32 {name_copy=0x18400,shield_name,center_suffix,high_suffix,right_suffix,left_suffix,item_text};
struct Suffix {u32 id,site,literal;};
constexpr Suffix suffixes[]{
    {center_suffix,0xF93FA,0x1AA180},{high_suffix,0xF943F,0x1AA18C},
    {right_suffix,0xF947B,0x1AA198},{left_suffix,0xF94A0,0x1AA1A4}
};
void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(inline_hook(name_copy,0xF9314,{0x8D,0x94,0x24,0x8C,1,0,0}));
    hooks.push_back(inline_hook(shield_name,0xF93AE,{0x8D,0x8C,0x24,0x88,1,0,0}));
    for(const auto& suffix:suffixes) {
        auto hook=inline_hook(suffix.id,suffix.site,suffix.id==center_suffix
            ? std::initializer_list<unsigned char>{0x8B,0x0D,0,0,0,0}
            : std::initializer_list<unsigned char>{0xA1,0,0,0,0});
        const auto literal=address(at<char>(suffix.literal));
        std::memcpy(hook.expected+(suffix.id==center_suffix ? 2 : 1),&literal,4);
        hooks.push_back(hook);
    }
    hooks.push_back(call(item_text,0xF95C3,0x10E5A0,3));
}
Status resolve(TextComponent component,const char* value,std::vector<char>& encoded) {
    const auto source=windows_inventory::read_expression(value);
    std::string name;auto status=message_project_source(source.children.front(),true,name);
    if(status!=Status::ok) return status;
    status=codec(layout_op::encode_native,name.c_str(),encoded);
    if(status!=Status::ok) return status;
    // F9340: >=30 cells keeps 28 plus '..'. SHIELD additionally uses
    // F93C1: >=25 keeps 23 plus '..', before appending native stance labels.
    const auto cells=*at<unsigned char>(0xF9342);
    status=native_text_limit(encoded,cells*8-1,(cells-2)*8,1);
    if(status!=Status::ok) return status;
    if(component==TextComponent::hud_wielded_shield_text) {
        const auto shield_cells=*at<unsigned char>(0xF93C3);
        status=native_text_limit(encoded,shield_cells*8-1,(shield_cells-2)*8,1);
        if(status!=Status::ok) return status;
    }
    for(std::size_t i=1;i<source.children.size();++i) {
        std::string suffix;status=message_project_source(source.children[i],true,suffix);
        if(status!=Status::ok) return status;
        std::vector<char> bytes;status=codec(layout_op::encode_native,suffix.c_str(),bytes);
        if(status!=Status::ok) return status;
        encoded.insert(encoded.end()-1,bytes.begin(),bytes.end()-1);
    }
    return Status::ok;
}
Status dispatch(const NativeEvent& e,DispatchResult&,bool& handled) {
    handled=e.id>=name_copy && e.id<=item_text;
    if(!handled || e.phase==NativePhase::after) return Status::ok;
    if(e.id==name_copy) {
        // F9314..F932B copies the exact 52640 return into this display buffer.
        const auto* original=ptr<char>(e.frame->eax);
        auto source=native_message_source::concat({message_source_bound(original)});
        source.component=TextComponent::hud_wielded_item_text;
        message_bind_copy(ptr<char>(e.frame->esp+0x18C),original,std::move(source));
    } else if(e.id==shield_name) {
        windows_messages::values.at(e.frame->esp+0x188).text.component=TextComponent::hud_wielded_shield_text;
    } else if(e.id>=center_suffix && e.id<=left_suffix) {
        const auto& suffix=suffixes[e.id-center_suffix];
        windows_messages::values.at(e.frame->esp+0x188).text.children.push_back(
            message_source_lookup("hud.wielded",at<char>(suffix.literal)));
    } else if(e.id==item_text) {
        // F95C8 restores this original hand index from caller ESP+3C.
        // The Before CALL frame includes the native return address at ESP.
        native_component_binding::note_native_record(e,*ptr<u32>(e.frame->esp+0x40));
        native_component_binding::note_native_field(e,static_cast<u32>(TextComponent::hud_wielded_item_text));
        const auto* original=ptr<char>(e.arguments[0]);
        if(e.arguments[0]==address(at<char>(0x18D3E8)))
            native_component_binding::note_original_for_consumer(e,original);
        else {
            const auto& source=windows_messages::values.at(address(original)).text;
            return windows_inventory::bind_expression(e,original,source,source.component);
        }
    }
    return Status::ok;
}
}
Status resolve_hud_wielded_text(TextComponent component,const char* value,std::vector<char>& encoded) {
    return windows_wielded::resolve(component,value,encoded);
}
