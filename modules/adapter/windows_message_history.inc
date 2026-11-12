// FE2B0 consumes the original msglog.txt body, after F6510 has expanded
// resources, changed sentence case and removed control markers. These rules
// describe complete native expressions; no actor lookup or UI state is kept.
namespace windows_combat_declarations {
bool lexical(const std::string&,char,native_message_source::Text&);
}
namespace windows_message_history {
using namespace windows_conversation_sources;
const Form history_forms[]{
    {"What do you want to call {0}?","c",'h',"0","message.history.form"},
    {"ANIMAL COMMANDS: {0}: {1}","cm",'h',"01","message.history.form"},
    {"ANIMAL GROUP COMMANDS: {0}","m",'h',"0","message.history.form"},
    {"{0} {1}.","cs",'h',"01","message.history.form"},
    {"There is {0} here and you take a closer look at this area.","g",'h',"0","message.history.form"},
    {"You don't have anything to {0}.","v",'h',"0","message.history.form"},
    // 100846 formats the selected native title and row, then 1008A2
    // removes the pipe annotation before F6510 writes the English body.
    {"{0}: {1}","MO",'h',"01","message.history.form"},
    // 507F42, PICK_UP:PC and CARRY_TOO_HEAVY:PC. Item operands use the
    // same complete recorded-name grammar as retained combat declarations.
    {"You see {0} here.","i",'h',"0","message.history.form"},
    {"You see {0} there.","i",'h',"0","message.history.form"},
    {"You pick up the {0}.","i",'h',"0","message.history.form"},
    {"Nggggh! {0} is too heavy for you to lift.","i",'h',"0","message.history.form"},
    // 464730 constructs the numbered requirement and selected preference.
    {"({0}) You need {1}.","qr",'h',"01","message.history.form"},
    {"({0}) You may optionally use {1}.","qr",'h',"01","message.history.form"},
    {"({0}) You need {1} - preferably {2}.","qri",'h',"012","message.history.form"},
    {"({0}) You need {1} - preferably of {2}.","qri",'h',"012","message.history.form"},
    {"{0} of {1} * {2}","iiq",'r',"012","message.history.form"},
    {"{0} * {1}","iq",'r',"01","message.history.form"},
    {"{0} (of {1})","rq",'r',"01","message.history.form"},
    {"{0}, or {1}","rr",'r',"01","message.history.form"},
    {"{0} or {1}","rr",'r',"01","message.history.form"},
    {"{0} or by hand","r",'r',"0","message.history.form"},
    {"{0}","i",'r',"0","message.history.form"},
    // 494BC0 supplies standalone terrain and snow/crust descriptions.
    {"{0}","g",'h',"0","message.history.form"},
    {"{0} with {1}","SC",'g',"01","message.history.form"},
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
#include "windows_message_history_menu_words.inc"
};
const Grammar& history_grammar() {
    static const Grammar value=[] {
        Grammar result(std::begin(history_forms),std::end(history_forms),
            std::begin(history_words),std::end(history_words));
        for(const auto& word:lexemes) {
            if(std::strcmp(word.domain,"npc")==0 || std::strcmp(word.domain,"terrain")==0 ||
               std::strcmp(word.domain,"geography.snow")==0 || std::strcmp(word.domain,"geography.crust")==0)
                result.words[word.source].push_back(&word);
        }
        return result;
    }();
    return value;
}
bool parse_history(const std::string& input,char kind,Text& output) {
    if(kind=='n') {output=native_message_source::original(input);return true;}
    if(kind=='i') return windows_combat_declarations::lexical(input,kind,output);
    if(kind=='q') {
        // The original requirement index/count conversions emit decimal digits.
        if(input.empty() || input.find_first_not_of("0123456789")!=std::string::npos) return false;
        output=native_message_source::original(input);return true;
    }
    const auto& data=history_grammar();
    const auto word=data.words.find(input);
    if(word!=data.words.end()) {
        for(const auto* lexeme:word->second) if(kind==lexeme->kind ||
            (kind=='S' && std::strcmp(lexeme->domain,"geography.snow")==0) ||
            (kind=='C' && std::strcmp(lexeme->domain,"geography.crust")==0)) {
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
    // 4432AB can use the selected base item rather than a glossary label.
    if(kind=='O') return windows_combat_declarations::lexical(input,'i',output);
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
