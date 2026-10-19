// PE 3.89 native value producers. These companions contain text only.
// Evidence: settlement-value-producers-ghidra.c, settlement-additional-values-ghidra.c,
// settlement-final-name-primitives-ghidra.c and settlement-message-helpers-ghidra.c.
Status message_lookup_value(const char*,const char*,std::string&);
Status message_translate_bound(const char*,std::string&);
Status message_identity_value(const char*,std::string&);
Status message_crafted_item_source(const unsigned char*,const char*,MessageText&);

namespace windows_message_items {
void observe_value(u32,u32,const char*,const MessageText&);
void prepare_input(u32,u32,const char*);
void observe_status(u32,u32,Status);
}

namespace windows_message_values {
constexpr u32 first_hook=0xc000;
enum class Kind : u32 { quality,tree,direction,plural,singular,indefinite,definite,
    lowercase,npc,identity,bodypart,time,quantity,injury,hunger,thirst,trap,
    work,work_item,construction,activity,activity_copy,silhouette,burntime,
    temperature,encounter,spell,profile,corpse_size,corpse_damage,corpse_age,corpse_injury,
    corpse,corpse_burn,craft,comma_list,list_add,count_list,treatment,flora,helper_list,bowstring,proper,injury_label,track_age,or_list };
struct Site {u32 site,target;Kind kind;};
// GENERATED_NATIVE_VALUE_SITES
const Site sites[]={
    {0x65167,0x15efb0,Kind::indefinite},
    {0x15e49f,0x162930,Kind::or_list},
    {0x167b15,0x167880,Kind::track_age},
    {0xd7d02,0xd4ef0,Kind::injury_label},
    {0xd7fdf,0xd4ef0,Kind::injury_label},
    {0xd50d0,0xd4600,Kind::bodypart},
    {0x166b,0x15eff0,Kind::plural},
    {0x17ff,0x15eff0,Kind::plural},
    {0x18f7,0x15eff0,Kind::plural},
    {0x1acf,0x15eff0,Kind::plural},
    {0x1d09,0x15f400,Kind::singular},
    {0x1ff5,0x15eff0,Kind::plural},
    {0x3ec4,0x163840,Kind::activity_copy},
    {0x3ee7,0x163190,Kind::activity},
    {0x4056,0x163840,Kind::activity_copy},
    {0x4a0a,0x163840,Kind::activity_copy},
    {0x539f,0xd4020,Kind::lowercase},
    {0x53c5,0x163190,Kind::activity},
    {0x53cc,0xd4020,Kind::lowercase},
    {0x5aef,0x163190,Kind::activity},
    {0x5d5d,0x5340,Kind::trap},
    {0x5e06,0x163190,Kind::activity},
    {0x5e4e,0x163190,Kind::activity},
    {0x5e97,0x163190,Kind::activity},
    {0x5ee7,0x163190,Kind::activity},
    {0x5f37,0x163190,Kind::activity},
    {0x5f87,0x163190,Kind::activity},
    {0x60ed,0x163190,Kind::activity},
    {0x6137,0x163190,Kind::activity},
    {0x6187,0x163190,Kind::activity},
    {0x6381,0x163840,Kind::activity_copy},
    {0x63a3,0x5340,Kind::trap},
    {0x695d,0x5340,Kind::trap},
    {0x6964,0x162bd0,Kind::indefinite},
    {0x6d49,0xd4600,Kind::bodypart},
    {0x6e08,0x5340,Kind::trap},
    {0x1bec8,0x199b0,Kind::time},
    {0x27636,0xad4f0,Kind::npc},
    {0x2c82f,0x162bd0,Kind::indefinite},
    {0x2c8aa,0x15ee90,Kind::encounter},
    {0x2cd75,0xad4f0,Kind::npc},
    {0x2cd7c,0x162e30,Kind::list_add},
    {0x2cdbb,0x162ed0,Kind::count_list},
    {0x2da73,0x162bd0,Kind::indefinite},
    {0x2da9d,0x162bd0,Kind::indefinite},
    {0x2fa0e,0x162bd0,Kind::indefinite},
    {0x2fae6,0x1627a0,Kind::comma_list},
    {0x2fdfe,0x162bd0,Kind::indefinite},
    {0x2fed8,0x1627a0,Kind::comma_list},
    {0x31131,0x1627a0,Kind::comma_list},
    {0x31158,0x1627a0,Kind::comma_list},
    {0x31622,0x163840,Kind::activity_copy},
    {0x3263f,0x163190,Kind::activity},
    {0x3265d,0x163190,Kind::activity},
    {0x3267b,0x163190,Kind::activity},
    {0x32696,0x163190,Kind::activity},
    {0x32867,0xd4020,Kind::lowercase},
    {0x35796,0xd4020,Kind::lowercase},
    {0x35b7d,0xd4020,Kind::lowercase},
    {0x36a48,0xd4020,Kind::lowercase},
    {0x37a6b,0x163190,Kind::activity},
    {0x38925,0x163190,Kind::activity},
    {0x38935,0x163190,Kind::activity},
    {0x38940,0x163190,Kind::activity},
    {0x3894e,0x163190,Kind::activity},
    {0x40c9f,0x162bd0,Kind::indefinite},
    {0x40d1f,0x51510,Kind::quality},
    {0x40d26,0x162bd0,Kind::indefinite},
    {0x40dfa,0x51510,Kind::quality},
    {0x4151f,0x40b20,Kind::craft},
    {0x4154d,0x40b20,Kind::craft},
    {0x4155d,0x40b20,Kind::craft},
    {0x4156d,0x40b20,Kind::craft},
    {0x4157d,0x40b20,Kind::craft},
    {0x4158d,0x40b20,Kind::craft},
    {0x41609,0x199b0,Kind::time},
    {0x41612,0x199b0,Kind::time},
    {0x41b8b,0x1070f0,Kind::work_item},
    {0x41b93,0x1018e0,Kind::work},
    {0x41ca6,0xd4020,Kind::lowercase},
    {0x41cb2,0x15eff0,Kind::plural},
    {0x41cb9,0xd4020,Kind::lowercase},
    {0x438a0,0x1018e0,Kind::work},
    {0x43ddf,0x163840,Kind::activity_copy},
    {0x44bbb,0x1070f0,Kind::work_item},
    {0x44bc3,0x1018e0,Kind::work},
    {0x4566b,0x1018e0,Kind::work},
    {0x45716,0x163840,Kind::activity_copy},
    {0x45bd9,0x163190,Kind::activity},
    {0x46696,0x163190,Kind::activity},
    {0x466de,0x163190,Kind::activity},
    {0x46727,0x163190,Kind::activity},
    {0x46869,0x163190,Kind::activity},
    {0x468b7,0x163190,Kind::activity},
    {0x46907,0x163190,Kind::activity},
    {0x4699c,0x163190,Kind::activity},
    {0x469a9,0x163190,Kind::activity},
    {0x469b6,0x163190,Kind::activity},
    {0x472b2,0x4b800,Kind::quantity},
    {0x47322,0x4b800,Kind::quantity},
    {0x475e9,0x4b800,Kind::quantity},
    {0x47713,0x4b800,Kind::quantity},
    {0x47a88,0x4b800,Kind::quantity},
    {0x483af,0x163190,Kind::activity},
    {0x4842b,0x163190,Kind::activity},
    {0x48539,0x163190,Kind::activity},
    {0x48557,0x163190,Kind::activity},
    {0x48679,0x163190,Kind::activity},
    {0x48697,0x163190,Kind::activity},
    {0x486e2,0x163190,Kind::activity},
    {0x48721,0x163190,Kind::activity},
    {0x490b2,0x48d50,Kind::bowstring},
    {0x4bd10,0x4b2f0,Kind::quantity},
    {0x4cb7b,0x199b0,Kind::time},
    {0x4fd4d,0x163190,Kind::activity},
    {0x4fe92,0x163190,Kind::activity},
    {0x50b1b,0x162cf0,Kind::definite},
    {0x5189c,0xae750,Kind::corpse},
    {0x5198f,0x51510,Kind::quality},
    {0x51ac4,0x15eff0,Kind::plural},
    {0x51b3e,0x15e2c0,Kind::tree},
    {0x51b78,0x15e2c0,Kind::tree},
    {0x51bb4,0xd4020,Kind::lowercase},
    {0x51c5b,0x15e2c0,Kind::tree},
    {0x51d3e,0x15e2c0,Kind::tree},
    {0x51d9d,0x15e2c0,Kind::tree},
    {0x51df7,0x15eff0,Kind::plural},
    {0x51efd,0xad4f0,Kind::npc},
    {0x51f25,0xad4f0,Kind::npc},
    {0x52225,0x15eff0,Kind::plural},
    {0x52251,0x15f400,Kind::singular},
    {0x52258,0x15eff0,Kind::plural},
    {0x522aa,0x15f400,Kind::singular},
    {0x522b1,0x15eff0,Kind::plural},
    {0x522df,0x15f400,Kind::singular},
    {0x522e6,0x15eff0,Kind::plural},
    {0x52314,0x15f400,Kind::singular},
    {0x5231b,0x15eff0,Kind::plural},
    {0x52358,0x15f400,Kind::singular},
    {0x5235f,0x15eff0,Kind::plural},
    {0x52384,0x15eff0,Kind::plural},
    {0x523ae,0x15f400,Kind::singular},
    {0x523d7,0x15eff0,Kind::plural},
    {0x523fc,0x15eff0,Kind::plural},
    {0x52427,0x15eff0,Kind::plural},
    {0x5244c,0x15eff0,Kind::plural},
    {0x52477,0x15eff0,Kind::plural},
    {0x524a3,0x15f400,Kind::singular},
    {0x524aa,0x15eff0,Kind::plural},
    {0x524e5,0x15f400,Kind::singular},
    {0x524ec,0x15eff0,Kind::plural},
    {0x5251b,0x15f400,Kind::singular},
    {0x52522,0x15eff0,Kind::plural},
    {0x525a3,0xd4020,Kind::lowercase},
    {0x52838,0x15f400,Kind::singular},
    {0x5283f,0x15eff0,Kind::plural},
    {0x5286c,0x15f400,Kind::singular},
    {0x52873,0x15eff0,Kind::plural},
    {0x5289f,0x15f400,Kind::singular},
    {0x528a6,0x15eff0,Kind::plural},
    {0x528d2,0x15f400,Kind::singular},
    {0x528d9,0x15eff0,Kind::plural},
    {0x5292f,0x15f400,Kind::singular},
    {0x52936,0x15eff0,Kind::plural},
    {0x5295f,0x15f400,Kind::singular},
    {0x52966,0x15eff0,Kind::plural},
    {0x5298f,0x15f400,Kind::singular},
    {0x52996,0x15eff0,Kind::plural},
    {0x52a0a,0x4b800,Kind::quantity},
    {0x52aae,0xd4020,Kind::lowercase},
    {0x58452,0xd4020,Kind::lowercase},
    {0x58569,0xd4020,Kind::lowercase},
    {0x585bd,0xd4020,Kind::lowercase},
    {0x6208f,0x51510,Kind::quality},
    {0x64b94,0xd4020,Kind::lowercase},
    {0x64ba5,0x4b2f0,Kind::quantity},
    {0x64bde,0xd4020,Kind::lowercase},
    {0x64bef,0x4b2f0,Kind::quantity},
    {0x64c1b,0xd4020,Kind::lowercase},
    {0x64c42,0x4b800,Kind::quantity},
    {0x64c6e,0xd4020,Kind::lowercase},
    {0x64c95,0x4b800,Kind::quantity},
    {0x64cdf,0xd4020,Kind::lowercase},
    {0x64d06,0x4b800,Kind::quantity},
    {0x64d4d,0xd4020,Kind::lowercase},
    {0x64d90,0xd4020,Kind::lowercase},
    {0x64db6,0x4b800,Kind::quantity},
    {0x64de7,0xd4020,Kind::lowercase},
    {0x64e0d,0x4b800,Kind::quantity},
    {0x64e49,0xd4020,Kind::lowercase},
    {0x64e70,0x4b800,Kind::quantity},
    {0x6511f,0xd4020,Kind::lowercase},
    {0x6516e,0xd4020,Kind::lowercase},
    {0x651ac,0x4b800,Kind::quantity},
    {0x6920f,0xd4020,Kind::lowercase},
    {0x692ba,0xd4020,Kind::lowercase},
    {0x69711,0x162cf0,Kind::definite},
    {0x6974a,0x162cf0,Kind::definite},
    {0x6a12e,0x162cf0,Kind::definite},
    {0x6a14d,0x162cf0,Kind::definite},
    {0x6a57b,0x162cf0,Kind::definite},
    {0x6a8db,0x162cf0,Kind::definite},
    {0x6d5c2,0xd4020,Kind::lowercase},
    {0x83fd0,0x162bd0,Kind::indefinite},
    {0x8412f,0x162bd0,Kind::indefinite},
    {0x841e6,0x162bd0,Kind::indefinite},
    {0x842c0,0x162bd0,Kind::indefinite},
    {0x89f9a,0xaaf20,Kind::helper_list},
    {0x987d1,0xae480,Kind::corpse_damage},
    {0x9885f,0xd450,Kind::corpse_burn},
    {0x9c3b0,0xd4020,Kind::lowercase},
    {0x9c6ed,0xd4020,Kind::lowercase},
    {0x9f972,0xd4020,Kind::lowercase},
    {0x9fe48,0x15e4d0,Kind::temperature},
    {0xa0996,0xd4020,Kind::lowercase},
    {0xa2436,0x162bd0,Kind::indefinite},
    {0xa245a,0xd4020,Kind::lowercase},
    {0xa35fd,0xd4020,Kind::lowercase},
    {0xaac68,0xad4f0,Kind::npc},
    {0xab049,0xad4f0,Kind::npc},
    {0xab050,0x162e30,Kind::list_add},
    {0xab06d,0x162ed0,Kind::count_list},
    {0xadcfe,0xadbc0,Kind::corpse_size},
    {0xadd57,0xad4f0,Kind::npc},
    {0xae325,0xad4f0,Kind::npc},
    {0xae444,0xad4f0,Kind::npc},
    {0xae7d8,0xae480,Kind::corpse_damage},
    {0xae800,0xadca0,Kind::profile},
    {0xae80f,0xadca0,Kind::profile},
    {0xae85a,0xd450,Kind::corpse_burn},
    {0xae88d,0xd6f00,Kind::corpse_injury},
    {0xae944,0xae680,Kind::corpse_age},
    {0xaed15,0xadca0,Kind::profile},
    {0xaedf2,0x162e30,Kind::list_add},
    {0xaeef2,0x162e30,Kind::list_add},
    {0xaf059,0x162e30,Kind::list_add},
    {0xaf075,0x162ed0,Kind::count_list},
    {0xaf320,0xd71b0,Kind::injury},
    {0xb0330,0x846c0,Kind::identity},
    {0xb033d,0x846c0,Kind::identity},
    {0xb15e0,0xd4020,Kind::lowercase},
    {0xb1602,0xd4020,Kind::lowercase},
    {0xbc7a9,0xd4020,Kind::lowercase},
    {0xbcd46,0xd4020,Kind::lowercase},
    {0xbeb63,0x15e2c0,Kind::tree},
    {0xbeee2,0xae3f0,Kind::silhouette},
    {0xbf22f,0xae3f0,Kind::silhouette},
    {0xbf366,0xae3f0,Kind::silhouette},
    {0xbf399,0xae3f0,Kind::silhouette},
    {0xc0d9a,0xd4020,Kind::lowercase},
    {0xd50d0,0xd4600,Kind::bodypart},
    {0xd5348,0xd4020,Kind::lowercase},
    {0xd5555,0x15fd00,Kind::hunger},
    {0xd566b,0x15fe60,Kind::thirst},
    {0xd6c85,0xd4600,Kind::bodypart},
    {0xd73a3,0xd4600,Kind::bodypart},
    {0xd75a3,0xd71b0,Kind::injury},
    {0xd75d7,0xd71b0,Kind::injury},
    {0xd8c15,0xd71b0,Kind::injury},
    {0xd8d97,0xd4020,Kind::lowercase},
    {0xd9174,0xd8a10,Kind::treatment},
    {0xd931c,0xd4020,Kind::lowercase},
    {0xd93ba,0xd8a10,Kind::treatment},
    {0xd9922,0xd4020,Kind::lowercase},
    {0xd9a10,0xd71b0,Kind::injury},
    {0xd9a17,0xd4020,Kind::lowercase},
    {0xd9a6b,0xd71b0,Kind::injury},
    {0xd9a72,0xd4020,Kind::lowercase},
    {0xd9c06,0xd4020,Kind::lowercase},
    {0xd9c77,0xd4020,Kind::lowercase},
    {0xdabac,0xd4020,Kind::lowercase},
    {0xdc961,0x162e30,Kind::list_add},
    {0xdca74,0x162e30,Kind::list_add},
    {0xdcad1,0x162e30,Kind::list_add},
    {0xdcbb9,0x162e30,Kind::list_add},
    {0xdcc15,0x162ed0,Kind::count_list},
    {0xdcfdd,0xad4f0,Kind::npc},
    {0xdcff1,0xad4f0,Kind::npc},
    {0xdd005,0xad4f0,Kind::npc},
    {0xdfbab,0xe7ef0,Kind::spell},
    {0xdff4f,0xe7ef0,Kind::spell},
    {0xe2aa5,0xae3f0,Kind::silhouette},
    {0xe2e63,0xae3f0,Kind::silhouette},
    {0xe69b5,0x4b800,Kind::quantity},
    {0xe6a5d,0x4b2f0,Kind::quantity},
    {0xe9baf,0xe7ef0,Kind::spell},
    {0xe9f9e,0xae3f0,Kind::silhouette},
    {0xe9fab,0x162bd0,Kind::indefinite},
    {0xea052,0xae3f0,Kind::silhouette},
    {0xea05f,0x162bd0,Kind::indefinite},
    {0xea0e9,0xae3f0,Kind::silhouette},
    {0xea0f6,0x162bd0,Kind::indefinite},
    {0xf8d89,0xad4f0,Kind::npc},
    {0xf96eb,0x163190,Kind::activity},
    {0xf9f7e,0x15f450,Kind::temperature},
    {0xfa599,0x4b2f0,Kind::quantity},
    {0x1018a0,0xd4020,Kind::lowercase},
    {0x101a45,0x1018e0,Kind::work},
    {0x101e30,0x101790,Kind::construction},
    {0x101e55,0x101790,Kind::construction},
    {0x1022c8,0x163840,Kind::activity_copy},
    {0x102473,0xd4020,Kind::lowercase},
    {0x102d4b,0x4b2f0,Kind::quantity},
    {0x102e2a,0x4b2f0,Kind::quantity},
    {0x107581,0x1627a0,Kind::comma_list},
    {0x10769d,0x101790,Kind::construction},
    {0x107701,0x162bd0,Kind::indefinite},
    {0x107712,0xe1ef0,Kind::proper},
    {0x10777e,0x3550,Kind::flora},
    {0x1077c8,0x1070f0,Kind::work_item},
    {0x1077d0,0x1018e0,Kind::work},
    {0x1077f4,0x1070f0,Kind::work_item},
    {0x1077fc,0x1018e0,Kind::work},
    {0x107870,0x1070f0,Kind::work_item},
    {0x1078bd,0x1070f0,Kind::work_item},
    {0x107a96,0x5340,Kind::trap},
    {0x107abb,0x5340,Kind::trap},
    {0x107ac8,0x5340,Kind::trap},
    {0x107da6,0xae3f0,Kind::silhouette},
    {0x107e28,0xadca0,Kind::profile},
    {0x107ebc,0xae750,Kind::corpse},
    {0x107fb9,0x19610,Kind::burntime},
    {0x10866b,0x15e4d0,Kind::temperature},
    {0x118499,0x163840,Kind::activity_copy},
    {0x1184f7,0x163190,Kind::activity},
    {0x1185a8,0x163190,Kind::activity},
    {0x1187e5,0x163840,Kind::activity_copy},
    {0x118963,0x15e2c0,Kind::tree},
    {0x1189c3,0xd4020,Kind::lowercase},
    {0x118a12,0xd4020,Kind::lowercase},
    {0x118c29,0x163190,Kind::activity},
    {0x118eed,0x162bd0,Kind::indefinite},
    {0x1190e4,0x1070f0,Kind::work_item},
    {0x1190ec,0x1018e0,Kind::work},
    {0x119936,0x163840,Kind::activity_copy},
    {0x1199f7,0x163190,Kind::activity},
    {0x11ab2a,0x163840,Kind::activity_copy},
    {0x11ab85,0x163190,Kind::activity},
    {0x11abca,0x163840,Kind::activity_copy},
    {0x11b31c,0x163190,Kind::activity},
    {0x11b337,0x163190,Kind::activity},
    {0x11b352,0x163190,Kind::activity},
    {0x11b36d,0x163190,Kind::activity},
    {0x11b388,0x163190,Kind::activity},
    {0x11b3a3,0x163190,Kind::activity},
    {0x11b3be,0x163190,Kind::activity},
    {0x11bb2e,0xd4020,Kind::lowercase},
    {0x11bc90,0xd4020,Kind::lowercase},
    {0x11c821,0xae680,Kind::corpse_age},
    {0x11c831,0xae750,Kind::corpse},
    {0x11c89b,0x163840,Kind::activity_copy},
    {0x11cab9,0xad4f0,Kind::npc},
    {0x11d320,0x163190,Kind::activity},
    {0x11d366,0x163840,Kind::activity_copy},
    {0x11d3d2,0xae680,Kind::corpse_age},
    {0x11d3e5,0xae750,Kind::corpse},
    {0x11d443,0xd450,Kind::corpse_burn},
    {0x11d460,0xae750,Kind::corpse},
    {0x11d4d9,0x163840,Kind::activity_copy},
    {0x11d52a,0xae480,Kind::corpse_damage},
    {0x11d5ab,0xd6f00,Kind::corpse_injury},
    {0x11dddf,0x163190,Kind::activity},
    {0x11dde6,0xd4020,Kind::lowercase},
    {0x11de05,0x163190,Kind::activity},
    {0x11de0c,0xd4020,Kind::lowercase},
    {0x11de7d,0x163840,Kind::activity_copy},
    {0x11defa,0x163190,Kind::activity},
    {0x11e26a,0x163190,Kind::activity},
    {0x11e271,0xd4020,Kind::lowercase},
    {0x11e292,0x163190,Kind::activity},
    {0x11e299,0xd4020,Kind::lowercase},
    {0x11e2e0,0x163840,Kind::activity_copy},
    {0x11e33c,0x163190,Kind::activity},
    {0x11e577,0x199b0,Kind::time},
    {0x11e5d2,0x163190,Kind::activity},
    {0x11e642,0x163840,Kind::activity_copy},
    {0x11edf1,0x163190,Kind::activity},
    {0x11edf8,0xd4020,Kind::lowercase},
    {0x11ee18,0x163190,Kind::activity},
    {0x11ee1f,0xd4020,Kind::lowercase},
    {0x11f076,0x163840,Kind::activity_copy},
    {0x11f0ab,0x163190,Kind::activity},
    {0x11f0b6,0xd4020,Kind::lowercase},
    {0x11f5f6,0xd4020,Kind::lowercase},
    {0x11f9a0,0x163840,Kind::activity_copy},
    {0x11fafd,0xd4020,Kind::lowercase},
    {0x11fbb5,0x163190,Kind::activity},
    {0x11fd38,0x163840,Kind::activity_copy},
    {0x1201f8,0x163840,Kind::activity_copy},
    {0x1202e6,0x1018e0,Kind::work},
    {0x120521,0x4b800,Kind::quantity},
    {0x120556,0x4b800,Kind::quantity},
    {0x120768,0x163190,Kind::activity},
    {0x1208f4,0x163190,Kind::activity},
    {0x120a4b,0x163190,Kind::activity},
    {0x120e62,0x163190,Kind::activity},
    {0x12143b,0x163190,Kind::activity},
    {0x12191e,0x163190,Kind::activity},
    {0x121ddc,0x163190,Kind::activity},
    {0x121df7,0x163190,Kind::activity},
    {0x121e12,0x163190,Kind::activity},
    {0x121e2d,0x163190,Kind::activity},
    {0x121e48,0x163190,Kind::activity},
    {0x121e63,0x163190,Kind::activity},
    {0x121eac,0x163190,Kind::activity},
    {0x121ec7,0x163190,Kind::activity},
    {0x121ee2,0x163190,Kind::activity},
    {0x121efd,0x163190,Kind::activity},
    {0x121f18,0x163190,Kind::activity},
    {0x1220c2,0xad4f0,Kind::npc},
    {0x123a56,0xd4020,Kind::lowercase},
    {0x128db6,0xd4600,Kind::bodypart},
    {0x12c385,0xad4f0,Kind::npc},
    {0x12c3f0,0xad4f0,Kind::npc},
    {0x12c42a,0xad4f0,Kind::npc},
    {0x12d679,0xd4600,Kind::bodypart},
    {0x12dc6d,0xd4020,Kind::lowercase},
    {0x12dd27,0xd4020,Kind::lowercase},
    {0x12dde6,0xd4020,Kind::lowercase},
    {0x12de5a,0xd4020,Kind::lowercase},
    {0x12f431,0xd4020,Kind::lowercase},
    {0x12f438,0x162bd0,Kind::indefinite},
    {0x12f4da,0xd4020,Kind::lowercase},
    {0x12f4e1,0x162bd0,Kind::indefinite},
    {0x1302cc,0xd4600,Kind::bodypart},
    {0x1321c8,0xd4020,Kind::lowercase},
    {0x132460,0xd4020,Kind::lowercase},
    {0x132610,0xd4020,Kind::lowercase},
    {0x134174,0xad4f0,Kind::npc},
    {0x1342f8,0xad4f0,Kind::npc},
    {0x135529,0xd4020,Kind::lowercase},
    {0x135530,0x15eff0,Kind::plural},
    {0x1355cc,0xd4020,Kind::lowercase},
    {0x1355d3,0x15eff0,Kind::plural},
    {0x1355f5,0xd4020,Kind::lowercase},
    {0x1355fc,0x15eff0,Kind::plural},
    {0x13a02c,0xad4f0,Kind::npc},
    {0x13a07d,0xad4f0,Kind::npc},
    {0x13a0b1,0xad4f0,Kind::npc},
    {0x13a0e3,0xad4f0,Kind::npc},
    {0x13a117,0xad4f0,Kind::npc},
    {0x13a14d,0xad4f0,Kind::npc},
    {0x13bf60,0xad4f0,Kind::npc},
    {0x13ca3a,0xd4020,Kind::lowercase},
    {0x13ce0e,0x162bd0,Kind::indefinite},
    {0x13d070,0x15eff0,Kind::plural},
    {0x13d0df,0xd4020,Kind::lowercase},
    {0x13d178,0x15eff0,Kind::plural},
    {0x13d17f,0xd4020,Kind::lowercase},
    {0x13d1a2,0xd4020,Kind::lowercase},
    {0x13d1a9,0x162bd0,Kind::indefinite},
    {0x13d206,0x15eff0,Kind::plural},
    {0x13d213,0x162bd0,Kind::indefinite},
    {0x13e7dd,0x199b0,Kind::time},
    {0x1403e8,0x163190,Kind::activity},
    {0x1407c8,0x162bd0,Kind::indefinite},
    {0x141533,0x15eff0,Kind::plural},
    {0x142f0c,0xad4f0,Kind::npc},
    {0x142f15,0xadbc0,Kind::corpse_size},
    {0x1431eb,0xad4f0,Kind::npc},
    {0x143c52,0xad4f0,Kind::npc},
    {0x146809,0xad4f0,Kind::npc},
    {0x146d62,0x846c0,Kind::identity},
    {0x14899a,0xd4020,Kind::lowercase},
    {0x148d42,0xd4020,Kind::lowercase},
    {0x149513,0xe7ef0,Kind::spell},
    {0x149532,0xe7ef0,Kind::spell},
    {0x14954a,0xe7ef0,Kind::spell},
    {0x14bba8,0xd4020,Kind::lowercase},
    {0x14bbc9,0xd4020,Kind::lowercase},
    {0x14ddaf,0xae3f0,Kind::silhouette},
    {0x14de24,0xd4020,Kind::lowercase},
    {0x14f2d1,0xd4020,Kind::lowercase},
    {0x14f36b,0xd4020,Kind::lowercase},
    {0x15175f,0xae3f0,Kind::silhouette},
    {0x152a00,0xe7ef0,Kind::spell},
    {0x1531bc,0xe7ef0,Kind::spell},
    {0x154669,0xad4f0,Kind::npc},
    {0x154baf,0xae3f0,Kind::silhouette},
    {0x1551ab,0xad4f0,Kind::npc},
    {0x1551b2,0xd4020,Kind::lowercase},
    {0x155762,0xad4f0,Kind::npc},
    {0x1568c8,0xae3f0,Kind::silhouette},
    {0x157bbc,0xae3f0,Kind::silhouette},
    {0x15e42c,0x15e2c0,Kind::tree},
    {0x15efb6,0x15ee90,Kind::encounter},
    {0x15f041,0xd4020,Kind::lowercase},
    {0x160226,0x15eba0,Kind::direction},
    {0x16025b,0x15eba0,Kind::direction},
    {0x1605ed,0x846c0,Kind::identity},
    {0x160624,0x846c0,Kind::identity},
    {0x1607a0,0x162bd0,Kind::indefinite},
    {0x1607d2,0x162cf0,Kind::definite},
    {0x1609c3,0x162cf0,Kind::definite},
    {0x1609f5,0x162bd0,Kind::indefinite},
    {0x160b17,0xad4f0,Kind::npc},
    {0x160b54,0xad4f0,Kind::npc},
    {0x160b71,0x162bd0,Kind::indefinite},
    {0x160be1,0xad4f0,Kind::npc},
    {0x162f61,0x15eff0,Kind::plural},
    {0x16387c,0x163190,Kind::activity},
    {0x1638b3,0xd4020,Kind::lowercase},
    {0x163972,0x163190,Kind::activity},
    {0x1662f5,0xd4020,Kind::lowercase},
    {0x166388,0x101790,Kind::construction},
    {0x1663c0,0x101790,Kind::construction},
    {0x166d1e,0xd4020,Kind::lowercase},
    {0x167ada,0xd4020,Kind::lowercase},
    {0x16c1b4,0xd4600,Kind::bodypart},
    {0x172e79,0x15eff0,Kind::plural},
    {0x173048,0xae3f0,Kind::silhouette},
    {0x17317a,0xae3f0,Kind::silhouette},
    {0x173187,0x162bd0,Kind::indefinite},
    {0x176a5a,0xae3f0,Kind::silhouette},
    {0x17a393,0x846c0,Kind::identity},
    {0x17a39e,0x846c0,Kind::identity},
    {0x17a434,0x846c0,Kind::identity},
    {0x17a43f,0x846c0,Kind::identity},
    {0x17a521,0x846c0,Kind::identity},
    {0x17a52c,0x846c0,Kind::identity},
    {0x17baa4,0xae3f0,Kind::silhouette},
    {0x17d182,0xd4020,Kind::lowercase},
    {0x17fab9,0xd4020,Kind::lowercase},
    {0x17fade,0xd4020,Kind::lowercase},
    {0x17fb0a,0xd4020,Kind::lowercase},
    {0x183acb,0xd4600,Kind::bodypart},
    {0x1842c8,0x15f450,Kind::temperature},
    {0x184434,0xd4600,Kind::bodypart},
    {0x1844a8,0xd4600,Kind::bodypart},
    {0x184532,0xd4600,Kind::bodypart},
};
struct Value {u32 site,producer,owner;std::string domain,original;MessageText text;};
struct Part {MessageText text;bool comma;};
struct Pending {
    Kind kind;u32 ecx,edx;std::string input;MessageText text,detail;
    Status source_status=Status::ok;
    std::vector<Value> children;std::vector<Part> parts;
};
std::vector<Pending> pending;
std::vector<std::vector<Value>> tags;
const char* producer_domain(u32 producer) {
    switch(producer) {
    case 0x51770:case 0x52640:case 0x1070f0:case 0x40b20:return "item";
    case 0x51510:return "item.quality";
    case 0x15e2c0:return "tree";
    case 0xad4f0:case 0xae3f0:case 0x15ee90:case 0xadca0:return "npc";
    case 0x846c0:return "identity";
    case 0xd4600:return "bodypart";
    case 0x15eba0:return "direction";
    case 0x15fd00:case 0x15fe60:return "status";
    case 0x199b0:case 0x19610:return "time";
    case 0x4b2f0:case 0x4b800:return "unit";
    case 0xd71b0:return "injury";
    case 0x5340:return "trap";
    case 0x1018e0:case 0x101790:return "work";
    case 0x163190:case 0x163840:return "activity";
    case 0x15e4d0:case 0x15f450:return "temperature";
    case 0xe7ef0:return "spell";
    case 0xadbc0:case 0xae480:case 0xae680:case 0xd6f00:case 0xd450:case 0xae750:return "corpse";
    default:return "bound";
    }
}
void observe_chain_value(u32,u32,const char*,const MessageText&);
void begin_tag() {tags.emplace_back();}
void end_tag() {tags.pop_back();}
void observe_value(u32 site,u32 producer,const char* original,const MessageText& text) {
    const Value value{site,producer,address(original),producer_domain(producer),original,text};
    if(!pending.empty()) pending.back().children.push_back(value);
    if(!tags.empty()) tags.back().push_back(value);
    observe_chain_value(site,producer,original,text);
}
MessageText source(const char* domain,const char* original) {
    if(*original=='\0') return native_message_source::original("");
    const auto find=[&](const std::vector<Value>& values)->const MessageText* {
        for(auto i=values.rbegin();i!=values.rend();++i)
            if((std::strcmp(domain,"bound")==0 || i->domain==domain || i->domain=="bound") &&
               i->original==original) return &i->text;
        return nullptr;
    };
    if(!pending.empty()) if(const auto* value=find(pending.back().children)) return *value;
    if(!tags.empty()) if(const auto* value=find(tags.back())) return *value;
    return std::strcmp(domain,"bound")==0 ? message_source_bound(original):message_source_lookup(domain,original);
}
Status resolve(const char* domain,const char* original,std::string& output) {
    return message_project_source(source(domain,original),true,output);
}
MessageText pattern(const char* domain,const char* original,std::initializer_list<MessageText> values) {
    return native_message_source::format(message_source_lookup(domain,original),values,
        std::vector<std::string>(values.size(),"%s"));
}
MessageText npc_source(const Pending& call) {
    const auto index=static_cast<std::int32_t>(call.ecx);const auto flags=call.edx;
    if(index==-1) return message_source_lookup("npc","human");
    const auto* creature=at<unsigned char>(0x5d51400+static_cast<u32>(index)*0x568);
    const auto category=creature[0];const auto species=*reinterpret_cast<const u32*>(creature+0xbc);
    const auto gender=creature[0xcf],known=creature[0x1dc];
    const auto* description=reinterpret_cast<const char*>(creature+8);
    const auto* proper_name=reinterpret_cast<const char*>(creature+0x30);
    if(flags&1) return message_source_lookup("npc",category==1 ? "human":description);
    auto text=message_source_lookup("npc",description);
    if(category!=1) {
        if(gender&2) {
            const char* young=species==0x25e || species==0x26b || species==0x26c || species==0x294
                ? "calf" : species==0x265 || species==0x266 || species==0x267 ? "piglet"
                : species==0x268 ? "lamb" : species==0x26a ? "puppy" : "cub";
            const auto name=message_source_lookup("npc",young);
            if(species==0x265 || species==0x266 || species==0x267 || species==0x268) text=name;
            else text=pattern("npc","%s %s",{text,name});
        } else if(gender&1) {
            if(species==0x294) text=pattern("npc","bull %s",{text});
            else if(species==0x268) text=message_source_lookup("npc","ram");
            else if(species==0x267) text=message_source_lookup("npc","boar");
            else if(species==0x26b || species==0x26c)
                text=native_message_source::concat({text,message_source_lookup("npc"," stag")});
        } else {
            if(species==0x25d) text=pattern("npc","female %s",{text});
            else if(species==0x267) text=message_source_lookup("npc","sow");
            else if(species==0x26a) text=message_source_lookup("npc","female dog");
            else if(species==0x26b || species==0x26c)
                text=native_message_source::concat({text,message_source_lookup("npc"," doe")});
        }
    }
    if(flags&8) return pattern("npc","%s the %s",{message_source_identity(proper_name),text});
    const auto description_text=text;bool definite=true;
    if((known&1) || (category==1 && *at<u32>(0xa2d28a0)!=0)) {
        text=message_source_identity(proper_name);
        if(flags&4) text=pattern("npc","%s the %s",{text,description_text});
        if(flags&2) text=message_source_identity(proper_name);
        definite=false;
    }
    if(known&2) {
        text=message_source_identity(proper_name);if(flags&2) definite=false;
        if(flags&4) {text=pattern("npc","%s called %s",{description_text,text});definite=true;}
    }
    if((flags&2) && definite) text=pattern("article","the %s",{text});
    return text;
}
MessageText tag_source(const char* tag,const char* original) {
    // Exact shipped tags, classified from 5601C0. The native lookup alone
    // consumes control tokens such as MALE/FEM/ANIMAL and attack aspects.
    const std::string name=tag;
    const auto one_of=[&](std::initializer_list<const char*> names) {
        for(const auto* candidate:names) if(name==candidate) return true;
        return false;
    };
    if(one_of({"npc","who","attacker","defender","num","prepdays","weapon_slot",
        "wc_bonus","attack_class","defense_class","attack_aspect","defend_aspect"}))
        return native_message_source::original(original);
    if(name=="plr_name" || name=="identity") return message_source_identity(original);
    if(name=="direction" || name=="npc_direction") return source("direction",original);
    if(one_of({"npc_sound","npc_aggsound","attacker_sound","attacker_aggsound",
        "defender_sound","defender_aggsound","who_sound","who_aggsound"})) return source("sound",original);
    if(name=="plr_gender") return source("npc",original);
    if(name=="plr_identity" || name=="plr_bad_name") return source("identity",original);
    if(one_of({"reptitle_help_ind","reptitle_mischief_ind","reptitle_stealing",
        "reptitle_tra_ind","reptitle_trading","reptitle_trading_ind"})) return source("reputation",original);
    if(one_of({"fullitem","item","item_container","item_def","item_def_verbose","item_defdesc",
        "item_ind","item_raw","item_verbose_def","item_verbose_ind","items","items_ind",
        "items_nonum","items_verbose","raw_item","the_fullitem","the_fullitem(s)","the_item",
        "the_item_container"})) return source("item",original);
    if(name=="attack_weapon") return source("bound",at<char>(0x1e9e88));
    if(name=="attack_bow") return source("bound",at<char>(0x1e9ce8));
    if(name=="defend_weapon") return source("bound",at<char>(0x1e9c80));
    if(name=="bodypart") return source("bound",at<char>(0x1e9db8));
    if(name=="bodypart_counterstrike") return source("bound",at<char>(0x1e9d50));
    if(name=="wounded_bodypart") return source("bound",at<char>(0x1e9bb0));
    if(name=="status") return source("bound",at<char>(0x1e9b08));
    if(one_of({"attacker_defdesc","attacker_desc","defender_defdesc","defender_desc",
        "defender_descdesc","npc_defdesc","npc_definite_partitive","npc_desc","npc_ind",
        "the_npc"})) return source("npc",original);
    if(name=="var") return source("bound",at<char>(0x1e98d0));
    if(name=="%s" || name=="bound") return source("bound",original);
    return source(tag,original);
}
Status translate_tag(const char* tag,const char* original,std::string& output) {
    return message_project_source(tag_source(tag,original),true,output);
}
const char* transform_domain(u32 site) {
    // These inputs are raw descriptor fields, not a copied producer return.
    // High p-code and the actual descriptor copies are recorded in
    // settlement-value-transform-inputs.tsv / settlement-transform-upstreams-ghidra.c.
    switch(site) {
    case 0x166b:case 0x32867:case 0x35796:case 0x35b7d:case 0x58569:case 0x585bd:
    case 0xb15e0:case 0xb1602:case 0xbc7a9:
    case 0x12dc6d:case 0x12dd27:case 0x12dde6:case 0x12de5a:
    case 0x1321c8:case 0x14de24:
    case 0x17fab9:case 0x17fade:case 0x17fb0a:return "item";
    case 0x11f5f6:return "item.alternate";
    case 0x2c82f:case 0xa0996:case 0xc0d9a:case 0x14bba8:case 0x14bbc9:
    case 0x14f2d1:case 0x14f36b:case 0x167ada:return "npc";
    case 0x41cb2:return "menu.recipe";
    case 0x2da73:case 0x2da9d:return "identity";
    case 0xd5348:return "status";
    case 0x58452:case 0x9f972:case 0xa35fd:case 0xdabac:
    case 0x11bb2e:case 0x11bc90:case 0x17d182:return "posture";
    case 0x83fd0:case 0x8412f:case 0x841e6:case 0x842c0:
    case 0x1607a0:case 0x1607d2:return "reputation";
    case 0x123a56:return "skill";
    case 0x1638b3:return "activity";
    default:return "bound";
    }
}
#include "windows_message_value_builders.inc"
void append_hooks(std::vector<HookSpec>& hooks) {
    for(u32 i=0;i<sizeof(sites)/sizeof(sites[0]);++i)
        hooks.push_back(native_name_input::native_call(first_hook+i,sites[i].site,sites[i].target,0));
    append_builder_hooks(hooks);
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    const auto builder_status=dispatch_builder(event,handled);if(handled) return builder_status;
    handled=event.id>=first_hook && event.id<first_hook+sizeof(sites)/sizeof(sites[0]);
    if(!handled) return Status::ok;
    const auto& site=sites[event.id-first_hook];const auto kind=site.kind;
    if(event.phase==NativePhase::before) {
        Pending call{};call.kind=kind;call.ecx=event.frame->ecx;call.edx=event.frame->edx;
        if(kind==Kind::plural || kind==Kind::singular || kind==Kind::indefinite ||
           kind==Kind::definite || kind==Kind::lowercase) {
            const auto* input=ptr<char>(call.ecx);
            windows_message_items::prepare_input(site.site,site.target,input);call.input=input;
            if((kind==Kind::plural || kind==Kind::singular) && call.input.find('/')!=std::string::npos)
                call.text=message_source_lookup("grammar",input);
            else if(std::strcmp(transform_domain(site.site),"item")==0)
                // Every site in this exact group passes descriptor +9, as
                // recorded in settlement-value-transform-inputs.tsv. Keep
                // its native naming selector for persisted compound names.
                call.source_status=message_crafted_item_source(reinterpret_cast<const unsigned char*>(input)-9,input,call.text);
            else call.text=source(transform_domain(site.site),input);
        }
        if(kind==Kind::encounter) call.text=source(site.site==0x15efb6 ? "bound":"npc",ptr<char>(call.edx));
        prepare_chain_call(call,site,event);
        pending.push_back(std::move(call));return Status::ok;
    }
    auto& call=pending.back();
    if(call.source_status!=Status::ok) {
        const auto status=call.source_status;pending.pop_back();
        windows_message_items::observe_status(site.site,site.target,status);return status;
    }
    if((kind==Kind::work || kind==Kind::construction) && event.frame->eax==0) {pending.pop_back();return Status::ok;}
    if(kind==Kind::list_add) {pending.pop_back();return Status::ok;}
    const auto* original=ptr<char>(kind==Kind::corpse_damage || kind==Kind::corpse_age ||
        kind==Kind::corpse_injury ? call.edx:kind==Kind::corpse_burn || kind==Kind::helper_list ? call.ecx:event.frame->eax);
    switch(kind) {
    case Kind::quality:call.text=message_source_lookup("item.quality",original);break;
    case Kind::tree:call.text=message_source_lookup("tree",original);break;
    case Kind::direction:call.text=message_source_lookup("direction",original);break;
    case Kind::npc:call.text=npc_source(call);break;
    case Kind::proper:call.text=message_source_identity(original);break;
    case Kind::track_age:call.text=message_source_lookup("track-age",original);break;
    case Kind::identity:call.text=identity_source(call,original);break;
    case Kind::bodypart:call.text=source("bound",original);break;
    // Formatted branches bind actual scalar arguments below; the other native
    // time branches copy complete literal values. Neither parses output text.
    case Kind::time:case Kind::burntime:call.text=source("time",original);break;
    case Kind::quantity:call.text=message_source_bound(original);break;
    case Kind::injury:call.text=injury_source(call,original);break;
    case Kind::injury_label: {
        if(call.input=="compound") {
            MessageText part;
            for(const auto& child:call.children) if(child.producer==0xd4600) part=child.text;
            call.text=pattern("injury","%sin %s",{call.text,native_message_source::concat({call.detail,part})});
        } else call.text=message_source_lookup("injury",original);
        break;
    }
    case Kind::hunger:case Kind::thirst:call.text=message_source_lookup("status",original);break;
    case Kind::trap:call.text=source("trap",original);break;
    case Kind::work:call.text=message_source_lookup("work",original);break;
    case Kind::activity:call.text=message_source_lookup("activity",original);break;
    case Kind::activity_copy:case Kind::work_item:case Kind::silhouette:case Kind::construction:
        call.text=source("bound",original);break;
    case Kind::temperature:call.text=message_source_lookup("temperature",original);break;
    case Kind::spell:call.text=message_source_lookup("spell",original);break;
    case Kind::corpse_size:call.text=source("bound",original);break;
    case Kind::corpse_damage:case Kind::corpse_injury:
        call.text=*original ? message_source_template(call.input.c_str(),original):native_message_source::original("");break;
    case Kind::corpse_age:case Kind::corpse_burn:
        call.text=*original ? message_source_lookup("corpse",original):native_message_source::original("");break;
    case Kind::profile:if(call.input!="normal" && call.input!="normalized") call.text=source("bound",original);break;
    case Kind::craft:if(call.input!="list") call.text=source("bound",original);break;
    case Kind::treatment:call.text=message_source_lookup("treatment",original);break;
    case Kind::flora:call.text=source("bound",original);break;
    case Kind::helper_list:call.text=source("bound",original);break;
    case Kind::bowstring:
        call.text=call.input=="formatted" ? source("bound",original):message_source_lookup("bowstring",original);break;
    case Kind::comma_list:case Kind::or_list:call.text=comma_list_source(call,original);break;
    case Kind::plural:
        // 572E57 reads arbitrary user text for the native plural diagnostic;
        // 572E80 echoes the native result, not an authored game noun.
        if(site.site==0x172e79) call.text=message_source_identity(original);
        break;
    case Kind::corpse:case Kind::count_list:case Kind::list_add:case Kind::encounter:
    case Kind::singular:case Kind::lowercase:case Kind::indefinite:case Kind::definite:break;
    }
    // These native grammar operations change the English spelling while
    // retaining the same semantic child. Keep its lookup key (in particular
    // the complete singular/plural slash entry) below the actual-owner node.
    const bool transformed=kind==Kind::plural || kind==Kind::singular ||
        kind==Kind::indefinite || kind==Kind::definite || kind==Kind::lowercase || kind==Kind::encounter;
    auto text=transformed ? native_message_source::concat({call.text}):call.text;
    text.original=message_source_utf8(original);capture_copy(site,event,text);pending.pop_back();
    message_bind_source(original,text);observe_value(site.site,site.target,original,text);
    windows_message_items::observe_value(site.site,site.target,original,text);return Status::ok;
}
void save(std::vector<unsigned char>& output) {
    const auto write_values=[&](const std::vector<Value>& values) {
        message_state_write(output,static_cast<u32>(values.size()));
        for(const auto& value:values) {
            message_state_write(output,value.site);message_state_write(output,value.producer);message_state_write(output,value.owner);
            message_state_string(output,value.domain);message_state_string(output,value.original);native_message_source::write(output,value.text);
        }
    };
    message_state_write(output,static_cast<u32>(pending.size()));
    for(const auto& call:pending) {
        message_state_write(output,call.kind);message_state_write(output,call.ecx);message_state_write(output,call.edx);message_state_write(output,call.source_status);
        message_state_string(output,call.input);native_message_source::write(output,call.text);native_message_source::write(output,call.detail);
        write_values(call.children);message_state_write(output,static_cast<u32>(call.parts.size()));
        for(const auto& part:call.parts) {message_state_write(output,part.comma);native_message_source::write(output,part.text);}
    }
    message_state_write(output,static_cast<u32>(tags.size()));for(const auto& tag:tags) write_values(tag);save_builders(output);
}
void restore(const unsigned char*& input) {
    const auto read_values=[&](std::vector<Value>& values) {
        u32 count;message_state_read(input,count);
        for(u32 i=0;i<count;++i) {
            Value value;message_state_read(input,value.site);message_state_read(input,value.producer);message_state_read(input,value.owner);
            message_state_string(input,value.domain);message_state_string(input,value.original);value.text=native_message_source::read(input);
            values.push_back(std::move(value));
        }
    };
    u32 count;message_state_read(input,count);pending.clear();
    for(u32 i=0;i<count;++i) {
        Pending call;message_state_read(input,call.kind);message_state_read(input,call.ecx);message_state_read(input,call.edx);message_state_read(input,call.source_status);
        message_state_string(input,call.input);call.text=native_message_source::read(input);call.detail=native_message_source::read(input);
        read_values(call.children);u32 parts;message_state_read(input,parts);
        for(u32 n=0;n<parts;++n) {Part part;message_state_read(input,part.comma);part.text=native_message_source::read(input);call.parts.push_back(std::move(part));}
        pending.push_back(std::move(call));
    }
    message_state_read(input,count);tags.clear();tags.resize(count);for(auto& tag:tags) read_values(tag);restore_builders(input);
}
}
