# 已接入界面的完整原生语言重建

日期：2026-11-10。对象为 Windows x86《不真实的世界》3.89.1 / Steam Build 26139145，原 PE SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。本文的 RVA 来自原 PE 静态反汇编；没有启动游戏、运行产物、模拟输入、编写或执行测试及断言。

本记录承接 [共用擦除整改](20261110-common-language-reconstruction.md) 和 [第4、5代构建记录](20261110-native-full-language-boundaries.md)。前两份文档的未完成列表是各自批次当时的状态，后续实现及交付以本文和各族静态证据为准。

## 共用协议

语言切换只提交语言版本和原生输入返回请求，不先清屏、不遍历 Mod 的组件列表绘制、不替换原生缓存矩形。原生菜单的共同 `D1120/D12B4` 边界、普通等待 `D1C00` 和动画输入 `D25E0` 消费该请求；每个显示族执行其已经确认的完整原生构造区间，再继续原生保存、选择、呈现和释放。

构造覆盖完整背景、面板、文字、数值、图形及控件。构造期间明确跳过原区间中的业务修改、随机数、音频、日志、配置读写、资源退役与新输入等待；普通运行分支仍继续各自原指令。相对条件跳转通过原生目标显式续接，不复制旧位移到 Hook trampoline。

缓存按真实 first、second、menu 和四个 named 槽保存语言 revision。恢复旧语言缓存前，借用该原生 owner 的真实语义输入，先经原生缓存恢复取得场景底，再完整构造父界面并调用原生 save。之后仍由原 restore/present/free 执行。嵌套窗口消耗当前页的 pending 不会把其它父缓存误当作已更新。

没有记录或扫描像素，没有文字位置、裁剪、颜色与 UTF-8 的延后重放序列，没有 Present 叠字、页面快照、坐标表或第二套布局。

## 显示族及覆盖依据

