// Native map legends, separate from GAME.NFO's encyclopedia consumers.
// These are text-call identities only; the game supplies all geometry,
// culture colors, shading, texture contents and resource lifetimes.
struct CultureMapLabel { u32 software_site,renderer_site; const char* topic; };
const CultureMapLabel culture_map_labels[]{
    {0x108995,0x10ac94,"kaumo"},
    {0x1089b9,0x10acb9,"kiesse"},
    {0x1089dd,0x10acde,"reemi"},
    {0x108a01,0x10ad1d,"koivula"},
    {0x108a25,0x10ad42,"sartola"},
    {0x108a49,0x10ad67,"driik"},
    {0x108a6d,0x10ad8c,"islanders"},
    {0x108a91,0x10adcb,"kuikka_tribe"},
    {0x108ab5,0x10adf0,"owl_tribe"},
    {0x108ad9,0x10ae2f,"seal_tribe"},
    {0x108b00,0x10ae54,"njerpez"}
};
void culture_map_label(Frame& frame) {
    const auto site=frame.resume-host->image_base-5;
    const CultureMapLabel* label=nullptr;
    for(const auto& entry:culture_map_labels)
        if(entry.software_site==site || entry.renderer_site==site) { label=&entry; break; }
    const bool renderer=site==label->renderer_site;
    Frame arguments=frame;
    std::string encoded;
    if(chinese) {
        encoded=culture_text(std::string("topic.")+label->topic+".title");
        argument(arguments,renderer?3:2)=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    frame.rax=call(arguments,renderer?0x13e2e0:0x13e8b0);
}
void culture_map_title(Frame& frame) {
    const bool renderer=frame.resume-host->image_base-5==0x10ac6d;
    Frame arguments=frame;
    std::string encoded;
    if(chinese) {
        encoded=culture_text(renderer?"map.title":"map.indicators_title");
        argument(arguments,renderer?5:4)=reinterpret_cast<std::uintptr_t>(encoded.c_str());
    }
    if(renderer) {
        // renderwinbox has eight SysV integer-class arguments. Its title
        // style 0x28 calls renderTekstiPalkki(type 1), a left-aligned native
        // renderer path; the byte-count centering branches are not used.
        using Native8=std::uintptr_t (*)(std::uintptr_t,std::uintptr_t,std::uintptr_t,std::uintptr_t,
                                        std::uintptr_t,std::uintptr_t,std::uintptr_t,std::uintptr_t);
        const auto* stack=reinterpret_cast<const std::uintptr_t*>(frame.stack());
        frame.rax=native<Native8>(0x147610)(arguments.rdi,arguments.rsi,arguments.rdx,arguments.rcx,
                                           arguments.r8,arguments.r9,stack[0],stack[1]);
    } else {
        frame.rax=call(arguments,0x1471a0,7,frame);
    }
}
void install_culture_map() {
    for(const auto& label:culture_map_labels) {
        hooks->instruction(label.software_site,5,culture_map_label);
        hooks->instruction(label.renderer_site,5,culture_map_label);
    }
    hooks->instruction(0x108972,5,culture_map_title);
    hooks->instruction(0x10ac6d,5,culture_map_title);
}
