#include "native_paragraph.h"

namespace uwcn::adapter {
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_draw_native_paragraph(const NativeParagraphCall*) {
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
}
