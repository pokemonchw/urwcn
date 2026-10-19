#include "hooks.h"
#include "native_targets.h"
#include "sdk/host_abi.h"
#include "sdk/text_services.h"
#include "sdk/service_helpers.h"
#include "sdk/utf8.h"
#include "modules/render/render_api.h"
#include "modules/render/sdl_api.h"
#include <dlfcn.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <array>
#include <cstdio>
#include <cstring>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

extern "C" void uwcn_linux_redraw_main_fragment(std::uintptr_t);
extern "C" void uwcn_linux_redraw_main_return();
namespace {
using namespace uwcn;
using linux_host::Frame;
using linux_host::Phase;
using linux_host::CallState;
const HostApi* host;
const linux_host::Hooks* hooks;
bool chinese=true;
enum class Scope { none,main_menu,creation,culture,sex,season,load_saved,ancestors,setup,encyclopedia,attributes,encyclopedia_keyword,encyclopedia_intro,encyclopedia_notice };
Scope scope=Scope::none;
bool intro_active;
bool intro_chinese;
u32 active_view;
bool redrawing_view;
bool redrawing_main_background;
bool font_redraw_pending;
void redraw_language();
struct Glyph { std::string utf8; int width=-1; };
std::map<unsigned,Glyph> glyphs;
template<class T> T* at(u32 rva) { return reinterpret_cast<T*>(host->image_base+rva); }
template<class T> T native(u32 rva) { return reinterpret_cast<T>(host->image_base+rva); }
void require(Status status) {
    if(status!=Status::ok) throw std::runtime_error("Linux native text service failed: "+std::to_string(static_cast<u32>(status)));
}
std::string encode(const std::string& utf8) {
    std::string encoded;
    const CodecRequest request{utf8.c_str()};
    require(invoke_text(host,ModuleId::layout,layout_op::encode_native,&request,sizeof(request),encoded));
    std::vector<u32> scalars;
    decode_utf8(utf8.data(),utf8.size(),scalars);
    std::size_t index=0;
    for(auto scalar:scalars) {
        if(scalar<0x80) { ++index; continue; }
        const auto token=(static_cast<unsigned char>(encoded[index])<<8)|static_cast<unsigned char>(encoded[index+1]);
        auto& glyph=glyphs[token];
        if(glyph.utf8.empty()) append_utf8(glyph.utf8,scalar);
        index+=2;
    }
    return encoded;
}
std::string translated(TextComponent component,const char* original,const char* value=nullptr) {
    std::string native_display,native_value;
    if(component>=TextComponent::hud_label && component<=TextComponent::world_time) {
        for(auto* p=reinterpret_cast<const unsigned char*>(original);*p;++p) append_utf8(native_display,*p);
        original=native_display.c_str();
        if(value) {
            for(auto* p=reinterpret_cast<const unsigned char*>(value);*p;++p) append_utf8(native_value,*p);
            value=native_value.c_str();
        }
    }
    std::string result;
    const TextRequest request{component,original,value};
    require(invoke_text(host,ModuleId::semantic,text_op::translate,&request,sizeof(request),result));
    return encode(result);
}
Glyph* token(const unsigned char* text) {
    if(*text<0x80 || !text[1]) return nullptr;
    const auto found=glyphs.find((unsigned(*text)<<8)|text[1]);
    return found==glyphs.end() ? nullptr : &found->second;
}
#include "native_utf8.inc"
render::TextRequest glyph_request(Glyph& glyph,int x,int y,u32 color) {
    render::TextRequest request{};
    request.utf8=glyph.utf8.c_str();
    request.surface=*at<render::Surface*>(0xa916ea0); // screen, native owner
    request.x=x; request.y=y; request.color=color;
    request.native_line_height=10; request.ink_height=9;
    request.logical_width=*at<int>(0x26dc68);
    request.logical_height=*at<int>(0x26dc64);
    return request;
}
int glyph_width(Glyph& glyph) {
    if(glyph.width<0) {
        auto request=glyph_request(glyph,0,0,0xffffffff);
        render::Metrics result{};
        u32 bytes=sizeof(result);
        require(host->invoke(ModuleId::render,render::op::measure,&request,sizeof(request),&result,&bytes));
        glyph.width=result.logical_width;
    }
    return glyph.width;
}
int width(const char* text) {
    linux_host::BusinessCall lease(*hooks);
    const auto display=native_display(text);
    int result=0;
    for(auto* cursor=reinterpret_cast<const unsigned char*>(display.c_str()); *cursor; ) {
        if(auto* glyph=token(cursor)) { result+=glyph_width(*glyph); cursor+=2; }
        else { result+=8; ++cursor; }
    }
    return result;
}
u32 color_rgba() {
    using GetRGBA=void (*)(u32,const render::PixelFormat*,unsigned char*,unsigned char*,unsigned char*,unsigned char*);
    const auto get=reinterpret_cast<GetRGBA>(dlsym(RTLD_DEFAULT,"SDL_GetRGBA"));
    render::Color color{};
    get(*at<u32>(0xa916104),(*at<render::Surface*>(0xa916ea0))->format,&color.r,&color.g,&color.b,&color.a);
    return color.r|(u32(color.g)<<8)|(u32(color.b)<<16)|0xff000000u;
}
void textput(int x,int y,const char* text) {
    linux_host::BusinessCall lease(*hooks);
    const auto display=native_display(text);
    const auto putasc=native<void (*)(int,int,unsigned char)>(0x13b6c0);
    const auto color=color_rgba();
    for(auto* cursor=reinterpret_cast<const unsigned char*>(display.c_str()); *cursor && *cursor!='\n';) {
        if(auto* glyph=token(cursor)) {
            auto request=glyph_request(*glyph,x,y,color);
            render::Metrics result{}; u32 bytes=sizeof(result);
            require(host->invoke(ModuleId::render,render::op::draw,&request,sizeof(request),&result,&bytes));
            x+=result.logical_width; cursor+=2;
        } else { putasc(x,y,*cursor++); x+=8; }
    }
}
void rentextput(render::Renderer* renderer,int x,int y,const char* text,render::Color color,unsigned flags) {
    linux_host::BusinessCall lease(*hooks);
    const auto display=native_display(text);
    const auto renderasc=native<void (*)(render::Renderer*,int,int,unsigned char,int,int,int,unsigned)>(0x13d700);
    for(auto* cursor=reinterpret_cast<const unsigned char*>(display.c_str()); *cursor && *cursor!='\n';) {
        if(auto* glyph=token(cursor)) {
            auto request=glyph_request(*glyph,x,y,color.r|(u32(color.g)<<8)|(u32(color.b)<<16)|0xff000000u);
            request.renderer=renderer;
            render::Metrics result{}; u32 bytes=sizeof(result);
            require(host->invoke(ModuleId::render,render::op::draw_renderer,&request,sizeof(request),&result,&bytes));
            x+=result.logical_width; cursor+=2;
        } else { renderasc(renderer,x,y,*cursor++,color.r,color.g,color.b,flags); x+=8; }
    }
}
using Native6=std::uintptr_t (*)(std::uintptr_t,std::uintptr_t,std::uintptr_t,std::uintptr_t,std::uintptr_t,std::uintptr_t);
using Native7=std::uintptr_t (*)(std::uintptr_t,std::uintptr_t,std::uintptr_t,std::uintptr_t,std::uintptr_t,std::uintptr_t,std::uintptr_t);
std::uintptr_t call(Frame& frame,u32 target) {
    return native<Native6>(target)(frame.rdi,frame.rsi,frame.rdx,frame.rcx,frame.r8,frame.r9);
}
std::uintptr_t call(Frame& registers,u32 target,unsigned arguments,const Frame& native_frame) {
    // Stack arguments follow the gateway frame, not a translated register copy.
    if(arguments==7) return native<Native7>(target)(registers.rdi,registers.rsi,registers.rdx,registers.rcx,registers.r8,registers.r9,*reinterpret_cast<const std::uintptr_t*>(native_frame.stack()));
    return call(registers,target);
}
std::uint64_t& argument(Frame& frame,unsigned index) {
    switch(index) {
    case 0:return frame.rdi; case 1:return frame.rsi; case 2:return frame.rdx;
    case 3:return frame.rcx; case 4:return frame.r8; default:return frame.r9;
    }
}
#include "name_input.inc"
enum class Value { literal,option,version,about_version,copyright,footer_copyright,key_suffix,page,place };
struct Binding { u32 site,target; TextComponent component; unsigned argument; Value value=Value::literal; unsigned arguments=6; };
using C=TextComponent;
const Binding bindings[]{
    {0xa4b4,0x13e8b0,C::startup_loading,2},
    {0x12e257,0x1471a0,C::setup_title,4,Value::literal,7},
    {0x12e2a4,0x1afe00,C::setup_controls_help,1},
    {0x12e2b2,0x1afe00,C::setup_config_help,1},
    {0x12e3f7,0x13e8b0,C::setup_fullscreen,2,Value::option},
    {0x12e45c,0x13e8b0,C::setup_logical_resize,2,Value::option},
    {0x12e4aa,0x13e8b0,C::setup_logical_resize_help,2},
    {0x12e4dc,0x13e8b0,C::setup_video_restart_help,2},
    {0x12e520,0x13e8b0,C::setup_audio,2,Value::option},
    {0x12e5b0,0x13e8b0,C::setup_volume,2,Value::option},
    {0x12e63b,0x13e8b0,C::setup_background_music,2,Value::option},
    {0x12e70a,0x13e8b0,C::setup_traditional_movement,2,Value::option},
    {0x12f52c,0x13e8b0,C::setup_traditional_movement_help,2},
    {0x12e7a2,0x13e8b0,C::setup_auto_enter_homestead,2,Value::option},
    {0x12e7ed,0x13e8b0,C::setup_auto_enter_homestead_help,2},
    {0x12e840,0x13e8b0,C::setup_map_lighting,2,Value::option},
    {0x12e88a,0x13e8b0,C::setup_map_lighting_help,2},
    {0x12f61d,0x13e8b0,C::setup_night_brightness,2,Value::option},
    {0x12f67b,0x13e8b0,C::setup_night_brightness_help,2},
    {0x12e8e7,0x13e8b0,C::setup_units,2,Value::option},
    {0x12e931,0x13e8b0,C::setup_units_help,2},
    {0x12e980,0x13e8b0,C::setup_right_alt_hotkeys,2,Value::option},
    {0x12e9ca,0x13e8b0,C::setup_right_alt_hotkeys_help,2},
    {0x12ea19,0x13e8b0,C::setup_map_grid,2,Value::option},
    {0x12ea63,0x13e8b0,C::setup_map_grid_help,2},
    {0x12eab5,0x13e8b0,C::setup_old_hardware_mode,2,Value::option},
    {0x12eb09,0x13e8b0,C::setup_old_hardware_mode_help,2},
    {0x12eb3c,0x13e8b0,C::setup_old_hardware_software_help,2},
    {0x12eb6f,0x13e8b0,C::setup_old_hardware_restart_help,2},
    {0x12ebb9,0x13e8b0,C::setup_mobile_controller,2,Value::option},
    {0x12ec09,0x13e8b0,C::setup_mobile_controller_help,2},
    {0x15a7c5,0x1471a0,C::about_title,4,Value::literal,7},
    {0x15a807,0x13b460,C::about_version,0,Value::about_version},
    {0x15a828,0x13e8b0,C::about_version,2,Value::about_version},
    {0x15a85f,0x13b460,C::about_copyright,0,Value::copyright},
    {0x15a880,0x13e8b0,C::about_copyright,2,Value::copyright},
    {0x15a8d9,0x13b460,C::about_publisher,0},
    {0x15a8f8,0x13e8b0,C::about_publisher,2},
    {0x15a9f6,0x13b460,C::about_release_notes,0},
    {0x15aa15,0x13e8b0,C::about_release_notes,2},
    {0x15aa80,0x13b460,C::about_install_label,0},
    {0x15aaa2,0x13e8b0,C::about_install_label,2},
    {0x15ab3c,0x144fb0,C::about_press_key,2},
    // endgame: complete native text consumers, including the seven-argument
    // panel, native centext and full button. No page layout is stored here.
    {0x10e81e,0x1471a0,C::farewell_title,4,Value::literal,7},
    {0x10e960,0x13e8b0,C::farewell_tree,2},
    {0x10e977,0x13e8b0,C::farewell_river,2},
    {0x10e98e,0x13e8b0,C::farewell_fish,2},
    {0x10e9a5,0x13e8b0,C::farewell_money,2},
    {0x10e9bc,0x13e8b0,C::farewell_source,2},
    {0x10e9f5,0x13ea90,C::farewell_dedication,3},
    {0x10ea27,0x13e8b0,C::farewell_earth,2},
    {0x10ea59,0x13e8b0,C::farewell_spirit,2},
    {0x10ea8b,0x13e8b0,C::farewell_courage,2},
    {0x10eaa1,0x144fb0,C::farewell_press_key,2},
    {0x15a46b,0x1471a0,C::credits_title,4,Value::literal,7},
    {0x15a48c,0x1afe00,C::credits_introduction_1,1},
    {0x15a49a,0x1afe00,C::credits_introduction_2,1},
    {0x15a4b6,0x1afe00,C::credits_alexander,1},
    {0x15a4c4,0x1afe00,C::credits_andrew,1},
    {0x15a4d2,0x1afe00,C::credits_artemis,1},
    {0x15a4e0,0x1afe00,C::credits_artemiy,1},
    {0x15a4ee,0x1afe00,C::credits_brian,1},
    {0x15a4fc,0x1afe00,C::credits_flap,1},
    {0x15a50a,0x1afe00,C::credits_hamsolovski,1},
    {0x15a518,0x1afe00,C::credits_jeremy,1},
    {0x15a526,0x1afe00,C::credits_kerri,1},
    {0x15a534,0x1afe00,C::credits_kuu,1},
    {0x15a542,0x1afe00,C::credits_lani,1},
    {0x15a550,0x1afe00,C::credits_paulo,1},
    {0x15a55e,0x1afe00,C::credits_plotinus,1},
    {0x15a56c,0x1afe00,C::credits_rain,1},
    {0x15a57a,0x1afe00,C::credits_scott,1},
    {0x15a588,0x1afe00,C::credits_shawn,1},
    {0x15a596,0x1afe00,C::credits_tommy,1},
    {0x15a5a4,0x1afe00,C::credits_wickerman,1},
    {0x15a5b2,0x1afe00,C::credits_countrymen_1,1},
    {0x15a5c0,0x1afe00,C::credits_countrymen_2,1},
    {0x15a5ce,0x1afe00,C::credits_photo_contributors,1},
    {0x15a5dc,0x1afe00,C::credits_veterans,1},
    {0x15a611,0x144fb0,C::credits_press_key,2},
    {0x15b1b9,0x13e8b0,C::load_saved_empty,2},
    {0x15b1eb,0x13e8b0,C::load_saved_press_key,2},
    {0x15b75e,0x1afe00,C::production,1},
    {0x15b7c3,0x1afe00,C::copyright,1,Value::footer_copyright},
    {0x15b80a,0x1afe00,C::authors,1},
    {0x15a6f8,0x13b460,C::version,0,Value::version},
    {0x15a71b,0x13e8b0,C::version,2,Value::version},
    {0x15caa8,0x13e8b0,C::intro_north,2},
    {0x15cb10,0x13e8b0,C::intro_roleplaying,2},
    {0x124626,0x1afe00,C::scenario_introduction_1,1},
    {0x124634,0x1afe00,C::scenario_introduction_2,1},
    {0x124642,0x1afe00,C::scenario_introduction_3,1},
    {0x124650,0x1afe00,C::scenario_introduction_4,1},
    {0x124685,0x144fb0,C::scenario_press_key,2},
    {0x1f86d,0x1471a0,C::profile_heading,4,Value::literal,7},
    {0x1e17c,0x1471a0,C::profile_name_title,4,Value::literal,7},
    {0x1e371,0x1afe00,C::profile_name_help,1},
    {0x1e39a,0x1afe00,C::profile_name_help_repeat,1},
    {0x1bca5,0x1afe00,C::profile_sex_help,1},
    {0x1c314,0x1afe00,C::profile_season_help,1},
    {0x1efa9,0x1afe00,C::profile_portrait_help,1},
    {0x10d4c9,0x1471a0,C::profile_physical,4,Value::literal,7},
    {0x10d4f8,0x1471a0,C::profile_physique,4,Value::literal,7},
    {0x10d80d,0x1471a0,C::profile_personality,4,Value::literal,7},
    {0x10d88a,0x1471a0,C::profile_appearance,4,Value::literal,7},
    {0x10d6b7,0x108880,C::profile_strength,2},
    {0x10d6dc,0x108880,C::profile_endurance,2},
    {0x10d701,0x108880,C::profile_dexterity,2},
    {0x10d726,0x108880,C::profile_agility,2},
    {0x10d74b,0x108880,C::profile_speed,2},
    {0x10d770,0x108880,C::profile_eyesight,2},
    {0x10d795,0x108880,C::profile_hearing,2},
    {0x10d7ba,0x108880,C::profile_smell_taste,2},
    {0x10d7df,0x108880,C::profile_touch,2},
    {0x10d834,0x108880,C::profile_intelligence,2},
    {0x10d859,0x108880,C::profile_will,2},
    {0x10d8fd,0x13e8b0,C::profile_height,2},
    {0x10d981,0x13e8b0,C::profile_weight,2},
    {0x10d95e,0x146ed0,C::profile_measurement,3},
    {0x10d9da,0x146ed0,C::profile_measurement,3},
    {0x10db12,0x1afe00,C::profile_confirm_background,1},
    {0x10db20,0x1afe00,C::profile_confirm_attributes,1},
    {0x10da8a,0x1afe00,C::profile_attributes_ready,1},
    {0x10da98,0x1afe00,C::profile_attributes_press_key,1},
    {0x1056ee,0x13b460,C::ancestors_order_label,0},
    {0x10570c,0x13e8b0,C::ancestors_order_label,2},
    {0x105aec,0x13e8b0,C::ancestors_empty,2},
    {0x10582f,0x13e8b0,C::ancestors_page,2,Value::page},
    {0x105681,0x145300,C::ancestors_select_hint,2},
    {0x122b17,0x13e8b0,C::hud_label,2},
    {0x122b3a,0x13e8b0,C::hud_label,2},
    {0x122b5d,0x13e8b0,C::hud_label,2},
    {0x122b80,0x13e8b0,C::hud_label,2},
    {0x122ba3,0x13e8b0,C::hud_label,2},
    {0x122dc6,0x13e8b0,C::hud_label,2},
    {0x122e81,0x13e8b0,C::hud_label,2},
    {0x122f6e,0x13e8b0,C::hud_label,2},
    {0x122f35,0x146ed0,C::hud_label,3},
    {0x122cde,0x144c60,C::hud_condition,3},
    {0x122d3b,0x144c60,C::hud_condition,3},
    {0x122d77,0x144c60,C::hud_condition,3},
    {0x12270f,0x13e8b0,C::hud_label,2},
    {0x122825,0x144fb0,C::hud_label,2,Value::key_suffix},
    {0x12303b,0x144fb0,C::hud_label,2,Value::key_suffix},
    {0x11ea9e,0x146ed0,C::hud_label,3},
    {0x1231af,0x1223b0,C::hud_label,2,Value::literal,7},
    {0x1231d9,0x1223b0,C::hud_label,2,Value::literal,7},
    {0x123218,0x1223b0,C::hud_label,2,Value::literal,7},
    {0x123281,0x1223b0,C::hud_label,2,Value::literal,7},
    {0x1232eb,0x1223b0,C::hud_label,2,Value::literal,7},
    {0x12333f,0x1223b0,C::hud_label,2,Value::literal,7},
    {0x123380,0x1223b0,C::hud_label,2,Value::literal,7},
    {0x12c202,0x127ed0,C::hud_penalty,1},
    {0x12c25f,0x127ed0,C::hud_penalty,1},
    {0x12c2bc,0x127ed0,C::hud_penalty,1},
    {0x12c31f,0x127ed0,C::hud_penalty,1},
    {0x123814,0x141650,C::hud_action,4},
    {0x123b56,0x141650,C::hud_direction,4},
    {0x123941,0x141650,C::hud_speed,4},
    {0xbd272,0x13ea90,C::world_place_gloss,3,Value::place},
    {0xbd2cd,0x13ea90,C::world_region,3},
    {0xbd317,0x13ea90,C::world_region,3},
    {0xbd646,0x13ea90,C::world_location,3},
    {0xbd8ad,0x13ea90,C::world_date,3},
    {0xbd976,0x13ea90,C::world_map_kind,3},
    {0xbd8e6,0x13b460,C::world_scale,0},
    {0xbd908,0xaee30,C::world_scale,3},
    {0x12c8eb,0x13e8b0,C::world_season,2},
    {0x12c925,0x1afe00,C::world_month,1},
    {0x12c9b7,0x13e8b0,C::world_time,2},
};
void bound(Frame& frame) {
    const auto site=static_cast<u32>(frame.resume-host->image_base-5);
    const Binding* binding=nullptr;
    for(const auto& entry:bindings) if(entry.site==site) { binding=&entry; break; }
    Frame arguments=frame;
    const bool introduction=binding->component==C::intro_north || binding->component==C::intro_roleplaying ||
        (binding->component==C::version && intro_active);
    const bool enabled=introduction ? intro_chinese : chinese;
    if(!enabled) { frame.rax=call(arguments,binding->target,binding->arguments,frame); return; }
    const char* original=reinterpret_cast<const char*>(argument(frame,binding->argument));
    std::string prefix;
    if(binding->value==Value::key_suffix) {
        const auto bytes=std::strchr(original+1,'.')-original+1;
        prefix.assign(original,bytes);
        original+=bytes;
    }
    std::string value;
    switch(binding->value) {
    case Value::option: value=std::string(original).substr(std::string(original).find(':')+2); break;
    case Value::version: value=std::string(original).substr(8); break;
    case Value::about_version: value=std::string(original).substr(23); break;
    case Value::copyright: value=std::string(original).substr(4,std::string(original).find(" by ")-4); break;
    case Value::footer_copyright: value=std::string(original).substr(4,std::string(original).find("<br>")-4); break;
    case Value::page: {
        int page{},total{};
        std::sscanf(original,"Page %d of %d",&page,&total);
        value=std::to_string(page)+"/"+std::to_string(total);
        break;
    }
    case Value::place:value=at<char>(0x1e69380);break;
    default:break;
    }
    auto encoded=prefix+translated(binding->component,original,value.empty()?nullptr:value.c_str());
    argument(arguments,binding->argument)=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    frame.rax=call(arguments,binding->target,binding->arguments,frame);
}
void show_cursor(Frame& frame) { frame.rdx=width(reinterpret_cast<const char*>(frame.r14)); }
void profile_identity(Frame& frame) {
    Frame arguments=frame;
    std::string display;
    if(chinese) {
        // choose_culture stores the CULTURE_INHABITANT index at Plr+0xD.
        // plrnam supplies "name inhabitant"; borrow only its display prefix.
        const auto* original=reinterpret_cast<const char*>(frame.rdi);
        const auto* separator=std::strchr(original,' ');
        const std::string name(original,separator);
        const auto culture=*at<unsigned char>(0xac8604d);
        const auto component=static_cast<C>(static_cast<u32>(C::profile_culture_0)+culture);
        display=native_display(name.c_str())+" "+translated(component,separator+1);
        arguments.rdi=reinterpret_cast<std::uintptr_t>(display.c_str());
    }
    frame.rax=call(arguments,0x1225e0);
}
void profile_start_age(Frame& frame) {
    using Format=int (*)(char*,int,std::size_t,const char*,...);
    const auto format=native<Format>(0x8f80);
    auto* output=reinterpret_cast<char*>(frame.rdi);
    const auto* original=reinterpret_cast<const char*>(frame.rcx);
    if(chinese) {
        const auto age=std::to_string(static_cast<unsigned>(frame.r8));
        const auto display=translated(C::profile_start_age,original,age.c_str());
        frame.rax=format(output,frame.rsi,frame.rdx,"%s",display.c_str());
    } else frame.rax=format(output,frame.rsi,frame.rdx,original,static_cast<unsigned>(frame.r8));
}
void center_pair(Frame& frame) {
    frame.rdx=width(reinterpret_cast<const char*>(frame.rbp));
    frame.rcx=frame.rdx+width(reinterpret_cast<const char*>(frame.rbx));
}
void center_tail(Frame& frame) { frame.rdx=width(reinterpret_cast<const char*>(frame.rbp)); }
void paragraph_width(Frame& frame) {
    frame.rdx=std::uint32_t(frame.r14)+width(reinterpret_cast<const char*>(frame.rbp));
    frame.rax=std::uint32_t(frame.rax+frame.r13);
}
void paragraph_advance(Frame& frame) {
    frame.rdx-=frame.r12;
    frame.rax=std::uint32_t(frame.r14)+width(reinterpret_cast<const char*>(frame.r12));
}
void title_width(Frame& frame) {
    frame.rax=width(reinterpret_cast<const char*>(frame.r15));
    frame.r14=static_cast<std::uint32_t>(static_cast<std::int32_t>(frame.r14)>>1);
}
void button_length(Frame& frame) { frame.rax=(width(reinterpret_cast<const char*>(frame.rbp))+7)/8; }
void button_character(Frame& frame) {
    auto* output=reinterpret_cast<char*>(frame.rdi);
    auto* input=reinterpret_cast<const unsigned char*>(frame.rbp+frame.r15);
    if(token(input)) { output[0]=input[0]; output[1]=input[1]; output[2]=0; ++frame.r15; frame.rax=2; }
    else { output[0]=static_cast<char>(frame.r8); output[1]=0; frame.rax=1; }
}
void button_advance(Frame& frame) {
    frame.r12=std::uint32_t(frame.r12)+width(reinterpret_cast<const char*>(frame.r14));
    frame.resume=host->image_base+0x1451ad;
}
void sink_width(Frame& frame) {
    frame.rax=width(reinterpret_cast<const char*>(frame.r12));
    frame.rcx=static_cast<std::uint32_t>(frame.r13);
}
void menu_draw(Frame& frame) {
    const auto previous=scope;
    const auto site=frame.resume-host->image_base-5;
    if(site==0x15cf80) scope=Scope::main_menu;
    else if(site==0x12ec3e) scope=Scope::setup;
    else if(site==0x15b065 || site==0x15b187) scope=Scope::load_saved;
    else if(site==0x15d0e1) scope=Scope::creation;
    else if(site==0x1c000) scope=Scope::culture;
    else if(site==0x1bd1e || site==0x1bd58) scope=Scope::sex;
    else if(site==0x1c3c1) scope=Scope::season;
    else if(site==0x10dbd7) scope=Scope::attributes;
    frame.rax=call(frame,0xf5570);
    scope=previous;
}
void menu_text(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    if(chinese && scope==Scope::main_menu) {
        const auto row=(frame.rdx-(host->image_base+0x663f120))/0xe8;
        encoded=translated(static_cast<C>(row),reinterpret_cast<const char*>(frame.rdx));
        arguments.rdx=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x13e8b0);
}
void menu_title(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    if(chinese && (scope==Scope::load_saved || scope==Scope::creation || scope==Scope::culture || scope==Scope::sex || scope==Scope::season)) {
        const auto component=scope==Scope::load_saved ? C::load_saved_title : scope==Scope::creation ? C::character_creation_title :
            scope==Scope::culture ? C::profile_culture_title : scope==Scope::season ? C::profile_season_title : C::profile_sex_title;
        encoded=translated(component,reinterpret_cast<const char*>(frame.r8));
        arguments.r8=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x146a30);
}
void menu_button(Frame& frame) {
    Frame arguments=frame;
    const auto* original=reinterpret_cast<const char*>(frame.rdx);
    std::string encoded;
    if(chinese && (scope==Scope::creation || scope==Scope::culture || scope==Scope::sex || scope==Scope::season || scope==Scope::setup || scope==Scope::attributes)) {
        C component{};
        const auto row=(frame.rdx-(host->image_base+0x663f120))/0xe8;
        const auto action=*reinterpret_cast<const int*>(host->image_base+0x663f120+row*0xe8+0xc8);
        if(scope==Scope::setup) component=C::setup_exit;
        else if(scope==Scope::creation) {
            switch(action) {
            case 'Q':component=C::character_creation_quick;break;
            case 'C':component=C::character_creation_custom;break;
            case 'E':component=C::character_creation_easy;break;
            case 'T':component=C::character_creation_too_easy;break;
            case 27:component=C::character_creation_exit;break;
            }
        } else if(scope==Scope::culture) {
            if(action>='0' && action<='9') component=static_cast<C>(static_cast<u32>(C::profile_culture_0)+action-'0');
            else if(action=='R') component=C::profile_random;
            else if(action=='?') component=C::profile_cultures;
            else if(action==27) component=C::profile_back;
        } else if(scope==Scope::attributes) {
            switch(action) {
            case 'Y':component=C::profile_continue;break;
            case 'N':component=C::profile_reroll;break;
            }
        } else if(scope==Scope::season) {
            switch(action) {
            case '1':component=C::profile_season_spring;break;
            case '2':component=C::profile_season_summer;break;
            case '3':component=C::profile_season_autumn;break;
            case '4':component=C::profile_season_winter;break;
            case 27:component=C::profile_back;break;
            }
        } else {
            switch(action) {
            case 'M':component=C::profile_male;break;
            case 'F':component=C::profile_female;break;
            case 27:component=C::profile_back;break;
            }
        }
        const auto prefix=std::strchr(original+1,'.')-original+1;
        encoded=std::string(original,prefix)+translated(component,original+prefix);
        arguments.rdx=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x144fb0);
}
void ancestor_title(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    // Ancestors(-1) is the list; other values display a memorial's own name.
    if(chinese && static_cast<std::int32_t>(frame.rbx)==-1) {
        encoded=translated(C::ancestors_title,reinterpret_cast<const char*>(frame.rcx));
        arguments.rcx=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x146ed0);
}
void intro_line(Frame& frame,Phase phase,CallState& state) {
    if(phase==Phase::after) return;
    const auto line=(static_cast<int>(frame.r12)-400)/10;
    const auto component=static_cast<C>(static_cast<u32>(C::intro_story_0)+line);
    const auto site=frame.resume-host->image_base-5;
    const auto index=site==0x15c9ad ? 0u : 2u;
    state.target=site==0x15c9ad ? 0x13b460 : 0x15b8c0;
    if(intro_chinese) {
        const auto encoded=translated(component,reinterpret_cast<const char*>(argument(frame,index)));
        state.text=static_cast<char*>(host->allocate(encoded.size()+1));
        std::memcpy(state.text,encoded.c_str(),encoded.size()+1);
        argument(frame,index)=reinterpret_cast<std::uintptr_t>(state.text);
    }
}

struct Progress { C component; const char* value; };
const Progress* progress;
bool startup_audio_active;
void startup_message(Frame& frame) {
    const auto site=frame.resume-host->image_base-5;
    if((site==0x16dbc || site==0x17013 || site==0x16df1 || site==0x17043) && !startup_audio_active) {
        frame.rax=call(frame,0x159c20);
        return;
    }
    Progress current{};
    const auto* original=reinterpret_cast<const char*>(frame.rdi);
    if(site==0xaa27) current.component=C::startup_sound_init;
    else if(site==0x170bf) current.component=C::startup_audio_device_failed;
    else if(site==0x181ed) current.component=C::startup_intro;
    else if(site==0x16dbc || site==0x17013) {
        current.component=C::startup_audio;
        // Both native callers already format a resource name, not a filename.
        current.value=original+15;
    } else { current.component=C::startup_audio_failed; current.value=original+16; }
    const auto* previous=progress;
    progress=&current;
    frame.rax=call(frame,0x159c20);
    progress=previous;
}
void startup_draw(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    if(chinese && progress) {
        encoded=translated(progress->component,reinterpret_cast<const char*>(frame.rdx),progress->value);
        arguments.rdx=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x13e8b0);
}
void poll_language(Frame& frame,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        const auto site=frame.resume-host->image_base-5;
        state.target=site==0xf6ce8 || site==0xf777e ? 0x8ea0 : 0x81e0;
        return;
    }
    if(font_redraw_pending) {
        font_redraw_pending=false;
        // Consume font invalidation after the resident publication completes,
        // at the same native boundary as language refresh. These owners have
        // confirmed full reconstruction, including their background caches.
        if(scope==Scope::main_menu || active_view) redraw_language();
    }
    auto* event=reinterpret_cast<SDL_Event*>(frame.rdi);
    if(frame.rax && event->type==SDL_KEYDOWN && event->key.keysym.scancode==SDL_SCANCODE_F10 &&
       (event->key.keysym.mod & KMOD_SHIFT)) {
        if(!event->key.repeat) { chinese=!chinese; redraw_language(); }
        event->type=0; // Consume this actual Mod shortcut at the native input boundary.
    }
}
void name_error(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    if(chinese) {
        const auto* original=reinterpret_cast<const char*>(frame.rsi);
        const auto component=std::strcmp(original,"Too short character name.")==0 ? C::profile_name_too_short :
            std::strcmp(original,"Character name can't contain spaces or special characters.")==0 ? C::profile_name_invalid : C::profile_name_exists;
        encoded=translated(component,original);
        arguments.rsi=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x1afe00);
}
const C* spot_component;
struct Spot { u32 site; C component; };
const Spot spots[]{
    {0x1056b0,C::ancestors_exit},{0x105729,C::ancestors_order_played},
    {0x105754,C::ancestors_order_lived},{0x10577f,C::ancestors_order_journeyed},
    {0x105b23,C::ancestors_previous_page},{0x105b56,C::ancestors_next_page}
};
void spot_scope(Frame& frame) {
    const auto site=frame.resume-host->image_base-5;
    const auto* previous=spot_component;
    for(const auto& spot:spots) if(spot.site==site) { spot_component=&spot.component; break; }
    frame.rax=call(frame,0xf4f50);
    spot_component=previous;
}
void spot_draw(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    if(chinese && spot_component) {
        const auto* original=reinterpret_cast<const char*>(frame.rdx);
        const auto prefix=std::strchr(original+1,'.')-original+1;
        encoded=std::string(original,prefix)+translated(*spot_component,original+prefix);
        arguments.rdx=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x144fb0);
}
unsigned scenario_record;
bool village;
void scenario_scope(Frame&,Phase phase,CallState& state) {
    if(phase==Phase::before) { scenario_record=0; state.target=0x124190; }
}
void scenario_title(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    const auto* original=reinterpret_cast<const char*>(frame.r8);
    village=std::strcmp(original,"THE VILLAGE")==0;
    if(chinese && village) {
        encoded=translated(C::scenario_village_title,original);
        arguments.r8=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x1471a0,7,frame);
}
void scenario_append(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    const auto* original=reinterpret_cast<const char*>(frame.rsi);
    // The native reader appends fourteen source lines (one blank separator)
    // plus its terminal empty EOF read. Ordinals name semantic source records.
    if(village && original[0] && std::strcmp(original,"<br>")!=0) {
        const auto component=static_cast<C>(static_cast<u32>(C::scenario_village_departure_1)+scenario_record++);
        if(chinese) {
            encoded=translated(component,original);
            if(std::strncmp(original,"<br>",4)==0) encoded="<br>"+encoded;
            arguments.rsi=reinterpret_cast<std::uintptr_t>(encoded.c_str());
        }
    }
    frame.rax=call(arguments,0x1afe00);
}
void intro_scope(Frame&,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        intro_chinese=chinese;
        intro_active=true;
        state.target=0x15ca20;
    } else intro_active=false;
}
void startup_audio_scope(Frame& frame,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        state.data[0]=startup_audio_active;
        startup_audio_active=true;
        const auto site=frame.resume-host->image_base-5;
        state.target=site==0xaa2c ? 0x17060 : site==0xaa4a ? 0x18130 : 0x17130;
    } else startup_audio_active=state.data[0];
}
struct AncestorNumbers { int age,days,kilometers; };
std::vector<AncestorNumbers> ancestor_rows;
void ancestor_row(Frame&,Phase phase,CallState& state) {
    if(phase==Phase::before) { ancestor_rows.push_back({}); state.target=0x1039b0; }
    else ancestor_rows.pop_back();
}
void ancestor_format(Frame& frame) {
    using Format=int (*)(char*,int,std::size_t,const char*,...);
    const auto format=native<Format>(0x8f80);
    const bool lived=frame.resume-host->image_base-5==0x103c0c;
    if(lived) {
        const int days=*reinterpret_cast<const int*>(frame.stack());
        if(!ancestor_rows.empty()) { ancestor_rows.back().age=static_cast<int>(frame.r9); ancestor_rows.back().days=days; }
        frame.rax=format(reinterpret_cast<char*>(frame.rdi),static_cast<int>(frame.rsi),frame.rdx,
            reinterpret_cast<const char*>(frame.rcx),reinterpret_cast<const char*>(frame.r8),static_cast<int>(frame.r9),days);
    } else {
        if(!ancestor_rows.empty()) ancestor_rows.back().kilometers=static_cast<int>(frame.r9);
        frame.rax=format(reinterpret_cast<char*>(frame.rdi),static_cast<int>(frame.rsi),frame.rdx,
            reinterpret_cast<const char*>(frame.rcx),reinterpret_cast<const char*>(frame.r8),static_cast<int>(frame.r9));
    }
}
void ancestor_summary(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    if(chinese && !ancestor_rows.empty()) {
        const bool lived=frame.resume-host->image_base-5==0x103e18;
        const auto& numbers=ancestor_rows.back();
        const auto value=lived ? std::to_string(numbers.age)+" 岁，度过了 "+std::to_string(numbers.days)+" 天冒险生涯" :
            std::to_string(numbers.kilometers);
        encoded=translated(lived ? C::ancestors_lived : C::ancestors_journeyed,reinterpret_cast<const char*>(frame.rdx),value.c_str());
        arguments.rdx=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x13e8b0);
}
#include "culture_info.inc"
#include "culture_map.inc"
#include "spells.inc"
#include "skills.inc"

