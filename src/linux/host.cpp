#include "hooks.h"
#include "control.h"
#include "elf_module.h"
#include "file_identity.h"
#include "sdk/host_abi.h"
#include <dlfcn.h>
#include <link.h>
#include <array>
#include <atomic>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <map>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

namespace uwcn::linux_host {
namespace {
using Main=int (*)(int,char**,char**);
Main native_main;
constexpr const char* names[]{"catalog","semantic","render","layout","main_menu","adapter"};
struct Module {
    void* image{};
    const ModuleApi* table{};
    std::uintptr_t retiring_address{};
    std::vector<std::uint8_t> state;
    bool saved{};
    u32 generation=1;
    std::string hash;
};
std::array<Module,6> modules;
std::filesystem::path package;
std::wstring package_wide;
HostApi host;
std::thread::id game_thread;
std::atomic<bool> initialized{};
u32 active_calls{};
bool servicing{};
std::mutex control_lock;
std::condition_variable changed;
enum class TransactionPhase { idle,prepare_requested,ready,commit_requested,abort_requested,applied,failed,cancelled };
TransactionPhase phase=TransactionPhase::idle;
bool suspended{};
bool control_stopped{};
u32 change_mask{};
std::string transaction,stage_path,response;
std::map<std::string,std::string> candidates;
struct Lease {
    Lease() { enter_business(); }
    ~Lease() { leave_business(); }
};
std::string relative_module(u32 index) { return "modules/uwcn_"+std::string(names[index])+".dll"; }
void require(Status status,const std::string& operation) {
    if(status!=Status::ok) throw std::runtime_error(operation+": status "+std::to_string(static_cast<u32>(status)));
}
Status invoke(ModuleId id,u32 operation,const void* input,u32 bytes,void* output,u32* capacity) {
    auto& module=modules.at(static_cast<u32>(id)-1);
    if(!module.table) return Status::unavailable;
    Lease lease;
    return module.table->invoke(operation,input,bytes,output,capacity);
}
void log(const wchar_t* message) { std::fwprintf(stderr,L"URWCN: %ls\n",message); }
void load_module(u32 index,bool restore) {
    const auto file=package/relative_module(index);
    inspect_module(file,index+1);
    auto& module=modules[index];
    module.image=dlopen(file.c_str(),RTLD_NOW|RTLD_LOCAL);
    if(!module.image) throw std::runtime_error(dlerror());
    const auto get=reinterpret_cast<GetModuleApi>(dlsym(module.image,"uwcn_get_module_api"));
    if(!get) throw std::runtime_error("Missing module API: "+file.string());
    const auto* table=get();
    if(!table || table->size!=sizeof(ModuleApi) || table->abi!=kHostAbi || static_cast<u32>(table->id)!=index+1)
        throw std::runtime_error("Module API differs: "+file.string());
    module.table=table;
    if(index==5) begin_hooks();
    require(table->initialize(&host),"Initialize "+std::string(names[index]));
    if(restore) require(table->restore_state(module.state.data(),module.state.size()),"Restore "+std::string(names[index]));
    module.hash=file_sha256(file);
}
void unload_module(u32 index) {
    auto& module=modules[index];
    if(module.image) {
        if(module.table) { module.table->shutdown(); module.table=nullptr; }
        link_map* mapping{};
        if(dlinfo(module.image,RTLD_DI_LINKMAP,&mapping)!=0) throw std::runtime_error(dlerror());
        module.retiring_address=mapping->l_addr;
        if(dlclose(module.image)!=0) throw std::runtime_error(dlerror());
        module.image=nullptr;
    }
    if(!module.retiring_address) return;
    struct Identity { std::uintptr_t base; bool mapped; } identity{module.retiring_address,false};
    dl_iterate_phdr([](dl_phdr_info* entry,std::size_t,void* data) {
        auto& result=*static_cast<Identity*>(data);
        if(entry->dlpi_addr==result.base) result.mapped=true;
        return 0;
    },&identity);
    if(identity.mapped) throw std::runtime_error("dlclose left module mapped: "+relative_module(index));
    module.retiring_address=0;
}
void inspect_candidates() {
    candidates.clear();
    std::ifstream listing(std::filesystem::path(stage_path)/"candidate-files.tsv");
    std::string line;
    auto read_line=[&] {
        if(!std::getline(listing,line)) return false;
        if(!line.empty() && line.back()=='\r') line.pop_back();
        return true;
    };
    if(!read_line() || line!="UWCN_CANDIDATE_V1") throw std::runtime_error("Invalid candidate file manifest");
    while(read_line()) {
        const auto tab=line.find('\t');
        if(tab!=64) throw std::runtime_error("Invalid candidate hash record");
        const auto relative=line.substr(tab+1),hash=line.substr(0,tab);
        const std::filesystem::path path(relative);
        if(relative.empty() || path.has_root_path() || path.lexically_normal()!=path ||
           relative.starts_with("../") || relative==".." || relative=="uwcn_loader.dll")
            throw std::runtime_error("Invalid business candidate path: "+relative);
        if(!candidates.emplace(relative,hash).second) throw std::runtime_error("Duplicate candidate: "+relative);
        if(file_sha256(std::filesystem::path(stage_path)/path)!=hash)
            throw std::runtime_error("Candidate hash differs: "+relative);
    }
    if(!candidates.contains("release.json")) throw std::runtime_error("Candidate release manifest missing");
    for(u32 i=0;i<modules.size();++i) if(change_mask&(1u<<i)) {
        const auto relative=relative_module(i);
        if(!candidates.contains(relative)) throw std::runtime_error("Selected module absent from candidate: "+relative);
        inspect_module(std::filesystem::path(stage_path)/relative,i+1);
    }
}
void prepare_transaction() {
    inspect_candidates(); // Read ELF descriptors without executing candidate code.
    for(u32 i=0;i<modules.size();++i) if(change_mask&(1u<<i)) {
        auto& module=modules[i];
        if(module.saved) continue; // Explicit retry uses the original suspended state.
        u32 size{};
        const auto status=module.table->save_state(nullptr,&size);
        if(status!=Status::ok && status!=Status::insufficient_buffer) require(status,"Size state "+std::string(names[i]));
        module.state.resize(size);
        require(module.table->save_state(module.state.data(),&size),"Save state "+std::string(names[i]));
        module.saved=true;
    }
    { std::lock_guard lock(control_lock); suspended=true; }
    if(change_mask&32u) retire_hooks();
    for(int i=5;i>=0;--i) if(change_mask&(1u<<i)) unload_module(i);
}
void commit_transaction() {
    for(const auto& [relative,hash]:candidates)
        if(file_sha256(package/relative)!=hash) throw std::runtime_error("Published file differs from candidate: "+relative);
    for(u32 i=0;i<modules.size();++i) if(change_mask&(1u<<i)) load_module(i,true);
    for(u32 i=0;i<modules.size();++i) {
        u32 capacity{};
        require(invoke(static_cast<ModuleId>(i+1),kModuleDependenciesChanged,&change_mask,sizeof(change_mask),nullptr,&capacity),
                "Refresh dependencies "+std::string(names[i]));
    }
    for(u32 i=0;i<modules.size();++i) if(change_mask&(1u<<i)) {
        ++modules[i].generation;
        modules[i].saved=false;
        modules[i].state.clear();
    }
}
void complete(TransactionPhase result,const std::string& receipt) {
    std::lock_guard lock(control_lock);
    phase=result; response=receipt; changed.notify_all();
}
void initialize() {
    if(file_sha256("/proc/self/exe")!=game_sha256)
        throw std::runtime_error("The resident requires the recorded Linux ELF identity");
    package=std::filesystem::canonical(std::getenv("UWCN_PACKAGE"));
    package_wide=package.wstring();
    std::uintptr_t base{};
    dl_iterate_phdr([](dl_phdr_info* information,std::size_t,void* result) {
        *static_cast<std::uintptr_t*>(result)=information->dlpi_addr;
        return 1;
    },&base);
    prepare_hooks(base);
    host={sizeof(HostApi),kHostAbi,base,package_wide.c_str(),invoke,nullptr,
        [](u32 bytes)->void* { return std::malloc(bytes); },std::free,log,nullptr};
    for(u32 i=0;i<modules.size();++i) load_module(i,false);
    game_thread=std::this_thread::get_id();
    start_control();
    initialized=true;
}
int enter_game(int argc,char** argv,char** environment) {
    try { initialize(); }
    catch(const std::exception& error) { std::fprintf(stderr,"URWCN: %s\n",error.what()); return 1; }
    const int result=native_main(argc,argv,environment);
    initialized=false;
    stop_control();
    return result;
}
}
void enter_business() { ++active_calls; }
void leave_business() { --active_calls; }
void service_control() {
    if(!initialized || std::this_thread::get_id()!=game_thread || servicing || active_calls) return;
    {
        std::lock_guard lock(control_lock);
        if(phase!=TransactionPhase::prepare_requested) return;
    }
    servicing=true;
    for(;;) {
        TransactionPhase request;
        {
            std::unique_lock lock(control_lock);
            changed.wait(lock,[] { return phase==TransactionPhase::prepare_requested || phase==TransactionPhase::commit_requested || phase==TransactionPhase::abort_requested; });
            request=phase;
        }
        try {
            if(request==TransactionPhase::prepare_requested) {
                prepare_transaction();
                complete(TransactionPhase::ready,"ReadyToPublish "+transaction);
            } else if(request==TransactionPhase::abort_requested) {
                complete(TransactionPhase::cancelled,"Cancelled "+transaction+" Suspended");
            } else {
                commit_transaction();
                std::string receipt="Applied "+transaction;
                for(u32 i=0;i<modules.size();++i) if(change_mask&(1u<<i))
                    receipt+=' '+std::string(names[i])+':'+modules[i].hash+':'+std::to_string(modules[i].generation);
                // A metadata-only publication still has an explicit Applied receipt.
                if(!change_mask) receipt+=" metadata";
                { std::lock_guard lock(control_lock); suspended=false; }
                complete(TransactionPhase::applied,receipt);
                break;
            }
        } catch(const std::exception& error) {
            bool paused;
            { std::lock_guard lock(control_lock); paused=suspended; }
            if(!paused) for(auto& module:modules) { module.saved=false; module.state.clear(); }
            complete(TransactionPhase::failed,"Failed "+transaction+' '+error.what()+(paused ? " Suspended" : " Running"));
            if(!paused) break;
        }
        // Ready, failed-after-retirement and cancellation stay on this resident
        // stack. Only an explicit successful COMMIT releases the native wait.
    }
    servicing=false;
}
void end_control_requests() {
    initialized=false;
    std::lock_guard lock(control_lock);
    control_stopped=true;
    phase=TransactionPhase::failed;
    response="Failed game exited before transaction completion";
    changed.notify_all();
}
std::string control_command(const std::string& line) {
    std::istringstream input(line);
    std::string command,id;
    input>>command;
    std::unique_lock lock(control_lock);
    if(control_stopped) return response;
    if(command=="STATUS") return "UWCN_LINUX_CONTROL_V1 ABI=2 "+std::string(suspended ? "Suspended " : "Running ")+response;
    input>>id;
    if(command=="PREPARE") {
        u32 mask{};
        std::string stage;
        if(!(input>>mask) || mask>63 || id.size()!=32) return "Failed invalid PREPARE";
        std::getline(input>>std::ws,stage);
        if(stage.empty() || !std::filesystem::path(stage).is_absolute()) return "Failed invalid stage path";
        if(phase!=TransactionPhase::idle && phase!=TransactionPhase::applied && phase!=TransactionPhase::failed && phase!=TransactionPhase::cancelled)
            return "Failed transaction already active";
        if(suspended && mask!=change_mask) return "Failed suspended transaction requires the same module mask";
        transaction=id; change_mask=mask; stage_path=stage;
        phase=TransactionPhase::prepare_requested;
    } else if(command=="COMMIT" && id==transaction && phase==TransactionPhase::ready) phase=TransactionPhase::commit_requested;
    else if(command=="ABORT" && id==transaction && phase==TransactionPhase::ready) phase=TransactionPhase::abort_requested;
    else return "Failed transaction state mismatch";
    changed.notify_all();
    changed.wait(lock,[] { return phase==TransactionPhase::ready || phase==TransactionPhase::applied || phase==TransactionPhase::failed || phase==TransactionPhase::cancelled; });
    return response;
}
}
extern "C" int __libc_start_main(uwcn::linux_host::Main main,int argc,char** argv,void (*init)(),void (*fini)(),void (*rtld_fini)(),void* stack_end) {
    using namespace uwcn::linux_host;
    using Start=int (*)(Main,int,char**,void (*)(),void (*)(),void (*)(),void*);
    native_main=main;
    const auto start=reinterpret_cast<Start>(dlsym(RTLD_NEXT,"__libc_start_main"));
    return start(enter_game,argc,argv,init,fini,rtld_fini,stack_end);
}
