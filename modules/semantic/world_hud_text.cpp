#include "world_hud_text.h"
#include "sdk/service_helpers.h"
#include "sdk/utf8.h"
#include <string_view>

namespace uwcn {
namespace {
struct Lexeme { const char* english; const char* key; };
// Original 0A3E70 initializer and 0A8F50 join rules are recorded in
// docs/evidence/world-hud-ghidra.c. These arrays contain vocabulary only.
#include "world_place_lexemes.inc"

Status lookup(const HostApi* host,const std::string& key,std::string& result) {
    const CatalogRequest request{key.c_str()};
    return invoke_text(host,ModuleId::catalog,catalog_op::lookup,&request,sizeof(request),result);
}
void replace(std::string& text,const char* marker,const std::string& value) {
    text.replace(text.find(marker),std::char_traits<char>::length(marker),value);
}
std::string lower_initial(std::string text) {
    if(text[0]>='A' && text[0]<='Z') text[0]+=32;
    return text;
}
std::string native_lexeme(const char* text) {
    std::string unicode;
    for(auto* p=reinterpret_cast<const unsigned char*>(text);*p;++p) append_utf8(unicode,*p);
    return unicode;
}
std::string display_name(std::string_view source) {
    // Native 10E5A0 remaps C4/E4/F6 to its original Finnish font entries.
    // Preserve those same letters when the display name enters UTF-8.
    std::string result;
    for(const unsigned char c:source) {
        switch(c) {
        case 0xC4: result+="\xC3\x84"; break;
        case 0xE4: result+="\xC3\xA4"; break;
        case 0xF6: result+="\xC3\xB6"; break;
        default: result+=static_cast<char>(c); break;
        }
    }
    return result;
}
Status place_gloss(const HostApi* host,const std::string& source,
                   std::string_view native_name,std::string& result) {
    // 0A8F50's 0x8000 named-place branch supplies the same proper name for
    // both languages. Preserve that confirmed branch's user/world name.
    if(std::string_view(source)==native_name) { result=display_name(source); return Status::ok; }
    for(const auto& prefix:place_prefixes) {
        std::string first=native_lexeme(prefix.english);
        const bool separated=first.back()=='_';
        if(separated) first.back()=' ';
        if(source.compare(0,first.size(),first)!=0) continue;
        for(const auto& suffix:place_suffixes) {
            std::string second=native_lexeme(suffix.english);
            if(second[0]=='_') {
                if(separated) second.erase(0,1);
                else second[0]=' ';
            }
            if(source.compare(first.size(),std::string::npos,second)!=0) continue;
            std::string a,b;
            auto status=lookup(host,prefix.key,a);
            if(status!=Status::ok) return status;
            status=lookup(host,suffix.key,b);
            if(status!=Status::ok) return status;
            result=a+b;
            return Status::ok;
        }
    }
    return Status::unavailable;
}
Status culture(const HostApi* host,const std::string& source,std::string& result) {
    return lookup(host,"world.culture."+source,result);
}
Status region(const HostApi* host,const std::string& source,std::string& result) {
    // 09B040 flag 4 explicitly emits an empty supplementary region line.
    if(source.empty()) { result.clear(); return Status::ok; }
    const auto normalized=lower_initial(source);
    if(normalized=="no man's land") return lookup(host,"world.region.unclaimed",result);
    if(normalized.compare(0,5,"near ")==0) {
        std::string name;
        auto status=region(host,source.substr(5),name);
        if(status!=Status::ok) return status;
        status=lookup(host,"world.region.near",result);
        if(status==Status::ok) replace(result,"{name}",name);
        return status;
    }
    constexpr Lexeme directions[]={
        {"northern ","north"},{"southern ","south"},{"western ","west"},
        {"eastern ","east"},{"north-eastern ","north_east"},
        {"north-western ","north_west"},{"south-eastern ","south_east"},
        {"south-western ","south_west"},{"north of ","outside_north"},
        {"south of ","outside_south"},{"east of ","outside_east"},
        {"west of ","outside_west"}
    };
    for(const auto& direction:directions) {
        const auto count=std::char_traits<char>::length(direction.english);
        if(normalized.compare(0,count,direction.english)!=0) continue;
        std::string name;
        auto status=culture(host,source.substr(count),name);
        if(status!=Status::ok) return status;
        status=lookup(host,std::string("world.region.")+direction.key,result);
        if(status==Status::ok) replace(result,"{name}",name);
        return status;
    }
    // 09AD00 also emits the culture name alone for its central region.
    return culture(host,source,result);
}
Status month(const HostApi* host,const std::string& source,std::string& result) {
    const auto normalized=lower_initial(source);
    constexpr Lexeme phases[]={{"beginning of ","beginning"},{"early ","early"},
                              {"late ","late"},{"end of ","end"}};
    for(const auto& phase:phases) {
        const auto count=std::char_traits<char>::length(phase.english);
        if(normalized.compare(0,count,phase.english)!=0) continue;
        std::string name;
        auto status=lookup(host,"world.month."+source.substr(count),name);
        if(status!=Status::ok) return status;
        status=lookup(host,std::string("world.month_phase.")+phase.key,result);
        if(status==Status::ok) replace(result,"{month}",name);
        return status;
    }
    // Days 11..20 carry the month name without a phase in 15E910.
    return lookup(host,"world.month."+source,result);
}
Status date(const HostApi* host,const std::string& source,std::string& result) {
    // 08A310 formats exactly "day %d of %s week before %s"; 090705
    // capitalizes its initial before the HUD's centered text call.
    const auto of=source.find(" of ");
    const auto before=source.find(" week before ");
    const auto day=source.substr(4,of-4);
    const auto week=source.substr(of+4,before-of-4);
    std::string landmark;
    auto status=lookup(host,"world.landmark."+source.substr(before+13),landmark);
    if(status!=Status::ok) return status;
    status=lookup(host,week=="last"?"world.date.last":"world.date.number",result);
    if(status!=Status::ok) return status;
    replace(result,"{landmark}",landmark);
    replace(result,"{day}",day);
    if(week!="last") replace(result,"{week}",week.substr(0,week.size()-2));
    return Status::ok;
}
}

Status translate_world_hud(const HostApi* host,const TextRequest& request,void* output,u32* capacity) {
    const std::string source=request.original;
    std::string result;
    Status status;
    switch(request.component) {
    case TextComponent::world_place_gloss: {
        std::string translated;
        status=place_gloss(host,source.substr(1,source.size()-2),request.value,translated);
        result='"'+translated+'"';
        break;
    }
    case TextComponent::world_location: {
        const auto quote=source.find('"');
        const auto name_end=quote-1;
        const auto at=source.rfind(" at ",name_end);
        const auto name_begin=at==std::string::npos?0:at+4;
        std::string translated;
        status=place_gloss(host,source.substr(quote+1,source.size()-quote-2),
                           std::string_view(source).substr(name_begin,name_end-name_begin),translated);
        std::string prefix=source.substr(0,quote);
        if(at!=std::string::npos && status==Status::ok) {
            std::string relation;
            status=lookup(host,"world.location.at",relation);
            prefix=display_name(source.substr(0,at))+relation+display_name(source.substr(at+4,quote-at-4));
        } else {
            prefix=display_name(prefix);
        }
        result=prefix+'"'+translated+'"';
        break;
    }
    case TextComponent::world_region: status=region(host,source,result); break;
    case TextComponent::world_date: status=date(host,source,result); break;
    case TextComponent::world_scale: status=lookup(host,"world.scale."+source,result); break;
    case TextComponent::world_map_kind: status=lookup(host,"world.map."+source,result); break;
    case TextComponent::world_season: status=lookup(host,"world.season."+lower_initial(source),result); break;
    case TextComponent::world_month: status=month(host,source,result); break;
    case TextComponent::world_time: status=lookup(host,"world.time."+source,result); break;
    default: return Status::invalid;
    }
    return status==Status::ok?copy_text(result,output,capacity):status;
}
}

