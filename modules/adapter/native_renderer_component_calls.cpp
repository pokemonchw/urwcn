#include "native_renderer_component_calls.h"

namespace uwcn::adapter::native_renderer_component_calls {
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_renderer_paragraph(const ParagraphCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t"
        "movl 8(%esp),%ebx\n\t"
        "pushl 28(%ebx)\n\t"
        "pushl 24(%ebx)\n\t"
        "pushl 20(%ebx)\n\t"
        "pushl 16(%ebx)\n\t"
        "pushl 12(%ebx)\n\t"
        "movl 4(%ebx),%ecx\n\t"
        "movl 8(%ebx),%edx\n\t"
        "call *(%ebx)\n\t"
        "addl $20,%esp\n\t"
        "popl %ebx\n\t"
        "ret\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_renderer_panel(const PanelCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t"
        "movl 8(%esp),%ebx\n\t"
        "pushl 32(%ebx)\n\t"
        "pushl 28(%ebx)\n\t"
        "pushl 24(%ebx)\n\t"
        "pushl 20(%ebx)\n\t"
        "pushl 16(%ebx)\n\t"
        "pushl 12(%ebx)\n\t"
        "movl 4(%ebx),%ecx\n\t"
        "movl 8(%ebx),%edx\n\t"
        "call *(%ebx)\n\t"
        "addl $24,%esp\n\t"
        "popl %ebx\n\t"
        "ret\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_renderer_text_block(const TextBlockCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t"
        "movl 8(%esp),%ebx\n\t"
        "pushl 24(%ebx)\n\t"
        "pushl 20(%ebx)\n\t"
        "pushl 16(%ebx)\n\t"
        "pushl 12(%ebx)\n\t"
        "movl 4(%ebx),%ecx\n\t"
        "movl 8(%ebx),%edx\n\t"
        "call *(%ebx)\n\t"
        "addl $16,%esp\n\t"
        "popl %ebx\n\t"
        "ret\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_renderer_heading(const HeadingCall*) {
    __asm__ __volatile__(
        "movl 4(%esp),%eax\n\t"
        "movl 4(%eax),%ecx\n\t"
        "movl 8(%eax),%edx\n\t"
        "call *(%eax)\n\t"
        "ret\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_renderer_marked_button(const MarkedButtonCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t"
        "movl 8(%esp),%ebx\n\t"
        "pushl 20(%ebx)\n\t"
        "pushl 16(%ebx)\n\t"
        "pushl 12(%ebx)\n\t"
        "movl 4(%ebx),%ecx\n\t"
        "movl 8(%ebx),%edx\n\t"
        "call *(%ebx)\n\t"
        "addl $12,%esp\n\t"
        "popl %ebx\n\t"
        "ret\n\t");
}
}
