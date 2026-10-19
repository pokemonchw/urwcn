#include "sdk/host_abi.h"
#include "sdk/text_services.h"
#include "sdk/service_helpers.h"
#include "sdk/utf8.h"
#include <filesystem>
#include <fstream>
#include <map>
#include <set>

namespace {
using namespace uwcn;
std::map<std::string,std::string> entries;
std::string repertoire;
Status UWCN_CALL initialize(const HostApi* host) {
    if (!host || host->abi!=kHostAbi || host->size!=sizeof(HostApi)) return Status::invalid;
    std::map<std::string,std::string> parsed;
    std::set<std::uint32_t> scalars;
    std::string line;
    for(const auto* file:{L"catalog/zh-CN/main_menu.tsv",L"catalog/zh-CN/hud.tsv",L"catalog/zh-CN/world_hud.tsv"}) {
    std::ifstream stream(std::filesystem::path(host->package_path)/file,std::ios::binary);
    if (!stream) return Status::unavailable;
    while(std::getline(stream,line)) {
        if(!line.empty() && line.back()=='\r') line.pop_back();
        if(line.empty() || line[0]=='#') continue;
        const auto tab=line.find('\t');
        if(tab==std::string::npos || tab==0) return Status::invalid;
        const auto key=line.substr(0,tab), value=line.substr(tab+1);
        std::vector<std::uint32_t> decoded;
        if(!decode_utf8(value.data(),value.size(),decoded)) return Status::invalid;
        if(!parsed.emplace(key,value).second) return Status::invalid;
        for(auto c:decoded) scalars.insert(c);
    }
    if(!stream.eof()) return Status::failed;
    }
    std::string characters;
    for(auto c:scalars) append_utf8(characters,c);
    entries.swap(parsed);
    repertoire.swap(characters);
    return Status::ok;
}
Status UWCN_CALL invoke(u32 op,const void* input,u32 bytes,void* output,u32* capacity) {
    if(op==kModuleDependenciesChanged) return input && bytes==sizeof(u32) ? Status::ok : Status::invalid;
    if(op==catalog_op::repertoire) return copy_text(repertoire,output,capacity);
    if(op!=catalog_op::lookup || !input || bytes!=sizeof(CatalogRequest)) return Status::invalid;
    const auto& request=*static_cast<const CatalogRequest*>(input);
    if(!request.key) return Status::invalid;
    auto it=entries.find(request.key);
    return it==entries.end() ? Status::unavailable : copy_text(it->second,output,capacity);
}
void UWCN_CALL shutdown() { entries.clear();repertoire.clear(); }
const ModuleApi api={sizeof(ModuleApi),kHostAbi,ModuleId::catalog,initialize,invoke,empty_save,empty_restore,shutdown};
}
UWCN_EXPORT const uwcn::ModuleDescriptor uwcn_module_descriptor={uwcn::kDescriptorMagic,uwcn::kHostAbi,1,uwcn::kModuleMachine,1};
UWCN_EXPORT const uwcn::ModuleApi* UWCN_CALL uwcn_get_module_api() { return &api; }
