#include "native_ui_cache_owners.h"
#include <array>
#include <cstring>
#include <optional>

namespace uwcn::adapter::native_ui_cache_owners {
namespace {
std::uintptr_t base{};
Callbacks callbacks{};

enum class Family : u32 { first,second,named,menu };
enum class Operation : u32 { save,restore };
struct CopySite { u32 caller_return; Family family; Operation operation; };
struct Copy { Slot slot; Operation operation; };

// Actual original caller-return addresses, including the compiler's indirect
// register CALLs. The census is 33 first-background copies, three second-
// background copies, two named copies and two menu-cache copies.
constexpr std::array<CopySite,40> copies{{
    {0x3A38E,Family::first,Operation::save},
    {0x48FE6,Family::first,Operation::save},
    {0x5558B,Family::first,Operation::save},
    {0x5690F,Family::first,Operation::save},
    {0x56A4D,Family::first,Operation::save},
    {0x56FAE,Family::first,Operation::save},
    {0xB0E5E,Family::first,Operation::save},
    {0xD7A55,Family::first,Operation::save},
    {0xF5A63,Family::first,Operation::save},
    {0xFB96C,Family::first,Operation::save},
    {0xFBBCB,Family::first,Operation::save},
    {0x10031D,Family::first,Operation::save},
    {0x103A9D,Family::first,Operation::save},
    {0x10DA42,Family::first,Operation::save},
    {0x125C2D,Family::first,Operation::save},
    {0x125C79,Family::first,Operation::save},
    {0x125DC9,Family::first,Operation::save},
    {0x125DFE,Family::first,Operation::save},
    {0x125E36,Family::first,Operation::save},
    {0x125E6B,Family::first,Operation::save},
    {0x125EA0,Family::first,Operation::save},
    {0x158D32,Family::first,Operation::save},
    {0x15DD9C,Family::first,Operation::save},
    {0x3A679,Family::first,Operation::restore},
    {0x56582,Family::first,Operation::restore},
    {0x56B1D,Family::first,Operation::restore},
    {0x57456,Family::first,Operation::restore},
    {0x574D4,Family::first,Operation::restore},
    {0xB1018,Family::first,Operation::restore},
    {0x100799,Family::first,Operation::restore},
    {0x10DA77,Family::first,Operation::restore},
    {0x10DAF7,Family::first,Operation::restore},
    {0x16ECD7,Family::first,Operation::restore},
    {0x10D37B,Family::second,Operation::save},
    {0x10D3B7,Family::second,Operation::restore},
    {0x10D447,Family::second,Operation::restore},
    {0x10C674,Family::named,Operation::save},
    {0x10C711,Family::named,Operation::restore},
    {0xD118F,Family::menu,Operation::save},
    {0x10DBE9,Family::menu,Operation::restore}
}};

enum Hook : u32 {
    first_created=0x5600,
    second_created,
    menu_created,
    named_created,
    named_cleared
};

template<class T> T* at(u32 rva) {
    return reinterpret_cast<T*>(base+rva);
}
Slot named_slot(u32 index) {
    return static_cast<Slot>(static_cast<u32>(Slot::named0)+index);
}

std::optional<Copy> identify(u32 caller_return,const void* source,const void* destination) {
    for(const auto& site:copies) {
        if(site.caller_return!=caller_return) continue;
        const auto main=*at<void*>(0x61BBB10);
        const bool saving=site.operation==Operation::save;
        if((saving ? source : destination)!=main) return std::nullopt;
        const auto cache=saving ? destination : source;
        if(site.family==Family::named) {
            for(u32 index=0;index<4;++index) {
                const auto owner=*at<void*>(0xA1C1CC4+index*sizeof(u32));
                if(owner && cache==owner) return Copy{named_slot(index),site.operation};
            }
            return std::nullopt;
        }
        u32 owner_rva{};
        Slot slot{};
        switch(site.family) {
        case Family::first: owner_rva=0xA1C2014;slot=Slot::first;break;
        case Family::second: owner_rva=0xA1BBD24;slot=Slot::second;break;
        case Family::menu: owner_rva=0xA1C1CE0;slot=Slot::menu;break;
        case Family::named: break;
        }
        const auto owner=*at<void*>(owner_rva);
        if(owner && cache==owner) return Copy{slot,site.operation};
        return std::nullopt;
    }
    return std::nullopt;
}

HookSpec owner_store(u32 id,u32 site,u32 owner_rva) {
    HookSpec spec{id,HookKind::inline_code,site,0,0,5,{0xA3}};
    const auto owner=static_cast<u32>(base+owner_rva);
    std::memcpy(spec.expected+1,&owner,sizeof(owner));
    return spec;
}
}

void initialize(std::uintptr_t image_base) {
    base=image_base;
    callbacks={};
}
void set_callbacks(const Callbacks& observers) { callbacks=observers; }

u32 owner_field(Slot slot) {
    switch(slot) {
    case Slot::first:return 0xA1C2014;
    case Slot::second:return 0xA1BBD24;
    case Slot::menu:return 0xA1C1CE0;
    default:return 0xA1C1CC4+(static_cast<u32>(slot)-static_cast<u32>(Slot::named0))*sizeof(u32);
    }
}
void* surface(Slot slot) {return *at<void*>(owner_field(slot));}
Status before_blit(u32 caller_return,const void* source,const void* destination,
    const render::Rect* source_rect,render::Rect* destination_rect,BlitPreparation& prepared) {
    const auto copy=identify(caller_return,source,destination);
    if(copy && copy->operation==Operation::restore) {
        prepared.restoring=true;prepared.slot=copy->slot;
        return callbacks.before_restore(copy->slot,{source,source_rect,destination_rect},prepared.restore);
    }
    return Status::ok;
}
void after_blit(u32 caller_return,const void* source,const void* destination,
    const BlitPreparation& prepared,int native_result) {
    if(prepared.restoring) {
        callbacks.after_restore(prepared.slot,prepared.restore,native_result);
        return;
    }
    if(native_result!=0) return;
    const auto copy=identify(caller_return,source,destination);
    if(!copy) return;
    if(copy->operation==Operation::save) callbacks.save(copy->slot);
}

void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(owner_store(first_created,0x10C21F,0xA1C2014));
    hooks.push_back(owner_store(second_created,0x10C2A2,0xA1BBD24));
    hooks.push_back(owner_store(menu_created,0x10C4A6,0xA1C1CE0));
    HookSpec named{named_created,HookKind::inline_code,0x10C661,0,0,7,
        {0x89,0x34,0x9D}};
    const auto slots=static_cast<u32>(base+0xA1C1CC4);
    std::memcpy(named.expected+3,&slots,sizeof(slots));
    hooks.push_back(named);
    // This exact memset belongs to 10C4C0's successful name match. EDI is the
    // original selected slot, preserved by the original cdecl memset call.
    hooks.push_back({named_cleared,HookKind::call,0x10C51A,0x18AE60,3,5,
        {0xE8,0x41,0xE9,0x07,0x00}});
}

Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=true;
    switch(event.id) {
    case first_created: callbacks.retire(Slot::first);return Status::ok;
    case second_created: callbacks.retire(Slot::second);return Status::ok;
    case menu_created: callbacks.retire(Slot::menu);return Status::ok;
    case named_created:
        callbacks.retire(named_slot(event.frame->ebx));
        return Status::ok;
    case named_cleared:
        if(event.phase==NativePhase::after) callbacks.retire(named_slot(event.frame->edi));
        return Status::ok;
    default:
        handled=false;
        return Status::ok;
    }
}

void shutdown() {
    callbacks={};
    base=0;
}
}
