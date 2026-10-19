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

// Exact replacements for the native UI operand instructions below. These
// synchronous scalar loans do not name or modify a player's original fields.
extern "C" {
uwcn::u32 uwcn_summary_operand_resume{},uwcn_summary_layout{},uwcn_summary_thirst{},uwcn_summary_warmth{};
__attribute__((naked)) void UWCN_CALL uwcn_summary_compare_zero() {
    __asm__ __volatile__("cmpl $0,_uwcn_summary_layout\n\tjmp *_uwcn_summary_operand_resume\n\t");
}
__attribute__((naked)) void UWCN_CALL uwcn_summary_compare_ebx() {
    __asm__ __volatile__("cmpl %ebx,_uwcn_summary_layout\n\tjmp *_uwcn_summary_operand_resume\n\t");
}
__attribute__((naked)) void UWCN_CALL uwcn_summary_multiply_thirst() {
    __asm__ __volatile__("imull _uwcn_summary_thirst\n\tjmp *_uwcn_summary_operand_resume\n\t");
}
__attribute__((naked)) void UWCN_CALL uwcn_summary_load_warmth() {
    __asm__ __volatile__("movss _uwcn_summary_warmth,%xmm2\n\tjmp *_uwcn_summary_operand_resume\n\t");
}
}

namespace uwcn::adapter::native_component_binding {
namespace {
using namespace native_component_model;
using namespace native_text_resource;
std::uintptr_t base{};
PaintServices services{};
DecodeParserSource decode_parser_source{};
EncodeParserSource encode_parser_source{};
bool preparing{};
bool restoring_builder{};
bool builder_exists{};
u32 parser_owner_depth{};
u32 source_resolution_depth{};
ParagraphSource builder;
// The native parser is a source-language builder as well as a UI scratch
// resource. These nodes retain its actual input grammar, never encoded words.
enum class BuilderOperation:u32 { append,grammar,count_zero,compose };
struct BuilderNode {
    BuilderOperation operation;u32 first{},second{};std::string native_original;
};
std::vector<BuilderNode> builder_nodes;
std::map<std::pair<u64,TextComponent>,TextSource> fields;
std::map<u32,HookSpec> metadata;
enum Hook:u32 {
    credits_break_reset=0x5500,credits_break_append,parser_entry,
    parser_clear_first,parser_clear_second,parser_clear_third,parser_clear_fourth,
    compound_hint_secondary=0x5507,parser_grammar,parser_compose_first,parser_compose_second,
    parser_count_zero_first,parser_count_zero_second,parser_help_clear,
    world_map_first,world_map_second,world_map_third,world_map_marker,world_map_controls,
    hud_status_first,hud_status_bar_first=hud_status_first+10,
    hud_status_weight=hud_status_bar_first+10,hud_summary_first,
    hud_summary_operand_first=hud_summary_first+5,
    parser_count_capture_first=hud_summary_operand_first+17
};
struct GrammarStart {u32 consumer,capture;};
constexpr GrammarStart grammar_starts[]{
    {0x3A7EE,0x3A78E},{0x3A86E,0x3A814},{0x3A8EE,0x3A894},
    {0x3A96E,0x3A914},{0x3A9EE,0x3A994},{0xAF38E,0xAF311},
    {0xAF5D6,0xAF4B1},{0xAF7FF,0xAF6BA},
    {0x40E78,0},{0xAE33A,0},{0x13402D,0},{0x138A95,0}
};
std::map<u32,u32> grammar_starts_at;
enum class SummaryOperand {layout_zero,layout_ebx,nutrition_esi,nutrition_ecx,hunger_ecx,thirst_multiply,thirst_eax,vigour_edx,warmth_xmm};
struct SummaryRead {u32 site,field;SummaryOperand operand;};
constexpr SummaryRead summary_reads[]{
    {0xF9941,0x1E6EC4,SummaryOperand::layout_zero},{0xF9CDE,0x1E6EC4,SummaryOperand::layout_zero},
    {0xF9D6D,0x1E6EC4,SummaryOperand::layout_ebx},{0xF9E1E,0x1E6EC4,SummaryOperand::layout_zero},
    {0xF9EA4,0x1E6EC4,SummaryOperand::layout_ebx},{0xF9EE2,0x1E6EC4,SummaryOperand::layout_zero},
    {0xF9F9D,0x1E6EC4,SummaryOperand::layout_zero},{0xFA081,0x1E6EC4,SummaryOperand::layout_zero},
    {0xF9BF6,0xA32B17C,SummaryOperand::nutrition_esi},{0xF9EEB,0xA32B17C,SummaryOperand::nutrition_ecx},
    {0xF9F27,0xA32B17C,SummaryOperand::nutrition_ecx},{0xF9C0D,0xA32BCE8,SummaryOperand::hunger_ecx},
    {0xF9DC3,0xA32B0D4,SummaryOperand::thirst_multiply},{0xF9E06,0xA32B0D4,SummaryOperand::thirst_eax},
    {0xFA0A2,0xA32B0D8,SummaryOperand::vigour_edx},{0xFA190,0xA32B0D8,SummaryOperand::vigour_edx},
    {0x15F486,0xA32BD14,SummaryOperand::warmth_xmm}
};
// Each operand is the real native record Y field loaded by that exact caller.
// This is source identity metadata; no rectangle or row layout is specified.
struct HudValueCall {u32 site,target,record_field;};
constexpr HudValueCall hud_value_calls[]{
    {0xFF07B,0xFEF00,0xA40EB5C},{0xFF10F,0xFEF00,0xA40EB60},
    {0x102DBA,0xFEF00,0xA40EB30},{0x102F71,0xFEF00,0xA40EB34},
    {0x102FE1,0xFEF00,0xA40EB38},{0x10306D,0xFEF00,0xA40EB3C},
    {0x1030B0,0xFEF00,0xA40EB40},{0x103141,0xFEF00,0xA40EB44},
    {0x10318D,0xFEF00,0xA40EB48},{0x103242,0xFEF00,0xA40EB4C},
    {0xFF131,0xFEE50,0xA40EB60},{0x102DCD,0xFEE50,0xA40EB30},
    {0x102F84,0xFEE50,0xA40EB34},{0x103080,0xFEE50,0xA40EB3C},
    {0x103154,0xFEE50,0xA40EB44},{0x10326B,0xFEE50,0xA40EB4C}
};

struct EventInputs {
    u64 token;
    u32 id,ecx,edx;
    std::array<u32,5> arguments;
    std::optional<TextSource> text;
    std::optional<std::int32_t> center;
    std::optional<u32> native_record;
    std::optional<u32> native_field;
    bool explicit_source{};
};
std::vector<EventInputs> event_inputs;
struct CallText { PreparedText text;u32 menu{};Handle component{};bool entered{}; };
std::map<u64,CallText> calls;
struct ParserBinding { u64 token;TextSource source; };
std::vector<ParserBinding> parser_bindings;

const HudStatusSummaryInputs* summary_source() {
    if(const auto* source=painting_hud_status_summary()) return source;
    for(const auto& [token,call]:calls) {
        (void)token;
        if(call.component && get(call.component).kind==Kind::hud_status_summary)
            return &std::get<HudStatusSummaryInputs>(get(call.component).inputs);
    }
    return nullptr;
}

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
    return {native_root_component::current(),identity,input.native_field.value_or(static_cast<u32>(component))};
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
Status observe_parser(const NativeEvent& event) {
    if(restoring_builder || parser_owner_depth || native_ui_scene::materializing()) return Status::ok;
    TextSource source;
    if(parser_bindings.empty()) {
        std::string original;
        const auto status=decode_parser_source(pointer<const char>(event.frame->edx),original);
        if(status!=Status::ok) return status;
        source=original_text(original.c_str());
    } else source=parser_bindings.back().source;
    if(event.frame->ecx) clear_paragraph_builder();
    const auto index=static_cast<u32>(builder.fragments.size());
    std::string native_original;
    if(source.policy==TextPolicy::original) {
        if(parser_bindings.empty()) native_original=pointer<const char>(event.frame->edx);
        else {
            std::vector<char> bytes;const auto neutral=source.prefix+source.original+source.suffix;
            const auto status=encode_parser_source(neutral.c_str(),bytes);if(status!=Status::ok) return status;
            native_original.assign(bytes.data(),bytes.size()-1);
        }
    }
    builder.fragments.push_back(std::move(source));builder_exists=true;
    builder_nodes.push_back({BuilderOperation::append,index,0,std::move(native_original)});
    return Status::ok;
}
bool observing_builder() {
    return !restoring_builder && !parser_owner_depth && !native_ui_scene::materializing();
}
Status restore_native_builder() {
    using Reset=void (UWCN_CALL *)();using Parse=void (__fastcall *)(u32,const char*);
    using Grammar=void (__fastcall *)(u32,u32);using Compose=const char* (UWCN_CALL *)();
    restoring_builder=true;
    reinterpret_cast<Reset>(base+0x1620C0)();
    std::vector<u32> counts(builder.fragments.size()+1);
    for(const auto& node:builder_nodes) {
        switch(node.operation) {
        case BuilderOperation::append: {
            const auto& source=builder.fragments[node.first];
            if(source.policy==TextPolicy::original)
                reinterpret_cast<Parse>(base+0x162300)(0,node.native_original.c_str());
            else {
                std::vector<char> encoded;
                auto status=resolve(source,encoded);
                if(status!=Status::ok) { restoring_builder=false;return status; }
                if(prepare_paragraph_fragment(source,encoded)) {
                    status=services.paragraph_words(encoded);
                    if(status!=Status::ok) { restoring_builder=false;return status; }
                    reinterpret_cast<Parse>(base+0x162300)(0,encoded.data());
                }
            }
            counts[node.first+1]=*reinterpret_cast<const u32*>(base+0xA225314);
            break;
        }
        case BuilderOperation::grammar:
            reinterpret_cast<Grammar>(base+0x161E90)(counts[node.first],node.second);break;
        case BuilderOperation::count_zero:
            *reinterpret_cast<u32*>(base+0xA225314)=0;break;
        case BuilderOperation::compose:
            // 162100 owns a 1024-slot native source-string ring. Rebuild the
            // same resource through its original function, without advancing
            // the ring to a different source resource during locale painting.
            *reinterpret_cast<u32*>(base+0xA44B7A8)=(node.first+1023u)&1023u;
            reinterpret_cast<Compose>(base+0x162100)();break;
        }
    }
    restoring_builder=false;return Status::ok;
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
    } else if(target==0x605B0) {
        const WorldMapInputs inputs{signed_value(input.ecx),signed_value(input.edx),args[0],args[1],
            *reinterpret_cast<const std::uint8_t*>(base+0x2F7FD3)};
        handle=upsert_world_map(key(hook,input,TextComponent::load_character),inputs);
    } else if(target==0x60360) {
        const WorldMapMarkerInputs inputs{args[0],*reinterpret_cast<const std::int32_t*>(base+0x1E2C10),
            *reinterpret_cast<const std::int32_t*>(base+0x1E2C14),*reinterpret_cast<const std::int32_t*>(base+0xEFA84C),
            *reinterpret_cast<const std::int32_t*>(base+0x14FBC58)};
        handle=upsert_world_map_marker(key(hook,input,TextComponent::load_character),inputs);
    } else if(target==0x60450) {
        const WorldMapControlsInputs inputs{*reinterpret_cast<const std::uint8_t*>(base+0x2EEC17),
            *reinterpret_cast<const u32*>(base+0xA211068)};
        handle=upsert_world_map_controls(key(hook,input,TextComponent::load_character),inputs);
    } else if(target==0xF8E20) {
        std::string label,value;
        auto status=decode_parser_source(pointer<const char>(args[0]),label);if(status!=Status::ok) return status;
        status=decode_parser_source(pointer<const char>(args[1]),value);if(status!=Status::ok) return status;
        const auto label_source=args[0]==static_cast<u32>(base+0x1AA240) ? original_text(label.c_str()) :
            from_request({TextComponent::hud_label,label.c_str(),nullptr});
        const HudStatusCellInputs inputs{signed_value(input.ecx),signed_value(input.edx),args[2],args[4],
            *reinterpret_cast<const u32*>(base+0x61BBCEC),*reinterpret_cast<const u32*>(base+0xA1C0EBC),
            original_text(value.c_str())};
        const SourceKey source_key{native_root_component::current(),0xA40EB30ull+args[4]*4ull,0};
        handle=upsert_hud_status_cell(source_key,inputs,label_source);
    } else if(target==0xFEE50 || target==0xFEF00) {
        const auto native_record=std::find_if(std::begin(hud_value_calls),std::end(hud_value_calls),
            [&](const HudValueCall& value){return value.site==hook.site_rva;});
        const SourceKey source_key{native_root_component::current(),native_record->record_field,0};
        if(target==0xFEF00) handle=update_hud_status_bar(source_key,signed_value(args[0]),signed_value(args[1]));
        else {
            TextSource source;
            if(hook.site_rva==0x102DCD) {
                std::string original;const auto status=decode_parser_source(pointer<const char>(args[0]),original);
                if(status!=Status::ok) return status;
                source=original_text(original.c_str());
            } else source=*input.text;
            handle=update_hud_status_text(source_key,source,args[1]);
        }
    } else if(target==0xF9910) {
        const HudStatusSummaryInputs inputs{*reinterpret_cast<const u32*>(base+0x1E6EC4),
            *reinterpret_cast<const u32*>(base+0xA32B17C),*reinterpret_cast<const std::uint8_t*>(base+0xA32BCE8),
            *reinterpret_cast<const u32*>(base+0xA32B0D4),*reinterpret_cast<const u32*>(base+0xA32B0D8),
            *reinterpret_cast<const u32*>(base+0xA32BD14),*reinterpret_cast<const u32*>(base+0x61BBCEC),
            *reinterpret_cast<const u32*>(base+0xA1C0EBC),native_component_style::capture_panel()};
        handle=upsert_hud_status_summary({native_root_component::current(),0xF9910,0},inputs);
    } else {
        if(!input.text) return Status::ok;
        const auto source_key=key(hook,input,input.text->component);
        switch(target) {
        case 0x116270: {
            // FA33F constructs the complete MessageFlow background resource.
            // That parent owns this Panel source and its native consumption.
            if(hook.site_rva==0xFA33F) return Status::ok;
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
                {native_input(signed_value(input.edx)),native_input(signed_value(args[0]))},
                {*reinterpret_cast<const u32*>(base+0x5F54A30),*reinterpret_cast<const u32*>(base+0x5F54A9C)}};
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
        case 0x10E720: {
            const CompoundHintInputs inputs{origin(input),args[1],native_component_style::capture_button()};
            handle=upsert_compound_hint(source_key,inputs,*input.text);break;
        }
        case 0x1157B0: {
            const TitleStripInputs inputs{origin(input),native_input(signed_value(args[0])),args[2],
                native_component_style::capture_panel()};
            handle=upsert_title_strip(source_key,inputs,*input.text);text_argument=1;break;
        }
        case 0x8FE90: {
            const ScaleRulerInputs inputs{origin(input),native_input(signed_value(args[0]))};
            handle=upsert_scale_ruler(source_key,inputs,*input.text);text_argument=1;break;
        }
        default:return Status::ok;
        }
    }
    auto& prepared=calls[event.token].text;
    preparing=true;const auto status=prepare(handle,services,prepared);preparing=false;
    if(status!=Status::ok) return status;
    if(target==0x10EB40) {
        const auto parsed=parse_prepared(prepared);if(parsed!=Status::ok) return parsed;
    } else if(target==0xF8E20) {
        event.arguments[0]=address(prepared.fragments[0].data());
        event.arguments[1]=address(prepared.fragments[1].data());
    } else if(target==0xFEE50) {
        event.arguments[0]=address(prepared.fragments[2].data());
    } else if(target==0xFEF00 || target==0xF9910) {
        // The accepted amount/maximum remain the original native integers.
    } else if(target==0x605B0 || target==0x60360 || target==0x60450) {
        // These complete native map components have no text argument.
    } else if(target==0xF8F80 || target==0xF9030)
        event.frame->ecx=address(prepared.fragments.front().data());
    else event.arguments[text_argument]=address(prepared.fragments.front().data());
    calls[event.token].component=handle;
    services.enter(handle,get(handle).kind,paint_outline(handle));calls[event.token].entered=true;
    native_ui_scene::component_constructed(handle);
    return Status::ok;
}
void leave_call(u64 token) {
    const auto call=calls.find(token);
    if(call!=calls.end() && call->second.entered)
        services.leave(call->second.component,get(call->second.component).kind);
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
    builder_exists=false;builder={};builder_nodes.clear();fields.clear();metadata.clear();
    calls.clear();parser_bindings.clear();event_inputs.clear();grammar_starts_at.clear();
}
void set_parser_source_decoder(DecodeParserSource decoder) { decode_parser_source=decoder; }
void set_parser_source_encoder(EncodeParserSource encoder) { encode_parser_source=encoder; }
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
    hooks.push_back(call(compound_hint_secondary,0x15D936,0x10E720,2));
    HookSpec grammar{parser_grammar,HookKind::inline_code,0x161E99,0,0,5,{0xA1}};
    std::memcpy(grammar.expected+1,&cookie,4);hooks.push_back(grammar);
    hooks.push_back(call(parser_compose_first,0x13405E,0x162100,0));
    hooks.push_back(call(parser_compose_second,0x138AC6,0x162100,0));
    hooks.push_back(call(world_map_first,0x5B7F9,0x605B0,2));
    hooks.push_back(call(world_map_second,0x5F72D,0x605B0,2));
    hooks.push_back(call(world_map_third,0x60AED,0x605B0,2));
    hooks.push_back(call(world_map_marker,0x60AFA,0x60360,1));
    hooks.push_back(call(world_map_controls,0x60B02,0x60450,0));
    constexpr u32 status_calls[]{0xFA5AF,0xFA5D3,0xFA60D,0xFA62B,0xFA665,
        0xFA683,0xFA6BD,0xFA6DB,0xFA6F9,0xFA733};
    for(u32 index=0;index<std::size(status_calls);++index)
        hooks.push_back(call(hud_status_first+index,status_calls[index],0xF8E20,5));
    for(u32 index=0;index<10;++index)
        hooks.push_back(call(hud_status_bar_first+index,hud_value_calls[index].site,0xFEF00,2));
    hooks.push_back(call(hud_status_weight,0x102DCD,0xFEE50,2));
    constexpr u32 summary_calls[]{0x58C77,0x89804,0xFA744,0x1035CC,0x1845F6};
    for(u32 index=0;index<std::size(summary_calls);++index)
        hooks.push_back(call(hud_summary_first+index,summary_calls[index],0xF9910,0));
    for(u32 index=0;index<std::size(summary_reads);++index) {
        const auto& read=summary_reads[index];
        HookSpec hook{hud_summary_operand_first+index,HookKind::inline_code,read.site,0,0,0,{}};
        u32 operand=2;
        switch(read.operand) {
        case SummaryOperand::layout_zero:hook.byte_count=7;hook.expected[0]=0x83;hook.expected[1]=0x3D;break;
        case SummaryOperand::layout_ebx:hook.byte_count=6;hook.expected[0]=0x39;hook.expected[1]=0x1D;break;
        case SummaryOperand::nutrition_esi:hook.byte_count=6;hook.expected[0]=0x8B;hook.expected[1]=0x35;break;
        case SummaryOperand::nutrition_ecx:hook.byte_count=6;hook.expected[0]=0x8B;hook.expected[1]=0x0D;break;
        case SummaryOperand::hunger_ecx:hook.byte_count=7;hook.expected[0]=0x0F;hook.expected[1]=0xB6;hook.expected[2]=0x0D;operand=3;break;
        case SummaryOperand::thirst_multiply:hook.byte_count=6;hook.expected[0]=0xF7;hook.expected[1]=0x2D;break;
        case SummaryOperand::thirst_eax:hook.byte_count=5;hook.expected[0]=0xA1;operand=1;break;
        case SummaryOperand::vigour_edx:hook.byte_count=6;hook.expected[0]=0x8B;hook.expected[1]=0x15;break;
        case SummaryOperand::warmth_xmm:hook.byte_count=8;hook.expected[0]=0xF3;hook.expected[1]=0x0F;hook.expected[2]=0x10;hook.expected[3]=0x15;operand=4;break;
        }
        const auto field=static_cast<u32>(base+read.field);std::memcpy(hook.expected+operand,&field,4);
        hooks.push_back(hook);
    }
    for(u32 index=0;index<8;++index) {
        HookSpec capture{parser_count_capture_first+index,HookKind::inline_code,
            grammar_starts[index].capture,0,0,5,{0xA1}};
        const auto count=static_cast<u32>(base+0xA225314);std::memcpy(capture.expected+1,&count,4);
        hooks.push_back(capture);
    }
    for(const auto [id,site]:std::array<std::pair<u32,u32>,3>{{
        {parser_count_zero_first,0x134049},{parser_count_zero_second,0x138AB1},{parser_help_clear,0x16266C}}}) {
        HookSpec clear{id,HookKind::inline_code,site,0,0,10,{0xC7,0x05}};
        const auto count=static_cast<u32>(base+0xA225314);std::memcpy(clear.expected+2,&count,4);
        hooks.push_back(clear);
    }
    metadata.clear();for(const auto& hook:hooks) metadata.emplace(hook.id,hook);
}
void begin_event(const NativeEvent& event) {
    EventInputs input{event.token,event.id,event.frame->ecx,event.frame->edx,{},{},{},{},{},false};
    const auto hook=metadata.find(event.id);
    if(hook!=metadata.end() && hook->second.kind==HookKind::call) {
        const auto count=std::min<u32>(event.argument_count,static_cast<u32>(input.arguments.size()));
        std::copy_n(event.arguments,count,input.arguments.begin());
        const char* original=nullptr;
        switch(hook->second.target_rva) {
        case 0x116270:case 0x115E70:original=pointer<const char>(input.arguments[2]);break;
        case 0x114680:case 0xE10F0:case 0x10E720:original=pointer<const char>(input.arguments[0]);break;
        case 0x10E910:case 0xCFAF0:case 0x1157B0:case 0x8FE90:original=pointer<const char>(input.arguments[1]);break;
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
void note_native_field(const NativeEvent&,u32 field) { event_inputs.back().native_field=field; }
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
Status finish_event(const NativeEvent& event,DispatchResult& result,Status native_dispatch_status) {
    const auto input=std::move(event_inputs.back());event_inputs.pop_back();
    if(native_dispatch_status!=Status::ok) {
        leave_call(event.token);calls.erase(event.token);unbind_parser_source(event.token);
        native_menu_component::unbind_constructor_source(event.token);return native_dispatch_status;
    }
    if(event.id>=hud_summary_operand_first &&
        event.id<hud_summary_operand_first+std::size(summary_reads)) {
        if(const auto* source=summary_source()) {
            const auto& read=summary_reads[event.id-hud_summary_operand_first];
            const auto next=read.site+metadata.at(event.id).byte_count;
            uwcn_summary_operand_resume=static_cast<u32>(base+next);
            const auto branch=[&](auto function) {
                result.resume_rva=static_cast<u32>(reinterpret_cast<std::uintptr_t>(function)-base);
            };
            switch(read.operand) {
            case SummaryOperand::layout_zero:
                uwcn_summary_layout=source->layout;branch(uwcn_summary_compare_zero);break;
            case SummaryOperand::layout_ebx:
                uwcn_summary_layout=source->layout;branch(uwcn_summary_compare_ebx);break;
            case SummaryOperand::nutrition_esi:event.frame->esi=source->nutrition;result.resume_rva=next;break;
            case SummaryOperand::nutrition_ecx:event.frame->ecx=source->nutrition;result.resume_rva=next;break;
            case SummaryOperand::hunger_ecx:event.frame->ecx=source->hunger;result.resume_rva=next;break;
            case SummaryOperand::thirst_multiply:
                uwcn_summary_thirst=source->thirst;branch(uwcn_summary_multiply_thirst);break;
            case SummaryOperand::thirst_eax:event.frame->eax=source->thirst;result.resume_rva=next;break;
            case SummaryOperand::vigour_edx:event.frame->edx=source->vigour;result.resume_rva=next;break;
            case SummaryOperand::warmth_xmm:
                uwcn_summary_warmth=source->warmth_bits;branch(uwcn_summary_load_warmth);break;
            }
        }
        return Status::ok;
    }
    if(event.phase==NativePhase::after) {
        if(event.id>=parser_clear_first && event.id<=parser_clear_fourth &&
            observing_builder()) clear_paragraph_builder();
        if((event.id==parser_compose_first || event.id==parser_compose_second) && observing_builder()) {
            builder_nodes.push_back({BuilderOperation::compose,*reinterpret_cast<const u32*>(base+0xA44B7A8),0,{}});
            builder.grammar.push_back({static_cast<u32>(builder.fragments.size()),0,0,ParagraphOperation::compose});
        }
        const auto native_call=calls.find(event.token);
        if(native_call!=calls.end() && native_call->second.menu) {
            const auto& component=get(native_call->second.component);
            const auto& action=std::get<ActionButtonInputs>(component.inputs);
            u32 row=action.row_id;
            if(action.locator==ActionLocator::action) {
                row=0;
                while(*reinterpret_cast<const u32*>(base+0x5F4EF10+
                    row*native_menu_model::row_stride+0xC8)!=action.action) ++row;
            }
            native_menu_component::commit_row(native_call->second.menu,row,component.text);
            native_menu_model::capture_into(native_call->second.menu);
        }
        leave_call(event.token);
        calls.erase(event.token);unbind_parser_source(event.token);
        native_menu_component::unbind_constructor_source(event.token);return Status::ok;
    }
    if(event.id==parser_entry) return observe_parser(event);
    if(observing_builder()) {
        if(event.id>=parser_count_capture_first && event.id<parser_count_capture_first+8) {
            grammar_starts_at.insert_or_assign(grammar_starts[event.id-parser_count_capture_first].capture,
                static_cast<u32>(builder.fragments.size()));return Status::ok;
        }
        if(event.id==parser_grammar) {
            const auto consumer=*pointer<const u32>(event.frame->ebp+4)-static_cast<u32>(base)-5;
            const auto producer=std::find_if(std::begin(grammar_starts),std::end(grammar_starts),
                [&](const GrammarStart& start){return start.consumer==consumer;});
            const auto first=producer->capture ? grammar_starts_at.at(producer->capture) : 0u;
            builder.grammar.push_back({static_cast<u32>(builder.fragments.size()),first,input.edx});
            builder_nodes.push_back({BuilderOperation::grammar,first,input.edx,{}});return Status::ok;
        }
        if(event.id==parser_count_zero_first || event.id==parser_count_zero_second) {
            builder.grammar.push_back({static_cast<u32>(builder.fragments.size()),0,0,ParagraphOperation::count_zero});
            builder_nodes.push_back({BuilderOperation::count_zero,0,0,{}});return Status::ok;
        }
        if(event.id==parser_help_clear) { clear_paragraph_builder();return Status::ok; }
    }
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
void clear_paragraph_builder() {
    builder={};builder_nodes.clear();grammar_starts_at.clear();builder_exists=true;
}
Status restore_paragraph_builder() { return restore_native_builder(); }
Status consume_paragraph_source(const ParagraphSource& source) {
    PreparedText prepared;
    for(const auto& fragment:source.fragments) {
        prepared.fragments.emplace_back();
        auto status=resolve(fragment,prepared.fragments.back());if(status!=Status::ok) return status;
        if(!prepare_paragraph_fragment(fragment,prepared.fragments.back())) continue;
        status=services.paragraph_words(prepared.fragments.back());if(status!=Status::ok) return status;
    }
    restoring_builder=true;parse_prepared_paragraph(source,prepared.fragments);restoring_builder=false;
    return Status::ok;
}
Status replace_paragraph_builder(const ParagraphSource& source) {
    builder=source;builder_exists=true;builder_nodes.clear();grammar_starts_at.clear();
    auto ring_slot=*reinterpret_cast<const u32*>(base+0xA44B7A8);
    const auto append_grammar=[&](u32 after) {
        for(const auto& node:builder.grammar) if(node.after_fragments==after) {
            switch(node.operation) {
            case ParagraphOperation::grammar:
                builder_nodes.push_back({BuilderOperation::grammar,node.first_fragment,node.comma_count,{}});break;
            case ParagraphOperation::count_zero:
                builder_nodes.push_back({BuilderOperation::count_zero,0,0,{}});break;
            case ParagraphOperation::compose:
                ring_slot=(ring_slot+1u)&1023u;
                builder_nodes.push_back({BuilderOperation::compose,ring_slot,0,{}});break;
            }
        }
    };
    append_grammar(0);
    for(u32 index=0;index<builder.fragments.size();++index) {
        std::string original;
        if(builder.fragments[index].policy==TextPolicy::original) {
            std::vector<char> bytes;
            const auto& fragment=builder.fragments[index];
            const auto neutral=fragment.prefix+fragment.original+fragment.suffix;
            const auto status=encode_parser_source(neutral.c_str(),bytes);
            if(status!=Status::ok) return status;
            original.assign(bytes.data(),bytes.size()-1);
        }
        builder_nodes.push_back({BuilderOperation::append,index,0,std::move(original)});append_grammar(index+1);
    }
    return restore_paragraph_builder();
}
void retire_root(u64 owner) {
    for(auto field=fields.begin();field!=fields.end();) {
        if(field->first.first==owner) field=fields.erase(field);else ++field;
    }
}
std::vector<std::uint8_t> save() {
    Writer output;output.scalar(builder_exists?1u:0u);output.scalar(static_cast<u32>(builder.fragments.size()));
    for(const auto& fragment:builder.fragments) output.text(fragment);
    output.scalar(static_cast<u32>(builder.grammar.size()));
    for(const auto& node:builder.grammar) {
        output.scalar(node.after_fragments);output.scalar(node.first_fragment);output.scalar(node.comma_count);
        output.scalar(static_cast<u32>(node.operation));
    }
    output.scalar(static_cast<u32>(builder_nodes.size()));
    for(const auto& node:builder_nodes) {
        output.scalar(static_cast<u32>(node.operation));output.scalar(node.first);output.scalar(node.second);output.string(node.native_original);
    }
    output.scalar(static_cast<u32>(grammar_starts_at.size()));
    for(const auto [capture,boundary]:grammar_starts_at) {output.scalar(capture);output.scalar(boundary);}
    output.scalar(static_cast<u32>(fields.size()));
    for(const auto& [key,source]:fields) { output.scalar(key.first);output.scalar(static_cast<u32>(key.second));output.text(source); }
    return std::move(output.bytes);
}
void restore(const void* payload) {
    Reader input{static_cast<const std::uint8_t*>(payload)};builder_exists=input.scalar<u32>()!=0;
    builder={};builder_nodes.clear();const auto fragments=input.scalar<u32>();
    for(u32 i=0;i<fragments;++i) builder.fragments.push_back(input.text());
    const auto grammar=input.scalar<u32>();
    for(u32 i=0;i<grammar;++i) {
        const auto after=input.scalar<u32>(),first=input.scalar<u32>(),commas=input.scalar<u32>();
        const auto operation=static_cast<ParagraphOperation>(input.scalar<u32>());
        builder.grammar.push_back({after,first,commas,operation});
    }
    const auto nodes=input.scalar<u32>();
    for(u32 i=0;i<nodes;++i) {
        const auto operation=static_cast<BuilderOperation>(input.scalar<u32>());
        const auto first=input.scalar<u32>(),second=input.scalar<u32>();
        builder_nodes.push_back({operation,first,second,input.string()});
    }
    grammar_starts_at.clear();const auto captures=input.scalar<u32>();
    for(u32 i=0;i<captures;++i) {
        const auto capture=input.scalar<u32>(),boundary=input.scalar<u32>();grammar_starts_at.emplace(capture,boundary);
    }
    fields.clear();const auto count=input.scalar<u32>();
    for(u32 i=0;i<count;++i) {
        const auto owner=input.scalar<u64>();const auto component=static_cast<TextComponent>(input.scalar<u32>());
        fields.emplace(std::make_pair(owner,component),input.text());
    }
    calls.clear();parser_bindings.clear();event_inputs.clear();preparing=false;restoring_builder=false;parser_owner_depth=0;source_resolution_depth=0;
}
void shutdown() {
    base=0;services={};decode_parser_source=nullptr;encode_parser_source=nullptr;fields.clear();metadata.clear();builder={};builder_nodes.clear();
    builder_exists=false;calls.clear();parser_bindings.clear();event_inputs.clear();preparing=false;restoring_builder=false;parser_owner_depth=0;source_resolution_depth=0;
    grammar_starts_at.clear();
}
}
