#pragma once
#include "../../sdk/host_abi.h"
#include "../../sdk/text_services.h"

namespace urwcn {
Status translate_hud(const HostApi*,const TextRequest&,void*,u32*);
}
