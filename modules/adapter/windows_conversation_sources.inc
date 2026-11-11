// Complete native conversation inputs, reconstructed from their statically
// extracted text grammar. This contains no page, position or drawing state.
namespace windows_conversation_sources {
using Text=native_message_source::Text;
struct Form {const char* source;const char* slots;char kind;const char* order;const char* domain;};
struct Lexeme {const char* source;const char* domain;const char* key;char kind;};
const Form forms[]{
#include "windows_conversation_forms.inc"
};
const Lexeme lexemes[]{
#include "windows_conversation_lexemes.inc"
};
const char* append_pieces[]{
#include "windows_conversation_appends.inc"
};
struct Rule {
    std::string source,slots;char kind;std::string order,domain;
    std::vector<std::string> literals;
};
struct Grammar {
    std::map<std::string,std::vector<const Form*>> literals;
    std::map<std::string,std::vector<const Lexeme*>> words;
    std::vector<Rule> rules;
    Grammar() {
        for(const auto& lexeme:lexemes) words[lexeme.source].push_back(&lexeme);
        for(const auto& form:forms) {
            if(!*form.slots) {literals[form.source].push_back(&form);continue;}
            Rule rule{form.source,form.slots,form.kind,form.order,form.domain,{}};
            std::size_t start=0;
            for(std::size_t slot=0;slot<rule.slots.size();++slot) {
                const auto marker="{"+std::to_string(slot)+"}";
                const auto next=rule.source.find(marker,start);
                rule.literals.push_back(rule.source.substr(start,next-start));
                start=next+marker.size();
            }
            rule.literals.push_back(rule.source.substr(start));
            rules.push_back(std::move(rule));
        }
        // The original complete sentence rules precede their shorter native
        // lexical constructions. Matching never replaces words in a sentence.
        std::stable_sort(rules.begin(),rules.end(),[](const Rule& left,const Rule& right) {
            return left.source.size()-left.slots.size()*3 > right.source.size()-right.slots.size()*3;
        });
    }
};
const Grammar& grammar() {static const Grammar value;return value;}
bool parse(const std::string&,char,Text&);
bool accepts(char input,char source) {
    if(input=='t') return true;
    if(input=='l') return source=='l' || source=='i' || source=='c';
    if(input=='g') return source=='g' || source=='d' || source=='k';
    return input==source;
}
bool domain(const std::string& input,char kind,Text& output) {
    if(kind=='n') {output=native_message_source::original(input);return true;}
    if(kind=='a') {
        if(input!=message_source_utf8(at<char>(0xA32A6E8))) return false;
        output=native_message_source::original(input);return true;
    }
    if(kind=='v') {
        if(input.empty() || input.find_first_not_of("0123456789.+- ")!=std::string::npos) return false;
        output=native_message_source::original(input);return true;
    }
    return parse(input,kind,output);
}
bool match(const Rule& rule,const std::string& input,std::size_t slot,std::size_t position,
           std::vector<std::string>& operands,std::vector<Text>& values) {
    const auto& literal=rule.literals[slot];
    if(input.compare(position,literal.size(),literal)!=0) return false;
    position+=literal.size();
    if(slot==rule.slots.size()) {
        if(position!=input.size()) return false;
        values.clear();
        for(std::size_t index=0;index<operands.size();++index) {
            Text value;
            if(!domain(operands[index],rule.slots[index],value)) return false;
            values.push_back(std::move(value));
        }
        return true;
    }
    const auto& next=rule.literals[slot+1];
    auto end=next.empty()?position:input.find(next,position);
    while(end!=std::string::npos && end<=input.size()) {
        operands.push_back(input.substr(position,end-position));
        if(match(rule,input,slot+1,end,operands,values)) return true;
        operands.pop_back();
        if(end==input.size()) break;
        end=next.empty()?end+1:input.find(next,end+1);
    }
    return false;
}
bool parse(const std::string& input,char kind,Text& output) {
    if(input.empty()) {output=native_message_source::original("");return true;}
    // plr_identity's native proper-name branch is precisely this game field.
    if(kind=='p' && input==message_source_utf8(at<char>(0xA32A6E8))) {
        output=native_message_source::original(input);return true;
    }
    if(kind=='p' && input==message_source_utf8(at<char>(0xA32A6F6))) {
        const auto component=static_cast<TextComponent>(static_cast<u32>(TextComponent::profile_culture_0)+
            *at<unsigned char>(0xA32A6F5));
        output=native_message_source::lookup(component,input);return true;
    }
    const auto& data=grammar();
    const auto literal=data.literals.find(input);
    if(literal!=data.literals.end()) {
        for(const auto* form:literal->second) if(accepts(kind,form->kind)) {
            output=native_message_source::lookup(TextComponent::message_value,input,form->domain);return true;
        }
    }
    const auto word=data.words.find(input);
    if(word!=data.words.end()) {
        for(const auto* lexeme:word->second) {
            if(!accepts(kind,lexeme->kind)) continue;
            output=native_message_source::lookup(TextComponent::message_value,lexeme->key,lexeme->domain);return true;
        }
    }
    for(const auto& rule:data.rules) {
        if(!accepts(kind,rule.kind)) continue;
        std::vector<std::string> operands;
        std::vector<Text> values;
        if(!match(rule,input,0,0,operands,values)) continue;
        // Original parameter order and Chinese grammatical order are both
        // explicit static metadata. Keep each proper name in its own operand.
        output={};output.kind=native_message_source::Kind::format;output.original=input;
        output.children.push_back(native_message_source::lookup(
            TextComponent::message_value,rule.source,rule.domain));
        for(const auto position:rule.order) {
            const auto index=static_cast<std::size_t>(position-'0');
            output.syntax.push_back("{"+std::to_string(index)+"}");
            output.children.push_back(std::move(values[index]));
        }
        return true;
    }
    if(kind=='t') {
        // These are the exact complete authored fragments concatenated by
        // native dialogue/quest builders, including their original spaces.
        // This is a source grammar operation, never a word substitution pass.
        for(const auto* piece:append_pieces) {
            const std::string atom(piece);
            if(input.size()<=atom.size()) continue;
            Text rest;
            if(input.compare(0,atom.size(),atom)==0 && parse(input.substr(atom.size()),'t',rest)) {
                output=native_message_source::concat({native_message_source::lookup(
                    TextComponent::message_value,atom,"conversation.form"),std::move(rest)});
                return true;
            }
            if(input.compare(input.size()-atom.size(),atom.size(),atom)==0 &&
               parse(input.substr(0,input.size()-atom.size()),'t',rest)) {
                output=native_message_source::concat({std::move(rest),native_message_source::lookup(
                    TextComponent::message_value,atom,"conversation.form")});
                return true;
            }
        }
    }
    return false;
}
Status source(const char* original,Text& output) {
    return parse(message_source_utf8(original),'t',output)?Status::ok:Status::unavailable;
}
Status utf8(const char* original,std::string& output) {
    Text text;
    const auto status=source(original,text);
    return status==Status::ok?message_project_source(text,true,output):status;
}
Status bind_line(native_menu_component::Handle menu,u32 row,const char* label) {
    const auto* suffix=std::strchr(label,'.')+1;
    Text text;const auto status=source(suffix,text);
    if(status!=Status::ok) return status;
    native_menu_model::bind_row(menu,row,windows_inventory::expression(suffix,text),std::string(label,suffix));
    return Status::ok;
}
Status bind_menu(native_menu_component::Handle menu) {
    const auto& records=native_menu_model::paint_records(menu);
    u32 count{};std::memcpy(&count,records.header.data()+0x14,sizeof(count));
    for(u32 row=0;row<count;++row) {
        const auto* label=reinterpret_cast<const char*>(records.rows.data()+row*native_menu_model::row_stride);
        if(!*label) continue; // The actual native empty separator rows.
        const auto status=bind_line(menu,row,label);if(status!=Status::ok) return status;
    }
    return Status::ok;
}
}

