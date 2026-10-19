// 455060 returns its selected-item explanation through 6F2C30. Native copy
// loops preserve the English buffer; these entry points propagate only its
// source expression. 458D57 later consumes this exact native output owner.
namespace windows_message_transfers {
enum Hook:u32 {literal_copy=0xec00,literal_without_marker,
    stack_copy_first,stack_copy_second,stack_copy_third,stack_copy_fourth,
    stack_without_marker_first,stack_without_marker_second,
    stack_without_marker_third,stack_without_marker_fourth,
    resource_copy_first,resource_copy_second,resource_copy_third,
    resource_without_marker_first,resource_without_marker_second,resource_without_marker_third,
    row_copy=0xec20,bedding_default,bedding_plentiful,bedding_some,bedding_additional,
    projectile_first,projectile_second,projectile_third,projectile_fourth,
    plant_first=0xec30,plant_second,plant_last,plant_space,projectile_record,projectile_period,
    healing_name,healing_eases,healing_complete,projectile_period_visible,projectile_period_deflected};
struct SelectedCopy {u32 id,site,offset;};
const SelectedCopy selected_copies[]={
    {row_copy,0x1bf14,0x40c},
    {bedding_default,0xd9ef0,0x40c},{bedding_plentiful,0xda07d,0x40c},
    {bedding_some,0xda0a7,0x40c},{bedding_additional,0xda116,0x40c},
    {projectile_first,0x12b727,0x4dc},{projectile_second,0x12b78b,0x4dc},
    {projectile_third,0x12b847,0x4dc},{projectile_fourth,0x12b91b,0x4dc}
};
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    for(const auto pair:{std::pair<u32,u32>{literal_copy,0x56881},
                         {literal_without_marker,0x568b0}}) {
        auto hook=instruction(pair.first,pair.second,{0x8a,0x81,0,0,0,0});
        const auto source=address(at<char>(pair.first==literal_copy ? 0x195d34 : 0x195d35));
        std::memcpy(hook.expected+2,&source,4);hooks.push_back(hook);
    }
    const u32 full_stack[]={0x56c30,0x56d20,0x56e10,0x56f20};
    const u32 stripped_stack[]={0x56c70,0x56d60,0x56e50,0x56f60};
    for(u32 index=0;index<4;++index) {
        hooks.push_back(instruction(stack_copy_first+index,full_stack[index],{0x8a,0x84,0x0c,0x98,7,0,0}));
        hooks.push_back(instruction(stack_without_marker_first+index,stripped_stack[index],{0x8a,0x84,0x0c,0x99,7,0,0}));
    }
    const u32 full_resource[]={0x56cb0,0x56da0,0x56eb1};
    const u32 stripped_resource[]={0x56cea,0x56dda,0x56eea};
    const auto destination=address(at<char>(0x2f2c30));
    for(u32 index=0;index<3;++index) {
        for(const auto pair:{std::pair<u32,u32>{resource_copy_first+index,full_resource[index]},
                             {resource_without_marker_first+index,stripped_resource[index]}}) {
            auto hook=instruction(pair.first,pair.second,{0xba,0,0,0,0});
            std::memcpy(hook.expected+1,&destination,4);hooks.push_back(hook);
        }
    }
    for(const auto& copy:selected_copies) {
        auto hook=instruction(copy.id,copy.site,{0x8d,0x95,0,0,0,0});
        const u32 offset=0u-copy.offset;std::memcpy(hook.expected+2,&offset,4);hooks.push_back(hook);
    }
    for(const auto pair:{std::pair<u32,u32>{plant_first,0x3249},
                         {plant_second,0x3298},{plant_last,0x3318},
                         {healing_name,0xd7d28}})
        hooks.push_back(instruction(pair.first,pair.second,{0x8b,0xca,0xc1,0xe9,0x02}));
    auto space=instruction(plant_space,0x32ba,{0x66,0xa1,0,0,0,0});
    const auto space_source=address(at<char>(0x18c8c0));
    std::memcpy(space.expected+2,&space_source,4);hooks.push_back(space);
    hooks.push_back(instruction(projectile_record,0x12b940,{0x8a,0x84,0x15,0x24,0xfb,0xff,0xff}));
    const auto period_source=address(at<char>(0x19285c));
    for(const auto pair:{std::pair<u32,u32>{projectile_period,0x4e74b},
                         {projectile_period_visible,0x1300a1},{projectile_period_deflected,0x13031a}}) {
        auto period=instruction(pair.first,pair.second,{0x66,0xa1,0,0,0,0});
        std::memcpy(period.expected+2,&period_source,4);hooks.push_back(period);
    }
    auto eases=instruction(healing_eases,0xd7d93,{0xbe,0,0,0,0});
    const auto eases_source=address(at<char>(0x1a54e0));
    std::memcpy(eases.expected+1,&eases_source,4);hooks.push_back(eases);
    auto healed=instruction(healing_complete,0xd7daa,{0xa1,0,0,0,0});
    const auto healed_source=address(at<char>(0x1a54fc));
    std::memcpy(healed.expected+1,&healed_source,4);hooks.push_back(healed);
}
void append(char* destination,const char* input,MessageText tail) {
    const auto previous=message_source_bound(destination);
    const std::string english=std::string(destination)+input;
    message_bind_copy(destination,english.c_str(),native_message_source::concat({previous,std::move(tail)}));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=(event.id>=literal_copy && event.id<=resource_without_marker_third) ||
        (event.id>=row_copy && event.id<=projectile_fourth) ||
        (event.id>=plant_first && event.id<=projectile_period_deflected);
    if(!handled || event.phase!=NativePhase::inline_before)return Status::ok;
    if(event.id>=row_copy && event.id<=projectile_fourth) {
        const auto& copy=selected_copies[event.id-row_copy];
        const auto* input=ptr<char>(event.frame->eax);
        message_bind_copy(ptr<char>(event.frame->ebp-copy.offset),input,message_source_bound(input));
        return Status::ok;
    }
    if(event.id>=plant_first) {
        if(event.id<=plant_last) {
            const auto* input=ptr<char>(event.frame->esi);
            append(ptr<char>(event.frame->ebp-0x408),input,message_source_bound(input));
        } else if(event.id==plant_space) {
            const auto* input=at<char>(0x18c8c0);
            append(ptr<char>(event.frame->ebp-0x408),input,native_message_source::original(input));
        } else if(event.id==projectile_record) {
            if(event.frame->edx!=0)return Status::ok;
            const auto* input=ptr<char>(event.frame->ebp-0x4dc);
            message_bind_copy(at<char>(0xa211b78),input,message_source_bound(input));
        } else if(event.id==projectile_period || event.id==projectile_period_visible || event.id==projectile_period_deflected) {
            const auto* input=at<char>(0x19285c);
            append(at<char>(0xa211b78),input,native_message_source::original(input));
        } else if(event.id==healing_name) {
            const auto* input=ptr<char>(event.frame->esi);
            const std::string english=std::string(":@")+input;
            message_bind_copy(ptr<char>(event.frame->ebp-0x70),english.c_str(),
                native_message_source::concat({native_message_source::original(":@"),message_source_bound(input)}));
        } else {
            const auto* input=at<char>(event.id==healing_eases ? 0x1a54e0 : 0x1a54fc);
            append(ptr<char>(event.frame->ebp-0x70),input,message_source_lookup("healing-tail",input));
        }
        return Status::ok;
    }
    const char* input;
    bool stripped;
    if(event.id<=literal_without_marker) {
        // The native backedge targets the same complete MOV instruction.
        // Capture only its actual first iteration, before any byte is copied.
        if(event.frame->ecx!=0)return Status::ok;
        input=at<char>(0x195d34);stripped=event.id==literal_without_marker;
    } else if(event.id<=stack_without_marker_fourth) {
        if(event.frame->ecx!=0)return Status::ok;
        input=ptr<char>(event.frame->esp+0x798);stripped=event.id>=stack_without_marker_first;
    } else {
        input=ptr<char>(event.frame->esi);stripped=event.id>=resource_without_marker_first;
    }
    auto source=message_source_bound(input);
    if(stripped)source=native_message_source::without_initial_marker(std::move(source));
    message_bind_copy(at<char>(0x2f2c30),input+(stripped ? 1 : 0),std::move(source));
    return Status::ok;
}
}
