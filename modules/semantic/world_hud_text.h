#pragma once
#include "sdk/host_abi.h"
#include "sdk/text_services.h"

namespace uwcn {
Status translate_world_hud(const HostApi* host,const TextRequest& request,void* output,u32* capacity);
}
