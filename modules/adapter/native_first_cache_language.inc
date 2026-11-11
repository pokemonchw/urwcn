// A1C2014 is the game's single first-background owner. Every original restore
// has completed its SDL copy and caller stack cleanup at the hooks below; its
// original upload, fade and present instructions have not run yet.
namespace native_parent_cache_language {bool restoring_first_hud();}
namespace native_first_cache_language {
enum Hook:u32 {
    cultures=0x53E0,inventory_cancel,inventory_description,inventory_selected,
    inventory_result,npcs,command,normal,fade,world,statistics_row,statistics_message
};
enum class Parent {hud,main,statistics};
bool constructing_statistics{};

void append_hooks(std::vector<HookSpec>& hooks) {
    struct Restore {u32 id,site;};
    for(const auto [id,site]:{
        Restore{cultures,0x3A67Cu},Restore{inventory_cancel,0x56585u},
        Restore{inventory_description,0x56B20u},Restore{inventory_selected,0x57459u},
        Restore{inventory_result,0x574D7u},Restore{npcs,0xB101Bu},
        Restore{command,0x10079Cu},Restore{normal,0x10DA7Au},
        Restore{fade,0x10DAFAu},Restore{world,0x16ECDAu}}) {
        auto restore=inline_hook(id,site,{0x83,0x3D,0,0,0,0,0});
        const auto disabled=address(at<void>(0x61BBA5C));
        std::memcpy(restore.expected+2,&disabled,4);hooks.push_back(restore);
    }
    auto row=inline_hook(statistics_row,0x647D0,{0xF3,0x0F,0x10,0x83,0,0,0,0});
    const auto values=address(at<void>(0x1D30D18));
    std::memcpy(row.expected+4,&values,4);hooks.push_back(row);
    hooks.push_back(call(statistics_message,0x6522E,0xF6510,0));
}

// 6BA00 loads the accepted terminal progress input 100, then calls 64730 at
// 6BA05 before F5A30. Its table/format/controls remain one complete original
// constructor. Only the record-initialization business block is cut out.
Status pause_parent() {
    const auto status=native_parent_cache_language::game_parent();
    if(status!=Status::ok) return status;
    constructing_statistics=true;
    reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0x64730)(100);
    constructing_statistics=false;
    return Status::ok;
}

Parent parent(const NativeEvent& event) {
    if(event.id!=normal && event.id!=fade) return Parent::hud;
    if(native_parent_cache_language::restoring_first_hud()) return Parent::hud;
    // Both original common restorers save exactly one register and have no
    // EBP frame. Their actual direct caller return therefore lives at ESP+4.
    const auto caller=*ptr<const u32>(event.frame->esp+4)-static_cast<u32>(host->image_base);
    struct Caller {u32 return_rva;Parent parent;};
    constexpr Caller callers[]{
        {0x48FFE,Parent::hud},{0xD7C8E,Parent::hud},
        {0xF5AE4,Parent::statistics},{0xFBA4C,Parent::hud},
        {0xFBCBA,Parent::hud},{0x105508,Parent::hud},
        {0x125C3A,Parent::main},{0x125D6F,Parent::main},
        {0x125DD6,Parent::main},{0x125E0E,Parent::main},
        {0x125E43,Parent::main},{0x125E78,Parent::main},
        {0x125EAD,Parent::main},{0x17D869,Parent::hud},
        {0x56850,Parent::hud},{0x5754C,Parent::hud},
        {0x57750,Parent::hud},{0x15923F,Parent::hud},
        {0x159362,Parent::hud},{0x15DF4F,Parent::hud}
    };
    // This is the exhaustive original E8 caller census, plus the explicitly
    // named synchronous HUD construction phase above; it is not a heuristic.
    return std::find_if(std::begin(callers),std::end(callers),
        [caller](const auto& item){return item.return_rva==caller;})->parent;
}

Status restore(const NativeEvent& event) {
    const auto slot=static_cast<u32>(native_ui_cache_owners::Slot::first);
    if(!native_ui_scene::cache_needs_language(slot)) return Status::ok;
    const auto owner=parent(event);
    const auto flip=*at<u32>(0x61BBA5C);
    *at<u32>(0x61BBA5C)=1;
    Status status;
    if(owner==Parent::main) {
        // This native transaction activates the first cache's actual Menu
        // input owner, constructs the complete main page and calls 10DA10.
        status=native_full_language::parent_main();
    } else {
        status=owner==Parent::statistics ? pause_parent() : native_parent_cache_language::game_parent();
        if(status==Status::ok)
            reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0x10DA10)();
    }
    *at<u32>(0x61BBA5C)=flip;
    // The real 10DA10 copy has committed this same first owner's language
    // revision. Its original pending CMP/upload/fade/present now continues.
    return status;
}

Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=false;
    if(event.id<cultures || event.id>statistics_message) return Status::ok;
    handled=true;
    if(event.phase==NativePhase::after) return Status::ok;
    if(event.id==statistics_row) {
        if(constructing_statistics) {
            // EBX is the original 244h record stride. +1D30CFC is the actual
            // already accepted value read at 64AD1, immediately before text.
            event.frame->edx=*ptr<const u32>(event.frame->ebx+address(at<void>(0x1D30CFC)));
            result.resume_rva=0x64AF3;
        }
        return Status::ok;
    }
    if(event.id==statistics_message) {
        // The terminal message is already an accepted canonical F6510 record
        // repainted by HUD::rebuild. Do not append that business message again.
        if(constructing_statistics) result.skip_original=1;
        return Status::ok;
    }
    return restore(event);
}
}
