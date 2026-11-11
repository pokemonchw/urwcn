#include "crash_monitor.h"
#include "emergency_save.h"
#include <dbghelp.h>
#include <tlhelp32.h>
#include <array>
#include <cwchar>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <utility>
#include <vector>

namespace urwcn::launcher {
namespace {
std::string utf8(const std::wstring& value) {
    const auto count=WideCharToMultiByte(CP_UTF8,0,value.data(),static_cast<int>(value.size()),nullptr,0,nullptr,nullptr);
    std::string result(count,0);
    WideCharToMultiByte(CP_UTF8,0,value.data(),static_cast<int>(value.size()),result.data(),count,nullptr,nullptr);
    return result;
}
std::wstring timestamp() {
    SYSTEMTIME now{};GetSystemTime(&now);
    wchar_t text[64];
    std::swprintf(text,std::size(text),L"%04u%02u%02u-%02u%02u%02u-%03u",
        now.wYear,now.wMonth,now.wDay,now.wHour,now.wMinute,now.wSecond,now.wMilliseconds);
    return text;
}
struct Module {DWORD64 base,size;std::wstring name,path;};
std::vector<Module> modules(DWORD pid,std::ostream& report) {
    std::vector<Module> result;
    HANDLE snapshot=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE|TH32CS_SNAPMODULE32,pid);
    if(snapshot==INVALID_HANDLE_VALUE) {report<<"module_snapshot_error="<<GetLastError()<<'\n';return result;}
    MODULEENTRY32W entry{};entry.dwSize=sizeof(entry);
    if(Module32FirstW(snapshot,&entry)) do {
        result.push_back({reinterpret_cast<DWORD64>(entry.modBaseAddr),entry.modBaseSize,entry.szModule,entry.szExePath});
    } while(Module32NextW(snapshot,&entry));
    else report<<"module_enumeration_error="<<GetLastError()<<'\n';
    CloseHandle(snapshot);return result;
}
void address(std::ostream& report,DWORD64 pc,const std::vector<Module>& images) {
    report<<"0x"<<std::hex<<pc<<std::dec;
    for(const auto& image:images) if(pc>=image.base && pc-image.base<image.size) {
        report<<' '<<utf8(image.name)<<"+0x"<<std::hex<<(pc-image.base)<<std::dec;break;
    }
}
void stack(std::ostream& report,HANDLE process,HANDLE thread,CONTEXT context,
           const std::vector<Module>& images,bool symbols) {
    report<<"EIP="<<std::hex<<context.Eip<<" ESP="<<context.Esp<<" EBP="<<context.Ebp
        <<" EAX="<<context.Eax<<" EBX="<<context.Ebx<<" ECX="<<context.Ecx
        <<" EDX="<<context.Edx<<" ESI="<<context.Esi<<" EDI="<<context.Edi
        <<" EFLAGS="<<context.EFlags<<std::dec<<'\n';
    report<<"fault/current PC: ";address(report,context.Eip,images);report<<'\n';
    if(!symbols) return;
    STACKFRAME64 frame{};
    frame.AddrPC={context.Eip,0,AddrModeFlat};
    frame.AddrFrame={context.Ebp,0,AddrModeFlat};
    frame.AddrStack={context.Esp,0,AddrModeFlat};
    DWORD64 previous_pc=0,previous_sp=0;
    for(unsigned index=0;index<256;++index) {
        if(!StackWalk64(IMAGE_FILE_MACHINE_I386,process,thread,&frame,&context,nullptr,
                       SymFunctionTableAccess64,SymGetModuleBase64,nullptr)) {
            report<<"stack_walk_end=unwind_stopped\n";break;
        }
        if(!frame.AddrPC.Offset) {report<<"stack_walk_end=null_pc\n";break;}
        if(frame.AddrPC.Offset==previous_pc && frame.AddrStack.Offset==previous_sp) {
            report<<"stack_walk_end=repeated_frame\n";break;
        }
        previous_pc=frame.AddrPC.Offset;previous_sp=frame.AddrStack.Offset;
        report<<'#'<<index<<' ';address(report,frame.AddrPC.Offset,images);
        alignas(SYMBOL_INFO) std::array<unsigned char,sizeof(SYMBOL_INFO)+MAX_SYM_NAME> storage{};
        auto* symbol=reinterpret_cast<SYMBOL_INFO*>(storage.data());
        symbol->SizeOfStruct=sizeof(SYMBOL_INFO);symbol->MaxNameLen=MAX_SYM_NAME;
        DWORD64 displacement=0;
        if(SymFromAddr(process,frame.AddrPC.Offset,&displacement,symbol))
            report<<' '<<symbol->Name<<"+0x"<<std::hex<<displacement<<std::dec;
        report<<" SP=0x"<<std::hex<<frame.AddrStack.Offset<<std::dec<<'\n';
        if(index==255) report<<"stack_walk_end=256_frame_limit\n";
    }
}
}
CrashMonitor::CrashMonitor(const PROCESS_INFORMATION& process,std::filesystem::path root,
    std::filesystem::path game,std::wstring hash):process_(process),root_(std::move(root)),
    game_(std::move(game)),reports_(root_/L"package"/L"crashes"),game_hash_(std::move(hash)) {}
