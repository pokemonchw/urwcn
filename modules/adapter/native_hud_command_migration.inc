// Read the target component's original accepted title from its live native
// producer. No page, geometry, pixels or historical text replay is retained.
// HDA8 does not migrate unrecorded Command inputs from older state ABIs.
namespace native_hud_command_migration {
const char* operand(u32 rva) {return ptr<const char>(*at<const u32>(rva));}

// F7820 establishes EBP before aligning its local stack. Every direct caller
// is closed against the executable's E8 target census, including 5238 (which
// a linear disassembly misses after the preceding switch data).
// Precondition: the real F7820 mode's bit 0 is clear. With bit 0 set F78C4
// chooses its own fixed heading and never consumes the caller's title input.
const char* target_title(const NativeEvent& event) {
    const auto page=event.frame->ebp;
    const auto caller=*ptr<const u32>(page+4)-static_cast<u32>(host->image_base);
    const auto parent=*ptr<const u32>(page);
    if(caller==0xF880D) return ptr<const char>(*ptr<const u32>(parent-0x30));
    if(caller==0xF8B56) return ptr<const char>(*ptr<const u32>(parent-0x4C));
    if(caller==0xF8BCA) {
        // F8BC0 only PUSHes ESI before calling F7820; its own accepted ECX
        // comes from one of two original MOV ECX,imm32 callers.
        const auto wrapper_caller=*ptr<const u32>(page+12)-static_cast<u32>(host->image_base);
        return operand(wrapper_caller==0x59CC ? 0x59C3 : 0x16627D);
    }
    struct Producer {u32 caller,operand;};
    static constexpr Producer producers[]{
        {0x469F,0x4694},{0x523D,0x5232},{0x58F0,0x58E5},{0x599B,0x5990},
        {0x6342,0x6337},{0x316AE,0x316A3},{0x3B55B,0x3B550},
        {0x46070,0x46065},{0x4CF9B,0x4CF90},{0x4D1C4,0x4D1B9},
        {0x58F70,0x58F65},{0x101D6C,0x101D61},
        {0x118443,0x118438},{0x1188C1,0x1188B6},{0x1195A1,0x119596},
        {0x11984E,0x119843},{0x11A32F,0x11A324},{0x11A50E,0x11A503},
        {0x11A72F,0x11A724},{0x11A94A,0x11A93F},{0x11BD27,0x11BD1C},
        {0x11C196,0x11C18B},{0x11FA7A,0x11FA6F},{0x11FD64,0x11FD59},
        {0x1322E5,0x1322DA},{0x132552,0x132547},{0x166C24,0x166C19},
        {0x166FBF,0x166FB4},{0x170D7C,0x170D6D},{0x17DB9B,0x17DB90},
        // All three mode-4 debug producers explicitly accept an empty title.
        {0x175145,0x17513A},{0x175172,0x175167},{0x17B35A,0x17B34F}
    };
    const auto& source=*std::find_if(std::begin(producers),std::end(producers),
        [caller](const auto& value){return value.caller==caller;});
    return operand(source.operand);
}

}
