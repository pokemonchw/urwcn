#pragma once
#include "../../sdk/host_abi.h"
#include <string>
#include <vector>

namespace uwcn::adapter::native_root_component {
using RootRevision=u64;

enum class SourceKind : u32 { filename=1, native_surface_owner=2, native_clear=3 };

// Neutral inputs of the original 1127C0 background component. The native
// constructor consumes these dimensions and owns image placement/scaling.
// A surface source names its original global owner, never a borrowed surface.
struct BackgroundSource {
    SourceKind kind;
    u32 owner_rva;
    std::int32_t width,height;
    std::string filename;
};

void initialize(std::uintptr_t image_base);
void append_hooks(std::vector<HookSpec>& hooks);
Status dispatch(const NativeEvent&,DispatchResult&,bool& handled);

// The existing native FillRect gateway reports only the original 10B9F0
// clear completion here. Pointers are consumed synchronously and not retained.
void native_clear_filled(u32 caller_return_rva,const void* destination,int result);

// Zero means that no successful background construction has established a
// root. A revision is a stable value; it is not an address or native frame.
RootRevision current();
const BackgroundSource& source(RootRevision revision);
std::vector<RootRevision> revisions();

// Native cache lifecycle owners use activate after restoring their own
// content. It changes only the current root identity; zero clears that identity.
void activate(RootRevision revision);

// Materialize this same source into the current native target. Image sources
// re-enter complete 1127C0; native_clear consumes the original FillRect request
// without 10B9F0's upload/present tail. Success activates the existing revision
// without constructing another root. Native image-load/SDL failures retain
// their original behavior and are reported as Status::failed.
Status paint_background(RootRevision revision);

// The caller retires a revision only after its native scene/cache owners have
// released it. Methods taking a nonzero revision require a live revision.
void retire(RootRevision revision);

// Pure-value payload, with no pixels, text drawing history, native frames,
// borrowed pointers or module callbacks. save/restore run outside the
// synchronous native background construction/materialization invocation.
std::vector<std::uint8_t> save();
void restore(const void* payload);
void shutdown();
}
