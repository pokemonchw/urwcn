#pragma once
#include <string>
namespace uwcn::linux_host {
void start_control();
void stop_control();
void end_control_requests();
std::string control_command(const std::string&);
}
