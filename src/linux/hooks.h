#pragma once
#include <cstddef>
#include <cstdint>

namespace uwcn::linux_host {
// Saved at an inspected, non-leaf native instruction boundary. original_rsp
// is immediately after this structure. Native stack arguments stay in place.
struct Frame {
    std::uint64_t r15,r14,r13,r12,r11,r10,r9,r8,rdi,rsi,rbp,rbx,rdx,rcx,rax,flags,id,resume;
    std::uintptr_t stack() const { return reinterpret_cast<std::uintptr_t>(this)+sizeof(Frame); }
};
using InlineCallback=void (*)(Frame&);
struct Hooks {
    std::uintptr_t base;
    void (*call)(std::uint32_t,void*);
    void (*replace)(std::uint32_t,std::uint32_t,void*);
    void (*instruction)(std::uint32_t,std::uint32_t,InlineCallback);
    void (*finish)();
};
void prepare_hooks(std::uintptr_t);
}
extern "C" const uwcn::linux_host::Hooks* uwcn_linux_hooks();
