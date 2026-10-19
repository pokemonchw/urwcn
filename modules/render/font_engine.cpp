#include "font_engine.h"
#if defined(_WIN32)
#include <wincrypt.h>
#else
#include <dlfcn.h>
#include <openssl/evp.h>
#include <cstdlib>
#include <fstream>
#endif
#include <algorithm>
#include <cmath>
#include <cstring>
#include <set>

namespace uwcn::render {
namespace {
template<class T> bool symbol(HMODULE lib,const char* name,T& result) {
#if defined(_WIN32)
    result=reinterpret_cast<T>(GetProcAddress(lib,name)); return result!=nullptr;
#else
    result=reinterpret_cast<T>(dlsym(lib,name)); return result!=nullptr;
#endif
}
#if defined(_WIN32)
bool sha256(const std::wstring& path,std::array<std::uint8_t,32>& result) {
    HANDLE file=CreateFileW(path.c_str(),GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,nullptr);
    if(file==INVALID_HANDLE_VALUE) return false;
    HCRYPTPROV provider{}; HCRYPTHASH hash{};
    bool ok=CryptAcquireContextW(&provider,nullptr,nullptr,PROV_RSA_AES,CRYPT_VERIFYCONTEXT)!=0;
    if(ok) ok=CryptCreateHash(provider,CALG_SHA_256,0,0,&hash)!=0;
    std::uint8_t bytes[32768]; DWORD count{};
    while(ok) {
        if(!ReadFile(file,bytes,sizeof(bytes),&count,nullptr)) { ok=false; break; }
        if(!count) break;
        ok=CryptHashData(hash,bytes,count,0)!=0;
    }
    DWORD size=static_cast<DWORD>(result.size());
    if(ok) ok=CryptGetHashParam(hash,HP_HASHVAL,result.data(),&size,0)!=0;
    if(hash) CryptDestroyHash(hash);
    if(provider) CryptReleaseContext(provider,0);
    CloseHandle(file); return ok;
}
#else
bool sha256(const std::string& path,std::array<std::uint8_t,32>& result) {
    std::ifstream stream(path,std::ios::binary);
    if(!stream) return false;
    auto* context=EVP_MD_CTX_new();
    EVP_DigestInit_ex(context,EVP_sha256(),nullptr);
    char bytes[32768];
    while(stream.read(bytes,sizeof(bytes)) || stream.gcount())
        EVP_DigestUpdate(context,bytes,stream.gcount());
    unsigned length{};
    EVP_DigestFinal_ex(context,result.data(),&length);
    EVP_MD_CTX_free(context);
    return stream.eof();
}
#endif
bool scalar(const std::string& text,std::size_t& offset,std::uint32_t& value) {
    const auto lead=static_cast<unsigned char>(text[offset++]);
    if(lead<0x80) { value=lead; return true; }
    int count{}; std::uint32_t minimum{};
    if(lead>=0xC2 && lead<=0xDF) { count=1; value=lead&31; minimum=0x80; }
    else if(lead>=0xE0 && lead<=0xEF) { count=2; value=lead&15; minimum=0x800; }
    else if(lead>=0xF0 && lead<=0xF4) { count=3; value=lead&7; minimum=0x10000; }
    else return false;
    if(offset+count>text.size()) return false;
    while(count--) { const auto c=static_cast<unsigned char>(text[offset++]); if((c&0xC0)!=0x80) return false; value=(value<<6)|(c&63); }
    return value>=minimum && value<=0x10FFFF && !(value>=0xD800 && value<=0xDFFF);
}
}
bool Sdl::initialize() {
#if defined(_WIN32)
    sdl=GetModuleHandleW(L"SDL2.dll"); if(!sdl) return false;
#else
    sdl=dlopen("libSDL2-2.0.so.0",RTLD_NOW|RTLD_LOCAL);
    if(!sdl) return false;
#endif
#define SDL_BIND(name) if(!symbol(sdl,"SDL_" #name,name)) return false
    SDL_BIND(GetVersion); SDL_BIND(LockSurface); SDL_BIND(UnlockSurface);
    SDL_BIND(FreeSurface); SDL_BIND(CreateRGBSurfaceWithFormatFrom);
    SDL_BIND(UpperBlit); SDL_BIND(SetSurfaceBlendMode); SDL_BIND(GetRGBA);
    SDL_BIND(RenderGetScale); SDL_BIND(CreateTextureFromSurface);
    SDL_BIND(SetTextureBlendMode); SDL_BIND(SetTextureScaleMode);
    SDL_BIND(RenderCopyF); SDL_BIND(DestroyTexture);
#undef SDL_BIND
    Version version{}; GetVersion(&version);
#if defined(_WIN32)
    if(version.major!=2 || version.minor!=30 || version.patch!=0) return false;
    wchar_t module[MAX_PATH]; if(!GetModuleFileNameW(sdl,module,MAX_PATH)) return false;
    std::wstring library(module); library.erase(library.find_last_of(L"\\/")+1); library+=L"SDL2_ttf.dll";
    ttf=LoadLibraryExW(library.c_str(),nullptr,LOAD_WITH_ALTERED_SEARCH_PATH); if(!ttf) return false;
#else
    ttf=dlopen("libSDL2_ttf-2.0.so.0",RTLD_NOW|RTLD_LOCAL);
    if(!ttf) return false;
#endif
    if(!symbol(ttf,"TTF_Linked_Version",LinkedVersion)) return false;
#define TTF_BIND(name) if(!symbol(ttf,"TTF_" #name,name)) return false
    TTF_BIND(Init); TTF_BIND(Quit); TTF_BIND(OpenFontIndex); TTF_BIND(CloseFont);
    TTF_BIND(SetFontStyle); TTF_BIND(SetFontHinting); TTF_BIND(FontAscent); TTF_BIND(FontDescent);
    TTF_BIND(FontHeight); TTF_BIND(GlyphMetrics32); TTF_BIND(GlyphIsProvided32);
    TTF_BIND(SizeUTF8); TTF_BIND(RenderUTF8_Blended);
#undef TTF_BIND
#if defined(_WIN32)
    const auto* v=LinkedVersion(); if(!v || v->major!=2 || v->minor!=20 || v->patch!=2) return false;
#endif
    if(Init()!=0) return false;
    ttf_reference=true;
    return true;
}
void Sdl::shutdown() {
    if(ttf_reference) Quit();
    ttf_reference=false;
#if defined(_WIN32)
    if(ttf) FreeLibrary(ttf);
#else
    if(ttf) dlclose(ttf);
    if(sdl) dlclose(sdl);
#endif
    ttf=nullptr; sdl=nullptr;
}
namespace {
std::uint32_t pack(Color c) { return c.r|(std::uint32_t(c.g)<<8)|(std::uint32_t(c.b)<<16)|(std::uint32_t(c.a)<<24); }
bool read_glyph_surface(Sdl& api,Surface* source,Image& result) {
    // The sole caller supplies a new TTF_RenderUTF8_Blended glyph surface.
    // No native UI surface or renderer output is read by the font backend.
    if(api.LockSurface(source)!=0) return false;
    result.w=source->w; result.h=source->h; result.pixels.resize(std::size_t(result.w)*result.h);
    for(int y=0;y<result.h;++y) for(int x=0;x<result.w;++x) {
        std::uint32_t pixel{}; std::memcpy(&pixel,static_cast<const char*>(source->pixels)+std::size_t(y)*source->pitch+std::size_t(x)*source->format->bytes,source->format->bytes);
        Color color{}; api.GetRGBA(pixel,source->format,&color.r,&color.g,&color.b,&color.a); result.pixels[std::size_t(y)*result.w+x]=pack(color);
    }
    api.UnlockSurface(source); return true;
}
}
bool FontEngine::initialize(const std::string& repertoire) {
    glyphs_.clear();
    if(!api.initialize()) return false;
#if defined(_WIN32)
    wchar_t directory[MAX_PATH]; if(!GetWindowsDirectoryW(directory,MAX_PATH)) return false;
    const std::wstring file=std::wstring(directory)+L"\\Fonts\\msyhbd.ttc";
    if(!sha256(file,identity_)) return false;
    const int length=WideCharToMultiByte(CP_UTF8,0,file.c_str(),-1,nullptr,0,nullptr,nullptr);
    std::vector<char> path(length); WideCharToMultiByte(CP_UTF8,0,file.c_str(),-1,path.data(),length,nullptr,nullptr); path_=path.data();
#else
    path_=std::getenv("UWCN_FONT");
    if(!sha256(path_,identity_)) return false;
#endif
    reference_="国田永高汉翻译Agjpqy0123456789_|()[]，。！？：；、（）【】《》“”‘’·—…";
    for(int c=32;c<127;++c) reference_.push_back(static_cast<char>(c));
    reference_+=repertoire;
    std::set<std::uint32_t> seen;
    for(std::size_t i=0;i<reference_.size();) {
        const auto begin=i; std::uint32_t cp{}; if(!scalar(reference_,i,cp)) return false;
        if(cp>=32 && seen.insert(cp).second) glyphs_.push_back(reference_.substr(begin,i-begin));
    }
    return true;
}
void FontEngine::shutdown() { for(auto& f:fonts_) api.CloseFont(f->font); fonts_.clear(); glyphs_.clear(); reference_.clear(); api.shutdown(); }
bool FontEngine::baseline(Font* f,const std::string& text,int& baseline) {
    const int ascent=api.FontAscent(f); int maxy=ascent;
    // Size_Internal 3085..3120: the baseline in its complete surface includes
    // ystart=-min(0,ascent-max_glyph_top). Horizontal placement deliberately
    // uses the complete surface's layout origin, not an inferred private pen.
    for(std::size_t i=0;i<text.size();) {
        std::uint32_t cp{}; if(!scalar(text,i,cp)) return false;
        int left{},right{},bottom{},top{},advance{};
        if(!api.GlyphIsProvided32(f,cp) || api.GlyphMetrics32(f,cp,&left,&right,&bottom,&top,&advance)!=0) return false;
        maxy=std::max(maxy,top);
    }
    baseline=maxy; return true;
}
bool FontEngine::raw_coverage(CalibratedFont& f,const std::string& text,int width,GlyphCoverage& out) {
    out={};
    if(!baseline(f.font,text,out.baseline)) return false;
    if(width==0 || text.empty()) return true;
    // Blended coverage is independent of foreground RGB. Keep opaque white
    // coverage; TTF 2.20.2 interprets a supplied alpha of zero as opaque.
    auto* surface=api.RenderUTF8_Blended(f.font,text.c_str(),Color{255,255,255,255});
    if(!surface) return false;
    Image full; const bool read=read_glyph_surface(api,surface,full); api.FreeSurface(surface); if(!read) return false;
    int left=full.w,top=full.h,right=0,bottom=0;
    for(int y=0;y<full.h;++y) for(int x=0;x<full.w;++x) if(full.pixels[std::size_t(y)*full.w+x]>>24) { left=std::min(left,x); top=std::min(top,y); right=std::max(right,x+1); bottom=std::max(bottom,y+1); }
    if(right<=left || bottom<=top) return true;
    out.crop_x=left; out.crop_y=top; out.w=right-left; out.h=bottom-top;
    out.alpha.resize(std::size_t(out.w)*out.h);
    for(int y=0;y<out.h;++y) for(int x=0;x<out.w;++x) {
        out.alpha[std::size_t(y)*out.w+x]=static_cast<std::uint8_t>(full.pixels[std::size_t(y+top)*full.w+x+left]>>24);
    }
    return true;
}
bool FontEngine::sample_glyph(CalibratedFont& f,const std::string& glyph,int& top,int& bottom,bool& ink) {
    // Calibration candidates never populate the runtime text LRU.
    int width{},height{};
    if(api.SizeUTF8(f.font,glyph.c_str(),&width,&height)!=0) return false;
    GlyphCoverage coverage;
    if(!raw_coverage(f,glyph,width,coverage)) return false;
    ink=coverage.h!=0;
    top=coverage.crop_y-coverage.baseline;
    bottom=top+coverage.h;
    return true;
}
CachedText* FontEngine::find_text(CalibratedFont& f,const std::string& text) {
    for(auto i=f.texts.begin();i!=f.texts.end();++i) {
        if(i->text!=text) continue;
        f.texts.splice(f.texts.begin(),f.texts,i);
        return &f.texts.front();
    }
    return nullptr;
}
void FontEngine::cache_text(CalibratedFont& f,CachedText&& entry) {
    const auto bytes=entry.text.size()+entry.coverage.alpha.size();
    for(auto i=f.texts.begin();i!=f.texts.end();++i) {
        if(i->text!=entry.text) continue;
        f.text_bytes-=i->text.size()+i->coverage.alpha.size();
        f.texts.erase(i);
        break;
    }
    // Admission limits affect only reuse; the caller already has the complete
    // result, including text whose coverage exceeds the retained-byte budget.
    if(bytes>max_text_bytes_per_font) return;
    while(f.texts.size()>=max_texts_per_font || f.text_bytes+bytes>max_text_bytes_per_font) {
        const auto& oldest=f.texts.back();
        f.text_bytes-=oldest.text.size()+oldest.coverage.alpha.size();
        f.texts.pop_back();
    }
    f.text_bytes+=bytes;
    f.texts.push_front(std::move(entry));
}
bool FontEngine::text_width(CalibratedFont& f,const std::string& text,int& width) {
    if(const auto* cached=find_text(f,text)) { width=cached->width; return true; }
    int height{};
    if(api.SizeUTF8(f.font,text.c_str(),&width,&height)!=0) return false;
    CachedText entry;
    entry.text=text; entry.width=width;
    cache_text(f,std::move(entry));
    return true;
}
void FontEngine::colorize(int width,const GlyphCoverage& coverage,std::uint32_t color,Raster& out) {
    out.width=width; out.baseline=coverage.baseline;
    out.crop_x=coverage.crop_x; out.crop_y=coverage.crop_y;
    out.image.w=coverage.w; out.image.h=coverage.h;
    out.image.pixels.resize(coverage.alpha.size());
    const auto rgb=color&0xFFFFFF,alpha=color>>24;
    for(std::size_t i=0;i<coverage.alpha.size();++i) {
        const auto a=(std::uint32_t(coverage.alpha[i])*alpha+127)/255;
        out.image.pixels[i]=rgb|(a<<24);
    }
}
bool FontEngine::raster(CalibratedFont& f,const std::string& text,std::uint32_t color,Raster& out) {
    auto* cached=find_text(f,text);
    if(cached && cached->has_coverage) {
        colorize(cached->width,cached->coverage,color,out);
        return true;
    }
    int width{},height{};
    if(cached) width=cached->width;
    else if(api.SizeUTF8(f.font,text.c_str(),&width,&height)!=0) return false;
    CachedText entry;
    entry.text=text; entry.width=width;
    if(!raw_coverage(f,text,width,entry.coverage)) return false;
    entry.has_coverage=true;
    colorize(width,entry.coverage,color,out);
    cache_text(f,std::move(entry));
    return true;
}
void FontEngine::density_changed(double density) {
    // Retain the logical-density font and the current physical-density fonts.
    // Repeating the same density does not discard a calibrated font or its LRU.
    for(auto i=fonts_.begin();i!=fonts_.end();) {
        if((*i)->density!=1.0 && (*i)->density!=density) { api.CloseFont((*i)->font); i=fonts_.erase(i); } else ++i;
    }
}
CalibratedFont* FontEngine::font(double density,int line_height,int ink_height,int outline) {
#if defined(__linux__)
    constexpr long face=37; // Local SourceHanSans.ttc: Source Han Sans SC Bold.
#else
    constexpr long face=0;
#endif
    const int physical_line=static_cast<int>(std::floor(line_height*density));
    const int physical_ink=static_cast<int>(std::floor(ink_height*density));
    if(physical_line<1 || physical_ink<1) return nullptr;
    for(auto i=fonts_.begin();i!=fonts_.end();++i) {
        const auto& f=*i;
        if(f->density!=density || f->line_height!=line_height || f->ink_budget!=ink_height || f->outline!=outline) continue;
        std::rotate(fonts_.begin(),i,i+1);
        return fonts_.front().get();
    }
    const int border=outline?static_cast<int>(std::ceil(density)):0;
    // Descending search returns the same maximum eligible candidate without
    // assuming that hinted ink height is monotonic between point sizes.
    for(int size=physical_line*2;size>=1;--size) {
        auto f=std::make_unique<CalibratedFont>(); f->font=api.OpenFontIndex(path_.c_str(),size,face); if(!f->font) return nullptr;
        api.SetFontStyle(f->font,0); api.SetFontHinting(f->font,0);
        f->point=size; f->ascent=api.FontAscent(f->font); f->descent=api.FontDescent(f->font); f->height=api.FontHeight(f->font);
        f->top=0; f->bottom=0; f->density=density; f->line_height=line_height; f->ink_budget=ink_height; f->outline=outline;
        int top=0,bottom=0; bool first=true,fits=true;
        for(const auto& glyph:glyphs_) {
            int a{},b{}; bool ink{};
            if(!sample_glyph(*f,glyph,a,b,ink)) { api.CloseFont(f->font); return nullptr; }
            if(!ink) continue;
            if(first) { top=a; bottom=b; first=false; } else { top=std::min(top,a); bottom=std::max(bottom,b); }
            // Adding reference glyphs can only expand this candidate's union.
            if(bottom-top>physical_ink || bottom-top+2*border>physical_line) { fits=false; break; }
        }
        if(first || !fits) { api.CloseFont(f->font); continue; }
        f->top=top-border; f->bottom=bottom+border;
        if(fonts_.size()==max_fonts) { api.CloseFont(fonts_.back()->font); fonts_.pop_back(); }
        fonts_.insert(fonts_.begin(),std::move(f));
        return fonts_.front().get();
    }
    return nullptr;
}
bool FontEngine::measure(CalibratedFont& f,const std::string& text,double sx,Metrics& out) {
    int width{}; if(sx<=0 || !text_width(f,text,width)) return false;
    out={static_cast<int>(std::lround(width/sx)),width,f.point,f.ascent,f.descent,f.height,f.top,f.bottom,sx,f.density};
    return true;
}
}
