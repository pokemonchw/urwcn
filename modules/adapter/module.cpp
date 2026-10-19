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
bool about_refresh_pending=true;
bool about_redrawing{};
bool credits_refresh_pending=true;
bool credits_redrawing{};
bool character_creation_refresh_pending=true;
bool profile_culture_refresh_pending=true;
bool profile_sex_refresh_pending=true;
bool scenario_refresh_pending=true;
bool scenario_redrawing{};
bool rebuilding_main_background{};

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
    scenario_intro_paragraph, scenario_button, scenario_redraw_entry, scenario_redraw_wait,
    setup_panel=300, shared_title_text, setup_controls_append, setup_config_append,
    setup_footer, shared_footer_paragraph, setup_exit_scope, setup_exit_text, setup_exit_width,
    setup_body_first=0x600, credits_append_first=0x700,
    load_saved_empty_panel=0xA00, load_saved_list_panel, load_saved_empty_text, load_saved_key_text,
    ancestors_title=0x900, ancestors_empty, ancestors_order, ancestors_exit,
    ancestors_played, ancestors_living, ancestors_distance, ancestors_previous, ancestors_next,
    ancestors_select, ancestors_select_prefix, ancestors_select_suffix,
    ancestors_page_format, ancestors_page_text, ancestors_row,
    ancestors_lived_format, ancestors_distance_format, ancestors_lived_text, ancestors_distance_text
};
enum class Scope : u32 {
    menu=1, footer=2, version=3, paragraph=4, text=5, allocation=6, menu_input=7,
    startup_audio=8, startup_intro=9, startup_progress=10, intro_story=11,
    about=12, titled_panel=13, plain_button=14, credits=15,
    setup_panel=30, setup_footer=31, setup_exit=32, intro_version=33,
    character_creation=34, character_creation_panel=35, character_creation_label=36,
    profile_culture=37, profile_sex=38, profile_panel=39, profile_footer=40,
    scenario_story=41, scenario_panel=42, creation_button=43, creation_paragraph=44,
    encyclopedia_input=45,
    load_saved_panel=0xA0,
    ancestors_title=50, ancestors_select=51, ancestors_row=52,
    hud_centered=0x100, hud_penalty=0x101, hud_button=0x102,
    hud_title=0x103, hud_renderer=0x104, hud_renderer_text=0x105, hud_scale=0x106
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
struct AncestorNumbers { std::int32_t age,days,kilometers; };

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
Status translate(TextComponent component,const char* original,const char* value,std::vector<char>& encoded) {
    // Keep encoding, font metrics and native targets active in both languages.
    // Intro fades overwrite existing pixels; one native sequence uses one mode.
    const bool intro=component==TextComponent::intro_north || component==TextComponent::intro_roleplaying
        || (component>=TextComponent::intro_story_0 && component<=TextComponent::intro_story_10)
        || (component==TextComponent::version && in(Scope::intro_version));
    if(!(intro ? intro_chinese : chinese_enabled))
        return codec(layout_op::encode_native,original,encoded);
    TextRequest request{component,original,value};
    std::vector<char> utf8;
    auto result=service_text(ModuleId::main_menu,text_op::translate,&request,sizeof(request),utf8);
    if(result!=Status::ok) return result;
    return codec(layout_op::encode_native,utf8.data(),encoded);
}

// 10E5A0/10DDB0 consume the current native surface. Its real physical size and
// the confirmed 800x600 logical domain define the complete-string raster scale.
render::TextRequest render_request(const char* utf8,std::int32_t x,std::int32_t y,u32 pixel) {
    void* surface=*at<void*>(0x61BBB10);
    auto format=*reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(surface)+4);
    unsigned char r{},g{},b{};
    get_rgb(pixel,format,&r,&g,&b);
    return {utf8,surface,*at<void*>(0xA2110CC),x,y,
        static_cast<u32>(r)|(static_cast<u32>(g)<<8)|(static_cast<u32>(b)<<16)|0xFF000000u,
        10,9,0,0,outline_budget(),800,600};
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
    active.push_back({e.token,Scope::text,0,x,1,x+measured.logical_width/2,e.arguments[2]});
    return Status::ok;
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
    std::vector<char> encoded;
    const auto status=translate(component,display,nullptr,encoded);
    if(status!=Status::ok) return status;
    encoded.insert(encoded.begin(),original,suffix);
    return lend_text(e,encoded,e.arguments[0],Scope::character_creation_label);
}

