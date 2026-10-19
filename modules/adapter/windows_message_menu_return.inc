// 5008F0 returns an upper-menu selection through native 6F2C30, which
// 455060 subsequently displays. These are the three actual item-option
// callers, separate from 5002B0's immediate echo. Row identity and clipping
// use the same native 659F988 records already owned by menu_echo.
namespace windows_message_menu_return {
constexpr u32 row_first=0xee00,remove_format=0xee07,clip_first=0xee20;
enum Hook:u32 { echo_format=0xee30,echo_clear,echo_separator,
    echo_strip_marker,echo_copy,item_copy };
const u32 row_calls[]={0x4fd04,0x4fdb2,0x4fe44,0x4fef2,0x50084,0x50114,0x502a6};
const u32 clip_sites[]={0x4fd1e,0x4fdce,0x4fe5e,0x4ff0e,0x5009e,0x5012e,0x502bf};
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::native_call;using native_name_input::instruction;
    for(u32 i=0;i<std::size(row_calls);++i)hooks.push_back(native_call(row_first+i,row_calls[i],0x10d0,4));
    hooks.push_back(native_call(remove_format,0x50245,0x10d0,3));
    for(u32 i=0;i<std::size(clip_sites);++i) {
        auto hook=instruction(clip_first+i,clip_sites[i],{0x66,0xc7,0x87,0,0,0,0,0x2e,0x2e});
        const auto dots=address(at<char>(0x619f9a8));std::memcpy(hook.expected+3,&dots,4);hooks.push_back(hook);
    }
    hooks.push_back(native_call(echo_format,0x100d86,0x10d0,4));
    hooks.push_back(native_call(echo_clear,0x100da9,0x18ae60,3));
    hooks.push_back(instruction(echo_separator,0x100ddb,{0xc6,0x44,0x05,0x8c,0x00}));
    hooks.push_back(instruction(echo_strip_marker,0x100e06,{0x33,0xd2,0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00}));
    hooks.push_back(instruction(echo_copy,0x100de2,{0x8a,0x44,0x0d,0x8c,0x8d,0x49,0x01}));
    hooks.push_back(instruction(item_copy,0x5020e,{0x8d,0x95,0x8c,0xfb,0xff,0xff}));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    const bool row_event=event.id>=row_first && event.id<row_first+std::size(row_calls);
    const bool clip_event=event.id>=clip_first && event.id<clip_first+std::size(clip_sites);
    handled=row_event || clip_event || event.id==remove_format || (event.id>=echo_format && event.id<=item_copy);
    if(!handled)return Status::ok;
    if(clip_event) {
        windows_message_menu_echo::rows.at(address(at<char>(0x619f988))+event.frame->edi).clipped=true;
        return Status::ok;
    }
    if(event.id==item_copy) {
        const auto* source=ptr<char>(event.frame->eax);
        message_bind_copy(ptr<char>(event.frame->ebp-0x474),source,message_source_bound(source));return Status::ok;
    }
    if(row_event || event.id==remove_format || event.id==echo_format) {
        // The CRT preserves EBX and its argument words. Observe the real
        // completed format, without retaining an additional pending scope.
        if(event.phase==NativePhase::before)return Status::ok;
        MessageText source;
        if(row_event) {
            const auto* caption=ptr<char>(event.arguments[3]);const auto index=event.id-row_first;
            if(index==1 || index==3)source=message_source_lookup("activity",caption);
            else if(index==6)source=message_source_bound(caption);
            else source=message_source_lookup("menu.return.label",caption);
            windows_message_menu_echo::rows[event.arguments[0]]={std::move(source),ptr<char>(event.arguments[0]),false,row_calls[index]};
            return Status::ok;
        }
        if(event.id==remove_format) {
            source=windows_message_menu_echo::menu_format(ptr<char>(event.arguments[1]),
                {message_source_bound(ptr<char>(event.arguments[2]))},{"%s"});
        } else {
            const auto& row=windows_message_menu_echo::rows.at(address(at<char>(0x619f988))+event.frame->ebx);
            auto selected=row.source;
            if(row.clipped) {
                const std::string caption=ptr<char>(event.arguments[3]);
                const auto prefix=windows_message_menu_echo::native_visible_prefix(row.native.c_str()+2,caption.size()-2);
                const auto status=windows_message_menu_echo::visible_prefix(row.source,prefix.size(),selected);
                if(status!=Status::ok)return status;
                selected=native_message_source::concat({std::move(selected),native_message_source::original("..")});
            }
            source=windows_message_menu_echo::menu_format(ptr<char>(event.arguments[1]),
                {message_source_lookup("menu.return.title",ptr<char>(event.arguments[2])),std::move(selected)},{"%s","%s"});
        }
        message_bind_source(ptr<char>(event.arguments[0]),std::move(source));return Status::ok;
    }
    const auto* local=ptr<char>(event.frame->ebp-0x74);
    if(event.id==echo_clear) {
        if(event.phase==NativePhase::after)message_bind_source(ptr<char>(event.arguments[0]),native_message_source::original(""));
    } else if(event.id==echo_separator) {
        auto source=native_message_source::before_separator(message_source_bound(local),'|');
        const std::string selected(local,event.frame->eax);
        message_bind_copy(local,selected.c_str(),std::move(source));
    } else if(event.id==echo_strip_marker) {
        message_bind_copy(at<char>(0x2f2c30),local+1,native_message_source::without_initial_marker(message_source_bound(local)));
    } else if(event.id==echo_copy && event.frame->ecx==0) {
        // First iteration of the actual native copy loop.
        message_bind_copy(at<char>(0x2f2c30),local,message_source_bound(local));
    }
    return Status::ok;
}
}
