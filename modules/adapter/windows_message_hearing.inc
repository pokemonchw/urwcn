// Native 4FDCB0/4FE030 selected-source copies. Each observation immediately
// precedes an unconditional NUL-terminated copy with no intervening call.
// All visibility, FORCE_HEAR/ALWAYS_HEAR and distance decisions stay native.
namespace windows_message_hearing {
enum Hook:u32 { direct_body=0xed00,npc_default_hear,npc_explicit_hear,
    npc_forced_hear,npc_always_hear,npc_visible,npc_heard,
    point_default_hear,point_explicit_hear,point_forced_hear,
    point_always_hear,point_visible,point_heard };
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    hooks.push_back(instruction(direct_body,0xfdce8,{0x8d,0x8d,0xf4,0xf7,0xff,0xff}));
    hooks.push_back(instruction(npc_default_hear,0xfdd4b,{0x33,0xc9,0x0f,0x1f,0x00}));
    hooks.push_back(instruction(npc_explicit_hear,0xfdd66,{0x8d,0x95,0xf4,0xfb,0xff,0xff}));
    hooks.push_back(instruction(npc_forced_hear,0xfddaf,{0x33,0xc9,0x0f,0x1f,0x40,0x00}));
    hooks.push_back(instruction(npc_always_hear,0xfddfb,{0x33,0xc9,0x0f,0x1f,0x00}));
    auto npc=instruction(npc_visible,0xfdecd,{0xb9,0,0,0,0});
    const auto body=address(at<char>(0xa40eb70));
    std::memcpy(npc.expected+1,&body,4);hooks.push_back(npc);
    hooks.push_back(instruction(npc_heard,0xfdfb2,{0x33,0xc9,0x0f,0x1f,0x40,0x00}));
    hooks.push_back(instruction(point_default_hear,0xfe0b0,{0x33,0xc9,0x0f,0x1f,0x40,0x00}));
    hooks.push_back(instruction(point_explicit_hear,0xfe0d6,{0x8d,0x95,0xf4,0xfb,0xff,0xff}));
    hooks.push_back(instruction(point_forced_hear,0xfe11f,{0x33,0xc9,0x0f,0x1f,0x40,0x00}));
    hooks.push_back(instruction(point_always_hear,0xfe16b,{0x33,0xc9,0x0f,0x1f,0x00}));
    auto point=instruction(point_visible,0xfe1a7,{0xba,0,0,0,0});
    std::memcpy(point.expected+1,&body,4);hooks.push_back(point);
    hooks.push_back(instruction(point_heard,0xfe22f,{0x33,0xc9,0x0f,0x1f,0x40,0x00}));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=direct_body && event.id<=point_heard;
    if(!handled)return Status::ok;
    const char* source{};const char* destination{};
    switch(event.id) {
    case direct_body:
        source=ptr<char>(event.frame->esi);destination=ptr<char>(event.frame->ebp-0x80c);break;
    case npc_default_hear:case npc_forced_hear:case npc_always_hear:
    case point_default_hear:case point_forced_hear:case point_always_hear:
        source=at<char>(0xa2248b8);destination=ptr<char>(event.frame->ebp-0x40c);break;
    case npc_explicit_hear:
        source=ptr<char>(event.frame->edi);destination=ptr<char>(event.frame->ebp-0x40c);break;
    case point_explicit_hear:
        source=ptr<char>(event.frame->esi);destination=ptr<char>(event.frame->ebp-0x40c);break;
    case npc_visible:
        source=ptr<char>(event.frame->esi);destination=at<char>(0xa40eb70);break;
    case point_visible:
        source=ptr<char>(event.frame->ecx);destination=at<char>(0xa40eb70);break;
    case npc_heard:case point_heard:
        source=ptr<char>(event.frame->ebp-0x40c);destination=at<char>(0xa40eb70);break;
    }
    message_bind_copy(destination,source,message_source_bound(source));
    return Status::ok;
}
}
