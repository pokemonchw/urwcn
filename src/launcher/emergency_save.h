#pragma once
#include <windows.h>
#include <cstdint>
#include <filesystem>
#include <ostream>
#include <string>

namespace urwcn::launcher {
// The caller holds an outstanding debug event: every game thread is stopped.
// This serializer reads remote data and writes files; it never executes game
// code, resumes a thread, or modifies the crashed process's memory.
bool emergency_save(HANDLE process,std::uintptr_t image_base,
    const std::wstring& game_hash,const std::filesystem::path& game_directory,
    const std::filesystem::path& project_root,const std::filesystem::path& incident,
    std::ostream& report);
}
