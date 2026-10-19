// Windows GAME.NFO consumers. Source records identify semantic asset data;
// native link_show/Lisaa_Linkit retain flow, links, selection and UI storage.
struct WindowsEncyclopediaTopic { const char* name;const char* key;bool language_terms=false; };
const WindowsEncyclopediaTopic windows_encyclopedia_topics[]{
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
#include "../../src/linux/encyclopedia_topics.inc"
};
enum WindowsEncyclopediaHook : u32 {
    we_source_first=0x7900,we_body=0x7903,we_tokenize,we_upper_first,
    we_upper_second,we_short,we_word_fit,we_pair_fit,we_word_text,we_space_text,we_space_copy,
    we_link_first=0x7920,we_link_second,we_link_third,we_boundary_first,we_boundary_second,
    we_measure_pair,we_prefix_width,we_label_width,we_underline,we_link_text,
    we_topic_title=0x7940,we_browser_title,we_notice,we_notice_button,we_initial_notice,we_initial_button,
    we_navigation_first=0x7950,we_intro_first=0x7960,we_intro_title=0x796A,
    we_intro_paragraph,we_help_scope,we_help_append,we_help_paragraph,
    we_preview_scope_first=0x7980,we_preview_title=0x7990,we_preview_summary,
    we_preview_button,we_texture_preview_scope,we_texture_preview_title,
    we_texture_preview_summary,we_texture_preview_button,
    we_map_software_title=0x79A0,we_map_renderer_title,
    we_map_software_first=0x79B0,we_map_renderer_first=0x79C0,
    we_select_wait=0x79D4
};
constexpr u32 we_flow_begin=0x57F1;
const WindowsEncyclopediaTopic* windows_encyclopedia_topic;
const WindowsEncyclopediaTopic* windows_encyclopedia_preview;
bool windows_encyclopedia_line;
bool windows_encyclopedia_native_consuming;
bool windows_encyclopedia_help;
unsigned windows_encyclopedia_help_record;
std::uint64_t windows_encyclopedia_record;
std::map<std::string,std::string> windows_encyclopedia_words;
struct WindowsUpperSource { u64 token;std::string text; };
std::vector<WindowsUpperSource> windows_encyclopedia_upper;
u32 windows_encyclopedia_link_frame;
struct WindowsFlowScope { bool consuming,line;u32 link_frame; };
std::vector<WindowsFlowScope> windows_encyclopedia_flow_scopes;
std::string windows_link_spelling(std::string text) {
    for(auto& c:text) if(c==' ')c='.';
    return text;
}
bool windows_encyclopedia_scalar(const unsigned char* p) {
    return p[0]>=0x80 && p[0]<=0xBF && p[1]>=0x80;
}
const WindowsEncyclopediaTopic* windows_find_topic(const char* name) {
    using Upper=const char* (__fastcall *)(const char*);
    const auto* upper=reinterpret_cast<Upper>(host->image_base+0xD3DB0)(name);
    for(const auto& topic:windows_encyclopedia_topics)
        if(std::strcmp(upper,topic.name)==0)return &topic;
    return nullptr; // Native keyword lookup also has a no-topic result.
}
Status windows_culture_text(const std::string& key,std::vector<char>& encoded) {
    const TextRequest request{TextComponent::culture_text,"",key.c_str()};
    std::vector<char> utf8;
    auto status=service_text(ModuleId::semantic,text_op::translate,&request,sizeof(request),utf8);
    return status==Status::ok ? codec(layout_op::encode_native,utf8.data(),encoded) : status;
}
Status initialize_windows_encyclopedia() {
    struct Link { const char* name;const char* key; };
    const Link links[]{
#include "../../src/linux/encyclopedia_links.inc"
    };
    windows_encyclopedia_words.clear();
    for(const auto& link:links) {
        std::vector<char> label;
        auto status=windows_culture_text(std::string("link.")+link.key,label);
        if(status!=Status::ok)return status;
        windows_encyclopedia_words.emplace(link.name,label.data());
        windows_encyclopedia_words.emplace(windows_link_spelling(link.name),label.data());
    }
    return Status::ok;
}
std::string windows_culture_display(const char* input) {
    const auto whole=windows_encyclopedia_words.find(input);
    if(whole!=windows_encyclopedia_words.end())return whole->second;
    std::string result;
    auto* p=reinterpret_cast<const unsigned char*>(input);
    while(*p) {
        if(windows_encyclopedia_scalar(p)) { result.append(reinterpret_cast<const char*>(p),2);p+=2;continue; }
        if(*p==' ') { ++p;continue; }
        if(*p<'A'||*p>'Z') { result.push_back(*p++);continue; }
        const auto* start=p;
        while(*p&&!windows_encyclopedia_scalar(p)&&*p!=' '&&*p!='<'&&*p!='>'&&
              *p!=','&&*p!=';'&&*p!=':'&&*p!='['&&*p!=']')++p;
        const std::string word(reinterpret_cast<const char*>(start),p-start);
        const auto found=windows_encyclopedia_words.find(word);
        result+=found==windows_encyclopedia_words.end()?word:found->second;
    }
    return result;
}
std::string windows_encyclopedia_tokens(const char* input) {
    std::string words;
    for(auto* p=reinterpret_cast<const unsigned char*>(input);*p;) {
        if(windows_encyclopedia_scalar(p)) {
            if(!words.empty()&&words.back()!=' '&&words.back()!='>')words+=' ';
            words.append(reinterpret_cast<const char*>(p),2);words+=' ';p+=2;
        }else if(*p==' ') {
            if(!words.empty()&&words.back()!=' '&&words.back()!='>')words+=' ';
            ++p;
        }else words.push_back(*p++);
    }
    return words;
}
Status windows_culture_width(const char* input,std::int32_t& width) {
    if(!windows_encyclopedia_line) {
        render::Metrics measured{};
        const auto status=native_name_input::measure(input,measured);
        width=measured.logical_width;return status;
    }
    // 3DBA1 -> 10E700 advances once per native token. Prefixes and lookahead
    // must add those same rounded advances, rather than round a merged string.
    // Native topic labels (including names containing spaces) remain one unit.
    width=0;
    const auto whole=windows_encyclopedia_words.find(input);
    if(whole!=windows_encyclopedia_words.end()) {
        render::Metrics measured{};
        const auto status=metrics(whole->second.c_str(),measured);
        width=measured.logical_width;return status;
    }
    for(const char* p=input;*p;) {
        if(*p==' ') { ++p;continue; }
        const auto* start=p;
        if(windows_encyclopedia_scalar(reinterpret_cast<const unsigned char*>(p)))p+=2;
        else while(*p&&*p!=' '&&!windows_encyclopedia_scalar(reinterpret_cast<const unsigned char*>(p)))++p;
        const auto display=windows_culture_display(std::string(start,p-start).c_str());
        render::Metrics measured{};
        const auto status=metrics(display.c_str(),measured);
        if(status!=Status::ok)return status;
        width+=measured.logical_width;
    }
    return Status::ok;
}
Status windows_culture_lend(const NativeEvent& e,const std::string& key,u32& destination,Scope scope) {
    std::string original;
    auto status=decode_parser_original(ptr<char>(destination),original);
    if(status!=Status::ok)return status;
    std::vector<char> encoded;
    status=translate(TextComponent::culture_text,original.c_str(),key.c_str(),encoded);
    return status==Status::ok ? lend_text(e,encoded,destination,scope) : status;
}
Status windows_culture_paragraph(const NativeEvent& e,const std::string& key) {
    std::string original;
    auto status=decode_parser_original(ptr<char>(e.frame->edx),original);
    if(status!=Status::ok)return status;
    std::vector<char> encoded;
    status=translate(TextComponent::culture_text,original.c_str(),key.c_str(),encoded);
    if(status!=Status::ok)return status;
    const auto words=native_paragraph_words(encoded.data());
    encoded.assign(words.begin(),words.end());encoded.push_back(0);
    return lend_text(e,encoded,e.frame->edx,Scope::allocation);
}
Status windows_culture_draw(const NativeEvent& e) {
    if(!windows_encyclopedia_native_consuming)return Status::ok;
    std::vector<char> encoded;
    if(windows_encyclopedia_line) {
        const auto text=windows_culture_display(ptr<char>(e.arguments[0]));
        encoded.assign(text.begin(),text.end());encoded.push_back(0);
    } else {
        const auto status=native_name_input::display(ptr<char>(e.arguments[0]),encoded);
        if(status!=Status::ok)return status;
    }
    return lend_text(e,encoded,e.arguments[0],Scope::text);
}
Status windows_encyclopedia_flow_prepare(const native_link_flow_component::Record& record,
    std::vector<std::string>& fragments) {
    std::vector<char> encoded;
    auto status=native_text_resource::resolve_source(record.text,resolve_display_text,encode_component_original,encoded);
    if(status!=Status::ok)return status;
    if(!chinese_enabled||record.text.policy==native_text_resource::TextPolicy::original) {
        fragments.push_back(record.native_original);return Status::ok;
    }
    std::string source;
    for(std::size_t i=0;encoded[i];) {
        if(encoded[i]!='{') { source.push_back(encoded[i++]);continue; }
        const auto end=std::string(encoded.data()).find('}',i+1);
        source+=' ';source+=windows_link_spelling(std::string(encoded.data()+i+1,end-i-1));source+=' ';
        i=end+1;
    }
    std::string fragment;
    auto submit=[&] { fragments.push_back(std::move(fragment));fragment.clear(); };
    for(auto* p=reinterpret_cast<const unsigned char*>(source.c_str());*p;) {
        const auto* start=p;
        if(windows_encyclopedia_scalar(p))p+=2;
        else if(*p=='<') { while(*p++!='>'){} }
        else if(*p==' ')++p;
        else do { ++p; }while(*p&&*p!=' '&&*p!='<'&&!windows_encyclopedia_scalar(p));
        const auto bytes=std::size_t(p-start);
        if(fragment.size()+bytes>180)submit();
        fragment.append(reinterpret_cast<const char*>(start),bytes);
    }
    if(!fragment.empty())submit();
    return Status::ok;
}
void windows_encyclopedia_flow_enter(native_link_flow_component::Handle,
    const native_link_flow_component::Record& record) {
    windows_encyclopedia_flow_scopes.push_back({windows_encyclopedia_native_consuming,
        windows_encyclopedia_line,windows_encyclopedia_link_frame});
    windows_encyclopedia_native_consuming=true;
    windows_encyclopedia_line=chinese_enabled&&record.text.policy==native_text_resource::TextPolicy::semantic;
    windows_encyclopedia_link_frame=0;
    native_component_binding::begin_parser_owner();
}
void windows_encyclopedia_flow_leave(native_link_flow_component::Handle) {
    native_component_binding::end_parser_owner();
    const auto previous=windows_encyclopedia_flow_scopes.back();windows_encyclopedia_flow_scopes.pop_back();
    windows_encyclopedia_native_consuming=previous.consuming;
    windows_encyclopedia_line=previous.line;windows_encyclopedia_link_frame=previous.link_frame;
}
void configure_windows_encyclopedia_flow_services() {
    native_link_flow_component::configure({windows_encyclopedia_flow_prepare,
        windows_encyclopedia_flow_enter,windows_encyclopedia_flow_leave});
}
Status windows_encyclopedia_body(const NativeEvent& e,DispatchResult& result) {
    const auto* original=ptr<char>(e.frame->ecx);
    std::string english;
    auto status=decode_parser_original(original,english);if(status!=Status::ok)return status;
    const auto key="record."+std::to_string(windows_encyclopedia_record);
    // 3D8E7's real short-record grammar is retained as an original resource;
    // translated continuation records may independently have an empty value.
    const auto text=std::strlen(original)<=2 ? native_text_resource::original_text(english.c_str()) :
        native_text_resource::from_request({TextComponent::culture_text,english.c_str(),key.c_str()});
    const auto owner=native_link_flow_component::active();
    const auto record=native_link_flow_component::append(owner,windows_encyclopedia_record,text,original,ptr<char>(e.frame->edx));
    status=native_link_flow_component::consume(owner,record,e.frame->eax);
    if(status!=Status::ok)return status;
    result.skip_original=1;return Status::ok;
}
u32 windows_encyclopedia_match(const NativeEvent& e) {
    const auto* input=ptr<unsigned char>(e.arguments[0]);
    const auto name=windows_link_spelling(ptr<char>(e.arguments[1]));
    const auto* original=ptr<char>(e.frame->ebp-0xAA8);
    auto alias=[](unsigned char c) { return (c>='A'&&c<='Z')||(c>='0'&&c<='9')||
        c=='.'||c=='-'||c=='\''||c=='/'; };
    for(const auto* p=input;*p;) {
        if(windows_encyclopedia_scalar(p)) { p+=2;continue; }
        if(!alias(*p)) { ++p;continue; }
        const auto* start=p;do { ++p; }while(alias(*p));
        if(std::size_t(p-start)==name.size()&&std::memcmp(original+(start-input),name.data(),name.size())==0)
            return address(start);
    }
    return 0;
}
const char* __cdecl windows_encyclopedia_strstr(const char* input,const char* needle) {
    using Find=const char* (__cdecl *)(const char*,const char*);
    if(!windows_encyclopedia_line||address(input)!=windows_encyclopedia_link_frame-0x388)
        return (*at<Find>(0x18C350))(input,needle);
    NativeFrame frame{};frame.ebp=windows_encyclopedia_link_frame;
    u32 args[]{address(input),address(needle)};
    const NativeEvent event{NativePhase::inline_before,0,0,&frame,args,2};
    return ptr<char>(windows_encyclopedia_match(event));
}
struct WindowsCultureMapCall { u32 software,renderer;const char* key; };
constexpr WindowsCultureMapCall windows_culture_map_calls[]{
    {0xE11EE,0xE3AB7,"kaumo"},{0xE120F,0xE3AD4,"kiesse"},
    {0xE1230,0xE3AF1,"reemi"},{0xE1251,0xE3B11,"koivula"},
    {0xE1272,0xE3B2E,"sartola"},{0xE1293,0xE3B4B,"driik"},
    {0xE12B4,0xE3B68,"islanders"},{0xE12D5,0xE3B88,"kuikka_tribe"},
    {0xE12F6,0xE3BA5,"owl_tribe"},{0xE1315,0xE3BC2,"seal_tribe"},
    {0xE1334,0xE3BE2,"njerpez"}
};
Status dispatch_windows_encyclopedia(const NativeEvent& e,DispatchResult& result,bool& handled) {
    handled=true;
    if(e.phase==NativePhase::after) {
        if(e.id>=we_source_first&&e.id<we_source_first+3) {
            // The game uses UCRT FILEs. Its own fgetpos import returns the
            // binary file offset, identical to the shared GAME.NFO identity.
            using Position=int (__cdecl *)(void*,std::int64_t*);
            std::int64_t position{};
            const auto status=(*at<Position>(0x18C4DC))(ptr<void>(e.arguments[0]),&position);
            if(status!=0)return Status::failed;
            windows_encyclopedia_record=static_cast<std::uint64_t>(position);
            return Status::ok;
        }
        if(e.id==we_upper_first||e.id==we_upper_second) {
            const auto source=std::find_if(windows_encyclopedia_upper.begin(),windows_encyclopedia_upper.end(),
                [&](const WindowsUpperSource& value){return value.token==e.token;});
            if(source!=windows_encyclopedia_upper.end()) {
                auto* output=ptr<char>(e.frame->eax);
                for(std::size_t i=0;source->text[i];) {
                    if(windows_encyclopedia_scalar(reinterpret_cast<const unsigned char*>(source->text.c_str()+i))) {
                        output[i]=source->text[i];output[i+1]=source->text[i+1];i+=2;
                    }else ++i;
                }
                windows_encyclopedia_upper.erase(source);
            }
            return Status::ok;
        }
        if(e.id>=we_preview_scope_first&&e.id<we_preview_scope_first+2) {
            windows_encyclopedia_preview=nullptr;return Status::ok;
        }
        if(e.id==we_help_scope) { windows_encyclopedia_help=false;return Status::ok; }
        handled=false;return Status::ok;
    }
    if(e.id>=we_source_first&&e.id<we_source_first+3)return Status::ok;
    if(e.id>=we_preview_scope_first&&e.id<we_preview_scope_first+2) {
        windows_encyclopedia_preview=windows_find_topic(ptr<char>(e.frame->ecx));return Status::ok;
    }
    if(e.id>=we_map_software_first&&e.id<we_map_software_first+std::size(windows_culture_map_calls))
        return windows_culture_lend(e,std::string("topic.")+windows_culture_map_calls[e.id-we_map_software_first].key+".title",
                                   e.arguments[0],Scope::text);
    if(e.id>=we_map_renderer_first&&e.id<we_map_renderer_first+std::size(windows_culture_map_calls))
        return windows_culture_lend(e,std::string("topic.")+windows_culture_map_calls[e.id-we_map_renderer_first].key+".title",
                                   e.arguments[2],Scope::hud_renderer);
    if(e.id>=we_intro_first&&e.id<we_intro_first+10)
        return windows_culture_paragraph(e,"ui.intro_"+std::to_string(334200+(e.id-we_intro_first)*14));
    if(e.id>=we_navigation_first&&e.id<we_navigation_first+4) {
        const char* keys[]{"ui.home","ui.back","ui.exit","ui.keyword"};
        const auto* original=ptr<char>(e.arguments[1]);
        const auto* suffix=std::strchr(original,'.')+1;
        const std::string prefix(original,suffix);
        std::string english;
        auto status=decode_parser_original(suffix,english);if(status!=Status::ok)return status;
        std::vector<char> label;
        if(e.id==we_navigation_first+1) {
            std::string topic;
            status=decode_parser_original(at<char>(0x2D1F20),topic);if(status!=Status::ok)return status;
            status=translate(TextComponent::culture_back,english.c_str(),topic.c_str(),label);
        } else status=translate(TextComponent::culture_text,english.c_str(),keys[e.id-we_navigation_first],label);
        if(status!=Status::ok)return status;
        native_component_binding::note_prefix(e,prefix.c_str());
        label.insert(label.begin(),prefix.begin(),prefix.end());
        return lend_text(e,label,e.arguments[1],Scope::setup_exit,*at<u32>(0x5F54A9C));
    }
    switch(e.id) {
    case we_flow_begin:
        *at<u32>(0x61BBB3C)=60;
        native_link_flow_component::begin({native_root_component::current(),0x3DF74,
            static_cast<u32>(TextComponent::culture_text)},ptr<char>(e.frame->ebp-0x268));
        result.resume_rva=0x3DF7E;
        return Status::ok;
    case we_select_wait: {
        const auto flow=native_link_flow_component::active();
        if(flow&&native_link_flow_component::menu_owner(flow)==native_menu_component::active()) {
            native_link_flow_component::seal(flow);
            native_ui_scene::flow_constructed(flow);
        }
        begin(e,Scope::encyclopedia_input);
        return Status::ok;
    }
    case we_body:return windows_encyclopedia_body(e,result);
    case we_tokenize:
        if(windows_encyclopedia_line) {
            const auto words=windows_encyclopedia_tokens(ptr<char>(e.frame->edx));
            std::vector<char> encoded(words.begin(),words.end());encoded.push_back(0);
            return lend_text(e,encoded,e.frame->edx,Scope::allocation);
        }
        return Status::ok;
    case we_upper_first:case we_upper_second:
        if(windows_encyclopedia_native_consuming) {
            windows_encyclopedia_upper.push_back({e.token,ptr<char>(e.frame->ecx)});
            if(e.id==we_upper_second)windows_encyclopedia_link_frame=e.frame->ebp;
        }
        return Status::ok;
    case we_short:
        e.frame->ecx-=e.frame->edx;
        // Only CF is live across the following native JAE. Preserve its byte
        // length in ECX, while a complete two-byte scalar counts as text.
        e.frame->eflags=(e.frame->eflags&~1u)|
            (e.frame->ecx<3&&!(windows_encyclopedia_line&&e.frame->ecx!=0)?1u:0u);
        result.skip_original=1;
        return Status::ok;
    case we_word_fit:case we_pair_fit:
        if(windows_encyclopedia_native_consuming) {
            std::int32_t measured{};
            const auto status=windows_culture_width(ptr<char>(e.frame->ebp-(e.id==we_word_fit?0x598:0xB90)),measured);
            if(status!=Status::ok)return status;
            if(e.id==we_pair_fit) {
                e.frame->esi=*at<u32>(0xA1C1CB4);
                e.frame->ecx-=e.frame->edx;
            }
            e.frame->eax=(e.id==we_word_fit?e.frame->eax:e.frame->esi)+static_cast<u32>(measured);
            if(e.id==we_word_fit) { e.frame->ecx=address(at<char>(0x19416C));result.skip_original=1; }
            else result.skip_original=1;
        }
        return Status::ok;
    case we_word_text:case we_link_text:return windows_culture_draw(e);
    case we_space_text:
        if(windows_encyclopedia_line) { e.frame->eax=0;result.skip_original=1; }
        else return windows_culture_draw(e);
        return Status::ok;
    case we_space_copy:
        // A transport scalar already carries its complete token boundary.
        // Keep native separators after ASCII tokens, including adjacent links,
        // without expanding every CJK scalar in the native 200-byte prefix.
        if(windows_encyclopedia_line&&windows_encyclopedia_scalar(ptr<unsigned char>(e.frame->ebp-0x598))) {
            e.frame->esi=*at<u32>(0xA225314);result.resume_rva=0x3DC3B;
        }
        return Status::ok;
    case we_link_second:
        if(windows_encyclopedia_line) { e.frame->esi=address(reinterpret_cast<const void*>(windows_encyclopedia_strstr));result.skip_original=1; }
        return Status::ok;
    case we_link_first:case we_link_third:
        if(windows_encyclopedia_line) { e.frame->eax=windows_encyclopedia_match(e);result.skip_original=1; }
        else { using Find=const char* (__cdecl *)(const char*,const char*);
            e.frame->eax=address((*at<Find>(0x18C350))(ptr<char>(e.arguments[0]),ptr<char>(e.arguments[1])));result.skip_original=1; }
        return Status::ok;
    case we_boundary_first:case we_boundary_second: {
        using Find=const char* (__cdecl *)(const char*,int);
        e.frame->eax=windows_encyclopedia_line&&e.arguments[1]>=0x80?e.arguments[0]:
            address((*at<Find>(0x18C348))(ptr<char>(e.arguments[0]),e.arguments[1]));
        result.skip_original=1;return Status::ok;
    }
    case we_measure_pair:
        if(windows_encyclopedia_native_consuming) {
            std::int32_t prefix{},label{};
            auto status=windows_culture_width(ptr<char>(e.frame->ebp-0x194),prefix);
            if(status!=Status::ok)return status;
            status=windows_culture_width(ptr<char>(e.frame->edi),label);
            if(status!=Status::ok)return status;
            e.frame->ecx=*ptr<u32>(e.frame->ebp-0xABC);
            e.frame->eax=e.frame->ecx+prefix+label;result.skip_original=1;
        }
        return Status::ok;
    case we_prefix_width:
        if(windows_encyclopedia_native_consuming) {
            std::int32_t measured{};
            const auto status=windows_culture_width(ptr<char>(e.frame->ebp-0x194),measured);
            if(status!=Status::ok)return status;
            e.frame->eax+=static_cast<u32>(measured);
            e.frame->ecx=e.frame->edi;result.skip_original=1;
        }
        return Status::ok;
    case we_label_width:
        if(windows_encyclopedia_native_consuming) {
            std::int32_t measured{};
            const auto status=windows_culture_width(ptr<char>(e.frame->ebp-0xCC),measured);
            if(status!=Status::ok)return status;
            e.frame->eax=measured+3;result.skip_original=1;
        }
        return Status::ok;
    case we_underline:
        if(windows_encyclopedia_native_consuming) {
            std::int32_t measured{};
            const auto status=windows_culture_width(ptr<char>(e.frame->ebp-0xCC),measured);
            if(status!=Status::ok)return status;
            e.arguments[0]=e.frame->ecx+static_cast<u32>(measured);
        }
        return Status::ok;
    case we_topic_title:
        windows_encyclopedia_topic=windows_find_topic(ptr<char>(e.arguments[2]));
        if(windows_encyclopedia_topic)return windows_culture_lend(e,std::string("topic.")+windows_encyclopedia_topic->key+".title",
                                                               e.arguments[2],Scope::titled_panel);
        return Status::ok;
    case we_browser_title:
        return windows_culture_lend(e,"ui.title",e.arguments[0],Scope::text);
    case we_intro_title:return windows_culture_lend(e,"ui.first_timer_title",e.arguments[2],Scope::profile_panel);
    case we_notice:case we_initial_notice:return windows_culture_lend(e,"ui.no_info",e.arguments[0],Scope::text);
    case we_notice_button:case we_initial_button:return windows_culture_lend(e,"ui.continue",e.arguments[0],Scope::plain_button);
    case we_intro_paragraph:case we_help_paragraph:begin(e,Scope::paragraph,e.arguments[3]);return Status::ok;
    case we_help_scope:windows_encyclopedia_help=true;windows_encyclopedia_help_record=0;return Status::ok;
    case we_help_append:
        if(windows_encyclopedia_help)return windows_culture_paragraph(e,"ui.help_"+std::to_string(++windows_encyclopedia_help_record));
        return Status::ok;
    case we_preview_title:case we_preview_summary:
        if(windows_encyclopedia_preview)return windows_culture_lend(e,std::string("topic.")+windows_encyclopedia_preview->key+
            (e.id==we_preview_title?".title":".summary"),e.arguments[0],Scope::text);
        return Status::ok;
    case we_preview_button:
        if(windows_encyclopedia_preview) {
            const auto* original=ptr<char>(e.arguments[1]);
            const char* suffix=std::strchr(original,'.')+1;
            const std::string prefix(original,suffix);
            std::string english;
            auto status=decode_parser_original(suffix,english);if(status!=Status::ok)return status;
            std::vector<char> label;
            status=translate(TextComponent::culture_text,english.c_str(),"ui.launch",label);
            if(status!=Status::ok)return status;
            native_component_binding::note_prefix(e,prefix.c_str());
            label.insert(label.begin(),prefix.begin(),prefix.end());
            return lend_text(e,label,e.arguments[1],Scope::setup_exit,*at<u32>(0x5F54A9C));
        }
        return Status::ok;
    case we_map_software_title:return windows_culture_lend(e,"map.indicators_title",e.arguments[2],Scope::profile_panel);
    case we_map_renderer_title:return windows_culture_lend(e,"map.title",e.arguments[3],Scope::hud_renderer);
    default:handled=false;return Status::ok;
    }
}
void append_windows_encyclopedia_hooks(std::vector<HookSpec>& hooks) {
    auto flow=inline_hook(we_flow_begin,0x3DF74,{0xC7,0x05,0,0,0,0,0x3C,0,0,0});
    const auto cursor=address(at<u32>(0x61BBB3C));std::memcpy(flow.expected+2,&cursor,sizeof(cursor));hooks.push_back(flow);
    hooks.push_back(call(we_select_wait,0x3E1DE,0xD1120,0));
    const u32 reads[]{0x3DF9C,0x3DFBE,0x3E021};
    for(u32 i=0;i<3;++i)hooks.push_back(call(we_source_first+i,reads[i],0xD4280,1));
    hooks.push_back(call(we_body,0x3E054,0x3D820,0));
    hooks.push_back(call(we_tokenize,0x3D93A,0x162300,0));
    hooks.push_back(call(we_upper_first,0x3D87B,0xD3DB0,0));
    hooks.push_back(call(we_upper_second,0x3D353,0xD3DB0,0));
    hooks.push_back(inline_hook(we_short,0x3D8E7,{0x2B,0xCA,0x83,0xF9,0x03}));
    auto word=inline_hook(we_word_fit,0x3D9BC,{0x8D,0x04,0xC8,0xB9,0,0,0,0});
    const auto br=address(at<char>(0x19416C));std::memcpy(word.expected+4,&br,4);hooks.push_back(word);
    auto pair=inline_hook(we_pair_fit,0x3DAC7,{0x8B,0x35,0,0,0,0,0x2B,0xCA,0x8D,0x04,0xCE});
    const auto position=address(at<void>(0xA1C1CB4));std::memcpy(pair.expected+2,&position,4);hooks.push_back(pair);
    hooks.push_back(call(we_word_text,0x3DBA1,0x10E5A0,3));
    hooks.push_back(call(we_space_text,0x3DC13,0x10E5A0,3));
    auto space=inline_hook(we_space_copy,0x3DC2C,{0x66,0xA1,0,0,0,0});
    const auto blank=address(at<char>(0x18C8C0));std::memcpy(space.expected+2,&blank,4);hooks.push_back(space);
    const u32 matchsites[]{0x3D39A,0x3D470,0x3D52A};
    for(u32 i=0;i<3;++i) {
        const bool register_call=i==1;
        auto hook=inline_hook(we_link_first+i,matchsites[i],register_call?
            std::initializer_list<unsigned char>{0x8B,0x35,0,0,0,0}:
            std::initializer_list<unsigned char>{0xFF,0x15,0,0,0,0});
        const auto entry=address(at<void>(0x18C350));std::memcpy(hook.expected+2,&entry,4);hooks.push_back(hook);
    }
    for(u32 i=0;i<2;++i) {
        auto hook=inline_hook(we_boundary_first+i,i?0x3D4EB:0x3D4BD,{0xFF,0x15,0,0,0,0});
        const auto entry=address(at<void>(0x18C348));std::memcpy(hook.expected+2,&entry,4);hooks.push_back(hook);
    }
    hooks.push_back(inline_hook(we_measure_pair,0x3D591,{0x8B,0x8D,0x44,0xF5,0xFF,0xFF,0x8D,0x04,0xC1}));
    hooks.push_back(inline_hook(we_prefix_width,0x3D5FB,{0x8D,0x04,0xC8,0x8B,0xCF}));
    hooks.push_back(inline_hook(we_label_width,0x3D6AE,{0x8D,0x04,0xF5,0x03,0,0,0}));
    hooks.push_back(call(we_underline,0x3D728,0x114340,3));
    hooks.push_back(call(we_link_text,0x3D78D,0x10E5A0,3));
    hooks.push_back(call(we_topic_title,0x3DF31,0x116270,5));
    hooks.push_back(call(we_browser_title,0x3E75A,0x10E5A0,3));
    hooks.push_back(call(we_notice,0x3DCE9,0x10E5A0,3));
    hooks.push_back(call(we_notice_button,0x3DCFE,0x114680,1));
    hooks.push_back(call(we_initial_notice,0x3E8AF,0x10E5A0,3));
    hooks.push_back(call(we_initial_button,0x3E8C4,0x114680,1));
    const u32 nav[]{0x3E148,0x3E1A3,0x3E1BF,0x3E1D6};
    for(u32 i=0;i<4;++i)hooks.push_back(call(we_navigation_first+i,nav[i],0xCFAF0,2));
    const u32 intro[]{0x3E317,0x3E323,0x3E32F,0x3E33B,0x3E347,0x3E353,0x3E35F,0x3E36B,0x3E377,0x3E383};
    for(u32 i=0;i<10;++i)hooks.push_back(call(we_intro_first+i,intro[i],0x162300,0));
    hooks.push_back(call(we_intro_title,0x3E3A5,0x116270,5));
    hooks.push_back(call(we_intro_paragraph,0x3E3DD,0x10EB40,4));
    hooks.push_back(call(we_help_scope,0x3E441,0x162530,0));
    hooks.push_back(call(we_help_append,0x162627,0x162300,0));
    hooks.push_back(call(we_help_paragraph,0x3E476,0x10EB40,4));
    const u32 preview[]{0xF7BA,0xE0ECA};
    for(u32 i=0;i<2;++i)hooks.push_back(call(we_preview_scope_first+i,preview[i],0x3CA90,0));
    hooks.push_back(call(we_preview_title,0x3CBA8,0x10E5A0,3));
    hooks.push_back(call(we_preview_summary,0x3CC8A,0x10E5A0,3));
    hooks.push_back(call(we_preview_button,0x3CCF3,0xCFAF0,2));
    hooks.push_back(call(we_map_software_title,0xE11CD,0x116270,5));
    hooks.push_back(call(we_map_renderer_title,0xE3A9A,0x1166C0,6));
    for(u32 i=0;i<std::size(windows_culture_map_calls);++i) {
        hooks.push_back(call(we_map_software_first+i,windows_culture_map_calls[i].software,0x10E5A0,3));
        hooks.push_back(call(we_map_renderer_first+i,windows_culture_map_calls[i].renderer,0x10E260,4));
    }
}

