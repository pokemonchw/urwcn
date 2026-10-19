#pragma once
#include <filesystem>
#include <string>

namespace uwcn::linux_host {
inline constexpr char game_sha256[]="4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe";
std::string file_sha256(const std::filesystem::path&);
}
