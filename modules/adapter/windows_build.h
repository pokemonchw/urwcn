#pragma once
#include "../../sdk/host_abi.h"
#include <algorithm>
#include <cstring>
#include <iterator>

namespace urwcn::adapter::windows_build {
// The launcher admits only the two exact PE fingerprints in profiles/.
// Build 26139145's native version getter reads this seven-byte string.
inline bool newer_build{};
inline void initialize(std::uintptr_t image_base) {
    newer_build=std::memcmp(reinterpret_cast<const void*>(image_base+0x1AFAC0),"3.89.1",7)==0;
}
inline bool is_3891() { return newer_build; }

// Entries are individually recovered native data references, not a section-wide
// relocation rule. Legacy addresses remain the semantic IDs used by the catalog.
#include "windows_3891_rdata.inc"
inline u32 rdata_rva(u32 legacy_rva) {
    return newer_build && std::binary_search(std::begin(shifted_rvas),std::end(shifted_rvas),legacy_rva)
        ? legacy_rva+0x10 : legacy_rva;
}
}
