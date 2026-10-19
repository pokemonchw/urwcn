#include "native_menu_component.h"
#include "native_ui_scene.h"
#include <algorithm>
#include <cstring>
#include <utility>

namespace uwcn::adapter::native_menu_component {
namespace {
std::uintptr_t base{};
const HostApi* host{};
native_text_resource::Resolve resolve{};
native_text_resource::EncodeOriginal encode_original{};
DecodeOriginal decode_original{};
BeforeConsume before_consume{};
Enter enter_scope{};
Leave leave_scope{};
Measure measure{};
Status paint_result=Status::ok;
bool painting{};
Handle painting_source{};
bool native_consuming{};
struct ConstructorSource { u64 token;native_text_resource::TextSource source; };
std::vector<ConstructorSource> title_sources,row_sources;
struct Borrow { u64 token;u32 allocation; };
std::vector<Borrow> borrows;
enum Hook : u32 {
    constructor_begin=0x7E00,constructor_commit,paint_begin,paint_commit,
    row_commit,plain_title,row_annotation,annotation_origin,selector_width,renderer_selector_width
};
// Reuse the existing CALL hooks; installing another patch at these sites would
// replace the same native boundary twice. The root dispatch sends them here.
constexpr u32 menu_text=10,menu_panel=221,menu_button=222;
constexpr u32 rows_rva=0x5F4EF10;
Handle source_handle() { return painting?painting_source:native_menu_model::active(); }

template<class T> T* pointer(u32 value) {
    return reinterpret_cast<T*>(static_cast<std::uintptr_t>(value));
}
u32 address(const void* value) { return static_cast<u32>(reinterpret_cast<std::uintptr_t>(value)); }
u32 row_index(u32 native_record) {
    return (native_record-static_cast<u32>(base+rows_rva))/native_menu_model::row_stride;
}
native_text_resource::TextSource original_source(const char* text) {
    std::string utf8;
    // The configured decoder is the game's confirmed native single-byte /
    // proper-name input conversion, before any display transport is borrowed.
    decode_original(text,utf8);
    return native_text_resource::original_text(utf8.c_str());
}
void bind_original_title() {
    native_menu_model::bind_title(native_menu_model::active(),
        original_source(reinterpret_cast<const char*>(base+0x5F54A38)));
}
void bind_original_row(u32 index) {
    native_menu_model::bind_row(native_menu_model::active(),index,
        original_source(reinterpret_cast<const char*>(base+rows_rva+index*native_menu_model::row_stride)),{});
    native_menu_model::bind_annotation(native_menu_model::active(),index,
        original_source(reinterpret_cast<const char*>(base+rows_rva+index*native_menu_model::row_stride+0x64)));
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
Status measure_row(u32 index,std::int32_t& width) {
    std::vector<char> encoded;
    const auto status=resolve_binding(native_menu_model::row(source_handle(),index),encoded);
    if(status!=Status::ok) {paint_result=status;return status;}
    const auto measured=measure(encoded.data(),width);
    if(measured!=Status::ok) paint_result=measured;
    return measured;
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
    painting_source=0;
    native_consuming=false;title_sources.clear();row_sources.clear();
    borrows.clear();
    native_menu_model::initialize(base);
    // The predecessor's live native model is an actual source model, including
    // its current input fields. No past paint calls or page fields are inferred.
    native_menu_model::create_from_native();
}
void configure(const HostApi* api,native_text_resource::Resolve resolver,
    native_text_resource::EncodeOriginal encoder,DecodeOriginal decoder,
    BeforeConsume before,Enter enter,Leave leave) {
    host=api;
    resolve=resolver;
    encode_original=encoder;
    decode_original=decoder;
    before_consume=before;
    enter_scope=enter;
    leave_scope=leave;
    // The live predecessor model is adopted at initialize before services are
    // rebound. Its actual count identifies precisely the native active rows.
    bind_original_title();
    const auto count=*reinterpret_cast<const u32*>(base+0x5F54A34);
    for(u32 row=0;row<count;++row) bind_original_row(row);
}
void configure_measure(Measure callback) {measure=callback;}

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
    hooks.push_back({row_annotation,HookKind::call,0xD03C9,0x10E5A0,3,5,
        {0xE8,0xD2,0xE1,0x03,0x00}});
    hooks.push_back({annotation_origin,HookKind::inline_code,0xD03BB,0,0,7,
        {0x8D,0x0C,0xFD,0x0F,0,0,0}});
    hooks.push_back({selector_width,HookKind::inline_code,0xD07FB,0,0,7,
        {0x8D,0x04,0xCD,0,0,0,0}});
    hooks.push_back({renderer_selector_width,HookKind::inline_code,0xD0A49,0,0,7,
        {0x8D,0x04,0xCD,0,0,0,0}});
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
        native_ui_scene::menu_retired(active());native_menu_model::deactivate();
        return Status::ok;
    case constructor_commit:
        *reinterpret_cast<u32*>(base+0x5F54AB4)=0;
        native_menu_model::create_from_native();
        bind_original_title();
        if(!title_sources.empty()) native_menu_model::bind_title(active(),title_sources.back().source);
        result.resume_rva=0xCF988;
        return Status::ok;
    case row_commit:
        // Commit the original CF990 count store, after its English label,
        // annotation and action have entered their native record.
        *reinterpret_cast<u32*>(base+0x5F54A34)=event.frame->esi;
        native_menu_model::capture_into(native_menu_model::active());
        bind_original_row(event.frame->esi-1);
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
        native_ui_scene::menu_constructed(active());
        result.resume_rva=0xD03FD;
        return Status::ok;
    case menu_panel:case plain_title: {
        const auto consumer=event.id==menu_panel?Consumer::title_panel:Consumer::plain_title;
        if(!painting) {
            const auto status=before_consume(event,consumer);if(status!=Status::ok) return status;
        }
        const auto& binding=native_menu_model::title(source_handle());
        return lend(event,binding,event.arguments[event.id==menu_panel?2:0],consumer);
    }
    case menu_text:case menu_button: {
        const auto consumer=event.id==menu_button?Consumer::button_row:Consumer::plain_row;
        if(!painting) {
            const auto status=before_consume(event,consumer);if(status!=Status::ok) return status;
        }
        const auto& binding=native_menu_model::row(source_handle(),row_index(event.frame->esi));
        return lend(event,binding,event.arguments[0],consumer);
    }
    case row_annotation:
        return lend(event,native_menu_model::annotation(source_handle(),row_index(event.frame->esi)),
            event.arguments[0],Consumer::annotation);
    case annotation_origin: {
        std::int32_t width;const auto status=measure_row(row_index(event.frame->esi),width);
        if(status!=Status::ok) return status;
        // Replace only the original LEA's width operand. The following native
        // ADD [row+D0] remains the owner of the annotation's actual position.
        event.frame->ecx=static_cast<u32>(width+0xF);result.resume_rva=0xD03C2;return Status::ok;
    }
    case selector_width:case renderer_selector_width: {
        // Both native strlen exits keep EDX = original row address + 1.
        std::int32_t width;const auto status=measure_row(row_index(event.frame->edx-1),width);
        if(status!=Status::ok) return status;
        event.frame->eax=static_cast<u32>(width);
        result.resume_rva=event.id==selector_width?0xD0802:0xD0A50;return Status::ok;
    }
    default:
        handled=false;
        return Status::ok;
    }
}

Handle active() { return native_menu_model::active(); }
Handle snapshot(Handle handle) { return native_menu_model::snapshot(handle); }
Handle input_owner(Handle handle) { return native_menu_model::input_owner(handle); }
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
        prefix.assign(label,static_cast<std::size_t>(std::strchr(label,'.')+1-label));
    }
    const auto source=native_text_resource::from_request({component,original,value});
    native_menu_model::bind_row(active(),row_index(native_record),source,prefix);
}
Status resolve_title(std::vector<char>& encoded) {
    return resolve_binding(native_menu_model::title(source_handle()),encoded);
}
Status resolve_row(u32 native_record,std::vector<char>& encoded) {
    return resolve_binding(native_menu_model::row(source_handle(),row_index(native_record)),encoded);
}
void commit_row(Handle menu,u32 index,const native_text_resource::TextSource& source) {
    const auto owner=input_owner(menu);
    native_menu_model::bind_row(owner,index,source,{});
    native_menu_model::bind_annotation(owner,index,
        original_source(reinterpret_cast<const char*>(base+rows_rva+index*native_menu_model::row_stride+0x64)));
}

Status paint(Handle handle) {
    const auto previous=active();
    if(previous) retain(previous);
    activate(handle);
    paint_result=Status::ok;
    using Paint=void (UWCN_CALL *)();
    const auto& style=native_menu_model::style(handle);
    painting_source=handle;
    painting=true;
    {
        native_component_style::PanelScope panel_style(style.panel);
        native_component_style::ButtonScope button_style(style.button);
        reinterpret_cast<Paint>(base+0xCFFB0)();
    }
    painting=false;
    painting_source=0;
    native_menu_model::capture_into(active());
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
    base=0;host=nullptr;resolve=nullptr;encode_original=nullptr;decode_original=nullptr;before_consume=nullptr;enter_scope=nullptr;leave_scope=nullptr;measure=nullptr;painting=false;painting_source=0;
}
}
