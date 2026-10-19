#include "elf_module.h"
#include <elf.h>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <vector>

namespace uwcn::linux_host {
ModuleDescriptor inspect_module(const std::filesystem::path& path,u32 id) {
    std::ifstream stream(path,std::ios::binary|std::ios::ate);
    if(!stream) throw std::runtime_error("Cannot open candidate ELF: "+path.string());
    const auto size=stream.tellg();
    if(size<static_cast<std::streamoff>(sizeof(Elf64_Ehdr))) throw std::runtime_error("Truncated ELF: "+path.string());
    std::vector<unsigned char> bytes(static_cast<std::size_t>(size));
    stream.seekg(0);
    if(!stream.read(reinterpret_cast<char*>(bytes.data()),bytes.size())) throw std::runtime_error("Cannot read ELF: "+path.string());
    auto region=[&](std::uint64_t offset,std::uint64_t length) {
        if(offset>bytes.size() || length>bytes.size()-offset) throw std::runtime_error("Invalid ELF extent: "+path.string());
        return bytes.data()+offset;
    };
    const auto& header=*reinterpret_cast<const Elf64_Ehdr*>(bytes.data());
    if(std::memcmp(header.e_ident,ELFMAG,SELFMAG)!=0 || header.e_ident[EI_CLASS]!=ELFCLASS64 ||
       header.e_ident[EI_DATA]!=ELFDATA2LSB || header.e_machine!=EM_X86_64 || header.e_type!=ET_DYN ||
       header.e_shentsize!=sizeof(Elf64_Shdr)) throw std::runtime_error("Not a Linux x86-64 shared module: "+path.string());
    const auto* sections=reinterpret_cast<const Elf64_Shdr*>(region(header.e_shoff,std::uint64_t(header.e_shnum)*sizeof(Elf64_Shdr)));
    ModuleDescriptor descriptor{};
    bool found=false;
    for(unsigned i=0;i<header.e_shnum;++i) {
        const auto& section=sections[i];
        if(section.sh_type==SHT_DYNAMIC) {
            const auto* dynamic=reinterpret_cast<const Elf64_Dyn*>(region(section.sh_offset,section.sh_size));
            for(std::size_t j=0;j<section.sh_size/sizeof(Elf64_Dyn);++j)
                if(dynamic[j].d_tag==DT_FLAGS_1 && (dynamic[j].d_un.d_val&DF_1_NODELETE))
                    throw std::runtime_error("ELF NODELETE prevents module retirement: "+path.string());
        }
        if(section.sh_type!=SHT_DYNSYM) continue;
        if(section.sh_link>=header.e_shnum || section.sh_entsize!=sizeof(Elf64_Sym)) throw std::runtime_error("Invalid ELF symbols: "+path.string());
        const auto& strings=sections[section.sh_link];
        const auto* names=reinterpret_cast<const char*>(region(strings.sh_offset,strings.sh_size));
        const auto* symbols=reinterpret_cast<const Elf64_Sym*>(region(section.sh_offset,section.sh_size));
        for(std::size_t j=0;j<section.sh_size/sizeof(Elf64_Sym);++j) {
            const auto& symbol=symbols[j];
            if(ELF64_ST_BIND(symbol.st_info)==STB_GNU_UNIQUE)
                throw std::runtime_error("GNU_UNIQUE prevents module retirement: "+path.string());
            constexpr char name[]="uwcn_module_descriptor";
            if(symbol.st_name>strings.sh_size || strings.sh_size-symbol.st_name<sizeof(name) ||
               std::memcmp(names+symbol.st_name,name,sizeof(name))!=0) continue;
            if(symbol.st_shndx>=header.e_shnum || symbol.st_shndx==SHN_UNDEF || symbol.st_size!=sizeof(ModuleDescriptor))
                throw std::runtime_error("Invalid module descriptor symbol: "+path.string());
            const auto& owner=sections[symbol.st_shndx];
            if(symbol.st_value<owner.sh_addr || symbol.st_value-owner.sh_addr>owner.sh_size ||
               sizeof(ModuleDescriptor)>owner.sh_size-(symbol.st_value-owner.sh_addr))
                throw std::runtime_error("Invalid module descriptor extent: "+path.string());
            std::memcpy(&descriptor,region(owner.sh_offset+symbol.st_value-owner.sh_addr,sizeof(descriptor)),sizeof(descriptor));
            found=true;
        }
    }
    if(!found || descriptor.magic!=kDescriptorMagic || descriptor.abi!=kHostAbi ||
       descriptor.module_id!=id || descriptor.machine!=kModuleMachine || descriptor.state_schema!=1)
        throw std::runtime_error("Module ABI/identity/state schema differs: "+path.string());
    return descriptor;
}
}
