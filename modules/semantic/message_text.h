#pragma once
#include "sdk/host_abi.h"
#include "sdk/text_services.h"

uwcn::Status translate_message(const uwcn::HostApi*,const uwcn::TextRequest&,
                              void*,uwcn::u32*);
