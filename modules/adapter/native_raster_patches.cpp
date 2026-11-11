#include "native_raster_patches.h"
#include "native_raster.h"
#include <cstring>

// Fixed image inspected with local objdump and PE raw-byte reads, 2026-10-19:
// urw.exe SHA256 e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9.
// All addresses below are RVAs, preferred image base 00400000. The installer
// compares complete instructions, including relocated absolute operands.
// Compiled helpers and their integer division dependencies still require the
// parent's static no-FP instruction inspection before this module is enabled.
#define URWCN_NR_INTEGER __attribute__((target("no-sse,no-sse2,no-mmx")))
#define URWCN_NR_HELPER URWCN_NR_INTEGER __attribute__((used,noinline))
#define URWCN_NR_ENTRY __attribute__((naked,used))

namespace urwcn::adapter::native_raster {
namespace {
// Raw PUSHFD/PUSHAD stack, intentionally separate from normalized Host frames.
// saved_esp is the value after PUSHFD; original native ESP is saved_esp + 4.
struct Registers {
    u32 edi,esi,ebp,saved_esp,ebx,edx,ecx,eax,eflags;
};
struct Bindings {
    render::Surface** main_surface;
    const render::Rect* message_rectangle;
    const std::uint8_t* glyph_masks;
    const u32* foreground;
    int (__cdecl *lock)(render::Surface*);
    void (__cdecl *unlock)(render::Surface*);
};
Bindings bindings{};

URWCN_NR_INTEGER Target current_target() {
    return {*bindings.main_surface,800,600};
}
URWCN_NR_INTEGER Target register_target(u32 surface) {
    return {reinterpret_cast<render::Surface*>(surface),800,600};
}
URWCN_NR_INTEGER bool logical_point(int x,int y) {
    return x>=0 && x<800 && y>=0 && y<600;
}
URWCN_NR_INTEGER const u32* native_stack(const Registers* registers) {
    return reinterpret_cast<const u32*>(registers->saved_esp+4);
}
URWCN_NR_INTEGER int gradient_edge(int coordinate,int physical,int logical) {
    return static_cast<int>((std::int64_t(coordinate)*physical+logical/2)/logical);
}
URWCN_NR_INTEGER int gradient_last(int coordinate,int physical,int logical) {
    // The original gradient includes its last logical row/column. Extend its
    // complete half-open physical cell, using the native canvas edge rule.
    return gradient_edge(coordinate+1,physical,logical)-1;
}
URWCN_NR_INTEGER Target lock_target() {
    Target target=current_target();
    // Original 10BAD8/10BCC4/10BE07 check bit 2 and ignore the lock result.
    if(target.surface->flags&2u) {
        bindings.lock(target.surface);
        target=current_target(); // Original routines reload the native owner.
    }
    return target;
}
URWCN_NR_INTEGER void unlock_target(Target target) {
    // Preserve the original post-write/read flags check, not a guessed flag.
    if(target.surface->flags&2u) bindings.unlock(target.surface);
}
}

extern "C" {
std::uintptr_t urwcn_nr_resume_606c3{};
std::uintptr_t urwcn_nr_resume_607e4{};
std::uintptr_t urwcn_nr_resume_11454f{};
std::uintptr_t urwcn_nr_resume_d7aa9{};
std::uintptr_t urwcn_nr_resume_fc98f{};
render::Surface** urwcn_nr_main_surface{};
std::uintptr_t urwcn_nr_gradient_rows{},urwcn_nr_gradient_end{};
std::uintptr_t urwcn_nr_gradient_columns{},urwcn_nr_gradient_next_row{};
std::uintptr_t urwcn_nr_resume_gradient_row{},urwcn_nr_resume_gradient_shade{};
std::uintptr_t urwcn_nr_resume_gradient_read_x{},urwcn_nr_resume_gradient_read_y{};
std::uintptr_t urwcn_nr_resume_gradient_write_x{},urwcn_nr_resume_gradient_write_y{};

// Whole native functions: ECX/EDX are coordinates, stack arguments remain
// caller-cleaned. Pixel/line/glyph have no consumed return value. Read returns
// its packed pixel in EAX (10BD00); all nonvolatile registers remain intact.
URWCN_NR_HELPER void __cdecl urwcn_nr_pixel(Registers* registers) {
    const int x=static_cast<int>(registers->ecx);
    const int y=static_cast<int>(registers->edx);
    if(!logical_point(x,y)) return;
    const Target target=lock_target();
    pixel(target,x,y,native_stack(registers)[1]);
    unlock_target(target);
}
URWCN_NR_HELPER void __cdecl urwcn_nr_read(Registers* registers) {
    const int x=static_cast<int>(registers->ecx);
    const int y=static_cast<int>(registers->edx);
    if(!logical_point(x,y)) {
        registers->eax=0; // 10BCA8..10BCAC native rejection result.
        return;
    }
    const Target target=lock_target();
    registers->eax=read_pixel(target,x,y);
    unlock_target(target);
}
URWCN_NR_HELPER void __cdecl urwcn_nr_line(Registers* registers) {
    const auto* stack=native_stack(registers);
    const int x1=static_cast<int>(registers->ecx);
    const int y1=static_cast<int>(registers->edx);
    const int x2=static_cast<int>(stack[1]);
    const int y2=static_cast<int>(stack[2]);
    if(!logical_point(x1,y1) || !logical_point(x2,y2)) return;
    const Target target=lock_target();
    line(target,x1,y1,x2,y2,stack[3]);
    unlock_target(target);
}
URWCN_NR_HELPER void __cdecl urwcn_nr_glyph(Registers* registers) {
    const int x=static_cast<int>(registers->ecx);
    const int y=static_cast<int>(registers->edx);
    const auto code=static_cast<std::uint8_t>(native_stack(registers)[1]);
    const auto* mask=bindings.glyph_masks+u32(code)*80;
    // The original calls SDL only for an in-bounds byte exactly equal to 1.
    // Find whether this one native glyph draws, then lock the batch once.
    bool visible=false;
    for(int gy=0;gy<10 && !visible;++gy) {
        for(int gx=0;gx<8;++gx) {
            if(mask[gy*8+gx]==1 && logical_point(x+gx,y+gy)) {
                visible=true;
                break;
            }
        }
    }
    if(!visible) return;
    const u32 packed=*bindings.foreground;
    const Target target=lock_target();
    glyph(target,x,y,mask,packed);
    unlock_target(target);
}

// Inline helpers run between the game's own lock and unlock. They call only
// the pure integer kernels, never SDL, Host dispatch, font services or logging.
URWCN_NR_HELPER void __cdecl urwcn_nr_write_606c3(Registers* registers) {
    // 606BB consumes logical y; 606BE replaces ECX with pixels. The loop keeps
    // y in [EBP-8], explicitly reloaded at 606AC after SDL_LockSurface.
    const int y=*reinterpret_cast<const int*>(registers->ebp-8);
    pixel(register_target(registers->esi),static_cast<int>(registers->edi),y,0);
}
URWCN_NR_HELPER void __cdecl urwcn_nr_write_607e4(Registers* registers) {
    const Target target=current_target();
    pixel(target,static_cast<int>(registers->esi),static_cast<int>(registers->edi),registers->ecx);
    // Replay the covered MOV ECX,[image+61BBB10], which changes no flags.
    registers->ecx=reinterpret_cast<u32>(target.surface);
}
URWCN_NR_HELPER void __cdecl urwcn_nr_write_11454f(Registers* registers) {
    pixel(register_target(registers->esi),static_cast<int>(registers->ebx),
          static_cast<int>(registers->edi),registers->edx);
}
URWCN_NR_HELPER void __cdecl urwcn_nr_read_d7aa9(Registers* registers) {
    // Native address is pixels + (pitch/4)*400 + 0xA70, without another *4.
    // It samples (668,100), not row 400. The prior TEST flags feed D7AB0 JZ.
    registers->edi=read_pixel(register_target(registers->esi),668,100);
}
URWCN_NR_HELPER void __cdecl urwcn_nr_read_fc98f(Registers* registers) {
    // pixels + (pitch/4)*364 + 0xA70 samples (668,91); flags feed FC996 JZ.
    registers->edi=read_pixel(register_target(registers->esi),668,91);
}
// These helpers only extend the actual F6510 gradient's loop operands. The
// original F68D5 read, color comparisons, F69C7 write and SDL lock/unlock run
// unchanged, once per physical pixel. No Mod pixel scan or retained draw data.
URWCN_NR_HELPER void __cdecl urwcn_nr_gradient_begin(Registers* registers) {
    const auto* surface=*bindings.main_surface;
    registers->ebx=gradient_edge(static_cast<int>(registers->ebx),surface->h,600);
    registers->eax=gradient_last(static_cast<int>(registers->eax),surface->h,600);
}
URWCN_NR_HELPER void __cdecl urwcn_nr_gradient_row(Registers* registers) {
    const auto* surface=*bindings.main_surface;
    registers->edi=gradient_edge(static_cast<int>(registers->edx)+5,surface->w,800);
    registers->eax=gradient_last(static_cast<int>(registers->eax+registers->edx),surface->w,800);
}
URWCN_NR_HELPER void __cdecl urwcn_nr_gradient_shade(Registers* registers) {
    const auto* surface=*bindings.main_surface;
    // Invert rounded physical cell edges. F684A..F6869 still calculate and
    // clamp the original logical-row tint, even at a fractional output scale.
    const auto logical_y=static_cast<int>(((std::uint64_t(registers->ebx)*2+1)*600-1)/
                                        (std::uint64_t(surface->h)*2));
    registers->eax=logical_y-bindings.message_rectangle->y-4;
}
URWCN_NR_HELPER void __cdecl urwcn_nr_gradient_column_end(Registers* registers) {
    registers->eax=gradient_last(static_cast<int>(registers->eax),(*bindings.main_surface)->w,800);
}
URWCN_NR_HELPER void __cdecl urwcn_nr_gradient_row_end(Registers* registers) {
    registers->eax=gradient_last(static_cast<int>(registers->eax),(*bindings.main_surface)->h,600);
}
}

// Basic asm only in naked entries. The C++ helper sees the original registers
// by value on the stack; EBX keeps that stack address across its cdecl call.
// ESP is 16-byte aligned immediately before CALL. No FP/SIMD state is touched
// by these entries. POPFD preserves flags even where a native JZ follows MOV.
#define URWCN_NR_ENTER(helper) \
    "pushfl\n\tpushal\n\tmovl %esp,%ebx\n\t" \
    "andl $-16,%esp\n\tsubl $12,%esp\n\tpushl %ebx\n\t" \
    "call _" #helper "\n\tmovl %ebx,%esp\n\tpopal\n\tpopfl\n\t"

extern "C" {
URWCN_NR_ENTRY void urwcn_nr_entry_pixel() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_pixel) "ret\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_read() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_read) "ret\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_line() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_line) "ret\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_glyph() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_glyph) "ret\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_606c3() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_write_606c3)
                         "jmp *_urwcn_nr_resume_606c3\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_607e4() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_write_607e4)
                         "jmp *_urwcn_nr_resume_607e4\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_11454f() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_write_11454f)
                         // Covered TEST must produce the flags for 114555 JZ.
                         "testb $2,(%esi)\n\tjmp *_urwcn_nr_resume_11454f\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_d7aa9() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_read_d7aa9)
                         "jmp *_urwcn_nr_resume_d7aa9\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_fc98f() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_read_fc98f)
                         "jmp *_urwcn_nr_resume_fc98f\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_gradient_begin() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_gradient_begin)
                         "cmpl %eax,%ebx\n\tja 1f\n\t"
                         "jmp *_urwcn_nr_gradient_rows\n\t"
                         "1: jmp *_urwcn_nr_gradient_end\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_gradient_row() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_gradient_row)
                         "jmp *_urwcn_nr_resume_gradient_row\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_gradient_shade() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_gradient_shade)
                         "cltd\n\tjmp *_urwcn_nr_resume_gradient_shade\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_gradient_column_end() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_gradient_column_end)
                         "cmpl %eax,%edi\n\tjbe 1f\n\t"
                         "jmp *_urwcn_nr_gradient_next_row\n\t"
                         "1: jmp *_urwcn_nr_gradient_columns\n\t");
}
URWCN_NR_ENTRY void urwcn_nr_entry_gradient_row_end() {
    __asm__ __volatile__(URWCN_NR_ENTER(urwcn_nr_gradient_row_end)
                         "cmpl %eax,%ebx\n\tjbe 1f\n\t"
                         "jmp *_urwcn_nr_gradient_end\n\t"
                         "1: jmp *_urwcn_nr_gradient_rows\n\t");
}
}

