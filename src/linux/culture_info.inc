// Linux 3.89 GAME.NFO consumers; see 20261019-culture-info-static.txt.
// Only source identities and synchronous text arguments live here. Native
// link_show/Lisaa_Linkit own wrapping, cursors, links, hit boxes and pixels.
struct CultureTopic { const char* name; const char* key; bool language_terms=false; };
const CultureTopic culture_topics[]{
    {"CULTURES","cultures"},{"CULTURE","cultures"},
    {"EASTERN PEOPLES","eastern_peoples"},{"WESTERN PEOPLES","western_peoples"},
    {"KAUMOLAISET","kaumo"},{"KAUMO","kaumo"},
    {"KIESSEL\xc4ISET","kiesse"},{"KIESSE","kiesse"},
    {"DRIIKIL\xc4ISET","driik"},{"DRIIK","driik"},
    {"REEMIL\xc4ISET","reemi"},{"REEMI","reemi"},
    {"SARTOLAISET","sartola"},{"SARTOLA","sartola"},
    {"ISLANDERS","islanders"},{"KOIVULAISET","koivula"},{"KOIVULA","koivula"},
    {"NORTHERN PEOPLES","northern_peoples"},{"NORTHERN TRIBES","northern_peoples"},
    {"KUIKKA-TRIBE","kuikka_tribe"},{"OWL-TRIBE","owl_tribe"},{"SEAL-TRIBE","seal_tribe"},
    {"NJERPEZIT","njerpez"},{"NJERPEZ","njerpez"},
    {"LANGUAGE","language",true},{"LANGUAGE INFLEXIONS","language_inflexions",true},
#include "encyclopedia_topics.inc"
};
const CultureTopic* culture_topic;
const CultureTopic* culture_preview;
bool culture_browser_chinese;
bool culture_line_active;
bool culture_help_active;
bool culture_redrawing;
unsigned culture_help_record;
long culture_record_offset;
std::map<std::string,std::string> culture_words;

