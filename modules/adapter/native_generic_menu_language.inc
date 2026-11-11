// Remaining current D1120 owners from the complete 36-call census. Each
// branch names an actual original owner; there is no default HUD parent.
namespace native_conversation_language {Status rebuild();}
namespace windows_inventory {
native_text_resource::TextSource expression(const char*,const MessageText&,TextComponent);
Status consume_source(const NativeEvent&,const native_text_resource::TextSource&,u32,Scope);
}
namespace native_generic_menu_language {
using View=native_language_redraw::View;
enum class Construction {none,query,history,known_detail,known_list,known_field};
Construction constructing{};
u32 history_body{};
enum Hook:u32 {query_finished=0x51E0,query_second_finished,history_entry,
    history_cache,history_body_entry,history_finished,known_detail_finished,known_list_finished,
    known_list_cleanup,history_line_width,history_append,history_paragraph,history_footer,
    query_panel,query_second_panel,field_input,
    field_text=0x5265,field_cursor_width,field_detail_finished,
    query_input,query_second_input,history_input};
extern "C" std::uintptr_t urwcn_generic_history_capacity_target{};
extern "C" std::uintptr_t urwcn_generic_history_body_target{};
extern "C" std::uintptr_t urwcn_generic_history_eof{};
extern "C" std::uintptr_t urwcn_generic_history_eof_return{};
extern "C" {
std::uintptr_t urwcn_generic_query_input_target{},urwcn_generic_query_input_return{},
    urwcn_generic_query_second_input_return{},urwcn_generic_history_input_return{};
}

struct Query {u32 target,frame,text;};
struct KnownDetail {u32 target,frame,self;};
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_generic_known_detail(const KnownDetail*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%eax\n\tmovl 4(%eax),%ebp\n\t"
        "movl 8(%eax),%ebx\n\tcall *(%eax)\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t");
}
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_generic_query(const Query*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%eax\n\tmovl 4(%eax),%ebp\n\t"
        "movl 8(%eax),%esi\n\tcall *(%eax)\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t");
}
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_generic_query_input() {
    // Preserve D1120's actual native caller at EBP+4. A phased CALL hook
    // would replace it with the resident After bridge and hide its owner.
    __asm__ __volatile__("pushl _urwcn_generic_query_input_return\n\tjmp *_urwcn_generic_query_input_target\n\t");
}
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_generic_query_second_input() {
    __asm__ __volatile__("pushl _urwcn_generic_query_second_input_return\n\tjmp *_urwcn_generic_query_input_target\n\t");
}
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_generic_history_input() {
    __asm__ __volatile__("pushl _urwcn_generic_history_input_return\n\tjmp *_urwcn_generic_query_input_target\n\t");
}
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_generic_history_capacity() {
    // FE3C7's original capacity calculation begins with the three pending
    // memset arguments; FE3DF owns their ADD ESP,0Ch cleanup.
    __asm__ __volatile__("subl $12,%esp\n\tjmp *_urwcn_generic_history_capacity_target\n\t");
}
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_generic_history_body() {
    __asm__ __volatile__("addl $36,%esp\n\tjmp *_urwcn_generic_history_body_target\n\t");
}
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_generic_history_file() {
    // The ordinary native path still runs its exact pending argument cleanup
    // and feof(FILE*) call. No relative CALL or ESP operation is replayed.
    __asm__ __volatile__(
        "addl $36,%esp\n\tpushl %ebx\n\t"
        "call *_urwcn_generic_history_eof\n\tjmp *_urwcn_generic_history_eof_return\n\t");
}
u32 continuation(const void* target) {
    return static_cast<u32>(reinterpret_cast<std::uintptr_t>(target)-host->image_base);
}
void append_hooks(std::vector<HookSpec>& hooks) {
    const auto main=address(at<void>(0x61BBB10));
    for(const auto [id,site]:{std::pair{query_finished,0xFB988u},
            std::pair{query_second_finished,0xFBBE7u}}) {
        auto finished=inline_hook(id,site,{0xA1,0,0,0,0});
        std::memcpy(finished.expected+1,&main,4);hooks.push_back(finished);
    }
    hooks.push_back(inline_hook(history_entry,0xFE2D7,{0xC7,0x44,0x24,0x1C,0,0,0,0}));
    auto cache=inline_hook(history_cache,0xFE409,{0x39,0x35,0,0,0,0});
    const auto saved=address(at<void>(0x61BBAFC));
    std::memcpy(cache.expected+2,&saved,4);hooks.push_back(cache);
    auto body=inline_hook(history_body_entry,0xFE47D,{0x83,0xC4,0x24,0x53,0xFF,0x15,0,0,0,0});
    const auto eof=address(at<void>(0x18C4E0));
    std::memcpy(body.expected+6,&eof,4);hooks.push_back(body);
    auto finished=inline_hook(history_finished,0xFEA44,{0xBA,0,0,0,0});
    const auto empty=address(at<void>(0x18C616));
    std::memcpy(finished.expected+1,&empty,4);hooks.push_back(finished);
    // Both original branches are continued explicitly, never replayed.
    hooks.push_back(inline_hook(known_detail_finished,0xE46AC,{0x83,0xF8,0xD6,0x74,0x5B}));
    hooks.push_back(inline_hook(known_list_finished,0xE4BD6,{0x8B,0xF0,0x85,0xF6,0x79,0x19}));
    auto cleanup=inline_hook(known_list_cleanup,0xE4C24,{0xC7,0x05,0,0,0,0,0,0,0,0});
    const auto detail_texture=address(at<void>(0x61BB644));
    std::memcpy(cleanup.expected+2,&detail_texture,4);hooks.push_back(cleanup);
    hooks.push_back(inline_hook(history_line_width,0xFE5F8,{0x2B,0xCA,0x8D,4,0xCD,0,0,0,0}));
    hooks.push_back(call(history_append,0xFE86E,0x162300,0));
    hooks.push_back(call(history_paragraph,0xFE9BB,0x10EB40,4));
    hooks.push_back(call(history_footer,0xFEA3C,0x10E5A0,3));
    hooks.push_back(call(query_panel,0xFB983,0x116270,5));
    hooks.push_back(call(query_second_panel,0xFBBE2,0x116270,5));
    // The original relative CALL is always continued explicitly, never
    // replayed from an inline trampoline at a different instruction address.
    hooks.push_back(inline_hook(query_input,0xFBA25,{0xE8,0xF6,0x56,0xFD,0xFF}));
    hooks.push_back(inline_hook(query_second_input,0xFBC93,{0xE8,0x88,0x54,0xFD,0xFF}));
    hooks.push_back(inline_hook(history_input,0xFEB77,{0xE8,0xA4,0x25,0xFD,0xFF}));
    hooks.push_back(call(field_input,0x10FB17,0xD3BF0,0));
    hooks.push_back(call(field_text,0x10FA4D,0x10E260,4));
    hooks.push_back(inline_hook(field_cursor_width,0x10FA77,{0x8D,0x14,0xD5,2,0,0,0}));
    hooks.push_back(inline_hook(field_detail_finished,0xE4673,{0x80,0xFB,2,0x75,0x2F}));
    urwcn_generic_history_capacity_target=host->image_base+0xFE3C7;
    urwcn_generic_history_body_target=host->image_base+0xFE673;
    urwcn_generic_history_eof=*at<u32>(0x18C4E0);
    urwcn_generic_history_eof_return=host->image_base+0xFE487;
    urwcn_generic_query_input_target=host->image_base+0xD1120;
    urwcn_generic_query_input_return=host->image_base+0xFBA2A;
    urwcn_generic_query_second_input_return=host->image_base+0xFBC98;
    urwcn_generic_history_input_return=host->image_base+0xFEB7C;
}

