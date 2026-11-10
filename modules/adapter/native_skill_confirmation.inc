// Choose_SkillOptions confirmation: original native construction and Menu
// storage provide the entire display. No page layout or pixels are retained.
namespace native_skill_confirmation {
enum Hook:u32 { frame_entry=0x5150,frame_draw };
bool constructing{};

void append_hooks(std::vector<HookSpec>& hooks) {
    auto entry=inline_hook(frame_entry,0x121BF,{0xA1,0,0,0,0});
    const auto surface=address(at<void>(0x61BBB10));
    std::memcpy(entry.expected+1,&surface,4);hooks.push_back(entry);
    // This actual CALL return is also the balanced native fragment endpoint.
    hooks.push_back(call(frame_draw,0x12250,0xCFFB0,0));
}

Status menu(const NativeEvent& event,bool& rebuilt,u32&) {
    using View=native_language_redraw::View;
    if(!native_language_redraw::pending(View::skills) ||
       *ptr<const u32>(event.frame->ebp+4)!=host->image_base+0x1225A)
        return Status::ok;

    u32 selected{},skill_rows{};
    {
        // The real MENULIST.SAV owner is retained by native_menu_storage.
        // CF790's departure captured its latest selection before replacing
        // the shared native ranges with the current confirmation Menu.
        const auto& source=native_menu_model::paint_records(native_menu_storage::stored_menu());
        std::memcpy(&selected,source.header.data()+0x90,4);
        std::memcpy(&skill_rows,source.header.data()+0x9C,4);
    }

    // 3CA90 writes this exact English lookup argument plus a newline to the
    // game's GFX.NFO (3CAA6..3CAD9) before constructing the skill preview.
    // The confirmation path has not replaced that native semantic resource.
    // It preserves the last real preview independently of an F1/Exit choice.
    char topic[100];
    auto* source=std::fopen(at<char>(0x194F98),"rt");
    std::fgets(topic,sizeof(topic),source);
    std::fclose(source);
    topic[std::strcspn(topic,"\r\n")]=0;
    u32 preview=0;
    for(;preview<skill_rows;++preview) {
        const auto skill=at<u32>(0x5F937B8)[preview];
        if(std::strncmp(topic,at<char>(0xA32A708+skill*12),12)==0) break;
    }

    auto status=native_full_language::construct_skills(1,preview);
    if(status!=Status::ok) return status;
    *at<u32>(0x5F54AB0)=selected;
    reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0xD0650)(selected,0);

    // 121BA first clears the original native hotspot-registration table
    // (FFAA0), exactly as the ordinary confirmation construction does.
    // 121BF..12255 then constructs its complete Menu and background. No
    // outer EBP operand occurs in this balanced fragment. The real input
    // frame and its original selected confirmation row remain suspended.
    constructing=true;
    status=host->native_fragment(0x121BA,0x12255);
    constructing=false;
    if(status!=Status::ok) return status;
    native_language_redraw::completed(View::skills);
    rebuilt=true;
    return Status::ok;
}

Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=false;
    if(event.id==frame_entry && constructing) {
        // The original enclosing 12160 frame loads this same IAT at 121A5.
        // Supply that confirmed caller input to the short native fragment.
        event.frame->esi=*at<u32>(0x18C1F8);
        event.frame->eax=*at<u32>(0x61BBB10);
        result.resume_rva=0x121C4;
        handled=true;
    }
    return Status::ok;
}
}
