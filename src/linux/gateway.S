.text
.globl uwcn_linux_gateway
.hidden uwcn_linux_gateway
.type uwcn_linux_gateway,@function
uwcn_linux_gateway:
    pushfq
    pushq %rax
    pushq %rcx
    pushq %rdx
    pushq %rbx
    pushq %rbp
    pushq %rsi
    pushq %rdi
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
    movq %rsp,%r12
    movq %rsp,%rdi
    andq $-16,%rsp
    subq $512,%rsp
    fxsave64 (%rsp)
    cld
    call uwcn_linux_dispatch
    fxrstor64 (%rsp)
    movq %r12,%rsp
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rdi
    popq %rsi
    popq %rbp
    popq %rbx
    popq %rdx
    popq %rcx
    popq %rax
    popfq
    leaq 8(%rsp),%rsp
    ret
.size uwcn_linux_gateway,.-uwcn_linux_gateway
.section .note.GNU-stack,"",@progbits
