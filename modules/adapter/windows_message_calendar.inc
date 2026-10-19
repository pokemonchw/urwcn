// Native 48A310 date construction and 48E4F0 place-context construction.
// Evidence: hud-right-ghidra.c, world-hud-ghidra.c and
// settlement-calendar-context-disassembly.txt. Native record selection,
// calendar arithmetic, coordinates and output buffers remain unchanged.
namespace windows_message_calendar {
enum class Kind:u32 { date,place };
enum Hook:u32 { date_first=0xe900,place_call=0xe906,ordinal_number,ordinal_debug,
    ordinal_last,day_format,debug_day_format,moon_call,date_on,date_day,
    date_full_on,date_full,date_short,place_culture,place_at,place_format };
const u32 date_calls[]={0x17231c,0x172340,0x172364,0x172388,0x1723ac,0x1723d0};
struct Frame {
    Kind kind{};u32 parent{},pending_owner{};
    MessageText body,ordinal,day,moon,prefix,place,pending;
};
std::vector<Frame> frames;
bool owns(const NativeEvent& event) {
    return !frames.empty() && *ptr<u32>(event.frame->ebp)==frames.back().parent;
}
MessageText pattern(const char* source,std::vector<MessageText> values,std::vector<std::string> conversions) {
    return native_message_source::format(message_source_lookup("calendar.format",source),
        std::move(values),std::move(conversions));
}
MessageText number(u32 value) {
    return native_message_source::scalar(native_message_source::Scalar::signed32,value,"%d");
}
void observe_geography(u32 site,const MessageText& source) {
    if(frames.empty() || frames.back().kind!=Kind::place)return;
    auto& frame=frames.back();
    if(site==0x8e637)frame.prefix=native_message_source::concat({std::move(frame.prefix),source});
    if(site==0x8e6a3)frame.place=source;
}
void save(std::vector<unsigned char>& state) {
    message_state_write(state,static_cast<u32>(frames.size()));
    for(const auto& frame:frames) {
        message_state_write(state,frame.kind);message_state_write(state,frame.parent);
        message_state_write(state,frame.pending_owner);
        for(const auto* source:{&frame.body,&frame.ordinal,&frame.day,&frame.moon,&frame.prefix,&frame.place,&frame.pending})
            native_message_source::write(state,*source);
    }
}
void restore(const unsigned char*& state) {
    u32 count{};message_state_read(state,count);frames.resize(count);
    for(auto& frame:frames) {
        message_state_read(state,frame.kind);message_state_read(state,frame.parent);
        message_state_read(state,frame.pending_owner);
        for(auto* source:{&frame.body,&frame.ordinal,&frame.day,&frame.moon,&frame.prefix,&frame.place,&frame.pending})
            *source=native_message_source::read(state);
    }
}
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::native_call;using native_name_input::instruction;
    for(u32 i=0;i<std::size(date_calls);++i)
        hooks.push_back(native_call(date_first+i,date_calls[i],0x8a310,52));
    hooks.push_back(native_call(place_call,0x1772e8,0x8e4f0,1));
    struct Call {u32 id,site,words;};
    for(const auto& call:{Call{ordinal_number,0x8a38b,3},Call{ordinal_debug,0x8a3ae,3},
        Call{day_format,0x8a4a3,5},Call{debug_day_format,0x8a4cc,4},
        Call{date_full_on,0x8a57f,5},Call{date_full,0x8a5a0,5},Call{date_short,0x8a5e1,4},
        Call{place_culture,0x8e61a,3},Call{place_format,0x8e6b9,4}})
        hooks.push_back(native_call(call.id,call.site,0x10d0,call.words));
    hooks.push_back(native_call(moon_call,0x8a4e2,0x15e910,0));
    auto last=instruction(ordinal_last,0x8a474,{0xa1,0,0,0,0});
    const auto last_word=address(at<char>(0x19cf94));std::memcpy(last.expected+1,&last_word,4);hooks.push_back(last);
    hooks.push_back(instruction(date_on,0x8a50f,{0xc7,0x03,0x6f,0x6e,0x20,0x00}));
    hooks.push_back(instruction(date_day,0x8a515,{0x8d,0x95,0x90,0xfb,0xff,0xff}));
    auto at_word=instruction(place_at,0x8e68a,{0xa1,0,0,0,0});
    const auto at_text=address(at<char>(0x19d368));std::memcpy(at_word.expected+1,&at_text,4);hooks.push_back(at_word);
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=date_first && event.id<=place_format;if(!handled)return Status::ok;
    if(event.id<=place_call) {
        if(event.phase==NativePhase::before) {
            Frame frame;frame.kind=event.id==place_call?Kind::place:Kind::date;
            frame.parent=event.frame->ebp;frames.push_back(std::move(frame));
        } else {
            auto frame=std::move(frames.back());frames.pop_back();
            message_bind_source(ptr<char>(event.frame->eax),std::move(frame.body));
        }
        return Status::ok;
    }
    // These producers also serve native HUD calls. Only the observed shared
    // message caller owns the semantic construction scope.
    if(!owns(event))return Status::ok;
    auto& frame=frames.back();
    if(event.id==ordinal_last) {
        frame.ordinal=message_source_lookup("calendar.ordinal","last");return Status::ok;
    }
    if(event.id==date_on) {frame.prefix=message_source_lookup("calendar.part","on ");return Status::ok;}
    if(event.id==date_day) {
        frame.body=native_message_source::concat({frame.prefix,frame.day});return Status::ok;
    }
    if(event.id==place_at) {
        frame.prefix=native_message_source::concat({std::move(frame.prefix),message_source_lookup("calendar.part"," at ")});
        return Status::ok;
    }
    if(event.id==moon_call) {
        if(event.phase==NativePhase::after) {
            const auto* source=ptr<char>(event.frame->eax);
            frame.moon=message_source_lookup("calendar.moon",source);message_bind_source(source,frame.moon);
        }
        return Status::ok;
    }
    if(event.phase==NativePhase::after) {
        const auto* output=ptr<char>(frame.pending_owner);
        frame.pending.original=message_source_utf8(output);message_bind_source(output,frame.pending);
        if(event.id==ordinal_number || event.id==ordinal_debug)frame.ordinal=frame.pending;
        else if(event.id==day_format || event.id==debug_day_format)frame.day=frame.pending;
        else if(event.id==place_culture)frame.prefix=frame.pending;
        else frame.body=frame.pending;
        return Status::ok;
    }
    frame.pending_owner=event.arguments[0];const auto* source=ptr<char>(event.arguments[1]);
    if(event.id==ordinal_number || event.id==ordinal_debug) {
        frame.pending=native_message_source::format(message_source_lookup("calendar.ordinal",source),
            {number(event.arguments[2])},{"%d"});
    } else if(event.id==day_format) {
        // The native ordinal suffix has now been appended, or 'last' selected.
        frame.ordinal.original=message_source_utf8(ptr<char>(event.arguments[3]));
        // Chinese states the selected season, week, then day. The root's
        // original is assigned from this same native sprintf result after
        // execution, while the typed operands retain their proven sources.
        frame.pending={};frame.pending.kind=native_message_source::Kind::format;
        frame.pending.children={message_source_lookup("calendar.format",source),
            message_source_lookup("calendar.season",ptr<char>(event.arguments[4])),frame.ordinal,number(event.arguments[2])};
        frame.pending.syntax={"%s","%s","%d"};
    } else if(event.id==debug_day_format) {
        frame.ordinal.original=message_source_utf8(ptr<char>(event.arguments[2]));
        frame.pending=pattern(source,{frame.ordinal,number(event.arguments[3])},{"%s","%d"});
    } else if(event.id==place_culture) {
        frame.pending=pattern(source,{message_source_lookup("identity",ptr<char>(event.arguments[2]))},{"%s"});
    } else if(event.id==place_format) {
        frame.pending=pattern(source,{frame.prefix,frame.place},{"%s","%s"});
    } else {
        std::vector<MessageText> parts{message_source_lookup("calendar.season",ptr<char>(event.arguments[2])),frame.moon};
        if(event.id!=date_short)parts.push_back(frame.day);
        const auto count=parts.size();frame.pending=pattern(source,std::move(parts),std::vector<std::string>(count,"%s"));
    }
    return Status::ok;
}
}
