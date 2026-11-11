#include "emergency_save.h"
#include <algorithm>
#include <array>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace urwcn::launcher {
namespace {
namespace fs=std::filesystem;
using Bytes=std::vector<unsigned char>;
constexpr std::uint32_t preferred_base=0x400000;
constexpr std::size_t player_size=0x1654,object_size=0x24,creature_size=0x568;
constexpr std::size_t world_size=0x601401,zoom_size=0x15948,marker_size=0x9c;
// All VAs and disk sizes below come from the admitted 3.89.1 PE's native
// Save/SaveMap/save_creatures/dataextract/save_zoommap and matching readers.
// See docs/evidence/20261111-launcher-emergency-save.md.
struct Remote {
    HANDLE process;std::uintptr_t base;
    Bytes read(std::uint32_t va,std::size_t size) const {
        Bytes bytes(size);SIZE_T copied=0;
        if(!ReadProcessMemory(process,reinterpret_cast<const void*>(base+va-preferred_base),
                              bytes.data(),size,&copied) || copied!=size) {
            std::ostringstream error;error<<"ReadProcessMemory VA=0x"<<std::hex<<va
                <<" size=0x"<<size<<" read=0x"<<copied<<" error="<<std::dec<<GetLastError();
            throw std::runtime_error(error.str());
        }
        return bytes;
    }
    template<class T> T scalar(std::uint32_t va) const {
        const auto bytes=read(va,sizeof(T));T value;std::memcpy(&value,bytes.data(),sizeof(value));return value;
    }
};
template<class T> T get(const Bytes& bytes,std::size_t offset) {
    T value;std::memcpy(&value,bytes.data()+offset,sizeof(value));return value;
}
template<class T> void set(Bytes& bytes,std::size_t offset,T value) {
    std::memcpy(bytes.data()+offset,&value,sizeof(value));
}
std::string text(const Bytes& bytes,std::size_t offset,std::size_t capacity) {
    const auto begin=bytes.begin()+offset,end=begin+capacity;
    const auto terminator=std::find(begin,end,0);
    if(terminator==end) throw std::runtime_error("Native fixed-capacity string has no terminator");
    return {begin,terminator};
}
std::wstring path_text(const std::string& bytes) {
    const int size=MultiByteToWideChar(CP_ACP,MB_ERR_INVALID_CHARS,bytes.data(),static_cast<int>(bytes.size()),nullptr,0);
    if(!size) throw std::runtime_error("Cannot decode native filesystem name");
    std::wstring value(size,0);
    if(!MultiByteToWideChar(CP_ACP,MB_ERR_INVALID_CHARS,bytes.data(),static_cast<int>(bytes.size()),value.data(),size))
        throw std::runtime_error("Cannot decode native filesystem name");
    return value;
}
std::string path_utf8(const fs::path& path) {
    const auto value=path.u8string();return {value.begin(),value.end()};
}
void filename(const std::wstring& name) {
    if(name.empty() || name==L"." || name==L".." || name.find_first_of(L"\\/:*?\"<>|")!=std::wstring::npos)
        throw std::runtime_error("Native save identity is not a filename");
}
Bytes file_bytes(const fs::path& file) {
    std::ifstream input(file,std::ios::binary|std::ios::ate);
    if(!input) throw std::runtime_error("Cannot read existing native save file");
    const auto size=input.tellg();
    if(size<0) throw std::runtime_error("Cannot size existing native save file");
    Bytes bytes(static_cast<std::size_t>(size));input.seekg(0);
    if(!input.read(reinterpret_cast<char*>(bytes.data()),static_cast<std::streamsize>(bytes.size())))
        throw std::runtime_error("Cannot read complete native save file");
    return bytes;
}
void write_file(const fs::path& file,const Bytes& bytes,std::ostream& report) {
    HANDLE output=CreateFileW(file.c_str(),GENERIC_WRITE,FILE_SHARE_READ,nullptr,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);
    if(output==INVALID_HANDLE_VALUE) throw std::runtime_error("Cannot create recovery save file; error="+std::to_string(GetLastError()));
    DWORD written=0;
    const bool copied=bytes.empty() || (WriteFile(output,bytes.data(),static_cast<DWORD>(bytes.size()),&written,nullptr) && written==bytes.size());
    const auto write_error=GetLastError();
    const bool flushed=FlushFileBuffers(output)!=FALSE;const auto flush_error=GetLastError();
    CloseHandle(output);
    if(!copied || !flushed) throw std::runtime_error("Recovery file write/flush failed: "+std::to_string(write_error)+"/"+std::to_string(flush_error));
    report<<"saved_file="<<path_utf8(file.filename())<<" bytes="<<bytes.size()<<'\n';report.flush();
}
void append(Bytes& destination,const Bytes& value) {destination.insert(destination.end(),value.begin(),value.end());}
void record_at(Bytes& destination,std::size_t offset,const unsigned char* source,std::size_t size) {
    if(offset>std::numeric_limits<std::uint32_t>::max()-size) throw std::runtime_error("Native record offset exceeds x86 file format");
    if(destination.size()<offset+size) destination.resize(offset+size);
    std::memcpy(destination.data()+offset,source,size);
}
int chunk(int coordinate) {
    // Exact native 4EBBC0 classification. Edge coordinates use the last chunk.
    for(int index=-2;index<=2;++index)
        if(coordinate>=200+index*64 && coordinate<264+index*64) return index;
    return 2;
}
struct Snapshot {
    Bytes player,data,creatures,creature_ids,markers,herbs;
    std::int32_t x,y,iso_x,iso_y,day;
    std::string map;
    bool bigmap;
};
void save_creatures(const Snapshot& state,Bytes& persisted) {
    if(persisted.size()%creature_size) throw std::runtime_error("Native CRS has a partial record");
    for(unsigned index=0;index<500;++index) {
        const auto record=index*creature_size;
        const auto identity=get<std::int32_t>(state.creature_ids,index*4);
        if(!state.creatures[record] || identity<1000) continue;
        bool present=false;
        // Native inventory is 50 complete 0x24-byte records at Plr+AE4.
        for(unsigned item=0;item<50;++item) {
            const auto at=0xae4+item*object_size;
            if(state.player[at+4]==4 && get<std::int32_t>(state.player,at+12)==identity) present=true;
        }
        for(std::size_t at=0;at<state.data.size();at+=object_size)
            if((state.data[at+4]==4 || state.data[at+4]==0x34) &&
               get<std::int32_t>(state.data,at+12)==static_cast<std::int32_t>(index+1000)) present=true;
        if(!present) continue;
        if(static_cast<std::size_t>(identity-1000)>=persisted.size()/creature_size)
            throw std::runtime_error("Active creature identity is outside the native CRS record arena");
        Bytes value(state.creatures.begin()+record,state.creatures.begin()+record+creature_size);
        if(value[0x67]!=13) set(value,0x1d4,state.day);
        set(value,0x2e8,static_cast<std::int16_t>(state.iso_x));
        set(value,0x2ea,static_cast<std::int16_t>(state.iso_y));
        record_at(persisted,static_cast<std::size_t>(identity-1000)*creature_size,value.data(),value.size());
    }
}
void persist_creature_references(Snapshot& state) {
    // Native SaveMap changes only the saved DATA copy. Keep the raw crashed
    // process, the dump and the source snapshot unchanged.
    for(std::size_t at=0;at<state.data.size();at+=object_size) {
        if(state.data[at+4]!=4 && state.data[at+4]!=0x34) continue;
        const auto reference=get<std::uint32_t>(state.data,at+12);
        if(reference<1000 || reference-1000>=500) continue;
        const auto index=reference-1000;
        if(!state.creatures[index*creature_size] || !get<std::uint32_t>(state.creature_ids,index*4)) continue;
        const auto creature_ref=get<std::uint32_t>(state.creatures,index*creature_size+0x52c);
        if(creature_ref<1000 || reference!=creature_ref)
            set(state.data,at+12,get<std::uint32_t>(state.creature_ids,index*4));
    }
}
std::size_t marker(Bytes& markers,int x,int y) {
    std::size_t vacant=markers.size();
    for(std::size_t at=0;at<markers.size();at+=marker_size) {
        if(get<std::int16_t>(markers,at)==x && get<std::int16_t>(markers,at+2)==y) return at;
        if(vacant==markers.size() && get<std::int16_t>(markers,at)==0) vacant=at;
    }
    // The original 4EC010 explicitly chooses slot zero when all 10000 slots
    // are occupied. This is the native selection rule, not a recovery default.
    return vacant==markers.size()?0:vacant;
}
void save_zoom(const Remote& remote,Snapshot& state,const fs::path& directory,std::ostream& report) {
    Bytes index,maps;
    if(fs::exists(directory/L"ZOOMINDEX.DAT")) {
        index=file_bytes(directory/L"ZOOMINDEX.DAT");maps=file_bytes(directory/L"ZOOMMAPS.DAT");
        if(index.size()%12 || maps.size()%zoom_size || index.size()/12!=maps.size()/zoom_size)
            throw std::runtime_error("Native zoom index and record arena do not agree");
    } else {
        // Exact sentinel schema created by 4EB810 before the first zoom save.
        index.resize(12);maps.resize(zoom_size);
        set(index,0,remote.scalar<std::uint32_t>(0x06422aec));
        set(index,4,std::int32_t{-1});set(index,8,std::int32_t{-1});
        set(maps,0,std::int32_t{-1});set(maps,4,std::int32_t{-1});
    }
    const std::array<Bytes,4> grids{remote.read(0x00cf9448,world_size),remote.read(0x03f8b8e0,world_size),
        remote.read(0x012fa850,world_size),remote.read(0x006f8040,world_size)};
    for(int cy=-2;cy<=2;++cy) for(int cx=-2;cx<=2;++cx) {
        const int x=state.iso_x+cx,y=state.iso_y+cy;
        Bytes value(zoom_size);
        set(value,0,x);set(value,4,y);
        for(unsigned grid=0;grid<4;++grid) for(int row=0;row<64;++row) {
            const auto origin=static_cast<std::size_t>((200+cy*64+row)*0xc01+200+cx*64);
            std::memcpy(value.data()+8+grid*4096+row*64,grids[grid].data()+origin,64);
        }
        unsigned count=0;
        for(std::size_t at=0;at<state.data.size();at+=object_size) {
            if(!state.data[at+4]) continue;
            const auto ox=get<std::uint16_t>(state.data,at),oy=get<std::uint16_t>(state.data,at+2);
            if(chunk(ox)!=cx || chunk(oy)!=cy) continue;
            if(count==2000) throw std::runtime_error("Zoom chunk exceeds the native 2000-record on-disk capacity");
            const auto to=8+16384+count++*object_size;
            std::memcpy(value.data()+to,state.data.data()+at,object_size);
            set(value,to,static_cast<std::int16_t>(int(ox)-200-cx*64));
            set(value,to+2,static_cast<std::int16_t>(int(oy)-200-cy*64));
        }
        std::size_t ordinal=index.size()/12;
        for(std::size_t i=1;i<index.size()/12;++i)
            if(get<std::int32_t>(index,i*12+4)==x && get<std::int32_t>(index,i*12+8)==y) {ordinal=i;break;}
        if(ordinal==index.size()/12) {
            const auto old=index.size();index.resize(old+12);
            set(index,old,remote.scalar<std::uint32_t>(0x06422aec));set(index,old+4,x);set(index,old+8,y);
        }
        record_at(maps,ordinal*zoom_size,value.data(),value.size());
        const auto at=marker(state.markers,x,y);
        set(state.markers,at,static_cast<std::int16_t>(x));set(state.markers,at+2,static_cast<std::int16_t>(y));
        set(state.markers,at+4,static_cast<std::int16_t>(state.day));
        if(cx==chunk(state.x) && cy==chunk(state.y)) {
            set(state.markers,at+0x94,state.x-cx*64-199);
            set(state.markers,at+0x98,state.y-cy*64-199);
        }
    }
    write_file(directory/L"ZOOMMAPS.DAT",maps,report);write_file(directory/L"ZOOMINDEX.DAT",index,report);
}
void save_village(const Remote& remote,const fs::path& directory,const std::wstring& identity,std::ostream& report) {
    const auto id=remote.scalar<std::int32_t>(0x005e2c1c);
    if(id==-1000) return; // Original Save has no pending village record.
    Bytes village=remote.read(0x0217f558,0x2ca4);set(village,8,id);
    const auto path=directory/(identity+L".VIL");
    Bytes persisted;if(fs::exists(path)) persisted=file_bytes(path);
    if(persisted.size()%village.size()) throw std::runtime_error("Native VIL has a partial record");
    std::size_t at=0;
    while(at<persisted.size() && get<std::int32_t>(persisted,at+8)!=id) at+=village.size();
    record_at(persisted,at,village.data(),village.size());write_file(path,persisted,report);
}
}

