#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <shellapi.h>
#include <tlhelp32.h>
#include <bcrypt.h>
#include <array>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <cstdint>

static constexpr wchar_t expected_hash[]=L"e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9";
static std::wstring sha256(const std::wstring& path) {
    std::ifstream file(std::filesystem::path(path),std::ios::binary);
    if(!file) return {};
    BCRYPT_ALG_HANDLE algorithm=nullptr; BCRYPT_HASH_HANDLE hash=nullptr; DWORD size=0,written=0;
    if(BCryptOpenAlgorithmProvider(&algorithm,BCRYPT_SHA256_ALGORITHM,nullptr,0)<0) return {};
    BCryptGetProperty(algorithm,BCRYPT_OBJECT_LENGTH,reinterpret_cast<PUCHAR>(&size),sizeof(size),&written,0);
    std::vector<unsigned char> object(size); std::array<unsigned char,65536> bytes{}; std::array<unsigned char,32> digest{};
    bool ok=BCryptCreateHash(algorithm,&hash,object.data(),size,nullptr,0,0)>=0;
    while(ok && file) { file.read(reinterpret_cast<char*>(bytes.data()),bytes.size()); const auto count=file.gcount(); if(count>0) ok=BCryptHashData(hash,bytes.data(),static_cast<ULONG>(count),0)>=0; }
    if(ok) ok=BCryptFinishHash(hash,digest.data(),digest.size(),0)>=0;
    if(hash) BCryptDestroyHash(hash);
    BCryptCloseAlgorithmProvider(algorithm,0);
    if(!ok) return {};
    std::wstring result; constexpr wchar_t alphabet[]=L"0123456789abcdef";
    for(auto byte:digest) { result.push_back(alphabet[byte>>4]); result.push_back(alphabet[byte&15]); } return result;
}
static DWORD entry_rva(const std::wstring& path) {
    std::ifstream file(std::filesystem::path(path),std::ios::binary);
    IMAGE_DOS_HEADER dos{}; IMAGE_NT_HEADERS32 nt{};
    if(!file.read(reinterpret_cast<char*>(&dos),sizeof(dos)) || dos.e_magic!=IMAGE_DOS_SIGNATURE || dos.e_lfanew<0) return 0;
    file.seekg(dos.e_lfanew);
    if(!file.read(reinterpret_cast<char*>(&nt),sizeof(nt)) || nt.Signature!=IMAGE_NT_SIGNATURE || nt.FileHeader.Machine!=IMAGE_FILE_MACHINE_I386 || nt.OptionalHeader.Magic!=IMAGE_NT_OPTIONAL_HDR32_MAGIC) return 0;
    return nt.OptionalHeader.AddressOfEntryPoint;
}
static bool write_code(HANDLE process,void* address,const void* data,SIZE_T bytes) {
    DWORD previous=0,ignored=0; SIZE_T written=0;
    if(!VirtualProtectEx(process,address,bytes,PAGE_EXECUTE_READWRITE,&previous)) return false;
    const bool ok=WriteProcessMemory(process,address,data,bytes,&written) && written==bytes && FlushInstructionCache(process,address,bytes);
    const bool restored=VirtualProtectEx(process,address,bytes,previous,&ignored)!=0;
    return ok && restored;
}
static bool stop_at_initialized_entry(const PROCESS_INFORMATION& process,DWORD entry_offset) {
    // CREATE_PROCESS is delivered before user-mode execution. Arm the exact PE
    // entry, let Windows initialize its imports, then hold the entry instruction.
    // The loader's earlier system breakpoint is not the initialization boundary.
    std::uintptr_t entry=0; unsigned char original=0; bool initial_break=false;
    if(ResumeThread(process.hThread)==static_cast<DWORD>(-1)) return false;
    for(;;) {
        DEBUG_EVENT event{};
        if(!WaitForDebugEvent(&event,INFINITE)) return false;
        DWORD continuation=DBG_CONTINUE;
        if(event.dwDebugEventCode==CREATE_PROCESS_DEBUG_EVENT) {
            entry=reinterpret_cast<std::uintptr_t>(event.u.CreateProcessInfo.lpBaseOfImage)+entry_offset;
            SIZE_T bytes=0;
            const bool read=ReadProcessMemory(process.hProcess,reinterpret_cast<void*>(entry),&original,1,&bytes) && bytes==1;
            if(event.u.CreateProcessInfo.hFile) CloseHandle(event.u.CreateProcessInfo.hFile);
            const unsigned char breakpoint=0xcc;
            if(!read || !write_code(process.hProcess,reinterpret_cast<void*>(entry),&breakpoint,1)) return false;
        } else if(event.dwDebugEventCode==LOAD_DLL_DEBUG_EVENT) {
            if(event.u.LoadDll.hFile) CloseHandle(event.u.LoadDll.hFile);
        } else if(event.dwDebugEventCode==EXCEPTION_DEBUG_EVENT) {
            const auto& exception=event.u.Exception.ExceptionRecord;
            if(exception.ExceptionCode==EXCEPTION_BREAKPOINT && reinterpret_cast<std::uintptr_t>(exception.ExceptionAddress)==entry && event.dwThreadId==process.dwThreadId) {
                CONTEXT context{}; context.ContextFlags=CONTEXT_CONTROL;
                if(!GetThreadContext(process.hThread,&context) || !write_code(process.hProcess,reinterpret_cast<void*>(entry),&original,1)) return false;
                context.Eip=static_cast<DWORD>(entry);
                if(!SetThreadContext(process.hThread,&context) || SuspendThread(process.hThread)==static_cast<DWORD>(-1)) return false;
                if(!ContinueDebugEvent(event.dwProcessId,event.dwThreadId,DBG_CONTINUE)) return false;
                return DebugActiveProcessStop(process.dwProcessId)!=0;
            }
            if(!initial_break && exception.ExceptionCode==EXCEPTION_BREAKPOINT) initial_break=true;
            else continuation=DBG_EXCEPTION_NOT_HANDLED;
        } else if(event.dwDebugEventCode==EXIT_PROCESS_DEBUG_EVENT) {
            ContinueDebugEvent(event.dwProcessId,event.dwThreadId,DBG_CONTINUE); return false;
        }
        if(!ContinueDebugEvent(event.dwProcessId,event.dwThreadId,continuation)) return false;
    }
}
static std::uintptr_t remote_module(DWORD process_id,const wchar_t* name) {
    HANDLE snapshot=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE|TH32CS_SNAPMODULE32,process_id);
    if(snapshot==INVALID_HANDLE_VALUE) return 0;
    MODULEENTRY32W entry{}; entry.dwSize=sizeof(entry); std::uintptr_t address=0;
    if(Module32FirstW(snapshot,&entry)) do { if(_wcsicmp(entry.szModule,name)==0) { address=reinterpret_cast<std::uintptr_t>(entry.modBaseAddr); break; } } while(Module32NextW(snapshot,&entry));
    CloseHandle(snapshot); return address;
}
static bool remote_call(HANDLE process,std::uintptr_t function,void* argument,DWORD& result) {
    HANDLE thread=CreateRemoteThread(process,nullptr,0,reinterpret_cast<LPTHREAD_START_ROUTINE>(function),argument,0,nullptr);
    if(!thread) return false;
    const bool ok=WaitForSingleObject(thread,INFINITE)==WAIT_OBJECT_0 && GetExitCodeThread(thread,&result);
    CloseHandle(thread); return ok;
}
int WINAPI wWinMain(HINSTANCE,HINSTANCE,PWSTR,int) {
    std::wstring game=L"D:\\program\\steam\\steamapps\\common\\UnRealWorld\\urw.exe";
    int count=0; LPWSTR* arguments=CommandLineToArgvW(GetCommandLineW(),&count);
    if(!arguments) return 1;
    if(count==3 && std::wstring(arguments[1])==L"--game") game=arguments[2];
    else if(count!=1) { LocalFree(arguments); MessageBoxW(nullptr,L"用法：uwcn_launcher.exe [--game 游戏完整路径]",L"UWCn",MB_ICONERROR); return 1; }
    LocalFree(arguments);
    game=std::filesystem::absolute(game).wstring();
    if(sha256(game)!=expected_hash) { MessageBoxW(nullptr,L"游戏文件指纹不符合已确认的 UnReal World 3.89 Steam Build 25939378。未启动游戏。",L"UWCn",MB_ICONERROR); return 1; }
    const DWORD game_entry=entry_rva(game);
    if(!game_entry) { MessageBoxW(nullptr,L"游戏 PE32 入口无效。未启动游戏。",L"UWCn",MB_ICONERROR); return 1; }
    wchar_t own_path[32768]{}; GetModuleFileNameW(nullptr,own_path,32768);
    const std::wstring loader=(std::filesystem::path(own_path).parent_path()/L"package"/L"uwcn_loader.dll").wstring();
    HMODULE mapped=LoadLibraryExW(loader.c_str(),nullptr,DONT_RESOLVE_DLL_REFERENCES);
    if(!mapped) { MessageBoxW(nullptr,L"无法读取正式 package/uwcn_loader.dll。",L"UWCn",MB_ICONERROR); return 1; }
    auto bootstrap=GetProcAddress(mapped,"uwcn_initialize");
    if(!bootstrap) { FreeLibrary(mapped); MessageBoxW(nullptr,L"驻留 DLL 缺少初始化导出。",L"UWCn",MB_ICONERROR); return 1; }
    const auto bootstrap_rva=reinterpret_cast<std::uintptr_t>(bootstrap)-reinterpret_cast<std::uintptr_t>(mapped); FreeLibrary(mapped);
    STARTUPINFOW startup{}; startup.cb=sizeof(startup); PROCESS_INFORMATION process{};
    std::wstring command=L"\""+game+L"\""; const auto directory=std::filesystem::path(game).parent_path().wstring();
    // SDL 2.30 reads this inherited hint in WIN_VideoInit, before the native
    // SDL_CreateWindow call. Keep SDL's pixel coordinates and let the native
    // HD targets use the real output density without Windows bitmap scaling.
    if(!SetEnvironmentVariableW(L"SDL_WINDOWS_DPI_AWARENESS",L"permonitorv2")) {
        MessageBoxW(nullptr,L"无法设置高清显示启动参数。未启动游戏。",L"UWCn",MB_ICONERROR); return 1;
    }
    if(!CreateProcessW(game.c_str(),command.data(),nullptr,nullptr,FALSE,CREATE_SUSPENDED|DEBUG_ONLY_THIS_PROCESS,nullptr,directory.c_str(),&startup,&process)) { MessageBoxW(nullptr,L"无法创建游戏进程。",L"UWCn",MB_ICONERROR); return 1; }
    if(!stop_at_initialized_entry(process,game_entry)) {
        TerminateProcess(process.hProcess,1); DebugActiveProcessStop(process.dwProcessId); CloseHandle(process.hThread); CloseHandle(process.hProcess);
        MessageBoxW(nullptr,L"无法完成 Windows 加载阶段的入口交接。新建进程已结束，游戏入口未被恢复。",L"UWCn",MB_ICONERROR); return 1;
    }
    const auto local_load=GetProcAddress(GetModuleHandleW(L"kernel32.dll"),"LoadLibraryW"); HMODULE owner=nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,reinterpret_cast<LPCWSTR>(local_load),&owner);
    wchar_t owner_path[32768]{}; GetModuleFileNameW(owner,owner_path,32768);
    const auto owner_name=std::filesystem::path(owner_path).filename().wstring();
    const auto remote_owner=remote_module(process.dwProcessId,owner_name.c_str());
    const auto load_address=remote_owner+reinterpret_cast<std::uintptr_t>(local_load)-reinterpret_cast<std::uintptr_t>(owner);
    const SIZE_T bytes=(loader.size()+1)*sizeof(wchar_t);
    void* remote_text=VirtualAllocEx(process.hProcess,nullptr,bytes,MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
    SIZE_T copied=0; DWORD loaded=0,initialized=0;
    bool ok=remote_owner && remote_text && WriteProcessMemory(process.hProcess,remote_text,loader.c_str(),bytes,&copied) && copied==bytes;
    if(ok) ok=remote_call(process.hProcess,load_address,remote_text,loaded) && loaded;
    if(remote_text) VirtualFreeEx(process.hProcess,remote_text,0,MEM_RELEASE);
    if(ok) ok=remote_call(process.hProcess,static_cast<std::uintptr_t>(loaded)+bootstrap_rva,reinterpret_cast<void*>(static_cast<std::uintptr_t>(process.dwThreadId)),initialized) && initialized==1;
    if(ok) ok=ResumeThread(process.hThread)!=static_cast<DWORD>(-1);
    if(!ok) { TerminateProcess(process.hProcess,1); MessageBoxW(nullptr,L"Mod 初始化未完成，新建的挂起进程已结束。请查看 package/uwcn.log。",L"UWCn",MB_ICONERROR); }
    CloseHandle(process.hThread); CloseHandle(process.hProcess); return ok ? 0 : 1;
}
