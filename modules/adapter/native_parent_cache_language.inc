// DF7B0's real parent caches are reconstructed by their complete native
// owners before the original named restore. No drawing contributions or
// translated page fields are retained by this protocol.
namespace native_hud_language { Status rebuild(); Status save_second(); }
namespace native_conversation_language {
Status rebuild();bool owns(native_root_component::RootRevision);
}
namespace native_parent_cache_language {
Status game_parent() {
    return native_conversation_language::owns(native_root_component::current()) ?
        native_conversation_language::rebuild() : native_hud_language::rebuild();
}
enum class Construction { none,culture,command,positioned_command,injuries,armour,inventory,
    item_paragraph,herb_paragraph,course_reward,quantity,quantity_bounded,
    quantity_prompt,quantity_bounded_prompt };
Construction constructing{};
bool restoring_positioned_background{};
bool restoring_first_background{};
u32 preview{},armour_page{},inventory_body{},inventory_preview{},command_menu{};
u32 paragraph_body{};
const native_component_model::ParagraphSource* paragraph_source{};
Status paragraph_status{};
bool restoring_first_hud() {return restoring_first_background;}
void restore_first_hud() {
    restoring_first_background=true;
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x10DA60)();
    restoring_first_background=false;
}
enum Hook:u32 {
    restore_fade=0x5152,restore_normal,culture_input,culture_auto,
    command_entry,command_debug_title,command_paint,command_debug_wait,
    command_input,command_result,positioned_save,positioned_paint,
    positioned_input,positioned_result,
    positioned_counter=0x5180,injuries_entry,injuries_music,
    injuries_seed,injuries_input,injuries_result,
    armour_entry,armour_music,armour_page_input,armour_input,armour_result,
    inventory_entry,inventory_menu,inventory_rows_done,inventory_count,
    inventory_input,inventory_result,command_storage,positioned_storage,course_restore,positioned_upload,
    item_wait,herb_wait,item_paragraph_entry,item_paragraph_finished,item_preview_finished,
    herb_paragraph_body,herb_paragraph_finished,
    reward_entry,reward_input,reward_result,
    quantity_save=0x51C0,quantity_bounded_save,quantity_input,quantity_bounded_input,
    quantity_result,quantity_bounded_result,quantity_restore,quantity_bounded_restore,
    quantity_getst,quantity_bounded_getst,quantity_prompt_end,quantity_bounded_prompt_end,
    stats_restore,stats_abort_restore,spend_restore,spend_abort_restore,emote_restore,chat_restore,
    item_parent_restore,herb_parent_restore,inventory_parent_restore,positioned_parent_restore
};

