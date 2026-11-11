#include "native_footer_component.h"
#include "native_component_calls.h"
#include "native_root_component.h"
#include "../render/byayoi_sprite.h"
#include <algorithm>
#include <cstring>
#include <map>
#include <utility>

namespace uwcn::adapter::native_footer_component {
namespace {
std::uintptr_t base{};
Services services{};
Handle next_handle=1;
struct Version { u32 references;Source source; };
std::map<Handle,Version> models;
std::map<SourceKey,Handle> current_sources;
void retain_dependencies(const Source& source) {
    native_component_model::retain(source.panel);
    native_component_model::retain(source.production);
    native_image_component::retain(source.logo);
}
void release_dependencies(const Source& source) {
    native_component_model::release(source.panel);
    native_component_model::release(source.production);
    native_image_component::release(source.logo);
}
struct Writer {
    std::vector<std::uint8_t> bytes;
    template<class T> void scalar(T value) {
        const auto* p=reinterpret_cast<const std::uint8_t*>(&value);
        bytes.insert(bytes.end(),p,p+sizeof(value));
    }
    void string(const std::string& value) {
        scalar(static_cast<u32>(value.size()));bytes.insert(bytes.end(),value.begin(),value.end());
    }
    void key(SourceKey value) { scalar(value.owner);scalar(value.native_source);scalar(value.field); }
    void text(const TextSource& value) {
        scalar(static_cast<u32>(value.component));string(value.original);string(value.value);
        scalar(value.has_value?1u:0u);scalar(static_cast<u32>(value.policy));
        string(value.prefix);string(value.suffix);
    }
};
struct Reader {
    const std::uint8_t* cursor;
    template<class T> T scalar() { T value;std::memcpy(&value,cursor,sizeof(value));cursor+=sizeof(value);return value; }
    std::string string() {
        const auto size=scalar<u32>();std::string value(reinterpret_cast<const char*>(cursor),size);cursor+=size;return value;
    }
    SourceKey key() { const auto owner=scalar<u64>(),native_source=scalar<u64>();const auto field=scalar<u32>();return {owner,native_source,field}; }
    TextSource text() {
        const auto component=static_cast<TextComponent>(scalar<u32>());auto original=string(),value=string();
        const bool has_value=scalar<u32>()!=0;const auto policy=static_cast<native_text_resource::TextPolicy>(scalar<u32>());
        auto prefix=string(),suffix=string();
        return {component,std::move(original),std::move(value),has_value,policy,std::move(prefix),std::move(suffix)};
    }
};
Status paint_text(const Source& source,const std::string& text) {
    // Measure semantic <br> fragments with the same outline scope as the
    // complete native centered-text call. Markup is not printable text.
    std::int32_t width{};
    std::string native_text;
    std::size_t begin=0;
    for(;;) {
        const auto end=text.find("<br>",begin);
        const auto fragment=text.substr(begin,end==std::string::npos ? end : end-begin);
        std::int32_t fragment_width{};
        const auto status=services.measure(fragment.c_str(),fragment_width);
        if(status!=Status::ok) return status;
        width=std::max(width,fragment_width);
        native_text+=fragment;
        if(end==std::string::npos) break;
        // D4430, called by 10E910, consumes space-delimited input records.
        native_text+=" <br> ";begin=end+4;
    }
    const auto& panel=std::get<native_component_model::PanelInputs>(native_component_model::get(source.panel).inputs);
    const auto& production=std::get<native_component_model::ParagraphInputs>(native_component_model::get(source.production).inputs);
    const auto& logo=native_image_component::get(source.logo);
    const auto gap=logo.y-panel.origin.y.input;
    // This added sibling uses the current native root's right edge. The
    // original developer paragraph and its panel are not its right boundary.
    const auto x=native_root_component::source(source.source.owner).width-gap-width;
    const auto status=services.sprite(x+(width-byayoi_sprite::width)/2,logo.y);
    if(status!=Status::ok) return status;
    const native_component_calls::CenteredTextCall call{
        static_cast<u32>(base+0x10E910),x,logo.y+byayoi_sprite::height+gap,
        width,native_text.c_str(),production.color,production.outline};
    native_component_calls::uwcn_component_centered_text(&call);
    return Status::ok;
}
}
void initialize(std::uintptr_t image_base) {
    base=image_base;services={};next_handle=1;models.clear();current_sources.clear();
}
void configure(const Services& value) { services=value; }
Handle upsert(const Source& replacement) {
    retain_dependencies(replacement);
    const auto previous=current_sources.find(replacement.source);
    if(previous!=current_sources.end()) {
        auto& version=models.find(previous->second)->second;
        if(version.references==1) {
            release_dependencies(version.source);version.source=replacement;return previous->second;
        }
        const auto old=previous->second,handle=next_handle++;
        models.emplace(handle,Version{1,replacement});previous->second=handle;release(old);return handle;
    }
    const auto handle=next_handle++;models.emplace(handle,Version{1,replacement});
    current_sources.emplace(replacement.source,handle);return handle;
}
const Source& get(Handle handle) { return models.find(handle)->second.source; }
void retain(Handle handle) { ++models.find(handle)->second.references; }
void release(Handle handle) {
    const auto version=models.find(handle);
    if(--version->second.references==0) { release_dependencies(version->second.source);models.erase(version); }
}
void remove_owner(u64 owner) {
    for(auto entry=current_sources.begin();entry!=current_sources.end();) {
        if(entry->first.owner==owner) { const auto handle=entry->second;entry=current_sources.erase(entry);release(handle); }
        else ++entry;
    }
}
Status paint(Handle handle) {
    const auto& source=get(handle);
    std::vector<char> credit,version;
    auto status=native_text_resource::resolve_source(source.credit,services.resolve,services.encode_original,credit);
    if(status!=Status::ok) return status;
    status=native_text_resource::resolve_source(source.version,services.resolve,services.encode_original,version);
    if(status!=Status::ok) return status;
    // The explicitly authored English resources are empty. Their sprite and
    // paragraph exist exactly when the shared semantic resources have content.
    if(credit.front()==0 && version.front()==0) return Status::ok;
    const auto& production=std::get<native_component_model::ParagraphInputs>(native_component_model::get(source.production).inputs);
    services.enter(handle,production.outline);
    status=paint_text(source,std::string(credit.data())+"<br>"+version.data());
    const auto leave_status=services.leave(handle);
    return status==Status::ok ? leave_status : status;
}
std::vector<std::uint8_t> save() {
    Writer output;output.scalar(next_handle);output.scalar(static_cast<u32>(models.size()));
    output.scalar(static_cast<u32>(current_sources.size()));
    for(const auto& [handle,version]:models) {
        output.scalar(handle);output.scalar(version.references);const auto& source=version.source;
        output.key(source.source);output.scalar(source.panel);output.scalar(source.production);output.scalar(source.logo);
        output.text(source.credit);output.text(source.version);
    }
    for(const auto& [source,handle]:current_sources) { output.key(source);output.scalar(handle); }
    return std::move(output.bytes);
}
void restore(const void* payload) {
    Reader input{static_cast<const std::uint8_t*>(payload)};next_handle=input.scalar<u32>();
    const auto count=input.scalar<u32>(),sources=input.scalar<u32>();models.clear();current_sources.clear();
    for(u32 i=0;i<count;++i) {
        const auto handle=input.scalar<u32>(),references=input.scalar<u32>();const auto key=input.key();
        const auto panel=input.scalar<u32>(),production=input.scalar<u32>(),logo=input.scalar<u32>();
        auto credit=input.text(),version=input.text();
        models.emplace(handle,Version{references,{key,panel,production,logo,std::move(credit),std::move(version)}});
    }
    for(u32 i=0;i<sources;++i) { const auto key=input.key();const auto handle=input.scalar<u32>();current_sources.emplace(key,handle); }
}
void shutdown() {
    for(const auto& [handle,version]:models) release_dependencies(version.source);
    models.clear();current_sources.clear();base=0;next_handle=1;services={};
}
}
