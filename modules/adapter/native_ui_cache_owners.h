#pragma once
#include "../../sdk/host_abi.h"
#include <vector>

namespace uwcn::adapter::native_ui_cache_owners {
enum class Slot : u32 { first=0,second=1,named0=2,named1=3,named2=4,named3=5,menu=6 };

struct Callbacks {
    void (*save)(Slot);
    void (*before_restore)(Slot);
    void (*after_restore)(Slot,bool region);
    void (*retire)(Slot);
};

void initialize(std::uintptr_t image_base);
// All four callbacks are installed before native execution resumes. They
// belong to the current adapter instance and are not serialized or retained
// across replacement. A callback does not replace/free the native source or
// destination while the observed original blit still owns those arguments.
void set_callbacks(const Callbacks& callbacks);

// Only the statically enumerated native copy caller returns and their actual
// native cache owners are observed. The pointers identify this synchronous
// operation; no pointer, rectangle, pixels or UI content is retained.
void before_blit(u32 caller_return_rva,const void* source,const void* destination);
// region means that this original operation supplied a nonnull source rect;
// the observer does not interpret, save or infer any rectangle geometry.
void after_blit(u32 caller_return_rva,const void* source,const void* destination,
    bool region,int native_result);

// Resource creation/replacement and the original named-slot clear retire
// only the corresponding native cache's ownership binding.
void append_hooks(std::vector<HookSpec>& hooks);
Status dispatch(const NativeEvent&,DispatchResult&,bool& handled);
void shutdown();
}
