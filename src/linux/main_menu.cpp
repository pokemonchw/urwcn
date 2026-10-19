#include "sdk/host_abi.h"
#include "sdk/text_services.h"
#include "sdk/service_helpers.h"

namespace {
using namespace uwcn;
const HostApi* host;
Status initialize(const HostApi* api) { host=api; return Status::ok; }
Status invoke(u32 op,const void* input,u32 bytes,void* output,u32* capacity) {
    return host->invoke(ModuleId::semantic,op,input,bytes,output,capacity);
}
void shutdown() { host=nullptr; }
const ModuleApi api{sizeof(ModuleApi),kHostAbi,ModuleId::main_menu,initialize,invoke,empty_save,empty_restore,shutdown};
}
UWCN_EXPORT const uwcn::ModuleDescriptor uwcn_module_descriptor{uwcn::kDescriptorMagic,uwcn::kHostAbi,5,uwcn::kModuleMachine,1};
UWCN_EXPORT const uwcn::ModuleApi* uwcn_get_module_api() { return &api; }
