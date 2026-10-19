#include "native_culture_legend.h"
#include <cstring>
#include <memory>
#include <optional>

namespace uwcn::adapter::native_culture_legend {
namespace {
constexpr u32 factory=0xE3A50,owner=0x5F8FA78;
constexpr u32 ordinary_constructor=0x5B00;
constexpr std::array<u32,3> palette_fields{0x1E8798,0x1E87A4,0x1E87A0};
std::uintptr_t base{};
Services services{};
u64 next_revision=1,language_revision=1,resource_language{};
std::optional<Source> active;
u32 native_resource{};
bool building{};

template<class T> T& native(u32 field) {return *reinterpret_cast<T*>(base+field);}
Source capture() {
    Source value{next_revision++,native_component_style::capture_panel(),native<u32>(0x1E87AC),{}};
    for(std::size_t index=0;index<palette_fields.size();++index) value.palette[index]=native<u32>(palette_fields[index]);
    return value;
}
struct Construction {
    native_component_style::PanelScope panel;
    u32 previous_panel;
    std::array<u32,3> previous_palette;
    u64 revision;
    explicit Construction(const Source& value):panel(value.panel),previous_panel(native<u32>(0x1E87AC)),revision(value.revision) {
        for(std::size_t index=0;index<palette_fields.size();++index) {
            previous_palette[index]=native<u32>(palette_fields[index]);
            native<u32>(palette_fields[index])=value.palette[index];
        }
        native<u32>(0x1E87AC)=value.panel_color;
        services.enter(revision);
    }
    ~Construction() {
        services.leave(revision);native<u32>(0x1E87AC)=previous_panel;
        for(std::size_t index=0;index<palette_fields.size();++index)
            native<u32>(palette_fields[index])=previous_palette[index];
    }
};
std::unique_ptr<Construction> ordinary;
template<class T> void append(std::vector<std::uint8_t>& output,T value) {
    const auto* bytes=reinterpret_cast<const std::uint8_t*>(&value);output.insert(output.end(),bytes,bytes+sizeof(value));
}
template<class T> T read(const std::uint8_t*& input) {T value;std::memcpy(&value,input,sizeof(value));input+=sizeof(value);return value;}
}
void initialize(std::uintptr_t image_base,const Services& callbacks) {
    base=image_base;services=callbacks;next_revision=1;language_revision=1;resource_language=0;
    active.reset();ordinary.reset();native_resource=0;building=false;
}
void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back({ordinary_constructor,HookKind::call,0x117C01,factory,0,5,{0xE8,0x4A,0xBE,0xFC,0xFF}});
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id==ordinary_constructor;
    if(!handled) return Status::ok;
    if(event.phase==NativePhase::before) {
        active=capture();building=true;ordinary=std::make_unique<Construction>(*active);
    } else if(event.phase==NativePhase::after) {
        native_resource=native<u32>(owner);resource_language=language_revision;
        ordinary.reset();building=false;
    }
    return Status::ok;
}
Status language_changed() {
    ++language_revision;
    // No native resource exists before this game's original constructor has
    // run, or after its genuine SDL owner has retired it.
    if(!active) return Status::ok;
    const Construction inputs(*active);building=true;
    using Construct=void (UWCN_CALL *)();
    reinterpret_cast<Construct>(base+factory)();
    native_resource=native<u32>(owner);resource_language=language_revision;building=false;
    return native_resource ? Status::ok : Status::failed;
}
void native_texture_destroying(u32 texture) {
    if(!building && native_resource==texture) {native_resource=0;active.reset();resource_language=0;}
}
bool constructed() {return active.has_value();}
const Source& source() {return *active;}
std::vector<std::uint8_t> save() {
    std::vector<std::uint8_t> output;
    append(output,next_revision);append(output,language_revision);append(output,resource_language);
    append(output,native_resource);append(output,active?1u:0u);
    if(active) {
        append(output,active->revision);append(output,active->panel.background_mode);append(output,active->panel.title_fill_color);
        append(output,active->panel_color);for(const auto color:active->palette) append(output,color);
    }
    return output;
}
void restore(const void* payload) {
    const auto* input=static_cast<const std::uint8_t*>(payload);
    next_revision=read<u64>(input);language_revision=read<u64>(input);resource_language=read<u64>(input);
    native_resource=read<u32>(input);const bool exists=read<u32>(input)!=0;active.reset();ordinary.reset();building=false;
    if(exists) {
        Source value{};value.revision=read<u64>(input);value.panel.background_mode=read<u32>(input);
        value.panel.title_fill_color=read<u32>(input);value.panel_color=read<u32>(input);
        for(auto& color:value.palette) color=read<u32>(input);active=value;
    }
}
void shutdown() {ordinary.reset();active.reset();base=0;services={};native_resource=0;building=false;}
}
