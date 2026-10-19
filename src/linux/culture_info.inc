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
    {"LANGUAGE","language",true},{"LANGUAGE INFLEXIONS","language_inflexions",true}
};
const CultureTopic* culture_topic;
const CultureTopic* culture_preview;
bool culture_browser_chinese;
bool culture_line_active;
bool culture_help_active;
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
    return nullptr; // Other encyclopedia topics retain their own native consumer.
}
bool culture_word_character(unsigned char value) {
    return (value>='A' && value<='Z') || (value>='a' && value<='z') || value=='-' || value>=0x80;
}
std::string culture_display_words(const char* input) {
    std::string result;
    const auto* cursor=reinterpret_cast<const unsigned char*>(input);
    while(*cursor) {
        if(token(cursor)) { result.append(reinterpret_cast<const char*>(cursor),2); cursor+=2; continue; }
        if(!culture_word_character(*cursor)) { result.push_back(*cursor++); continue; }
        const auto* start=cursor;
        std::string key;
        while(*cursor && !token(cursor) && culture_word_character(*cursor)) {
            auto value=*cursor++;
            if(value>='a' && value<='z') value-=32;
            key.push_back(value);
        }
        // The language examples explain these actual spellings and inflections.
        const bool literal=culture_topic && culture_topic->language_terms &&
            (key.starts_with("KAUMO") || key.starts_with("KIESSE") || key.starts_with("DRIIK") ||
             key.starts_with("REEMI") || key.starts_with("SARTOLA") || key.starts_with("KOIVU"));
        const auto found=culture_words.find(key);
        if(!literal && found!=culture_words.end()) result+=found->second;
        else result.append(reinterpret_cast<const char*>(start),cursor-start);
    }
    return result;
}
void culture_browser(Frame& frame) {
    const auto previous_scope=scope;
    const auto previous_view=active_view;
    const auto* previous_topic=culture_topic;
    const auto previous_language=culture_browser_chinese;
    scope=Scope::encyclopedia;
    active_view=0;
    // This browser owns a persistent heading and a sequence of native topic
    // caches. Keep its language until the native browser is opened again.
    culture_browser_chinese=chinese;
    frame.rax=call(frame,0x51a70);
    culture_browser_chinese=previous_language;
    culture_topic=previous_topic;
    active_view=previous_view;
    scope=previous_scope;
}
void culture_show_topic(Frame& frame) {
    culture_topic=find_culture_topic(reinterpret_cast<const char*>(frame.rdi));
    frame.rax=call(frame,0x511d0);
}
void culture_read_record(Frame& frame) {
    // Capture the native file's actual record identity, including its original
    // CRLF offsets. Headers, %POP, image names and lookup buffers stay native.
    culture_record_offset=std::ftell(reinterpret_cast<FILE*>(frame.rdx));
    frame.rax=call(frame,0xf9680);
}
void culture_body(Frame& frame) {
    Frame arguments=frame;
    std::string encoded;
    const auto previous=culture_line_active;
    culture_line_active=culture_browser_chinese && culture_topic;
    if(culture_line_active) {
        encoded=culture_text("record."+std::to_string(culture_record_offset));
        if(culture_topic->language_terms) {
            // These records teach the original inflections. Keep their native
            // CP437 ä so StrUpr and the native topic table still recognize them.
            std::string spelling;
            for(auto* p=reinterpret_cast<const unsigned char*>(encoded.c_str());*p;) {
                if(auto* glyph=token(p)) {
                    if(glyph->utf8=="ä") spelling.push_back(static_cast<char>(0x84));
                    else spelling.append(reinterpret_cast<const char*>(p),2);
                    p+=2;
                } else spelling.push_back(*p++);
            }
            encoded=std::move(spelling);
        }
        arguments.rdi=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,0x50cd0);
    culture_line_active=previous;
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
void culture_help(Frame& frame) {
    culture_help_record=0;
    culture_help_active=culture_browser_chinese;
    frame.rax=call(frame,0x1b0130);
    culture_help_active=false;
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
void culture_preview_scope(Frame& frame) {
    culture_preview=find_culture_topic(reinterpret_cast<const char*>(frame.rdi));
    frame.rax=call(frame,0x4fe10);
    culture_preview=nullptr;
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
void install_culture_info() {
    const char* words[]{
#include "culture_word_keys.inc"
    };
    for(const auto* word:words) culture_words.emplace(word,culture_text(std::string("word.")+word));
    for(auto site:{0x106005u,0x106dadu,0x106efdu}) hooks->instruction(site,5,culture_browser);
    for(auto site:{0x5176du,0x51858u,0x51868u,0x518bbu,0x518c8u,0x51967u}) hooks->instruction(site,5,culture_show_topic);
    for(auto site:{0x51467u,0x514fbu,0x5154eu}) hooks->instruction(site,5,culture_read_record);
    hooks->instruction(0x514c8,5,culture_body);
    for(auto site:{0x50d3cu,0x507a6u}) hooks->instruction(site,5,culture_upper);
    for(auto site:{0x50e1du,0x50eb5u,0x509eeu,0x509fdu,0x50a19u,0x50a28u,0x50a92u,0x50b15u,0x50b7bu})
        hooks->instruction(site,5,culture_link_width);
    for(auto site:{0x50ee5u,0x50c39u}) hooks->instruction(site,5,culture_link_draw);
    for(auto site:{0x513f5u,0x51b16u,0x51910u}) hooks->instruction(site,5,culture_heading);
    for(auto site:{0x515d3u,0x5160cu,0x51627u,0x5170au}) hooks->instruction(site,5,culture_navigation);
    hooks->instruction(0x517c3,5,culture_help);
    hooks->instruction(0x1b021d,5,culture_help_append);
    hooks->instruction(0x1c03c,5,culture_preview_scope);
    for(auto site:{0x4fefeu,0x4fffbu}) hooks->instruction(site,5,culture_preview_text);
    hooks->instruction(0x500d6,5,culture_preview_button);
}