Status bind_chat_lines_menu(native_menu_component::Handle menu) {
    return windows_conversation_sources::bind_menu(menu);
}
Status bind_chat_line_record(const NativeEvent& event) {
    const auto row=(event.frame->esi-address(at<void>(0x5F4EF10)))/native_menu_model::row_stride;
    return windows_conversation_sources::bind_line(native_menu_component::source(),row,ptr<const char>(event.frame->esi));
}
Status lend_conversation_sentence(const NativeEvent& event) {
    if(!chinese_enabled || !windows_build::is_3891()) return Status::ok;
    std::string utf8;
    auto status=windows_conversation_sources::utf8(ptr<const char>(event.frame->ecx),utf8);
    if(status!=Status::ok) return status;
    // Only this read-only native word-flow invocation sees the UTF-8 loan.
    // Its accepted English sentence remains with the existing logical owner.
    std::vector<char> display;status=encode_parser_original(utf8.c_str(),display);
    if(status!=Status::ok) return status;
    auto loan=event;loan.token=0xFFFFFFF600000000ull|event.frame->ebp;
    return lend_text(loan,display,event.frame->ecx,Scope::allocation);
}
Status lend_conversation_display(const NativeEvent& event,u32& input,Scope scope,u32 outline=0) {
    windows_conversation_sources::Text text;
    auto status=windows_conversation_sources::source(ptr<const char>(input),text);
    if(status!=Status::ok) return status;
    const auto source=windows_inventory::expression(ptr<const char>(input),text);
    native_component_binding::bind_source(event,source);
    if(!chinese_enabled) return Status::ok;
    std::vector<char> encoded;
    status=native_text_resource::resolve_source(source,resolve_display_text,encode_component_original,encoded);
    return status==Status::ok?lend_text(event,encoded,input,scope,outline):status;
}
