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
struct CreationStory { u32 id,record; };
bool creation_select_pending=true,creation_confirmation_pending=true,creation_course_pending=true;
bool creation_select_redrawing{},creation_confirmation_redrawing{},creation_course_redrawing{};
bool creation_world_pending=true,creation_world_redrawing{};
u32 creation_world_legend{};
bool creation_complete_pending=true,creation_complete_redrawing{};

// Transport delimiters feed the existing 5000 x 130-byte native word table.
// These are character tokens, not display lines; 10EB40 decides every wrap.
void creation_words(std::vector<char>& encoded) {
    std::vector<char> words;
    for(auto* p=reinterpret_cast<const unsigned char*>(encoded.data());*p;) {
        if(*p>=0x80) {
            if(!words.empty() && words.back()!=' ' && words.back()!='>') words.push_back(' ');
            words.push_back(static_cast<char>(*p++));words.push_back(static_cast<char>(*p++));
            words.push_back(' ');
        } else words.push_back(static_cast<char>(*p++));
    }
    words.push_back(0);encoded=std::move(words);
}
Status creation_lend(const NativeEvent& e,TextComponent component,const char* key,
                     u32& destination,CreationKind kind) {
    const auto* original=ptr<char>(destination);
    std::vector<char> encoded;
    auto status=translate(component,original,key,encoded);
    if(status!=Status::ok) return status;
    if(kind==CreationKind::words && chinese_enabled) creation_words(encoded);
    if(kind==CreationKind::button && chinese_enabled) {
        const auto* suffix=std::strchr(original,'.');
        if(suffix) encoded.insert(encoded.begin(),original,suffix+1);
        else encoded.insert(encoded.begin(),original,original+3); // confirmed <Y>/<N>
    }
    const auto scope=kind==CreationKind::panel ? Scope::scenario_panel :
        (kind==CreationKind::words || kind==CreationKind::format) ? Scope::allocation : kind==CreationKind::center ? Scope::hud_centered :
        kind==CreationKind::button ? Scope::creation_button : kind==CreationKind::plain_button ? Scope::plain_button : Scope::text;
    const auto outline=kind==CreationKind::text ? e.arguments[2] : kind==CreationKind::center ? e.arguments[3] :
        kind==CreationKind::button ? *at<u32>(0x5F54A9C) : 0;
    return lend_text(e,encoded,destination,scope,outline);
}
void invalidate_windows_creation() {
    creation_select_pending=creation_confirmation_pending=creation_course_pending=creation_world_pending=true;
    creation_complete_pending=true;
}
Status creation_complete_rebuild() {
    auto status=native_targets::promote();
    if(status!=Status::ok) return status;
    creation_complete_redrawing=true;
    // Keep 12F80's native stack frame; enter only its completed-page drawing.
    // D3CDC returns before input, and 13341 goes straight to the epilogue.
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x12F80)();
    creation_complete_redrawing=false;
    creation_complete_pending=false;
    return Status::ok;
}
Status creation_complete_identity(const NativeEvent& e) {
    std::vector<char> encoded;
    if(!chinese_enabled) {
        const auto status=native_name_input::display(ptr<char>(e.arguments[1]),encoded);
        if(status!=Status::ok) return status;
    } else {
        // 1321E builds Plr.name + Plr.inhabitant only for this display line.
        // Use the same name and the confirmed Plr.culture ID, without writing
        // either the native English identity or its formatted scratch buffer.
        auto status=native_name_input::display(at<char>(0xA32A6E8),encoded);
        if(status!=Status::ok) return status;
        std::vector<char> name,culture,culture_utf8;
        status=codec(layout_op::decode_native,encoded.data(),name);
        if(status!=Status::ok) return status;
        const auto component=static_cast<TextComponent>(static_cast<u32>(TextComponent::profile_culture_0)+
            *at<unsigned char>(0xA32A6F5));
        status=translate(component,at<char>(0xA32A6F6),nullptr,culture);
        if(status!=Status::ok) return status;
        status=codec(layout_op::decode_native,culture.data(),culture_utf8);
        if(status!=Status::ok) return status;
        const auto identity=std::string(name.data())+" "+culture_utf8.data();
        status=translate(TextComponent::creation_complete_enter,ptr<char>(e.arguments[1]),identity.c_str(),encoded);
        if(status!=Status::ok) return status;
    }
    return lend_text(e,encoded,e.arguments[1],Scope::hud_centered,e.arguments[3]);
}
Status creation_rebuild(u32 page) {
    auto status=native_targets::promote();
    if(status!=Status::ok) return status;
    const auto selection=*at<u32>(0x5F54AB0);
    if(page==0) {
        creation_select_redrawing=true;
        reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x108A0)();
        creation_select_redrawing=false;creation_select_pending=false;
    } else if(page==1) {
        creation_confirmation_redrawing=true;
        reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0x105C0)(0);
        creation_confirmation_redrawing=false;creation_confirmation_pending=false;
    } else if(page==2) {
        creation_course_redrawing=true;
        reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0x10D40)(0);
        creation_course_redrawing=false;creation_course_pending=false;
    } else {
        creation_world_redrawing=true;
        reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x60B60)();
        creation_world_redrawing=false;creation_world_pending=false;
    }
    *at<u32>(0x5F54AB0)=selection;
    return refresh_menu_cache();
}
Status windows_creation_input(const NativeEvent& e) {
    if(creation_complete_pending && e.id==about_input_tick && e.phase==NativePhase::before &&
        *ptr<u32>(e.frame->ebp+4)==host->image_base+0x13341) return creation_complete_rebuild();
    if(creation_select_pending && native_language_redraw::menu_input(e,0x10B89)) return creation_rebuild(0);
    if(creation_confirmation_pending && native_language_redraw::menu_input(e,0x1077E)) return creation_rebuild(1);
    if(creation_course_pending && native_language_redraw::menu_input(e,0x110C5)) return creation_rebuild(2);
    return Status::ok;
}

