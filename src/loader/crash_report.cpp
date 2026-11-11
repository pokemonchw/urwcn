#include "crash_report.h"
#include <dbghelp.h>
#include <cstring>
#include <cwchar>
#include <iterator>

namespace urwcn::host::crash_report {
namespace {
constexpr u32 native_exception_filter=0xFFFF1000;
constexpr u32 native_cookie_check=0xFFFF1001;
std::wstring directory;
struct EventIdentity {u32 id{},phase{};u64 token{};};
thread_local EventIdentity last_event;

void dump(EXCEPTION_POINTERS* exception) {
    SYSTEMTIME time{};GetSystemTime(&time);
    wchar_t name[96];
    std::swprintf(name,std::size(name),L"\\%04u%02u%02u-%02u%02u%02u-%03u-p%lu-t%lu.dmp",
        time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,
        GetCurrentProcessId(),GetCurrentThreadId());
    const auto path=directory+name;
    HANDLE file=CreateFileW(path.c_str(),GENERIC_WRITE,FILE_SHARE_READ,nullptr,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,nullptr);
    if(file==INVALID_HANDLE_VALUE) {
        log((L"Crash dump creation failed: error="+std::to_wstring(GetLastError())+L" path="+path).c_str());
        return;
    }
    MINIDUMP_EXCEPTION_INFORMATION information{GetCurrentThreadId(),exception,FALSE};
    const bool written=MiniDumpWriteDump(GetCurrentProcess(),GetCurrentProcessId(),file,MiniDumpNormal,
        exception?&information:nullptr,nullptr,nullptr)!=FALSE;
    const auto error=written?ERROR_SUCCESS:GetLastError();
    CloseHandle(file);
    log((L"Crash dump: written="+std::to_wstring(written)+L" error="+std::to_wstring(error)+L" path="+path).c_str());
}

void record(EXCEPTION_POINTERS* exception,const wchar_t* stage) {
    const auto& context=*exception->ContextRecord;
    wchar_t details[512];
    std::swprintf(details,std::size(details),
        L"%ls exception: code=%08lX address=%p EIP=%08lX ESP=%08lX EBP=%08lX "
        L"EAX=%08lX EBX=%08lX ECX=%08lX EDX=%08lX ESI=%08lX EDI=%08lX "
        L"native_id=%lu phase=%lu token=%llu",
        stage,exception->ExceptionRecord->ExceptionCode,exception->ExceptionRecord->ExceptionAddress,
        context.Eip,context.Esp,context.Ebp,context.Eax,context.Ebx,context.Ecx,context.Edx,context.Esi,context.Edi,
        static_cast<unsigned long>(last_event.id),static_cast<unsigned long>(last_event.phase),
        static_cast<unsigned long long>(last_event.token));
    log(details);dump(exception);
}

LONG WINAPI first_chance(EXCEPTION_POINTERS* exception) {
    switch(exception->ExceptionRecord->ExceptionCode) {
    case EXCEPTION_ACCESS_VIOLATION:case EXCEPTION_IN_PAGE_ERROR:
    case EXCEPTION_ILLEGAL_INSTRUCTION:case EXCEPTION_STACK_OVERFLOW:
    case EXCEPTION_NONCONTINUABLE_EXCEPTION:
        record(exception,L"First-chance");break;
    default:break;
    }
    // Observation precedes SEH unwinding. The original exception dispatch,
    // application filters and termination decisions remain in control.
    return EXCEPTION_CONTINUE_SEARCH;
}
}

Status initialize(const std::wstring& package) {
    directory=package+L"\\crashes";
    if(!CreateDirectoryW(directory.c_str(),nullptr) && GetLastError()!=ERROR_ALREADY_EXISTS) return Status::failed;
    // Read the admitted PE's actual import metadata, as the resident SDL
    // control bridge does. 3.89.1's explicit CRT failure calls use 18C040.
    const auto base=api.image_base;
    const auto* dos=reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
    const auto* nt=reinterpret_cast<const IMAGE_NT_HEADERS32*>(base+dos->e_lfanew);
    const auto* imports=reinterpret_cast<const IMAGE_IMPORT_DESCRIPTOR*>(base+
        nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
    for(;imports->Name;++imports) {
        if(_stricmp(reinterpret_cast<const char*>(base+imports->Name),"KERNEL32.dll")!=0) continue;
        auto* source=reinterpret_cast<const IMAGE_THUNK_DATA32*>(base+imports->OriginalFirstThunk);
        auto* target=reinterpret_cast<const IMAGE_THUNK_DATA32*>(base+imports->FirstThunk);
        for(;source->u1.AddressOfData;++source,++target) {
            if(IMAGE_SNAP_BY_ORDINAL32(source->u1.Ordinal)) continue;
            const auto* entry=reinterpret_cast<const IMAGE_IMPORT_BY_NAME*>(base+source->u1.AddressOfData);
            if(std::strcmp(reinterpret_cast<const char*>(entry->Name),"UnhandledExceptionFilter")!=0) continue;
            HookSpec hook{native_exception_filter,HookKind::import_slot,
                static_cast<u32>(reinterpret_cast<std::uintptr_t>(target)-base),0,1,4,{}};
            std::memcpy(hook.expected,&target->u1.Function,4);
            // 18A0AE compares the caller's ECX cookie with the original
            // process cookie; its mismatch branch can execute INT 29h and
            // bypass every in-process exception handler. Observe that exact
            // comparison without skipping or changing it.
            HookSpec cookie{native_cookie_check,HookKind::inline_code,0x18A0AE,0,0,6,{0x3B,0x0D}};
            const auto cookie_address=static_cast<u32>(base+0x1E200C);
            std::memcpy(cookie.expected+2,&cookie_address,4);
            const HookSpec hooks[]{hook,cookie};
            const auto status=install_hooks(hooks,2);
            if(status!=Status::ok) return status;
            return AddVectoredExceptionHandler(1,first_chance)?Status::ok:Status::failed;
        }
    }
    return Status::unavailable;
}

void native_event(const NativeEvent& event) {
    last_event={event.id,static_cast<u32>(event.phase),event.token};
}

bool dispatch(const NativeEvent& event) {
    if(event.id==native_cookie_check) {
        const auto cookie=*reinterpret_cast<const u32*>(api.image_base+0x1E200C);
        if(event.frame->ecx!=cookie) {
            wchar_t details[512];
            const auto& frame=*event.frame;
            const auto caller=*reinterpret_cast<const u32*>(static_cast<std::uintptr_t>(frame.esp));
            std::swprintf(details,std::size(details),
                L"Native cookie mismatch: return=%08lX ESP=%08lX EBP=%08lX "
                L"EAX=%08lX EBX=%08lX ECX=%08lX EDX=%08lX ESI=%08lX EDI=%08lX "
                L"native_id=%lu phase=%lu token=%llu",
                static_cast<unsigned long>(caller),static_cast<unsigned long>(frame.esp),static_cast<unsigned long>(frame.ebp),
                static_cast<unsigned long>(frame.eax),static_cast<unsigned long>(frame.ebx),static_cast<unsigned long>(frame.ecx),
                static_cast<unsigned long>(frame.edx),static_cast<unsigned long>(frame.esi),static_cast<unsigned long>(frame.edi),
                static_cast<unsigned long>(last_event.id),static_cast<unsigned long>(last_event.phase),
                static_cast<unsigned long long>(last_event.token));
            log(details);dump(nullptr);
        }
        return true;
    }
    if(event.id!=native_exception_filter) return false;
    // The game's CRT explicitly clears its top-level filter before calling
    // this imported function (18A0C4/18A0CD and 18AB67/18AB71). Observe the
    // real EXCEPTION_POINTERS argument before the unchanged original call.
    if(event.phase==NativePhase::before)
        record(reinterpret_cast<EXCEPTION_POINTERS*>(static_cast<std::uintptr_t>(event.arguments[0])),L"CRT filter");
    return true;
}
}