struct MenuInput { u32 site; Scope scope; };
const MenuInput menu_inputs[]{
    {0x15cf85,Scope::main_menu},{0x15d0e6,Scope::creation},
    {0x1c07c,Scope::culture},{0x1bd2c,Scope::sex},{0x1c3c6,Scope::season},
    {0x10dbe7,Scope::attributes}
};
void menu_input(Frame& frame,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        state.data[0]=static_cast<u32>(scope);
        for(const auto& entry:menu_inputs)
            if(entry.site==frame.resume-host->image_base-5) { scope=entry.scope; break; }
        state.target=0xf8630;
    } else scope=static_cast<Scope>(state.data[0]);
}
void view_wait(Frame& frame,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        state.target=0xf9060;
        state.skip=redrawing_view;
        if(state.skip) frame.rax=0;
    }
}
void view_scope(Frame& frame,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        state.data[0]=active_view;
        active_view=frame.resume-host->image_base-5==0x15cff4 ? 0x15a750 : 0x15a440;
        state.target=active_view;
    } else active_view=state.data[0];
}
void redraw_list() {
    native<void (*)()>(0xf5570)();
    // Same owner and branch as LIST_Go at F865E/F866B. Save the newly
    // drawn rows before restoring the native selection highlight.
    if(*at<int>(0x663f014)!=2) native<void (*)()>(0x13d5a0)();
    const auto position=*at<int>(0x663f010);
    const auto skip=*at<int>(0x663f120+position*0xe8+0xe0);
    if(!skip) native<void (*)(int,int)>(0xf3f80)(position,0);
}
void rebuild_main_menu() {
    const auto previous=scope;
    scope=Scope::main_menu;
    // MakeStartList uses a frameless list: LIST_Draw does not erase its
    // previous text. Re-enter the native background/footer fragment and
    // panel/logo builder before drawing rows in the selected language.
    redrawing_main_background=true;
    uwcn_linux_redraw_main_fragment(host->image_base+0x15ceeb);
    redrawing_main_background=false;
    native<void (*)()>(0x15cbe0)();
    redraw_list();
    scope=previous;
}
void redraw_language() {
    if(active_view) {
        rebuild_main_menu();
        // UrW_Start owns SCREENSAVE around AboutScreen/CreditsScreen.
        // Replace that native background before rebuilding the open view,
        // so its eventual restore_page cannot bring back the old language.
        native<void (*)()>(0x13d590)();
        redrawing_view=true;
        native<void (*)()>(active_view)();
        redrawing_view=false;
        native<void (*)()>(0x13fe50)();
        return;
    }
    if(scope==Scope::encyclopedia || scope==Scope::encyclopedia_intro) {
        redraw_culture();
    } else if(scope==Scope::main_menu) {
        rebuild_main_menu();
        native<void (*)()>(0x13fe50)();
    } else if(scope==Scope::creation || scope==Scope::culture || scope==Scope::sex || scope==Scope::season) {
        redraw_list();
        native<void (*)()>(0x13fe50)();
    }
}
void invalidate_glyph_widths() {
    for(auto& entry:glyphs) entry.second.width=-1;
}
void main_background(Frame& frame) {
    // Original full-canvas bestfitPic arguments and its seventh stack argument
    // remain native. All retired resources are released before it borrows any.
    if(linux_targets::synchronize_main_menu()) invalidate_glyph_widths();
    frame.rax=call(frame,0x144560,7,frame);
}
void main_background_end(Frame& frame) {
    if(redrawing_main_background)
        frame.resume=reinterpret_cast<std::uintptr_t>(uwcn_linux_redraw_main_return);
    else
        frame.rdi=host->image_base+0x2016a5; // Covered native LEA RDI.
}
void resize_native_targets(Frame& frame) {
    frame.rax=call(frame,0x13a040); // Native map textures rebuild first.
    if(scope!=Scope::main_menu || active_view || !linux_targets::synchronize_main_menu()) return;
    invalidate_glyph_widths();
    rebuild_main_menu();
    native<void (*)()>(0x13fe50)();
}
Status initialize(const HostApi* api) {
    host=api;
    const auto get=reinterpret_cast<const linux_host::Hooks* (*)()>(dlsym(RTLD_DEFAULT,"uwcn_linux_hooks_v2"));
    hooks=get();
    install_name_input();
    install_culture_info();
    install_culture_map();
    install_spells();
    install_skills();
    linux_targets::install(*hooks);
    hooks->instruction(0x15cf21,5,main_background);
    hooks->instruction(0x15cf44,7,main_background_end);
    hooks->instruction(0xf6d9e,5,resize_native_targets);
    hooks->replace(0x13b460,8,reinterpret_cast<void*>(+[](char* text)->int { return width(text); }));
    hooks->replace(0x13b760,5,reinterpret_cast<void*>(textput));
    hooks->replace(0x13de10,6,reinterpret_cast<void*>(rentextput));
    hooks->replace(0x13e1b0,6,reinterpret_cast<void*>(rentextput));
    hooks->instruction(0x13ea00,6,show_cursor);
    hooks->instruction(0x13eb6f,10,center_pair);
    hooks->instruction(0x13ec9c,6,center_tail);
    hooks->instruction(0x13eec3,7,paragraph_width);
    hooks->instruction(0x13f00f,7,paragraph_advance);
    hooks->instruction(0x14709b,6,title_width);
    hooks->instruction(0x1452e3,5,button_length);
    hooks->instruction(0x145264,5,button_character);
    hooks->instruction(0x145286,9,button_advance);
    hooks->instruction(0x127d7c,6,sink_width);
    for(const auto& binding:bindings) hooks->instruction(binding.site,5,bound);
    hooks->instruction(0x10d610,5,profile_identity);
    hooks->instruction(0x10d641,5,profile_start_age);
    for(auto site:{0x15cf80u,0x12ec3eu,0x15b065u,0x15b187u,0x15d0e1u,0x1c000u,0x1bd1eu,0x1bd58u,0x1c3c1u,0x10dbd7u}) hooks->instruction(site,5,menu_draw);
    hooks->instruction(0xf572f,5,menu_text);
    hooks->instruction(0xf5617,5,menu_title);
    hooks->instruction(0xf57d4,5,menu_button);
    hooks->instruction(0x1e38c,5,name_error);
    hooks->instruction(0x10523a,5,ancestor_title);
    for(auto site:{0x15c9adu,0x15c9c7u}) hooks->around(site,intro_line,false);
    for(auto site:{0xaa27u,0x170bfu,0x181edu,0x16dbcu,0x17013u,0x16df1u,0x17043u}) hooks->instruction(site,5,startup_message);
    hooks->instruction(0x159c6d,5,startup_draw);
    for(const auto& spot:spots) hooks->instruction(spot.site,5,spot_scope);
    hooks->instruction(0xf502d,5,spot_draw);
    hooks->around(0x124615,scenario_scope,false);
    hooks->instruction(0x1244b8,5,scenario_title);
    hooks->instruction(0x124565,5,scenario_append);
    hooks->around(0xa4f8,intro_scope,false);
    for(auto site:{0xaa2cu,0xaa45u,0xaa4au,0xaa54u}) hooks->around(site,startup_audio_scope,false);
    hooks->around(0x1055f1,ancestor_row,false);
    for(auto site:{0x103c0cu,0x103c97u}) hooks->instruction(site,5,ancestor_format);
    for(auto site:{0x103e18u,0x103e3cu}) hooks->instruction(site,5,ancestor_summary);
    for(const auto& entry:menu_inputs) hooks->around(entry.site,menu_input,false);
    for(auto site:{0x15cff4u,0x15cfc3u}) hooks->around(site,view_scope,false);
    hooks->around(0x15ab41,view_wait,false);
    hooks->around(0x15a61a,view_wait,true);
    for(auto site:{0xf6ce8u,0xf777eu,0xf6f00u,0xf7130u,0xf7181u,0xf71f1u,0xf7261u,0xf72d1u,0xf734du,0xf73a1u,0xf74f3u})
        hooks->around(site,poll_language,false);
    hooks->finish();
    return Status::ok;
}
Status invoke(u32 operation,const void* input,u32 bytes,void*,u32* capacity) {
    if(operation!=kModuleDependenciesChanged || !input || bytes!=sizeof(u32)) return Status::invalid;
    invalidate_glyph_widths();
    refresh_culture_words();
    if(*static_cast<const u32*>(input)&4u) font_redraw_pending=true;
    if(capacity) *capacity=0;
    return Status::ok;
}
Status save_state(void* output,u32* capacity) {
    linux_host::StateWriter state;
    state.put(u32{1});
    state.put(chinese); state.put(scope); state.put(intro_active); state.put(intro_chinese);
    state.put(active_view); state.put(startup_audio_active);
    state.put(scenario_record); state.put(village);
    state.put(name_input_active); state.put(name_text_committed);
    state.put(topic_id(culture_topic)); state.put(topic_id(culture_preview));
    state.put(culture_browser_chinese); state.put(culture_help_active);
    state.put(culture_help_record); state.put(culture_record_offset);
    state.put(static_cast<u32>(ancestor_rows.size()));
    for(const auto& row:ancestor_rows) state.put(row);
    state.put(static_cast<u32>(glyphs.size()));
    for(const auto& [id,glyph]:glyphs) { state.put(id); state.text(glyph.utf8); }
    linux_targets::save(state);
    return copy_output(state.bytes.data(),state.bytes.size(),output,capacity);
}
Status restore_state(const void* input,u32 bytes) {
    linux_host::StateReader state(input,bytes);
    if(state.get<u32>()!=1) return Status::invalid;
    chinese=state.get<bool>(); scope=state.get<Scope>();
    intro_active=state.get<bool>(); intro_chinese=state.get<bool>();
    active_view=state.get<u32>(); startup_audio_active=state.get<bool>();
    scenario_record=state.get<unsigned>(); village=state.get<bool>();
    name_input_active=state.get<bool>(); name_text_committed=state.get<bool>();
    culture_topic=topic_pointer(state.get<unsigned>()); culture_preview=topic_pointer(state.get<unsigned>());
    culture_browser_chinese=state.get<bool>(); culture_help_active=state.get<bool>();
    culture_help_record=state.get<unsigned>(); culture_record_offset=state.get<long>();
    ancestor_rows.clear();
    const auto rows=state.get<u32>();
    for(u32 i=0;i<rows;++i) ancestor_rows.push_back(state.get<AncestorNumbers>());
    glyphs.clear();
    const auto count=state.get<u32>();
    for(u32 i=0;i<count;++i) {
        const auto id=state.get<unsigned>();
        glyphs.emplace(id,Glyph{state.text(),-1});
    }
    linux_targets::restore(state);
    if(state.remaining) return Status::invalid;
    refresh_culture_words();
    return Status::ok;
}
void shutdown() { glyphs.clear(); culture_words.clear(); }
const ModuleApi api{sizeof(ModuleApi),kHostAbi,ModuleId::adapter,initialize,invoke,save_state,restore_state,shutdown};
}
UWCN_EXPORT const uwcn::ModuleDescriptor uwcn_module_descriptor{uwcn::kDescriptorMagic,uwcn::kHostAbi,6,uwcn::kModuleMachine,1};
UWCN_EXPORT const uwcn::ModuleApi* uwcn_get_module_api() { return &api; }
