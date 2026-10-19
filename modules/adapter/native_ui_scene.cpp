#include "native_ui_scene.h"
#include "native_component_binding.h"
#include "native_targets.h"
#include "native_culture_legend.h"
#include <algorithm>
#include <cstring>
#include <map>

namespace uwcn::adapter::native_ui_scene {
namespace {
enum class ComponentKind:u32 { component,menu,image,flow,renderer,footer,cache_region,message };
struct Child {
    native_text_resource::SourceKey source;
    ComponentKind kind;
    u32 handle;
};
struct Container {
    native_root_component::RootRevision background;
    Revision parent;
    std::vector<Child> children;
};
struct CacheIdentity {
    u32 lifetime;
    native_targets::SurfaceSource constructor;
};
// This is one native cache-restore component, not a list of text draws. Its
// constructor source is the native saved Scene, its resource belongs to the
// original cache slot, and its rectangles are that complete copy's inputs.
// Repeated updates replace the same component and its native layer position.
struct CacheRegion {
    u32 references;
    native_text_resource::SourceKey key;
    Slot slot;
    u32 owner_field;
    Revision source;
    native_targets::SurfaceSource constructor;
    bool has_source,has_destination;
    render::Rect from,to;
    native_menu_component::Handle menu;
};
std::uintptr_t base{};
native_component_model::PaintServices services{};
Revision next_revision=1;
Revision active_revision{};
std::map<Revision,Container> containers;
std::map<Slot,Revision> caches;
u64 language_revision=1;
std::map<Slot,u64> cache_languages;
u32 next_cache_lifetime=1,next_region=1;
std::map<Slot,CacheIdentity> cache_sources;
std::map<u32,CacheRegion> regions;
bool painting{};

void retain_region(u32 handle) {++regions.find(handle)->second.references;}
void release_region(u32 handle) {
    const auto region=regions.find(handle);
    if(--region->second.references==0) {
        const auto menu=region->second.menu;
        regions.erase(region);
        if(menu) native_menu_component::release(menu);
    }
}

void retain(const Child& child) {
    if(child.kind==ComponentKind::component) native_component_model::retain(child.handle);
    else if(child.kind==ComponentKind::menu) native_menu_component::retain(child.handle);
    else if(child.kind==ComponentKind::image) native_image_component::retain(child.handle);
    else if(child.kind==ComponentKind::flow) native_link_flow_component::retain(child.handle);
    else if(child.kind==ComponentKind::renderer) native_renderer_component_binding::retain(child.handle);
    else if(child.kind==ComponentKind::footer) native_footer_component::retain(child.handle);
    else if(child.kind==ComponentKind::cache_region) retain_region(child.handle);
    else native_message_flow::retain(child.handle);
}
void release(const Child& child) {
    if(child.kind==ComponentKind::component) native_component_model::release(child.handle);
    else if(child.kind==ComponentKind::menu) native_menu_component::release(child.handle);
    else if(child.kind==ComponentKind::image) native_image_component::release(child.handle);
    else if(child.kind==ComponentKind::flow) native_link_flow_component::release(child.handle);
    else if(child.kind==ComponentKind::renderer) native_renderer_component_binding::release(child.handle);
    else if(child.kind==ComponentKind::footer) native_footer_component::release(child.handle);
    else if(child.kind==ComponentKind::cache_region) release_region(child.handle);
    else native_message_flow::release(child.handle);
}
void retire_unused() {
    // Cache resources are created before the first native background exists.
    // Their retirement is valid in this construction phase; revision zero is
    // absence of a Scene, never a background or a container to traverse.
    std::vector<Revision> live;
    if(active_revision) live.push_back(active_revision);
    for(const auto& [slot,revision]:caches) live.push_back(revision);
    for(std::size_t index=0;index<live.size();++index) {
        const auto& container=containers.find(live[index])->second;
        const auto parent=container.parent;
        if(parent && std::find(live.begin(),live.end(),parent)==live.end()) live.push_back(parent);
        for(const auto& child:container.children) {
            if(child.kind==ComponentKind::cache_region) {
                const auto source=regions.find(child.handle)->second.source;
                if(std::find(live.begin(),live.end(),source)==live.end()) live.push_back(source);
            }
        }
    }
    for(auto container=containers.begin();container!=containers.end();) {
        const auto revision=container->first;
        if(std::find(live.begin(),live.end(),revision)==live.end()) {
            for(const auto& child:container->second.children) release(child);
            container=containers.erase(container);
        } else ++container;
    }
    std::vector<native_root_component::RootRevision> backgrounds;
    const auto current_background=native_root_component::current();
    if(current_background) backgrounds.push_back(current_background);
    for(const auto& entry:containers) backgrounds.push_back(entry.second.background);
    for(const auto background:native_root_component::revisions()) {
        if(std::find(backgrounds.begin(),backgrounds.end(),background)==backgrounds.end()) {
            native_component_model::remove_owner(background);
            native_component_binding::retire_root(background);
            native_image_component::remove_owner(background);
            native_footer_component::remove_owner(background);
            native_message_flow::remove_owner(background);
            native_root_component::retire(background);
        }
    }
}
void make_writable() {
    const bool frozen=std::any_of(caches.begin(),caches.end(),
        [](const auto& binding){return binding.second==active_revision;}) ||
        std::any_of(containers.begin(),containers.end(),
            [](const auto& entry){return entry.second.parent==active_revision;}) ||
        std::any_of(regions.begin(),regions.end(),
            [](const auto& entry){return entry.second.source==active_revision;});
    if(frozen) {
        auto copy=containers.find(active_revision)->second;
        for(const auto& child:copy.children) retain(child);
        active_revision=next_revision++;
        containers.emplace(active_revision,std::move(copy));
    }
}
void upsert(Child child) {
    make_writable();
    auto& children=containers.find(active_revision)->second.children;
    const auto existing=std::find_if(children.begin(),children.end(),
        [&](const Child& value){return value.source==child.source;});
    retain(child);
    if(existing==children.end()) children.push_back(child);
    else if((child.kind==ComponentKind::menu && existing->handle!=child.handle) ||
        child.kind==ComponentKind::cache_region) {
        release(*existing);children.erase(existing);children.push_back(child);
    } else { release(*existing);*existing=child; }
}
native_menu_component::Handle source_menu_owner(const Child& child) {
    using Get=native_menu_component::Handle (*)(u32);
    static const Get readers[]{
        [](u32 h){return native_component_model::menu_owner(h);},
        [](u32 h){return h;},
        [](u32)->u32{return 0;},
        [](u32 h){return native_link_flow_component::menu_owner(h);},
        [](u32 h){return native_renderer_component_binding::menu_owner(h);},
        [](u32)->u32{return 0;},
        [](u32 h){return regions.find(h)->second.menu;},
        [](u32)->u32{return 0;}
    };
    return readers[static_cast<u32>(child.kind)](child.handle);
}
native_menu_component::Handle menu_owner(const Child& child) {
    const auto source=source_menu_owner(child);
    return source ? native_menu_component::input_owner(source) : 0;
}
Status paint_region(u32 handle);
struct NativeCacheResources {
    NativeCacheResources() {native_renderer_component_binding::begin_native_cache_resources();}
    ~NativeCacheResources() {native_renderer_component_binding::end_native_cache_resources();}
};
Status paint(Revision revision,native_renderer_component_binding::PaintDestination destination) {
    const auto& container=containers.find(revision)->second;
    auto status=container.parent ? paint(container.parent,destination) :
        native_root_component::paint_background(container.background);
    if(status!=Status::ok) return status;
    for(const auto& child:container.children) {
        if(child.kind==ComponentKind::component) status=native_component_model::paint(child.handle,services);
        else if(child.kind==ComponentKind::menu) status=native_menu_component::paint(child.handle);
        else if(child.kind==ComponentKind::image) status=native_image_component::paint(child.handle);
        else if(child.kind==ComponentKind::flow) status=native_link_flow_component::paint(child.handle);
        else if(child.kind==ComponentKind::renderer) status=native_renderer_component_binding::paint(child.handle,destination);
        else if(child.kind==ComponentKind::footer) status=native_footer_component::paint(child.handle);
        else if(child.kind==ComponentKind::cache_region) status=paint_region(child.handle);
        else status=native_message_flow::paint(child.handle);
        if(status!=Status::ok) return status;
    }
    return Status::ok;
}
void prepare_region(const CacheRegion& region,native_ui_cache_owners::PreparedRestore& prepared) {
    prepared.has_source=region.has_source;prepared.has_destination=region.has_destination;
    prepared.source=region.from;prepared.destination=region.to;
    if(region.menu) {
        // Both original 10DBB0 callers obtain this rectangle from the actual
        // Menu header. Resolve those same fields after native menu layout;
        // an old translated width or a former selected-row rectangle is not
        // a source. The logical input owner remains the game's current view.
        const auto previous=native_menu_component::active();
        if(previous) native_menu_component::retain(previous);
        native_menu_component::activate(region.menu);
        prepared.source=*reinterpret_cast<const render::Rect*>(base+0x5F54A20);
        prepared.destination=prepared.source;
        if(previous) {native_menu_component::activate(previous);native_menu_component::release(previous);}
        else native_menu_component::deactivate();
    }
}
Status paint_region(u32 handle) {
    const auto& region=regions.find(handle)->second;
    const auto surface=native_targets::create_component_surface(region.constructor);
    if(!surface) return Status::failed;
    auto& cache=*reinterpret_cast<u32*>(base+region.owner_field);
    auto& target=*reinterpret_cast<u32*>(base+0x61BBB10);
    const auto previous_cache=cache,previous_target=target;
    const auto previous_background=native_root_component::current();
    // The temporary resource is installed into the actual native cache owner
    // while that owner's neutral Scene is materialized. No texture or bitmap
    // from the previous language supplies its base.
    cache=surface;target=surface;
    Status status;
    {
        const NativeCacheResources resources;
        status=paint(region.source,native_renderer_component_binding::PaintDestination::native_surface_cache);
    }
    target=previous_target;
    native_root_component::activate(previous_background);
    if(status==Status::ok) {
        native_ui_cache_owners::PreparedRestore prepared;
        prepare_region(region,prepared);
        status=native_targets::copy_cache_component(surface,
            prepared.has_source?&prepared.source:nullptr,
            prepared.has_destination?&prepared.destination:nullptr);
    }
    cache=previous_cache;
    native_targets::destroy_component_surface(surface);
    return status;
}
// The native software cache copy does not select a Menu or a Flow. Keep the
// caller's actual logical input view across all source materialization; frozen
// resource owners may update their own native layout, never become the input
// view merely because they occur last in a cached parent layer.
struct InputView {
    native_menu_component::Handle menu=native_menu_component::active();
    native_link_flow_component::Handle flow=native_link_flow_component::active();
    InputView() {
        if(menu) native_menu_component::retain(menu);
        if(flow) native_link_flow_component::retain(flow);
    }
    ~InputView() {
        if(native_link_flow_component::active()!=flow) {
            if(flow) native_link_flow_component::activate(flow);
            else native_link_flow_component::deactivate();
        }
        if(native_menu_component::active()!=menu) {
            if(menu) native_menu_component::activate(menu);
            else native_menu_component::deactivate();
        }
        if(flow) native_link_flow_component::release(flow);
        if(menu) native_menu_component::release(menu);
    }
};
Status install_renderer_sources(Revision revision,bool materialize_renderer) {
    const auto& container=containers.find(revision)->second;
    if(container.parent) {
        const auto status=install_renderer_sources(container.parent,materialize_renderer);if(status!=Status::ok) return status;
    }
    for(const auto& child:container.children) {
        if(child.kind==ComponentKind::renderer) {
            native_renderer_component_binding::activate(child.handle);
            if(materialize_renderer) {
                const auto status=native_renderer_component_binding::paint(child.handle,
                    native_renderer_component_binding::PaintDestination::active_native_owner);
                if(status!=Status::ok) return status;
            }
        }
    }
    return Status::ok;
}
template<class T> void append(std::vector<std::uint8_t>& output,const T& value) {
    const auto offset=output.size();output.resize(offset+sizeof(value));
    std::memcpy(output.data()+offset,&value,sizeof(value));
}
template<class T> T read(const std::uint8_t*& cursor) {
    T value;std::memcpy(&value,cursor,sizeof(value));cursor+=sizeof(value);return value;
}
void append_surface(std::vector<std::uint8_t>& output,const native_targets::SurfaceSource& value) {
    append(output,value.flags);append(output,value.width);append(output,value.height);append(output,value.depth);
    append(output,value.red_mask);append(output,value.green_mask);append(output,value.blue_mask);append(output,value.alpha_mask);
}
native_targets::SurfaceSource read_surface(const std::uint8_t*& cursor) {
    native_targets::SurfaceSource value;
    value.flags=read<u32>(cursor);value.width=read<std::int32_t>(cursor);
    value.height=read<std::int32_t>(cursor);value.depth=read<std::int32_t>(cursor);
    value.red_mask=read<u32>(cursor);value.green_mask=read<u32>(cursor);
    value.blue_mask=read<u32>(cursor);value.alpha_mask=read<u32>(cursor);return value;
}
void append_rect(std::vector<std::uint8_t>& output,const render::Rect& value) {
    append(output,value.x);append(output,value.y);append(output,value.w);append(output,value.h);
}
render::Rect read_rect(const std::uint8_t*& cursor) {
    const auto x=read<std::int32_t>(cursor),y=read<std::int32_t>(cursor);
    const auto w=read<std::int32_t>(cursor),h=read<std::int32_t>(cursor);return {x,y,w,h};
}
}

void initialize(std::uintptr_t image_base,const native_component_model::PaintServices& paint_services) {
    base=image_base;services=paint_services;next_revision=1;active_revision=0;
    containers.clear();caches.clear();painting=false;
    language_revision=1;cache_languages.clear();
    next_cache_lifetime=1;next_region=1;cache_sources.clear();regions.clear();
}
void synchronize_root() {
    if(painting) return;
    const auto background=native_root_component::current();
    if(!background) return;
    if(active_revision && containers.find(active_revision)->second.background==background) return;
    active_revision=next_revision++;
    containers.emplace(active_revision,Container{background,0,{}});
    retire_unused();
}
void component_constructed(native_component_model::Handle handle) {
    if(painting) return;
    synchronize_root();
    if(!active_revision) return;
    const auto& model=native_component_model::get(handle);
    upsert({model.source,ComponentKind::component,handle});
}
void menu_constructed(native_menu_component::Handle handle) {
    if(painting) return;
    synchronize_root();
    if(!active_revision) return;
    const auto& children=containers.find(active_revision)->second.children;
    if(std::any_of(children.begin(),children.end(),[handle](const Child& child){
        return (child.kind==ComponentKind::flow || child.kind==ComponentKind::renderer) &&
            menu_owner(child)==native_menu_component::input_owner(handle);
    })) return;
    const auto background=containers.find(active_revision)->second.background;
    // CF790 replaces the one native menu view. A cache retains the previous
    // container as a parent source; this slot never grows with menu handles.
    upsert({{background,0x5F54A20,0},ComponentKind::menu,handle});
}
void image_constructed(native_image_component::Handle handle) {
    if(painting) return;
    synchronize_root();
    if(!active_revision) return;
    upsert({native_image_component::get(handle).source,ComponentKind::image,handle});
}
void menu_retired(native_menu_component::Handle owner) {
    if(painting || !active_revision || !owner) return;
    owner=native_menu_component::input_owner(owner);
    make_writable();auto& children=containers.find(active_revision)->second.children;
    std::vector<native_renderer_component_binding::Handle> renderers;
    for(auto child=children.begin();child!=children.end();) {
        if(menu_owner(*child)==owner) {
            if(child->kind==ComponentKind::component) native_component_model::remove(child->handle);
            if(child->kind==ComponentKind::renderer) {native_renderer_component_binding::retain(child->handle);renderers.push_back(child->handle);}
            release(*child);child=children.erase(child);
        } else ++child;
    }
    const auto flow=native_link_flow_component::active();
    if(flow && native_menu_component::input_owner(native_link_flow_component::menu_owner(flow))==owner)
        native_link_flow_component::deactivate();
    for(const auto renderer:renderers) {
        native_renderer_component_binding::menu_retired(renderer,owner);native_renderer_component_binding::release(renderer);
    }
}
void footer_constructed(native_footer_component::Handle handle) {
    if(painting) return;
    synchronize_root();if(!active_revision) return;
    upsert({native_footer_component::get(handle).source,ComponentKind::footer,handle});
}
void message_constructed(native_message_flow::Handle handle) {
    if(painting) return;
    synchronize_root();if(!active_revision) return;
    upsert({native_message_flow::get(handle).key,ComponentKind::message,handle});
}
void flow_constructed(native_link_flow_component::Handle handle) {
    if(painting) return;
    synchronize_root();if(!active_revision) return;make_writable();
    auto& children=containers.find(active_revision)->second.children;
    const auto owner=native_menu_component::input_owner(native_link_flow_component::menu_owner(handle));
    auto position=children.size();
    for(std::size_t index=0;index<children.size();) {
        const auto& child=children[index];
        if(menu_owner(child)==owner) position=std::min(position,index);
        if(child.kind==ComponentKind::menu && menu_owner(child)==owner) {
            release(child);children.erase(children.begin()+index);
        } else ++index;
    }
    const Child flow{native_link_flow_component::source(handle).key,ComponentKind::flow,handle};
    const auto existing=std::find_if(children.begin(),children.end(),[&](const Child& child){return child.source==flow.source;});
    retain(flow);
    if(existing!=children.end()) {release(*existing);*existing=flow;}
    else children.insert(children.begin()+position,flow);
}
void renderer_constructed(native_renderer_component_binding::Handle handle) {
    if(painting) return;
    synchronize_root();if(!active_revision) return;make_writable();
    const auto source_owner=native_renderer_component_binding::menu_owner(handle);
    const auto owner=source_owner ? native_menu_component::input_owner(source_owner) : 0;
    if(owner) {
        auto& children=containers.find(active_revision)->second.children;
        for(auto child=children.begin();child!=children.end();) {
            if(child->kind==ComponentKind::menu && menu_owner(*child)==owner) {release(*child);child=children.erase(child);}
            else ++child;
        }
    }
    upsert({native_renderer_component_binding::source(handle),ComponentKind::renderer,handle});
}
void renderer_retired(native_text_resource::SourceKey key) {
    if(painting || !active_revision) return;
    make_writable();auto& children=containers.find(active_revision)->second.children;
    const auto child=std::find_if(children.begin(),children.end(),[&](const Child& value){return value.kind==ComponentKind::renderer && value.source==key;});
    if(child!=children.end()) {release(*child);children.erase(child);}
}
Revision current() { return active_revision; }
bool materializing() { return painting; }
void cache_saved(Slot slot) {
    if(painting) return;
    synchronize_root();
    if(!active_revision) return;
    // The native save freezes the source of the pixels it has just copied.
    // Its next construction layer consumes this retained source as its base.
    // Detached menu sources preserve English input/model values; SDL pixels
    // and generated text are never copied into the source container.
    auto frozen=containers.find(active_revision)->second;
    std::map<native_menu_component::Handle,native_menu_component::Handle> menu_snapshots;
    std::vector<native_menu_component::Handle> independent_menus;
    for(auto& child:frozen.children) {
        if(child.kind==ComponentKind::flow) {
            const auto previous=menu_owner(child);
            child.handle=native_link_flow_component::snapshot(child.handle);
            menu_snapshots.emplace(previous,native_link_flow_component::menu_owner(child.handle));
        } else if(child.kind==ComponentKind::menu) {
            const auto previous=menu_owner(child);child.handle=native_menu_component::snapshot(child.handle);
            menu_snapshots.emplace(previous,child.handle);
        }
    }
    for(auto& child:frozen.children) {
        if(child.kind==ComponentKind::flow || child.kind==ComponentKind::menu) continue;
        if(child.kind==ComponentKind::cache_region) {retain(child);continue;}
        if(child.kind==ComponentKind::message) {child.handle=native_message_flow::snapshot(child.handle);continue;}
        const auto previous=menu_owner(child);
        native_menu_component::Handle frozen_menu{};
        if(previous) {
            const auto existing=menu_snapshots.find(previous);
            if(existing==menu_snapshots.end()) {
                frozen_menu=native_menu_component::snapshot(source_menu_owner(child));
                menu_snapshots.emplace(previous,frozen_menu);independent_menus.push_back(frozen_menu);
            } else frozen_menu=existing->second;
        }
        if(child.kind==ComponentKind::renderer)
            child.handle=native_renderer_component_binding::snapshot(child.handle,frozen_menu);
        else if(child.kind==ComponentKind::component && previous)
            {child.handle=native_component_model::snapshot(child.handle,frozen_menu);child.source=native_component_model::get(child.handle).source;}
        else retain(child);
    }
    for(const auto menu:independent_menus) native_menu_component::release(menu);
    const auto frozen_revision=next_revision++;
    containers.emplace(frozen_revision,std::move(frozen));
    caches[slot]=frozen_revision;
    cache_languages[slot]=language_revision;
    const auto existing_source=cache_sources.find(slot);
    const auto cache_slot=static_cast<native_ui_cache_owners::Slot>(slot);
    const auto constructor=native_targets::component_surface_source(native_ui_cache_owners::surface(cache_slot));
    if(existing_source==cache_sources.end()) cache_sources.emplace(slot,CacheIdentity{next_cache_lifetime++,constructor});
    else existing_source->second.constructor=constructor;
    const auto background=containers.find(frozen_revision)->second.background;
    active_revision=next_revision++;
    containers.emplace(active_revision,Container{background,frozen_revision,{}});
    retire_unused();
}
void cache_retired(Slot slot) {
    if(painting) return;
    caches.erase(slot);cache_languages.erase(slot);cache_sources.erase(slot);retire_unused();
}
Status materialize_cache(Slot slot,void* native_surface) {
    const InputView input;
    auto& target=*reinterpret_cast<void**>(base+0x61BBB10);
    const auto previous_target=target;
    const auto previous_background=native_root_component::current();
    target=native_surface;painting=true;
    Status status;
    {
        const NativeCacheResources resources;
        status=paint(caches.find(slot)->second,native_renderer_component_binding::PaintDestination::native_surface_cache);
    }
    painting=false;target=previous_target;
    native_root_component::activate(previous_background);
    return status;
}
Status prepare_cache_restore(Slot slot,const native_ui_cache_owners::RestoreInput& input,
    native_ui_cache_owners::PreparedRestore& prepared) {
    synchronize_root();
    if(!active_revision) return Status::unavailable;
    const auto status=prepare_cache(slot,const_cast<void*>(input.native_surface));
    if(status!=Status::ok) return status;
    const auto& identity=cache_sources.find(slot)->second;
    const auto cache_slot=static_cast<native_ui_cache_owners::Slot>(slot);
    const auto field=native_ui_cache_owners::owner_field(cache_slot);
    const auto background=containers.find(active_revision)->second.background;
    const auto menu=cache_slot==native_ui_cache_owners::Slot::menu ? native_menu_component::active() : 0;
    const auto handle=next_region++;
    CacheRegion region{1,{background,(static_cast<u64>(field)<<32)|identity.lifetime,0},slot,field,
        caches.find(slot)->second,identity.constructor,input.source!=nullptr,input.destination!=nullptr,
        input.source?*input.source:render::Rect{},input.destination?*input.destination:render::Rect{},menu};
    if(menu) native_menu_component::retain(menu);
    regions.emplace(handle,std::move(region));
    prepared.component=handle;
    prepare_region(regions.find(handle)->second,prepared);
    return Status::ok;
}
Status cache_restored(Slot slot,const native_ui_cache_owners::PreparedRestore& prepared,int native_result) {
    const auto& region=regions.find(prepared.component)->second;
    if(native_result!=0) {release_region(prepared.component);return Status::failed;}
    if(!region.has_source) {
        const InputView input;
        active_revision=caches.find(slot)->second;
        native_root_component::activate(containers.find(active_revision)->second.background);
        painting=true;const auto status=install_renderer_sources(active_revision,true);painting=false;
        release_region(prepared.component);
        retire_unused();
        return status;
    }
    // Commit the same canonical instance consumed by the ordinary native
    // copy. It replaces this slot/lifetime's restore component, rather than
    // appending individual blit calls or selecting children by their pixels.
    upsert({region.key,ComponentKind::cache_region,prepared.component});
    release_region(prepared.component);
    retire_unused();
    return Status::ok;
}
Status repaint() {
    if(!active_revision) return Status::unavailable;
    const InputView input;
    const auto previous_background=native_root_component::current();
    painting=true;const auto status=paint(active_revision,native_renderer_component_binding::PaintDestination::active_native_owner);
    if(status==Status::ok) install_renderer_sources(active_revision,false);
    painting=false;
    native_root_component::activate(previous_background);
    return status;
}
Status language_changed() {
    ++language_revision;
    const auto resource=native_culture_legend::language_changed();
    return resource==Status::ok?repaint():resource;
}
Status prepare_cache(Slot slot,void* surface) {
    auto& cached_language=cache_languages.find(slot)->second;
    if(cached_language==language_revision) return Status::ok;
    const auto status=materialize_cache(slot,surface);
    if(status==Status::ok) cached_language=language_revision;
    return status;
}
std::vector<std::uint8_t> save() {
    std::vector<std::uint8_t> payload;
    append(payload,next_revision);append(payload,active_revision);append(payload,language_revision);
    append(payload,next_cache_lifetime);append(payload,next_region);
    append(payload,static_cast<u32>(containers.size()));append(payload,static_cast<u32>(caches.size()));
    append(payload,static_cast<u32>(regions.size()));
    for(const auto& [revision,container]:containers) {
        append(payload,revision);append(payload,container.background);append(payload,container.parent);
        append(payload,static_cast<u32>(container.children.size()));
        for(const auto& child:container.children) {
            append(payload,child.source.owner);append(payload,child.source.native_source);
            append(payload,child.source.field);append(payload,static_cast<u32>(child.kind));append(payload,child.handle);
        }
    }
    for(const auto& [slot,revision]:caches) {
        append(payload,slot);append(payload,revision);append(payload,cache_languages.find(slot)->second);
        const auto& identity=cache_sources.find(slot)->second;
        append(payload,identity.lifetime);append_surface(payload,identity.constructor);
    }
    for(const auto& [handle,region]:regions) {
        append(payload,handle);append(payload,region.references);
        append(payload,region.key.owner);append(payload,region.key.native_source);append(payload,region.key.field);
        append(payload,region.slot);append(payload,region.owner_field);append(payload,region.source);
        append_surface(payload,region.constructor);
        append(payload,region.has_source?1u:0u);append(payload,region.has_destination?1u:0u);
        append_rect(payload,region.from);append_rect(payload,region.to);append(payload,region.menu);
    }
    return payload;
}
void restore(const void* payload) {
    const auto* cursor=static_cast<const std::uint8_t*>(payload);
    next_revision=read<Revision>(cursor);active_revision=read<Revision>(cursor);
    language_revision=read<u64>(cursor);
    next_cache_lifetime=read<u32>(cursor);next_region=read<u32>(cursor);
    const auto container_count=read<u32>(cursor),cache_count=read<u32>(cursor),region_count=read<u32>(cursor);
    containers.clear();caches.clear();cache_languages.clear();cache_sources.clear();regions.clear();painting=false;
    for(u32 i=0;i<container_count;++i) {
        const auto revision=read<Revision>(cursor);
        Container container{read<native_root_component::RootRevision>(cursor),read<Revision>(cursor),{}};
        const auto child_count=read<u32>(cursor);
        for(u32 child_index=0;child_index<child_count;++child_index) {
            Child child{};
            child.source.owner=read<u64>(cursor);child.source.native_source=read<u64>(cursor);
            child.source.field=read<u32>(cursor);child.kind=static_cast<ComponentKind>(read<u32>(cursor));
            child.handle=read<u32>(cursor);container.children.push_back(child);
        }
        containers.emplace(revision,std::move(container));
    }
    for(u32 i=0;i<cache_count;++i) {
        const auto slot=read<Slot>(cursor);caches.emplace(slot,read<Revision>(cursor));cache_languages.emplace(slot,read<u64>(cursor));
        const auto lifetime=read<u32>(cursor);cache_sources.emplace(slot,CacheIdentity{lifetime,read_surface(cursor)});
    }
    for(u32 i=0;i<region_count;++i) {
        const auto handle=read<u32>(cursor);CacheRegion region{};
        region.references=read<u32>(cursor);
        region.key.owner=read<u64>(cursor);region.key.native_source=read<u64>(cursor);region.key.field=read<u32>(cursor);
        region.slot=read<Slot>(cursor);region.owner_field=read<u32>(cursor);region.source=read<Revision>(cursor);
        region.constructor=read_surface(cursor);
        region.has_source=read<u32>(cursor)!=0;region.has_destination=read<u32>(cursor)!=0;
        region.from=read_rect(cursor);region.to=read_rect(cursor);region.menu=read<u32>(cursor);
        regions.emplace(handle,std::move(region));
    }
}
void shutdown() {
    for(const auto& [revision,container]:containers) {(void)revision;for(const auto& child:container.children) release(child);}
    containers.clear();caches.clear();cache_languages.clear();cache_sources.clear();regions.clear();base=0;services={};painting=false;
}
}
