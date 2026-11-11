// The encyclopedia's two native no-information waits. Construction borrows
// original accepted inputs synchronously; the only reload state is the real
// link/keyword branch, never a native frame, page, layout or pixel record.
namespace native_encyclopedia_wait_language {
using View=native_language_redraw::View;
enum class Input:u32 { none,link,keyword };
struct State { Input input; };
State state{};
std::vector<std::uint8_t> save() {
    const auto* bytes=reinterpret_cast<const std::uint8_t*>(&state);
    return {bytes,bytes+sizeof(state)};
}
void restore(const void* payload,u32) {std::memcpy(&state,payload,sizeof(state));}

enum class Construction { none,initial,parent,notice,keyword_text };
Construction constructing{};
const char* initial_title{};
enum Hook:u32 {
    initial_body=0x5230,initial_wait,initial_finished,notice_wait,
    accepted_input,accepted_keyword,parent_published,keyword_text_finished
};

// 3E4F0..3E582 constructs the original keyword field and returns the actual
// MapRGB result in EAX. Its original body uses EBX's MapRGB import, with no
// enclosing local access; Full's keyword_prompt_end supplies the balanced RET.
extern "C" __attribute__((naked)) u32 URWCN_CALL urwcn_encyclopedia_wait_prompt(
        const native_full_language::KeywordFragment*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%eax\n\tmovl 4(%eax),%ebx\n\tcall *(%eax)\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t");
}
struct KeywordText {u32 target,text,color,x,y;};
// Enter the original 10F6AC call instruction with its complete real arguments.
// The inner CALL below installs our continuation beneath those three native
// arguments. The 10F6B1 gate then discards exactly those arguments and RETurns
// here. The original text hook still owns its Unicode/text scope lifecycle.
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_encyclopedia_wait_text(const KeywordText*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%ebx\n\tcall 1f\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t"
        "1:\n\tpushl $0\n\tpushl 8(%ebx)\n\tpushl 4(%ebx)\n\t"
        "movl 12(%ebx),%ecx\n\tmovl 16(%ebx),%edx\n\tjmp *(%ebx)\n\t");
}
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_encyclopedia_wait_text_return() {
    __asm__ __volatile__("addl $12,%esp\n\tret\n\t");
}

void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(inline_hook(initial_body,0x3E783,
        {0x33,0xC0,0x66,0x66,0x66,0x0F,0x1F,0x84,0,0,0,0,0}));
    hooks.push_back(call(initial_wait,0x3E8CC,0xD3C80,0));
    auto finished=inline_hook(initial_finished,0x3E8D1,{0xB9,0,0,0,0});
    // 3E6B3 is the same original resource MOV and remains unhooked. Read
    // its operand rather than this Hook's already-patched bytes on reload.
    const auto music_name=*at<u32>(0x3E6B4);
    std::memcpy(finished.expected+1,&music_name,4);hooks.push_back(finished);
    hooks.push_back(call(notice_wait,0x3DD06,0xD3C80,0));
    // Both original branches are explicitly continued, so the relative JNE
    // is never copied into the resident replay trampoline.
    hooks.push_back(inline_hook(accepted_input,0x3E4E8,{0x3C,0x20,0x0F,0x85,0xB7,0,0,0}));
    hooks.push_back(inline_hook(accepted_keyword,0x3E58E,{0x8B,0xC8,0x8D,0x54,0x24,0x10}));
    auto published=inline_hook(parent_published,0x3E47E,{0xC7,0x05,0,0,0,0,0,0,0,0});
    const auto flip=address(at<void>(0x61BBA5C));
    std::memcpy(published.expected+2,&flip,4);hooks.push_back(published);
    auto text_finished=inline_hook(keyword_text_finished,0x10F6B1,{0x8B,0x35,0,0,0,0});
    const auto cursor_x=address(at<void>(0xA1C1CB4));
    std::memcpy(text_finished.expected+2,&cursor_x,4);hooks.push_back(text_finished);
}

