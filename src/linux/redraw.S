.text
.globl uwcn_linux_redraw_main_fragment
.hidden uwcn_linux_redraw_main_fragment
.type uwcn_linux_redraw_main_fragment,@function
uwcn_linux_redraw_main_fragment:
    pushq %rbx
    # Enter 15CEEB..15CF44 with the original mid-function stack alignment:
    # RSP is aligned before that fragment's own CALL instructions.
    subq $8,%rsp
    call *%rdi
    addq $8,%rsp
    popq %rbx
    ret
.size uwcn_linux_redraw_main_fragment,.-uwcn_linux_redraw_main_fragment
.globl uwcn_linux_redraw_main_return
.hidden uwcn_linux_redraw_main_return
.type uwcn_linux_redraw_main_return,@function
uwcn_linux_redraw_main_return:
    ret
.size uwcn_linux_redraw_main_return,.-uwcn_linux_redraw_main_return
.section .note.GNU-stack,"",@progbits

.text
.globl uwcn_linux_redraw_world_fragment
.hidden uwcn_linux_redraw_world_fragment
.type uwcn_linux_redraw_world_fragment,@function
uwcn_linux_redraw_world_fragment:
    pushq %r14
    pushq %r15
    # Both native fragments expect RSP aligned before their own CALLs.
    # The indirect CALL below supplies their eventual fragment return slot.
    movl %esi,%r15d
    xorl %r14d,%r14d
    call *%rdi
    popq %r15
    popq %r14
    ret
.size uwcn_linux_redraw_world_fragment,.-uwcn_linux_redraw_world_fragment
.globl uwcn_linux_redraw_world_return
.hidden uwcn_linux_redraw_world_return
.type uwcn_linux_redraw_world_return,@function
uwcn_linux_redraw_world_return:
    ret
.size uwcn_linux_redraw_world_return,.-uwcn_linux_redraw_world_return
