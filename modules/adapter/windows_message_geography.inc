// PE 3.89 geography text companions. Native producers retain all coordinate,
// terrain, culture, direction, distance, unit and generated-name decisions.
// This observes their selected words and native format arguments only.
// Evidence: settlement-geography-producers-ghidra.c,
// settlement-companion-builders-ghidra.c, settlement-data-source-producers-ghidra.c,
// settlement-geography-builders-disassembly.txt and settlement-place-builder-disassembly.txt.
namespace windows_message_values {
void observe_value(u32,u32,const char*,const std::string&);
}
namespace windows_message_geography {
enum class Kind : u32 { terrain,region,direction,distance,combined,location,place_display,place,
                        nearby,area,region_location };
struct Site {u32 site,target,words;Kind kind;};
constexpr u32 first_call=0xf000;
const Site sites[]={
    {0x90418,0x7520,0,Kind::terrain},
    {0x8e637,0x7520,0,Kind::terrain},
    {0x1083c4,0x7520,0,Kind::terrain},
    {0x13c1d8,0x9c0b0,2,Kind::nearby},
    {0x14f901,0x9c300,0,Kind::area},
    {0x14ea3b,0x9c300,0,Kind::area},
    {0x176d25,0x9c300,0,Kind::area},
    {0x149135,0x9c760,0,Kind::region_location},
    {0x17b45b,0x9c760,0,Kind::region_location},
    {0x13c3c4,0x9c7d0,3,Kind::combined},
    {0x13c658,0x9c7d0,3,Kind::combined},
    {0x14f1b2,0x9c7d0,3,Kind::combined},
    {0x14f26a,0x9c7d0,3,Kind::combined},
    {0x156430,0x9c7d0,3,Kind::combined},
    {0x1568a5,0x9c7d0,3,Kind::combined},
    {0x154b8c,0x9c7d0,3,Kind::combined},
    {0x15173c,0x9c7d0,3,Kind::combined},
    {0x14e25a,0x9c7d0,3,Kind::combined},
    {0x14e9f7,0x9c7d0,3,Kind::combined},
    {0x14d0e9,0x9c7d0,3,Kind::combined},
    {0x14a749,0x9c7d0,3,Kind::combined},
    {0x1552b6,0x9c7d0,3,Kind::combined},
    {0x171c9b,0x9c7d0,3,Kind::combined},
    {0x171d72,0x9c7d0,3,Kind::combined},
    {0x176c99,0x9c7d0,3,Kind::combined},
    {0x176d05,0x9c7d0,3,Kind::combined},
    {0x176dc7,0x9c7d0,3,Kind::combined},
    {0x176e29,0x9c7d0,3,Kind::combined},
    {0x9009b,0x9b040,1,Kind::region},
    {0x900da,0x9b040,1,Kind::region},
    {0xde489,0x9b040,1,Kind::region},
    {0x13c43d,0x9b040,1,Kind::region},
    {0x13c6e0,0x9b040,1,Kind::region},
    {0x9c7ab,0x9b040,1,Kind::region},
    {0x148ed4,0x9b040,1,Kind::region},
    {0x14be0f,0x9b040,1,Kind::region},
    {0x171d12,0x9b040,1,Kind::region},
    {0x171de9,0x9b040,1,Kind::region},
    {0x17244d,0x9b040,1,Kind::region},
    {0x1724f7,0x9b040,1,Kind::region},
    {0x172901,0x9b040,1,Kind::region},
    {0x172b61,0x9b040,1,Kind::region},
    {0x176e83,0x9b040,1,Kind::region},
    {0x157c89,0x9b040,1,Kind::region},
    {0x13c430,0x15ec00,0,Kind::location},
    {0x13c6d3,0x15ec00,0,Kind::location},
    {0x13c825,0x15ec00,0,Kind::location},
    {0x9c79e,0x15ec00,0,Kind::location},
    {0x171d05,0x15ec00,0,Kind::location},
    {0x171ddc,0x15ec00,0,Kind::location},
    {0x1724e6,0x15ec00,0,Kind::location},
    {0x1728f0,0x15ec00,0,Kind::location},
    {0x172b50,0x15ec00,0,Kind::location},
    {0x176b55,0x15ec00,0,Kind::location},
    {0x139ae9,0x9b970,3,Kind::direction},
    {0x139b1f,0x9b970,3,Kind::direction},
    {0x9c14a,0x9b970,3,Kind::direction},
    {0x9c1aa,0x9b970,3,Kind::direction},
    {0x9c233,0x9b970,3,Kind::direction},
    {0x9c298,0x9b970,3,Kind::direction},
    {0x9c2c4,0x9b970,3,Kind::direction},
    {0x9c819,0x9b970,3,Kind::direction},
    {0xe9fc8,0x9b970,3,Kind::direction},
    {0xea032,0x9b970,3,Kind::direction},
    {0xea0c9,0x9b970,3,Kind::direction},
    {0x155479,0x9b970,3,Kind::direction},
    {0x1730df,0x9b970,3,Kind::direction},
    {0x173159,0x9b970,3,Kind::direction},
    {0x2df9e,0x76c0,0,Kind::terrain},
    {0x2ef92,0x76c0,0,Kind::terrain},
    {0x2f0aa,0x76c0,0,Kind::terrain},
    {0x6aaad,0x76c0,0,Kind::terrain},
    {0x6ab78,0x76c0,0,Kind::terrain},
    {0x6acba,0x76c0,0,Kind::terrain},
    {0x4620d,0x76c0,0,Kind::terrain},
    {0x46486,0x76c0,0,Kind::terrain},
    {0x101f65,0x76c0,0,Kind::terrain},
    {0x1027e9,0x76c0,0,Kind::terrain},
    {0x102a90,0x76c0,0,Kind::terrain},
    {0x101899,0x76c0,0,Kind::terrain},
    {0x119b58,0x76c0,0,Kind::terrain},
    {0x119408,0x76c0,0,Kind::terrain},
    {0x2eb03,0x76c0,0,Kind::terrain},
    {0x166d17,0x76c0,0,Kind::terrain},
    {0x77a2,0x76c0,0,Kind::terrain},
    {0xa242f,0x76c0,0,Kind::terrain},
    {0xf9717,0x76c0,0,Kind::terrain},
    {0x40682,0x76c0,0,Kind::terrain},
    {0xffe1c,0x76c0,0,Kind::terrain},
    {0x1081cb,0x76c0,0,Kind::terrain},
    {0x10246c,0x76c0,0,Kind::terrain},
    {0x9c3a9,0x76c0,0,Kind::terrain},
    {0x9c55c,0x76c0,0,Kind::terrain},
    {0x9c5d4,0x76c0,0,Kind::terrain},
    {0x9c645,0x76c0,0,Kind::terrain},
    {0x9c6b6,0x76c0,0,Kind::terrain},
    {0x148993,0x76c0,0,Kind::terrain},
    {0x148d3b,0x76c0,0,Kind::terrain},
    {0x132459,0x76c0,0,Kind::terrain},
    {0x9b185,0x9ad00,1,Kind::region},
    {0x9b221,0x9ad00,1,Kind::region},
    {0x9c85f,0x9bb30,3,Kind::distance},
    {0x15eda1,0x9bb30,3,Kind::distance},
    {0x1554a9,0x9bb30,3,Kind::distance},
    {0x176c0d,0x9bb30,3,Kind::distance},
    {0x8e6a3,0x8e420,0,Kind::place_display},
    {0x15ec9d,0x8e420,0,Kind::place_display},
    {0x15ecc9,0x8e420,0,Kind::place_display},
    {0x8e411,0xa8f50,2,Kind::place},
    {0x8e491,0xa8f50,2,Kind::place},
    {0x8e4ca,0xa8f50,2,Kind::place},
    {0x148eb5,0xa8f50,2,Kind::place},
};
enum Hook : u32 {
    distance_km=0xf200,distance_miles,distance_km_append,distance_miles_append,
    location_format,place_format,near_meters,near_yards,near_visible,near_inside,
    area_border,area_plain,region_location_format,constant_km_short,constant_km_couple,
    constant_miles_short,constant_miles_couple,distance_away,
    place_finnish,place_named,place_outside,place_prefix,place_suffix,
    near_corner,near_close,area_neighbor_copy
};
enum class PlaceOrigin : u32 { identity,gloss };
struct Frame {
    u32 site{},target{},owner{},pending_owner{},first_owner{},second_owner{};
    Kind kind{};
    PlaceOrigin origin=PlaceOrigin::identity;
    Status status=Status::ok;
    bool constant_distance{};
    std::string body,first,second,pending;
};
std::vector<Frame> frames;

void save(std::vector<unsigned char>& state) {
    message_state_write(state,static_cast<u32>(frames.size()));
    for(const auto& frame:frames) {
        for(const auto value:{frame.site,frame.target,frame.owner,frame.pending_owner,
                             frame.first_owner,frame.second_owner}) message_state_write(state,value);
        message_state_write(state,frame.kind);message_state_write(state,frame.origin);
        message_state_write(state,frame.status);message_state_write(state,frame.constant_distance);
        for(const auto* text:{&frame.body,&frame.first,&frame.second,&frame.pending})
            message_state_string(state,*text);
    }
}
void restore(const unsigned char*& state) {
    u32 count{};message_state_read(state,count);frames.resize(count);
    for(auto& frame:frames) {
        for(auto* value:{&frame.site,&frame.target,&frame.owner,&frame.pending_owner,
                        &frame.first_owner,&frame.second_owner}) message_state_read(state,*value);
        message_state_read(state,frame.kind);message_state_read(state,frame.origin);
        message_state_read(state,frame.status);message_state_read(state,frame.constant_distance);
        for(auto* text:{&frame.body,&frame.first,&frame.second,&frame.pending})
            message_state_string(state,*text);
    }
}
Status lookup(Frame& frame,const char* domain,const char* source,std::string& output) {
    if(frame.status==Status::ok) frame.status=message_lookup_value(domain,source,output);
    return frame.status;
}
Status format(Frame& frame,const char* source,
              const std::vector<std::pair<const char*,std::string>>& arguments,
              std::string& output) {
    if(lookup(frame,"geography.format",source,output)!=Status::ok) return frame.status;
    std::size_t start=0;
    for(const auto& [specifier,value]:arguments) {
        const auto position=output.find(specifier,start);
        output.replace(position,std::strlen(specifier),value);
        start=position+value.size();
    }
    return Status::ok;
}

void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::native_call;
    using native_name_input::instruction;
    for(u32 index=0;index<sizeof(sites)/sizeof(sites[0]);++index)
        hooks.push_back(native_call(first_call+index,sites[index].site,sites[index].target,sites[index].words));
    struct Format {u32 id,site,words;};
    for(const auto& entry:{Format{distance_km,0x9bc13,3},Format{distance_miles,0x9bcd7,3},
        Format{distance_km_append,0x9bfc4,3},Format{distance_miles_append,0x9c02f,3},
        Format{location_format,0x15ed37,3},Format{place_format,0x8e4da,4},
        Format{near_meters,0x9c16b,4},Format{near_yards,0x9c182,4},
        Format{near_visible,0x9c1b9,3},Format{near_inside,0x9c1dd,2},
        Format{area_border,0x9c70d,6},Format{area_plain,0x9c742,4},
        Format{region_location_format,0x9c7ba,4}})
        hooks.push_back(native_call(entry.id,entry.site,0x10d0,entry.words));
    auto absolute=[&](u32 id,u32 site,std::initializer_list<unsigned char> bytes,u32 offset,u32 rva) {
        auto hook=instruction(id,site,bytes);
        const auto value=address(at<char>(rva));std::memcpy(hook.expected+offset,&value,4);
        hooks.push_back(hook);
    };
    absolute(constant_km_short,0x9bc2e,{0x0f,0x10,0x05,0,0,0,0},3,0x19db78);
    absolute(constant_km_couple,0x9bc85,{0x0f,0x10,0x05,0,0,0,0},3,0x19dba4);
    absolute(constant_miles_short,0x9bcf2,{0x0f,0x10,0x05,0,0,0,0},3,0x19dbd0);
    absolute(constant_miles_couple,0x9bd3b,{0x0f,0x10,0x05,0,0,0,0},3,0x19dbf0);
    absolute(distance_away,0x9c07a,{0x8b,0x0d,0,0,0,0},2,0x19dd28);
    absolute(place_finnish,0xa8fed,{0x8d,0x88,0,0,0,0},2,0x54f6200);
    hooks.push_back(instruction(place_named,0xa9139,{0x25,0xff,0x7f,0,0}));
    absolute(place_outside,0xa8f9c,{0x66,0xa1,0,0,0,0},2,0x195a1c);
    absolute(place_prefix,0xa902d,{0x8d,0x88,0,0,0,0},2,0x54f0200);
    absolute(place_suffix,0xa904e,{0x8d,0x88,0,0,0,0},2,0x54f5200);
    absolute(near_corner,0x9c1fa,{0xa1,0,0,0,0},1,0x19dd88);
    absolute(near_close,0x9c26f,{0xa1,0,0,0,0},1,0x19dda0);
    hooks.push_back(instruction(area_neighbor_copy,0x9c6e7,{0x8d,0x8d,0xc0,0xfe,0xff,0xff}));
}

