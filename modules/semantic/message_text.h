#pragma once
#include "sdk/host_abi.h"
#include "sdk/text_services.h"

urwcn::Status translate_message(const urwcn::HostApi*,const urwcn::TextRequest&,
                              void*,urwcn::u32*);
