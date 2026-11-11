# NPC 对话界面的完整文本来源与原生接入

2026-11-11 用户后续截图确认本批显示仍有错误：自我介绍残留参数标记，告别／返回漏译。此前“补齐”的交付结论不充分；原因和后续修正见[显示错误修正记录](20261111-conversation-display-correction.md)。下文首批交接保留为历史回执，不能据其 Applied 认定画面正确。

日期：2026-11-11，Asia/Shanghai。对象：Windows x86《不真实的世界》3.89.1 / Steam Build 26139145，PE SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。本文代码地址为 RVA；提取清单、反汇编及反编译标识使用 VA，基址 `400000h`。

用户第二张截图确认：上一批仅补齐名称、标题与聊天方式菜单，NPC 问候正文、台词选项、告别及返回项仍漏译。此前标题批次的 Applied 不能证明正文已经处理。本批沿该页全部完整文本入口追溯来源，不以截图的某一句或一个智者作为词库边界。

全程仅进行原 PE、资源文件与源码的离线反编译和静态审阅；未启动、关闭、重启或操作游戏，未模拟输入，未运行测试、产物或编写测试用例、断言。正式交接仅使用用户已经授权的驻留发布事务。

## 提取闭包与分支

[conversation_AllText.java](conversation_AllText.java) 在既有 Ghidra `inventory3891/urw.exe` 工程上以 `-readOnly -noanalysis` 提取135个完整函数：`1337F0..1471C0` 的聊天代码、四个输入入口的全部调用者，以及资源选择、标签展开和身份辅助函数。真实 fastcall 参数已声明，避免把 ECX/EDX 或栈上 command 错认成可见文字。原始输出位于本地 `build/analysis/conversation-20261111/all-text-ghidra.c`；可提交的 [调用者清单](20261111-conversation-callers.tsv)、[指令文字引用清单](20261111-conversation-source-references.tsv) 保留逐点索引。引用清单包含内部命令、优化复制尾片及浮点数据候选，不将它们等同于独立台词。

另对 PE 代码节逐字节计算 E8/E9 相对目标，所得 [PE 全调用清单](20261111-conversation-pe-calls.tsv) 与 Ghidra 全引用一致：334处 E8、没有到这四个入口的 E9。它们全部进入下表的完整消费边界。

| 原生输入 | 调用点 | 对应显示消费 |
| --- | ---: | --- |
| `1339B0` NPC 整句 | 221 | `1339C6` 完整输入，原 word-flow、`133AC0/133B70` 完整词元绘制 |
| `134350` 玩家整句 | 3 | `134366` 完整输入，原 word-flow、`13443D/134495` 完整词元绘制 |
| `134C70` 台词／反应选项 | 92 | 原 command、条件、去重及编号保留，`142786` 原 Menu 行、`D031F` 完整按钮后缀消费译文 |
| `134D90` 动作结果 | 18 | mode=0 完整原句；mode=1 实际 NPC 描述＋动作；`134E75` 原段落、`134E89` 原继续按钮 |

聊天页还有2个原 Menu 构造、14个 AddMenuRow 调用、8个交易侧栏直接文本 CALL、1个顶部 Heading 和2个人物 Panel。既有名称／标题批次与本批正文、选项、侧栏及按钮共同覆盖这些消费者。空分隔行来自原构造，按键、动作值及条件均不改动。

原生分派与来源按以下族追溯，译文不参与分支选择：

