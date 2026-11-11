// Windows 3.89.1: AD4F0's existing neutral NPC source now reaches both
// native conversation name consumers. See 20261111-chat-ui-native.md.
Status bind_conversation_text(const NativeEvent& event,u32& input) {
    const auto* original=ptr<const char>(input);
    const auto source=windows_inventory::expression(original,windows_messages::values.at(input).text);
    native_component_binding::bind_source(event,source);
    if(!chinese_enabled) return native_conversation_language::unicode_title(event,input);
    std::vector<char> encoded;
    const auto status=native_text_resource::resolve_source(source,resolve_display_text,encode_component_original,encoded);
    return status==Status::ok ? lend_text(event,encoded,input,Scope::titled_panel) : status;
}

namespace windows_conversation_text {
constexpr u32 title_format=0x18800;
constexpr u32 sidebar_first=0x18820,continue_button=0x18828,sidebar_item_copy=0x18829,
    sidebar_item_width=0x1882A,sidebar_item_index=0x1882B,sidebar_item_index_end=0x1882C;
constexpr u32 sidebar_sites[]{0x134842,0x1348A6,0x1348D4,0x134923,
    0x134956,0x1349BB,0x134A65,0x134AAD};
void append_hooks(std::vector<HookSpec>& hooks) {
    if(!windows_build::is_3891()) return;
    hooks.push_back(call(title_format,0x134307,0x10D0,3));
    for(u32 index=0;index<std::size(sidebar_sites);++index)
        hooks.push_back(call(sidebar_first+index,sidebar_sites[index],0x10E5A0,3));
    hooks.push_back(call(continue_button,0x134E89,0x114680,1));
    hooks.push_back(call(sidebar_item_copy,0x134A04,0x10D0,3));
    hooks.push_back(inline_hook(sidebar_item_width,0x134A1C,{0x2B,0xC2,0x83,0xF8,0x1C}));
    hooks.push_back(inline_hook(sidebar_item_index,0x134A23,{0x66,0xC7,0x85,0x12,0xFC,0xFF,0xFF,0x2E,0x2E}));
    auto restore=inline_hook(sidebar_item_index_end,0x134A32,{0xA1,0,0,0,0});
    const auto surface=address(at<void>(0x61BBB10));
    std::memcpy(restore.expected+1,&surface,4);hooks.push_back(restore);
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id==title_format || (event.id>=sidebar_first && event.id<=sidebar_item_index_end);
    if(!handled) return Status::ok;
    if(event.id==sidebar_item_copy) {
        if(event.phase!=NativePhase::after) return Status::ok;
        const auto source=windows_messages::values.at(event.arguments[2]).text;
        message_bind_source(ptr<const char>(event.arguments[0]),source);
        if(!chinese_enabled) return Status::ok;
        std::string text;auto status=message_project_source(source,true,text);
        if(status!=Status::ok) return status;
        std::vector<char> encoded;status=encode_component_original(text.c_str(),encoded);
        if(status==Status::ok) std::memcpy(ptr<void>(event.arguments[0]),encoded.data(),encoded.size());
        return status;
    }
    if(event.id>=sidebar_item_width) {
        if(!chinese_enabled) return Status::ok;
        if(event.id==sidebar_item_width) {
            render::Metrics measured{};
            const auto status=metrics_at_outline(ptr<const char>(event.frame->ebp-0x408),
                *at<const unsigned char>(0x134A38),measured);
            // Only extend the original strlen operand. Its own SUB/CMP/JB
            // still decides whether this native item label is abbreviated.
            event.frame->eax=event.frame->edx+(measured.logical_width+7)/8;
            return status;
        }
        if(event.id==sidebar_item_index) {
            const auto* text=ptr<const char>(event.frame->ebp-0x408);
            const auto retained=*at<const std::int32_t>(0x134A26)+0x408;
            std::size_t cut=0;
            for(std::size_t next=0;text[next];) {
                next+=static_cast<unsigned char>(text[next])<0x80?1u:2u;
                const std::string prefix(text,next);render::Metrics measured{};
                const auto status=metrics_at_outline(prefix.c_str(),*at<const unsigned char>(0x134A38),measured);
                if(status!=Status::ok) return status;
                if(measured.logical_width>retained*8) break;
                cut=next;
            }
            // Convert the native retained-character index to a complete
            // encoded-glyph byte index. The two ORIGINAL MOVs write both
            // dots and NUL; their original branch remains the only caller.
            // EAX is dead after the native length comparison until 134A32.
            event.frame->eax=event.frame->ebp;
            event.frame->ebp+=static_cast<u32>(cut-retained);
        } else if((event.frame->eflags&1u)==0) {
            // The original JB and its two MOVs preserve the CMP carry flag.
            // Only the non-JB branch used the converted native write index.
            event.frame->ebp=event.frame->eax;
        }
        return Status::ok;
    }
    if(event.id>=sidebar_first && event.id<=continue_button) {
        if(event.phase==NativePhase::after) {end(event.token);return Status::ok;}
        if(event.id==sidebar_first+6) {
            const auto& value=windows_messages::values.at(event.arguments[0]);
            native_component_binding::bind_source(event,windows_inventory::expression(
                value.source.c_str(),value.text));
            begin(event,Scope::text,event.arguments[2]);return Status::ok;
        }
        return lend_conversation_display(event,event.arguments[0],
            event.id==continue_button?Scope::plain_button:Scope::text,
            event.id==continue_button?0:event.arguments[2]);
    }
    if(event.phase!=NativePhase::after) return Status::ok;
    // The real sprintf and original stack buffer have finished unchanged.
    // Its sole operand is the immediately preceding 1342F8 -> AD4F0 result.
    message_bind_source(ptr<const char>(event.arguments[0]),native_message_source::format(
        message_source_lookup("conversation.format",ptr<const char>(event.arguments[1])),
        {windows_messages::values.at(event.arguments[2]).text},{"%s"}));
    return Status::ok;
}
}