// Adapter handoff state contains only ordinary semantic/input scope state and
// token-owned call arguments. Topic pointers are static-table identities;
// neither module addresses nor a translated page or layout is serialized.
struct WindowsEncyclopediaStateWriter {
    std::vector<std::uint8_t> bytes;
    template<class T> void value(T scalar) {
        const auto* first=reinterpret_cast<const std::uint8_t*>(&scalar);
        bytes.insert(bytes.end(),first,first+sizeof(scalar));
    }
    void string(const std::string& text) {
        value(static_cast<u32>(text.size()));bytes.insert(bytes.end(),text.begin(),text.end());
    }
};
struct WindowsEncyclopediaStateReader {
    const std::uint8_t* cursor;
    template<class T> T value() {
        T scalar;std::memcpy(&scalar,cursor,sizeof(scalar));cursor+=sizeof(scalar);return scalar;
    }
    std::string string() {
        const auto size=value<u32>();std::string text(reinterpret_cast<const char*>(cursor),size);cursor+=size;return text;
    }
};
std::vector<std::uint8_t> save_windows_encyclopedia_state() {
    WindowsEncyclopediaStateWriter output;
    output.value(windows_encyclopedia_topic ? static_cast<u32>(windows_encyclopedia_topic-windows_encyclopedia_topics) :
        static_cast<u32>(std::size(windows_encyclopedia_topics)));
    output.value(windows_encyclopedia_preview ? static_cast<u32>(windows_encyclopedia_preview-windows_encyclopedia_topics) :
        static_cast<u32>(std::size(windows_encyclopedia_topics)));
    output.value(windows_encyclopedia_line?1u:0u);output.value(windows_encyclopedia_native_consuming?1u:0u);
    output.value(windows_encyclopedia_help?1u:0u);output.value(windows_encyclopedia_help_record);
    output.value(windows_encyclopedia_record);output.value(windows_encyclopedia_link_frame);
    output.value(static_cast<u32>(windows_encyclopedia_upper.size()));
    output.value(static_cast<u32>(windows_encyclopedia_flow_scopes.size()));
    for(const auto& source:windows_encyclopedia_upper) { output.value(source.token);output.string(source.text); }
    for(const auto& scope:windows_encyclopedia_flow_scopes) {
        output.value(scope.consuming?1u:0u);output.value(scope.line?1u:0u);output.value(scope.link_frame);
    }
    return std::move(output.bytes);
}
void restore_windows_encyclopedia_state(const void* payload) {
    WindowsEncyclopediaStateReader input{static_cast<const std::uint8_t*>(payload)};
    const auto topic=input.value<u32>(),preview=input.value<u32>();
    windows_encyclopedia_topic=topic==std::size(windows_encyclopedia_topics) ? nullptr : &windows_encyclopedia_topics[topic];
    windows_encyclopedia_preview=preview==std::size(windows_encyclopedia_topics) ? nullptr : &windows_encyclopedia_topics[preview];
    windows_encyclopedia_line=input.value<u32>()!=0;windows_encyclopedia_native_consuming=input.value<u32>()!=0;
    windows_encyclopedia_help=input.value<u32>()!=0;windows_encyclopedia_help_record=input.value<unsigned>();
    windows_encyclopedia_record=input.value<std::uint64_t>();windows_encyclopedia_link_frame=input.value<u32>();
    const auto upper_count=input.value<u32>(),scope_count=input.value<u32>();
    windows_encyclopedia_upper.clear();windows_encyclopedia_flow_scopes.clear();
    for(u32 index=0;index<upper_count;++index) {
        const auto token=input.value<u64>();auto text=input.string();windows_encyclopedia_upper.push_back({token,std::move(text)});
    }
    for(u32 index=0;index<scope_count;++index) {
        const bool consuming=input.value<u32>()!=0,line=input.value<u32>()!=0;const auto frame=input.value<u32>();
        windows_encyclopedia_flow_scopes.push_back({consuming,line,frame});
    }
}
