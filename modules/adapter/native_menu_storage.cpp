#include "native_menu_storage.h"
#include "native_menu_model.h"
#include <windows.h>
#include <array>
#include <cstring>
#include <map>
#include <tuple>

namespace uwcn::adapter::native_menu_storage {
namespace {
std::uintptr_t base{};
native_menu_model::Handle saved_source{},writing_source{};
enum Hook:u32 { native_write=0x5800,native_read };
enum class Part:u32 { header,rows };
struct NativePair {u32 header_return,rows_return;};
// Both buffers and their sizes are literal original native input fields:
// header 5F54A20/190h; rows 5F4EF10/5AA0h. Each pair uses the same fopen
// MENULIST.SAV(1A4E10), wb(18F978) or rb(18F1F8), then fclose.
constexpr std::array<NativePair,7> writes{{
    {0xF654,0xF663},{0xFAF6,0xFB05},{0xD7BAF,0xD7BBE},
    {0xE0DCD,0xE0DDC},{0xFCB0F,0xFCB1E},{0x10050C,0x10051B},
    {0x100AFD,0x100B0C}
}};
constexpr std::array<NativePair,6> reads{{
    {0xF99F,0xF9AE},{0xD7C28,0xD7C37},{0xE1048,0xE105B},
    {0xFCF82,0xFCF95},{0x10072F,0x10073E},{0x100CEB,0x100CFA}
}};
std::map<u64,Part> pending;
template<std::size_t N>
bool locate(const std::array<NativePair,N>& pairs,u32 caller,Part& part) {
    for(const auto& pair:pairs) {
        if(caller==pair.header_return) {part=Part::header;return true;}
        if(caller==pair.rows_return) {part=Part::rows;return true;}
    }
    return false;
}
void append(std::vector<std::uint8_t>& bytes,u32 value) {
    const auto* input=reinterpret_cast<const std::uint8_t*>(&value);
    bytes.insert(bytes.end(),input,input+sizeof(value));
}
}
void initialize(std::uintptr_t image_base) {
    base=image_base;saved_source=0;writing_source=0;pending.clear();
}
void append_hooks(std::vector<HookSpec>& hooks) {
    // The original EXE imports api-ms-win-crt-stdio-l1-1-0.dll. These UCRT
    // exports are its actual original fread/fwrite entry points; the IAT may
    // already contain the same resident Host thunk on a module replacement.
    const auto runtime=GetModuleHandleW(L"ucrtbase.dll");
    for(const auto& [id,rva,name]:std::array<std::tuple<u32,u32,const char*>,2>{{
        {native_write,0x18C4D8,"fwrite"},{native_read,0x18C4A8,"fread"}}}) {
        HookSpec hook{id,HookKind::import_slot,rva,0,4,4,{}};
        const auto original=static_cast<u32>(reinterpret_cast<std::uintptr_t>(GetProcAddress(runtime,name)));
        std::memcpy(hook.expected,&original,4);hooks.push_back(hook);
    }
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id==native_write || event.id==native_read;
    if(!handled) return Status::ok;
    if(event.phase==NativePhase::before) {
        const auto caller=*reinterpret_cast<const u32*>(static_cast<std::uintptr_t>(event.frame->esp))-
            static_cast<u32>(base);
        Part part;
        const bool participating=event.id==native_write ? locate(writes,caller,part) : locate(reads,caller,part);
        if(!participating) return Status::ok;
        pending.emplace(event.token,part);
        if(part==Part::header) {
            const auto active=native_menu_model::active();
            native_menu_model::capture_into(active);
            if(event.id==native_write) {
                writing_source=active;native_menu_model::retain(writing_source);
            }
        }
    } else if(event.phase==NativePhase::after) {
        const auto call=pending.find(event.token);
        if(call==pending.end()) return Status::ok;
        if(call->second==Part::rows) {
            if(event.id==native_write) {
                if(saved_source) native_menu_model::release(saved_source);
                saved_source=writing_source;writing_source=0;
            } else {
                // The original fread just restored both real native ranges.
                // Adopt those values, including native selection; activate()
                // would instead overwrite them from an old stored model.
                native_menu_model::adopt_from_native(saved_source);
            }
        }
        pending.erase(call);
    }
    return Status::ok;
}
std::vector<std::uint8_t> save() {
    std::vector<std::uint8_t> bytes;append(bytes,saved_source);append(bytes,writing_source);return bytes;
}
void restore(const void* payload) {
    const auto* bytes=static_cast<const std::uint8_t*>(payload);
    std::memcpy(&saved_source,bytes,4);std::memcpy(&writing_source,bytes+4,4);pending.clear();
}
void shutdown() {
    if(saved_source) native_menu_model::release(saved_source);
    if(writing_source) native_menu_model::release(writing_source);
    saved_source=0;writing_source=0;pending.clear();base=0;
}
}
