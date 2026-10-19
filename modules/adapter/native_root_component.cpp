#include "native_root_component.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <map>
#include <optional>
#include <utility>

namespace uwcn::adapter::native_root_component {
namespace {
std::uintptr_t base{};
RootRevision next_revision=1;
RootRevision current_revision{};
RootRevision painting_revision{};
bool background_painted{};
std::map<RootRevision,BackgroundSource> roots;

struct Construction {
    BackgroundSource source;
    RootRevision revision;
};
std::optional<Construction> construction;

enum Hook : u32 {
    background_construct=0x5300,
    background_drawn,
    background_return,
    background_load_failed,
    clear_construct,
    clear_return
};

// 10C790 loads these three original background resources. All six surface
// arguments in the complete 1127C0 direct-call census use these exact owners.
constexpr std::array<u32,3> surface_owners{0x61BBACC,0xA2110C8,0xA2110D4};

template<class T> T* at(u32 rva) {
    return reinterpret_cast<T*>(base+rva);
}
template<class T> T* pointer(u32 value) {
    return reinterpret_cast<T*>(static_cast<std::uintptr_t>(value));
}
u32 address(const void* value) {
    return static_cast<u32>(reinterpret_cast<std::uintptr_t>(value));
}

HookSpec call(u32 id,u32 site,u32 target,u32 arguments) {
    HookSpec spec{id,HookKind::call,site,target,arguments,5,{0xE8}};
    const auto displacement=target-site-5;
    std::memcpy(spec.expected+1,&displacement,sizeof(displacement));
    return spec;
}

u32 surface_owner(u32 surface) {
    // The pinned original executable's six surface-source calls use exactly
    // these native owners; no other surface-source contract is introduced.
    return *std::find_if(surface_owners.begin(),surface_owners.end(),
        [surface](u32 owner){return *at<u32>(owner)==surface;});
}

Status construct(const NativeEvent& event) {
    BackgroundSource neutral{};
    if(painting_revision) {
        neutral=roots.find(painting_revision)->second;
    } else {
        neutral.width=*pointer<const std::int32_t>(event.frame->ebp+0x10);
        neutral.height=*pointer<const std::int32_t>(event.frame->ebp+0x14);
        if(event.frame->edx) {
            neutral.kind=SourceKind::native_surface_owner;
            neutral.owner_rva=surface_owner(event.frame->edx);
        } else {
            neutral.kind=SourceKind::filename;
            neutral.filename=pointer<const char>(event.frame->ecx);
        }
    }

    construction=Construction{std::move(neutral),painting_revision};
    const auto& original=construction->source;
    // Both normal construction and locale materialization enter the original
    // component with its canonical source. The owned filename remains alive
    // until that complete native invocation reaches its cookie-return hook.
    event.frame->ecx=original.kind==SourceKind::filename
        ? address(original.filename.c_str()) : 0;
    event.frame->edx=original.kind==SourceKind::native_surface_owner
        ? *at<u32>(original.owner_rva) : 0;
    *pointer<std::int32_t>(event.frame->ebp+0x10)=original.width;
    *pointer<std::int32_t>(event.frame->ebp+0x14)=original.height;
    return Status::ok;
}

void commit() {
    const auto& completed=*construction;
    if(completed.revision) {
        current_revision=completed.revision;
        background_painted=true;
    } else {
        const auto revision=next_revision++;
        roots.emplace(revision,completed.source);
        current_revision=revision;
    }
}

template<class T> void write(std::uint8_t*& cursor,T value) {
    std::memcpy(cursor,&value,sizeof(value));
    cursor+=sizeof(value);
}
template<class T> T read(const std::uint8_t*& cursor) {
    T value;
    std::memcpy(&value,cursor,sizeof(value));
    cursor+=sizeof(value);
    return value;
}

struct BackgroundCall {
    u32 target,filename,surface;
    std::int32_t width,height;
};

struct NativeRect { std::int32_t x,y,w,h; };

BackgroundSource clear_source() {
    const auto& rect=*at<NativeRect>(0x1DDAB0);
    return {SourceKind::native_clear,0,rect.w,rect.h,{}};
}

int paint_clear() {
    using Fill=int (UWCN_CALL *)(void*,const NativeRect*,u32);
    // This is the same native target, native rectangle and color consumed by
    // 10B9F0 at 10BA17. Its original upload/present tail is not part of paint.
    const auto fill=*at<Fill>(0x18C1E8);
    return fill(*at<void*>(0x61BBB10),at<NativeRect>(0x1DDAB0),0);
}
}

// 1127C0 uses ECX/EDX and four caller-cleaned stack slots. Its first two
// slots are unused; [EBP+10]/[EBP+14] are the original target width/height.
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_draw_native_root_background(
    const BackgroundCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t"
        "movl 8(%esp),%ebx\n\t"
        "pushl 16(%ebx)\n\t"
        "pushl 12(%ebx)\n\t"
        "pushl $0\n\t"
        "pushl $0\n\t"
        "movl 4(%ebx),%ecx\n\t"
        "movl 8(%ebx),%edx\n\t"
        "call *(%ebx)\n\t"
        "addl $16,%esp\n\t"
        "popl %ebx\n\t"
        "ret\n\t");
}

