#include "hooks.h"
#include <sys/mman.h>
#include <unistd.h>
#include <array>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <vector>

extern "C" void uwcn_linux_gateway();
namespace uwcn::linux_host {
namespace {
constexpr std::size_t arena_bytes=65536;
unsigned char* arena;
std::size_t used;
Hooks api;
std::vector<InlineCallback> callbacks;
void writable(void* pointer,std::size_t bytes,int protection) {
    const auto page=static_cast<std::uintptr_t>(sysconf(_SC_PAGESIZE));
    const auto begin=reinterpret_cast<std::uintptr_t>(pointer)&~(page-1);
    const auto end=(reinterpret_cast<std::uintptr_t>(pointer)+bytes+page-1)&~(page-1);
    if(mprotect(reinterpret_cast<void*>(begin),end-begin,protection)!=0)
        throw std::runtime_error("mprotect: "+std::string(std::strerror(errno)));
}
unsigned char* relay(void* target) {
    auto* code=arena+used;
    used+=16;
    code[0]=0xff; code[1]=0x25;
    std::memset(code+2,0,4);
    std::memcpy(code+6,&target,8);
    return code;
}
void branch(std::uint32_t site,std::uint32_t bytes,unsigned char opcode,void* target) {
    auto* code=reinterpret_cast<unsigned char*>(api.base+site);
    auto* bridge=relay(target);
    const auto displacement=static_cast<std::int32_t>(bridge-(code+5));
    writable(code,bytes,PROT_READ|PROT_WRITE|PROT_EXEC);
    code[0]=opcode;
    std::memcpy(code+1,&displacement,4);
    std::memset(code+5,0x90,bytes-5);
    writable(code,bytes,PROT_READ|PROT_EXEC);
}
void replace(std::uint32_t site,std::uint32_t bytes,void* target) { branch(site,bytes,0xe9,target); }
void call(std::uint32_t site,void* target) { branch(site,5,0xe8,target); }
void instruction(std::uint32_t site,std::uint32_t bytes,InlineCallback callback) {
    const auto index=static_cast<std::uint32_t>(callbacks.size());
    callbacks.push_back(callback);
    auto* code=arena+used;
    used+=32;
    code[0]=0x68;
    std::memcpy(code+1,&index,4);
    code[5]=0xff; code[6]=0x25;
    std::memset(code+7,0,4);
    auto* gateway=reinterpret_cast<void*>(uwcn_linux_gateway);
    std::memcpy(code+11,&gateway,8);
    branch(site,bytes,0xe8,code);
}
void finish() {
    if(mprotect(arena,arena_bytes,PROT_READ|PROT_EXEC)!=0)
        throw std::runtime_error("Cannot finalize native hook gateways");
}
}
void prepare_hooks(std::uintptr_t base) {
    // The ELF's final PT_LOAD ends at RVA 0x0ada89e0. This dedicated bridge
    // range is within rel32 reach and outside every native load segment.
    arena=static_cast<unsigned char*>(mmap(reinterpret_cast<void*>(base+0x20000000),arena_bytes,
        PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED_NOREPLACE,-1,0));
    if(arena==MAP_FAILED) throw std::runtime_error("Native gateway allocation: "+std::string(std::strerror(errno)));
    api={base,call,replace,instruction,finish};
}
}
extern "C" const uwcn::linux_host::Hooks* uwcn_linux_hooks() { return &uwcn::linux_host::api; }
extern "C" __attribute__((visibility("hidden"))) void uwcn_linux_dispatch(uwcn::linux_host::Frame* frame) {
    uwcn::linux_host::callbacks[frame->id](*frame);
}
