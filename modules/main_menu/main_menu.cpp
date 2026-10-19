#include "sdk/host_abi.h"
#include "sdk/text_services.h"
#include <windows.h>
#include <bcrypt.h>
#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {
using namespace uwcn;
const HostApi* host_api=nullptr;
std::string translation_version;

Status sha256(std::istream& stream,std::array<std::uint8_t,32>& digest) {
    BCRYPT_ALG_HANDLE algorithm=nullptr;
    BCRYPT_HASH_HANDLE hash=nullptr;
    if(BCryptOpenAlgorithmProvider(&algorithm,BCRYPT_SHA256_ALGORITHM,nullptr,0)<0) return Status::failed;
    DWORD object_size=0,written=0;
    bool ok=BCryptGetProperty(algorithm,BCRYPT_OBJECT_LENGTH,reinterpret_cast<PUCHAR>(&object_size),
                              sizeof(object_size),&written,0)>=0;
    std::vector<std::uint8_t> object(object_size);
    if(ok) ok=BCryptCreateHash(algorithm,&hash,object.data(),object_size,nullptr,0,0)>=0;
    std::array<std::uint8_t,32768> buffer;
    while(ok && stream) {
        stream.read(reinterpret_cast<char*>(buffer.data()),buffer.size());
        const auto count=stream.gcount();
        if(count>0) ok=BCryptHashData(hash,buffer.data(),static_cast<ULONG>(count),0)>=0;
    }
    if(ok) ok=stream.eof() && !stream.bad();
    if(ok) ok=BCryptFinishHash(hash,digest.data(),static_cast<ULONG>(digest.size()),0)>=0;
    if(hash) BCryptDestroyHash(hash);
    BCryptCloseAlgorithmProvider(algorithm,0);
    return ok ? Status::ok : Status::failed;
}

Status generate_translation_version(std::string& version) {
    // The identity covers the formal business modules and their Chinese catalog,
    // in ModuleId order. Paths and lowercase digests are part of the hash input;
    // neither the loader nor a runtime UI value participates in this version.
    constexpr const char* files[]={
        "modules/uwcn_catalog.dll", "modules/uwcn_semantic.dll",
        "modules/uwcn_render.dll", "modules/uwcn_layout.dll",
        "modules/uwcn_main_menu.dll", "modules/uwcn_adapter.dll",
        "catalog/zh-CN/main_menu.tsv", "catalog/zh-CN/hud.tsv", "catalog/zh-CN/world_hud.tsv",
        "catalog/zh-CN/cultures.tsv", "catalog/zh-CN/messages.tsv"
    };
    std::string identity="uwcn-package-version-v1\n";
    constexpr char hexadecimal[]="0123456789abcdef";
    std::array<std::uint8_t,32> digest;
    for(const char* file:files) {
        std::ifstream stream(std::filesystem::path(host_api->package_path)/file,std::ios::binary);
        if(!stream) return Status::unavailable;
        const auto status=sha256(stream,digest);
        if(status!=Status::ok) return status;
        identity+=file;
        identity+='\t';
        for(auto byte:digest) {
            identity+=hexadecimal[byte>>4];
            identity+=hexadecimal[byte&15];
        }
        identity+='\n';
    }
    std::istringstream aggregate(identity);
    const auto status=sha256(aggregate,digest);
    if(status!=Status::ok) return status;

    // Match dfcn's five-character base-36 presentation, using this package's
    // SHA-256 as the big-endian integer and retaining both letters and digits.
    constexpr char alphabet[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr std::uint64_t modulus=36u*36u*36u*36u*36u;
    std::uint64_t value=0;
    for(auto byte:digest) value=(value*256u+byte)%modulus;
    version.assign(5,'0');
    for(int i=4;i>=0;--i) {
        version[static_cast<std::size_t>(i)]=alphabet[value%36u];
        value/=36u;
    }
    if(std::all_of(version.begin(),version.end(),[](char c) { return c>='0' && c<='9'; }))
        version[digest[0]%5]=static_cast<char>('A'+digest[1]%26);
    else if(std::all_of(version.begin(),version.end(),[](char c) { return c>='A' && c<='Z'; }))
        version[digest[0]%5]=static_cast<char>('0'+digest[1]%10);
    return Status::ok;
}

Status UWCN_CALL initialize(const HostApi* host) {
    if(!host || host->abi!=kHostAbi || host->size!=sizeof(HostApi)) return Status::invalid;
    host_api=host;return Status::ok;
}
Status UWCN_CALL invoke(u32 op,const void* input,u32 bytes,void* output,u32* capacity) {
    if(op==kModuleDependenciesChanged) {
        translation_version.clear();
        return input && bytes==sizeof(u32) ? Status::ok : Status::invalid;
    }
    if(op!=text_op::translate || !input || bytes!=sizeof(TextRequest)) return Status::invalid;
    // Field values are supplied by the exact native caller while alive. No
    // persistent row pointer, page field snapshot, or layout is built here.
    auto request=*static_cast<const TextRequest*>(input);
    if(request.component==TextComponent::translation_version) {
        if(translation_version.empty()) {
            const auto status=generate_translation_version(translation_version);
            if(status!=Status::ok) return status;
        }
        request.value=translation_version.c_str();
    }
    return host_api->invoke(ModuleId::semantic,text_op::translate,&request,sizeof(request),output,capacity);
}
Status UWCN_CALL save(void*,u32* bytes) { if(!bytes)return Status::invalid;*bytes=0;return Status::ok; }
Status UWCN_CALL restore(const void*,u32 bytes) { return bytes?Status::invalid:Status::ok; }
void UWCN_CALL shutdown() { translation_version.clear();host_api=nullptr; }
const ModuleApi api={sizeof(ModuleApi),kHostAbi,ModuleId::main_menu,initialize,invoke,save,restore,shutdown};
}
UWCN_EXPORT const uwcn::ModuleDescriptor uwcn_module_descriptor={uwcn::kDescriptorMagic,uwcn::kHostAbi,5,0x14c,1};
UWCN_EXPORT const uwcn::ModuleApi* UWCN_CALL uwcn_get_module_api() { return &api; }