bool emergency_save(HANDLE process,std::uintptr_t image_base,const std::wstring& game_hash,
    const fs::path& game_directory,const fs::path& project_root,const fs::path& incident,std::ostream& report) {
    report<<"\nIndependent native-format emergency serializer\n";
    // The old 3.89 PE is not present in the current static evidence. No schema
    // is inferred from shared code or version-string similarity.
    if(game_hash!=L"c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d") {
        report<<"save_error=no_confirmed_native_save_schema_for_this_executable\n";return false;
    }
    try {
        const Remote remote{process,image_base};
        const auto identity=path_text(text(remote.read(0x0a783c10,128),0,128));filename(identity);
        const auto native_directory=path_text(text(remote.read(0x0a783c90,1024),0,1024));
        const auto source=fs::canonical(game_directory/identity);
        if(fs::canonical(game_directory/native_directory)!=source)
            throw std::runtime_error("Native CharacterPath and CharacterFile do not identify the same save directory");
        Snapshot state;
        state.player=remote.read(0x0a72a6e8,player_size);
        if(text(state.player,0,13).empty()) throw std::runtime_error("No named native character exists at this crash boundary");
        state.map=text(state.player,0x96d,13);
        if(state.map.empty()) throw std::runtime_error("The character has no constructed native map");
        filename(path_text(state.map));state.bigmap=state.map=="BIGMAP";
        const auto previous=file_bytes(source/(identity+L".URS"));
        if(previous.size()!=player_size || text(previous,0,13)!=text(state.player,0,13))
            throw std::runtime_error("Current player and existing native save identity differ");
        state.data=remote.read(0x0a6d28a8,360000);
        state.creatures=remote.read(0x06151400,500*creature_size);
        state.creature_ids=remote.read(0x0634c160,500*4);
        state.markers=remote.read(0x06422af8,0x17cdc0);
        state.herbs=remote.read(0x0590acb8,100*0x1a8);
        state.x=remote.scalar<std::int32_t>(0x0a6d1c9c);state.y=remote.scalar<std::int32_t>(0x0a72bd40);
        state.iso_x=get<std::int32_t>(state.player,0x11fc);state.iso_y=get<std::int32_t>(state.player,0x1200);
        // 48C160/4ECDE0 use the native 3072 x 2048 world domain. Reject
        // corrupt coordinates before arithmetic or any file publication.
        if(state.iso_x<0 || state.iso_x>=0xc00 || state.iso_y<0 || state.iso_y>=0x800 ||
           state.x<0 || state.x>0xc00 || state.y<0 || state.y>0x800)
            throw std::runtime_error("Crash coordinates exceed the native map domains");
        state.day=get<std::int32_t>(state.player,0xadc);
        set(state.player,0xa88,remote.scalar<unsigned char>(0x0a784110));
        set(state.player,0xa8c,state.x);set(state.player,0xa90,state.y);
        set(state.player,0x1204,state.bigmap?0:state.x);set(state.player,0x1208,state.bigmap?0:state.y);
        set(state.player,0x1634,remote.scalar<std::uint32_t>(0x065bb5c8));
        set(state.player,0x1218,std::uint32_t{0x185});
        const auto prepared=incident/L"save"/identity;
        report<<"native_save_directory="<<path_utf8(source)<<"\nrecovery_copy="<<path_utf8(prepared)<<'\n';
        fs::create_directories(prepared.parent_path());
        // Unloaded historical areas, portraits and side files remain exactly
        // as persisted. All live Save-owned records below replace this copy.
        fs::copy(source,prepared,fs::copy_options::recursive);
        auto creatures=file_bytes(prepared/(identity+L".CRS"));
        save_creatures(state,creatures);write_file(prepared/(identity+L".CRS"),creatures,report);
        persist_creature_references(state);
        if(state.bigmap) {
            write_file(prepared/L"WORLD.DAT",remote.read(0x00cf9448,world_size),report);
            write_file(prepared/L"WORLD.PLM",remote.read(0x03f8b8e0,world_size),report);
            write_file(prepared/L"DATA.DAT",state.data,report);
        } else {
            // 48E1B0 copies the saved world maps and DATA to these resident
            // backing arrays before switching to local terrain. The active
            // grids now contain local terrain, so they are not WORLD files.
            write_file(prepared/L"WORLD.DAT",remote.read(0x02d86ac8,world_size),report);
            write_file(prepared/L"WORLD.PLM",remote.read(0x03388450,world_size),report);
            write_file(prepared/L"DATA.DAT",remote.read(0x0a72bdd0,360000),report);
            save_zoom(remote,state,prepared,report);
        }
        write_file(prepared/(path_text(state.map)+L".DAT"),state.data,report);
        write_file(prepared/(identity+L".OBJ"),remote.read(0x059216a8,0x82f690),report);
        write_file(prepared/L"CONSTANT.OBJ",remote.read(0x058f9ff8,0x10cc0),report);
        Bytes herbs;
        for(std::size_t at=0;at<state.herbs.size();at+=0x1a8)
            if(state.herbs[at+0xd]) herbs.insert(herbs.end(),state.herbs.begin()+at,state.herbs.begin()+at+0x1a8);
        write_file(prepared/L"HERBLORE.DAT",herbs,report);
        Bytes weather(4);set(weather,0,std::uint32_t{3});
        append(weather,remote.read(0x0a7e6e4c,12));append(weather,remote.read(0x0a7e6df8,0x44));
        append(weather,remote.read(0x0a7e7028,0xbfc8));write_file(prepared/L"GLOBWEATHER.DAT",weather,report);
        write_file(prepared/L"kulttuuri.dat",remote.read(0x02182200,0x1800),report);
        write_file(prepared/L"MARKER.DAT",state.markers,report);
        write_file(prepared/L"EXTRAMARKER.DAT",remote.read(0x05790900,0x15f900),report);
        save_village(remote,prepared,identity,report);
        write_file(prepared/(identity+L".URS"),state.player,report);
        report<<"serialization_complete=1\n";report.flush();
        const auto recycled=project_root/L"回收"/incident.filename()/L"game-saves"/identity;
        const auto candidate=game_directory/(L".urwcn-save-"+incident.filename().wstring());
        // Prepare the install on the game's own filesystem before moving the
        // old directory. The final rename never exposes a half-copied save.
        fs::copy(prepared,candidate,fs::copy_options::recursive);
        fs::create_directories(recycled.parent_path());
        // Preserve the original directory first; install the complete new
        // native directory at exactly the same location consumed by Load.
        fs::rename(source,recycled);
        report<<"original_save_archived=1\narchive="<<path_utf8(recycled)
              <<"\ninstall_candidate="<<path_utf8(candidate)<<'\n';report.flush();
        fs::rename(candidate,source);
        report<<"native_save_installed=1\n"
              <<"save_note=frozen_crash_state; memory consistency and gameplay validity cannot be inferred from serialization success\n";
        return true;
    } catch(const std::exception& error) {
        report<<"save_error="<<error.what()<<"\n";report.flush();return false;
    }
}
}
