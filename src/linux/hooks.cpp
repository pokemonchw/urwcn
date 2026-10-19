#include "hooks.h"
#include <sys/mman.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <stdexcept>
#include <vector>

extern "C" void uwcn_linux_gateway();
namespace uwcn::linux_host {
namespace {
constexpr std::size_t arena_bytes=65536;
unsigned char* arena;
std::size_t used;
Hooks api;
enum class Kind { replacement,instruction,around,tail };
struct Hook {
    std::uint32_t site,bytes;
    Kind kind;
    std::vector<unsigned char> original;
    unsigned char* relay;
    InlineCallback callback{};
    CallCallback phased{};
    unsigned active{};
    bool installed{};
};
std::vector<Hook> records;
void writable(void* pointer,std::size_t bytes,int protection) {
    const auto page=static_cast<std::uintptr_t>(sysconf(_SC_PAGESIZE));
    const auto begin=reinterpret_cast<std::uintptr_t>(pointer)&~(page-1);
    const auto end=(reinterpret_cast<std::uintptr_t>(pointer)+bytes+page-1)&~(page-1);
    if(mprotect(reinterpret_cast<void*>(begin),end-begin,protection)!=0)
        throw std::runtime_error("mprotect: "+std::string(std::strerror(errno)));
}
void jump(unsigned char* code,void* target) {
    code[0]=0xff; code[1]=0x25;
    std::memset(code+2,0,4);
    std::memcpy(code+6,&target,8);
}
Hook& register_hook(std::uint32_t site,std::uint32_t bytes,Kind kind) {
    for(auto& entry:records) if(entry.site==site) {
        if(entry.bytes!=bytes || entry.kind!=kind)
            throw std::runtime_error("Hook contract changed at RVA "+std::to_string(site));
        return entry;
    }
    auto* original=reinterpret_cast<unsigned char*>(api.base+site);
    if(used+32>arena_bytes) throw std::runtime_error("Native gateway arena exhausted");
    records.push_back({site,bytes,kind,{original,original+bytes},arena+used});
    used+=32;
    return records.back();
}
void patch(Hook& entry,unsigned char opcode) {
    auto* code=reinterpret_cast<unsigned char*>(api.base+entry.site);
    const auto displacement=static_cast<std::int32_t>(entry.relay-(code+5));
    writable(code,entry.bytes,PROT_READ|PROT_WRITE|PROT_EXEC);
    code[0]=opcode;
    std::memcpy(code+1,&displacement,4);
    std::memset(code+5,0x90,entry.bytes-5);
    writable(code,entry.bytes,PROT_READ|PROT_EXEC);
    entry.installed=true;
}
void replace(std::uint32_t site,std::uint32_t bytes,void* target) {
    auto& entry=register_hook(site,bytes,Kind::replacement);
    jump(entry.relay,target);
    patch(entry,0xe9);
}
void gateway(Hook& entry) {
    const auto index=static_cast<std::uint32_t>(&entry-records.data());
    entry.relay[0]=0x68;
    std::memcpy(entry.relay+1,&index,4);
    jump(entry.relay+5,reinterpret_cast<void*>(uwcn_linux_gateway));
    patch(entry,entry.kind==Kind::tail ? 0xe9 : 0xe8);
}
void instruction(std::uint32_t site,std::uint32_t bytes,InlineCallback callback) {
    auto& entry=register_hook(site,bytes,Kind::instruction);
    entry.callback=callback;
    gateway(entry);
}
void around(std::uint32_t site,CallCallback callback,bool tail) {
    auto& entry=register_hook(site,5,tail ? Kind::tail : Kind::around);
    entry.phased=callback;
    gateway(entry);
}
void finish() {
    for(const auto& entry:records) if(entry.active && !entry.installed)
        throw std::runtime_error("Active native call lost its After hook at RVA "+std::to_string(entry.site));
    writable(arena,arena_bytes,PROT_READ|PROT_EXEC);
}
struct Lease {
    Lease() { enter_business(); }
    ~Lease() { leave_business(); }
};
}
void begin_hooks() { writable(arena,arena_bytes,PROT_READ|PROT_WRITE); }
void retire_hooks() {
    for(auto& entry:records) if(entry.installed) {
        auto* code=reinterpret_cast<void*>(api.base+entry.site);
        writable(code,entry.bytes,PROT_READ|PROT_WRITE|PROT_EXEC);
        std::memcpy(code,entry.original.data(),entry.bytes);
        writable(code,entry.bytes,PROT_READ|PROT_EXEC);
        entry.callback=nullptr;
        entry.phased=nullptr;
        entry.installed=false;
    }
}
void prepare_hooks(std::uintptr_t base) {
    // Final ELF PT_LOAD ends at RVA 0x0ada89e0; this arena is in rel32 reach.
    arena=static_cast<unsigned char*>(mmap(reinterpret_cast<void*>(base+0x20000000),arena_bytes,
        PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED_NOREPLACE,-1,0));
    if(arena==MAP_FAILED) throw std::runtime_error("Native gateway allocation: "+std::string(std::strerror(errno)));
    api={base,replace,instruction,around,finish,enter_business,leave_business};
}
void dispatch(Frame& frame) {
    const auto index=frame.id;
    if(records[index].kind==Kind::instruction) {
        Lease lease;
        records[index].callback(frame);
        return;
    }
    ++records[index].active;
    CallState state;
    Frame arguments=frame;
    { Lease lease; records[index].phased(arguments,Phase::before,state); }
    // Only resident code, integer arguments and native frames span this call.
    // Re-read the callback by stable slot after it returns: reload may have
    // replaced the adapter and extended the hook registry during native wait.
    if(!state.skip) {
        using Native=std::uintptr_t (*)(std::uintptr_t,std::uintptr_t,std::uintptr_t,
                                       std::uintptr_t,std::uintptr_t,std::uintptr_t);
        frame.rax=reinterpret_cast<Native>(api.base+state.target)(arguments.rdi,arguments.rsi,
            arguments.rdx,arguments.rcx,arguments.r8,arguments.r9);
    } else frame.rax=arguments.rax;
    { Lease lease; records[index].phased(frame,Phase::after,state); }
    std::free(state.text);
    --records[index].active;
}
}
extern "C" const uwcn::linux_host::Hooks* uwcn_linux_hooks_v2() { return &uwcn::linux_host::api; }
extern "C" __attribute__((visibility("hidden"))) void uwcn_linux_dispatch(uwcn::linux_host::Frame* frame) {
    uwcn::linux_host::dispatch(*frame);
}
