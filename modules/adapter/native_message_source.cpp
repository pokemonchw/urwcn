#include "native_message_source.h"
#include <cstdio>
#include <cstring>
#include <utility>

namespace uwcn::adapter::native_message_source {
namespace {
template<class T> std::string number(const std::string& conversion,T value) {
    const auto count=std::snprintf(nullptr,0,conversion.c_str(),value);
    std::vector<char> result(static_cast<std::size_t>(count)+1);
    std::snprintf(result.data(),result.size(),conversion.c_str(),value);
    return {result.data(),static_cast<std::size_t>(count)};
}
std::string number(const Text& source) {
    const auto& conversion=source.syntax.front();
    switch(source.scalar) {
    case Scalar::signed32:return number(conversion,static_cast<std::int32_t>(source.bits));
    case Scalar::signed_long32:return number(conversion,static_cast<long>(source.bits));
    case Scalar::unsigned32:return number(conversion,static_cast<u32>(source.bits));
    case Scalar::character:return number(conversion,static_cast<int>(source.bits));
    case Scalar::real64: { double value;std::memcpy(&value,&source.bits,sizeof(value));return number(conversion,value); }
    }
    return {};
}
void append_literal(std::string& output,const std::string& input,std::size_t begin,std::size_t length) {
    auto text=input.substr(begin,length);
    for(auto position=text.find("%%");position!=std::string::npos;position=text.find("%%",position+1)) text.erase(position,1);
    output+=text;
}
template<class T> void scalar_write(std::vector<unsigned char>& out,T value) {
    const auto* bytes=reinterpret_cast<const unsigned char*>(&value);out.insert(out.end(),bytes,bytes+sizeof(value));
}
template<class T> T scalar_read(const unsigned char*& input) { T value;std::memcpy(&value,input,sizeof(value));input+=sizeof(value);return value; }
void string_write(std::vector<unsigned char>& out,const std::string& text) {
    scalar_write(out,static_cast<u32>(text.size()));out.insert(out.end(),text.begin(),text.end());
}
std::string string_read(const unsigned char*& input) {
    const auto size=scalar_read<u32>(input);std::string text(reinterpret_cast<const char*>(input),size);input+=size;return text;
}
}
Text original(std::string english) { Text text;text.original=std::move(english);return text; }
Text lookup(TextComponent component,std::string english,std::string key) {
    auto text=original(std::move(english));text.kind=Kind::lookup;text.component=component;text.key=std::move(key);return text;
}
Text scalar(Scalar kind,u64 bits,std::string conversion) {
    Text text;text.kind=Kind::scalar;text.scalar=kind;text.bits=bits;text.syntax.push_back(std::move(conversion));
    text.original=number(text);return text;
}
Text format(Text source,std::vector<Text> values,std::vector<std::string> conversions) {
    Text text;text.kind=Kind::format;text.syntax=std::move(conversions);text.children.push_back(std::move(source));
    for(auto& value:values) text.children.push_back(std::move(value));
    const auto& pattern=text.children.front().original;std::size_t cursor=0;
    for(std::size_t index=0;index<text.syntax.size();++index) {
        const auto position=pattern.find(text.syntax[index],cursor);append_literal(text.original,pattern,cursor,position-cursor);
        text.original+=text.children[index+1].original;cursor=position+text.syntax[index].size();
    }
    append_literal(text.original,pattern,cursor,pattern.size()-cursor);return text;
}
Text replace_first(Text source,std::string token,Text value) {
    Text text;text.kind=Kind::replace_first;text.original=source.original;
    text.original.replace(text.original.find(token),token.size(),value.original);
    text.syntax.push_back(std::move(token));text.children.push_back(std::move(source));text.children.push_back(std::move(value));return text;
}
Text concat(std::vector<Text> values) {
    Text text;text.kind=Kind::concat;text.children=std::move(values);
    for(const auto& value:text.children) text.original+=value.original;return text;
}
Text before_separator(Text source,char separator) {
    // 5008A2 terminates the selected menu echo at its first control '|'.
    Text text;text.kind=Kind::before_separator;
    text.original=source.original.substr(0,source.original.find(separator));
    text.syntax.emplace_back(1,separator);text.children.push_back(std::move(source));return text;
}
Text without_initial_marker(Text source) {
    // The native selected-copy branch has already chosen source + 1 after
    // strchr("!:?+=>", source[0]); retain that exact source operation.
    Text text;text.kind=Kind::without_initial_marker;
    text.original=source.original;text.original.erase(0,1);
    text.children.push_back(std::move(source));return text;
}
Status project(const Text& text,Lookup resolver,bool chinese,std::string& output) {
    if(!chinese) {output=text.original;return Status::ok;}
    switch(text.kind) {
    case Kind::original:output=text.original;return Status::ok;
    case Kind::lookup:return resolver(text.component,text.original.c_str(),text.key.empty()?nullptr:text.key.c_str(),output);
    case Kind::scalar:output=number(text);return Status::ok;
    case Kind::format: {
        std::string pattern;auto status=project(text.children.front(),resolver,true,pattern);if(status!=Status::ok)return status;
        output.clear();std::size_t cursor=0;
        for(std::size_t index=0;index<text.syntax.size();++index) {
            const auto position=pattern.find(text.syntax[index],cursor);append_literal(output,pattern,cursor,position-cursor);
            std::string value;status=project(text.children[index+1],resolver,true,value);if(status!=Status::ok)return status;
            output+=value;cursor=position+text.syntax[index].size();
        }
        append_literal(output,pattern,cursor,pattern.size()-cursor);return Status::ok;
    }
    case Kind::replace_first: {
        auto status=project(text.children[0],resolver,true,output);if(status!=Status::ok)return status;
        std::string value;status=project(text.children[1],resolver,true,value);if(status!=Status::ok)return status;
        output.replace(output.find(text.syntax.front()),text.syntax.front().size(),value);return Status::ok;
    }
    case Kind::concat:
        output.clear();for(const auto& child:text.children) {std::string value;const auto status=project(child,resolver,true,value);
            if(status!=Status::ok)return status;output+=value;}return Status::ok;
    case Kind::before_separator: {
        const auto status=project(text.children.front(),resolver,true,output);if(status!=Status::ok)return status;
        output=output.substr(0,output.find(text.syntax.front()));return Status::ok;
    }
    case Kind::without_initial_marker: {
        const auto status=project(text.children.front(),resolver,true,output);if(status!=Status::ok)return status;
        output.erase(0,1);return Status::ok;
    }
    }
    return Status::ok;
}
void write(std::vector<unsigned char>& output,const Text& text) {
    scalar_write(output,static_cast<u32>(text.kind));scalar_write(output,static_cast<u32>(text.component));
    string_write(output,text.original);string_write(output,text.key);scalar_write(output,static_cast<u32>(text.scalar));scalar_write(output,text.bits);
    scalar_write(output,static_cast<u32>(text.syntax.size()));for(const auto& syntax:text.syntax)string_write(output,syntax);
    scalar_write(output,static_cast<u32>(text.children.size()));for(const auto& child:text.children)write(output,child);
}
Text read(const unsigned char*& input) {
    Text text;text.kind=static_cast<Kind>(scalar_read<u32>(input));text.component=static_cast<TextComponent>(scalar_read<u32>(input));
    text.original=string_read(input);text.key=string_read(input);text.scalar=static_cast<Scalar>(scalar_read<u32>(input));text.bits=scalar_read<u64>(input);
    const auto syntaxes=scalar_read<u32>(input);for(u32 i=0;i<syntaxes;++i)text.syntax.push_back(string_read(input));
    const auto count=scalar_read<u32>(input);for(u32 i=0;i<count;++i)text.children.push_back(read(input));return text;
}
}