void receive_child(const Frame& child,const NativeEvent& event) {
    if(frames.empty()) return;
    auto& parent=frames.back();
    if(parent.status!=Status::ok) return;
    parent.status=child.status;
    if(child.status!=Status::ok) return;
    // These copies are direct consumers of this exact child return, proved
    // by the instructions immediately after each named CALL.
    if(parent.kind==Kind::combined) {
        if(child.site==0x9c819) parent.body=child.body;
        if(child.site==0x9c85f) parent.body+="，"+child.body;
    }
    if(parent.kind==Kind::location) {
        if(child.site==0x15ec9d) {
            parent.first=child.body;parent.first_owner=event.frame->ebp-0x70;
        }
        if(child.site==0x15ecc9) {
            parent.second=child.body;parent.second_owner=event.frame->ebp-0xd8;
        }
    }
    if(parent.kind==Kind::nearby &&
       (child.site==0x9c233 || child.site==0x9c298 || child.site==0x9c2c4))
        parent.body+=child.body;
    if(parent.kind==Kind::area) {
        if(child.site==0x9c3a9) parent.first=child.body;
        if(child.site==0x9c55c || child.site==0x9c5d4 ||
           child.site==0x9c645 || child.site==0x9c6b6) parent.second=child.body;
    }
}

Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    const bool producer=event.id>=first_call && event.id<first_call+sizeof(sites)/sizeof(sites[0]);
    handled=producer || (event.id>=distance_km && event.id<=area_neighbor_copy);
    if(!handled) return Status::ok;
    if(producer) {
        const auto& site=sites[event.id-first_call];
        if(event.phase==NativePhase::before) {
            frames.emplace_back();auto& frame=frames.back();
            frame.site=site.site;frame.target=site.target;frame.kind=site.kind;
            if(site.kind==Kind::place) frame.owner=event.arguments[1];
            return Status::ok;
        }
        auto frame=std::move(frames.back());frames.pop_back();
        if(frame.kind!=Kind::place) frame.owner=event.frame->eax;
        const auto* original=ptr<char>(frame.owner);
        if(frame.status==Status::ok) {
            switch(frame.kind) {
            case Kind::terrain:lookup(frame,"terrain",original,frame.body);break;
            case Kind::region:lookup(frame,"geography.region",original,frame.body);break;
            case Kind::direction:lookup(frame,"geography.direction",original,frame.body);break;
            case Kind::distance:
                if(frame.constant_distance) lookup(frame,"geography.distance",original,frame.body);
                break;
            case Kind::place:
                // Finnish, named-place and out-of-world branches each mark
                // identity explicitly. Only the English-gloss branch marks gloss.
                if(frame.origin==PlaceOrigin::identity)
                    frame.status=message_identity_value(original,frame.body);
                break;
            case Kind::combined:case Kind::location:case Kind::place_display:
            case Kind::nearby:case Kind::area:case Kind::region_location:break;
            }
        }
        if(frame.status==Status::ok) {
            message_bind_value(original,frame.body);
            windows_message_values::observe_value(site.site,site.target,original,frame.body);
        }
        receive_child(frame,event);
        return frame.status;
    }
    auto& frame=frames.back();
    if(frame.status!=Status::ok) return frame.status;
    if(event.id<=region_location_format) {
        if(event.phase==NativePhase::after) {
            message_bind_value(ptr<char>(frame.pending_owner),frame.pending);
            return frame.status;
        }
        frame.pending_owner=event.arguments[0];
        const auto* source=ptr<char>(event.arguments[1]);
        if(event.id==distance_km || event.id==distance_miles) {
            format(frame,source,{{"%d",std::to_string(static_cast<std::int32_t>(event.arguments[2]))}},frame.pending);
            frame.body=frame.pending;
        } else if(event.id==distance_km_append || event.id==distance_miles_append) {
            // The native walk-duration branches have finished all constant
            // overwrites before reaching these two actual append formats.
            lookup(frame,"geography.distance",ptr<char>(event.frame->ebx),frame.body);
            format(frame,source,{{"%d",std::to_string(static_cast<std::int32_t>(event.arguments[2]))}},frame.pending);
            frame.body+=frame.pending;frame.constant_distance=false;
        } else if(event.id==location_format) {
            // Native 55ED1B selected precisely one of these two copied values.
            const auto& argument=event.arguments[2]==frame.first_owner ? frame.first : frame.second;
            format(frame,source,{{"%s",argument}},frame.pending);frame.body=frame.pending;
        } else if(event.id==place_format || event.id==region_location_format) {
            std::string name,gloss;
            frame.status=message_translate_bound(ptr<char>(event.arguments[2]),name);
            if(frame.status==Status::ok)
                frame.status=message_translate_bound(ptr<char>(event.arguments[3]),gloss);
            if(frame.status==Status::ok)
                format(frame,source,{{"%s",name},{"%s",gloss}},frame.pending);
            frame.body=frame.pending;
        } else if(event.id==near_meters || event.id==near_yards) {
            std::string direction;
            frame.status=message_translate_bound(ptr<char>(event.arguments[3]),direction);
            if(frame.status==Status::ok)
                format(frame,source,{{"%d",std::to_string(static_cast<std::int32_t>(event.arguments[2]))},
                                     {"%s",direction}},frame.pending);
            frame.body=frame.pending;
        } else if(event.id==near_visible) {
            std::string direction;
            frame.status=message_translate_bound(ptr<char>(event.arguments[2]),direction);
            if(frame.status==Status::ok) format(frame,source,{{"%s",direction}},frame.pending);
            frame.body=frame.pending;
        } else if(event.id==near_inside) {
            format(frame,source,{},frame.pending);frame.body=frame.pending;
        } else if(event.id==area_border || event.id==area_plain) {
            std::string size,direction;
            lookup(frame,"geography.size",ptr<char>(event.arguments[2]),size);
            if(event.id==area_border) {
                lookup(frame,"direction",ptr<char>(event.arguments[5]),direction);
                format(frame,source,{{"%s",size},{"%s",frame.first},
                                     {"%s",frame.second},{"%s",direction}},frame.pending);
            } else format(frame,source,{{"%s",size},{"%s",frame.first}},frame.pending);
            frame.body=frame.pending;
        }
        return frame.status;
    }
    switch(event.id) {
    case constant_km_short:case constant_km_couple:
    case constant_miles_short:case constant_miles_couple:
        frame.constant_distance=true;break;
    case distance_away:
        if(!frame.constant_distance) {
            std::string value;
            format(frame," away",{{"%s",frame.body}},value);frame.body=std::move(value);
        }
        break;
    case place_finnish:case place_named:case place_outside:
        frame.origin=PlaceOrigin::identity;break;
    case place_prefix:
        frame.origin=PlaceOrigin::gloss;
        lookup(frame,"geography.prefix",at<char>(0x54f0200+event.frame->eax),frame.body);
        break;
    case place_suffix: {
        std::string suffix;
        lookup(frame,"geography.suffix",at<char>(0x54f5200+event.frame->eax),suffix);
        frame.body+=suffix;break;
    }
    case near_corner:case near_close: {
        std::string text;
        lookup(frame,"geography.format",event.id==near_corner ? "just around the corner " : "just nearby ",text);
        frame.body+=text;break;
    }
    case area_neighbor_copy:
        message_bind_value(ptr<char>(event.frame->ebp-0x140),frame.second);break;
    }
    return frame.status;
}
}