| 显示族 | 完整原生构造及状态 |
| --- | --- |
| 主菜单、设置、关于、鸣谢、创建方式、读档 | 完整原根及菜单、路径、底栏、正文和按钮；弹窗及设置返回前更新真实父主菜单 first，原设置值、读档业务和选择不变。 |
| 先祖列表、单条先祖和列表详情 | 原 `DE990/DD380/DD400` 构造；保留原排序、分页、当前记录和选择；详情使用原 `ancestors` 命名背景，不重新读索引。 |
| 属性、文化、性别、姓名、头像、季节 | 完整 hut/标题及原生各阶段面板；后续阶段重建原生灰化的前序完成态；不重新生成文化、性别、属性、月份或头像业务值。 |
| 正在编辑的姓名及校验页脚 | 保留真实 getst 输入缓冲、光标、IME、容量及提交状态；按本次原 F210 接受的 footer mode/tint 构造完整页脚，不重跑验证和 PRNG。详见 [姓名边界](20261110-name-input-language-construction.md)。 |
| 技能及点数确认 | 完整技能分组、信息条、数值、帮助、点数面板；当前选择与最后预览独立；点数确认同时构造后方技能页，使用原 MENULIST，不另造不存在的 second 缓存。详见 [确认窗口](20261110-skill-confirmation-language-reconstruction.md)。 |
| 法术、百科、世界地图 | 完整原纹理/底栏/简介、原百科换行与链接表、原世界地图和图例；选择继续使用原动作或英文链接标识。正在编辑的百科关键词也构造完整原页与 prompt，保留实际 getst 输入。详见 [关键词边界](20261110-encyclopedia-keyword-language.md)。 |
| 情境选择、确认、故事、创建完成、游戏进程 | 原完整背景、故事图片、正文和控件；跳过任务动作和角色初始化；gamecourse 返回时更新其真实父背景。详见 [等待及动画](20261110-wait-animation-language.md)。 |
| HUD、消息、分页、独立等待、地图浏览、目标选择 | 原完整 HUD、状态、持有物、时间地点、命令及消息；保留原分页游标、More/Continue 语义、地图选择和目标；不重新计算移动业务、雪地 PRNG、盾牌或消息计数。详见 [HUD 边界](20261110-hud-message-map-language.md)。 |
| 速度组件构造中的消息等待 | 实际两处DB960 query之前可分页。组件以原FB239/FB242双发布为提交点保存完整逻辑输入；重建已发布版本，再恢复当前未发布前缀，保留原query和原帧唯一继续。没有缺数字补空、数字重算、像素快照或提前发布半成品。 |
| 命令、定位命令、物品、伤势、护甲、奖励菜单、数量及百科父窗口 | 完整原窗口及外围帮助/预览；借用真实标题、模式、过滤对象、页码、数量界限和当前记录；数量编辑保留原 getst；返回百科时更新其命名父缓存及实际 first/局部背景。详见 [父缓存](20261110-parent-cache-language-reconstruction.md)。 |
| 暂停统计与共用背景 | FIRST 全部10个恢复、共用20个caller统一按原缓存revision重建，统计页保留已接受记录并跳过业务表初始化。SECOND 补齐原先漏接的7个save，全8个save与2个restore进入原生命周期；奖励菜单不能按普通HUD恢复。详见 [FIRST 边界](20261110-first-cache-language.md)。 |
| 启动加载、失败等待、开场和告别 | 原完整加载界面与已接受资源输入；原动画阶段、计数、色调及时间继续，重建不另等待、不重播音乐或执行淡变；告别不重跑退出业务。详见 [等待及动画](20261110-wait-animation-language.md)。 |
| NPC资料、聊天、emote、消息历史、问答及两种地点地图 | NPC按真实Root拥有整句、说话者和逻辑段落源，原双栏word-flow负责换行与游标；共享业务父按真实NPC/HUD owner分派。历史和问答完整构造独立Panel、正文、控件，地点地图连同原known-map完整工厂重建；地图字段编辑保留原64字节ring。详见 [菜单普查](20261110-generic-menu-language.md) 与 [会话](20261110-conversation-language-reconstruction.md)。 |
| 任务日志详情、列表及空列表 | 原800×600独立纹理和全renderer Clear/Copy完整覆盖；保留实际任务record/page/index，跳过任务重新枚举、排序和业务提交。详见 [任务日志](20261110-quest-journal-language.md)。 |
| 文本输入及连续输入 | 普查全部26个10F5B0调用及地图64字节ring变体；姓名、百科关键词、数量沿各自完整父构造，其余输入保留真实提示消息、已接受输入和当前缓冲，使用原getst背景采样、文字及光标生命周期重建。连续输入随真实消息Record交替构造，不从atoi后的数字猜回字符串。详见 [全部文本编辑](20261110-text-edit-language-reconstruction.md)。 |

原生等待静态普查覆盖36个D1120、24个D3C80和18个D3BF0直接CALL；已接语义的实际owner均进入对应完整构造。未接汉化的六类原英文诊断/目录提示保留原页，切换不清屏、不伪造译文。输入阶段及属性mode0/2等变体见 [等待普查](20261110-wait-census-language.md)。

## 语义输入及兼容交接

保存的是组件原本接受的英文语义、标量选择及输入阶段，不保存帧指针。实时帧仅在一次同步原生构造内借用。姓名错误页脚新增真实 mode/tint 输入捕获；HUD 的原 `F90D0` 输入进入自身语义状态，百科的实际link/keyword选择在原生产者处记录。

本轮私有状态明确升级为 **HDA8**，21个长度分节全部保存/恢复，错误页脚节为完整16字节；第18节包含速度组件真实工作/提交状态，第20节是完整会话语义源，第21节为文本输入的真实语义状态。Host API、模块描述容器 schema1 及原有组件枚举不改。HDA8 不接受 HDA7 或更旧状态，不再把缺失节默认为空、不把未知关键词路径默认成link、不按当前页面放宽迁移要求。

这是实际状态 ABI 不兼容：旧版在 `F90D0` 已返回且进入下一轮 `17CC80..17D014` 时没有保留上一命令；旧版 `3E110` 已返回的真实space/link选择也未保留，当前选择还可被鼠标悬停覆盖；原 SECOND 有七处未登记save。这些历史信息不能由新构造捕获补回。完整静态依据见 [Command历史输入](20261110-hud-command-migration.md) 和 [百科无结果边界](20261110-encyclopedia-no-info-language.md)。

