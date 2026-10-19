// Included inside the adapter's anonymous namespace. This file contains only
// confirmed native call identities and synchronous text/measurement adapters.
// No HUD coordinates, persistent fields or drawing replay are stored.
enum HudHook : u32 {
    hud_surface_first=0x6000,
    hud_command=0x6100,hud_repeat,hud_help,hud_wielded,
    hud_penalty_first=0x6120,hud_penalty_width=0x6130,hud_penalty_draw,
    hud_center_first=0x6200,hud_center_fit=0x6210,hud_center_line,hud_center_last,
    hud_center_draw_line,hud_center_draw_last,
    hud_month_append=0x6220,hud_month_paragraph,hud_scale_width,hud_scale_call,hud_scale_text,
    hud_action=0x6300,hud_direction,hud_speed,
    hud_renderer_wrapper,hud_renderer_top,hud_renderer_bottom,hud_renderer_left,
    hud_renderer_right,hud_renderer_foreground,hud_speed_number,hud_target_entry,
    hud_identity_width,hud_identity_draw_first,hud_identity_draw_second
};
struct HudSurfaceCall { u32 site; TextComponent component; };
constexpr HudSurfaceCall hud_surface_calls[]{
    {0xF8E84,TextComponent::hud_label},
    {0xF99B0,TextComponent::hud_label},{0xF99E6,TextComponent::hud_label},
    {0xF9A1C,TextComponent::hud_label},{0xF9A52,TextComponent::hud_label},
    {0xF9BEE,TextComponent::hud_label},{0xF9BA1,TextComponent::hud_label},
    {0xF9DB6,TextComponent::hud_label},{0xF9EDA,TextComponent::hud_label},
    {0xF9F70,TextComponent::hud_condition},{0xFA074,TextComponent::hud_condition},
    {0xFA27E,TextComponent::hud_condition},
    {0x10376C,TextComponent::world_season},{0x10385B,TextComponent::world_time}
};
constexpr HudSurfaceCall hud_center_calls[]{
    {0x90270,TextComponent::world_place_gloss},
    {0x902C8,TextComponent::world_region},{0x9031A,TextComponent::world_region},
    {0x90588,TextComponent::world_location},{0x9076B,TextComponent::world_date},
    {0x9083D,TextComponent::world_map_kind}
};

