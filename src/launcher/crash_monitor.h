#pragma once
#include <windows.h>
#include <cstdint>
#include <filesystem>
#include <map>
#include <string>

namespace urwcn::launcher {
class CrashMonitor {
public:
    CrashMonitor(const PROCESS_INFORMATION&,std::filesystem::path root,
                 std::filesystem::path game,std::wstring game_hash);
    bool initialize();
    DWORD observe(const DEBUG_EVENT&);
    bool remote_call(std::uintptr_t function,void* argument,DWORD& result);
    bool run();
    DWORD exit_code() const {return exit_code_;}
    void log(const std::string&) const;
private:
    void capture(const DEBUG_EVENT&);
    PROCESS_INFORMATION process_;
    std::filesystem::path root_,game_,reports_;
    std::wstring game_hash_;
    std::map<DWORD,HANDLE> threads_;
    std::uintptr_t image_base_{};
    unsigned sequence_{};
    DWORD exit_code_{};
    bool exited_{},captured_{};
};
}