- 问候及身份：一般、晨间、夜间、久别、姓名未知／已知、介绍自己、职业／技艺、文化称谓、声望、拒绝与告别。
- 问路：井、湖、洞穴、村庄、远方文化区域、智者、铁匠、具名人物；在场、背后、屋内、附近、较远及不知道位置的原分支。
- 求助／结伴：治疗、狩猎、工作、探险、护送、借用／归还装备、服务期限、报酬、到期及分开。
- 交付与交易：一般礼物／帮助／伙伴，普通物品、动物、服务、欠债与偿债；接受、拒绝、重谈、物品品质、负重、数量、余款、指定报酬及完成交易。
- 铁匠：八类原产品选项、已有订单、新订单、工期、付款、领取、超期、忙碌及原生错误台词。
- 冲突／指令：抢劫、反抗、拒绝、偷窃、财产侵犯、驱逐、命案嫌疑，NPC／动物命令及工作所需装备、环境不足的实际台词。
- 任务：正文、简介、追问、接受／拒绝／放弃、进度、交付、完成、报酬和原调试选项；包括任务中选择的角色、地点、物品、数值、口信和时间。

任务文本不能只在聊天函数周围找。继续追溯 `hud_map_AllText.java` 已完整提取的15类任务／标题构造和1个记录装载入口：采药、受伤冒险者、老人小舟、偷鸟贼、狼与女人、强盗、森林遮隐、文化护送、迷路者、物资需求、森林少女、水族、森林之灵、石头／树枝、随机标题，以及 `1574B0` 原记录读取。来源覆盖新生成及随后从原任务记录消费的正文和选项；原存档、记录字段及英文控制串保持。

[conversation_Helpers.java](conversation_Helpers.java) 另提取 `15EFF0/15F400` 单复数、`1627A0/162930` 列表、`15DFC0` 玩家完整身份、`52640/51770` 物品名、`199B0/19610` 时间、`138EA0` 选项引号、`162BD0` 冠词及 `161B00` 通用资源构造。原聊天资源选择有38个 CALL；通用资源有18个 CALL，后者包括实际用于正文的 `TIMESPAN_DAY`。`urw_chat.txt` 的79条已选资源、七个情绪槽和原默认槽保持原选择；本批接入它们展开后的完整显示语义，同时纳入 `TIMESPAN_DAY` 与 `FUZZY_NUM` 的全部原分支。

技能等级另从 `15E9F0/15EA60` 的真实 `5E9F50 + index*100` 表提取11级，以及 `skilled expert` 原分支。位置回答的 `%s` 经 `139890` 确认是 He/She 代词，已按代词翻译，不能误当作需保留原样的人名。原资源缺题台词 `1614DB/1616A3` 也是明确存在的显示分支，纳入完整句式；没有在 Mod 中新增缺源回退。

## 完整语义与词库

可审阅的源文／译文／实参类别／原始地址记录在 [conversation.zh-CN.json](../../translations/messages/conversation.zh-CN.json)，共1885条作者记录。生成入口 [generate_conversation_sources.py](../../translations/generate_conversation_sources.py) 物化2275条完整句式与语法产生式、13034个有限词值拼写、56个原生完整追加片段，首批向词库写入2269个去重语义键（后续修正为2272个，见修正记录）。最终资源为 `translations/messages_embedded/values.conversation.zh-CN.tsv` 及 `catalog/zh-CN/messages.tsv`。保存原有词库的顺序与内容，新增本批键；没有运行依赖旧 PE 地址的全量词库生成脚本。

`windows_conversation_sources.inc` 在完整原生输入处识别提取出的有限源语法，生成既有 `native_message_source::Text` 表达式，再由正式词库投影中文。完整句式匹配先确定所有原文分隔与实参，再解析实参；不是在一句英文中逐词搜索替换。实参类型来自对应构造：

- `n` 是明确的人名、村名、地区专名或原资源题名；`a` 仅匹配实际玩家姓名字段。
- `p` 是原生玩家称谓；完整身份来自 `15DFC0` 的实际姓名＋文化字段，中文文化使用原 Profile 文化语义。NPC 描述使用 `c`。
- `v` 对应原数值格式；物品 `i`、地理 `g`、方向 `d`、文化 `k`、时间 `h`、单位 `u`、列表 `l` 分域解析。物品和地理的空格组合只消费各自已知词值，不能作为任意英文句子的逐词翻译通道。
- 完整台词、任务正文和实际追加片段保留原句来源；16条任务格式段落接续、具名强盗整段拼接及 `139890` 的完整位置接续分别列明来源。中文的实参顺序明确写入静态元数据，例如先地点后人名，不把不同 `%s` 混为一类。