// The four original signed bounds checks use this same native surface's
// physical dimensions. PUSH/POP preserve EAX and the CMP flags reach the
// original JL/JGE. The original negative-coordinate checks remain in place.
#define URWCN_NR_GRADIENT_BOUND(name,offset,coordinate) \
    extern "C" URWCN_NR_ENTRY void urwcn_nr_entry_gradient_##name() { \
        __asm__ __volatile__( \
            "pushl %eax\n\tmovl _urwcn_nr_main_surface,%eax\n\t" \
            "movl (%eax),%eax\n\tcmpl " #offset "(%eax),%" #coordinate "\n\t" \
            "popl %eax\n\tjmp *_urwcn_nr_resume_gradient_" #name "\n\t"); \
    }
URWCN_NR_GRADIENT_BOUND(read_x,8,edi)
URWCN_NR_GRADIENT_BOUND(read_y,12,ebx)
URWCN_NR_GRADIENT_BOUND(write_x,8,edi)
URWCN_NR_GRADIENT_BOUND(write_y,12,ebx)
#undef URWCN_NR_GRADIENT_BOUND

namespace {
struct Patch {
    u32 rva;
    std::uint8_t size,absolute_operand;
    void (*entry)();
    std::uint8_t raw[9];
    std::uint8_t original[9]{};
    std::uint8_t replacement[9]{};
    DWORD old_protection{};
};
// Whole functions replace the entire function, so their covered prologue is
// restored on removal but never replayed by a replacement entry.
Patch patches[]={
    {0x10BAB0,6,0,urwcn_nr_entry_pixel,{0x55,0x8B,0xEC,0x53,0x8B,0xD9}},
    {0x10BC90,5,0,urwcn_nr_entry_read,{0x53,0x8B,0xD9,0x33,0xC9}},
    {0x114340,6,0,urwcn_nr_entry_line,{0x55,0x8B,0xEC,0x83,0xEC,0x20}},
    {0x10BD90,6,0,urwcn_nr_entry_glyph,{0x55,0x8B,0xEC,0x83,0xEC,0x18}},
    // MOV [ECX+EAX*4],0; resume at the native TEST [ESI],2.
    {0x606C3,7,0,urwcn_nr_entry_606c3,{0xC7,0x04,0x81,0,0,0,0}},
    // MOV [EDX+EAX*4],ECX; MOV ECX,[absolute main owner].
    {0x607E4,9,5,urwcn_nr_entry_607e4,{0x89,0x0C,0x82,0x8B,0x0D,0x10,0xBB,0x5B,0x06}},
    // MOV [ECX+EAX*4],EDX; TEST BYTE [ESI],2; resume at JZ.
    {0x11454F,6,0,urwcn_nr_entry_11454f,{0x89,0x14,0x81,0xF6,0x06,0x02}},
    // MOV EDI,[ECX+EAX+0xA70]; prior TEST flags must survive to JZ.
    {0xD7AA9,7,0,urwcn_nr_entry_d7aa9,{0x8B,0xBC,0x01,0x70,0x0A,0,0}},
    {0xFC98F,7,0,urwcn_nr_entry_fc98f,{0x8B,0xBC,0x01,0x70,0x0A,0,0}},
    // Complete native message-gradient loop geometry; its original physical
    // pixel reads/writes are no longer replaced with logical-cell samples.
    {0xF67FD,8,0,urwcn_nr_entry_gradient_begin,{0x3B,0xD8,0x0F,0x87,0x16,0x02,0,0}},
    {0xF682D,5,0,urwcn_nr_entry_gradient_row,{0x8D,0x7A,0x05,0x03,0xC2}},
    {0xF6845,5,0,urwcn_nr_entry_gradient_shade,{0x8B,0x44,0x24,0x30,0x99}},
    {0xF6889,6,0,urwcn_nr_entry_gradient_read_x,{0x81,0xFF,0x20,0x03,0,0}},
    {0xF6899,6,0,urwcn_nr_entry_gradient_read_y,{0x81,0xFB,0x58,0x02,0,0}},
    {0xF6984,6,0,urwcn_nr_entry_gradient_write_x,{0x81,0xFF,0x20,0x03,0,0}},
    {0xF698C,6,0,urwcn_nr_entry_gradient_write_y,{0x81,0xFB,0x58,0x02,0,0}},
    {0xF69F6,8,0,urwcn_nr_entry_gradient_column_end,{0x3B,0xF8,0x0F,0x86,0x72,0xFE,0xFF,0xFF}},
    {0xF6A13,8,0,urwcn_nr_entry_gradient_row_end,{0x3B,0xD8,0x0F,0x86,0x05,0xFE,0xFF,0xFF}}
};
constexpr std::size_t patch_count=sizeof(patches)/sizeof(patches[0]);
std::uintptr_t installed_image{};
bool installed{};
bool original_bytes_written{};

bool restore_protection(std::size_t count) {
    bool ok=true;
    // Reverse order matters when two patch spans share a page.
    while(count) {
        Patch& patch=patches[--count];
        DWORD ignored{};
        if(!VirtualProtect(reinterpret_cast<void*>(installed_image+patch.rva),
                           patch.size,patch.old_protection,&ignored)) ok=false;
    }
    return ok;
}
bool allow_writes() {
    for(std::size_t i=0;i<patch_count;++i) {
        Patch& patch=patches[i];
        if(!VirtualProtect(reinterpret_cast<void*>(installed_image+patch.rva),
                           patch.size,PAGE_EXECUTE_READWRITE,&patch.old_protection)) {
            restore_protection(i);
            return false;
        }
    }
    return true;
}
bool finish_writes() {
    bool ok=true;
    for(const Patch& patch:patches) {
        if(!FlushInstructionCache(GetCurrentProcess(),
                                  reinterpret_cast<void*>(installed_image+patch.rva),patch.size)) ok=false;
    }
    if(!restore_protection(patch_count)) ok=false;
    return ok;
}
bool write_all(bool enable) {
    if(!allow_writes()) return false;
    for(const Patch& patch:patches) {
        std::memcpy(reinterpret_cast<void*>(installed_image+patch.rva),
                    enable?patch.replacement:patch.original,patch.size);
    }
    if(enable) installed=true;
    original_bytes_written=!enable;
    const bool ok=finish_writes();
    // Do not acknowledge removal until both code publication and protection
    // restoration finish. A failed OS operation leaves removal resumable.
    if(ok && !enable) installed=false;
    return ok;
}
}

