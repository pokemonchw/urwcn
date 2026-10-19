#include "internal.h"
#include <bcrypt.h>
#include <array>
#include <vector>
#include <mutex>
#include <atomic>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cwchar>

namespace uwcn::host {
HMODULE self=nullptr;
HostApi api{};
static std::wstring package_path;
static std::recursive_mutex gate;
static u32 active_calls=0;
static bool enabled=true;
static DWORD game_thread=0;
struct Module { HMODULE image=nullptr; const ModuleApi* table=nullptr; std::vector<std::uint8_t> state; u32 generation=1; };
static std::array<Module,6> modules;
static constexpr const wchar_t* names[]={L"catalog",L"semantic",L"render",L"layout",L"main_menu",L"adapter"};
static std::mutex control_lock;
enum class TransactionPhase { idle, prepare_requested, ready, commit_requested, abort_requested, cancelled, applied, failed };
static TransactionPhase phase=TransactionPhase::idle;
static std::wstring transaction,stage_path,error_text;
static u32 change_mask=0;
static HANDLE control_done=nullptr;
static std::array<std::wstring,6> candidate_hash;
static std::vector<HANDLE> candidate_files;
struct CandidateFile { std::wstring relative,hash; };
static std::vector<CandidateFile> candidate_identity;

void UWCN_CALL log(const wchar_t* message) {
    OutputDebugStringW(L"[UWCn] "); OutputDebugStringW(message); OutputDebugStringW(L"\n");
    const std::wstring path=package_path+L"\\uwcn.log";
    HANDLE file=CreateFileW(path.c_str(),FILE_APPEND_DATA,FILE_SHARE_READ|FILE_SHARE_WRITE,nullptr,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);
    if(file!=INVALID_HANDLE_VALUE) {
        int length=WideCharToMultiByte(CP_UTF8,0,message,-1,nullptr,0,nullptr,nullptr);
        std::string bytes(static_cast<std::size_t>(length),0);
        WideCharToMultiByte(CP_UTF8,0,message,-1,bytes.data(),length,nullptr,nullptr);
        if(!bytes.empty()) bytes.back()='\n';
        DWORD written=0; WriteFile(file,bytes.data(),static_cast<DWORD>(bytes.size()),&written,nullptr); CloseHandle(file);
    }
}
static void* UWCN_CALL allocate(u32 size) { return HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,size); }
static void UWCN_CALL release(void* value) { if(value) HeapFree(GetProcessHeap(),0,value); }
Status UWCN_CALL invoke(ModuleId module,u32 operation,const void* request,u32 size,void* response,u32* capacity) {
    std::lock_guard<std::recursive_mutex> lock(gate);
    const u32 index=static_cast<u32>(module)-1;
    if(index>=modules.size() || !enabled || !modules[index].table) return Status::unavailable;
    struct Lease { Lease() { ++active_calls; } ~Lease() { --active_calls; } } lease;
    return modules[index].table->invoke(operation,request,size,response,capacity);
}
void dispatch(NativeEvent& event,DispatchResult& result) {
    u32 capacity=sizeof(result);
    const auto status=invoke(ModuleId::adapter,kNativeDispatch,&event,sizeof(event),&result,&capacity);
    if(status!=Status::ok && status!=Status::unavailable) log((L"Native dispatch rejected id "+std::to_wstring(event.id)+L" with status "+std::to_wstring(static_cast<u32>(status))).c_str());
}

