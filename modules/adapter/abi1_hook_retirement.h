#pragma once
#include "../../sdk/host_abi.h"
#include <windows.h>
#include <array>
#include <cstring>
#include <initializer_list>
#include <span>

// One-way migration of the published tracking hooks, not a Host ABI service.
// See docs/evidence/20261019-abi1-hook-retirement.md for the exact binary and
// main-thread commit boundary to which this private layout belongs.
namespace uwcn::adapter::abi1_retirement {
// Process-local entry handles, not module pointers or text drawing records.
// Persist count entries across adapter reloads; these resident allocations stay
// alive until process exit. A fresh process has no retired thunk aliases.
struct RetirementRoute { u32 id,thunk,original; };
struct RetirementRoutes {
    u32 count{};
    std::array<RetirementRoute,13> entries{};
};
struct RouteBinding { u32 id,target; };
namespace detail {
struct InlineSite {
    u32 id;
    u32 rva;
    u32 size;
    std::array<std::uint8_t,7> bytes;
};
inline constexpr std::array<InlineSite,4> inline_sites{{
    {50,0x10BB04,6,{0x89,0x0C,0x82,0xF6,0x06,0x02,0}},
    {51,0x11454F,6,{0x89,0x14,0x81,0xF6,0x06,0x02,0}},
    {52,0x10BB7D,7,{0x8B,0x45,0xFC,0x48,0x83,0xF8,0x03}},
    {53,0x10BE33,6,{0x89,0x14,0x81,0xF6,0x07,0x02,0}}
}};
struct ImportSite { u32 id,rva,arguments; const char* name; };
inline constexpr std::array<ImportSite,13> import_sites{{
    {0x4000,0x18C204,4,"SDL_UpperBlit"},
    {0x4001,0x18C1E8,3,"SDL_FillRect"},
    {0x4002,0x18C1F4,1,"SDL_FreeSurface"},
    {0x4003,0x18C1E0,2,"SDL_CreateTextureFromSurface"},
    {0x4004,0x18C21C,4,"SDL_UpdateTexture"},
    {0x4005,0x18C228,4,"SDL_RenderCopy"},
    {0x4006,0x18C22C,1,"SDL_DestroyTexture"},
    {0x4007,0x18C224,1,"SDL_RenderClear"},
    {0x4008,0x18C1EC,2,"SDL_RenderFillRect"},
    {0x4009,0x18C1C0,3,"SDL_RenderDrawPoint"},
    {0x400A,0x18C1F0,8,"SDL_CreateRGBSurface"},
    {0x400B,0x18C208,5,"SDL_CreateTexture"},
    {0x400C,0x18C17C,4,"SDL_UpperBlitScaled"}
}};
struct Removal {
    HookSpec spec{};
    u32 thunk{}; // Zero denotes the already-original native entry.
    u32 original{};
};
inline u32 word(const std::uint8_t* bytes) {
    u32 value{};
    std::memcpy(&value,bytes,4);
    return value;
}
inline bool read(u32 address,void* bytes,std::size_t size) {
    SIZE_T count{};
    return ReadProcessMemory(GetCurrentProcess(),reinterpret_cast<const void*>(static_cast<std::uintptr_t>(address)),bytes,size,&count)!=0 && count==size;
}
inline u32 jump_target(u32 instruction,const std::uint8_t* bytes) {
    return instruction+5+word(bytes+1);
}
inline std::array<std::uint8_t,5> jump(u32 instruction,u32 target) {
    std::array<std::uint8_t,5> bytes{{0xE9,0,0,0,0}};
    const u32 displacement=target-instruction-5;
    std::memcpy(bytes.data()+1,&displacement,4);
    return bytes;
}
inline bool published_thunk(const Removal& entry,u32 bridge,u32 image_base) {
    std::array<std::uint8_t,64> code{};
    if(!read(entry.thunk,code.data(),code.size())) return false;
    if(code[0]!=0x68 || code[5]!=0xE9 || jump_target(entry.thunk+5,code.data()+5)!=bridge) return false;
    // The published x86 Slot is HookSpec[40], code[4], original[4].
    std::array<std::uint8_t,48> slot{};
    if(!read(word(code.data()+1),slot.data(),slot.size())) return false;
    if(std::memcmp(slot.data(),&entry.spec,40)!=0 || word(slot.data()+40)!=entry.thunk || word(slot.data()+44)!=entry.original) return false;
    if(entry.spec.kind==HookKind::inline_code) {
        const u32 size=entry.spec.byte_count;
        if(std::memcmp(code.data()+16,entry.spec.expected,size)!=0 || code[16+size]!=0xE9) return false;
        if(jump_target(entry.thunk+16+size,code.data()+16+size)!=image_base+entry.spec.site_rva+size) return false;
    }
    return true;
}
inline bool write_code(u32 address,const void* bytes,u32 size) {
    void* destination=reinterpret_cast<void*>(static_cast<std::uintptr_t>(address));
    DWORD previous{};
    if(!VirtualProtect(destination,size,PAGE_EXECUTE_READWRITE,&previous)) return false;
    std::memcpy(destination,bytes,size);
    const bool flushed=FlushInstructionCache(GetCurrentProcess(),destination,size)!=0;
    DWORD ignored{};
    const bool restored=VirtualProtect(destination,size,previous,&ignored)!=0;
    return flushed && restored;
}
inline bool write_import(u32 address,u32 original) {
    auto* destination=reinterpret_cast<volatile LONG*>(static_cast<std::uintptr_t>(address));
    DWORD previous{};
    if(!VirtualProtect(const_cast<LONG*>(destination),4,PAGE_READWRITE,&previous)) return false;
    InterlockedExchange(destination,static_cast<LONG>(original));
    DWORD ignored{};
    return VirtualProtect(const_cast<LONG*>(destination),4,previous,&ignored)!=0;
}
}

// Call from adapter initialize before install_hooks. A hot transaction must
// replace render and adapter together; the recorded main-thread commit boundary
// is required. Startup contains only original bytes and performs no writes.
// IDs 50..53 and 0x4000..0x400C must never be registered again in this process.
inline Status retire_tracking_hooks(std::uintptr_t native_image,HMODULE resident_loader,HMODULE sdl,RetirementRoutes* routes=nullptr) {
    const u32 image_base=static_cast<u32>(native_image);
    const u32 loader_base=static_cast<u32>(reinterpret_cast<std::uintptr_t>(resident_loader));
    std::array<detail::Removal,17> removals{};
    RetirementRoutes recognized{};
    std::size_t index{};
    // Recognize every entry before modifying any native code or pointer.
    for(const auto& site:detail::inline_sites) {
        auto& entry=removals[index++];
        entry.spec.id=site.id;
        entry.spec.kind=HookKind::inline_code;
        entry.spec.site_rva=site.rva;
        entry.spec.byte_count=site.size;
        std::memcpy(entry.spec.expected,site.bytes.data(),site.size);
        entry.original=image_base; // Published Slot uses image_base + target_rva.
        std::array<std::uint8_t,7> installed{};
        if(!detail::read(image_base+site.rva,installed.data(),site.size)) return Status::invalid;
        if(std::memcmp(installed.data(),site.bytes.data(),site.size)==0) continue;
        if(installed[0]!=0xE9) return Status::invalid;
        for(u32 byte=5;byte<site.size;++byte) if(installed[byte]!=0x90) return Status::invalid;
        entry.thunk=detail::jump_target(image_base+site.rva,installed.data());
        if(!detail::published_thunk(entry,loader_base+0x19940,image_base)) return Status::invalid;
    }
    for(const auto& site:detail::import_sites) {
        auto& entry=removals[index++];
        entry.spec.id=site.id;
        entry.spec.kind=HookKind::import_slot;
        entry.spec.site_rva=site.rva;
        entry.spec.argument_count=site.arguments;
        entry.spec.byte_count=4;
        entry.original=static_cast<u32>(reinterpret_cast<std::uintptr_t>(GetProcAddress(sdl,site.name)));
        if(!entry.original) return Status::invalid;
        std::memcpy(entry.spec.expected,&entry.original,4);
        u32 installed{};
        if(!detail::read(image_base+site.rva,&installed,4)) return Status::invalid;
        if(installed==entry.original) continue;
        entry.thunk=installed;
        if(!detail::published_thunk(entry,loader_base+0x198D0,image_base)) return Status::invalid;
        recognized.entries[recognized.count++]={site.id,entry.thunk,entry.original};
    }
    if(routes) *routes=recognized;
    // Cached game function pointers can still name the old SDL thunk. Redirect
    // its entry before restoring the IAT, keeping its allocation and Slot alive.
    for(const auto& entry:removals) {
        if(!entry.thunk) continue;
        if(entry.spec.kind==HookKind::import_slot) {
            const auto direct=detail::jump(entry.thunk,entry.original);
            if(!detail::write_code(entry.thunk,direct.data(),static_cast<u32>(direct.size()))) return Status::failed;
            if(!detail::write_import(image_base+entry.spec.site_rva,entry.original)) return Status::failed;
        } else if(!detail::write_code(image_base+entry.spec.site_rva,entry.spec.expected,entry.spec.byte_count)) return Status::failed;
    }
    return Status::ok;
}

// Call only at the same recorded main-thread transaction boundary. A binding
// applies to its recognized resident alias; IDs with no old alias need no write.
// Before unloading a target's business DLL, explicitly bind each affected route
// back to that route's original SDL address. Restore serialized aliases before
// binding the new generation. This does not modify the native IAT or Host Slot.
inline Status bind_routes(const RetirementRoutes& routes,std::span<const RouteBinding> bindings) {
    for(u32 index=0;index<routes.count;++index) {
        const auto& route=routes.entries[index];
        for(const auto& binding:bindings) {
            if(binding.id!=route.id) continue;
            const auto direct=detail::jump(route.thunk,binding.target);
            if(!detail::write_code(route.thunk,direct.data(),static_cast<u32>(direct.size()))) return Status::failed;
        }
    }
    return Status::ok;
}
inline Status bind_routes(const RetirementRoutes& routes,std::initializer_list<RouteBinding> bindings) {
    return bind_routes(routes,std::span<const RouteBinding>(bindings.begin(),bindings.size()));
}
}
