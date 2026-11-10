// 55060 / 54160: the native inventory owns the list, controls and preview.
// Only original text expressions cross these complete component CALLs.
// Evidence: docs/evidence/20261110-wield-inventory-native.md.
// Sacrifice: docs/evidence/20261110-sacrifice-inventory-native.md.
// Complete caller/text census: docs/evidence/20261110-inventory-all-text.md.
Status native_text_limit(std::vector<char>& encoded,std::int32_t maximum,std::int32_t retained,u32 outline) {
    render::Metrics measured{};auto status=metrics_at_outline(encoded.data(),outline,measured);
    if(status!=Status::ok || measured.logical_width<=maximum) return status;
    const std::string full(encoded.data());std::size_t cut=0;
    for(std::size_t next=0;next<full.size();) {
        next+=static_cast<unsigned char>(full[next])<0x80 ? 1u : 2u;
        const auto prefix=full.substr(0,next);
        status=metrics_at_outline(prefix.c_str(),outline,measured);
        if(status!=Status::ok) return status;
        if(measured.logical_width>retained) break;
        cut=next;
    }
    const auto clipped=full.substr(0,cut)+"..";
    encoded.assign(clipped.begin(),clipped.end());encoded.push_back(0);return Status::ok;
}
namespace windows_inventory {
enum Hook:u32 {
    text_first=0x18200,name_copy=0x18300,row_format,partial_row_format,item_button,
    viewing_all,viewing_category,all_types_format,viewing_width,all_types_width,
    enter_origin,remaining_format,
    extra_text_first=0x18320,weight_copy=0x18340,quantity_format,quantity_more_format,cancel_source
};
struct TextCall {u32 site,target;const char* domain;};
constexpr TextCall text_calls[]{
    {0x5565B,0x116270,"inventory.ui"},
    {0x5570A,0x10E5A0,"inventory.ui"},
    {0x5573A,0x10E5A0,"inventory.verb"},
    {0x5576B,0x10E5A0,"inventory.ui"},
    {0x559D2,0x10E5A0,"inventory.ui"},
    {0x55A23,0xCFAF0,"inventory.ui"},
    {0x55A78,0x10E5A0,"inventory.ui"},
    {0x55B04,0xCFAF0,"inventory.ui"},
    {0x55B7E,0xCFAF0,"inventory.ui"},
    {0x55C76,0xCFAF0,"inventory.ui"},
    {0x55CA9,0xCFAF0,"inventory.ui"},
    {0x55D2A,0xCFAF0,"inventory.ui"},
    {0x55E2C,0xCFAF0,"inventory.ui"},
    {0x55E49,0xCFAF0,"inventory.ui"},
    {0x55E69,0xCFAF0,"inventory.ui"},
    {0x55EAB,0xCFAF0,"inventory.ui"},
    {0x55F9E,0x10E5A0,"inventory.ui"},
    {0x56015,0xCFAF0,"inventory.ui"},
    {0x5434B,0x1157B0,"menu.label"},
    {0x548E0,0x1157B0,"menu.label"},
    {0x5438E,0x10E5A0,"inventory.ui"},
    {0x543D6,0x10E5A0,"inventory.ui"},
    {0x5440F,0x10E5A0,"inventory.ui"},
    {0x544E4,0x10E5A0,"inventory.ui"},
    {0x54920,0x10E5A0,"inventory.ui"}
};
// Append independently: the original text IDs and the two following IDs stay
// stable across compatible module handover.
constexpr TextCall extra_text_calls[]{
    {0x5478B,0x10E5A0,"inventory.ui"},
    {0x547E1,0x10E5A0,"inventory.ui"},
    {0x4B19C,0x10E5A0,"inventory.ui"},
    {0xFBE1B,0x116270,"inventory.ui"},
    {0xFBFB8,0x116270,"inventory.ui"},
    {0xFBE91,0xCFAF0,"inventory.ui"},
    {0xFBF3F,0xCFAF0,"inventory.ui"},
    {0xFC05F,0x10E5A0,"inventory.ui"},
    {0xFBC54,0xCFAF0,"inventory.ui"},
    {0xFBC6D,0xCFAF0,"inventory.ui"}
};

std::string expression_key(const MessageText& source) {
    std::vector<unsigned char> bytes;native_message_source::write(bytes,source);
    constexpr char digits[]="0123456789abcdef";
    std::string value;
    for(const auto byte:bytes) {value+=digits[byte>>4];value+=digits[byte&15];}
    return value;
}
native_text_resource::TextSource expression(const char* original,const MessageText& source,
        TextComponent component=TextComponent::native_message_expression) {
    return {component,message_source_utf8(original),expression_key(source),true,
        native_text_resource::TextPolicy::semantic,{},{}};
}
Status consume_source(const NativeEvent& e,const native_text_resource::TextSource& source,u32 argument,Scope scope) {
    native_component_binding::bind_source(e,source);
    // CFAF0 forwards this label to CF990 while constructing the accepted
    // native Menu. Keep its semantic source with that same original row.
    if(scope==Scope::setup_exit || scope==Scope::creation_button)
        native_menu_component::bind_constructor_row(e.token,source);
    if(!chinese_enabled) return Status::ok;
    std::vector<char> encoded;
    const auto status=native_text_resource::resolve_source(source,resolve_display_text,encode_component_original,encoded);
    if(status!=Status::ok) return status;
    return lend_text(e,encoded,e.arguments[argument],scope,
        scope==Scope::text ? e.arguments[2] : *at<u32>(0x5F54A9C));
}
Status bind_expression(const NativeEvent& e,const char* original,const MessageText& source,
        TextComponent component=TextComponent::native_message_expression) {
    native_component_binding::bind_source(e,expression(original,source,component));
    return Status::ok;
}
MessageText read_expression(const char* value) {
    const std::string key(value);std::vector<unsigned char> bytes;
    for(std::size_t i=0;i<key.size();i+=2)
        bytes.push_back(static_cast<unsigned char>(std::stoul(key.substr(i,2),nullptr,16)));
    const auto* cursor=bytes.data();return native_message_source::read(cursor);
}
Status resolve_expression(TextComponent component,const char* value,std::vector<char>& encoded) {
    const auto source=read_expression(value);
    std::string text;auto status=message_project_source(source,true,text);
    if(status!=Status::ok) return status;
    status=codec(layout_op::encode_native,text.c_str(),encoded);
    if(status!=Status::ok || component!=TextComponent::inventory_item_text) return status;
    // 54619 compares the complete native label with 40 cells, then 5461E
    // retains 38 cells and appends two dots. Extend that same native bound
    // using complete glyph metrics; no UI position or output is cached.
    // CFAF0 retains the two original prefix cells separately from this suffix.
    const auto cells=*at<unsigned char>(0x5461B)-2;
    return native_text_limit(encoded,cells*8-1,(cells-2)*8,0);
}
Status bind_text(const NativeEvent& e,const TextCall& c) {
    const auto argument=c.target==0x116270 ? 2u :
        c.target==0xCFAF0 || c.target==0x1157B0 ? 1u : 0u;
    const auto* original=ptr<char>(e.arguments[argument]);
    if(c.site==0x55A78 && std::strncmp(original,"...or select ",13)==0)
        return consume_source(e,expression(original,windows_messages::values.at(address(original)).text),0,Scope::text);
    if(c.site==0x547E1 || c.site==0xFBE1B || c.site==0xFBFB8) {
        if(c.site==0x547E1)
            native_component_binding::note_native_record(e,*ptr<u32>(e.frame->ebp-0x81C));
        return consume_source(e,expression(original,message_source_bound(original)),argument,
            c.target==0x116270 ? Scope::titled_panel : Scope::text);
    }
    if(c.site==0xFBC54 || c.site==0xFBC6D) {
        // These actual labels are <Y>es / <N>o, with native highlight
        // delimiters, rather than the dotted keycap syntax used below.
        return consume_source(e,native_text_resource::from_request(
            {TextComponent::message_value,original,"inventory.ui"}),argument,Scope::creation_button);
    }
    // Every 55060/581F0 caller is statically enumerated, including the
    // original empty verb. The native EBP+14h input owns that distinction.
    const auto* domain=c.site==0x5570A && *ptr<char>(*ptr<u32>(e.frame->ebp+0x14))==0
        ? "inventory.no-verb" : c.domain;
    const auto* suffix=c.target==0xCFAF0 ? std::strchr(original,'.')+1 : original;
    auto source=native_text_resource::from_request({TextComponent::message_value,
        message_source_utf8(suffix).c_str(),domain});
    source.prefix.assign(original,suffix);
    if(c.target==0x1157B0) native_component_binding::note_native_record(e,
        c.site==0x5434B ? static_cast<unsigned char>(e.frame->ebx) : e.frame->edi);
    if(c.site==0x54920) native_component_binding::note_native_record(e,e.frame->edi);
    if(c.site==0x5438E || c.site==0x543D6 || c.site==0x5440F || c.site==0x544E4 || c.site==0x5478B)
        native_component_binding::note_native_record(e,*ptr<u32>(e.frame->ebp-0x81C));
    const auto scope=c.target==0x116270 || c.target==0x1157B0 ? Scope::titled_panel :
        c.target==0xCFAF0 ? Scope::setup_exit : Scope::text;
    return consume_source(e,source,argument,scope);
}
Status measure_expression(const char* original,render::Metrics& measured) {
    std::vector<char> encoded;
    const auto& source=windows_messages::values.at(address(original)).text;
    auto status=resolve_display_text(TextComponent::native_message_expression,original,expression_key(source).c_str(),encoded);
    return status==Status::ok ? metrics_at_outline(encoded.data(),0,measured) : status;
}
void append_hooks(std::vector<HookSpec>& hooks) {
    for(u32 i=0;i<std::size(text_calls);++i) {
        const auto& c=text_calls[i];
        hooks.push_back(call(text_first+i,c.site,c.target,c.target==0x116270 ? 5 :
            c.target==0xCFAF0 ? 2 : 3));
    }
    hooks.push_back(call(name_copy,0x5451D,0x52640,1));
    hooks.push_back(call(row_format,0x545CF,0x10D0,4));
    hooks.push_back(call(partial_row_format,0x545FE,0x10D0,5));
    hooks.push_back(call(item_button,0x54690,0xCFAF0,2));
    hooks.push_back(call(viewing_all,0x55EC7,0x10D0,2));
    hooks.push_back(call(viewing_category,0x55EE6,0x10D0,3));
    hooks.push_back(call(all_types_format,0x55FB9,0x10D0,3));
    hooks.push_back(inline_hook(viewing_width,0x55F42,{0x8D,0x04,0xCD,0,0,0,0}));
    hooks.push_back(inline_hook(all_types_width,0x55FEB,{0x8D,0x04,0xCD,0,0,0,0}));
    hooks.push_back(inline_hook(enter_origin,0x559EE,{0x8D,0x89,0xE9,0,0,0}));
    hooks.push_back(call(remaining_format,0x55BEC,0x10D0,3));
    hooks.push_back(call(text_first+std::size(text_calls),0x55F86,0x10E5A0,3));
    hooks.push_back(call(text_first+std::size(text_calls)+1,0x55FF9,0xCFAF0,2));
    for(u32 i=0;i<std::size(extra_text_calls);++i) {
        const auto& c=extra_text_calls[i];
        hooks.push_back(call(extra_text_first+i,c.site,c.target,c.target==0x116270 ? 5 :
            c.target==0xCFAF0 ? 2 : 3));
    }
    // 4BD15..4BD1F prepares the exact 4B2F0 return's native copy. The loop
    // backedge starts at 4BD20, after this single source association.
    hooks.push_back(inline_hook(weight_copy,0x4BD15,{0x8B,0xD3,0x2B,0xD0,0x0F,0x1F,0x80,0,0,0,0}));
    hooks.push_back(call(quantity_format,0xFBDE8,0x10D0,3));
    hooks.push_back(call(quantity_more_format,0xFBF99,0x10D0,3));
    hooks.push_back(call(cancel_source,0x568C8,0xFBB10,0));
}
Status dispatch(const NativeEvent& e,DispatchResult& result,bool& handled) {
    handled=(e.id>=text_first && e.id<=remaining_format) ||
        (e.id>=extra_text_first && e.id<extra_text_first+std::size(extra_text_calls)) ||
        (e.id>=weight_copy && e.id<=cancel_source);
    if(!handled) return Status::ok;
    if(e.id>=extra_text_first && e.id<extra_text_first+std::size(extra_text_calls))
        return e.phase==NativePhase::before ? bind_text(e,extra_text_calls[e.id-extra_text_first]) : Status::ok;
    if(e.id==weight_copy) {
        if(e.phase==NativePhase::inline_before) {
            const auto* original=ptr<char>(e.frame->eax);
            message_bind_copy(ptr<char>(e.frame->ebx),original,message_source_bound(original));
        }
        return Status::ok;
    }
    if(e.id==quantity_format || e.id==quantity_more_format) {
        if(e.phase==NativePhase::after) message_bind_source(ptr<char>(e.arguments[0]),native_message_source::format(
            message_source_lookup("inventory.format",ptr<char>(e.arguments[1])),
            {native_message_source::scalar(native_message_source::Scalar::signed32,e.arguments[2],"%d")},{"%d"}));
        return Status::ok;
    }
    if(e.id==cancel_source) {
        if(e.phase==NativePhase::before) {
            const auto* original=ptr<char>(e.frame->ecx);
            message_bind_source(ptr<char>(e.frame->ecx),message_source_lookup("inventory.ui",original));
        }
        return Status::ok;
    }
    if(e.id>=text_first && e.id<text_first+std::size(text_calls))
        return e.phase==NativePhase::before ? bind_text(e,text_calls[e.id-text_first]) : Status::ok;
    if(e.id==name_copy && e.phase==NativePhase::after) {
        // 54522..5453B copies this exact returned quantity/name to EBP-808.
        const auto* original=ptr<char>(e.frame->eax);
        message_bind_copy(ptr<char>(e.frame->ebp-0x808),original,message_source_bound(original));
    }
    if((e.id==row_format || e.id==partial_row_format) && e.phase==NativePhase::after) {
        const auto* name=ptr<char>(e.arguments[e.id==row_format ? 3 : 4]);
        const auto& copied=windows_messages::values.at(address(name));
        auto item=copied.text;
        // The only additions between the proven copy and sprintf are the
        // native unpaid/taken annotations. Their original appended input is
        // sliced at that actual copied source length, never token-guessed.
        const auto* suffix=name+copied.source.size();
        if(*suffix) item=native_message_source::concat({item,message_source_lookup("inventory.suffix",suffix)});
        std::vector<MessageText> values{native_message_source::scalar(native_message_source::Scalar::character,e.arguments[2],"%c")};
        std::vector<std::string> syntax{"%c"};
        if(e.id==partial_row_format) {
            values.push_back(native_message_source::scalar(native_message_source::Scalar::signed32,e.arguments[3],"%d"));
            syntax.emplace_back("%d");
        }
        values.push_back(std::move(item));syntax.emplace_back("%s");
        message_bind_source(ptr<char>(e.arguments[0]),native_message_source::format(
            message_source_identity(ptr<char>(e.arguments[1])),std::move(values),std::move(syntax)));
    }
    if(e.phase==NativePhase::after) {
        if(e.id==viewing_all) message_bind_source(ptr<char>(e.arguments[0]),
            message_source_lookup("inventory.ui",ptr<char>(e.arguments[1])));
        if(e.id==viewing_category) message_bind_source(ptr<char>(e.arguments[0]),native_message_source::format(
            message_source_lookup("inventory.format",ptr<char>(e.arguments[1])),
            {message_source_lookup("menu.label",ptr<char>(e.arguments[2]))},{"%s"}));
        if(e.id==all_types_format) message_bind_source(ptr<char>(e.arguments[0]),native_message_source::format(
            message_source_lookup("inventory.format",ptr<char>(e.arguments[1])),
            {native_message_source::scalar(native_message_source::Scalar::character,e.arguments[2],"%c")},{"%c"}));
        if(e.id==remaining_format) message_bind_source(ptr<char>(e.arguments[0]),native_message_source::format(
            message_source_lookup("inventory.format",ptr<char>(e.arguments[1])),
            {native_message_source::scalar(native_message_source::Scalar::signed32,e.arguments[2],"%d")},{"%d"}));
        return Status::ok;
    }
    if(e.id==item_button) {
        const auto* original=ptr<char>(e.arguments[1]);
        auto source=expression(original,windows_messages::values.at(address(original)).text,TextComponent::inventory_item_text);
        // The original single-letter cap and '.' remain native button syntax.
        const auto split=source.original.find('.')+1;
        source.prefix=source.original.substr(0,split);source.original.erase(0,split);
        const auto& formatted=windows_messages::values.at(address(original)).text;
        auto suffix=formatted.children.back();
        if(formatted.children.size()==4) suffix=native_message_source::format(
            native_message_source::original("(%d) %s"),{formatted.children[2],std::move(suffix)},{"%d","%s"});
        source.value=expression_key(suffix);
        return consume_source(e,source,1,Scope::setup_exit);
    }
    if(e.id==text_first+std::size(text_calls) || e.id==text_first+std::size(text_calls)+1) {
        const auto* original=ptr<char>(e.arguments[e.id==text_first+std::size(text_calls) ? 0 : 1]);
        if(e.id==text_first+std::size(text_calls)) {
            render::Metrics measured{};auto status=measure_expression(original,measured);
            if(status!=Status::ok) return status;
            native_component_binding::note_center(e,static_cast<std::int32_t>(e.frame->ecx)+measured.logical_width/2);
            return consume_source(e,expression(original,windows_messages::values.at(address(original)).text),0,Scope::text);
        }
        const auto* suffix=std::strchr(original,'.')+1;
        auto source=native_text_resource::from_request({TextComponent::message_value,suffix,"inventory.ui"});
        source.prefix.assign(original,suffix);return consume_source(e,source,1,Scope::setup_exit);
    }
    if(!chinese_enabled) return Status::ok;
    if(e.id==viewing_width || e.id==all_types_width) {
        const auto* original=ptr<char>(e.frame->esp+(e.id==viewing_width ? 0x7A4 : 0x7A0));
        render::Metrics measured{};auto status=measure_expression(original,measured);
        if(status!=Status::ok) return status;
        e.frame->eax=static_cast<u32>(measured.logical_width);
        result.resume_rva=e.id==viewing_width ? 0x55F49 : 0x55FF2;
    } else if(e.id==enter_origin) {
        // Extend the native LEA's text operand by the measured prefix delta.
        // Its original displacement and the following keycap CALL still run.
        const char* original="Use hotkeys, mouse click or ";
        std::vector<char> encoded;auto status=resolve_display_text(TextComponent::message_value,original,"inventory.ui",encoded);
        if(status!=Status::ok) return status;
        render::Metrics measured{};status=metrics_at_outline(encoded.data(),0,measured);
        if(status!=Status::ok) return status;
        e.frame->ecx+=measured.logical_width-static_cast<u32>(std::strlen(original)*8);
    }
    return Status::ok;
}
}
Status resolve_native_message_expression(TextComponent component,const char* value,std::vector<char>& encoded) {
    return windows_inventory::resolve_expression(component,value,encoded);
}
