# 不真实的世界 3.89.1 Windows 原生 CALL 边界静态复核

日期：2026-11-10。仅只读分析磁盘 PE 与项目源码；不启动游戏、启动器或 DLL，不注入、不模拟输入、不执行或编写测试，不添加断言。

## 对象与方法

安装目录：`/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld`。当前 `urw.exe` 为 PE32 / I386，首选基址 `0x400000`，SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`；Steam 清单为 Build `26139145`，安装包 `news.txt` 为 3.89.1。旧适配对象为 3.89 / Build `25939378`，SHA-256 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。

根据 PE 节表把 RVA 换算为磁盘偏移。只读提取 Windows adapter 中 `call`、`native_call` 和直接构造 `HookKind::call` 的字面站点；按照各注册循环的真实目标展开消息、菜单、设置、制作角色、百科、HUD、原生图像等 CALL 表；以源声明的 `E8 + (target-site-5)` 对照新文件中的五个原始字节。随后使用离线 objdump 阅读变化处周围指令，不运行分析对象。临时解析过程没有保存为测试或分析脚本。

共展开 2532 条源声明记录，按物理 RVA 去重为 2513 个站点。2509 个站点与旧声明字节一致，4 个站点发生以下确定变化。这仅证明 CALL 站点与目标关系，不能证明所有被调函数内部实现或全部数据地址不变。

## 四个确定迁移的 CALL

| 语义来源 | 旧 RVA | 3.89.1 RVA | 目标 RVA | 新文件 CALL 字节 |
| --- | --- | --- | --- | --- |
| lowercase / item descriptor | `0xBC7A9` | `0xBC7B9` | `0xD4020` | `E8 62 78 01 00` |
| lowercase | `0xBCD46` | `0xBCD56` | `0xD4020` | `E8 C5 72 01 00` |
| tree | `0xBEB63` | `0xBEB73` | `0x15E2C0` | `E8 48 F7 09 00` |
| silhouette | `0xBEEE2` | `0xBEEF2` | `0xAE3F0` | `E8 F9 F4 FE FF` |

四处均为新文件原始指令证据，不能通过对任意地址统一加 `0x10` 外推。`0xBC7B4` 计算 `[EBX+9]`，`0xBC7B7` 将其送入 ECX，`0xBC7B9` 再调用原 `D4020`，与已有 item descriptor 语义相符。`0xBEB71` 保持 ECX=EBX，调用原树描述入口 `15E2C0`。`0xBEEF2` 前保留原结构按值复制和 ECX=1，调用原轮廓描述入口 `AE3F0`。

源码修改位于 `modules/adapter/windows_message_values.inc` 的 `physical_call_site` 和 `append_hooks`：依据 `windows_build::is_3891()` 仅映射上述四个物理 hook 站点，旧构建仍使用原站点。`sites[]` 继续作为语义来源元数据，dispatch 仍经 `event.id` 取得原条目，所以 `transform_domain` 中的 `case 0xBC7A9` 必须保留；它描述原有语义条目，并非执行地址。`prepare_input`、`observe_value`、`prepare_chain_call` 等既有消费方也继续看到相同的语义身份。

全 Windows adapter 源码对 `0xBC000..0xBEFFF` 字面地址搜索仅命中这四个来源条目、这一语义 case 和新增物理映射；未发现另外的硬编码 resume RVA 或直接函数调用需要随本段一起迁移。

## 站点覆盖明细

以下为源声明展开数量，包含表中原有重复站点。`hud_value_calls` 按真实注册循环只展开前十项；后六项 penalty 入口由对应已有 hook 注册。原生图像只展开 `fields` 中十个独立 hook，footer_logo 已由主表注册。

```text
literal calls 316
windows_message_formats.inc:entries 929
windows_message_value_builders.inc:value_formats 72
windows_message_values.inc:sites 530
windows_message_menu_echo.inc:sources 186
windows_message_geography.inc:sites 122
windows_message_value_chains.inc:part_calls 10
windows_creation.inc:creation_text_calls 46
setup_text_calls.h:setup_text_calls 27
credits_text_calls.h:credits_text_calls 24
hud_native.inc:hud_surface_calls 14
hud_native.inc:hud_center_calls 6
windows_profile_extras.inc:windows_attribute_panels 4
windows_profile_extras.inc:windows_attribute_labels 11
native_component_binding.cpp:hud_value_calls 10
windows_message_helpers.inc:tiers 5
windows_message_menu_echo.inc:titles 35
windows_renderer_text.inc:renderer_leaves 5
windows_message_calendar.inc:date_calls 6
windows_message_format_builders.inc:stores 5
windows_message_format_builders.inc:craft_menu_names 3
windows_message_menu_return.inc:row_calls 7
windows_creation.inc:creation_paragraph_calls 4
windows_encyclopedia.inc:reads 3
windows_encyclopedia.inc:nav 4
windows_encyclopedia.inc:intro 10
windows_encyclopedia.inc:preview 2
windows_skills_spells.inc:panels 3
windows_skills_spells.inc:help 3
windows_skills_spells.inc:paragraphs 3
hud_native.inc:penalties 5
native_component_binding.cpp:status_calls 10
native_component_binding.cpp:summary_calls 5
windows_culture_map_calls software 11
windows_culture_map_calls renderer 11
confirmations 4
debug sources 9
windows_message_items.inc:local Site 16
windows_message_calendar.inc:local Call 9
windows_message_geography.inc:local Format 13
windows_message_menu_echo.inc:local Call 21
direct HookSpec call 3
native_image_component fields 10
TOTAL 2532 UNIQUE 2513 DIFFERENCES 4
```

## 数据与 inline 边界

另外只读提取 `windows_message*.inc`、`windows_messages.inc`、`native_name_input.inc` 中 202 条显式 RVA 的 `instruction` 字节模板，其所有非零模板字节与新 PE 原址一致，未见额外的指令形状或物理站点变化。许多模板用零占位后再填绝对操作数，因此本项没有把零占位当成匹配依据，不能解读为 202 条完整指令字节均未变化；完整绝对操作数由数据映射与对应原生边界复核处理。

本记录没有将 CALL 对照结果当作放行新文件指纹的充分条件。新构建的只读数据存在地址移动；原生 inline 指令中的绝对地址、各类 format / literal / catalog 键，以及直接按 RVA 取原文的源身份，须由对应数据和原生组件复核记录确认并整改。整个旧 PE 和完整旧 `.text` 原字节当前不在本工作目录的本地静态材料中，本记录不声称整个 `.text` 或整个 PE 不变。

静态复审新的 `windows_build.h` / `module.cpp` 接入：在 adapter 设置 `host` 后、所有原生组件初始化及 HookSpec 构建前读取确定的新版本字符串；`at` 仅将旧逻辑数据地址转成已枚举的新物理数据地址，`ptr` 对真实原生绝对地址的解引用保持原语义。这个边界没有增加布局、绘制、缓存或输入生命周期。`physical_call_site` 只改变四条 CALL 的安装地址，`sites[]`、hook ID、producer target、寄存器及参数读取保持原有语义。离散二分映射表必须排序去重，并包含实际传入值，例如 `at<char>(0x193D4C+3)` 对应 `0x193D4F`，不能只登记字符串起始地址。该数据表由对应资源复核记录完成后才能确认其最终覆盖。

## 全部零槽差异的逐条精核

在 202 条显式站点模板内继续逐字节比较，包含每个固定零字节：164 条与新文件完全一致；38 条模板与新文件存在差异。下表逐条指出模板的源行、随后 `memcpy` 的源行及四字节填充位置。38 条的每一个差异字节均落在明确的四字节填充范围内，没有把任何固定零字节或未知动态字节忽略。

依照当前 `windows_3891_rdata.inc` 的 393 个离散旧 RVA、`rdata_rva` 的真实规则及首选加载基址 `0x400000`，重建这 38 条完整期望字节，与新 PE 原址全部逐字节一致。映射表静态计数为 393 项，严格排序且无重复。其中 33 条填充地址保持旧值；5 条填充地址移动，涉及四个旧 RVA：`1A54E0`、`1A54FC`、`1A9F08`、`1A9D88`（最后一个由两个站点消费）。未发现未解释的零槽差异，也未发现固定低字节 `00` 变为 `10` 的漏改。该结论仅覆盖本节列明的 202 条显式站点模板；其余循环生成模板由原生组件及资源复核记录覆盖。

源文件均位于 `modules/adapter/`，行号取本轮静态读取时的源码。偏移从对应 instruction 模板开头按零计数，全部填充长度为四字节。

| 模板源码 | memcpy 行 | 站点 RVA | 填充偏移 | 旧数据 RVA → 新数据 RVA |
| --- | --- | --- | --- | --- |
| `native_name_input.inc:103` | 105 | `0x10f7fb` | 2 | `0xa49b9a8` → `0xa49b9a8` |
| `native_name_input.inc:118` | 120 | `0xd3e00` | 3 | `0x5f54bc0` → `0x5f54bc0` |
| `windows_message_value_copies.inc:30` | 31 | `0x130303` | 1 | `0xa211b78` → `0xa211b78` |
| `windows_message_value_copies.inc:33` | 34 | `0x1304e8` | 1 | `0xa2122e8` → `0xa2122e8` |
| `windows_message_calendar.inc:62` | 63 | `0x8a474` | 1 | `0x19cf94` → `0x19cf94` |
| `windows_message_calendar.inc:66` | 67 | `0x8e68a` | 1 | `0x19d368` → `0x19d368` |
| `windows_message_transfers.inc:55` | 57 | `0x32ba` | 2 | `0x18c8c0` → `0x18c8c0` |
| `windows_message_transfers.inc:65` | 67 | `0xd7d93` | 1 | `0x1a54e0` → `0x1a54f0` |
| `windows_message_transfers.inc:68` | 70 | `0xd7daa` | 1 | `0x1a54fc` → `0x1a550c` |
| `windows_message_hearing.inc:16` | 18 | `0xfdecd` | 1 | `0xa40eb70` → `0xa40eb70` |
| `windows_message_hearing.inc:24` | 25 | `0xfe1a7` | 1 | `0xa40eb70` → `0xa40eb70` |
| `windows_message_resources.inc:113` | 115 | `0x161e74` | 1 | `0xa224eb0` → `0xa224eb0` |
| `windows_message_resources.inc:127` | 129 | `0x16116a` | 2 | `0xa2d0497` → `0xa2d0497` |
| `windows_message_resources.inc:132` | 134 | `0x161281` | 1 | `0xa2248b8` → `0xa2248b8` |
| `windows_messages.inc:192` | 194 | `0xf65e8` | 1 | `0x1a9f08` → `0x1a9f18` |
| `windows_messages.inc:195` | 197 | `0xf6a45` | 1 | `0x61a84b8` → `0x61a84b8` |
| `windows_messages.inc:198` | 200 | `0xf6d8a` | 5 | `0xa3840e8` → `0xa3840e8` |
| `windows_messages.inc:203` | 205 | `0xf6e09` | 2 | `0x61a84b7` → `0x61a84b7` |
| `windows_messages.inc:224` | 225 | `0xf67c3` | 3 | `0x61a84b8` → `0x61a84b8` |
| `windows_messages.inc:226` | 227 | `0xf67dd` | 4 | `0x5f5ae66` → `0x5f5ae66` |
| `windows_messages.inc:228` | 229 | `0xf5b7f` | 4 | `0x1a9d88` → `0x1a9d98` |
| `windows_messages.inc:230` | 231 | `0xf5c13` | 5 | `0xa211068` → `0xa211068` |
| `windows_messages.inc:233` | 234 | `0xf5c31` | 1 | `0x1a9d88` → `0x1a9d98` |
| `windows_messages.inc:235` | 236 | `0xf6164` | 1 | `0x61a968c` → `0x61a968c` |
| `windows_messages.inc:237` | 238 | `0xfa347` | 2 | `0x478e0e9` → `0x478e0e9` |
| `windows_message_format_builders.inc:98` | 100 | `0x633de` | 1 | `0x1d308e0` → `0x1d308e0` |
| `windows_message_format_builders.inc:105` | 107 | `0x167a1f` | 1 | `0x1940d4` → `0x1940d4` |
| `windows_message_format_builders.inc:108` | 110 | `0x167ac2` | 1 | `0x1a0328` → `0x1a0328` |
| `windows_message_format_builders.inc:134` | 137 | `0x3710f` | 1 | `0x27d521` → `0x27d521` |
| `windows_message_format_builders.inc:135` | 137 | `0x37177` | 1 | `0x27d521` → `0x27d521` |
| `windows_message_combat_body.inc:44` | 46 | `0x127060` | 2 | `0xa211b78` → `0xa211b78` |
| `windows_message_combat_body.inc:47` | 49 | `0x127b30` | 3 | `0x4d8f4f2` → `0x4d8f4f2` |
| `windows_message_display.inc:19` | 21 | `0xf6cb8` | 1 | `0x61a8cb8` → `0x61a8cb8` |
| `windows_message_menu_echo.inc:508` | 509 | `0xffaa1` | 1 | `0x619fa50` → `0x619fa50` |
| `windows_message_menu_echo.inc:528` | 529 | `0x4313d` | 1 | `0x1964f4` → `0x1964f4` |
| `windows_message_menu_echo.inc:530` | 531 | `0x431de` | 2 | `0x18c350` → `0x18c350` |
| `windows_message_menu_echo.inc:532` | 533 | `0x42fa4` | 1 | `0x1964e0` → `0x1964e0` |
| `windows_message_helpers.inc:54` | 56 | `0x17afc0` | 1 | `0xa32b055` → `0xa32b055` |


## 剩余注册 helper 族的完整静态核对

补齐此前 202 条显式 `instruction` 范围以外的 helper：依注册循环展开所有条目，按源码的堆栈位移、动态 opcode/mode/value、绝对操作数和现有离散数据映射重建完整期望字节。新增覆盖 488 个唯一原生站点，488 个站点全部完整字节吻合新 PE，没有使用忽略零字节的比较。

最初 53 条 `inline_hook` 中 39 条字面模板完全相同、14 条存在地址占位；本次逐条恢复全部 14 处真实绝对值后，53 条全部吻合。另外覆盖百科 5 条间接字符串边界、renderer_text 11 条组件度量边界，以及全部以下消息辅助器、循环或表生成模板。488 个站点内部无重复；它们不属于之前 202 条显式 `instruction` 的站点范围。原生组件自身的独立复核见对应原生边界记录，本节不重复其已完成部分。

| 本次补齐的 helper 族 | 站点数 |
| --- | --- |
| literal inline_hook | 53 |
| renderer_text instruction | 11 |
| encyclopedia loop inline_hook | 5 |
| message absolute opcode | 15 |
| requirement literal | 4 |
| message absolute/operand | 58 |
| transfer stack | 8 |
| treatment loop | 7 |
| combat append | 24 |
| transfer resource | 6 |
| transfer selected copies | 9 |
| combat copies | 23 |
| combat punctuation | 6 |
| combat record copies | 10 |
| unit append | 9 |
| menu echo clips | 103 |
| menu return clips | 7 |
| counter writers | 109 |
| transfer literal | 2 |
| transfer period | 3 |
| quest record close | 2 |
| material literals | 2 |
| name input stop | 3 |
| transfer append pairs | 4 |
| audit copy pairs | 2 |
| name input erase pairs | 3 |
| 合计（唯一站点） | 488 |

本次补齐范围内没有尚未确认的注册 helper 字节、占位填充或固定零字节差异。结合前述 CALL 边界对照，四条 CALL 迁移已明确；数据源地址覆盖另见 [资源静态复核](20261110-windows-3891-resources.md)。本记录不把这些接入点字节相同外推成全部被调函数内部、整个业务或整个 PE 内容相同；也不宣称运行、画面或游戏交互验收。


本文件及四站点修改属于源码和静态证据交付；编译、正式文件发布和运行状态由主任务另行记录。

