# 2026-10-19 Linux 全部开局情境汉化

用户在首轮确认页接入后要求“每个选项都要处理”。本轮将 `RNDCAMP.0` 至 `.12` 的全部标题与完整故事接入同一原生显示路径，覆盖确认页，以及选定后的开局介绍。此前选择列表的13个名称、13条简介保持已有接入。

## 完整范围

`scenario.confirm.*` 词库现在共215项：13个标题、199条非空故事源记录、共用确认问题和两个按钮。各源文件的非空正文记录与译文逐项对照如下；序号标识源文件与源记录，不是显示行或坐标。

| RNDCAMP 文件号 | 情境 | 非空故事记录 |
| --- | --- | --- |
| 0 | 不真实的世界 | 15 |
| 1 | 村庄 | 13 |
| 2 | 逃亡的奴隶 | 21 |
| 3 | 不幸的狩猎之旅 | 20 |
| 4 | 孤独的拓荒者 | 21 |
| 5 | 受伤、无助与恐惧 | 14 |
| 6 | 陷阱与诱捕 | 19 |
| 7 | 我想当渔夫 | 19 |
| 8 | 废弃的陷阱围栏 | 21 |
| 9 | 废弃营地 | 7 |
| 10 | 农耕 | 5 |
| 11 | 有强盗！ | 11 |
| 12 | 并非所有流浪者都迷失了方向 | 13 |

每项均包含全部叙事和原有情境说明。“我想当渔夫”原文件没有单独的括号说明，未添加虚构内容。名称沿用选择页译名；`Njerpez` 沿用“涅尔佩兹”，`turnip` 沿用百科“芜菁”，故事中的游戏名统一为“不真实的世界”。尤萨仅是显示译名，不改英文源文件中的 `Jussa`。

## 静态证据与接入

