// Windows native Choose_Name/encyclopedia getst, map text field and key_event boundaries. This file is
// included after codec()/metrics(); it owns no UI layout or drawing cache.
// Static instructions: docs/evidence/20261019-windows-chinese-input.md and
// docs/evidence/20261110-map-marker-chinese-input.md and
// docs/evidence/20261111-encyclopedia-chinese-search.md.
namespace native_name_input {
enum Hook : u32 {
    scope=0x5400,commit,stop_initial,stop_modifiers,edit_dispatch,backspace,
    erase_initial,erase_backspace,erase_random,cursor,uppercase,lowercase,path_capacity,
    showtext_copy,renshowtext_copy,renderer_showtext_copy,
    marker_edit=0x5410,marker_cursor,marker_finished,marker_extent
};
// active: 1 = Choose_Name/getst, 2 = map-marker ring editor, 3 = encyclopedia/getst.
struct State { u32 active{},committed{}; };
State state{};
bool getst_active() { return state.active==1 || state.active==3; }
struct Api {
    int (__cdecl *SetHint)(const char*,const char*);
    void (__cdecl *StartTextInput)();
    void (__cdecl *StopTextInput)();
    void (__cdecl *SetTextInputRect)(const render::Rect*);
    void (__cdecl *RenderGetLogicalSize)(render::Renderer*,int*,int*);
    int (__cdecl *GetRendererOutputSize)(render::Renderer*,int*,int*);
    void (__cdecl *RenderLogicalToWindow)(render::Renderer*,float,float,int*,int*);
} api{};

// Complete UTF-8 scalars and native single-byte Nordic letters coexist in
// persistent names. Transport pairs belong only to native display buffers.
unsigned span(const unsigned char* text) {
    const unsigned lead=*text;
    const unsigned bytes=lead>=0xc2 && lead<=0xdf ? 2 :
        lead>=0xe0 && lead<=0xef ? 3 : lead>=0xf0 && lead<=0xf4 ? 4 : 0;
    if(!bytes) return 0;
    for(unsigned i=1;i<bytes;++i) if((text[i]&0xc0)!=0x80) return 0;
    if((lead==0xe0 && text[1]<0xa0) || (lead==0xed && text[1]>=0xa0) ||
       (lead==0xf0 && text[1]<0x90) || (lead==0xf4 && text[1]>=0x90)) return 0;
    return bytes;
}
bool transport(const unsigned char* text) {
    return text[0]>=0x80 && text[0]<=0xbf && text[1]>=0x80 &&
        text[1]!=0xc4 && text[1]!=0xe4 && text[1]!=0xf6;
}
bool contains_utf8(const char* text) {
    for(auto* p=reinterpret_cast<const unsigned char*>(text);*p;++p)
        if(span(p)) return true;
    return false;
}
bool requires_unicode(const char* text) {
    for(auto* p=reinterpret_cast<const unsigned char*>(text);*p;) {
        const auto bytes=span(p);
        if(bytes>=3 || (bytes==2 && *p>=0xC4)) return true;
        p+=bytes ? bytes : 1;
    }
    return false;
}
bool contains_display(const char* text) {
    for(auto* p=reinterpret_cast<const unsigned char*>(text);*p;++p)
        if(transport(p) || span(p)) return true;
    return false;
}
u32 native_scalar(unsigned c) {
    // These three byte substitutions are the actual native wrappers' mapping.
    if(c==0x8e) return 0xc4;
    if(c==0x84) return 0xe4;
    if(c==0x94) return 0xf6;
    return c;
}
Status display(const char* input,std::vector<char>& output) {
    std::string result;
    for(auto* p=reinterpret_cast<const unsigned char*>(input);*p;) {
        if(transport(p)) { result.append(reinterpret_cast<const char*>(p),2); p+=2; continue; }
        const auto bytes=span(p);
        if(bytes || *p>=0x80) {
            std::string scalar;
            if(bytes) scalar.assign(reinterpret_cast<const char*>(p),bytes);
            else append_utf8(scalar,native_scalar(*p));
            std::vector<char> encoded;
            const auto status=codec(layout_op::encode_native,scalar.c_str(),encoded);
            if(status!=Status::ok) return status;
            result.append(encoded.data(),encoded.size()-1);
            p+=bytes ? bytes : 1;
        } else result.push_back(*p++);
    }
    output.assign(result.begin(),result.end());
    output.push_back('\0');
    return Status::ok;
}
struct UnicodeMeasure {
    bool entered;
    inline static u64 next_token=0xFFFFFFFA00000000ull;
    u64 token;
    explicit UnicodeMeasure(const char* input):entered(!chinese_enabled && contains_utf8(input)),token(++next_token) {
        if(entered) active.push_back({token,Scope::profile_identity_unicode,0,0,0,0,0});
    }
    ~UnicodeMeasure() {if(entered) end(token);}
};
Status measure(const char* input,render::Metrics& measured,u32 outline=outline_budget()) {
    const UnicodeMeasure unicode(input);
    std::vector<char> encoded;
    const auto status=display(input,encoded);
    return status==Status::ok ? metrics_at_outline(encoded.data(),outline,measured) : status;
}
Status initialize(HMODULE sdl) {
#define NAME_BIND(name) api.name=reinterpret_cast<decltype(api.name)>(GetProcAddress(sdl,"SDL_" #name)); if(!api.name) return Status::unavailable
    NAME_BIND(SetHint); NAME_BIND(StartTextInput); NAME_BIND(StopTextInput); NAME_BIND(SetTextInputRect);
    NAME_BIND(RenderGetLogicalSize); NAME_BIND(GetRendererOutputSize); NAME_BIND(RenderLogicalToWindow);
#undef NAME_BIND
    api.SetHint("SDL_IME_SHOW_UI","1");
    return Status::ok;
}
HookSpec instruction(u32 id,u32 site,std::initializer_list<unsigned char> bytes) {
    HookSpec result{id,HookKind::inline_code,site,0,0,static_cast<u32>(bytes.size()),{}};
    std::copy(bytes.begin(),bytes.end(),result.expected);
    return result;
}
HookSpec native_call(u32 id,u32 site,u32 target,u32 arguments) {
    HookSpec result{id,HookKind::call,site,target,arguments,5,{0xe8}};
    const auto relative=target-site-5;
    std::memcpy(result.expected+1,&relative,4);
    return result;
}
void append_hooks(std::vector<HookSpec>& hooks) {
    hooks.push_back(native_call(scope,0x119ab,0x10f5b0,0));
    // Relative branches are fully implemented by edit_dispatch, never replayed.
    hooks.push_back(instruction(edit_dispatch,0x10f77f,{0x83,0xfb,0x08,0x0f,0x85,0x86,0,0,0}));
    auto erased=instruction(backspace,0x10f7fb,{0x88,0x81,0,0,0,0});
    const auto buffer=address(at<char>(0xa49b9a8));
    std::memcpy(erased.expected+2,&buffer,4);
    hooks.push_back(erased);
    for(const auto field:{std::pair<u32,u32>{erase_initial,0x10f65c},
                         {erase_backspace,0x10f7a7},{erase_random,0x10f8f5}})
        hooks.push_back(instruction(field.first,field.second,{0x8d,0x04,0xcd,0x05,0,0,0}));
    hooks.push_back(native_call(cursor,0x10f6c6,0x10e5a0,3));
    for(const auto field:{std::pair<u32,u32>{commit,0xd1f81},
                         {stop_initial,0xd1c6e},{stop_modifiers,0xd1cf0}}) {
        auto stopped=instruction(field.first,field.second,{0xff,0x15,0,0,0,0});
        const auto slot=address(at<void*>(0x18c238));
        std::memcpy(stopped.expected+2,&slot,4);
        hooks.push_back(stopped);
    }
    auto upper=instruction(uppercase,0xd3e00,{0x0f,0xb6,0x86,0,0,0,0});
    const auto uppercase_buffer=address(at<char>(0x5f54bc0));
    std::memcpy(upper.expected+3,&uppercase_buffer,4);
    hooks.push_back(upper);
    // D408E follows the native tolower call and its argument cleanup, before
    // any byte is written back. These complete replay bytes do not change ESP.
    hooks.push_back(instruction(lowercase,0xd408e,{0x0f,0xb6,0xc1,0x05,0x7c,0xff,0xff,0xff}));
    // The one stacked native strncpy count survives StrUnicode's fastcall.
    hooks.push_back(native_call(path_capacity,0x11bc5,0xd3ef0,1));
    hooks.push_back(instruction(showtext_copy,0x10e5d2,{0x8d,0x8d,0xd0,0xfe,0xff,0xff}));
    hooks.push_back(instruction(renshowtext_copy,0x10e29d,{0x8d,0x8d,0xc8,0xfe,0xff,0xff}));
    hooks.push_back(instruction(renderer_showtext_copy,0x10e43d,{0x8d,0x8d,0xc8,0xfe,0xff,0xff}));
    if(windows_build::is_3891()) {
        // Implement both sides of the relative JNE; never replay the branch.
        hooks.push_back(instruction(marker_edit,0x10fb4d,{0x83,0xfb,8,0x75,0x1d}));
        hooks.push_back(native_call(marker_cursor,0x10fa7e,0x10e260,4));
        auto finished=instruction(marker_finished,0x10fc08,{0xff,0x15,0,0,0,0});
        const auto free_surface=address(at<void*>(0x18c1f4));
        std::memcpy(finished.expected+2,&free_surface,4);hooks.push_back(finished);
        hooks.push_back(instruction(marker_extent,0x10fa98,
            {0x8b,0x43,8,0x89,0x45,0xe4,0x8b,0x43,0x0c,0x89,0x45,0xe8}));
    }
}
Status candidate_rectangle(int x,int y,u32 outline) {
    auto* renderer=*at<render::Renderer*>(0xa2110cc);
    int logical_w,logical_h;
    api.RenderGetLogicalSize(renderer,&logical_w,&logical_h);
    float sx=1,sy=1;
    if(!logical_w || !logical_h) {
        int output_w,output_h;
        if(api.GetRendererOutputSize(renderer,&output_w,&output_h)!=0) return Status::failed;
        sx=float(output_w)/800;
        sy=float(output_h)/600;
    }
    render::Metrics underscore{};
    const auto status=measure("_",underscore,outline);
    if(status!=Status::ok) return status;
    render::Rect rectangle;
    int right,bottom;
    api.RenderLogicalToWindow(renderer,x*sx,y*sy,&rectangle.x,&rectangle.y);
    api.RenderLogicalToWindow(renderer,(x+underscore.logical_width)*sx,(y+11)*sy,&right,&bottom);
    rectangle.w=right-rectangle.x;
    rectangle.h=bottom-rectangle.y;
    api.SetTextInputRect(&rectangle);
    return Status::ok;
}
void activate_marker() {
    if(state.active==2) return;
    state={2,0};
    if(translation_available) api.StartTextInput();
}
void activate_keyword() {
    if(state.active==3) return;
    state={3,0};
    if(translation_available) api.StartTextInput();
}
void finish_keyword() {
    state={};
    if(translation_available) api.StopTextInput();
}
void append_committed(char* buffer,std::size_t capacity) {
    auto used=std::strlen(buffer);
    for(auto* p=at<unsigned char>(0x5f549b8);*p;) {
        // SDL_TEXTINPUT contains complete UTF-8 scalars. Keep the native
        // byte capacity, including when a candidate commits several scalars.
        const unsigned bytes=*p<0x80 ? 1 : *p<0xe0 ? 2 : *p<0xf0 ? 3 : 4;
        if(used+bytes>capacity) break;
        std::memcpy(buffer+used,p,bytes);
        used+=bytes;p+=bytes;
    }
    buffer[used]=0;
}
void erase_last(unsigned char* text) {
    std::size_t last=0;
    for(std::size_t cursor=0;text[cursor];) {
        last=cursor;
        const auto bytes=span(text+cursor);
        cursor+=bytes ? bytes : 1;
    }
    text[last]=0;
}
void set_translation_available(bool available) {
    state.committed=0;
    if(!state.active) return;
    if(available) api.StartTextInput();
    else api.StopTextInput();
}
Status dispatch(const NativeEvent& event,DispatchResult& result,bool& handled) {
    handled=true;
    switch(event.id) {
    case scope:
        if(event.phase==NativePhase::before) {
            state={1,0};
            if(translation_available) {
                begin(event,Scope::text);
                api.StartTextInput();
            }
        } else {
            state.active=0;
            if(translation_available) api.StopTextInput();
        }
        return Status::ok;
    case commit:
        if(translation_available && state.active) {
            // key_event has copied the true SDL_TEXTINPUT text to getkeystring.
            state.committed=1;
            result.resume_rva=0xd2083; // Native -2 return; getkey skips keysym.
        }
        return Status::ok;
    case stop_initial: case stop_modifiers:
        if(translation_available && state.active) result.resume_rva=event.id==stop_initial ? 0xd1c74 : 0xd1cf6;
        return Status::ok;
    case edit_dispatch:
        if(translation_available && getst_active() && state.committed) {
            state.committed=0;
            const auto* text=at<unsigned char>(0x5f549b8);
            if(text[0]=='*' && !text[1]) {
                event.frame->ebx='*';
                result.resume_rva=0x10f80e;
                return Status::ok;
            }
            const auto capacity=*ptr<u32>(event.frame->ebp-0xb4);
            append_committed(at<char>(0xa49b9a8),capacity);
            result.resume_rva=0x10f8b7; // Native color/coordinates and redraw.
        } else result.resume_rva=event.frame->ebx==8 ? 0x10f788 : 0x10f80e;
        return Status::ok;
    case backspace:
        if(translation_available && getst_active()) {
            erase_last(at<unsigned char>(0xa49b9a8));
            result.resume_rva=0x10f801;
        }
        return Status::ok;
    case erase_initial: case erase_backspace: case erase_random:
        if(translation_available && getst_active()) {
            render::Metrics measured{};
            const auto status=measure(at<char>(0xa49b9a8),measured);
            if(status!=Status::ok) return status;
            event.frame->eax=static_cast<u32>(measured.logical_width+5);
            result.resume_rva=event.id==erase_initial ? 0x10f663 :
                event.id==erase_backspace ? 0x10f7ae : 0x10f8fc;
        }
        return Status::ok;
    case cursor:
        return translation_available && getst_active() && event.phase==NativePhase::before ?
            candidate_rectangle(static_cast<int>(event.frame->ecx),static_cast<int>(event.frame->edx),outline_budget()) : Status::ok;
    case marker_edit:
        if(translation_available && state.active==2 && state.committed) {
            state.committed=0;
            append_committed(ptr<char>(event.frame->esi),64);
            result.resume_rva=0x10fa10;
        } else if(translation_available && state.active==2 && event.frame->ebx==8) {
            erase_last(ptr<unsigned char>(event.frame->esi));
            result.resume_rva=0x10fa10;
        } else result.resume_rva=event.frame->ebx==8 ? 0x10fb52 : 0x10fb6f;
        return Status::ok;
    case marker_cursor:
        if(translation_available && event.phase==NativePhase::before) {
            // 10FA8C..10FAA1 constructs the native output destination from
            // these same live locals. Translate its actual local cursor to
            // the main renderer only for the operating system's IME UI.
            const int x=*ptr<int>(event.frame->ebp-0x34)+static_cast<int>(event.frame->edx);
            const int y=*ptr<int>(event.frame->ebp-0x38)-2+static_cast<int>(event.arguments[0]);
            return candidate_rectangle(x,y,0);
        }
        return Status::ok;
    case marker_finished:
        state={};
        if(translation_available) api.StopTextInput();
        return Status::ok;
    case marker_extent: {
        const auto source=native_targets::component_surface_source(ptr<void>(event.frame->ebx));
        *ptr<int>(event.frame->ebp-0x1c)=source.width;
        *ptr<int>(event.frame->ebp-0x18)=source.height;
        event.frame->eax=static_cast<u32>(source.height);
        result.skip_original=1;
        return Status::ok;
    }
    case uppercase:
        if(const auto bytes=span(at<unsigned char>(0x5f54bc0)+event.frame->esi)) {
            event.frame->esi+=bytes-1;
            result.resume_rva=0xd3e41;
        }
        return Status::ok;
    case lowercase:
        if(const auto bytes=span(ptr<unsigned char>(event.frame->edi+event.frame->esi))) {
            event.frame->esi+=bytes-1;
            result.resume_rva=0xd40b8;
        }
        return Status::ok;
    case path_capacity:
        if(event.phase==NativePhase::before && contains_utf8(ptr<char>(event.frame->ecx)))
            event.arguments[0]=48; // 12 input bytes, each native 0xXX: 48 < 64.
        return Status::ok;
    case showtext_copy: case renshowtext_copy: case renderer_showtext_copy: {
        auto* text=ptr<char>(event.frame->ebp-(event.id==showtext_copy ? 0x130 : 0x138));
        if(contains_utf8(text)) {
            std::vector<char> encoded;
            const auto status=display(text,encoded);
            if(status!=Status::ok) return status;
            std::memcpy(text,encoded.data(),encoded.size());
        }
        return Status::ok;
    }
    default: handled=false; return Status::ok;
    }
}
State save() { return state; }
void restore(State saved) { state=saved; }
}