Status keyword(const char* query) {
    native_full_language::constructing=native_full_language::Construction::encyclopedia_keyword;
    const native_full_language::KeywordFragment prompt{
        address(at<void>(0x3E4F0)),*at<u32>(0x18C1F8)};
    const auto color=urwcn_encyclopedia_wait_prompt(&prompt);
    native_full_language::constructing=native_full_language::Construction::none;
    // These positions were just produced by that original field constructor.
    // Only its accepted completed text is redrawn; the edit loop and caret
    // were already completed before 3E64E entered this notice.
    const KeywordText text{address(at<void>(0x10F6AC)),address(query),color,
        *at<u32>(0xA1C1CB4),*at<u32>(0x61BBB3C)};
    constructing=Construction::keyword_text;
    urwcn_encyclopedia_wait_text(&text);
    constructing=Construction::none;
    return Status::ok;
}

Status initial(const char* title) {
    initial_title=title;
    constructing=Construction::initial;
    reinterpret_cast<void (__fastcall *)(const char*)>(host->image_base+0x3E680)(title);
    constructing=Construction::none;initial_title=nullptr;
    return Status::ok;
}
Status notice(const char* query) {
    const auto accepted=state.input;
    auto selection=*at<u32>(0x5F54AB0);
    constructing=Construction::parent;
    const auto status=native_full_language::encyclopedia(selection);
    constructing=Construction::none;
    if(status!=Status::ok) return status;
    *at<u32>(0x5F54AB0)=selection;
    reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0xD0650)(selection,0);
    if(accepted==Input::keyword) {
        const auto text_status=keyword(query);
        if(text_status!=Status::ok) return text_status;
    }
    constructing=Construction::notice;
    reinterpret_cast<void (__fastcall *)(const char*)>(host->image_base+0x3DCA0)(query);
    constructing=Construction::none;
    return Status::ok;
}

Status wait(const NativeEvent& event) {
    if(event.phase!=NativePhase::before || !native_language_redraw::pending(View::encyclopedia))
        return Status::ok;
    const auto caller=*ptr<const u32>(event.frame->ebp+4)-static_cast<u32>(host->image_base);
    if(caller!=0x3E8D1 && caller!=0x3DD0B) return Status::ok;
    const auto flip=*at<u32>(0x61BBA5C);
    *at<u32>(0x61BBA5C)=1;
    Status status{};
    if(caller==0x3E8D1) {
        const auto page=*ptr<const u32>(event.frame->ebp);
        const auto* title=ptr<const char>((page&~7u)-0x70);
        status=initial(title);
    } else {
        // 3DCA0 has no EBP prologue. Its first PUSH ECX preserves the real
        // failed query directly above the suspended D3C80 return address.
        const auto* query=ptr<const char>(*ptr<const u32>(event.frame->ebp+8));
        status=notice(query);
    }
    *at<u32>(0x61BBA5C)=flip;
    if(status!=Status::ok) return status;
    native_language_redraw::completed(View::encyclopedia);
    reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0x10B720)();
    return Status::ok;
}

Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=false;
    if(event.phase==NativePhase::after) return Status::ok;
    switch(event.id) {
    case native_full_language::encyclopedia_entry:
        if(constructing==Construction::initial) {
            event.frame->edi=event.frame->ecx;event.frame->eax=0;result.resume_rva=0x3E6D1;
        }
        break;
    case initial_body:
        if(constructing==Construction::initial) {
            std::memcpy(ptr<void>(event.frame->esp+0x10),initial_title,std::strlen(initial_title)+1);
            result.resume_rva=0x3E867;
        }
        break;
    case initial_wait:
        if(constructing==Construction::initial) {result.skip_original=1;handled=true;}
        return Status::ok;
    case initial_finished:
        if(constructing==Construction::initial) result.resume_rva=0x3E942;
        break;
    case notice_wait:
        if(constructing==Construction::notice) {result.skip_original=1;handled=true;}
        return Status::ok;
    case accepted_input:
        state.input=static_cast<unsigned char>(event.frame->eax)==0x20 ? Input::keyword : Input::link;
        result.resume_rva=state.input==Input::keyword ? 0x3E4F0 : 0x3E5A7;
        break;
    case accepted_keyword:
        state.input=Input::keyword;
        break;
    case parent_published:
        if(constructing==Construction::parent) result.resume_rva=0x3E4CA;
        break;
    case keyword_text_finished:
        if(constructing==Construction::keyword_text)
            result.resume_rva=static_cast<u32>(reinterpret_cast<std::uintptr_t>(
                urwcn_encyclopedia_wait_text_return)-host->image_base);
        break;
    default:break;
    }
    handled=result.resume_rva!=0;
    return Status::ok;
}
}
