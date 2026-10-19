// Linux 3.89 kartta_main / rndworld_screen / NaytaMittakaava.
// The original owners supply layout, button actions and all numeric values.
extern "C" void uwcn_linux_redraw_world_fragment(std::uintptr_t,unsigned);
extern "C" void uwcn_linux_redraw_world_return();

std::string world_generation_text(const char* key) {
    return translated(C::world_generation_text,"",key);
}
struct WorldGenerationBinding {
    u32 site,target;
    const char* key;
    unsigned argument,arguments=6;
    bool key_suffix=false;
};
const WorldGenerationBinding world_generation_bindings[]{
    {0x7e856,0x1471a0,"title",4,7},
    {0x7bc27,0x13e8b0,"scale",2},
    {0x7ed4f,0xf4f50,"zoom_in",3,6,true},
    {0x7ed6a,0xf4f50,"zoom_out",3,6,true},
    {0x7ee55,0xf4f50,"regions",3,6,true},
    {0x7ee70,0xf4f50,"indicators",3,6,true},
    {0x7ee8b,0xf4f50,"home_culture",3,6,true},
    {0x7eea6,0xf4f50,"start_location",3,6,true},
    {0x7eec1,0xf4f50,"new_world",3,6,true},
    {0x7eedc,0xf4f50,"enter",3,6,true},
};

// These scalars describe the current native rebuild, never page contents.
// A newly loaded adapter refreshes at the next native control-building pass.
bool world_generation_refresh=true;
bool world_generation_chinese;
bool rebuilding_world_generation;
bool world_generation_restore_selection;
int world_generation_selection;

void world_generation_list_style(Frame& frame) {
    frame.rax=call(frame,0xf4a40);
    world_generation_refresh=false;
    world_generation_chinese=chinese;
    if(rebuilding_world_generation)
        frame.resume=reinterpret_cast<std::uintptr_t>(uwcn_linux_redraw_world_return);
}
void world_generation_map_flip(Frame& frame) {
    frame.rax=call(frame,0x13fe50);
    if(rebuilding_world_generation)
        frame.resume=reinterpret_cast<std::uintptr_t>(uwcn_linux_redraw_world_return);
}
void world_generation_controls_begin(Frame& frame) {
    if(world_generation_refresh || world_generation_chinese!=chinese) {
        world_generation_selection=native<int (*)()>(0xf6100)();
        rebuilding_world_generation=true;
        native<void (*)()>(0x7e7f0)();
        // 7ED00..7ED30 redraws the current map and optional culture legend.
        // R15 is kartta_main's native legend-toggle value at this boundary.
        uwcn_linux_redraw_world_fragment(host->image_base+0x7ed00,frame.r15);
        // 7EC18..7EC61 repeats only the original list reset and style.
        // Subsequent original button calls rebuild their own hit geometry.
        uwcn_linux_redraw_world_fragment(host->image_base+0x7ec18,0);
        rebuilding_world_generation=false;
        world_generation_restore_selection=true;
    }
}
void world_generation_bound(Frame& frame) {
    const auto site=frame.resume-host->image_base-5;
    if(site==0x7ed4f) world_generation_controls_begin(frame);
    const WorldGenerationBinding* binding=nullptr;
    for(const auto& entry:world_generation_bindings) if(entry.site==site) { binding=&entry; break; }
    Frame arguments=frame;
    std::string display;
    if(chinese) {
        display=world_generation_text(binding->key);
        if(binding->key_suffix) {
            const auto* original=reinterpret_cast<const char*>(argument(frame,binding->argument));
            display=std::string(original,std::strchr(original,'.')-original+1)+display;
        }
        argument(arguments,binding->argument)=reinterpret_cast<std::uintptr_t>(display.c_str());
    }
    frame.rax=call(arguments,binding->target,binding->arguments,frame);
    if(site==0x7eedc && world_generation_restore_selection) {
        native<void (*)(int)>(0xf6110)(world_generation_selection);
        world_generation_restore_selection=false;
    }
}
void world_generation_format(Frame& frame) {
    const auto* original=reinterpret_cast<const char*>(frame.rcx);
    const auto display=chinese ? world_generation_text(
        frame.resume-host->image_base-5==0x7bbb1 ? "zoom_format" : "distance_format") : std::string(original);
    // Keep NaytaMittakaava's original 100-byte output and its computed R8D.
    using Format=int (*)(char*,int,std::size_t,const char*,...);
    frame.rax=native<Format>(0x8f80)(reinterpret_cast<char*>(frame.rdi),frame.rsi,frame.rdx,
                                   display.c_str(),static_cast<int>(frame.r8));
}
void install_world_generation() {
    for(const auto& binding:world_generation_bindings) hooks->instruction(binding.site,5,world_generation_bound);
    for(auto site:{0x7bbb1u,0x7bc69u}) hooks->instruction(site,5,world_generation_format);
    hooks->instruction(0x7ec5c,5,world_generation_list_style);
    hooks->instruction(0x7ed2b,5,world_generation_map_flip);
}
