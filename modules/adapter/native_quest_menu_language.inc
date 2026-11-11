// Complete quest-journal constructors, borrowed from their real live frames.
// The game recreates and owns the entire texture, images, controls and Menu;
// this transaction retains no page fields, layout, pixels or native frame.
namespace native_quest_menu_language {
using View=native_language_redraw::View;
enum class Construction { none,detail,list,empty };
Construction constructing{};
enum Hook:u32 {
    detail_finished=0x51F0,list_finished,list_index,empty_wait,empty_finished,
    title_panel,title_text,empty_text_first
};
struct Detail {u32 target,frame,origin,recreate,set_target;};
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_quest_detail(const Detail*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%eax\n\tmovl 4(%eax),%ebp\n\t"
        "movl 8(%eax),%edi\n\tmovl 12(%eax),%ecx\n\t"
        "movl 16(%eax),%ebx\n\tcall *(%eax)\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t");
}
u32 component_return() {
    return static_cast<u32>(reinterpret_cast<std::uintptr_t>(
        native_component_calls::urwcn_component_fragment_return)-host->image_base);
}
void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(inline_hook(detail_finished,0x1586D5,{0x8B,0xC8,0x83,0xF9,0xD6}));
    hooks.push_back(inline_hook(list_finished,0x1590A8,{0x8B,0xF0,0x83,0xFE,0xD6}));
    hooks.push_back(call(list_index,0x158DA3,0x1587A0,0));
    hooks.push_back(call(empty_wait,0x159330,0xD3C80,0));
    auto finished=inline_hook(empty_finished,0x159335,{0xC7,0x05,0,0,0,0,0,0,0,0});
    const auto flip=address(at<void>(0x61BBA5C));
    std::memcpy(finished.expected+2,&flip,4);hooks.push_back(finished);
    if(windows_build::is_3891()) {
        hooks.push_back(call(title_panel,0x1135AB,0x1166C0,6));
        hooks.push_back(call(title_text,0x1135C1,0x10E260,4));
        hooks.push_back(call(empty_text_first,0x15928B,0x10E260,4));
        hooks.push_back(call(empty_text_first+1,0x1592DA,0x10E260,4));
    }
}
Status heading(const NativeEvent& event) {
    std::vector<char> encoded;
    const auto status=translate(TextComponent::message_value,at<char>(0x1CC6F8),"quest.journal",encoded);
    if(status!=Status::ok) return status;
    // 113550 supplies this exact panel's renderer, x, y and width. Native
    // 115AD0 mode 5 constructs the same 1166C0 band, then measures and centers
    // its complete title. No English title position is copied into the Mod.
    const native_renderer_component_calls::SectionCall call{
        address(at<void>(0x115AD0)),event.frame->ecx,
        static_cast<std::int32_t>(event.frame->edx),
        static_cast<std::int32_t>(event.arguments[0]),
        static_cast<std::int32_t>(event.arguments[1]),encoded.data(),5};
    begin(event,Scope::hud_renderer_text,1);
    native_renderer_component_calls::urwcn_renderer_section(&call);
    end(event.token);
    return Status::ok;
}
Status construct(u32 page,Construction kind) {
    const auto flip=*at<u32>(0x61BBA5C);
    *at<u32>(0x61BBA5C)=1;
    // AE3F0 is the original NPC description wrapper: it temporarily copies
    // its accepted NPC record into slot 499, then clears that exact record.
    // Preserve this complete English formatting scratch across reconstruction.
    std::vector<std::uint8_t> npc(0x568);
    std::memcpy(npc.data(),at<void>(0x5DF9DB8),npc.size());
    constructing=kind;
    if(kind==Construction::detail) {
        // The only interactive 157D10 caller is 1591A5 (flags=8).
        // Its by-value F1E0 quest record and accepted origin remain in this
        // live frame. The earlier flags=6 caller returns before any wait.
        const Detail detail{address(at<void>(0x157D75)),page,
            *ptr<const u32>(page-0x1EFD4),*ptr<const u32>(page-0x1EFE0),
            *at<u32>(0x18C288)};
        urwcn_quest_detail(&detail);
    } else {
        // 158D3F is the complete original texture reconstruction loop after
        // the native FIRST save and initial page/selection initialization.
        const native_full_language::BorrowedFrame list{address(at<void>(0x158D3F)),page};
        native_full_language::urwcn_full_language_frame(&list);
    }
    constructing=Construction::none;
    std::memcpy(at<void>(0x5DF9DB8),npc.data(),npc.size());
    *at<u32>(0x61BBA5C)=flip;
    native_language_redraw::completed(View::hud);
    return Status::ok;
}
Status menu(const NativeEvent& event,bool& rebuilt,u32&) {
    rebuilt=false;
    if(!native_language_redraw::pending(View::hud)) return Status::ok;
    const auto caller=*ptr<const u32>(event.frame->ebp+4)-static_cast<u32>(host->image_base);
    if(caller!=0x1586D5 && caller!=0x1590A8) return Status::ok;
    const auto page=*ptr<const u32>(event.frame->ebp);
    const auto status=construct(page,caller==0x1586D5 ? Construction::detail : Construction::list);
    rebuilt=status==Status::ok;
    return status;
}
Status wait(const NativeEvent& event) {
    if(event.phase!=NativePhase::before || !native_language_redraw::pending(View::hud))
        return Status::ok;
    // 158DB4/158DBA select this exact native output owner and context before
    // entering the empty branch. Other D3C80 pages own different contexts.
    if(*at<u32>(0xA1C2010)!=0x10 ||
       *at<u32>(0xA1C1CBC)!=*at<u32>(0xA220EF4)) return Status::ok;
    // The hooked 159330 CALL substitutes the resident After bridge for the
    // D3C80 return address. Its saved EBP still names the real 158CE0 frame;
    // that constructor's sole, unhooked caller is 17DED9 -> 17DEDE. At this
    // D3D05 tick, 158CE0 calls D3C80 only from its empty-list branch.
    const auto page=*ptr<const u32>(event.frame->ebp);
    if(*ptr<const u32>(page+4)!=host->image_base+0x17DEDE) return Status::ok;
    return construct(page,Construction::empty);
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=false;
    if(event.id>=title_panel && event.id<=empty_text_first+1) {
        handled=true;
        if(event.phase==NativePhase::after) {end(event.token);return Status::ok;}
        if(!chinese_enabled) return Status::ok;
        if(event.id==title_panel) {
            const auto status=heading(event);
            if(status==Status::ok) result.skip_original=1;
            return status;
        }
        if(event.id==title_text) {result.skip_original=1;return Status::ok;}
        std::vector<char> encoded;
        const auto status=translate(TextComponent::message_value,
            ptr<char>(event.arguments[1]),"quest.journal",encoded);
        if(status!=Status::ok) return status;
        return lend_text(event,encoded,event.arguments[1],Scope::hud_renderer_text,event.arguments[3]&1u);
    }
    if(event.phase==NativePhase::after) return Status::ok;
    switch(event.id) {
    case native_full_language::input_entry:
        if(constructing!=Construction::none) result.resume_rva=0xD19B3;
        break;
    case detail_finished:
        if(constructing==Construction::detail) result.resume_rva=component_return();
        break;
    case list_finished:
        if(constructing==Construction::list) result.resume_rva=component_return();
        break;
    case list_index:
        if(constructing==Construction::list || constructing==Construction::empty) {
            // The real page already owns the accepted .QST index/count.
            // Re-enumerating 1587A0 would replace and re-sort those inputs.
            event.frame->eax=*ptr<const u32>(event.frame->ebp-0x42C);
            result.skip_original=1;handled=true;
        }
        return Status::ok;
    case empty_wait:
        if(constructing==Construction::empty) {result.skip_original=1;handled=true;}
        return Status::ok;
    case empty_finished:
        if(constructing==Construction::empty) result.resume_rva=component_return();
        break;
    default:break;
    }
    handled=result.resume_rva!=0;
    return Status::ok;
}
}
