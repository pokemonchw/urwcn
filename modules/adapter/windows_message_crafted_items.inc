// PE 3.89 persistent descriptor-name grammar. 4C0AC0 stores the entire native
// 0xAC record, and 4C0110/4C0190 copy that record back without retaining a
// construction call frame. These readers recover its English source grammar;
// they never store a Chinese value in the record or a translated name cache.
namespace windows_message_crafted_items {
struct Atom { const char* source;const char* domain; };
struct Pattern { const char* source; };
struct Wood { const char* source;const char* pattern;const char* tree; };
#include "windows_message_crafted_item_atoms.inc"

MessageText lookup(const char* domain,const std::string& source) {
    return native_message_source::lookup(TextComponent::message_value,source,domain);
}
bool material(const std::string& source,MessageText& output);
bool capture(const std::string& source,const char* pattern,std::string& value) {
    const std::string syntax(pattern);
    const auto marker=syntax.find("%s");
    const auto prefix=syntax.substr(0,marker);
    const auto suffix=syntax.substr(marker+2);
    if(source.size()<=prefix.size()+suffix.size() ||
        source.compare(0,prefix.size(),prefix)!=0 ||
        source.compare(source.size()-suffix.size(),suffix.size(),suffix)!=0) return false;
    value=source.substr(prefix.size(),source.size()-prefix.size()-suffix.size());return true;
}
bool material(const std::string& source,MessageText& output) {
    for(const auto& atom:atoms) if(source==atom.source) {
        output=lookup(atom.domain,source);return true;
    }
    // Exact wood replacements performed at 451C5B/451D3E. A translated word
    // is never sliced to reproduce the original English replacement offsets.
    for(const auto& wood:woods) if(source==wood.source) {
        output=native_message_source::format(lookup("crafted-wood-format",wood.pattern),
            {lookup("tree",wood.tree)},{"%s"});output.original=source;return true;
    }
    for(const auto& pattern:crafted_patterns) {
        std::string argument;MessageText child;
        if(capture(source,pattern.source,argument) && material(argument,child)) {
            output=native_message_source::format(lookup("crafted-name-format",pattern.source),
                {std::move(child)},{"%s"});output.original=source;return true;
        }
    }
    // 467A30 requests count=1, flags=4. That native mode suppresses quality
    // and hook/string text; spoiled/rotten and winter still participate.
    for(const auto* prefix:{"spoiled ","rotten "}) {
        const auto length=std::strlen(prefix);
        if(source.compare(0,length,prefix)==0) {
            MessageText child;
            if(material(source.substr(length),child)) {
                const auto* key=*prefix=='s' ? "Spoiled " : "Rotten ";
                output=native_message_source::concat({lookup("item",key),std::move(child)});
                output.original=source;return true;
            }
        }
    }
    for(const auto* pattern:{"winter %s","slender %s trunk","block of %s wood"}) {
        std::string argument;MessageText child;
        if(capture(source,pattern,argument) && material(argument,child)) {
            output=native_message_source::format(lookup("item",pattern),{std::move(child)},{"%s"});
            output.original=source;return true;
        }
    }
    // 51CEC0 / 51E9D0 and the cleaning/dehairing branches preserve the
    // actual species atom in descriptor +0x31. Its native 25-byte spelling
    // has a dedicated inventory; it is never a creature's proper-name field.
    for(const auto* pattern:{"%s-skin","clean %s-skin","De-haired %s-skin",
                            "de-haired %s-skin","%s fur","%s leather","%s cut"}) {
        std::string argument;
        if(capture(source,pattern,argument)) {
            for(const auto& animal:animals) if(argument==animal) {
                output=native_message_source::format(lookup("crafted-animal-format",pattern),
                    {lookup("material.animal",argument)},{"%s"});output.original=source;return true;
            }
        }
    }
    // Native 451B51 prepends a concrete tree atom to the concrete base name.
    for(const auto* tree:trees) {
        const std::string prefix=std::string(tree)+" ";
        if(source.compare(0,prefix.size(),prefix)!=0) continue;
        MessageText child;
        if(material(source.substr(prefix.size()),child)) {
            output=native_message_source::format(lookup("item","%s %s"),
                {lookup("tree",tree),std::move(child)},{"%s","%s"});output.original=source;return true;
        }
    }
    return false;
}
}

Status message_material_source(const char* original,MessageText& output) {
    return windows_message_crafted_items::material(message_source_utf8(original),output) ?
        Status::ok : Status::unavailable;
}
Status message_crafted_item_source(const unsigned char* descriptor,const char* original,MessageText& output) {
    u32 id;std::memcpy(&id,descriptor+4,sizeof(id));
    if(id==0x19a || id==0x19c || id==0x19d || id==0x19f || id==0x1f4) {
        return message_material_source(original,output);
    }
    // +0x93 is the native naming selector: zero uses the base inventory;
    // one retains the supplied/generated +9 name. Flora selectors >=2 are
    // applied later by 451770 itself, after this same base-name boundary.
    if(descriptor[0x93]!=1) {
        output=message_source_lookup("item",original);return Status::ok;
    }
    return message_material_source(original,output);
}
