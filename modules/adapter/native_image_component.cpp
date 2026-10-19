#include "native_image_component.h"
#include "native_root_component.h"
#include "native_ui_scene.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <map>
#include <utility>

namespace uwcn::adapter::native_image_component {
namespace {
std::uintptr_t base{};
Handle next_handle=1;
struct Version { u32 references;ImageSource source; };
std::map<Handle,Version> images;
std::map<SourceKey,Handle> current_sources;
struct Pending { u64 token;Handle handle; };
std::vector<Pending> pending;
struct AssetField { u32 id,site; };
// Each entry names one confirmed native asset field, not a paint occurrence.
// The footer already has module.cpp's footer_logo CALL hook (enum value 21).
constexpr u32 footer_logo=21;
constexpr std::array<AssetField,9> fields{{
    {0x7F00,0x124732},{0x7F01,0x105729},{0x7F02,0x12EE4},
    {0x7F03,0xFB6BA},{0x7F04,0x10DDF},{0x7F05,0x10E52},
    {0x7F06,0x10ED1},{0x7F07,0x18084B},{footer_logo,0x125125}
}};
struct NativeImageCall {
    u32 target;
    const char* descriptor;
    std::int32_t x,y;
};
// 112260 reads this native input at 112273 and uses it after the native image
// blit at 11235D..112388 to decide whether to construct the original border.
struct BorderScope {
    u32 previous;
    explicit BorderScope(u32 value):previous(*reinterpret_cast<u32*>(base+0x61BBAD0)) {
        *reinterpret_cast<u32*>(base+0x61BBAD0)=value;
    }
    ~BorderScope() { *reinterpret_cast<u32*>(base+0x61BBAD0)=previous; }
};
struct Writer {
    std::vector<std::uint8_t> bytes;
    template<class T> void scalar(T value) {
        const auto* p=reinterpret_cast<const std::uint8_t*>(&value);
        bytes.insert(bytes.end(),p,p+sizeof(value));
    }
    void key(SourceKey value) { scalar(value.owner);scalar(value.native_source);scalar(value.field); }
    void string(const std::string& value) {
        scalar(static_cast<u32>(value.size()));bytes.insert(bytes.end(),value.begin(),value.end());
    }
};
struct Reader {
    const std::uint8_t* cursor;
    template<class T> T scalar() {
        T value;std::memcpy(&value,cursor,sizeof(value));cursor+=sizeof(value);return value;
    }
    SourceKey key() {
        const auto owner=scalar<u64>(),native_source=scalar<u64>();const auto field=scalar<u32>();
        return {owner,native_source,field};
    }
    std::string string() {
        const auto size=scalar<u32>();
        std::string value(reinterpret_cast<const char*>(cursor),size);cursor+=size;return value;
    }
};
}

// 112980: ECX=descriptor, EDX=native image x, one caller-cleaned y argument;
// plain RET at 112A61. The native descriptor parser calls complete 112260.
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_paint_native_image(const NativeImageCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t"
        "movl 8(%esp),%ebx\n\t"
        "pushl 12(%ebx)\n\t"
        "movl 4(%ebx),%ecx\n\t"
        "movl 8(%ebx),%edx\n\t"
        "call *(%ebx)\n\t"
        "addl $4,%esp\n\t"
        "popl %ebx\n\t"
        "ret\n\t");
}

