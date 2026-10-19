// Dedicated native message concatenation boundaries, Windows 3.89.
// 461CF0 constructs a tool suitability clause in EBP-870, then appends the
// quality clause from EBP-470 at either 46232D..46235B or 4623BB..4623E9.
// The native copy loops contain no calls or input waits. Only their neutral
// source expression is carried between the two boundaries; native bytes stay.
namespace windows_message_format_builders {
enum Hook : u32 { quality_begin=0xe400,quality_end,quality_low_begin,quality_low_end,
    requirement_inventory_begin,requirement_inventory_end,
    requirement_nearby_begin,requirement_nearby_end,
    requirement_store_first=0xe420,requirement_store_last=0xe424,
    requirement_list_first=0xe430,requirement_list_last=0xe431,
    nearby_objects=0xe440,object_construction_copy,object_plant_copy,object_item_copy,
    object_fresh_copy,object_corpse_copy,object_overflow_copy,object_fixed,
    object_work_begin,object_work_end,physical_list_copy,physical_hurt_copy,
    hunger_begin,hunger_finish,terrain_article_copy,treatment_method_copy,
    treatment_result_first=0xe460,treatment_result_last=0xe466,
    copied_value_first=0xe480,copied_value_last=0xe487,
    fish_lists=0xe490,
    craft_begin=0xe4a0,craft_suffix,craft_store,craft_save_row,craft_restore_row,
    track_begin=0xe4b0,track_human,track_npc,track_subject_end,track_append,track_finish,
    craft_menu_name_first=0xe4c0,craft_menu_name_last=0xe4c2,
    craft_cure_template=0xe4d0,craft_clean_template,craft_tanning_template,
    craft_selected_row=0xe4e0,
    food_material_copy=0xe500,crafted_material_copy,food_first_material,crafted_first_material,
    food_mixed,crafted_mixed,food_name_suffix,crafted_name_suffix,food_beverage,food_direct,food_default,
    crafted_result_copy,crafted_descriptor_copy };
struct Append { u32 destination; MessageText source; };
std::vector<Append> appends;
struct Craft { bool appended=false;MessageText name; };
std::vector<Craft> crafts;
std::vector<MessageText> track_subjects;
void save(std::vector<unsigned char>& output) {
    message_state_write(output,static_cast<u32>(appends.size()));
    for(const auto& append:appends) {
        message_state_write(output,append.destination);native_message_source::write(output,append.source);
    }
    message_state_write(output,static_cast<u32>(crafts.size()));
    for(const auto& craft:crafts) {
        message_state_write(output,craft.appended);native_message_source::write(output,craft.name);
    }
}
void restore(const unsigned char*& input) {
    u32 count;message_state_read(input,count);appends.clear();
    for(u32 index=0;index<count;++index) {
        u32 destination;message_state_read(input,destination);
        appends.push_back({destination,native_message_source::read(input)});
    }
    message_state_read(input,count);crafts.clear();
    for(u32 index=0;index<count;++index) {
        bool appended;message_state_read(input,appended);
        crafts.push_back({appended,native_message_source::read(input)});
    }
}

void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    hooks.push_back(instruction(quality_begin,0x6232d,{0x8d,0x95,0x90,0xfb,0xff,0xff}));
    hooks.push_back(instruction(quality_end,0x6235b,{0x8b,0xbd,0x54,0xf6,0xff,0xff}));
    hooks.push_back(instruction(quality_low_begin,0x623bb,{0x8d,0x95,0x90,0xfb,0xff,0xff}));
    hooks.push_back(instruction(quality_low_end,0x623e9,{0x8b,0xbd,0x54,0xf6,0xff,0xff}));
    hooks.push_back(instruction(requirement_inventory_begin,0x6897d,{0x8d,0x95,0xf8,0xfb,0xff,0xff}));
    hooks.push_back(instruction(requirement_inventory_end,0x68992,{0x8d,0x8d,0xf8,0xfb,0xff,0xff}));
    hooks.push_back(instruction(requirement_nearby_begin,0x689e1,{0x8d,0x95,0xf8,0xfb,0xff,0xff}));
    hooks.push_back(instruction(requirement_nearby_end,0x689fd,{0x8d,0x8d,0xf8,0xfb,0xff,0xff}));
    constexpr u32 stores[]{0x6971c,0x69756,0x6a159,0x6a587,0x6a8e6};
    for(u32 i=0;i<std::size(stores);++i)
        hooks.push_back(native_name_input::native_call(requirement_store_first+i,stores[i],0x68660,0));
    hooks.push_back(native_name_input::native_call(requirement_list_first,0x68978,0x68740,0));
    hooks.push_back(native_name_input::native_call(requirement_list_last,0x689dc,0x68740,0));
    hooks.push_back(instruction(nearby_objects,0x107561,{0x8d,0x8d,0x8c,0xf7,0xff,0xff}));
    hooks.push_back(instruction(object_construction_copy,0x1076a2,{0x8d,0x95,0x8c,0xfb,0xff,0xff}));
    hooks.push_back(instruction(object_plant_copy,0x107783,{0x8d,0x95,0x8c,0xfb,0xff,0xff}));
    hooks.push_back(instruction(object_item_copy,0x107930,{0x8d,0x95,0x8c,0xfb,0xff,0xff}));
    hooks.push_back(instruction(object_fresh_copy,0x1079c0,{0x8a,0x84,0x0d,0x8c,0xef,0xff,0xff}));
    hooks.push_back(instruction(object_corpse_copy,0x107ec1,{0x8d,0x95,0x8c,0xfb,0xff,0xff}));
    hooks.push_back(instruction(object_overflow_copy,0x107f8b,{0xff,0x85,0x70,0xeb,0xff,0xff}));
    hooks.push_back(instruction(object_fixed,0x1076c0,{0x8a,0xa5,0x8b,0xeb,0xff,0xff}));
    hooks.push_back(instruction(object_work_begin,0x107816,{0x8d,0x8d,0x8c,0xfb,0xff,0xff}));
    hooks.push_back(instruction(object_work_end,0x107851,{0xe9,0x6a,0xfe,0xff,0xff}));
    hooks.push_back(instruction(physical_list_copy,0xdcc1a,{0x8d,0x95,0xf8,0xef,0xff,0xff}));
    hooks.push_back(instruction(physical_hurt_copy,0xdcc51,{0x66,0x0f,0xd6,0x85,0xf8,0xef,0xff,0xff}));
    hooks.push_back(instruction(hunger_begin,0xd5612,{0x8d,0x8c,0x24,0xb8,0,0,0}));
    hooks.push_back(native_name_input::native_call(hunger_finish,0xd561c,0xf6510,0));
    hooks.push_back(instruction(terrain_article_copy,0xa243d,{0x8d,0x94,0x24,0x50,0x02,0,0}));
    hooks.push_back(instruction(treatment_method_copy,0xd93c1,{0x8d,0x95,0x28,0xff,0xff,0xff}));
    constexpr u32 treatment_copies[]{0xd9b25,0xd9b4c,0xd9b70,0xd9b9c,0xd9bc0,0xd9bec,0xd9c57};
    for(u32 i=0;i<std::size(treatment_copies);++i)
        hooks.push_back(instruction(treatment_result_first+i,treatment_copies[i],{0x8d,0x95,0x28,0xfb,0xff,0xff}));
    hooks.push_back(instruction(copied_value_first+0,0x3115f,{0x8d,0x95,0xf4,0xef,0xff,0xff}));
    hooks.push_back(instruction(copied_value_first+1,0x11cac0,{0x8d,0x94,0x24,0xd0,0x3f,0,0}));
    hooks.push_back(instruction(copied_value_first+2,0x165b84,{0x8a,0x08,0x8d,0x40,0x01}));
    hooks.push_back(instruction(copied_value_first+3,0x11ddeb,{0x8d,0x95,0x24,0xff,0xff,0xff}));
    hooks.push_back(instruction(copied_value_first+4,0x11de11,{0x8d,0x55,0x8c,0x2b,0xd0}));
    hooks.push_back(instruction(copied_value_first+5,0x11edfd,{0x8d,0x94,0x24,0xe0,0x0e,0,0}));
    hooks.push_back(instruction(copied_value_first+6,0x11ee24,{0x8d,0x94,0x24,0x78,0x0e,0,0}));
    hooks.push_back(instruction(copied_value_first+7,0xd7fe4,{0x8d,0x95,0x28,0xff,0xff,0xff}));
    hooks.push_back(instruction(fish_lists,0x31116,{0x8d,0x8d,0xf4,0xfb,0xff,0xff}));
    auto craft_start=instruction(craft_begin,0x633de,{0xb9,0,0,0,0});
    const auto scratch=address(at<char>(0x1d308e0));
    std::memcpy(craft_start.expected+1,&scratch,4);hooks.push_back(craft_start);
    hooks.push_back(instruction(craft_suffix,0x6436e,{0x8d,0x55,0x98,0xc6,0x45,0x98,0x20}));
    hooks.push_back(instruction(craft_store,0x6439c,{0x69,0xfb,0x44,0x02,0,0}));
    hooks.push_back(instruction(craft_save_row,0x43658,{0xb9,0x91,0,0,0}));
    hooks.push_back(instruction(craft_restore_row,0x436af,{0xb9,0x91,0,0,0}));
    auto unknown=instruction(track_begin,0x167a1f,{0xa1,0,0,0,0});
    const auto unknown_word=address(at<char>(0x1940d4));
    std::memcpy(unknown.expected+1,&unknown_word,4);hooks.push_back(unknown);
    auto human=instruction(track_human,0x167ac2,{0xa1,0,0,0,0});
    const auto human_word=address(at<char>(0x1a0328));
    std::memcpy(human.expected+1,&human_word,4);hooks.push_back(human);
    hooks.push_back(instruction(track_npc,0x167aea,{0x8d,0x7c,0x24,0x70,0x2b,0xd6}));
    hooks.push_back(instruction(track_subject_end,0x167b07,{0x8b,0x4c,0x24,0x3c,0x8d,0x44,0x24,0x50}));
    hooks.push_back(instruction(track_append,0x167c09,{0x8b,0xca,0xc1,0xe9,0x02}));
    hooks.push_back(native_name_input::native_call(track_finish,0x167c3a,0xf6510,0));
    constexpr u32 craft_menu_names[]{0x5feb,0x600b,0x43299};
    for(u32 index=0;index<std::size(craft_menu_names);++index)
        hooks.push_back(native_name_input::native_call(craft_menu_name_first+index,craft_menu_names[index],0x6c8b0,0));
    hooks.push_back(instruction(craft_cure_template,0x11e0a0,{0x8d,0x95,0xf0,0xf4,0xff,0xff}));
    hooks.push_back(instruction(craft_clean_template,0x11e981,{0x8d,0xb4,0x24,0x34,0x03,0,0}));
    hooks.push_back(instruction(craft_tanning_template,0x11f826,{0x8d,0xbc,0x24,0x68,0x07,0,0}));
    hooks.push_back(instruction(craft_selected_row,0x64719,{0xb9,0x91,0,0,0}));
    hooks.push_back(instruction(food_material_copy,0x3697a,{0x8d,0x95,0xc0,0xfe,0xff,0xff}));
    hooks.push_back(instruction(crafted_material_copy,0x6d503,{0x8d,0x95,0xc0,0xfe,0xff,0xff}));
    hooks.push_back(instruction(food_first_material,0x369b1,{0x8a,0x84,0x0d,0xc0,0xfe,0xff,0xff}));
    hooks.push_back(instruction(crafted_first_material,0x6d531,{0x8a,0x8c,0x05,0xc0,0xfe,0xff,0xff}));
    for(const auto pair:{std::pair<u32,u32>{food_mixed,0x369fd},{crafted_mixed,0x6d579}}) {
        auto spec=instruction(pair.first,pair.second,{0xa1,0,0,0,0});
        const auto literal=address(at<char>(0x193cc4));std::memcpy(spec.expected+1,&literal,4);hooks.push_back(spec);
    }
    hooks.push_back(instruction(food_name_suffix,0x36a68,{0x8b,0xca,0xc1,0xe9,0x02}));
    hooks.push_back(instruction(crafted_name_suffix,0x6d5e8,{0x8b,0xca,0xc1,0xe9,0x02}));
    // At this MOVQ the complete native beverage literal is already in XMM0.
    hooks.push_back(instruction(food_beverage,0x37059,{0x66,0x0f,0xd6,0x45,0x90}));
    auto direct=instruction(food_direct,0x3710f,{0xb9,0,0,0,0});
    auto standard=instruction(food_default,0x37177,{0xbe,0,0,0,0});
    const auto food_name=address(at<char>(0x27d521));
    std::memcpy(direct.expected+1,&food_name,4);std::memcpy(standard.expected+1,&food_name,4);
    hooks.push_back(direct);hooks.push_back(standard);
    hooks.push_back(instruction(crafted_result_copy,0x425de,{0x8d,0x95,0xa8,0xf5,0xff,0xff}));
    hooks.push_back(instruction(crafted_descriptor_copy,0x42610,{0x8a,0x84,0x0d,0xa8,0xf5,0xff,0xff}));
}

