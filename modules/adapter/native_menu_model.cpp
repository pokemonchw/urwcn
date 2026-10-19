#include "native_menu_model.h"
#include <cstring>
#include <map>
#include <utility>

namespace uwcn::adapter::native_menu_model {
namespace {
struct Instance {
    u32 references=1; // The active native view owns one reference.
    Handle input_owner{};
    MenuModel native{};
    PaintStyle style{};
    TextBinding title;
    std::array<TextBinding,row_capacity> rows;
    std::array<TextBinding,row_capacity> annotations;
};
std::uintptr_t base{};
Handle next_handle=1;
Handle active_handle{};
std::map<Handle,Instance> models;
constexpr u32 header_rva=0x5F54A20;
constexpr u32 rows_rva=0x5F4EF10;

void capture_active() {
    if(active_handle) capture_into(active_handle);
}
void append(std::vector<std::uint8_t>& output,const void* data,u32 bytes) {
    const auto offset=output.size();
    output.resize(offset+bytes);
    std::memcpy(output.data()+offset,data,bytes);
}
void write_u32(std::vector<std::uint8_t>& output,u32 value) {
    append(output,&value,sizeof(value));
}
void write_u64(std::vector<std::uint8_t>& output,u64 value) {
    append(output,&value,sizeof(value));
}
void write_string(std::vector<std::uint8_t>& output,const std::string& value) {
    write_u32(output,static_cast<u32>(value.size()));
    append(output,value.data(),static_cast<u32>(value.size()));
}
void write_binding(std::vector<std::uint8_t>& output,const TextBinding& binding) {
    write_u32(output,binding.bound?1u:0u);
    if(!binding.bound) return;
    write_u64(output,binding.key.owner);
    write_u64(output,binding.key.native_source);
    write_u32(output,binding.key.field);
    write_u32(output,static_cast<u32>(binding.source.component));
    write_u32(output,binding.source.has_value?1u:0u);
    write_u32(output,static_cast<u32>(binding.source.policy));
    write_string(output,binding.source.original);
    write_string(output,binding.source.value);
    write_string(output,binding.source.prefix);
    write_string(output,binding.source.suffix);
    write_string(output,binding.prefix);
}
u32 read_u32(const std::uint8_t*& cursor) {
    u32 value;
    std::memcpy(&value,cursor,sizeof(value));
    cursor+=sizeof(value);
    return value;
}
u64 read_u64(const std::uint8_t*& cursor) {
    u64 value;
    std::memcpy(&value,cursor,sizeof(value));
    cursor+=sizeof(value);
    return value;
}
std::string read_string(const std::uint8_t*& cursor) {
    const auto bytes=read_u32(cursor);
    std::string value(reinterpret_cast<const char*>(cursor),bytes);
    cursor+=bytes;
    return value;
}
TextBinding read_binding(const std::uint8_t*& cursor) {
    TextBinding binding;
    binding.bound=read_u32(cursor)!=0;
    if(!binding.bound) return binding;
    binding.key.owner=read_u64(cursor);
    binding.key.native_source=read_u64(cursor);
    binding.key.field=read_u32(cursor);
    binding.source.component=static_cast<TextComponent>(read_u32(cursor));
    binding.source.has_value=read_u32(cursor)!=0;
    binding.source.policy=static_cast<native_text_resource::TextPolicy>(read_u32(cursor));
    binding.source.original=read_string(cursor);
    binding.source.value=read_string(cursor);
    binding.source.prefix=read_string(cursor);
    binding.source.suffix=read_string(cursor);
    binding.prefix=read_string(cursor);
    return binding;
}
}

void initialize(std::uintptr_t image_base) {
    base=image_base;
    native_component_style::initialize(base);
    next_handle=1;
    active_handle=0;
    models.clear();
}

Handle create_from_native() {
    const Handle handle=next_handle++;
    models.emplace(handle,Instance{});
    models.find(handle)->second.input_owner=handle;
    capture_into(handle);
    capture_style(handle);
    active_handle=handle;
    return handle;
}

Handle snapshot(Handle handle) {
    if(handle==active_handle) capture_into(handle);
    const Handle copy=next_handle++;
    auto instance=models.find(handle)->second;
    instance.references=1;
    retain(instance.input_owner);
    instance.title.key.owner=copy;
    for(auto& binding:instance.rows) binding.key.owner=copy;
    for(auto& binding:instance.annotations) binding.key.owner=copy;
    models.emplace(copy,std::move(instance));
    return copy;
}

Handle input_owner(Handle handle) { return models.find(handle)->second.input_owner; }

void capture_into(Handle handle) {
    auto& model=models.find(input_owner(handle))->second.native;
    std::memcpy(model.header.data(),reinterpret_cast<const void*>(base+header_rva),header_bytes);
    std::memcpy(model.rows.data(),reinterpret_cast<const void*>(base+rows_rva),rows_bytes);
}

void capture_style(Handle handle) {
    auto& instance=models.find(input_owner(handle))->second;
    instance.style.panel=native_component_style::capture_panel();
    // D0287/D030F load header+10h into 61BBAC4; D0314/D031A load
    // header+7Ch into 61BBA54. The normal full menu consumer owns these writes.
    std::memcpy(&instance.style.button.suffix_color,instance.native.header.data()+0x10,sizeof(u32));
    std::memcpy(&instance.style.button.suffix_outline,instance.native.header.data()+0x7C,sizeof(u32));
}
const PaintStyle& style(Handle handle) { return models.find(handle)->second.style; }

void retain(Handle handle) { ++models.find(handle)->second.references; }
void release(Handle handle) {
    auto instance=models.find(handle);
    if(--instance->second.references==0) {
        const auto owner=instance->second.input_owner;models.erase(instance);
        if(owner!=handle) release(owner);
    }
}

void activate(Handle handle) {
    handle=input_owner(handle);
    capture_active();
    const auto previous=active_handle;
    retain(handle);
    const auto& model=models.find(handle)->second.native;
    std::memcpy(reinterpret_cast<void*>(base+header_rva),model.header.data(),header_bytes);
    std::memcpy(reinterpret_cast<void*>(base+rows_rva),model.rows.data(),rows_bytes);
    active_handle=handle;
    if(previous) release(previous);
}

void deactivate() {
    capture_active();
    const auto previous=active_handle;
    active_handle=0;
    if(previous) release(previous);
}

void adopt_from_native(Handle saved_source) {
    const auto owner=input_owner(saved_source),previous=active_handle;
    retain(owner);active_handle=owner;capture_into(owner);
    if(previous) release(previous);
}

void destroy(Handle handle) {
    if(active_handle==handle) deactivate();
    else release(handle);
}

Handle active() { return active_handle; }

void bind_title(Handle handle,const native_text_resource::TextSource& source) {
    models.find(handle)->second.title={true,
        {handle,header_rva+0x18,static_cast<u32>(source.component)},source,{}};
}
void bind_row(Handle handle,u32 index,const native_text_resource::TextSource& source,
    const std::string& prefix) {
    models.find(handle)->second.rows[index]={true,
        {handle,rows_rva+index*row_stride,static_cast<u32>(source.component)},source,prefix};
}
const TextBinding& title(Handle handle) { return models.find(handle)->second.title; }
const TextBinding& row(Handle handle,u32 index) { return models.find(handle)->second.rows[index]; }
void bind_annotation(Handle handle,u32 index,const native_text_resource::TextSource& source) {
    models.find(handle)->second.annotations[index]={true,
        {handle,rows_rva+index*row_stride+0x64,static_cast<u32>(source.component)},source,{}};
}
const TextBinding& annotation(Handle handle,u32 index) { return models.find(handle)->second.annotations[index]; }

std::vector<std::uint8_t> save() {
    capture_active();
    std::vector<std::uint8_t> payload;
    write_u32(payload,next_handle);
    write_u32(payload,active_handle);
    write_u32(payload,static_cast<u32>(models.size()));
    for(const auto& [handle,instance]:models) {
        write_u32(payload,handle);
        write_u32(payload,instance.references);
        write_u32(payload,instance.input_owner);
        append(payload,instance.native.header.data(),header_bytes);
        append(payload,instance.native.rows.data(),rows_bytes);
        write_u32(payload,instance.style.panel.background_mode);
        write_u32(payload,instance.style.panel.title_fill_color);
        write_u32(payload,instance.style.button.suffix_color);
        write_u32(payload,instance.style.button.suffix_outline);
        write_binding(payload,instance.title);
        for(const auto& binding:instance.rows) write_binding(payload,binding);
        for(const auto& binding:instance.annotations) write_binding(payload,binding);
    }
    return payload;
}

void restore(const void* payload) {
    auto* cursor=static_cast<const std::uint8_t*>(payload);
    next_handle=read_u32(cursor);
    active_handle=read_u32(cursor);
    const auto count=read_u32(cursor);
    models.clear();
    for(u32 i=0;i<count;++i) {
        const auto handle=read_u32(cursor);
        auto& instance=models.emplace(handle,Instance{}).first->second;
        instance.references=read_u32(cursor);
        instance.input_owner=read_u32(cursor);
        std::memcpy(instance.native.header.data(),cursor,header_bytes);
        cursor+=header_bytes;
        std::memcpy(instance.native.rows.data(),cursor,rows_bytes);
        cursor+=rows_bytes;
        instance.style.panel.background_mode=read_u32(cursor);
        instance.style.panel.title_fill_color=read_u32(cursor);
        instance.style.button.suffix_color=read_u32(cursor);
        instance.style.button.suffix_outline=read_u32(cursor);
        instance.title=read_binding(cursor);
        for(auto& binding:instance.rows) binding=read_binding(cursor);
        for(auto& binding:instance.annotations) binding=read_binding(cursor);
    }
}
}
