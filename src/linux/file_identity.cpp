#include "file_identity.h"
#include <openssl/evp.h>
#include <array>
#include <fstream>
#include <stdexcept>

namespace uwcn::linux_host {
std::string file_sha256(const std::filesystem::path& path) {
    std::ifstream stream(path,std::ios::binary);
    if(!stream) throw std::runtime_error("Cannot read "+path.string());
    auto* context=EVP_MD_CTX_new();
    EVP_DigestInit_ex(context,EVP_sha256(),nullptr);
    std::array<char,32768> bytes{};
    while(stream.read(bytes.data(),bytes.size()) || stream.gcount())
        EVP_DigestUpdate(context,bytes.data(),stream.gcount());
    std::array<unsigned char,32> digest{};
    unsigned length{};
    EVP_DigestFinal_ex(context,digest.data(),&length);
    EVP_MD_CTX_free(context);
    if(!stream.eof()) throw std::runtime_error("Read failed: "+path.string());
    constexpr char hex[]="0123456789abcdef";
    std::string result;
    for(auto value:digest) { result+=hex[value>>4]; result+=hex[value&15]; }
    return result;
}
}