现有驻留框架的 COMMIT 必须调用新模块 `restore_state`，没有不恢复旧私有状态而无损替换活动 UI 的能力。因此本轮不能向旧HDA7进程承诺兼容业务热交接，也不提交已知不兼容的Reload去尝试。正式文件发布和当前旧进程应用必须分别报告；不关闭、重启、模拟操作游戏，亦不要求用户返回某个特定界面来规避这一状态ABI边界。

英文模式中的 UTF-8 姓名在已确认的完整原生文字调用内进入 Unicode 编码与真实度量。菜单测量读取该行真实中性来源，标题、按钮和正文共用同一调用期编码/绘制作用域。原始姓名及其它英文业务数据不改写；北欧单字节原资源继续按其真实编码解释。同步度量作用域各用独立 token，不跨输入等待保存。

## 历史结构审查

原 Scene 来源图沿用旧HDA7内部结构，供真实缓存身份与原菜单输入交接，已无整页/缓存绘制能力；HDA8不读取旧HDA7载荷。`native_renderer_component_binding::paint` 的旧子组件序列与 `native_footer_component::paint` 的 Mod 几何安排仍是既有待退役项，位置和影响见 [共用整改中的审查记录](20261110-common-language-reconstruction.md)。本次完整原生构造不调用该 Scene 绘制序列，不能把新增语言覆盖当成这些历史结构已经合规。

Linux 分支及 HDA4 等旧驻留 ABI 不包含本轮 Windows 改动；不宣称跨 ABI 的原位迁移。

## 交付状态

源码修改、统一队列编译和正式文件发布均已完成。全部新增源码在提交前保存并冻结，批次期间没有修改本请求范围的源码。构建仅用于生成交付产物，没有运行产物或测试。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Publish
```

| 项目 | 本轮回执 |
| --- | --- |
| 请求ID | `893a7ad2de0744089f3effbd524d4a97` |
| 批次ID | `ff8e5a6a13144baa9043907cb70041ff` |
| 队列结果 | `build/.compile-queue/results/893a7ad2de0744089f3effbd524d4a97.json`，`Success=true` |
| 批次日志 | `build/.compile-queue/batches/ff8e5a6a13144baa9043907cb70041ff.log`，`Built target urwcn_adapter` |
| 编译对象 | MinGW x86 Adapter；一次配置、一次增量构建，无清理构建树 |
| 正式发布事务 | `c7b8d414dcaa4e5b95613f8243837b0c`，`publication-result.json success=true` |
| 正式更新 | `package/modules/urwcn_adapter.dll`、`package/release.json` |
| 正式Adapter SHA-256 | `a71c5165fa65c008b7d369d51253d7f4b2bfcbca79b6d5da8aa5cbdadf19e07a`，与构建产物及正式清单一致 |
| 旧件归档 | `回收/20261110-150410-c7b8d414dcaa4e5b95613f8243837b0c/package/`，保留原`modules/urwcn_adapter.dll`和`release.json`相对路径 |
| 旧Adapter SHA-256 | `eea7881b0c52896992ec9de701f06a3ef52c029e8704c9a2af59b52630f1741b`，归档文件仍匹配上一正式版本 |
| 运行时应用 | `ReloadRequested=false`，`runtime_requested=false`，`runtime_receipts=[]`；没有Applied回执 |

已读取请求结果、完整批次日志、发布结果及正式清单，并读取正式件、构建件和旧归档件哈希。编译包含函数指针转换、未使用项、缩进及extern初始化警告，没有编译或链接错误；没有以编译代替运行画面验收。

正式启动路径已更新，不需要独立修复包或改用构建目录启动器。当前旧HDA7进程未应用本轮HDA8，原因及不可恢复输入见前文；下次从根`urwcn_launcher.exe`正常启动加载本轮正式Adapter。没有关闭、重启游戏或要求返回任何特定页面。
