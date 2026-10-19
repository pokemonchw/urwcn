#pragma once
#include "../../sdk/host_abi.h"
#include <vector>

namespace uwcn::adapter::native_menu_storage {
// MENULIST.SAV is the original game's single native menu storage resource.
// Its real fwrite/fread protocol owns source identity independently of pixel
// caches. Only the statically confirmed header/row calls participate here.
void initialize(std::uintptr_t image_base);
void append_hooks(std::vector<HookSpec>&);
Status dispatch(const NativeEvent&,DispatchResult&,bool& handled);
std::vector<std::uint8_t> save();
void restore(const void* payload);
void shutdown();
}