static std::wstring module_path(const std::wstring& base,u32 index) { return base+L"\\modules\\uwcn_"+names[index]+L".dll"; }
struct ReadPin {
    HANDLE file;
    explicit ReadPin(const std::wstring& path):file(CreateFileW(path.c_str(),GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr)) {}
    ~ReadPin() { if(file!=INVALID_HANDLE_VALUE) CloseHandle(file); }
};
static bool read_bytes(const std::wstring& path,std::vector<std::uint8_t>& bytes) {
    std::ifstream stream(std::filesystem::path(path),std::ios::binary|std::ios::ate);
    if(!stream) return false;
    const auto length=stream.tellg();
    if(length<0) return false;
    bytes.resize(static_cast<std::size_t>(length)); stream.seekg(0);
    return static_cast<bool>(stream.read(reinterpret_cast<char*>(bytes.data()),static_cast<std::streamsize>(bytes.size())));
}
static std::wstring hash_bytes(const std::vector<std::uint8_t>& bytes) {
    BCRYPT_ALG_HANDLE algorithm=nullptr; BCRYPT_HASH_HANDLE hash=nullptr;
    DWORD object_size=0,result_size=0;
    if(BCryptOpenAlgorithmProvider(&algorithm,BCRYPT_SHA256_ALGORITHM,nullptr,0)<0) return {};
    BCryptGetProperty(algorithm,BCRYPT_OBJECT_LENGTH,reinterpret_cast<PUCHAR>(&object_size),sizeof(object_size),&result_size,0);
    std::vector<std::uint8_t> object(object_size); std::array<std::uint8_t,32> digest{};
    bool ok=BCryptCreateHash(algorithm,&hash,object.data(),object_size,nullptr,0,0)>=0;
    if(ok) ok=BCryptHashData(hash,const_cast<PUCHAR>(bytes.data()),static_cast<ULONG>(bytes.size()),0)>=0;
    if(ok) ok=BCryptFinishHash(hash,digest.data(),static_cast<ULONG>(digest.size()),0)>=0;
    if(hash) BCryptDestroyHash(hash);
    BCryptCloseAlgorithmProvider(algorithm,0);
    if(!ok) return {};
    std::wstring hex; constexpr wchar_t alphabet[]=L"0123456789abcdef";
    for(auto byte:digest) { hex.push_back(alphabet[byte>>4]); hex.push_back(alphabet[byte&15]); }
    return hex;
}

