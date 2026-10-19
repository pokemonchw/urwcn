// Linux 3.89 Choose_Name -> getst -> getkey -> key_event. See
// docs/evidence/20261019-linux-chinese-input.md for native instruction/ABI evidence.
bool name_input_active;
bool name_text_committed;

struct InputApi {
    int (*SetHint)(const char*,const char*);
    void (*StartTextInput)();
    void (*StopTextInput)();
    void (*SetTextInputRect)(const SDL_Rect*);
    void (*RenderGetLogicalSize)(SDL_Renderer*,int*,int*);
    int (*GetRendererOutputSize)(SDL_Renderer*,int*,int*);
    void (*RenderLogicalToWindow)(SDL_Renderer*,float,float,int*,int*);
} input_api;

void name_input(Frame&,Phase phase,CallState& state) {
    if(phase==Phase::before) {
        name_input_active=true;
        name_text_committed=false;
        input_api.StartTextInput();
        state.target=0x1402b0;
    } else {
        name_input_active=false;
        input_api.StopTextInput();
    }
}
void input_stop(Frame& frame) {
    if(!name_input_active) frame.rax=call(frame,0x87e0);
}
void input_commit(Frame& frame) {
    if(!name_input_active) { frame.rax=call(frame,0x87e0); return; }
    // key_event has already copied this SDL_TEXTINPUT into getkeystring.
    // -2 is getkey's native non-key return, bypassing processed_keysym.
    name_text_committed=true;
    frame.rax=std::uint32_t(-2);
    frame.resume=host->image_base+0xf6e3b;
}
void input_dispatch(Frame& frame) {
    // This boundary is after getst erased its old underscore cursor.
    // Native editing, return, random-name and redraw branches remain native.
    if(name_input_active && name_text_committed) {
        name_text_committed=false;
        const auto* text=at<unsigned char>(0x663ea60);
        if(text[0]=='*' && !text[1]) {
            frame.r12='*';
            frame.resume=host->image_base+0x1405e0;
            return;
        }
        auto* buffer=at<char>(0xa97e780);
        auto used=std::strlen(buffer);
        const auto capacity=*reinterpret_cast<const int*>(frame.stack()+0x1c);
        for(auto* cursor=text;*cursor;) {
            const unsigned bytes=*cursor<0x80 ? 1 : *cursor<0xe0 ? 2 : *cursor<0xf0 ? 3 : 4;
            // SDL_TEXTINPUT supplies complete UTF-8 scalars. The existing
            // getst byte budget also bounds the following Plr.name[13] copy.
            if(used+bytes>static_cast<unsigned>(capacity)) break;
            std::memcpy(buffer+used,cursor,bytes);
            used+=bytes;
            cursor+=bytes;
        }
        buffer[used]=0;
        frame.resume=host->image_base+0x140358;
        return;
    }
    // Covered CMP/JNE: implement its two successors, without synthesizing a key.
    frame.resume=host->image_base+(std::uint32_t(frame.r12)==8 ? 0x140409 : 0x1405e0);
}
void input_erase_width(Frame& frame) {
    if(name_input_active) {
        auto* rectangle=reinterpret_cast<render::Rect*>(frame.rsi);
        rectangle->w=width(at<char>(0xa97e780))+5; // Native getst's erase margin.
    }
    frame.rax=call(frame,0x8260);
}
void input_backspace(Frame& frame) {
    auto* text=reinterpret_cast<unsigned char*>(frame.rax);
    std::size_t last=frame.rdx-1;
    if(name_input_active) {
        std::size_t cursor=0;
        while(text[cursor]) {
            last=cursor;
            const auto bytes=utf8_span(text+cursor);
            cursor+=bytes ? bytes : 1; // Native single-byte defaults remain valid.
        }
    }
    text[last]=0;
}
void input_cursor(Frame& frame) {
    frame.rax=call(frame,0x13e8b0);
    if(!name_input_active) return;
    auto* renderer=*at<SDL_Renderer*>(0xa916ed0);
    int logical_w,logical_h;
    input_api.RenderGetLogicalSize(renderer,&logical_w,&logical_h);
    float sx=1,sy=1;
    if(!logical_w || !logical_h) {
        int output_w,output_h;
        input_api.GetRendererOutputSize(renderer,&output_w,&output_h);
        sx=float(output_w)/ *at<int>(0x26dc68);
        sy=float(output_h)/ *at<int>(0x26dc64);
    }
    // Borrow this native cursor call's coordinates; retain no UI geometry.
    const auto x=static_cast<int>(frame.rdi),y=static_cast<int>(frame.rsi);
    SDL_Rect rectangle;
    int right,bottom;
    input_api.RenderLogicalToWindow(renderer,x*sx,y*sy,&rectangle.x,&rectangle.y);
    input_api.RenderLogicalToWindow(renderer,(x+width("_"))*sx,(y+11)*sy,&right,&bottom);
    rectangle.w=right-rectangle.x;
    rectangle.h=bottom-rectangle.y;
    input_api.SetTextInputRect(&rectangle);
}
void input_display_copy(Frame& frame) {
    Frame arguments=frame;
    const auto display=native_display(reinterpret_cast<const char*>(frame.rsi));
    arguments.rsi=reinterpret_cast<std::uintptr_t>(display.c_str());
    frame.rax=call(arguments,0x8aa0);
}
void uppercase_utf8(Frame& frame) {
    const auto* character=reinterpret_cast<const unsigned char*>(frame.rbp+frame.rbx);
    if(const auto bytes=utf8_span(character)) {
        frame.rbx+=bytes;
        frame.resume=host->image_base+0xf91ac;
    } else frame.rdi=*character; // Covered MOVZX; native toupper follows.
}
void lowercase_utf8(Frame& frame) {
    frame.rbx+=frame.r12; // Covered ADD RBX,R12.
    const auto* character=reinterpret_cast<const unsigned char*>(frame.rbx);
    if(const auto bytes=utf8_span(character)) {
        frame.rbp=std::uint32_t(frame.rbp+bytes);
        frame.resume=host->image_base+0xf93ad;
    } else frame.rdi=*character; // Covered MOVZX; native tolower follows.
}
void name_save_encoding(Frame& frame) {
    const auto* text=reinterpret_cast<const unsigned char*>(frame.rdi);
    for(auto* cursor=text;*cursor;++cursor) {
        if(utf8_span(cursor)) {
            // This is Choose_Name's final path construction, after StrUpr.
            // UTF-8 fits the native 32-byte SaveFile copy; keep every character.
            frame.rax=frame.rdi;
            return;
        }
    }
    frame.rax=call(frame,0xf9250); // Original ASCII/legacy name path encoding.
}
void install_name_input() {
#define INPUT_BIND(name) input_api.name=reinterpret_cast<decltype(input_api.name)>(dlsym(RTLD_DEFAULT,"SDL_" #name))
    INPUT_BIND(SetHint); INPUT_BIND(StartTextInput); INPUT_BIND(StopTextInput); INPUT_BIND(SetTextInputRect);
    INPUT_BIND(RenderGetLogicalSize); INPUT_BIND(GetRendererOutputSize); INPUT_BIND(RenderLogicalToWindow);
#undef INPUT_BIND
    // The installed sdl2-compat uses SDL3's native IME UI setting.
    input_api.SetHint("SDL_IME_IMPLEMENTED_UI","none");
    hooks->around(0x1e1e4,name_input,false);
    hooks->instruction(0xf6e82,5,input_commit);
    hooks->instruction(0xf6cca,5,input_stop);
    hooks->instruction(0xf6f80,5,input_stop);
    hooks->instruction(0x1403ff,10,input_dispatch);
    hooks->instruction(0x1404db,5,input_backspace);
    for(auto site:{0x140481u,0x1406bau,0x140727u}) hooks->instruction(site,5,input_erase_width);
    hooks->instruction(0x14038b,5,input_cursor);
    hooks->instruction(0x13e8ef,5,input_display_copy);
    hooks->instruction(0x13e324,5,input_display_copy);
    hooks->instruction(0xf91f0,5,uppercase_utf8);
    hooks->instruction(0xf9378,6,lowercase_utf8);
    hooks->instruction(0x1e31d,5,name_save_encoding);
}
