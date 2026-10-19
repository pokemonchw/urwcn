#include "internal.h"
#include <cstring>
#include <algorithm>

namespace uwcn::host {
using Poll=int (__cdecl *)(void*);
using WaitTimeout=int (__cdecl *)(void*,int);
using Peep=int (__cdecl *)(void*,int,int,u32,u32);
using Pump=void (__cdecl *)();
using Delay=void (__cdecl *)(u32);
using Present=void (__cdecl *)(void*);
using Error=const char* (__cdecl *)();
static Poll poll_event=nullptr;
static WaitTimeout wait_timeout=nullptr;
static Peep peep_events=nullptr;
static Pump pump_events=nullptr,clear_error=nullptr;
static Delay delay=nullptr;
static Present present=nullptr;
static Error get_error=nullptr;
static int __cdecl poll_bridge(void* event) { service_control(); return poll_event(event); }
static int __cdecl wait_bridge(void* event) {
    for(;;) {
        service_control(); clear_error();
        const int result=wait_timeout(event,16);
        if(result || *get_error()) return result;
    }
}
static int __cdecl timeout_bridge(void* event,int timeout) {
    const ULONGLONG start=GetTickCount64();
    for(;;) {
        service_control();
        const int remaining=timeout<0 ? 16 : std::max(0,timeout-static_cast<int>(GetTickCount64()-start));
        clear_error(); const int result=wait_timeout(event,std::min(16,remaining));
        if(result || *get_error() || (timeout>=0 && GetTickCount64()-start>=static_cast<ULONGLONG>(timeout))) return result;
    }
}
static int __cdecl peep_bridge(void* events,int count,int action,u32 first,u32 last) { service_control(); return peep_events(events,count,action,first,last); }
static void __cdecl pump_bridge() { service_control(); pump_events(); }
static void __cdecl delay_bridge(u32 milliseconds) {
    if(milliseconds==0) { service_control(); delay(0); return; }
    const ULONGLONG start=GetTickCount64();
    service_control();
    while(GetTickCount64()-start<milliseconds) {
        const u32 remaining=milliseconds-static_cast<u32>(GetTickCount64()-start);
        delay(std::min<u32>(16,remaining)); service_control();
    }
}
static void __cdecl present_bridge(void* renderer) { service_control(); present(renderer); }
bool install_control_imports() {
    HMODULE sdl=GetModuleHandleW(L"SDL2.dll");
    if(!sdl) return false;
    poll_event=reinterpret_cast<Poll>(GetProcAddress(sdl,"SDL_PollEvent"));
    wait_timeout=reinterpret_cast<WaitTimeout>(GetProcAddress(sdl,"SDL_WaitEventTimeout"));
    peep_events=reinterpret_cast<Peep>(GetProcAddress(sdl,"SDL_PeepEvents"));
    pump_events=reinterpret_cast<Pump>(GetProcAddress(sdl,"SDL_PumpEvents"));
    delay=reinterpret_cast<Delay>(GetProcAddress(sdl,"SDL_Delay"));
    present=reinterpret_cast<Present>(GetProcAddress(sdl,"SDL_RenderPresent"));
    get_error=reinterpret_cast<Error>(GetProcAddress(sdl,"SDL_GetError"));
    clear_error=reinterpret_cast<Pump>(GetProcAddress(sdl,"SDL_ClearError"));
    if(!poll_event || !wait_timeout || !peep_events || !pump_events || !delay || !present || !get_error || !clear_error) return false;
    const auto base=api.image_base;
    const auto* dos=reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
    const auto* nt=reinterpret_cast<const IMAGE_NT_HEADERS32*>(base+dos->e_lfanew);
    auto* imports=reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base+nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
    for(;imports->Name;++imports) {
        if(_stricmp(reinterpret_cast<const char*>(base+imports->Name),"SDL2.dll")!=0) continue;
        auto* source=reinterpret_cast<IMAGE_THUNK_DATA32*>(base+imports->OriginalFirstThunk);
        auto* target=reinterpret_cast<IMAGE_THUNK_DATA32*>(base+imports->FirstThunk);
        for(;source->u1.AddressOfData;++source,++target) {
            if(IMAGE_SNAP_BY_ORDINAL32(source->u1.Ordinal)) continue;
            const auto* entry=reinterpret_cast<const IMAGE_IMPORT_BY_NAME*>(base+source->u1.AddressOfData);
            const char* name=reinterpret_cast<const char*>(entry->Name); std::uintptr_t bridge=0;
            if(std::strcmp(name,"SDL_PollEvent")==0) bridge=reinterpret_cast<std::uintptr_t>(&poll_bridge);
            else if(std::strcmp(name,"SDL_WaitEvent")==0) bridge=reinterpret_cast<std::uintptr_t>(&wait_bridge);
            else if(std::strcmp(name,"SDL_WaitEventTimeout")==0) bridge=reinterpret_cast<std::uintptr_t>(&timeout_bridge);
            else if(std::strcmp(name,"SDL_PeepEvents")==0) bridge=reinterpret_cast<std::uintptr_t>(&peep_bridge);
            else if(std::strcmp(name,"SDL_PumpEvents")==0) bridge=reinterpret_cast<std::uintptr_t>(&pump_bridge);
            else if(std::strcmp(name,"SDL_Delay")==0) bridge=reinterpret_cast<std::uintptr_t>(&delay_bridge);
            else if(std::strcmp(name,"SDL_RenderPresent")==0) bridge=reinterpret_cast<std::uintptr_t>(&present_bridge);
            if(bridge) {
                DWORD previous=0,ignored=0;
                if(!VirtualProtect(&target->u1.Function,4,PAGE_READWRITE,&previous)) return false;
                target->u1.Function=static_cast<DWORD>(bridge);
                if(!VirtualProtect(&target->u1.Function,4,previous,&ignored)) return false;
            }
        }
    }
    return true;
}
}
