# Windows 3.89.1 外置资源及原文地址静态对照

日期：2026-11-10。对象为本机 Steam Build `26139145` 的《不真实的世界》3.89.1 Windows x86。本文只读 PE、资源、旧反编译 TSV 与源码，不执行游戏、交付产物或测试；未编写测试用例、脚本或断言。

当前 `urw.exe` SHA-256：`c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。PE 首选基址为 `0x400000`；下表 VA 均为该首选基址下的虚拟地址，不是文件偏移。

## 外置资源

`GAME.NFO` SHA-256 仍为 `071f384ad992d0a688833693f207a5cf8a969b4811e5e6603597d189087a4d5d`，与 `catalog/zh-CN/cultures.tsv:2` 及旧 profile 相同。文件字节、原生读取后的记录偏移和全部百科词库键可复用。

`translations/messages/inventory.json` 记录的八个原文件与当前安装文件摘要逐项一致；因此 987 条外置资源显示记录及 KEY/source 翻译资料无需重译。

| 文件 | 当前 SHA-256（与旧记录相同） |
| --- | --- |
| `urw_chat.txt` | `929bb1d2ac761ccb23424f434cf5e8ed0fc8ab21b301d6c0d1244c63be561284` |
| `urw_combat.txt` | `9a420ad13ef6abfa1a1139fefdc0a0d7c7360ec3430a18fbf59387013b3636d7` |
| `urw_defs.txt` | `5a9b9572b5a537021e044334fe1f839ef23c1a64a262b79350f9bdb04e15efe9` |
| `urw_msg.txt` | `eff9d6af418210bffa6aeef3e93ec95bcd6d95f171a6ea64e48c4ac727eab7cc` |
| `urw_pronouns.txt` | `7c4093e84fa70bc376c00465cdb41ac3d286e26fb0ea2626a4325068f483289e` |
| `urw_sounds.txt` | `1124d2654fd168a32214d88666a55ec1878d87cc289a678412cd63a92c9de4bb` |
| `urw_tags.txt` | `61c6eb11c86b39e094a7dd3e94c1c5e65acce8df9040620e6dddfd7ac0420abf` |
| `urw_uname_flora.txt` | `32702ea7c6d0400aea03f7ea4525f2f9a02175eb5e1abe8919f17b942fd1b967` |

## PE 地址的消费方式

`modules/adapter/windows_message_formats.inc:1073` 使用原生 `event.arguments[1]` 与 `image_base + candidate.format` 比较以选择当前调用的真实分支；该 `format` RVA 必须映射到新版地址。`construct` 的 `entry.key` 以及 `Kind::literal` 的 `parameter.tag` 是词库语义标识；`modules/semantic/message_text.cpp` 对以 `format.` 开头的名字直接查 `message.<旧 key>`，因此这些 key 保留原值，不能随新地址改名。

`windows_message_helpers.inc` 的 cause_pair 另有显式 `0x1AF124` 地址比较，必须消费新 `0x1AF134`。`at<T>(字面值)`、`at(part.literal)`、`at(literals[i])`、`at(form.first/second)`、`at(punctuation.source)`、`at(unit_appends[].literal)`、`at(source.literal)` 和 `at(candidate.format)` 的地址来源均纳入下面显式表来源集合：枚举 adapter 的 C++、头文件和 inc 中全部落在旧 `.rdata` 范围内的十六进制 RVA，再逐项比对原文字节或原生指令操作数。此集合也包含固定指令期望操作数所用的数据地址。

静态来源集合共有 **692** 个不同的旧 `.rdata` RVA；其中 **393** 个被明确证实移到旧址 `+0x10`，已写入 `modules/adapter/windows_3891_rdata.inc` 的排序 `shifted_rvas`。余下 **299** 项由 **245** 项旧 TSV 原文同址、**25** 项既有消费者操作数保持原地址和 **29** 项 IAT 槽组成；它们不进入移位表。25 项详列下文，IAT 槽由原生组件静态审查对照导入身份与既有指令操作数。该表不实现整节迁移，也不把 `.data` 地址作为 `.rdata` 处理。

旧源原文锚点由 `docs/evidence/*.tsv` 中明确成对的 `string_va/source`、`string_va/text`、`format_va/format`、`literal_va/literal` 列恢复。无引号的 TSV 逐物理行处理，避免原文开头的引号被误当 CSV 多行字段；带引号的 TSV 按其原有字段语法读取。

在全部旧原文锚点中，最后一项确认同址的邻近锚点是旧 VA `0x005A40B4` 的 `[MATERIAL:wool]`；最早确认移位的锚点是旧 VA `0x005A40E8` 的 `[TILEGFX:it-rawwool]`，新版为 `0x005A40F8`。新 PE 的 `0x005A40C4` 为 `[TYPE:textile]`，`0x005A40D4` 为 `[TILEGFX:it-fabric]`。这些邻近锚点不足以证明整个 `.rdata` 区间的统一规则，因此代码只采用显式地址集合。

`windows_message_format_builders.inc:224` 的 `at<char>(0x193D4C+3)` 还消费旧 VA `0x00593D4F` 子串：旧 `settlement-static-catalog.tsv` 与 `settlement-formats-classification.tsv` 保存的完整模式为 `%s beverage`，新 PE 在相同 VA `0x00593D4C` 的字节仍为 `%s beverage`，因此 `+3` 后相同位置仍为 `beverage`；该地址不移位、不进入 `shifted_rvas`。

29 个 IAT 槽已由 [原生组件静态对照](20261110-windows-3891-native-contracts.md) 最后一节完整列明：新版导入名称与旧代码用途逐项一致，14 处实际读取这些槽的 CALL/MOV 原生指令完整六字节在同址一致。这些槽没有推定或待确认的迁移项。

## 保持原地址的二十五项消费者

下列地址没有旧 TSV 的 VA/完整原文配对；证据来自修改前既有源码中同一语义消费者保存的指针/期望操作数，以及新版同一原生调用或复制指令仍使用该地址。它们保持同址的依据是原生操作数，而不是处于某个地址范围。表中原文是新版 PE 的字节读取结果，未冒称持有旧 PE 的字节副本。

| 旧与新 RVA | 新 PE 指令 VA | 当前原文 |
| --- | --- | --- |
| `0x18FA68` | `0x410D56`, `0x411121`, `0x41112B` | `gamecourse` |
| `0x18FFB0` | `0x41107B` | `You have completed both game courses. Now proceed with free gameplay in the UnReal World.` |
| `0x190328` | `0x411A2E` | `Too short character name.` |
| `0x190344` | `0x411ADB` | `Character name can't contain spaces or special characters.` |
| `0x190380` | `0x411C7A` | `File folder for a character with that name already exists!` |
| `0x195A1C` | `0x4A8F9C`, `0x500FEA`, `0x50103C` | `  ` |
| `0x198528` | `0x44B73B` | ` lb` |
| `0x19852C` | `0x44B75A` | ` lbs` |
| `0x198534` | `0x44B77F` | ` oz` |
| `0x198538` | `0x44B7BA` | ` kg` |
| `0x19853C` | `0x44B7DA` | ` g` |
| `0x19CF94` | `0x48A474` | `last` |
| `0x19D368` | `0x48E68A`, `0x490111` | ` at ` |
| `0x19D7B8` | `0x494D7C` | ` (` |
| `0x19D7BC` | `0x494F22` | ` with ` |
| `0x19D7E4` | `0x4950CF` | `Crag` |
| `0x19D7EC` | `0x4950EE` | `Base rock` |
| `0x19D7F8` | `0x4950AA` | `Marshland` |
| `0x19DB78` | `0x49BC2E` | `less than a kilometer` |
| `0x19DBA4` | `0x49BC85` | `just a couple of kilometers` |
| `0x19DBD0` | `0x49BCF2` | `less than a mile` |
| `0x19DBF0` | `0x49BD3B` | `just a couple of miles` |
| `0x19DD28` | `0x49C07A` | ` away` |
| `0x19DD88` | `0x49C1FA` | `just around the corner ` |
| `0x19DDA0` | `0x49C26F`, `0x539ABA` | `just nearby ` |

对应旧源码：`windows_creation.inc` 的 gamecourse/head/completed 消费者、`module.cpp` 的三种 `profile_name_error` 原文、`windows_message_value_builders.inc` 的 `unit_appends` 表、`windows_message_calendar.inc` 的 `last_word/at_text` 原始操作数，以及 `windows_message_geography.inc` 的 `absolute` 原始操作数表。其引用的同址新指令仍分别负责同一目录名、帮助文本、错误文本、单位、日期和地理短语。

### 445 个移位词库 key 与 393 个地址映射项的数量关系

445 个移位 `message.format.<旧VA>` key 中，376 个旧 RVA 在 adapter 中作为实际地址常量使用；另 69 个只作为词库语义 key 使用、或直接从原生事件接收新格式串指针，不能因为 key 内有旧地址字样就再映射其名字。显式表中的 393 项 = 376 个实际格式 RVA + 17 个其他实际文字、资源名或非字符串常量 RVA。因此该数量差不是遗漏69项地址映射。

词库保留旧 key，原生事件已经携带的新指针不重复映射；只有从旧数据常量重建地址的消费点调用 `rdata_rva`。

## 缺少旧 TSV 原文的消费者证据

以下八项由既有消费者的旧 RVA 与同一原生指令的新操作数对应，不以全局同名字符串搜索决定地址：

| 旧 RVA | 新 RVA | 新 PE 引用指令 VA | 新字符串 |
| --- | --- | --- | --- |
| `0x1A9D88` | `0x1A9D98` | `0x004F5B82` | `pausescr` |
| `0x1A9D94` | `0x1A9DA4` | `0x004F5B9D` | `       Press [SPACE] to continue    ` |
| `0x1AA14C` | `0x1AA15C` | `0x004F9191` | `Command: ` |
| `0x1AF124` | `0x1AF134` | `0x00523942` | `due to %s and %s` |
| `0x1D8288` | `0x1D8298` | `0x0056311A` | `and more` |
| `0x1DCF60` | `0x1DCF70` | `0x00587E22` | `During the day the temperature will be ` |
| `0x1DCF88` | `0x1DCF98` | `0x00587E77` | `During the night the temperature will be ` |
| `0x1DCFB4` | `0x1DCFC4` | `0x00587ECA` | ` Tomorrow the temperature will be ` |

另五项 `0x1AA240`、`0x1AA314`、`0x1ACAB8`、`0x1ACAD0`、`0x1DDAB0` 由并行原生组件静态审查确认移位；它们包括字符串内部片段、资源名和非字符串常量，不能按普通 C 字符串解释。详见原生组件审查记录。

技能 helper 的十个格式串和宝藏构造的四个格式串虽没有旧 TSV 原文，却由既有 hook 的语义 ID、旧词库 key、对应新 PE 的 `push` 操作数与格式参数位置共同对应；下表逐项保留该指令 VA。其余五个持久任务标题在既有 `windows_message_quest_records.inc` 中保存了完整英文模式，与新址字节一致。

## 全部格式 key 原文映射

`catalog/zh-CN/messages.tsv` 共 **744** 个 `message.format.<VA>` key：**299** 项旧原文同址、**426** 项旧 TSV 原文在新址 `+0x10` 完全相同、**5** 项由既有源码完整模式确认 `+0x10`、**14** 项由原生 hook 操作数确认 `+0x10`。本范围没有出现其他 delta，也没有未列出的 key。

已记录原文的 725 项在“同址或 +0x10”候选中均唯一；没有用全局字符串首次命中决定迁移地址。短字符串、标点和通用格式在 PE 中可能重复，地址仍受对应消费者和原生调用操作数约束。

| 旧 key 中的 VA | 新 PE 原文 VA | 静态依据 | 新 PE 原文（保留空白） |
| --- | --- | --- | --- |
| `0058c670` | `0058c670` | 旧原文同址 | `%s` |
| `0058c680` | `0058c680` | 旧原文同址 | `%s %s` |
| `0058ca90` | `0058ca90` | 旧原文同址 | `!That's not possible because the ground is %s!` |
| `0058cc10` | `0058cc10` | 旧原文同址 | `!The %s is full already!` |
| `0058cc74` | `0058cc74` | 旧原文同址 | `=Ok. Some %s has been ground into the %s.` |
| `0058cf80` | `0058cf80` | 旧原文同址 | `monesko vuoden päivä nyt: %d - kasvin istutuspäivä: %d` |
| `0058d2e8` | `0058d2e8` | 旧原文同址 | `Ansan asetuksen laatu: %d` |
| `0058d308` | `0058d308` | 旧原文同址 | `:@The %s is now set and readied. Don't forget to check it after a day or two.` |
| `0058d458` | `0058d458` | 旧原文同址 | `+You trigger and release the %s.` |
| `0058d494` | `0058d494` | 旧原文同址 | ` now.` |
| `0058d49c` | `0058d49c` | 旧原文同址 | `Ok, you have disassembled the ` |
| `0058d4c8` | `0058d4c8` | 旧原文同址 | `Walked into %s` |
| `0058d4d8` | `0058d4d8` | 旧原文同址 | `&Your %s gets hurt!` |
| `0058d4ec` | `0058d4ec` | 旧原文同址 | `the %s` |
| `0058e290` | `0058e290` | 旧原文同址 | `#%d %s` |
| `0058f77c` | `0058f77c` | 旧原文同址 | `!Bug! Couldn't resolve %s-skill. Report!` |
| `005903bc` | `005903bc` | 旧原文同址 | `%d` |
| `005909f0` | `005909f0` | 旧原文同址 | `kult: %d ani: %s` |
| `00591368` | `00591368` | 旧原文同址 | `aseta_heitetty_esine %d,%d - %d` |
| `005918a0` | `005918a0` | 旧原文同址 | `Hae_Pakopaikka: %d u: %d,%d (plrx,y %d,%d)` |
| `005918cc` | `005918cc` | 旧原文同址 | `NPC #%d uusi pakopaikka=%d,%d` |
| `0059190c` | `0059190c` | 旧原文同址 | `Pakene (%d)` |
| `005919ac` | `005919ac` | 旧原文同址 | `Saalistus kohti %d,%d (%s)` |
| `005919f4` | `005919f4` | 旧原文同址 | `Metsästys kohti %d,%d (%s)` |
| `00591a2c` | `00591a2c` | 旧原文同址 | `#%d Menepaikkaan: %d,%d` |
| `00591a44` | `00591a44` | 旧原文同址 | `Menepaikkaan: %d,%d reached - cancel now` |
| `00591a70` | `00591a70` | 旧原文同址 | `Poistu paikkaan: %d,%d` |
| `00591a88` | `00591a88` | 旧原文同址 | `headhome -> %d,%d (cr %d)` |
| `00591aa4` | `00591aa4` | 旧原文同址 | `puuha %d timeout` |
| `00591ab8` | `00591ab8` | 旧原文同址 | `#%d puuha on 0` |
| `00591af8` | `00591af8` | 旧原文同址 | `Riistaelain check %s ` |
| `00591b34` | `00591b34` | 旧原文同址 | `Haaskasta(%d) -> %s - scary food %s - reject` |
| `00591b8c` | `00591b8c` | 旧原文同址 | `ravinnonhankinta(%s #%d)` |
| `00591bb8` | `00591bb8` | 旧原文同址 | `%s energia %d/%d - ei ravintotarvetta` |
| `00591bf0` | `00591bf0` | 旧原文同址 | `%s -> eat plant: %d,%d (%s)` |
| `00591c0c` | `00591c0c` | 旧原文同址 | `#%d haaska/saalis haku` |
| `00591e80` | `00591e80` | 旧原文同址 | `after theft: %d` |
| `00592138` | `00592138` | 旧原文同址 | `socpopul before %d` |
| `0059214c` | `0059214c` | 旧原文同址 | `socpopul after %d` |
| `00592180` | `00592180` | 旧原文同址 | `!@You encounter an animal. You think it's %s...` |
| `005921b0` | `005921b0` | 旧原文同址 | `!@You encounter %s...` |
| `00592280` | `00592280` | 旧原文同址 | `#%s can not reach you and will be left behind.` |
| `00592320` | `00592320` | 旧原文同址 | `creature_swap() PlayerX,Y: %d,%d` |
| `00592344` | `00592344` | 旧原文同址 | `T: %d D: %d` |
| `005923fc` | `005923fc` | 旧原文同址 | `Transporting %s.` |
| `00592468` | `00592468` | 旧原文同址 | `You shake the needles from your shoulders and come forward among the people. You are entering %s village...` |
| `005924d8` | `005924d8` | 旧原文同址 | `You shake the needles from your shoulders and come forward among the people. You are entering %s settlement...` |
| `005927f4` | `005927f4` | 旧原文同址 | `There is %s here and ` |
| `005928a0` | `005928a0` | 旧原文同址 | `a njerpez camp` |
| `005928b0` | `005928b0` | 旧原文同址 | `a cave` |
| `005928b8` | `005928b8` | 旧原文同址 | `settled area` |
| `00592a70` | `00592a70` | 旧原文同址 | `Veden syvyys 0-2 arvona: %d` |
| `00592c28` | `00592c28` | 旧原文同址 | `=This might be a good location considering the ongoing %s spawning period.` |
| `00592c80` | `00592c80` | 旧原文同址 | `_The %s are spawning at this time of the year, but not quite at this location.` |
| `00592cd0` | `00592cd0` | 旧原文同址 | `_The %s is spawning at this time of the year, but not quite at this location.` |
| `00592d20` | `00592d20` | 旧原文同址 | `fishing` |
| `00592ff0` | `00592ff0` | 旧原文同址 | `+You use the whole %s as a bait, hoping for bigger fish to get attracted in it.` |
| `00593040` | `00593040` | 旧原文同址 | `+You use pieces of %s as a bait.` |
| `005931e8` | `005931e8` | 旧原文同址 | `Kutupaikkaa (%s) loytyy: %d,%d` |
| `00593208` | `00593208` | 旧原文同址 | `Kutemista kohdassa: %d,%d` |
| `00593224` | `00593224` | 旧原文同址 | `Kuteva kala: %s` |
| `005933a8` | `005933a8` | 旧原文同址 | `Yrttivaikutus #%d - %s` |
| `005935f4` | `005935f4` | 旧原文同址 | `lisaa yhteisravinto: %s maara: %d paino: %.2f` |
| `00593624` | `00593624` | 旧原文同址 | `lisattavan hinta: %.2f (%.2f/lbs)` |
| `0059365c` | `0059365c` | 旧原文同址 | `Yhteisravintoesinelisäys: %s ravintoesineWT: %.2f -> %.2f` |
| `00593698` | `00593698` | 旧原文同址 | `lisattavan hinta: %.2f (%.2f/lbs) yhteishnyt: %.2f (%.2f/lbs)` |
| `005936d8` | `005936d8` | 旧原文同址 | `yhteisravintoesine %d,%d,%d neste: %d paino: %.2f` |
| `00593720` | `00593720` | 旧原文同址 | `Itemruoan_Tarve: ruoka = %d kcal/lbs -> massun vetoisuus %d Tarve: %.2f` |
| `005937b8` | `005937b8` | 旧原文同址 | `Energiavaranto: %d` |
| `005937cc` | `005937cc` | 旧原文同址 | `Vatsa: %d` |
| `005938f4` | `005938f4` | 旧原文同址 | `!That %s is unknown to you.` |
| `00593910` | `00593910` | 旧原文同址 | `!You know the %s is poisonous.` |
| `00593bac` | `00593bac` | 旧原文同址 | `!The %s is empty!` |
| `00593c10` | `00593c10` | 旧原文同址 | `drink` |
| `00593c34` | `00593c34` | 旧原文同址 | `Sailioi; kohde (%s) jo valmiiksi sailiossa #%d` |
| `00593c64` | `00593c64` | 旧原文同址 | `Sailioi: säiliöidään esineeseen %s (ESINE:%u)` |
| `00593c94` | `00593c94` | 旧原文同址 | `sailio max_wt: %.2f` |
| `00593ccc` | `00593ccc` | 旧原文同址 | `%s ` |
| `00593cf0` | `00593cf0` | 旧原文同址 | `Yhteisravintoesine H.P.R,N: %d %d %d %d Paino: %.2f` |
| `00593d24` | `00593d24` | 旧原文同址 | `Yhteisravintoesine perlbs price: %.2f` |
| `00593d4c` | `00593d4c` | 旧原文同址 | `%s beverage` |
| `00593d60` | `00593d60` | 旧原文同址 | `ember-roasted %s` |
| `00593d74` | `00593d74` | 旧原文同址 | `boiled %s` |
| `00593d80` | `00593d80` | 旧原文同址 | `roasted %s` |
| `00593d8c` | `00593d8c` | 旧原文同址 | `dried %s` |
| `00593d98` | `00593d98` | 旧原文同址 | `salted %s` |
| `00593da4` | `00593da4` | 旧原文同址 | `smoked %s` |
| `00593e34` | `00593e34` | 旧原文同址 | `%s - %d PORTIONS` |
| `00594394` | `00594394` | 旧原文同址 | `%s isantakasvi: %s` |
| `00594510` | `00594510` | 旧原文同址 | `HERBML %d+%d = %d kasviML %d` |
| `005955e8` | `005955e8` | 旧原文同址 | `!%s is completely full!` |
| `00595600` | `00595600` | 旧原文同址 | `poista lahdesailio %s [slot %d]` |
| `00595620` | `00595620` | 旧原文同址 | `Kaada_Astiaan() materiaali: %s paino %.2f` |
| `0059564c` | `0059564c` | 旧原文同址 | `=You've got a full %s now.` |
| `005958ac` | `005958ac` | 旧原文同址 | `%s of %s` |
| `00595a98` | `00595a98` | 旧原文同址 | `soc member %s sees pickup` |
| `00595ab4` | `00595ab4` | 旧原文同址 | `debtitem got og.coordinates %d,%d` |
| `00595bd8` | `00595bd8` | 旧原文同址 | `%s.Done - proceed with selected.` |
| `00595c30` | `00595c30` | 旧原文同址 | `...or select %d more entries.` |
| `00595cb0` | `00595cb0` | 旧原文同址 | `%s.Move` |
| `00595cf8` | `00595cf8` | 旧原文同址 | `Viewing: %s` |
| `00595d10` | `00595d10` | 旧原文同址 | `%c.All types` |
| `00595da8` | `00595da8` | 旧原文同址 | `move data#%d %s -> %d,%d` |
| `00595ddc` | `00595ddc` | 旧原文同址 | `setdatamove #%d: data:%d ref:%d` |
| `00595e48` | `00595e48` | 旧原文同址 | `haul items` |
| `00595f4c` | `00595f4c` | 旧原文同址 | `datamove #%d: datA:%d ref:%d` |
| `00596008` | `00596008` | 旧原文同址 | `!This %s has no teeth to remove.` |
| `00596064` | `00596064` | 旧原文同址 | `=You got %s.` |
| `005962c0` | `005962c0` | 旧原文同址 | `att ca:%d block ca:%d` |
| `005962d8` | `005962d8` | 旧原文同址 | `aQ: %d bQ: %d` |
| `005962e8` | `005962e8` | 旧原文同址 | `wp %s strikes with ca %d vlc: %.2f` |
| `0059630c` | `0059630c` | 旧原文同址 | `KE: %d` |
| `00596314` | `00596314` | 旧原文同址 | `KE after velocity (%.2f): %d` |
| `00596334` | `00596334` | 旧原文同址 | `KE = %d FPA = %d` |
| `00596348` | `00596348` | 旧原文同址 | `KE = %d FPA ont target = %d` |
| `00596364` | `00596364` | 旧原文同址 | `TRUEFPA:%d -- HITFPA:%d BLOCKFPA:%d` |
| `00596388` | `00596388` | 旧原文同址 | `!%s can damage!` |
| `00596398` | `00596398` | 旧原文同址 | `[AD:%.0f]` |
| `005963a4` | `005963a4` | 旧原文同址 | `%d times exceed, %.2f contact pct` |
| `005963c8` | `005963c8` | 旧原文同址 | `[BD:%.0f]` |
| `005963d4` | `005963d4` | 旧原文同址 | `c_area(%d) vs. item_area(%d) = %.2f%% destroyed` |
| `00596404` | `00596404` | 旧原文同址 | `!The string of your %s breaks!` |
| `00596424` | `00596424` | 旧原文同址 | `_You use the lit %s to %s.` |
| `00596440` | `00596440` | 旧原文同址 | `_You use the lit %s nearby to %s.` |
| `005964ac` | `005964ac` | 旧原文同址 | `Tekodata for %s - do %s` |
| `0059650c` | `0059650c` | 旧原文同址 | `TKRAJA: %d (%d) MATRAJA: %d (%d) Laatu:%d->%d` |
| `0059653c` | `0059653c` | 旧原文同址 | `MULTIGAP: %d OGLAATU: %d ALENNUS: %d` |
| `00596564` | `00596564` | 旧原文同址 | `%d %s` |
| `0059656c` | `0059656c` | 旧原文同址 | `QLIST #%d = %u` |
| `005965d0` | `005965d0` | 旧原文同址 | `QLIST #%d = %d` |
| `005966f0` | `005966f0` | 旧原文同址 | `_This process should be complete %s.` |
| `00596818` | `00596818` | 旧原文同址 | `?You can make %u %s from one %s.` |
| `00596aa8` | `00596aa8` | 旧原文同址 | `REPAIR WORN-OUT %s` |
| `00596ac8` | `00596ac8` | 旧原文同址 | `#%d MCinprocess %d,%d` |
| `00596ae0` | `00596ae0` | 旧原文同址 | `spent: %d needed: %d` |
| `00596af8` | `00596af8` | 旧原文同址 | `after add spent: %d needed: %d` |
| `00596b48` | `00596b48` | 旧原文同址 | `+There's really no need to repair this %s yet.` |
| `00596b78` | `00596b78` | 旧原文同址 | `!Unfortunately this %s has been worn out beyond repair.` |
| `00596c5c` | `00596c5c` | 旧原文同址 | `!The %s doesn't have a separate head and haft to remove!` |
| `00596cf4` | `00596cf4` | 旧原文同址 | `+You have removed the %s haft from its head.` |
| `00596d24` | `00596d24` | 旧原文同址 | `=You obtained %s and %s.` |
| `00596efc` | `00596efc` | 旧原文同址 | `+You finish repairing your %s.` |
| `00597004` | `00597004` | 旧原文同址 | `spent: %d left: %d` |
| `00597088` | `00597088` | 旧原文同址 | `You successfully deconstructed the %s.` |
| `005971ec` | `005971ec` | 旧原文同址 | `!%s %s is too short to be shortened anymore.` |
| `0059721c` | `0059721c` | 旧原文同址 | `!One ft %s is too short to be shortened anymore.` |
| `00597250` | `00597250` | 旧原文同址 | `?How much of this %s %s you want to cut?` |
| `005972b4` | `005972b4` | 旧原文同址 | `=You cut %s piece from the %s.` |
| `00597348` | `00597348` | 旧原文同址 | `+You are about to join %s %s to another piece of tying equipment.` |
| `0059738c` | `0059738c` | 旧原文同址 | `?Now select another %s to join them together.` |
| `005974d0` | `005974d0` | 旧原文同址 | `=After tying the two %s together you now got %s %s.` |
| `0059789c` | `0059789c` | 旧原文同址 | `+%s` |
| `005988b4` | `005988b4` | 旧原文同址 | `+The %s drops on the ground.` |
| `00598bdc` | `00598bdc` | 旧原文同址 | `#QT dec at WT %.2f = %.2f%%` |
| `00598bf8` | `00598bf8` | 旧原文同址 | `+Your worn out %s breaks apart.` |
| `00598c40` | `00598c40` | 旧原文同址 | `Sailio palautuu, ESINE %u` |
| `00598c70` | `00598c70` | 旧原文同址 | `+The %s is empty now.` |
| `00598c88` | `00598c88` | 旧原文同址 | `Sailiokohta nyt slot #%d item %d * %d` |
| `00598d70` | `00598d70` | 旧原文同址 | `!Emptying the %s will discard its contents for good.` |
| `00599228` | `00599228` | 旧原文同址 | `Kelpoisuus:%s` |
| `00599238` | `00599238` | 旧原文同址 | `%s kätevyys: %d%% = %d  laatu: %d` |
| `0059925c` | `0059925c` | 旧原文同址 | `%s is %s tool here` |
| `00599270` | `00599270` | 旧原文同址 | `For one step that %s is %s tool` |
| `00599290` | `00599290` | 旧原文同址 | `%s is used` |
| `0059929c` | `0059929c` | 旧原文同址 | ` but suffers from %s quality.` |
| `005992bc` | `005992bc` | 旧原文同址 | ` and its %s quality certainly helps.` |
| `005992e4` | `005992e4` | 旧原文同址 | ` and, what is worse, of %s quality.` |
| `00599308` | `00599308` | 旧原文同址 | ` even though its %s quality counts.` |
| `0059932c` | `0059932c` | 旧原文同址 | `!%s` |
| `00599330` | `00599330` | 旧原文同址 | `use: %d%% maxqua: %d` |
| `00599348` | `00599348` | 旧原文同址 | `kl #%d %s` |
| `00599354` | `00599354` | 旧原文同址 | `maara: %u paino: %.2f` |
| `0059936c` | `0059936c` | 旧原文同址 | `painotapa (laskuri nyt: %.2f) painokoklaatu: %.2f` |
| `005993a0` | `005993a0` | 旧原文同址 | `maaratapa (laskuri nyt: %u) maarakoklaatu:%d` |
| `005993d0` | `005993d0` | 旧原文同址 | `painokoklaatu: %.2f TULOS: %d` |
| `005993f0` | `005993f0` | 旧原文同址 | `maarakoklaatu: %d TULOS: %d` |
| `0059a0fc` | `0059a0fc` | 旧原文同址 | ` (of %u)` |
| `0059a11c` | `0059a11c` | 旧原文同址 | `%s of %s * %u` |
| `0059a198` | `0059a198` | 旧原文同址 | ` - preferably %s.` |
| `0059a1b4` | `0059a1b4` | 旧原文同址 | ` - preferably of %s.` |
| `0059a1cc` | `0059a1cc` | 旧原文同址 | `)` |
| `0059a1d0` | `0059a1d0` | 旧原文同址 | `_(` |
| `0059a1d4` | `0059a1d4` | 旧原文同址 | `materiaali: %s - %s - %.2f` |
| `0059a1f0` | `0059a1f0` | 旧原文同址 | `vaateitem skill: %s` |
| `0059a20c` | `0059a20c` | 旧原文同址 | `linen %s` |
| `0059a218` | `0059a218` | 旧原文同址 | `hemp %s` |
| `0059a228` | `0059a228` | 旧原文同址 | `woollen %s` |
| `0059a234` | `0059a234` | 旧原文同址 | `nettle %s` |
| `0059a25c` | `0059a25c` | 旧原文同址 | `valmistuva vaate %s. skill: %s palat: %d` |
| `0059a288` | `0059a288` | 旧原文同址 | `paino: %.2f / %.2f` |
| `0059a29c` | `0059a29c` | 旧原文同址 | `B:%d E:%d T:%d P:%d S:%d FF:%d` |
| `0059a848` | `0059a848` | 旧原文同址 | `!The %s doesn't have enough capacity for the selected ingredients.` |
| `0059a8b0` | `0059a8b0` | 旧原文同址 | `kayttolista #%d - kaytetty:` |
| `0059a8cc` | `0059a8cc` | 旧原文同址 | `Id: %u Maara: %u Paino: %.2f` |
| `0059a8fc` | `0059a8fc` | 旧原文同址 | `paras_tarvike %s-hyvyys: %d` |
| `0059a92c` | `0059a92c` | 旧原文同址 | `rejected: %s data #%d (chosen already)` |
| `0059a954` | `0059a954` | 旧原文同址 | `check: %s data #%d` |
| `0059a968` | `0059a968` | 旧原文同址 | `sopiva: %s data: %d,%d` |
| `0059a980` | `0059a980` | 旧原文同址 | `start_invsearch laatu:%d hyvyys:%d` |
| `0059a9a4` | `0059a9a4` | 旧原文同址 | `invsopiva: %s inv: %d` |
| `0059a9f8` | `0059a9f8` | 旧原文同址 | `:Using %s is optional. Press [ESC] to skip the item selection.` |
| `0059aa68` | `0059aa68` | 旧原文同址 | `paras invstash: %s` |
| `0059aa7c` | `0059aa7c` | 旧原文同址 | `paras datastash: %s` |
| `0059aa90` | `0059aa90` | 旧原文同址 | `!%u pieces at a time is the maximum. Selecting %u pieces.` |
| `0059aad0` | `0059aad0` | 旧原文同址 | `!All of the %s will be used which is far more than needed. You can cancel the task and shorten it to required length at will.` |
| `0059ab50` | `0059ab50` | 旧原文同址 | `!That %s is too short for the purpose.` |
| `0059acb0` | `0059acb0` | 旧原文同址 | `#%d ot: %d` |
| `0059acbc` | `0059acbc` | 旧原文同址 | `#%d (act:%d) jaadyta: %s` |
| `0059bdd4` | `0059bdd4` | 旧原文同址 | `newscheck; #%d dist %d` |
| `0059be04` | `0059be04` | 旧原文同址 | `created:%d mindist:%d (now: %d)` |
| `0059be24` | `0059be24` | 旧原文同址 | `newstick in sync: created:%d, got:%d` |
| `0059be60` | `0059be60` | 旧原文同址 | `news delivery: knowledge #%d` |
| `0059be80` | `0059be80` | 旧原文同址 | `newstick updated: created:%d, got:%d` |
| `0059bea8` | `0059bea8` | 旧原文同址 | `news created: %d min - now %d min` |
| `0059becc` | `0059becc` | 旧原文同址 | `tiledist: %d minutedist: %d` |
| `0059bef0` | `0059bef0` | 旧原文同址 | `SocQuestCreator (%d,%d) soc: %d tags: %s` |
| `0059bf78` | `0059bf78` | 旧原文同址 | ` quest gen try %d / %d` |
| `0059bff4` | `0059bff4` | 旧原文同址 | `SocQuestCreatore trying to generate quest #%d` |
| `0059c024` | `0059c024` | 旧原文同址 | `precond months %d-%d (now %d)` |
| `0059c044` | `0059c044` | 旧原文同址 | `precond population %d-%d (now %d)` |
| `0059c068` | `0059c068` | 旧原文同址 | `precond minimum socfamiliarity %d (now %d)` |
| `0059c094` | `0059c094` | 旧原文同址 | `precond minimum overall rep %d (now %d)` |
| `0059c0bc` | `0059c0bc` | 旧原文同址 | `precond min days played %d (now %u)` |
| `0059c0ec` | `0059c0ec` | 旧原文同址 | `SocQuestCreat: picked npc #%d (%s) of soc #%d for quest #%d` |
| `0059c220` | `0059c220` | 旧原文同址 | `SocQuestCreat: quest %d already exists - rejected` |
| `0059c254` | `0059c254` | 旧原文同址 | `  SocQuestCreator -- DoQuestForNPC: %d (%s)` |
| `0059c2f0` | `0059c2f0` | 旧原文同址 | `vilmaint \| gap: %d \| pop: %d \| lastday: %d` |
| `0059c428` | `0059c428` | 旧原文同址 | `debt forgiven - everdebt now %.2f (debt level before: %d after %d)` |
| `0059c46c` | `0059c46c` | 旧原文同址 | `maksuhairiot: %d` |
| `0059c8d4` | `0059c8d4` | 旧原文同址 | `Maps total: %d` |
| `0059c940` | `0059c940` | 旧原文同址 | `Remove %d maps` |
| `0059ca40` | `0059ca40` | 旧原文同址 | `debti: %s` |
| `0059ca64` | `0059ca64` | 旧原文同址 | `vilpool #%d: %s count incr. to %d` |
| `0059ca88` | `0059ca88` | 旧原文同址 | `vilpool #%d: %s add %d` |
| `0059caa0` | `0059caa0` | 旧原文同址 | `flush %s * %d` |
| `0059cab0` | `0059cab0` | 旧原文同址 | `varastoi to %d,%d` |
| `0059cc3c` | `0059cc3c` | 旧原文同址 | `SPENDSTART %d (MIN %d, SEC: %d)` |
| `0059cc64` | `0059cc64` | 旧原文同址 | ` %d hours` |
| `0059cc70` | `0059cc70` | 旧原文同址 | `%d minutes` |
| `0059cc7c` | `0059cc7c` | 旧原文同址 | `%d seconds` |
| `0059ce9c` | `0059ce9c` | 旧原文同址 | `#%s helps you with this task.` |
| `0059cebc` | `0059cebc` | 旧原文同址 | `#%s help you with this task.` |
| `0059cedc` | `0059cedc` | 旧原文同址 | `#You get some help with this task from %s.` |
| `0059cf08` | `0059cf08` | 旧原文同址 | `TimeHelp (%d pct) activated. Numohelpers: %d : spendtick %d` |
| `0059cf44` | `0059cf44` | 旧原文同址 | `SPENDEND l: %d spendtick: %d (MINDONE %d) CompaidCounter: %d` |
| `0059d080` | `0059d080` | 旧原文同址 | `claim - IsoX,Y: %d,%d [%d,%d,%d,%d]` |
| `0059d0a4` | `0059d0a4` | 旧原文同址 | `owned: %s` |
| `0059d104` | `0059d104` | 旧原文同址 | `Looking for ` |
| `0059d130` | `0059d130` | 旧原文同址 | `name: %s` |
| `0059d13c` | `0059d13c` | 旧原文同址 | `viim x,y: %d,%d` |
| `0059d14c` | `0059d14c` | 旧原文同址 | `meet: %d now: %u` |
| `0059d160` | `0059d160` | 旧原文同址 | `sotu: %u` |
| `0059d188` | `0059d188` | 旧原文同址 | `found isox,isoy zoommap: %d,%d` |
| `0059d1a8` | `0059d1a8` | 旧原文同址 | `searching sotu %d` |
| `0059d1bc` | `0059d1bc` | 旧原文同址 | `!On this map! %d,%d. ` |
| `0059d314` | `0059d314` | 旧原文同址 | `kohta: %d ranta: %d reldepth: %d gotshore:%d` |
| `0059d648` | `0059d648` | 旧原文同址 | `icebreak check %d,%d icemm: %d wt:%d holds:%d` |
| `0059d68c` | `0059d68c` | 旧原文同址 | `crust break check %d,%d icemm: %d wt:%d holds:%d` |
| `0059d848` | `0059d848` | 旧原文同址 | `+%s has burnt out.` |
| `0059d85c` | `0059d85c` | 旧原文同址 | `+Light of the %s is fading.` |
| `0059e41c` | `0059e41c` | 旧原文同址 | `sneak` |
| `0059e440` | `0059e440` | 旧原文同址 | `!The water is %s.` |
| `0059e5d0` | `0059e5d0` | 旧原文同址 | `!You reckon the %s is somewhere up ahead, just out of sight. Move forward carefully to catch up with it.` |
| `0059e654` | `0059e654` | 旧原文同址 | `stacks: %d weight: %.2f (over %.2f)` |
| `0059e678` | `0059e678` | 旧原文同址 | `stacks: %d weight: %.2f` |
| `0059e690` | `0059e690` | 旧原文同址 | `nakosuoja: %d` |
| `0059e72c` | `0059e72c` | 旧原文同址 | `!You are not able move ahead %s!` |
| `0059e750` | `0059e750` | 旧原文同址 | `!You can't run any longer %s!` |
| `0059e81c` | `0059e81c` | 旧原文同址 | `ACTUAL_MOBILITY: %d` |
| `0059ea7c` | `0059ea7c` | 旧原文同址 | `MoveTransport %d -> %d,%d` |
| `005a0058` | `005a0058` | 旧原文同址 | `Socrole %d for %s` |
| `005a021c` | `005a021c` | 旧原文同址 | `!%s seems to notice your hideout!` |
| `005a0298` | `005a0298` | 旧原文同址 | `pako kohtaan: %d,%d (npc: %d,%d pelaaja: %d,%d)` |
| `005a0704` | `005a0704` | 旧原文同址 | `hinta: %.2f (= %.2f rahaa)` |
| `005a0720` | `005a0720` | 旧原文同址 | `AGE: %d months (%d dats)` |
| `005a073c` | `005a073c` | 旧原文同址 | `days_played:%u ensitap.:%d (%d)<br>` |
| `005a0760` | `005a0760` | 旧原文同址 | `energy: %d/%d obstacle:%d<br>` |
| `005a0780` | `005a0780` | 旧原文同址 | `ruokavalio #1:%u #2:%u<br>` |
| `005a079c` | `005a079c` | 旧原文同址 | `lauma: %d lstatus: %d<br>` |
| `005a07b8` | `005a07b8` | 旧原文同址 | `PUUHA: %d (aika: %d) PAAPUUHA: %d saalistaako:%d<br>` |
| `005a07f0` | `005a07f0` | 旧原文同址 | `NPC: %d SOTU: %u OMISTAJA: %d QUEST: %u<br>` |
| `005a083c` | `005a083c` | 旧原文同址 | `HERBLORE: %d<br>SWIMMING: %d<br>CROSSBOW: %d<br>` |
| `005a0870` | `005a0870` | 旧原文同址 | `Paino: %.2f (Keskip.: %2.f Kerroin:%d)<br>` |
| `005a089c` | `005a089c` | 旧原文同址 | `Load: %d, Encumbrance: %d Injury:%d<br>` |
| `005a08c4` | `005a08c4` | 旧原文同址 | `Fatigue rate: %.2f, Fatigue: %.2f<br>` |
| `005a08ec` | `005a08ec` | 旧原文同址 | `INVA o-j:%.2f v-j:%.2f o-k:%.2f v-k:%.2f<br>` |
| `005a091c` | `005a091c` | 旧原文同址 | `km/h kaynti:%d max:%d - actual: %d (%d km/h)<br>` |
| `005a0950` | `005a0950` | 旧原文同址 | `LastActionBit: %d<br>` |
| `005a0968` | `005a0968` | 旧原文同址 | `korkeus: %.2f keskipiste: %.2f<br>` |
| `005a098c` | `005a098c` | 旧原文同址 | `Pako x,y: %d,%d (viimeisin x,y: %d,%d)<br>` |
| `005a09c0` | `005a09c0` | 旧原文同址 | `Moraali<br>Karta:%d Pakene:%d Hyokkaa:%d<br>` |
| `005a09f0` | `005a09f0` | 旧原文同址 | `Varovaisuus:%d<br>` |
| `005a0a04` | `005a0a04` | 旧原文同址 | `Hinta: %.2f (=%d rahaa)<br>` |
| `005a0a34` | `005a0a34` | 旧原文同址 | `SOC<br>soc: %u<br>perinta: : %d<br>vio_theft: %d<br>` |
| `005a0a6c` | `005a0a6c` | 旧原文同址 | `KOTI ISOX,ISOY: %d,%d<br>` |
| `005a0a88` | `005a0a88` | 旧原文同址 | `reclaim_needed: %d<br>gotdebt: %d<br>` |
| `005a0ab0` | `005a0ab0` | 旧原文同址 | `banish: %d (until %d day)<br>` |
| `005a0ad0` | `005a0ad0` | 旧原文同址 | `violence: %d bfagg: %d murder: %d ` |
| `005a0af4` | `005a0af4` | 旧原文同址 | `maksuhairiot: %d everdebt: %.2f<br>` |
| `005a43d8` | `005a43e8` | 旧原文同字节 | `#%d maps read - please wait...` |
| `005a441c` | `005a442c` | 旧原文同字节 | `#%d objects kept.` |
| `005a5230` | `005a5240` | 旧原文同字节 | `:%s %s.` |
| `005a529c` | `005a52ac` | 旧原文同字节 | `&You are %s` |
| `005a52a8` | `005a52b8` | 旧原文同字节 | `Vatsa: %d Energiavaranto: %d` |
| `005a53f4` | `005a5404` | 旧原文同字节 | `!You fall %d meters and get your %s knocked on the way down!` |
| `005a5434` | `005a5444` | 旧原文同字节 | `Hurt after %d meters fall` |
| `005a5570` | `005a5580` | 旧原文同字节 | `:@Your ` |
| `005a5578` | `005a5588` | 旧原文同字节 | ` anymore.` |
| `005a5584` | `005a5594` | 旧原文同字节 | `:@You don't suffer from ` |
| `005a569c` | `005a56ac` | 旧原文同字节 | `Oikeakasi: %.2f Vasen: %.2f Jompikumpi: %.2f` |
| `005a579c` | `005a57ac` | 旧原文同字节 | `!There is no external treatment for %s!` |
| `005a57c4` | `005a57d4` | 旧原文同字节 | `Hoitobit %d jo päällä.` |
| `005a5824` | `005a5834` | 旧原文同字节 | `Yrttihoitotarve: %s` |
| `005a5838` | `005a5848` | 旧原文同字节 | `Yrttihoito: %s` |
| `005a5858` | `005a5868` | 旧原文同字节 | `!The %s still continues to bleed.` |
| `005a587c` | `005a588c` | 旧原文同字节 | `=Bleeding of the %s is now stopped.` |
| `005a5920` | `005a5930` | 旧原文同字节 | `!The treatment causes the %s to start bleeding.` |
| `005a5a0c` | `005a5a1c` | 旧原文同字节 | `Ennen unta: Vatsa: %d Energia: %d` |
| `005a5a30` | `005a5a40` | 旧原文同字节 | `Exh: %d` |
| `005a5df0` | `005a5e00` | 旧原文同字节 | `Herättyä: Vatsa: %d Energia: %d` |
| `005a5e10` | `005a5e20` | 旧原文同字节 | `Slept: %d` |
| `005a5fb0` | `005a5fc0` | 旧原文同字节 | `hurt body` |
| `005a5fbc` | `005a5fcc` | 旧原文同字节 | `_%s needed, but only your %s is in usable condition.` |
| `005a6004` | `005a6014` | 旧原文同字节 | `_%s needed.` |
| `005a6010` | `005a6020` | 旧原文同字节 | `!It will be slow and difficult to %s now.` |
| `005a603c` | `005a604c` | 旧原文同字节 | `INVASUHDE_liikuntaelimet: %.2f` |
| `005a8a70` | `005a8a80` | 旧原文同字节 | `+You carve some shards of the %s into an ant nest as a sacrifice.` |
| `005a8ab4` | `005a8ac4` | 旧原文同字节 | `The %s got used completely.` |
| `005a8ad0` | `005a8ae0` | 旧原文同字节 | `!For some reason, this doesn't feel like the right place nor time to sacrifice the %s.` |
| `005a8e50` | `005a8e60` | 旧原文同字节 | `_This spell about %s is performed by following the given instructions by using the common game mechanics and actions.` |
| `005a915c` | `005a916c` | 旧原文同字节 | `I promise you %s from my flock to be found in the %s.` |
| `005a9f38` | `005a9f48` | 旧原文同字节 | `%s%s%s` |
| `005a9fa4` | `005a9fb4` | 旧原文同字节 | `Select %s` |
| `005aa700` | `005aa710` | 旧原文同字节 | `HOW MANY? (OF TOTAL %d)` |
| `005aa764` | `005aa774` | 旧原文同字节 | `!The minimum is %d, which is now selected.` |
| `005aabd4` | `005aabe4` | 旧原文同字节 | `#Entering ` |
| `005aabe0` | `005aabf0` | 旧原文同字节 | `You enter %s.` |
| `005aac20` | `005aac30` | 旧原文同字节 | ` \| BIGXY %d,%d` |
| `005aac30` | `005aac40` | 旧原文同字节 | `%d-%d (of %d)` |
| `005aace0` | `005aacf0` | 旧原文同字节 | `listhotkey %d - %s` |
| `005aad8c` | `005aad9c` | 旧原文同字节 | `? %s` |
| `005aaf2c` | `005aaf3c` | 旧原文同字节 | `build_pause (%d,%d) - mc: %d` |
| `005aaf4c` | `005aaf5c` | 旧原文同字节 | `rakennusaika %d/%d` |
| `005aaf60` | `005aaf70` | 旧原文同字节 | `rakenna: [%d] pura: [%d]` |
| `005aafd4` | `005aafe4` | 旧原文同字节 | `!Not possible! There's %s.` |
| `005ab000` | `005ab010` | 旧原文同字节 | `leftmins: %d spentmins: %d` |
| `005ab1b0` | `005ab1c0` | 旧原文同字节 | `!Placing %s there is either too far or incorrectly aligned from the framework center!` |
| `005ac224` | `005ac234` | 旧原文同字节 | `your settlement, ` |
| `005ac238` | `005ac248` | 旧原文同字节 | `a shelter, ` |
| `005ac244` | `005ac254` | 旧原文同字节 | `a kota, ` |
| `005ac250` | `005ac260` | 旧原文同字节 | `set traps, ` |
| `005ac25c` | `005ac26c` | 旧原文同字节 | `a net set to catch, ` |
| `005ac274` | `005ac284` | 旧原文同字节 | `a punt, ` |
| `005ac280` | `005ac290` | 旧原文同字节 | `a raft, ` |
| `005ac28c` | `005ac29c` | 旧原文同字节 | `#There is %s at this location.` |
| `005ac2ac` | `005ac2bc` | 旧原文同字节 | `#There are several objects %s:` |
| `005ac2cc` | `005ac2dc` | 旧原文同字节 | `#Things that are %s:` |
| `005ac2e4` | `005ac2f4` | 旧原文同字节 | `marked location - "%s"` |
| `005ac2fc` | `005ac30c` | 旧原文同字节 | `Freezeitem: %s * %d [extrach: %d]` |
| `005ac320` | `005ac330` | 旧原文同字节 | `%d %s %s` |
| `005ac32c` | `005ac33c` | 旧原文同字节 | ` (work in progress)` |
| `005ac340` | `005ac350` | 旧原文同字节 | `%s (being prepared)` |
| `005ac354` | `005ac364` | 旧原文同字节 | `ItemInProcess (%s) %d,%d D:%d C:%d` |
| `005ac378` | `005ac388` | 旧原文同字节 | `Extra: %d   Set_Day (smoke): %d` |
| `005ac398` | `005ac3a8` | 旧原文同字节 | `fresh %s` |
| `005ac3e4` | `005ac3f4` | 旧原文同字节 | `%s %d` |
| `005ac3ec` | `005ac3fc` | 旧原文同字节 | `set %s` |
| `005ac3f4` | `005ac404` | 旧原文同字节 | `triggered %s` |
| `005ac404` | `005ac414` | 旧原文同字节 | `ansakelpoisia: %d` |
| `005ac418` | `005ac428` | 旧原文同字节 | `ansa spawn rnd: %d to %d,%d` |
| `005ac434` | `005ac444` | 旧原文同字节 | `%s set to catch fish` |
| `005ac44c` | `005ac45c` | 旧原文同字节 | `HeatValue: %d` |
| `005ac4a8` | `005ac4b8` | 旧原文同字节 | `%s shaped figure in the distance` |
| `005ac4cc` | `005ac4dc` | 旧原文同字节 | `[DEBUG_INFO] sotu: %d quest: %d` |
| `005ac4ec` | `005ac4fc` | 旧原文同字节 | `total burn mins: %d  lastburn: %d` |
| `005ac510` | `005ac520` | 旧原文同字节 | `#You see %s %s.` |
| `005ac520` | `005ac530` | 旧原文同字节 | `:This fire will burn %s.` |
| `005ac53c` | `005ac54c` | 旧原文同字节 | `_...and %u more.` |
| `005ac550` | `005ac560` | 旧原文同字节 | `%s (%d,%d) [mc: %d] syvyys:%d korkeus: %d (PINTA: %d) terrain_altitude: %.2f` |
| `005ac5a0` | `005ac5b0` | 旧原文同字节 | `mapwise ice: %d mm (%d cm)` |
| `005ac5bc` | `005ac5cc` | 旧原文同字节 | `True ice: %d mm (%d cm)` |
| `005ac5d4` | `005ac5e4` | 旧原文同字节 | `soc: %d` |
| `005ac5dc` | `005ac5ec` | 旧原文同字节 | `luontotyyppi: %d jaatyy:%d` |
| `005ac5f8` | `005ac608` | 旧原文同字节 | `'%s'` |
| `005ac600` | `005ac610` | 旧原文同字节 | `TYPE:%d DATA:%d Extra:%d Set_Day:%d (spent:%d, left:%d)` |
| `005ac65c` | `005ac66c` | 旧原文同字节 | `_The water is %s.` |
| `005acef4` | `005acf04` | 旧原文同字节 | `craftquality: ML:%d success:%d SI:%d` |
| `005acf1c` | `005acf2c` | 旧原文同字节 | `craftquality tulos: %d` |
| `005acf34` | `005acf44` | 旧原文同字节 | `TYOAIKA_mod: %d -> %d` |
| `005acfd4` | `005acfe4` | 旧原文同字节 | `!That's only a %s and doesn't provide proper bark.` |
| `005ad090` | `005ad0a0` | 旧原文同字节 | `!It is not possible to peel bark from a %s at this time of the year.` |
| `005ad1f0` | `005ad200` | 旧原文同字节 | `+You managed to harvest %s from this tree.` |
| `005ad428` | `005ad438` | 旧原文同字节 | `og time to fell: %d` |
| `005ad43c` | `005ad44c` | 旧原文同字节 | `calc time to fell: %d (%d-%d)` |
| `005ad45c` | `005ad46c` | 旧原文同字节 | `FELLSPEND: spend(%d) - spent already:%d` |
| `005ad494` | `005ad4a4` | 旧原文同字节 | `not felled, spent working: %d` |
| `005ad4b4` | `005ad4c4` | 旧原文同字节 | `time left: %d total spent: %d` |
| `005ad6a8` | `005ad6b8` | 旧原文同字节 | `I need some equipment to %s.` |
| `005ad750` | `005ad760` | 旧原文同字节 | `UINTI debug suhde: %.2f` |
| `005ad768` | `005ad778` | 旧原文同字节 | `&You swim at ease.` |
| `005ad77c` | `005ad78c` | 旧原文同字节 | `&You feel slightly fatigued from swimming.` |
| `005ad7a8` | `005ad7b8` | 旧原文同字节 | `&You are moderately fatigued from swimming.` |
| `005ad7d4` | `005ad7e4` | 旧原文同字节 | `&You are lacking the strength to swim much longer.` |
| `005ad808` | `005ad818` | 旧原文同字节 | `&You are exhausted and having trouble to keep afloat!` |
| `005ad840` | `005ad850` | 旧原文同字节 | `&You struggle in the water with your last bit of strength! You are in danger of drowning!` |
| `005adab4` | `005adac4` | 旧原文同字节 | `at %d meters` |
| `005adac4` | `005adad4` | 旧原文同字节 | `{fall}:You lose your grip %s!` |
| `005adcb0` | `005adcc0` | 旧原文同字节 | `You start to cut the %s carcass...` |
| `005adcf8` | `005add08` | 旧原文同字节 | `=You got %d edible cuts of %s meat.` |
| `005add1c` | `005add2c` | 旧原文同字节 | `%s fat` |
| `005ade5c` | `005ade6c` | 旧原文同字节 | `!Do %s first! Only then it is possible to %s.` |
| `005adea0` | `005adeb0` | 旧原文同字节 | `Cured de-haired %s-skin` |
| `005adeb8` | `005adec8` | 旧原文同字节 | `Cured %s-skin` |
| `005adf00` | `005adf10` | 旧原文同字节 | `!The %s needs no de-hairing.` |
| `005adf20` | `005adf30` | 旧原文同字节 | `De-haired %s-skin` |
| `005adfb0` | `005adfc0` | 旧原文同字节 | `clean %s-skin` |
| `005ae128` | `005ae138` | 旧原文同字节 | `#Tanning process now requires you to %s.` |
| `005ae17c` | `005ae18c` | 旧原文同字节 | `%s %s-skin` |
| `005ae188` | `005ae198` | 旧原文同字节 | `_This step is complete %s. After that, continue tanning the skin until the whole process is finished off.` |
| `005ae250` | `005ae260` | 旧原文同字节 | `!That's only a %s and doesn't provide proper branches.` |
| `005ae398` | `005ae3a8` | 旧原文同字节 | `+You finished cutting the %s. They are lying beside you on the ground.` |
| `005ae618` | `005ae628` | 旧原文同字节 | `start the fire` |
| `005ae78c` | `005ae79c` | 旧原文同字节 | `_You can spin %s of yarn on one go.` |
| `005ae7b0` | `005ae7c0` | 旧原文同字节 | `_From that stack of fibre you can spin about %s of yarn.` |
| `005ae7f0` | `005ae800` | 旧原文同字节 | `_From that stack of sinew fibre you can make about %s of sinew yarn.` |
| `005aea04` | `005aea14` | 旧原文同字节 | `Retted %s` |
| `005aeac0` | `005aead0` | 旧原文同字节 | `!Here you can process only %u plants on one go! Selecting %u pieces.` |
| `005aede4` | `005aedf4` | 旧原文同字节 | `Dried retted %s` |
| `005aedf4` | `005aee04` | 旧原文同字节 | `dried %s tendon` |
| `005aeeb8` | `005aeec8` | 旧原文同字节 | `:You see %s is bleeding.` |
| `005aeee4` | `005aeef4` | 旧原文同字节 | `Try to treat %s wounds?` |
| `005aefa4` | `005aefb4` | 旧原文同字节 | `>ML A: %d (-%d) -- ML B: %d (-%d)` |
| `005aefc8` | `005aefd8` | 旧原文同字节 | `EML A: %d -- EML B: %d` |
| `005aefe0` | `005aeff0` | 旧原文同字节 | `>PEN muutos: %d` |
| `005aeff0` | `005af000` | 旧原文同字节 | `>EML A: %d -- EML B: %d` |
| `005af008` | `005af018` | 旧原文同字节 | `Kayta no-list taitoa: %s (%d%%)` |
| `005af028` | `005af038` | 旧原文同字节 | `Kayta taitoa: %s (%d%%) [-%d] [+%d] Kehitys: %d` |
| `005af088` | `005af098` | 旧原文同字节 | `#Using: ` |
| `005af104` | `005af114` | 原语义hook的新版操作数 005238f2 | `due to %s` |
| `005af110` | `005af120` | 原语义hook的新版操作数 00523916 | `mostly due to %s` |
| `005af124` | `005af134` | 原语义hook的新版操作数 00523942 | `due to %s and %s` |
| `005af138` | `005af148` | 原语义hook的新版操作数 00523949 | `due to %s and %s - plus other penalties` |
| `005af160` | `005af170` | 原语义hook的新版操作数 00523a7c | `already unskilled %s attempt` |
| `005af180` | `005af190` | 原语义hook的新版操作数 00523aa7 | `%s attempt` |
| `005af18c` | `005af19c` | 原语义hook的新版操作数 00523ad2 | `%s performance` |
| `005af19c` | `005af1ac` | 原语义hook的新版操作数 00523afd | `%s expertise` |
| `005af1ac` | `005af1bc` | 原语义hook的新版操作数 00523b19 | `mastery in %s` |
| `005af1bc` | `005af1cc` | 原语义hook的新版操作数 00523b2c | `&Your %s ` |
| `005b0140` | `005b0150` | 旧原文同字节 | `new LAST_TACTICAL_ADVANTAGE: %d` |
| `005b0438` | `005b0448` | 旧原文同字节 | `ATTACK_RESULT: %s%d` |
| `005b05fc` | `005b060c` | 旧原文同字节 | `Haavatulos: %s` |
| `005b060c` | `005b061c` | 旧原文同字节 | `HAAVOITA %d: impact: %d Haarniskointi: %d -> eff_impact: %d` |
| `005b0668` | `005b0678` | 旧原文同字节 | `Aste: %d F:%d S:%d E:%d B:%d IP:%d` |
| `005b0864` | `005b0874` | 旧原文同字节 | `GetMissileVelocity %s - WT: %.2f vminus: %.2f - VELOCITY: %.2f` |
| `005b08ac` | `005b08bc` | 旧原文同字节 | `Missile: %d,%d -> %d,%d : Etaisyys: %d` |
| `005b08d4` | `005b08e4` | 旧原文同字节 | `Lentava ase: %s` |
| `005b08e4` | `005b08f4` | 旧原文同字节 | `Ampuva jousi: %s` |
| `005b0908` | `005b0918` | 旧原文同字节 | `Missiletaito: %s ML: %d` |
| `005b096c` | `005b097c` | 旧原文同字节 | `Missile_success:%d accuracy:%d` |
| `005b098c` | `005b099c` | 旧原文同字节 | `Missile IMPACT:%d AttackAspect:%d` |
| `005b09b0` | `005b09c0` | 旧原文同字节 | `Velocity: %.2f Aero: %.2f` |
| `005b09cc` | `005b09dc` | 旧原文同字节 | `laukaisukorkeus: %.2f m / maali: %.2f m cone: %.2f` |
| `005b0a00` | `005b0a10` | 旧原文同字节 | `MslHit VC:%.2f m/2 KE:%d` |
| `005b0a1c` | `005b0a2c` | 旧原文同字节 | `RealImpact calc - d6*%d + %d Deathblow: %d` |
| `005b0a48` | `005b0a58` | 旧原文同字节 | `RealImpact %d (noppasumma %d + %d)` |
| `005b0ac4` | `005b0ad4` | 旧原文同字节 | `!%s osumariski %d%%` |
| `005b0ad8` | `005b0ae8` | 旧原文同字节 | `!%s ei ammu!` |
| `005b0ae8` | `005b0af8` | 旧原文同字节 | `!%s kokeilee kuitenkin ampua!` |
| `005b0b78` | `005b0b88` | 旧原文同字节 | `Head%s` |
| `005b0b80` | `005b0b90` | 旧原文同字节 | `Arms%s` |
| `005b0b88` | `005b0b98` | 旧原文同字节 | `Legs%s` |
| `005b0b9c` | `005b0bac` | 旧原文同字节 | `strikeimpact %d maxdices: %d` |
| `005b0bbc` | `005b0bcc` | 旧原文同字节 | `>WPMOD: A:%d D:%d = %d` |
| `005b0c40` | `005b0c50` | 旧原文同字节 | `MOVEDODGE: %d` |
| `005b0c50` | `005b0c60` | 旧原文同字节 | `>Dodge_ML(%d): %d` |
| `005b0c78` | `005b0c88` | 旧原文同字节 | `Block with %s` |
| `005b0c90` | `005b0ca0` | 旧原文同字节 | `Counterstrike with %s` |
| `005b0cfc` | `005b0d0c` | 旧原文同字节 | `NPCdefend: %s Dge:%d Blk:%d chose:%d` |
| `005b0f80` | `005b0f90` | 旧原文同字节 | `MISSILE olento_osuma - OGImpact: %d` |
| `005b0fa4` | `005b0fb4` | 旧原文同字节 | `MISSILE olento_osuma - NewImpact: %d (OGI %d+KE %d / 2)` |
| `005b101c` | `005b102c` | 旧原文同字节 | `A-SKILL:%s(%d) D-SKILL:%s(%d)` |
| `005b1090` | `005b10a0` | 旧原文同字节 | `>OUTNUMBERED BY %d NPCs` |
| `005b10e8` | `005b10f8` | 旧原文同字节 | `ZonePenalty: %d` |
| `005b10f8` | `005b1108` | 旧原文同字节 | `>HANDPENALTY:%d` |
| `005b1108` | `005b1118` | 旧原文同字节 | `DEFENDER ZonePenalty: %d` |
| `005b1138` | `005b1148` | 旧原文同字节 | `>DEFENDER HANDPENALTY:%d` |
| `005b1154` | `005b1164` | 旧原文同字节 | `>A_BONUS:%d D_BONUS:%d` |
| `005b116c` | `005b117c` | 旧原文同字节 | `>A_PEN:%d D_PEN:%d` |
| `005b1180` | `005b1190` | 旧原文同字节 | `>EML_sync A_PEN:%d D_PEN:%d` |
| `005b119c` | `005b11ac` | 旧原文同字节 | `Puolustus Ignore: SUCCESS (%d) BOOST` |
| `005b11c4` | `005b11d4` | 旧原文同字节 | `Puolustus Ignore: SUCCESS NOW %d` |
| `005b11e8` | `005b11f8` | 旧原文同字节 | `+The %s breaks!` |
| `005b13a4` | `005b13b4` | 旧原文同字节 | `one handed penalty: %d` |
| `005b13f4` | `005b1404` | 旧原文同字节 | `You kick the %s behind you with your heel.` |
| `005b1434` | `005b1444` | 旧原文同字节 | `You kick the %s. Ouch!` |
| `005b1488` | `005b1498` | 旧原文同字节 | `!You can't reach to hit the %s! It's high above your head.` |
| `005b3b20` | `005b3b30` | 旧原文同字节 | `It's %s.` |
| `005b62a4` | `005b62b4` | 旧原文同字节 | `?What do you want to call %s?` |
| `005b633c` | `005b634c` | 旧原文同字节 | `ANIMAL COMMANDS: %s` |
| `005b6950` | `005b6960` | 旧原文同字节 | `No, %s. We are not talking. Go.` |
| `005b6b60` | `005b6b70` | 旧原文同字节 | `NO NewQuestsAllowed - not played enough, days played %u` |
| `005b6b98` | `005b6ba8` | 旧原文同字节 | `NO NewQuestsAllowed - day interval - last quest: %u now %u` |
| `005b6c80` | `005b6c90` | 旧原文同字节 | `Quest #%d - ERRORS: %d` |
| `005b7b1c` | `005b7b2c` | 原语义hook的新版操作数 005489a0 | `on a small %s island` |
| `005b7bdc` | `005b7bec` | 原语义hook的新版操作数 00548d48 | `within a deep chasm in the %s` |
| `005b7c18` | `005b7c28` | 原语义hook的新版操作数 00548e2e | ` of %s origin` |
| `005b7c28` | `005b7c38` | 原语义hook的新版操作数 00548ebf | `treasure of %s %s` |
| `005b8250` | `005b8260` | 既有源码原文 | `Need for %s` |
| `005bd700` | `005bd710` | 既有源码原文 | `From %s to %s` |
| `005be030` | `005be040` | 既有源码原文 | `Adventurer's %s` |
| `005c1a0c` | `005c1a1c` | 既有源码原文 | `Disoriented %s` |
| `005c9460` | `005c9470` | 既有源码原文 | `%s in the forest cover` |
| `005cc660` | `005cc670` | 旧原文同字节 | `DoQuestForNPC failed to generate quest #%d for npc #%d` |
| `005cc698` | `005cc6a8` | 旧原文同字节 | `DoQuestForNPC generated quest #%d for npc #%d` |
| `005cc808` | `005cc818` | 旧原文同字节 | `!%s quest has expired and is removed from the quest journal.` |
| `005d80dc` | `005d80ec` | 旧原文同字节 | `!ERROR: %s is missing!` |
| `005d8104` | `005d8114` | 旧原文同字节 | `I haven't been taught to talk about %s.` |
| `005d8188` | `005d8198` | 旧原文同字节 | `I can't talk about %s.` |
| `005d8258` | `005d8268` | 旧原文同字节 | `!You can't %s while %s!` |
| `005d8270` | `005d8280` | 旧原文同字节 | `!You can't %s!` |
| `005d88c4` | `005d88d4` | 旧原文同字节 | `!%s is not allowed on the wilderness map.` |
| `005d9050` | `005d9060` | 旧原文同字节 | `+You removed %s from that fishing rod.` |
| `005d90a8` | `005d90b8` | 旧原文同字节 | `+You have unstrung the %s.` |
| `005d91f8` | `005d9208` | 旧原文同字节 | `+Now you have a %s.` |
| `005d9328` | `005d9338` | 旧原文同字节 | `+Now you have a strung %s ready to use.` |
| `005d9398` | `005d93a8` | 旧原文同字节 | `#You continue filling up the pit.` |
| `005d93bc` | `005d93cc` | 旧原文同字节 | `#You start digging a pit.` |
| `005d93d8` | `005d93e8` | 旧原文同字节 | `#You start filling up the pit.` |
| `005d9584` | `005d9594` | 旧原文同字节 | `Tie npc: %d` |
| `005d95bc` | `005d95cc` | 旧原文同字节 | `Tie Cre[%d].bfdom set to %d` |
| `005d9660` | `005d9670` | 旧原文同字节 | ` has burnt out and can't be lighted.` |
| `005d9688` | `005d9698` | 旧原文同字节 | `Your ` |
| `005d9690` | `005d96a0` | 旧原文同字节 | `light a %s` |
| `005d9714` | `005d9724` | 旧原文同字节 | `You stroke the %s.` |
| `005d98cc` | `005d98dc` | 旧原文同字节 | `!There's no special way to apply %s.` |
| `005d9974` | `005d9984` | 旧原文同字节 | `Here you notice %s %s %s` |
| `005d9990` | `005d99a0` | 旧原文同字节 | `which are numerous and mixed` |
| `005d99b0` | `005d99c0` | 旧原文同字节 | ` %s` |
| `005d99b4` | `005d99c4` | 旧原文同字节 | `mixed with some other unclear tracks` |
| `005d99dc` | `005d99ec` | 旧原文同字节 | ` leading %s` |
| `005d99e8` | `005d99f8` | 旧原文同字节 | `Jaljen vahvuus: %d` |
| `005d99fc` | `005d9a0c` | 旧原文同字节 | `Ikä päivinä: %d` |
| `005d9a0c` | `005d9a1c` | 旧原文同字节 | `Jaljen COUNT: %d` |
| `005d9b48` | `005d9b58` | 旧原文同字节 | `ActIt (%d)` |
| `005d9b54` | `005d9b64` | 旧原文同字节 | `Activity based Esc Cre[%d]` |
| `005d9d48` | `005d9d58` | 旧原文同字节 | `!The fire burns your ` |
| `005d9de4` | `005d9df4` | 旧原文同字节 | `_You are about to discard %s.` |
| `005d9f70` | `005d9f80` | 旧原文同字节 | `#1st weapon: ` |
| `005d9f94` | `005d9fa4` | 旧原文同字节 | `#2nd weapon: ` |
| `005da3d8` | `005da3e8` | 旧原文同字节 | `60 minute embers: %d` |
| `005da3f8` | `005da408` | 旧原文同字节 | `fert data: %d` |
| `005da448` | `005da458` | 旧原文同字节 | `%s * %d - tee uniikki.` |
| `005da468` | `005da478` | 旧原文同字节 | `Aikahyppy %d` |
| `005da514` | `005da524` | 旧原文同字节 | `x+ %d y+ ,%d on pesa` |
| `005da52c` | `005da53c` | 旧原文同字节 | `%d,%d on lahde` |
| `005da54c` | `005da55c` | 旧原文同字节 | `Day: %d Month: %d` |
| `005da560` | `005da570` | 旧原文同字节 | `from %d to %d (last 30)` |
| `005da578` | `005da588` | 旧原文同字节 | `avgtemp: %d avgrain %d` |
| `005da590` | `005da5a0` | 旧原文同字节 | `from %d to %d (last 90)` |
| `005da5a8` | `005da5b8` | 旧原文同字节 | `from %d to %d (last 180)` |
| `005da5c8` | `005da5d8` | 旧原文同字节 | `Day %d  Month %d` |
| `005da5dc` | `005da5ec` | 旧原文同字节 | `GUU \| Vaihe: %d, Kuunvalo: %d, Kulma: %d` |
| `005da608` | `005da618` | 旧原文同字节 | `snowtopice: %d` |
| `005da618` | `005da628` | 旧原文同字节 | `Summary: (%d-%d) avgtemp: %d  avgrain: %d` |
| `005da644` | `005da654` | 旧原文同字节 | `temp: %d rain: %d raintype: %d  wndspeed: %d` |
| `005da674` | `005da684` | 旧原文同字节 | `snow: %d mm (%d cm) pilvisyys: %d` |
| `005da698` | `005da6a8` | 旧原文同字节 | `sa now: %d sa next: %d` |
| `005da6b0` | `005da6c0` | 旧原文同字节 | `CurDay: %d CurHour: %d (plrhour: %d)` |
| `005da6d8` | `005da6e8` | 旧原文同字节 | `water temp: %d globweather.ice: %d` |
| `005da6fc` | `005da70c` | 旧原文同字节 | `PLR bodytemp: %.2f` |
| `005da710` | `005da720` | 旧原文同字节 | `Moon xpos: %d \| Moon phase: %d` |
| `005da7c4` | `005da7d4` | 旧原文同字节 | `Osumapros. %d` |
| `005da800` | `005da810` | 旧原文同字节 | `tex %d` |
| `005da840` | `005da850` | 旧原文同字节 | `rods %d+%d = %d` |
| `005da868` | `005da878` | 旧原文同字节 | `%d ` |
| `005da86c` | `005da87c` | 旧原文同字节 | `%d,%d` |
| `005da8ec` | `005da8fc` | 旧原文同字节 | `There's a blacksmith in a village %s` |
| `005da920` | `005da930` | 旧原文同字节 | `There's a sage in a village %s` |
| `005da96c` | `005da97c` | 旧原文同字节 | `globVilID %d` |
| `005da97c` | `005da98c` | 旧原文同字节 | `after rumble globVilID %d` |
| `005da9c4` | `005da9d4` | 旧原文同字节 | `village %d` |
| `005da9f8` | `005daa08` | 旧原文同字节 | `island %d,%d` |
| `005daa08` | `005daa18` | 旧原文同字节 | `cave %d,%d` |
| `005daa14` | `005daa24` | 旧原文同字节 | `Cliff %d,%d` |
| `005daa4c` | `005daa5c` | 旧原文同字节 | `important: %d` |
| `005daa74` | `005daa84` | 旧原文同字节 | `Loc: %d,%d` |
| `005daa80` | `005daa90` | 旧原文同字节 | `There's a treasure %s %s` |
| `005daa9c` | `005daaac` | 旧原文同字节 | `The treasure is %s, %s. It's said to be %s.` |
| `005dab04` | `005dab14` | 旧原文同字节 | `pathmake: %d` |
| `005dab28` | `005dab38` | 旧原文同字节 | `%d,%d (nyt %d,%d) %s` |
| `005dabdc` | `005dabec` | 旧原文同字节 | `cur %d` |
| `005dac08` | `005dac18` | 旧原文同字节 | `Success %d - icegone forecast %d.%d. (in %d days)` |
| `005dac3c` | `005dac4c` | 旧原文同字节 | `Success %d - ice no more safe forecast %d.%d. (in %d days)` |
| `005daca4` | `005dacb4` | 旧原文同字节 | `bear teeth: %d` |
| `005dacc4` | `005dacd4` | 旧原文同字节 | `prev: %d cur: %d - spent: %d` |
| `005dace4` | `005dacf4` | 旧原文同字节 | `time left: %d` |
| `005dad08` | `005dad18` | 旧原文同字节 | `nopee=%d` |
| `005dad18` | `005dad28` | 旧原文同字节 | `og: 60 CF muutos: %d` |
| `005dad30` | `005dad40` | 旧原文同字节 | `og: 60 MF muutos: %d` |
| `005dad48` | `005dad58` | 旧原文同字节 | `og: 60 MS muutos: %d` |
| `005dad60` | `005dad70` | 旧原文同字节 | `og: 60 CS muutos: %d` |
| `005dae74` | `005dae84` | 旧原文同字节 | `data, sotu: %d` |
| `005dae84` | `005dae94` | 旧原文同字节 | `rel:%d` |
| `005daea8` | `005daeb8` | 旧原文同字节 | `sup %d,%d` |
| `005daebc` | `005daecc` | 旧原文同字节 | `Methaltij: %d` |
| `005daecc` | `005daedc` | 旧原文同字节 | `Vesjhaltij: %d` |
| `005daedc` | `005daeec` | 旧原文同字节 | `Global Methaltij: %d` |
| `005daef4` | `005daf04` | 旧原文同字节 | `Global Vesjhaltij: %d` |
| `005daf0c` | `005daf1c` | 旧原文同字节 | `supercounter: %d` |
| `005daf24` | `005daf34` | 旧原文同字节 | `rcpos[%d] = %d(%s)` |
| `005daf38` | `005daf48` | 旧原文同字节 | ` Data ref: %d` |
| `005daf7c` | `005daf8c` | 旧原文同字节 | `%s AgeInMonths: %d` |
| `005daff4` | `005db004` | 旧原文同字节 | `Cre Sotu %d` |
| `005db184` | `005db194` | 旧原文同字节 | `ZoomExtras used: %d / %d` |
| `005db1d0` | `005db1e0` | 旧原文同字节 | `dead: %d alive: %d met: %d` |
| `005db220` | `005db230` | 旧原文同字节 | `canreach: %d` |
| `005db2a8` | `005db2b8` | 旧原文同字节 | `Growing %s` |
| `005db2b4` | `005db2c4` | 旧原文同字节 | `Wintering %s` |
| `005db2c4` | `005db2d4` | 旧原文同字节 | `Harvested %s` |
| `005db344` | `005db354` | 旧原文同字节 | `#%d pstack D:%d` |
| `005db3a8` | `005db3b8` | 旧原文同字节 | `Creating quest for this soc area: %d` |
| `005db3d8` | `005db3e8` | 旧原文同字节 | `%d,%d spotloc: %d` |
| `005db3f8` | `005db408` | 旧原文同字节 | `Socarea: %d` |
| `005db404` | `005db414` | 旧原文同字节 | `credit: %.2f` |
| `005db414` | `005db424` | 旧原文同字节 | `soccenter: %d` |
| `005db424` | `005db434` | 旧原文同字节 | `EMBARGO nfs: %d reset: %d` |
| `005db440` | `005db450` | 旧原文同字节 | `GENEROSITY: %.2f` |
| `005db454` | `005db464` | 旧原文同字节 | `#everdebt: %.2f generosity: %.2f` |
| `005db478` | `005db488` | 旧原文同字节 | `socfam: %d` |
| `005db484` | `005db494` | 旧原文同字节 | `population: %d` |
| `005db494` | `005db4a4` | 旧原文同字节 | `lastday: %d meets: %d meetgap: %d` |
| `005db4b8` | `005db4c8` | 旧原文同字节 | `suspicion: %d` |
| `005db4c8` | `005db4d8` | 旧原文同字节 | `soc isox,y: %d,%d` |
| `005db4dc` | `005db4ec` | 旧原文同字节 | `theft: %d` |
| `005db4e8` | `005db4f8` | 旧原文同字节 | `murder: %d` |
| `005db4f4` | `005db504` | 旧原文同字节 | `violence: %d` |
| `005db504` | `005db514` | 旧原文同字节 | `trade: %d %s` |
| `005db514` | `005db524` | 旧原文同字节 | `steal: %d %s` |
| `005db524` | `005db534` | 旧原文同字节 | `mischief: %d %s` |
| `005db534` | `005db544` | 旧原文同字节 | `help: %d %s` |
| `005db5d0` | `005db5e0` | 旧原文同字节 | `queststruct: %d` |
| `005db5e0` | `005db5f0` | 旧原文同字节 | `QUALIST: %d` |
| `005db5ec` | `005db5fc` | 旧原文同字节 | `zx,zy:%d,%d zrx,zry:%d,%d` |
| `005db608` | `005db618` | 旧原文同字节 | `Uint32: %ld Sint32: %ld` |
| `005db620` | `005db630` | 旧原文同字节 | `zoomextra %ld` |
| `005db630` | `005db640` | 旧原文同字节 | `int: %ld - unsigned int: %ld - Uint32: %ld - Uint16: %ld - Sint16: %d - short int: %ld - char: %ld` |
| `005db694` | `005db6a4` | 旧原文同字节 | `float: %ld` |
| `005db6a0` | `005db6b0` | 旧原文同字节 | `creature: %ld` |
| `005db6b0` | `005db6c0` | 旧原文同字节 | `item: %ld` |
| `005db6bc` | `005db6cc` | 旧原文同字节 | `data: %ld` |
| `005db6c8` | `005db6d8` | 旧原文同字节 | `obj: %ld` |
| `005db6d4` | `005db6e4` | 旧原文同字节 | `plr: %ld` |
| `005db6e0` | `005db6f0` | 旧原文同字节 | `vil: %ld` |
| `005db6fc` | `005db70c` | 旧原文同字节 | `a: %d b: %d` |
| `005db714` | `005db724` | 旧原文同字节 | `frz %d` |
| `005db71c` | `005db72c` | 旧原文同字节 | `nodmg %d` |
| `005db728` | `005db738` | 旧原文同字节 | `onko_taistelutilanne: %d` |
| `005db808` | `005db818` | 旧原文同字节 | `normal: %s - mock: %s` |
| `005db82c` | `005db83c` | 旧原文同字节 | `%s / %s` |
| `005db9dc` | `005db9ec` | 旧原文同字节 | `inv %d` |
| `005db9e4` | `005db9f4` | 旧原文同字节 | `vatsa: %d jano: %d energia: %d %d:%d` |
| `005dba30` | `005dba40` | 旧原文同字节 | `onkohuone og: %d` |
| `005dba44` | `005dba54` | 旧原文同字节 | `onkohuonessa koordinaatti %d` |
| `005dba64` | `005dba74` | 旧原文同字节 | `Koko: %d Lampo: %d` |
| `005dba78` | `005dba88` | 旧原文同字节 | `Huonelämpö: %d` |
| `005dba94` | `005dbaa4` | 旧原文同字节 | `Mitattu: %.2f` |
| `005dbaa8` | `005dbab8` | 旧原文同字节 | `last: %d now: %d` |
| `005dbabc` | `005dbacc` | 旧原文同字节 | `ALL_SEE: %d taeka: %s now: %d` |
| `005dbadc` | `005dbaec` | 旧原文同字节 | `W: %d now: %u` |
| `005dbaf8` | `005dbb08` | 旧原文同字节 | `PlaeyrX,Y: %d,%d ISO %d %d [%d]` |
| `005dbb18` | `005dbb28` | 旧原文同字节 | `mintick: %d` |
| `005dbb3c` | `005dbb4c` | 旧原文同字节 | `alltime: %d` |
| `005dbb48` | `005dbb58` | 旧原文同字节 | `Zoom-out loc x,y: %d,%d` |
| `005dbb60` | `005dbb70` | 旧原文同字节 | `socid: %d own:%d` |
| `005dbb74` | `005dbb84` | 旧原文同字节 | `Päiväys: %d.%d.   %d:%d` |
| `005dbb9c` | `005dbbac` | 旧原文同字节 | `Day %d Month %d` |
| `005dbbb8` | `005dbbc8` | 旧原文同字节 | `Uusi Arvo: %d` |
| `005dbbc8` | `005dbbd8` | 旧原文同字节 | `Vanha Arvo: %d` |
| `005dbbd8` | `005dbbe8` | 旧原文同字节 | `isokartta_saari: %d` |
| `005dbbec` | `005dbbfc` | 旧原文同字节 | `WordLocation: %s` |
| `005dbc00` | `005dbc10` | 旧原文同字节 | `Suolampi: %d` |
| `005dbc48` | `005dbc58` | 旧原文同字节 | `TRES %d,%d!` |
| `005dbc54` | `005dbc64` | 旧原文同字节 | `%s at %d,%d` |
| `005dbc90` | `005dbca0` | 旧原文同字节 | `#--- %d %s %d,%d` |
| `005dbca4` | `005dbcb4` | 旧原文同字节 | `%s %s (%d) (%s)` |
| `005dbcb4` | `005dbcc4` | 旧原文同字节 | `Koti %d,%d` |
| `005dbcc0` | `005dbcd0` | 旧原文同字节 | `#%d FORESTCOVER TRACKS %d,%d Activity: %d COUNT: %d` |
| `005dbcf4` | `005dbd04` | 旧原文同字节 | `!Njerpez %d,%d extra %d count %d` |
| `005dbd18` | `005dbd28` | 旧原文同字节 | `!Robber %d,%d extra %d count %d` |
| `005dbd38` | `005dbd48` | 旧原文同字节 | `entries: %d wandering: %d static: %d` |
| `005dbd60` | `005dbd70` | 旧原文同字节 | `spiritdata: %d tracks: %d items: %d avanto: %d jaatyva_avanto: %d` |
| `005dbda4` | `005dbdb4` | 旧原文同字节 | `freezeitems: %d item_in_process: %d traps: %d carcass: %d` |
| `005dbde0` | `005dbdf0` | 旧原文同字节 | `growing plants: %d wintering plants: %d harvested: %d` |
| `005dbe18` | `005dbe28` | 旧原文同字节 | `This map entries: %d` |
| `005dbe30` | `005dbe40` | 旧原文同字节 | `T:%d D:%d C:%d` |
| `005dbe84` | `005dbe94` | 旧原文同字节 | `=ocdescr: %s` |
| `005dbe94` | `005dbea4` | 旧原文同字节 | `=ekuvaus: %s` |
| `005dbea4` | `005dbeb4` | 旧原文同字节 | `Materiaali: %d` |
| `005dbeb4` | `005dbec4` | 旧原文同字节 | `A/D: %d/%d` |
| `005dbec0` | `005dbed0` | 旧原文同字节 | `MAGIC:%d` |
| `005dbecc` | `005dbedc` | 旧原文同字节 | `Ravinto: %d kcal per esine, %d kcal per lb` |
| `005dbef8` | `005dbf08` | 旧原文同字节 | `TYPE: %d SYMBOL: %d (%s) ESINE: %d B,E,P,FF: %d,%d,%d,%d Neste: %d` |
| `005dbf3c` | `005dbf4c` | 旧原文同字节 | `TILEGFX:%s` |
| `005dbf48` | `005dbf58` | 旧原文同字节 | `A/D:%d/%d` |
| `005dbf54` | `005dbf64` | 旧原文同字节 | `Prot1 %d Prot2 %d Prot3 %d` |
| `005dbf70` | `005dbf80` | 旧原文同字节 | `un_id: %d` |
| `005dbf7c` | `005dbf8c` | 旧原文同字节 | `ownerID: %d (ownflag: %d) x,y: %d,%d` |
| `005dbfa8` | `005dbfb8` | 旧原文同字节 | `Price: %.2f (= %.2f rahaa) PricePerLbs: %.6f WT: %.2f MAX_WT: %.2f` |
| `005dbfec` | `005dbffc` | 旧原文同字节 | `Long WT: %f` |
| `005dbff8` | `005dc008` | 旧原文同字节 | `octype: %d` |
| `005dc004` | `005dc014` | 旧原文同字节 | `Esinehinta: %.2f (= %.2f rahaa)` |
| `005dc024` | `005dc034` | 旧原文同字节 | `kg hinta: %.2f (= %.2f rahaa)` |
| `005dc044` | `005dc054` | 旧原文同字节 | `leashcheck: %d` |
| `005dc05c` | `005dc06c` | 旧原文同字节 | `Yrttivaikutus: %d` |
| `005dc070` | `005dc080` | 旧原文同字节 | `SPECIAL: %d Sailio: %d` |
| `005dc088` | `005dc098` | 旧原文同字节 | `SPECIAL_STATUS: %d` |
| `005dc09c` | `005dc0ac` | 旧原文同字节 | `Laatu: %d Laatumuuttuja: %d` |
| `005dc0b8` | `005dc0c8` | 旧原文同字节 | `Laatu: %d (arvo %d) tiedossa: %d` |
| `005dc0dc` | `005dc0ec` | 旧原文同字节 | ` Skill: %s Itemmatskill: %s` |
| `005dc0f8` | `005dc108` | 旧原文同字节 | `Sailio: %s (#%d) (ESINE %d)` |
| `005dc114` | `005dc124` | 旧原文同字节 | `Sailio TYPE: %d SYMBOL: %d ESINE: %d B,E,P: %d,%d,%d Neste: %d` |
| `005dc18c` | `005dc19c` | 旧原文同字节 | `DEBUG_kasveja_aina: %d` |
| `005dc2a4` | `005dc2b4` | 旧原文同字节 | `!Warning! %d streams closed!` |
| `005dca2c` | `005dca3c` | 旧原文同字节 | `Remains heat: %d` |
| `005dca84` | `005dca94` | 旧原文同字节 | `Nyt palava tuli sytytetty %d minuuttia (%d tuntia) sitten` |
| `005dcb48` | `005dcb58` | 旧原文同字节 | `Kokonaispaloaika: %d` |
| `005dcb60` | `005dcb70` | 旧原文同字节 | `firesite_lifespan: %d` |
| `005dcb78` | `005dcb88` | 旧原文同字节 | `Kokonaisajan mukainen palon keskiarvo: %.2f` |
| `005dcba4` | `005dcbb4` | 旧原文同字节 | `Vaikuttava lämpötila: %.2f` |
| `005dcbc0` | `005dcbd0` | 旧原文同字节 | `PALELTUMAKOHTAOLETUS %s` |
| `005dcbd8` | `005dcbe8` | 旧原文同字节 | `kylmapoikkeama: %d` |
| `005dcbec` | `005dcbfc` | 旧原文同字节 | `Kylmäpoikkeutettu lämpötila: %d` |
| `005dcc0c` | `005dcc1c` | 旧原文同字节 | `Lämminpoikketettu lämpötila: %d` |
| `005dcc2c` | `005dcc3c` | 旧原文同字节 | `maxrise balance: %.2f bodymod %.2f` |
| `005dcc50` | `005dcc60` | 旧原文同字节 | `maxrise: %.2f` |
| `005dcc60` | `005dcc70` | 旧原文同字节 | `PLR_Lampotila: %d bodytemp_mod: %.2f` |
| `005dcc88` | `005dcc98` | 旧原文同字节 | `%d -> %d` |
| `005dcc94` | `005dcca4` | 旧原文同字节 | `:%s` |
| `005dcc98` | `005dcca8` | 旧原文同字节 | `ARVOTTU PALELTUMAKOHTA: %s - %d` |
| `005dccb8` | `005dccc8` | 旧原文同字节 | `!Your %s feels cold.` |
| `005dccd0` | `005dcce0` | 旧原文同字节 | `minor` |
| `005dccd8` | `005dcce8` | 旧原文同字节 | `serious` |
| `005dcce0` | `005dccf0` | 旧原文同字节 | `severe` |
| `005dcce8` | `005dccf8` | 旧原文同字节 | `:You feel a %s frostbite in your %s.` |

## 显式移位集合与消费者

下表列出代码映射表的全部旧 RVA 和实际静态消费者文件。每项新 RVA 均为旧 RVA `+0x10`。

| 旧 RVA | 新 RVA | 消费者 |
| --- | --- | --- |
| `0x1A43D8` | `0x1A43E8` | `modules/adapter/windows_message_formats.inc` |
| `0x1A441C` | `0x1A442C` | `modules/adapter/windows_message_formats.inc` |
| `0x1A5230` | `0x1A5240` | `modules/adapter/windows_message_formats.inc` |
| `0x1A529C` | `0x1A52AC` | `modules/adapter/windows_message_formats.inc` |
| `0x1A52A8` | `0x1A52B8` | `modules/adapter/windows_message_formats.inc` |
| `0x1A53F4` | `0x1A5404` | `modules/adapter/windows_message_formats.inc` |
| `0x1A54E0` | `0x1A54F0` | `modules/adapter/windows_message_transfers.inc` |
| `0x1A54FC` | `0x1A550C` | `modules/adapter/windows_message_transfers.inc` |
| `0x1A569C` | `0x1A56AC` | `modules/adapter/windows_message_formats.inc` |
| `0x1A578C` | `0x1A579C` | `modules/adapter/windows_message_late_sources.inc` |
| `0x1A579C` | `0x1A57AC` | `modules/adapter/windows_message_formats.inc` |
| `0x1A57C4` | `0x1A57D4` | `modules/adapter/windows_message_formats.inc` |
| `0x1A5824` | `0x1A5834` | `modules/adapter/windows_message_formats.inc` |
| `0x1A5838` | `0x1A5848` | `modules/adapter/windows_message_formats.inc` |
| `0x1A5858` | `0x1A5868` | `modules/adapter/windows_message_formats.inc` |
| `0x1A587C` | `0x1A588C` | `modules/adapter/windows_message_formats.inc` |
| `0x1A5920` | `0x1A5930` | `modules/adapter/windows_message_formats.inc` |
| `0x1A5A0C` | `0x1A5A1C` | `modules/adapter/windows_message_formats.inc` |
| `0x1A5A30` | `0x1A5A40` | `modules/adapter/windows_message_formats.inc` |
| `0x1A5DF0` | `0x1A5E00` | `modules/adapter/windows_message_formats.inc` |
| `0x1A5E10` | `0x1A5E20` | `modules/adapter/windows_message_formats.inc` |
| `0x1A5FB0` | `0x1A5FC0` | `modules/adapter/windows_message_format_builders.inc` |
| `0x1A5FBC` | `0x1A5FCC` | `modules/adapter/windows_message_formats.inc` |
| `0x1A6004` | `0x1A6014` | `modules/adapter/windows_message_formats.inc` |
| `0x1A6010` | `0x1A6020` | `modules/adapter/windows_message_formats.inc` |
| `0x1A603C` | `0x1A604C` | `modules/adapter/windows_message_formats.inc` |
| `0x1A64DC` | `0x1A64EC` | `modules/adapter/windows_message_combat_body.inc` |
| `0x1A8A70` | `0x1A8A80` | `modules/adapter/windows_message_formats.inc` |
| `0x1A8AB4` | `0x1A8AC4` | `modules/adapter/windows_message_formats.inc` |
| `0x1A8AD0` | `0x1A8AE0` | `modules/adapter/windows_message_formats.inc` |
| `0x1A8E50` | `0x1A8E60` | `modules/adapter/windows_message_formats.inc` |
| `0x1A915C` | `0x1A916C` | `modules/adapter/windows_message_formats.inc` |
| `0x1A9D88` | `0x1A9D98` | `modules/adapter/windows_messages.inc` |
| `0x1A9D94` | `0x1A9DA4` | `modules/adapter/windows_message_display.inc` |
| `0x1A9F08` | `0x1A9F18` | `modules/adapter/windows_messages.inc` |
| `0x1A9F38` | `0x1A9F48` | `modules/adapter/windows_message_formats.inc` |
| `0x1AA14C` | `0x1AA15C` | `modules/adapter/hud_native.inc` |
| `0x1AA240` | `0x1AA250` | `modules/adapter/hud_native.inc`, `modules/adapter/native_component_binding.cpp` |
| `0x1AA314` | `0x1AA324` | `modules/adapter/native_renderer_component_binding.cpp` |
| `0x1AA764` | `0x1AA774` | `modules/adapter/windows_message_formats.inc` |
| `0x1AAD8C` | `0x1AAD9C` | `modules/adapter/windows_message_formats.inc` |
| `0x1AAF2C` | `0x1AAF3C` | `modules/adapter/windows_message_formats.inc` |
| `0x1AAF4C` | `0x1AAF5C` | `modules/adapter/windows_message_formats.inc` |
| `0x1AAF60` | `0x1AAF70` | `modules/adapter/windows_message_formats.inc` |
| `0x1AAFD4` | `0x1AAFE4` | `modules/adapter/windows_message_formats.inc` |
| `0x1AB000` | `0x1AB010` | `modules/adapter/windows_message_formats.inc` |
| `0x1AB1B0` | `0x1AB1C0` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC224` | `0x1AC234` | `modules/adapter/windows_message_format_builders.inc` |
| `0x1AC238` | `0x1AC248` | `modules/adapter/windows_message_format_builders.inc` |
| `0x1AC244` | `0x1AC254` | `modules/adapter/windows_message_format_builders.inc` |
| `0x1AC250` | `0x1AC260` | `modules/adapter/windows_message_format_builders.inc` |
| `0x1AC25C` | `0x1AC26C` | `modules/adapter/windows_message_format_builders.inc` |
| `0x1AC274` | `0x1AC284` | `modules/adapter/windows_message_format_builders.inc` |
| `0x1AC280` | `0x1AC290` | `modules/adapter/windows_message_format_builders.inc` |
| `0x1AC28C` | `0x1AC29C` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC2AC` | `0x1AC2BC` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC2CC` | `0x1AC2DC` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC2E4` | `0x1AC2F4` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC2FC` | `0x1AC30C` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC320` | `0x1AC330` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC32C` | `0x1AC33C` | `modules/adapter/windows_message_format_builders.inc` |
| `0x1AC340` | `0x1AC350` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC354` | `0x1AC364` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC378` | `0x1AC388` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC398` | `0x1AC3A8` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC3E4` | `0x1AC3F4` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC3EC` | `0x1AC3FC` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC3F4` | `0x1AC404` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC404` | `0x1AC414` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC418` | `0x1AC428` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC434` | `0x1AC444` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC44C` | `0x1AC45C` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC4A8` | `0x1AC4B8` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC4CC` | `0x1AC4DC` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC4EC` | `0x1AC4FC` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC510` | `0x1AC520` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC520` | `0x1AC530` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC53C` | `0x1AC54C` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC550` | `0x1AC560` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC5A0` | `0x1AC5B0` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC5BC` | `0x1AC5CC` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC5D4` | `0x1AC5E4` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC5DC` | `0x1AC5EC` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC5F8` | `0x1AC608` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC600` | `0x1AC610` | `modules/adapter/windows_message_formats.inc` |
| `0x1AC65C` | `0x1AC66C` | `modules/adapter/windows_message_formats.inc` |
| `0x1ACAB8` | `0x1ACAC8` | `modules/adapter/native_targets.cpp` |
| `0x1ACAD0` | `0x1ACAE0` | `modules/adapter/native_targets.cpp` |
| `0x1ACEF4` | `0x1ACF04` | `modules/adapter/windows_message_formats.inc` |
| `0x1ACF1C` | `0x1ACF2C` | `modules/adapter/windows_message_formats.inc` |
| `0x1ACF34` | `0x1ACF44` | `modules/adapter/windows_message_formats.inc` |
| `0x1ACFD4` | `0x1ACFE4` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD090` | `0x1AD0A0` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD1F0` | `0x1AD200` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD428` | `0x1AD438` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD43C` | `0x1AD44C` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD45C` | `0x1AD46C` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD494` | `0x1AD4A4` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD4B4` | `0x1AD4C4` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD6A8` | `0x1AD6B8` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD750` | `0x1AD760` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD768` | `0x1AD778` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD77C` | `0x1AD78C` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD7A8` | `0x1AD7B8` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD7D4` | `0x1AD7E4` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD808` | `0x1AD818` | `modules/adapter/windows_message_formats.inc` |
| `0x1AD840` | `0x1AD850` | `modules/adapter/windows_message_formats.inc` |
| `0x1ADAB4` | `0x1ADAC4` | `modules/adapter/windows_message_formats.inc` |
| `0x1ADAC4` | `0x1ADAD4` | `modules/adapter/windows_message_formats.inc` |
| `0x1ADCB0` | `0x1ADCC0` | `modules/adapter/windows_message_formats.inc` |
| `0x1ADCF8` | `0x1ADD08` | `modules/adapter/windows_message_formats.inc` |
| `0x1ADD1C` | `0x1ADD2C` | `modules/adapter/windows_message_formats.inc` |
| `0x1ADE5C` | `0x1ADE6C` | `modules/adapter/windows_message_formats.inc` |
| `0x1AE128` | `0x1AE138` | `modules/adapter/windows_message_formats.inc` |
| `0x1AE188` | `0x1AE198` | `modules/adapter/windows_message_format_builders.inc` |
| `0x1AE250` | `0x1AE260` | `modules/adapter/windows_message_formats.inc` |
| `0x1AE78C` | `0x1AE79C` | `modules/adapter/windows_message_formats.inc` |
| `0x1AE7B0` | `0x1AE7C0` | `modules/adapter/windows_message_formats.inc` |
| `0x1AE7F0` | `0x1AE800` | `modules/adapter/windows_message_formats.inc` |
| `0x1AEAC0` | `0x1AEAD0` | `modules/adapter/windows_message_formats.inc` |
| `0x1AEEB8` | `0x1AEEC8` | `modules/adapter/windows_message_formats.inc` |
| `0x1AEEE4` | `0x1AEEF4` | `modules/adapter/windows_message_formats.inc` |
| `0x1AEFA4` | `0x1AEFB4` | `modules/adapter/windows_message_formats.inc` |
| `0x1AEFC8` | `0x1AEFD8` | `modules/adapter/windows_message_formats.inc` |
| `0x1AEFE0` | `0x1AEFF0` | `modules/adapter/windows_message_formats.inc` |
| `0x1AEFF0` | `0x1AF000` | `modules/adapter/windows_message_formats.inc` |
| `0x1AF124` | `0x1AF134` | `modules/adapter/windows_message_helpers.inc` |
| `0x1B0140` | `0x1B0150` | `modules/adapter/windows_message_formats.inc` |
| `0x1B0438` | `0x1B0448` | `modules/adapter/windows_message_combat_body.inc` |
| `0x1B05FC` | `0x1B060C` | `modules/adapter/windows_message_formats.inc` |
| `0x1B060C` | `0x1B061C` | `modules/adapter/windows_message_formats.inc` |
| `0x1B0668` | `0x1B0678` | `modules/adapter/windows_message_formats.inc` |
| `0x1B08AC` | `0x1B08BC` | `modules/adapter/windows_message_formats.inc` |
| `0x1B096C` | `0x1B097C` | `modules/adapter/windows_message_formats.inc` |
| `0x1B098C` | `0x1B099C` | `modules/adapter/windows_message_formats.inc` |
| `0x1B09B0` | `0x1B09C0` | `modules/adapter/windows_message_formats.inc` |
| `0x1B09CC` | `0x1B09DC` | `modules/adapter/windows_message_formats.inc` |
| `0x1B0A00` | `0x1B0A10` | `modules/adapter/windows_message_formats.inc` |
| `0x1B0A1C` | `0x1B0A2C` | `modules/adapter/windows_message_formats.inc` |
| `0x1B0A48` | `0x1B0A58` | `modules/adapter/windows_message_formats.inc` |
| `0x1B0B9C` | `0x1B0BAC` | `modules/adapter/windows_message_formats.inc` |
| `0x1B0BBC` | `0x1B0BCC` | `modules/adapter/windows_message_formats.inc` |
| `0x1B0C40` | `0x1B0C50` | `modules/adapter/windows_message_formats.inc` |
| `0x1B0C50` | `0x1B0C60` | `modules/adapter/windows_message_formats.inc` |
| `0x1B0CFC` | `0x1B0D0C` | `modules/adapter/windows_message_formats.inc` |
| `0x1B0F80` | `0x1B0F90` | `modules/adapter/windows_message_formats.inc` |
| `0x1B0FA4` | `0x1B0FB4` | `modules/adapter/windows_message_formats.inc` |
| `0x1B101C` | `0x1B102C` | `modules/adapter/windows_message_formats.inc` |
| `0x1B1090` | `0x1B10A0` | `modules/adapter/windows_message_formats.inc` |
| `0x1B10E8` | `0x1B10F8` | `modules/adapter/windows_message_formats.inc` |
| `0x1B10F8` | `0x1B1108` | `modules/adapter/windows_message_formats.inc` |
| `0x1B1108` | `0x1B1118` | `modules/adapter/windows_message_formats.inc` |
| `0x1B1138` | `0x1B1148` | `modules/adapter/windows_message_formats.inc` |
| `0x1B1154` | `0x1B1164` | `modules/adapter/windows_message_formats.inc` |
| `0x1B116C` | `0x1B117C` | `modules/adapter/windows_message_formats.inc` |
| `0x1B1180` | `0x1B1190` | `modules/adapter/windows_message_formats.inc` |
| `0x1B119C` | `0x1B11AC` | `modules/adapter/windows_message_formats.inc` |
| `0x1B11C4` | `0x1B11D4` | `modules/adapter/windows_message_formats.inc` |
| `0x1B11E8` | `0x1B11F8` | `modules/adapter/windows_message_formats.inc` |
| `0x1B13A4` | `0x1B13B4` | `modules/adapter/windows_message_formats.inc` |
| `0x1B13F4` | `0x1B1404` | `modules/adapter/windows_message_formats.inc` |
| `0x1B1434` | `0x1B1444` | `modules/adapter/windows_message_formats.inc` |
| `0x1B1488` | `0x1B1498` | `modules/adapter/windows_message_formats.inc` |
| `0x1B3B20` | `0x1B3B30` | `modules/adapter/windows_message_formats.inc` |
| `0x1B62A4` | `0x1B62B4` | `modules/adapter/windows_message_formats.inc` |
| `0x1B6B60` | `0x1B6B70` | `modules/adapter/windows_message_formats.inc` |
| `0x1B6B98` | `0x1B6BA8` | `modules/adapter/windows_message_formats.inc` |
| `0x1B6C80` | `0x1B6C90` | `modules/adapter/windows_message_formats.inc` |
| `0x1CC660` | `0x1CC670` | `modules/adapter/windows_message_formats.inc` |
| `0x1CC698` | `0x1CC6A8` | `modules/adapter/windows_message_formats.inc` |
| `0x1CC808` | `0x1CC818` | `modules/adapter/windows_message_formats.inc` |
| `0x1D80DC` | `0x1D80EC` | `modules/adapter/windows_message_formats.inc` |
| `0x1D8104` | `0x1D8114` | `modules/adapter/windows_message_formats.inc` |
| `0x1D8188` | `0x1D8198` | `modules/adapter/windows_message_formats.inc` |
| `0x1D8258` | `0x1D8268` | `modules/adapter/windows_message_formats.inc` |
| `0x1D8288` | `0x1D8298` | `modules/adapter/windows_message_value_chains.inc` |
| `0x1D88C4` | `0x1D88D4` | `modules/adapter/windows_message_formats.inc` |
| `0x1D9050` | `0x1D9060` | `modules/adapter/windows_message_formats.inc` |
| `0x1D90A8` | `0x1D90B8` | `modules/adapter/windows_message_formats.inc` |
| `0x1D91F8` | `0x1D9208` | `modules/adapter/windows_message_formats.inc` |
| `0x1D9328` | `0x1D9338` | `modules/adapter/windows_message_formats.inc` |
| `0x1D9398` | `0x1D93A8` | `modules/adapter/windows_message_formats.inc` |
| `0x1D93BC` | `0x1D93CC` | `modules/adapter/windows_message_formats.inc` |
| `0x1D93D8` | `0x1D93E8` | `modules/adapter/windows_message_formats.inc` |
| `0x1D9584` | `0x1D9594` | `modules/adapter/windows_message_formats.inc` |
| `0x1D95BC` | `0x1D95CC` | `modules/adapter/windows_message_formats.inc` |
| `0x1D9714` | `0x1D9724` | `modules/adapter/windows_message_formats.inc` |
| `0x1D98CC` | `0x1D98DC` | `modules/adapter/windows_message_formats.inc` |
| `0x1D9974` | `0x1D9984` | `modules/adapter/windows_message_formats.inc` |
| `0x1D99B0` | `0x1D99C0` | `modules/adapter/windows_message_formats.inc` |
| `0x1D99DC` | `0x1D99EC` | `modules/adapter/windows_message_formats.inc` |
| `0x1D99E8` | `0x1D99F8` | `modules/adapter/windows_message_formats.inc` |
| `0x1D99FC` | `0x1D9A0C` | `modules/adapter/windows_message_formats.inc` |
| `0x1D9A0C` | `0x1D9A1C` | `modules/adapter/windows_message_formats.inc` |
| `0x1D9B48` | `0x1D9B58` | `modules/adapter/windows_message_formats.inc` |
| `0x1D9B54` | `0x1D9B64` | `modules/adapter/windows_message_formats.inc` |
| `0x1D9DE4` | `0x1D9DF4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA3D8` | `0x1DA3E8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA3F8` | `0x1DA408` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA448` | `0x1DA458` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA468` | `0x1DA478` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA514` | `0x1DA524` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA52C` | `0x1DA53C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA54C` | `0x1DA55C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA560` | `0x1DA570` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA578` | `0x1DA588` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA590` | `0x1DA5A0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA5A8` | `0x1DA5B8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA5C8` | `0x1DA5D8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA5DC` | `0x1DA5EC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA608` | `0x1DA618` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA618` | `0x1DA628` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA644` | `0x1DA654` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA674` | `0x1DA684` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA698` | `0x1DA6A8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA6B0` | `0x1DA6C0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA6D8` | `0x1DA6E8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA6FC` | `0x1DA70C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA710` | `0x1DA720` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA7C4` | `0x1DA7D4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA800` | `0x1DA810` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA840` | `0x1DA850` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA868` | `0x1DA878` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA86C` | `0x1DA87C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA8EC` | `0x1DA8FC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA920` | `0x1DA930` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA96C` | `0x1DA97C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA97C` | `0x1DA98C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA9C4` | `0x1DA9D4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DA9F8` | `0x1DAA08` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAA08` | `0x1DAA18` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAA14` | `0x1DAA24` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAA4C` | `0x1DAA5C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAA74` | `0x1DAA84` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAA80` | `0x1DAA90` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAA9C` | `0x1DAAAC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAB04` | `0x1DAB14` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAB28` | `0x1DAB38` | `modules/adapter/windows_message_formats.inc` |
| `0x1DABDC` | `0x1DABEC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAC08` | `0x1DAC18` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAC3C` | `0x1DAC4C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DACA4` | `0x1DACB4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DACC4` | `0x1DACD4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DACE4` | `0x1DACF4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAD08` | `0x1DAD18` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAD18` | `0x1DAD28` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAD30` | `0x1DAD40` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAD48` | `0x1DAD58` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAD60` | `0x1DAD70` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAE74` | `0x1DAE84` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAE84` | `0x1DAE94` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAEA8` | `0x1DAEB8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAEBC` | `0x1DAECC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAECC` | `0x1DAEDC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAEDC` | `0x1DAEEC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAEF4` | `0x1DAF04` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAF0C` | `0x1DAF1C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAF24` | `0x1DAF34` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAF38` | `0x1DAF48` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAF7C` | `0x1DAF8C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DAFF4` | `0x1DB004` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB184` | `0x1DB194` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB1D0` | `0x1DB1E0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB220` | `0x1DB230` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB2A8` | `0x1DB2B8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB2B4` | `0x1DB2C4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB2C4` | `0x1DB2D4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB344` | `0x1DB354` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB3A8` | `0x1DB3B8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB3D8` | `0x1DB3E8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB3F8` | `0x1DB408` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB404` | `0x1DB414` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB414` | `0x1DB424` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB424` | `0x1DB434` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB440` | `0x1DB450` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB454` | `0x1DB464` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB478` | `0x1DB488` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB484` | `0x1DB494` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB494` | `0x1DB4A4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB4B8` | `0x1DB4C8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB4C8` | `0x1DB4D8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB4DC` | `0x1DB4EC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB4E8` | `0x1DB4F8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB4F4` | `0x1DB504` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB504` | `0x1DB514` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB514` | `0x1DB524` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB524` | `0x1DB534` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB534` | `0x1DB544` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB5D0` | `0x1DB5E0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB5E0` | `0x1DB5F0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB5EC` | `0x1DB5FC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB608` | `0x1DB618` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB620` | `0x1DB630` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB630` | `0x1DB640` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB694` | `0x1DB6A4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB6A0` | `0x1DB6B0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB6B0` | `0x1DB6C0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB6BC` | `0x1DB6CC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB6C8` | `0x1DB6D8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB6D4` | `0x1DB6E4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB6E0` | `0x1DB6F0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB6FC` | `0x1DB70C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB714` | `0x1DB724` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB71C` | `0x1DB72C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB728` | `0x1DB738` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB808` | `0x1DB818` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB82C` | `0x1DB83C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB9DC` | `0x1DB9EC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DB9E4` | `0x1DB9F4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBA30` | `0x1DBA40` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBA44` | `0x1DBA54` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBA64` | `0x1DBA74` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBA78` | `0x1DBA88` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBA94` | `0x1DBAA4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBAA8` | `0x1DBAB8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBABC` | `0x1DBACC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBADC` | `0x1DBAEC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBAF8` | `0x1DBB08` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBB18` | `0x1DBB28` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBB3C` | `0x1DBB4C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBB48` | `0x1DBB58` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBB60` | `0x1DBB70` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBB74` | `0x1DBB84` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBB9C` | `0x1DBBAC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBBB8` | `0x1DBBC8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBBC8` | `0x1DBBD8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBBD8` | `0x1DBBE8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBBEC` | `0x1DBBFC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBC00` | `0x1DBC10` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBC48` | `0x1DBC58` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBC54` | `0x1DBC64` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBC90` | `0x1DBCA0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBCA4` | `0x1DBCB4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBCB4` | `0x1DBCC4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBCC0` | `0x1DBCD0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBCF4` | `0x1DBD04` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBD18` | `0x1DBD28` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBD38` | `0x1DBD48` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBD60` | `0x1DBD70` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBDA4` | `0x1DBDB4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBDE0` | `0x1DBDF0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBE18` | `0x1DBE28` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBE30` | `0x1DBE40` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBE84` | `0x1DBE94` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBE94` | `0x1DBEA4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBEA4` | `0x1DBEB4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBEB4` | `0x1DBEC4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBEC0` | `0x1DBED0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBECC` | `0x1DBEDC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBEF8` | `0x1DBF08` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBF3C` | `0x1DBF4C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBF48` | `0x1DBF58` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBF54` | `0x1DBF64` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBF70` | `0x1DBF80` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBF7C` | `0x1DBF8C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBFA8` | `0x1DBFB8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBFEC` | `0x1DBFFC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DBFF8` | `0x1DC008` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC004` | `0x1DC014` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC024` | `0x1DC034` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC044` | `0x1DC054` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC05C` | `0x1DC06C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC070` | `0x1DC080` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC088` | `0x1DC098` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC09C` | `0x1DC0AC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC0B8` | `0x1DC0C8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC0DC` | `0x1DC0EC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC0F8` | `0x1DC108` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC114` | `0x1DC124` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC18C` | `0x1DC19C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DC2A4` | `0x1DC2B4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCA2C` | `0x1DCA3C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCA84` | `0x1DCA94` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCB48` | `0x1DCB58` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCB60` | `0x1DCB70` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCB78` | `0x1DCB88` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCBA4` | `0x1DCBB4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCBC0` | `0x1DCBD0` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCBD8` | `0x1DCBE8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCBEC` | `0x1DCBFC` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCC0C` | `0x1DCC1C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCC2C` | `0x1DCC3C` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCC50` | `0x1DCC60` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCC60` | `0x1DCC70` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCC88` | `0x1DCC98` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCC94` | `0x1DCCA4` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCC98` | `0x1DCCA8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCCB8` | `0x1DCCC8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCCE8` | `0x1DCCF8` | `modules/adapter/windows_message_formats.inc` |
| `0x1DCF60` | `0x1DCF70` | `modules/adapter/windows_message_weather.inc` |
| `0x1DCF88` | `0x1DCF98` | `modules/adapter/windows_message_weather.inc` |
| `0x1DCFB4` | `0x1DCFC4` | `modules/adapter/windows_message_weather.inc` |
| `0x1DDAB0` | `0x1DDAC0` | `modules/adapter/native_renderer_component_binding.cpp`, `modules/adapter/native_root_component.cpp` |

本记录只支持列明的外置资源、数据地址及语义 key 复用，不代替原生调用位置、参数 ABI、字形绘制生命周期的独立静态审查，也不宣称编译、正式发布或运行验收完成。
