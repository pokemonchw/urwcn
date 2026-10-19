// UTF-8 user names coexist with the game's single-byte text and the Mod's
// display-only tokens. Persistent names never contain those transient tokens.
unsigned utf8_span(const unsigned char* text) {
    const unsigned lead=*text;
    const unsigned bytes=lead>=0xc2 && lead<=0xdf ? 2 :
        lead>=0xe0 && lead<=0xef ? 3 : lead>=0xf0 && lead<=0xf4 ? 4 : 0;
    if(!bytes) return 0;
    for(unsigned i=1;i<bytes;++i)
        if((text[i]&0xc0)!=0x80) return 0;
    if((lead==0xe0 && text[1]<0xa0) || (lead==0xed && text[1]>=0xa0) ||
       (lead==0xf0 && text[1]<0x90) || (lead==0xf4 && text[1]>=0x90)) return 0;
    return bytes;
}
std::string native_display(const char* text) {
    std::string result;
    for(auto* cursor=reinterpret_cast<const unsigned char*>(text);*cursor;) {
        if(token(cursor)) {
            result.append(reinterpret_cast<const char*>(cursor),2);
            cursor+=2;
        } else if(const auto bytes=utf8_span(cursor)) {
            result+=encode(std::string(reinterpret_cast<const char*>(cursor),bytes));
            cursor+=bytes;
        } else result.push_back(*cursor++);
    }
    return result;
}
