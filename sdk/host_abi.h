#pragma once
#include <cstdint>
#include <cstddef>

#if defined(_WIN32)
#define UWCN_CALL __cdecl
#define UWCN_EXPORT extern "C" __declspec(dllexport)
#else
#define UWCN_CALL
#define UWCN_EXPORT extern "C"
#endif

namespace uwcn {
using u32 = std::uint32_t;
using u64 = std::uint64_t;
inline constexpr u32 kHostAbi = 1; // New reconstruction; not compatible with the removed ABI 3.
enum class ModuleId : u32 { catalog=1, semantic=2, render=3, layout=4, main_menu=5, adapter=6 };
enum class Status : u32 { ok=0, invalid=1, unavailable=2, insufficient_buffer=3, failed=4 };
enum class NativePhase : u32 { before=0, after=1, inline_before=2 };
enum class HookKind : u32 { call=0, inline_code=1, import_slot=2 };

// These register values are writable. esp is the native entry stack address;
// changing esp is not supported. Call arguments exclude the return address.
struct NativeFrame { u32 edi,esi,ebp,esp,ebx,edx,ecx,eax,eflags; };
struct NativeEvent {
    NativePhase phase;
    u32 id;
    u64 token;
    NativeFrame* frame;
    u32* arguments;
    u32 argument_count;
};
struct DispatchResult {
    u32 skip_original;
    // Inline hooks only: zero replays the documented bytes; nonzero resumes at
    // image_base + resume_rva after the adapter has implemented those bytes.
    u32 resume_rva;
};
inline constexpr u32 kNativeDispatch = 1;
inline constexpr u32 kNativeInvalidate = 2;
inline constexpr u32 kModuleDependenciesChanged = 0xFFFF0001;

struct HookSpec {
    u32 id;
    HookKind kind;
    u32 site_rva;
    u32 target_rva; // CALL target; zero for inline/import slots.
    u32 argument_count;
    u32 byte_count; // 5 for E8; whole instructions (5..16) for inline; 4 for IAT.
    std::uint8_t expected[16];
    // Inline replay bytes must be position-independent and contain no ESP
    // adjustment or relative control transfer. The adapter supplies evidence.
};

struct HostApi {
    u32 size;
    u32 abi;
    std::uintptr_t image_base;
    const wchar_t* package_path;
    Status (UWCN_CALL *invoke)(ModuleId,u32,const void*,u32,void*,u32*);
    Status (UWCN_CALL *install_hooks)(const HookSpec*,u32);
    void* (UWCN_CALL *allocate)(u32);
    void (UWCN_CALL *release)(void*);
    void (UWCN_CALL *log)(const wchar_t*);
    // Execute a statically confirmed, stack-balanced native drawing fragment.
    // It must not enter input/animation waits or read an enclosing stack frame.
    // end_rva is the return address of an already registered CALL hook.
    Status (UWCN_CALL *native_fragment)(u32 begin_rva,u32 end_rva);
};
struct ModuleApi {
    u32 size;
    u32 abi;
    ModuleId id;
    Status (UWCN_CALL *initialize)(const HostApi*);
    Status (UWCN_CALL *invoke)(u32,const void*,u32,void*,u32*);
    Status (UWCN_CALL *save_state)(void*,u32*);
    Status (UWCN_CALL *restore_state)(const void*,u32);
    void (UWCN_CALL *shutdown)();
};
using GetModuleApi = const ModuleApi* (UWCN_CALL *)();

// Present in each module's PE export table; readable without loading the DLL.
struct ModuleDescriptor { u32 magic,abi,module_id,machine,state_schema; };
inline constexpr u32 kDescriptorMagic=0x314E4355;
}
