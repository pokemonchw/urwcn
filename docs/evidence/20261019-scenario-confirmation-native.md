# 2026-10-19 Linux 开局情境确认页汉化

本记录保留首轮单情境接入及发布回执。用户随后要求每个选项均处理，当前全部13项的范围、实现及交付状态以 [全部开局情境记录](20261019-all-scenarios-native.md) 为准。

对应截图 `codex-clipboard-54f100a8-62d9-47b7-8a7e-218f4921d248.png`：标题“开局情境：不真实的世界”、确认提示、是／否按钮以及完整故事，共19项词库记录。故事的十五条原始非空记录组成四段叙事和一段情境说明，编号标识源记录，不是屏幕行槽。原生 `<Y>` / `<N>` 高亮快捷键和输入动作保留，中文后缀为“是”／“否”。

## 静态依据

目标为不真实的世界3.89、Steam Build 25939378、Linux x86-64；原 `urw3-bin` SHA-256 为 `4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。以下均为 ELF RVA。

只读复用既有 Ghidra 工程及 `EquipmentDecompile.java`，使用 `-readOnly -noanalysis` 提取函数，没有执行游戏或交付产物。依据文件保存在本地：

- `build/analysis/scenario-confirmation-linux-ghidra.c`：`get_camp`、`show_scenario`、`LIST_ButtonSpotEntry`、`Piirra_Nappain`、`SANATAULUKKO_Lisaa`，五个函数均已提取。
- `build/analysis/scenario-confirmation-controls-linux.asm`：原故事生成、问题、按钮和选择分支。
- `build/analysis/scenario-confirmation-story-linux.asm`：故事读取、图片选择、标题、段落表构建及绘制。
- `build/analysis/scenario-confirmation-input-linux.asm`：`LIST_Go` 栈布局、缓存、选择框与输入返回边界。
- 安装目录的 `RNDCAMP.0`：第4至16、18至19行是十五条非空故事源记录。第7、11、15行以两个空格开头，原显示函数为它们添加 `<br>`；空行和最后的 EOF 空读取仍由原生处理。

`get_camp:1CDC0` 将 `Scenario: ` 和英文情境名、图片、故事写入角色的 `story.txt`，然后调用 `show_scenario:124190`。本次不修改任何文件读写参数、内部源记录、图片选择字符串或情境编号。中文只在下列显示参数中借入：

| 原生调用 | 本次接入与保留行为 |
| --- | --- |
| `1244B8 → 1471A0 winbox` | R8 借入中文标题；七个参数包含原栈上的颜色值，背景透明状态、尺寸和标题绘制保持原生。 |
| `124565 → 1AFE00 SANATAULUKKO_Lisaa` | RSI 借入对应故事源记录的中文，保留原 `<br>`；原 reset/append 标志不改。 |
| `1245A7 → 13ECE0 showtext_sanataulukko` | 不修改调用，游戏自己决定正文的折行、行高、颜色和区域。 |
| `1CF17 → 13E8B0 showtext` | RDX 借入确认提示，原样保留位置、颜色和阴影参数。 |
| `1CF5E / 1CF79 → F4F50 LIST_ButtonSpotEntry` | RCX 借入 `<Y>是` / `<N>否`；EDI 的 Y/N 动作值不改。原函数通过同一个完整标签绘制按钮、调用 textwidth 并生成选择和鼠标几何。 |

SDK 新增 `scenario_confirmation_text=0xC21`，Semantic 查询 `scenario.confirm.*`；主词库新增19项。既有枚举值、Host ABI 2、状态格式和驻留桥不变。

## 中文度量与 UI 所有权

正文用既有 Layout 双字节编码和 `native_paragraph_words` 提供完整中文字符词元。`13EEC3`、`13F00F` 的宽度／光标扩展与 `13EF3D` 的中文分词空格处理继续由原生段落调用消费。没有将 UTF-8 字节交给原生 ASCII 字形索引。

标题含 NUL 为23字节，提示21字节，带原生高亮标记的按钮各6字节。最长故事记录在分词前含 NUL 为75字节，分词后每个中文字词元只有2字节，小于130字节的原生词元槽。标题和按钮沿原生1024字节临时缓冲；逐字按钮缓冲为100字节。

原按钮无句点分隔符，`Piirra_Nappain` 的既有 `1452E3` 扩展按完整文本宽度计算原生8像素边框片数，原生代码再扣除 `<`、`>` 标记的两个单元。`145264` 和 `145286` 负责完整字符与同源光标推进；`LIST_ButtonSpotEntry` 通过 `textwidth` 得到同源宽度，保留原生标记修正与选择／命中流程。没有复制按钮坐标或让原生 UI 消费 Mod 布局。

字形在已确认实际输出密度的原生 screen 内同步生成并提交。游戏持有背景、图片、菜单缓存及已经绘入的像素。没有页面字段快照、固定坐标表、像素记录或 SDL Present 重放。

## 已打开确认页的刷新

复用情境选择页已有的 `F871F` Hook。原 `LIST_Go` 保存六个寄存器并分配 `0x428` 字节，当前原生 `RSP+0x458` 的单一调用返回槽为 `1CFD5` 时才刷新确认页。`1CFD0 → LIST_Go` 不 Hook，因此发布前已经打开的页仍能识别。

1. 调用原生 `LIST_Position:F6100` 读取当前选择。
2. 只进入原生 `1CEFC..1CF7E` 显示片段：完整 `show_scenario` 读取既有英文故事并重建背景、图片、标题、正文，随后原问题、`LIST_Reset` 和两次按钮调用重建控件。
3. `src/linux/redraw.S` 保留中段入口所需的调用前栈对齐。原 `LIST_Reset` 的临时第七参数由原两次 POP 平衡；最后按钮 Hook 完成原调用后，直接返回此片段的包装函数。
4. 跳过 `get_camp` 前半段的故事文件创建、玩家路径复制，以及后半段的输入等待和选择结果处理；不消耗随机数，不推进开局业务。
5. 用原 `Set_LIST_Position:F6110` 恢复选择，依次调用原 `save_menubuf:13D5A0`、`LIST_Highlight:F3F80` 和 `Flip:13FE50`，与 `LIST_Go` 的缓存先于选择框顺序一致。
6. Hook 重现原 `MOV ESI,1`，RAX 保留真实输入结果，继续原生输入处理。

刷新标志描述新模块、依赖变化及语言差异，不保存整页内容。故事身份及源记录计数在每次原生标题构建时重新确定；新故事身份字段只用于不含等待的同次绘制，不改变跨热加载序列化格式。

页面在下一次自然 `getkey` 返回时刷新；热发布的 Applied 只表示模块交接完成，不等于已经可见刷新，不模拟事件唤醒。首次进入和后续开局介绍重用同一 `show_scenario` 显示接入。

## 审查与整改状态

- `src/linux/adapter.cpp:scenario_title` 原来把 Linux 标题与 `THE VILLAGE` 比较，但静态确认实际读入 `Scenario: THE VILLAGE`；影响为既有村庄汉化分支未命中。本次已按真实记录修正，并将记录计数重置放到共享标题边界，覆盖确认页与后续介绍页。没有对未知标题添加猜测性处理。
- `src/linux/adapter.cpp:glyph_request` 仍未完整传递原生阴影预算；`src/linux/native_targets.cpp` 的活动页面密度重建仅在已确认的主菜单边界完成。影响为阴影占位与非主菜单途中缩放的密度一致性；既有待整改，本次不宣称解决。
- `docs/hot-reload.md:25`、`:31`、`:123`、`:125` 仍含页面快照、DisplayPlan 布局及重放叙述，与现行 UI 所有权规则冲突。影响为可能误导后续实现；历史正文待清理，本次未采用。
- `catalog/zh-CN/main_menu.tsv:profile.heading` 仍含英文游戏名；既有文化选择页译名问题待后续更正。本页标题与故事正文均使用“不真实的世界”。

修改前八份源码／词库／profile／README 已按原相对路径存入 `回收/20261019-scenario-confirmation-source/`。既有未跟踪文件 `docs/evidence/20261019-crop-growth-analysis.md` 保持原样。

## 交付状态

源码修改、统一队列编译、正式文件发布及已授权的兼容业务热加载均已完成，交付时间为2026-10-19 18:42:31（Asia/Shanghai）。

统一入口：

```sh
.toolchains/powershell/pwsh -NoProfile -Command '& ./build.ps1 -Toolchain Linux -Module catalog,semantic,adapter -Publish -Reload -TargetPid 3968932'
```

- 请求 `eacf1988984c482ab7a1fb62e76aa120`，批次 `0fc53d5ede184decbe73527effb27799`。已读取对应 `build/.compile-queue/results/<请求ID>.json` 和 `batches/<批次ID>.log`，`Success=true`；一次配置、一次增量构建，未清理构建树。提交后至批次结束未修改本次源码。
- 队列参数为 Linux、`/usr/bin/cmake`、`/usr/bin/g++`、`build/linux-x86_64`、正式 `package/`、Publish/Reload=true、PID `3968932`。未绕过队列或建立平行运行目录。
- 编译保留 `modules/semantic/semantic.cpp:11` 既有15条 HUD/world 枚举未列入 key switch 的 `-Wswitch` 警告；这些组件在 invoke 的独立 HUD 分支派发，本次新增组件已显式列入 switch。日志没有编译错误，不将成功写成无警告。
- 发布事务 `0fab878c436845faa01f8e38a214cefb`。已读取 `build/linux-x86_64/stage/0fab878c436845faa01f8e38a214cefb/publication-result.json`，`success=true`、`runtime_requested=true`。
- PID `3968932` 先返回 `ReadyToPublish`；旧五件按原相对路径移入 `回收/20261019-184231-0fab878c436845faa01f8e38a214cefb/package/` 后，正式更新 Adapter、Semantic、主词库、Linux profile 和发布清单。已只读确认归档存在。Catalog 二进制内容未变化，随词库参与热交接。
- 该进程随后返回 `Applied`，Adapter 第5代、Catalog/Semantic 第4代。没有修改根启动器或驻留桥，没有关闭或重启游戏；已有画面仍按上节的下一次自然输入返回边界刷新。
- 以下四件源码／构建与正式文件 SHA-256 一致，且与正式 `package/release.json` 一致。

| 正式内容 | SHA-256 |
| --- | --- |
| Adapter | `09b07009780c742cf944e9ccba89f818087a900ae884d91780cb9d21090c1fa2` |
| Semantic | `e1ee015bab20a950f1eba7d1919ffe1a1ceef399a78a54089ec65890a1f47a0e` |
| 主词库 | `01ca7d3b048156cf885672acc9b96b56224523e7ee134990b39dae1adf8f5a7c` |
| Linux profile | `a470e65e146c4b2e3b323c2b15d812e3d17229da3db7c86064bffd1fc185c0fa` |

没有启动游戏、运行产物或测试，没有模拟输入、建立测试脚本、测试工程、断言、保护、回退或兜底逻辑。编译仅用于交付，发布结果不代替运行或视觉验收。
