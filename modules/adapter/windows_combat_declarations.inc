// Completed native declaration text, consumed by F6510 and FE2B0. Existing
// records can predate the four declaration-copy source hooks. This grammar
// uses their original text, never current actors, weapons or combat state.
// Evidence: docs/evidence/20261111-combat-narrative-branches.md and
// docs/evidence/20261111-combat-retained-source.md.
namespace windows_combat_declarations {
using namespace windows_conversation_sources;
struct Declaration {Form form;const char* resource;const char* tokens[5];};
// Longer native constructions precede the overlapping unarmed construction.
// Select the complete structure before interpreting its lexical operands:
// a weapon sentence cannot become an unarmed sentence with the weapon tail
// swallowed by the native bare-proper-name production.
const Declaration declarations[]{
    {{"You try {0} {1} with your {2}.","vci",'d',"012","WEAPON_ATTACK_DECLARATION"},
     "You try [ATTACK_VERB:<attack_aspect>] <defender_defdesc> with your <attack_weapon>.",
     {"[ATTACK_VERB:<attack_aspect>]","<defender_defdesc>","<attack_weapon>"}},
    {{"{0} tries {1} {2} with {3} {4}.","cvcpi",'d',"01234","WEAPON_ATTACK_DECLARATION"},
     "<attacker_defdesc> tries [ATTACK_VERB:<attack_aspect>] <defender_defdesc> with [PP_GEN:<attacker>] <attack_weapon>.",
     {"<attacker_defdesc>","[ATTACK_VERB:<attack_aspect>]","<defender_defdesc>","[PP_GEN:<attacker>]","<attack_weapon>"}},
    {{"You aim your {0} at {1} and shoot.","ic",'d',"01","BOW_ATTACK_DECLARATION"},
     "You aim your <attack_bow> at <defender_defdesc> and shoot.",
     {"<attack_bow>","<defender_defdesc>"}},
    {{"{0} aims {1} {2} at {3} and shoots.","cpic",'d',"0123","BOW_ATTACK_DECLARATION"},
     "<attacker_desc> aims [PP_GEN:<attacker>] <attack_bow> at <defender_defdesc> and shoots.",
     {"<attacker_desc>","[PP_GEN:<attacker>]","<attack_bow>","<defender_defdesc>"}},
    {{"You try to throw your {0} at {1}.","ic",'d',"01","THROW_ATTACK_DECLARATION"},
     "You try to throw your <attack_weapon> at <defender_defdesc>.",
     {"<attack_weapon>","<defender_defdesc>"}},
    {{"{0} tries to throw {1} {2} at {3}.","cpic",'d',"0123","THROW_ATTACK_DECLARATION"},
     "<attacker_desc> tries to throw [PP_GEN:<attacker>] <attack_weapon> at <defender_defdesc>.",
     {"<attacker_desc>","[PP_GEN:<attacker>]","<attack_weapon>","<defender_defdesc>"}},
    {{"You hear sounds of fighting in the {0}.","d",'d',"0","WEAPON_ATTACK_DECLARATION"},
     "You hear sounds of fighting in the [IN_DIR:<npc_direction>].",
     {"[IN_DIR:<npc_direction>]"}},
    {{"You try {0} {1}.","vc",'d',"01","UNARMED_ATTACK_DECLARATION"},
     "You try [ATTACK_VERB:<attack_aspect>] <defender_defdesc>.",
     {"[ATTACK_VERB:<attack_aspect>]","<defender_defdesc>"}},
    // The native ANIMAL and * branches have identical source and translation.
    {{"{0} tries {1} {2}.","cvc",'d',"012","UNARMED_ATTACK_DECLARATION"},
     "<attacker_defdesc> tries [ATTACK_VERB:<attack_aspect>] <defender_defdesc>.",
     {"<attacker_defdesc>","[ATTACK_VERB:<attack_aspect>]","<defender_defdesc>"}}
};
struct Word {const char* source;const char* resource;char kind;};
const Word words[]{
#include "windows_combat_declaration_words.inc"
};
bool word(const std::string& input,char kind,Text& output) {
    for(const auto& value:words) if(value.kind==kind && input==value.source) {
        output=message_source_template(value.resource,value.source);return true;
    }
    return false;
}
// Independent recursive domain for recorded item text. The shared ordinary
// conversation parser's actor-name lookup is not part of this consumer.
bool lexical(const std::string& input,char kind,Text& output) {
    if(kind=='c') {
        if(input=="you" || input=="You") {output=message_source_lookup("npc","you");return true;}
        return windows_message_history::parse_history(input,'c',output);
    }
    if(kind=='n') {output=native_message_source::original(input);return true;}
    if(kind=='v') return windows_conversation_sources::domain(input,'v',output);
    const auto& data=grammar();
    const auto literal=data.literals.find(input);
    if(literal!=data.literals.end()) for(const auto* form:literal->second) if(form->kind==kind) {
        output=message_source_lookup(form->domain,input.c_str());return true;
    }
    const auto atom=data.words.find(input);
    if(atom!=data.words.end()) for(const auto* value:atom->second) if(value->kind==kind) {
        output=message_source_lookup(value->domain,value->key);return true;
    }
    for(const auto& rule:data.rules) {
        if(rule.kind!=kind) continue;
        std::vector<std::string> operands(rule.slots.size());std::vector<Text> values;
        if(!match(rule,input,0,0,operands,values,lexical)) continue;
        output={};output.kind=native_message_source::Kind::format;output.original=input;
        output.children.push_back(message_source_lookup(rule.domain.c_str(),rule.source.c_str()));
        for(const auto position:rule.order) {
            const auto index=static_cast<std::size_t>(position-'0');
            output.syntax.push_back("{"+std::to_string(index)+"}");
            output.children.push_back(values[index]);
        }
        return true;
    }
    return false;
}
bool operand(const std::string& input,char kind,Text& output) {
    return kind=='v' || kind=='p' || kind=='d' ? word(input,kind,output) : lexical(input,kind,output);
}
bool structure(const std::string& input,char kind,Text& output) {
    if(kind=='v' || kind=='p' || kind=='d') return word(input,kind,output);
    output=native_message_source::original(input);return true;
}
const std::vector<Rule>& rules() {
    static const auto value=[] {
        std::vector<Rule> result;
        const std::array<Lexeme,0> empty{};
        for(const auto& declaration:declarations) {
            const Grammar single(&declaration.form,&declaration.form+1,empty.data(),empty.data());
            result.push_back(single.rules.front());
        }
        return result;
    }();
    return value;
}
bool parse(const std::string& input,MessageText& output) {
    const auto& patterns=rules();
    for(std::size_t index=0;index<patterns.size();++index) {
        const auto& rule=patterns[index];
        std::vector<std::string> operands(rule.slots.size());std::vector<Text> values;
        if(!match(rule,input,0,0,operands,values,structure)) continue;
        // The matched complete display structure owns these operands.
        // Do not reclassify it as the shorter unarmed production.
        if(!match(rule,input,0,0,operands,values,operand)) return false;
        const auto& declaration=declarations[index];
        output=message_source_template(declaration.form.domain,declaration.resource);
        for(std::size_t slot=0;slot<values.size();++slot)
            output=native_message_source::replace_first(std::move(output),declaration.tokens[slot],std::move(values[slot]));
        output.original=input;return true;
    }
    return false;
}
bool literal_expression(const MessageText& input,MessageText& output) {
    return input.kind==native_message_source::Kind::lookup &&
        input.component==TextComponent::message_literal && input.key.empty() && parse(input.original,output);
}
}
