#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace uwcn {
// Strict scalar decoding. Invalid input is rejected at the service boundary.
inline bool decode_utf8(const char* text,std::size_t size,std::vector<std::uint32_t>& result) {
    result.clear();
    for (std::size_t i=0;i<size;) {
        const auto lead=static_cast<unsigned char>(text[i++]);
        std::uint32_t scalar=0, minimum=0;
        unsigned continuation=0;
        if (lead<0x80) scalar=lead;
        else if (lead>=0xc2 && lead<=0xdf) { scalar=lead&0x1f;continuation=1;minimum=0x80; }
        else if (lead>=0xe0 && lead<=0xef) { scalar=lead&0xf;continuation=2;minimum=0x800; }
        else if (lead>=0xf0 && lead<=0xf4) { scalar=lead&7;continuation=3;minimum=0x10000; }
        else return false;
        if (i+continuation>size) return false;
        for(unsigned n=0;n<continuation;++n) {
            const auto next=static_cast<unsigned char>(text[i++]);
            if ((next&0xc0)!=0x80) return false;
            scalar=(scalar<<6)|(next&0x3f);
        }
        if (scalar<minimum || scalar>0x10ffff || (scalar>=0xd800 && scalar<=0xdfff)) return false;
        result.push_back(scalar);
    }
    return true;
}
inline void append_utf8(std::string& text,std::uint32_t c) {
    if(c<0x80) text.push_back(static_cast<char>(c));
    else if(c<0x800) {
        text.push_back(static_cast<char>(0xc0|(c>>6)));
        text.push_back(static_cast<char>(0x80|(c&0x3f)));
    } else if(c<0x10000) {
        text.push_back(static_cast<char>(0xe0|(c>>12)));
        text.push_back(static_cast<char>(0x80|((c>>6)&0x3f)));
        text.push_back(static_cast<char>(0x80|(c&0x3f)));
    } else {
        text.push_back(static_cast<char>(0xf0|(c>>18)));
        text.push_back(static_cast<char>(0x80|((c>>12)&0x3f)));
        text.push_back(static_cast<char>(0x80|((c>>6)&0x3f)));
        text.push_back(static_cast<char>(0x80|(c&0x3f)));
    }
}
}