Status profile_name_error(const NativeEvent& e,DispatchResult& result,TextComponent component,u32 source_rva) {
    std::vector<char> encoded;
    const auto status=translate(component,at<char>(source_rva),nullptr,encoded);
    if(status!=Status::ok) return status;
    // Each site is the final MOVQ of one confirmed error-literal copy. Replace
    // that display-only local (0x400 bytes); validation and the input stay native.
    std::memcpy(ptr<void>(e.frame->ebp-0x408),encoded.data(),encoded.size());
    result.skip_original=1;
    return Status::ok;
}

Status scenario_body_record(const NativeEvent& e) {
    const auto* original=ptr<char>(e.arguments[2]);
    // RNDCAMP.1 has thirteen nonempty body records and one empty separator.
    // FB712's terminal EOF read also leaves an empty record. Keep both native
    // empty sprintf/append calls, including their original whitespace.
    if(!*original) return Status::ok;
    const auto story=std::find_if(active.rbegin(),active.rend(),
        [](const Active& scope){return scope.kind==Scope::scenario_story;});
    auto& record=*ptr<u32>(story->allocation);
    const auto component=static_cast<TextComponent>(
        static_cast<u32>(TextComponent::scenario_village_departure_1)+record++);
    std::vector<char> encoded;
    const auto status=translate(component,original,nullptr,encoded);
    if(status!=Status::ok) return status;
    // This is an input-file record ordinal, not a rendered line. The original
    // sprintf keeps its <br>/space format, then 162300 tokenizes the result.
    // The thirteen fixed translations fit the native 0x400-byte destination.
    return lend_text(e,encoded,e.arguments[2],Scope::allocation);
}

Status capture_footer_edge(const NativeEvent& e) {
    // 12510E supplies the live footer panel x and width. Its outer footer
    // scope owns this one boundary value only until native construction ends.
    const auto footer=std::find_if(active.rbegin(),active.rend(),
        [](const Active& scope){return scope.kind==Scope::footer;});
    auto* edge=static_cast<std::int32_t*>(host->allocate(sizeof(std::int32_t)));
    if(!edge) return Status::failed;
    *edge=static_cast<std::int32_t>(e.frame->ecx+e.arguments[0]);
    footer->allocation=address(edge);
    return Status::ok;
}

Status footer_branding(const NativeEvent& e) {
    if(!chinese_enabled) return Status::ok;
    // 125125 is this footer's original image call, before 125137 resets the
    // production paragraph. The sibling uses the live panel edge and logo y;
    // no screen positions or text rows are retained across this invocation.
    begin(e,Scope::paragraph,1);
    std::vector<char> credit,version;
    auto status=translate(TextComponent::translation_credit,"",nullptr,credit);
    if(status!=Status::ok) return status;
    status=translate(TextComponent::translation_version,"",nullptr,version);
    if(status!=Status::ok) return status;
    render::Metrics credit_size{},version_size{};
    status=metrics(credit.data(),credit_size);
    if(status!=Status::ok) return status;
    status=metrics(version.data(),version_size);
    if(status!=Status::ok) return status;
    const auto width=std::max(credit_size.logical_width,version_size.logical_width);
    // The native footer uses a five-unit gap from hirvilogo.png to its label.
    // Apply that same spacing to the explicitly requested adjacent component.
    constexpr std::int32_t gap=5;
    const auto footer=std::find_if(active.rbegin(),active.rend(),
        [](const Active& scope){return scope.kind==Scope::footer;});
    const auto label_x=*ptr<std::int32_t>(footer->allocation)-gap-width;
    const auto logo_y=static_cast<std::int32_t>(e.arguments[0]);
    const render::SpriteRequest sprite{*at<void*>(0x61BBB10),
        label_x+(width-byayoi_sprite::width)/2,logo_y,800,600};
    status=host->invoke(ModuleId::render,render::op::sprite,&sprite,sizeof(sprite),nullptr,nullptr);
    if(status!=Status::ok) return status;

    const std::string paragraph=std::string(credit.data())+"<br>"+version.data();
    status=paragraph_capacity(paragraph.c_str());
    if(status!=Status::ok) return status;
    using Parse = void (__fastcall *)(u32,const char*);
    reinterpret_cast<Parse>(host->image_base+0x162300)(1,paragraph.c_str());
    using MapRGB = u32 (UWCN_CALL *)(const void*,unsigned char,unsigned char,unsigned char);
    const auto* surface=*at<render::Surface*>(0x61BBB10);
    const auto color=(*at<MapRGB>(0x18C1F8))(surface->format,176,196,222);
    const NativeParagraphCall call{address(at<void>(0x10EB40)),label_x,logo_y+byayoi_sprite::height+gap,
        width,byayoi_sprite::height,color,1};
    // The original tokenizer, wrap comparisons, <br> advancement, cursor and
    // word drawing run synchronously. Existing native width/glyph hooks apply.
    uwcn_draw_native_paragraph(&call);
    return Status::ok;
}

