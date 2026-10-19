#pragma once
#include "../../sdk/text_services.h"
#include "../../sdk/host_abi.h"
#include <string>
#include <vector>

namespace uwcn::adapter::native_message_source {
enum class Kind:u32 { original,lookup,scalar,format,replace_first,concat,before_separator,without_initial_marker };
enum class Scalar:u32 { signed32,signed_long32,unsigned32,real64,character };
// These are original English input expressions, not translated message text,
// native output words, UI positions, pixels or a display-call history.
struct Text {
    Kind kind=Kind::original;
    TextComponent component=TextComponent::message_literal;
    std::string original,key;
    Scalar scalar=Scalar::signed32;
    u64 bits{};
    std::vector<Text> children;
    std::vector<std::string> syntax;
};
using Lookup=Status (*)(TextComponent,const char*,const char*,std::string&);
Text original(std::string english);
Text lookup(TextComponent,std::string english,std::string key={});
Text scalar(Scalar,u64 bits,std::string conversion);
Text format(Text source,std::vector<Text> values,std::vector<std::string> conversions);
Text replace_first(Text source,std::string token,Text value);
Text concat(std::vector<Text>);
Text before_separator(Text source,char separator);
Text without_initial_marker(Text source);
Status project(const Text&,Lookup,bool chinese,std::string&);
void write(std::vector<unsigned char>&,const Text&);
Text read(const unsigned char*&);
}
