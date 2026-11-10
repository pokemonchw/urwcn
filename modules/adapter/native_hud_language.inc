// Full native HUD and live map reconstruction. Retained values are actual
// component English inputs and logical native selections. Native frames own
// all layout, controls, surface/texture construction and cache replacement.
namespace native_hud_command_migration {const char* target_title(const NativeEvent&);}
namespace native_parent_cache_language {
Status second_parent(const NativeEvent&,bool&);
Status restore_hud_named(const NativeEvent&);
Status game_parent();
}
namespace native_first_cache_language {Status pause_parent();}
namespace native_hud_language {
using View=native_language_redraw::View;
constexpr auto hud_view=static_cast<View>(25),map_view=static_cast<View>(26),messages_view=static_cast<View>(27);
enum Hook:u32 {
    command_input=0x53A0,completed_x,completed_y,message_panel,hud_finished,
    hide_write,speed_query,speed_stack,speed_value,speed_color,activity_expired,
    shield_reset,shield_first,shield_second,shield_both,item_debug,
    message_input,message_prompt_end,map_result,map_input,second_save,map_parent_restore,
    main_input,modal_input,modal_finished,target_result,target_help_branch,target_help_end,location_cache,
    second_parent_restore,target_parent_restore
};
bool constructing{},prompt_constructing{},second_constructing{},command_constructed{},modal_constructing{};
bool map_constructing{};
u32 map_selection{};
bool target_constructing{};
u32 target_x{},target_y{},target_item{};
std::string target_heading;
std::string command;
// One original FAA30 widget, accepted at its real operand reads and committed
// only after the native software and headingicons publications. No layout,
// palette, rendered strings, glyphs or frame addresses belong to this source.
struct WidgetInput {
    u32 mode{},hide{},fallen{},action{},hiding{},direction_label{},units{},ratio{},
        direction_icon{},clock{},query_first{},query_second{};
    std::array<u32,8> activity{};
};
WidgetInput working_widget,published_widget;
bool widget_published{};
bool accepting_widget{};
u32 working_widget_phase{};
const WidgetInput* widget_input{};
u32 widget_phase{};
u32 display_units() {return widget_input ? widget_input->units : *at<u32>(0xA2D0AF4);}
enum WidgetHook:u32 {
    widget_mode=0x5291,widget_hide,widget_fallen,widget_action,widget_hiding,
    widget_direction_label,widget_units,widget_ratio,widget_query_second,
    widget_direction_icon,widget_activity,widget_publication=0x529D,widget_rect,
    widget_target
};
extern "C" std::uintptr_t uwcn_hud_widget_prefix_end{};
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_hud_widget_prefix_return() {
    // Both confirmed prefix cuts have eight original native arguments pending.
    __asm__ __volatile__("addl $8,%esp\n\tjmp *_uwcn_hud_widget_prefix_end\n\t");
}

void adopt_command(const char* original) {command=original;command_constructed=true;}
void adopt_main_wait() {adopt_command(at<char>(0x18C616));}
u32 fragment_return() {
    return static_cast<u32>(reinterpret_cast<std::uintptr_t>(native_component_calls::uwcn_component_fragment_return)-host->image_base);
}
struct BorrowedFrame {u32 target,frame;};
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_hud_borrow_frame(const BorrowedFrame*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%ebx\n\tmovl 4(%ebx),%ebp\n\tcall *(%ebx)\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t");
}
void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(inline_hook(command_input,0xF90E4,{0x8B,0xF1,0x8D,0x45,0x90}));
    struct CompletionWrite {u32 id,site,field;};
    for(const auto [id,site,field]:{CompletionWrite{completed_x,0xFA2E7u,0xA3840E8u},
            CompletionWrite{completed_y,0xFA2F1u,0xA3840C4u}}) {
        auto write=inline_hook(id,site,{0xC7,0x05,0,0,0,0,0,0,0,0});
        const auto target=address(at<void>(field));std::memcpy(write.expected+2,&target,4);hooks.push_back(write);
    }
    hooks.push_back(inline_hook(message_panel,0xFA308,{0x68,0x99,0,0,0}));
    auto tail=inline_hook(hud_finished,0xFA749,{0x83,0x3D,0,0,0,0,0});
    auto field=address(at<void>(0x61BBA5C));std::memcpy(tail.expected+2,&field,4);hooks.push_back(tail);
    auto hide=inline_hook(hide_write,0xFAC79,{0xC6,0x05,0,0,0,0,0});
    field=address(at<void>(0x61A9DAF));std::memcpy(hide.expected+2,&field,4);hooks.push_back(hide);
    hooks.push_back(call(speed_query,0xFACFD,0xDB960,0));
    hooks.push_back(inline_hook(speed_stack,0xFAD07,{0xB8,0x67,0x66,0x66,0x66}));
    hooks.push_back(inline_hook(speed_value,0xFAD3F,{0x8D,0x84,0x24,0xB8,0,0,0}));
    hooks.push_back(inline_hook(speed_color,0xFAE47,{0x8D,4,0x80,0x66,0x0F,0x6E,0xC0}));
    auto expired=inline_hook(activity_expired,0xFB128,{0xC7,4,0xB5,0,0,0,0,0,0,0,0});
    field=address(at<void>(0x61A8CC4));std::memcpy(expired.expected+3,&field,4);hooks.push_back(expired);
    auto reset=inline_hook(shield_reset,0xF92D0,{0x80,0x25,0,0,0,0,0xFE});
    field=address(at<void>(0xA32BA95));std::memcpy(reset.expected+2,&field,4);hooks.push_back(reset);
    for(const auto [id,site]:{std::pair{shield_first,0xF9422u},std::pair{shield_second,0xF9459u},std::pair{shield_both,0xF94BAu}}) {
        auto write=inline_hook(id,site,{0x88,0x15,0,0,0,0});std::memcpy(write.expected+2,&field,4);hooks.push_back(write);
    }
    hooks.push_back(call(item_debug,0xAE7B6,0xAECB0,0));
    hooks.push_back(call(message_input,0xF5BCE,0xD3BF0,0));
    hooks.push_back(inline_hook(message_prompt_end,0xF5BB8,{0x8B,0x55,0xF0,0x8B,0x4D,0xEC}));
    hooks.push_back(inline_hook(map_result,0xE5F5E,{0x8B,0xC8,0x83,0xF9,0x64}));
    hooks.push_back(call(map_input,0xE5F59,0xD1120,0));
    auto save=inline_hook(second_save,0x10D350,{0x83,0x3D,0,0,0,0,0});
    field=address(at<void>(0x61BBAFC));std::memcpy(save.expected+2,&field,4);hooks.push_back(save);
    for(const auto [id,site]:{std::pair{map_parent_restore,0x10D3BAu},
            std::pair{second_parent_restore,0x10D44Au}}) {
        auto restore=inline_hook(id,site,{0x83,0x3D,0,0,0,0,0});
        field=address(at<void>(0x61BBA5C));std::memcpy(restore.expected+2,&field,4);hooks.push_back(restore);
    }
    hooks.push_back(call(main_input,0x17D0A6,0xD3BF0,0));
    hooks.push_back(call(modal_input,0xF5AC3,0xD3BF0,0));
    auto modal=inline_hook(modal_finished,0xF5A78,{0x83,0x3D,0,0,0,0,0});
    field=address(at<void>(0x61BBA5C));std::memcpy(modal.expected+2,&field,4);hooks.push_back(modal);
    hooks.push_back(inline_hook(target_result,0xF7DD9,{0x3D,0x2F,4,0,0}));
    // Both original branches are continued explicitly. The actual target-list
    // selection at ESP+18 remains owned by this suspended native page.
    hooks.push_back(inline_hook(target_help_branch,0xF7B49,
        {0x89,0x44,0x24,0x18,0x38,0x5C,0x24,0x17,0x0F,0x84,0x0C,1,0,0}));
    auto help_end=inline_hook(target_help_end,0xF7BB6,{0x3B,0x05,0,0,0,0});
    field=address(at<void>(0x61A618C));std::memcpy(help_end.expected+2,&field,4);hooks.push_back(help_end);
    hooks.push_back(inline_hook(location_cache,0x8FFE5,{0x85,0xC0,0x0F,0x84,0x58,8,0,0}));
    hooks.push_back(call(target_parent_restore,0xF854D,0x10C690,0));
    auto operand=[&](u32 id,u32 site,std::initializer_list<unsigned char> bytes,u32 offset,u32 field) {
        auto hook=inline_hook(id,site,bytes);const auto value=address(at<void>(field));
        std::memcpy(hook.expected+offset,&value,4);hooks.push_back(hook);
    };
    // FAA4B and FB115 already belong to hud_target_entry and the HUD icon
    // activity_age event. Observe those actual events without duplicate hooks.
    operand(widget_mode,0xFAACA,{0x0F,0xB6,0x0D,0,0,0,0},3,0xA32B054);
    operand(widget_hide,0xFAAEB,{0x80,0x3D,0,0,0,0,1},2,0x61A9DAF);
    operand(widget_fallen,0xFAB22,{0x80,0x3D,0,0,0,0,0},2,0x53908FB);
    operand(widget_action,0xFAB91,{0x8A,0x15,0,0,0,0},2,0xA32BCE6);
    operand(widget_hiding,0xFAC48,{0x83,0x3D,0,0,0,0,1},2,0xA3840E4);
    operand(widget_direction_label,0xFACA1,{0xA1,0,0,0,0},1,0xA384110);
    operand(widget_units,0xFAD61,{0x83,0x3D,0,0,0,0,0},2,0xA2D0AF4);
    operand(widget_ratio,0xFAE3D,{0x0F,0xB6,0x05,0,0,0,0},3,0xA32B1AF);
    hooks.push_back(call(widget_query_second,0xFAE71,0xDB960,0));
    operand(widget_direction_icon,0xFAF3B,{0x8B,0x15,0,0,0,0},2,0xA384110);
    operand(widget_activity,0xFB060,{0x8B,0x1C,0xB5,0,0,0,0},3,0x61A8CC4);
    hooks.push_back(inline_hook(widget_publication,0xFB247,{0x69,0xC8,0x48,0x0C,0,0}));
    operand(widget_rect,0xFB258,{0x89,0x81,0,0,0,0},2,0xA38521C);
    operand(widget_target,0x10C400,{0xA3,0,0,0,0},1,0x61BBB0C);
    uwcn_hud_widget_prefix_end=host->image_base+0xFB250;
}

