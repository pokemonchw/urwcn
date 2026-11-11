// FE2B0 consumes the original msglog.txt body, after F6510 has expanded
// resources, changed sentence case and removed control markers. These rules
// describe complete native expressions; no actor lookup or UI state is kept.
namespace windows_message_history {
using namespace windows_conversation_sources;
const Form history_forms[]{
    {"What do you want to call {0}?","c",'h',"0","message.history.form"},
    {"ANIMAL COMMANDS: {0}: {1}","cm",'h',"01","message.history.form"},
    {"ANIMAL GROUP COMMANDS: {0}","m",'h',"0","message.history.form"},
    {"{0} {1}.","cs",'h',"01","message.history.form"},
    {"There is {0} here and you take a closer look at this area.","g",'h',"0","message.history.form"},
    {"You don't have anything to {0}.","v",'h',"0","message.history.form"},
    {"the {0}","c",'c',"0","conversation.lexical.npc"},
    {"The {0}","c",'c',"0","message.history.form"},
    {"{0} called {1}","cn",'c',"01","message.history.form"},
    {"{0} the {1}","nc",'c',"01","conversation.lexical.npc"},
    // AD4F0 also emits a bare proper name. The record itself is the source;
    // a renamed/departed animal's old name need not occur in today's actors.
    {"{0}","n",'c',"0","message.history.form"}
};
const Lexeme history_words[]{
#include "windows_message_history_words.inc"
};
const Grammar& history_grammar() {
    static const Grammar value=[] {
        Grammar result(std::begin(history_forms),std::end(history_forms),
            std::begin(history_words),std::end(history_words));
        for(const auto& word:lexemes) {
            if(std::strcmp(word.domain,"npc")==0 || std::strcmp(word.domain,"terrain")==0)
                result.words[word.source].push_back(&word);
        }
        return result;
    }();
    return value;
}
bool parse_history(const std::string& input,char kind,Text& output) {
    if(kind=='n') {output=native_message_source::original(input);return true;}
    const auto& data=history_grammar();
    const auto word=data.words.find(input);
    if(word!=data.words.end()) {
        for(const auto* lexeme:word->second) if(kind==lexeme->kind) {
            output=native_message_source::lookup(TextComponent::message_value,lexeme->key,lexeme->domain);
            return true;
        }
    }
    for(const auto& rule:data.rules) {
        if(rule.kind!=kind) continue;
        std::vector<std::string> operands(rule.slots.size());
        std::vector<Text> values;
        if(!match(rule,input,0,0,operands,values,parse_history)) continue;
        output={};output.kind=native_message_source::Kind::format;output.original=input;
        output.children.push_back(native_message_source::lookup(
            TextComponent::message_value,rule.source,rule.domain));
        for(const auto position:rule.order) {
            const auto index=static_cast<std::size_t>(position-'0');
            output.syntax.push_back("{"+std::to_string(index)+"}");
            output.children.push_back(values[index]);
        }
        return true;
    }
    return false;
}
native_text_resource::TextSource source(const char* original) {
    const auto english=message_source_utf8(original);
    Text text;
    if(windows_combat_declarations::parse(english,text)) return windows_inventory::expression(original,text);
    if(parse_history(english,'h',text)) return windows_inventory::expression(original,text);
    return native_text_resource::from_request({TextComponent::message_value,english.c_str(),"message.history"});
}
}
