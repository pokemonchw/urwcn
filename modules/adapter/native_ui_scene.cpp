#include "native_ui_scene.h"
#include "native_component_binding.h"
#include <algorithm>
#include <cstring>
#include <map>

namespace uwcn::adapter::native_ui_scene {
namespace {
enum class ComponentKind:u32 { component,menu,image,flow,renderer,footer };
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
std::uintptr_t base{};
native_component_model::PaintServices services{};
Revision next_revision=1;
Revision active_revision{};
std::map<Revision,Container> containers;
std::map<Slot,Revision> caches;
u64 language_revision=1;
std::map<Slot,u64> cache_languages;
bool painting{};

void retain(const Child& child) {
    if(child.kind==ComponentKind::component) native_component_model::retain(child.handle);
    else if(child.kind==ComponentKind::menu) native_menu_component::retain(child.handle);
    else if(child.kind==ComponentKind::image) native_image_component::retain(child.handle);
    else if(child.kind==ComponentKind::flow) native_link_flow_component::retain(child.handle);
    else if(child.kind==ComponentKind::renderer) native_renderer_component_binding::retain(child.handle);
    else native_footer_component::retain(child.handle);
}
void release(const Child& child) {
    if(child.kind==ComponentKind::component) native_component_model::release(child.handle);
    else if(child.kind==ComponentKind::menu) native_menu_component::release(child.handle);
    else if(child.kind==ComponentKind::image) native_image_component::release(child.handle);
    else if(child.kind==ComponentKind::flow) native_link_flow_component::release(child.handle);
    else if(child.kind==ComponentKind::renderer) native_renderer_component_binding::release(child.handle);
    else native_footer_component::release(child.handle);
}
void retire_unused() {
    // Cache resources are created before the first native background exists.
    // Their retirement is valid in this construction phase; revision zero is
    // absence of a Scene, never a background or a container to traverse.
    std::vector<Revision> live;
    if(active_revision) live.push_back(active_revision);
    for(const auto& [slot,revision]:caches) live.push_back(revision);
    for(std::size_t index=0;index<live.size();++index) {
        const auto parent=containers.find(live[index])->second.parent;
        if(parent && std::find(live.begin(),live.end(),parent)==live.end()) live.push_back(parent);
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
            native_root_component::retire(background);
        }
    }
}
void make_writable() {
    const bool frozen=std::any_of(caches.begin(),caches.end(),
        [](const auto& binding){return binding.second==active_revision;}) ||
        std::any_of(containers.begin(),containers.end(),
            [](const auto& entry){return entry.second.parent==active_revision;});
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
    else if(child.kind==ComponentKind::menu && existing->handle!=child.handle) {
        release(*existing);children.erase(existing);children.push_back(child);
    } else { release(*existing);*existing=child; }
}
native_menu_component::Handle menu_owner(const Child& child) {
    using Get=native_menu_component::Handle (*)(u32);
    static const Get readers[]{
        [](u32 h){return native_component_model::menu_owner(h);},
        [](u32 h){return h;},
        [](u32)->u32{return 0;},
        [](u32 h){return native_link_flow_component::menu_owner(h);},
        [](u32 h){return native_renderer_component_binding::menu_owner(h);},
        [](u32)->u32{return 0;}
    };
    return readers[static_cast<u32>(child.kind)](child.handle);
}
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
        else status=native_footer_component::paint(child.handle);
        if(status!=Status::ok) return status;
    }
    return Status::ok;
}
Status activate_views(Revision revision,bool materialize_renderer) {
    const auto& container=containers.find(revision)->second;
    if(container.parent) {
        const auto status=activate_views(container.parent,materialize_renderer);if(status!=Status::ok) return status;
    }
    for(const auto& child:container.children) {
        if(child.kind==ComponentKind::component) {
            const auto owner=menu_owner(child);if(owner) native_menu_component::activate(owner);
        } else if(child.kind==ComponentKind::flow) native_link_flow_component::activate(child.handle);
        else if(child.kind==ComponentKind::menu) native_menu_component::activate(child.handle);
        else if(child.kind==ComponentKind::renderer) {
            native_renderer_component_binding::activate(child.handle);
            if(materialize_renderer) {
                const auto status=native_renderer_component_binding::paint(child.handle,
                    native_renderer_component_binding::PaintDestination::active_native_owner);
                if(status!=Status::ok) return status;
            }
            const auto owner=native_renderer_component_binding::menu_owner(child.handle);
            if(owner) native_menu_component::activate(owner);
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
}

void initialize(std::uintptr_t image_base,const native_component_model::PaintServices& paint_services) {
    base=image_base;services=paint_services;next_revision=1;active_revision=0;
    containers.clear();caches.clear();painting=false;
    language_revision=1;cache_languages.clear();
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
        return (child.kind==ComponentKind::flow || child.kind==ComponentKind::renderer) && menu_owner(child)==handle;
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
    if(flow && native_link_flow_component::menu_owner(flow)==owner) native_link_flow_component::deactivate();
    for(const auto renderer:renderers) {
        native_renderer_component_binding::menu_retired(renderer,owner);native_renderer_component_binding::release(renderer);
    }
}
void footer_constructed(native_footer_component::Handle handle) {
    if(painting) return;
    synchronize_root();if(!active_revision) return;
    upsert({native_footer_component::get(handle).source,ComponentKind::footer,handle});
}
void flow_constructed(native_link_flow_component::Handle handle) {
    if(painting) return;
    synchronize_root();if(!active_revision) return;make_writable();
    auto& children=containers.find(active_revision)->second.children;
    const auto owner=native_link_flow_component::menu_owner(handle);
    auto position=children.size();
    for(std::size_t index=0;index<children.size();) {
        const auto& child=children[index];
        if(menu_owner(child)==owner) position=std::min(position,index);
        if(child.kind==ComponentKind::menu && child.handle==owner) {
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
    const auto owner=native_renderer_component_binding::menu_owner(handle);
    if(owner) {
        auto& children=containers.find(active_revision)->second.children;
        for(auto child=children.begin();child!=children.end();) {
            if(child->kind==ComponentKind::menu && child->handle==owner) {release(*child);child=children.erase(child);}
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
            const auto previous=native_link_flow_component::menu_owner(child.handle);
            child.handle=native_link_flow_component::snapshot(child.handle);
            menu_snapshots.emplace(previous,native_link_flow_component::menu_owner(child.handle));
        } else if(child.kind==ComponentKind::menu) {
            const auto previous=child.handle;child.handle=native_menu_component::snapshot(previous);
            menu_snapshots.emplace(previous,child.handle);
        }
    }
    for(auto& child:frozen.children) {
        if(child.kind==ComponentKind::flow || child.kind==ComponentKind::menu) continue;
        const auto previous=menu_owner(child);
        native_menu_component::Handle frozen_menu{};
        if(previous) {
            const auto existing=menu_snapshots.find(previous);
            if(existing==menu_snapshots.end()) {
                frozen_menu=native_menu_component::snapshot(previous);
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
    const auto background=containers.find(frozen_revision)->second.background;
    active_revision=next_revision++;
    containers.emplace(active_revision,Container{background,frozen_revision,{}});
    retire_unused();
}
void cache_retired(Slot slot) {
    if(painting) return;
    caches.erase(slot);cache_languages.erase(slot);retire_unused();
}
Status materialize_cache(Slot slot,void* native_surface) {
    auto& target=*reinterpret_cast<void**>(base+0x61BBB10);
    const auto previous_target=target;
    const auto previous_background=native_root_component::current();
    target=native_surface;painting=true;
    const auto status=paint(caches.find(slot)->second,native_renderer_component_binding::PaintDestination::native_surface_cache);
    painting=false;target=previous_target;
    native_root_component::activate(previous_background);
    return status;
}
Status cache_restored(Slot slot,bool whole_root) {
    if(painting) return Status::ok;
    if(whole_root) {
        active_revision=caches.find(slot)->second;
        native_root_component::activate(containers.find(active_revision)->second.background);
        painting=true;const auto status=activate_views(active_revision,true);painting=false;
        retire_unused();
        return status;
    }
    return Status::ok;
}
Status repaint() {
    if(!active_revision) return Status::unavailable;
    const auto previous_background=native_root_component::current();
    painting=true;const auto status=paint(active_revision,native_renderer_component_binding::PaintDestination::active_native_owner);
    if(status==Status::ok) activate_views(active_revision,false);
    painting=false;
    native_root_component::activate(previous_background);
    return status;
}
Status language_changed() {++language_revision;return repaint();}
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
    append(payload,static_cast<u32>(containers.size()));append(payload,static_cast<u32>(caches.size()));
    for(const auto& [revision,container]:containers) {
        append(payload,revision);append(payload,container.background);append(payload,container.parent);
        append(payload,static_cast<u32>(container.children.size()));
        for(const auto& child:container.children) {
            append(payload,child.source.owner);append(payload,child.source.native_source);
            append(payload,child.source.field);append(payload,static_cast<u32>(child.kind));append(payload,child.handle);
        }
    }
    for(const auto& [slot,revision]:caches) { append(payload,slot);append(payload,revision);append(payload,cache_languages.find(slot)->second); }
    return payload;
}
void restore(const void* payload) {
    const auto* cursor=static_cast<const std::uint8_t*>(payload);
    next_revision=read<Revision>(cursor);active_revision=read<Revision>(cursor);
    language_revision=read<u64>(cursor);
    const auto container_count=read<u32>(cursor),cache_count=read<u32>(cursor);
    containers.clear();caches.clear();cache_languages.clear();painting=false;
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
    }
}
void shutdown() {
    for(const auto& [revision,container]:containers) {(void)revision;for(const auto& child:container.children) release(child);}
    containers.clear();caches.clear();cache_languages.clear();base=0;services={};painting=false;
}
}
