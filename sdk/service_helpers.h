#pragma once
#include "host_abi.h"
#include <cstring>
#include <string>
#include <vector>

namespace uwcn {
inline Status copy_output(const void* data, u32 bytes, void* output, u32* capacity) {
    if (!capacity) return Status::invalid;
    const u32 available = *capacity;
    *capacity = bytes;
    if (!output || available < bytes) return bytes ? Status::insufficient_buffer : Status::ok;
    if (bytes) std::memcpy(output, data, bytes);
    return Status::ok;
}
inline Status copy_text(const std::string& text, void* output, u32* capacity) {
    return copy_output(text.c_str(), static_cast<u32>(text.size()+1), output, capacity);
}
inline Status invoke_text(const HostApi* host, ModuleId module, u32 op,
                          const void* request, u32 request_bytes, std::string& result) {
    u32 bytes=0;
    Status status=host->invoke(module,op,request,request_bytes,nullptr,&bytes);
    if (status!=Status::insufficient_buffer || !bytes) return status;
    std::vector<char> buffer(bytes);
    status=host->invoke(module,op,request,request_bytes,buffer.data(),&bytes);
    if (status!=Status::ok) return status;
    if (!bytes || buffer[bytes-1]!='\0') return Status::invalid;
    result.assign(buffer.data(),bytes-1);
    return Status::ok;
}
inline Status UWCN_CALL empty_save(void* output,u32* bytes) {
    return copy_output(nullptr,0,output,bytes);
}
inline Status UWCN_CALL empty_restore(const void*,u32 bytes) {
    return bytes ? Status::invalid : Status::ok;
}
}