原 `TALKLINE`、条件、冒号选择器、任务标记、文件路径及 command 保持英文并由游戏解析。任务的 `label|TALKLINE ...:response]` 仅把实际可见 label 和 response 分别纳入显示语法。没有改变原选项值、去重或输入动作，也没有“未识别则逐词翻译／保留某段英文”的补救分支。

原单复数表的 `/` 两侧与 `15EFF0` 的 `fe/f/tooth/lock of/x/ch/ry/s` 规则只用于离线生成有限词值别名，语义键仍指向原词库条目。原生单复数业务照常执行；Mod 不改物品描述、数量或任务数据。

## 原生 UI、度量和生命周期

逐指令依据见 [完整文字及索引边界](20261111-conversation-native-boundaries.asm)。

1. `1339C6/134366` 保存原来已经接受的完整英文／UTF-8 输入；中文只借给本次原 word-flow。既有按 Root、speaker、paragraph 保存的原语义输入继续用于原背景和原双方 Panel 的完整重建，未增加页面中文快照、输出行或绘制贡献。
2. 原 `133A16/1343A6` 标量读取已支持完整 UTF-8。本批在 `133A5D/1343EC` 的原 delimiter 分类结果处，使一个完整非 ASCII 字形也成为合法词元边界。原 `ADD ESP`、`TEST`、下一字符空格判断、宽度比较、换行及行距仍执行；原字宽与游标推进接口继续消费实际完整字形度量。两个原退出点释放当前输入借用。
3. 普通菜单消费在原 `Choose a line / reaction:` 实例的 `button_row` 绑定完整后缀。当前已开菜单在实际 `1427FA` 等待返回边界、原完整重建之前补绑定同一批原行；随后原 Menu 物化、原选择框、命中、键帽和输入循环使用这些来源。
4. `134E75` 在原动作结果段落调用消费完整表达式；`134E89` 翻译继续按钮，保留 `[SPACE]` 原输入标记。沿原组件绘制中文字形、度量和按钮推进。
5. 交易侧栏八个完整文字 CALL 全部消费对应语义。`134A04` 原 `sprintf` 完成后，其仅供侧栏显示的栈上 scratch 获得中文；真实物品、数量和原 producer 不改。`134A1C` 仅把原长度比较的操作数扩展为原8单位文本格的真实字宽，原 `CMP 1Ch / JB` 自己选择是否截断。被选中的原分支在 `134A23` 把原保留26格的索引换算为完整编码字形的字节索引；两条原 `MOV` 仍负责写点号及 NUL。其间临时借用 EBP 作该真实目标索引，`134A32` 根据原 CMP 的 carry 分支状态恢复 EBP，之后原 `MOV EAX,[surface]` 继续。没有独立裁剪回调、侧栏行槽、坐标表或绘制重放。
6. 完整重建按 `141F70` 的真实条件恢复 `134790` 侧栏：`mode=3 && trade=0`，或 `trade=2`，或 `mode∈{2,3,10,11} && trade=1`。它只消费原交易状态，不接受物品、不生成报价、不重新分派选项或等待输入。此前文档将它与 `134B60/134C70` 一并列为业务生成不准确，已在两份原记录更正。

本批沿既有完整原生组件目标和真实输出密度提交字形；不增加全局 SDL／逐像素跟踪、像素与 UTF-8 贡献记录、Present 前叠字或缓存文字重放。新增来源没有 UI 坐标、裁剪矩形、样式或延后绘制身份。

## 既有待整改项

这些项目仍不符合当前原生 UI 所有权要求，不能因以前编译／发布完成就视为合规：

