#include "internal.h"
#include <array>
#include <vector>
#include <memory>
#include <cstring>
#include <atomic>

namespace uwcn::host {
struct Slot { HookSpec spec; std::uint8_t* code; std::uintptr_t original; };
struct Pending { Slot* slot; u64 token; u32 original_return; u32* arguments; };
static std::vector<std::unique_ptr<Slot>> slots;
static thread_local std::vector<Pending> pending;
static thread_local std::vector<u32> fragments;
static std::atomic<u64> next_token{1};
extern "C" void uwcn_call_bridge();
extern "C" void uwcn_after_bridge();
extern "C" void uwcn_inline_bridge();
extern "C" void uwcn_fragment_return();
extern "C" void __cdecl uwcn_enter_fragment(u32);
static u32 return_target(u32 address) {
    return !fragments.empty() && fragments.back()==address ? reinterpret_cast<u32>(&uwcn_fragment_return) : address;
}

static void copy_registers(NativeFrame& destination,const u32* raw,u32 native_esp) {
    std::memcpy(&destination,raw,sizeof(destination));
    destination.esp=native_esp;
}
static void restore_registers(u32* raw,const NativeFrame& source) {
    const u32 saved_esp=raw[3];
    std::memcpy(raw,&source,sizeof(source));
    raw[3]=saved_esp; // POPAD discards this field.
}

extern "C" u32 __cdecl uwcn_before_route(u32* raw) {
    Slot* slot=reinterpret_cast<Slot*>(raw[9]);
    NativeFrame frame{};
    copy_registers(frame,raw,reinterpret_cast<u32>(raw+10));
    NativeEvent event{NativePhase::before,slot->spec.id,next_token.fetch_add(1),&frame,raw+11,slot->spec.argument_count};
    DispatchResult decision{};
    dispatch(event,decision);
    if(decision.skip_original) {
        event.phase=NativePhase::after;
        DispatchResult after{};
        dispatch(event,after);
        restore_registers(raw,frame);
        raw[10]=return_target(raw[10]);
        return 1;
    }
    pending.push_back({slot,event.token,raw[10],raw+11});
    restore_registers(raw,frame);
    raw[9]=static_cast<u32>(slot->original);
    raw[10]=reinterpret_cast<u32>(&uwcn_after_bridge);
    return 0;
}

extern "C" void __cdecl uwcn_after_dispatch(u32* raw) {
    Pending call=pending.back();
    pending.pop_back();
    NativeFrame frame{};
    copy_registers(frame,raw,reinterpret_cast<u32>(raw+10));
    NativeEvent event{NativePhase::after,call.slot->spec.id,call.token,&frame,call.arguments,call.slot->spec.argument_count};
    DispatchResult decision{};
    dispatch(event,decision);
    restore_registers(raw,frame);
    raw[9]=return_target(call.original_return);
}

extern "C" void __cdecl uwcn_inline_dispatch(u32* raw) {
    Slot* slot=reinterpret_cast<Slot*>(raw[9]);
    NativeFrame frame{};
    copy_registers(frame,raw,reinterpret_cast<u32>(raw+10));
    NativeEvent event{NativePhase::inline_before,slot->spec.id,next_token.fetch_add(1),&frame,raw+10,slot->spec.argument_count};
    DispatchResult decision{};
    dispatch(event,decision);
    restore_registers(raw,frame);
    raw[9]=decision.resume_rva ? static_cast<u32>(api.image_base+decision.resume_rva)
        : decision.skip_original ? static_cast<u32>(api.image_base+slot->spec.site_rva+slot->spec.byte_count)
        : reinterpret_cast<u32>(slot->code+16);
}

#if defined(__GNUC__) && defined(__i386__)
extern "C" __attribute__((naked)) void uwcn_fragment_return() { __asm__ __volatile__("ret\n"); }
extern "C" __attribute__((naked)) void __cdecl uwcn_enter_fragment(u32) {
    __asm__ __volatile__("pushl %ebp\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tmovl 20(%esp),%eax\n\tcall *%eax\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tpopl %ebp\n\tret\n");
}
extern "C" __attribute__((naked)) void uwcn_call_bridge() {
    __asm__ __volatile__(
        "pushfl\n\tpushal\n\tmovl %esp,%ebx\n\tsubl $528,%esp\n\tandl $-16,%esp\n\tfxsave (%esp)\n\tsubl $12,%esp\n\tpushl %ebx\n\tcall _uwcn_before_route\n\taddl $16,%esp\n\tfxrstor (%esp)\n\tmovl %ebx,%esp\n\ttestl %eax,%eax\n\tjnz 1f\n\tpopal\n\tpopfl\n\tret\n"
        "1:\n\tpopal\n\tpopfl\n\tleal 4(%esp),%esp\n\tret\n");
}
extern "C" __attribute__((naked)) void uwcn_after_bridge() {
    __asm__ __volatile__("pushl $0\n\tpushfl\n\tpushal\n\tmovl %esp,%ebx\n\tsubl $528,%esp\n\tandl $-16,%esp\n\tfxsave (%esp)\n\tsubl $12,%esp\n\tpushl %ebx\n\tcall _uwcn_after_dispatch\n\taddl $16,%esp\n\tfxrstor (%esp)\n\tmovl %ebx,%esp\n\tpopal\n\tpopfl\n\tret\n");
}
extern "C" __attribute__((naked)) void uwcn_inline_bridge() {
    __asm__ __volatile__("pushfl\n\tpushal\n\tmovl %esp,%ebx\n\tsubl $528,%esp\n\tandl $-16,%esp\n\tfxsave (%esp)\n\tsubl $12,%esp\n\tpushl %ebx\n\tcall _uwcn_inline_dispatch\n\taddl $16,%esp\n\tfxrstor (%esp)\n\tmovl %ebx,%esp\n\tpopal\n\tpopfl\n\tret\n");
}
#else
#error The verified native bridge requires the bundled i686 MinGW toolchain.
#endif

static void relative(std::uint8_t* at,std::uint8_t opcode,std::uintptr_t target) {
    at[0]=opcode;
    const std::int32_t displacement=static_cast<std::int32_t>(target-reinterpret_cast<std::uintptr_t>(at)-5);
    std::memcpy(at+1,&displacement,4);
}
static bool write_patch(void* destination,const void* bytes,u32 size) {
    DWORD old=0;
    if(!VirtualProtect(destination,size,PAGE_EXECUTE_READWRITE,&old)) return false;
    std::memcpy(destination,bytes,size);
    FlushInstructionCache(GetCurrentProcess(),destination,size);
    DWORD ignored=0;
    return VirtualProtect(destination,size,old,&ignored)!=0;
}

Status UWCN_CALL install_hooks(const HookSpec* specs,u32 count) {
    // Complete validation occurs before the first native instruction is changed.
    for(u32 i=0;i<count;++i) {
        const auto& s=specs[i];
        if((s.kind==HookKind::call && (s.byte_count!=5 || s.expected[0]!=0xe8)) ||
           (s.kind==HookKind::inline_code && (s.byte_count<5 || s.byte_count>16)) ||
           (s.kind==HookKind::import_slot && s.byte_count!=4)) return Status::invalid;
        Slot* previous=nullptr;
        for(const auto& slot:slots) if(slot->spec.id==s.id) previous=slot.get();
        if(previous) {
            if(std::memcmp(&previous->spec,&s,sizeof(s))!=0) return Status::invalid;
        } else if(std::memcmp(reinterpret_cast<void*>(api.image_base+s.site_rva),s.expected,s.byte_count)!=0) return Status::invalid;
        if(s.kind==HookKind::call) {
            std::int32_t delta=0; std::memcpy(&delta,s.expected+1,4);
            if(s.site_rva+5+delta!=s.target_rva) return Status::invalid;
        }
    }
    for(u32 i=0;i<count;++i) {
        const auto& s=specs[i];
        bool present=false;
        for(const auto& slot:slots) if(slot->spec.id==s.id) present=true;
        if(present) continue;
        auto slot=std::make_unique<Slot>();
        slot->spec=s;
        slot->code=static_cast<std::uint8_t*>(VirtualAlloc(nullptr,64,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE));
        if(!slot->code) return Status::failed;
        slot->original=api.image_base+s.target_rva;
        if(s.kind==HookKind::import_slot) std::memcpy(&slot->original,reinterpret_cast<void*>(api.image_base+s.site_rva),4);
        slot->code[0]=0x68;
        const u32 address=reinterpret_cast<u32>(slot.get());
        std::memcpy(slot->code+1,&address,4);
        relative(slot->code+5,0xe9,reinterpret_cast<std::uintptr_t>(s.kind==HookKind::inline_code ? &uwcn_inline_bridge : &uwcn_call_bridge));
        if(s.kind==HookKind::inline_code) {
            std::memcpy(slot->code+16,s.expected,s.byte_count);
            relative(slot->code+16+s.byte_count,0xe9,api.image_base+s.site_rva+s.byte_count);
        }
        DWORD previous=0;
        if(!VirtualProtect(slot->code,64,PAGE_EXECUTE_READ,&previous)) return Status::failed;
        FlushInstructionCache(GetCurrentProcess(),slot->code,64);
        std::array<std::uint8_t,16> patch{}; patch.fill(0x90);
        if(s.kind==HookKind::import_slot) std::memcpy(patch.data(),&slot->code,4);
        else {
            patch[0]=s.kind==HookKind::call ? 0xe8 : 0xe9;
            const std::int32_t delta=static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(slot->code)-(api.image_base+s.site_rva)-5);
            std::memcpy(patch.data()+1,&delta,4);
        }
        slots.push_back(std::move(slot));
        if(!write_patch(reinterpret_cast<void*>(api.image_base+s.site_rva),patch.data(),s.byte_count)) return Status::failed;
    }
    return Status::ok;
}
Status UWCN_CALL native_fragment(u32 begin_rva,u32 end_rva) {
    bool boundary=false;
    for(const auto& slot:slots) if(slot->spec.kind==HookKind::call && slot->spec.site_rva+5==end_rva) boundary=true;
    if(!boundary || !begin_rva) return Status::invalid;
    fragments.push_back(static_cast<u32>(api.image_base+end_rva));
    uwcn_enter_fragment(static_cast<u32>(api.image_base+begin_rva));
    fragments.pop_back();
    return Status::ok;
}
}

