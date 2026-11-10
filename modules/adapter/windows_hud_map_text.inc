// Windows 3.89.1 HUD/map text closure. See 20261110-hud-map-all-text.md.
// Every source is an original producer, format operand or complete text CALL.
// No positions, page contents, target pixels or deferred drawing are retained.
Status lend_hud_command(const NativeEvent& e) {
    if(!chinese_enabled) return Status::ok;
    std::vector<char> encoded;
    auto status=hud_translate(TextComponent::message_value,native_hud_language::command.c_str(),
        "hud.command",encoded);
    if(status!=Status::ok) return status;
    // F9109 compares >26; F910E retains 24 bytes and adds two dots.
    status=native_text_limit(encoded,26*8,24*8,e.arguments[2]&1u);
    if(status!=Status::ok) return status;
    return lend_text(e,encoded,e.arguments[0],Scope::text);
}

namespace windows_hud_map_text {
enum Hook:u32 {
    repeat_source=0x18600,repeat_draw,
    control_first=0x18610,panel_first=0x18620,label_first=0x18630,
    marker_first=0x18640,parser_first=0x18650,paragraph_first=0x18660,
    format_first=0x18670,annotation_store_first=0x18690,informant=0x186A0,
    place_width,order_width,net_width,marker_width_first,marker_width_second,
    craft_name_first=0x186B0,override_copy=0x186B2
};
constexpr u32 panels[]{0xE4224,0xE4A1D};
constexpr u32 labels[]{0xE45F8,0xE581D};
constexpr u32 markers[]{0xE440B,0xE442C,0xE5781,0xE57AB};
constexpr u32 parsers[]{0xE41E5,0xE41F1,0xE4DA2,0xE4DBF,0xE4DDD,0xE4DFD,
    0xE4FA4,0xE50F7,0xE53F7};
constexpr u32 paragraphs[]{0xE4245,0xE54E2,0xE5595};
enum Format:u32 {order_days,visit_days,order,net,trap,place,quest_origin,quest_first,
    quest_second,quest_informant,quest_target};
struct FormatCall {u32 site,words;};
constexpr FormatCall formats[]{
    {0xE505D,3},{0xE5352,3},{0xE50E7,4},{0xE53AF,3},{0xE53D3,3},{0xE4F94,3},
    {0xE2AC8,4},{0xE2BC6,4},{0xE2CC6,4},{0xE2E26,3},{0xE2FC2,4}
};
constexpr u32 stores[]{0xE2AE2,0xE2BE4,0xE2CE4,0xE2EDE,0xE2FE0};
void bind_format(u32 owner,MessageText source) {
    // The following native sprintf writes this exact original expression.
    auto original=source.original;
    windows_messages::values[owner]={std::move(original),std::move(source)};
}
MessageText age(const char* original) {
    // These are the three actual branches in E5025 and E530D.
    if(std::strcmp(original,"today")==0 || std::strcmp(original,"yesterday")==0)
        return message_source_lookup("hud.map",original);
    return windows_messages::values.at(address(original)).text;
}
MessageText quest_title(const char* uppercase) {
    // All five E2960 format sites select the current quest's 636C83F title.
    const auto* record=at<char>(0x5F6C820);
    windows_message_quest_records::bind_record(record);
    auto source=native_message_source::concat({message_source_bound(record+31)});
    source.original=message_source_utf8(uppercase); // Native toupper's result.
    return source;
}
Status paragraph_source(const NativeEvent& e,u32 index) {
    if(!chinese_enabled) return Status::ok;
    const auto* original=ptr<char>(e.frame->edx);
    const auto source=index<2 ? message_source_lookup("hud.map",original) : message_source_bound(original);
    std::string utf8;auto status=message_project_source(source,true,utf8);
    if(status!=Status::ok) return status;
    std::vector<char> encoded;status=codec(layout_op::encode_native,utf8.c_str(),encoded);
    if(status!=Status::ok) return status;
    // Feed complete glyph words to the existing 162300 parser. 10EFD0 owns
    // line selection, spacing, width/height measurement and both final draws.
    const auto words=native_paragraph_words(encoded.data());
    encoded.assign(words.begin(),words.end());encoded.push_back(0);
    return lend_text(e,encoded,e.frame->edx,Scope::allocation);
}
void append_hooks(std::vector<HookSpec>& hooks) {
    if(!windows_build::is_3891()) return;
    hooks.push_back(inline_hook(repeat_source,0xF9869,{0x8D,0x4C,0x24,0x20,0x8D,0x51,0x01}));
    hooks.push_back(call(repeat_draw,0xF98F1,0x10E5A0,3));
    for(u32 i=0;i<std::size(windows_map_dialog_control_calls);++i)
        hooks.push_back(call(control_first+i,windows_map_dialog_control_calls[i].site,0xCFD10,3));
    for(u32 i=0;i<std::size(panels);++i) hooks.push_back(call(panel_first+i,panels[i],0x1166C0,6));
    for(u32 i=0;i<std::size(labels);++i) hooks.push_back(call(label_first+i,labels[i],0x10E260,4));
    for(u32 i=0;i<std::size(markers);++i) hooks.push_back(call(marker_first+i,markers[i],0x10E260,4));
    for(u32 i=0;i<std::size(parsers);++i) hooks.push_back(call(parser_first+i,parsers[i],0x162300,0));
    for(u32 i=0;i<std::size(paragraphs);++i) hooks.push_back(call(paragraph_first+i,paragraphs[i],0x10EFD0,5));
    for(u32 i=0;i<std::size(formats);++i) hooks.push_back(call(format_first+i,formats[i].site,0x10D0,formats[i].words));
    for(u32 i=0;i<std::size(stores);++i) hooks.push_back(call(annotation_store_first+i,stores[i],0xE2850,2));
    hooks.push_back(call(informant,0xE2E63,0xAE3F0,0));
    hooks.push_back(inline_hook(place_width,0xE4FB9,{0x2B,0xCA,0xC6,0x85,0x37,0xEE,0xFF,0xFF,1}));
    auto order_measure=inline_hook(order_width,0xE510C,{0x2B,0xCA,0xBA,0,0,0,0});
    const auto separator=address(at<char>(0x19416C));std::memcpy(order_measure.expected+3,&separator,4);
    hooks.push_back(order_measure);
    hooks.push_back(inline_hook(net_width,0xE540C,{0x2B,0xCA,0xB0,1,0x3B,0xCB}));
    hooks.push_back(inline_hook(marker_width_first,0xE5177,{0x2B,0xCA,0x8D,0x41,4}));
    hooks.push_back(inline_hook(marker_width_second,0xE519D,{0x2B,0xCA,0x8B,0xBD,0,0xEE,0xFF,0xFF}));
    hooks.push_back(call(craft_name_first,0xF97BC,0x6C8B0,0));
    hooks.push_back(call(craft_name_first+1,0xF983C,0x6C8B0,0));
    auto copy=inline_hook(override_copy,0x1639FD,{0xBA,0,0,0,0});
    const auto name=address(at<char>(0xA2D1C38));std::memcpy(copy.expected+1,&name,4);hooks.push_back(copy);
}
Status dispatch(const NativeEvent& e,DispatchResult&,bool& handled) {
    handled=e.id>=repeat_source && e.id<=override_copy;
    if(!handled) return Status::ok;
    if(e.id>=control_first && e.id<control_first+std::size(windows_map_dialog_control_calls)) {
        const auto index=e.id-control_first;
        if(e.phase==NativePhase::before)
            begin(e,static_cast<Scope>(static_cast<u32>(Scope::known_map_dialog_control_first)+index));
        else if(e.phase==NativePhase::after) {
            const auto& call=windows_map_dialog_control_calls[index];
            const auto* original=ptr<char>(e.arguments[2]);
            const auto source=call.key ? native_text_resource::from_request({TextComponent::culture_text,original,call.key}) :
                windows_inventory::expression(original,message_source_identity(original));
            native_menu_component::commit_row(native_menu_component::active(),*at<u32>(0x5F54A34)-1,source);
        }
        return Status::ok;
    }
    if(e.id>=annotation_store_first && e.id<annotation_store_first+std::size(stores)) {
        if(e.phase==NativePhase::after) {
            // Every successful E2850 copy leaves EDX=destination-source.
            // Its selected native slot is observed from that actual result.
            const auto* original=ptr<char>(e.arguments[1]);
            message_bind_copy(ptr<char>(e.frame->edx+e.arguments[1]),original,message_source_bound(original));
        }
        return Status::ok;
    }
    if(e.id==informant) {
        if(e.phase==NativePhase::after) {
            const auto owner=e.frame->ebp-0x408;
            const bool same=*at<u32>(0x5FA2C84)==*at<u32>(0x5F7B75C) &&
                *at<u32>(0x5FA2C88)==*at<u32>(0x5F7B760);
            auto prefix=same ? native_message_source::original("") : windows_messages::values.at(owner).text;
            bind_format(owner,native_message_source::concat({std::move(prefix),
                message_source_lookup("hud.map","<indblue>informant: </indblue><infoblue>"),
                message_source_identity(ptr<char>(e.frame->eax)),native_message_source::original("</infoblue><br>")}));
        }
        return Status::ok;
    }
    if(e.id==craft_name_first || e.id==craft_name_first+1) {
        if(e.phase==NativePhase::after) {
            const auto* name=ptr<char>(e.frame->eax);
            const auto first=address(at<char>(0x54FA001));
            MessageText source;
            // 6C8B0 returns either an embedded requirement or CONSTANT.OBJ
            // descriptor+9. Preserve that actual source class and item grammar.
            if(e.frame->eax>=first && e.frame->eax<first+400*0xAC) {
                const auto status=message_crafted_item_source(ptr<unsigned char>(e.frame->eax-9),name,source);
                if(status!=Status::ok) return status;
            } else source=message_source_lookup("craft-requirement",name);
            if(*at<std::int32_t>(0xA2C6AA4)==-2)
                source=native_message_source::concat({message_source_lookup("hud.map","(mod) "),std::move(source)});
            bind_format(e.frame->esp+0x20,std::move(source));
        }
        return Status::ok;
    }
    if(e.phase==NativePhase::after) return Status::ok;
    if(e.id==override_copy) {
        const auto* original=ptr<char>(e.frame->edi);
        message_bind_copy(at<char>(0xA2D1C38),original,message_source_bound(original));
        return Status::ok;
    }
    if(e.id>=place_width && e.id<=marker_width_second) {
        if(!chinese_enabled) return Status::ok;
        const bool user=e.id==marker_width_first || e.id==marker_width_second;
        const auto* original=ptr<char>(e.frame->ebp-(e.id==marker_width_first ? 0x11B8 :
            e.id==marker_width_second ? 0x1154 : 0x808));
        std::vector<char> encoded;Status status;
        if(user) status=native_name_input::display(original,encoded);
        else {
            const auto source=message_source_bound(original);
            const auto key=windows_inventory::expression_key(source);
            status=resolve_display_text(TextComponent::native_message_expression,source.original.c_str(),key.c_str(),encoded);
        }
        if(status!=Status::ok) return status;
        render::Metrics measured{};status=metrics_at_outline(encoded.data(),0,measured);
        if(status!=Status::ok) return status;
        // The following SUB obtains the native maximum-length operand.
        // Its comparisons, +4 marker allowance, *8+20 and 300..720 bounds
        // remain original. No Mod width or paragraph snapshot survives.
        e.frame->ecx=e.frame->edx+static_cast<u32>((measured.logical_width+7)/8);
        return Status::ok;
    }
    if(e.id==repeat_source) {
        const auto* original=ptr<char>(e.frame->esp+0x20);
        const auto action=*at<std::int32_t>(0xA2C6AA4);
        MessageText source;
        if(action==-1 || action==-2 || action==0x7A) {
            if(*at<char>(0xA2D1C38)) {
                source=message_source_bound(at<char>(0xA2D1C38));
                if(action==-2) source=native_message_source::concat({message_source_lookup("hud.map","(mod) "),std::move(source)});
            } else source=windows_messages::values.at(address(original)).text;
        } else source=message_source_lookup(action==0xF0 ? "terrain" : "activity",original);
        message_bind_source(original,std::move(source));return Status::ok;
    }
    if(e.id==repeat_draw) {
        if(!chinese_enabled) return Status::ok;
        const auto& source=windows_messages::values.at(e.arguments[0]).text;
        std::vector<char> encoded;
        const auto key=windows_inventory::expression_key(source);
        auto status=resolve_display_text(TextComponent::native_message_expression,source.original.c_str(),key.c_str(),encoded);
        if(status!=Status::ok) return status;
        status=native_text_limit(encoded,24*8,23*8,e.arguments[2]&1u);
        if(status!=Status::ok) return status;
        return lend_text(e,encoded,e.arguments[0],Scope::text);
    }
    if(e.id>=format_first && e.id<format_first+std::size(formats)) {
        const auto kind=e.id-format_first;
        std::vector<MessageText> arguments;std::vector<std::string> syntax;
        if(kind==order_days || kind==visit_days) {
            arguments.push_back(native_message_source::scalar(native_message_source::Scalar::signed32,e.arguments[2],"%d"));
            syntax.push_back("%d");
        } else if(kind==order) {
            arguments={message_source_identity(ptr<char>(e.arguments[2])),age(ptr<char>(e.arguments[3]))};
            syntax={"%s","%s"};
        } else if(kind==net || kind==trap) {
            arguments={age(ptr<char>(e.arguments[2]))};syntax={"%s"};
        } else if(kind==place) {
            arguments={message_source_bound(ptr<char>(e.arguments[2]))};syntax={"%s"};
        } else {
            arguments={quest_title(ptr<char>(e.arguments[2]))};syntax={"%s"};
            if(kind!=quest_informant) {
                arguments.push_back(kind==quest_origin ? message_source_identity(ptr<char>(e.arguments[3])) :
                    message_source_bound(ptr<char>(e.arguments[3])));syntax.push_back("%s");
            }
        }
        bind_format(e.arguments[0],native_message_source::format(
            message_source_lookup("hud.map",ptr<char>(e.arguments[1])),std::move(arguments),std::move(syntax)));
        return Status::ok;
    }
    if(e.id>=parser_first && e.id<parser_first+std::size(parsers)) return paragraph_source(e,e.id-parser_first);
    if(e.id>=paragraph_first && e.id<paragraph_first+std::size(paragraphs)) {
        begin(e,Scope::hud_renderer);return Status::ok;
    }
    if(e.id>=panel_first && e.id<panel_first+std::size(panels))
        return hud_lend(e,TextComponent::message_value,3,Scope::hud_renderer,"hud.map");
    if(e.id>=label_first && e.id<label_first+std::size(labels))
        return hud_lend(e,TextComponent::message_value,1,Scope::hud_renderer_text,"hud.map",e.arguments[3]&1u);
    if(e.id>=marker_first && e.id<marker_first+std::size(markers)) {
        std::vector<char> encoded;auto status=native_name_input::display(ptr<char>(e.arguments[1]),encoded);
        if(status!=Status::ok) return status;
        return lend_text(e,encoded,e.arguments[1],Scope::hud_renderer_text,e.arguments[3]&1u);
    }
    handled=false;return Status::ok;
}
}