Status dispatch_windows_creation(const NativeEvent& e,DispatchResult& result,bool& handled) {
    handled=true;
    if(e.phase==NativePhase::after) {
        if(e.id==about_button_character && in(Scope::creation_button)) return native_button::character(e);
        handled=false;return Status::ok;
    }
    if(e.id>=creation_text_first && e.id<creation_text_first+std::size(creation_text_calls)) {
        const auto& field=creation_text_calls[e.id-creation_text_first];
        if(field.site==0x60D32 && creation_world_pending && !creation_world_redrawing) {
            creation_world_legend=e.frame->edi;
            const auto status=creation_rebuild(3);
            if(status!=Status::ok) return status;
        }
        if(field.component==TextComponent::creation_complete_title) creation_complete_pending=false;
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
    case creation_complete_entry:
        if(creation_complete_redrawing) result.resume_rva=0x13187;
        return Status::ok;
    case creation_complete_exit:
        if(creation_complete_redrawing) result.resume_rva=0x133C1;
        return Status::ok;
    case scenario_redraw_wait:
        if(creation_complete_redrawing) {result.resume_rva=0xD3D0F;return Status::ok;}
        break;
    case scenario_story_scope: case creation_preview: {
        scenario_refresh_pending=false;
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
        if(!*original) return Status::ok; // confirmed empty records and terminal EOF
        const auto story=std::find_if(active.rbegin(),active.rend(),[](const Active& item){return item.kind==Scope::scenario_story;});
        auto* source=ptr<CreationStory>(story->allocation);
        const auto key="story."+std::to_string(source->id)+"."+std::to_string(source->record++);
        return creation_lend(e,TextComponent::scenario_confirmation_text,key.c_str(),e.arguments[2],CreationKind::words);
    }
    case scenario_body_paragraph:
        begin(e,Scope::paragraph,e.arguments[3]);begin(e,Scope::creation_paragraph,e.arguments[3]);return Status::ok;
    case creation_select_title: case creation_course_title:
        return creation_lend(e,e.id==creation_select_title ? TextComponent::scenario_selection_text : TextComponent::game_course_text,
            "title",e.frame->ecx,CreationKind::panel);
    case creation_select_name: {
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
    case creation_select_exit:
        creation_select_pending=false;
        if(creation_select_redrawing) result.resume_rva=0x10BAF;
        return Status::ok;
    case creation_confirmation_entry:
        if(creation_confirmation_redrawing) result.resume_rva=0x10707;
        return Status::ok;
    case creation_confirmation_exit:
        creation_confirmation_pending=false;
        if(creation_confirmation_redrawing) result.resume_rva=0x10797;
        return Status::ok;
    case creation_course_entry:
        if(creation_course_redrawing) result.resume_rva=0x10D60;
        return Status::ok;
    case creation_course_exit:
        creation_course_pending=false;
        if(creation_course_redrawing) result.resume_rva=0x11135;
        return Status::ok;
    case creation_footer_rng:
        if(creation_select_redrawing || creation_course_redrawing) {
            e.frame->esi=*at<u32>(0x18C1F8);result.resume_rva=0xF293;
        }
        return Status::ok;
    case creation_world_entry:
        if(creation_world_redrawing) {e.frame->edi=creation_world_legend;result.resume_rva=0x60BB8;}
        return Status::ok;
    case creation_world_after_title:
        if(creation_world_redrawing) {*at<u32>(0x61BBAC8)=0;result.resume_rva=0x6109F;}
        return Status::ok;
    case creation_world_after_map:
        if(creation_world_redrawing) {e.frame->ebx=0;result.resume_rva=0x60CC2;}
        return Status::ok;
    case creation_world_exit:
        if(creation_world_redrawing) result.resume_rva=0x6113D;
        return Status::ok;
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