// Resolve a PE export as file data. No candidate code or DllMain executes here.
static bool inspect_module(const std::vector<std::uint8_t>& bytes,u32 id) {
    if(bytes.size()<sizeof(IMAGE_DOS_HEADER)) return false;
    const auto* dos=reinterpret_cast<const IMAGE_DOS_HEADER*>(bytes.data());
    if(dos->e_magic!=IMAGE_DOS_SIGNATURE || dos->e_lfanew<0 || static_cast<std::size_t>(dos->e_lfanew)+sizeof(IMAGE_NT_HEADERS32)>bytes.size()) return false;
    const auto* nt=reinterpret_cast<const IMAGE_NT_HEADERS32*>(bytes.data()+dos->e_lfanew);
    if(nt->Signature!=IMAGE_NT_SIGNATURE || nt->FileHeader.Machine!=IMAGE_FILE_MACHINE_I386 || nt->OptionalHeader.Magic!=IMAGE_NT_OPTIONAL_HDR32_MAGIC) return false;
    const std::size_t section_offset=static_cast<std::size_t>(dos->e_lfanew)+4+sizeof(IMAGE_FILE_HEADER)+nt->FileHeader.SizeOfOptionalHeader;
    if(section_offset+nt->FileHeader.NumberOfSections*sizeof(IMAGE_SECTION_HEADER)>bytes.size()) return false;
    const auto* sections=reinterpret_cast<const IMAGE_SECTION_HEADER*>(bytes.data()+section_offset);
    auto address=[&](u32 rva,u32 size)->const std::uint8_t* {
        for(u32 i=0;i<nt->FileHeader.NumberOfSections;++i) {
            const auto& section=sections[i];
            if(rva>=section.VirtualAddress && rva-section.VirtualAddress<=section.SizeOfRawData && size<=section.SizeOfRawData-(rva-section.VirtualAddress)) {
                const std::size_t offset=section.PointerToRawData+(rva-section.VirtualAddress);
                if(offset+size<=bytes.size()) return bytes.data()+offset;
            }
        }
        return nullptr;
    };
    const auto directory=nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    const auto* exports=reinterpret_cast<const IMAGE_EXPORT_DIRECTORY*>(address(directory.VirtualAddress,sizeof(IMAGE_EXPORT_DIRECTORY)));
    if(!exports) return false;
    const auto* names_rva=reinterpret_cast<const u32*>(address(exports->AddressOfNames,exports->NumberOfNames*4));
    const auto* ordinals=reinterpret_cast<const WORD*>(address(exports->AddressOfNameOrdinals,exports->NumberOfNames*2));
    const auto* functions=reinterpret_cast<const u32*>(address(exports->AddressOfFunctions,exports->NumberOfFunctions*4));
    if(!names_rva || !ordinals || !functions) return false;
    for(u32 i=0;i<exports->NumberOfNames;++i) {
        const auto* name=address(names_rva[i],23);
        if(!name || std::memcmp(name,"uwcn_module_descriptor",23)!=0 || ordinals[i]>=exports->NumberOfFunctions) continue;
        const auto* description=reinterpret_cast<const ModuleDescriptor*>(address(functions[ordinals[i]],sizeof(ModuleDescriptor)));
        return description && description->magic==kDescriptorMagic && description->abi==kHostAbi && description->module_id==id && description->machine==IMAGE_FILE_MACHINE_I386 && description->state_schema==1;
    }
    return false;
}
static std::string manifest_value(const std::string& manifest,const std::string& key) {
    const auto name=manifest.find("\""+key+"\"");
    if(name==std::string::npos) return {};
    const auto colon=manifest.find(':',name+key.size()+2);
    if(colon==std::string::npos) return {};
    const auto first=manifest.find_first_not_of(" \r\n\t",colon+1);
    if(first==std::string::npos || manifest[first]!='\"') return {};
    const auto last=manifest.find('\"',first+1);
    return last==std::string::npos ? std::string{} : manifest.substr(first+1,last-first-1);
}
static bool load_module(u32 index,bool restore) {
    const std::wstring path=module_path(package_path,index);
    const std::wstring release_path=package_path+L"\\release.json";
    ReadPin module_pin(path),manifest_pin(release_path);
    if(module_pin.file==INVALID_HANDLE_VALUE || manifest_pin.file==INVALID_HANDLE_VALUE) { error_text=L"Cannot pin formal module and release manifest: "+path; return false; }
    std::vector<std::uint8_t> bytes;
    if(!read_bytes(path,bytes) || !inspect_module(bytes,index+1)) { error_text=L"Invalid x86 module descriptor: "+path; return false; }
    std::vector<std::uint8_t> manifest_bytes;
    if(!read_bytes(release_path,manifest_bytes)) { error_text=L"Cannot read formal release manifest."; return false; }
    const std::string manifest(manifest_bytes.begin(),manifest_bytes.end());
    const std::string name(names[index],names[index]+std::wcslen(names[index]));
    const std::string identity=manifest_value(manifest,"modules/uwcn_"+name+".dll");
    const auto digest=hash_bytes(bytes);
    if(manifest_value(manifest,"format")!="uwcn-release-v1" || identity.size()!=64 || std::wstring(identity.begin(),identity.end())!=digest) { error_text=L"Formal module hash differs from release manifest: "+path; return false; }
    auto& module=modules[index];
    module.image=LoadLibraryExW(path.c_str(),nullptr,LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR|LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
    if(!module.image) { error_text=L"LoadLibrary failed: "+path; return false; }
    const auto get=reinterpret_cast<GetModuleApi>(GetProcAddress(module.image,"uwcn_get_module_api"));
    module.table=get ? get() : nullptr;
    if(!module.table || module.table->size!=sizeof(ModuleApi) || module.table->abi!=kHostAbi || static_cast<u32>(module.table->id)!=index+1) {
        error_text=L"Invalid module function table: "+path; module.table=nullptr; FreeLibrary(module.image); module.image=nullptr; return false;
    }
    if(module.table->initialize(&api)!=Status::ok) {
        error_text=L"Module initialization failed: "+path; module.table->shutdown(); module.table=nullptr; FreeLibrary(module.image); module.image=nullptr; return false;
    }
    if(restore && !module.state.empty() && module.table->restore_state(module.state.data(),static_cast<u32>(module.state.size()))!=Status::ok) {
        error_text=L"Module state restoration failed: "+path; module.table->shutdown(); module.table=nullptr; FreeLibrary(module.image); module.image=nullptr; return false;
    }
    return true;
}
bool initialize_modules() {
    for(u32 i=0;i<modules.size();++i) if(!load_module(i,false)) { log(error_text.c_str()); return false; }
    return true;
}
static void release_candidates() { for(HANDLE file:candidate_files) CloseHandle(file); candidate_files.clear(); candidate_identity.clear(); }
static std::wstring wide(const std::string& value);
static bool prepare_transaction() {
    std::ifstream listing(std::filesystem::path(stage_path+L"\\candidate-files.tsv"),std::ios::binary);
    std::string line;
    if(!std::getline(listing,line)) { error_text=L"Missing candidate file manifest."; return false; }
    if(!line.empty() && line.back()=='\r') line.pop_back();
    if(line!="UWCN_CANDIDATE_V1") { error_text=L"Invalid candidate file manifest."; return false; }
    while(std::getline(listing,line)) {
        if(!line.empty() && line.back()=='\r') line.pop_back();
        const auto tab=line.find('\t');
        if(tab!=64) { error_text=L"Invalid candidate identity line."; return false; }
        CandidateFile identity{wide(line.substr(tab+1)),wide(line.substr(0,tab))};
        if(identity.relative.empty() || identity.relative.find(L"..")!=std::wstring::npos || std::filesystem::path(identity.relative).has_root_path()) { error_text=L"Invalid candidate relative path."; return false; }
        const auto path=(std::filesystem::path(stage_path)/identity.relative).wstring();
        HANDLE file=CreateFileW(path.c_str(),GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
        if(file==INVALID_HANDLE_VALUE) { error_text=L"Cannot pin candidate: "+path; return false; }
        candidate_files.push_back(file);
        std::vector<std::uint8_t> bytes;
        if(!read_bytes(path,bytes) || hash_bytes(bytes)!=identity.hash) { error_text=L"Candidate file identity mismatch: "+path; return false; }
        candidate_identity.push_back(std::move(identity));
    }
    for(u32 i=0;i<modules.size();++i) if(change_mask&(1u<<i)) {
        const auto path=module_path(stage_path,i);
        const std::wstring relative=L"modules/uwcn_"+std::wstring(names[i])+L".dll";
        bool listed=false;
        for(const auto& identity:candidate_identity) if(identity.relative==relative) listed=true;
        if(!listed) { error_text=L"Selected module absent from candidate file manifest."; return false; }
        std::vector<std::uint8_t> bytes;
        if(!read_bytes(path,bytes) || !inspect_module(bytes,i+1)) { error_text=L"Invalid candidate descriptor: "+path; return false; }
        candidate_hash[i]=hash_bytes(bytes);
        if(candidate_hash[i].empty()) { error_text=L"Candidate hashing failed."; return false; }
    }
    for(u32 i=0;i<modules.size();++i) if(change_mask&(1u<<i)) {
        auto& module=modules[i]; u32 size=0;
        if(!module.table) continue; // A cancelled transaction retains its saved state.
        const Status sizing=module.table->save_state(nullptr,&size);
        if(sizing!=Status::ok && sizing!=Status::insufficient_buffer) { error_text=L"State sizing failed."; return false; }
        module.state.resize(size);
        if(size && module.table->save_state(module.state.data(),&size)!=Status::ok) { error_text=L"State save failed."; return false; }
    }
    enabled=false;
    for(int i=5;i>=0;--i) if(change_mask&(1u<<i)) {
        auto& module=modules[static_cast<std::size_t>(i)];
        if(!module.image) continue;
        module.table->shutdown(); module.table=nullptr;
        if(!FreeLibrary(module.image)) { error_text=L"FreeLibrary failed; module remains disabled."; return false; }
        module.image=nullptr;
    }
    return true;
}
static bool commit_transaction() {
    for(const auto& identity:candidate_identity) {
        std::vector<std::uint8_t> bytes;
        if(!read_bytes((std::filesystem::path(package_path)/identity.relative).wstring(),bytes) || hash_bytes(bytes)!=identity.hash) { error_text=L"Published file differs from candidate: "+identity.relative; return false; }
    }
    for(u32 i=0;i<modules.size();++i) if(change_mask&(1u<<i)) {
        std::vector<std::uint8_t> bytes;
        if(!read_bytes(module_path(package_path,i),bytes) || hash_bytes(bytes)!=candidate_hash[i] || !inspect_module(bytes,i+1)) { error_text=L"Published module differs from pinned candidate."; return false; }
    }
    // Initialization occurs with the gate held. Only the initialized providers
    // are callable; no native callback can observe a partially loaded group.
    enabled=true;
    for(u32 i=0;i<modules.size();++i) if(change_mask&(1u<<i)) {
        if(!load_module(i,true)) { enabled=false; return false; }
        ++modules[i].generation;
    }
    for(u32 i=0;i<modules.size();++i) {
        u32 capacity=0;
        if(invoke(static_cast<ModuleId>(i+1),kModuleDependenciesChanged,&change_mask,sizeof(change_mask),nullptr,&capacity)!=Status::ok) {
            enabled=false; error_text=L"Module dependency refresh failed: "+std::wstring(names[i]); return false;
        }
    }
    return true;
}
void service_control() {
    if(GetCurrentThreadId()!=game_thread) return;
    std::unique_lock<std::recursive_mutex> lock(gate,std::try_to_lock);
    if(!lock.owns_lock() || active_calls!=0) return;
    {
        std::lock_guard<std::mutex> control(control_lock);
        if(phase!=TransactionPhase::prepare_requested) return;
    }
    const bool prepared=prepare_transaction();
    {
        std::lock_guard<std::mutex> control(control_lock);
        phase=prepared ? TransactionPhase::ready : TransactionPhase::failed;
        if(!prepared) release_candidates();
        SetEvent(control_done);
    }
    if(!prepared) return;
    // No game or business frame advances while formal files are being replaced.
    for(;;) {
        bool commit=false,cancel=false;
        { std::lock_guard<std::mutex> control(control_lock); commit=phase==TransactionPhase::commit_requested; cancel=phase==TransactionPhase::abort_requested; }
        if(cancel) {
            std::lock_guard<std::mutex> control(control_lock);
            release_candidates(); phase=TransactionPhase::cancelled; SetEvent(control_done); log(L"Publication cancelled; retired modules remain disabled, saved state retained."); return;
        }
        if(commit) break;
        Sleep(10);
    }
    const bool committed=commit_transaction();
    {
        std::lock_guard<std::mutex> control(control_lock);
        phase=committed ? TransactionPhase::applied : TransactionPhase::failed;
        release_candidates(); SetEvent(control_done);
    }
    log(committed ? L"Compatible module transaction applied." : error_text.c_str());
}

static std::string utf8(const std::wstring& value) {
    const int size=WideCharToMultiByte(CP_UTF8,0,value.data(),static_cast<int>(value.size()),nullptr,0,nullptr,nullptr);
    std::string result(static_cast<std::size_t>(size),0); WideCharToMultiByte(CP_UTF8,0,value.data(),static_cast<int>(value.size()),result.data(),size,nullptr,nullptr); return result;
}
static std::wstring wide(const std::string& value) {
    const int size=MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,value.data(),static_cast<int>(value.size()),nullptr,0);
    std::wstring result(static_cast<std::size_t>(size),0); MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,value.data(),static_cast<int>(value.size()),result.data(),size); return result;
}
static DWORD WINAPI control_thread(void*) {
    const std::wstring pipe_name=L"\\\\.\\pipe\\uwcn-"+std::to_wstring(GetCurrentProcessId());
    for(;;) {
        HANDLE pipe=CreateNamedPipeW(pipe_name.c_str(),PIPE_ACCESS_DUPLEX,PIPE_TYPE_BYTE|PIPE_READMODE_BYTE|PIPE_WAIT|PIPE_REJECT_REMOTE_CLIENTS,1,8192,8192,0,nullptr);
        if(pipe==INVALID_HANDLE_VALUE) return 0;
        if(!ConnectNamedPipe(pipe,nullptr) && GetLastError()!=ERROR_PIPE_CONNECTED) { CloseHandle(pipe); continue; }
        std::string line; char character=0; DWORD count=0;
        while(ReadFile(pipe,&character,1,&count,nullptr) && count==1 && character!='\n' && line.size()<8192) if(character!='\r') line.push_back(character);
        std::wistringstream input(wide(line)); std::wstring command,id; input>>command>>id;
        bool wait=false; std::wstring response;
        {
            std::lock_guard<std::mutex> control(control_lock);
            if(command==L"PREPARE" && (phase==TransactionPhase::idle || phase==TransactionPhase::applied ||
                                      phase==TransactionPhase::cancelled || phase==TransactionPhase::failed)) {
                u32 mask=0; input>>mask; std::wstring path; std::getline(input,path); if(!path.empty() && path[0]==L' ') path.erase(0,1);
                if(mask==0 || mask>63 || path.empty()) response=L"Failed invalid request";
                else { transaction=id; change_mask=mask; stage_path=path; error_text.clear(); ResetEvent(control_done); phase=TransactionPhase::prepare_requested; wait=true; }
            } else if(command==L"COMMIT" && id==transaction && phase==TransactionPhase::ready) {
                ResetEvent(control_done); phase=TransactionPhase::commit_requested; wait=true;
            } else if(command==L"ABORT" && id==transaction && phase==TransactionPhase::ready) {
                ResetEvent(control_done); phase=TransactionPhase::abort_requested; wait=true;
            } else response=L"Failed transaction state mismatch";
        }
        if(wait) {
            WaitForSingleObject(control_done,INFINITE);
            std::lock_guard<std::mutex> control(control_lock);
            if(phase==TransactionPhase::ready) response=L"ReadyToPublish "+transaction;
            else if(phase==TransactionPhase::cancelled) response=L"Cancelled "+transaction+L" Disabled";
            else if(phase==TransactionPhase::applied) {
                response=L"Applied "+transaction;
                for(u32 i=0;i<modules.size();++i) if(change_mask&(1u<<i)) response+=L" "+std::wstring(names[i])+L":"+candidate_hash[i]+L":"+std::to_wstring(modules[i].generation);
            } else response=L"Failed "+error_text;
        }
        const std::string bytes=utf8(response)+"\n"; WriteFile(pipe,bytes.data(),static_cast<DWORD>(bytes.size()),&count,nullptr); FlushFileBuffers(pipe); DisconnectNamedPipe(pipe); CloseHandle(pipe);
    }
}
void start_control_server() { control_done=CreateEventW(nullptr,TRUE,FALSE,nullptr); HANDLE thread=CreateThread(nullptr,0,control_thread,nullptr,0,nullptr); if(thread) CloseHandle(thread); }
}

extern "C" __declspec(dllexport) DWORD WINAPI uwcn_initialize(void* main_thread) {
    using namespace uwcn::host;
    wchar_t path[32768]{}; GetModuleFileNameW(self,path,32768);
    package_path=std::filesystem::path(path).parent_path().wstring();
    game_thread=static_cast<DWORD>(reinterpret_cast<std::uintptr_t>(main_thread));
    api={sizeof(uwcn::HostApi),uwcn::kHostAbi,reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr)),package_path.c_str(),invoke,install_hooks,allocate,release,log,native_fragment};
    if(!initialize_modules() || !install_control_imports()) return 0;
    start_control_server(); log(L"UWCn reconstruction ABI 1 initialized."); return 1;
}
BOOL WINAPI DllMain(HINSTANCE instance,DWORD reason,LPVOID) { if(reason==DLL_PROCESS_ATTACH) { uwcn::host::self=instance; DisableThreadLibraryCalls(instance); } return TRUE; }