void CrashMonitor::log(const std::string& text) const {
    const auto line=utf8(timestamp())+" UTC pid="+std::to_string(process_.dwProcessId)+" "+text+"\n";
    HANDLE file=CreateFileW((root_/L"package"/L"launcher.log").c_str(),FILE_APPEND_DATA,
        FILE_SHARE_READ|FILE_SHARE_WRITE,nullptr,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);
    if(file!=INVALID_HANDLE_VALUE) {
        DWORD written=0;WriteFile(file,line.data(),static_cast<DWORD>(line.size()),&written,nullptr);CloseHandle(file);
    }
}
bool CrashMonitor::initialize() {
    std::error_code error;std::filesystem::create_directories(reports_,error);
    if(error) return false;
    if(!DebugSetProcessKillOnExit(FALSE)) return false;
    log("external crash monitor attached; game_sha256="+utf8(game_hash_));return true;
}
DWORD CrashMonitor::observe(const DEBUG_EVENT& event) {
    switch(event.dwDebugEventCode) {
    case CREATE_PROCESS_DEBUG_EVENT:
        image_base_=reinterpret_cast<std::uintptr_t>(event.u.CreateProcessInfo.lpBaseOfImage);
        threads_[event.dwThreadId]=event.u.CreateProcessInfo.hThread;
        if(event.u.CreateProcessInfo.hFile) CloseHandle(event.u.CreateProcessInfo.hFile);
        break;
    case CREATE_THREAD_DEBUG_EVENT:threads_[event.dwThreadId]=event.u.CreateThread.hThread;break;
    case EXIT_THREAD_DEBUG_EVENT:threads_.erase(event.dwThreadId);break;
    case LOAD_DLL_DEBUG_EVENT:if(event.u.LoadDll.hFile) CloseHandle(event.u.LoadDll.hFile);break;
    case EXCEPTION_DEBUG_EVENT:
        // First chance belongs to the application's own VEH/SEH. The
        // debugger sees unhandled exceptions and fast-fail before destruction.
        if(!event.u.Exception.dwFirstChance) capture(event);
        return DBG_EXCEPTION_NOT_HANDLED;
    case EXIT_PROCESS_DEBUG_EVENT:
        exited_=true;
        exit_code_=event.u.ExitProcess.dwExitCode;
        log("process exited; code="+std::to_string(event.u.ExitProcess.dwExitCode)+
            " exception_captured="+std::to_string(captured_));
        if(!captured_ && event.u.ExitProcess.dwExitCode)
            log("No unhandled exception event preceded exit; no live crash context or emergency save is available at this exit event.");
        break;
    default:break;
    }
    return DBG_CONTINUE;
}
bool CrashMonitor::remote_call(std::uintptr_t function,void* argument,DWORD& result) {
    DWORD tid=0;
    HANDLE thread=CreateRemoteThread(process_.hProcess,nullptr,0,
        reinterpret_cast<LPTHREAD_START_ROUTINE>(function),argument,0,&tid);
    if(!thread) return false;
    bool finished=false,ok=true;
    while(!finished && !exited_) {
        DEBUG_EVENT event{};
        if(!WaitForDebugEvent(&event,INFINITE)) {ok=false;break;}
        const auto continuation=observe(event);
        finished=event.dwDebugEventCode==EXIT_THREAD_DEBUG_EVENT && event.dwThreadId==tid;
        if(finished) result=event.u.ExitThread.dwExitCode;
        if(!ContinueDebugEvent(event.dwProcessId,event.dwThreadId,continuation)) {ok=false;break;}
    }
    CloseHandle(thread);return ok && finished && !exited_;
}
bool CrashMonitor::run() {
    log("game entry resumed; monitoring until process exit");
    while(!exited_) {
        DEBUG_EVENT event{};
        if(!WaitForDebugEvent(&event,INFINITE)) {log("WaitForDebugEvent failed: "+std::to_string(GetLastError()));return false;}
        const auto continuation=observe(event);
        if(!ContinueDebugEvent(event.dwProcessId,event.dwThreadId,continuation)) {
            log("ContinueDebugEvent failed: "+std::to_string(GetLastError()));return false;
        }
    }
    return true;
}
void CrashMonitor::capture(const DEBUG_EVENT& event) {
    captured_=true;
    const auto incident=reports_/(timestamp()+L"-p"+std::to_wstring(event.dwProcessId)+
        L"-t"+std::to_wstring(event.dwThreadId)+L"-"+std::to_wstring(++sequence_));
    std::error_code error;
    if(!std::filesystem::create_directory(incident,error)) {
        log("Cannot create incident directory: "+std::to_string(error.value()));return;
    }
    std::ofstream report(incident/L"report.txt",std::ios::binary);
    const auto& exception=event.u.Exception.ExceptionRecord;
    report<<"URWCN external crash report\ntime_utc="<<utf8(timestamp())<<"\ngame="<<utf8(game_.wstring())
        <<"\ngame_sha256="<<utf8(game_hash_)<<"\npid="<<event.dwProcessId<<" tid="<<event.dwThreadId
        <<"\nexception_code=0x"<<std::hex<<exception.ExceptionCode<<" flags=0x"<<exception.ExceptionFlags
        <<" address=0x"<<reinterpret_cast<std::uintptr_t>(exception.ExceptionAddress)<<std::dec<<'\n';
    for(DWORD index=0;index<exception.NumberParameters;++index)
        report<<"exception_parameter["<<index<<"]=0x"<<std::hex<<exception.ExceptionInformation[index]<<std::dec<<'\n';
    const auto fault=threads_.find(event.dwThreadId);
    CONTEXT context{};context.ContextFlags=CONTEXT_ALL;
    const bool have_context=fault!=threads_.end() && GetThreadContext(fault->second,&context);
    if(!have_context) report<<"fault_context_error="<<GetLastError()<<'\n';
    EXCEPTION_RECORD record=exception;
    EXCEPTION_POINTERS pointers{&record,&context};
    MINIDUMP_EXCEPTION_INFORMATION information{event.dwThreadId,&pointers,FALSE};
    HANDLE dump=CreateFileW((incident/L"process.dmp").c_str(),GENERIC_WRITE,FILE_SHARE_READ,nullptr,
                           CREATE_NEW,FILE_ATTRIBUTE_NORMAL,nullptr);
    bool dumped=false;
    if(dump!=INVALID_HANDLE_VALUE) {
        const auto type=static_cast<MINIDUMP_TYPE>(MiniDumpWithFullMemory|MiniDumpWithFullMemoryInfo|
            MiniDumpWithThreadInfo|MiniDumpWithUnloadedModules);
        dumped=MiniDumpWriteDump(process_.hProcess,process_.dwProcessId,dump,type,
            have_context?&information:nullptr,nullptr,nullptr)!=FALSE;
        if(!dumped) report<<"minidump_error="<<GetLastError()<<'\n';
        if(!FlushFileBuffers(dump)) report<<"minidump_flush_error="<<GetLastError()<<'\n';
        CloseHandle(dump);
    } else report<<"minidump_create_error="<<GetLastError()<<'\n';
    report<<"full_memory_dump_written="<<dumped<<'\n';report.flush();
    const bool saved=emergency_save(process_.hProcess,image_base_,game_hash_,game_.parent_path(),root_,incident,report);
    report<<"emergency_save_committed="<<saved<<'\n';report.flush();
    if(!CopyFileW((root_/L"package"/L"release.json").c_str(),(incident/L"release.json").c_str(),TRUE))
        report<<"release_manifest_copy_error="<<GetLastError()<<'\n';
    const auto images=modules(process_.dwProcessId,report);
    report<<"\nModules (live crash addresses):\n";
    for(const auto& image:images)
        report<<std::hex<<image.base<<" size="<<image.size<<std::dec<<' '<<utf8(image.path)<<'\n';
    SymSetOptions(SYMOPT_UNDNAME|SYMOPT_DEFERRED_LOADS|SYMOPT_FAIL_CRITICAL_ERRORS|SYMOPT_NO_PROMPTS);
    const bool symbols=SymInitialize(process_.hProcess,nullptr,TRUE)!=FALSE;
    if(!symbols) report<<"symbol_initialize_error="<<GetLastError()<<'\n';
    for(const auto& [tid,thread]:threads_) {
        report<<"\nThread "<<tid<<(tid==event.dwThreadId?" (faulting)":"")<<'\n';
        CONTEXT current{};current.ContextFlags=CONTEXT_ALL;
        if(tid==event.dwThreadId && have_context) current=context;
        else if(!GetThreadContext(thread,&current)) {report<<"context_error="<<GetLastError()<<'\n';continue;}
        stack(report,process_.hProcess,thread,current,images,symbols);
    }
    if(symbols) SymCleanup(process_.hProcess);
    report.flush();
    log("incident="+utf8(incident.wstring())+" full_memory_dump_written="+std::to_string(dumped)+
        " emergency_save_committed="+std::to_string(saved)+" report_written="+std::to_string(report.good()));
}
}
