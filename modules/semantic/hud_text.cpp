#include "hud_text.h"
#include "../../sdk/service_helpers.h"
#include <string>

namespace uwcn {
Status translate_hud(const HostApi* host,const TextRequest& request,void* output,u32* capacity) {
    std::string original=request.original;
    // These are already selected native HUD display values. Percentages and
    // speed numbers are never recomputed from gameplay state.
    if(request.component==TextComponent::hud_penalty && original!="None")
        return copy_text(original,output,capacity);
    std::string key;
    switch(request.component) {
    case TextComponent::hud_label: key="hud.label."+original; break;
    case TextComponent::hud_condition: key="hud.condition."+original; break;
    case TextComponent::hud_penalty: key="hud.none"; break;
    case TextComponent::hud_action:
        key="hud.action."+original.substr(original.find_first_not_of(' ')); break;
    case TextComponent::hud_direction:
        key="hud.direction."+original.substr(original.find_first_not_of(' ')); break;
    case TextComponent::hud_speed:
        key="hud.speed"; break;
    default: return Status::invalid;
    }
    const CatalogRequest lookup{key.c_str()};
    std::string translated;
    const auto status=invoke_text(host,ModuleId::catalog,catalog_op::lookup,&lookup,sizeof(lookup),translated);
    if(status!=Status::ok) return status;
    if(request.component==TextComponent::hud_action || request.component==TextComponent::hud_direction)
        translated.insert(0,original,0,original.find_first_not_of(' '));
    return copy_text(translated,output,capacity);
}
}
