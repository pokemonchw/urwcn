#include "sdk/host_abi.h"
#include "sdk/text_services.h"
#include "sdk/service_helpers.h"
#include "sdk/utf8.h"
#include <algorithm>
#include <map>

namespace {
using namespace uwcn;
// A transport alphabet for the confirmed native tokenizer. Native wrappers
// remap C4/E4/F6, so those bytes never appear in the encoded representation.
// This representation has no bearing on width: Render supplies real metrics.
constexpr u32 trailing_count=125;
constexpr u32 token_capacity=64*trailing_count;
std::vector<u32> scalar_by_token;
std::map<u32,u32> token_by_scalar;
bool excluded(unsigned value) { return value==0xc4 || value==0xe4 || value==0xf6; }
unsigned trailing(u32 index) {
    for(unsigned value=0x80;value<=0xff;++value) {
        if(excluded(value)) continue;
        if(!index) return value;
        --index;
    }
    return 0;
}
bool trailing_index(unsigned value,u32& index) {
    if(value<0x80 || value>0xff || excluded(value)) return false;
    index=value-0x80;
    for(unsigned excluded_value:{0xc4u,0xe4u,0xf6u}) if(value>excluded_value)--index;
    return true;
}
Status encode(const char* input,std::string& result) {
    std::vector<u32> scalars;
    if(!decode_utf8(input,std::strlen(input),scalars)) return Status::invalid;
    for(auto scalar:scalars) {
        if(scalar<0x80) {result.push_back(static_cast<char>(scalar));continue;}
        auto it=token_by_scalar.find(scalar);
        if(it==token_by_scalar.end()) {
            if(scalar_by_token.size()==token_capacity) return Status::invalid;
            const auto index=static_cast<u32>(scalar_by_token.size());
            scalar_by_token.push_back(scalar);
            it=token_by_scalar.emplace(scalar,index).first;
        }
        result.push_back(static_cast<char>(0x80+it->second/trailing_count));
        result.push_back(static_cast<char>(trailing(it->second%trailing_count)));
    }
    return Status::ok;
}
Status decode(const char* input,std::string& result) {
    const auto size=std::strlen(input);
    for(std::size_t i=0;i<size;++i) {
        const auto lead=static_cast<unsigned char>(input[i]);
        if(lead<0x80) {result.push_back(static_cast<char>(lead));continue;}
        if(lead>0xbf || i+1==size) return Status::invalid;
        u32 tail=0;
        if(!trailing_index(static_cast<unsigned char>(input[++i]),tail)) return Status::invalid;
        const u32 index=(lead-0x80)*trailing_count+tail;
        if(index>=scalar_by_token.size()) return Status::invalid;
        append_utf8(result,scalar_by_token[index]);
    }
    return Status::ok;
}
Status UWCN_CALL initialize(const HostApi* host) {
    return host && host->abi==kHostAbi && host->size==sizeof(HostApi) ? Status::ok : Status::invalid;
}
Status UWCN_CALL invoke(u32 op,const void* input,u32 bytes,void* output,u32* capacity) {
    if(op==kModuleDependenciesChanged) return input && bytes==sizeof(u32) ? Status::ok : Status::invalid;
    if(op==layout_op::decode) {
        if(!input || bytes!=sizeof(DecodeRequest)) return Status::invalid;
        const auto& request=*static_cast<const DecodeRequest*>(input);
        if(!request.utf8) return Status::invalid;
        std::vector<u32> scalars;
        if(!decode_utf8(request.utf8,request.byte_count,scalars)) return Status::invalid;
        return copy_output(scalars.data(),static_cast<u32>(scalars.size()*sizeof(u32)),output,capacity);
    }
    if((op!=layout_op::encode_native && op!=layout_op::decode_native) || !input || bytes!=sizeof(CodecRequest)) return Status::invalid;
    const auto& request=*static_cast<const CodecRequest*>(input);
    if(!request.text) return Status::invalid;
    std::string result;
    const auto status=op==layout_op::encode_native ? encode(request.text,result) : decode(request.text,result);
    return status==Status::ok ? copy_text(result,output,capacity) : status;
}
Status UWCN_CALL save(void* output,u32* capacity) {
    std::vector<u32> state{1,static_cast<u32>(scalar_by_token.size())};
    state.insert(state.end(),scalar_by_token.begin(),scalar_by_token.end());
    return copy_output(state.data(),static_cast<u32>(state.size()*sizeof(u32)),output,capacity);
}
Status UWCN_CALL restore(const void* input,u32 bytes) {
    if(!input || bytes<2*sizeof(u32) || bytes%sizeof(u32)) return Status::invalid;
    const auto* state=static_cast<const u32*>(input);
    const auto count=state[1];
    if(state[0]!=1 || count>token_capacity || bytes!=(count+2)*sizeof(u32)) return Status::invalid;
    std::vector<u32> scalars(state+2,state+2+count);
    std::map<u32,u32> indices;
    for(u32 i=0;i<count;++i) {
        const auto scalar=scalars[i];
        if(scalar<0x80 || scalar>0x10ffff || (scalar>=0xd800 && scalar<=0xdfff)) return Status::invalid;
        if(!indices.emplace(scalar,i).second) return Status::invalid;
    }
    scalar_by_token.swap(scalars);token_by_scalar.swap(indices);
    return Status::ok;
}
void UWCN_CALL shutdown() { scalar_by_token.clear();token_by_scalar.clear(); }
const ModuleApi api={sizeof(ModuleApi),kHostAbi,ModuleId::layout,initialize,invoke,save,restore,shutdown};
}
UWCN_EXPORT const uwcn::ModuleDescriptor uwcn_module_descriptor={uwcn::kDescriptorMagic,uwcn::kHostAbi,4,uwcn::kModuleMachine,1};
UWCN_EXPORT const uwcn::ModuleApi* UWCN_CALL uwcn_get_module_api() { return &api; }
