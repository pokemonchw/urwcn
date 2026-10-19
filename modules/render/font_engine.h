#pragma once
#include "render_api.h"
#include "sdl_api.h"
#include <array>
#include <cstddef>
#include <list>
#include <memory>
#include <string>
#include <vector>

namespace uwcn::render {
struct Image { int w{},h{}; std::vector<std::uint32_t> pixels; };
struct Raster {
    Image image;
    int width{},baseline{},crop_x{},crop_y{};
};
// Font-local shape data only: offsets are relative to the TTF surface, never
// native UI coordinates. Color is applied when producing the requested Raster.
struct GlyphCoverage {
    int w{},h{},baseline{},crop_x{},crop_y{};
    std::vector<std::uint8_t> alpha;
};
struct CachedText {
    std::string text;
    int width{};
    bool has_coverage{};
    GlyphCoverage coverage;
};
struct CalibratedFont {
    Font* font{};
    int point{},ascent{},descent{},height{},top{},bottom{},ink_budget{},line_height{},outline{};
    double density{};
    std::list<CachedText> texts;
    std::size_t text_bytes{};
};
class FontEngine {
public:
    Sdl api;
    bool initialize(const std::string& repertoire);
    void shutdown();
    void density_changed(double);
    // Borrowed until a later font lookup, density change or shutdown can evict it.
    CalibratedFont* font(double density,int line_height,int ink_height,int outline);
    bool raster(CalibratedFont&,const std::string&,std::uint32_t,Raster&);
    bool measure(CalibratedFont&,const std::string&,double sx,Metrics&);
    const std::array<std::uint8_t,32>& identity() const { return identity_; }
private:
    static constexpr std::size_t max_fonts=8;
    static constexpr std::size_t max_texts_per_font=256;
    static constexpr std::size_t max_text_bytes_per_font=8*1024*1024;
    std::string path_,reference_;
    std::vector<std::string> glyphs_;
    std::vector<std::unique_ptr<CalibratedFont>> fonts_;
    std::array<std::uint8_t,32> identity_{};
    bool baseline(Font*,const std::string&,int&);
    bool raw_coverage(CalibratedFont&,const std::string&,int,GlyphCoverage&);
    bool sample_glyph(CalibratedFont&,const std::string&,int&,int&,bool&);
    CachedText* find_text(CalibratedFont&,const std::string&);
    void cache_text(CalibratedFont&,CachedText&&);
    bool text_width(CalibratedFont&,const std::string&,int&);
    static void colorize(int,const GlyphCoverage&,std::uint32_t,Raster&);
};
}
