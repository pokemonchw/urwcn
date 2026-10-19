#include "native_menu_component.h"
#include <algorithm>
#include <cstring>
#include <utility>

namespace uwcn::adapter::native_menu_component {
namespace {
std::uintptr_t base{};
const HostApi* host{};
native_text_resource::Resolve resolve{};
native_text_resource::EncodeOriginal encode_original{};
Enter enter_scope{};
Leave leave_scope{};
Status paint_result=Status::ok;
bool painting{};
bool native_consuming{};
struct ConstructorSource { u64 token;native_text_resource::TextSource source; };
std::vector<ConstructorSource> title_sources,row_sources;
struct Borrow { u64 token;u32 allocation; };
std::vector<Borrow> borrows;
enum Hook : u32 {
    constructor_begin=0x7E00,constructor_commit,paint_begin,paint_commit,
    row_commit,plain_title
};
// Reuse the existing CALL hooks; installing another patch at these sites would
// replace the same native boundary twice. The root dispatch sends them here.
constexpr u32 menu_text=10,menu_panel=221,menu_button=222;
constexpr u32 rows_rva=0x5F4EF10;

template<class T> T* pointer(u32 value) {
    return reinterpret_cast<T*>(static_cast<std::uintptr_t>(value));
}
u32 address(const void* value) { return static_cast<u32>(reinterpret_cast<std::uintptr_t>(value)); }
u32 row_index(u32 native_record) {
    return (native_record-static_cast<u32>(base+rows_rva))/native_menu_model::row_stride;
}
HookSpec absolute(u32 id,u32 site,u32 rva,std::uint8_t opcode) {
    HookSpec hook{id,HookKind::inline_code,site,0,0,5,{opcode}};
    const auto operand=static_cast<u32>(base+rva);
    std::memcpy(hook.expected+1,&operand,sizeof(operand));
    return hook;
}
HookSpec store_zero(u32 id,u32 site,u32 rva) {
    HookSpec hook{id,HookKind::inline_code,site,0,0,10,{0xC7,0x05}};
    const auto operand=static_cast<u32>(base+rva);
    std::memcpy(hook.expected+2,&operand,sizeof(operand));
    return hook;
}
Status resolve_binding(const native_menu_model::TextBinding& binding,std::vector<char>& encoded) {
    const auto& source=binding.source;
    auto status=native_text_resource::resolve_source(source,resolve,encode_original,encoded);
    if(status!=Status::ok) return status;
    encoded.insert(encoded.begin(),binding.prefix.begin(),binding.prefix.end());
    return Status::ok;
}
Status lend(const NativeEvent& event,const native_menu_model::TextBinding& binding,
    u32& argument,Consumer consumer) {
    std::vector<char> encoded;
    const auto status=resolve_binding(binding,encoded);
    if(status!=Status::ok) {
        paint_result=status;
        return status;
    }
    auto* allocation=host->allocate(static_cast<u32>(encoded.size()));
    std::memcpy(allocation,encoded.data(),encoded.size());
    argument=address(allocation);
    borrows.push_back({event.token,address(allocation)});
    enter_scope(event,consumer);
    return Status::ok;
}
void append(std::vector<std::uint8_t>& output,const void* data,u32 bytes) {
    const auto offset=output.size();
    output.resize(offset+bytes);
    std::memcpy(output.data()+offset,data,bytes);
}
template<class T> void write(std::vector<std::uint8_t>& output,T value) { append(output,&value,sizeof(value)); }
template<class T> T read(const std::uint8_t*& cursor) {
    T value;std::memcpy(&value,cursor,sizeof(value));cursor+=sizeof(value);return value;
}
void write_string(std::vector<std::uint8_t>& output,const std::string& value) {
    write(output,static_cast<u32>(value.size()));append(output,value.data(),static_cast<u32>(value.size()));
}
std::string read_string(const std::uint8_t*& cursor) {
    const auto count=read<u32>(cursor);std::string value(reinterpret_cast<const char*>(cursor),count);cursor+=count;return value;
}
void write_sources(std::vector<std::uint8_t>& output,const std::vector<ConstructorSource>& sources) {
    write(output,static_cast<u32>(sources.size()));
    for(const auto& pending:sources) {
        const auto& source=pending.source;write(output,pending.token);write(output,static_cast<u32>(source.component));
        write(output,source.has_value?1u:0u);write(output,static_cast<u32>(source.policy));
        write_string(output,source.original);write_string(output,source.value);
        write_string(output,source.prefix);write_string(output,source.suffix);
    }
}
void read_sources(const std::uint8_t*& cursor,std::vector<ConstructorSource>& sources) {
    sources.clear();const auto count=read<u32>(cursor);
    for(u32 i=0;i<count;++i) {
        const auto token=read<u64>(cursor);native_text_resource::TextSource source;
        source.component=static_cast<TextComponent>(read<u32>(cursor));source.has_value=read<u32>(cursor)!=0;
        source.policy=static_cast<native_text_resource::TextPolicy>(read<u32>(cursor));
        source.original=read_string(cursor);source.value=read_string(cursor);
        source.prefix=read_string(cursor);source.suffix=read_string(cursor);
        sources.push_back({token,std::move(source)});
    }
}
}

void initialize(std::uintptr_t image_base) {
    base=image_base;
    painting=false;
    native_consuming=false;title_sources.clear();row_sources.clear();
    borrows.clear();
    native_menu_model::initialize(base);
    // The predecessor's live native model is an actual source model, including
    // its current input fields. No past paint calls or page fields are inferred.
    native_menu_model::create_from_native();
}
void configure(const HostApi* api,native_text_resource::Resolve resolver,
    native_text_resource::EncodeOriginal encoder,Enter enter,Leave leave) {
    host=api;
    resolve=resolver;
    encode_original=encoder;
    enter_scope=enter;
    leave_scope=leave;
}

void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(absolute(constructor_begin,0xCF793,0x5F54BB4,0xA1));
    hooks.push_back(store_zero(constructor_commit,0xCF97E,0x5F54AB4));
    hooks.push_back(absolute(paint_begin,0xCFFB6,0x5F54A28,0xA1));
    hooks.push_back(store_zero(paint_commit,0xD03F3,0x61BBAC4));
    HookSpec row{row_commit,HookKind::inline_code,0xCFACB,0,0,6,{0x89,0x35}};
    const auto count=static_cast<u32>(base+0x5F54A34);
    std::memcpy(row.expected+2,&count,sizeof(count));
    hooks.push_back(row);
    hooks.push_back({plain_title,HookKind::call,0xD027F,0x10E5A0,3,5,
        {0xE8,0x1C,0xE3,0x03,0x00}});
}

Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=true;
    if(event.phase==NativePhase::after) {
        const auto borrowed=std::find_if(borrows.begin(),borrows.end(),
            [&](const Borrow& value){return value.token==event.token;});
        if(borrowed!=borrows.end()) {
            leave_scope(event.token);
            host->release(pointer<void>(borrowed->allocation));
            borrows.erase(borrowed);
            return Status::ok;
        }
        handled=false;
        return Status::ok;
    }
    switch(event.id) {
    case constructor_begin:
        // Only the active native-view reference retires. A real native cache
        // root can retain this Menu instance independently; no parent is guessed.
        native_menu_model::deactivate();
        return Status::ok;
    case constructor_commit:
        *reinterpret_cast<u32*>(base+0x5F54AB4)=0;
        native_menu_model::create_from_native();
        if(!title_sources.empty()) native_menu_model::bind_title(active(),title_sources.back().source);
        result.resume_rva=0xCF988;
        return Status::ok;
    case row_commit:
        // Commit the original CF990 count store, after its English label,
        // annotation and action have entered their native record.
        *reinterpret_cast<u32*>(base+0x5F54A34)=event.frame->esi;
        native_menu_model::capture_into(native_menu_model::active());
        if(!row_sources.empty()) native_menu_model::bind_row(active(),event.frame->esi-1,row_sources.back().source,{});
        result.resume_rva=0xCFAD1;
        return Status::ok;
    case paint_begin:
        native_consuming=true;
        native_menu_model::activate(native_menu_model::active());
        if(!painting) native_menu_model::capture_style(native_menu_model::active());
        return Status::ok;
    case paint_commit:
        *reinterpret_cast<u32*>(base+0x61BBAC4)=0;
        native_menu_model::capture_into(native_menu_model::active());
        native_consuming=false;
        result.resume_rva=0xD03FD;
        return Status::ok;
    case menu_panel:case plain_title: {
        const auto& binding=native_menu_model::title(native_menu_model::active());
        if(!binding.bound) { handled=false;return Status::ok; }
        return lend(event,binding,event.arguments[event.id==menu_panel?2:0],
            event.id==menu_panel?Consumer::title_panel:Consumer::plain_title);
    }
    case menu_text:case menu_button: {
        const auto& binding=native_menu_model::row(native_menu_model::active(),row_index(event.frame->esi));
        if(!binding.bound) { handled=false;return Status::ok; }
        return lend(event,binding,event.arguments[0],
            event.id==menu_button?Consumer::button_row:Consumer::plain_row);
    }
    default:
        handled=false;
        return Status::ok;
    }
}

