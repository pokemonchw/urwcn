#include "message_text.h"
#include "sdk/service_helpers.h"
#include <string>

namespace {
std::string identity(const char* value) {
    constexpr char digits[]="0123456789abcdef";
    std::string output;
    for(auto* p=reinterpret_cast<const unsigned char*>(value);*p;++p) {
        output+=digits[*p>>4];output+=digits[*p&15];
    }
    return output;
}
}

uwcn::Status translate_message(const uwcn::HostApi* host,const uwcn::TextRequest& request,
                              void* output,uwcn::u32* capacity) {
    using namespace uwcn;
    std::string key="message.";
    switch(request.component) {
    case TextComponent::message_literal:
        key+="literal."+identity(request.original);
        break;
    case TextComponent::message_template: {
        std::string name=request.value;
        if(name.compare(0,7,"format.")==0) key+=name;
        else {
            // 560CB0 separates KEY from the already-expanded :selector.
            // Selection itself has already happened in the game.
            name=name.substr(0,name.find(':'));
            key+="template."+name+"."+identity(request.original);
        }
        break;
    }
    case TextComponent::message_value:
        key+="value."+std::string(request.value)+"."+identity(request.original);
        break;
    case TextComponent::message_continue:key+="continue";break;
    case TextComponent::message_more:key+="more";break;
    default:return Status::invalid;
    }
    const CatalogRequest lookup{key.c_str()};
    return host->invoke(ModuleId::catalog,catalog_op::lookup,&lookup,sizeof(lookup),output,capacity);
}
