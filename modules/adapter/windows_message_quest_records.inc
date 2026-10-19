// Native F1E0 quest records: type at +4 and title at +31. The game keeps
// its English record, file format and quest decisions. Only title source
// expressions follow the confirmed construction, memcpy and fread boundaries.
Status message_material_source(const char*,MessageText&);
namespace windows_message_quest_records {
using Text=native_message_source::Text;
enum Hook:u32 { forest_subject_copy=0xe120,forest_format,forest_case,
    record_copy,record_loaded,debug_record_loaded };
struct Copy {u32 owner;Text title;Status status=Status::ok;};
std::vector<Copy> copies;
std::vector<Copy> titles;
std::vector<Text> capitalized;
void save(std::vector<unsigned char>& output) {
    for(const auto* collection:{&copies,&titles}) {
        message_state_write(output,static_cast<u32>(collection->size()));
        for(const auto& value:*collection) {message_state_write(output,value.owner);native_message_source::write(output,value.title);message_state_write(output,value.status);}
    }
    message_state_write(output,static_cast<u32>(capitalized.size()));
    for(const auto& value:capitalized) native_message_source::write(output,value);
}
void restore(const unsigned char*& input) {
    for(auto* collection:{&copies,&titles}) {
        u32 count;message_state_read(input,count);collection->clear();
        for(u32 index=0;index<count;++index) {
            Copy value;message_state_read(input,value.owner);value.title=native_message_source::read(input);
            message_state_read(input,value.status);collection->push_back(std::move(value));
        }
    }
    u32 count;message_state_read(input,count);capitalized.clear();
    for(u32 index=0;index<count;++index) capitalized.push_back(native_message_source::read(input));
}

Text title_format(const char* key,const char* pattern,std::vector<Text> arguments) {
    const auto count=arguments.size();
    return native_message_source::format(message_source_template(key,pattern),
        std::move(arguments),std::vector<std::string>(count,"%s"));
}
Status bind_record(const char* record) {
    const auto type=*reinterpret_cast<const unsigned short*>(record+4);
    const auto* title=record+31;
    const std::string english=title;
    switch(type) {
    case 3: // 547780: selected 43A070 descriptor's base item name, +9.
        message_bind_source(title,message_source_value("item",title));return Status::ok;
    case 5: { // 54DCD0 admits native generated names as well as stock items.
        Text item;
        const auto status=message_material_source(english.substr(13).c_str(),item);
        if(status!=Status::ok)return status;
        message_bind_source(title,title_format("format.005be030","Adventurer's %s",
            {std::move(item)}));return Status::ok;
    }
    case 35: { // Keep the source captured by the native fresh-title construction.
        const auto captured=windows_messages::values.find(address(title));
        if(captured!=windows_messages::values.end() && captured->second.source==english)return Status::ok;
        // Successful read hooks erase the previous record before this path.
        // 542D30 excludes player-owned animals; 543340 naming requires ownership.
        message_bind_source(title,title_format("format.005c9460","%s in the forest cover",
            {message_source_value("npc",english.substr(0,english.size()-20).c_str())}));return Status::ok;
    }
    case 37: { // 54D542: two entries from the 14-slot 58E3C4 culture table.
        const auto separator=english.find(" to ",5);
        message_bind_source(title,title_format("format.005bd700","From %s to %s",{
            message_source_value("quest.culture",english.substr(5,separator-5).c_str()),
            message_source_value("quest.culture",english.substr(separator+4).c_str())}));return Status::ok;
    }
    case 38: // 55086F: the NPC record's class at +8, never its proper name.
        message_bind_source(title,title_format("format.005c1a0c","Disoriented %s",
            {message_source_value("npc",english.substr(12).c_str())}));return Status::ok;
    case 40: // 54A055: exactly "nice knives" or "quality arrows".
        message_bind_source(title,title_format("format.005b8250","Need for %s",
            {message_source_lookup("quest.need",english.substr(9).c_str())}));return Status::ok;
    case 10:case 15:case 20:case 30:case 50:case 51:case 52:case 70:case 71:case 72:
        message_bind_source(title,message_source_lookup("quest.title",title));return Status::ok;
    }
    return Status::ok;
}
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::native_call;
    using native_name_input::instruction;
    hooks.push_back(instruction(forest_subject_copy,0x1551b7,{0x8d,0x55,0x8c,0x2b,0xd0}));
    hooks.push_back(native_call(forest_format,0x1553ec,0x10d0,3));
    hooks.push_back(instruction(forest_case,0x155410,{0xb8,0x23,0,0,0}));
    hooks.push_back(native_call(record_copy,0x1578b4,0x18b5a0,3));
    // The successful fopen path has completed fread. Hook the complete
    // fclose IAT CALL, before native cdecl argument cleanup and the shared
    // 579660 join. No replayed instruction adjusts ESP.
    const auto close_iat=address(at<u32>(0x18c4b4));
    for(const auto pair:{std::pair<u32,u32>{record_loaded,0x157518},
                         {debug_record_loaded,0x179657}}) {
        auto hook=instruction(pair.first,pair.second,{0xff,0x15,0,0,0,0});
        std::memcpy(hook.expected+2,&close_iat,4);hooks.push_back(hook);
    }
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=forest_subject_copy && event.id<=debug_record_loaded;
    if(!handled)return Status::ok;
    if(event.id==forest_subject_copy && event.phase==NativePhase::inline_before) {
        const auto* subject=ptr<char>(event.frame->eax);
        message_bind_copy(ptr<char>(event.frame->ebp-0x74),subject,message_source_bound(subject));
    } else if(event.id==forest_format) {
        if(event.phase==NativePhase::before) {
            titles.push_back({event.arguments[0],title_format("format.005c9460",
                ptr<char>(event.arguments[1]),{message_source_bound(ptr<char>(event.arguments[2]))})});
        } else if(event.phase==NativePhase::after) {
            auto title=std::move(titles.back());titles.pop_back();
            message_bind_source(ptr<char>(title.owner),title.title);
            capitalized.push_back(std::move(title.title));
        }
    } else if(event.id==forest_case && event.phase==NativePhase::inline_before) {
        // 55540B has just applied the native first-byte toupper result.
        message_bind_source(at<char>(0xa41e1ef),std::move(capitalized.back()));capitalized.pop_back();
    } else if(event.id==record_copy) {
        if(event.phase==NativePhase::before) {
            const auto* source=ptr<char>(event.arguments[1]);const auto status=bind_record(source);
            Copy copy{event.arguments[0]+31,{},status};
            if(status==Status::ok)copy.title=message_source_bound(source+31);
            // The native memcpy still has one matching return event, even
            // when its source expression cannot be projected.
            copies.push_back(std::move(copy));return status;
        } else if(event.phase==NativePhase::after) {
            auto copy=std::move(copies.back());copies.pop_back();
            if(copy.status==Status::ok)message_bind_source(ptr<char>(copy.owner),std::move(copy.title));
            return copy.status;
        }
    } else if(event.id==record_loaded && event.phase==NativePhase::inline_before) {
        const auto* record=ptr<char>(event.frame->edi);
        // Successful fread replaces the record occupying this native buffer.
        windows_messages::values.erase(address(record+31));return bind_record(record);
    } else if(event.id==debug_record_loaded && event.phase==NativePhase::inline_before) {
        const auto* record=ptr<char>(event.frame->esp+0xb1bc);
        windows_messages::values.erase(address(record+31));return bind_record(record);
    }
    return Status::ok;
}
}
