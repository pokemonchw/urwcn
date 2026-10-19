#pragma once
#include "sdk/host_abi.h"
#include <filesystem>
namespace uwcn::linux_host {
ModuleDescriptor inspect_module(const std::filesystem::path&,u32 id);
}
