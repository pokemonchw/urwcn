#include "immediate_text.h"
#include "immediate_renderer.h"
#include "immediate_sprite.h"
#include "../../sdk/text_services.h"
#include <cstring>
#include <vector>

namespace {
using namespace uwcn;
const HostApi* host{};
render::FontEngine fonts;
bool initialized{};
Status output(const void* value,u32 size,void* destination,u32* capacity) {
    if(!capacity) return Status::invalid;
    const auto available=*capacity; *capacity=size;
    if(size && (!destination || available<size)) return Status::insufficient_buffer;
    if(size) std::memcpy(destination,value,size);
    return Status::ok;
}
bool ready() {
    if(initialized) return true;
    u32 bytes{};
    auto status=host->invoke(ModuleId::catalog,catalog_op::repertoire,nullptr,0,nullptr,&bytes);
    if(status!=Status::insufficient_buffer || !bytes) return false;
    std::vector<char> repertoire(bytes);
    if(host->invoke(ModuleId::catalog,catalog_op::repertoire,nullptr,0,repertoire.data(),&bytes)!=Status::ok) return false;
    if(!fonts.initialize(repertoire.data())) { fonts.shutdown(); return false; }
    initialized=true;
    return true;
}
Status UWCN_CALL initialize(const HostApi* api) {
    if(!api || api->size!=sizeof(HostApi) || api->abi!=kHostAbi) return Status::invalid;
    host=api;
    return Status::ok;
}
Status UWCN_CALL invoke(u32 operation,const void* input,u32 input_bytes,void* result,u32* result_bytes) {
    if(operation==kModuleDependenciesChanged) {
        if(!input || input_bytes!=sizeof(u32)) return Status::invalid;
        if((*static_cast<const u32*>(input)&1u) && initialized) {
            fonts.shutdown(); initialized=false;
        }
        if(result_bytes) *result_bytes=0;
        return Status::ok;
    }
    if(operation==render::op::measure || operation==render::op::draw) {
        if(!input || input_bytes!=sizeof(render::TextRequest)) return Status::invalid;
        const auto& request=*static_cast<const render::TextRequest*>(input);
        if(!request.utf8 || !request.surface || request.logical_width<=0 || request.logical_height<=0 ||
           request.native_line_height<=0 || request.ink_height<=0) return Status::invalid;
        // Font/SDL state is created on the native drawing thread. The actual
        // native destination determines raster density; the window is not read
        // or temporarily made a target, and no text survives this invocation.
        if(!ready()) return Status::failed;
        const auto* surface=static_cast<const render::Surface*>(request.surface);
        const double sx=double(surface->w)/request.logical_width;
        const double sy=double(surface->h)/request.logical_height;
        render::Metrics metrics{};
        const auto status=render::surface_text(fonts,request,sx,sy,operation==render::op::draw,metrics);
        if(status!=Status::ok) return status;
        return output(&metrics,sizeof(metrics),result,result_bytes);
    }
    if(operation==render::op::sprite) {
        if(!input || input_bytes!=sizeof(render::SpriteRequest)) return Status::invalid;
        const auto& request=*static_cast<const render::SpriteRequest*>(input);
        if(!request.surface || request.logical_width<=0 || request.logical_height<=0)
            return Status::invalid;
        if(!ready()) return Status::failed;
        if(result_bytes) *result_bytes=0;
        return render::surface_sprite(fonts.api,request);
    }
    if(operation==render::op::measure_renderer || operation==render::op::draw_renderer) {
        if(!input || input_bytes!=sizeof(render::TextRequest)) return Status::invalid;
        const auto& request=*static_cast<const render::TextRequest*>(input);
        if(!request.utf8 || !request.renderer || request.native_line_height<=0 || request.ink_height<=0)
            return Status::invalid;
        if(!ready()) return Status::failed;
        render::Metrics metrics{};
        const auto status=render::renderer_text(fonts,request,operation==render::op::draw_renderer,metrics);
        if(status!=Status::ok) return status;
        return output(&metrics,sizeof(metrics),result,result_bytes);
    }
    return Status::invalid;
}
Status UWCN_CALL save_state(void*,u32* bytes) {
    if(!bytes) return Status::invalid;
    *bytes=0; // Only font-owned derived data exists; native UI owns its pixels.
    return Status::ok;
}
Status UWCN_CALL restore_state(const void* data,u32 bytes) {
    // The published predecessor's schema 1 contains derived Paint history.
    // It is deliberately retired, not reconstructed into a new UI cache.
    if(!bytes) return Status::ok;
    if(!data || bytes<sizeof(u32)) return Status::invalid;
    u32 schema{}; std::memcpy(&schema,data,sizeof(schema));
    return schema==1 ? Status::ok : Status::invalid;
}
void UWCN_CALL shutdown() {
    if(initialized) fonts.shutdown();
    initialized=false; host=nullptr;
}
const ModuleApi api{sizeof(ModuleApi),kHostAbi,ModuleId::render,initialize,invoke,save_state,restore_state,shutdown};
}
UWCN_EXPORT const uwcn::ModuleDescriptor uwcn_module_descriptor{uwcn::kDescriptorMagic,uwcn::kHostAbi,static_cast<uwcn::u32>(uwcn::ModuleId::render),uwcn::kModuleMachine,1};
UWCN_EXPORT const uwcn::ModuleApi* UWCN_CALL uwcn_get_module_api() { return &api; }