Status query(const NativeEvent& event,bool second) {
    // D1120 saved its original caller ESI at -43Ch. This is the accepted
    // complete query, before the native sprintf's shared scratch is reused.
    const std::string text=ptr<const char>(*ptr<const u32>(event.frame->ebp-0x43C));
    const auto owner=*ptr<const u32>(event.frame->ebp);
    Status status;
    if(second && text=="Are you sure to cancel?")
        status=native_parent_cache_language::inventory_query_parent(owner);
    else {
        native_parent_cache_language::restore_first_hud();
        status=native_parent_cache_language::game_parent();
    }
    if(status!=Status::ok) return status;
    constructing=Construction::query;
    const Query input{address(at<void>(second ? 0xFBB97 : 0xFB938)),owner,address(text.c_str())};
    // Begin after the original F6510 echo. Continue through the original
    // Panel, CF790, both CFAF0 buttons and the empty native input actions.
    // CFAF0 paints these kind-100 buttons immediately; CFFB0 returns on
    // their empty title and cannot reconstruct the buttons from NOTEXTSPOT.
    // Skip only this synchronous copy's D1120; the real wait stays suspended.
    urwcn_generic_query(&input);
    constructing=Construction::none;
    return Status::ok;
}
Status history(const NativeEvent& event) {
    const auto owner=*ptr<const u32>(event.frame->ebp);
    // FE2B0 is the original AND ESP,-8 / SUB D4Ch / three-saved-register frame.
    // Borrow only the existing logical file window; original tables remain
    // the game's seventy accepted English message records.
    history_body=(owner&~u32{7})-0xD58;
    const auto fade=*at<u32>(0x61BBCD8);
    constructing=Construction::history;
    reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0xFE2B0)();
    constructing=Construction::none;
    *at<u32>(0x61BBCD8)=fade;
    history_body=0;
    return Status::ok;
}
Status known_map(const NativeEvent& event,bool detail,bool field=false) {
    auto status=native_renderer_component_binding::construct_known_map();
    if(status!=Status::ok) return status;
    constructing=field ? Construction::known_field :
        (detail ? Construction::known_detail : Construction::known_list);
    if(detail) {
        const auto owner=*ptr<const u32>(event.frame->ebp);
        const KnownDetail input{address(at<void>(0xE413B)),owner,
            *ptr<const std::uint8_t>(owner-0xA31)};
        urwcn_generic_known_detail(&input);
    } else reinterpret_cast<void (URWCN_CALL *)()>(host->image_base+0xE4960)();
    constructing=Construction::none;
    return Status::ok;
}
Status menu(const NativeEvent& event,bool& rebuilt,u32& selected) {
    const auto caller=*ptr<const u32>(event.frame->ebp+4)-static_cast<u32>(host->image_base);
    if(caller==0xE46AC || caller==0xE4BD6) {
        if(!native_language_redraw::pending(View::map)) return Status::ok;
        const auto flip=*at<u32>(0x61BBA5C);
        *at<u32>(0x61BBA5C)=1;
        const auto status=known_map(event,caller==0xE46AC);
        *at<u32>(0x61BBA5C)=flip;
        if(status==Status::ok) {native_language_redraw::completed(View::map);rebuilt=true;}
        return status;
    }
    if(!native_language_redraw::pending(View::hud)) return Status::ok;
    if(caller!=0xFBA2A && caller!=0xFBC98 && caller!=0xFEB7C &&
       caller!=0x1427FA && caller!=0x14705A) return Status::ok;
    const auto current=native_menu_component::active();
    native_menu_component::retain(current);
    const bool query_owner=caller==0xFBA2A || caller==0xFBC98;
    const bool complete_constructor=query_owner || caller==0xFEB7C;
    if(caller==0x14705A && windows_build::is_3891()) bind_chat_mode_menu(current);
    if(caller==0x1427FA && windows_build::is_3891()) {
        const auto status=bind_chat_lines_menu(current);
        if(status!=Status::ok) {native_menu_component::release(current);return status;}
    }
    const auto flip=*at<u32>(0x61BBA5C);
    *at<u32>(0x61BBA5C)=1;
    Status status;
    if(query_owner) status=query(event,caller==0xFBC98);
    else if(caller==0xFEB7C) status=history(event);
    else {
        status=native_conversation_language::rebuild();
        if(status==Status::ok && caller==0x1427FA) {
            // Renew the actual chat-options parent's same native rectangle,
            // after full NPC/speaker construction and before its current Menu.
            const auto owner=*ptr<const u32>(event.frame->ebp);
            reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0x10C540)(
                address(at<void>(0x1B61FC)),owner-0x880);
        }
    }
    if(!complete_constructor) {
        native_menu_component::activate(current);
        if(status==Status::ok) status=native_menu_component::paint(current);
    }
    if(status==Status::ok) {
        *at<u32>(0x5F54AB0)=selected;
        // D1167 saves the complete new query pixels, then D1217 selects from
        // that cache. Leave that ordering with its original suspended D1120.
        if(!complete_constructor)
            reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0xD0650)(selected,0);
    }
    *at<u32>(0x61BBA5C)=flip;
    native_menu_component::release(current);
    if(status==Status::ok) {native_language_redraw::completed(View::hud);rebuilt=true;}
    return status;
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=false;
    // Keep the existing history Hook identities while the 3.89.1 complete
    // consumer handles both phases, its semantic source and actual widths.
    if(windows_build::is_3891() && (event.id==history_line_width || event.id==history_append ||
       event.id==history_paragraph || event.id==history_footer)) return Status::ok;
    if(event.id==history_input) {
        handled=true;
        // FE2B0 has now constructed its complete native kind-100 footer.
        // Stop only this borrowed construction before it reads a new action.
        result.resume_rva=continuation(constructing==Construction::history ?
            reinterpret_cast<const void*>(native_component_calls::urwcn_component_fragment_return) :
            reinterpret_cast<const void*>(urwcn_generic_history_input));
        return Status::ok;
    }
    if(event.id==query_input || event.id==query_second_input) {
        handled=true;
        if(constructing==Construction::query) {
            // All native arguments are balanced here. Return only from the
            // borrowed construction, before interpreting an input result.
            result.resume_rva=continuation(reinterpret_cast<const void*>(
                native_component_calls::urwcn_component_fragment_return));
        } else {
            result.resume_rva=continuation(event.id==query_input ?
                reinterpret_cast<const void*>(urwcn_generic_query_input) :
                reinterpret_cast<const void*>(urwcn_generic_query_second_input));
        }
        return Status::ok;
    }
    if(event.id==field_input) {
        handled=true;
        if(windows_build::is_3891()) {
            if(event.phase==NativePhase::before) native_name_input::activate_marker();
            else {
                const auto status=native_targets::promote_text_field(
                    *ptr<u32>(event.frame->ebp-0x2c),*ptr<u32>(event.frame->ebp-0x28));
                if(status!=Status::ok) return status;
            }
        }
        if(event.phase!=NativePhase::after || event.frame->eax!=static_cast<u32>(-2) ||
           native_name_input::state.committed || !native_language_redraw::pending(View::map)) return Status::ok;
        // The real 10F950 frame still owns its accepted ring buffer, native
        // surface/renderer, coordinates and native colour arguments. Its -2
        // branch will redraw that exact prompt and present from 10FA10.
        const auto flip=*at<u32>(0x61BBA5C);
        *at<u32>(0x61BBA5C)=1;
        const auto status=known_map(event,true,true);
        *at<u32>(0x61BBA5C)=flip;
        if(status==Status::ok) native_language_redraw::completed(View::map);
        return status;
    }
    if(event.id==field_text) {
        handled=true;
        if(event.phase==NativePhase::after) {end(event.token);return Status::ok;}
        if(!windows_build::is_3891()) return Status::ok;
        native_name_input::activate_marker();
        if(!translation_available) return Status::ok;
        std::vector<char> encoded;
        const auto status=native_name_input::display(ptr<const char>(event.arguments[1]),encoded);
        if(status!=Status::ok) return status;
        return lend_text(event,encoded,event.arguments[1],Scope::hud_renderer_text,0);
    }
    if(event.id==field_cursor_width && event.phase!=NativePhase::after) {
        handled=true;
        const auto* input=ptr<const char>(*ptr<const u32>(event.frame->ebp-0x40));
        const native_name_input::UnicodeMeasure unicode(input);
        std::vector<char> encoded;
        auto status=native_name_input::display(input,encoded);
        if(status!=Status::ok) return status;
        render::Metrics measured{};
        status=windows_renderer_text::measure(encoded.data(),
            ptr<void>(*ptr<const u32>(event.frame->ebp-0x28)),0,measured);
        if(status!=Status::ok) return status;
        event.frame->edx=static_cast<u32>(measured.logical_width)+2;
        result.resume_rva=0x10FA7E;
        return Status::ok;
    }
    if(event.id==field_detail_finished && event.phase!=NativePhase::after) {
        handled=true;
        // All native texture, labels, Menu and renderer-owner writes are
        // complete. Stop before the accepted mode=2 automatically starts its
        // second field; the actual 10F950 input remains the sole live editor.
        result.resume_rva=constructing==Construction::known_field ?
            continuation(reinterpret_cast<const void*>(native_component_calls::urwcn_component_fragment_return)) :
            ((event.frame->ebx&0xFF)==2 ? 0xE4678 : 0xE46A7);
        return Status::ok;
    }
    if(event.id==native_full_language::input_entry && event.phase!=NativePhase::after &&
       (constructing==Construction::known_detail || constructing==Construction::known_list)) {
        handled=true;result.resume_rva=0xD19B3;return Status::ok;
    }
    if(event.id<query_finished || event.id>query_second_panel || event.phase==NativePhase::after)
        return Status::ok;
    handled=true;
    if(event.id==known_detail_finished) {
        result.resume_rva=constructing==Construction::known_detail ?
            continuation(reinterpret_cast<const void*>(native_component_calls::urwcn_component_fragment_return)) :
            (event.frame->eax==static_cast<u32>(-42) ? 0xE470C : 0xE46B1);
        return Status::ok;
    }
    if(event.id==known_list_finished) {
        if(constructing==Construction::known_list) result.resume_rva=0xE4C1A;
        else {
            event.frame->esi=event.frame->eax;
            result.resume_rva=static_cast<std::int32_t>(event.frame->eax)>=0 ? 0xE4BF5 : 0xE4BDC;
        }
        return Status::ok;
    }
    if(event.id==known_list_cleanup) {
        // The complete factory's new texture and native rectangle remain the
        // current input owner. Skip only the original final retirement writes.
        if(constructing==Construction::known_list) result.resume_rva=0xE4C35;
        return Status::ok;
    }
    if(event.id==history_line_width) {
        render::Metrics measured{};
        const auto status=native_name_input::measure(ptr<const char>(event.frame->esp+0x950),measured);
        if(status!=Status::ok) return status;
        event.frame->eax=static_cast<u32>(measured.logical_width);result.resume_rva=0xFE601;
        return Status::ok;
    }
    if(event.id==query_panel || event.id==query_second_panel) {
        const auto* original=ptr<char>(event.arguments[2]);
        // FB942/FBBA1 only copy ESI through sprintf("%s"). Resolve the
        // accepted prompt's complete producer expression, including dynamic
        // NPC/resource operands, before borrowing this native Panel title.
        return windows_inventory::consume_source(event,windows_inventory::expression(
            original,message_source_bound(ptr<char>(event.frame->esi)),
            TextComponent::native_message_expression),2,Scope::titled_panel);
    }
    if(event.id==history_append || event.id==history_paragraph || event.id==history_footer)
        return Status::ok;
    if(event.id==query_finished || event.id==query_second_finished) {
        return Status::ok;
    }
    if(event.id==history_body_entry) {
        if(constructing==Construction::history) {
            event.frame->eax=*ptr<const u32>(history_body+0x20);
            event.frame->ebx=*ptr<const u32>(history_body+0x18);
            event.frame->ecx=event.frame->ebx;
            // Panel arguments are still pending at this original boundary.
            event.frame->edi=*ptr<const u32>(event.frame->esp+36+0x28);
            result.resume_rva=continuation(reinterpret_cast<const void*>(urwcn_generic_history_body));
        } else result.resume_rva=continuation(reinterpret_cast<const void*>(urwcn_generic_history_file));
        return Status::ok;
    }
    if(constructing!=Construction::history) return Status::ok;
    if(event.id==history_entry) {
        for(const auto field:{0x14u,0x18u,0x20u})
            *ptr<u32>(event.frame->esp+field)=*ptr<const u32>(history_body+field);
        event.frame->esi=0;
        result.resume_rva=continuation(reinterpret_cast<const void*>(urwcn_generic_history_capacity));
    } else if(event.id==history_cache) result.resume_rva=0xFE442;
    else if(event.id==history_finished) {
        // The original constructor supplies the line capacity used by its
        // ordinary next/previous-page business after the current real wait.
        *ptr<u32>(history_body+0x28)=*ptr<const u32>(event.frame->esp+0x28);
        // Continue through CF790 and all six native CFAF0 buttons. The empty
        // kind-100 Menu cannot redraw these buttons through CFFB0 alone.
    }
    return Status::ok;
}
}
