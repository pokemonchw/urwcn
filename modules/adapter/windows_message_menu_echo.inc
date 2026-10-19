// PE 3.89 upper menu rows and their 5002B0 message echo. These rows belong to
// 659F988 / stride 20C, not the lower CF790 component's E8 entries.
// Only native row identity and text expressions are retained. Native builders
// still choose rows, actions, limits, descriptions and all UI geometry.
// Evidence: settlement-menu-builders-ghidra.c, menu-callers-ghidra.c,
// menu-label-sources.tsv, menu-clip-refs.tsv and menu-echo-disassembly.txt.
namespace windows_message_menu_echo {
enum class SourceKind:u32 { label,empty,bound,section,treatment,bodypart };
struct Site {u32 site,target,words;SourceKind kind;};
constexpr u32 source_first=0xe200,clip_first=0xe300,title_first=0xe370;
const Site sources[]={
    {0x5e12,0xffcc0,1,SourceKind::bound},
    {0x5e5a,0xffcc0,1,SourceKind::bound},
    {0x5ea3,0xffcc0,1,SourceKind::bound},
    {0x5ef3,0xffcc0,1,SourceKind::bound},
    {0x5f43,0xffcc0,1,SourceKind::bound},
    {0x5f93,0xffcc0,1,SourceKind::bound},
    {0x5fd7,0xffcc0,1,SourceKind::empty},
    {0x5ff7,0xffd60,2,SourceKind::bound},
    {0x6017,0xffd60,2,SourceKind::bound},
    {0x605c,0xffcc0,1,SourceKind::label},
    {0x6098,0xffcc0,1,SourceKind::empty},
    {0x60b1,0xffd60,2,SourceKind::label},
    {0x60f9,0xffcc0,1,SourceKind::bound},
    {0x6143,0xffcc0,1,SourceKind::bound},
    {0x6193,0xffcc0,1,SourceKind::bound},
    {0x61d7,0xffcc0,1,SourceKind::empty},
    {0x6236,0x10d0,4,SourceKind::label},
    {0x3264b,0xffcc0,1,SourceKind::bound},
    {0x32669,0xffcc0,1,SourceKind::bound},
    {0x32687,0xffcc0,1,SourceKind::bound},
    {0x326a2,0xffcc0,1,SourceKind::bound},
    {0x3896e,0xffcc0,1,SourceKind::bound},
    {0x38982,0xffcc0,1,SourceKind::label},
    {0x389e4,0x10d0,4,SourceKind::empty},
    {0x38a74,0x10d0,4,SourceKind::label},
    {0x38b04,0x10d0,4,SourceKind::label},
    {0x38b94,0x10d0,4,SourceKind::label},
    {0x38c24,0x10d0,4,SourceKind::label},
    {0x38cb4,0x10d0,4,SourceKind::label},
    {0x38d0f,0xffb30,0,SourceKind::section},
    {0x38d76,0x10d0,4,SourceKind::empty},
    {0x38dba,0xffcc0,1,SourceKind::bound},
    {0x38dcf,0xffcc0,1,SourceKind::bound},
    {0x38de4,0xffcc0,1,SourceKind::bound},
    {0x38f5c,0xffcc0,1,SourceKind::label},
    {0x43033,0xffd60,2,SourceKind::bound},
    {0x43201,0xfff30,2,SourceKind::bound},
    {0x432c0,0xffd60,2,SourceKind::bound},
    {0x4332f,0xfff30,2,SourceKind::bound},
    {0x433ec,0xfff30,2,SourceKind::bound},
    {0x45c44,0x10d0,4,SourceKind::label},
    {0x45cd4,0x10d0,4,SourceKind::label},
    {0x45d64,0x10d0,4,SourceKind::label},
    {0x45df4,0x10d0,4,SourceKind::label},
    {0x45e39,0xffcc0,1,SourceKind::empty},
    {0x45e4e,0xffcc0,1,SourceKind::bound},
    {0x466a2,0xffcc0,1,SourceKind::bound},
    {0x466ea,0xffcc0,1,SourceKind::bound},
    {0x46733,0xffcc0,1,SourceKind::bound},
    {0x46793,0xffcc0,1,SourceKind::label},
    {0x46824,0x10d0,4,SourceKind::empty},
    {0x46875,0xffcc0,1,SourceKind::bound},
    {0x468c3,0xffcc0,1,SourceKind::bound},
    {0x46913,0xffcc0,1,SourceKind::bound},
    {0x46a24,0x10d0,4,SourceKind::label},
    {0x46ae4,0x10d0,4,SourceKind::label},
    {0x46b4e,0xffcc0,1,SourceKind::bound},
    {0x46bf4,0x10d0,4,SourceKind::empty},
    {0x46c3c,0xffcc0,1,SourceKind::bound},
    {0x46c51,0xffcc0,1,SourceKind::bound},
    {0x46cb4,0x10d0,4,SourceKind::empty},
    {0x46d44,0x10d0,4,SourceKind::label},
    {0x47b94,0x10d0,4,SourceKind::label},
    {0x47c24,0x10d0,4,SourceKind::label},
    {0x47cb4,0x10d0,4,SourceKind::label},
    {0x47d44,0x10d0,4,SourceKind::label},
    {0x47dd4,0x10d0,4,SourceKind::label},
    {0x47e64,0x10d0,4,SourceKind::label},
    {0x47ef4,0x10d0,4,SourceKind::label},
    {0x47f84,0x10d0,4,SourceKind::label},
    {0x48014,0x10d0,4,SourceKind::label},
    {0x480a4,0x10d0,4,SourceKind::label},
    {0x48134,0x10d0,4,SourceKind::label},
    {0x481c4,0x10d0,4,SourceKind::label},
    {0x48254,0x10d0,4,SourceKind::label},
    {0x482af,0xffb30,0,SourceKind::section},
    {0x48324,0x10d0,4,SourceKind::label},
    {0x483c0,0xffcc0,1,SourceKind::bound},
    {0x4843c,0xffcc0,1,SourceKind::bound},
    {0x484f4,0x10d0,4,SourceKind::empty},
    {0x48545,0xffcc0,1,SourceKind::bound},
    {0x48563,0xffcc0,1,SourceKind::bound},
    {0x48634,0x10d0,4,SourceKind::empty},
    {0x48685,0xffcc0,1,SourceKind::bound},
    {0x486a3,0xffcc0,1,SourceKind::bound},
    {0x486f3,0xffcc0,1,SourceKind::bound},
    {0x4870f,0xffcc0,1,SourceKind::empty},
    {0x4872d,0xffcc0,1,SourceKind::bound},
    {0x489fc,0xffb30,0,SourceKind::section},
    {0x531c7,0xffb30,0,SourceKind::label},
    {0x53244,0x10d0,4,SourceKind::label},
    {0x532d4,0x10d0,4,SourceKind::empty},
    {0x53319,0xffb30,0,SourceKind::label},
    {0xa36c4,0x10d0,4,SourceKind::label},
    {0xa3774,0x10d0,4,SourceKind::label},
    {0xa3814,0x10d0,4,SourceKind::label},
    {0xa38b4,0x10d0,4,SourceKind::label},
    {0xa3954,0x10d0,4,SourceKind::label},
    {0xa3a24,0x10d0,4,SourceKind::label},
    {0xa3ab4,0x10d0,4,SourceKind::empty},
    {0xa3b44,0x10d0,4,SourceKind::label},
    {0xa3bf4,0x10d0,4,SourceKind::label},
    {0xa3c3e,0xffcc0,1,SourceKind::label},
    {0xd8ec7,0x10d0,4,SourceKind::treatment},
    {0xd8fa4,0x10d0,4,SourceKind::treatment},
    {0xd9074,0x10d0,4,SourceKind::treatment},
    {0xd9124,0x10d0,4,SourceKind::treatment},
    {0xd91d5,0x10d0,4,SourceKind::treatment},
    {0xd92d4,0x10d0,4,SourceKind::treatment},
    {0xf8d97,0xffb30,0,SourceKind::bound},
    {0x108794,0x10d0,4,SourceKind::label},
    {0x108834,0x10d0,4,SourceKind::label},
    {0x1088a4,0x10d0,4,SourceKind::label},
    {0x108944,0x10d0,4,SourceKind::label},
    {0x1089d7,0x10d0,4,SourceKind::label},
    {0x108a87,0x10d0,4,SourceKind::label},
    {0x118aa5,0x10d0,4,SourceKind::label},
    {0x118b44,0x10d0,4,SourceKind::label},
    {0x11b328,0xffcc0,1,SourceKind::bound},
    {0x11b343,0xffcc0,1,SourceKind::bound},
    {0x11b35e,0xffcc0,1,SourceKind::bound},
    {0x11b379,0xffcc0,1,SourceKind::bound},
    {0x11b394,0xffcc0,1,SourceKind::bound},
    {0x11b3af,0xffcc0,1,SourceKind::bound},
    {0x11b3ca,0xffcc0,1,SourceKind::bound},
    {0x121de8,0xffcc0,1,SourceKind::bound},
    {0x121e03,0xffcc0,1,SourceKind::bound},
    {0x121e1e,0xffcc0,1,SourceKind::bound},
    {0x121e39,0xffcc0,1,SourceKind::bound},
    {0x121e54,0xffcc0,1,SourceKind::bound},
    {0x121e6f,0xffcc0,1,SourceKind::bound},
    {0x121eb8,0xffcc0,1,SourceKind::bound},
    {0x121ed3,0xffcc0,1,SourceKind::bound},
    {0x121eee,0xffcc0,1,SourceKind::bound},
    {0x121f09,0xffcc0,1,SourceKind::bound},
    {0x121f24,0xffcc0,1,SourceKind::bound},
    {0x12c676,0x10d0,4,SourceKind::label},
    {0x12c744,0x10d0,4,SourceKind::label},
    {0x12c814,0x10d0,4,SourceKind::label},
    {0x12cea4,0x10d0,4,SourceKind::label},
    {0x12cf58,0x10d0,4,SourceKind::bound},
    {0x12d016,0x10d0,4,SourceKind::bound},
    {0x12d0c9,0x10d0,4,SourceKind::bound},
    {0x12d215,0xffb30,0,SourceKind::bodypart},
    {0x12d31f,0xffb30,0,SourceKind::bodypart},
    {0x12d41f,0xffb30,0,SourceKind::bodypart},
    {0x12d51f,0xffb30,0,SourceKind::bodypart},
    {0x12ec35,0x10d0,4,SourceKind::label},
    {0x12ed06,0x10d0,4,SourceKind::bound},
    {0x12edd7,0x10d0,4,SourceKind::bound},
    {0x12eea8,0x10d0,4,SourceKind::bound},
    {0x12ef64,0x10d0,4,SourceKind::label},
    {0x12eff4,0x10d0,4,SourceKind::empty},
    {0x12f084,0x10d0,4,SourceKind::label},
    {0x12f924,0x10d0,4,SourceKind::label},
    {0x12f9b4,0x10d0,4,SourceKind::label},
    {0x12fa44,0x10d0,4,SourceKind::label},
    {0x12fad4,0x10d0,4,SourceKind::label},
    {0x1435a6,0x10d0,4,SourceKind::label},
    {0x1436c8,0x10d0,4,SourceKind::label},
    {0x1437b4,0x10d0,4,SourceKind::label},
    {0x143864,0x10d0,4,SourceKind::label},
    {0x143916,0x10d0,4,SourceKind::label},
    {0x1439e4,0x10d0,4,SourceKind::label},
    {0x143ac4,0x10d0,4,SourceKind::empty},
    {0x143b64,0x10d0,4,SourceKind::label},
    {0x143c04,0x10d0,4,SourceKind::label},
    {0x145324,0x10d0,4,SourceKind::label},
    {0x1453b4,0x10d0,4,SourceKind::empty},
    {0x145444,0x10d0,4,SourceKind::label},
    {0x1454d4,0x10d0,4,SourceKind::label},
    {0x145564,0x10d0,4,SourceKind::label},
    {0x1455f4,0x10d0,4,SourceKind::empty},
    {0x145684,0x10d0,4,SourceKind::label},
    {0x145714,0x10d0,4,SourceKind::label},
    {0x1457a4,0x10d0,4,SourceKind::label},
    {0x145834,0x10d0,4,SourceKind::empty},
    {0x1458e5,0x10d0,4,SourceKind::label},
    {0x145954,0x10d0,4,SourceKind::label},
    {0x1459f6,0x10d0,4,SourceKind::label},
    {0x145a94,0x10d0,4,SourceKind::empty},
    {0x145b34,0x10d0,4,SourceKind::label},
    {0x145c25,0x10d0,4,SourceKind::label},
    {0x146820,0xffb30,0,SourceKind::bound},
    {0x146894,0x10d0,4,SourceKind::empty},
    {0x146924,0x10d0,4,SourceKind::label},
};
struct ClipSite {u32 site;bool ebx;};
const ClipSite clips[]={
    {0x12faee,false},
    {0x12fa5e,false},
    {0x12f9ce,false},
    {0x12f93e,false},
    {0x38d8f,false},
    {0x38cce,false},
    {0x38c3e,false},
    {0x38bae,false},
    {0x38b1e,false},
    {0x38a8e,false},
    {0x389fe,false},
    {0x46d5e,false},
    {0x46cce,false},
    {0x46c0e,false},
    {0x46afe,false},
    {0x46a3e,false},
    {0xd92ee,false},
    {0xd91ee,false},
    {0xd913e,false},
    {0xd908e,false},
    {0xd8fbe,false},
    {0xd8ee0,false},
    {0x4864e,false},
    {0x4850e,false},
    {0x4833e,false},
    {0x4826e,false},
    {0x481de,false},
    {0x4814e,false},
    {0x480be,false},
    {0x4802e,false},
    {0x47f9e,false},
    {0x47f0e,false},
    {0x47e7e,false},
    {0x47dee,false},
    {0x47d5e,false},
    {0x47cce,false},
    {0x47c3e,false},
    {0x47bae,false},
    {0xffbff,false},
    {0x45e0e,false},
    {0x45d7e,false},
    {0x45cee,false},
    {0x45c5e,false},
    {0x624f,true},
    {0x12d0e2,true},
    {0x12d02f,true},
    {0x12cf71,true},
    {0x12cebe,true},
    {0x12c82e,false},
    {0x12c75e,false},
    {0x12c68f,false},
    {0x532ee,true},
    {0x5325e,true},
    {0x145b4e,true},
    {0x145c3e,true},
    {0x145aae,true},
    {0x145a0f,true},
    {0x14596e,true},
    {0x14584e,true},
    {0x1457be,true},
    {0x14572e,true},
    {0x14569e,true},
    {0x14560e,true},
    {0x14557e,true},
    {0x1454ee,true},
    {0x14545e,true},
    {0x1453ce,true},
    {0x14533e,true},
    {0x14693e,true},
    {0x1468ae,true},
    {0x143b7e,true},
    {0x143c1e,true},
    {0x143ade,true},
    {0x1439fe,false},
    {0x1437ce,false},
    {0x14392f,false},
    {0x14387e,false},
    {0x1436e1,false},
    {0x1435bf,true},
    {0x12f09e,true},
    {0x12f00e,true},
    {0x12ef7e,true},
    {0x12eec1,true},
    {0x12edf0,true},
    {0x12ed1f,true},
    {0x12ec4e,true},
    {0xa3c0e,false},
    {0xa3b5e,false},
    {0xa3ace,false},
    {0xa3a3e,false},
    {0xa396e,false},
    {0xa38ce,false},
    {0xa382e,false},
    {0xa378e,false},
    {0xa36de,false},
    {0x4683e,false},
    {0x118b5e,true},
    {0x118abe,true},
    {0x108ab0,false},
    {0x108a00,false},
    {0x10895e,false},
    {0x1088be,false},
    {0x1087ae,false},
};
const u32 titles[]={
    0x62a3,
    0x326c3,
    0x38e3e,
    0x38eb3,
    0x38eee,
    0x38fce,
    0x45e6d,
    0x45eb2,
    0x4695c,
    0x46dbb,
    0x46e09,
    0x46e3d,
    0x48376,
    0x483ee,
    0x487ee,
    0x48a23,
    0x48a88,
    0x53323,
    0xa3c55,
    0xd934c,
    0xf8da6,
    0x108ae0,
    0x118b98,
    0x11b3e1,
    0x121e90,
    0x121f45,
    0x122375,
    0x1223be,
    0x12c8c7,
    0x12d564,
    0x12f0d8,
    0x12fb28,
    0x143caa,
    0x145bab,
    0x14696e,
};
enum Hook:u32 { clear_rows=0xe3a0,row_main,row_special,row_key_zero,row_action,
    row_icon,row_recipe,terrain_label,echo_format,echo_clear,echo_separator,echo_display,
    animal_title,recipe_count_cook,recipe_count_diy,recipe_join_generic,
    recipe_join_item,recipe_join_override,cook_copy,cook_append,biy_copy,biy_override,
    aim_head,aim_arms,aim_legs,defense_block,defense_first,defense_second,
    npc_case_capture,npc_case_complete };
struct Row {MessageText source;std::string native;bool clipped{};u32 writer{};};
struct Input {MessageText source;SourceKind kind{};u32 owner{},site{},parent_frame{};Status status=Status::ok;};
struct Echo {MessageText title,source;Status status=Status::ok;};
std::map<u32,Row> rows;
std::vector<Input> inputs;
std::vector<Echo> echoes;
// Temporary selected recipe text is attached to its actual native EBP frame.
std::map<u32,MessageText> recipes;
std::vector<Input> formats;

MessageText select_source(SourceKind kind,const char* native) {
    switch(kind) {
    case SourceKind::label:return message_source_lookup("menu.label",native);
    case SourceKind::empty:return message_source_identity(native);
    case SourceKind::bound:return message_source_bound(native);
    case SourceKind::section:return message_source_lookup("menu.section",native);
    case SourceKind::treatment:return message_source_lookup("treatment",native);
    case SourceKind::bodypart: {
        // 52D215/31F/41F/51F copy this same native resource result and only
        // uppercase the first byte before passing their local to 4FFB30.
        auto source=message_source_bound(at<char>(0xa224eb0));
        source.original=message_source_utf8(native);return source;
    }
    }
    return {};
}
void save_row(u32 owner,const Input& input) {
    rows[owner]={input.source,ptr<char>(owner),false,input.site};
}
bool owns_builder(const NativeEvent& event) {
    // The four builders are also called by other native UI components.
    // Only a captured parent CALL owns this echo source scope.
    return !inputs.empty() && *ptr<u32>(event.frame->ebp)==inputs.back().parent_frame;
}
MessageText menu_format(const char* pattern,std::vector<MessageText> values,
                        std::vector<std::string> syntax) {
    return native_message_source::format(message_source_lookup("menu.format",pattern),
        std::move(values),std::move(syntax));
}
std::string native_visible_prefix(const char* full,std::size_t native_bytes) {
    // The menu's original byte cut can bisect a UTF-8 name scalar. Decode
    // against the original complete name using the existing native parser
    // codec, so a partial UTF-8 sequence cannot become legacy byte glyphs.
    const auto* begin=reinterpret_cast<const unsigned char*>(full);
    std::string result;
    for(std::size_t offset=0;offset<native_bytes;) {
        const auto bytes=native_name_input::span(begin+offset);
        if(bytes) {
            if(offset+bytes>native_bytes)break;
            result.append(reinterpret_cast<const char*>(begin+offset),bytes);offset+=bytes;
        } else {append_utf8(result,native_name_input::native_scalar(begin[offset]));++offset;}
    }
    return result;
}
Status visible_prefix(const MessageText& source,std::size_t visible,MessageText& result) {
    // This is the source prefix selected by the real native row terminator.
    // It is not a limit on Chinese bytes or glyphs. Lookup-prefix entries are
    // authored for each finite original leaf: unfinished words have no added
    // meaning, while the caller retains the native '..'.
    using Kind=native_message_source::Kind;
    if(visible==source.original.size()) {result=source;return Status::ok;}
    switch(source.kind) {
    case Kind::original:
        result=native_message_source::original(source.original.substr(0,visible));return Status::ok;
    case Kind::lookup: {
        const auto domain="menu.prefix."+source.key+"/"+source.original;
        const auto prefix=source.original.substr(0,visible);
        result=native_message_source::lookup(TextComponent::message_value,prefix,domain);return Status::ok;
    }
    case Kind::concat: {
        std::vector<MessageText> children;
        for(const auto& child:source.children) {
            if(visible==0)break;
            const auto amount=std::min(visible,child.original.size());MessageText part;
            const auto status=visible_prefix(child,amount,part);if(status!=Status::ok)return status;
            children.push_back(std::move(part));visible-=amount;
        }
        result=native_message_source::concat(std::move(children));return Status::ok;
    }
    case Kind::format: {
        // These native menu producers use %s exclusively. Retain only the
        // format literals and actual argument spans that precede the native
        // cut; reduced literal forms have their own explicit translations.
        const auto& pattern=source.children.front().original;
        std::string prefix;std::vector<MessageText> children;
        std::vector<std::string> conversions;std::size_t cursor=0;
        for(std::size_t index=0;index<source.syntax.size() && visible!=0;++index) {
            const auto position=pattern.find(source.syntax[index],cursor);
            const auto literal=position-cursor,amount=std::min(visible,literal);
            prefix+=pattern.substr(cursor,amount);visible-=amount;
            if(amount!=literal || visible==0) {cursor=position;break;}
            const auto& child=source.children[index+1];
            const auto child_amount=std::min(visible,child.original.size());MessageText part;
            const auto status=visible_prefix(child,child_amount,part);if(status!=Status::ok)return status;
            prefix+=source.syntax[index];conversions.push_back(source.syntax[index]);children.push_back(std::move(part));
            visible-=child_amount;cursor=position+source.syntax[index].size();
            if(child_amount!=child.original.size())break;
        }
        if(visible!=0)prefix+=pattern.substr(cursor,visible);
        const auto grammar_domain="menu.prefix.format/"+pattern;
        auto reduced=prefix==pattern?source.children.front():message_source_lookup(grammar_domain.c_str(),prefix.c_str());
        result=native_message_source::format(std::move(reduced),std::move(children),std::move(conversions));return Status::ok;
    }
    default:return Status::invalid;
    }
}
void save(std::vector<unsigned char>& state) {
    message_state_write(state,static_cast<u32>(rows.size()));
    for(const auto& [owner,row]:rows) {
        message_state_write(state,owner);message_state_string(state,row.native);
        message_state_write(state,row.clipped);
        message_state_write(state,row.writer);native_message_source::write(state,row.source);
    }
    for(const auto* stack:{&inputs,&formats}) {
        message_state_write(state,static_cast<u32>(stack->size()));
        for(const auto& input:*stack) {
            message_state_write(state,input.kind);message_state_write(state,input.owner);
            message_state_write(state,input.site);message_state_write(state,input.parent_frame);
            message_state_write(state,input.status);
            native_message_source::write(state,input.source);
        }
    }
    message_state_write(state,static_cast<u32>(echoes.size()));
    for(const auto& echo:echoes) {message_state_write(state,echo.status);
        native_message_source::write(state,echo.title);native_message_source::write(state,echo.source);}
    message_state_write(state,static_cast<u32>(recipes.size()));
    for(const auto& [frame,source]:recipes) {message_state_write(state,frame);native_message_source::write(state,source);}
}
void restore(const unsigned char*& state) {
    u32 count{};message_state_read(state,count);rows.clear();
    for(u32 i=0;i<count;++i) {u32 owner{};message_state_read(state,owner);auto& row=rows[owner];
        message_state_string(state,row.native);message_state_read(state,row.clipped);message_state_read(state,row.writer);
        row.source=native_message_source::read(state);}
    for(auto* stack:{&inputs,&formats}) {
        message_state_read(state,count);stack->resize(count);
        for(auto& input:*stack) {message_state_read(state,input.kind);message_state_read(state,input.owner);
            message_state_read(state,input.site);message_state_read(state,input.parent_frame);
            message_state_read(state,input.status);
            input.source=native_message_source::read(state);}
    }
    message_state_read(state,count);echoes.resize(count);
    for(auto& echo:echoes) {message_state_read(state,echo.status);echo.title=native_message_source::read(state);
        echo.source=native_message_source::read(state);}
    message_state_read(state,count);recipes.clear();
    for(u32 i=0;i<count;++i) {u32 frame{};message_state_read(state,frame);recipes.emplace(frame,native_message_source::read(state));}
}
void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;using native_name_input::native_call;
    for(u32 index=0;index<std::size(sources);++index) {
        const auto& source=sources[index];
        hooks.push_back(native_call(source_first+index,source.site,source.target,source.words));
    }
    for(u32 index=0;index<std::size(clips);++index) {
        const auto& clip=clips[index];
        auto hook=instruction(clip_first+index,clip.site,{0x66,0xc7,
            static_cast<unsigned char>(clip.ebx?0x83:0x87),0,0,0,0,0x2e,0x2e});
        const auto target=address(at<char>(0x619f9a8));std::memcpy(hook.expected+3,&target,4);hooks.push_back(hook);
    }
    for(u32 index=0;index<std::size(titles);++index)
        hooks.push_back(native_call(title_first+index,titles[index],0x1002b0,0));
    auto clear=instruction(clear_rows,0xffaa1,{0xbe,0,0,0,0});
    const auto table=address(at<char>(0x619fa50));std::memcpy(clear.expected+1,&table,4);hooks.push_back(clear);
    struct Call {u32 id,site,target,words;};
    for(const auto& call:{Call{row_main,0xffba7,0x10d0,4},
        Call{row_special,0xffbe4,0x10d0,3},Call{row_key_zero,0xffc32,0x10d0,4},
        Call{row_action,0xffd21,0x10d0,4},Call{row_icon,0xffe60,0x10d0,4},
        Call{row_recipe,0xfffa1,0x10d0,4},Call{terrain_label,0xffe1c,0x76c0,0},
        Call{echo_format,0x100846,0x10d0,4},Call{echo_clear,0x100871,0x18ae60,3},
        Call{animal_title,0x143c64,0x10d0,3},
        Call{recipe_count_cook,0x431a8,0x10d0,3},Call{recipe_count_diy,0x4326e,0x10d0,3},
        Call{recipe_join_generic,0x432ab,0x10d0,4},Call{recipe_join_item,0x4330f,0x10d0,4},
        Call{recipe_join_override,0x433cc,0x10d0,4},
        Call{aim_head,0x12cef7,0x10d0,3},Call{aim_arms,0x12cfaa,0x10d0,3},
        Call{aim_legs,0x12d068,0x10d0,3},Call{defense_block,0x12eca5,0x10d0,3},
        Call{defense_first,0x12ed76,0x10d0,3},Call{defense_second,0x12ee47,0x10d0,3}})
        hooks.push_back(native_call(call.id,call.site,call.target,call.words));
    hooks.push_back(instruction(echo_separator,0x1008a2,{0xc6,0x44,0x04,0x38,0x00}));
    // Native ECX now identifies the finalized echo. F6510 retains its normal
    // entry/display observer; this observes only this particular caller.
    hooks.push_back(native_call(echo_display,0x1008ab,0xf6510,0));
    auto cook=instruction(cook_copy,0x4313d,{0xba,0,0,0,0});
    const auto quantity=address(at<char>(0x1964f4));std::memcpy(cook.expected+1,&quantity,4);hooks.push_back(cook);
    auto append=instruction(cook_append,0x431de,{0x8b,0x35,0,0,0,0});
    const auto strstr_iat=address(at<char>(0x18c350));std::memcpy(append.expected+2,&strstr_iat,4);hooks.push_back(append);
    auto biy=instruction(biy_copy,0x42fa4,{0xba,0,0,0,0});
    const auto quoted=address(at<char>(0x1964e0));std::memcpy(biy.expected+1,&quoted,4);hooks.push_back(biy);
    hooks.push_back(instruction(biy_override,0x43004,{0x33,0xc9,0x66,0x66,0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00}));
    hooks.push_back(instruction(npc_case_capture,0x14680e,{0x8b,0xf0,0x0f,0xb6,0x0e}));
    hooks.push_back(instruction(npc_case_complete,0x14681b,{0x8d,0x4f,0x41,0x8b,0xd6}));
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    const bool source_event=event.id>=source_first && event.id<source_first+std::size(sources);
    const bool clip_event=event.id>=clip_first && event.id<clip_first+std::size(clips);
    const bool title_event=event.id>=title_first && event.id<title_first+std::size(titles);
    handled=source_event || clip_event || title_event || (event.id>=clear_rows && event.id<=npc_case_complete);
    if(!handled)return Status::ok;
    if(source_event) {
        const auto& site=sources[event.id-source_first];
        if(event.phase==NativePhase::before) {
            const auto* native=ptr<char>(site.target==0x10d0?event.arguments[3]:event.frame->edx);
            Input input{select_source(site.kind,native),site.kind,0,site.site,event.frame->ebp};
            if(site.site==0x43033 || site.site==0x43201)input.source=recipes.at(event.frame->ebp);
            if(site.target==0x10d0)input.owner=event.arguments[0];
            inputs.push_back(std::move(input));
        } else {
            if(site.target==0x10d0)save_row(inputs.back().owner,inputs.back());
            if(site.site==0x43033 || site.site==0x43201)recipes.erase(event.frame->ebp);
            inputs.pop_back();
        }
        return Status::ok;
    }
    if(clip_event) {
        const auto& clip=clips[event.id-clip_first];
        if(clip.site==0xffbff && !owns_builder(event))return Status::ok;
        const auto owner=address(at<char>(0x619f988))+(clip.ebx?event.frame->ebx:event.frame->edi);
        rows.at(owner).clipped=true;return Status::ok;
    }
    if(title_event) {
        if(event.phase==NativePhase::before) {
            Echo echo;const auto site=titles[event.id-title_first];
            const auto* title=ptr<char>(event.frame->ecx);
            if(site==0x38fce || site==0x487ee || site==0x48a88)
                echo.title=message_source_lookup("menu.section",title);
            else if(site==0x143caa && std::strcmp(title,"ANIMAL GROUP COMMANDS")!=0)
                echo.title=message_source_bound(title);
            else echo.title=message_source_lookup("menu.title",title);
            echoes.push_back(std::move(echo));
        } else echoes.pop_back();
        return Status::ok;
    }
    switch(event.id) {
    case npc_case_capture: {
        // 546819 changes only the first native byte of 4AD4F0's actual result.
        Input input;input.source=message_source_bound(ptr<char>(event.frame->eax));
        formats.push_back(std::move(input));return Status::ok;
    }
    case npc_case_complete:
        message_bind_source(ptr<char>(event.frame->esi),formats.back().source);
        formats.pop_back();return Status::ok;
    case clear_rows:rows.clear();return Status::ok;
    case terrain_label:
        if(!owns_builder(event))return Status::ok;
        if(event.phase==NativePhase::after)inputs.back().source=message_source_lookup("terrain",ptr<char>(event.frame->eax));
        return Status::ok;
    case row_main:case row_special:case row_key_zero:case row_action:case row_icon:case row_recipe:
        if(!owns_builder(event))return Status::ok;
        if(event.phase==NativePhase::before)inputs.back().owner=event.arguments[0];
        else save_row(inputs.back().owner,inputs.back());
        // The real key-zero sprintf overwrites the earlier 34-byte result;
        // save_row consequently clears its earlier clipped marker.
        return Status::ok;
    case echo_format:
        if(event.phase==NativePhase::before) {
            auto& echo=echoes.back();const auto owner=address(at<char>(0x619f988))+event.frame->edi;
            const auto& row=rows.at(owner);auto selected=row.source;
            if(row.clipped) {
                // 500834 points past the actual row key and period. The row
                // already contains the native two dots and NUL at 32/34;
                // take precisely the visible native caption before them.
                const std::string caption=ptr<char>(event.arguments[3]);
                const auto* full_caption=row.native.c_str()+row.native.find('.')+1;
                const auto prefix=native_visible_prefix(full_caption,caption.size()-2);
                echo.status=visible_prefix(row.source,prefix.size(),selected);
                if(echo.status!=Status::ok)return echo.status;
                selected=native_message_source::concat({std::move(selected),native_message_source::original("..")});
            }
            echo.source=menu_format(ptr<char>(event.arguments[1]),{echo.title,std::move(selected)},{"%s","%s"});
        }
        return echoes.back().status;
    case echo_clear:
        if(event.phase==NativePhase::after) {echoes.back().source=native_message_source::original("");echoes.back().status=Status::ok;}
        return Status::ok;
    case echo_separator:
        echoes.back().source=native_message_source::before_separator(std::move(echoes.back().source),'|');return echoes.back().status;
    case echo_display:
        if(event.phase==NativePhase::before && echoes.back().status==Status::ok)
            message_bind_source(ptr<char>(event.frame->ecx),echoes.back().source);
        return echoes.back().status;
    case cook_copy:
        recipes[event.frame->ebp]=message_source_lookup("menu.recipe",ptr<char>(event.frame->ebp-0x204));return Status::ok;
    case cook_append:
        recipes.at(event.frame->ebp)=native_message_source::concat({recipes.at(event.frame->ebp),message_source_bound(ptr<char>(event.frame->ebp-0x26c))});
        return Status::ok;
    case biy_copy:
        recipes[event.frame->ebp]=message_source_lookup("terrain",ptr<char>(event.frame->ebp-0x39c));return Status::ok;
    case biy_override:
        recipes[event.frame->ebp]=message_source_lookup("menu.recipe",at<char>(0x2f70b8));return Status::ok;
    case animal_title:case recipe_count_cook:case recipe_count_diy:
    case recipe_join_generic:case recipe_join_item:case recipe_join_override:
    case aim_head:case aim_arms:case aim_legs:
    case defense_block:case defense_first:case defense_second:
        if(event.phase==NativePhase::before) {
            Input input;input.owner=event.arguments[0];
            if(event.id==animal_title)input.source=menu_format(ptr<char>(event.arguments[1]),
                {message_source_bound(ptr<char>(event.arguments[2]))},{"%s"});
            else if(event.id==recipe_count_cook || event.id==recipe_count_diy)
                input.source=menu_format(ptr<char>(event.arguments[1]),
                    {native_message_source::scalar(native_message_source::Scalar::signed32,event.arguments[2],"%d")},{"%d"});
            else if(event.id==aim_head || event.id==aim_arms || event.id==aim_legs) {
                // 52C070 returns one of three literal suffixes or its cleared
                // buffer. The pipe remains a native control delimiter.
                const auto* suffix=ptr<char>(event.arguments[2]);
                auto source=*suffix?message_source_lookup("menu.aim-suffix",suffix):message_source_identity(suffix);
                input.source=menu_format(ptr<char>(event.arguments[1]),{std::move(source)},{"%s"});
            }
            else if(event.id==defense_block || event.id==defense_first || event.id==defense_second) {
                // 4C0190's selected descriptor is copied to local_4C4/624/6D4;
                // these arguments are the corresponding +9 base-name fields.
                MessageText name;input.status=message_crafted_item_source(
                    ptr<unsigned char>(event.arguments[2]-9),ptr<char>(event.arguments[2]),name);
                input.source=menu_format(ptr<char>(event.arguments[1]),
                    {std::move(name)},{"%s"});
            }
            else {
                auto name=event.id==recipe_join_generic?message_source_bound(ptr<char>(event.arguments[2])):
                    message_source_lookup("menu.recipe",ptr<char>(event.arguments[2]));
                const auto* tail=ptr<char>(event.arguments[3]);
                auto suffix=*tail?message_source_bound(tail):message_source_identity(tail);
                input.source=menu_format(ptr<char>(event.arguments[1]),{std::move(name),std::move(suffix)},{"%s","%s"});
            }
            formats.push_back(std::move(input));return formats.back().status;
        } else {
            const auto status=formats.back().status;
            if(status==Status::ok)message_bind_source(ptr<char>(formats.back().owner),formats.back().source);
            formats.pop_back();return status;
        }
    default:return Status::ok;
    }
}
}