Status redraw_menu();
Status redraw_credits() {
    auto status=native_targets::promote();
    if(status!=Status::ok) return status;
    using Native = void (UWCN_CALL *)();
    // 125E4D..125E73 saves/restores the same native menu background as About.
    reinterpret_cast<Native>(host->image_base+0x10DA60)();
    status=redraw_menu();
    if(status!=Status::ok) return status;
    reinterpret_cast<Native>(host->image_base+0x10DA10)();
    credits_redrawing=true;
    // Complete prologue and epilogue; skip only 124685's input wait.
    reinterpret_cast<Native>(host->image_base+0x1244F0)();
    credits_redrawing=false;
    credits_refresh_pending=false;
    reinterpret_cast<Native>(host->image_base+0x10B720)();
    return Status::ok;
}
Status redraw_about() {
    auto status=native_targets::promote();
    if(status!=Status::ok) return status;
    // Run the complete native function so its prologue/epilogue stay balanced.
    // Only its input wait is skipped during this synchronous redraw.
    using Native = void (UWCN_CALL *)();
    // The original About caller saves the menu in A1C2014. Restore and replace
    // that native background so both the visible menu and its later restore
    // use the new language. 10DA60/10DA10 own the copy and presentation.
    reinterpret_cast<Native>(host->image_base+0x10DA60)();
    status=redraw_menu();
    if(status!=Status::ok) return status;
    reinterpret_cast<Native>(host->image_base+0x10DA10)();
    about_redrawing=true;
    reinterpret_cast<Native>(host->image_base+0x1247C0)();
    about_redrawing=false;
    about_refresh_pending=false;
    reinterpret_cast<Native>(host->image_base+0x10B720)();
    return Status::ok;
}
Status refresh_menu_cache() {
    using Blit = int (UWCN_CALL *)(void*,const void*,void*,void*);
    // Repeat the exact D1189 logical rectangle through the native coordinate
    // extension; the game-owned working surface receives actual drawn pixels.
    auto blit=*at<Blit>(0x18C204);
    auto rect=*at<render::Rect>(0x1DDAB0);
    if(blit(*at<void*>(0x61BBB10),&rect,*at<void*>(0xA1C1CE0),&rect)!=0) return Status::failed;
    using Selection = void (__fastcall *)(std::int32_t,std::int32_t);
    reinterpret_cast<Selection>(host->image_base+0xD0650)(*at<std::int32_t>(0x5F54AB0),0);
    using Present = void (UWCN_CALL *)();
    reinterpret_cast<Present>(host->image_base+0x10B720)();
    return Status::ok;
}
Status redraw_menu() {
    auto status=native_targets::promote();
    if(status!=Status::ok) return status;
    // The native background draw also retires its own cached slave textures.
    // Suppress only startup business assignments while replaying that balanced
    // original drawing fragment, then rebuild footer, panel and menu pixels.
    rebuilding_main_background=true;
    status=host->native_fragment(0x125AA6,0x125AF5);
    rebuilding_main_background=false;
    if(status!=Status::ok) return status;
    // This balanced fragment performs the native footer, panel, version and
    // row drawing. Its end precedes D1120, so no input wait is re-entered.
    status=host->native_fragment(0x125BA3,0x125BE1);
    if(status!=Status::ok) return status;
    return refresh_menu_cache();
}
Status redraw_character_creation() {
    auto status=native_targets::promote();
    if(status!=Status::ok) return status;
    // One complete CFFB0 call rebuilds this native panel from its unchanged
    // English rows. No CF790 initialization, input wait or creation action.
    status=host->native_fragment(0x125CFB,0x125D00);
    if(status!=Status::ok) return status;
    return refresh_menu_cache();
}
Status redraw_profile_menu(u32 draw_call) {
    auto status=native_targets::promote();
    if(status!=Status::ok) return status;
    // F678/F377 are complete CFFB0 calls using the current native menu table.
    // Stop before selection business or input; retain the existing selection.
    status=host->native_fragment(draw_call,draw_call+5);
    if(status!=Status::ok) return status;
    return refresh_menu_cache();
}
Status redraw_scenario() {
    auto status=native_targets::promote();
    if(status!=Status::ok) return status;
    using Native = void (UWCN_CALL *)();
    scenario_redrawing=true;
    // Run the balanced native frame. FB7D1 skips only first-entry scenario
    // business; D3CDC returns through the normal epilogue before input drain.
    reinterpret_cast<Native>(host->image_base+0xFB7D0)();
    scenario_redrawing=false;
    scenario_refresh_pending=false;
    return Status::ok;
}
void invalidate_windows_creation();
void invalidate_windows_profile();
void invalidate_windows_encyclopedia();
Status invalidate() {
    invalidate_windows_creation();
    invalidate_windows_profile();
    invalidate_windows_encyclopedia();
    native_language_redraw::request_ancestors();
    about_refresh_pending=true;
    credits_refresh_pending=true;
    character_creation_refresh_pending=true;
    profile_culture_refresh_pending=true;
    profile_sex_refresh_pending=true;
    scenario_refresh_pending=true;
    if(in(Scope::about)) return redraw_about();
    if(in(Scope::credits)) return redraw_credits();
    if(in(Scope::menu_input)) return redraw_menu();
    return Status::ok;
}

