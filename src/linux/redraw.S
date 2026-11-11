.text
.globl urwcn_linux_redraw_main_fragment
.hidden urwcn_linux_redraw_main_fragment
.type urwcn_linux_redraw_main_fragment,@function
urwcn_linux_redraw_main_fragment:
    pushq %rbx
    # Enter 15CEEB..15CF44 with the original mid-function stack alignment:
    # RSP is aligned before that fragment's own CALL instructions.
    subq $8,%rsp
    call *%rdi
    addq $8,%rsp
    popq %rbx
    ret
.size urwcn_linux_redraw_main_fragment,.-urwcn_linux_redraw_main_fragment
.globl urwcn_linux_redraw_main_return
.hidden urwcn_linux_redraw_main_return
.type urwcn_linux_redraw_main_return,@function
urwcn_linux_redraw_main_return:
    ret
.size urwcn_linux_redraw_main_return,.-urwcn_linux_redraw_main_return
.section .note.GNU-stack,"",@progbits

.text
.globl urwcn_linux_redraw_world_fragment
.hidden urwcn_linux_redraw_world_fragment
.type urwcn_linux_redraw_world_fragment,@function
urwcn_linux_redraw_world_fragment:
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
.size urwcn_linux_redraw_world_fragment,.-urwcn_linux_redraw_world_fragment
.globl urwcn_linux_redraw_world_return
.hidden urwcn_linux_redraw_world_return
.type urwcn_linux_redraw_world_return,@function
urwcn_linux_redraw_world_return:
    ret
.size urwcn_linux_redraw_world_return,.-urwcn_linux_redraw_world_return

.globl urwcn_linux_redraw_scenario_fragment
.hidden urwcn_linux_redraw_scenario_fragment
.type urwcn_linux_redraw_scenario_fragment,@function
urwcn_linux_redraw_scenario_fragment:
    # 1CEFC..1CF7E expects RSP aligned before its native CALLs. Its temporary
    # seventh LIST_Reset argument is balanced by the original two POPs.
    pushq %rbx
    subq $8,%rsp
    call *%rdi
    addq $8,%rsp
    popq %rbx
    ret
.size urwcn_linux_redraw_scenario_fragment,.-urwcn_linux_redraw_scenario_fragment
.globl urwcn_linux_redraw_scenario_return
.hidden urwcn_linux_redraw_scenario_return
.type urwcn_linux_redraw_scenario_return,@function
urwcn_linux_redraw_scenario_return:
    ret
.size urwcn_linux_redraw_scenario_return,.-urwcn_linux_redraw_scenario_return

.globl urwcn_linux_redraw_game_course_fragment
.hidden urwcn_linux_redraw_game_course_fragment
.type urwcn_linux_redraw_game_course_fragment,@function
urwcn_linux_redraw_game_course_fragment:
    # 1D5E3..1D86D uses RBP for winH and balances each native seventh
    # argument itself. Supply native call alignment and preserve RBP.
    pushq %rbp
    subq $8,%rsp
    call *%rdi
    addq $8,%rsp
    popq %rbp
    ret
.size urwcn_linux_redraw_game_course_fragment,.-urwcn_linux_redraw_game_course_fragment
.globl urwcn_linux_redraw_game_course_return
.hidden urwcn_linux_redraw_game_course_return
.type urwcn_linux_redraw_game_course_return,@function
urwcn_linux_redraw_game_course_return:
    ret
.size urwcn_linux_redraw_game_course_return,.-urwcn_linux_redraw_game_course_return
