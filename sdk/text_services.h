#pragma once
#include <cstdint>

namespace uwcn {
// A component identifies a confirmed native consumer, never an English match.
enum class TextComponent : std::uint32_t {
    load_character = 0, create_character = 1, setup = 2, ancestors = 3,
    about = 4, credits = 5, quit = 6, bonus_material = 7,
    version = 0x100, production = 0x101, copyright = 0x102, authors = 0x103,
    startup_loading = 0x200, startup_sound_init = 0x201, startup_audio_device_failed = 0x202,
    startup_intro = 0x203, startup_audio = 0x204, startup_audio_failed = 0x205,
    intro_north = 0x300, intro_roleplaying = 0x301,
    intro_story_0 = 0x310, intro_story_1 = 0x311, intro_story_2 = 0x312,
    intro_story_3 = 0x313, intro_story_4 = 0x314, intro_story_5 = 0x315,
    intro_story_6 = 0x316, intro_story_7 = 0x317, intro_story_8 = 0x318,
    intro_story_9 = 0x319, intro_story_10 = 0x31A,
    translation_credit = 0x400, translation_version = 0x401,
    about_title = 0x500, about_version = 0x501, about_copyright = 0x502,
    about_publisher = 0x503, about_release_notes = 0x504,
    about_install_label = 0x505, about_press_key = 0x506,
    setup_title = 0x600,
    setup_fullscreen = 0x601, setup_logical_resize = 0x602, setup_audio = 0x603,
    setup_volume = 0x604, setup_background_music = 0x605, setup_traditional_movement = 0x606,
    setup_auto_enter_homestead = 0x607, setup_map_lighting = 0x608,
    setup_night_brightness = 0x609, setup_units = 0x60A, setup_right_alt_hotkeys = 0x60B,
    setup_map_grid = 0x60C, setup_old_hardware_mode = 0x60D, setup_mobile_controller = 0x60E,
    setup_logical_resize_help = 0x60F, setup_video_restart_help = 0x610,
    setup_traditional_movement_help = 0x611, setup_auto_enter_homestead_help = 0x612,
    setup_map_lighting_help = 0x613, setup_night_brightness_help = 0x614,
    setup_units_help = 0x615, setup_right_alt_hotkeys_help = 0x616, setup_map_grid_help = 0x617,
    setup_old_hardware_mode_help = 0x618, setup_old_hardware_software_help = 0x619,
    setup_old_hardware_restart_help = 0x61A, setup_mobile_controller_help = 0x61B,
    setup_controls_help = 0x61C, setup_config_help = 0x61D, setup_exit = 0x61E,
    credits_title = 0x700, credits_introduction_1 = 0x701, credits_introduction_2 = 0x702,
    credits_alexander = 0x703, credits_andrew = 0x704, credits_artemis = 0x705,
    credits_artemiy = 0x706, credits_brian = 0x707, credits_flap = 0x708,
    credits_hamsolovski = 0x709, credits_jeremy = 0x70A, credits_kerri = 0x70B,
    credits_kuu = 0x70C, credits_lani = 0x70D, credits_paulo = 0x70E,
    credits_plotinus = 0x70F, credits_rain = 0x710, credits_scott = 0x711,
    credits_shawn = 0x712, credits_tommy = 0x713, credits_wickerman = 0x714,
    credits_countrymen_1 = 0x715, credits_countrymen_2 = 0x716,
    credits_photo_contributors = 0x717, credits_veterans = 0x718, credits_press_key = 0x719,
    character_creation_title = 0x800, character_creation_quick = 0x801,
    character_creation_custom = 0x802, character_creation_easy = 0x803,
    character_creation_too_easy = 0x804, character_creation_exit = 0x805,
    ancestors_title = 0x900, ancestors_empty = 0x901, ancestors_order_label = 0x902,
    ancestors_order_played = 0x903, ancestors_order_lived = 0x904, ancestors_order_journeyed = 0x905,
    ancestors_exit = 0x906, ancestors_previous_page = 0x907, ancestors_next_page = 0x908,
    ancestors_select_hint = 0x909, ancestors_page = 0x90A,
    ancestors_lived = 0x90B, ancestors_journeyed = 0x90C,
    load_saved_title = 0xA00, load_saved_empty = 0xA01, load_saved_press_key = 0xA02,
    profile_heading = 0xB00, profile_culture_title = 0xB01, profile_sex_title = 0xB02,
    profile_name_title = 0xB03, profile_random = 0xB04, profile_cultures = 0xB05,
    profile_back = 0xB06, profile_male = 0xB07, profile_female = 0xB08, profile_name_help = 0xB09,
    profile_name_help_repeat = 0xB0A, profile_sex_help = 0xB0B,
    profile_name_too_short = 0xB0C, profile_name_invalid = 0xB0D, profile_name_exists = 0xB0E,
    profile_culture_0 = 0xB10, profile_culture_1 = 0xB11, profile_culture_2 = 0xB12,
    profile_culture_3 = 0xB13, profile_culture_4 = 0xB14, profile_culture_5 = 0xB15,
    profile_culture_6 = 0xB16, profile_culture_7 = 0xB17, profile_culture_8 = 0xB18,
    profile_culture_9 = 0xB19,
    scenario_village_title = 0xC00,
    scenario_introduction_1 = 0xC01, scenario_introduction_2 = 0xC02,
    scenario_introduction_3 = 0xC03, scenario_introduction_4 = 0xC04,
    scenario_press_key = 0xC05,
    scenario_village_departure_1 = 0xC10, scenario_village_departure_2 = 0xC11,
    scenario_village_departure_3 = 0xC12, scenario_village_traders_1 = 0xC13,
    scenario_village_traders_2 = 0xC14, scenario_village_traders_3 = 0xC15,
    scenario_village_arrival_1 = 0xC16, scenario_village_arrival_2 = 0xC17,
    scenario_village_arrival_3 = 0xC18, scenario_village_arrival_4 = 0xC19,
    scenario_village_advice_1 = 0xC1A, scenario_village_advice_2 = 0xC1B,
    scenario_village_advice_3 = 0xC1C,
    culture_text = 0xD00,
    farewell_title = 0xE00, farewell_tree = 0xE01, farewell_river = 0xE02,
    farewell_fish = 0xE03, farewell_money = 0xE04, farewell_source = 0xE05,
    farewell_dedication = 0xE06, farewell_earth = 0xE07,
    farewell_spirit = 0xE08, farewell_courage = 0xE09, farewell_press_key = 0xE0A,
    hud_label = 0x10000, hud_condition = 0x10001, hud_penalty = 0x10002,
    hud_action = 0x10003, hud_direction = 0x10004, hud_speed = 0x10005,
    world_place_gloss = 0x10100, world_location = 0x10101, world_region = 0x10102,
    world_date = 0x10103, world_scale = 0x10104, world_map_kind = 0x10105,
    world_season = 0x10106, world_month = 0x10107, world_time = 0x10108
};
namespace text_op { constexpr std::uint32_t translate = 1; }
namespace catalog_op { constexpr std::uint32_t lookup = 1, repertoire = 2; }
namespace layout_op { constexpr std::uint32_t decode = 1, encode_native = 2, decode_native = 3; }

// Pointers are borrowed only for this synchronous service invocation.
// Output is UTF-8 including NUL; *output_bytes reports the required capacity.
struct TextRequest {
    TextComponent component;
    const char* original;
    const char* value;
};
struct CatalogRequest { const char* key; };
struct DecodeRequest { const char* utf8; std::uint32_t byte_count; };
struct CodecRequest { const char* text; };
// Decode output is a sequence of Unicode scalar values, without a sentinel.
}
