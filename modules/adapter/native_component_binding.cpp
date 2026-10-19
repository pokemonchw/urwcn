#include "native_component_binding.h"
#include "native_component_style.h"
#include "native_root_component.h"
#include "native_ui_scene.h"
#include "native_menu_model.h"
#include "native_menu_component.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <iterator>
#include <map>
#include <optional>
#include <utility>

namespace uwcn::adapter::native_component_binding {
namespace {
using namespace native_component_model;
using namespace native_text_resource;
std::uintptr_t base{};
PaintServices services{};
DecodeParserSource decode_parser_source{};
bool preparing{};
bool restoring_builder{};
bool builder_exists{};
u32 parser_owner_depth{};
u32 source_resolution_depth{};
ParagraphSource builder;
std::map<std::pair<u64,TextComponent>,TextSource> fields;
std::map<u32,HookSpec> metadata;
enum Hook:u32 {
    credits_break_reset=0x5500,credits_break_append,parser_entry,
    parser_clear_first,parser_clear_second,parser_clear_third,parser_clear_fourth
};

struct EventInputs {
    u64 token;
    u32 id,ecx,edx;
    std::array<u32,5> arguments;
    std::optional<TextSource> text;
    std::optional<std::int32_t> center;
    std::optional<u32> native_record;
    bool explicit_source{};
};
std::vector<EventInputs> event_inputs;
struct CallText { PreparedText text;u32 menu{};Handle component{}; };
std::map<u64,CallText> calls;
struct ParserBinding { u64 token;TextSource source; };
std::vector<ParserBinding> parser_bindings;

template<class T> T* pointer(u32 value) {
    return reinterpret_cast<T*>(static_cast<std::uintptr_t>(value));
}
u32 address(const void* value) {
    return static_cast<u32>(reinterpret_cast<std::uintptr_t>(value));
}
std::int32_t signed_value(u32 value) { return static_cast<std::int32_t>(value); }
NativeAnchor origin(const EventInputs& input) {
    return {native_input(signed_value(input.ecx)),native_input(signed_value(input.edx))};
}
HookSpec call(u32 id,u32 site,u32 target,u32 arguments) {
    HookSpec result{id,HookKind::call,site,target,arguments,5,{0xE8}};
    const auto displacement=target-site-5;
    std::memcpy(result.expected+1,&displacement,4);return result;
}
SourceKey key(const HookSpec& hook,const EventInputs& input,TextComponent component) {
    const u64 identity=input.native_record
        ? (static_cast<u64>(hook.site_rva)<<32)|*input.native_record : hook.site_rva;
    return {native_root_component::current(),identity,static_cast<u32>(component)};
}
Status resolve(const TextSource& text,std::vector<char>& encoded) {
    preparing=true;
    const auto status=resolve_source(text,services.resolve,services.encode_original,encoded);
    preparing=false;return status;
}

bool centered_field(u32 site) {
    switch(site) {
    case 0x1247A7:case 0x1248A1:case 0x1248F9:case 0x124949:
    case 0x124A59:case 0x124AE0:case 0x1249B8:case 0x124B2E:
    case 0xDF115:return true;
    default:return false;
    }
}
TextComponent paragraph_field() {
    const auto semantic=std::find_if(builder.fragments.begin(),builder.fragments.end(),
        [](const TextSource& source){return source.policy==TextPolicy::semantic;});
    return semantic==builder.fragments.end() ? TextComponent::load_character : semantic->component;
}
Status parse_prepared(const PreparedText& prepared) {
    restoring_builder=true;
    parse_prepared_paragraph(builder,prepared.fragments);
    restoring_builder=false;return Status::ok;
}
Status prepare_builder(const ParagraphSource& source,PreparedText& prepared) {
    for(const auto& fragment:source.fragments) {
        prepared.fragments.emplace_back();
        auto status=resolve(fragment,prepared.fragments.back());
        if(status!=Status::ok) return status;
        status=services.paragraph_words(prepared.fragments.back());
        if(status!=Status::ok) return status;
    }
    return Status::ok;
}
Status observe_parser(const NativeEvent& event) {
    if(restoring_builder || parser_owner_depth || native_ui_scene::materializing()) return Status::ok;
    TextSource source;
    if(parser_bindings.empty()) {
        std::string original;
        const auto status=decode_parser_source(pointer<const char>(event.frame->edx),original);
        if(status!=Status::ok) return status;
        source=original_text(original.c_str());
    } else source=parser_bindings.back().source;
    if(event.frame->ecx) builder.fragments.clear();
    builder.fragments.push_back(std::move(source));builder_exists=true;
    return Status::ok;
}
Status construct(const NativeEvent& event,const HookSpec& hook,const EventInputs& input) {
    if(consuming_component()) return Status::ok;
    const auto target=hook.target_rva;
    const auto& args=input.arguments;
    Handle handle{};
    u32 text_argument{};
    if(target==0x10EB40) {
        if(signed_value(args[1])==-1) return Status::ok;
        const ParagraphInputs inputs{origin(input),native_input(signed_value(args[0])),
            native_input(signed_value(args[1])),args[2],args[3]};
        handle=upsert_paragraph(key(hook,input,paragraph_field()),inputs,builder);
    } else {
        if(!input.text) return Status::ok;
        const auto source_key=key(hook,input,input.text->component);
        switch(target) {
        case 0x116270: {
            const PanelInputs inputs{origin(input),native_input(signed_value(args[0])),
                native_input(signed_value(args[1])),args[3],args[4],native_component_style::capture_panel()};
            handle=upsert_panel(source_key,inputs,*input.text);text_argument=2;break;
        }
        case 0x115E70: {
            // D01A5 belongs to the retained native menu instance, whose model
            // already owns its native title and row record identities.
            if(hook.site_rva==0xD01A5) return Status::ok;
            const LegacyPanelInputs inputs{origin(input),native_input(signed_value(args[0])),
                native_input(signed_value(args[1])),args[3],native_component_style::capture_panel()};
            handle=upsert_legacy_panel(source_key,inputs,*input.text);text_argument=2;break;
        }
        case 0x114680: {
            if(hook.site_rva==0xD031F) return Status::ok;
            const ButtonInputs inputs{origin(input),0,native_component_style::capture_button()};
            handle=upsert_button(source_key,inputs,*input.text);break;
        }
        case 0x10E910: {
            const CenteredTextInputs inputs{origin(input),native_input(signed_value(args[0])),args[2],args[3]};
            handle=upsert_centered_text(source_key,inputs,*input.text);text_argument=1;break;
        }
        case 0x10E5A0: {
            // These two leaves consume the actual retained Menu records. The
            // whole native Menu owns them, rather than independent root fields.
            if(!input.explicit_source || parser_owner_depth ||
                hook.site_rva==0xD027F || hook.site_rva==0xD0367) return Status::ok;
            if(centered_field(hook.site_rva) && !input.center) return Status::ok;
            auto anchor=origin(input);
            if(input.center) anchor.x=native_center(*input.center);
            const TextBlockInputs inputs{anchor,args[1],args[2]};
            handle=upsert_text_block(source_key,inputs,*input.text);break;
        }
        case 0xE10F0: {
            const StatisticLabelInputs inputs{native_input(signed_value(input.edx)),signed_value(args[1])};
            handle=upsert_statistic_label(source_key,inputs,*input.text);break;
        }
        case 0xCFAF0: {
            const auto menu=native_menu_model::active();
            const bool explicit_row=*reinterpret_cast<const u32*>(base+0x5F549B0)!=0 && input.ecx!=0x423;
            const auto row=explicit_row ? *reinterpret_cast<const u32*>(base+0x5F54A34) : 0u;
            const ActionButtonInputs inputs{menu,input.ecx,
                explicit_row?ActionLocator::native_row:ActionLocator::action,row,
                {native_input(signed_value(input.edx)),native_input(signed_value(args[0]))}};
            const auto native_source=explicit_row ? 0x5F4EF10+row*native_menu_model::row_stride : input.ecx;
            const SourceKey action_key{native_root_component::current(),
                (static_cast<u64>(menu)<<32)|native_source,static_cast<u32>(input.text->component)};
            handle=upsert_action_button(action_key,inputs,*input.text);text_argument=1;
            calls[event.token].menu=menu;break;
        }
        case 0xF8F80:case 0xF9030: {
            const NativeHeadingInputs inputs{native_component_style::capture_panel()};
            handle=upsert_native_heading(source_key,target==0xF9030,inputs,*input.text);break;
        }
        default:return Status::ok;
        }
    }
    auto& prepared=calls[event.token].text;
    preparing=true;const auto status=prepare(handle,services,prepared);preparing=false;
    if(status!=Status::ok) return status;
    if(target==0x10EB40) {
        const auto parsed=parse_prepared(prepared);if(parsed!=Status::ok) return parsed;
    } else if(target==0xF8F80 || target==0xF9030)
        event.frame->ecx=address(prepared.fragments.front().data());
    else event.arguments[text_argument]=address(prepared.fragments.front().data());
    calls[event.token].component=handle;
    native_ui_scene::component_constructed(handle);
    return Status::ok;
}

struct Writer {
    std::vector<std::uint8_t> bytes;
    template<class T> void scalar(T value) {
        const auto* p=reinterpret_cast<const std::uint8_t*>(&value);bytes.insert(bytes.end(),p,p+sizeof(value));
    }
    void string(const std::string& value) {
        scalar(static_cast<u32>(value.size()));bytes.insert(bytes.end(),value.begin(),value.end());
    }
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
    TextSource text() {
        const auto component=static_cast<TextComponent>(scalar<u32>());
        auto original=string(),value=string();const bool has_value=scalar<u32>()!=0;
        const auto policy=static_cast<TextPolicy>(scalar<u32>());
        auto prefix=string(),suffix=string();
        return {component,std::move(original),std::move(value),has_value,policy,std::move(prefix),std::move(suffix)};
    }
};
}

void configure(std::uintptr_t image_base,const PaintServices& paint_services) {
    base=image_base;services=paint_services;preparing=false;restoring_builder=false;
    parser_owner_depth=0;source_resolution_depth=0;
    builder_exists=false;builder.fragments.clear();fields.clear();metadata.clear();
    calls.clear();parser_bindings.clear();event_inputs.clear();
}
void set_parser_source_decoder(DecodeParserSource decoder) { decode_parser_source=decoder; }
void register_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(call(credits_break_reset,0x124523,0x162300,0));
    hooks.push_back(call(credits_break_append,0x124547,0x162300,0));
    HookSpec parser{parser_entry,HookKind::inline_code,0x162306,0,0,5,{0xA1}};
    const auto cookie=static_cast<u32>(base+0x1E200C);std::memcpy(parser.expected+1,&cookie,4);
    hooks.push_back(parser);
    hooks.push_back(call(parser_clear_first,0x3A716,0x1620C0,0));
    hooks.push_back(call(parser_clear_second,0xADD7B,0x1620C0,0));
    hooks.push_back(call(parser_clear_third,0xAED49,0x1620C0,0));
    hooks.push_back(call(parser_clear_fourth,0xE4CE1,0x1620C0,0));
    metadata.clear();for(const auto& hook:hooks) metadata.emplace(hook.id,hook);
}
void begin_event(const NativeEvent& event) {
    EventInputs input{event.token,event.id,event.frame->ecx,event.frame->edx,{},{},{},{},false};
    const auto hook=metadata.find(event.id);
    if(hook!=metadata.end() && hook->second.kind==HookKind::call) {
        const auto count=std::min<u32>(event.argument_count,static_cast<u32>(input.arguments.size()));
        std::copy_n(event.arguments,count,input.arguments.begin());
        const char* original=nullptr;
        switch(hook->second.target_rva) {
        case 0x116270:case 0x115E70:original=pointer<const char>(input.arguments[2]);break;
        case 0x114680:case 0xE10F0:original=pointer<const char>(input.arguments[0]);break;
        case 0x10E910:case 0xCFAF0:original=pointer<const char>(input.arguments[1]);break;
        case 0xF8F80:case 0xF9030:original=pointer<const char>(input.ecx);break;
        default:break;
        }
        if(original && event.phase==NativePhase::before && !native_ui_scene::materializing()) {
            std::string neutral;decode_parser_source(original,neutral);input.text=original_text(neutral.c_str());
        }
    }
    event_inputs.push_back(std::move(input));
}
void note_source(const TextRequest& request) {
    if(preparing || source_resolution_depth || restoring_builder || native_ui_scene::materializing()) return;
    const auto source=from_request(request);
    fields.insert_or_assign({native_root_component::current(),request.component},source);
    event_inputs.back().text=source;
    event_inputs.back().explicit_source=true;
}
void bind_source(const NativeEvent&,const TextSource& source) {
    event_inputs.back().text=source;
    event_inputs.back().explicit_source=true;
    if(source.policy==TextPolicy::semantic)
        fields.insert_or_assign({native_root_component::current(),source.component},source);
}
void note_source_for_consumer(const NativeEvent&,TextComponent component) {
    event_inputs.back().text=fields.find({native_root_component::current(),component})->second;
    event_inputs.back().explicit_source=true;
}
void note_original_for_consumer(const NativeEvent&,const char* original) {
    event_inputs.back().text=original_text(original);
    event_inputs.back().explicit_source=true;
}
void note_prefix(const NativeEvent&,const char* prefix) {
    auto& source=*event_inputs.back().text;source.prefix=prefix;
    if(source.policy==TextPolicy::semantic)
        fields.insert_or_assign({native_root_component::current(),source.component},source);
}
void note_suffix(const NativeEvent&,const char* suffix) {
    auto& source=*event_inputs.back().text;source.suffix=suffix;
    if(source.policy==TextPolicy::semantic)
        fields.insert_or_assign({native_root_component::current(),source.component},source);
}
void note_center(const NativeEvent&,std::int32_t center) { event_inputs.back().center=center; }
void note_native_record(const NativeEvent&,u32 record) { event_inputs.back().native_record=record; }
const TextSource* current_source() {
    const auto& source=event_inputs.back().text;return source ? &*source : nullptr;
}
const TextSource& field_source(TextComponent component) {
    return fields.find({native_root_component::current(),component})->second;
}
const TextSource* current_event_source() { return current_source(); }
const ParagraphSource& current_paragraph_source() { return builder; }
bool current_event_center(std::int32_t& center) {
    const auto& value=event_inputs.back().center;if(!value) return false;center=*value;return true;
}
bool current_event_record(u32& record) {
    const auto& value=event_inputs.back().native_record;if(!value) return false;record=*value;return true;
}
bool consuming_component() {
    return native_menu_component::consuming() ||
        std::any_of(calls.begin(),calls.end(),[](const auto& call){return call.second.component!=0;});
}
bool parser_owned() { return parser_owner_depth!=0; }
void begin_source_resolution() { ++source_resolution_depth; }
void end_source_resolution() { --source_resolution_depth; }
void bind_parser_source(u64 token,const TextSource& source) { parser_bindings.push_back({token,source}); }
void unbind_parser_source(u64 token) {
    parser_bindings.erase(std::remove_if(parser_bindings.begin(),parser_bindings.end(),
        [token](const ParserBinding& binding){return binding.token==token;}),parser_bindings.end());
}
void begin_parser_owner() { ++parser_owner_depth; }
void end_parser_owner() { --parser_owner_depth; }
Status finish_event(const NativeEvent& event,DispatchResult&,Status native_dispatch_status) {
    const auto input=std::move(event_inputs.back());event_inputs.pop_back();
    if(native_dispatch_status!=Status::ok) {
        calls.erase(event.token);unbind_parser_source(event.token);
        native_menu_component::unbind_constructor_source(event.token);return native_dispatch_status;
    }
    if(event.phase==NativePhase::after) {
        if(event.id>=parser_clear_first && event.id<=parser_clear_fourth &&
            !restoring_builder && !parser_owner_depth && !native_ui_scene::materializing()) {
            builder.fragments.clear();builder_exists=true;
        }
        const auto native_call=calls.find(event.token);
        if(native_call!=calls.end() && native_call->second.menu)
            native_menu_model::capture_into(native_call->second.menu);
        calls.erase(event.token);unbind_parser_source(event.token);
        native_menu_component::unbind_constructor_source(event.token);return Status::ok;
    }
    if(event.id==parser_entry) return observe_parser(event);
    const auto metadata_entry=metadata.find(event.id);
    if(metadata_entry==metadata.end() || metadata_entry->second.kind!=HookKind::call ||
        native_ui_scene::materializing()) return Status::ok;
    const auto& hook=metadata_entry->second;
    if((hook.target_rva==0xCF790 || hook.target_rva==0xCF990) && input.text) {
        event.frame->edx=input.edx;
        if(hook.target_rva==0xCF790) native_menu_component::bind_constructor_title(event.token,*input.text);
        else native_menu_component::bind_constructor_row(event.token,*input.text);
        return Status::ok;
    }
    if(hook.target_rva==0x162300) {
        if(parser_owner_depth) return Status::ok;
        auto source=input.text;
        if(event.id==credits_break_reset || event.id==credits_break_append)
            source=original_text(pointer<const char>(input.edx));
        if(source) {
            bind_parser_source(event.token,*source);
            auto& prepared=calls[event.token].text;prepared.fragments.emplace_back();
            auto status=resolve(*source,prepared.fragments.back());if(status!=Status::ok) return status;
            status=services.paragraph_words(prepared.fragments.back());if(status!=Status::ok) return status;
            event.frame->edx=address(prepared.fragments.back().data());
        }
        return Status::ok;
    }
    if(!native_root_component::current()) return Status::ok;
    return construct(event,hook,input);
}
bool has_paragraph_builder() { return builder_exists; }
Status restore_paragraph_builder() {
    PreparedText prepared;const auto status=prepare_builder(builder,prepared);
    return status==Status::ok ? parse_prepared(prepared) : status;
}
Status replace_paragraph_builder(const ParagraphSource& source) {
    builder=source;builder_exists=true;return restore_paragraph_builder();
}
void retire_root(u64 owner) {
    for(auto field=fields.begin();field!=fields.end();) {
        if(field->first.first==owner) field=fields.erase(field);else ++field;
    }
}
std::vector<std::uint8_t> save() {
    Writer output;output.scalar(builder_exists?1u:0u);output.scalar(static_cast<u32>(builder.fragments.size()));
    for(const auto& fragment:builder.fragments) output.text(fragment);
    output.scalar(static_cast<u32>(fields.size()));
    for(const auto& [key,source]:fields) { output.scalar(key.first);output.scalar(static_cast<u32>(key.second));output.text(source); }
    return std::move(output.bytes);
}
void restore(const void* payload) {
    Reader input{static_cast<const std::uint8_t*>(payload)};builder_exists=input.scalar<u32>()!=0;
    builder.fragments.clear();const auto fragments=input.scalar<u32>();
    for(u32 i=0;i<fragments;++i) builder.fragments.push_back(input.text());
    fields.clear();const auto count=input.scalar<u32>();
    for(u32 i=0;i<count;++i) {
        const auto owner=input.scalar<u64>();const auto component=static_cast<TextComponent>(input.scalar<u32>());
        fields.emplace(std::make_pair(owner,component),input.text());
    }
    calls.clear();parser_bindings.clear();event_inputs.clear();preparing=false;restoring_builder=false;parser_owner_depth=0;source_resolution_depth=0;
}
void shutdown() {
    base=0;services={};decode_parser_source=nullptr;fields.clear();metadata.clear();builder.fragments.clear();
    builder_exists=false;calls.clear();parser_bindings.clear();event_inputs.clear();preparing=false;restoring_builder=false;parser_owner_depth=0;source_resolution_depth=0;
}
}
