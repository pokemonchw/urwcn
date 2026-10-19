// 526F70 assembles the chosen combat narrative before 527A7C -> 4FDCB0.
// These are the actual native copy/append branches, including the later
// severity messages at 528305 and 528400. No combat decision is repeated.
namespace windows_message_combat_body {
constexpr u32 first_copy=0xf400,first_append=0xf440,first_punctuation=0xf480;
constexpr u32 projectile_copy=0xf490,attack_result=0xf491;
struct Copy {u32 site,offset;};
const Copy copies[]={
    {0x126fd0,0x474},{0x126ff9,0x474},{0x12701a,0x474},{0x12703b,0x474},
    {0x1270c8,0x8dc},{0x1270e9,0x8dc},{0x127113,0x8dc},{0x127139,0x8dc},
    {0x127314,0x8dc},{0x12733c,0x8dc},{0x12736c,0x8dc},
    {0x127391,0x8dc},{0x1273b9,0x8dc},
    {0x1281f3,0x474},{0x128219,0x474},{0x12823a,0x474},
    {0x12827c,0x474},{0x12829d,0x474},{0x1282be,0x474},{0x1282df,0x474},
    {0x128393,0x474},{0x1283b9,0x474},{0x1283da,0x474}
};
const u32 appends[]={
    0x127188,0x1272b8,0x127408,
    0x12747b,0x1274b8,0x1274f8,0x127538,
    0x1275b8,0x127628,0x127678,0x1276b8,0x1276f8,
    0x127750,0x127789,0x1277c8,0x127808,
    0x127868,0x1278a8,0x1278e8,0x127928,
    0x127978,0x1279b8,0x1279f8,0x127a2e
};
struct Punctuation {u32 site,source;};
const Punctuation punctuation[]={
    {0x12708f,0x18c8c0},{0x1271aa,0x18c8c0},{0x1271ca,0x1a64dc},
    {0x1272e1,0x18c8c0},{0x12742a,0x18c8c0},{0x127a4a,0x19285c}
};
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    for(u32 index=0;index<std::size(copies);++index) {
        auto hook=instruction(first_copy+index,copies[index].site,{0x8d,0x95,0,0,0,0});
        const u32 displacement=0u-copies[index].offset;
        std::memcpy(hook.expected+2,&displacement,4);hooks.push_back(hook);
    }
    for(u32 index=0;index<std::size(appends);++index)
        hooks.push_back(instruction(first_append+index,appends[index],{0x8b,0xca,0xc1,0xe9,0x02}));
    for(u32 index=0;index<std::size(punctuation);++index) {
        auto hook=instruction(first_punctuation+index,punctuation[index].site,{0x66,0xa1,0,0,0,0});
        const auto input=address(at<char>(punctuation[index].source));
        std::memcpy(hook.expected+2,&input,4);hooks.push_back(hook);
    }
    auto projectile=instruction(projectile_copy,0x127060,{0x8a,0x81,0,0,0,0});
    const auto projectile_owner=address(at<char>(0xa211b78));
    std::memcpy(projectile.expected+2,&projectile_owner,4);hooks.push_back(projectile);
    auto result=instruction(attack_result,0x127b30,{0x0f,0xb6,0x05,0,0,0,0});
    const auto flag=address(at<unsigned char>(0x4d8f4f2));
    std::memcpy(result.expected+3,&flag,4);hooks.push_back(result);
}
void append(char* destination,const char* input,MessageText tail) {
    const auto prior=message_source_bound(destination);
    const std::string english=std::string(destination)+input;
    message_bind_copy(destination,english.c_str(),
        native_message_source::concat({prior,std::move(tail)}));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=(event.id>=first_copy && event.id<first_copy+std::size(copies)) ||
        (event.id>=first_append && event.id<first_append+std::size(appends)) ||
        (event.id>=first_punctuation && event.id<first_punctuation+std::size(punctuation)) ||
        event.id==projectile_copy || event.id==attack_result;
    if(!handled || event.phase!=NativePhase::inline_before)return Status::ok;
    auto* body=ptr<char>(event.frame->ebp-0x474);
    if(event.id>=first_copy && event.id<first_copy+std::size(copies)) {
        const auto& copy=copies[event.id-first_copy];
        const auto* input=ptr<char>(event.frame->eax);
        message_bind_copy(ptr<char>(event.frame->ebp-copy.offset),input,message_source_bound(input));
    } else if(event.id>=first_append && event.id<first_append+std::size(appends)) {
        const auto* input=ptr<char>(event.frame->esi);
        append(body,input,message_source_bound(input));
    } else if(event.id>=first_punctuation && event.id<first_punctuation+std::size(punctuation)) {
        const auto* input=at<char>(punctuation[event.id-first_punctuation].source);
        append(body,input,native_message_source::original(input));
    } else if(event.id==projectile_copy) {
        // The byte-copy backedge targets this complete MOV. Its ECX=0
        // iteration is the actual source-copy entry for this invocation.
        if(event.frame->ecx==0) {
            const auto* input=at<char>(0xa211b78);
            message_bind_copy(body,input,message_source_bound(input));
        }
    } else {
        // 527B2B has completed "ATTACK_RESULT: %s%d". The first operand is
        // the chosen native outcome code (also consumed by strstr below),
        // and EBX still holds the same numeric outcome. Preserve both values.
        auto source=native_message_source::format(
            message_source_template("format.005b0438",at<char>(0x1b0438)),
            {message_source_identity(ptr<char>(event.frame->ebp-0x874)),
             native_message_source::scalar(native_message_source::Scalar::signed32,event.frame->ebx,"%d")},
            {"%s","%d"});
        message_bind_source(body,std::move(source));
    }
    return Status::ok;
}
}
