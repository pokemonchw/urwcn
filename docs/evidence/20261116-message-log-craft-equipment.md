# 消息日志：制作说明、产出、动作回显与装备结果

2026-11-16，用户截图 `codex-clipboard-2b9a3db4-cb75-4ad9-a059-f6c93d9c5be8.png`；Windows x86《不真实的世界》3.89.1 / Steam Build 26139145。只读现有英文日志、原生资源、磁盘PE、已有完整反编译和反汇编，不运行游戏或测试。

后续更正：用户截图 `codex-clipboard-e712adcb-d28f-4ec9-ab00-63a4f5e6a760.png` 确认初批发布后两条木杆产出提示仍为英文。初批将中文参数顺序误写为英文顺序；本文件原“产出提示已补齐”的结论不成立。初批编译和Applied回执仅代表文件及业务交接完成。原因和本轮交付见文末“产出句式参数顺序更正”。

## 漏译原因与静态来源

现有角色 `ALICE/msglog.txt` 中保留了截图的全部英文输入。`FE2B0` 读取这些原文，不保留实时消息的格式实参身份；已有实时翻译不能覆盖未接入的历史整句。

| 历史原文／类别 | 已确认的原生来源 | 修改 |
| --- | --- | --- |
| `(You can split boards from big trunks by using a timbercraft skill.)` | `468AC0` 在 `46910D..46915D` 读取实际材料记录 `+B8Ch` 的配方说明；为空时复制 `46BBF0` 返回的默认说明。`469182` 的三个实参是前缀、完整说明、后缀，`46918F → 4F6510` 输出 | 原词库已译配方说明和默认说明，历史身份只手工列出了后者。词库生成器现在从同一 `craft-requirement-description` 域推导所有完整括号正文及原生大小写变体，新增20项，包含劈板、木块、纱线、晾晒架、浸泡、温暖房间等 |
| `You can make 3 staves from one slender trunk.` | `441CD1` 使用 `596818` 的 `?You can make %u %s from one %s.`；`441CA6 / 441CB9` 分别对两个原生材料／物品名调用 `4D4020`，数量来自原 `2130AC4`，`441CE3 → 4F6510` | 完整 `qrr` 语法，数量只接受原无符号十进制；产品与材料复用留存物品语法及已有要求名称。`staves` 使用原 `item/staff`，`slender trunk` 使用 `craft-requirement/Slender trunk` |
| `BUILDING OPTIONS: Post spruce` | `46980 → 563190` 返回实际动作名称，`500846` 构建标题／所选项，`5008A2` 去掉竖线附注，`5008AB → 4F6510` 输出；详见[建造分支清单](20261112-building-menu-branches.md) | 历史菜单选项语法增加现有 `activity` 静态词源，按域选择动作译文；Post spruce 使用“制云杉撑杆”。继续工作、拆除等同类动作也消费原静态动作名 |
| `The fine broad knife wielded as a primary weapon.` | 原 `messages/urw_combat.txt:24..37` 的 HANDMODE、WIELD_WEAPON、UNWIELD_WEAPON；主手／副手和PC／NPC分支由游戏已经选好 | 补齐主手、副手持武器、NPC持武器、PC／NPC收起武器5条完整历史句式。品质、冠词、物品名称复用既有留存物品语法，不查询当前装备 |
| 同类穿脱消息 | 原 `messages/urw_msg.txt:993..995 / 1021..1022` 的 WEAR_OK、TAKEOFF_OK | 补齐PC／NPC穿戴及卸下3条完整历史句式，与已选原生资源译文一致 |

