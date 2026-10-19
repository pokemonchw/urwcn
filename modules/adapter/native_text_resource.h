#pragma once
#include "../../sdk/text_services.h"
#include "../../sdk/host_abi.h"
#include <string>
#include <tuple>
#include <vector>

namespace uwcn::adapter::native_text_resource {
// These are new UI resource identifiers, not offsets in a native structure.
// The producer supplies its actual owner and native record/semantic field ID.
// A call token, draw ordinal and a computed text position are not source IDs.
struct SourceKey {
    u64 owner;
    u64 native_source;
    u32 field;
    bool operator<(const SourceKey& other) const {
        return std::tie(owner,native_source,field)<
            std::tie(other.owner,other.native_source,other.field);
    }
    bool operator==(const SourceKey& other) const {
        return owner==other.owner && native_source==other.native_source && field==other.field;
    }
};

enum class TextPolicy : u32 { semantic,original };
// An owned native text source. Encoded/translated display strings are borrowed
// only while a native component measures and paints this resource.
struct TextSource {
    TextComponent component;
    std::string original;
    std::string value;
    bool has_value;
    TextPolicy policy=TextPolicy::semantic;
    // Original source surrounding the semantic part, such as an action key
    // and '.', sprintf's markup or a player's unchanged name. This is input,
    // never a translated output fragment or a layout instruction from the Mod.
    std::string prefix;
    std::string suffix;
};

inline TextSource from_request(const TextRequest& request) {
    return {request.component,request.original,request.value ? request.value : "",
        request.value!=nullptr,TextPolicy::semantic};
}
inline TextSource original_text(const char* original) {
    return {TextComponent::load_character,original,{},false,TextPolicy::original};
}
using Resolve = Status (*)(TextComponent,const char*,const char*,std::vector<char>&);
using EncodeOriginal = Status (*)(const char*,std::vector<char>&);
inline Status resolve_source(const TextSource& source,Resolve resolve,EncodeOriginal encode_original,
                             std::vector<char>& encoded) {
    const auto status=source.policy==TextPolicy::semantic
        ? resolve(source.component,source.original.c_str(),source.has_value?source.value.c_str():nullptr,encoded)
        : encode_original(source.original.c_str(),encoded);
    if(status!=Status::ok) return status;
    std::vector<char> prefix,suffix;
    auto projection=encode_original(source.prefix.c_str(),prefix);
    if(projection!=Status::ok) return projection;
    projection=encode_original(source.suffix.c_str(),suffix);
    if(projection!=Status::ok) return projection;
    encoded.insert(encoded.begin(),prefix.begin(),prefix.end()-1);
    encoded.insert(encoded.end()-1,suffix.begin(),suffix.end()-1);
    return Status::ok;
}
}
