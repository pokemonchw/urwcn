#include "../../sdk/host_abi.h"
#include "../../sdk/text_services.h"
#include "../../sdk/utf8.h"
#include "../render/render_api.h"
#include "../render/sdl_api.h"
#include "abi1_hook_retirement.h"
#include "native_targets.h"
#include "native_raster_patches.h"
#include "native_paragraph.h"
#include "native_language_input.h"
#include "native_language_redraw.h"
#include "native_menu_component.h"
#include "native_menu_storage.h"
#include "native_component_calls.h"
#include "native_root_component.h"
#include "native_component_model.h"
#include "native_component_binding.h"
#include "native_image_component.h"
#include "native_footer_component.h"
#include "native_link_flow_component.h"
#include "native_message_source.h"
#include "native_message_flow.h"
#include "native_renderer_component_model.h"
#include "native_renderer_component_binding.h"
#include "native_hud_icons.h"
#include "native_culture_legend.h"
#include "native_ui_scene.h"
#include "native_ui_cache_owners.h"
#include "native_button.h"
#include "setup_text_calls.h"
#include "credits_text_calls.h"
#include "../render/byayoi_sprite.h"
#include <windows.h>
#include <algorithm>
#include <cstring>
#include <initializer_list>
#include <iterator>
#include <map>
#include <cstdio>
#include <string>
#include <vector>

