// The remaining actual getst callers: one history-search field and twenty-one
// HUD command/name fields. Accepted input values belong to the logical prompt;
// no UI position, native frame or drawing contribution is retained.
namespace native_text_edit_language {
using Root=native_root_component::RootRevision;
using Flow=native_message_flow::Handle;
enum Hook:u32 { entry=0x52C0,initial_clear,initial_branch,input,finished,flags,history_end,affirmative_end };
enum class Construction {none,completed,origin,history,affirmative};
Construction constructing{};
struct Value {u32 color,capacity;std::string original;};
struct Prompt {bool affirmative;std::vector<Value> values;};
struct Source {Flow flow;std::map<u64,Prompt> prompts;};
struct Editing {bool active;Root root;Flow flow;u64 prompt;u32 caller,color,capacity;std::string shown;};
std::map<Root,Source> sources;
Editing editing{};
const Value* completed_value{};
Status construction_status{};
bool hud_caller(u32 caller) {
    switch(caller) {
    case 0x8B4F7:case 0x8B812:case 0x143226:
    case 0x16FEA2:case 0x17018C:case 0x170653:case 0x172E5C:
    case 0x1754C7:case 0x1776A6:case 0x177806:case 0x1795CC:
    case 0x17AF1D:case 0x17AF36:case 0x17B211:case 0x17B569:
    case 0x17B607:case 0x17B656:case 0x17B697:case 0x17B7AC:
    case 0x17BDFF:case 0x17C7E7:return true;
    default:return false;
    }
}
u32 accepted_caller(const NativeEvent& event) {
    // The character/animal name CALL scopes replace getst's direct return
    // with the resident After bridge. Both original callers establish EBP.
    // NameAnimal's own unhooked 143D40 CALL still returns to 143D45, and its
    // only getst CALL is 143221. Recover that exact native input owner from
    // the saved parent frame; no translated prompt or buffer is inspected.
    if(windows_build::is_3891() && native_name_input::state.active==1 &&
       *ptr<const u32>(*ptr<const u32>(event.frame->ebp)+4)==host->image_base+0x143D45)
        return 0x143226;
    return *ptr<const u32>(event.frame->ebp+4)-static_cast<u32>(host->image_base);
}
Flow flow(Root root) {
    return native_message_flow::current({root,0x61A8CE4,static_cast<u32>(TextComponent::message_literal)});
}
void prune() {
    const auto roots=native_root_component::revisions();
    for(auto source=sources.begin();source!=sources.end();)
        if(std::find(roots.begin(),roots.end(),source->first)==roots.end()) source=sources.erase(source);
        else {
            const auto current=flow(source->first);const auto& records=native_message_flow::get(current).records;
            source->second.flow=current;
            for(auto prompt=source->second.prompts.begin();prompt!=source->second.prompts.end();)
                if(std::find_if(records.begin(),records.end(),[&](const auto& record){return record.identity==prompt->first;})==records.end())
                    prompt=source->second.prompts.erase(prompt);
                else ++prompt;
            ++source;
        }
}
u32 continuation(const void* function) {
    return static_cast<u32>(reinterpret_cast<std::uintptr_t>(function)-host->image_base);
}
struct Setup {u32 target,frame,color,capacity;};
extern "C" std::uintptr_t urwcn_text_edit_initial_target{};
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_text_edit_initial() {
    // 10F68E cleans the second memset's original three arguments. The native
    // initial-buffer clearing call is skipped, but its stack shape remains.
    __asm__ __volatile__("subl $12,%esp\n\tjmp *_urwcn_text_edit_initial_target\n\t");
}
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_text_edit_setup_return() {
    // The borrowed 10F5C5 setup still executes its original PUSH EDI at
    // 10F5CD. The two original earlier saves belong to the suspended frame.
    __asm__ __volatile__("popl %edi\n\tret\n\t");
}
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_text_edit_setup(const Setup*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%eax\n\tmovl 4(%eax),%ebp\n\t"
        "movl 8(%eax),%ecx\n\tmovl 12(%eax),%edx\n\tcall *(%eax)\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t");
}
extern "C" __attribute__((naked)) void URWCN_CALL urwcn_text_edit_history(const native_component_calls::NoArgumentCall*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%eax\n\tsubl $128,%esp\n\tcall *(%eax)\n\taddl $128,%esp\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t");
}
void append_hooks(std::vector<HookSpec>& hooks) {
    auto start=inline_hook(entry,0x10F5C5,{0x8B,0x35,0,0,0,0,0x8B,0xD9});
    auto field=address(at<void>(0xA1C1CB4));std::memcpy(start.expected+2,&field,4);hooks.push_back(start);
    hooks.push_back(call(initial_clear,0x10F605,0x18AE60,3));
    auto initial=inline_hook(initial_branch,0x10F60D,{0xF6,5,0,0,0,0,1});
    field=address(at<void>(0x61BBA58));std::memcpy(initial.expected+2,&field,4);hooks.push_back(initial);
    hooks.push_back(call(input,0x10F719,0xD3BF0,0));
    auto finish=inline_hook(finished,0x10F924,{0x8B,0x4D,0xFC,0xB8,0,0,0,0});
    field=address(at<void>(0xA49B9A8));std::memcpy(finish.expected+4,&field,4);hooks.push_back(finish);
    auto flag=inline_hook(flags,0x10F930,{0xC7,5,0,0,0,0,0,0,0,0});
    field=address(at<void>(0x61BBA58));std::memcpy(flag.expected+2,&field,4);hooks.push_back(flag);
    hooks.push_back(inline_hook(history_end,0xFECCA,{0xBA,0x5F,0,0,0}));
    auto affirmative=inline_hook(affirmative_end,0xFBAAE,{0x83,0x3D,0,0,0,0,0});
    field=address(at<void>(0x61BBA5C));std::memcpy(affirmative.expected+2,&field,4);hooks.push_back(affirmative);
    urwcn_text_edit_initial_target=host->image_base+0x10F687;
}
Status history(const NativeEvent& event) {
    const auto current=native_menu_component::active();native_menu_component::retain(current);
    const auto owner=*ptr<const u32>(event.frame->ebp);
    const auto body=(owner&~u32{7})-0xD58;
    auto status=native_generic_menu_language::history(event);
    native_menu_component::activate(current);
    if(status==Status::ok) status=native_menu_component::paint(current);
    if(status==Status::ok) {
        const auto selected=*ptr<const u32>(body+0x1C);
        *at<u32>(0x5F54AB0)=selected;
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0xD0650)(selected,0);
        constructing=Construction::history;
        const native_component_calls::NoArgumentCall prompt{address(at<void>(0xFEBCB))};
        urwcn_text_edit_history(&prompt);constructing=Construction::none;
    }
    native_menu_component::release(current);return status;
}
Status after_message(Flow owner,const native_message_flow::Record& record) {
    // Only a real accepted getst associated with this exact completed prompt
    // contributes a semantic field. Later F6510 records remain in the same
    // native flow and perform their own full scroll over these native pixels.
    const auto source=sources.find(native_message_flow::get(owner).key.owner);
    if(source==sources.end()) return Status::ok;
    const auto prompt=source->second.prompts.find(record.identity);
    if(prompt==source->second.prompts.end()) return Status::ok;
    if(prompt->second.affirmative) {
        // 17C7E2 follows the true FB8A0 branch. Rebuild that original accepted
        // Yes echo at FBA91 using the flow's actual completed cursor output.
        constructing=Construction::affirmative;
        const native_component_calls::NoArgumentCall echo{address(at<void>(0xFBA91))};
        native_component_calls::urwcn_component_skill_help(&echo);constructing=Construction::none;
    }
    for(const auto& value:prompt->second.values) {
        constructing=Construction::completed;completed_value=&value;construction_status=Status::ok;
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0x10F5B0)(value.color,value.capacity);
        constructing=Construction::none;completed_value=nullptr;
        if(construction_status!=Status::ok) return construction_status;
    }
    return Status::ok;
}
Status hud() {
    const auto status=native_hud_language::rebuild();
    if(status!=Status::ok) return status;
    // paint preserves a caller's general cursor. Its actual canonical state
    // now includes completed prompt fields, in the original message order.
    const auto& state=native_message_flow::current_state(flow(native_root_component::current()));
    *at<u32>(0xA1C1CB4)=state.cursor_x;*at<u32>(0x61BBB3C)=state.cursor_y;
    return Status::ok;
}
Status redraw(const NativeEvent& event,DispatchResult& result,bool& handled,u32 caller) {
    const auto flip=*at<u32>(0x61BBA5C);*at<u32>(0x61BBA5C)=1;
    const auto status=caller==0xFECD6 ? history(event) : hud();
    if(status==Status::ok) {
        // Reuse getst's own complete setup on the real suspended frame. Its
        // current capacity/color enter unchanged; its native cursor inputs and
        // background sample come from the just-constructed prompt endpoint.
        constructing=Construction::origin;
        const Setup setup{address(at<void>(0x10F5C5)),event.frame->ebp,
            *ptr<const u32>(event.frame->ebp-0xAC),*ptr<const u32>(event.frame->ebp-0xB4)};
        urwcn_text_edit_setup(&setup);constructing=Construction::none;
        event.frame->esi=*ptr<const u32>(event.frame->ebp-0xA4);
        event.frame->edi=*ptr<const u32>(event.frame->ebp-0xB8);
        event.frame->ebx=*ptr<const u32>(event.frame->ebp-0xAC);
        native_language_redraw::completed(native_language_redraw::View::hud);
        result.resume_rva=0x10F6A0;handled=true;
    }
    *at<u32>(0x61BBA5C)=flip;return status;
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=false;
    // 3E589's real getst frame owns the encyclopedia keyword buffer. The
    // existing input CALL also identifies a frame suspended before hot reload.
    if(event.id==input && windows_build::is_3891() &&
       *ptr<const u32>(event.frame->ebp+4)==host->image_base+0x3E58E)
        native_name_input::activate_keyword();
    // The existing Full name_text hook owns this shared CALL and its After
    // scope retirement. Run this narrow semantic callback before Full, then
    // let Full continue its ordinary Unicode scope on the resulting input.
    if(event.id==native_full_language::name_text && event.phase==NativePhase::before) {
        if(constructing==Construction::completed) {
            std::vector<char> encoded;
            construction_status=encode_component_original(completed_value->original.c_str(),encoded);
            if(construction_status!=Status::ok) {handled=true;return construction_status;}
            if(native_name_input::requires_unicode(completed_value->original.c_str())) begin(event,Scope::profile_identity_unicode);
            const auto status=lend_text(event,encoded,event.arguments[0],Scope::text,event.arguments[2]);
            handled=status!=Status::ok;return status;
        }
        if(constructing==Construction::none && editing.active) {
            const auto status=decode_parser_original(ptr<const char>(event.arguments[0]),editing.shown);
            handled=status!=Status::ok;return status;
        }
        return Status::ok;
    }
    if(event.id==native_full_language::name_input_result &&
       event.phase!=NativePhase::after && event.frame->eax==static_cast<u32>(-2) &&
       native_language_redraw::pending(native_language_redraw::View::hud)) {
        const auto caller=accepted_caller(event);
        if(hud_caller(caller) || caller==0xFECD6) return redraw(event,result,handled,caller);
    }
    if(event.id==native_name_input::edit_dispatch && constructing==Construction::completed) {
        result.resume_rva=0x10F924;handled=true;return Status::ok;
    }
    if(event.id<entry || event.id>affirmative_end) return Status::ok;
    if(event.phase==NativePhase::after) return Status::ok;
    switch(event.id) {
    case entry:
        if(constructing==Construction::none) {
            const auto caller=accepted_caller(event);
            if(windows_build::is_3891() && caller==0x3E58E) native_name_input::activate_keyword();
            editing.active=hud_caller(caller);
            if(editing.active) {
                prune();const auto root=native_root_component::current();const auto current=flow(root);
                const auto prompt=native_message_flow::get(current).records.back().identity;
                auto [source,created]=sources.try_emplace(root,Source{current,{}});
                source->second.flow=current;
                auto [fields,new_prompt]=source->second.prompts.try_emplace(prompt,Prompt{});
                if(caller==0x17C7E7) fields->second.affirmative=true;
                editing={true,root,current,prompt,caller,event.frame->ecx,event.frame->edx,{}};
            }
        }
        break;
    case initial_clear:
        if(constructing==Construction::completed || constructing==Construction::origin) result.skip_original=1;
        break;
    case initial_branch:
        if(constructing==Construction::completed)
            result.resume_rva=continuation(reinterpret_cast<const void*>(urwcn_text_edit_initial));
        else if(constructing==Construction::origin)
            result.resume_rva=continuation(reinterpret_cast<const void*>(urwcn_text_edit_setup_return));
        break;
    case input:
        if(constructing==Construction::completed) {event.frame->eax=13;result.skip_original=1;}
        break;
    case finished:
        if(windows_build::is_3891() && *ptr<const u32>(event.frame->ebp+4)==host->image_base+0x3E58E)
            native_name_input::finish_keyword();
        if(constructing==Construction::none && editing.active) {
            sources.find(editing.root)->second.prompts.find(editing.prompt)->second.values.push_back(
                {editing.color,editing.capacity,editing.shown});
            editing={};
        }
        break;
    case flags:
        if(constructing==Construction::completed) result.skip_original=1;
        break;
    case history_end:
        if(constructing==Construction::history)
            result.resume_rva=continuation(reinterpret_cast<const void*>(native_component_calls::urwcn_component_fragment_return));
        break;
    case affirmative_end:
        if(constructing==Construction::affirmative)
            result.resume_rva=continuation(reinterpret_cast<const void*>(native_component_calls::urwcn_component_fragment_return));
        break;
    }
    handled=result.skip_original || result.resume_rva;return Status::ok;
}
template<class T> void append(std::vector<std::uint8_t>& output,const T& value) {
    const auto* bytes=reinterpret_cast<const std::uint8_t*>(&value);output.insert(output.end(),bytes,bytes+sizeof(T));
}
void string(std::vector<std::uint8_t>& output,const std::string& value) {
    append(output,static_cast<u32>(value.size()));output.insert(output.end(),value.begin(),value.end());
}
template<class T> T read(const std::uint8_t*& cursor) {T value;std::memcpy(&value,cursor,sizeof(T));cursor+=sizeof(T);return value;}
std::string string(const std::uint8_t*& cursor) {
    const auto bytes=read<u32>(cursor);std::string value(reinterpret_cast<const char*>(cursor),bytes);cursor+=bytes;return value;
}
std::vector<std::uint8_t> save() {
    prune();std::vector<std::uint8_t> output;append(output,static_cast<u32>(sources.size()));
    for(const auto& [root,source]:sources) {
        append(output,root);append(output,source.flow);append(output,static_cast<u32>(source.prompts.size()));
        for(const auto& [identity,prompt]:source.prompts) {
            append(output,identity);append(output,prompt.affirmative?1u:0u);append(output,static_cast<u32>(prompt.values.size()));
            for(const auto& value:prompt.values) {append(output,value.color);append(output,value.capacity);string(output,value.original);}
        }
    }
    append(output,editing.active?1u:0u);append(output,editing.root);append(output,editing.flow);append(output,editing.prompt);append(output,editing.caller);
    append(output,editing.color);append(output,editing.capacity);string(output,editing.shown);return output;
}
void restore(const void* payload,u32) {
    sources.clear();editing={};constructing=Construction::none;completed_value=nullptr;construction_status=Status::ok;
    const auto* cursor=static_cast<const std::uint8_t*>(payload);const auto count=read<u32>(cursor);
    for(u32 i=0;i<count;++i) {
        const auto root=read<Root>(cursor);Source source;source.flow=read<Flow>(cursor);
        const auto prompts=read<u32>(cursor);
        for(u32 index=0;index<prompts;++index) {
            const auto identity=read<u64>(cursor);Prompt prompt;prompt.affirmative=read<u32>(cursor)!=0;
            const auto values=read<u32>(cursor);
            for(u32 value=0;value<values;++value) {
                const auto color=read<u32>(cursor),capacity=read<u32>(cursor);
                prompt.values.push_back({color,capacity,string(cursor)});
            }
            source.prompts.emplace(identity,std::move(prompt));
        }
        sources.emplace(root,std::move(source));
    }
    editing.active=read<u32>(cursor)!=0;editing.root=read<Root>(cursor);editing.flow=read<Flow>(cursor);
    editing.prompt=read<u64>(cursor);editing.caller=read<u32>(cursor);
    editing.color=read<u32>(cursor);editing.capacity=read<u32>(cursor);editing.shown=string(cursor);
}
}