void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(call(restore_fade,0xDF8ED,0x10C690,0));
    hooks.push_back(call(restore_normal,0xDF935,0x10C690,0));
    hooks.push_back(call(culture_input,0xF8CF,0xD1120,0));
    auto culture=inline_hook(culture_auto,0xF819,{0x83,0x3D,0,0,0,0,1});
    const auto creation_mode=address(at<void>(0x217ABC));
    std::memcpy(culture.expected+2,&creation_mode,4);hooks.push_back(culture);
    auto command=inline_hook(command_entry,0x1002F3,{0x0F,0x28,0x05,0,0,0,0});
    const auto whole_screen=address(at<void>(0x1DDAC0));
    std::memcpy(command.expected+3,&whole_screen,4);hooks.push_back(command);
    hooks.push_back(call(command_debug_title,0x1003FA,0x100E50,0));
    hooks.push_back(call(command_paint,0x100525,0xCFFB0,0));
    hooks.push_back(call(command_debug_wait,0x10063B,0x100E50,0));
    hooks.push_back(call(command_input,0x100640,0xD1120,0));
    hooks.push_back(inline_hook(command_result,0x100645,{0x8B,0xF0,0x8D,0x44,0x24,0x38}));
    hooks.push_back(call(positioned_save,0x1009DE,0x10C540,0));
    hooks.push_back(call(positioned_paint,0x100B16,0xCFFB0,0));
    hooks.push_back(call(positioned_input,0x100C21,0xD1120,0));
    hooks.push_back(inline_hook(positioned_result,0x100C26,{0x83,0xBD,0x68,0xFF,0xFF,0xFF,0}));
    auto counter=inline_hook(positioned_counter,0x10093C,{0x88,0x1D,0,0,0,0});
    const auto message_counter=address(at<void>(0x478E0E9));
    std::memcpy(counter.expected+2,&message_counter,4);hooks.push_back(counter);
    auto injuries=inline_hook(injuries_entry,0xD7A03,{0x33,0xD2,0xB9,0,0,0,0});
    const auto visibility=address(at<void>(0xA38522C));
    std::memcpy(injuries.expected+3,&visibility,4);hooks.push_back(injuries);
    hooks.push_back(call(injuries_music,0xD7AC7,0xC000,0));
    hooks.push_back(inline_hook(injuries_seed,0xD7564,{0x6A,0,0xFF,0x15,0,0,0,0}));
    const auto time=address(at<void>(0x18C50C));
    std::memcpy(hooks.back().expected+4,&time,4);
    hooks.push_back(call(injuries_input,0xD7BD0,0xD1120,0));
    hooks.push_back(inline_hook(injuries_result,0xD7BD5,{0x8B,0xF0,0x83,0xFE,0xFF}));
    auto armour=inline_hook(armour_entry,0xFC8F3,{0xBE,0,0,0,0});
    std::memcpy(armour.expected+1,&visibility,4);hooks.push_back(armour);
    hooks.push_back(call(armour_music,0xFC957,0xC000,0));
    hooks.push_back(inline_hook(armour_page_input,0xFCB30,{0x83,0x7D,0x88,0,0x75,0x15}));
    hooks.push_back(call(armour_input,0xFCE90,0xD1120,0));
    hooks.push_back(inline_hook(armour_result,0xFCE95,{0x83,0xF8,0xFF,0x74,0xF6}));
    hooks.push_back(inline_hook(inventory_entry,0x55084,{0x33,0xDB,0x89,0x44,0x24,0x48}));
    hooks.push_back(call(inventory_menu,0x55794,0xCF790,5));
    hooks.push_back(inline_hook(inventory_rows_done,0x55819,{0x8B,0x4C,0x24,0x44,0x3B,0xC1}));
    auto count=inline_hook(inventory_count,0x54695,{0xFF,0x05,0,0,0,0});
    const auto drawn_items=address(at<void>(0x2F711C));
    std::memcpy(count.expected+2,&drawn_items,4);hooks.push_back(count);
    hooks.push_back(call(inventory_input,0x561E8,0xD1120,0));
    hooks.push_back(inline_hook(inventory_result,0x561ED,{0x8B,0xF8,0x89,0x7C,0x24,0x1C}));
    auto command_saved=inline_hook(command_storage,0x1004DB,{0xA1,0,0,0,0});
    const auto rows=address(at<void>(0x5F54A34));
    std::memcpy(command_saved.expected+1,&rows,4);hooks.push_back(command_saved);
    auto positioned_saved=inline_hook(positioned_storage,0x100ACC,{0xA1,0,0,0,0});
    std::memcpy(positioned_saved.expected+1,&rows,4);hooks.push_back(positioned_saved);
    hooks.push_back(call(course_restore,0x11126,0x10C690,0));
    hooks.push_back(call(positioned_upload,0x10C77A,0x10B770,3));
    hooks.push_back(call(item_wait,0xB06D6,0xD3BF0,0));
    hooks.push_back(call(herb_wait,0x3AB42,0xD3BF0,0));
    hooks.push_back(inline_hook(item_paragraph_entry,0xB04E5,{0x6A,0,0x6A,0,0x6A,0xFF}));
    hooks.push_back(inline_hook(item_paragraph_finished,0xB058B,{0x83,0xC4,0x10,0x8B,0xCE}));
    hooks.push_back(inline_hook(item_preview_finished,0xB06A8,{0x83,0xC4,4,0xBA,0x21,2,0,0}));
    hooks.push_back(inline_hook(herb_paragraph_body,0x3A71B,{0x8D,0x95,0xF8,0xF7,0xFF,0xFF}));
    hooks.push_back(inline_hook(herb_paragraph_finished,0x3AB2B,{0x6A,1,0x56,0x68,0x2C,1,0,0}));
    auto reward=inline_hook(reward_entry,0x15D2D4,{0x68,0,0,0,0});
    const auto directory=address(at<void>(0xA383C90));
    std::memcpy(reward.expected+1,&directory,4);hooks.push_back(reward);
    hooks.push_back(call(reward_input,0x15D4D2,0xD1120,0));
    hooks.push_back(inline_hook(reward_result,0x15D4D7,{0x83,0xF8,0xFF,0x74,0xF6}));
    hooks.push_back(call(quantity_save,0xFBDC8,0x10C540,0));
    hooks.push_back(call(quantity_bounded_save,0xFC20F,0x10C540,0));
    hooks.push_back(call(quantity_input,0xFBF56,0xD1120,0));
    hooks.push_back(call(quantity_bounded_input,0xFC390,0xD1120,0));
    hooks.push_back(inline_hook(quantity_result,0xFBF5B,{0x83,0xF8,0x64,0x7C,4}));
    hooks.push_back(inline_hook(quantity_bounded_result,0xFC395,{0x83,0xF8,0x64,0x7C,4}));
    hooks.push_back(call(quantity_restore,0xFC0C8,0x10C690,0));
    hooks.push_back(call(quantity_bounded_restore,0xFC4EF,0x10C690,0));
    hooks.push_back(call(quantity_getst,0xFC08A,0x10F5B0,0));
    hooks.push_back(call(quantity_bounded_getst,0xFC4B4,0x10F5B0,0));
    hooks.push_back(inline_hook(quantity_prompt_end,0xFC08F,{0x8D,0x54,0x24,0x20,0x2B,0xD0}));
    hooks.push_back(inline_hook(quantity_bounded_prompt_end,0xFC4B9,{0x8D,0x54,0x24,0x18,0x2B,0xD0}));
    hooks.push_back(call(stats_restore,0x6BA17,0x10C690,0));
    hooks.push_back(call(stats_abort_restore,0x6BA52,0x10C690,0));
    hooks.push_back(call(spend_restore,0x8A19A,0x10C690,0));
    hooks.push_back(call(spend_abort_restore,0x8A21C,0x10C690,0));
    hooks.push_back(call(emote_restore,0x134E9B,0x10C690,0));
    hooks.push_back(call(chat_restore,0x14281A,0x10C690,0));
    hooks.push_back(call(item_parent_restore,0xB070D,0x10C690,0));
    hooks.push_back(call(herb_parent_restore,0x3AB5A,0x10C690,0));
    hooks.push_back(call(inventory_parent_restore,0x56A14,0x10C690,0));
    hooks.push_back(call(positioned_parent_restore,0x100D43,0x10C690,0));
}

