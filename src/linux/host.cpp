#include "hooks.h"
#include "file_identity.h"
#include "sdk/host_abi.h"
#include <dlfcn.h>
#include <link.h>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>

namespace {
using namespace uwcn;
using Main=int (*)(int,char**,char**);
Main native_main;
std::array<const ModuleApi*,7> modules{};
std::array<void*,7> libraries{};
std::wstring package_wide;
Status invoke(ModuleId id,u32 operation,const void* input,u32 bytes,void* output,u32* capacity) {
    return modules[static_cast<u32>(id)]->invoke(operation,input,bytes,output,capacity);
}
void log(const wchar_t* message) { std::fwprintf(stderr,L"URWCN: %ls\n",message); }
void initialize() {
    if(uwcn::linux_host::file_sha256("/proc/self/exe")!=uwcn::linux_host::game_sha256)
        throw std::runtime_error("The resident requires the recorded Linux ELF identity");
    const std::filesystem::path package(std::getenv("UWCN_PACKAGE"));
    package_wide=package.wstring();
    std::uintptr_t base{};
    dl_iterate_phdr([](dl_phdr_info* information,std::size_t,void* result) {
        *static_cast<std::uintptr_t*>(result)=information->dlpi_addr;
        return 1;
    },&base);
    uwcn::linux_host::prepare_hooks(base);
    static HostApi host{sizeof(HostApi),kHostAbi,base,package_wide.c_str(),invoke,nullptr,
        [](u32 bytes)->void* { return std::malloc(bytes); },std::free,log,nullptr};
    constexpr const char* names[]{"catalog","semantic","layout","render","main_menu","adapter"};
    for(const auto* name:names) {
        const auto file=package/"modules"/("uwcn_"+std::string(name)+".dll");
        void* library=dlopen(file.c_str(),RTLD_NOW|RTLD_LOCAL);
        if(!library) throw std::runtime_error(dlerror());
        const auto* descriptor=static_cast<const ModuleDescriptor*>(dlsym(library,"uwcn_module_descriptor"));
        if(!descriptor || descriptor->magic!=kDescriptorMagic || descriptor->machine!=kModuleMachine || descriptor->abi!=kHostAbi)
            throw std::runtime_error("Module descriptor differs from Linux native service ABI: "+file.string());
        const auto get=reinterpret_cast<GetModuleApi>(dlsym(library,"uwcn_get_module_api"));
        const auto* api=get();
        const auto index=static_cast<u32>(api->id);
        libraries[index]=library;
        modules[index]=api;
        if(api->initialize(&host)!=Status::ok) throw std::runtime_error("Module initialization failed: "+file.string());
    }
}
int enter_game(int argc,char** argv,char** environment) {
    try { initialize(); }
    catch(const std::exception& error) { std::fprintf(stderr,"URWCN: %s\n",error.what()); return 1; }
    return native_main(argc,argv,environment);
}
}
extern "C" int __libc_start_main(Main main,int argc,char** argv,void (*init)(),void (*fini)(),void (*rtld_fini)(),void* stack_end) {
    using Start=int (*)(Main,int,char**,void (*)(),void (*)(),void (*)(),void*);
    native_main=main;
    const auto start=reinterpret_cast<Start>(dlsym(RTLD_NEXT,"__libc_start_main"));
    return start(enter_game,argc,argv,init,fini,rtld_fini,stack_end);
}