Status dispatch_hud(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_windows_profile(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_windows_creation(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_windows_skills(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_windows_encyclopedia(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_windows_renderer(const NativeEvent&,DispatchResult&,bool&);
Status dispatch_windows_menu_background(const NativeEvent&,DispatchResult&,bool&);
Status windows_creation_input(const NativeEvent&);
bool windows_profile_input(const NativeEvent&);
Status dispatch(const NativeEvent& e,DispatchResult& result) {
    result={};
    bool handled{};
    auto extension=native_name_input::dispatch(e,result,handled);
    if(handled) { if(e.phase==NativePhase::after) end(e.token);return extension; }
    for(auto dispatch_extension:{dispatch_windows_profile,dispatch_windows_creation,
            dispatch_windows_skills,dispatch_windows_encyclopedia,dispatch_windows_renderer,
            dispatch_windows_menu_background}) {
        extension=dispatch_extension(e,result,handled);
        if(handled) { if(e.phase==NativePhase::after) end(e.token);return extension; }
    }
    const auto language_input=native_language_input::dispatch(e,result,host->image_base);
    if(language_input.handled) {
        if(!language_input.toggle) return Status::ok;
        chinese_enabled=!chinese_enabled;
        native_language_redraw::request();
        return invalidate();
    }
    if(character_creation_refresh_pending && native_language_redraw::menu_input(e,0x125D05))
        return redraw_character_creation();
    if(profile_culture_refresh_pending && native_language_redraw::menu_input(e,0xF8D4))
        return redraw_profile_menu(0xF678);
    if(profile_sex_refresh_pending && native_language_redraw::menu_input(e,0xF43A))
        return redraw_profile_menu(0xF377);
    if(windows_profile_input(e)) return redraw_profile_menu(0xFB36);
    extension=windows_creation_input(e);
    if(extension!=Status::ok) return extension;
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
    case scenario_story_scope:
        scenario_refresh_pending=false;
        // 10B94 stores the selected RNDCAMP index plus 100; FB7F2 removes
        // that creation marker before this display call. RNDCAMP.1 is Village.
        if(*at<u32>(0xA32B0C8)==1) {
            auto* record=static_cast<u32*>(host->allocate(sizeof(u32)));
            *record=0;
            active.push_back({e.token,Scope::scenario_story,address(record),0,0,0,0});
        }
        break;
    case scenario_panel:
        if(in(Scope::scenario_story)) {
            std::vector<char> encoded;
            const auto status=translate(TextComponent::scenario_village_title,
                ptr<char>(e.arguments[2]),nullptr,encoded);
            if(status!=Status::ok) return status;
            // FB691's flags 0x30 use the existing left-aligned native title.
            return lend_text(e,encoded,e.arguments[2],Scope::scenario_panel);
        }
        break;
    case scenario_body_format:
        if(in(Scope::scenario_story)) return scenario_body_record(e);
        break;
    case scenario_body_paragraph:
        if(in(Scope::scenario_story)) begin(e,Scope::paragraph,e.arguments[3]);
        break;
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
    case scenario_redraw_entry:
        if(scenario_redrawing) result.resume_rva=0xFB7FD;
        break;
    case scenario_redraw_wait:
        if(scenario_redrawing) result.resume_rva=0xD3D0F;
        break;
    case profile_culture_scope:
        profile_culture_refresh_pending=false;
        begin(e,Scope::profile_culture); break;
    case profile_sex_scope:
        profile_sex_refresh_pending=false;
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
        character_creation_refresh_pending=false;
        begin(e,Scope::character_creation); break;
    case character_creation_panel:
        if(in(Scope::character_creation) || in(Scope::profile_culture) || in(Scope::profile_sex)) {
            const auto component=in(Scope::profile_culture) ? TextComponent::profile_culture_title :
                in(Scope::profile_sex) ? TextComponent::profile_sex_title : TextComponent::character_creation_title;
            std::vector<char> encoded;
            const auto status=translate(component,ptr<char>(e.arguments[2]),nullptr,encoded);
            if(status!=Status::ok) return status;
            // D01A5 -> 115E70(flags 4) -> 1157B0(mode 2): native left alignment.
            return lend_text(e,encoded,e.arguments[2],Scope::character_creation_panel);
        }
        break;
    case character_creation_button:
        if(in(Scope::profile_culture)) {
            const auto action=*ptr<u32>(e.frame->esi+0xC8);
            if(action>='0' && action<='9')
                return character_creation_label(e,static_cast<TextComponent>(
                    static_cast<u32>(TextComponent::profile_culture_0)+action-'0'));
            switch(action) {
            case 'R': return character_creation_label(e,TextComponent::profile_random);
            case '?': return character_creation_label(e,TextComponent::profile_cultures);
            case 27: return character_creation_label(e,TextComponent::profile_back);
            }
        }
        if(in(Scope::profile_sex)) {
            switch(*ptr<u32>(e.frame->esi+0xC8)) {
            case 'M': return character_creation_label(e,TextComponent::profile_male);
            case 'F': return character_creation_label(e,TextComponent::profile_female);
            case 27: return character_creation_label(e,TextComponent::profile_back);
            }
        }
        if(in(Scope::character_creation)) {
            // The action field belongs to the unchanged English native row.
            switch(*ptr<u32>(e.frame->esi+0xC8)) {
            case 'Q': return character_creation_label(e,TextComponent::character_creation_quick);
            case 'C': return character_creation_label(e,TextComponent::character_creation_custom);
            case 'E': return character_creation_label(e,TextComponent::character_creation_easy);
            case 'T': return character_creation_label(e,TextComponent::character_creation_too_easy);
            case 27: return character_creation_label(e,TextComponent::character_creation_exit);
            }
        }
        break;
    case load_saved_empty_panel: case load_saved_list_panel:
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
        void* numbers=host->allocate(sizeof(AncestorNumbers));
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
            const bool lived=e.id==ancestors_lived_text;
            const auto value=lived ? std::to_string(numbers.age)+" 岁，度过了 "+
                std::to_string(numbers.days)+" 天冒险生涯" : std::to_string(numbers.kilometers);
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
        about_refresh_pending=false;
        begin(e,Scope::about); break;
    case credits_scope:
        credits_refresh_pending=false;
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
    case about_wait:
        if(about_redrawing) result.skip_original=1;
        break;
    case credits_wait:
        if(credits_redrawing) result.skip_original=1;
        break;
    case about_input_tick:
        // D3C80 owns this EBP frame. Exact original returns identify windows
        // opened before their scope hooks existed. The shared hook ID stays.
        if(about_refresh_pending && *ptr<u32>(e.frame->ebp+4)==host->image_base+0x124C4B)
            return redraw_about();
        if(credits_refresh_pending && *ptr<u32>(e.frame->ebp+4)==host->image_base+0x12468A)
            return redraw_credits();
        // FB868 tail-jumps into D3C80; its original caller return is 17E86A.
        // Keep 17E865 unhooked so this also identifies already-open pages.
        if(scenario_refresh_pending && *ptr<u32>(e.frame->ebp+4)==host->image_base+0x17E86A)
            return redraw_scenario();
        break;
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
        if(in(Scope::setup_panel) || in(Scope::ancestors_title) || in(Scope::character_creation_panel)
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
    case intro_story_scope: begin(e,Scope::intro_story); break;
    case intro_story_width:
        if(in(Scope::intro_story)) {
            // 125400..12542F copied the English table's EDI-indexed line to
            // this native display buffer and pushed its address. Replace only
            // that copy; the supplied catalog's longest encoded line is 47
            // bytes including NUL, within [EBP-70, EBP-4)'s 0x6C bytes.
            auto* display=ptr<char>(e.frame->ebp-0x70);
            const auto component=static_cast<TextComponent>(static_cast<u32>(TextComponent::intro_story_0)+e.frame->edi);
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
        if(in(Scope::intro_story)) begin(e,Scope::text,e.arguments[2]);
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
        if(in(Scope::footer)) return capture_footer_edge(e);
        break;
    case footer_logo:
        if(in(Scope::footer)) return footer_branding(e);
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
        if(in(Scope::footer)) return paragraph_capacity(ptr<char>(e.frame->edx));
        break;
    case menu_text:
        if(in(Scope::menu)) {
            if(e.frame->ebx>7) return Status::invalid;
            std::vector<char> encoded;
            auto status=translate(static_cast<TextComponent>(e.frame->ebx),ptr<char>(e.arguments[0]),nullptr,encoded);
            if(status!=Status::ok) return status;
            if(encoded.size()>0x12C) return Status::insufficient_buffer;
            return lend_text(e,encoded,e.arguments[0],Scope::text);
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
#include "windows_renderer_text.inc"
#include "windows_menu_redraw.inc"
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
        call(scenario_body_paragraph,0xFB7A3,0x10EB40,4),
        call(scenario_introduction_1,0xFB80C,0x162300,0),
        call(scenario_introduction_2,0xFB818,0x162300,0),
        call(scenario_introduction_3,0xFB824,0x162300,0),
        call(scenario_introduction_4,0xFB830,0x162300,0),
        call(scenario_intro_paragraph,0xFB84B,0x10EB40,4),
        call(scenario_button,0xFB85F,0x114680,1),
        inline_hook(scenario_redraw_entry,0xFB7D1,{0x8B,0x35,0,0,0,0}),
        inline_hook(scenario_redraw_wait,0xD3CDC,{0x8B,0x35,0,0,0,0}),
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
    // Both MOV ESI,[absolute] operands have native HIGHLOW relocations.
    const u32 scenario_index=address(at<void>(0xA32B0C8));
    const u32 poll_event_import=address(at<void>(0x18C24C));
    for(auto& h:hooks) {
        if(h.id==scenario_redraw_entry) std::memcpy(h.expected+2,&scenario_index,4);
        if(h.id==scenario_redraw_wait) std::memcpy(h.expected+2,&poll_event_import,4);
    }
    append_hud_hooks(hooks);
    append_windows_profile_hooks(hooks);
    append_windows_creation_hooks(hooks);
    append_windows_skills_hooks(hooks);
    append_windows_encyclopedia_hooks(hooks);
    windows_renderer_text::append_hooks(hooks);
    native_name_input::append_hooks(hooks);
    append_windows_menu_background_hooks(hooks);
    native_language_input::append_hooks(host->image_base,hooks);
    native_language_redraw::append_hooks(hooks);
    status=host->install_hooks(hooks.data(),static_cast<u32>(hooks.size()));
    if(status!=Status::ok) initialization_failure(L"native text hook installation",status);
    return status;
}
Status UWCN_CALL invoke(u32 operation,const void* input,u32 bytes,void* output,u32* output_bytes) {
    if(operation==kNativeInvalidate) return invalidate();
    if(operation==kModuleDependenciesChanged) {
        if(!input || bytes!=sizeof(u32)) return Status::invalid;
        if(output_bytes) *output_bytes=0;
        const auto status=initialize_windows_encyclopedia();
        if(status!=Status::ok) return status;
        return invalidate();
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
    const u32 language[]={chinese_enabled?1u:0u,intro_chinese?1u:0u,
        native_language_input::save().f10_consumed,redraw.pending,redraw.rebuilding,
        name.active,name.committed};
    const u32 active_bytes=sizeof(u32)+static_cast<u32>(active.size()*sizeof(Active));
    const u32 required=active_bytes+2*sizeof(u32)+sizeof(retired_routes)+static_cast<u32>(native.size())+sizeof(language);
    if(!output || *bytes<required) { *bytes=required; return Status::insufficient_buffer; }
    const u32 count=static_cast<u32>(active.size());
    std::memcpy(output,&count,sizeof(count));
    if(count) std::memcpy(static_cast<unsigned char*>(output)+sizeof(count),active.data(),count*sizeof(Active));
    auto* suffix=static_cast<unsigned char*>(output)+active_bytes;
    const u32 tag=0x34414448,native_bytes=static_cast<u32>(native.size());
    std::memcpy(suffix,&tag,sizeof(tag)); suffix+=sizeof(tag);
    std::memcpy(suffix,&retired_routes,sizeof(retired_routes)); suffix+=sizeof(retired_routes);
    std::memcpy(suffix,&native_bytes,sizeof(native_bytes)); suffix+=sizeof(native_bytes);
    std::memcpy(suffix,native.data(),native.size());
    std::memcpy(suffix+native.size(),language,sizeof(language));
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
    // The published predecessor contains exactly this Active array. New native
    // resource identities are appended under an explicit format tag.
    if(bytes==active_bytes) return Status::ok;
    const auto prefix=active_bytes+2*sizeof(u32)+sizeof(retired_routes);
    if(bytes<prefix) return Status::invalid;
    const auto* suffix=static_cast<const unsigned char*>(input)+active_bytes;
    u32 tag{},native_bytes{};
    std::memcpy(&tag,suffix,sizeof(tag)); suffix+=sizeof(tag);
    // HDA2 is the published predecessor, with Chinese always enabled. HDA3
    // appends only language/input state; native resource and Active layouts stay.
    if(tag!=0x32414448 && tag!=0x33414448 && tag!=0x34414448) return Status::invalid;
    std::memcpy(&retired_routes,suffix,sizeof(retired_routes)); suffix+=sizeof(retired_routes);
    std::memcpy(&native_bytes,suffix,sizeof(native_bytes)); suffix+=sizeof(native_bytes);
    const u32 language_bytes=tag==0x34414448 ? 7*sizeof(u32) : tag==0x33414448 ? 5*sizeof(u32) : 0;
    if(bytes!=prefix+native_bytes+language_bytes || retired_routes.count>retired_routes.entries.size()) return Status::invalid;
    auto status=native_targets::restore(suffix,native_bytes);
    if(status!=Status::ok) return status;
    if(tag==0x33414448 || tag==0x34414448) {
        u32 language[7]{};
        std::memcpy(language,suffix+native_bytes,language_bytes);
        chinese_enabled=language[0]!=0;
        intro_chinese=language[1]!=0;
        native_language_input::restore({language[2]});
        native_language_redraw::restore({language[3],language[4]});
        if(tag==0x34414448) native_name_input::restore({language[5],language[6]});
    }
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
    native_targets::forget();
    active.clear(); host=nullptr; get_rgb=nullptr;
}
const ModuleApi api{sizeof(ModuleApi),kHostAbi,ModuleId::adapter,initialize,invoke,save_state,restore_state,shutdown};
}
}

UWCN_EXPORT const uwcn::ModuleDescriptor uwcn_module_descriptor{
    uwcn::kDescriptorMagic,uwcn::kHostAbi,static_cast<uwcn::u32>(uwcn::ModuleId::adapter),0x14C,1};
UWCN_EXPORT const uwcn::ModuleApi* UWCN_CALL uwcn_get_module_api() { return &uwcn::adapter::api; }
