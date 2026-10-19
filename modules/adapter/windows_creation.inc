// Windows 3.89 PE display boundaries. All addresses are PE RVAs, established
// from urw.exe e0b15bbb... by read-only disassembly and decompilation.
// Native functions continue to own layout, input, cached pixels and selection.
enum CreationHook : u32 {
    creation_text_first=0xA000,creation_preview=0xA100,creation_select_name,
    creation_select_summary,creation_select_help_1,creation_select_help_2,
    creation_select_title,creation_course_title,creation_course_help_last,
    creation_course_name_wild,creation_story_title,creation_story_record,
    creation_story_paragraph,creation_paragraph_first=0xA130,
    creation_word_space=0xA150,creation_button_highlight_1,creation_button_highlight_2,creation_button_prefix_width,
    creation_select_exit,creation_confirmation_entry,creation_confirmation_exit,
    creation_course_entry,creation_course_exit,creation_footer_rng,
    creation_world_entry,creation_world_after_title,creation_world_after_map,
    creation_world_exit,creation_world_format_first=0xA170,
    creation_world_number_first=0xA180,creation_footer_first=0xA190,
    creation_complete_enter=0xA1A0,creation_complete_entry,creation_complete_exit
};
enum class CreationKind { text,panel,words,button,plain_button,center,format };
struct CreationTextCall {
    u32 site,target,count,argument;
    TextComponent component;
    const char* key;
    CreationKind kind;
};
constexpr CreationTextCall creation_text_calls[]{
    {0x1071D,0x10E5A0,3,0,TextComponent::scenario_confirmation_text,"question",CreationKind::text},
    {0x10750,0xCFAF0,2,1,TextComponent::scenario_confirmation_text,"yes",CreationKind::button},
    {0x10764,0xCFAF0,2,1,TextComponent::scenario_confirmation_text,"no",CreationKind::button},
    {0x10DB7,0x116270,5,2,TextComponent::game_course_text,"title",CreationKind::panel},
    {0x10DFB,0x162300,0,0,TextComponent::game_course_text,"free.1",CreationKind::words},
    {0x10E07,0x162300,0,0,TextComponent::game_course_text,"free.2",CreationKind::words},
    {0x10E13,0x162300,0,0,TextComponent::game_course_text,"free.3",CreationKind::words},
    {0x10E6E,0x162300,0,0,TextComponent::game_course_text,"wild.1",CreationKind::words},
    {0x10E7A,0x162300,0,0,TextComponent::game_course_text,"wild.2",CreationKind::words},
    {0x10E86,0x162300,0,0,TextComponent::game_course_text,"wild.3",CreationKind::words},
    {0x10EED,0x162300,0,0,TextComponent::game_course_text,"advanced.1",CreationKind::words},
    {0x10EF9,0x162300,0,0,TextComponent::game_course_text,"advanced.2",CreationKind::words},
    {0x10F05,0x162300,0,0,TextComponent::game_course_text,"advanced.3",CreationKind::words},
    {0x10F9D,0xCFAF0,2,1,TextComponent::game_course_text,"name.free",CreationKind::button},
    {0x11066,0xCFAF0,2,1,TextComponent::game_course_text,"name.advanced",CreationKind::button},
    {0x10FD9,0x10E5A0,3,0,TextComponent::game_course_text,"completed.wild",CreationKind::text},
    {0x11041,0x10E5A0,3,0,TextComponent::game_course_text,"completed.advanced",CreationKind::text},
    {0x11091,0x162300,0,0,TextComponent::game_course_text,"help.1",CreationKind::words},
    {0x1109D,0x162300,0,0,TextComponent::game_course_text,"help.2",CreationKind::words},
    {0x60BF5,0x116270,5,2,TextComponent::world_generation_text,"title",CreationKind::panel},
    {0x5F713,0x116270,5,2,TextComponent::world_generation_text,"title",CreationKind::panel},
    {0x5FCEF,0x116270,5,2,TextComponent::world_generation_text,"title",CreationKind::panel},
    {0x6051B,0x10E5A0,3,0,TextComponent::world_generation_text,"scale",CreationKind::text},
    {0x60D32,0xCFAF0,2,1,TextComponent::world_generation_text,"zoom_in",CreationKind::button},
    {0x60D49,0xCFAF0,2,1,TextComponent::world_generation_text,"zoom_out",CreationKind::button},
    {0x60E0E,0xCFAF0,2,1,TextComponent::world_generation_text,"regions",CreationKind::button},
    {0x60E27,0xCFAF0,2,1,TextComponent::world_generation_text,"indicators",CreationKind::button},
    {0x60E40,0xCFAF0,2,1,TextComponent::world_generation_text,"home_culture",CreationKind::button},
    {0x60E59,0xCFAF0,2,1,TextComponent::world_generation_text,"start_location",CreationKind::button},
    {0x60E72,0xCFAF0,2,1,TextComponent::world_generation_text,"new_world",CreationKind::button},
    {0x60E8B,0xCFAF0,2,1,TextComponent::world_generation_text,"enter",CreationKind::button},
    {0xE6EEC,0x116270,5,2,TextComponent::farewell_title,nullptr,CreationKind::panel},
    {0xE7020,0x10E5A0,3,0,TextComponent::farewell_tree,nullptr,CreationKind::text},
    {0xE703A,0x10E5A0,3,0,TextComponent::farewell_river,nullptr,CreationKind::text},
    {0xE7057,0x10E5A0,3,0,TextComponent::farewell_fish,nullptr,CreationKind::text},
    {0xE7074,0x10E5A0,3,0,TextComponent::farewell_money,nullptr,CreationKind::text},
    {0xE7091,0x10E5A0,3,0,TextComponent::farewell_source,nullptr,CreationKind::text},
    {0xE70C9,0x10E910,4,1,TextComponent::farewell_dedication,nullptr,CreationKind::center},
    {0xE70FC,0x10E5A0,3,0,TextComponent::farewell_earth,nullptr,CreationKind::text},
    {0xE712F,0x10E5A0,3,0,TextComponent::farewell_spirit,nullptr,CreationKind::text},
    {0xE7162,0x10E5A0,3,0,TextComponent::farewell_courage,nullptr,CreationKind::text},
    {0xE7179,0x114680,1,0,TextComponent::farewell_press_key,nullptr,CreationKind::plain_button},
    {0x131D7,0x10E910,4,1,TextComponent::creation_complete_title,nullptr,CreationKind::center},
    {0x132EB,0x10E910,4,1,TextComponent::creation_complete_proverb,nullptr,CreationKind::center},
    {0x13320,0x10E910,4,1,TextComponent::creation_complete_source,nullptr,CreationKind::center},
    {0x13334,0x114680,1,0,TextComponent::creation_complete_press_key,nullptr,CreationKind::plain_button}
};
constexpr u32 creation_paragraph_calls[]{0x10B0B,0x10E34,0x10EA7,0x10F24};
constexpr const char* creation_story_titles[]{
    "Scenario: THE UNREAL WORLD","Scenario: THE VILLAGE","Scenario: RUNAWAY SLAVE",
    "Scenario: UNFORTUNATE HUNTING TRIP","Scenario: LONELY SETTLER",
    "Scenario: HURT, HELPLESS, AND AFRAID","Scenario: TRAPS AND TRAPPING",
    "Scenario: I WANT TO BE A FISHERMAN","Scenario: ABANDONED TRAP-FENCE",
    "Scenario: ABANDONED CAMP","Scenario: AGRICULTURE","Scenario: THERE BE ROBBERS!",
    "Scenario: NOT ALL WHO WANDER ARE LOST"
};
struct CreationStory { u32 id,record,current_record; };
Status creation_lend(const NativeEvent& e,TextComponent component,const char* key,
                     u32& destination,CreationKind kind) {
    const auto* original=ptr<char>(destination);
    const char* display=original;
    if(kind==CreationKind::button) {
        const auto* separator=std::strchr(original,'.');
        display=separator ? separator+1 : original+3;
    }
    std::vector<char> encoded;
    auto status=translate(component,display,key,encoded);
    if(status!=Status::ok) return status;
    if(kind==CreationKind::words && chinese_enabled) {
        const auto words=native_paragraph_words(encoded.data());
        encoded.assign(words.begin(),words.end());encoded.push_back(0);
    }
    if(kind==CreationKind::button) {
        native_component_binding::note_prefix(e,std::string(original,display).c_str());
        encoded.insert(encoded.begin(),original,display);
    }
    const auto scope=kind==CreationKind::panel ? Scope::scenario_panel :
        (kind==CreationKind::words || kind==CreationKind::format) ? Scope::allocation : kind==CreationKind::center ? Scope::hud_centered :
        kind==CreationKind::button ? Scope::creation_button : kind==CreationKind::plain_button ? Scope::plain_button : Scope::text;
    const auto outline=kind==CreationKind::text ? e.arguments[2] : kind==CreationKind::center ? e.arguments[3] :
        kind==CreationKind::button ? *at<u32>(0x5F54A9C) : 0;
    return lend_text(e,encoded,destination,scope,outline);
}
Status creation_complete_identity(const NativeEvent& e) {
    // The native producer formats the original identity for this display.
    // The semantic value keeps its real culture ID and unchanged Unicode name.
    std::string original,name;
    auto status=decode_parser_original(ptr<char>(e.arguments[1]),original);
    if(status!=Status::ok) return status;
    status=decode_parser_original(at<char>(0xA32A6E8),name);
    if(status!=Status::ok) return status;
    const auto value=std::to_string(*at<unsigned char>(0xA32A6F5))+"|"+name;
    std::vector<char> encoded;
    status=translate(TextComponent::creation_complete_enter,original.c_str(),value.c_str(),encoded);
    if(status!=Status::ok) return status;
    return lend_text(e,encoded,e.arguments[1],Scope::hud_centered,e.arguments[3]);
}
Status dispatch_windows_creation(const NativeEvent& e,DispatchResult& result,bool& handled) {
    handled=true;
    if(e.phase==NativePhase::after) {
        if(e.id==about_button_character && in(Scope::creation_button)) return native_button::character(e);
        handled=false;return Status::ok;
    }
    if(e.id>=creation_text_first && e.id<creation_text_first+std::size(creation_text_calls)) {
        const auto& field=creation_text_calls[e.id-creation_text_first];

        auto& destination=field.kind==CreationKind::words ? e.frame->edx : e.arguments[field.argument];
        return creation_lend(e,field.component,field.key,destination,field.kind);
    }
    if(e.id>=creation_paragraph_first && e.id<creation_paragraph_first+std::size(creation_paragraph_calls)) {
        begin(e,Scope::paragraph,e.arguments[3]);
        begin(e,Scope::creation_paragraph,e.arguments[3]);return Status::ok;
    }
    if(e.id>=creation_footer_first && e.id<creation_footer_first+2) {
        begin(e,Scope::profile_footer);return Status::ok;
    }
    switch(e.id) {
    case creation_complete_enter:return creation_complete_identity(e);
    case scenario_story_scope: case creation_preview: {

        auto* story=static_cast<CreationStory*>(host->allocate(sizeof(CreationStory)));
        *story={};active.push_back({e.token,Scope::scenario_story,address(story),0,0,0,0});return Status::ok;
    }
    case scenario_panel: {
        const auto story=std::find_if(active.rbegin(),active.rend(),[](const Active& item){return item.kind==Scope::scenario_story;});
        auto* source=ptr<CreationStory>(story->allocation);
        const auto* title=ptr<char>(e.arguments[2]);
        const auto identity=std::find_if(std::begin(creation_story_titles),std::end(creation_story_titles),
            [title](const char* candidate){return std::strcmp(title,candidate)==0;});
        source->id=static_cast<u32>(identity-std::begin(creation_story_titles));
        source->record=0;
        const auto key="title."+std::to_string(source->id);
        return creation_lend(e,TextComponent::scenario_confirmation_text,key.c_str(),e.arguments[2],CreationKind::panel);
    }
    case scenario_body_format: {
        const auto* original=ptr<char>(e.arguments[2]);
        const auto story=std::find_if(active.rbegin(),active.rend(),[](const Active& item){return item.kind==Scope::scenario_story;});
        auto* source=ptr<CreationStory>(story->allocation);
        source->current_record=*original ? 1u : 0u;
        if(!source->current_record) return Status::ok; // original empty record and terminal EOF
        const auto key="story."+std::to_string(source->id)+"."+std::to_string(source->record++);
        const auto status=creation_lend(e,TextComponent::scenario_confirmation_text,key.c_str(),e.arguments[2],CreationKind::words);
        if(status!=Status::ok) return status;
        const auto* pattern=ptr<char>(e.arguments[1]);
        native_component_binding::note_prefix(e,std::string(pattern,
            static_cast<std::size_t>(std::strstr(pattern,"%s")-pattern)).c_str());
        return Status::ok;
    }
    case scenario_body_append: {
        const auto story=std::find_if(active.rbegin(),active.rend(),[](const Active& item){return item.kind==Scope::scenario_story;});
        if(ptr<CreationStory>(story->allocation)->current_record)
            native_component_binding::note_source_for_consumer(e,TextComponent::scenario_confirmation_text);
        return Status::ok;
    }
    case scenario_body_paragraph:
        begin(e,Scope::paragraph,e.arguments[3]);begin(e,Scope::creation_paragraph,e.arguments[3]);return Status::ok;
    case creation_select_title: case creation_course_title:
        return creation_lend(e,e.id==creation_select_title ? TextComponent::scenario_selection_text : TextComponent::game_course_text,
            "title",e.frame->ecx,CreationKind::panel);
    case creation_select_name: {
        native_component_binding::note_native_record(e,e.frame->ebx);
        const auto key="name."+std::to_string(e.frame->ebx);
        return creation_lend(e,TextComponent::scenario_selection_text,key.c_str(),e.arguments[0],CreationKind::text);
    }
    case creation_select_summary: case creation_select_help_1: case creation_select_help_2: {
        const auto key=e.id==creation_select_summary ? "summary."+std::to_string(e.frame->ebx) :
            std::string(e.id==creation_select_help_1 ? "help.1" : "help.2");
        return creation_lend(e,TextComponent::scenario_selection_text,key.c_str(),e.frame->edx,CreationKind::words);
    }
    case creation_course_help_last:
        return creation_lend(e,TextComponent::game_course_text,
            e.frame->edx==address(at<char>(0x18FFB0)) ? "help.completed" : "help.3",e.frame->edx,CreationKind::words);
    case creation_course_name_wild:
        return creation_lend(e,TextComponent::game_course_text,
            std::strcmp(ptr<char>(e.arguments[1]),"A.TUTORIAL GAME COURSE")==0 ? "name.tutorial" : "name.wild",
            e.arguments[1],CreationKind::button);
    case creation_word_space:
        if(contains_display(ptr<char>(e.frame->ebp-0x404))) result.skip_original=1;
        return Status::ok;
    case setup_exit_width:
        if(in(Scope::creation_button)) {
            render::Metrics measured{};const auto status=metrics(ptr<char>(e.frame->edi),measured);
            if(status!=Status::ok) return status;
            e.frame->eax=static_cast<u32>(measured.logical_width+10);result.skip_original=1;return Status::ok;
        }
        break;
    case creation_button_prefix_width:
        if(contains_display(ptr<char>(e.frame->ebp-0x408))) {
            render::Metrics measured{};const auto status=metrics(ptr<char>(e.frame->ebp-0x408),measured);
            if(status!=Status::ok) return status;
            e.frame->eax=static_cast<u32>(measured.logical_width+10);result.skip_original=1;
        }
        return Status::ok;
    case about_button_width:
        if(in(Scope::creation_button) && !std::strchr(native_button::label(e),'.')) return native_button::width(e,result,metrics);
        break;
    case about_button_advance:
        if(in(Scope::creation_button)) {
            const auto* label=native_button::label(e);
            if(label[e.frame->ebx]=='<' || label[e.frame->ebx]=='>') {
                e.frame->edx=*ptr<u32>(e.frame->ebp-0xA4);++e.frame->ebx;result.skip_original=1;return Status::ok;
            }
            return native_button::advance(e,result,metrics);
        }
        break;
    case about_button_text: case setup_exit_text: case creation_button_highlight_1: case creation_button_highlight_2:
        if(in(Scope::creation_button)) {begin(e,Scope::text,e.arguments[2]);return Status::ok;}
        break;
    default:
        if(e.id>=creation_world_format_first && e.id<creation_world_format_first+2) {
            const auto* key=e.id==creation_world_format_first ? "zoom_format" : "distance_format";
            return creation_lend(e,TextComponent::world_generation_text,key,e.arguments[1],CreationKind::format);
        }
        if(e.id>=creation_world_number_first && e.id<creation_world_number_first+2) {begin(e,Scope::text,e.arguments[2]);return Status::ok;}
        break;
    }
    handled=false;return Status::ok;
}
void append_windows_creation_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(call(creation_complete_enter,0x13264,0x10E910,4));
    auto complete_entry=inline_hook(creation_complete_entry,0x12F96,{0x89,0x0D,0,0,0,0});
    const u32 complete_state=address(at<void>(0x217ABC));
    std::memcpy(complete_entry.expected+2,&complete_state,4);hooks.push_back(complete_entry);
    hooks.push_back(inline_hook(creation_complete_exit,0x13341,{0x33,0xC0,0x0F,0x1F,0x40,0x00}));
    for(u32 i=0;i<std::size(creation_text_calls);++i) {
        const auto& field=creation_text_calls[i];hooks.push_back(call(creation_text_first+i,field.site,field.target,field.count));
    }
    for(u32 i=0;i<std::size(creation_paragraph_calls);++i)
        hooks.push_back(call(creation_paragraph_first+i,creation_paragraph_calls[i],0x10EB40,4));
    hooks.push_back(call(creation_footer_first,0x10B6F,0xF210,0));
    hooks.push_back(call(creation_footer_first+1,0x110B0,0xF210,0));
    hooks.push_back(call(creation_preview,0x10707,0xFB390,0));
    hooks.push_back(call(creation_select_title,0x108E5,0x107F0,0));
    hooks.push_back(call(creation_course_title,0x10D91,0x107F0,0));
    hooks.push_back(call(creation_select_name,0x10A35,0x10E5A0,3));
    hooks.push_back(call(creation_select_summary,0x10AD5,0x162300,0));
    hooks.push_back(call(creation_select_help_1,0x10B5C,0x162300,0));
    hooks.push_back(call(creation_select_help_2,0x10B68,0x162300,0));
    hooks.push_back(call(creation_course_help_last,0x110A9,0x162300,0));
    hooks.push_back(call(creation_course_name_wild,0x11005,0xCFAF0,2));
    hooks.push_back(call(creation_button_highlight_1,0x11492D,0x10E5A0,3));
    hooks.push_back(call(creation_button_highlight_2,0x1149D2,0x10E5A0,3));
    hooks.push_back(inline_hook(creation_button_prefix_width,0xCFC40,{0x8D,0x04,0xCD,0x0A,0,0,0}));
    auto space=inline_hook(creation_word_space,0x10EEDA,{0x66,0xA1,0,0,0,0,0x66,0x89,0x07});
    const u32 native_space=address(at<void>(0x18C8C0));std::memcpy(space.expected+2,&native_space,4);hooks.push_back(space);
    auto select=inline_hook(creation_select_exit,0x10B74,{0x83,0x3D,0,0,0,0,0x01});
    const u32 museum=address(at<void>(0x217ABC));std::memcpy(select.expected+2,&museum,4);hooks.push_back(select);
    hooks.push_back(inline_hook(creation_confirmation_entry,0x105D6,{0x8B,0xD9,0x33,0xD2,0x66,0x0F,0x1F,0x44,0,0}));
    auto confirm=inline_hook(creation_confirmation_exit,0x1076C,{0x83,0x3D,0,0,0,0,0x01});
    std::memcpy(confirm.expected+2,&museum,4);hooks.push_back(confirm);
    auto course=inline_hook(creation_course_entry,0x10D56,{0xB9,0,0,0,0});
    const u32 save_name=address(at<void>(0x18FA68));std::memcpy(course.expected+1,&save_name,4);hooks.push_back(course);
    hooks.push_back(inline_hook(creation_course_exit,0x110BA,{0x66,0x0F,0x1F,0x44,0,0}));
    hooks.push_back(inline_hook(creation_footer_rng,0xF21D,{0x89,0x4D,0xFC,0x33,0xFF}));
    hooks.push_back(inline_hook(creation_world_entry,0x60B73,{0xB9,1,0,0,0}));
    auto after_title=inline_hook(creation_world_after_title,0x60C03,{0xC7,0x05,0,0,0,0,0,0,0,0});
    const u32 title_state=address(at<void>(0x61BBAC8));std::memcpy(after_title.expected+2,&title_state,4);hooks.push_back(after_title);
    auto after_map=inline_hook(creation_world_after_map,0x610FB,{0x83,0x3D,0,0,0,0,0});
    const u32 present_state=address(at<void>(0xA1C1C54));std::memcpy(after_map.expected+2,&present_state,4);hooks.push_back(after_map);
    auto world_exit=inline_hook(creation_world_exit,0x60E93,{0x83,0x3D,0,0,0,0,1});
    std::memcpy(world_exit.expected+2,&museum,4);hooks.push_back(world_exit);
    hooks.push_back(call(creation_world_format_first,0x60491,0x10D0,3));
    hooks.push_back(call(creation_world_format_first+1,0x6055B,0x10D0,3));
    hooks.push_back(call(creation_world_number_first,0x604CC,0x10E5A0,3));
    hooks.push_back(call(creation_world_number_first+1,0x6058E,0x10E5A0,3));
}
