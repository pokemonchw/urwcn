// Native renderer text construction and metrics. All positions, wrapping,
// hit records, tile counts and targets remain owned by the original functions.
namespace windows_renderer_text {
enum Hook : u32 {
    paragraph_fit=0x7c00,paragraph_measure_advance,paragraph_draw_advance,paragraph_space,
    centered_heading,panel_title,panel_title_inset,marked_tiles,marked_advance,
    hit_prefix,hit_complete,
    renderer_leaf_first=0x7c20
};
Status measure(const char* encoded,void* renderer,u32 outline,render::Metrics& measured) {
    std::vector<char> utf8;
    auto status=codec(layout_op::decode_native,encoded,utf8);
    if(status!=Status::ok) return status;
    const render::TextRequest request{utf8.data(),nullptr,renderer,0,0,0,10,9,0,0,outline,0,0};
    u32 bytes=sizeof(measured);
    return host->invoke(ModuleId::render,render::op::measure_renderer,
        &request,sizeof(request),&measured,&bytes);
}
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    using native_name_input::native_call;
    hooks.push_back(instruction(paragraph_fit,0x10f409,{0x8d,0x0c,0xd8,0x8b,0x45,0x0c}));
    hooks.push_back(instruction(paragraph_measure_advance,0x10f4fe,
        {0x8d,0x04,0xd8,0x8b,0x9d,0xdc,0xf3,0xff,0xff}));
    hooks.push_back(instruction(paragraph_draw_advance,0x10f551,
        {0x8d,0x1c,0xcb,0x89,0x9d,0xf0,0xf3,0xff,0xff}));
    auto space=instruction(paragraph_space,0x10f47c,{0x66,0xa1,0,0,0,0,0x66,0x89,0x07});
    const auto native_space=address(at<char>(0x18c8c0));
    std::memcpy(space.expected+2,&native_space,4);
    hooks.push_back(space);
    hooks.push_back(instruction(centered_heading,0x113507,
        {0x8b,0x4d,0xe4,0x2b,0xc2,0xc1,0xe0,0x03}));
    hooks.push_back(instruction(panel_title,0x115b59,{0x8d,0x04,0xcd,0,0,0,0}));
    hooks.push_back(instruction(panel_title_inset,0x115d09,{0x8d,0x04,0xcd,0,0,0,0}));
    hooks.push_back(instruction(marked_tiles,0x114f67,{0x8b,0x45,0x08,0x2b,0xfa}));
    hooks.push_back(instruction(marked_advance,0x11511d,
        {0x8d,0x1c,0xcb,0x89,0x9d,0xcc,0xf3,0xff,0xff}));
    hooks.push_back(instruction(hit_prefix,0xcfeaa,{0x8d,0x04,0xcd,0x0a,0,0,0}));
    hooks.push_back(instruction(hit_complete,0xcfecb,{0x8d,0x04,0xcd,0x0a,0,0,0}));
    constexpr u32 renderer_leaves[]{0x10e4bb,0x10e4d1,0x10e4e5,0x10e4f9,0x10e50e};
    for(u32 i=0;i<std::size(renderer_leaves);++i)
        hooks.push_back(native_call(renderer_leaf_first+i,renderer_leaves[i],0x10e170,3));
}
Status draw_main_renderer(const NativeEvent& event) {
    // 10E170 receives x in EDX, then y/text/packed RGB on the stack. Unlike
    // 10DE90, it borrows the actual main renderer from the native owner slot.
    const std::string original=ptr<char>(event.arguments[1]);
    const auto line=original.substr(0,original.find('\n'));
    std::vector<char> utf8;
    auto status=codec(layout_op::decode_native,line.c_str(),utf8);
    if(status!=Status::ok) return status;
    const render::TextRequest request{utf8.data(),nullptr,*at<void*>(0xa2110cc),
        static_cast<std::int32_t>(event.frame->edx),static_cast<std::int32_t>(event.arguments[0]),
        event.arguments[2]|0xff000000u,10,9,0,0,1,0,0};
    render::Metrics measured{};
    u32 bytes=sizeof(measured);
    return host->invoke(ModuleId::render,render::op::draw_renderer,
        &request,sizeof(request),&measured,&bytes);
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=true;
    if(event.id>=renderer_leaf_first && event.id<renderer_leaf_first+5) {
        if(event.phase==NativePhase::before &&
           native_name_input::contains_display(ptr<char>(event.arguments[1]))) {
            const auto status=draw_main_renderer(event);
            if(status!=Status::ok) return status;
            result.skip_original=1;
        }
        return Status::ok;
    }
    const char* text;
    void* renderer;
    u32 outline=0;
    u32 native_prefix=0;
    switch(event.id) {
    case paragraph_fit:
    case paragraph_measure_advance:
    case paragraph_draw_advance:
    case paragraph_space:
        text=ptr<char>(event.frame->ebp-(event.id==paragraph_fit ? 0x40c :
            event.id==paragraph_space ? 0xc0c : 0x80c));
        renderer=*ptr<void*>(event.frame->ebp-0xc30);
        outline=*ptr<u32>(event.frame->ebp+0x18)&1;
        break;
    case centered_heading:
        text=ptr<char>(event.frame->edi);
        renderer=*ptr<void*>(event.frame->ebp-0x1c);
        outline=1;
        break;
    case panel_title: case panel_title_inset:
        text=ptr<char>(event.frame->ebx);
        renderer=*ptr<void*>(event.frame->ebp-4);
        outline=1;
        break;
    case marked_tiles: case marked_advance:
        text=ptr<char>(event.frame->ebp-0x808);
        renderer=*ptr<void*>(event.frame->ebp-0xc2c);
        outline=*ptr<u32>(event.frame->ebp+0x14)&1;
        break;
    case hit_prefix: case hit_complete:
        text=event.id==hit_prefix ? ptr<char>(event.frame->ebp-0x40c) : ptr<char>(event.frame->edi);
        if(event.id==hit_complete) {
            if(const auto* separator=std::strchr(text,'.')) {
                native_prefix=static_cast<u32>(separator+1-text)*8;
                text=separator+1;
            }
        }
        renderer=*at<void*>(0xa2110cc);
        outline=*at<u32>(0x5f54ba0)&1;
        break;
    default: handled=false; return Status::ok;
    }
    if(!native_name_input::contains_display(text)) return Status::ok;
    if(event.id==paragraph_space) {
        // The tokenizer inserts a separating space between complete Chinese
        // units. It is not an additional visible Western word space.
        if(native_name_input::transport(reinterpret_cast<const unsigned char*>(text)))
            result.resume_rva=0x10f485;
        return Status::ok;
    }
    render::Metrics measured{};
    const auto status=measure(text,renderer,outline,measured);
    if(status!=Status::ok) return status;
    const auto width=static_cast<u32>(measured.logical_width);
    switch(event.id) {
    case paragraph_fit:
        event.frame->ecx=event.frame->eax+width;
        event.frame->eax=*ptr<u32>(event.frame->ebp+0xc);
        result.resume_rva=0x10f40f;
        break;
    case paragraph_measure_advance:
        event.frame->eax+=width;
        event.frame->ebx=*ptr<u32>(event.frame->ebp-0xc24);
        result.resume_rva=0x10f507;
        break;
    case paragraph_draw_advance:
        event.frame->ebx+=width;
        *ptr<u32>(event.frame->ebp-0xc10)=event.frame->ebx;
        result.resume_rva=0x10f55a;
        break;
    case centered_heading:
        event.frame->ecx=address(renderer);
        event.frame->eax=width;
        result.resume_rva=0x11350f;
        break;
    case panel_title: case panel_title_inset:
        event.frame->eax=width;
        result.resume_rva=event.id==panel_title ? 0x115b60 : 0x115d10;
        break;
    case marked_tiles:
        event.frame->eax=*ptr<u32>(event.frame->ebp+8);
        event.frame->edi=(width+7)/8;
        result.resume_rva=0x114f6c;
        break;
    case marked_advance:
        event.frame->ebx+=width;
        *ptr<u32>(event.frame->ebp-0xc34)=event.frame->ebx;
        result.resume_rva=0x115126;
        break;
    case hit_prefix: case hit_complete:
        event.frame->eax=native_prefix+width+10;
        result.resume_rva=event.id==hit_prefix ? 0xcfeb1 : 0xcfed2;
        break;
    default: break;
    }
    return Status::ok;
}
}
