// PE 3.89: 587300 constructs a finite weather description; 587AB0 joins
// exactly two descriptions at its native stringstream append sites. Recover
// that completed English expression at the final copy, without repeating
// weather arithmetic or retaining a translated forecast/state snapshot.
namespace windows_message_weather {
enum Hook:u32 { forecast_copy=0xef00,message_copy };

Status source(const char* native,MessageText& output) {
    const std::string english=message_source_utf8(native);
    struct Form { u32 first,second;const char* separator; };
    // 587E1B..587E8F: day + space + night.
    // 587E70..587EE2: night + tomorrow (whose native prefix starts with space).
    for(const auto& form:{Form{0x1dcf60,0x1dcf88," "},Form{0x1dcf88,0x1dcfb4,""}}) {
        const std::string first=at<char>(form.first),second=at<char>(form.second);
        if(english.compare(0,first.size(),first)!=0)continue;
        const std::string join=std::string(form.separator)+second;
        const auto boundary=english.find(join,first.size());
        if(boundary==std::string::npos)continue;
        const auto before=english.substr(first.size(),boundary-first.size());
        const auto after=english.substr(boundary+join.size());
        output=native_message_source::concat({
            message_source_lookup("weather.period",first.c_str()),
            message_source_lookup("weather.description",before.c_str()),
            native_message_source::original(form.separator),
            message_source_lookup("weather.period",second.c_str()),
            message_source_lookup("weather.description",after.c_str())});
        output.original=english;return Status::ok;
    }
    return Status::unavailable;
}

void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    // The copy loop backedge targets 587F86; no instruction from that loop
    // is included in this six-byte observer. EDI already holds string capacity.
    hooks.push_back(instruction(forecast_copy,0x187f75,{0x8d,0x55,0xc0,0x8b,0x4d,0xc0}));
    // The following loop starts at 521D94, exactly after this hook span.
    hooks.push_back(instruction(message_copy,0x121d8f,{0x8d,0x14,0x24,0x2b,0xd0}));
}

Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=forecast_copy && event.id<=message_copy;
    if(!handled || event.phase!=NativePhase::inline_before)return Status::ok;
    if(event.id==message_copy) {
        const auto* native=ptr<char>(event.frame->eax);
        message_bind_copy(ptr<char>(event.frame->esp),native,message_source_bound(native));
        return Status::ok;
    }
    // This is the native std::string storage choice at 587F7B/587F83.
    const u32 storage=event.frame->ebp-0x40;
    const auto* native=ptr<char>(event.frame->edi>=0x10 ? *ptr<u32>(storage) : storage);
    MessageText expression;const auto status=source(native,expression);
    if(status!=Status::ok)return status;
    message_bind_copy(at<char>(0xa641ee0),native,std::move(expression));
    return Status::ok;
}
}
