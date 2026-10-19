// Windows PE 3.89 profile/season consumers. Addresses and stack operands were
// read from the installed e0b15bbb... EXE, independently of the Linux port.
enum WindowsProfileHook : u32 {
    wp_season_draw=0x7800,wp_season_help,wp_season_footer,wp_portrait_help,
    wp_attribute_panel_first=0x7810,wp_attribute_label_first=0x7820,
    wp_attribute_label_draw=0x7830,wp_attribute_identity,wp_attribute_age,
    wp_attribute_age_width,wp_attribute_age_text,wp_attribute_height,
    wp_attribute_weight,wp_attribute_height_value,wp_attribute_weight_value,
    wp_attribute_ready,wp_attribute_press,wp_attribute_background,
    wp_attribute_confirm,wp_attribute_paragraph_first=0x7840,
    wp_attribute_draw=0x7850,wp_attribute_identity_width,wp_attribute_identity_draw,
    wp_portrait_footer,wp_title_width_first,wp_title_width_second
};
constexpr u32 wp_name_error_parser=0x57F2;
// The three confirmed literal-copy constructors select this neutral display
// resource. ESI is only success/failure at the later 118EE parser consumer.
struct WindowsProfileErrorSource { u32 component,native_source_rva; };
WindowsProfileErrorSource windows_profile_error_source{};
void windows_profile_error_constructed(TextComponent component,u32 native_source_rva) {
    windows_profile_error_source={static_cast<u32>(component),native_source_rva};
}
std::vector<std::uint8_t> save_windows_profile_error_source() {
    const auto* bytes=reinterpret_cast<const std::uint8_t*>(&windows_profile_error_source);
    return {bytes,bytes+sizeof(windows_profile_error_source)};
}
void restore_windows_profile_error_source(const void* bytes) {
    std::memcpy(&windows_profile_error_source,bytes,sizeof(windows_profile_error_source));
}
bool windows_season_drawing;
bool windows_attributes_drawing;
bool windows_season_refresh=true;
void invalidate_windows_profile() { windows_season_refresh=true; }
bool windows_profile_input(const NativeEvent& e) {
    return windows_season_refresh&&native_language_redraw::menu_input(e,0xFB40);
}
Status windows_title_metrics(const char* input,render::Metrics& measured) {
    std::vector<char> encoded,utf8;
    auto status=native_name_input::display(input,encoded);
    if(status!=Status::ok)return status;
    status=codec(layout_op::decode_native,encoded.data(),utf8);
    if(status!=Status::ok)return status;
    auto request=render_request(utf8.data(),0,0,0);
    request.outline=1; // These native title calls all pass shadow=1.
    u32 bytes=sizeof(measured);
    return host->invoke(ModuleId::render,render::op::measure,&request,sizeof(request),&measured,&bytes);
}
struct WindowsProfileField { u32 site; TextComponent component; };
constexpr WindowsProfileField windows_attribute_panels[]{
    {0xE670E,TextComponent::profile_physical},{0xE6730,TextComponent::profile_physique},
    {0xE6900,TextComponent::profile_personality},{0xE6953,TextComponent::profile_appearance}
};
constexpr WindowsProfileField windows_attribute_labels[]{
    {0xE6828,TextComponent::profile_strength},{0xE683F,TextComponent::profile_endurance},
    {0xE6856,TextComponent::profile_dexterity},{0xE686D,TextComponent::profile_agility},
    {0xE6884,TextComponent::profile_speed},{0xE689B,TextComponent::profile_eyesight},
    {0xE68B2,TextComponent::profile_hearing},{0xE68C9,TextComponent::profile_smell_taste},
    {0xE68E3,TextComponent::profile_touch},{0xE691A,TextComponent::profile_intelligence},
    {0xE6931,TextComponent::profile_will}
};
Status windows_profile_text(const NativeEvent& e,TextComponent component,u32& destination,
                            Scope kind,const char* value=nullptr) {
    std::vector<char> encoded;
    Status status;
    if(e.id==character_creation_panel) {
        native_menu_component::bind_title(component,ptr<char>(destination),value);
        status=native_menu_component::resolve_title(encoded);
    } else status=translate(component,ptr<char>(destination),value,encoded);
    if(status!=Status::ok) return status;
    return lend_text(e,encoded,destination,kind);
}
Status windows_profile_append(const NativeEvent& e,TextComponent component) {
    std::vector<char> encoded;
    auto status=translate(component,ptr<char>(e.frame->edx),nullptr,encoded);
    if(status!=Status::ok) return status;
    const auto words=native_paragraph_words(encoded.data());
    encoded.assign(words.begin(),words.end());encoded.push_back(0);
    return lend_text(e,encoded,e.frame->edx,Scope::allocation);
}
Status dispatch_windows_profile(const NativeEvent& e,DispatchResult& result,bool& handled) {
    handled=true;
    if(e.phase==NativePhase::after) {
        if(e.id==wp_season_draw) { windows_season_drawing=false;return Status::ok; }
        if(e.id==wp_attribute_draw) { windows_attributes_drawing=false;return Status::ok; }
        if(e.id==wp_attribute_age && e.frame->edi!=0) {
            std::vector<char> encoded;
            const auto age=std::to_string(e.arguments[2]);
            auto status=translate(TextComponent::profile_start_age,ptr<char>(e.arguments[0]),age.c_str(),encoded);
            if(status!=Status::ok) return status;
            std::memcpy(ptr<void>(e.arguments[0]),encoded.data(),encoded.size());
            e.frame->eax=static_cast<u32>(encoded.size()-1);
            return Status::ok;
        }
        handled=false;return Status::ok;
    }
    if(e.id>=wp_attribute_panel_first && e.id<wp_attribute_panel_first+std::size(windows_attribute_panels))
        return windows_profile_text(e,windows_attribute_panels[e.id-wp_attribute_panel_first].component,
                                    e.arguments[2],Scope::profile_panel);
    if(e.id>=wp_attribute_label_first && e.id<wp_attribute_label_first+std::size(windows_attribute_labels))
        return windows_profile_text(e,windows_attribute_labels[e.id-wp_attribute_label_first].component,
                                    e.arguments[0],Scope::profile_panel);
    switch(e.id) {
    case wp_name_error_parser: {
        const auto& error=windows_profile_error_source;
        native_component_binding::bind_source(e,native_text_resource::from_request({
            static_cast<TextComponent>(error.component),at<char>(error.native_source_rva),nullptr}));
        return Status::ok;
    }
    case shared_title_text:
        if(native_name_input::contains_display(ptr<char>(e.arguments[0]))) {
            begin(e,Scope::text,e.arguments[2]);return Status::ok;
        }
        break;
    case wp_title_width_first:case wp_title_width_second:
        if(native_name_input::contains_display(ptr<char>(e.frame->esi))) {
            render::Metrics measured{};
            const auto status=windows_title_metrics(ptr<char>(e.frame->esi),measured);
            if(status!=Status::ok)return status;
            e.frame->eax=static_cast<u32>(measured.logical_width);result.skip_original=1;
        }
        return Status::ok;
    case about_title_width:
        if(in(Scope::profile_panel)) {
            render::Metrics measured{};
            const auto status=windows_title_metrics(ptr<char>(e.frame->esp+0x80),measured);
            if(status!=Status::ok)return status;
            e.frame->eax=static_cast<u32>(measured.logical_width);result.skip_original=1;return Status::ok;
        }
        break;
    case about_title_text:
        if(in(Scope::profile_panel)) {
            render::Metrics measured{};
            const auto status=windows_title_metrics(ptr<char>(e.arguments[0]),measured);
            if(status!=Status::ok)return status;
            const auto x=static_cast<std::int32_t>(e.frame->ecx);
            active.push_back({e.token,Scope::text,0,x,1,x+measured.logical_width/2,e.arguments[2]});
            return Status::ok;
        }
        break;
    case wp_season_draw: windows_season_drawing=true;windows_season_refresh=false;return Status::ok;
    case wp_attribute_draw: windows_attributes_drawing=true;return Status::ok;
    case character_creation_panel:
        if(windows_season_drawing)
            return windows_profile_text(e,TextComponent::profile_season_title,e.arguments[2],Scope::profile_panel);
        break;
    case character_creation_button:
        if(windows_season_drawing || windows_attributes_drawing) {
            const auto action=*ptr<u32>(e.frame->esi+0xC8);
            TextComponent component{};
            if(windows_season_drawing) {
                if(action>='1' && action<='4') component=static_cast<TextComponent>(
                    static_cast<u32>(TextComponent::profile_season_spring)+action-'1');
                else if(action==27) component=TextComponent::profile_back;
                else return Status::ok;
            } else {
                if(action=='Y') component=TextComponent::profile_continue;
                else if(action=='N') component=TextComponent::profile_reroll;
                else return Status::ok;
            }
            return character_creation_label(e,component);
        }
        break;
    case wp_season_help:return windows_profile_append(e,TextComponent::profile_season_help);
    case wp_portrait_help:return windows_profile_append(e,TextComponent::profile_portrait_help);
    case wp_season_footer:begin(e,Scope::profile_footer);return Status::ok;
    case wp_portrait_footer:begin(e,Scope::profile_footer);return Status::ok;
    case wp_attribute_label_draw:
        if(in(Scope::profile_panel)) { begin(e,Scope::text,e.arguments[2]);return Status::ok; }
        break;
    case wp_attribute_identity: {
        // E677A formats Plr.name + Plr.inhabitant. choose_culture stores the
        // culture ID at Plr+0xD; preserve the existing display name verbatim.
        const auto* original=ptr<char>(e.frame->ecx);
        const auto* separator=std::strchr(original,' ');
        const std::string name(original,separator);
        std::string original_culture,original_name;
        decode_parser_original(separator+1,original_culture);
        decode_parser_original(name.c_str(),original_name);
        std::vector<char> culture;
        const auto component=static_cast<TextComponent>(static_cast<u32>(TextComponent::profile_culture_0)+
            *at<unsigned char>(0xA32A6F5));
        auto status=translate(component,original_culture.c_str(),nullptr,culture);
        if(status!=Status::ok) return status;
        native_component_binding::note_prefix(e,(original_name+" ").c_str());
        std::vector<char> encoded;
        status=native_name_input::display(name.c_str(),encoded);
        if(status!=Status::ok) return status;
        encoded.back()=' ';
        encoded.insert(encoded.end(),culture.begin(),culture.end());
        return lend_text(e,encoded,e.frame->ecx,Scope::profile_panel);
    }
    case wp_attribute_age:return Status::ok;
    case wp_attribute_identity_width:
        if(in(Scope::profile_panel)||native_name_input::contains_display(ptr<char>(e.frame->edi))) {
            render::Metrics measured{};
            const auto status=windows_title_metrics(ptr<char>(e.frame->edi),measured);
            if(status!=Status::ok) return status;
            e.frame->ecx=0x195;
            e.frame->eax=static_cast<u32>(measured.logical_width);
            result.skip_original=1;
        }
        return Status::ok;
    case wp_attribute_identity_draw:
        if(in(Scope::profile_panel)||native_name_input::contains_display(ptr<char>(e.arguments[0])))
            begin(e,Scope::text,e.arguments[2]);
        return Status::ok;
    case wp_attribute_age_width: {
        // E67F6: LEA EAX,[ECX*8] only. The native following division and
        // subtraction continue to center the same formatted display buffer.
        render::Metrics measured{};
        auto status=windows_title_metrics(ptr<char>(*ptr<u32>(e.frame->esp)),measured);
        if(status!=Status::ok) return status;
        e.frame->eax=static_cast<u32>(measured.logical_width);
        result.skip_original=1;return Status::ok;
    }
    case wp_attribute_age_text:
        native_component_binding::note_source_for_consumer(e,TextComponent::profile_start_age);
        return centered_text(e);
    case wp_attribute_height:return windows_profile_text(e,TextComponent::profile_height,e.arguments[0],Scope::text);
    case wp_attribute_weight:return windows_profile_text(e,TextComponent::profile_weight,e.arguments[0],Scope::text);
    case wp_attribute_height_value:case wp_attribute_weight_value:
        return windows_profile_text(e,TextComponent::profile_measurement,e.arguments[0],Scope::text);
    case wp_attribute_ready:return windows_profile_append(e,TextComponent::profile_attributes_ready);
    case wp_attribute_press:return windows_profile_append(e,TextComponent::profile_attributes_press_key);
    case wp_attribute_background:return windows_profile_append(e,TextComponent::profile_confirm_background);
    case wp_attribute_confirm:return windows_profile_append(e,TextComponent::profile_confirm_attributes);
    default:
        if(e.id>=wp_attribute_paragraph_first && e.id<wp_attribute_paragraph_first+2) {
            begin(e,Scope::paragraph,e.arguments[3]);return Status::ok;
        }
        break;
    }
    handled=false;return Status::ok;
}
void append_windows_profile_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(call(wp_name_error_parser,0x118EE,0x162300,0));
    hooks.push_back(call(wp_season_draw,0xFB36,0xCFFB0,0));
    hooks.push_back(call(wp_season_help,0xFA4D,0x162300,0));
    hooks.push_back(call(wp_season_footer,0xFA54,0xF210,0));
    hooks.push_back(call(wp_portrait_help,0x125F0,0x162300,0));
    hooks.push_back(call(wp_portrait_footer,0x125F7,0xF210,0));
    for(u32 i=0;i<std::size(windows_attribute_panels);++i)
        hooks.push_back(call(wp_attribute_panel_first+i,windows_attribute_panels[i].site,0x116270,5));
    for(u32 i=0;i<std::size(windows_attribute_labels);++i)
        hooks.push_back(call(wp_attribute_label_first+i,windows_attribute_labels[i].site,0xE10F0,2));
    hooks.push_back(call(wp_attribute_label_draw,0xE1110,0x10E5A0,3));
    hooks.push_back(call(wp_attribute_identity,0xE6784,0xF9030,0));
    hooks.push_back(inline_hook(wp_attribute_identity_width,0xF909D,{0xB9,0x95,0x01,0,0,0xC1,0xE0,0x03}));
    hooks.push_back(call(wp_attribute_identity_draw,0xF90B5,0x10E5A0,3));
    hooks.push_back(inline_hook(wp_title_width_first,0x115849,{0x8D,0x04,0xCD,0,0,0,0}));
    hooks.push_back(inline_hook(wp_title_width_second,0x1159C9,{0x8D,0x04,0xCD,0,0,0,0}));
    hooks.push_back(call(wp_attribute_age,0xE67AF,0x10D0,3));
    hooks.push_back(inline_hook(wp_attribute_age_width,0xE67F6,{0x8D,0x04,0xCD,0,0,0,0}));
    hooks.push_back(call(wp_attribute_age_text,0xE680E,0x10E5A0,3));
    hooks.push_back(call(wp_attribute_height,0xE6995,0x10E5A0,3));
    hooks.push_back(call(wp_attribute_weight,0xE6A45,0x10E5A0,3));
    hooks.push_back(call(wp_attribute_height_value,0xE6A2A,0x10E5A0,3));
    hooks.push_back(call(wp_attribute_weight_value,0xE6AD2,0x10E5A0,3));
    hooks.push_back(call(wp_attribute_ready,0xE6B58,0x162300,0));
    hooks.push_back(call(wp_attribute_press,0xE6B64,0x162300,0));
    hooks.push_back(call(wp_attribute_background,0xE6BEA,0x162300,0));
    hooks.push_back(call(wp_attribute_confirm,0xE6BF6,0x162300,0));
    hooks.push_back(call(wp_attribute_paragraph_first,0xE6B97,0x10EB40,4));
    hooks.push_back(call(wp_attribute_paragraph_first+1,0xE6C28,0x10EB40,4));
    hooks.push_back(call(wp_attribute_draw,0xE6CA1,0xCFFB0,0));
}
