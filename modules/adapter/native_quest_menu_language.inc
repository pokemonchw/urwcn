// Complete quest-journal constructors, borrowed from their real live frames.
// The game recreates and owns the entire texture, images, controls and Menu;
// this transaction retains no page fields, layout, pixels or native frame.
namespace native_quest_menu_language {
using View=native_language_redraw::View;
enum class Construction { none,detail,list,empty };
Construction constructing{};
enum Hook:u32 { detail_finished=0x51F0,list_finished,list_index,empty_wait,empty_finished };
struct Detail {u32 target,frame,origin,recreate,set_target;};
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_quest_detail(const Detail*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%eax\n\tmovl 4(%eax),%ebp\n\t"
        "movl 8(%eax),%edi\n\tmovl 12(%eax),%ecx\n\t"
        "movl 16(%eax),%ebx\n\tcall *(%eax)\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t");
}
u32 component_return() {
    return static_cast<u32>(reinterpret_cast<std::uintptr_t>(
        native_component_calls::uwcn_component_fragment_return)-host->image_base);
}
void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(inline_hook(detail_finished,0x1586D5,{0x8B,0xC8,0x83,0xF9,0xD6}));
    hooks.push_back(inline_hook(list_finished,0x1590A8,{0x8B,0xF0,0x83,0xFE,0xD6}));
    hooks.push_back(call(list_index,0x158DA3,0x1587A0,0));
    hooks.push_back(call(empty_wait,0x159330,0xD3C80,0));
    auto finished=inline_hook(empty_finished,0x159335,{0xC7,0x05,0,0,0,0,0,0,0,0});
    const auto flip=address(at<void>(0x61BBA5C));
    std::memcpy(finished.expected+2,&flip,4);hooks.push_back(finished);
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
        uwcn_quest_detail(&detail);
    } else {
        // 158D3F is the complete original texture reconstruction loop after
        // the native FIRST save and initial page/selection initialization.
        const native_full_language::BorrowedFrame list{address(at<void>(0x158D3F)),page};
        native_full_language::uwcn_full_language_frame(&list);
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
    if(event.phase!=NativePhase::before || !native_language_redraw::pending(View::hud) ||
       *ptr<const u32>(event.frame->ebp+4)!=host->image_base+0x159335) return Status::ok;
    return construct(*ptr<const u32>(event.frame->ebp),Construction::empty);
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=false;
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