namespace uwcn::adapter {
namespace {
const HostApi* host{};
using GetRGB = void (UWCN_CALL *)(u32, const void*, unsigned char*, unsigned char*, unsigned char*);
GetRGB get_rgb{};
abi1_retirement::RetirementRoutes retired_routes{};
bool retired_for_publication{};
bool chinese_enabled=true;
bool intro_chinese=true;

enum Hook : u32 {
    menu_scope=1, footer_initial, footer_loop, version_scope, menu_input,
    menu_text=10, version_format, copyright_format, production_append, authors_append,
    version_text, production_paragraph, copyright_paragraph, authors_paragraph, paragraph_text,
    copyright_append, footer_logo, footer_panel,
    outline_top=30, outline_bottom, outline_left, outline_right, foreground,
    cursor_width=40, version_width, paragraph_width, paragraph_advance,
    window_targets_rebuilt=60,
    startup_heading=100, startup_audio_ogg_scope, startup_audio_samples_scope, startup_intro_scope,
    startup_sound_init, startup_device_failed, startup_intro_progress,
    startup_named_audio, startup_file_audio, startup_named_failed, startup_file_failed,
    startup_progress_text,
    intro_north=120, intro_roleplaying, intro_version_scope, intro_story_scope,
    intro_story_width, intro_story_fade_text, intro_story_settled_text, intro_sequence_scope,
    about_scope=140, about_panel, about_version_format, about_copyright_format,
    about_publisher_format, about_title_width, about_title_text,
    about_version_width, about_copyright_width, about_publisher_width,
    about_notes_width, about_install_width, about_website_width, about_path_width,
    about_version_text, about_copyright_text, about_publisher_text,
    about_notes_text, about_install_text, about_website_text, about_path_text,
    about_button, about_button_width, about_button_character,
    about_button_text, about_button_advance, about_wait, about_input_tick,
    credits_scope=180, credits_panel, credits_paragraph, credits_button, credits_wait,
    character_creation_scope=220, character_creation_panel, character_creation_button,
    profile_heading_panel=240, profile_culture_scope, profile_sex_scope, profile_name_panel,
    profile_name_help, profile_name_help_repeat, profile_name_footer,
    profile_sex_help, profile_sex_footer, profile_name_too_short, profile_name_invalid, profile_name_exists,
    scenario_story_scope=260, scenario_panel, scenario_body_format, scenario_body_paragraph,
    scenario_introduction_1, scenario_introduction_2, scenario_introduction_3, scenario_introduction_4,
    scenario_intro_paragraph, scenario_button,
    setup_panel=300, shared_title_text, setup_controls_append, setup_config_append,
    setup_footer, shared_footer_paragraph, setup_exit_scope, setup_exit_text, setup_exit_width,
    setup_body_first=0x600, credits_append_first=0x700,
    load_saved_empty_panel=0xA00, load_saved_list_panel, load_saved_empty_text, load_saved_key_text,
    ancestors_title=0x900, ancestors_empty, ancestors_order, ancestors_exit,
    ancestors_played, ancestors_living, ancestors_distance, ancestors_previous, ancestors_next,
    ancestors_select, ancestors_select_prefix, ancestors_select_suffix,
    ancestors_page_format, ancestors_page_text, ancestors_row,
    ancestors_lived_format, ancestors_distance_format, ancestors_lived_text, ancestors_distance_text,
    scenario_body_append=0x5700
};
enum class Scope : u32 {
    menu=1, footer=2, version=3, paragraph=4, text=5, allocation=6, menu_input=7,
    startup_audio=8, startup_intro=9, startup_progress=10, intro_story=11,
    about=12, titled_panel=13, plain_button=14, credits=15,
    setup_panel=30, setup_footer=31, setup_exit=32, intro_version=33,
    character_creation=34, character_creation_panel=35, character_creation_label=36,
    profile_culture=37, profile_sex=38, profile_panel=39, profile_footer=40,
    scenario_story=41, scenario_panel=42, creation_button=43, creation_paragraph=44,
    encyclopedia_input=45, spells_footer=46,
    load_saved_panel=0xA0,
    ancestors_title=50, ancestors_select=51, ancestors_row=52,
    hud_centered=0x100, hud_penalty=0x101, hud_button=0x102,
    hud_title=0x103, hud_renderer=0x104, hud_renderer_text=0x105, hud_scale=0x106,
    native_renderer_resource=0x107, hud_status_cell=0x108,
    message_pending=0x200, message_body=0x201
};
struct Active {
    u64 token;
    Scope kind;
    u32 allocation;
    std::int32_t text_x;
    u32 centered;
    std::int32_t center_x;
    u32 outline;
};
std::vector<Active> active;

// Three original sprintf arguments, borrowed only for the synchronous DEDA0
// summary call. No row index, position, text or page snapshot is retained.
struct AncestorNumbers { std::int32_t age,days,kilometers;u32 record_id; };

native_text_resource::TextSource startup_progress_source;
std::vector<std::uint8_t> save_startup_progress_source() {
    std::vector<std::uint8_t> output;
    const auto append=[&output](const auto& value) {
        const auto* p=reinterpret_cast<const std::uint8_t*>(&value);output.insert(output.end(),p,p+sizeof(value));
    };
    const auto string=[&output,&append](const std::string& value) {
        append(static_cast<u32>(value.size()));output.insert(output.end(),value.begin(),value.end());
    };
    append(static_cast<u32>(startup_progress_source.component));
    append(startup_progress_source.has_value?1u:0u);
    string(startup_progress_source.original);string(startup_progress_source.value);
    return output;
}
void restore_startup_progress_source(const void* data) {
    const auto* p=static_cast<const std::uint8_t*>(data);
    const auto read=[&p]() {u32 value;std::memcpy(&value,p,sizeof(value));p+=sizeof(value);return value;};
    const auto string=[&p,&read]() {const auto size=read();std::string value(reinterpret_cast<const char*>(p),size);p+=size;return value;};
    const auto component=static_cast<TextComponent>(read());const auto has_value=read();
    const auto original=string(),value=string();
    startup_progress_source=native_text_resource::from_request({component,original.c_str(),has_value?value.c_str():nullptr});
}

template<class T> T* at(u32 rva) { return reinterpret_cast<T*>(host->image_base+rva); }
template<class T> T* ptr(u32 address) { return reinterpret_cast<T*>(static_cast<std::uintptr_t>(address)); }
u32 address(const void* value) { return static_cast<u32>(reinterpret_cast<std::uintptr_t>(value)); }
bool in(Scope kind) {
    return std::any_of(active.rbegin(),active.rend(),[kind](const Active& a){return a.kind==kind;});
}
const Active* text_context() {
    for(auto i=active.rbegin();i!=active.rend();++i) if(i->kind==Scope::text) return &*i;
    return nullptr;
}
AncestorNumbers& ancestor_numbers() {
    const auto row=std::find_if(active.rbegin(),active.rend(),
        [](const Active& scope){return scope.kind==Scope::ancestors_row;});
    return *ptr<AncestorNumbers>(row->allocation);
}
void begin(const NativeEvent& e,Scope kind,u32 outline=0) { active.push_back({e.token,kind,0,0,0,0,outline}); }
u32 outline_budget() {
    for(auto i=active.rbegin();i!=active.rend();++i) {
        if(i->kind==Scope::text || i->kind==Scope::paragraph || i->kind==Scope::setup_exit
            || i->kind==Scope::hud_centered || i->kind==Scope::hud_penalty || i->kind==Scope::hud_scale
            || i->kind==Scope::creation_button || i->kind==Scope::creation_paragraph)
            return i->outline;
        if(i->kind==Scope::version || i->kind==Scope::intro_story || i->kind==Scope::titled_panel) return 1;
    }
    return 0;
}
void end(u64 token) {
    for(auto i=active.begin();i!=active.end();) {
        if(i->token==token) {
            if(i->allocation) host->release(ptr<void>(i->allocation));
            i=active.erase(i);
        } else ++i;
    }
}

Status service_text(ModuleId module,u32 operation,const void* input,u32 input_size,std::vector<char>& output) {
    u32 bytes{};
    auto result=host->invoke(module,operation,input,input_size,nullptr,&bytes);
    if(result!=Status::ok && result!=Status::insufficient_buffer) return result;
    if(!bytes) return Status::invalid;
    output.resize(bytes);
    result=host->invoke(module,operation,input,input_size,output.data(),&bytes);
    if(result!=Status::ok) return result;
    if(!bytes || bytes>output.size() || output[bytes-1]!='\0') return Status::invalid;
    output.resize(bytes);
    return Status::ok;
}
Status codec(u32 operation,const char* input,std::vector<char>& output) {
    CodecRequest request{input};
    return service_text(ModuleId::layout,operation,&request,sizeof(request),output);
}
Status translate_culture_back(const char* original,const char* topic,std::vector<char>& encoded);
Status translate_skills_limit(TextComponent component,const char* value,std::vector<char>& encoded);
Status translate_help_record(TextComponent component,const char* value,std::vector<char>& encoded);
Status resolve_display_text(TextComponent component,const char* original,const char* value,std::vector<char>& encoded) {
    // The same neutral native component resolves against the global language.
    if(!chinese_enabled)
        return codec(layout_op::encode_native,original,encoded);
    if(component==TextComponent::culture_back) return translate_culture_back(original,value,encoded);
    if(component==TextComponent::skills_limit_improve || component==TextComponent::skills_limit_degrade)
        return translate_skills_limit(component,value,encoded);
    if(component==TextComponent::skills_help_record || component==TextComponent::spells_help_record)
        return translate_help_record(component,value,encoded);
    std::string projected_value;
    if(component==TextComponent::creation_complete_enter) {
        const std::string identity(value);const auto separator=identity.find('|');
        const auto culture_id=static_cast<u32>(std::stoul(identity.substr(0,separator)));
        const auto culture_component=static_cast<TextComponent>(static_cast<u32>(TextComponent::profile_culture_0)+culture_id);
        std::vector<char> culture,culture_utf8;
        auto status=resolve_display_text(culture_component,"",nullptr,culture);
        if(status!=Status::ok) return status;
        status=codec(layout_op::decode_native,culture.data(),culture_utf8);
        if(status!=Status::ok) return status;
        projected_value=identity.substr(separator+1)+" "+culture_utf8.data();value=projected_value.c_str();
    }
    if(component==TextComponent::ancestors_lived) {
        const std::string numbers(value);const auto separator=numbers.find('|');
        projected_value=numbers.substr(0,separator)+" 岁，度过了 "+numbers.substr(separator+1)+" 天冒险生涯";
        value=projected_value.c_str();
    }
    TextRequest request{component,original,value};
    std::vector<char> utf8;
    auto result=service_text(ModuleId::main_menu,text_op::translate,&request,sizeof(request),utf8);
    if(result!=Status::ok) return result;
    return codec(layout_op::encode_native,utf8.data(),encoded);
}
Status translate(TextComponent component,const char* original,const char* value,std::vector<char>& encoded) {
    native_component_binding::note_source({component,original,value});
    return resolve_display_text(component,original,value,encoded);
}

// 10E5A0/10DDB0 consume the current native surface. Its actual native
// constructor domain and physical size define the complete-string raster scale.
render::TextRequest render_request(const char* utf8,std::int32_t x,std::int32_t y,u32 pixel) {
    void* surface=*at<void*>(0x61BBB10);
    const auto domain=native_targets::component_surface_source(surface);
    auto format=*reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(surface)+4);
    unsigned char r{},g{},b{};
    get_rgb(pixel,format,&r,&g,&b);
    return {utf8,surface,*at<void*>(0xA2110CC),x,y,
        static_cast<u32>(r)|(static_cast<u32>(g)<<8)|(static_cast<u32>(b)<<16)|0xFF000000u,
        10,9,0,0,outline_budget(),domain.width,domain.height};
}
Status metrics_at_outline(const char* encoded,u32 outline,render::Metrics& output) {
    std::vector<char> utf8;
    auto result=codec(layout_op::decode_native,encoded,utf8);
    if(result!=Status::ok) return result;
    auto request=render_request(utf8.data(),0,0,0);
    request.outline=outline;
    u32 bytes=sizeof(output);
    return host->invoke(ModuleId::render,render::op::measure,&request,sizeof(request),&output,&bytes);
}
Status metrics(const char* encoded,render::Metrics& output) {
    return metrics_at_outline(encoded,outline_budget(),output);
}
#include "native_name_input.inc"
bool contains_display(const char* text) { return native_name_input::contains_display(text); }

std::string native_paragraph_words(const char* encoded) {
    std::string words;
    for(auto* p=reinterpret_cast<const unsigned char*>(encoded);*p;) {
        if(native_name_input::transport(p)) {
            if(!words.empty() && words.back()!=' ' && words.back()!='>') words+=' ';
            words.append(reinterpret_cast<const char*>(p),2);
            words+=' ';
            p+=2;
        } else words.push_back(*p++);
    }
    return words;
}
Status draw(const NativeEvent& e) {
    std::vector<char> utf8;
    auto result=codec(layout_op::decode_native,ptr<char>(e.arguments[0]),utf8);
    if(result!=Status::ok) return result;
    auto request=render_request(utf8.data(),static_cast<std::int32_t>(e.frame->ecx),
        static_cast<std::int32_t>(e.frame->edx),*at<u32>(0xA211068));
    const auto* context=text_context();
    if(!context) request.outline=*ptr<u32>(e.frame->ebp+0x10)&1u;
    if(context && context->centered) {
        request.centered=1;
        request.center_x=context->center_x+request.x-context->text_x;
    }
    render::Metrics output{};
    u32 bytes=sizeof(output);
    return host->invoke(ModuleId::render,render::op::draw,&request,sizeof(request),&output,&bytes);
}
Status lend_text(const NativeEvent& e,std::vector<char>& encoded,u32& destination,Scope kind,u32 native_outline=0) {
    void* memory=host->allocate(static_cast<u32>(encoded.size()));
    if(!memory) return Status::failed;
    std::memcpy(memory,encoded.data(),encoded.size());
    active.push_back({e.token,kind,address(memory),static_cast<std::int32_t>(e.frame->ecx),0,0,
        kind==Scope::text?e.arguments[2]:native_outline});
    destination=address(memory);
    return Status::ok;
}
Status startup_progress(const NativeEvent& e,TextComponent component,const char* value=nullptr) {
    std::vector<char> encoded;
    auto status=translate(component,ptr<char>(e.frame->ecx),value,encoded);
    if(status!=Status::ok) return status;
    startup_progress_source=native_text_resource::from_request({component,ptr<char>(e.frame->ecx),value});
    // 10E5A0 copies this display string into its native 0x12C-byte buffer.
    if(encoded.size()>0x12C) return Status::insufficient_buffer;
    // Keep 123DF0's ECX and English buffer intact: it truncates and logs that
    // original. Only its nested 123E6D text call borrows the translated bytes.
    u32 display{};
    return lend_text(e,encoded,display,Scope::startup_progress);
}
Status formatted(const NativeEvent& e,TextComponent component,const char* value) {
    std::vector<char> encoded;
    auto result=translate(component,ptr<char>(e.arguments[0]),value,encoded);
    if(result!=Status::ok) return result;
    // The confirmed main-menu and About sprintf destinations have 0x400 bytes.
    if(encoded.size()>0x400) return Status::insufficient_buffer;
    std::memcpy(ptr<void>(e.arguments[0]),encoded.data(),encoded.size());
    e.frame->eax=static_cast<u32>(encoded.size()-1);
    return Status::ok;
}
Status native_width(const NativeEvent& e,DispatchResult& result,const char* encoded) {
    render::Metrics measured{};
    const auto status=metrics(encoded,measured);
    if(status!=Status::ok) return status;
    e.frame->eax=static_cast<u32>(measured.logical_width);
    result.skip_original=1;
    return Status::ok;
}
Status about_literal_width(const NativeEvent& e,DispatchResult& result,TextComponent component) {
    // These exact width sites follow the native literal copy to [EBP-408].
    // Only the display buffer changes; the following native centering runs.
    auto* display=ptr<char>(e.frame->ebp-0x408);
    std::vector<char> encoded;
    auto status=translate(component,display,nullptr,encoded);
    if(status!=Status::ok) return status;
    std::memcpy(display,encoded.data(),encoded.size());
    return native_width(e,result,display);
}
Status centered_text(const NativeEvent& e) {
    render::Metrics measured{};
    const auto status=metrics(ptr<char>(e.arguments[0]),measured);
    if(status!=Status::ok) return status;
    const auto x=static_cast<std::int32_t>(e.frame->ecx);
    switch(e.id) {
    case version_text:native_component_binding::note_source_for_consumer(e,TextComponent::version);break;
    case about_version_text:native_component_binding::note_source_for_consumer(e,TextComponent::about_version);break;
    case about_copyright_text:native_component_binding::note_source_for_consumer(e,TextComponent::about_copyright);break;
    case about_publisher_text:native_component_binding::note_source_for_consumer(e,TextComponent::about_publisher);break;
    case about_notes_text:native_component_binding::note_source_for_consumer(e,TextComponent::about_release_notes);break;
    case about_install_text:native_component_binding::note_source_for_consumer(e,TextComponent::about_install_label);break;
    case ancestors_page_text:native_component_binding::note_source_for_consumer(e,TextComponent::ancestors_page);break;
    case about_website_text:case about_path_text:
        native_component_binding::note_original_for_consumer(e,ptr<char>(e.arguments[0]));break;
    default:break;
    }
    native_component_binding::note_center(e,x+measured.logical_width/2);
    active.push_back({e.token,Scope::text,0,x,1,x+measured.logical_width/2,e.arguments[2]});
    return Status::ok;
}

Status encode_component_original(const char* text,std::vector<char>& encoded) {
    return codec(layout_op::encode_native,text,encoded);
}
Status decode_parser_original(const char* input,std::string& utf8) {
    for(auto* p=reinterpret_cast<const unsigned char*>(input);*p;) {
        const auto bytes=native_name_input::span(p);
        if(bytes) { utf8.append(reinterpret_cast<const char*>(p),bytes);p+=bytes; }
        else { append_utf8(utf8,native_name_input::native_scalar(*p));++p; }
    }
    return Status::ok;
}
Status encode_parser_original(const char* utf8,std::vector<char>& native) {
    std::vector<u32> scalars;
    if(!decode_utf8(utf8,std::strlen(utf8),scalars)) return Status::invalid;
    std::string result;
    for(const auto scalar:scalars) {
        // Inverse of the three confirmed native display-wrapper substitutions.
        if(scalar==0xC4) result.push_back(static_cast<char>(0x8E));
        else if(scalar==0xE4) result.push_back(static_cast<char>(0x84));
        else if(scalar==0xF6) result.push_back(static_cast<char>(0x94));
        else if(scalar<=0xFF) result.push_back(static_cast<char>(scalar));
        else append_utf8(result,scalar);
    }
    native.assign(result.begin(),result.end());native.push_back(0);
    return Status::ok;
}
Status encode_component_words(std::vector<char>& encoded) {
    const auto words=native_paragraph_words(encoded.data());
    encoded.assign(words.begin(),words.end());encoded.push_back(0);
    return Status::ok;
}
Status measure_component_text(const char* encoded,std::int32_t& width) {
    render::Metrics measured{};
    const auto status=metrics(encoded,measured);
    if(status==Status::ok) width=measured.logical_width;
    return status;
}
u64 component_paint_token(native_component_model::Handle handle) {
    return 0xFFFFFFFF00000000ull|handle;
}
void enter_component_paint(native_component_model::Handle handle,native_component_model::Kind kind,u32 outline) {
    using Kind=native_component_model::Kind;
    const auto& model=native_component_model::get(handle);
    const bool action_key=kind==Kind::button && model.text.prefix.find('.')!=std::string::npos;
    const auto scope=kind==Kind::panel || kind==Kind::legacy_panel || kind==Kind::title_strip ? Scope::titled_panel :
        kind==Kind::native_heading_band || kind==Kind::native_identity_heading ? Scope::titled_panel :
        kind==Kind::button ? (action_key ? Scope::setup_exit : Scope::plain_button) : kind==Kind::paragraph ? Scope::paragraph :
        kind==Kind::centered_text ? Scope::hud_centered : kind==Kind::action_button ? Scope::creation_button :
        kind==Kind::compound_hint ? Scope::ancestors_select : Scope::text;
    Active context{component_paint_token(handle),scope,0,0,0,0,outline};
    if(kind==Kind::hud_status_cell) {
        active.push_back({component_paint_token(handle),Scope::hud_status_cell,0,0,0,0,outline});
        active.push_back({component_paint_token(handle),Scope::hud_penalty,0,0,0,0,outline});
    }
    if(kind==Kind::text_block) {
        const auto& x=std::get<native_component_model::TextBlockInputs>(model.inputs).anchor.x;
        using Source=native_component_model::LayoutSource;
        if(x.source==Source::center_input || x.source==Source::center_native_i32) {
            context.centered=1;
            context.center_x=x.source==Source::center_input ? x.input : *at<std::int32_t>(x.rva);
        }
    }
    active.push_back(context);
}
void leave_component_paint(native_component_model::Handle handle,native_component_model::Kind) {
    end(component_paint_token(handle));
}
native_component_model::PaintServices component_paint_services() {
    return {resolve_display_text,encode_component_original,encode_component_words,
        measure_component_text,enter_component_paint,leave_component_paint};
}
u64 renderer_component_token(native_renderer_component_model::Handle handle) {
    return 0xFFFFFFFE00000000ull|handle;
}
void enter_renderer_component(native_renderer_component_model::Handle handle,
    native_renderer_component_model::Kind,u32 style) {
    active.push_back({renderer_component_token(handle),Scope::hud_renderer_text,0,0,0,0,style&1u});
}
void leave_renderer_component(native_renderer_component_model::Handle handle,
    native_renderer_component_model::Kind) {
    end(renderer_component_token(handle));
}
native_renderer_component_model::PaintServices renderer_component_services() {
    return {resolve_display_text,encode_component_original,encode_component_words,
        measure_component_text,enter_renderer_component,leave_renderer_component};
}
void enter_culture_resource(u64 revision) {
    active.push_back({0xFFFFFFFB00000000ull|revision,Scope::native_renderer_resource,0,0,0,0,0});
}
void leave_culture_resource(u64 revision) {end(0xFFFFFFFB00000000ull|revision);}
void report_ui_status(const wchar_t* operation,Status status) {
    if(status==Status::ok) return;
    const auto text=std::wstring(operation)+L"; status="+std::to_wstring(static_cast<u32>(status));
    host->log(text.c_str());
}
void cache_source_saved(native_ui_cache_owners::Slot slot) {
    native_ui_scene::cache_saved(static_cast<u32>(slot));
}
Status cache_source_before_restore(native_ui_cache_owners::Slot slot,
    const native_ui_cache_owners::RestoreInput& input,native_ui_cache_owners::PreparedRestore& prepared) {
    const auto status=native_ui_scene::prepare_cache_restore(static_cast<u32>(slot),input,prepared);
    report_ui_status(L"Native cache locale materialization",status);
    return status;
}
void cache_source_restored(native_ui_cache_owners::Slot slot,
    const native_ui_cache_owners::PreparedRestore& prepared,int result) {
    report_ui_status(L"Native cache source activation",
        native_ui_scene::cache_restored(static_cast<u32>(slot),prepared,result));
}
void cache_source_retired(native_ui_cache_owners::Slot slot) {
    native_ui_scene::cache_retired(static_cast<u32>(slot));
}
Status paragraph_capacity(const char* encoded) {
    // 162323/162328: a single leading space occupies a separate native token.
    // 1623CF..1624D9: '<' starts a token, '>' ends it, and a space ends a
    // token unless the next byte is another space. The delimiters themselves
    // '<' and '>' are retained; a run's non-final spaces are retained too.
    std::size_t length=0;
    std::size_t i=(encoded[0]==' ' && encoded[1]!=' ')?1:0;
    for(;encoded[i];++i) {
        const char c=encoded[i];
        if(c=='<') length=0;
        if(c==' ' && encoded[i+1]!=' ') { length=0; continue; }
        if(++length>=0x82) return Status::insufficient_buffer;
        if(c=='>') length=0;
    }
    return Status::ok;
}
Status append(const NativeEvent& e,TextComponent component) {
    const char* original=ptr<char>(e.frame->edx);
    std::string original_utf8;
    if(component==TextComponent::credits_countrymen_1) {
        // 1AF950 stores the three Latin-1 E4 bytes in the countrymen's names. The
        // native text wrapper converts E4 to CP850 84; our display transport
        // instead receives the same Unicode letters, including English mode.
        for(const auto* p=reinterpret_cast<const unsigned char*>(original);*p;++p)
            append_utf8(original_utf8,*p);
        original=original_utf8.c_str();
    }
    std::vector<char> encoded;
    auto result=translate(component,original,nullptr,encoded);
    if(result!=Status::ok) return result;
    const auto words=native_paragraph_words(encoded.data());
    encoded.assign(words.begin(),words.end());encoded.push_back(0);
    result=paragraph_capacity(encoded.data());
    if(result!=Status::ok) return result;
    return lend_text(e,encoded,e.frame->edx,Scope::allocation);
}

Status character_creation_label(const NativeEvent& e,TextComponent component) {
    // D031F lends 114680 the current native row. Keep the ASCII key and dot;
    // 1149F9 consumes the entire suffix, outside the key-cap character loop.
    const auto* original=ptr<char>(e.arguments[0]);
    const auto* suffix=std::strchr(original,'.')+1;
    std::string original_utf8;
    const char* display=suffix;
    if(component>=TextComponent::profile_culture_0 && component<=TextComponent::profile_culture_9) {
        // The native culture labels contain Latin-1 E4. Convert the borrowed
        // suffix before transport encoding, including when displaying English.
        for(const auto* p=reinterpret_cast<const unsigned char*>(suffix);*p;++p)
            append_utf8(original_utf8,*p);
        display=original_utf8.c_str();
    }
    native_menu_component::bind_row(e.frame->esi,component,display,nullptr,true);
    return Status::ok;
}

Status bind_menu_consumer_source(const NativeEvent&,native_menu_component::Consumer);
void enter_menu_component(const NativeEvent& event,native_menu_component::Consumer consumer) {
    using Consumer=native_menu_component::Consumer;
    const auto kind=consumer==Consumer::title_panel ? Scope::character_creation_panel :
        consumer==Consumer::button_row ? Scope::character_creation_label : Scope::text;
    begin(event,kind,kind==Scope::text ? event.arguments[2] : 0);
}

void windows_profile_error_constructed(TextComponent,u32);
Status profile_name_error(const NativeEvent& e,DispatchResult& result,TextComponent component,u32 source_rva) {
    windows_profile_error_constructed(component,source_rva);
    std::vector<char> encoded;
    const auto status=translate(component,at<char>(source_rva),nullptr,encoded);
    if(status!=Status::ok) return status;
    // Each site is the final MOVQ of one confirmed error-literal copy. Replace
    // that display-only local (0x400 bytes); validation and the input stay native.
    std::memcpy(ptr<void>(e.frame->ebp-0x408),encoded.data(),encoded.size());
    result.skip_original=1;
    return Status::ok;
}

#include "footer.inc"

Status invalidate() {
    const auto status=native_ui_scene::language_changed();
    if(status!=Status::ok) return status;
    const bool menu_active=*at<u32>(0x5F54DF0)!=0;
    const bool menu_renderer=menu_active && *at<u32>(0x5F54B94)!=0;
    // D153C/D196C/D19B3 own this shared native input phase. The original input
    // component draws its current selection after its body has been rebuilt.
    const auto draw_selection=[&] {
        const auto selection=*at<u32>(0x5F54AB0);
        constexpr u64 selection_token=0xFFFFFFFC00000000ull;
        active.push_back({selection_token,menu_renderer ? Scope::hud_renderer_text : Scope::creation_button,
            0,0,0,0,*at<u32>(0x5F54A9C)&1u});
        if(menu_renderer) {
            const native_component_calls::SelectorRendererCall call{
                address(at<void>(0xD0850)),selection};
            native_component_calls::uwcn_component_selector_renderer(&call);
        } else reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0xD0650)(selection,0);
        end(selection_token);
    };
    if(menu_active && !menu_renderer) draw_selection();
    native_language_redraw::request();
    // D1E26..D1E7B and D1ED1..D1F56 select the original presentation mode
    // from these shared input/renderer fields. The modern path composes its
    // native texture owners; 10B720 only uploads the software UI surface.
    const bool renderer=menu_renderer || *at<u32>(0x5F55634);
    using Present=void (UWCN_CALL *)();
    if(renderer) {
        reinterpret_cast<Present>(host->image_base+0x10B480)();
        // D125A -> D1266 composes the frame before drawing the modern selector
        // on the default target; composing afterward would erase that selector.
        if(menu_renderer) draw_selection();
        reinterpret_cast<Present>(host->image_base+0x10B680)();
    } else reinterpret_cast<Present>(host->image_base+0x10B720)();
    return Status::ok;
}
Status dispatch_hud(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_windows_profile(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_windows_creation(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_windows_skills(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_windows_encyclopedia(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_windows_renderer(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_windows_messages(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_native(const NativeEvent& e,DispatchResult& result) {
    result={};
    bool handled{};
    auto native_component=native_root_component::dispatch(e,result,handled);
    if(handled) return native_component;
    native_component=native_culture_legend::dispatch(e,result,handled);
    if(handled) return native_component;
    native_component=native_ui_cache_owners::dispatch(e,result,handled);
    if(handled) return native_component;
    native_component=native_menu_storage::dispatch(e,result,handled);
    if(handled) return native_component;
    native_component=native_renderer_component_model::dispatch(e,result,handled);
    if(handled) return native_component;
    native_component=native_image_component::dispatch(e,result,handled);
    if(handled) return native_component;
    native_component=native_menu_component::dispatch(e,result,handled);
    if(handled) return native_component;
    auto extension=native_name_input::dispatch(e,result,handled);
    if(handled) { if(e.phase==NativePhase::after) end(e.token);return extension; }
    for(auto dispatch_extension:{dispatch_windows_profile,dispatch_windows_creation,
            dispatch_windows_skills,dispatch_windows_encyclopedia,dispatch_windows_renderer,
            dispatch_windows_messages}) {
        extension=dispatch_extension(e,result,handled);
        if(handled) { if(e.phase==NativePhase::after) end(e.token);return extension; }
    }
    const auto language_input=native_language_input::dispatch(e,result,host->image_base);
    if(language_input.handled) {
        if(!language_input.toggle) return Status::ok;
        chinese_enabled=!chinese_enabled;
        intro_chinese=chinese_enabled;
        return invalidate();
    }
    if(native_language_redraw::dispatch(e,result)) return Status::ok;
    // Published old SDL calls can return through their resident After bridge
    // after a transaction. Their tracking service and 17 old IDs are retired.
    if(e.id>=0x4000 && e.id<=0x400C && e.phase==NativePhase::after) return Status::ok;
    if(e.phase==NativePhase::after) {
        Status status=Status::ok;
        if(e.id==version_format && in(Scope::version)) status=formatted(e,TextComponent::version,ptr<char>(e.arguments[2]));
        if(e.id==copyright_format && in(Scope::footer)) status=formatted(e,TextComponent::copyright,ptr<char>(e.arguments[2]));
        if(e.id==about_version_format) status=formatted(e,TextComponent::about_version,ptr<char>(e.arguments[2]));
        if(e.id==about_copyright_format) status=formatted(e,TextComponent::about_copyright,ptr<char>(e.arguments[2]));
        if(e.id==about_publisher_format) status=formatted(e,TextComponent::about_publisher,nullptr);
        if(e.id==about_button_character && (in(Scope::plain_button)
            || native_name_input::contains_display(native_button::label(e)))) status=native_button::character(e);
        if(e.id==ancestors_page_format) {
            const auto value=std::to_string(static_cast<std::int32_t>(e.arguments[2]))+" / "+
                std::to_string(static_cast<std::int32_t>(e.arguments[3]));
            status=formatted(e,TextComponent::ancestors_page,value.c_str());
        }
        if(e.id==footer_initial || e.id==footer_loop) status=complete_native_footer();
        end(e.token);
        if(e.id==window_targets_rebuilt) return invalidate();
        return status;
    }
    bool hud_handled{};
    const auto hud_status=dispatch_hud(e,result,hud_handled);
    if(hud_handled) return hud_status;
    if(e.id>=setup_body_first && e.id<setup_body_first+std::size(setup_text_calls)) {
        const auto& field=setup_text_calls[e.id-setup_body_first];
        const auto* original=ptr<char>(e.arguments[0]);
        // Every confirmed dynamic label is formatted by the game as
        // "LABEL: value" before this call. Borrow only its display suffix;
        // the shared English buffer, INI tokens and option actions stay intact.
        const char* value=field.dynamic_value ? std::strchr(original,':')+2 : nullptr;
        std::vector<char> encoded;
        const auto status=translate(field.component,original,value,encoded);
        if(status!=Status::ok) return status;
        return lend_text(e,encoded,e.arguments[0],Scope::text);
    }
    if(e.id>=credits_append_first && e.id<credits_append_first+std::size(credits_text_calls))
        return append(e,credits_text_calls[e.id-credits_append_first].component);
    switch(e.id) {
    case scenario_introduction_1: return append(e,TextComponent::scenario_introduction_1);
    case scenario_introduction_2: return append(e,TextComponent::scenario_introduction_2);
    case scenario_introduction_3: return append(e,TextComponent::scenario_introduction_3);
    case scenario_introduction_4: return append(e,TextComponent::scenario_introduction_4);
    case scenario_intro_paragraph:
        begin(e,Scope::paragraph,e.arguments[3]); break;
    case scenario_button: {
        std::vector<char> encoded;
        const auto status=translate(TextComponent::scenario_press_key,
            ptr<char>(e.arguments[0]),nullptr,encoded);
        if(status!=Status::ok) return status;
        return lend_text(e,encoded,e.arguments[0],Scope::plain_button);
    }
    case profile_culture_scope:
        begin(e,Scope::profile_culture); break;
    case profile_sex_scope:
        begin(e,Scope::profile_sex); break;
    case profile_heading_panel: case profile_name_panel: {
        const auto component=e.id==profile_heading_panel ? TextComponent::profile_heading : TextComponent::profile_name_title;
        std::vector<char> encoded;
        const auto status=translate(component,ptr<char>(e.arguments[2]),nullptr,encoded);
        if(status!=Status::ok) return status;
        // 12F0D flags 0x30 -> mode 1; 11939 flags 4 -> mode 2. Both native
        // title paths are left aligned and consume the shared 115A94 call.
        return lend_text(e,encoded,e.arguments[2],Scope::profile_panel);
    }
    case profile_name_help: return append(e,TextComponent::profile_name_help);
    case profile_name_help_repeat: return append(e,TextComponent::profile_name_help_repeat);
    case profile_sex_help: return append(e,TextComponent::profile_sex_help);
    case profile_name_footer: case profile_sex_footer: begin(e,Scope::profile_footer); break;
    case profile_name_too_short:
        return profile_name_error(e,result,TextComponent::profile_name_too_short,0x190328);
    case profile_name_invalid:
        return profile_name_error(e,result,TextComponent::profile_name_invalid,0x190344);
    case profile_name_exists:
        return profile_name_error(e,result,TextComponent::profile_name_exists,0x190380);
    case character_creation_scope:
        begin(e,Scope::character_creation); break;
    case load_saved_empty_panel: case load_saved_list_panel:
        native_menu_component::bind_title(TextComponent::load_saved_title,at<char>(0x5F54A38));
        begin(e,Scope::load_saved_panel); break;
    case load_saved_empty_text: case load_saved_key_text: {
        std::vector<char> encoded;
        const auto component=e.id==load_saved_empty_text
            ? TextComponent::load_saved_empty : TextComponent::load_saved_press_key;
        const auto status=translate(component,ptr<char>(e.arguments[0]),nullptr,encoded);
        if(status!=Status::ok) return status;
        return lend_text(e,encoded,e.arguments[0],Scope::text);
    }
    case ancestors_title: {
        // ESI is DE990's original ECX mode here: -1 is the ancestor list.
        // The death branch shares this call but keeps its original title.
        if(e.frame->esi!=static_cast<u32>(-1)) break;
        std::vector<char> encoded;
        const auto status=translate(TextComponent::ancestors_title,ptr<char>(e.arguments[1]),nullptr,encoded);
        if(status!=Status::ok) return status;
        return lend_text(e,encoded,e.arguments[1],Scope::ancestors_title);
    }
    case ancestors_empty: case ancestors_order: case ancestors_select: {
        const auto component=e.id==ancestors_empty ? TextComponent::ancestors_empty :
            e.id==ancestors_order ? TextComponent::ancestors_order_label : TextComponent::ancestors_select_hint;
        std::vector<char> encoded;
        const auto status=translate(component,ptr<char>(e.arguments[0]),nullptr,encoded);
        if(status!=Status::ok) return status;
        // 10E720 assembles complete strings around the ASCII [ENTER] marker;
        // its two native text leaves consume our encoded text and real width.
        return lend_text(e,encoded,e.arguments[0],
            e.id==ancestors_select ? Scope::ancestors_select : Scope::text);
    }
    case ancestors_select_prefix: case ancestors_select_suffix:
        if(in(Scope::ancestors_select)) begin(e,Scope::text,e.arguments[2]);
        break;
    case ancestors_page_text:
        begin(e,Scope::text,e.arguments[2]); break;
    case ancestors_row: {
        auto* numbers=static_cast<AncestorNumbers*>(host->allocate(sizeof(AncestorNumbers)));
        numbers->record_id=**ptr<u32*>(e.frame->ebp-0x5A8);
        active.push_back({e.token,Scope::ancestors_row,address(numbers),0,0,0,0});
        break;
    }
    case ancestors_lived_format:
        if(in(Scope::ancestors_row)) {
            auto& numbers=ancestor_numbers();
            numbers.age=static_cast<std::int32_t>(e.arguments[3]);
            numbers.days=static_cast<std::int32_t>(e.arguments[4]);
        }
        break;
    case ancestors_distance_format:
        if(in(Scope::ancestors_row))
            ancestor_numbers().kilometers=static_cast<std::int32_t>(e.arguments[3]);
        break;
    case ancestors_lived_text: case ancestors_distance_text:
        if(in(Scope::ancestors_row)) {
            const auto& numbers=ancestor_numbers();
            native_component_binding::note_native_record(e,numbers.record_id);
            const bool lived=e.id==ancestors_lived_text;
            const auto value=lived ? std::to_string(numbers.age)+"|"+
                std::to_string(numbers.days) : std::to_string(numbers.kilometers);
            std::vector<char> encoded;
            const auto status=translate(lived ? TextComponent::ancestors_lived : TextComponent::ancestors_journeyed,
                ptr<char>(e.arguments[0]),value.c_str(),encoded);
            if(status!=Status::ok) return status;
            // Native sprintf and its following toupper operate on English.
            // Only this display call borrows the translated complete sentence.
            return lend_text(e,encoded,e.arguments[0],Scope::text);
        }
        break;
    case intro_sequence_scope:
        intro_chinese=chinese_enabled;
        break;
    case about_scope:
        begin(e,Scope::about); break;
    case credits_scope:
        begin(e,Scope::credits); break;
    case credits_paragraph:
        begin(e,Scope::paragraph,e.arguments[3]); break;
    case about_panel: case credits_panel: {
        std::vector<char> encoded;
        const auto component=e.id==about_panel ? TextComponent::about_title : TextComponent::credits_title;
        const auto status=translate(component,ptr<char>(e.arguments[2]),nullptr,encoded);
        if(status!=Status::ok) return status;
        return lend_text(e,encoded,e.arguments[2],Scope::titled_panel);
    }
    case about_title_width:
        if(in(Scope::titled_panel))
            return native_width(e,result,ptr<char>(e.frame->esp+0x80));
        break;
    case about_title_text:
        if(in(Scope::titled_panel)) return centered_text(e);
        break;
    case about_version_width: case about_copyright_width: case about_publisher_width:
    case about_website_width:
        return native_width(e,result,ptr<char>(e.frame->ebp-0x408));
    case about_path_width:
        return native_width(e,result,ptr<char>(e.frame->ebp-0x808));
    case about_notes_width:
        return about_literal_width(e,result,TextComponent::about_release_notes);
    case about_install_width:
        return about_literal_width(e,result,TextComponent::about_install_label);
    case about_version_text: case about_copyright_text: case about_publisher_text:
    case about_notes_text: case about_install_text: case about_website_text: case about_path_text:
        return centered_text(e);
    case about_button: case credits_button: {
        std::vector<char> encoded;
        const auto component=e.id==about_button ? TextComponent::about_press_key : TextComponent::credits_press_key;
        const auto status=translate(component,ptr<char>(e.arguments[0]),nullptr,encoded);
        if(status!=Status::ok) return status;
        return lend_text(e,encoded,e.arguments[0],Scope::plain_button);
    }
    case about_button_width:
        if(in(Scope::plain_button) || (native_name_input::contains_display(native_button::label(e))
            && !std::strchr(native_button::label(e),'.'))) return native_button::width(e,result,metrics);
        break;
    case about_button_text:
        if(in(Scope::plain_button)) begin(e,Scope::text,e.arguments[2]);
        break;
    case about_button_advance:
        if(in(Scope::plain_button) || (native_name_input::contains_display(native_button::label(e))
            && !std::strchr(native_button::label(e),'.')))
            return native_button::advance(e,result,metrics);
        break;
    case about_wait:case credits_wait:case about_input_tick:break;
    case setup_panel: {
        std::vector<char> encoded;
        const auto status=translate(TextComponent::setup_title,ptr<char>(e.arguments[2]),nullptr,encoded);
        if(status!=Status::ok) return status;
        // 116270 copies the borrowed title; flags 0x30 select 1157B0 mode 1,
        // whose native left alignment does not use either strlen*8 center path.
        return lend_text(e,encoded,e.arguments[2],Scope::setup_panel);
    }
    case shared_title_text:
        if(in(Scope::load_saved_panel)) {
            // CFFB0 kind 8 -> 115E70 flags 4 -> 1157B0 mode 2. This native
            // left-aligned title does not use the strlen-based center paths.
            // Keep CF790's English menu title and the panel's copy unchanged.
            std::vector<char> encoded;
            const auto status=translate(TextComponent::load_saved_title,ptr<char>(e.arguments[0]),nullptr,encoded);
            if(status!=Status::ok) return status;
            return lend_text(e,encoded,e.arguments[0],Scope::text);
        }
        if(in(Scope::titled_panel) || in(Scope::setup_panel) || in(Scope::ancestors_title) || in(Scope::character_creation_panel)
            || in(Scope::profile_panel) || in(Scope::scenario_panel))
            begin(e,Scope::text,e.arguments[2]);
        break;
    case setup_controls_append: return append(e,TextComponent::setup_controls_help);
    case setup_config_append: return append(e,TextComponent::setup_config_help);
    case setup_footer: begin(e,Scope::setup_footer); break;
    case shared_footer_paragraph:
        if(in(Scope::setup_footer) || in(Scope::profile_footer)) begin(e,Scope::paragraph,e.arguments[3]);
        break;
    case setup_exit_scope: case ancestors_exit: case ancestors_played: case ancestors_living:
    case ancestors_distance: case ancestors_previous: case ancestors_next: {
        const auto* original=ptr<char>(e.arguments[1]);
        const auto* suffix=std::strchr(original,'.')+1;
        TextComponent component=TextComponent::setup_exit;
        switch(e.id) {
        case ancestors_exit: component=TextComponent::ancestors_exit; break;
        case ancestors_played: component=TextComponent::ancestors_order_played; break;
        case ancestors_living: component=TextComponent::ancestors_order_lived; break;
        case ancestors_distance: component=TextComponent::ancestors_order_journeyed; break;
        case ancestors_previous: component=TextComponent::ancestors_previous_page; break;
        case ancestors_next: component=TextComponent::ancestors_next_page; break;
        default: break;
        }
        std::vector<char> encoded;
        const auto status=translate(component,suffix,nullptr,encoded);
        if(status!=Status::ok) return status;
        native_component_binding::note_prefix(e,std::string(original,suffix).c_str());
        encoded.insert(encoded.begin(),original,suffix);
        // Keep the native key prefix/parser and lend only this synchronous
        // button call its localized label. 5F54A9C supplies the label outline.
        return lend_text(e,encoded,e.arguments[1],Scope::setup_exit,*at<u32>(0x5F54A9C));
    }
    case setup_exit_text:
        if(in(Scope::setup_exit) || in(Scope::character_creation_label)) begin(e,Scope::text,e.arguments[2]);
        break;
    case setup_exit_width:
        if(in(Scope::setup_exit) || native_name_input::contains_display(ptr<char>(e.frame->edi))) {
            // CFAF0 has already terminated its local copy at '.', while EDI
            // still owns the complete borrowed text. Preserve the native ESC
            // cell width, separator and margins; replace only suffix width.
            const auto prefix=std::strlen(ptr<char>(e.frame->ebp-0x408));
            render::Metrics measured{};
            const auto status=metrics(ptr<char>(e.frame->edi)+prefix+1,measured);
            if(status!=Status::ok) return status;
            e.frame->eax=static_cast<u32>((prefix+1)*8+10+measured.logical_width);
            result.skip_original=1;
        }
        break;
    case intro_north: case intro_roleplaying: {
        std::vector<char> encoded;
        const auto component=e.id==intro_north ? TextComponent::intro_north : TextComponent::intro_roleplaying;
        const auto status=translate(component,ptr<char>(e.arguments[0]),nullptr,encoded);
        if(status!=Status::ok) return status;
        return lend_text(e,encoded,e.arguments[0],Scope::text);
    }
    case intro_story_scope: {
        auto* field=static_cast<u32*>(host->allocate(sizeof(u32)));
        *field=static_cast<u32>(TextComponent::intro_story_0);
        active.push_back({e.token,Scope::intro_story,address(field),0,0,0,0});
        break;
    }
    case intro_story_width:
        if(in(Scope::intro_story)) {
            // 125400..12542F copied the English table's EDI-indexed line to
            // this native display buffer and pushed its address. Replace only
            // that copy; the supplied catalog's longest encoded line is 47
            // bytes including NUL, within [EBP-70, EBP-4)'s 0x6C bytes.
            auto* display=ptr<char>(e.frame->ebp-0x70);
            const auto component=static_cast<TextComponent>(static_cast<u32>(TextComponent::intro_story_0)+e.frame->edi);
            const auto owner=std::find_if(active.rbegin(),active.rend(),[](const Active& scope){return scope.kind==Scope::intro_story;});
            *ptr<u32>(owner->allocation)=static_cast<u32>(component);
            std::vector<char> encoded;
            auto status=translate(component,display,nullptr,encoded);
            if(status!=Status::ok) return status;
            render::Metrics measured{};
            status=metrics(encoded.data(),measured);
            if(status!=Status::ok) return status;
            std::memcpy(display,encoded.data(),encoded.size());
            // Replace only LEA EAX,[ECX*8]. The native instructions that
            // follow halve this width and calculate the line's center.
            e.frame->eax=static_cast<u32>(measured.logical_width);
            result.skip_original=1;
        }
        break;
    case intro_story_fade_text: case intro_story_settled_text:
        if(in(Scope::intro_story)) {
            const auto owner=std::find_if(active.rbegin(),active.rend(),[](const Active& scope){return scope.kind==Scope::intro_story;});
            const auto component=static_cast<TextComponent>(*ptr<u32>(owner->allocation));
            native_component_binding::note_source_for_consumer(e,component);
            render::Metrics old_width{},new_width{};
            auto status=metrics_at_outline(ptr<char>(e.arguments[0]),e.arguments[2]&1u,old_width);
            if(status!=Status::ok) return status;
            const auto center=static_cast<std::int32_t>(e.frame->ecx)+old_width.logical_width/2;
            native_component_binding::note_center(e,center);
            const auto& source=native_component_binding::field_source(component);
            std::vector<char> encoded;
            status=native_text_resource::resolve_source(source,resolve_display_text,encode_component_original,encoded);
            if(status!=Status::ok) return status;
            status=metrics_at_outline(encoded.data(),e.arguments[2]&1u,new_width);
            if(status!=Status::ok) return status;
            e.frame->ecx=static_cast<u32>(center-new_width.logical_width/2);
            return lend_text(e,encoded,e.arguments[0],Scope::text);
        }
        break;
    case startup_heading: {
        std::vector<char> encoded;
        auto status=translate(TextComponent::startup_loading,ptr<char>(e.arguments[0]),nullptr,encoded);
        if(status!=Status::ok) return status;
        if(encoded.size()>0x12C) return Status::insufficient_buffer;
        return lend_text(e,encoded,e.arguments[0],Scope::text);
    }
    case startup_audio_ogg_scope: case startup_audio_samples_scope:
        begin(e,Scope::startup_audio); break;
    case startup_intro_scope: begin(e,Scope::startup_intro); break;
    case startup_sound_init:
        return startup_progress(e,TextComponent::startup_sound_init);
    case startup_device_failed:
        return startup_progress(e,TextComponent::startup_audio_device_failed);
    case startup_intro_progress:
        if(in(Scope::startup_intro)) return startup_progress(e,TextComponent::startup_intro);
        break;
    case startup_named_audio:
        if(in(Scope::startup_audio))
            return startup_progress(e,TextComponent::startup_audio,ptr<char>(e.frame->edi));
        break;
    case startup_file_audio:
        if(in(Scope::startup_audio))
            return startup_progress(e,TextComponent::startup_audio,ptr<char>(e.frame->ebp-0x70));
        break;
    case startup_named_failed:
        if(in(Scope::startup_audio))
            return startup_progress(e,TextComponent::startup_audio_failed,ptr<char>(e.frame->ebp-0x808));
        break;
    case startup_file_failed:
        if(in(Scope::startup_audio))
            return startup_progress(e,TextComponent::startup_audio_failed,ptr<char>(e.frame->ebp-0x870));
        break;
    case startup_progress_text:
        for(auto i=active.rbegin();i!=active.rend();++i) {
            if(i->kind==Scope::startup_progress) {
                native_component_binding::bind_source(e,startup_progress_source);
                native_component_binding::note_native_field(e,0);
                e.arguments[0]=i->allocation;
                begin(e,Scope::text,e.arguments[2]);
                break;
            }
        }
        break;
    case menu_scope: begin(e,Scope::menu); break;
    case menu_input: begin(e,Scope::menu_input); break;
    case footer_initial: case footer_loop: {
        const auto status=native_targets::promote();
        if(status!=Status::ok) return status;
        begin(e,Scope::footer); break;
    }
    case intro_version_scope:
        begin(e,Scope::intro_version);
        [[fallthrough]];
    case version_scope: begin(e,Scope::version); break;
    case footer_panel:
        if(in(Scope::footer)) footer_native_panel(e);
        break;
    case footer_logo:
        break;
    case production_paragraph: case copyright_paragraph: case authors_paragraph:
        if(in(Scope::footer)) begin(e,Scope::paragraph,e.arguments[3]);
        break;
    case production_append:
        if(in(Scope::footer)) return append(e,TextComponent::production);
        break;
    case authors_append:
        if(in(Scope::footer)) return append(e,TextComponent::authors);
        break;
    case copyright_append:
        if(in(Scope::footer)) {
            native_component_binding::note_source_for_consumer(e,TextComponent::copyright);
            return paragraph_capacity(ptr<char>(e.frame->edx));
        }
        break;
    case version_text:
        if(in(Scope::version)) return centered_text(e);
        break;
    case paragraph_text:
        if(in(Scope::paragraph) || native_name_input::contains_display(ptr<char>(e.arguments[0])))
            begin(e,Scope::text,e.arguments[2]);
        break;
    case outline_top: case outline_bottom: case outline_left: case outline_right: case foreground:
        if(text_context() || native_name_input::contains_display(ptr<char>(e.arguments[0]))) {
            auto status=draw(e);
            if(status!=Status::ok) return status;
            result.skip_original=1;
        }
        break;
    case cursor_width:
        if(text_context() || native_name_input::contains_display(ptr<char>(e.frame->ebp-0x130))) {
            render::Metrics measured{};
            const auto* display=ptr<char>(e.frame->ebp-0x130);
            auto status=text_context() ? metrics(display,measured) :
                metrics_at_outline(display,*ptr<u32>(e.frame->ebp+0x10)&1u,measured);
            if(status!=Status::ok) return status;
            *at<u32>(0x61BBB3C)=e.frame->ebx;
            e.frame->eax+=static_cast<u32>(measured.logical_width);
            result.skip_original=1;
        }
        break;
    case version_width:
        if(in(Scope::version)) {
            render::Metrics measured{};
            auto status=metrics(ptr<char>(e.frame->ebp-0x408),measured);
            if(status!=Status::ok) return status;
            e.frame->eax=static_cast<u32>(measured.logical_width);
            result.skip_original=1;
        }
        break;
    case paragraph_width:
        if(in(Scope::paragraph) || native_name_input::contains_display(ptr<char>(e.frame->ebp-0x404))) {
            render::Metrics measured{};
            auto status=metrics(ptr<char>(e.frame->ebp-0x404),measured);
            if(status!=Status::ok) return status;
            e.frame->ecx=e.frame->eax+static_cast<u32>(measured.logical_width);
            e.frame->eax=*ptr<u32>(e.frame->ebp+8);
            result.skip_original=1;
        }
        break;
    case paragraph_advance:
        if(in(Scope::paragraph) || native_name_input::contains_display(ptr<char>(e.frame->ebp-0x804))) {
            render::Metrics measured{};
            auto status=metrics(ptr<char>(e.frame->ebp-0x804),measured);
            if(status!=Status::ok) return status;
            e.frame->eax+=static_cast<u32>(measured.logical_width);
            e.frame->ebx=*ptr<u32>(e.frame->ebp-0xC08);
            result.skip_original=1;
        }
        break;
    default: break;
    }
    return Status::ok;
}

Status dispatch(const NativeEvent& event,DispatchResult& result) {
    native_component_binding::begin_event(event);
    native_renderer_component_binding::begin_event(event);
    const auto status=native_renderer_component_binding::finish_event(event,result,
        dispatch_native(event,result));
    return native_component_binding::finish_event(event,result,status);
}

HookSpec call(u32 id,u32 site,u32 target,u32 count) {
    HookSpec s{id,HookKind::call,site,target,count,5,{0xE8}};
    const auto relative=target-site-5;
    std::memcpy(s.expected+1,&relative,4);
    return s;
}
HookSpec inline_hook(u32 id,u32 site,std::initializer_list<unsigned char> bytes) {
    HookSpec s{id,HookKind::inline_code,site,0,0,static_cast<u32>(bytes.size()),{}};
    std::copy(bytes.begin(),bytes.end(),s.expected);
    return s;
}
#include "hud_native.inc"
#include "windows_profile_extras.inc"
#include "windows_creation.inc"
#include "windows_skills_spells.inc"
#include "windows_encyclopedia.inc"
Status bind_menu_consumer_source(const NativeEvent& e,native_menu_component::Consumer consumer) {
    using Consumer=native_menu_component::Consumer;
    if(consumer==Consumer::plain_row && in(Scope::menu)) {
        native_menu_component::bind_row(e.frame->esi,static_cast<TextComponent>(e.frame->ebx),
            ptr<char>(e.arguments[0]));
    } else if(consumer==Consumer::title_panel) {
        if(windows_season_drawing)
            native_menu_component::bind_title(TextComponent::profile_season_title,ptr<char>(e.arguments[2]));
        else if(in(Scope::character_creation) || in(Scope::profile_culture) || in(Scope::profile_sex)) {
            const auto component=in(Scope::profile_culture) ? TextComponent::profile_culture_title :
                in(Scope::profile_sex) ? TextComponent::profile_sex_title : TextComponent::character_creation_title;
            native_menu_component::bind_title(component,ptr<char>(e.arguments[2]));
        }
    } else if(consumer==Consumer::button_row) {
        const auto action=*ptr<u32>(e.frame->esi+0xC8);
        if(windows_season_drawing) {
            if(action>='1' && action<='4') return character_creation_label(e,static_cast<TextComponent>(
                static_cast<u32>(TextComponent::profile_season_spring)+action-'1'));
            if(action==27) return character_creation_label(e,TextComponent::profile_back);
        } else if(windows_attributes_drawing) {
            if(action=='Y') return character_creation_label(e,TextComponent::profile_continue);
            if(action=='N') return character_creation_label(e,TextComponent::profile_reroll);
        } else if(in(Scope::profile_culture)) {
            if(action>='0' && action<='9') return character_creation_label(e,static_cast<TextComponent>(
                static_cast<u32>(TextComponent::profile_culture_0)+action-'0'));
            switch(action) {
            case 'R': return character_creation_label(e,TextComponent::profile_random);
            case '?': return character_creation_label(e,TextComponent::profile_cultures);
            case 27: return character_creation_label(e,TextComponent::profile_back);
            }
        } else if(in(Scope::profile_sex)) {
            switch(action) {
            case 'M': return character_creation_label(e,TextComponent::profile_male);
            case 'F': return character_creation_label(e,TextComponent::profile_female);
            case 27: return character_creation_label(e,TextComponent::profile_back);
            }
        } else if(in(Scope::character_creation)) {
            switch(action) {
            case 'Q': return character_creation_label(e,TextComponent::character_creation_quick);
            case 'C': return character_creation_label(e,TextComponent::character_creation_custom);
            case 'E': return character_creation_label(e,TextComponent::character_creation_easy);
            case 'T': return character_creation_label(e,TextComponent::character_creation_too_easy);
            case 27: return character_creation_label(e,TextComponent::character_creation_exit);
            }
        }
    }
    return Status::ok;
}
Status translate_skills_limit(TextComponent component,const char* value,std::vector<char>& encoded) {
    const char* key=component==TextComponent::skills_limit_improve ? "limit.improve" : "limit.degrade";
    const TextRequest request{TextComponent::skills_text,"",key};
    std::vector<char> utf8;
    auto status=service_text(ModuleId::main_menu,text_op::translate,&request,sizeof(request),utf8);
    if(status!=Status::ok) return status;
    std::string text(utf8.data());text.replace(text.find("{value}"),7,value);
    return codec(layout_op::encode_native,text.c_str(),encoded);
}
Status translate_help_record(TextComponent component,const char* value,std::vector<char>& encoded) {
    const std::string identity(value);
    const auto separator=identity.rfind('#');
    if(identity.substr(separator+1)!="0") {encoded.assign(1,0);return Status::ok;}
    const auto key=identity.substr(0,separator);
    const TextRequest request{component==TextComponent::skills_help_record ?
        TextComponent::skills_text : TextComponent::spells_text,"",key.c_str()};
    std::vector<char> utf8;
    const auto status=service_text(ModuleId::main_menu,text_op::translate,&request,sizeof(request),utf8);
    return status==Status::ok ? codec(layout_op::encode_native,utf8.data(),encoded) : status;
}
Status translate_culture_back(const char*,const char* topic,std::vector<char>& encoded) {
    std::vector<char> pattern;
    auto status=windows_culture_text("ui.back",pattern);
    if(status!=Status::ok) return status;
    auto wide=[](const char* value) {
        const int count=MultiByteToWideChar(CP_UTF8,0,value,-1,nullptr,0);
        std::wstring result(static_cast<std::size_t>(count),L'\0');
        MultiByteToWideChar(CP_UTF8,0,value,-1,result.data(),count);
        return result;
    };
    const auto topic_name=wide(topic);
    const WindowsEncyclopediaTopic* semantic_topic{};
    for(const auto& candidate:windows_encyclopedia_topics) {
        std::string native_name;
        decode_parser_original(candidate.name,native_name);
        const auto candidate_name=wide(native_name.c_str());
        if(CompareStringOrdinal(topic_name.data(),-1,candidate_name.data(),-1,TRUE)==CSTR_EQUAL) {
            semantic_topic=&candidate;break;
        }
    }
    std::vector<char> title;
    if(semantic_topic) status=windows_culture_text(std::string("topic.")+semantic_topic->key+".title",title);
    else status=codec(layout_op::encode_native,topic,title);
    if(status!=Status::ok) return status;
    std::string text(pattern.data());
    text.replace(text.find("{value}"),7,title.data());
    encoded.assign(text.begin(),text.end());encoded.push_back(0);
    return Status::ok;
}
#include "windows_renderer_text.inc"
#include "windows_messages.inc"
#include "windows_message_values.inc"
#include "windows_message_crafted_items.inc"
#include "windows_message_items.inc"
#include "windows_message_materials.inc"
#include "windows_message_geography.inc"
#include "windows_message_calendar.inc"
#include "windows_message_prayers.inc"
#include "windows_message_resources.inc"
#include "windows_message_display.inc"
#include "windows_message_formats.inc"
#include "windows_message_format_builders.inc"
#include "windows_message_helpers.inc"
#include "windows_message_quests.inc"
#include "windows_message_menu_echo.inc"
#include "windows_message_menu_return.inc"
#include "windows_message_appended.inc"
#include "windows_message_transfers.inc"
#include "windows_message_hearing.inc"
#include "windows_message_weather.inc"
#include "windows_message_debug_sources.inc"
#include "windows_message_combat_body.inc"
#include "windows_message_audit_copies.inc"
#include "windows_message_late_sources.inc"

Status message_translate_value(const char* tag,const char* value,std::string& text) {
    return windows_message_values::translate_tag(tag,value,text);
}
Status message_resolve_value(const char* domain,const char* value,std::string& text) {
    return windows_message_values::resolve(domain,value,text);
}
Status dispatch_windows_messages(const NativeEvent& event,DispatchResult& result,bool& handled) {
    if(event.id==windows_message_resources::tag_value) {
        if(event.phase==NativePhase::before) windows_message_values::begin_tag();
        const auto status=windows_message_resources::dispatch(event,result,handled);
        if(event.phase==NativePhase::after) windows_message_values::end_tag();
        return status;
    }
    for(auto dispatch:{windows_messages::dispatch,windows_message_values::dispatch,
            windows_message_items::dispatch,windows_message_materials::dispatch,windows_message_geography::dispatch,windows_message_calendar::dispatch,windows_message_prayers::dispatch,windows_message_resources::dispatch,
            windows_message_display::dispatch,windows_message_formats::dispatch,
            windows_message_helpers::dispatch,windows_message_quests::dispatch,
            windows_message_format_builders::dispatch,windows_message_menu_echo::dispatch,
            windows_message_menu_return::dispatch,
            windows_message_appended::dispatch,windows_message_transfers::dispatch,
            windows_message_hearing::dispatch,windows_message_weather::dispatch,
            windows_message_debug_sources::dispatch,windows_message_combat_body::dispatch,
            windows_message_audit_copies::dispatch,windows_message_late_sources::dispatch}) {
        const auto status=dispatch(event,result,handled);
        if(handled) return status;
    }
    return Status::ok;
}
void append_windows_message_hooks(std::vector<HookSpec>& hooks) {
    windows_messages::append_hooks(hooks);
    windows_message_values::append_hooks(hooks);
    windows_message_items::append_hooks(hooks);
    windows_message_materials::append_hooks(hooks);
    windows_message_geography::append_hooks(hooks);
    windows_message_calendar::append_hooks(hooks);
    windows_message_prayers::append_hooks(hooks);
    windows_message_resources::append_hooks(hooks);
    windows_message_display::append_hooks(hooks);
    windows_message_formats::append_hooks(hooks);
    windows_message_format_builders::append_hooks(hooks);
    windows_message_helpers::append_hooks(hooks);
    windows_message_quests::append_hooks(hooks);
    windows_message_menu_echo::append_hooks(hooks);
    windows_message_menu_return::append_hooks(hooks);
    windows_message_appended::append_hooks(hooks);
    windows_message_transfers::append_hooks(hooks);
    windows_message_hearing::append_hooks(hooks);
    windows_message_weather::append_hooks(hooks);
    windows_message_debug_sources::append_hooks(hooks);
    windows_message_combat_body::append_hooks(hooks);
    windows_message_audit_copies::append_hooks(hooks);
    windows_message_late_sources::append_hooks(hooks);
}
std::vector<unsigned char> save_windows_message_state() {
    std::vector<unsigned char> state;
    windows_messages::save(state);
    windows_message_values::save(state);
    windows_message_items::save(state);
    windows_message_geography::save(state);
    windows_message_calendar::save(state);
    windows_message_resources::save(state);
    windows_message_helpers::save(state);
    windows_message_quests::save(state);
    windows_message_formats::save(state);
    windows_message_format_builders::save(state);
    windows_message_menu_echo::save(state);
    return state;
}
void restore_windows_message_state(const unsigned char* state) {
    windows_messages::restore(state);
    windows_message_values::restore(state);
    windows_message_items::restore(state);
    windows_message_geography::restore(state);
    windows_message_calendar::restore(state);
    windows_message_resources::restore(state);
    windows_message_helpers::restore(state);
    windows_message_quests::restore(state);
    windows_message_formats::restore(state);
    windows_message_format_builders::restore(state);
    windows_message_menu_echo::restore(state);
}
std::vector<std::uint8_t> save_native_ui_state() {
    const std::vector<std::vector<std::uint8_t>> sections{
        native_root_component::save(),native_component_model::save(),native_component_binding::save(),
        native_image_component::save(),native_footer_component::save(),native_renderer_component_model::save(),native_hud_icons::save(),
        native_renderer_component_binding::save(),native_culture_legend::save(),native_link_flow_component::save(),
        native_message_flow::save(),native_ui_scene::save(),
        save_windows_encyclopedia_state(),save_windows_skill_help_sources(),save_windows_profile_error_source(),
        save_startup_progress_source(),native_menu_storage::save()};
    std::vector<std::uint8_t> output;
    for(const auto& section:sections) {
        const auto size=static_cast<u32>(section.size());
        const auto* bytes=reinterpret_cast<const std::uint8_t*>(&size);
        output.insert(output.end(),bytes,bytes+sizeof(size));
        output.insert(output.end(),section.begin(),section.end());
    }
    return output;
}
void restore_native_ui_state(const void* payload) {
    const auto* cursor=static_cast<const std::uint8_t*>(payload);
    using Restore=void (*)(const void*);
    const Restore restore_sections[]{native_root_component::restore,native_component_model::restore,
        native_component_binding::restore,native_image_component::restore,native_footer_component::restore,
        native_renderer_component_model::restore,native_hud_icons::restore,native_renderer_component_binding::restore,
        native_culture_legend::restore,
        native_link_flow_component::restore,native_message_flow::restore,native_ui_scene::restore,restore_windows_encyclopedia_state,
        restore_windows_skill_help_sources,restore_windows_profile_error_source,restore_startup_progress_source,
        native_menu_storage::restore};
    for(const auto restore:restore_sections) {
        u32 bytes;std::memcpy(&bytes,cursor,sizeof(bytes));cursor+=sizeof(bytes);
        restore(cursor);cursor+=bytes;
    }
}
Status dispatch_windows_renderer(const NativeEvent& e,DispatchResult& result,bool& handled) {
    return windows_renderer_text::dispatch(e,result,handled);
}
void initialization_failure(const wchar_t* boundary,Status status) {
    const auto message=std::wstring(L"Adapter initialization failed at ")+boundary+L"; status="+
        std::to_wstring(static_cast<u32>(status));
    host->log(message.c_str());
}
Status UWCN_CALL initialize(const HostApi* api) {
    if(!api || api->size<sizeof(HostApi) || api->abi!=kHostAbi) return Status::invalid;
    host=api;
    native_language_redraw::initialize(api->image_base);
    native_menu_component::initialize(api->image_base);
    native_menu_storage::initialize(api->image_base);
    native_menu_component::configure(api,resolve_display_text,encode_component_original,decode_parser_original,
        bind_menu_consumer_source,enter_menu_component,end);
    native_menu_component::configure_measure(measure_component_text);
    native_root_component::initialize(api->image_base);
    native_component_model::initialize(api->image_base);
    native_renderer_component_model::initialize(api->image_base);
    native_renderer_component_binding::configure(api->image_base,renderer_component_services());
    native_renderer_component_binding::configure_resource_services({enter_culture_resource,leave_culture_resource});
    native_culture_legend::initialize(api->image_base,{enter_culture_resource,leave_culture_resource});
    native_link_flow_component::initialize(api->image_base);
    configure_windows_encyclopedia_flow_services();
    native_message_flow::initialize(api->image_base);
    native_message_flow::configure(windows_messages::flow_services());
    native_image_component::initialize(api->image_base);
    native_footer_component::initialize(api->image_base);
    native_footer_component::configure(footer_services());
    native_ui_scene::initialize(api->image_base,component_paint_services());
    native_component_binding::configure(api->image_base,component_paint_services());
    native_component_binding::set_parser_source_decoder(decode_parser_original);
    native_component_binding::set_parser_source_encoder(encode_parser_original);
    native_ui_cache_owners::initialize(api->image_base);
    native_ui_cache_owners::set_callbacks({cache_source_saved,cache_source_before_restore,
        cache_source_restored,cache_source_retired});
    auto sdl=GetModuleHandleW(L"SDL2.dll");
    if(!sdl) return Status::unavailable;
    get_rgb=reinterpret_cast<GetRGB>(GetProcAddress(sdl,"SDL_GetRGB"));
    if(!get_rgb) return Status::unavailable;
    auto name_status=native_name_input::initialize(sdl);
    if(name_status!=Status::ok) { initialization_failure(L"native name input API",name_status);return name_status; }
    auto encyclopedia_status=initialize_windows_encyclopedia();
    if(encyclopedia_status!=Status::ok) { initialization_failure(L"encyclopedia link catalog",encyclopedia_status);return encyclopedia_status; }
    auto status=abi1_retirement::retire_tracking_hooks(api->image_base,GetModuleHandleW(L"uwcn_loader.dll"),sdl,&retired_routes);
    if(status!=Status::ok) { initialization_failure(L"retired native bridge",status);return status; }
    status=native_targets::initialize(api->image_base,sdl);
    if(status!=Status::ok) { initialization_failure(L"native target API",status);return status; }
    status=native_targets::install();
    if(status!=Status::ok) { initialization_failure(L"native target gateway installation",status);return status; }
    const auto routes=native_targets::routes();
    status=abi1_retirement::bind_routes(retired_routes,routes);
    if(status!=Status::ok) { initialization_failure(L"retired route binding",status);return status; }
    status=native_raster::install_raster_patches(api->image_base,sdl);
    if(status!=Status::ok) { initialization_failure(L"native raster installation",status);return status; }
    std::vector<HookSpec> hooks{
        call(load_saved_empty_panel,0x124FE7,0xCFFB0,0),
        call(load_saved_list_panel,0x12508D,0xCFFB0,0),
        call(load_saved_empty_text,0x12501E,0x10E5A0,3),
        call(load_saved_key_text,0x125054,0x10E5A0,3),
        call(ancestors_title,0xDEA14,0x1157B0,3),
        call(ancestors_empty,0xDEEE6,0x10E5A0,3),
        call(ancestors_order,0xDEF72,0x10E5A0,3),
        call(ancestors_exit,0xDEF21,0xCFAF0,2),
        call(ancestors_played,0xDEF91,0xCFAF0,2),
        call(ancestors_living,0xDEFC8,0xCFAF0,2),
        call(ancestors_distance,0xDEFFF,0xCFAF0,2),
        call(ancestors_previous,0xDF03A,0xCFAF0,2),
        call(ancestors_next,0xDF081,0xCFAF0,2),
        call(ancestors_select,0xDEEB0,0x10E720,2),
        call(ancestors_select_prefix,0x10E862,0x10E5A0,3),
        call(ancestors_select_suffix,0x10E8F2,0x10E5A0,3),
        call(ancestors_page_format,0xDF0BB,0x10D0,4),
        call(ancestors_page_text,0xDF115,0x10E5A0,3),
        call(ancestors_row,0xDEDA0,0xDD400,2),
        call(ancestors_lived_format,0xDD670,0x10D0,5),
        call(ancestors_distance_format,0xDD6D6,0x10D0,4),
        call(ancestors_lived_text,0xDDA0A,0x10E5A0,3),
        call(ancestors_distance_text,0xDDA30,0x10E5A0,3),
        call(intro_sequence_scope,0x18097D,0x1254C0,0),
        call(about_scope,0x125E39,0x1247C0,0),
        call(about_panel,0x124848,0x116270,5),
        call(about_version_format,0x124862,0x10D0,3),
        call(about_copyright_format,0x1248BA,0x10D0,3),
        call(about_publisher_format,0x12490D,0x10D0,2),
        // Title, plain-button and input consumers retain their published IDs;
        // Credits shares them through component scopes, never duplicate hooks.
        inline_hook(about_title_width,0x116631,{0x8B,0x44,0x24,0x40,0xC1,0xE0,0x03}),
        call(about_title_text,0x11665C,0x10E5A0,3),
        inline_hook(about_version_width,0x124887,{0x8D,0x04,0xCD,0,0,0,0}),
        inline_hook(about_copyright_width,0x1248E4,{0x8D,0x04,0xCD,0,0,0,0}),
        inline_hook(about_publisher_width,0x124934,{0x8D,0x04,0xCD,0,0,0,0}),
        inline_hook(about_notes_width,0x124A44,{0x8D,0x04,0xCD,0,0,0,0}),
        inline_hook(about_install_width,0x124ACB,{0x8D,0x04,0xCD,0,0,0,0}),
        inline_hook(about_website_width,0x1249A3,{0x8D,0x04,0xCD,0,0,0,0}),
        inline_hook(about_path_width,0x124B19,{0x8D,0x04,0xCD,0,0,0,0}),
        call(about_version_text,0x1248A1,0x10E5A0,3),
        call(about_copyright_text,0x1248F9,0x10E5A0,3),
        call(about_publisher_text,0x124949,0x10E5A0,3),
        call(about_notes_text,0x124A59,0x10E5A0,3),
        call(about_install_text,0x124AE0,0x10E5A0,3),
        call(about_website_text,0x1249B8,0x10E5A0,3),
        call(about_path_text,0x124B2E,0x10E5A0,3),
        call(about_button,0x124C3E,0x114680,1),
        inline_hook(about_button_width,0x1146DD,{0x89,0xB5,0x68,0xFF,0xFF,0xFF}),
        call(about_button_character,0x1148E9,0x10D0,3),
        call(about_button_text,0x114956,0x10E5A0,3),
        inline_hook(about_button_advance,0x11498A,{0x8B,0x95,0x5C,0xFF,0xFF,0xFF,0x43}),
        call(about_wait,0x124C46,0xD3C80,0),
        call(about_input_tick,0xD3D05,0xD3BF0,0),
        call(credits_scope,0x125E6E,0x1244F0,0),
        call(credits_panel,0x124511,0x116270,5),
        call(credits_paragraph,0x124669,0x10EB40,4),
        call(credits_button,0x12467D,0x114680,1),
        call(credits_wait,0x124685,0xD3C80,0),
        call(character_creation_scope,0x125CFB,0xCFFB0,0),
        call(character_creation_panel,0xD01A5,0x115E70,4),
        call(character_creation_button,0xD031F,0x114680,1),
        call(profile_heading_panel,0x12F0D,0x116270,5),
        call(profile_culture_scope,0xF678,0xCFFB0,0),
        call(profile_sex_scope,0xF377,0xCFFB0,0),
        call(profile_name_panel,0x11939,0x116270,5),
        call(profile_name_help,0x118CA,0x162300,0),
        call(profile_name_help_repeat,0x118FA,0x162300,0),
        call(profile_name_footer,0x11904,0xF210,0),
        call(profile_sex_help,0xF313,0x162300,0),
        call(profile_sex_footer,0xF31A,0xF210,0),
        inline_hook(profile_name_too_short,0x11A53,{0x66,0x0F,0xD6,0x85,0x08,0xFC,0xFF,0xFF}),
        inline_hook(profile_name_invalid,0x11B27,{0x66,0x0F,0xD6,0x85,0x28,0xFC,0xFF,0xFF}),
        inline_hook(profile_name_exists,0x11CC7,{0x66,0x0F,0xD6,0x85,0x28,0xFC,0xFF,0xFF}),
        call(scenario_story_scope,0xFB7FD,0xFB390,0),
        call(scenario_panel,0xFB691,0x116270,5),
        call(scenario_body_format,0xFB74D,0x10D0,3),
        call(scenario_body_append,0xFB75D,0x162300,0),
        call(scenario_body_paragraph,0xFB7A3,0x10EB40,4),
        call(scenario_introduction_1,0xFB80C,0x162300,0),
        call(scenario_introduction_2,0xFB818,0x162300,0),
        call(scenario_introduction_3,0xFB824,0x162300,0),
        call(scenario_introduction_4,0xFB830,0x162300,0),
        call(scenario_intro_paragraph,0xFB84B,0x10EB40,4),
        call(scenario_button,0xFB85F,0x114680,1),
        call(setup_panel,0x105752,0x116270,5),
        // Shared physical consumers have one stable hook ID each (301/305).
        // Additional confirmed panels extend scope checks, not hook sites.
        call(shared_title_text,0x115A94,0x10E5A0,3),
        call(setup_controls_append,0x105817,0x162300,0),
        call(setup_config_append,0x105823,0x162300,0),
        call(setup_footer,0x10582A,0xF210,0),
        call(shared_footer_paragraph,0xF2E5,0x10EB40,4),
        call(setup_exit_scope,0x106AFC,0xCFAF0,2),
        call(setup_exit_text,0x1149F9,0x10E5A0,3),
        inline_hook(setup_exit_width,0xCFC5D,{0x8D,0x04,0xCD,0x0A,0,0,0}),
        call(intro_north,0x1255EC,0x10E5A0,3),
        call(intro_roleplaying,0x1256C2,0x10E5A0,3),
        call(intro_version_scope,0x12582F,0x124710,0),
        call(intro_story_scope,0x1258B5,0x125370,0),
        inline_hook(intro_story_width,0x125430,{0x8D,0x04,0xCD,0,0,0,0}),
        call(intro_story_fade_text,0x125285,0x10E5A0,3),
        call(intro_story_settled_text,0x12530E,0x10E5A0,3),
        call(startup_heading,0x180894,0x10E5A0,3),
        call(startup_audio_ogg_scope,0x180B4D,0xB3D0,0),
        call(startup_audio_samples_scope,0x180B59,0xB3D0,0),
        call(startup_intro_scope,0x180B52,0xC1C0,0),
        call(startup_sound_init,0x180905,0x123DF0,0),
        call(startup_device_failed,0x180941,0x123DF0,0),
        call(startup_intro_progress,0xC2B5,0x123DF0,0),
        call(startup_named_audio,0xB0E0,0x123DF0,0),
        call(startup_file_audio,0xB3A6,0x123DF0,0),
        call(startup_named_failed,0xB016,0x123DF0,0),
        call(startup_file_failed,0xB331,0x123DF0,0),
        call(startup_progress_text,0x123E6D,0x10E5A0,3),
        call(menu_scope,0x125BDC,0xCFFB0,0),
        call(menu_input,0x125BE1,0xD1120,0),
        call(footer_initial,0x125AF5,0x1250E0,0),
        call(footer_loop,0x125BA3,0x1250E0,0),
        call(version_scope,0x125BD7,0x124710,0),
        call(window_targets_rebuilt,0xD1E99,0x10ADB0,0),
        call(menu_text,0xD0367,0x10E5A0,3),
        call(version_format,0x12474C,0x10D0,3),
        call(copyright_format,0x125189,0x10D0,3),
        call(production_append,0x125137,0x162300,0),
        call(authors_append,0x1251E4,0x162300,0),
        call(copyright_append,0x12519C,0x162300,0),
        call(footer_logo,0x125125,0x112980,1),
        call(footer_panel,0x12510E,0x116270,5),
        call(version_text,0x1247A7,0x10E5A0,3),
        call(production_paragraph,0x125173,0x10EB40,4),
        call(copyright_paragraph,0x1251D2,0x10EB40,4),
        call(authors_paragraph,0x12521C,0x10EB40,4),
        call(paragraph_text,0x10EF87,0x10E5A0,3),
        call(outline_top,0x10E67C,0x10DDB0,1),
        call(outline_bottom,0x10E68D,0x10DDB0,1),
        call(outline_left,0x10E69E,0x10DDB0,1),
        call(outline_right,0x10E6AF,0x10DDB0,1),
        call(foreground,0x10E6D8,0x10DDB0,1),
        inline_hook(cursor_width,0x10E700,{0x89,0x1D,0,0,0,0,0x8D,0x04,0xC8}),
        inline_hook(version_width,0x124793,{0x8D,0x04,0xCD,0,0,0,0}),
        inline_hook(paragraph_width,0x10EE68,{0x8D,0x0C,0xF0,0x8B,0x45,0x08}),
        inline_hook(paragraph_advance,0x10EF57,{0x8D,0x04,0xD8,0x8B,0x9D,0xF8,0xF3,0xFF,0xFF})
    };
    for(u32 i=0;i<std::size(setup_text_calls);++i)
        hooks.push_back(call(setup_body_first+i,setup_text_calls[i].site,0x10E5A0,3));
    for(u32 i=0;i<std::size(credits_text_calls);++i)
        hooks.push_back(call(credits_append_first+i,credits_text_calls[i].site,0x162300,0));
    // The absolute MOV operand has a HIGHLOW relocation at 10E702.
    // Both verification and resident replay use the loaded image address.
    const u32 cursor_y=address(at<void>(0x61BBB3C));
    for(auto& h:hooks) if(h.id==cursor_width) std::memcpy(h.expected+2,&cursor_y,4);
    append_hud_hooks(hooks);
    append_windows_profile_hooks(hooks);
    append_windows_creation_hooks(hooks);
    append_windows_skills_hooks(hooks);
    append_windows_encyclopedia_hooks(hooks);
    windows_renderer_text::append_hooks(hooks);
    append_windows_message_hooks(hooks);
    native_name_input::append_hooks(hooks);
    native_language_input::append_hooks(host->image_base,hooks);
    native_language_redraw::append_hooks(hooks);
    native_menu_component::append_hooks(hooks);
    native_menu_storage::append_hooks(hooks);
    native_root_component::append_hooks(hooks);
    native_culture_legend::append_hooks(hooks);
    native_image_component::append_hooks(hooks);
    native_ui_cache_owners::append_hooks(hooks);
    native_renderer_component_model::append_hooks(hooks);
    native_component_binding::register_hooks(hooks);
    native_renderer_component_binding::register_hooks(hooks);
    status=host->install_hooks(hooks.data(),static_cast<u32>(hooks.size()));
    if(status!=Status::ok) initialization_failure(L"native text hook installation",status);
    return status;
}
Status UWCN_CALL invoke(u32 operation,const void* input,u32 bytes,void* output,u32* output_bytes) {
    if(operation==kNativeInvalidate) return invalidate();
    if(operation==kModuleDependenciesChanged) {
        if(!input || bytes!=sizeof(u32)) return Status::invalid;
        if(output_bytes) *output_bytes=0;
        // Rebind derived text resources without changing the native UI's
        // language or cache lifecycle. Replacing business code is not a
        // language change and must not clear/reconstruct the current scene.
        return initialize_windows_encyclopedia();
    }
    if(operation!=kNativeDispatch || !input || bytes!=sizeof(NativeEvent) || !output_bytes) return Status::invalid;
    if(!output || *output_bytes<sizeof(DispatchResult)) {
        *output_bytes=sizeof(DispatchResult); return Status::insufficient_buffer;
    }
    *output_bytes=sizeof(DispatchResult);
    return dispatch(*static_cast<const NativeEvent*>(input),*static_cast<DispatchResult*>(output));
}
Status UWCN_CALL save_state(void* output,u32* bytes) {
    if(!bytes) return Status::invalid;
    const auto native=native_targets::save();
    const auto redraw=native_language_redraw::save();
    const auto name=native_name_input::save();
    const auto menu=native_menu_component::save();
    const auto messages=save_windows_message_state();
    const auto ui=save_native_ui_state();
    const u32 language[]={chinese_enabled?1u:0u,intro_chinese?1u:0u,
        native_language_input::save().f10_consumed,redraw.pending,redraw.rebuilding,
        name.active,name.committed};
    const u32 active_bytes=sizeof(u32)+static_cast<u32>(active.size()*sizeof(Active));
    const u32 required=active_bytes+5*sizeof(u32)+sizeof(retired_routes)+
        static_cast<u32>(native.size())+sizeof(language)+static_cast<u32>(menu.size())+
        static_cast<u32>(messages.size())+static_cast<u32>(ui.size());
    if(!output || *bytes<required) { *bytes=required; return Status::insufficient_buffer; }
    const u32 count=static_cast<u32>(active.size());
    std::memcpy(output,&count,sizeof(count));
    if(count) std::memcpy(static_cast<unsigned char*>(output)+sizeof(count),active.data(),count*sizeof(Active));
    auto* suffix=static_cast<unsigned char*>(output)+active_bytes;
    const u32 tag=0x37414448,native_bytes=static_cast<u32>(native.size()),
        menu_bytes=static_cast<u32>(menu.size()),message_bytes=static_cast<u32>(messages.size()),
        ui_bytes=static_cast<u32>(ui.size());
    std::memcpy(suffix,&tag,sizeof(tag)); suffix+=sizeof(tag);
    std::memcpy(suffix,&retired_routes,sizeof(retired_routes)); suffix+=sizeof(retired_routes);
    std::memcpy(suffix,&native_bytes,sizeof(native_bytes)); suffix+=sizeof(native_bytes);
    std::memcpy(suffix,&menu_bytes,sizeof(menu_bytes)); suffix+=sizeof(menu_bytes);
    std::memcpy(suffix,&message_bytes,sizeof(message_bytes)); suffix+=sizeof(message_bytes);
    std::memcpy(suffix,&ui_bytes,sizeof(ui_bytes)); suffix+=sizeof(ui_bytes);
    std::memcpy(suffix,native.data(),native.size());
    std::memcpy(suffix+native.size(),language,sizeof(language));
    std::memcpy(suffix+native.size()+sizeof(language),menu.data(),menu.size());
    std::memcpy(suffix+native.size()+sizeof(language)+menu.size(),messages.data(),messages.size());
    std::memcpy(suffix+native.size()+sizeof(language)+menu.size()+messages.size(),ui.data(),ui.size());
    *bytes=required;
    // Host::prepare_transaction invokes the non-sizing save exactly once on
    // the stopped native thread, before disabling or unloading any module.
    // Retire direct branches here so a real retirement error prevents FreeLibrary.
    std::vector<abi1_retirement::RouteBinding> originals;
    for(u32 i=0;i<retired_routes.count;++i) {
        const auto& route=retired_routes.entries[i];
        originals.push_back({route.id,route.original});
    }
    auto status=abi1_retirement::bind_routes(retired_routes,originals);
    if(status!=Status::ok) return status;
    status=native_targets::remove();
    if(status!=Status::ok) return status;
    status=native_raster::remove_raster_patches();
    if(status!=Status::ok) return status;
    retired_for_publication=true;
    return Status::ok;
}
Status UWCN_CALL restore_state(const void* input,u32 bytes) {
    if(!input || bytes<sizeof(u32)) return Status::invalid;
    u32 count{}; std::memcpy(&count,input,sizeof(count));
    const auto active_bytes=sizeof(u32)+static_cast<std::size_t>(count)*sizeof(Active);
    if(bytes<active_bytes) return Status::invalid;
    active.resize(count);
    if(count) std::memcpy(active.data(),static_cast<const unsigned char*>(input)+sizeof(count),count*sizeof(Active));
    // The first published format contained only Active scopes. It has neither
    // resource constructors nor the neutral UI sources required by this model.
    if(bytes==active_bytes) {
        host->log(L"Active-only state has no native component/cache constructor sources; no in-place migration is implemented.");
        return Status::unavailable;
    }
    const auto prefix=active_bytes+2*sizeof(u32)+sizeof(retired_routes);
    if(bytes<prefix) return Status::invalid;
    const auto* suffix=static_cast<const unsigned char*>(input)+active_bytes;
    u32 tag{},native_bytes{};
    std::memcpy(&tag,suffix,sizeof(tag)); suffix+=sizeof(tag);
    // HDA2 is the published predecessor, with Chinese always enabled. HDA3
    // appends only language/input state; native resource and Active layouts stay.
    // HDA6 was an unpublished translated-string snapshot; it is not the
    // neutral Text graph stored by HDA7 and has no implemented migration.
    if(tag!=0x32414448 && tag!=0x33414448 && tag!=0x34414448 && tag!=0x35414448 && tag!=0x37414448) return Status::invalid;
    std::memcpy(&retired_routes,suffix,sizeof(retired_routes)); suffix+=sizeof(retired_routes);
    std::memcpy(&native_bytes,suffix,sizeof(native_bytes)); suffix+=sizeof(native_bytes);
    u32 menu_bytes{},message_bytes{},ui_bytes{};
    if(tag==0x35414448 || tag==0x37414448) {
        std::memcpy(&menu_bytes,suffix,sizeof(menu_bytes)); suffix+=sizeof(menu_bytes);
    }
    if(tag==0x37414448) {
        std::memcpy(&message_bytes,suffix,sizeof(message_bytes)); suffix+=sizeof(message_bytes);
    }
    if(tag==0x37414448) {std::memcpy(&ui_bytes,suffix,sizeof(ui_bytes));suffix+=sizeof(ui_bytes);}
    const u32 language_bytes=(tag==0x34414448 || tag==0x35414448 || tag==0x37414448) ? 7*sizeof(u32) :
        tag==0x33414448 ? 5*sizeof(u32) : 0;
    const u32 extended_header_bytes=tag==0x37414448 ? 3*sizeof(u32) : tag==0x35414448 ? sizeof(u32) : 0;
    if(bytes!=prefix+extended_header_bytes+native_bytes+language_bytes+menu_bytes+message_bytes+ui_bytes ||
        retired_routes.count>retired_routes.entries.size()) return Status::invalid;
    auto status=native_targets::restore(suffix,native_bytes);
    if(status==Status::unavailable)
        host->log(L"NGT1 state has no native component/cache constructor sources; the current adapter cannot migrate this active UI to the global source model in place.");
    if(status!=Status::ok) return status;
    if(tag==0x33414448 || tag==0x34414448 || tag==0x35414448 || tag==0x37414448) {
        u32 language[7]{};
        std::memcpy(language,suffix+native_bytes,language_bytes);
        chinese_enabled=language[0]!=0;
        intro_chinese=language[1]!=0;
        native_language_input::restore({language[2]});
        if(tag==0x37414448) native_language_redraw::restore({language[3],language[4]});
        if(tag==0x34414448 || tag==0x35414448 || tag==0x37414448) native_name_input::restore({language[5],language[6]});
    }
    if(tag==0x37414448) native_menu_component::restore(suffix+native_bytes+language_bytes);
    if(tag==0x37414448) restore_windows_message_state(suffix+native_bytes+language_bytes+menu_bytes);
    if(tag==0x37414448) restore_native_ui_state(suffix+native_bytes+language_bytes+menu_bytes+message_bytes);
    const auto routes=native_targets::routes();
    status=abi1_retirement::bind_routes(retired_routes,routes);
    if(status!=Status::ok) return status;
    return Status::ok;
}
void UWCN_CALL shutdown() {
    if(!retired_for_publication) {
        std::vector<abi1_retirement::RouteBinding> originals;
        for(u32 i=0;i<retired_routes.count;++i) originals.push_back({retired_routes.entries[i].id,retired_routes.entries[i].original});
        abi1_retirement::bind_routes(retired_routes,originals);
        native_targets::remove();
        native_raster::remove_raster_patches();
    }
    native_ui_cache_owners::shutdown();
    native_ui_scene::shutdown();
    native_message_flow::shutdown();
    native_renderer_component_binding::shutdown();
    native_culture_legend::shutdown();
    native_hud_icons::shutdown();
    native_renderer_component_model::shutdown();
    native_link_flow_component::shutdown();
    native_footer_component::shutdown();
    native_image_component::shutdown();
    native_component_binding::shutdown();
    native_component_model::initialize(0);
    native_root_component::shutdown();
    native_menu_storage::shutdown();
    native_menu_component::shutdown();
    native_targets::forget();
    active.clear(); host=nullptr; get_rgb=nullptr;
}
const ModuleApi api{sizeof(ModuleApi),kHostAbi,ModuleId::adapter,initialize,invoke,save_state,restore_state,shutdown};
}
}

UWCN_EXPORT const uwcn::ModuleDescriptor uwcn_module_descriptor{
    uwcn::kDescriptorMagic,uwcn::kHostAbi,static_cast<uwcn::u32>(uwcn::ModuleId::adapter),0x14C,1};
UWCN_EXPORT const uwcn::ModuleApi* UWCN_CALL uwcn_get_module_api() { return &uwcn::adapter::api; }