Handle active() { return native_menu_model::active(); }
Handle snapshot(Handle handle) { return native_menu_model::snapshot(handle); }
void retain(Handle handle) { native_menu_model::retain(handle); }
void release(Handle handle) { native_menu_model::release(handle); }
void activate(Handle handle) { native_menu_model::activate(handle); }
void deactivate() { native_menu_model::deactivate(); }
bool consuming() { return native_consuming; }
void bind_constructor_title(u64 token,const native_text_resource::TextSource& source) { title_sources.push_back({token,source}); }
void bind_constructor_row(u64 token,const native_text_resource::TextSource& source) { row_sources.push_back({token,source}); }
void unbind_constructor_source(u64 token) {
    for(auto* sources:{&title_sources,&row_sources})
        sources->erase(std::remove_if(sources->begin(),sources->end(),
            [token](const ConstructorSource& source){return source.token==token;}),sources->end());
}

void bind_title(TextComponent component,const char* original,const char* value) {
    const auto source=native_text_resource::from_request({component,original,value});
    native_menu_model::bind_title(active(),source);
}
void bind_row(u32 native_record,TextComponent component,const char* original,
    const char* value,bool action_suffix) {
    std::string prefix;
    if(action_suffix) {
        const auto* label=pointer<char>(native_record);
        prefix.assign(label,std::strchr(label,'.')+1);
    }
    const auto source=native_text_resource::from_request({component,original,value});
    native_menu_model::bind_row(active(),row_index(native_record),source,prefix);
}
Status resolve_title(std::vector<char>& encoded) {
    return resolve_binding(native_menu_model::title(active()),encoded);
}
Status resolve_row(u32 native_record,std::vector<char>& encoded) {
    return resolve_binding(native_menu_model::row(active(),row_index(native_record)),encoded);
}

