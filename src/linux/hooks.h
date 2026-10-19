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
enum class Phase { before,after };
// Owned by the resident invocation, including while native code waits. data
// contains semantic scalars only; text is one borrowed native call argument,
// allocated through HostApi and released by the resident after that call.
struct CallState {
    std::uint32_t target{};
    bool skip{};
    std::uint64_t data[8]{};
    char* text{};
};
using CallCallback=void (*)(Frame&,Phase,CallState&);
struct Hooks {
    std::uintptr_t base;
    void (*replace)(std::uint32_t,std::uint32_t,void*);
    void (*instruction)(std::uint32_t,std::uint32_t,InlineCallback);
    void (*around)(std::uint32_t,CallCallback,bool tail);
    void (*finish)();
    void (*enter)();
    void (*leave)();
};
struct BusinessCall {
    const Hooks& hooks;
    explicit BusinessCall(const Hooks& value):hooks(value) { hooks.enter(); }
    ~BusinessCall() { hooks.leave(); }
};
void prepare_hooks(std::uintptr_t);
void begin_hooks();
void retire_hooks();
void enter_business();
void leave_business();
void service_control();
}
extern "C" const uwcn::linux_host::Hooks* uwcn_linux_hooks_v2();