Status hud_translate(TextComponent component,const char* original,const char* value,
                     std::vector<char>& encoded) {
    // Native proper names may contain the same Western bytes as the confirmed
    // profile names. Convert only this borrowed display string to Unicode.
    std::string utf8;
    for(auto* p=reinterpret_cast<const unsigned char*>(original);*p;++p) append_utf8(utf8,*p);
    std::string value_utf8;
    if(value) for(auto* p=reinterpret_cast<const unsigned char*>(value);*p;++p) append_utf8(value_utf8,*p);
    return translate(component,utf8.c_str(),value ? value_utf8.c_str() : nullptr,encoded);
}
Status hud_lend(const NativeEvent& e,TextComponent component,u32 argument,Scope scope,
                const char* value=nullptr,u32 outline=0) {
    std::vector<char> encoded;
    const auto status=hud_translate(component,ptr<char>(e.arguments[argument]),value,encoded);
    if(status!=Status::ok) return status;
    return lend_text(e,encoded,e.arguments[argument],scope,outline);
}
Status hud_draw_renderer(const NativeEvent& e) {
    std::vector<char> utf8;
    auto status=codec(layout_op::decode_native,ptr<char>(e.arguments[1]),utf8);
    if(status!=Status::ok) return status;
    u32 outline=*ptr<u32>(e.frame->ebp+0x14)&1u;
    for(auto i=active.rbegin();i!=active.rend();++i)
        if(i->kind==Scope::hud_renderer_text) { outline=i->outline; break; }
    const render::TextRequest request{utf8.data(),nullptr,ptr<void>(e.frame->ecx),
        static_cast<std::int32_t>(e.frame->edx),static_cast<std::int32_t>(e.arguments[0]),
        e.arguments[2]|0xFF000000u,10,9,0,0,outline,0,0};
    render::Metrics measured{};
    u32 bytes=sizeof(measured);
    return host->invoke(ModuleId::render,render::op::draw_renderer,&request,sizeof(request),&measured,&bytes);
}
Status hud_scale_metrics(const char* encoded,render::Metrics& measured) {
    std::vector<char> utf8;
    auto status=codec(layout_op::decode_native,encoded,utf8);
    if(status!=Status::ok) return status;
    auto request=render_request(utf8.data(),0,0,0);
    request.outline=1; // 08FF1E pushes the native scale label's shadow flag.
    u32 bytes=sizeof(measured);
    return host->invoke(ModuleId::render,render::op::measure,&request,sizeof(request),&measured,&bytes);
}
Status hud_identity_display(const NativeEvent& e,const char* original,std::vector<char>& encoded) {
    // FA3F2 formats "%s %s" from Plr.name and Plr.inhabitant. Choose_Name
    // excludes spaces in names; tribe suffixes themselves include "of ".
    // choose_culture stores the culture ID at Plr+0xD. Borrow display text only.
    const auto* separator=std::strchr(original,' ');
    const std::string name(original,separator);
    const auto component=static_cast<TextComponent>(static_cast<u32>(TextComponent::profile_culture_0)+
        *at<unsigned char>(0xA32A6F5));
    std::string original_culture,original_name;
    auto status=decode_parser_original(separator+1,original_culture);
    if(status!=Status::ok) return status;
    status=decode_parser_original(name.c_str(),original_name);
    if(status!=Status::ok) return status;
    std::vector<char> culture;
    status=translate(component,original_culture.c_str(),nullptr,culture);
    if(status!=Status::ok) return status;
    native_component_binding::note_prefix(e,(original_name+" ").c_str());
    status=native_name_input::display(name.c_str(),encoded);
    if(status!=Status::ok) return status;
    encoded.back()=' ';
    encoded.insert(encoded.end(),culture.begin(),culture.end());
    return Status::ok;
}
Status dispatch_hud(const NativeEvent& e,DispatchResult& result,bool& handled) {
    handled=true;
    if(e.id>=hud_surface_first && e.id<hud_surface_first+std::size(hud_surface_calls)) {
        // F8E20 owns the complete native cell, including its label, number,
        // bar and native cache record. Its prepared source is already current.
        if(e.id==hud_surface_first && native_component_binding::consuming_component()) return Status::ok;
        // The native arithmetic '+' separator uses the same label primitive.
        // Its statically identified literal remains native punctuation.
        if(e.id==hud_surface_first && e.arguments[0]==address(at<char>(0x1AA240))) return Status::ok;
        return hud_lend(e,hud_surface_calls[e.id-hud_surface_first].component,0,Scope::text);
    }
    if(e.id>=hud_center_first && e.id<hud_center_first+std::size(hud_center_calls)) {
        const auto component=hud_center_calls[e.id-hud_center_first].component;
        const auto* name=component==TextComponent::world_place_gloss ? ptr<char>(e.frame->ebp-0x278) : nullptr;
        return hud_lend(e,component,1,Scope::hud_centered,name,e.arguments[3]);
    }
    if(e.id>=hud_penalty_first && e.id<hud_penalty_first+5)
        return hud_lend(e,TextComponent::hud_penalty,0,Scope::hud_penalty,nullptr,1);
    switch(e.id) {
    case hud_command:
        // This call also consumes native command descriptions. Only its literal
        // heading branch has the statically confirmed Command: pointer.
        if(e.arguments[0]==address(at<char>(0x1AA14C)))
            return hud_lend(e,TextComponent::hud_label,0,Scope::text);
        return Status::ok;
    case hud_repeat: case hud_help:
        begin(e,Scope::hud_button); return Status::ok;
    case hud_wielded:
        return hud_lend(e,TextComponent::hud_label,1,Scope::hud_title);
    case setup_exit_text:
        if(in(Scope::hud_button)) return hud_lend(e,TextComponent::hud_label,0,Scope::text);
        break;
    case shared_title_text:
        if(in(Scope::hud_title)) { begin(e,Scope::text,e.arguments[2]); return Status::ok; }
        break;
    case hud_penalty_width:
        if(in(Scope::hud_penalty)) {
            render::Metrics width{};
            const auto status=metrics_at_outline(ptr<char>(e.frame->edx),0,width);
            if(status!=Status::ok) return status;
            e.frame->eax=static_cast<u32>(width.logical_width);
            e.frame->ecx-=e.frame->eax;
            result.skip_original=1;
        }
        return Status::ok;
    case hud_penalty_draw:
        if(in(Scope::hud_penalty)) begin(e,Scope::text,e.arguments[2]);
        return Status::ok;
    case hud_center_fit:
        if(in(Scope::hud_centered)) {
            render::Metrics line{},word{};
            auto status=metrics(ptr<char>(e.frame->ebp-0x404),line);
            if(status!=Status::ok) return status;
            status=metrics(ptr<char>(e.frame->ebp-0x804),word);
            if(status!=Status::ok) return status;
            e.frame->eax=static_cast<u32>(line.logical_width+word.logical_width);
            result.skip_original=1;
        }
        return Status::ok;
    case hud_center_line: case hud_center_last:
        if(in(Scope::hud_centered)) return native_width(e,result,ptr<char>(e.frame->ebp-0x404));
        return Status::ok;
    case hud_center_draw_line: case hud_center_draw_last:
        if(in(Scope::hud_centered)) begin(e,Scope::text,e.arguments[2]);
        return Status::ok;
    case hud_month_append:
        return append(e,TextComponent::world_month);
    case hud_month_paragraph:
        begin(e,Scope::paragraph,e.arguments[3]); return Status::ok;
    case hud_scale_width: {
        auto* original=ptr<char>(e.frame->ebp-0x70);
        std::vector<char> encoded;
        auto status=hud_translate(TextComponent::world_scale,original,nullptr,encoded);
        if(status!=Status::ok) return status;
        std::memcpy(original,encoded.data(),encoded.size());
        render::Metrics width{};
        status=hud_scale_metrics(original,width);
        if(status!=Status::ok) return status;
        // Replace LEA(line_length + strlen*8), then retain its CDQ/SUB.
        // The original division and scale-line positioning execute next.
        e.frame->eax=e.frame->edx+static_cast<u32>(width.logical_width);
        e.frame->edx=static_cast<std::int32_t>(e.frame->eax)<0 ? 0xFFFFFFFFu : 0;
        e.frame->eax-=e.frame->edx;
        result.skip_original=1;
        return Status::ok;
    }
    case hud_scale_call:
        native_component_binding::note_source_for_consumer(e,TextComponent::world_scale);
        begin(e,Scope::hud_scale,1); return Status::ok;
    case hud_scale_text:
        if(in(Scope::hud_scale)) begin(e,Scope::text,e.arguments[2]);
        return Status::ok;
    case hud_identity_width: {
        std::vector<char> encoded;
        auto status=hud_identity_display(e,ptr<char>(e.frame->ebp-0x408),encoded);
        if(status!=Status::ok) return status;
        render::Metrics measured{};
        status=metrics_at_outline(encoded.data(),1,measured);
        if(status!=Status::ok) return status;
        // Replace only LEA EAX,[ECX*8]. Native division, centering and both
        // panel branches continue with the width of the same display string.
        e.frame->eax=static_cast<u32>(measured.logical_width);
        result.skip_original=1;
        return Status::ok;
    }
    case hud_identity_draw_first: case hud_identity_draw_second: {
        std::vector<char> encoded;
        auto status=hud_identity_display(e,ptr<char>(e.arguments[0]),encoded);
        if(status!=Status::ok) return status;
        render::Metrics measured{};
        status=metrics_at_outline(encoded.data(),e.arguments[2]&1u,measured);
        if(status!=Status::ok) return status;
        native_component_binding::note_center(e,static_cast<std::int32_t>(e.frame->ecx)+measured.logical_width/2);
        return lend_text(e,encoded,e.arguments[0],Scope::text);
    }
    case hud_target_entry:
        return native_targets::promote_hud();
    case hud_speed: {
        const std::string original=ptr<char>(e.arguments[2]);
        const auto heading=original.substr(0,original.find(':')+1);
        std::vector<char> encoded;
        const auto status=hud_translate(TextComponent::hud_speed,heading.c_str(),nullptr,encoded);
        if(status!=Status::ok) return status;
        return lend_text(e,encoded,e.arguments[2],Scope::hud_renderer);
    }
    case hud_action: case hud_direction:
        return hud_lend(e,e.id==hud_action ? TextComponent::hud_action :
            TextComponent::hud_direction,
            2,Scope::hud_renderer);
    case hud_renderer_wrapper:
        if(in(Scope::hud_renderer)) begin(e,Scope::hud_renderer_text,e.arguments[3]&1u);
        return Status::ok;
    case hud_speed_number: {
        // FAD59/FADB6 already formatted the selected metric/imperial speed.
        // FAE38 supplies the heading alone; this native numeric draw consumes
        // the same value with its unit. Its coordinates and native color stay.
        std::string value=ptr<char>(e.arguments[1]);
        value+=*at<u32>(0xA2D0AF4) ? " km/h" : " mi/h";
        native_component_binding::note_original_for_consumer(e,value.c_str());
        std::vector<char> encoded;
        const auto status=codec(layout_op::encode_native,value.c_str(),encoded);
        if(status!=Status::ok) return status;
        return lend_text(e,encoded,e.arguments[1],Scope::hud_renderer_text,e.arguments[3]&1u);
    }
    case hud_renderer_top: case hud_renderer_bottom: case hud_renderer_left:
    case hud_renderer_right: case hud_renderer_foreground:
        if(in(Scope::hud_renderer_text) || in(Scope::native_renderer_resource) ||
            native_name_input::contains_display(ptr<char>(e.arguments[1]))) {
            const auto status=hud_draw_renderer(e);
            if(status!=Status::ok) return status;
            result.skip_original=1;
        }
        return Status::ok;
    default: break;
    }
    handled=false;
    return Status::ok;
}
void append_hud_hooks(std::vector<HookSpec>& hooks) {
    for(u32 i=0;i<std::size(hud_surface_calls);++i)
        hooks.push_back(call(hud_surface_first+i,hud_surface_calls[i].site,0x10E5A0,3));
    hooks.push_back(call(hud_command,0xF91E7,0x10E5A0,3));
    hooks.push_back(call(hud_repeat,0xF9660,0x114680,2));
    hooks.push_back(call(hud_help,0xFA394,0x114680,2));
    hooks.push_back(call(hud_wielded,0xF92A5,0x1157B0,3));
    constexpr u32 penalties[]{0xFF131,0x102F84,0x103080,0x103154,0x10326B};
    for(u32 i=0;i<std::size(penalties);++i)
        hooks.push_back(call(hud_penalty_first+i,penalties[i],0xFEE50,2));
    hooks.push_back(inline_hook(hud_penalty_width,0xFEEB2,{0xC1,0xE0,0x03,0x2B,0xC8}));
    hooks.push_back(call(hud_penalty_draw,0xFEEC9,0x10E5A0,3));
    hooks.push_back(inline_hook(hud_center_fit,0x10E9FB,{0x8D,0x04,0x0A,0xC1,0xE0,0x03}));
    hooks.push_back(inline_hook(hud_center_line,0x10EA74,{0x8D,0x04,0xCD,0,0,0,0}));
    hooks.push_back(inline_hook(hud_center_last,0x10EAF8,{0x8D,0x04,0xCD,0,0,0,0}));
    hooks.push_back(call(hud_center_draw_line,0x10EA95,0x10E5A0,3));
    hooks.push_back(call(hud_center_draw_last,0x10EB19,0x10E5A0,3));
    hooks.push_back(call(hud_month_append,0x1037BF,0x162300,0));
    hooks.push_back(call(hud_month_paragraph,0x103816,0x10EB40,4));
    for(u32 i=0;i<std::size(hud_center_calls);++i)
        hooks.push_back(call(hud_center_first+i,hud_center_calls[i].site,0x10E910,4));
    hooks.push_back(inline_hook(hud_scale_width,0x907B3,{0x8D,0x04,0xCA,0x99,0x2B,0xC2}));
    hooks.push_back(call(hud_scale_call,0x907DB,0x8FE90,2));
    hooks.push_back(call(hud_scale_text,0x8FF44,0x10E5A0,3));
    hooks.push_back(inline_hook(hud_identity_width,0xFA493,{0x8D,0x04,0xCD,0,0,0,0}));
    hooks.push_back(call(hud_identity_draw_first,0xFA4D8,0x10E5A0,3));
    hooks.push_back(call(hud_identity_draw_second,0xFA507,0x10E5A0,3));
    auto target=inline_hook(hud_target_entry,0xFAA4B,{0x8B,0x1D,0,0,0,0});
    const u32 color_import=address(at<void>(0x18C1E4));
    std::memcpy(target.expected+2,&color_import,4);
    hooks.push_back(target);
    hooks.push_back(call(hud_action,0xFAC9C,0x111560,4));
    hooks.push_back(call(hud_direction,0xFACF2,0x111560,4));
    hooks.push_back(call(hud_speed,0xFAE38,0x111560,4));
    hooks.push_back(call(hud_renderer_wrapper,0x111682,0x10E260,4));
    hooks.push_back(call(hud_speed_number,0xFAEFF,0x10E260,4));
    hooks.push_back(call(hud_renderer_top,0x10E33B,0x10DE90,3));
    hooks.push_back(call(hud_renderer_bottom,0x10E357,0x10DE90,3));
    hooks.push_back(call(hud_renderer_left,0x10E371,0x10DE90,3));
    hooks.push_back(call(hud_renderer_right,0x10E38D,0x10DE90,3));
    hooks.push_back(call(hud_renderer_foreground,0x10E3BD,0x10DE90,3));
}