磁盘PE数据确认 `59A1D0` 为 `_(`，`59A1CC` 为 `)`。前一轮手工制作记录将前缀写作 `?(`，本记录更正为实际 `_(`；两者在保存正文时都会去掉颜色标记，但来源证据须保持准确。原PE路径 `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，本轮读取的是磁盘文件，没有注入进程。

反编译见 `build/analysis/handcraft-20261112/final.c:2118`、`build/analysis/windows-3891-native-full.asm` 中 `441CA1..441CE3`、`46910D..46918F`、`4D4020..4D40CE`。`4D4020` 将输入转为小写；新 `windows_message_history_craft_words.inc` 从现有 `values.craft-authored.zh-CN.tsv` 的92个非空材料要求名称生成184个原大小写／小写词源，键保持原值。该表只含英文、语义域和词库键，没有UI位置、行号、页面记录或业务对象。

## 源码与词库

- `modules/adapter/windows_message_history.inc` 增加1条产出和8条装备历史语法，纳入原活动词源及材料要求词源。
- `translations/messages_embedded/values.message-history-handcraft.zh-CN.tsv` 增加上述9条整句译文。
- `translations/build-message-catalog.ps1` 从两种原生说明来源共用的既有语义域推导完整历史身份，继续使用已有 `History-Body` 和 `History-Case`。
- 运行该词库生成器的 `-ExistingLiterals` 数据生成入口后，静态比对原98978项键和值全部保留；新增29项，总计99007项。没有运行解析器、测试脚本或游戏来检查命中。

日志的 `FE5F8` 实际宽度入口和 `FE86E → 562300` 正文入口继续共用 `windows_message_history::source`，后续 `FE9BB → 50EB40` 由原段落消费。完整中文语义进入既有中文编码、字宽和原生组件当次真实目标密度字形接口；游戏继续管理70条记录、分页、换行、行距、颜色、按钮、背景和缓存。

没有新增Hook、驻留ABI、持久状态字段、固定坐标、行槽、整页中文快照、DisplayPlan、全局像素跟踪或延后重放。翻译未命中时继续现有已授权的原文显示行为，没有新增保护或故障兜底。

## 既有待整改边界

| 文件与位置 | 影响 | 状态 |
| --- | --- | --- |
| `modules/adapter/native_renderer_component_binding.cpp:47 / 570 / 672` | Owner.children及两处遍历重新绘制集合仍违反原生UI管理组件／缓存生命周期的要求，影响旧渲染owner重建 | 待整改；本轮不扩展或登记位置 |
| `modules/adapter/native_footer_component.cpp:58 / 79..87` | Mod计算主菜单署名间隔、宽度和位置，违反布局所有权 | 待整改 |
| `modules/adapter/native_ui_scene.cpp:12..20` | 历史Child／Container组件集合及序列化仍保留，完整退役未完成 | 待整改；不作为本轮显示依据 |
| `docs/design.md:196` 及其历史DisplayPlan／Present叠字建议 | 历史错误方案仍可能误导设计判断 | 待清理，文件开头已有否定说明；本轮不采用 |
| `modules/adapter/native_generic_menu_language.inc:146` 起的日志纯语言重建 | 仍复用旧一／二行缓存标志，长记录切换语言后的页面选择精度有既有缺口 | 待整改；本轮没有改变分页业务 |

本次未自行启动交付程序、启动／关闭／重启或操作游戏，未注入验证、模拟输入或运行测试，未创建测试用例、测试脚本、测试工程或断言。编译仅生成交付产物，兼容业务交接使用用户已授权的既有驻留事务。

## 交付状态

源码和99007项词库、产物编译、正式文件发布及兼容业务交接均已完成。统一入口为：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2735482958/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 已读取的结果 |
| --- | --- |
| 请求ID | `cf3820cccf6f47fd948cc7b02dd9cbe5` |
| 批次ID | `dada69f2e36644a0baeb8600391b2ee9` |
| 请求回执 | `build/.compile-queue/results/cf3820cccf6f47fd948cc7b02dd9cbe5.json`；Success、PublishRequested、ReloadRequested均为true |
| 完整批次日志 | `build/.compile-queue/batches/dada69f2e36644a0baeb8600391b2ee9.log`，已完整读取；一次配置、一次增量构建，Adapter重新编译链接，Catalog目标完成 |
| 正式发布事务 | `4b7fcad897fc4658a99b8002b27e4a2e`，2026-11-16 15:36:20（Asia/Shanghai）完成 |
| 发布回执 | `build/mingw-x86/stage/4b7fcad897fc4658a99b8002b27e4a2e/publication-result.json`；success=true，PID364 applied=true |
| 正式替换文件 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧文件回收 | `回收/20261116-153618-4b7fcad897fc4658a99b8002b27e4a2e/package/`，三件按原相对路径先移入再替换 |
| 现有进程 | Windows PID364、宿主PID1651717（15:30:24启动）；只读确认仍为原进程，原驻留桥ReadyToPublish后Catalog／Adapter均第2代Applied |
| Adapter SHA-256 | `1332d8b5a129828bf917f07949839f5fa006a807d15c374f6d30db7633d36dea`，构建件、正式件及Applied回执一致 |
| 词库 SHA-256 | `4184f514c6dade653baf1ecfa1d049e582d35c058326b644b69c8c16d4c227e8`，源码及正式件一致 |

```text
Applied 4b7fcad897fc4658a99b8002b27e4a2e catalog:bf126890ba7042524fd8a606e94d5390d74bed7b633449f2512c05cd7aa501c0:2 adapter:1332d8b5a129828bf917f07949839f5fa006a807d15c374f6d30db7633d36dea:2
```

提交后至批次结束没有修改请求范围源码，没有重复提交。构建保留既有函数指针转换、extern初始化、未使用项及缩进警告，新增历史文本文件无编译警告；无编译错误。Catalog DLL二进制未变，词库由其第2代重新加载。本批仍属15时，build-hour没有变化，不作为替换文件。

正常根启动器和当前游戏继续使用同一正式 `package/`，无需重启。没有创建独立修复包或平行运行副本。Applied仅证明已授权的业务交接完成，不代替游戏运行或画面验收；任意其它动态历史正文的覆盖不在本次证据之内，既有待整改边界仍如上记录。

## 产出句式参数顺序更正

后续用户截图显示，材料说明、撑云杉菜单回显及装备结果已变为中文，两条 `You can make 3 staves from one slender trunk.` 仍为英文。本轮不将它归因于缺词或未加载模块：源码和正式词库都已有该完整句式、`item/staff` 和 `craft-requirement/Slender trunk`。

静态原因是 `modules/adapter/windows_message_history.inc:26`（初批位置）的 `Form.order` 错误：英文三个原操作数为数量0、成品1、材料2，中文译文 `用一份{2}可以制作{0}份{1}。` 的实际消费顺序为201，初批却登记为012。`windows_message_history::parse_history` 按order生成表达式的syntax及children；`modules/adapter/native_message_source.cpp:87..95` 从当前cursor向后顺序消费syntax。旧顺序首先越过 `{2}`，最后无法在cursor后找到它，产生错误文本；`modules/layout/layout.cpp:34` 的已有UTF-8解码因此不能将其编码为中文。原文显示路径仍消费已确认的原生日志输入，没有新增故障逻辑。

本轮只将该原句的顺序改为201并添加语义注释，不改英文槽位、原数量、材料、物品名称、翻译正文、通用表达式投影或词库。静态查阅同批9条新增语法及对应译文：本句需要201，其余8条使用0或01，与译文顺序一致。没有运行解析器、脚本用例、断言或游戏验证。

中文语义为“用一份细树干可以制作3份木杆。”，来自原日志中的3、staves和slender trunk；同一句式的其它数量和材料继续消费自身原操作数。实际宽度与正文仍通过同一 `windows_message_history::source` 进入原生度量、分页、组件当次绘制及缓存管理。没有新增Hook、ABI、状态、坐标、UI快照、像素跟踪、重放或兜底；上文既有UI待整改项继续保留。

现有 `package/urwcn.log` 在两次兼容交接记录之间保留了原生派发20969／20970的status 1记录，对应 `native_generic_menu_language` 的history_line_width／history_append，与正文／度量表达式编码失败相符；该日志仅作已有现场证据，没有自行触发事件或采集运行验证。

修正源码、产物编译、正式文件发布及兼容业务交接均已完成。统一入口沿用上文命令，仅将模块集合改为 `-Module adapter`；词库没有重建或替换，仍为99007项。

| 项目 | 本轮已读取的实际结果 |
| --- | --- |
| 请求ID | `db90f6a252364afb8d642649bf491bba` |
| 批次ID | `bcaed2db97c54ff5ac72f220f7747a71` |
| 请求回执 | `build/.compile-queue/results/db90f6a252364afb8d642649bf491bba.json`；Success、PublishRequested、ReloadRequested均为true |
| 完整批次日志 | `build/.compile-queue/batches/bcaed2db97c54ff5ac72f220f7747a71.log`，已完整读取；一次配置、一次增量编译及链接，仅Adapter目标 |
| 正式事务 | `3d30f9f3927a4f39bd9ff08b95d19c3c`，2026-11-16 15:57:31（Asia/Shanghai）完成 |
| 发布回执 | `build/mingw-x86/stage/3d30f9f3927a4f39bd9ff08b95d19c3c/publication-result.json`；success=true，PID364 applied=true，Adapter第3代 |
| 正式替换文件 | `package/modules/urwcn_adapter.dll`、`package/release.json` |
| 旧文件回收 | `回收/20261116-155730-3d30f9f3927a4f39bd9ff08b95d19c3c/package/`，两件按原相对路径先移入再替换 |
| Adapter SHA-256 | `5c9b75623512634eca2fa6434b4fc7d737ab452e5c9badb2c8de11a3c05f1004`，构建件、正式件及Applied回执一致 |
| 回收Adapter SHA-256 | `1332d8b5a129828bf917f07949839f5fa006a807d15c374f6d30db7633d36dea`，与初批正式件一致 |
| 当前进程 | Windows PID364、宿主PID1651717，仍为15:30:24启动的同一游戏进程 |

```text
Applied 3d30f9f3927a4f39bd9ff08b95d19c3c adapter:5c9b75623512634eca2fa6434b4fc7d737ab452e5c9badb2c8de11a3c05f1004:3
```

提交至批次结束没有继续修改请求范围源码，也没有重复提交。只有既有编译警告，无编译错误；未运行产物、游戏、模拟输入或测试，画面结果仍待用户验收。无需重启、手动卸载或返回指定界面，没有平行运行副本。
