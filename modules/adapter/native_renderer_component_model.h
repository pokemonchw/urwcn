#pragma once
#include "native_component_model.h"
#include "native_menu_model.h"
#include "native_text_resource.h"
#include <variant>

namespace uwcn::adapter::native_renderer_component_model {
using native_text_resource::SourceKey;
using native_text_resource::TextSource;
using native_component_model::LayoutValue;
using native_component_model::NativeAnchor;
using native_component_model::ParagraphSource;
using Handle=u32;
enum class Kind : u32 { panel,paragraph,text_block,heading,marked_button,label_box };
enum class TargetKind:u32 { texture,software_surface };

// These are actual native pointer-owning fields, not a captured texture or a
// renderer guessed from the preceding draw. lifetime comes from that owner's
// confirmed create/destroy protocol. The owner resolves its current resource
// before painting; native_targets supplies its real current output density.
struct TargetSource {
    u64 lifetime;
    u32 renderer_owner_rva,texture_owner_rva;
    TargetKind kind=TargetKind::texture;
    u32 surface_owner_rva{};
};
struct NativeTarget { u32 renderer,texture;TargetKind kind; };
struct PanelInputs {
    NativeAnchor origin;LayoutValue width,height;u32 flags,color;
    native_component_style::PanelStyle style;
};
struct ParagraphInputs { NativeAnchor origin;LayoutValue width,height;u32 color,style; };
struct TextBlockInputs { NativeAnchor anchor;u32 color,style; };
struct LabelBoxInputs { NativeAnchor origin;LayoutValue width;u32 color; };
struct HeadingInputs {};
// CFD10 itself identifies a row by its original action. A Flow rebuild can
// change that row's index; the native action and the explicit menu owner stay
// its identity. The current native index is resolved inside that owner.
struct MarkedRowSource { native_menu_model::Handle owner;u32 action; };
struct MarkedButtonInputs { NativeAnchor origin;MarkedRowSource row; };
using Inputs=std::variant<PanelInputs,ParagraphInputs,TextBlockInputs,HeadingInputs,MarkedButtonInputs,LabelBoxInputs>;
struct Component {
    SourceKey source;TargetSource target;Kind kind;Inputs inputs;
    TextSource text;ParagraphSource paragraph;
};

void initialize(std::uintptr_t image_base);
Handle upsert_panel(SourceKey,TargetSource,const PanelInputs&,const TextSource&);
Handle upsert_paragraph(SourceKey,TargetSource,const ParagraphInputs&,const ParagraphSource&);
Handle upsert_text_block(SourceKey,TargetSource,const TextBlockInputs&,const TextSource&);
Handle upsert_label_box(SourceKey,TargetSource,const LabelBoxInputs&,const TextSource&);
Handle upsert_heading(SourceKey,TargetSource,const TextSource&);
Handle upsert_marked_button(SourceKey,TargetSource,const MarkedButtonInputs&,const TextSource&);
const Component& get(Handle);
u32 display_style(Handle);
// Complete CFD10 writes its own native row instead of entering CF990.
// Accept that row's canonical label after its ordinary/full locale consume.
void commit_native_row(Handle);
NativeTarget resolve_target(TargetSource);
void retain(Handle);
void release(Handle);
void remove(Handle);
void remove_owner(u64);
// Detached owning reference. The cache freezes neutral target/Menu resources;
// its Menu snapshot retains the same actual logical input owner, so rebuilding
// resources never installs a former selection as a separate input view.
Handle snapshot(Handle,TargetSource,native_menu_model::Handle menu_snapshot);

struct PaintServices {
    native_text_resource::Resolve resolve;
    Status (*encode_original)(const char*,std::vector<char>&);
    Status (*paragraph_words)(std::vector<char>&);
    Status (*measure)(const char*,std::int32_t&);
    void (*enter)(Handle,Kind,u32 style);
    void (*leave)(Handle,Kind);
};
struct PreparedText { std::vector<std::vector<char>> fragments; };
// Ordinary construction borrows these bytes for the same complete native
// call. Locale paint resolves this identical neutral source again.
Status prepare(Handle,const PaintServices&,PreparedText&);
Status paint(Handle,const PaintServices&);

// CFE08 precedes the confirmed CFE12 existing-row constructor/update decision.
// During a synchronous marked-button materialization it lets the original
// native branch recalculate its own geometry into the explicitly owned row.
// No coordinates, widths or hit rectangles are written by this Hook.
void append_hooks(std::vector<HookSpec>&);
Status dispatch(const NativeEvent&,DispatchResult&,bool& handled);
std::vector<std::uint8_t> save();
void restore(const void*);
void shutdown();
}