| 文件与位置 | 影响 | 状态 |
| --- | --- | --- |
| `native_footer_component.cpp:88` 起 | Mod 计算主菜单署名间隔及 x | 待整改，本批聊天不调用 |
| `module.cpp::enter_component_paint`，About 按钮中心例外 | Mod 从 Panel 输入计算按钮中心 | 待整改，本批不扩展 |
| `native_ui_scene.cpp:12` 起 | 历史 Child/Container 集合、序列化尚未完全退役 | 待整改，本批不据其恢复对话页面 |
| `native_renderer_component_binding.cpp:39` 起 | Owner children 及历史物化代码仍保留 | 待整改，本批不新增 renderer 子项 |
| `windows_inventory.inc:6` 的 `native_text_limit` 及其 inventory／HUD／百科调用 | 在投影／消费者侧自行截取前缀并加点号，尚未把该索引放回对应原生截断指令 | 待整改；本批侧栏不调用它，而扩展自己的已确认原生比较／索引边界 |

## 交付状态

本批源码、完整源文记录、生成资源及静态证据已保存；根统一队列完成一次配置、一次增量编译及正式兼容热发布。Adapter 完成重新编译、链接；Catalog 目标完成，Catalog DLL 内容沿用，正式词库文件已更新。日志只有既有函数指针转换、extern 初始化、未使用项及缩进警告，没有编译错误。提交请求后至批次结束，没有修改该批源码。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 468 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 本批回执 |
| --- | --- |
| 请求 ID | `34b9c39b4e33473c931fa0463222c803` |
| 批次 ID | `39034ef70ab94ea49839107bdb8e2f42` |
| 请求结果 | `build/.compile-queue/results/34b9c39b4e33473c931fa0463222c803.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 完整批次日志 | `build/.compile-queue/batches/39034ef70ab94ea49839107bdb8e2f42.log` |
| 正式事务 | `841e5394478c4e9baf03bd6d72ecdf1f`，2026-11-11 10:31:59（Asia/Shanghai）完成 |
| 正式发布结果 | `build/mingw-x86/stage/841e5394478c4e9baf03bd6d72ecdf1f/publication-result.json`，`success=true`、当前进程 `applied=true` |
| 已替换正式文件 | `package/modules/uwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧件归档 | `回收/20261111-103157-841e5394478c4e9baf03bd6d72ecdf1f/package/`，先归档三件，再替换，保持原相对路径 |
| 当前进程 | 只读进程表为宿主 PID `3145474`，既有 Proton Mono 只读枚举为 Windows PID `468` |
| 兼容交接 | 先收到 `ReadyToPublish`，提交后 Catalog 第3代、Adapter 第3代均返回 `Applied` |

已完整读取请求 JSON、批次日志、正式发布 JSON 与清单，正式文件及构建件哈希如下：

| 文件身份 | SHA-256 |
| --- | --- |
| Adapter，正式件／构建件／清单／Applied 一致 | `49b7bcb4ece44d05a0e8b8106b02780cd525a21eb684c99e1d02c612118f8113` |
| messages.tsv，源词库／正式件／清单一致 | `e2d572743984c6ba94406f2c1e1be8fcaf0d9ca553b7f1de16b3ce430244d5b3` |
| Catalog DLL，正式件／Applied 一致 | `cd5ea4f63e239691176f6bf1e38a1b4c232a0c9c5f8182eb80aacefbfa8e6719` |
| 已归档旧 Adapter | `1a28446a9c072657223e7979074bc3b4b81a9f0aa9974b6b01f39ffbbee3f8bd` |
| 已归档旧 messages.tsv | `c8b670d7fc349fd346ef323da6e8d3be09a67af78f56e8e87fe537549aec6d53` |

源码修改、产物编译、正式发布与当前进程兼容交接均完成。根 `uwcn_launcher.exe` 仍使用同一份正式包；无需重启，也没有建立平行修复目录。Applied 只证明兼容交接完成，未运行测试或自行验收画面。上一批标题修正的回执单独保留在 [原记录](20261111-chat-ui-native.md)。
