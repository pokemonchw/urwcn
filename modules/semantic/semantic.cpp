#include "sdk/host_abi.h"
#include "sdk/text_services.h"
#include "sdk/service_helpers.h"
#include "hud_text.h"
#include "world_hud_text.h"

namespace {
using namespace uwcn;
const HostApi* host_api=nullptr;
const char* key(TextComponent component) {
    switch(component) {
    case TextComponent::load_character:return "menu.load_character";
    case TextComponent::create_character:return "menu.create_character";
    case TextComponent::setup:return "menu.setup";
    case TextComponent::ancestors:return "menu.ancestors";
    case TextComponent::about:return "menu.about";
    case TextComponent::credits:return "menu.credits";
    case TextComponent::quit:return "menu.quit";
    case TextComponent::bonus_material:return "menu.bonus_material";
    case TextComponent::version:return "main.version";
    case TextComponent::production:return "main.production";
    case TextComponent::copyright:return "main.copyright";
    case TextComponent::authors:return "main.authors";
    case TextComponent::translation_credit:return "main.translation_credit";
    case TextComponent::translation_version:return "main.translation_version";
    case TextComponent::about_title:return "about.title";
    case TextComponent::about_version:return "about.version";
    case TextComponent::about_copyright:return "about.copyright";
    case TextComponent::about_publisher:return "about.publisher";
    case TextComponent::about_release_notes:return "about.release_notes";
    case TextComponent::about_install_label:return "about.install_label";
    case TextComponent::about_press_key:return "about.press_key";
    case TextComponent::farewell_title:return "farewell.title";
    case TextComponent::farewell_tree:return "farewell.tree";
    case TextComponent::farewell_river:return "farewell.river";
    case TextComponent::farewell_fish:return "farewell.fish";
    case TextComponent::farewell_money:return "farewell.money";
    case TextComponent::farewell_source:return "farewell.source";
    case TextComponent::farewell_dedication:return "farewell.dedication";
    case TextComponent::farewell_earth:return "farewell.earth";
    case TextComponent::farewell_spirit:return "farewell.spirit";
    case TextComponent::farewell_courage:return "farewell.courage";
    case TextComponent::farewell_press_key:return "farewell.press_key";
    case TextComponent::creation_complete_title:return "creation.complete_title";
    case TextComponent::creation_complete_enter:return "creation.complete_enter";
    case TextComponent::creation_complete_proverb:return "creation.complete_proverb";
    case TextComponent::creation_complete_source:return "creation.complete_source";
    case TextComponent::creation_complete_press_key:return "creation.complete_press_key";
    case TextComponent::credits_title:return "credits.title";
    case TextComponent::credits_introduction_1:return "credits.introduction_1";
    case TextComponent::credits_introduction_2:return "credits.introduction_2";
    case TextComponent::credits_alexander:return "credits.alexander";
    case TextComponent::credits_andrew:return "credits.andrew";
    case TextComponent::credits_artemis:return "credits.artemis";
    case TextComponent::credits_artemiy:return "credits.artemiy";
    case TextComponent::credits_brian:return "credits.brian";
    case TextComponent::credits_flap:return "credits.flap";
    case TextComponent::credits_hamsolovski:return "credits.hamsolovski";
    case TextComponent::credits_jeremy:return "credits.jeremy";
    case TextComponent::credits_kerri:return "credits.kerri";
    case TextComponent::credits_kuu:return "credits.kuu";
    case TextComponent::credits_lani:return "credits.lani";
    case TextComponent::credits_paulo:return "credits.paulo";
    case TextComponent::credits_plotinus:return "credits.plotinus";
    case TextComponent::credits_rain:return "credits.rain";
    case TextComponent::credits_scott:return "credits.scott";
    case TextComponent::credits_shawn:return "credits.shawn";
    case TextComponent::credits_tommy:return "credits.tommy";
    case TextComponent::credits_wickerman:return "credits.wickerman";
    case TextComponent::credits_countrymen_1:return "credits.countrymen_1";
    case TextComponent::credits_countrymen_2:return "credits.countrymen_2";
    case TextComponent::credits_photo_contributors:return "credits.photo_contributors";
    case TextComponent::credits_veterans:return "credits.veterans";
    case TextComponent::credits_press_key:return "credits.press_key";
    case TextComponent::character_creation_title:return "character_creation.title";
    case TextComponent::character_creation_quick:return "character_creation.quick";
    case TextComponent::character_creation_custom:return "character_creation.custom";
    case TextComponent::character_creation_easy:return "character_creation.easy";
    case TextComponent::character_creation_too_easy:return "character_creation.too_easy";
    case TextComponent::character_creation_exit:return "character_creation.exit";
    case TextComponent::load_saved_title:return "load_saved.title";
    case TextComponent::load_saved_empty:return "load_saved.empty";
    case TextComponent::load_saved_press_key:return "load_saved.press_key";
    case TextComponent::scenario_village_title:return "scenario.village_title";
    case TextComponent::scenario_introduction_1:return "scenario.introduction_1";
    case TextComponent::scenario_introduction_2:return "scenario.introduction_2";
    case TextComponent::scenario_introduction_3:return "scenario.introduction_3";
    case TextComponent::scenario_introduction_4:return "scenario.introduction_4";
    case TextComponent::scenario_press_key:return "scenario.press_key";
    case TextComponent::scenario_village_departure_1:return "scenario.village_departure_1";
    case TextComponent::scenario_village_departure_2:return "scenario.village_departure_2";
    case TextComponent::scenario_village_departure_3:return "scenario.village_departure_3";
    case TextComponent::scenario_village_traders_1:return "scenario.village_traders_1";
    case TextComponent::scenario_village_traders_2:return "scenario.village_traders_2";
    case TextComponent::scenario_village_traders_3:return "scenario.village_traders_3";
    case TextComponent::scenario_village_arrival_1:return "scenario.village_arrival_1";
    case TextComponent::scenario_village_arrival_2:return "scenario.village_arrival_2";
    case TextComponent::scenario_village_arrival_3:return "scenario.village_arrival_3";
    case TextComponent::scenario_village_arrival_4:return "scenario.village_arrival_4";
    case TextComponent::scenario_village_advice_1:return "scenario.village_advice_1";
    case TextComponent::scenario_village_advice_2:return "scenario.village_advice_2";
    case TextComponent::scenario_village_advice_3:return "scenario.village_advice_3";
    case TextComponent::profile_heading:return "profile.heading";
    case TextComponent::profile_culture_title:return "profile.culture_title";
    case TextComponent::profile_sex_title:return "profile.sex_title";
    case TextComponent::profile_season_title:return "profile.season_title";
    case TextComponent::profile_season_spring:return "profile.season_spring";
    case TextComponent::profile_season_summer:return "profile.season_summer";
    case TextComponent::profile_season_autumn:return "profile.season_autumn";
    case TextComponent::profile_season_winter:return "profile.season_winter";
    case TextComponent::profile_season_help:return "profile.season_help";
    case TextComponent::profile_portrait_help:return "profile.portrait_help";
    case TextComponent::profile_start_age:return "profile.start_age";
    case TextComponent::profile_appearance:return "profile.appearance";
    case TextComponent::profile_personality:return "profile.personality";
    case TextComponent::profile_physical:return "profile.physical";
    case TextComponent::profile_physique:return "profile.physique";
    case TextComponent::profile_strength:return "profile.strength";
    case TextComponent::profile_endurance:return "profile.endurance";
    case TextComponent::profile_dexterity:return "profile.dexterity";
    case TextComponent::profile_agility:return "profile.agility";
    case TextComponent::profile_speed:return "profile.speed";
    case TextComponent::profile_eyesight:return "profile.eyesight";
    case TextComponent::profile_hearing:return "profile.hearing";
    case TextComponent::profile_smell_taste:return "profile.smell_taste";
    case TextComponent::profile_touch:return "profile.touch";
    case TextComponent::profile_intelligence:return "profile.intelligence";
    case TextComponent::profile_will:return "profile.will";
    case TextComponent::profile_height:return "profile.height";
    case TextComponent::profile_weight:return "profile.weight";
    case TextComponent::profile_measurement:return nullptr; // Native unit suffix is dispatched by invoke.
    case TextComponent::profile_confirm_background:return "profile.confirm_background";
    case TextComponent::profile_confirm_attributes:return "profile.confirm_attributes";
    case TextComponent::profile_continue:return "profile.continue";
    case TextComponent::profile_reroll:return "profile.reroll";
    case TextComponent::profile_attributes_ready:return "profile.attributes_ready";
    case TextComponent::profile_attributes_press_key:return "profile.attributes_press_key";
    case TextComponent::profile_name_title:return "profile.name_title";
    case TextComponent::profile_random:return "profile.random";
    case TextComponent::profile_cultures:return "profile.cultures";
    case TextComponent::profile_back:return "profile.back";
    case TextComponent::profile_male:return "profile.male";
    case TextComponent::profile_female:return "profile.female";
    case TextComponent::profile_name_help:return "profile.name_help_utf8";
    case TextComponent::profile_name_help_repeat:return "profile.name_help_repeat_utf8";
    case TextComponent::profile_sex_help:return "profile.sex_help";
    case TextComponent::profile_name_too_short:return "profile.name_too_short";
    case TextComponent::profile_name_invalid:return "profile.name_invalid";
    case TextComponent::profile_name_exists:return "profile.name_exists";
    case TextComponent::profile_culture_0:return "profile.culture_0";
    case TextComponent::profile_culture_1:return "profile.culture_1";
    case TextComponent::profile_culture_2:return "profile.culture_2";
    case TextComponent::profile_culture_3:return "profile.culture_3";
    case TextComponent::profile_culture_4:return "profile.culture_4";
    case TextComponent::profile_culture_5:return "profile.culture_5";
    case TextComponent::profile_culture_6:return "profile.culture_6";
    case TextComponent::profile_culture_7:return "profile.culture_7";
    case TextComponent::profile_culture_8:return "profile.culture_8";
    case TextComponent::profile_culture_9:return "profile.culture_9";
    case TextComponent::setup_title:return "setup.title";
    case TextComponent::setup_fullscreen:return "setup.fullscreen";
    case TextComponent::setup_logical_resize:return "setup.logical_resize";
    case TextComponent::setup_audio:return "setup.audio";
    case TextComponent::setup_volume:return "setup.volume";
    case TextComponent::setup_background_music:return "setup.background_music";
    case TextComponent::setup_traditional_movement:return "setup.traditional_movement";
    case TextComponent::setup_auto_enter_homestead:return "setup.auto_enter_homestead";
    case TextComponent::setup_map_lighting:return "setup.map_lighting";
    case TextComponent::setup_night_brightness:return "setup.night_brightness";
    case TextComponent::setup_units:return "setup.units";
    case TextComponent::setup_right_alt_hotkeys:return "setup.right_alt_hotkeys";
    case TextComponent::setup_map_grid:return "setup.map_grid";
    case TextComponent::setup_old_hardware_mode:return "setup.old_hardware_mode";
    case TextComponent::setup_mobile_controller:return "setup.mobile_controller";
    case TextComponent::setup_logical_resize_help:return "setup.logical_resize_help";
    case TextComponent::setup_video_restart_help:return "setup.video_restart_help";
    case TextComponent::setup_traditional_movement_help:return "setup.traditional_movement_help";
    case TextComponent::setup_auto_enter_homestead_help:return "setup.auto_enter_homestead_help";
    case TextComponent::setup_map_lighting_help:return "setup.map_lighting_help";
    case TextComponent::setup_night_brightness_help:return "setup.night_brightness_help";
    case TextComponent::setup_units_help:return "setup.units_help";
    case TextComponent::setup_right_alt_hotkeys_help:return "setup.right_alt_hotkeys_help";
    case TextComponent::setup_map_grid_help:return "setup.map_grid_help";
    case TextComponent::setup_old_hardware_mode_help:return "setup.old_hardware_mode_help";
    case TextComponent::setup_old_hardware_software_help:return "setup.old_hardware_software_help";
    case TextComponent::setup_old_hardware_restart_help:return "setup.old_hardware_restart_help";
    case TextComponent::setup_mobile_controller_help:return "setup.mobile_controller_help";
    case TextComponent::setup_controls_help:return "setup.controls_help";
    case TextComponent::setup_config_help:return "setup.config_help";
    case TextComponent::setup_exit:return "setup.exit";
    case TextComponent::ancestors_title:return "ancestors.title";
    case TextComponent::ancestors_empty:return "ancestors.empty";
    case TextComponent::ancestors_order_label:return "ancestors.order_label";
    case TextComponent::ancestors_order_played:return "ancestors.order_played";
    case TextComponent::ancestors_order_lived:return "ancestors.order_lived";
    case TextComponent::ancestors_order_journeyed:return "ancestors.order_journeyed";
    case TextComponent::ancestors_exit:return "ancestors.exit";
    case TextComponent::ancestors_previous_page:return "ancestors.previous_page";
    case TextComponent::ancestors_next_page:return "ancestors.next_page";
    case TextComponent::ancestors_select_hint:return "ancestors.select_hint";
    case TextComponent::ancestors_page:return "ancestors.page";
    case TextComponent::ancestors_lived:return "ancestors.lived";
    case TextComponent::ancestors_journeyed:return "ancestors.journeyed";
    case TextComponent::startup_loading:return "startup.loading";
    case TextComponent::startup_sound_init:return "startup.sound_init";
    case TextComponent::startup_audio_device_failed:return "startup.audio_device_failed";
    case TextComponent::startup_intro:return "startup.intro";
    case TextComponent::startup_audio:return "startup.audio";
    case TextComponent::startup_audio_failed:return "startup.audio_failed";
    case TextComponent::intro_north:return "intro.north";
    case TextComponent::intro_roleplaying:return "intro.roleplaying";
    case TextComponent::intro_story_0:return "intro.myth_1";
    case TextComponent::intro_story_1:return "intro.myth_2";
    case TextComponent::intro_story_2:return "intro.myth_3";
    case TextComponent::intro_story_3:return "intro.myth_4";
    case TextComponent::intro_story_4:return "intro.myth_5";
    case TextComponent::intro_story_5:return "intro.myth_6";
    case TextComponent::intro_story_6:return "intro.myth_7";
    case TextComponent::intro_story_7:return "intro.myth_8";
    case TextComponent::intro_story_8:return "intro.myth_9";
    case TextComponent::intro_story_9:return "intro.myth_10";
    case TextComponent::intro_story_10:return "intro.myth_11";
    case TextComponent::culture_text:return nullptr; // Source-keyed culture consumer is dispatched by invoke.
    case TextComponent::spells_text:return nullptr; // Native spell ID/display consumer is dispatched by invoke.
    case TextComponent::skills_text:return nullptr; // Native skill display identity is dispatched by invoke.
    case TextComponent::world_generation_text:return nullptr; // Native world-generation display consumer.
    case TextComponent::scenario_selection_text:return nullptr; // Native RNDCAMP display consumer.
    case TextComponent::scenario_confirmation_text:return nullptr; // Native story confirmation display.
    case TextComponent::game_course_text:return nullptr; // Native game-course display calls.
    }
    return nullptr;
}
bool is_setup_value(TextComponent component) {
    return component>=TextComponent::setup_fullscreen && component<=TextComponent::setup_mobile_controller;
}
bool has_value(TextComponent component) {
    return component==TextComponent::version || component==TextComponent::translation_version ||
           component==TextComponent::copyright || component==TextComponent::about_version ||
           component==TextComponent::about_copyright ||
           component==TextComponent::ancestors_page || component==TextComponent::ancestors_lived ||
           component==TextComponent::ancestors_journeyed ||
           component==TextComponent::profile_start_age ||
           component==TextComponent::creation_complete_enter ||
           component==TextComponent::startup_audio || component==TextComponent::startup_audio_failed ||
           is_setup_value(component);
}
Status UWCN_CALL initialize(const HostApi* host) {
    if(!host || host->abi!=kHostAbi || host->size!=sizeof(HostApi)) return Status::invalid;
    host_api=host;
    // Check the complete component vocabulary before making this generation visible.
    for(auto component:{TextComponent::load_character,TextComponent::create_character,TextComponent::setup,
                       TextComponent::ancestors,TextComponent::about,TextComponent::credits,TextComponent::quit,
                       TextComponent::bonus_material,TextComponent::version,TextComponent::production,
                       TextComponent::copyright,TextComponent::authors,
                       TextComponent::about_title,TextComponent::about_version,TextComponent::about_copyright,
                       TextComponent::about_publisher,TextComponent::about_release_notes,
                       TextComponent::about_install_label,TextComponent::about_press_key,
                       TextComponent::farewell_title,TextComponent::farewell_tree,TextComponent::farewell_river,
                       TextComponent::farewell_fish,TextComponent::farewell_money,TextComponent::farewell_source,
                       TextComponent::farewell_dedication,TextComponent::farewell_earth,TextComponent::farewell_spirit,
                       TextComponent::farewell_courage,TextComponent::farewell_press_key,
                       TextComponent::creation_complete_title,TextComponent::creation_complete_enter,
                       TextComponent::creation_complete_proverb,TextComponent::creation_complete_source,
                       TextComponent::creation_complete_press_key,
                       TextComponent::credits_title,TextComponent::credits_introduction_1,
                       TextComponent::credits_introduction_2,TextComponent::credits_alexander,
                       TextComponent::credits_andrew,TextComponent::credits_artemis,TextComponent::credits_artemiy,
                       TextComponent::credits_brian,TextComponent::credits_flap,TextComponent::credits_hamsolovski,
                       TextComponent::credits_jeremy,TextComponent::credits_kerri,TextComponent::credits_kuu,
                       TextComponent::credits_lani,TextComponent::credits_paulo,TextComponent::credits_plotinus,
                       TextComponent::credits_rain,TextComponent::credits_scott,TextComponent::credits_shawn,
                       TextComponent::credits_tommy,TextComponent::credits_wickerman,
                       TextComponent::credits_countrymen_1,TextComponent::credits_countrymen_2,
                       TextComponent::credits_photo_contributors,TextComponent::credits_veterans,
                       TextComponent::credits_press_key,
                       TextComponent::character_creation_title,TextComponent::character_creation_quick,
                       TextComponent::character_creation_custom,TextComponent::character_creation_easy,
                       TextComponent::character_creation_too_easy,TextComponent::character_creation_exit,
                       TextComponent::load_saved_title,TextComponent::load_saved_empty,TextComponent::load_saved_press_key,
                       TextComponent::profile_heading,TextComponent::profile_culture_title,TextComponent::profile_sex_title,
                       TextComponent::profile_name_title,TextComponent::profile_random,TextComponent::profile_cultures,
                       TextComponent::profile_back,TextComponent::profile_male,TextComponent::profile_female,
                       TextComponent::profile_name_help,TextComponent::profile_name_help_repeat,TextComponent::profile_sex_help,
                       TextComponent::profile_name_too_short,TextComponent::profile_name_invalid,TextComponent::profile_name_exists,
                       TextComponent::profile_culture_0,TextComponent::profile_culture_1,
                       TextComponent::profile_culture_2,TextComponent::profile_culture_3,TextComponent::profile_culture_4,
                       TextComponent::profile_culture_5,TextComponent::profile_culture_6,TextComponent::profile_culture_7,
                       TextComponent::profile_culture_8,TextComponent::profile_culture_9,
                       TextComponent::profile_start_age,TextComponent::profile_appearance,
                       TextComponent::profile_personality,TextComponent::profile_physical,TextComponent::profile_physique,
                       TextComponent::profile_strength,TextComponent::profile_endurance,TextComponent::profile_dexterity,
                       TextComponent::profile_agility,TextComponent::profile_speed,TextComponent::profile_eyesight,
                       TextComponent::profile_hearing,TextComponent::profile_smell_taste,TextComponent::profile_touch,
                       TextComponent::profile_intelligence,TextComponent::profile_will,
                       TextComponent::profile_height,TextComponent::profile_weight,
                       TextComponent::profile_confirm_background,TextComponent::profile_confirm_attributes,
                       TextComponent::profile_continue,TextComponent::profile_reroll,
                       TextComponent::profile_attributes_ready,TextComponent::profile_attributes_press_key,
                       TextComponent::setup_title,TextComponent::setup_fullscreen,TextComponent::setup_logical_resize,
                       TextComponent::setup_audio,TextComponent::setup_volume,TextComponent::setup_background_music,
                       TextComponent::setup_traditional_movement,TextComponent::setup_auto_enter_homestead,
                       TextComponent::setup_map_lighting,TextComponent::setup_night_brightness,TextComponent::setup_units,
                       TextComponent::setup_right_alt_hotkeys,TextComponent::setup_map_grid,
                       TextComponent::setup_old_hardware_mode,TextComponent::setup_mobile_controller,
                       TextComponent::setup_logical_resize_help,TextComponent::setup_video_restart_help,
                       TextComponent::setup_traditional_movement_help,TextComponent::setup_auto_enter_homestead_help,
                       TextComponent::setup_map_lighting_help,TextComponent::setup_night_brightness_help,
                       TextComponent::setup_units_help,TextComponent::setup_right_alt_hotkeys_help,
                       TextComponent::setup_map_grid_help,TextComponent::setup_old_hardware_mode_help,
                       TextComponent::setup_old_hardware_software_help,TextComponent::setup_old_hardware_restart_help,
                       TextComponent::setup_mobile_controller_help,TextComponent::setup_controls_help,
                       TextComponent::setup_config_help,TextComponent::setup_exit,
                       TextComponent::ancestors_title,TextComponent::ancestors_empty,
                       TextComponent::ancestors_order_label,TextComponent::ancestors_order_played,
                       TextComponent::ancestors_order_lived,TextComponent::ancestors_order_journeyed,
                       TextComponent::ancestors_exit,TextComponent::ancestors_previous_page,
                       TextComponent::ancestors_next_page,TextComponent::ancestors_select_hint,
                       TextComponent::ancestors_page,TextComponent::ancestors_lived,TextComponent::ancestors_journeyed,
                       TextComponent::translation_credit,TextComponent::translation_version,TextComponent::startup_loading,
                       TextComponent::startup_sound_init,TextComponent::startup_audio_device_failed,
                       TextComponent::startup_intro,TextComponent::startup_audio,TextComponent::startup_audio_failed,
                       TextComponent::intro_north,TextComponent::intro_roleplaying,
                       TextComponent::intro_story_0,TextComponent::intro_story_1,TextComponent::intro_story_2,
                       TextComponent::intro_story_3,TextComponent::intro_story_4,TextComponent::intro_story_5,
                       TextComponent::intro_story_6,TextComponent::intro_story_7,TextComponent::intro_story_8,
                       TextComponent::intro_story_9,TextComponent::intro_story_10,
                       TextComponent::scenario_village_title,
                       TextComponent::scenario_introduction_1,TextComponent::scenario_introduction_2,
                       TextComponent::scenario_introduction_3,TextComponent::scenario_introduction_4,
                       TextComponent::scenario_press_key,
                       TextComponent::scenario_village_departure_1,TextComponent::scenario_village_departure_2,
                       TextComponent::scenario_village_departure_3,TextComponent::scenario_village_traders_1,
                       TextComponent::scenario_village_traders_2,TextComponent::scenario_village_traders_3,
                       TextComponent::scenario_village_arrival_1,TextComponent::scenario_village_arrival_2,
                       TextComponent::scenario_village_arrival_3,TextComponent::scenario_village_arrival_4,
                       TextComponent::scenario_village_advice_1,TextComponent::scenario_village_advice_2,
                       TextComponent::scenario_village_advice_3}) {
        CatalogRequest request{key(component)};
        std::string value;
        const auto status=invoke_text(host,ModuleId::catalog,catalog_op::lookup,&request,sizeof(request),value);
        if(status!=Status::ok) return status;
        const bool dynamic=has_value(component);
        const auto pos=value.find("{value}");
        if(dynamic && (pos==std::string::npos || value.find("{value}",pos+7)!=std::string::npos)) return Status::invalid;
        if(!dynamic && pos!=std::string::npos) return Status::invalid;
    }
    return Status::ok;
}
Status UWCN_CALL invoke(u32 op,const void* input,u32 bytes,void* output,u32* capacity) {
    if(op==kModuleDependenciesChanged) {
        if(!input || bytes!=sizeof(u32)) return Status::invalid;
        return (*static_cast<const u32*>(input)&1u) ? initialize(host_api) : Status::ok;
    }
    if(op!=text_op::translate || !input || bytes!=sizeof(TextRequest)) return Status::invalid;
    const auto& request=*static_cast<const TextRequest*>(input);
    if(request.component==TextComponent::profile_measurement) {
        // UnitString_Length/Weight already selected the units, precision and
        // number. Translate only their suffix at the profile's title consumer.
        const std::string original=request.original;
        const auto separator=original.find(' ');
        const auto name="profile.unit."+original.substr(separator+1);
        const CatalogRequest lookup{name.c_str()};
        std::string unit;
        const auto status=invoke_text(host_api,ModuleId::catalog,catalog_op::lookup,&lookup,sizeof(lookup),unit);
        if(status!=Status::ok) return status;
        return copy_text(original.substr(0,separator+1)+unit,output,capacity);
    }
    if(request.component==TextComponent::culture_text) {
        const std::string name=std::string("culture.")+request.value;
        const CatalogRequest lookup{name.c_str()};
        return host_api->invoke(ModuleId::catalog,catalog_op::lookup,&lookup,sizeof(lookup),output,capacity);
    }
    if(request.component==TextComponent::spells_text) {
        const std::string name=std::string("spells.")+request.value;
        const CatalogRequest lookup{name.c_str()};
        return host_api->invoke(ModuleId::catalog,catalog_op::lookup,&lookup,sizeof(lookup),output,capacity);
    }
    if(request.component==TextComponent::skills_text) {
        const std::string name=std::string("skills.")+request.value;
        const CatalogRequest lookup{name.c_str()};
        return host_api->invoke(ModuleId::catalog,catalog_op::lookup,&lookup,sizeof(lookup),output,capacity);
    }
    if(request.component==TextComponent::world_generation_text) {
        const std::string name=std::string("world_generation.")+request.value;
        const CatalogRequest lookup{name.c_str()};
        return host_api->invoke(ModuleId::catalog,catalog_op::lookup,&lookup,sizeof(lookup),output,capacity);
    }
    if(request.component==TextComponent::scenario_selection_text) {
        const std::string name=std::string("scenario.select.")+request.value;
        const CatalogRequest lookup{name.c_str()};
        return host_api->invoke(ModuleId::catalog,catalog_op::lookup,&lookup,sizeof(lookup),output,capacity);
    }
    if(request.component==TextComponent::scenario_confirmation_text) {
        const std::string name=std::string("scenario.confirm.")+request.value;
        const CatalogRequest lookup{name.c_str()};
        return host_api->invoke(ModuleId::catalog,catalog_op::lookup,&lookup,sizeof(lookup),output,capacity);
    }
    if(request.component==TextComponent::game_course_text) {
        const std::string name=std::string("game_course.")+request.value;
        const CatalogRequest lookup{name.c_str()};
        return host_api->invoke(ModuleId::catalog,catalog_op::lookup,&lookup,sizeof(lookup),output,capacity);
    }
    if(request.component>=TextComponent::hud_label && request.component<=TextComponent::hud_speed)
        return translate_hud(host_api,request,output,capacity);
    if(request.component>=TextComponent::world_place_gloss && request.component<=TextComponent::world_time)
        return translate_world_hud(host_api,request,output,capacity);
    const char* name=key(request.component);
    if(!name) return Status::invalid;
    const CatalogRequest lookup{name};
    std::string text;
    const auto status=invoke_text(host_api,ModuleId::catalog,catalog_op::lookup,&lookup,sizeof(lookup),text);
    if(status!=Status::ok) return status;
    if(has_value(request.component)) {
        if(!request.value) return Status::invalid;
        if(request.component==TextComponent::startup_audio) {
            const std::string resource_key=std::string("startup.resource.")+request.value;
            const CatalogRequest resource_lookup{resource_key.c_str()};
            std::string resource_name;
            const auto resource_status=invoke_text(host_api,ModuleId::catalog,catalog_op::lookup,
                                                  &resource_lookup,sizeof(resource_lookup),resource_name);
            if(resource_status!=Status::ok) return resource_status;
            text.replace(text.find("{value}"),7,resource_name);
        } else if(is_setup_value(request.component)) {
            std::string value=request.value;
            const bool number=request.component==TextComponent::setup_volume ||
                              request.component==TextComponent::setup_night_brightness;
            const bool brightness_label=request.component==TextComponent::setup_night_brightness &&
                                        (value=="0 (default)" || value=="60 (maximum)");
            if(!number || brightness_label) {
                const std::string value_key=std::string("setup.value.")+value;
                const CatalogRequest value_lookup{value_key.c_str()};
                const auto value_status=invoke_text(host_api,ModuleId::catalog,catalog_op::lookup,
                                                   &value_lookup,sizeof(value_lookup),value);
                if(value_status!=Status::ok) return value_status;
            }
            text.replace(text.find("{value}"),7,value);
        } else {
            text.replace(text.find("{value}"),7,request.value);
        }
    }
    return copy_text(text,output,capacity);
}
void UWCN_CALL shutdown() { host_api=nullptr; }
const ModuleApi api={sizeof(ModuleApi),kHostAbi,ModuleId::semantic,initialize,invoke,empty_save,empty_restore,shutdown};
}
UWCN_EXPORT const uwcn::ModuleDescriptor uwcn_module_descriptor={uwcn::kDescriptorMagic,uwcn::kHostAbi,2,uwcn::kModuleMachine,1};
UWCN_EXPORT const uwcn::ModuleApi* UWCN_CALL uwcn_get_module_api() { return &api; }