目标仍为不真实的世界3.89、Steam Build 25939378、Linux x86-64；原 ELF SHA-256 为 `4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。沿用并重新阅读首轮已导出的静态证据：

- `build/analysis/scenario-confirmation-linux-ghidra.c`：`get_camp`、`show_scenario`、原生按钮及分词器。
- `build/analysis/scenario-confirmation-story-linux.asm`、`scenario-confirmation-controls-linux.asm`、`scenario-confirmation-input-linux.asm`：标题／正文调用、确认控件及重建边界。
- 安装目录全部13份 `RNDCAMP` 文件，只读读取。各文件第一条是原情境名称，第二条是列表简介，第三条是图片，第四条开始是故事。全部文件以换行结尾；原 `get_camp` 保留其故事写入和 EOF 处理。
- `build/analysis/linux-symbols.txt:787`：原生 `SanaTaulukko` 大小为 `0x9EB10`，对应5000个130字节词元槽。

`src/linux/adapter.cpp:scenario_story_titles` 列出13个真实 `Scenario: ` 标题及原文件顺序，只存语义身份，不存位置或页面内容。`scenario_title` 在 `1244B8 → winbox` 的原生显示调用确定源文件 ID，重置非空源记录计数，借入 `scenario.confirm.title.<id>`；原标题及图片选择所读取的英文缓冲不改写。

`scenario_append` 在 `124565 → SANATAULUKKO_Lisaa` 使用 `scenario.confirm.story.<id>.<record>`。每个原非空故事记录对应一条译文，保持原 `<br>`、空行和终端空读取。全部13项共用已有中文完整字符分词，村庄不再使用另一条按人工空格分组的 Linux 正文分支；旧 `scenario.village_*` 词条和组件保留供 Windows 既有调用使用。

原 `1245A7 → showtext_sanataulukko` 继续拥有正文区域、折行、行距、颜色和绘制次序。`13EEC3`、`13F00F` 和 `13EF3D` 的既有完整字符宽度／推进／分词空格扩展继续使用。没有把 UTF-8 字节交给 ASCII 路径，也没有根据译文建立行槽、坐标表或另一套布局。

最长标题含 NUL 为37字节，远小于原1024字节临时缓冲；最长单条故事在双字节编码后含 NUL 为75字节。正文每个中文词元为2字节。最长整篇为522个中文字符，原生换段、空行及 EOF 的额外标记仍远小于5000个词元槽。这里仅做源文本和已确认容量的静态清点，没有运行原生函数、模块或测试。

原生确认控件接入 `1CF17`、`1CF5E`、`1CF79` 对全部情境共用，原 `<Y>`、`<N>` 高亮标记及 Y/N 动作保持。按钮文本同时进入原生绘制和 textwidth，按钮尺寸、选择和鼠标命中由原生构建管理。字形在已接入真实输出密度的原生 screen 上同步提交；背景、图片、表面缓存及呈现继续归游戏所有。

## 刷新与业务交接

所有情境确认页使用首轮已接入的 `F871F` 原生输入返回重建：只对 `RSP+0x458` 返回槽为 `1CFD5` 的当前调用，重入 `1CEFC..1CF7E` 显示片段，保留当前选择并由原生重建背景、图片、文字、控件、菜单缓存和选择框。不会执行故事文件写入、情境选择结果、随机数或新的输入等待。

确认页热更新或中英文切换后，在下一次自然 `getkey` 返回时重绘，不发送模拟事件。选定后的介绍页在其原生 `show_scenario` 构建时消费全部译文；其已完成面板的立即重建仍不在本次已确认边界内，不将确认页刷新能力外推到该等待窗口。

本轮不改 Semantic 的通用 `scenario_confirmation_text=0xC21` 派发、不改驻留桥、Hook 契约和 Host ABI 2。原 state-v1 的 `scenario_record`／`village` 字段按原顺序保留；新的13项故事 ID 在同次同步绘制的标题边界确定，不跨输入等待保存。旧单情境词库键由新版分情境键取代，因此 Adapter 与 Catalog 同事务发布。

## 审查记录

- 上轮 `src/linux/adapter.cpp:scenario_title/scenario_append` 仅识别两项情境，导致另外11项仍使用英文标题和正文；本轮已统一接入全部13项。此前首轮发布成功不代表所有选项已覆盖。
- `src/linux/adapter.cpp:glyph_request` 的原生阴影预算，以及 `src/linux/native_targets.cpp` 的非主菜单途中缩放重建边界，仍为既有待整改项；影响为阴影占位和密度一致性，不以本次编译或发布视为解决。
- `docs/hot-reload.md:25`、`:31`、`:123`、`:125` 仍有旧快照／DisplayPlan／重放叙述，与现行 UI 所有权要求冲突；历史正文待清理，本轮未采用。
- `catalog/zh-CN/main_menu.tsv:profile.heading` 的其他页面英文游戏名仍待更正。本轮13个标题、故事正文与对应列表已按“不真实的世界”统一译名。

修改前源码、词库、profile、README 和首轮记录保存在 `回收/20261019-all-scenarios-source/`，按原相对路径归档。既有未跟踪的作物分析文档保持原样。

## 交付状态

源码及词库修改、统一队列编译和正式热发布均完成，交付时间为2026-10-19 18:48:05（Asia/Shanghai）。

统一入口：

```sh
.toolchains/powershell/pwsh -NoProfile -Command '& ./build.ps1 -Toolchain Linux -Module catalog,adapter -Publish -Reload -TargetPid 3968932'
```

- 请求 `647f4313b98f407b9b2b24d20b0edcac`，批次 `35069b0b690843b0a95890df9f0e0fe2`。已读取对应 `build/.compile-queue/results/<请求ID>.json` 与 `batches/<批次ID>.log`，`Success=true`，日志无警告或错误；一次配置、一次增量构建，无清理。提交后至批次完成未修改本请求源码。
- 使用统一队列 Linux 默认 `/usr/bin/cmake`、`/usr/bin/g++`、`build/linux-x86_64`、正式 `package/`，Publish/Reload=true，TargetPid=`3968932`。没有绕过队列或创建平行运行副本。
- 正式事务 `1dc2eccb46974ed4a8d688270c15ccf2`；已读取 `build/linux-x86_64/stage/1dc2eccb46974ed4a8d688270c15ccf2/publication-result.json`，`success=true`、`runtime_requested=true`。
- PID `3968932` 先返回 `ReadyToPublish`，随后旧 Adapter、主词库、Linux profile、发布清单四件先移入 `回收/20261019-184805-1dc2eccb46974ed4a8d688270c15ccf2/package/`，再替换正式位置。已只读确认四件归档存在。Catalog 二进制未变，随词库参加热交接。
- 原进程返回 `Applied`，Adapter 第6代、Catalog 第5代。根启动器和驻留桥不变，没有关闭或重启游戏。回执只证明模块交接完成；现有确认页等待下一次自然原生输入返回刷新，不视为视觉验收。
- 以下源码／构建与正式文件 SHA-256 一致，并与正式 `package/release.json` 一致。

| 正式内容 | SHA-256 |
| --- | --- |
| Adapter | `aa5b6819be7e5a95b5e0cfb2c010302a422200336a199cf6b92f15c767eb9901` |
| 主词库 | `1805cf84cd53a0b0d4f4822bab722df086f1766c76f2855577bc3248f57dbac2` |
| Linux profile | `e076e51e228a61ae509d152d0e5c45fe3ecfa04fb91399b9ebe0bc494c4b0e43` |

全程不启动游戏、不模拟输入、不运行测试或产物，不创建测试脚本、测试工程、断言、保护、回退或兜底逻辑。静态分析、编译和发布不代替运行或视觉验收。
