// One accepted native conversation, with each speaker's logical paragraphs
// and complete accepted sentence inputs.
// There are no output lines, coordinates, styles, frames or drawing records.
namespace native_conversation_language {
using Root=native_root_component::RootRevision;
struct Paragraph {std::vector<std::string> sentences;};
struct Source {u32 actor;std::array<std::vector<Paragraph>,2> speech;};
std::map<Root,Source> sources;
bool constructing{},emote_constructing{};
u32 actor{};
Root constructing_root{};
Status construction_status{};
enum Hook:u32 {
    background=0x5240,npc_panel,player_panel,npc_input,player_input,
    npc_scalar,player_scalar,npc_fit,npc_tail_fit,npc_advance,npc_tail_advance,
    player_fit,player_advance,player_tail_advance,npc_text,npc_tail_text,
    player_text,player_tail_text,normalize,npc_flip,player_flip,delay,present,
    player_reset_end,emote_cleanup,emote_input,emote_end,title,
    title_actor,panel_actor,portrait_actor,emote_text,
    paragraph_break_first=0x5260,paragraph_break_end=paragraph_break_first+4
};
bool owns(Root root) {return sources.find(root)!=sources.end();}
void prune() {
    const auto live=native_root_component::revisions();
    for(auto i=sources.begin();i!=sources.end();)
        if(std::find(live.begin(),live.end(),i->first)==live.end()) i=sources.erase(i);
        else ++i;
}
u32 continuation(const void* function) {
    return static_cast<u32>(reinterpret_cast<std::uintptr_t>(function)-host->image_base);
}
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_conversation_advance() {
    __asm__ __volatile__("pushl $1024\n\tpushl $0\n\tjmp *%edx\n\t");
}
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_conversation_emote_continue() {
    __asm__ __volatile__("addl $36,%esp\n\tjmp *%eax\n\t");
}
struct Frame {u32 target,frame;};
extern "C" __attribute__((naked)) void UWCN_CALL uwcn_conversation_frame(const Frame*) {
    __asm__ __volatile__(
        "pushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "movl 20(%esp),%eax\n\tmovl 4(%eax),%ebp\n\tcall *(%eax)\n\t"
        "popl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tret\n\t");
}
void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(call(background,0x1342E5,0x1127C0,4));
    hooks.push_back(call(npc_panel,0x13418E,0x116270,5));
    hooks.push_back(call(player_panel,0x134242,0x116270,5));
    hooks.push_back(inline_hook(npc_input,0x1339C6,{0x8B,0xF9,0x8B,0xD7,0x89,0xBD,0xF4,0xF7,0xFF,0xFF}));
    hooks.push_back(inline_hook(player_input,0x134366,{0x8B,0xF9,0xC6,0x45,0x98,0}));
    hooks.push_back(inline_hook(npc_scalar,0x133A16,{0x8D,0x95,0xF8,0xF7,0xFF,0xFF}));
    hooks.push_back(inline_hook(player_scalar,0x1343A6,{0x8D,0x95,0x34,0xFF,0xFF,0xFF}));
    auto field=address(at<void>(0x1E9798));
    for(const auto [id,site]:{std::pair{npc_fit,0x133A8Fu},std::pair{npc_tail_fit,0x133B3Fu}}) {
        auto fit=inline_hook(id,site,{0x8B,0x15,0,0,0,0,0x8D,4,0xCE});
        std::memcpy(fit.expected+2,&field,4);hooks.push_back(fit);
    }
    hooks.push_back(inline_hook(npc_advance,0x133ADD,{0x2B,0xCA,0x68,0,4,0,0}));
    auto npc_tail=inline_hook(npc_tail_advance,0x133B88,{0xA1,0,0,0,0,0x2B,0xCA});
    field=address(at<void>(0x1E97A0));std::memcpy(npc_tail.expected+1,&field,4);hooks.push_back(npc_tail);
    auto fit=inline_hook(player_fit,0x13440F,{0x8B,0x15,0,0,0,0,0x8D,4,0xCE});
    field=address(at<void>(0x1E97A4));std::memcpy(fit.expected+2,&field,4);hooks.push_back(fit);
    for(const auto [id,site]:{std::pair{player_advance,0x134457u},std::pair{player_tail_advance,0x1344ADu}}) {
        auto advance=inline_hook(id,site,{0xA1,0,0,0,0,0x2B,0xCA});
        field=address(at<void>(0x1E979C));std::memcpy(advance.expected+1,&field,4);hooks.push_back(advance);
    }
    hooks.push_back(call(npc_text,0x133AC0,0x10E5A0,3));
    hooks.push_back(call(npc_tail_text,0x133B70,0x10E5A0,3));
    hooks.push_back(call(player_text,0x13443D,0x10E5A0,3));
    hooks.push_back(call(player_tail_text,0x134495,0x10E5A0,3));
    hooks.push_back(call(normalize,0xAD5A7,0xAD4B0,0));
    for(const auto [id,site]:{std::pair{npc_flip,0x13416Au},std::pair{player_flip,0x134238u}}) {
        auto write=inline_hook(id,site,{0xC7,5,0,0,0,0,0,0,0,0});
        field=address(at<void>(0x61BBA5C));std::memcpy(write.expected+2,&field,4);hooks.push_back(write);
    }
    auto wait=inline_hook(delay,0x133AFD,{0x6A,3,0xFF,0x15,0,0,0,0,0x83,0xC4,4});
    field=address(at<void>(0x18C268));std::memcpy(wait.expected+4,&field,4);hooks.push_back(wait);
    hooks.push_back(call(present,0x133B08,0x10B720,0));
    hooks.push_back(call(player_reset_end,0x1421D0,0x134B60,0));
    hooks.push_back(inline_hook(emote_cleanup,0x134DFC,{0x83,0xC4,0x24,0x85,0xFF}));
    hooks.push_back(call(emote_input,0x134E91,0xD3C80,0));
    auto end=inline_hook(emote_end,0x134E96,{0xB9,0,0,0,0});
    field=address(at<void>(0x1B1AD8));std::memcpy(end.expected+1,&field,4);hooks.push_back(end);
    hooks.push_back(call(title,0x134312,0xF8F80,0));
    for(const auto [id,site]:{std::pair{title_actor,0x1342EAu},std::pair{panel_actor,0x13415Bu}}) {
        auto read=inline_hook(id,site,{0x8B,0x0D,0,0,0,0});
        field=address(at<void>(0xA220630));std::memcpy(read.expected+2,&field,4);hooks.push_back(read);
    }
    auto portrait=inline_hook(portrait_actor,0x13419E,{0x69,0x0D,0,0,0,0,0x68,5,0,0});
    field=address(at<void>(0xA220630));std::memcpy(portrait.expected+2,&field,4);hooks.push_back(portrait);
    hooks.push_back(call(emote_text,0x134E75,0x10E910,4));
    constexpr u32 breaks[]{0x13867B,0x138D5B,0x138E32,0x140C21};
    for(u32 i=0;i<std::size(breaks);++i) {
        auto boundary=inline_hook(paragraph_break_first+i,breaks[i],{0x83,0x3D,0,0,0,0,0x0F});
        field=address(at<void>(0x1E97A0));std::memcpy(boundary.expected+2,&field,4);hooks.push_back(boundary);
    }
    auto boundary_end=inline_hook(paragraph_break_end,0x138695,{0xB9,0,0,0,0});
    field=address(at<void>(0x1B2960));std::memcpy(boundary_end.expected+1,&field,4);hooks.push_back(boundary_end);
}
Status unicode_title(const NativeEvent& event,u32& input) {
    const auto original=ptr<const char>(input);
    if(!native_name_input::requires_unicode(original)) return Status::ok;
    begin(event,Scope::profile_identity_unicode);
    std::vector<char> encoded;
    const auto status=encode_component_original(original,encoded);
    return status==Status::ok ? lend_text(event,encoded,input,Scope::titled_panel) : status;
}
Status accepted(const NativeEvent& event,u32 speaker) {
    if(constructing || !owns(native_root_component::current())) return Status::ok;
    std::string original;
    const auto status=decode_parser_original(ptr<const char>(event.frame->ecx),original);
    if(status!=Status::ok) return status;
    // NPC empty input returns immediately; player empty input still reaches
    // its actual final +8. Keep that accepted empty sentence too.
    if(speaker==0 && original.empty()) return Status::ok;
    // Each complete native input ends with its own +8 after its final fit.
    // Preserve sentence boundaries: inserting an ASCII space into the input
    // instead would include that space in the preceding word-fit operation.
    auto& speech=sources.find(native_root_component::current())->second.speech[speaker];
    if(speech.empty()) speech.emplace_back();
    speech.back().sentences.push_back(std::move(original));
    return Status::ok;
}
const char* raw(const NativeEvent& event,bool player) {
    return ptr<const char>(*ptr<const u32>(event.frame->ebp-(player?0xD0:0x80C)));
}
bool unicode(const NativeEvent& event,bool player) {return native_name_input::requires_unicode(raw(event,player));}
Status width(const NativeEvent& event,bool player,u32& result) {
    const native_name_input::UnicodeMeasure scope(raw(event,player));
    render::Metrics measured{};
    const auto status=metrics(ptr<const char>(event.frame->ebp-(player?0x68:0x408)),measured);
    result=static_cast<u32>(measured.logical_width);return status;
}
Status rebuild() {
    const auto root=native_root_component::current();
    const auto source=sources.find(root)->second;
    const auto flip=*at<u32>(0x61BBA5C);
    *at<u32>(0x61BBA5C)=1;constructing=true;actor=source.actor;
    constructing_root=root;construction_status=Status::ok;
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x1342C0)();
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x134330)();
    auto status=construction_status;
    if(status==Status::ok) status=host->native_fragment(0x1421B7,0x1421D5);
    for(u32 speaker=0;status==Status::ok && speaker<2;++speaker) {
        for(std::size_t index=0;status==Status::ok && index<source.speech[speaker].size();++index) {
            if(index) {
                // The original complete conditional paragraph boundary owns
                // its own cursor comparison, line step and left origin.
                const native_component_calls::NoArgumentCall boundary{address(at<void>(0x13867B))};
                native_component_calls::uwcn_component_skill_help(&boundary);
            }
            for(const auto& sentence:source.speech[speaker][index].sentences) {
                // Parser input remains an ordinary native string: byte Nordic
                // data and UTF-8 names, with the native substitutions inverted.
                std::vector<char> original;
                status=encode_parser_original(sentence.c_str(),original);
                if(status!=Status::ok) break;
                reinterpret_cast<void (__fastcall *)(const char*)>(host->image_base+(speaker?0x134350:0x1339B0))(original.data());
            }
        }
    }
    sources.insert_or_assign(root,source);
    constructing=false;actor=0;constructing_root=0;
    native_root_component::activate(root);*at<u32>(0x61BBA5C)=flip;
    return status;
}
Status wait(const NativeEvent& event) {
    if(event.phase!=NativePhase::before ||
       !native_language_redraw::pending(native_language_redraw::View::hud) ||
       *ptr<const u32>(event.frame->ebp+4)!=host->image_base+0x134E96) return Status::ok;
    // The real original formatted message remains in the suspended emote
    // frame's -408h scratch. Its source is neither copied nor reconstructed.
    const auto owner=*ptr<const u32>(event.frame->ebp);
    const auto name=address(at<void>(0x1B1AD8));
    const auto slot=native_parent_cache_language::named_slot(ptr<const char>(name));
    const auto rect=*at<u32>(0xA1C1CA0+(slot-static_cast<u32>(native_ui_cache_owners::Slot::named0))*4);
    const auto flip=*at<u32>(0x61BBA5C);
    *at<u32>(0x61BBA5C)=1;
    native_root_component::activate(native_ui_scene::saved_background(slot));
    auto status=rebuild();
    if(status==Status::ok) {
        reinterpret_cast<void (__fastcall *)(u32,u32)>(host->image_base+0x10C540)(name,rect);
        emote_constructing=true;
        const Frame body{address(at<void>(0x134DC7)),owner};
        uwcn_conversation_frame(&body);
        emote_constructing=false;
    }
    *at<u32>(0x61BBA5C)=flip;
    if(status!=Status::ok) return status;
    native_language_redraw::completed(native_language_redraw::View::hud);
    reinterpret_cast<void (UWCN_CALL *)()>(host->image_base+0x10B720)();
    return Status::ok;
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=false;
    if(event.id<background || event.id>paragraph_break_end) return Status::ok;
    if(event.phase==NativePhase::after) {
        if(event.id==background && !constructing) {
            prune();sources.insert_or_assign(native_root_component::current(),Source{*at<u32>(0xA220630),{}});
        }
        if(event.id==npc_panel || event.id==player_panel || event.id==title || event.id==emote_text ||
           (event.id>=npc_text && event.id<=player_tail_text)) end(event.token);
        return Status::ok;
    }
    if(event.id==background && constructing) {
        // This is the same accepted 1342C0 background source. Re-enter its
        // complete 1127C0 factory through the existing root materialization
        // contract, so all foreground constructors retain this logical Root.
        construction_status=native_root_component::paint_background(constructing_root);
        result.skip_original=1;handled=true;return construction_status;
    }
    if(event.id==npc_panel || event.id==player_panel) {
        if(!constructing && owns(native_root_component::current())) {
            auto& source=sources.find(native_root_component::current())->second;
            const auto speaker=event.id==player_panel?1u:0u;
            source.speech[speaker].clear();
        }
        const auto status=unicode_title(event,event.arguments[2]);
        handled=status!=Status::ok;return status;
    }
    if(event.id==title) {
        const auto status=unicode_title(event,event.frame->ecx);handled=status!=Status::ok;return status;
    }
    if(event.id>=paragraph_break_first && event.id<paragraph_break_end) {
        if(!constructing && owns(native_root_component::current())) {
            auto& speech=sources.find(native_root_component::current())->second.speech[0];
            if(speech.empty()) speech.emplace_back();
            speech.emplace_back();
        }
        return Status::ok;
    }
    if(event.id==paragraph_break_end && constructing) {
        result.resume_rva=continuation(reinterpret_cast<const void*>(native_component_calls::uwcn_component_fragment_return));
        handled=true;return Status::ok;
    }
    if(event.id==emote_text) {
        const auto original=ptr<const char>(event.arguments[1]);
        if(native_name_input::requires_unicode(original)) {
            begin(event,Scope::profile_identity_unicode);
            std::vector<char> encoded;const auto status=encode_component_original(original,encoded);
            if(status!=Status::ok) return status;
            return lend_text(event,encoded,event.arguments[1],Scope::hud_centered,event.arguments[3]);
        }
        return Status::ok;
    }
    if(constructing && (event.id==title_actor || event.id==panel_actor || event.id==portrait_actor)) {
        event.frame->ecx=event.id==portrait_actor ? actor*0x568 : actor;
        result.skip_original=1;handled=true;return Status::ok;
    }
    if(event.id==npc_input || event.id==player_input) return accepted(event,event.id==player_input?1:0);
    if(event.id==npc_scalar || event.id==player_scalar) {
        const bool player=event.id==player_scalar;
        const auto* input=reinterpret_cast<const unsigned char*>(raw(event,player))+event.frame->ebx;
        const auto bytes=native_name_input::span(input);
        if(bytes) {
            const std::string scalar(reinterpret_cast<const char*>(input),bytes);
            std::vector<char> encoded;
            const auto status=encode_component_original(scalar.c_str(),encoded);
            if(status!=Status::ok) return status;
            std::memcpy(ptr<void>(event.frame->ebp-(player?0xCC:0x808)),encoded.data(),encoded.size());
            event.frame->ebx+=bytes-1;
        }
        return Status::ok;
    }
    if(event.id>=npc_text && event.id<=player_tail_text) {
        const bool player=event.id>=player_text;
        if(unicode(event,player)) begin(event,Scope::profile_identity_unicode);
        begin(event,Scope::text,event.arguments[2]);return Status::ok;
    }
    if(event.id==npc_fit || event.id==npc_tail_fit || event.id==player_fit) {
        const bool player=event.id==player_fit;
        if(unicode(event,player)) {
            u32 measured{};const auto status=width(event,player,measured);if(status!=Status::ok) return status;
            event.frame->eax=event.frame->esi+measured;
            event.frame->edx=*at<u32>(player?0x1E97A4:0x1E9798);
            // The original CMP and its wrap branch remain outside this hook.
            // Only their character-width operand is expanded for Unicode.
            result.skip_original=1;
        }
    }
    if(event.id==npc_advance || event.id==npc_tail_advance ||
       event.id==player_advance || event.id==player_tail_advance) {
        const bool player=event.id==player_advance || event.id==player_tail_advance;
        if(unicode(event,player)) {
            u32 measured{};const auto status=width(event,player,measured);if(status!=Status::ok) return status;
            event.frame->eax=*at<u32>(player?0x1E979C:0x1E97A0)+measured;
            if(event.id==npc_advance) {
                event.frame->edx=address(at<void>(0x133AE9));
                result.resume_rva=continuation(reinterpret_cast<const void*>(uwcn_conversation_advance));
            } else if(event.id==npc_tail_advance) result.resume_rva=0x133B92;
            else if(event.id==player_advance) {
                *ptr<char>(event.frame->ebp-0x68)=0;result.resume_rva=0x134465;
            } else result.resume_rva=0x1344B7;
        }
    }
    if((event.id==normalize || event.id==npc_flip || event.id==player_flip ||
        event.id==present || event.id==player_reset_end) && constructing) result.skip_original=1;
    if(event.id==delay) {
        if(!constructing) (*at<void (__cdecl *)(u32)>(0x18C268))(3);
        result.skip_original=1;
    }
    if(event.id==emote_cleanup && emote_constructing) {
        event.frame->eax=address(at<void>(0x134E3F));
        result.resume_rva=continuation(reinterpret_cast<const void*>(uwcn_conversation_emote_continue));
    }
    if(event.id==emote_input && emote_constructing) result.skip_original=1;
    if(event.id==emote_end && emote_constructing)
        result.resume_rva=continuation(reinterpret_cast<const void*>(native_component_calls::uwcn_component_fragment_return));
    handled=result.skip_original || result.resume_rva;return Status::ok;
}
template<class T> void append(std::vector<std::uint8_t>& output,const T& value) {
    const auto* bytes=reinterpret_cast<const std::uint8_t*>(&value);output.insert(output.end(),bytes,bytes+sizeof(T));
}
template<class T> T read(const std::uint8_t*& cursor) {T value;std::memcpy(&value,cursor,sizeof(T));cursor+=sizeof(T);return value;}
std::vector<std::uint8_t> save() {
    prune();std::vector<std::uint8_t> output;append(output,static_cast<u32>(sources.size()));
    for(const auto& [root,source]:sources) {
        append(output,root);append(output,source.actor);
        for(const auto& speech:source.speech) {
            append(output,static_cast<u32>(speech.size()));
            for(const auto& paragraph:speech) {
                append(output,static_cast<u32>(paragraph.sentences.size()));
                for(const auto& sentence:paragraph.sentences) {
                    append(output,static_cast<u32>(sentence.size()));
                    output.insert(output.end(),sentence.begin(),sentence.end());
                }
            }
        }
    }
    return output;
}
void restore(const void* payload,u32) {
    sources.clear();constructing=emote_constructing=false;actor=0;constructing_root=0;construction_status=Status::ok;
    const auto* cursor=static_cast<const std::uint8_t*>(payload);
    const auto count=read<u32>(cursor);
    for(u32 i=0;i<count;++i) {
        const auto root=read<Root>(cursor);Source source{};source.actor=read<u32>(cursor);
        for(auto& speech:source.speech) {
            const auto count=read<u32>(cursor);
            for(u32 index=0;index<count;++index) {
                Paragraph paragraph;const auto count=read<u32>(cursor);
                for(u32 sentence=0;sentence<count;++sentence) {
                    const auto bytes=read<u32>(cursor);
                    paragraph.sentences.emplace_back(reinterpret_cast<const char*>(cursor),bytes);cursor+=bytes;
                }
                speech.push_back(std::move(paragraph));
            }
        }
        sources.emplace(root,std::move(source));
    }
}
}
