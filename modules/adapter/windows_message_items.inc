// PE 3.89 item-name construction companions. The original branches, buffers,
// descriptors, formatting and case conversion remain owned by the game.
// Evidence: settlement-value-producers-ghidra.c and
// settlement-item-builders-disassembly.txt. No UI layout is stored here.
namespace windows_message_values {
void observe_value(u32 callsite,u32 producer,const char* owner,const std::string& translated);
}
namespace windows_message_items {
enum Hook : u32 {
    enter_name=0xd000,enter_quantity,finish_name,finish_corpse,finish_quantity,
    clear_quality,stale_quality,spoiled_quality,rotten_quality,
    water_name,milk_name,leash_append,wood_hook,iron_hook,bone_hook,no_hook,no_string,
    alternate_name,flora_append,discard_length_quantity,quantity_ready,
    base_format,tree_format,trunk_format,block_format,winter_format,
    leash_format,tied_format,leash_id_format,flora_format,complete_format,
    burning_format,container_format,feet_format,portion_format,length_format,count_format
};
enum class Kind : u32 { name,quantity };
struct Frame {
    Kind kind{};
    u32 callsite{};
    u32 pending_owner{};
    Status status=Status::ok;
    std::string base_source;
    std::string prefix;
    std::string body;
    std::string tree;
    std::string noun;
    std::string primary;
    std::string content;
    std::string container;
    std::string suffix;
    std::string unit;
    std::string pending;
};
std::vector<Frame> frames;

void save(std::vector<unsigned char>& state) {
    message_state_write(state,static_cast<u32>(frames.size()));
    for(const auto& frame:frames) {
        message_state_write(state,frame.kind);
        message_state_write(state,frame.callsite);
        message_state_write(state,frame.pending_owner);
        message_state_write(state,frame.status);
        for(const auto* text:{&frame.base_source,&frame.prefix,&frame.body,&frame.tree,
            &frame.noun,&frame.primary,&frame.content,&frame.container,&frame.suffix,
            &frame.unit,&frame.pending}) message_state_string(state,*text);
    }
}
void restore(const unsigned char*& state) {
    u32 count{};message_state_read(state,count);frames.resize(count);
    for(auto& frame:frames) {
        message_state_read(state,frame.kind);
        message_state_read(state,frame.callsite);
        message_state_read(state,frame.pending_owner);
        message_state_read(state,frame.status);
        for(auto* text:{&frame.base_source,&frame.prefix,&frame.body,&frame.tree,
            &frame.noun,&frame.primary,&frame.content,&frame.container,&frame.suffix,
            &frame.unit,&frame.pending}) message_state_string(state,*text);
    }
}

Status lookup(Frame& frame,const char* domain,const char* source,std::string& output) {
    if(frame.status==Status::ok) frame.status=message_lookup_value(domain,source,output);
    return frame.status;
}
Status format(Frame& frame,const char* domain,const char* source,
              const std::vector<std::pair<const char*,std::string>>& arguments,
              std::string& output) {
    if(lookup(frame,domain,source,output)!=Status::ok) return frame.status;
    std::size_t start=0;
    for(const auto& [specifier,value]:arguments) {
        const auto position=output.find(specifier,start);
        output.replace(position,std::strlen(specifier),value);
        start=position+value.size();
    }
    return Status::ok;
}
void material_name(Frame& frame) {
    format(frame,"item.wood",frame.base_source.c_str(),{{"%s",frame.tree}},frame.body);
}

// The values observer calls this synchronously after a proven child producer.
// Callsite selects the native copy destination; no English-token inference or
// completed-value cache participates in this association.
void observe_value(u32 callsite,u32 producer,const char*,const std::string& translated) {
    if(frames.empty()) return;
    auto& frame=frames.back();
    if(frame.kind==Kind::name) {
        if(callsite==0x5198f && producer==0x51510) frame.prefix=translated;
        if(callsite==0x5189c && producer==0xae750) frame.body=translated;
        if(producer==0x15e2c0 && callsite>=0x51b3e && callsite<=0x51d9d) {
            frame.tree=translated;
            if(callsite==0x51c5b || callsite==0x51d3e) material_name(frame);
        }
        if((producer==0x15eff0 || producer==0x15f400) &&
           callsite>=0x52225 && callsite<=0x52522) frame.noun=translated;
    } else {
        if(producer==0x51770) {
            if(callsite==0x52741) frame.body=frame.primary=translated;
            if(callsite==0x527bf) frame.content=translated;
            if(callsite==0x527ea) frame.container=translated;
        }
        if((producer==0x15eff0 || producer==0x15f400) &&
           callsite>=0x52838 && callsite<=0x52996) frame.noun=translated;
        if(callsite==0x52a0a && producer==0x4b800) frame.unit=translated;
    }
}

void observe_status(u32 callsite,u32,Status status) {
    if(frames.empty()) return;
    auto& frame=frames.back();
    if((frame.kind==Kind::name && callsite>=0x51770 && callsite<=0x525a3) ||
       (frame.kind==Kind::quantity && callsite>=0x52640 && callsite<=0x52aae))
        frame.status=status;
}

void prepare_input(u32 callsite,u32 producer,const char* owner) {
    if(frames.empty()) return;
    auto& frame=frames.back();
    if(frame.status!=Status::ok) return;
    const bool tree_plural=frame.kind==Kind::name && callsite==0x51df7 && producer==0x15eff0;
    const bool name_case=frame.kind==Kind::name && callsite==0x525a3 && producer==0xd4020;
    const bool quantity_case=frame.kind==Kind::quantity && callsite==0x52aae && producer==0xd4020;
    if(tree_plural || name_case || quantity_case) message_bind_value(owner,frame.body);
}

void append_hooks(std::vector<HookSpec>& hooks) {
    using native_name_input::instruction;
    using native_name_input::native_call;
    auto absolute=[&](u32 id,u32 site,std::initializer_list<unsigned char> bytes,
                      u32 offset,u32 rva) {
        auto hook=instruction(id,site,bytes);
        const auto value=address(at<char>(rva));
        std::memcpy(hook.expected+offset,&value,4);hooks.push_back(hook);
    };
    absolute(enter_name,0x5177c,{0xa1,0,0,0,0},1,0x1e200c);
    absolute(enter_quantity,0x5264c,{0xa1,0,0,0,0},1,0x1e200c);
    hooks.push_back(instruction(finish_name,0x525a8,{0x8b,0x8c,0x24,0xdc,0x0c,0,0}));
    hooks.push_back(instruction(finish_corpse,0x518b7,{0x8b,0x8c,0x24,0xd0,0x0c,0,0}));
    hooks.push_back(instruction(finish_quantity,0x52ab3,{0x8b,0x8c,0x24,0x84,0x0d,0,0}));
    hooks.push_back(instruction(clear_quality,0x519d8,{0x8d,0x84,0x24,0x5c,0x07,0,0}));
    absolute(stale_quality,0x519ec,{0xa1,0,0,0,0},1,0x1957ac);
    absolute(spoiled_quality,0x51a4f,{0xf3,0x0f,0x7e,0x05,0,0,0,0},4,0x1957b4);
    absolute(rotten_quality,0x51a71,{0xa1,0,0,0,0},1,0x1957c0);
    absolute(water_name,0x51e79,{0xa1,0,0,0,0},1,0x18e1d0);
    absolute(milk_name,0x51e68,{0xa1,0,0,0,0},1,0x19358c);
    hooks.push_back(instruction(leash_append,0x51f97,{0x8d,0x94,0x24,0xf0,0x06,0,0}));
    absolute(wood_hook,0x5202a,{0xa1,0,0,0,0},1,0x19584c);
    absolute(iron_hook,0x5206a,{0xa1,0,0,0,0},1,0x195860);
    absolute(bone_hook,0x5209e,{0xa1,0,0,0,0},1,0x195870);
    absolute(no_hook,0x5213f,{0xa1,0,0,0,0},1,0x195880);
    absolute(no_string,0x520ea,{0xa1,0,0,0,0},1,0x195890);
    hooks.push_back(instruction(alternate_name,0x521af,{0x8d,0x8c,0x24,0x71,0x06,0,0}));
    absolute(flora_append,0x5254c,{0x66,0xa1,0,0,0,0},2,0x18c8c0);
    hooks.push_back(instruction(discard_length_quantity,0x529df,{0x8d,0x8c,0x24,0x80,0x05,0,0}));
    hooks.push_back(instruction(quantity_ready,0x52a56,{0x8b,0x44,0x24,0x14,0x0f,0xb6,0x00}));
    struct Site { u32 id,site,words; };
    for(const auto& entry:{
        Site{base_format,0x51a97,3},Site{tree_format,0x51b51,4},
        Site{trunk_format,0x51b8b,3},Site{block_format,0x51db0,3},
        Site{winter_format,0x51e25,3},Site{leash_format,0x51f10,3},
        Site{tied_format,0x51f38,3},Site{leash_id_format,0x51f5f,3},
        Site{flora_format,0x521eb,3},Site{complete_format,0x52599,4},
        Site{burning_format,0x527a0,3},Site{container_format,0x527fc,4},
        Site{feet_format,0x52918,3},Site{portion_format,0x529cc,4},
        Site{length_format,0x52a1d,3},Site{count_format,0x52a88,4}})
        hooks.push_back(native_call(entry.id,entry.site,0x10d0,entry.words));
}

Status finish(const NativeEvent& event) {
    auto frame=std::move(frames.back());frames.pop_back();
    const auto owner=event.frame->eax;
    const auto producer=frame.kind==Kind::name ? 0x51770u : 0x52640u;
    if(frame.status==Status::ok) {
        message_bind_value(ptr<char>(owner),frame.body);
        observe_value(frame.callsite,producer,ptr<char>(owner),frame.body);
        windows_message_values::observe_value(frame.callsite,producer,ptr<char>(owner),frame.body);
    } else {
        observe_status(frame.callsite,producer,frame.status);
    }
    return frame.status;
}

Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    handled=event.id>=enter_name && event.id<=count_format;
    if(!handled) return Status::ok;
    if(event.id==enter_name || event.id==enter_quantity) {
        frames.emplace_back();auto& frame=frames.back();
        frame.kind=event.id==enter_name ? Kind::name : Kind::quantity;
        frame.callsite=*ptr<u32>(event.frame->ebp+4)-address(at<char>(0))-5;
        return Status::ok;
    }
    if(event.id==finish_name || event.id==finish_corpse || event.id==finish_quantity)
        return finish(event);
    auto& frame=frames.back();
    if(frame.status!=Status::ok) return frame.status;
    if(event.id>=base_format) {
        if(event.phase==NativePhase::after) {
            message_bind_value(ptr<char>(frame.pending_owner),frame.pending);
            return frame.status;
        }
        frame.pending_owner=event.arguments[0];
        const auto* source=ptr<char>(event.arguments[1]);
        const auto number=[&](u32 word) {return std::to_string(static_cast<std::int32_t>(word));};
        switch(event.id) {
        case base_format:
            frame.base_source=ptr<char>(event.arguments[2]);
            lookup(frame,"item",frame.base_source.c_str(),frame.body);
            if(frame.status==Status::ok)
                message_bind_value(ptr<char>(event.arguments[2]),frame.body);
            frame.pending=frame.body;break;
        case tree_format:
            format(frame,"item",source,{{"%s",frame.tree},{"%s",frame.body}},frame.pending);
            frame.body=frame.pending;break;
        case trunk_format:case block_format:
            format(frame,"item",source,{{"%s",frame.tree}},frame.pending);
            frame.body=frame.pending;break;
        case winter_format:case burning_format:
            format(frame,"item",source,{{"%s",frame.body}},frame.pending);
            frame.body=frame.pending;break;
        case leash_format:case tied_format: {
            std::string npc;
            frame.status=message_translate_bound(ptr<char>(event.arguments[2]),npc);
            if(frame.status==Status::ok)
                format(frame,"item",source,{{"%s",npc}},frame.pending);
            frame.suffix=frame.pending;break;
        }
        case leash_id_format:
            format(frame,"item",source,{{"%d",number(event.arguments[2])}},frame.pending);
            frame.suffix+=frame.pending;break;
        case flora_format:
            lookup(frame,"nameatom",ptr<char>(event.arguments[2]),frame.body);
            frame.pending=frame.body;break;
        case complete_format:
            frame.body=frame.prefix+frame.body;
            frame.pending=frame.body;break;
        case container_format:
            format(frame,"item",source,{{"%s",frame.container},{"%s",frame.content}},frame.pending);
            frame.body=frame.pending;break;
        case feet_format:
            format(frame,"item",source,{{"%d",number(event.arguments[2])}},frame.pending);
            frame.noun=frame.pending;break;
        case portion_format:
            format(frame,"item.portion",source,{{"%s",frame.noun},{"%s",frame.primary}},frame.pending);
            frame.body=frame.pending;break;
        case length_format:
            format(frame,"item",source,{{"%s",frame.unit}},frame.pending);
            frame.body+=frame.pending;break;
        case count_format:
            format(frame,"item",source,{{"%d",number(event.arguments[2])},{"%s",frame.body}},frame.pending);
            frame.body=frame.pending;break;
        }
        return frame.status;
    }
    switch(event.id) {
    case clear_quality:frame.prefix.clear();break;
    case stale_quality:lookup(frame,"item","stale",frame.prefix);break;
    case spoiled_quality:lookup(frame,"item","Spoiled ",frame.prefix);break;
    case rotten_quality:lookup(frame,"item","Rotten ",frame.prefix);break;
    case water_name:lookup(frame,"item","water",frame.body);break;
    case milk_name:lookup(frame,"item","milk",frame.body);break;
    case leash_append:frame.body+=frame.suffix;break;
    case wood_hook:case iron_hook:case bone_hook:case no_hook:case no_string: {
        const char* source=event.id==wood_hook ? " with wooden hook" :
            event.id==iron_hook ? " with iron hook" : event.id==bone_hook ? " with bone hook" :
            event.id==no_hook ? " with no hook" : " with no string";
        std::string suffix;lookup(frame,"item",source,suffix);frame.body+=suffix;break;
    }
    case alternate_name:
        lookup(frame,"item.alternate",ptr<char>(event.frame->esp+0x671),frame.body);break;
    case flora_append:frame.body+=frame.noun;break;
    case discard_length_quantity:frame.body=frame.primary;break;
    case quantity_ready:
        message_bind_value(ptr<char>(*ptr<u32>(event.frame->esp+0x14)),frame.body);break;
    }
    return frame.status;
}
}