void initialize(std::uintptr_t image_base) {
    base=image_base;
    next_revision=1;
    current_revision=0;
    painting_revision=0;
    background_painted=false;
    construction.reset();
    roots.clear();
}

void append_hooks(std::vector<HookSpec>& hooks) {
    // After the original prologue, before ECX/EDX are changed. The absolute
    // cookie operand has a native HIGHLOW relocation and uses the real base.
    HookSpec entry{background_construct,HookKind::inline_code,0x1127C9,0,0,5,{0xA1}};
    const auto cookie=static_cast<u32>(base+0x1E200C);
    std::memcpy(entry.expected+1,&cookie,sizeof(cookie));
    hooks.push_back(entry);
    // Only this complete original image call commits a successful new root;
    // 1128A2's native IMG_Load failure branch never reaches it.
    hooks.push_back(call(background_drawn,0x11294E,0x1124A0,6));
    hooks.push_back(call(background_return,0x11296C,0x18A0AE,0));
    hooks.push_back(call(background_load_failed,0x1128C6,0x18A0AE,0));
    auto clear=entry;
    clear.id=clear_construct;
    clear.site_rva=0x10B9F6;
    hooks.push_back(clear);
    hooks.push_back(call(clear_return,0x10BA70,0x18A0AE,0));
}

Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=true;
    switch(event.id) {
    case background_construct:
        return construct(event);
    case background_drawn:
        if(event.phase==NativePhase::after) commit();
        return Status::ok;
    case background_return:
    case background_load_failed:
    case clear_return:
        if(event.phase==NativePhase::after) construction.reset();
        return Status::ok;
    case clear_construct:
        construction=Construction{clear_source(),0};
        return Status::ok;
    default:
        handled=false;
        return Status::ok;
    }
}

void native_clear_filled(u32 caller_return_rva,const void* destination,int result) {
    if(caller_return_rva==0x10BA1D && destination==*at<void*>(0x61BBB10) && result==0)
        commit();
}

RootRevision current() { return current_revision; }
const BackgroundSource& source(RootRevision revision) {
    return roots.find(revision)->second;
}
void activate(RootRevision revision) { current_revision=revision; }
std::vector<RootRevision> revisions() {
    std::vector<RootRevision> result;for(const auto& entry:roots) result.push_back(entry.first);return result;
}

Status paint_background(RootRevision revision) {
    const auto& original=source(revision);
    if(original.kind==SourceKind::native_clear) {
        const int result=paint_clear();
        if(result==0) current_revision=revision;
        return result==0 ? Status::ok : Status::failed;
    }
    const BackgroundCall native{
        static_cast<u32>(base+0x1127C0),
        original.kind==SourceKind::filename ? address(original.filename.c_str()) : 0,
        original.kind==SourceKind::native_surface_owner ? *at<u32>(original.owner_rva) : 0,
        original.width,original.height
    };
    painting_revision=revision;
    background_painted=false;
    uwcn_draw_native_root_background(&native);
    painting_revision=0;
    return background_painted ? Status::ok : Status::failed;
}

void retire(RootRevision revision) {
    roots.erase(revision);
    if(current_revision==revision) current_revision=0;
}

std::vector<std::uint8_t> save() {
    // Header: next revision, active revision, count. Per record: revision,
    // kind, owner RVA, width, height, filename byte count, filename bytes.
    std::size_t bytes=2*sizeof(RootRevision)+sizeof(u32);
    for(const auto& [revision,original]:roots)
        bytes+=sizeof(RootRevision)+5*sizeof(u32)+original.filename.size();
    std::vector<std::uint8_t> payload(bytes);
    auto* cursor=payload.data();
    write(cursor,next_revision);
    write(cursor,current_revision);
    write(cursor,static_cast<u32>(roots.size()));
    for(const auto& [revision,original]:roots) {
        write(cursor,revision);
        write(cursor,static_cast<u32>(original.kind));
        write(cursor,original.owner_rva);
        write(cursor,original.width);
        write(cursor,original.height);
        write(cursor,static_cast<u32>(original.filename.size()));
        std::memcpy(cursor,original.filename.data(),original.filename.size());
        cursor+=original.filename.size();
    }
    return payload;
}

void restore(const void* payload) {
    auto* cursor=static_cast<const std::uint8_t*>(payload);
    next_revision=read<RootRevision>(cursor);
    current_revision=read<RootRevision>(cursor);
    const auto count=read<u32>(cursor);
    roots.clear();
    for(u32 i=0;i<count;++i) {
        const auto revision=read<RootRevision>(cursor);
        BackgroundSource original{};
        original.kind=static_cast<SourceKind>(read<u32>(cursor));
        original.owner_rva=read<u32>(cursor);
        original.width=read<std::int32_t>(cursor);
        original.height=read<std::int32_t>(cursor);
        const auto filename_bytes=read<u32>(cursor);
        original.filename.assign(reinterpret_cast<const char*>(cursor),filename_bytes);
        cursor+=filename_bytes;
        roots.emplace(revision,std::move(original));
    }
    painting_revision=0;
    background_painted=false;
    construction.reset();
}

void shutdown() {
    construction.reset();
    roots.clear();
    current_revision=0;
    painting_revision=0;
    background_painted=false;
    base=0;
}
}