Status install_raster_patches(std::uintptr_t image_base,HMODULE sdl) {
    if(installed || !image_base || !sdl) return Status::invalid;
    const auto lock=reinterpret_cast<int (__cdecl *)(render::Surface*)>(GetProcAddress(sdl,"SDL_LockSurface"));
    const auto unlock=reinterpret_cast<void (__cdecl *)(render::Surface*)>(GetProcAddress(sdl,"SDL_UnlockSurface"));
    if(!lock || !unlock) return Status::unavailable;
    const u32 owner=static_cast<u32>(image_base+0x61BBB10);
    for(Patch& patch:patches) {
        std::memcpy(patch.original,patch.raw,patch.size);
        if(patch.absolute_operand) std::memcpy(patch.original+patch.absolute_operand,&owner,sizeof(owner));
        if(std::memcmp(reinterpret_cast<const void*>(image_base+patch.rva),patch.original,patch.size)) return Status::invalid;
        std::memset(patch.replacement,0x90,patch.size);
        patch.replacement[0]=0xE9;
        const u32 displacement=static_cast<u32>(reinterpret_cast<std::uintptr_t>(patch.entry)-(image_base+patch.rva+5));
        std::memcpy(patch.replacement+1,&displacement,sizeof(displacement));
    }
    bindings={reinterpret_cast<render::Surface**>(owner),
              reinterpret_cast<const render::Rect*>(image_base+0x61A8CE4),
              reinterpret_cast<const std::uint8_t*>(image_base+0xA1BBD28),
              reinterpret_cast<const u32*>(image_base+0xA211068),lock,unlock};
    urwcn_nr_resume_606c3=image_base+0x606CA;
    urwcn_nr_resume_607e4=image_base+0x607ED;
    urwcn_nr_resume_11454f=image_base+0x114555;
    urwcn_nr_resume_d7aa9=image_base+0xD7AB0;
    urwcn_nr_resume_fc98f=image_base+0xFC996;
    urwcn_nr_main_surface=bindings.main_surface;
    urwcn_nr_gradient_rows=image_base+0xF6805;
    urwcn_nr_gradient_end=image_base+0xF6A1B;
    urwcn_nr_gradient_columns=image_base+0xF6870;
    urwcn_nr_gradient_next_row=image_base+0xF69FE;
    urwcn_nr_resume_gradient_row=image_base+0xF6832;
    urwcn_nr_resume_gradient_shade=image_base+0xF684A;
    urwcn_nr_resume_gradient_read_x=image_base+0xF688F;
    urwcn_nr_resume_gradient_read_y=image_base+0xF689F;
    urwcn_nr_resume_gradient_write_x=image_base+0xF698A;
    urwcn_nr_resume_gradient_write_y=image_base+0xF6992;
    installed_image=image_base;
    return write_all(true)?Status::ok:Status::failed;
}

Status remove_raster_patches() {
    if(!installed) return Status::ok;
    for(const Patch& patch:patches) {
        if(std::memcmp(reinterpret_cast<const void*>(installed_image+patch.rva),
                       original_bytes_written?patch.original:patch.replacement,patch.size)) return Status::invalid;
    }
    if(original_bytes_written) {
        if(!finish_writes()) return Status::failed;
        installed=false;
        return Status::ok;
    }
    return write_all(false)?Status::ok:Status::failed;
}
}

#undef URWCN_NR_ENTER
#undef URWCN_NR_ENTRY
#undef URWCN_NR_HELPER
#undef URWCN_NR_INTEGER
