#pragma once
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

namespace uwcn::linux_host {
// Private versioned module-state bytes, never code addresses or UI content.
struct StateWriter {
    std::vector<std::uint8_t> bytes;
    template<class T> void put(const T& value) {
        const auto* begin=reinterpret_cast<const std::uint8_t*>(&value);
        bytes.insert(bytes.end(),begin,begin+sizeof(T));
    }
    void text(const std::string& value) {
        put(static_cast<std::uint32_t>(value.size()));
        bytes.insert(bytes.end(),value.begin(),value.end());
    }
};
struct StateReader {
    const std::uint8_t* cursor;
    std::size_t remaining;
    StateReader(const void* data,std::size_t bytes):cursor(static_cast<const std::uint8_t*>(data)),remaining(bytes) {}
    template<class T> T get() {
        if(remaining<sizeof(T)) throw std::runtime_error("Truncated Linux module state");
        T value;
        std::memcpy(&value,cursor,sizeof(T));
        cursor+=sizeof(T); remaining-=sizeof(T);
        return value;
    }
    std::string text() {
        const auto size=get<std::uint32_t>();
        if(remaining<size) throw std::runtime_error("Truncated Linux state string");
        std::string value(reinterpret_cast<const char*>(cursor),size);
        cursor+=size; remaining-=size;
        return value;
    }
};
}