struct PositionedCall {u32 target,title,x,y;};
struct QuantityCall {u32 target,maximum,format,x,y;};
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_parent_quantity(const QuantityCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tmovl 8(%esp),%ebx\n\t"
        "pushl 16(%ebx)\n\tpushl 12(%ebx)\n\t"
        "movl 4(%ebx),%ecx\n\tmovl 8(%ebx),%edx\n\tcall *(%ebx)\n\t"
        "addl $8,%esp\n\tpopl %ebx\n\tret\n\t");
}
struct QuantityPrompt {u32 target,frame,first,second;};
// The two original More fragments use a native scratch string and balanced
// argument pushes. Only FBF8E's real EBP and its accepted scalar registers
// are borrowed; neither fragment enters getst or copies its editing buffer.
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_parent_quantity_prompt(const QuantityPrompt*) {
    __asm__ __volatile__(
        "pushl %ebp\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edi\n\t"
        "subl $128,%esp\n\tmovl 148(%esp),%eax\n\t"
        "movl 4(%eax),%ebp\n\tmovl 8(%eax),%ebx\n\tmovl 12(%eax),%edi\n\tcall *(%eax)\n\t"
        "addl $128,%esp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tpopl %ebp\n\tret\n\t");
}
// 1008F0 takes ECX, EDX and a caller-cleaned stack argument. Its plain RET
// differs from a compiler fastcall with three arguments.
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_parent_positioned_command(const PositionedCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\t"
        "movl 8(%esp),%ebx\n\t"
        "pushl 12(%ebx)\n\t"
        "movl 4(%ebx),%ecx\n\t"
        "movl 8(%ebx),%edx\n\t"
        "call *(%ebx)\n\t"
        "addl $4,%esp\n\t"
        "popl %ebx\n\tret\n\t");
}
struct InventoryCall {u32 target,parent;};
// The seven original stack arguments remain live in the suspended owner.
// 55084 supplies the accepted drawing inputs after its own original prologue.
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_parent_inventory(const InventoryCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\t"
        "movl 12(%esp),%ebx\n\t"
        "movl 4(%ebx),%esi\n\t"
        "pushl 32(%esi)\n\tpushl 28(%esi)\n\tpushl 24(%esi)\n\t"
        "pushl 20(%esi)\n\tpushl 16(%esi)\n\tpushl 12(%esi)\n\tpushl 8(%esi)\n\t"
        "call *(%ebx)\n\taddl $28,%esp\n\t"
        "popl %esi\n\tpopl %ebx\n\tret\n\t");
}
// B04E5..B058B has no EBP operands. Its own two input coordinates, item
// record offset and measured outputs occupy a small native scratch frame.
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_parent_item_paragraph(const native_component_calls::NoArgumentCall*) {
    __asm__ __volatile__(
        "pushl %ebp\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edi\n\t"
        "subl $128,%esp\n\tmovl 148(%esp),%eax\n\tcall *(%eax)\n\t"
        "addl $128,%esp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tpopl %ebp\n\tret\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_parent_paragraph_return() {
    __asm__ __volatile__("addl $16,%esp\n\tret\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_parent_preview_return() {
    __asm__ __volatile__("addl $4,%esp\n\tret\n\t");
}
u32 continuation(const void* target) {
    return static_cast<u32>(reinterpret_cast<std::uintptr_t>(target)-host->image_base);
}
u32 named_slot(const char* name) {
    u32 index=0;
    while(std::strcmp(name,at<char>(0xA1C1AC0+index*100))!=0) ++index;
    return static_cast<u32>(native_ui_cache_owners::Slot::named0)+index;
}
u32 saved_selection(u32 slot) {
    const auto& menu=native_menu_model::paint_records(native_ui_scene::saved_menu(slot));
    u32 selected{};std::memcpy(&selected,menu.header.data()+0x90,4);return selected;
}
void select(u32 selected) {
    *at<u32>(0x5F54AB0)=selected;
    reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0xD0650)(selected,0);
}
Status culture(u32 accepted_preview) {
    // The native enclosing hut/title is independent of the accepted culture.
    native_full_language::constructing=native_full_language::Construction::profile_frame;
    const native_component_calls::NoArgumentCall frame{address(at<void>(0x12ED1))};
    native_component_calls::uwcn_component_skill_help(&frame);
    native_full_language::constructing=native_full_language::Construction::none;
    preview=accepted_preview;constructing=Construction::culture;
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0xF4F0)();
    constructing=Construction::none;return Status::ok;
}
Status command(u32 title,u32 accepted_preview,u32 source_menu) {
    preview=accepted_preview;command_menu=source_menu;constructing=Construction::command;
    reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0x1002B0)(title);
    constructing=Construction::none;command_menu=0;return Status::ok;
}
Status positioned_command(u32 title,u32 x,u32 y,u32 accepted_preview,u32 source_menu) {
    preview=accepted_preview;command_menu=source_menu;constructing=Construction::positioned_command;
    const PositionedCall input{address(at<void>(0x1008F0)),title,x,y};
    uwcn_parent_positioned_command(&input);
    constructing=Construction::none;command_menu=0;return Status::ok;
}
Status injuries() {
    constructing=Construction::injuries;
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0xD79F0)();
    constructing=Construction::none;return Status::ok;
}
Status armour(u32 mode,u32 filter,u32 page) {
    armour_page=page;constructing=Construction::armour;
    reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0xFC8D0)(mode,filter);
    constructing=Construction::none;return Status::ok;
}
Status inventory(u32 parent,u32 body,u32 accepted_preview) {
    inventory_body=body;inventory_preview=accepted_preview;constructing=Construction::inventory;
    const InventoryCall input{address(at<void>(0x55060)),parent};
    uwcn_parent_inventory(&input);
    constructing=Construction::none;inventory_body=0;return Status::ok;
}
Status family(u32 caller,u32 parent,u32 body,u32 selected,u32 mode,u32 last_preview,u32 source_menu) {
    Status status=Status::ok;
    switch(caller) {
    case 0xF978:
        status=culture(*ptr<const u32>(parent-0x78));break;
    case 0xE0FF8:
        status=native_full_language::construct_skills(mode,last_preview);break;
    case 0xB0798:case 0xFB7FD:case 0x17DECA:
        return game_parent();
    case 0x1006FE:case 0x100645:
        restore_first_hud();
        status=game_parent();
        if(status!=Status::ok) return status;
        reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x10DA10)();
        status=command(*ptr<const u32>(body+0x24),*ptr<const u32>(body+0x14),source_menu);break;
    case 0x100CBA:case 0x100C26:
        restoring_positioned_background=true;
        reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0x10C690)(address(at<void>(0x1AAD40)));
        restoring_positioned_background=false;
        status=game_parent();
        if(status!=Status::ok) return status;
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0x10C540)(
            address(at<void>(0x1AAD40)),parent-0x84);
        status=positioned_command(*ptr<const u32>(parent-0x9C),*ptr<const u32>(parent-0x8C),
            *ptr<const u32>(parent+8),*ptr<const u32>(parent-0xA0),source_menu);break;
    case 0xD7C07:case 0xD7BD5:
        restore_first_hud();
        status=game_parent();
        if(status!=Status::ok) return status;
        reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x10DA10)();
        status=injuries();break;
    case 0xFCF5D:case 0xFCE95:
        status=armour(*ptr<const u32>(parent-0x78),*ptr<const u32>(parent-0x7C),*ptr<const u32>(parent-0x74));break;
    case 0x56A75:case 0x561ED: {
        // 6EA934 is the last real item preview. The Menu selection may be F1.
        const auto accepted_preview=*at<u32>(0x2EA934);
        restore_first_hud();
        status=game_parent();
        if(status!=Status::ok) return status;
        reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x10DA10)();
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0x10C540)(address(at<void>(0x195AFC)),0);
        status=inventory(parent,body,accepted_preview);break;
    }
    }
    if(status==Status::ok) select(selected);
    return status;
}
Status restore_parent(const NativeEvent& event) {
    const auto name=ptr<const char>(event.frame->ecx);
    const auto slot=named_slot(name);
    if(!native_ui_scene::cache_needs_language(slot)) return Status::ok;
    const auto caller=*ptr<const u32>(event.frame->ebp+4)-static_cast<u32>(host->image_base);
    const auto parent=*ptr<const u32>(event.frame->ebp);
    const auto flip=*at<u32>(0x61BBA5C);
    const auto current_root=native_root_component::current();
    native_root_component::activate(native_ui_scene::saved_background(slot));
    *at<u32>(0x61BBA5C)=1;
    const bool has_menu=caller!=0xB0798 && caller!=0xFB7FD && caller!=0x17DECA;
    const auto selected=has_menu ? saved_selection(slot) : 0;
    const auto source_menu=has_menu ? native_ui_scene::saved_menu(slot) : 0;
    if(has_menu) native_menu_component::retain(source_menu);
    // The native cache supplies the unchanged scene pixels before this
    // parent's complete semantic constructors replace their own text/UI.
    // flip=1 selects the original no-presentation restore branch.
    reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0x10C690)(address(name));
    const auto status=family(caller,parent,event.frame->ebp+8,selected,event.frame->ebx,
        *ptr<const u32>(event.frame->ebp-0x490),source_menu);
    if(has_menu) native_menu_component::release(source_menu);
    *at<u32>(0x61BBA5C)=flip;
    if(status==Status::ok)
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0x10C540)(address(name),0);
    native_root_component::activate(current_root);
    return status;
}
Status restore_course_parent(const NativeEvent& event) {
    const auto name=ptr<const char>(event.frame->ecx);
    const auto slot=named_slot(name);
    if(!native_ui_scene::cache_needs_language(slot)) return Status::ok;
    const auto current_root=native_root_component::current();
    const auto flip=*at<u32>(0x61BBA5C);
    *at<u32>(0x61BBA5C)=1;
    native_root_component::activate(native_ui_scene::saved_background(slot));
    reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0x10C690)(address(name));
    const auto caller=*ptr<const u32>(event.frame->ebp+4)-static_cast<u32>(host->image_base);
    // 13052 has only the original bg-worldview image behind this page.
    // 15DCD3 has the playing HUD; its already-hidden world objects remain
    // untouched while their original cached scene pixels supply the base.
    const auto status=caller==0x15DCD3 ? game_parent() : Status::ok;
    if(status==Status::ok)
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0x10C540)(address(name),0);
    native_root_component::activate(current_root);
    *at<u32>(0x61BBA5C)=flip;
    return status;
}
Status paragraph(const NativeEvent& event,bool item) {
    // This is the original parser input resource, including semantic bindings
    // and grammar operations. It contains no lines, geometry or UI snapshots.
    const auto source=native_component_binding::current_paragraph_source();
    const auto name=address(at<void>(0x194370));
    const auto slot=named_slot(ptr<const char>(name));
    const auto current_root=native_root_component::current();
    const auto flip=*at<u32>(0x61BBA5C);
    *at<u32>(0x61BBA5C)=1;
    native_root_component::activate(native_ui_scene::saved_background(slot));
    reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0x10C690)(name);
    auto status=game_parent();
    if(status==Status::ok)
        status=native_component_binding::replace_paragraph_builder(source);
    if(status==Status::ok) {
        paragraph_source=&source;paragraph_body=event.frame->esp;paragraph_status=Status::ok;
        if(item) {
            constructing=Construction::item_paragraph;
            // Its original B0539 save renews infoview before any foreground
            // pixel is drawn. Neither the item producer nor input runs again.
            const native_component_calls::NoArgumentCall body{address(at<void>(0xB04E5))};
            uwcn_parent_item_paragraph(&body);
            if(*at<u32>(0x619F924)==1) {
                const native_component_calls::NoArgumentCall preview_call{address(at<void>(0xB0698))};
                native_component_calls::uwcn_component_skill_help(&preview_call);
            }
        } else {
            reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0x10C540)(name,0);
            constructing=Construction::herb_paragraph;
            // Execute the original MOV EBX input and parser reset, then the
            // confirmed gate consumes the same accepted neutral paragraph.
            const native_component_calls::NoArgumentCall body{address(at<void>(0x3A711))};
            native_component_calls::uwcn_component_skill_help(&body);
        }
        constructing=Construction::none;paragraph_source=nullptr;paragraph_body=0;
        status=paragraph_status;
    }
    native_root_component::activate(current_root);
    *at<u32>(0x61BBA5C)=flip;
    if(status!=Status::ok) return status;
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x10B720)();
    return Status::ok;
}
Status course_reward(u32 selected) {
    auto status=game_parent();
    if(status!=Status::ok) return status;
    constructing=Construction::course_reward;
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x15D2C0)();
    constructing=Construction::none;
    select(selected);
    return Status::ok;
}
Status quantity_parent(u32 owner,bool bounded) {
    const auto name=address(at<void>(0x1AA704));
    const auto slot=named_slot(ptr<const char>(name));
    const auto current_root=native_root_component::current();
    native_root_component::activate(native_ui_scene::saved_background(slot));
    reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0x10C690)(name);
    Status status{};
    if(!bounded && *ptr<const u32>(owner+4)==host->image_base+0x572AC) {
        const auto selected=saved_selection(slot);
        const auto source=native_ui_scene::saved_menu(slot);
        native_menu_component::retain(source);
        status=family(0x561ED,*ptr<const u32>(owner),owner+0x10,selected,0,0,source);
        native_menu_component::release(source);
    } else status=game_parent();
    if(status==Status::ok)
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0x10C540)(name,0);
    native_root_component::activate(current_root);
    return status;
}
Status quantity_page(u32 owner,u32 body,u32 minimum,bool bounded,u32 selected,bool editing) {
    auto status=quantity_parent(owner,bounded);
    if(status!=Status::ok) return status;
    const auto maximum=*ptr<const u32>(body+0x14);
    if(bounded) {
        constructing=Construction::quantity_bounded;
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0xFC1D0)(minimum,maximum);
    } else {
        // FBD80 has only these two callers. FC160's original title remains
        // in that live caller's own -408h input buffer; inventory passes zero.
        const auto format=*ptr<const u32>(owner+4)==host->image_base+0xFC1BE ?
            *ptr<const u32>(owner)-0x408 : 0;
        const QuantityCall input{address(at<void>(0xFBD80)),maximum,format,
            *ptr<const u32>(owner+8),*ptr<const u32>(owner+12)};
        constructing=Construction::quantity;
        uwcn_parent_quantity(&input);
    }
    constructing=Construction::none;
    select(selected);
    if(editing) {
        constructing=bounded ? Construction::quantity_bounded_prompt : Construction::quantity_prompt;
        const QuantityPrompt input{address(at<void>(bounded ? 0xFC3C8 : 0xFBF8E)),owner,
            bounded ? minimum : maximum,bounded ? maximum : *ptr<const u32>(owner+8)};
        uwcn_parent_quantity_prompt(&input);
        constructing=Construction::none;
    }
    return Status::ok;
}
// Each call supplies its statically identified whole parent constructor. The
// native rect pointer remains owned by the suspended enclosing game frame.
Status restore_named_parent(const NativeEvent& event,Status (*construct)()) {
    const auto name=event.frame->ecx;
    const auto slot=named_slot(ptr<const char>(name));
    if(!native_ui_scene::cache_needs_language(slot)) return Status::ok;
    const auto index=slot-static_cast<u32>(native_ui_cache_owners::Slot::named0);
    const auto rect=*at<u32>(0xA1C1CA0+index*sizeof(u32));
    const auto flip=*at<u32>(0x61BBA5C);
    const auto current_root=native_root_component::current();
    *at<u32>(0x61BBA5C)=1;
    native_root_component::activate(native_ui_scene::saved_background(slot));
    restoring_positioned_background=true;
    reinterpret_cast<void (__fastcall *)(u32)>(host->image_base+0x10C690)(name);
    restoring_positioned_background=false;
    const auto status=construct();
    if(status==Status::ok)
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0x10C540)(name,rect);
    native_root_component::activate(current_root);
    *at<u32>(0x61BBA5C)=flip;
    return status;
}
Status restore_hud_named(const NativeEvent& event) {
    return restore_named_parent(event,game_parent);
}
// Both original second restorers have one saved register at ESP. At 10D3BA
// the next word is 15D2C0's real return. The original copy already restored
// its own pixels and Root before this complete parent construction runs.
Status second_parent(const NativeEvent& event,bool& handled) {
    const auto caller=*ptr<const u32>(event.frame->esp+4)-static_cast<u32>(host->image_base);
    handled=caller==0x15D6DA ||
        ((caller==0xE9B75 || caller==0xE9B7C) &&
         *ptr<const u32>(event.frame->ebp+4)==host->image_base+0x15D628);
    if(!handled) return Status::ok;
    const auto slot=static_cast<u32>(native_ui_cache_owners::Slot::second);
    const auto selected=saved_selection(slot);
    const auto flip=*at<u32>(0x61BBA5C);
    *at<u32>(0x61BBA5C)=1;
    auto status=course_reward(selected);
    if(status==Status::ok) status=native_hud_language::save_second();
    *at<u32>(0x61BBA5C)=flip;
    return status;
}
Status menu(const NativeEvent& event,bool& rebuilt,u32& selected) {
    using View=native_language_redraw::View;
    if(!native_language_redraw::pending(View::hud)) return Status::ok;
    const auto caller=*ptr<const u32>(event.frame->ebp+4)-static_cast<u32>(host->image_base);
    if(caller==0xFBF5B || caller==0xFC395) {
        const auto flip=*at<u32>(0x61BBA5C);
        *at<u32>(0x61BBA5C)=1;
        const auto status=quantity_page(*ptr<const u32>(event.frame->ebp),event.frame->ebp+8,
            *ptr<const u32>(event.frame->ebp-0x438),caller==0xFC395,selected,false);
        *at<u32>(0x61BBA5C)=flip;
        if(status!=Status::ok) return status;
        native_language_redraw::completed(View::hud);rebuilt=true;return Status::ok;
    }
    if(caller==0x15D4D7) {
        const auto flip=*at<u32>(0x61BBA5C);
        *at<u32>(0x61BBA5C)=1;
        const auto status=course_reward(selected);
        *at<u32>(0x61BBA5C)=flip;
        if(status!=Status::ok) return status;
        native_language_redraw::completed(View::hud);rebuilt=true;return Status::ok;
    }
    if(caller!=0x100645 && caller!=0x100C26 && caller!=0xD7BD5 && caller!=0xFCE95 && caller!=0x561ED)
        return Status::ok;
    const auto flip=*at<u32>(0x61BBA5C);
    *at<u32>(0x61BBA5C)=1;
    const auto source_menu=native_menu_component::active();
    native_menu_component::retain(source_menu);
    const auto status=family(caller,*ptr<const u32>(event.frame->ebp),event.frame->ebp+8,selected,0,0,source_menu);
    native_menu_component::release(source_menu);
    *at<u32>(0x61BBA5C)=flip;
    if(status!=Status::ok) return status;
    native_language_redraw::completed(View::hud);rebuilt=true;return Status::ok;
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=false;
    if(event.id==item_wait || event.id==herb_wait) {
        handled=true;
        if(event.phase==NativePhase::after && event.frame->eax==static_cast<u32>(-2) &&
           native_language_redraw::pending(native_language_redraw::View::hud))
            return paragraph(event,event.id==item_wait);
        return Status::ok;
    }
    if(event.phase==NativePhase::after) return Status::ok;
    if(event.id==native_full_language::name_input_result &&
       event.frame->eax==static_cast<u32>(-2) &&
       native_language_redraw::pending(native_language_redraw::View::hud)) {
        const auto caller=*ptr<const u32>(event.frame->ebp+4)-static_cast<u32>(host->image_base);
        if(caller==0xFC08F || caller==0xFC4B9) {
            const auto selected=*at<u32>(0x5F54AB0);
            const auto flip=*at<u32>(0x61BBA5C);
            *at<u32>(0x61BBA5C)=1;
            const auto status=quantity_page(*ptr<const u32>(event.frame->ebp),event.frame->ebp+8,
                *ptr<const u32>(event.frame->ebp-0xC0),caller==0xFC4B9,selected,true);
            *at<u32>(0x61BBA5C)=flip;
            if(status!=Status::ok) return status;
            event.frame->esi=*ptr<const u32>(event.frame->ebp-0xA4);
            event.frame->edi=*ptr<const u32>(event.frame->ebp-0xB8);
            event.frame->ebx=*ptr<const u32>(event.frame->ebp-0xAC);
            native_language_redraw::completed(native_language_redraw::View::hud);
            result.resume_rva=0x10F6A0;handled=true;return Status::ok;
        }
    }
    if(event.id==quantity_restore || event.id==quantity_bounded_restore) {
        handled=true;
        const auto slot=named_slot(ptr<const char>(event.frame->ecx));
        if(!native_ui_scene::cache_needs_language(slot)) return Status::ok;
        const auto flip=*at<u32>(0x61BBA5C);
        *at<u32>(0x61BBA5C)=1;
        const auto status=quantity_parent(event.frame->ebp,event.id==quantity_bounded_restore);
        *at<u32>(0x61BBA5C)=flip;
        return status;
    }
    if(event.id>=stats_restore && event.id<=positioned_parent_restore) {
        handled=true;
        if(event.id==emote_restore || event.id==chat_restore)
            return restore_named_parent(event,native_conversation_language::rebuild);
        return restore_hud_named(event);
    }
    if(event.id==restore_fade || event.id==restore_normal) {
        handled=true;return restore_parent(event);
    }
    if(event.id==course_restore) {handled=true;return restore_course_parent(event);}
    if(event.id==positioned_upload && restoring_positioned_background) {
        result.skip_original=1;handled=true;return Status::ok;
    }
    if(event.id==item_paragraph_entry && constructing==Construction::item_paragraph) {
        event.frame->ebx=*ptr<const u32>(paragraph_body+0x44);
        event.frame->esi=*ptr<const u32>(paragraph_body+0x40);
        *ptr<u32>(event.frame->esp+0x20)=*ptr<const u32>(paragraph_body+0x20);
        *ptr<u32>(event.frame->esp+0x40)=event.frame->esi;
        *ptr<u32>(event.frame->esp+0x44)=event.frame->ebx;
    }
    if(event.id==item_paragraph_finished && constructing==Construction::item_paragraph) {
        // Native measurement and clamping produced these live owner outputs.
        *ptr<u32>(paragraph_body+0x18)=*ptr<const u32>(event.frame->esp+0x28);
        *ptr<u32>(paragraph_body+0x40)=*ptr<const u32>(event.frame->esp+0x50);
        *ptr<u32>(paragraph_body+0x44)=*ptr<const u32>(event.frame->esp+0x54);
        result.resume_rva=continuation(reinterpret_cast<const void*>(uwcn_parent_paragraph_return));
    }
    if(event.id==item_preview_finished && constructing==Construction::item_paragraph)
        result.resume_rva=continuation(reinterpret_cast<const void*>(uwcn_parent_preview_return));
    if(event.id==herb_paragraph_body && constructing==Construction::herb_paragraph) {
        paragraph_status=native_component_binding::replace_paragraph_builder(*paragraph_source);
        result.resume_rva=0x3AAB7;
    }
    if(event.id==herb_paragraph_finished && constructing==Construction::herb_paragraph)
        result.resume_rva=continuation(reinterpret_cast<const void*>(uwcn_parent_paragraph_return));
    if(event.id==reward_entry && constructing==Construction::course_reward) result.resume_rva=0x15D390;
    if(event.id==reward_input && constructing==Construction::course_reward) {
        reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0xCFFB0)();
        result.skip_original=1;
    }
    if(event.id==reward_result) {
        if(constructing==Construction::course_reward) {
            event.frame->ecx=*ptr<const u32>(event.frame->ebp-4)^event.frame->ebp;
            result.resume_rva=0x15D762;
        } else result.resume_rva=event.frame->eax==static_cast<u32>(-1) ? 0x15D4D2 : 0x15D4DC;
    }
    if((event.id==quantity_save && constructing==Construction::quantity) ||
       (event.id==quantity_bounded_save && constructing==Construction::quantity_bounded)) result.skip_original=1;
    if((event.id==quantity_input && constructing==Construction::quantity) ||
       (event.id==quantity_bounded_input && constructing==Construction::quantity_bounded)) {
        reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0xCFFB0)();
        result.skip_original=1;
    }
    if(event.id==quantity_result) result.resume_rva=constructing==Construction::quantity ? 0xFC0E7 :
        static_cast<std::int32_t>(event.frame->eax)<100 ? 0xFBF64 : 0xFBF60;
    if(event.id==quantity_bounded_result) result.resume_rva=constructing==Construction::quantity_bounded ? 0xFC1F4 :
        static_cast<std::int32_t>(event.frame->eax)<100 ? 0xFC39E : 0xFC39A;
    if((event.id==quantity_getst && constructing==Construction::quantity_prompt) ||
       (event.id==quantity_bounded_getst && constructing==Construction::quantity_bounded_prompt)) result.skip_original=1;
    if((event.id==quantity_prompt_end && constructing==Construction::quantity_prompt) ||
       (event.id==quantity_bounded_prompt_end && constructing==Construction::quantity_bounded_prompt))
        result.resume_rva=continuation(reinterpret_cast<const void*>(native_component_calls::uwcn_component_fragment_return));
    if(event.id==native_full_language::culture_save && constructing==Construction::culture) {
        *at<u32>(0x5F54ABC)=*at<u32>(0x5F54A34);
        *at<u32>(0x5F54AB0)=preview;
        *ptr<u32>(event.frame->ebp-0x78)=preview;
        event.frame->ebx=preview;result.resume_rva=0xF628;
    }
    if(event.id==culture_auto && constructing==Construction::culture) result.resume_rva=0xF8CF;
    if(event.id==culture_input && constructing==Construction::culture) result.skip_original=1;
    if(event.id==0x510B && constructing==Construction::culture) result.resume_rva=0xF9FD;
    if(event.id==command_entry && constructing==Construction::command) {
        event.frame->eax=*at<u32>(0x61A9698);event.frame->ecx=25;result.resume_rva=0x10032A;
    }
    if((event.id==command_debug_title || event.id==command_debug_wait || event.id==command_input) &&
       constructing==Construction::command) result.skip_original=1;
    if(event.id==command_paint && constructing==Construction::command) *at<u32>(0x5F54AB0)=preview;
    if((event.id==command_storage && constructing==Construction::command) ||
       (event.id==positioned_storage && constructing==Construction::positioned_command))
        native_menu_component::activate(command_menu);
    if(event.id==command_result && constructing==Construction::command) result.resume_rva=0x1007EC;
    if(event.id==positioned_save && constructing==Construction::positioned_command) result.skip_original=1;
    if(event.id==positioned_counter && constructing==Construction::positioned_command) result.skip_original=1;
    if(event.id==positioned_paint && constructing==Construction::positioned_command) *at<u32>(0x5F54AB0)=preview;
    if(event.id==positioned_input && constructing==Construction::positioned_command) result.skip_original=1;
    if(event.id==positioned_result && constructing==Construction::positioned_command) result.resume_rva=0x100D57;
    if(event.id==injuries_entry && constructing==Construction::injuries) result.resume_rva=0xD7A71;
    if(event.id==injuries_music && constructing==Construction::injuries) result.skip_original=1;
    if(event.id==injuries_seed && constructing==Construction::injuries) result.resume_rva=0xD759E;
    if(event.id==injuries_input && constructing==Construction::injuries) {
        reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0xCFFB0)();
        result.skip_original=1;
    }
    if(event.id==injuries_result && constructing==Construction::injuries) result.resume_rva=0xD7C93;
    if(event.id==armour_entry && constructing==Construction::armour) result.resume_rva=0xFC925;
    if(event.id==armour_music && constructing==Construction::armour) result.skip_original=1;
    if(event.id==armour_page_input) {
        if(constructing==Construction::armour) {
            event.frame->ebx=armour_page;*ptr<u32>(event.frame->ebp-0x74)=armour_page;
        }
        result.resume_rva=*ptr<const u32>(event.frame->ebp-0x78) ? 0xFCB4B : 0xFCB36;
    }
    if(event.id==armour_input && constructing==Construction::armour) result.skip_original=1;
    if(event.id==armour_result) result.resume_rva=constructing==Construction::armour ? 0xFCF0E :
        event.frame->eax==static_cast<u32>(-1) ? 0xFCE90 : 0xFCE9A;
    if(event.id==inventory_entry && constructing==Construction::inventory) {
        // Only the original constructor's accepted scalar inputs are lent to
        // its fresh native frame. Scratch strings/records remain its own.
        *ptr<u32>(event.frame->esp+0x10)=1;
        *ptr<u32>(event.frame->esp+0x14)=*ptr<const u32>(inventory_body+0x14);
        *ptr<u32>(event.frame->esp+0x34)=*ptr<const u32>(inventory_body+0x34);
        *ptr<u32>(event.frame->esp+0x3C)=*ptr<const u32>(inventory_body+0x3C);
        *ptr<u32>(event.frame->esp+0x40)=*ptr<const u32>(inventory_body+0x40);
        *ptr<u32>(event.frame->esp+0x4C)=*ptr<const u32>(inventory_body+0x4C);
        *ptr<unsigned char>(event.frame->esp+0xF)=*ptr<const unsigned char>(inventory_body+0xF);
        event.frame->esi=1;event.frame->edi=*ptr<const u32>(inventory_body+0x14);
        result.resume_rva=0x555E8;
    }
    if(event.id==inventory_menu && constructing==Construction::inventory) *at<u32>(0x5F54BB4)=inventory_preview;
    if(event.id==inventory_rows_done && constructing==Construction::inventory) {
        event.frame->ebx=*ptr<const u32>(inventory_body+0x38);
        result.resume_rva=0x55971;
    }
    if(event.id==inventory_count && constructing==Construction::inventory) result.skip_original=1;
    if(event.id==inventory_input && constructing==Construction::inventory) {
        reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0xCFFB0)();
        result.skip_original=1;
    }
    if(event.id==inventory_result && constructing==Construction::inventory) result.resume_rva=0x554F9;
    handled=result.skip_original || result.resume_rva;
    return Status::ok;
}
}