Status messages(u32 wait_frame=0,NativeFrame* input=nullptr) {
    auto flow_wait=wait_frame && native_message_flow::owns_wait(wait_frame);
    const auto source=flow_wait ? native_message_flow::waiting_source(wait_frame) : native_message_flow::current(
        {native_root_component::current(),0x61A8CE4,static_cast<u32>(TextComponent::message_literal)});
    if(!wait_frame) {wait_frame=native_message_flow::waiting_frame(source);flow_wait=wait_frame!=0;}
    // F5BAE clears the original 100 seed after the first Continue control.
    // The accepted record's entry seed and acknowledged count retain exactly
    // this native semantic choice, including an already-open pre-upgrade wait.
    // All 45 independent direct F5B00 callers in this PE write counter=100
    // and ECX=0 immediately before their call. Only the three F6510 parents
    // have the repeated line-count protocol and own a Flow continuation.
    const auto continue_control=wait_frame && (flow_wait ? native_message_flow::waiting_continue(wait_frame) : true);
    auto status=native_message_flow::paint(source);
    if(status==Status::ok && wait_frame) {
        if(!flow_wait && input) {
            const auto& current=native_message_flow::current_state(source);
            input->ebx=current.cursor_x;*ptr<u32>(wait_frame-0x18)=current.cursor_y;
        }
        *at<std::uint8_t>(0x478E0E9)=continue_control ? 100 : 0;
        prompt_constructing=true;
        const BorrowedFrame fragment{address(at<void>(0xF5B7F)),wait_frame};
        uwcn_hud_borrow_frame(&fragment);
        prompt_constructing=false;
    }
    if(status==Status::ok) native_language_redraw::completed(messages_view);
    return status;
}
Status rebuild() {
    // 51770 constructs its special item name through NPC slot 499, including
    // REP MOVS of 568h bytes and its +67h discriminator. Preserve that exact
    // formatter scratch record while the original complete wielded UI runs.
    std::array<std::uint8_t,0x568> item_name_record;
    std::memcpy(item_name_record.data(),at<void>(0x5DF9DB8),item_name_record.size());
    constructing=true;
    using Native=void (UWCN_CALL *)();
    reinterpret_cast<Native>(host->image_base+0xFA2A0)();
    reinterpret_cast<void (__fastcall *)(const char*)>(host->image_base+0xF90D0)(command.c_str());
    reinterpret_cast<Native>(host->image_base+0x102D10)();
    reinterpret_cast<Native>(host->image_base+0xFF040)();
    reinterpret_cast<Native>(host->image_base+0x103640)();
    reinterpret_cast<Native>(host->image_base+0x8FF70)();
    if(widget_published) {
        widget_input=&published_widget;widget_phase=0;
        native_hud_icons::borrow_direction(&widget_input->direction_icon);
        reinterpret_cast<Native>(host->image_base+0xFAA30)();
    }
    if(working_widget_phase) {
        widget_input=&working_widget;widget_phase=working_widget_phase;
        native_hud_icons::borrow_direction(&widget_input->direction_icon);
        reinterpret_cast<Native>(host->image_base+0xFAA30)();
    }
    native_hud_icons::borrow_direction(nullptr);
    widget_input=nullptr;widget_phase=0;
    constructing=false;
    std::memcpy(at<void>(0x5DF9DB8),item_name_record.data(),item_name_record.size());
    const auto status=messages();
    if(status==Status::ok) native_language_redraw::completed(hud_view);
    return status;
}
Status save_second() {
    // 10D340 owns this original cache and its flag. Only its initial cache-hit
    // decision is bypassed; its native rectangle/copy/flag lifecycle runs whole.
    second_constructing=true;
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x10D340)();
    second_constructing=false;
    return Status::ok;
}
Status refresh_second() {
    const auto status=native_parent_cache_language::game_parent();return status==Status::ok ? save_second() : status;
}
bool known_map_wait(const NativeEvent& event) {
    // E5EAA/E5EB0 select this exact original map target and context. E5F59
    // is CALL-hooked, so D1120's own return slot belongs to the resident.
    if(*at<u32>(0xA1C1CBC)!=*at<u32>(0x5F937B0) || *at<u32>(0xA1C2010)!=0xE) return false;
    const auto page=*ptr<const u32>(event.frame->ebp);
    const auto caller=*ptr<const u32>(page+4)-static_cast<u32>(host->image_base);
    // The two E5990 callers are unhooked; the original page EBP survives.
    return caller==0x1591CA || caller==0x17DF35;
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=false;
    if(event.id==hud_target_entry && event.phase!=NativePhase::after && !widget_input) {
        working_widget={};working_widget_phase=0;accepting_widget=true;
        // Preserve this event's original promote_hud consumer below.
    }
    if(event.id==0x5A05 && event.phase!=NativePhase::after) {
        // Shared original FB115 MOV EAX,clock. The ordinary HUD icon event
        // remains responsible for its own complete native consumer.
        if(widget_input) {
            event.frame->eax=widget_input->clock;result.resume_rva=0xFB11A;handled=true;
        } else if(accepting_widget) working_widget.clock=*at<u32>(0xA32B180);
        return Status::ok;
    }
    if(event.id==speed_query || event.id==widget_query_second) {
        handled=true;
        if(widget_input) {
            if(event.phase==NativePhase::before) {
                result.skip_original=1;
                if(!widget_phase || (event.id==speed_query && widget_phase==2))
                    event.frame->eax=event.id==speed_query ? widget_input->query_first : widget_input->query_second;
            }
        } else if(event.phase==NativePhase::before)
            working_widget_phase=event.id==speed_query ? 1 : 2;
        else if(event.phase==NativePhase::after) {
            if(event.id==speed_query) working_widget.query_first=event.frame->eax;
            else working_widget.query_second=event.frame->eax;
            working_widget_phase=0;
        }
        return Status::ok;
    }
    if(event.id>=widget_mode && event.id<=widget_target && event.phase!=NativePhase::after) {
        handled=true;
        auto zero=[&](bool value,u32 next) {
            event.frame->eflags=(event.frame->eflags&~u32{0x40})|(value ? 0x40u : 0u);
            result.resume_rva=next;
        };
        switch(event.id) {
        case widget_mode:
            if(widget_input) {event.frame->ecx=widget_input->mode;result.resume_rva=0xFAAD1;}
            else working_widget.mode=*at<std::uint8_t>(0xA32B054);
            break;
        case widget_hide:
            if(widget_input) zero(widget_input->hide==1,0xFAAF2);
            else working_widget.hide=*at<std::uint8_t>(0x61A9DAF);
            break;
        case widget_fallen:
            if(widget_input) zero(widget_input->fallen==0,0xFAB29);
            else working_widget.fallen=*at<std::uint8_t>(0x53908FB);
            break;
        case widget_action:
            if(widget_input) {
                event.frame->edx=(event.frame->edx&~u32{0xFF})|widget_input->action;result.resume_rva=0xFAB97;
            } else working_widget.action=*at<std::uint8_t>(0xA32BCE6);
            break;
        case widget_hiding:
            if(widget_input) zero(widget_input->hiding==1,0xFAC4F);
            else working_widget.hiding=*at<u32>(0xA3840E4);
            break;
        case widget_direction_label:
            if(widget_input) {event.frame->eax=widget_input->direction_label;result.resume_rva=0xFACA6;}
            else working_widget.direction_label=*at<u32>(0xA384110);
            break;
        case widget_units:
            if(widget_input) zero(widget_input->units==0,0xFAD68);
            else working_widget.units=*at<u32>(0xA2D0AF4);
            break;
        case widget_ratio:
            if(widget_input) {event.frame->eax=widget_input->ratio;result.resume_rva=0xFAE44;}
            else working_widget.ratio=*at<std::uint8_t>(0xA32B1AF);
            break;
        case widget_direction_icon:
            if(widget_input) {event.frame->edx=widget_input->direction_icon;result.resume_rva=0xFAF41;}
            else working_widget.direction_icon=*at<u32>(0xA384110);
            break;
        case widget_activity:
            if(widget_input) {event.frame->ebx=widget_input->activity[event.frame->esi];result.resume_rva=0xFB067;}
            else working_widget.activity[event.frame->esi]=at<u32>(0x61A8CC4)[event.frame->esi];
            break;
        case widget_publication:
            if(!widget_input) {published_widget=working_widget;widget_published=true;accepting_widget=false;}
            break;
        case widget_rect:
            if(widget_input && widget_phase) result.resume_rva=0xFB27F;
            break;
        case widget_target:
            widget_published=accepting_widget=false;working_widget_phase=0;working_widget={};published_widget={};
            break;
        }
        return Status::ok;
    }
    if(event.id==0x5903 && prompt_constructing) {handled=true;return Status::ok;}
    // Shared real D1120 result, before its ordinary -2 processing. Return
    // through that native frame, then reuse the existing map page frame.
    if(event.id==0x5100 && event.phase!=NativePhase::after &&
        event.frame->eax==static_cast<u32>(-2) && native_language_redraw::pending(map_view) &&
        known_map_wait(event)) {
        map_selection=*at<u32>(0x5F54AB0);map_constructing=true;
        result.resume_rva=0xD19B3;handled=true;return Status::ok;
    }
    if(event.id<command_input || event.id>target_parent_restore) return Status::ok;
    handled=true;
    if(event.id==main_input || event.id==modal_input) {
        if(event.phase==NativePhase::after && event.frame->eax==static_cast<u32>(-2) &&
            native_language_redraw::pending(hud_view)) {
            // The ordinary 17D014 constructor precedes this particular main
            // wait on every entry. This is its confirmed original input.
            if(event.id==main_input) adopt_main_wait();
            auto status=event.id==modal_input ? native_first_cache_language::pause_parent() : rebuild();
            if(status!=Status::ok) return status;
            if(event.id==modal_input) {
                modal_constructing=true;
                reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0xF5A30)();
                modal_constructing=false;
            }
            reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x10B720)();
            // The language event has been consumed. 17D0BD otherwise treats
            // -2 as a request for 99BE0's world/visibility business rebuild;
            // its ordinary continuation already uses the no-action value 0.
            if(event.id==main_input) event.frame->eax=0;
        }
        return Status::ok;
    }
    if(event.id==message_input) {
        if(event.phase==NativePhase::after && event.frame->eax==static_cast<u32>(-2) &&
            native_language_redraw::pending(messages_view)) {
            const auto status=native_language_redraw::pending(hud_view) ? native_parent_cache_language::game_parent() : Status::ok;
            return status==Status::ok ? messages(event.frame->ebp,event.frame) : status;
        }
        return Status::ok;
    }
    if(event.phase==NativePhase::after) return Status::ok;
    switch(event.id) {
    case command_input:
        if(!constructing) {
            const auto* original=ptr<const char>(event.frame->ecx);
            if(std::strcmp(original,ptr<char>(*at<u32>(0xF9119)))==0) adopt_main_wait();
            else adopt_command(original);
        }
        break;
    case completed_x:case completed_y:case hide_write:case activity_expired:
    case shield_reset:case shield_first:case shield_second:case shield_both:
        if(constructing) result.skip_original=1;
        break;
    case message_panel:if(constructing) result.resume_rva=0xFA34E;break;
    case hud_finished:if(constructing) result.resume_rva=0xFA794;break;
    case item_debug:if(constructing) result.skip_original=1;break;
    case speed_stack:
        if(widget_input && widget_phase==1) result.resume_rva=static_cast<u32>(
            reinterpret_cast<std::uintptr_t>(uwcn_hud_widget_prefix_return)-host->image_base);
        else if(widget_input && widget_phase==2) result.resume_rva=0xFAD3C;
        break;
    case speed_value:
        if(widget_input && widget_phase==2) {
            if(widget_input->units) result.resume_rva=0xFADD7;
            else {
                event.frame->eax=**at<const u32*>(0xFADBC);
                result.resume_rva=0xFADC3;
            }
        }
        break;
    case speed_color:
        if(widget_input && widget_phase==2) result.resume_rva=static_cast<u32>(
            reinterpret_cast<std::uintptr_t>(uwcn_hud_widget_prefix_return)-host->image_base);
        break;
    case message_prompt_end:if(prompt_constructing) result.resume_rva=fragment_return();break;
    case map_result:
        if(map_constructing) {
            event.frame->esi=*at<u32>(0x18C288);result.resume_rva=0xE5AC0;
        }
        break;
    case map_input:
        if(map_constructing) {
            *at<u32>(0x5F54AB0)=map_selection;map_constructing=false;
            native_language_redraw::completed(map_view);
        }
        break;
    case second_save:if(second_constructing) result.resume_rva=0x10D359;break;
    case map_parent_restore:case second_parent_restore:
        if(native_ui_scene::cache_needs_language(static_cast<u32>(native_ui_cache_owners::Slot::second))) {
            bool parent{};const auto status=native_parent_cache_language::second_parent(event,parent);
            return parent ? status : refresh_second();
        }
        break;
    case modal_finished:if(modal_constructing) result.resume_rva=0xF5AE4;break;
    case target_result:
        if(event.frame->eax==static_cast<u32>(-2) && native_language_redraw::pending(hud_view)) {
            const auto mode=*ptr<const std::uint8_t>(event.frame->esp+0x16);
            target_heading=mode&1 ? std::string{} : native_hud_command_migration::target_title(event);
            target_x=event.frame->ebx;target_y=event.frame->esi;target_item=event.frame->edi;
            const auto status=native_parent_cache_language::game_parent();if(status!=Status::ok) return status;
            // Re-save the exact original named look rectangle before the
            // original target header is reconstructed over its new parent.
            reinterpret_cast<void (__fastcall *)(const char*,const void*)>(host->image_base+0x10C540)(
                ptr<const char>(*at<u32>(0xF78BC)),ptr<const void>(event.frame->esp+0x40));
            event.frame->ebx=0;event.frame->esi=0;event.frame->edi=address(target_heading.c_str());
            // F784F originally lends this same title to F7AD0's %s.
            // F7CFD has since reused the slot for the saved display float;
            // replaying the construction must restore both original inputs.
            // F7CFD overwrites it again before the resumed input consumes it.
            *ptr<u32>(event.frame->esp+0x24)=event.frame->edi;
            target_constructing=true;result.resume_rva=0xF78B1;
        }
        break;
    case target_help_branch: {
        const auto help=*ptr<const std::uint8_t>(event.frame->esp+0x17);
        if(target_constructing) {
            if(help) result.resume_rva=0xF7B57;
            else {
                event.frame->ebx=target_x;event.frame->esi=target_y;event.frame->edi=target_item;
                target_constructing=false;target_heading.clear();result.resume_rva=0xF7CD9;
            }
        } else {
            *ptr<u32>(event.frame->esp+0x18)=event.frame->eax;
            result.resume_rva=help==static_cast<std::uint8_t>(event.frame->ebx) ? 0xF7C63 : 0xF7B57;
        }
        break;
    }
    case target_help_end:
        if(target_constructing) {
            event.frame->ebx=target_x;event.frame->esi=target_y;event.frame->edi=target_item;
            target_constructing=false;target_heading.clear();result.resume_rva=0xF7CD9;
        }
        break;
    case location_cache:
        result.resume_rva=constructing || event.frame->eax!=0 ? 0x8FFED : 0x90845;
        break;
    case target_parent_restore:
        return native_parent_cache_language::restore_hud_named(event);
    }
    return Status::ok;
}
std::vector<std::uint8_t> save() {
    const auto existing=9*sizeof(u32)+command.size()+target_heading.size();
    std::vector<std::uint8_t> result(existing+2*sizeof(u32)+2*sizeof(WidgetInput));
    const u32 state[]{command_constructed?1u:0u,map_constructing?1u:0u,map_selection,static_cast<u32>(command.size()),
        target_constructing?1u:0u,target_x,target_y,target_item,static_cast<u32>(target_heading.size())};
    std::memcpy(result.data(),state,sizeof(state));std::memcpy(result.data()+sizeof(state),command.data(),command.size());
    std::memcpy(result.data()+sizeof(state)+command.size(),target_heading.data(),target_heading.size());
    const u32 widget_state[]{widget_published?1u:0u,working_widget_phase};
    auto* widgets=result.data()+existing;
    std::memcpy(widgets,widget_state,sizeof(widget_state));widgets+=sizeof(widget_state);
    std::memcpy(widgets,&published_widget,sizeof(published_widget));widgets+=sizeof(published_widget);
    std::memcpy(widgets,&working_widget,sizeof(working_widget));
    return result;
}
void restore(const void* payload,u32) {
    const auto* state=static_cast<const u32*>(payload);
    command_constructed=state[0]!=0;map_constructing=state[1]!=0;map_selection=state[2];
    command.assign(reinterpret_cast<const char*>(state+9),state[3]);
    target_constructing=state[4]!=0;target_x=state[5];target_y=state[6];target_item=state[7];
    target_heading.assign(reinterpret_cast<const char*>(state+9)+state[3],state[8]);
    const auto* widgets=reinterpret_cast<const std::uint8_t*>(state+9)+state[3]+state[8];
    u32 widget_state[2];std::memcpy(widget_state,widgets,sizeof(widget_state));widgets+=sizeof(widget_state);
    widget_published=widget_state[0]!=0;working_widget_phase=widget_state[1];
    std::memcpy(&published_widget,widgets,sizeof(published_widget));widgets+=sizeof(published_widget);
    std::memcpy(&working_widget,widgets,sizeof(working_widget));
    constructing=prompt_constructing=second_constructing=modal_constructing=false;
    widget_input=nullptr;widget_phase=0;
    accepting_widget=working_widget_phase!=0;
}
}
