#pragma once
#include "../../sdk/text_services.h"

namespace uwcn::adapter {
// Confirmed 10E5A0 call sites inside 105700. This is a semantic call inventory,
// not a page layout: positions, colors, visibility and values stay in the game.
struct SetupTextCall {
    std::uint32_t site;
    TextComponent component;
    bool dynamic_value;
};
inline constexpr SetupTextCall setup_text_calls[]{
    {0x1059C3,TextComponent::setup_fullscreen,true},
    {0x105A77,TextComponent::setup_logical_resize,true},
    {0x105B25,TextComponent::setup_logical_resize_help,false},
    {0x105B59,TextComponent::setup_video_restart_help,false},
    {0x105BDA,TextComponent::setup_audio,true},
    {0x105CB3,TextComponent::setup_volume,true},
    {0x105DBA,TextComponent::setup_background_music,true},
    {0x105ECB,TextComponent::setup_traditional_movement,true},
    {0x105F8B,TextComponent::setup_traditional_movement_help,false},
    {0x10602B,TextComponent::setup_auto_enter_homestead,true},
    {0x1060E2,TextComponent::setup_auto_enter_homestead_help,false},
    {0x10617B,TextComponent::setup_map_lighting,true},
    {0x106234,TextComponent::setup_map_lighting_help,false},
    {0x1064E2,TextComponent::setup_night_brightness,true},
    {0x10659B,TextComponent::setup_night_brightness_help,false},
    {0x1065D8,TextComponent::setup_units,true},
    {0x10668F,TextComponent::setup_units_help,false},
    {0x1066CC,TextComponent::setup_right_alt_hotkeys,true},
    {0x106783,TextComponent::setup_right_alt_hotkeys_help,false},
    {0x1067C0,TextComponent::setup_map_grid,true},
    {0x106877,TextComponent::setup_map_grid_help,false},
    {0x1068B7,TextComponent::setup_old_hardware_mode,true},
    {0x10696E,TextComponent::setup_old_hardware_mode_help,false},
    {0x1069A9,TextComponent::setup_old_hardware_software_help,false},
    {0x1069E4,TextComponent::setup_old_hardware_restart_help,false},
    {0x106A21,TextComponent::setup_mobile_controller,true},
    {0x106AE2,TextComponent::setup_mobile_controller_help,false}
};
}
