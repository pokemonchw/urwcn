// Dedicated native message concatenation boundaries, Windows 3.89.
// 461CF0 constructs a tool suitability clause in EBP-870, then appends the
// quality clause from EBP-470 at either 46232D..46235B or 4623BB..4623E9.
// The native copy loops contain no calls or input waits. Only their translated
// text companion is carried between the two boundaries; native bytes are intact.
namespace windows_message_format_builders {
enum Hook : u32 { quality_begin=0xe400,quality_end,quality_low_begin,quality_low_end,
    requirement_inventory_begin,requirement_inventory_end,
    requirement_nearby_begin,requirement_nearby_end,
    requirement_store_first=0xe420,requirement_store_last=0xe424,
    requirement_list_first=0xe430,requirement_list_last=0xe431 };
struct Append { u32 destination; Status status; std::string translated; };
std::vector<Append> appends;

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
}

Status requirement_list(u32 selector,std::string& output) {
    const auto* table=at<char>(selector==1 ? 0x14fbcc8 : 0x14fe440);
    for(u32 row=0;row<100;++row) {
        const auto* source=table+row*100;
        if(!*source) continue;
        std::string item;
        const auto status=message_translate_bound(source,item);
        if(status!=Status::ok) return status;
        output+=item;
        // 4687DF/4688A5 use the next two actual slots, only below slot 98.
        if(row<98 && source[100]) output+=source[200] ? "、" : "和";
    }
    return Status::ok;
}

Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=(event.id>=quality_begin && event.id<=requirement_nearby_end) ||
        (event.id>=requirement_store_first && event.id<=requirement_store_last) ||
        (event.id>=requirement_list_first && event.id<=requirement_list_last);
    if(!handled || !chinese_enabled) return Status::ok;
    if(event.id>=requirement_store_first) {
        if(event.phase==NativePhase::before) {
            appends.push_back({0,Status::ok,{}});
            auto& current=appends.back();
            if(event.id>=requirement_list_first)
                current.status=requirement_list(event.frame->ecx,current.translated);
            else {
                const auto* source=ptr<char>(event.frame->ecx);
                // 468679/46867D: empty input or selector 0 clears both tables.
                if(*source && event.frame->edx) {
                    const bool nearby=event.frame->edx==2;
                    const auto index=*at<u32>(nearby ? 0xa44b784 : 0xa44b780);
                    current.destination=address(at<char>(nearby ? 0x14fe440 : 0x14fbcc8)+index*100);
                    current.status=message_translate_bound(source,current.translated);
                }
            }
            return current.status;
        }
        auto current=std::move(appends.back());
        appends.pop_back();
        if(event.id>=requirement_list_first) current.destination=event.frame->eax;
        if(current.destination && current.status==Status::ok)
            message_bind_value(ptr<char>(current.destination),current.translated);
        return current.status;
    }
    if(event.phase==NativePhase::after) return Status::ok;
    if(event.id==requirement_inventory_begin || event.id==requirement_nearby_begin) {
        appends.push_back({event.frame->ebp-0x408,Status::ok,{}});
        auto& current=appends.back();
        current.status=message_translate_bound(ptr<char>(event.frame->eax),current.translated);
        return current.status;
    }
    if(event.id==quality_begin || event.id==quality_low_begin) {
        const auto destination=event.frame->ebp-0x870;
        const auto* prefix=ptr<char>(destination);
        const auto* suffix=ptr<char>(event.frame->ebp-0x470);
        appends.push_back({destination,Status::ok,{}});
        auto& current=appends.back();
        // Native 461DB7 initially clears this clause. The no-item branch may
        // append to that empty clause before 46242C discards it again.
        if(*prefix) current.status=message_translate_bound(prefix,current.translated);
        if(current.status!=Status::ok) return current.status;
        // 462316/462326 and 4623A4/4623B4 explicitly construct this alternative.
        if(suffix[0]=='.' && suffix[1]==0) current.translated+="。";
        else {
            std::string quality;
            current.status=message_translate_bound(suffix,quality);
            if(current.status==Status::ok) current.translated+=quality;
        }
        return current.status;
    }
    auto current=std::move(appends.back());
    appends.pop_back();
    if(current.status==Status::ok)
        message_bind_value(ptr<char>(current.destination),current.translated);
    return current.status;
}
}
