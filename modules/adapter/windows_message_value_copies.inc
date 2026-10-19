// The combat record stores weapon/bodypart strings at +164/+22c. Its actual
// rep-movs and immediate string-copy exits carry source expressions with it.
// Evidence: settlement-tag-source-writers.tsv and native 52C110/52E370/52FCB0.
constexpr u32 first_combat_copy=0xc900;
struct CombatCopy {u32 site,destination;unsigned char opcode;};
const CombatCopy combat_copies[]={
    {0x128dbb,0x1e9bb0,0xba},{0x12b1e1,0x1e9e88,0xba},
    {0x12c4af,0xa21244c,0xbe},{0x12cafe,0xa21244c,0xba},
    {0x12cde7,0xa21244c,0xba},{0x12ce27,0xa21244c,0xba},
    {0x12d67e,0xa212514,0xba},{0x12f300,0xa21244c,0xba},
    {0x12fe31,0x1e9ce8,0xba},{0x1302d1,0xa2127a4,0xba}
};
enum CombatHook:u32 {combat_record_attack=0xc920,combat_record_defend,
    combat_record_counter,combat_attack_fields,combat_changed_bodypart,
    combat_defend_weapon,combat_counter_fields};
void append_value_copy_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    for(u32 i=0;i<sizeof(combat_copies)/sizeof(combat_copies[0]);++i) {
        const auto& copy=combat_copies[i];
        auto hook=instruction(first_combat_copy+i,copy.site,{copy.opcode,0,0,0,0});
        const auto destination=address(at<char>(copy.destination));
        std::memcpy(hook.expected+1,&destination,4);hooks.push_back(hook);
    }
    hooks.push_back(instruction(combat_record_attack,0x12fdc8,{0xba,1,0,0,0}));
    hooks.push_back(instruction(combat_record_defend,0x1303e4,{0xb9,0xa4,0,0,0}));
    hooks.push_back(instruction(combat_record_counter,0x1304e3,{0xb9,0xa4,0,0,0}));
    // Both native field copies are complete. Keep the preceding PUSH native;
    // inline replay observes only this complete LEA and does not adjust ESP.
    hooks.push_back(instruction(combat_attack_fields,0x12fec8,{0x8d,0x84,0x24,0x6c,2,0,0}));
    auto changed=instruction(combat_changed_bodypart,0x130303,{0xbf,0,0,0,0});
    const auto target=address(at<char>(0xa211b78));std::memcpy(changed.expected+1,&target,4);hooks.push_back(changed);
    hooks.push_back(instruction(combat_defend_weapon,0x1303fa,{0x33,0xc9,0x0f,0x1f,0x40,0}));
    hooks.push_back(instruction(combat_counter_fields,0x1304e8,{0xbe,0,0,0,0}));
    const auto source=address(at<char>(0xa2122e8));std::memcpy(hooks.back().expected+1,&source,4);
    // A243D's terrain article copy belongs to windows_message_format_builders;
    // that shared native entry has one Hook and one source-binding consumer.
}
void copy_record_sources(u32 destination,u32 origin) {
    for(const u32 offset:{0x164u,0x22cu}) {
        const auto* input=at<char>(origin+offset);
        message_bind_copy(at<char>(destination+offset),input,source("bound",input));
    }
}
void copy_combat_field(u32 destination,u32 origin) {
    message_bind_source(at<char>(destination),source("bound",at<char>(origin)));
}
Status dispatch_value_copy(const NativeEvent& event,bool& handled) {
    handled=(event.id>=first_combat_copy && event.id<first_combat_copy+sizeof(combat_copies)/sizeof(combat_copies[0])) ||
        (event.id>=combat_record_attack && event.id<=combat_counter_fields);
    if(!handled || event.phase!=NativePhase::inline_before) return Status::ok;
    if(event.id<combat_record_attack) {
        const auto* input=ptr<char>(event.frame->eax);
        message_bind_copy(at<char>(combat_copies[event.id-first_combat_copy].destination),input,source("bound",input));
    } else if(event.id==combat_record_attack) copy_record_sources(0xa212578,0xa2122e8);
    else if(event.id==combat_record_defend || event.id==combat_record_counter) copy_record_sources(0xa211fa8,0xa2122e8);
    else if(event.id==combat_attack_fields) {
        copy_combat_field(0x1e9e88,0xa2126dc);copy_combat_field(0x1e9db8,0xa2127a4);
    } else if(event.id==combat_changed_bodypart) copy_combat_field(0x1e9db8,0xa2127a4);
    else if(event.id==combat_defend_weapon) {
        const auto* input=at<char>(0xa21210c);
        message_bind_copy(at<char>(0x1e9c80),input,source("bound",input));
    } else if(event.id==combat_counter_fields) {
        copy_combat_field(0x1e9c80,0xa21244c);copy_combat_field(0x1e9d50,0xa212514);
    }
    return Status::ok;
}