Status paint(Handle handle) {
    const auto previous=active();
    if(previous) retain(previous);
    activate(handle);
    paint_result=Status::ok;
    using Paint=void (UWCN_CALL *)();
    const auto& style=native_menu_model::style(handle);
    painting=true;
    {
        native_component_style::PanelScope panel_style(style.panel);
        native_component_style::ButtonScope button_style(style.button);
        reinterpret_cast<Paint>(base+0xCFFB0)();
    }
    painting=false;
    native_menu_model::capture_into(handle);
    const auto status=paint_result;
    if(previous) {
        activate(previous);
        release(previous);
    } else deactivate();
    return status;
}

std::vector<std::uint8_t> save() {
    const auto model=native_menu_model::save();
    std::vector<std::uint8_t> payload;
    const auto model_bytes=static_cast<u32>(model.size());
    const auto count=static_cast<u32>(borrows.size());
    append(payload,&model_bytes,sizeof(model_bytes));
    append(payload,&count,sizeof(count));
    append(payload,model.data(),model_bytes);
    for(const auto& borrowed:borrows) {
        append(payload,&borrowed.token,sizeof(borrowed.token));
        append(payload,&borrowed.allocation,sizeof(borrowed.allocation));
    }
    write(payload,native_consuming?1u:0u);write_sources(payload,title_sources);write_sources(payload,row_sources);
    return payload;
}
void restore(const void* payload) {
    auto* cursor=static_cast<const std::uint8_t*>(payload);
    u32 model_bytes,count;
    std::memcpy(&model_bytes,cursor,sizeof(model_bytes));cursor+=sizeof(model_bytes);
    std::memcpy(&count,cursor,sizeof(count));cursor+=sizeof(count);
    native_menu_model::restore(cursor);cursor+=model_bytes;
    borrows.clear();
    for(u32 i=0;i<count;++i) {
        Borrow borrowed;
        std::memcpy(&borrowed.token,cursor,sizeof(borrowed.token));cursor+=sizeof(borrowed.token);
        std::memcpy(&borrowed.allocation,cursor,sizeof(borrowed.allocation));cursor+=sizeof(borrowed.allocation);
        borrows.push_back(borrowed);
    }
    native_consuming=read<u32>(cursor)!=0;read_sources(cursor,title_sources);read_sources(cursor,row_sources);
}
void shutdown() {
    // Outstanding native text calls retain resident allocations through state
    // handoff, just as the adapter's existing token-owned text loans do.
    borrows.clear();
    title_sources.clear();row_sources.clear();native_consuming=false;
    native_menu_model::initialize(0);
    base=0;host=nullptr;resolve=nullptr;encode_original=nullptr;enter_scope=nullptr;leave_scope=nullptr;painting=false;
}
}
