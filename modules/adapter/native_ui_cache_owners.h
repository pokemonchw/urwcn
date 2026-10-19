#pragma once
#include "../../sdk/host_abi.h"
#include "../render/sdl_api.h"
#include <vector>

namespace uwcn::adapter::native_ui_cache_owners {
enum class Slot : u32 { first=0,second=1,named0=2,named1=3,named2=4,named3=5,menu=6 };

// Complete original cache-copy inputs, borrowed only for this synchronous
// native operation. A cache component prepares its canonical arguments before
// that same original copy consumes them.
struct RestoreInput {
    const void* native_surface;
    const render::Rect* source;
    render::Rect* destination;
};
struct PreparedRestore {
    u32 component{};
    bool has_source{},has_destination{};
    render::Rect source{},destination{};
};
struct BlitPreparation {
    bool restoring{};
    Slot slot{};
    PreparedRestore restore;
};

struct Callbacks {
    void (*save)(Slot);
    Status (*before_restore)(Slot,const RestoreInput&,PreparedRestore&);
    void (*after_restore)(Slot,const PreparedRestore&,int native_result);
    void (*retire)(Slot);
};

void initialize(std::uintptr_t image_base);
// All four callbacks are installed before native execution resumes. They
// belong to the current adapter instance and are not serialized or retained
// across replacement. A callback does not replace/free the native source or
// destination while the observed original blit still owns those arguments.
void set_callbacks(const Callbacks& callbacks);

// Only the statically enumerated native copy caller returns and their actual
// native cache owners are observed. No pixels or text calls are observed.
// The prepared cache component owns the complete original rectangle inputs;
// no overlap calculation assigns another component to a rectangle.
Status before_blit(u32 caller_return_rva,const void* source,const void* destination,
    const render::Rect* source_rect,render::Rect* destination_rect,BlitPreparation&);
void after_blit(u32 caller_return_rva,const void* source,const void* destination,
    const BlitPreparation&,int native_result);
u32 owner_field(Slot);
void* surface(Slot);

// Resource creation/replacement and the original named-slot clear retire
// only the corresponding native cache's ownership binding.
void append_hooks(std::vector<HookSpec>& hooks);
Status dispatch(const NativeEvent&,DispatchResult&,bool& handled);
void shutdown();
}