MessageText nearby_object_list(u32 map_offset) {
    struct Part {u32 flag;unsigned char mask;u32 literal;const char* key;};
    constexpr Part parts[]{
        {0x6022b01,4,0x1ac224,"format.005ac224"},
        {0x6022b01,2,0x1ac238,"format.005ac238"},
        {0x6022b01,8,0x1ac244,"format.005ac244"},
        {0x6022b00,4,0x1ac250,"format.005ac250"},
        {0x6022b00,2,0x1ac25c,"format.005ac25c"},
        {0x6022b07,2,0x1ac274,"format.005ac274"},
        {0x6022b07,4,0x1ac280,"format.005ac280"}};
    std::vector<MessageText> values;
    for(const auto& part:parts) {
        if(!(*at<unsigned char>(part.flag+map_offset)&part.mask)) continue;
        // Every recovered literal ends with the exact native list delimiter.
        // Keep that delimiter as its own source node for 5627A0's later join.
        const auto* literal=at<char>(part.literal);
        const std::string item(literal,std::strlen(literal)-2);
        values.push_back(message_source_lookup("nearby-object",item.c_str()));
        values.push_back(native_message_source::original(", "));
    }
    return native_message_source::concat(std::move(values));
}

MessageText requirement_list(u32 selector) {
    std::vector<MessageText> values;
    const auto* table=at<char>(selector==1 ? 0x14fbcc8 : 0x14fe440);
    for(u32 row=0;row<100;++row) {
        const auto* source=table+row*100;
        if(!*source) continue;
        values.push_back(message_source_bound(source));
        // 4687DF/4688A5 use the next two actual slots, only below slot 98.
        if(row<98 && source[100]) values.push_back(message_source_lookup("message-punctuation",source[200] ? ", " : " and "));
    }
    return native_message_source::concat(std::move(values));
}

Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=(event.id>=quality_begin && event.id<=requirement_nearby_end) ||
        (event.id>=requirement_store_first && event.id<=requirement_store_last) ||
        (event.id>=requirement_list_first && event.id<=requirement_list_last) ||
        (event.id>=nearby_objects && event.id<=treatment_method_copy) ||
        (event.id>=treatment_result_first && event.id<=treatment_result_last) ||
        (event.id>=copied_value_first && event.id<=copied_value_last) || event.id==fish_lists ||
        (event.id>=craft_begin && event.id<=craft_restore_row) ||
        (event.id>=track_begin && event.id<=track_finish) ||
        (event.id>=craft_menu_name_first && event.id<=craft_menu_name_last) ||
        (event.id>=craft_cure_template && event.id<=craft_tanning_template) || event.id==craft_selected_row ||
        (event.id>=food_material_copy && event.id<=crafted_descriptor_copy);
    if(!handled) return Status::ok;
    if(event.id>=food_material_copy) {
        if(event.phase==NativePhase::after) return Status::ok;
        const auto frame=event.frame->ebp;
        if(event.id==crafted_result_copy) {
            const auto* input=ptr<char>(event.frame->eax);
            message_bind_copy(ptr<char>(frame-0xa58),input,message_source_bound(input));
        } else if(event.id==crafted_descriptor_copy) {
            // Native 442610..442623 copies the actual nonempty compound name
            // into descriptor +9, then 442625 sets descriptor +0x93 to one.
            if(event.frame->ecx==0) {
                const auto* input=ptr<char>(frame-0xa58);
                message_bind_copy(ptr<char>(frame-0xeff),input,message_source_bound(input));
            }
        } else if(event.id==food_material_copy || event.id==crafted_material_copy) {
            const auto* input=ptr<char>(event.id==food_material_copy ? event.frame->ecx : event.frame->eax);
            message_bind_copy(ptr<char>(frame-0x140),input,message_source_bound(input));
        } else if(event.id==food_first_material || event.id==crafted_first_material) {
            // These hooks are the actual copy-loop head. Only its native
            // first iteration establishes the selected first material source.
            const auto index=event.id==food_first_material ? event.frame->ecx : event.frame->eax;
            if(index==0) {
                const auto* input=ptr<char>(frame-0x140);
                message_bind_copy(ptr<char>(frame-(event.id==food_first_material ? 0xd8 : 0x70)),input,message_source_bound(input));
            }
        } else if(event.id==food_mixed || event.id==crafted_mixed) {
            const auto* literal=at<char>(0x193cc4);
            message_bind_copy(ptr<char>(frame-(event.id==food_mixed ? 0xd8 : 0x70)),literal,
                message_source_lookup("crafted-material",literal));
        } else if(event.id==food_name_suffix || event.id==crafted_name_suffix) {
            const auto* input=ptr<char>(event.frame->esi);
            message_bind_copy(ptr<char>(event.frame->edi),input,message_source_value("menu.recipe",input));
        } else if(event.id==food_beverage) {
            const auto* literal=at<char>(0x193d4c+3);
            message_bind_copy(ptr<char>(frame-0x70+3),literal,message_source_lookup("crafted-name",literal));
        } else {
            const auto* input=ptr<char>(event.id==food_direct ? event.frame->esi : event.frame->eax);
            auto source=event.id==food_direct ? message_source_value("menu.recipe",input) : message_source_bound(input);
            message_bind_copy(at<char>(0x27d521),input,std::move(source));
        }
        return Status::ok;
    }
    if(event.id==craft_selected_row) {
        if(event.phase==NativePhase::after) return Status::ok;
        // 4646F0 has already found its actual free row. Its sole copy uses
        // ESI for the descriptor scratch and EDI for that selected record.
        for(const auto field:{0u,0x64u}) {
            const auto* input=ptr<char>(event.frame->esi+field);
            message_bind_copy(ptr<char>(event.frame->edi+field),input,message_source_bound(input));
        }
        return Status::ok;
    }
    if(event.id>=craft_cure_template) {
        if(event.phase==NativePhase::after) return Status::ok;
        const auto destination=event.id==craft_cure_template ? event.frame->ebp-0xb10 :
            event.frame->esp+(event.id==craft_clean_template ? 0x334 : 0x768);
        const auto* input=event.id==craft_tanning_template ? at<char>(0x1ae188) : ptr<char>(event.frame->eax);
        auto source=event.id==craft_tanning_template ? message_source_template("format.005ae188",input) : message_source_bound(input);
        message_bind_copy(ptr<char>(destination),input,std::move(source));
        return Status::ok;
    }
    if(event.id>=craft_menu_name_first) {
        if(event.phase==NativePhase::after) {
            const auto* name=ptr<char>(event.frame->eax);
            message_bind_source(name,message_source_lookup("craft-requirement",name));
        }
        return Status::ok;
    }
    if(event.id>=track_begin) {
        if(event.phase==NativePhase::after) return Status::ok;
        const auto stack=event.frame->esp;
        if(event.id==track_begin)
            track_subjects.push_back(message_source_lookup("track-subject",at<char>(0x1940d4)));
        else if(event.id==track_human || event.id==track_npc) {
            const auto* prefix=ptr<char>(stack+0x70);
            // 567A42 clears this exact prefix; 567A82/567AA2 may replace it
            // with the native small/big descriptor before the selected noun.
            auto size=*prefix ? message_source_bound(prefix) : native_message_source::original("");
            const auto* noun=event.id==track_human ? at<char>(0x1a0328) : ptr<char>(event.frame->esi);
            auto subject=message_source_lookup(event.id==track_human ? "track-subject" : "npc",noun);
            track_subjects.back()=native_message_source::concat({std::move(size),std::move(subject)});
        } else if(event.id==track_subject_end) {
            auto subject=std::move(track_subjects.back());track_subjects.pop_back();
            message_bind_source(ptr<char>(stack+0x70),std::move(subject));
            message_bind_source(ptr<char>(stack+0x50),message_source_lookup("track-kind",ptr<char>(stack+0x50)));
        } else if(event.id==track_append) {
            const auto body=stack+0xd8;
            appends.push_back({body,native_message_source::concat({message_source_bound(ptr<char>(body)),
                message_source_bound(ptr<char>(stack+0x4d8)),message_source_lookup("message-punctuation",at<char>(0x19285c))})});
        } else {
            auto current=std::move(appends.back());appends.pop_back();
            message_bind_source(ptr<char>(current.destination),std::move(current.source));
        }
        return Status::ok;
    }
    if(event.id>=craft_begin) {
        if(event.phase==NativePhase::after) return Status::ok;
        if(event.id==craft_save_row || event.id==craft_restore_row) {
            // 443630 removes consumed requirement rows by saving and copying
            // the actual retained records. Preserve each record's two sources.
            const auto input=event.id==craft_save_row ? event.frame->ebx : event.frame->eax;
            const auto output=event.id==craft_save_row ? event.frame->ebp-0xe294+event.frame->eax : event.frame->edx;
            for(const auto field:{0u,0x64u})
                message_bind_copy(ptr<char>(output+field),ptr<char>(input+field),message_source_bound(ptr<char>(input+field)));
        } else if(event.id==craft_begin) crafts.emplace_back();
        else if(event.id==craft_suffix) {
            // This branch alone appends the saved '+' annotation, replacing
            // its leading plus with a space at 464371. All name selection has
            // already happened in 4633B0, including its 46C8B0 default branch.
            auto& craft=crafts.back();craft.appended=true;
            const std::string annotation=std::string(" ")+ptr<char>(event.frame->ebp-0x67);
            craft.name=native_message_source::concat({
                message_source_lookup("craft-requirement",at<char>(0x1d308e0)),
                message_source_lookup("craft-requirement-suffix",annotation.c_str())});
        } else {
            auto craft=std::move(crafts.back());crafts.pop_back();
            const auto* name=at<char>(0x1d308e0);
            const auto* description=at<char>(0x1d30944);
            const auto destination=address(at<char>(0x1d30b28))+event.frame->ebx*0x244;
            auto source=craft.appended ? std::move(craft.name) : message_source_lookup("craft-requirement",name);
            // 46439C..4643B2 performs the actual 0x244-byte record copy.
            message_bind_source(name,source);
            message_bind_copy(ptr<char>(destination),name,std::move(source));
            auto explanation=message_source_lookup("craft-requirement-description",description);
            message_bind_source(description,explanation);
            message_bind_copy(ptr<char>(destination+0x64),description,std::move(explanation));
        }
        return Status::ok;
    }
    if(event.id==fish_lists) {
        if(event.phase==NativePhase::after) return Status::ok;
        // 430FE0..431112 append these four literals to the two native buffers.
        // The flags here are the already computed branch results, not a new
        // spawning or location decision. 5627A0 receives separate item nodes.
        const auto frame=event.frame->ebp;
        constexpr u32 enabled[]{0x100f,0x1010,0x100d,0x1011};
        const bool local[]{*ptr<unsigned char>(frame-0x1048)!=0,
            *ptr<unsigned char>(frame-0x104c)!=0,*ptr<unsigned char>(frame-0x1044)!=0,
            (event.frame->ebx&0xff)!=0};
        constexpr u32 literals[]{0x192bfc,0x192c04,0x192c0c,0x192c18};
        std::vector<MessageText> lists[2];
        for(u32 i=0;i<std::size(enabled);++i) {
            if(!*ptr<unsigned char>(frame-enabled[i])) continue;
            const auto* literal=at<char>(literals[i]);
            const std::string species(literal,std::strlen(literal)-2);
            auto& list=lists[local[i] ? 0 : 1];
            list.push_back(message_source_lookup("fish-spawning",species.c_str()));
            list.push_back(native_message_source::original(", "));
        }
        message_bind_source(ptr<char>(frame-0x40c),native_message_source::concat(std::move(lists[0])));
        message_bind_source(ptr<char>(frame-0x80c),native_message_source::concat(std::move(lists[1])));
        return Status::ok;
    }
    if(event.id>=copied_value_first) {
        if(event.phase==NativePhase::after) return Status::ok;
        const auto index=event.id-copied_value_first;
        // 565B84 is the copy-loop head after native ADD ESP,4 / SUB EDX,EAX.
        // EAX+EDX equals the destination only on its original first iteration.
        if(index==2 && event.frame->eax+event.frame->edx!=event.frame->ebp-0x70) return Status::ok;
        const auto* source=ptr<char>(index<2 ? event.frame->ecx : event.frame->eax);
        constexpr std::int32_t offsets[]{-0x100c,0x3fd0,-0x70,-0xdc,-0x74,0xee0,0xe78,-0xd8};
        const auto base=index==1 || index==5 || index==6 ? event.frame->esp : event.frame->ebp;
        message_bind_copy(ptr<char>(base+offsets[index]),source,message_source_bound(source));
        return Status::ok;
    }
    if(event.id>=nearby_objects) {
        if(event.phase==NativePhase::after) return Status::ok;
        const auto frame=event.frame->ebp;
        if(event.id==nearby_objects) {
            message_bind_source(ptr<char>(frame-0x874),nearby_object_list(event.frame->esi));
        } else if(event.id==object_work_begin || event.id==hunger_begin) {
            const auto destination=event.id==object_work_begin ? frame-0x474 : event.frame->esp+0xb8;
            const std::string punctuation(1,static_cast<char>(event.frame->eax));
            auto suffix=event.id==object_work_begin ? message_source_template("format.005ac32c",at<char>(0x1ac32c)) :
                message_source_lookup("message-punctuation",punctuation.c_str());
            appends.push_back({destination,native_message_source::concat({message_source_bound(ptr<char>(destination)),std::move(suffix)})});
        } else if(event.id==object_work_end || event.id==hunger_finish) {
            auto current=std::move(appends.back());appends.pop_back();
            message_bind_source(ptr<char>(current.destination),std::move(current.source));
            // This replaces the recovered unconditional JMP, without replaying
            // its relative displacement from a trampoline.
            if(event.id==object_work_end) result.resume_rva=0x1076c0;
        } else if(event.id==object_overflow_copy) {
            message_bind_source(ptr<char>(frame-0x1474),message_source_bound(ptr<char>(frame-0x474)));
        } else if(event.id==object_fixed) {
            const auto offset=*ptr<u32>(frame-0x1480);
            const auto type=*at<unsigned char>(0xa2d28ac+offset);
            if(type==8 || type==0x62 || type==0x63)
                message_bind_source(ptr<char>(frame-0x474),message_source_lookup("object-description",ptr<char>(frame-0x474)));
        } else {
            const char* source=ptr<char>(event.frame->eax);
            u32 destination=frame-0x474;
            if(event.id==object_fresh_copy) {
                if(event.frame->ecx!=0) return Status::ok;
                source=ptr<char>(frame-0x1074);
            }
            else if(event.id==physical_list_copy) destination=frame-0x1008;
            else if(event.id==physical_hurt_copy) {
                source=at<char>(0x1a5fb0);destination=frame-0x1008;
            } else if(event.id==terrain_article_copy) {
                source=ptr<char>(event.frame->ecx);destination=event.frame->esp+0x250;
            } else if(event.id==treatment_method_copy) {
                source=ptr<char>(event.frame->ecx);destination=frame-0xd8;
            } else if(event.id>=treatment_result_first) destination=frame-0x4d8;
            auto value=event.id==physical_hurt_copy ? message_source_template("format.005a5fb0",source) : message_source_bound(source);
            message_bind_copy(ptr<char>(destination),source,std::move(value));
        }
        return Status::ok;
    }
    if(event.id>=requirement_store_first && event.id<=requirement_list_last) {
        if(event.phase==NativePhase::before) {
            appends.push_back({0,{}});
            auto& current=appends.back();
            if(event.id>=requirement_list_first)
                current.source=requirement_list(event.frame->ecx);
            else {
                const auto* source=ptr<char>(event.frame->ecx);
                // 468679/46867D: empty input or selector 0 clears both tables.
                if(*source && event.frame->edx) {
                    const bool nearby=event.frame->edx==2;
                    const auto index=*at<u32>(nearby ? 0xa44b784 : 0xa44b780);
                    current.destination=address(at<char>(nearby ? 0x14fe440 : 0x14fbcc8)+index*100);
                    current.source=message_source_bound(source);
                }
            }
            return Status::ok;
        }
        auto current=std::move(appends.back());
        appends.pop_back();
        if(event.id>=requirement_list_first) current.destination=event.frame->eax;
        if(current.destination)
            message_bind_source(ptr<char>(current.destination),std::move(current.source));
        return Status::ok;
    }
    if(event.phase==NativePhase::after) return Status::ok;
    if(event.id==requirement_inventory_begin || event.id==requirement_nearby_begin) {
        appends.push_back({event.frame->ebp-0x408,message_source_bound(ptr<char>(event.frame->eax))});
        return Status::ok;
    }
    if(event.id==quality_begin || event.id==quality_low_begin) {
        const auto destination=event.frame->ebp-0x870;
        const auto* prefix=ptr<char>(destination);
        const auto* suffix=ptr<char>(event.frame->ebp-0x470);
        // Native 461DB7 initially clears this clause. The no-item branch may
        // append to that empty clause before 46242C discards it again.
        auto clause=*prefix ? message_source_bound(prefix) : native_message_source::original("");
        // 462316/462326 and 4623A4/4623B4 explicitly construct this alternative.
        auto quality=suffix[0]=='.' && suffix[1]==0 ?
            message_source_lookup("message-punctuation",suffix) : message_source_bound(suffix);
        appends.push_back({destination,native_message_source::concat({std::move(clause),std::move(quality)})});
        return Status::ok;
    }
    auto current=std::move(appends.back());
    appends.pop_back();
    message_bind_source(ptr<char>(current.destination),std::move(current.source));
    return Status::ok;
}
}
