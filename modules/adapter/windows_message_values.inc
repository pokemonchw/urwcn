// PE 3.89 native value producers. These companions contain text only.
// Evidence: settlement-value-producers-ghidra.c, settlement-additional-values-ghidra.c,
// settlement-final-name-primitives-ghidra.c and settlement-message-helpers-ghidra.c.
Status message_lookup_value(const char*,const char*,std::string&);
Status message_translate_bound(const char*,std::string&);
Status message_identity_value(const char*,std::string&);
void message_bind_value(const char*,const std::string&);
namespace windows_message_items {
void observe_value(u32,u32,const char*,const std::string&);
void prepare_input(u32,u32,const char*);
void observe_status(u32,u32,Status);
}

namespace windows_message_values {
constexpr u32 first_hook=0xc000;
enum class Kind : u32 { quality,tree,direction,plural,singular,indefinite,definite,
    lowercase,npc,identity,bodypart,time,quantity,injury,hunger,thirst,trap,
    work,work_item,construction,activity,activity_copy,silhouette,burntime,
    temperature,encounter,spell,profile,corpse_size,corpse_damage,corpse_age,corpse_injury };
struct Site {u32 site,target;Kind kind;};
// GENERATED_NATIVE_VALUE_SITES
const Site sites[]={
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
    {0x13d25,0xd4020,Kind::lowercase},
    {0x1bec8,0x199b0,Kind::time},
    {0x27636,0xad4f0,Kind::npc},
    {0x2c82f,0x162bd0,Kind::indefinite},
    {0x2c8aa,0x15ee90,Kind::encounter},
    {0x2cd75,0xad4f0,Kind::npc},
    {0x2da73,0x162bd0,Kind::indefinite},
    {0x2da9d,0x162bd0,Kind::indefinite},
    {0x2fa0e,0x162bd0,Kind::indefinite},
    {0x2fdfe,0x162bd0,Kind::indefinite},
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
    {0x3d09d,0xd4020,Kind::lowercase},
    {0x40c9f,0x162bd0,Kind::indefinite},
    {0x40d1f,0x51510,Kind::quality},
    {0x40d26,0x162bd0,Kind::indefinite},
    {0x40dfa,0x51510,Kind::quality},
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
    {0x4bd10,0x4b2f0,Kind::quantity},
    {0x4be5a,0xd4020,Kind::lowercase},
    {0x4bf70,0xd4020,Kind::lowercase},
    {0x4cb7b,0x199b0,Kind::time},
    {0x4fd4d,0x163190,Kind::activity},
    {0x4fe92,0x163190,Kind::activity},
    {0x50b1b,0x162cf0,Kind::definite},
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
    {0x987d1,0xae480,Kind::corpse_damage},
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
    {0xadcfe,0xadbc0,Kind::corpse_size},
    {0xadd57,0xad4f0,Kind::npc},
    {0xae325,0xad4f0,Kind::npc},
    {0xae444,0xad4f0,Kind::npc},
    {0xae7d8,0xae480,Kind::corpse_damage},
    {0xae800,0xadca0,Kind::profile},
    {0xae80f,0xadca0,Kind::profile},
    {0xae88d,0xd6f00,Kind::corpse_injury},
    {0xae944,0xae680,Kind::corpse_age},
    {0xaed15,0xadca0,Kind::profile},
    {0xaf320,0xd71b0,Kind::injury},
    {0xaf342,0xd4020,Kind::lowercase},
    {0xaf58a,0xd4020,Kind::lowercase},
    {0xaf7a2,0xd4020,Kind::lowercase},
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
    {0xd931c,0xd4020,Kind::lowercase},
    {0xd9922,0xd4020,Kind::lowercase},
    {0xd9a10,0xd71b0,Kind::injury},
    {0xd9a17,0xd4020,Kind::lowercase},
    {0xd9a6b,0xd71b0,Kind::injury},
    {0xd9a72,0xd4020,Kind::lowercase},
    {0xd9c06,0xd4020,Kind::lowercase},
    {0xd9c77,0xd4020,Kind::lowercase},
    {0xdabac,0xd4020,Kind::lowercase},
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
    {0x10769d,0x101790,Kind::construction},
    {0x107701,0x162bd0,Kind::indefinite},
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
    {0x11c89b,0x163840,Kind::activity_copy},
    {0x11cab9,0xad4f0,Kind::npc},
    {0x11d320,0x163190,Kind::activity},
    {0x11d366,0x163840,Kind::activity_copy},
    {0x11d3d2,0xae680,Kind::corpse_age},
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
    {0x1394b2,0xd4020,Kind::lowercase},
    {0x1394d9,0xd4020,Kind::lowercase},
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
    {0x140447,0xd4020,Kind::lowercase},
    {0x1407c8,0x162bd0,Kind::indefinite},
    {0x1414e5,0xd4020,Kind::lowercase},
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
    {0x1498f5,0xd4020,Kind::lowercase},
    {0x149915,0xd4020,Kind::lowercase},
    {0x1499b1,0xd4020,Kind::lowercase},
    {0x149a01,0xd4020,Kind::lowercase},
    {0x149a3a,0xd4020,Kind::lowercase},
    {0x149a90,0xd4020,Kind::lowercase},
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
    {0x156480,0xd4020,Kind::lowercase},
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
struct Value {u32 site,producer,owner;std::string domain,source,translated;};
struct Pending {Kind kind;u32 ecx,edx;Status status;std::string input,translated;std::vector<Value> children;};
std::vector<Pending> pending;
std::vector<std::vector<Value>> tags;

const char* producer_domain(u32 producer) {
    switch(producer) {
    case 0x51770:case 0x52640:return "item";
    case 0x51510:return "item.quality";
    case 0x15e2c0:return "tree";
    case 0xad4f0:return "npc";
    case 0x846c0:return "identity";
    case 0xd4600:return "bodypart";
    case 0x15eba0:return "direction";
    case 0x15fd00:case 0x15fe60:return "status";
    case 0x199b0:return "time";
    case 0x4b2f0:case 0x4b800:return "unit";
    case 0xd71b0:return "injury";
    case 0x5340:return "trap";
    case 0x1018e0:case 0x101790:return "work";
    case 0x1070f0:return "item";
    case 0x163190:case 0x163840:return "activity";
    case 0xae3f0:case 0x15ee90:return "npc";
    case 0x19610:return "time";
    case 0x15e4d0:case 0x15f450:return "temperature";
    case 0xe7ef0:return "spell";
    case 0xadbc0:case 0xae480:case 0xae680:case 0xd6f00:case 0xd450:case 0xae750:return "corpse";
    default:return "bound";
    }
}
void begin_tag() {tags.emplace_back();}
void end_tag() {tags.pop_back();}
void observe_value(u32 site,u32 producer,const char* original,const std::string& translated) {
    const Value value{site,producer,address(original),producer_domain(producer),original,translated};
    if(!pending.empty()) pending.back().children.push_back(value);
    if(!tags.empty()) tags.back().push_back(value);
}
Status resolve(const char* domain,const char* source,std::string& translated) {
    // Only actual child results of the currently executing native producer or
    // 5601C0 tag expansion participate in native byte-copy propagation.
    const auto find=[&](const std::vector<Value>& values) {
        for(auto i=values.rbegin();i!=values.rend();++i) {
            if((std::strcmp(domain,"bound")==0 || i->domain==domain || i->domain=="bound") &&
               i->source==source) {translated=i->translated;return true;}
        }
        return false;
    };
    if(!pending.empty() && find(pending.back().children)) return Status::ok;
    if(!tags.empty() && find(tags.back())) return Status::ok;
    if(std::strcmp(domain,"bound")==0) return message_translate_bound(source,translated);
    return message_lookup_value(domain,source,translated);
}
Status name_value(const char* source,std::string& translated) {
    if(*source=='\0') {translated.clear();return Status::ok;}
    return resolve("bound",source,translated);
}
Status pattern(const char*,const char*,std::initializer_list<std::string>,std::string&);
Status quantity_value(const char* source,std::string& translated) {
    // 44B2F0 and 44B800 append one of these unit strings to a native
    // %.0f/%.1f/%.2f result. The native number and precision are retained.
    const std::string value=source;
    const auto split=value.find(' ');
    if(split==std::string::npos) {
        if(value.find_first_not_of("0123456789.-")==std::string::npos) {
            translated=value;return Status::ok;
        }
        return message_lookup_value("unit",source,translated);
    }
    std::string unit;
    const auto status=message_lookup_value("unit",value.substr(split+1).c_str(),unit);
    if(status==Status::ok) translated=value.substr(0,split)+unit;
    return status;
}
Status time_value(const char* source,std::string& translated) {
    const std::string value=source;
    if(value.compare(0,6,"after ")==0 && value.size()>11 &&
       value.compare(value.size()-5,5," days")==0) {
        auto status=message_lookup_value("time","after %d days",translated);
        if(status==Status::ok) translated.replace(translated.find("%d"),2,value.substr(6,value.size()-11));
        return status;
    }
    if(value.compare(0,3,"by ")==0) {
        std::string time;
        const auto status=message_lookup_value("time",value.substr(3).c_str(),time);
        return status==Status::ok ? pattern("time","by %s",{time},translated):status;
    }
    if(value.compare(0,5,"till ")==0) {
        std::string time;
        const auto status=message_lookup_value("time",value.substr(5).c_str(),time);
        return status==Status::ok ? pattern("time","till %s",{time},translated):status;
    }
    return message_lookup_value("time",source,translated);
}
Status pattern(const char* domain,const char* original,
               std::initializer_list<std::string> values,std::string& translated) {
    auto status=message_lookup_value(domain,original,translated);
    if(status!=Status::ok) return status;
    std::size_t at=0;
    for(const auto& value:values) {
        at=translated.find("%s",at);
        translated.replace(at,2,value);
        at+=value.size();
    }
    return Status::ok;
}
Status npc_value(const Pending& call,std::string& translated) {
    const auto index=static_cast<std::int32_t>(call.ecx);
    const auto flags=call.edx;
    if(index==-1) return message_lookup_value("npc","human",translated);
    const auto* creature=at<unsigned char>(0x5d51400+static_cast<u32>(index)*0x568);
    const auto category=creature[0];
    const auto species=*reinterpret_cast<const u32*>(creature+0xbc);
    const auto gender=creature[0xcf];
    const auto known=creature[0x1dc];
    const auto* description=reinterpret_cast<const char*>(creature+8);
    const auto* proper_name=reinterpret_cast<const char*>(creature+0x30);
    if(flags&1) return message_lookup_value("npc",category==1 ? "human":description,translated);
    auto status=message_lookup_value("npc",description,translated);
    if(status!=Status::ok) return status;
    if(category!=1) {
        if(gender&2) {
            const char* young=species==0x25e || species==0x26b || species==0x26c || species==0x294
                ? "calf" : species==0x265 || species==0x266 || species==0x267 ? "piglet"
                : species==0x268 ? "lamb" : species==0x26a ? "puppy" : "cub";
            std::string young_name;
            status=message_lookup_value("npc",young,young_name);
            if(status!=Status::ok) return status;
            if(species==0x265 || species==0x266 || species==0x267 || species==0x268)
                translated=young_name;
            else translated+=young_name;
        } else if(gender&1) {
            if(species==0x294) status=pattern("npc","bull %s",{translated},translated);
            else if(species==0x268) status=message_lookup_value("npc","ram",translated);
            else if(species==0x267) status=message_lookup_value("npc","boar",translated);
            else if(species==0x26b || species==0x26c) {
                std::string suffix;status=message_lookup_value("npc"," stag",suffix);translated+=suffix;
            }
        } else {
            if(species==0x25d) status=pattern("npc","female %s",{translated},translated);
            else if(species==0x267) status=message_lookup_value("npc","sow",translated);
            else if(species==0x26a) status=message_lookup_value("npc","female dog",translated);
            else if(species==0x26b || species==0x26c) {
                std::string suffix;status=message_lookup_value("npc"," doe",suffix);translated+=suffix;
            }
        }
        if(status!=Status::ok) return status;
    }
    if(flags&8) {
        std::string name;status=message_identity_value(proper_name,name);
        return status==Status::ok ? pattern("npc","%s the %s",{name,translated},translated):status;
    }
    bool definite=true;
    const std::string description_zh=translated;
    if((known&1) || (category==1 && *at<u32>(0xa2d28a0)!=0)) {
        status=message_identity_value(proper_name,translated);
        if(status!=Status::ok) return status;
        if(flags&4) status=pattern("npc","%s the %s",{translated,description_zh},translated);
        if(flags&2) status=message_identity_value(proper_name,translated);
        definite=false;
    }
    if(known&2) {
        status=message_identity_value(proper_name,translated);
        if(status!=Status::ok) return status;
        if(flags&2) definite=false;
        if(flags&4) {
            status=pattern("npc","%s called %s",{description_zh,translated},translated);
            definite=true;
        }
    }
    if(status==Status::ok && (flags&2) && definite)
        status=pattern("article","the %s",{translated},translated);
    return status;
}
Status translate_tag(const char* tag,const char* value,std::string& output) {
    const std::string name=tag;
    const auto has=[&](const char* part){return name.find(part)!=std::string::npos;};
    // These values select native branches or represent numbers; their exact
    // English spelling is business data consumed by 560CB0/561B00.
    if(name=="npc" || name=="who" || name=="attacker" || name=="defender" ||
       name=="num" || name=="prepdays" || name=="weapon_slot" || name=="wc_bonus" ||
       name=="attack_class" || name=="defense_class") {output=value;return Status::ok;}
    if(name=="plr_name" || name=="identity") return message_identity_value(value,output);
    if(has("direction")) return resolve("direction",value,output);
    if(has("_sound") || has("_aggsound")) return resolve("sound",value,output);
    if(name=="plr_gender") return resolve("npc",value,output);
    if(has("reptitle") || name=="plr_identity" || name=="plr_bad_name") return resolve("identity",value,output);
    if(has("item") || name=="attack_weapon" || name=="attack_bow" || name=="defend_weapon")
        return resolve("item",value,output);
    if(has("bodypart")) return resolve("bodypart",value,output);
    if(has("aspect")) return resolve("aspect",value,output);
    if(name=="status") return resolve("status",value,output);
    if(has("npc") || has("attacker") || has("defender") || has("who")) {
        if(std::strcmp(value,"you")==0) return message_lookup_value("npc",value,output);
        return resolve("npc",value,output);
    }
    if(name=="%s" || name=="bound" || name=="var") return resolve("bound",value,output);
    return resolve(tag,value,output);
}
#include "windows_message_value_builders.inc"
void append_hooks(std::vector<HookSpec>& hooks) {
    for(u32 i=0;i<sizeof(sites)/sizeof(sites[0]);++i)
        hooks.push_back(native_name_input::native_call(first_hook+i,sites[i].site,sites[i].target,0));
    append_builder_hooks(hooks);
}
Status dispatch(const NativeEvent& event,DispatchResult&,bool& handled) {
    auto builder_status=dispatch_builder(event,handled);
    if(handled) return builder_status;
    handled=event.id>=first_hook && event.id<first_hook+sizeof(sites)/sizeof(sites[0]);
    if(!handled) return Status::ok;
    const auto kind=sites[event.id-first_hook].kind;
    if(event.phase==NativePhase::before) {
        Pending call{kind,event.frame->ecx,event.frame->edx,Status::ok,{},{}};
        if(kind==Kind::plural || kind==Kind::singular || kind==Kind::indefinite ||
           kind==Kind::definite || kind==Kind::lowercase) {
            const auto& site=sites[event.id-first_hook];
            windows_message_items::prepare_input(site.site,site.target,ptr<char>(call.ecx));
            call.input=ptr<char>(call.ecx);
            const auto slash=call.input.find('/');
            if((kind==Kind::plural || kind==Kind::singular) && slash!=std::string::npos)
                call.status=message_lookup_value("grammar",call.input.c_str(),call.translated);
            else call.status=name_value(ptr<char>(call.ecx),call.translated);
        }
        if(kind==Kind::encounter)
            call.status=resolve("npc",ptr<char>(call.edx),call.translated);
        pending.push_back(std::move(call));
        return Status::ok;
    }
    auto& call=pending.back();
    // These two native functions explicitly return nullptr for an out-of-range
    // activity index; that branch does not produce a display value.
    if((kind==Kind::work || kind==Kind::construction) && event.frame->eax==0) {
        pending.pop_back();return Status::ok;
    }
    const auto* original=ptr<char>(kind==Kind::corpse_damage || kind==Kind::corpse_age ||
        kind==Kind::corpse_injury ? call.edx:event.frame->eax);
    const char* domain="bound";
    auto status=call.status;
    switch(kind) {
    case Kind::quality:domain="item.quality";status=message_lookup_value(domain,original,call.translated);break;
    case Kind::tree:domain="tree";status=message_lookup_value(domain,original,call.translated);break;
    case Kind::direction:domain="direction";status=message_lookup_value(domain,original,call.translated);break;
    case Kind::npc:domain="npc";status=npc_value(call,call.translated);break;
    case Kind::identity:domain="identity";status=identity_value(call,original,call.translated);break;
    case Kind::bodypart:domain="bodypart";status=message_translate_bound(at<char>(0xa224eb0),call.translated);break;
    case Kind::time:domain="time";status=time_value(original,call.translated);break;
    case Kind::quantity:domain="unit";status=quantity_value(original,call.translated);break;
    case Kind::injury:domain="injury";status=injury_value(call,original,call.translated);break;
    case Kind::hunger:case Kind::thirst:domain="status";status=message_lookup_value(domain,original,call.translated);break;
    case Kind::trap:domain="trap";status=resolve(domain,original,call.translated);break;
    case Kind::work:domain="work";status=message_lookup_value(domain,original,call.translated);break;
    case Kind::activity:domain="activity";status=message_lookup_value(domain,original,call.translated);break;
    case Kind::activity_copy:domain="activity";status=resolve("bound",original,call.translated);break;
    case Kind::work_item:domain="item";status=resolve(domain,original,call.translated);break;
    case Kind::silhouette:domain="npc";status=resolve(domain,original,call.translated);break;
    case Kind::burntime:domain="time";status=time_value(original,call.translated);break;
    case Kind::temperature:domain="temperature";status=message_lookup_value(domain,original,call.translated);break;
    case Kind::spell:domain="spell";status=message_lookup_value(domain,original,call.translated);break;
    case Kind::corpse_size:domain="corpse";status=resolve(domain,original,call.translated);break;
    case Kind::corpse_damage:case Kind::corpse_injury:
        domain="corpse";
        if(*original) status=resource_value(call.input.c_str(),original,call.translated);
        else {call.translated.clear();status=Status::ok;}
        break;
    case Kind::corpse_age:
        domain="corpse";status=message_lookup_value(domain,original,call.translated);break;
    case Kind::construction:domain="work";status=resolve(domain,original,call.translated);break;
    case Kind::profile:domain="npc";status=resolve(domain,original,call.translated);break;
    case Kind::encounter:break;
    case Kind::plural:case Kind::singular:case Kind::lowercase:break;
    case Kind::indefinite:case Kind::definite:break;
    }
    const auto translated=call.translated;
    pending.pop_back();
    const auto& site=sites[event.id-first_hook];
    if(status==Status::ok) {
        message_bind_value(original,translated);
        observe_value(site.site,site.target,original,translated);
        windows_message_items::observe_value(site.site,site.target,original,translated);
    } else windows_message_items::observe_status(site.site,site.target,status);
    return status;
}
void save(std::vector<unsigned char>& output) {
    const auto write_values=[&](const std::vector<Value>& values) {
        message_state_write(output,static_cast<u32>(values.size()));
        for(const auto& value:values) {
            message_state_write(output,value.site);message_state_write(output,value.producer);
            message_state_write(output,value.owner);message_state_string(output,value.domain);
            message_state_string(output,value.source);message_state_string(output,value.translated);
        }
    };
    message_state_write(output,static_cast<u32>(pending.size()));
    for(const auto& call:pending) {
        message_state_write(output,call.kind);message_state_write(output,call.ecx);
        message_state_write(output,call.edx);message_state_write(output,call.status);
        message_state_string(output,call.input);message_state_string(output,call.translated);
        write_values(call.children);
    }
    message_state_write(output,static_cast<u32>(tags.size()));
    for(const auto& tag:tags) write_values(tag);
    save_builders(output);
}
void restore(const unsigned char*& input) {
    const auto read_values=[&](std::vector<Value>& values) {
        u32 count;message_state_read(input,count);
        for(u32 i=0;i<count;++i) {
            Value value;message_state_read(input,value.site);message_state_read(input,value.producer);
            message_state_read(input,value.owner);message_state_string(input,value.domain);
            message_state_string(input,value.source);message_state_string(input,value.translated);
            values.push_back(std::move(value));
        }
    };
    u32 count;
    message_state_read(input,count);pending.clear();
    for(u32 i=0;i<count;++i) {
        Pending call;message_state_read(input,call.kind);message_state_read(input,call.ecx);
        message_state_read(input,call.edx);message_state_read(input,call.status);
        message_state_string(input,call.input);message_state_string(input,call.translated);
        read_values(call.children);
        pending.push_back(std::move(call));
    }
    message_state_read(input,count);tags.clear();tags.resize(count);
    for(auto& tag:tags) read_values(tag);
    restore_builders(input);
}
}
