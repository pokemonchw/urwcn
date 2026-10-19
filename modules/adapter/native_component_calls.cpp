#include "native_component_calls.h"

namespace uwcn::adapter::native_component_calls {
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_component_panel(const PanelCall*) {
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
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_component_legacy_panel(const LegacyPanelCall*) {
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
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_component_button(const ButtonCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t"
        "movl 8(%esp),%ebx\n\t"
        "pushl 12(%ebx)\n\t"
        "movl 4(%ebx),%ecx\n\t"
        "movl 8(%ebx),%edx\n\t"
        "call *(%ebx)\n\t"
        "addl $4,%esp\n\t"
        "popl %ebx\n\t"
        "ret\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_component_centered_text(const CenteredTextCall*) {
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
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_component_text_block(const TextBlockCall*) {
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
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_component_statistic_label(const StatisticLabelCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t"
        "movl 8(%esp),%ebx\n\t"
        "pushl 12(%ebx)\n\t"
        "pushl 8(%ebx)\n\t"
        "movl 4(%ebx),%edx\n\t"
        "call *(%ebx)\n\t"
        "addl $8,%esp\n\t"
        "popl %ebx\n\t"
        "ret\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_component_action_button(const ActionButtonCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t"
        "movl 8(%esp),%ebx\n\t"
        "pushl 16(%ebx)\n\t"
        "pushl 12(%ebx)\n\t"
        "movl 4(%ebx),%ecx\n\t"
        "movl 8(%ebx),%edx\n\t"
        "call *(%ebx)\n\t"
        "addl $8,%esp\n\t"
        "popl %ebx\n\t"
        "ret\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_component_native_heading(const NativeHeadingCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t"
        "movl 8(%esp),%ebx\n\t"
        "movl 4(%ebx),%ecx\n\t"
        "call *(%ebx)\n\t"
        "popl %ebx\n\t"
        "ret\n\t");
}
}