void initialize(std::uintptr_t image_base) {
    base=image_base;next_handle=1;images.clear();current_sources.clear();pending.clear();
}
void append_hooks(std::vector<HookSpec>& hooks) {
    for(const auto& field:fields) {
        if(field.id==footer_logo) continue;
        HookSpec hook{field.id,HookKind::call,field.site,0x112980,1,5,{0xE8}};
        const u32 relative=0x112980-field.site-5;
        std::memcpy(hook.expected+1,&relative,sizeof(relative));hooks.push_back(hook);
    }
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    const auto field=std::find_if(fields.begin(),fields.end(),
        [&event](const AssetField& source){return source.id==event.id;});
    if(field==fields.end()) { handled=false;return Status::ok; }
    // The existing footer hook also constructs the independently owned Mod
    // credit component. It must still run its normal module.cpp dispatch.
    handled=field->id!=footer_logo;
    if(event.phase==NativePhase::before) {
        const SourceKey key{native_root_component::current(),field->site,0};
        const auto handle=upsert(key,capture(event));
        retain(handle);pending.push_back({event.token,handle});
        const auto source=prepare(handle);
        event.frame->ecx=static_cast<u32>(reinterpret_cast<std::uintptr_t>(source.descriptor));
        event.frame->edx=static_cast<u32>(source.x);
        event.arguments[0]=static_cast<u32>(source.y);
    } else if(event.phase==NativePhase::after) {
        const auto invocation=std::find_if(pending.begin(),pending.end(),
            [&event](const Pending& value){return value.token==event.token;});
        native_ui_scene::image_constructed(invocation->handle);
        release(invocation->handle);pending.erase(invocation);
    }
    return Status::ok;
}
Inputs capture(const NativeEvent& event) {
    return {reinterpret_cast<const char*>(static_cast<std::uintptr_t>(event.frame->ecx)),
        static_cast<std::int32_t>(event.frame->edx),static_cast<std::int32_t>(event.arguments[0]),
        *reinterpret_cast<const u32*>(base+0x61BBAD0)};
}
Handle upsert(SourceKey key,const Inputs& inputs) {
    ImageSource replacement{key,inputs.descriptor,inputs.x,inputs.y,inputs.border};
    const auto source=current_sources.find(key);
    if(source!=current_sources.end()) {
        auto& current=images.find(source->second)->second;
        if(current.references==1) { current.source=std::move(replacement);return source->second; }
        const auto previous=source->second,handle=next_handle++;
        images.emplace(handle,Version{1,std::move(replacement)});source->second=handle;release(previous);
        return handle;
    }
    const auto handle=next_handle++;
    images.emplace(handle,Version{1,std::move(replacement)});current_sources.emplace(key,handle);
    return handle;
}
Handle current(SourceKey source) { return current_sources.at(source); }
const ImageSource& get(Handle handle) { return images.find(handle)->second.source; }
PreparedSource prepare(Handle handle) {
    const auto& source=get(handle);return {source.descriptor.c_str(),source.x,source.y,source.border};
}
void retain(Handle handle) { ++images.find(handle)->second.references; }
void release(Handle handle) {
    const auto image=images.find(handle);
    if(--image->second.references==0) images.erase(image);
}
void remove(Handle handle) {
    const auto source=current_sources.find(get(handle).source);
    if(source!=current_sources.end() && source->second==handle) {
        current_sources.erase(source);release(handle);
    }
}
void remove_owner(u64 owner) {
    for(auto source=current_sources.begin();source!=current_sources.end();) {
        if(source->first.owner==owner) {
            const auto handle=source->second;source=current_sources.erase(source);release(handle);
        } else ++source;
    }
}
Status paint(Handle handle) {
    const auto source=prepare(handle);
    const BorderScope border(source.border);
    const NativeImageCall call{static_cast<u32>(base+0x112980),source.descriptor,source.x,source.y};
    uwcn_paint_native_image(&call);
    return Status::ok;
}
std::vector<std::uint8_t> save() {
    Writer output;
    output.scalar(next_handle);output.scalar(static_cast<u32>(images.size()));
    output.scalar(static_cast<u32>(current_sources.size()));
    output.scalar(static_cast<u32>(pending.size()));
    for(const auto& [handle,version]:images) {
        output.scalar(handle);output.scalar(version.references);output.key(version.source.source);
        output.string(version.source.descriptor);output.scalar(version.source.x);
        output.scalar(version.source.y);output.scalar(version.source.border);
    }
    for(const auto& [source,handle]:current_sources) { output.key(source);output.scalar(handle); }
    for(const auto& invocation:pending) { output.scalar(invocation.token);output.scalar(invocation.handle); }
    return std::move(output.bytes);
}
void restore(const void* payload) {
    Reader input{static_cast<const std::uint8_t*>(payload)};
    next_handle=input.scalar<u32>();const auto count=input.scalar<u32>(),sources=input.scalar<u32>();
    const auto invocations=input.scalar<u32>();
    images.clear();current_sources.clear();pending.clear();
    for(u32 i=0;i<count;++i) {
        const auto handle=input.scalar<u32>(),references=input.scalar<u32>();
        const auto key=input.key();auto descriptor=input.string();
        const auto x=input.scalar<std::int32_t>(),y=input.scalar<std::int32_t>();const auto border=input.scalar<u32>();
        images.emplace(handle,Version{references,{key,std::move(descriptor),x,y,border}});
    }
    for(u32 i=0;i<sources;++i) {
        const auto key=input.key();const auto handle=input.scalar<u32>();current_sources.emplace(key,handle);
    }
    for(u32 i=0;i<invocations;++i) {
        const auto token=input.scalar<u64>();const auto handle=input.scalar<u32>();pending.push_back({token,handle});
    }
}
void shutdown() { images.clear();current_sources.clear();pending.clear();base=0;next_handle=1; }
}