std::string culture_text(const std::string& key) {
    return translated(C::culture_text,"",key.c_str());
}
const CultureTopic* find_culture_topic(const char* original) {
    const auto* upper=native<const char* (*)(const char*)>(0xf9140)(original);
    for(const auto& topic:culture_topics)
        if(std::strcmp(upper,topic.name)==0) return &topic;
    return nullptr; // Native keyword search can also return no topic.
}
// Complete native topic names are display units. Dots are a same-length
// transport for spaces inside a linked name; native topic storage stays English.
std::string culture_link_spelling(std::string text) {
    for(auto& value:text) if(value==' ') value='.';
    return text;
}
std::string culture_display_words(const char* input) {
    const auto whole=culture_words.find(input);
    if(whole!=culture_words.end()) return whole->second;
    std::string result;
    const auto* cursor=reinterpret_cast<const unsigned char*>(input);
    while(*cursor) {
        if(token(cursor)) { result.append(reinterpret_cast<const char*>(cursor),2); cursor+=2; continue; }
        if(*cursor==' ') { ++cursor; continue; } // Native tokenizer's separator, not Chinese spacing.
        if(*cursor<'A' || *cursor>'Z') { result.push_back(*cursor++); continue; }
        const auto* start=cursor;
        while(*cursor && !token(cursor) && *cursor!=' ' && *cursor!='<' && *cursor!='>' &&
              *cursor!=',' && *cursor!=';' && *cursor!=':' && *cursor!='[' && *cursor!=']') ++cursor;
        const std::string key(reinterpret_cast<const char*>(start),cursor-start);
        const auto found=culture_words.find(key);
        if(found!=culture_words.end()) result+=found->second;
        else result+=key; // Literal Latin spellings in the language articles.
    }
    return result;
}
std::string culture_link_source(const std::string& text) {
    std::string result;
    for(std::size_t i=0;i<text.size();) {
        if(text[i]!='{') { result.push_back(text[i++]); continue; }
        const auto end=text.find('}',i+1);
        result+=' ';
        result+=culture_link_spelling(text.substr(i+1,end-i-1));
        result+=' ';
        i=end+1;
    }
    return result;
}
unsigned topic_id(const CultureTopic* topic) { return topic ? unsigned(topic-culture_topics)+1 : 0; }
const CultureTopic* topic_pointer(unsigned id) { return id ? &culture_topics[id-1] : nullptr; }
void culture_browser(Frame&,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        state.data[0]=static_cast<u32>(scope);
        state.data[1]=active_view;
        state.data[2]=topic_id(culture_topic);
        state.data[3]=culture_browser_chinese;
        scope=Scope::encyclopedia;
        active_view=0;
        culture_browser_chinese=chinese;
        state.target=0x51a70;
    } else {
        culture_browser_chinese=state.data[3];
        culture_topic=topic_pointer(state.data[2]);
        active_view=state.data[1];
        scope=static_cast<Scope>(state.data[0]);
    }
}
void culture_show_topic(Frame& frame,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        scope=frame.resume-host->image_base-5==0x51967 ? Scope::encyclopedia_intro : Scope::encyclopedia;
        culture_topic=find_culture_topic(reinterpret_cast<const char*>(frame.rdi));
        state.target=0x511d0;
    }
}
void culture_read_record(Frame& frame) {
    // fgetstr skips comments internally. Its resulting FILE position names
    // the actual source record even when comments preceded it.
    auto* file=reinterpret_cast<FILE*>(frame.rdx);
    frame.rax=call(frame,0xf9680);
    culture_record_offset=std::ftell(file);
}
void culture_body(Frame& frame) {
    const auto previous=culture_line_active;
    // Native source records of 0..2 bytes are paragraph separators (510BA).
    culture_line_active=culture_browser_chinese && culture_topic &&
        std::strlen(reinterpret_cast<const char*>(frame.rdi))>2;
    if(!culture_line_active) frame.rax=call(frame,0x50cd0);
    else {
        const auto encoded=culture_link_source(culture_text("record."+std::to_string(culture_record_offset)));
        // link_show has 200-byte source copies. Split only its borrowed text
        // argument, at encoding/word boundaries; it still owns every wrap and
        // cursor decision. Empty records are explicit paragraph continuations.
        std::string fragment;
        auto submit=[&] {
            Frame arguments=frame;
            arguments.rdi=reinterpret_cast<std::uintptr_t>(fragment.c_str());
            frame.rax=call(arguments,0x50cd0);
            fragment.clear();
        };
        for(auto* p=reinterpret_cast<const unsigned char*>(encoded.c_str());*p;) {
            const auto* start=p;
            if(token(p)) p+=2;
            else if(*p=='<') { while(*p++!='>') {} }
            else if(*p==' ') ++p;
            else { do { ++p; } while(*p && *p!=' ' && *p!='<' && !token(p)); }
            const auto size=std::size_t(p-start);
            if(fragment.size()+size>180) submit();
            fragment.append(reinterpret_cast<const char*>(start),size);
        }
        if(!fragment.empty()) submit();
    }
    culture_line_active=previous;
}
void culture_tokenize(Frame& frame) {
    Frame arguments=frame;
    std::string words;
    if(culture_line_active) {
        for(auto* p=reinterpret_cast<const unsigned char*>(frame.rsi);*p;) {
            if(token(p)) {
                if(!words.empty() && words.back()!=' ') words+=' ';
                words.append(reinterpret_cast<const char*>(p),2);
                words+=' ';
                p+=2;
            } else if(*p==' ') {
                if(!words.empty() && words.back()!=' ') words+=' ';
                ++p;
            } else words.push_back(*p++);
        }
        arguments.rsi=reinterpret_cast<std::uintptr_t>(words.c_str());
    }
    frame.rax=call(arguments,0x1afe00);
}
void culture_word_space(Frame& frame) {
    if(culture_line_active) { frame.rax=0; return; }
    frame.rax=call(frame,frame.resume-host->image_base-5==0x50f5e ? 0x13e8b0 : 0x89a0);
}
void culture_short_record(Frame& frame) {
    // Original 510BA CMP/J A: a two-byte Chinese scalar is text, not a blank.
    const bool text=frame.rbx>2 || (culture_line_active && frame.rbx!=0);
    frame.resume=host->image_base+(text ? 0x50d82 : 0x510c4);
}
void culture_link_match(Frame& frame) {
    if(!culture_line_active) { frame.rax=call(frame,0x85e0); return; }
    const auto name=culture_link_spelling(reinterpret_cast<const char*>(frame.rsi));
    const auto* input=reinterpret_cast<const unsigned char*>(frame.rdi);
    // Lisaa_Linkit's original-case line copy is saved at RSP+38 (5078F).
    // Only complete authored aliases are links: SPEAR is not a second label
    // inside KAUMOLAIS.SPEAR, and a literal Kaumo in a language example stays
    // literal. Both native matching calls receive the same byte offset.
    const auto* original=*reinterpret_cast<const char* const*>(frame.stack()+0x38);
    auto alias_byte=[](unsigned char c) {
        return (c>='A' && c<='Z') || (c>='0' && c<='9') ||
            c=='.' || c=='-' || c=='\'' || c=='/';
    };
    frame.rax=0;
    for(const auto* p=input;*p;) {
        if(token(p)) { p+=2; continue; }
        if(!alias_byte(*p)) { ++p; continue; }
        const auto* start=p;
        do { ++p; } while(alias_byte(*p));
        if(std::size_t(p-start)==name.size() &&
           std::memcmp(original+(start-input),name.data(),name.size())==0) {
            frame.rax=reinterpret_cast<std::uintptr_t>(start);
            return;
        }
    }
}
void culture_link_boundary(Frame& frame) {
    // Both bytes of the display alphabet are >= 0x80. A Chinese scalar
    // borders the original ASCII topic just as a native word separator does.
    if(culture_line_active && static_cast<unsigned char>(frame.rsi)>=0x80) frame.rax=frame.rdi;
    else frame.rax=call(frame,0x86e0);
}
void culture_upper(Frame& frame) {
    frame.rax=call(frame,0xf9140);
    if(!culture_line_active) return;
    const auto* input=reinterpret_cast<const unsigned char*>(frame.rdi);
    auto* output=reinterpret_cast<unsigned char*>(frame.rax);
    for(std::size_t offset=0;input[offset];) {
        if(token(input+offset)) {
            output[offset]=input[offset]; output[offset+1]=input[offset+1]; offset+=2;
        } else ++offset;
    }
}
void culture_link_width(Frame& frame) {
    const auto* input=reinterpret_cast<const char*>(frame.rdi);
    frame.rax=width(culture_line_active ? culture_display_words(input).c_str() : input);
}
void culture_link_draw(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    if(culture_line_active) {
        encoded=culture_display_words(reinterpret_cast<const char*>(frame.rdx));
        arguments.rdx=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x13e8b0);
}
void culture_heading(Frame& frame) {
    const auto site=frame.resume-host->image_base-5;
    Frame arguments=frame;
    std::string encoded;
    if(culture_browser_chinese) {
        if(site==0x513f5 && culture_topic) encoded=culture_text(std::string("topic.")+culture_topic->key+".title");
        if(site==0x51b16) encoded=culture_text("ui.title");
        if(site==0x51910) encoded=culture_text("ui.keyword_title");
        if(!encoded.empty()) argument(arguments,site==0x513f5 ? 4 : 3)=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=site==0x513f5 ? call(arguments,0x1471a0,7,frame) : call(arguments,0x146ed0);
}
void culture_navigation(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    if(culture_browser_chinese) {
        const auto site=frame.resume-host->image_base-5;
        const auto* original=reinterpret_cast<const char*>(frame.rcx);
        const auto prefix=std::strchr(original+1,'.')-original+1;
        const auto* key=site==0x515d3 ? "ui.home" : site==0x5160c ? "ui.exit" :
            site==0x51627 ? "ui.keyword" : "ui.back";
        encoded=std::string(original,prefix)+culture_text(key);
        if(site==0x5170a) {
            const auto* target=at<char>(0x330f60); // Original link[28], never rewritten.
            const auto* topic=find_culture_topic(target);
            const auto label=topic ? culture_text(std::string("topic.")+topic->key+".title") : std::string(target);
            encoded.replace(encoded.find("{value}"),7,label);
        }
        arguments.rcx=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0xf4f50);
}
void culture_help(Frame&,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        culture_help_record=0;
        culture_help_active=culture_browser_chinese;
        state.target=0x1b0130;
    } else culture_help_active=false;
}
void culture_help_append(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    if(culture_help_active) {
        encoded=culture_text("ui.help_"+std::to_string(++culture_help_record));
        arguments.rsi=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x1afe00);
}
void culture_intro_append(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    if(culture_browser_chinese) {
        const auto site=frame.resume-host->image_base-5;
        encoded=culture_text("ui.intro_"+std::to_string(site));
        arguments.rsi=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x1afe00);
}
void culture_notice_text(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    const auto site=frame.resume-host->image_base-5;
    if(culture_browser_chinese) {
        encoded=culture_text(site==0x511a9 ? "ui.no_info" : "ui.continue");
        arguments.rdx=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,site==0x511a9 ? 0x13e8b0 : 0x144fb0);
}
void culture_notice(Frame& frame,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        state.data[0]=static_cast<u32>(scope);
        scope=Scope::encyclopedia_notice;
        state.target=0x51160;
    } else {
        scope=static_cast<Scope>(state.data[0]);
        if(culture_browser_chinese!=chinese) {
            culture_browser_chinese=chinese;
            // 518BB reconstructs the current topic after an unsuccessful
            // keyword search; 51C48 instead leaves the browser altogether.
            if(frame.resume-host->image_base-5==0x518af) {
                culture_redrawing=true;
                uwcn_linux_redraw_main_fragment(host->image_base+0x51ac4);
                culture_redrawing=false;
            }
        }
    }
}
void culture_preview_scope(Frame& frame,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        culture_preview=find_culture_topic(reinterpret_cast<const char*>(frame.rdi));
        state.target=0x4fe10;
    } else culture_preview=nullptr;
}
void culture_preview_text(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    if(chinese && culture_preview) {
        const auto site=frame.resume-host->image_base-5;
        encoded=culture_text(std::string("topic.")+culture_preview->key+(site==0x4fefe ? ".title" : ".summary"));
        arguments.rdx=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x13e8b0);
}
void culture_preview_button(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    if(chinese && culture_preview) {
        const auto* original=reinterpret_cast<const char*>(frame.rcx);
        const auto prefix=std::strchr(original+1,'.')-original+1;
        encoded=std::string(original,prefix)+culture_text("ui.launch");
        arguments.rcx=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0xf4f50);
}
void refresh_culture_words() {
    culture_words.clear();
    struct Link { const char* name; const char* key; };
    const Link links[]{
#include "encyclopedia_links.inc"
    };
    for(const auto& link:links) {
        const auto label=culture_text(std::string("link.")+link.key);
        culture_words.emplace(link.name,label);
        culture_words.emplace(culture_link_spelling(link.name),label);
    }
}
void culture_history(Frame& frame) {
    if(!culture_redrawing) frame.rax=call(frame,0x4fb90);
}
void culture_background_end(Frame& frame) {
    if(culture_redrawing) frame.resume=reinterpret_cast<std::uintptr_t>(uwcn_linux_redraw_main_return);
    else frame.rax=host->image_base+0x331100; // Covered native LEA RAX.
}
void culture_select(Frame& frame,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        state.target=0xf8630;
        state.data[0]=culture_redrawing;
        state.skip=culture_redrawing;
    } else if(state.data[0]) {
        frame.r8=0;
        frame.resume=host->image_base+0x5167b; // Native stack epilogue, no input action.
    }
}
void culture_cruise_select(Frame& frame,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        state.target=0x51580;
        state.data[0]=culture_redrawing;
    } else if(state.data[0]) frame.resume=host->image_base+0x51878;
}
void culture_present(Frame& frame) {
    if(!culture_redrawing) frame.rax=call(frame,0x13fe50);
}
void redraw_culture() {
    const auto position=*at<int>(0x663f010);
    const auto action=*at<int>(0x663f120+position*0xe8+0xc8);
    const std::string selection=action ? "" : at<char>(0x331100+(position+2)*200);
    const std::string topic=scope==Scope::encyclopedia_intro ? "FIRST TIMER INFO" : at<char>(0x32f6e0);
    culture_browser_chinese=chinese;
    culture_redrawing=true;
    // Reuse native background and header arguments, without music/history setup.
    uwcn_linux_redraw_main_fragment(host->image_base+0x51ac4);
    native<int (*)(const char*)>(0x51720)(topic.c_str());
    culture_redrawing=false;
    // Match the original action/topic, not its old screen position.
    for(int row=0;row<*at<int>(0x663ef94);++row) {
        const auto key=*at<int>(0x663f120+row*0xe8+0xc8);
        if(key==action && (action || selection==at<char>(0x331100+(row+2)*200))) {
            native<void (*)(int)>(0xf6110)(row);
            break;
        }
    }
    native<void (*)()>(0x13d5a0)();
    native<void (*)(int,int)>(0xf3f80)(*at<int>(0x663f010),0);
    native<void (*)()>(0x13fe50)();
}
void culture_keyword(Frame&,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        state.data[0]=static_cast<u32>(scope);
        scope=Scope::encyclopedia_keyword;
        state.target=0x1402b0;
    } else {
        scope=static_cast<Scope>(state.data[0]);
        if(culture_browser_chinese!=chinese) redraw_culture();
    }
}
void culture_list_key(Frame& frame,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        state.target=0xf8570;
        state.data[0]=chinese;
    } else if((scope==Scope::encyclopedia || scope==Scope::encyclopedia_intro) && state.data[0]!=chinese) {
        // LIST_Go's original selection local at F8665 is an index into the
        // rebuilt native entries; update it after the real getkey returns.
        *reinterpret_cast<int*>(frame.stack()+8)=*at<int>(0x663f010);
    }
}
void install_culture_info() {
    refresh_culture_words();
    for(auto site:{0x106005u,0x106dadu,0x106efdu}) hooks->around(site,culture_browser,false);
    for(auto site:{0x5176du,0x51858u,0x51868u,0x518bbu,0x518c8u,0x51967u}) hooks->around(site,culture_show_topic,false);
    for(auto site:{0x51467u,0x514fbu,0x5154eu}) hooks->instruction(site,5,culture_read_record);
    hooks->instruction(0x514c8,5,culture_body);
    hooks->instruction(0x50d92,5,culture_tokenize);
    hooks->instruction(0x510ba,10,culture_short_record);
    for(auto site:{0x50f5eu,0x50f72u}) hooks->instruction(site,5,culture_word_space);
    for(auto site:{0x50805u,0x509b6u}) hooks->instruction(site,5,culture_link_match);
    for(auto site:{0x50963u,0x50988u,0x50a49u}) hooks->instruction(site,5,culture_link_boundary);
    hooks->instruction(0x513cd,5,culture_history);
    hooks->instruction(0x51b36,7,culture_background_end);
    hooks->around(0x5162c,culture_select,false);
    hooks->around(0x5180d,culture_cruise_select,false);
    hooks->instruction(0x51808,5,culture_present);
    hooks->around(0x5193f,culture_keyword,false);
    hooks->around(0xf871a,culture_list_key,false);
    for(auto site:{0x50d3cu,0x507a6u}) hooks->instruction(site,5,culture_upper);
    for(auto site:{0x50e1du,0x50eb5u,0x509eeu,0x509fdu,0x50a19u,0x50a28u,0x50a92u,0x50b15u,0x50b7bu})
        hooks->instruction(site,5,culture_link_width);
    for(auto site:{0x50ee5u,0x50c39u}) hooks->instruction(site,5,culture_link_draw);
    for(auto site:{0x513f5u,0x51b16u,0x51910u}) hooks->instruction(site,5,culture_heading);
    for(auto site:{0x515d3u,0x5160cu,0x51627u,0x5170au}) hooks->instruction(site,5,culture_navigation);
    hooks->around(0x517c3,culture_help,false);
    hooks->instruction(0x1b021d,5,culture_help_append);
    for(auto site:{0x51978u,0x51986u,0x51994u,0x519a2u,0x519b0u,0x519beu,0x519ccu,0x519dau,0x519e8u,0x519f6u})
        hooks->instruction(site,5,culture_intro_append);
    for(auto site:{0x511a9u,0x511bfu}) hooks->instruction(site,5,culture_notice_text);
    for(auto site:{0x518afu,0x51c48u}) hooks->around(site,culture_notice,false);
    hooks->around(0x1c03c,culture_preview_scope,false);
    for(auto site:{0x4fefeu,0x4fffbu}) hooks->instruction(site,5,culture_preview_text);
    hooks->instruction(0x500d6,5,culture_preview_button);
}
