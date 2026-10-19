# 鸣谢窗口原生汉化

日期：2026-10-19。对应用户截图 `codex-clipboard-00ce4b3a-02c6-4b99-b3e2-ea4c8e9abc83.png`，目标 UnReal World 3.89 / Steam Build 25939378。以下地址均为 RVA。依据现有反汇编与原始字节实施，没有启动游戏、注入、模拟操作或运行测试，也没有创建测试用例或断言。

## 原生显示接入

本轮新增标题“致谢与贡献者”、24 个原生正文 append 语义及“按任意键继续”，保留全部姓名及顺序、Steam、Wiki、原生 `<br>`。`TextComponent::credits_title..credits_press_key` 使用显式 `0x700..0x719`，由 Semantic 和正式词库提供中文。`credits_text_calls.h` 只登记原生调用地址与语义组件，不包含位置、行槽、整页文本或绘制快照。

| 原生边界 | 接入方式 |
| --- | --- |
| `125E6E → 1244F0` | 全窗口作用域；原函数仍负责背景、正文、按钮及等待。 |
| `124511 → 116270` | 借用标题；共用 `116631` 实际字宽和 `11665C` 原生居中绘字。 |
| `12452F..12464F` 的24个已确认 `162300` 调用 | 每次同步借用对应编码译文；原生 tokenizer 立即消费。 |
| `124523`、`124547` | 两次独立 `<br>` 完全保持，首次 `ECX=1` 仍由原生清空并构建 token 存储。 |
| `124669 → 10EB40` | 段落作用域启用既有 `10EE68` 换行宽度、`10EF57` 推进度量及 `10EF87` 单词绘制。 |
| `12467D → 114680` | 借用完整按钮标签；共用原生瓦片数量、完整字符绘制及光标推进扩展。 |
| `124685 → D3C80` | 正常进入仍原生等待；仅完整函数的同步重绘跳过该次等待。 |

确切指令见 [完整窗口](credits-disassembly.txt)、[段落](credits-paragraph-disassembly.txt)、[tokenizer](credits-append-disassembly.txt)、[标题](credits-title-disassembly.txt)、[按钮](credits-button-disassembly.txt)。新增 Hook ID 为 `180..184` 和 `0x700..0x717`；标题、按钮、等待循环的既有共享 Hook ID 及 HookSpec 不变，不重复覆盖同一地址。Scope 原数值13、14只将名称改为 `titled_panel`、`plain_button`；新增 Credits 为15，既有 Active 保存格式、HDA3 后缀和 Host ABI 1 不变。

正文继续使用原生分词、换行、行距、颜色与返回值。词库中长句的空格是原生分词边界，不指定哪行显示；编码沿既有每个非 ASCII 字符两字节的传输规则，规避原 wrapper 会改写的 C4/E4/F6。固定译文的连续 token 在原生 `0x82` 字节槽容量内，标题和按钮在各自原生缓冲内；没有向按字节计宽的 ASCII 链裸传 UTF-8。`10E700` 的原生光标仍消费同源真实字宽。

按钮标签保留两端空格。既有 `native_button.h` 在 `1146DD` 以实际宽度换算原8单位背景瓦片数量，在 `1148E9` After 提供完整传输字符，在 `11498A` 使用完整前缀宽度差推进。按钮背景、端盖及原输入动作继续由游戏控制。段落4个参数与按钮1个参数仍由原 `124682 ADD ESP,14h` 一并释放；Mod 不插入额外清栈。

## 姓名编码

[原字节](credits-string-bytes.txt:88) 的 `Jarmo Mäenpää` 使用 Latin-1 `4D E4 65 6E 70 E4 E4`；[原文字 wrapper](credits-text-disassembly.txt:43) 将 E4 映射为 CP850 84。仅 `credits_countrymen_1` 的已确认显示输入先按 Latin-1 转 UTF-8，再进入现有传输编码。中英文模式均正确保留这三个 ä，原 PE 字符串不变；没有全局编码探测或猜测性回退。

## 绘制与原生重建

字形在原生组件的文字调用中，按 `61BBB10` 的真实物理尺寸立即绘入原生目标。游戏拥有面板、排版、缓存、上传和呈现；不增加固定坐标表、DisplayPlan、SDL Present 叠字、像素跟踪或文本贡献重放。

`Shift+F10` 和依赖更新沿 `invalidate()` 请求 Credits 原生重建。依据 [菜单原调用](credits-menu-disassembly.txt:366)，Credits 的 `125E4D..125E7D` 与 About 使用同一原生背景保存/恢复。同步重绘执行 `10DA60 → redraw_menu() → 10DA10 → 完整1244F0 → 10B720`，同时更新后方菜单及原生 `A1C2014` 背景。只在本次同步调用中跳过 `124685` 的输入等待，仍执行 `12468A POP ECX; RET`，完整函数栈平衡。该链包含原生中间呈现，不据静态分析承诺无闪烁。

全窗口的长等待由驻留桥 Before/After token 管理，无业务 DLL 栈帧跨越等待。对于更新前已打开、没有 Credits scope 的窗口，共用 `D3D05` 边界检查 `D3C80` 的原返回地址 `image_base+12468A`，处理 `credits_refresh_pending`。若仍停在原生事件等待，须自然事件令原流程到达此边界；不发送模拟输入、不关闭或重启游戏，不将 Applied 回执说成窗口已经换字。依据见 [等待循环](credits-key-wait-disassembly.txt:105)。

## 历史冲突和待整改

| 文件及位置 | 影响 | 本轮处理与状态 |
| --- | --- | --- |
| `credits-static.txt:20–24`、`:173–188` | 拆成28字段并规定固定中文行槽、负2偏移和自定标题中心，违反原生布局所有权。 | 新实现不采用；当前接入由本记录替代。旧文档相关正文仍待清理。 |
| `credits-static.txt:119–122`、`:137–170` | 保留英文宽度/推进，仅抑制原字形，中文布局与原生语义分离。 | 当前原生计宽、折行和完整字符推进接入真实度量；旧建议废止。 |
| `credits-static.txt:205–225`、`credits-delivery.txt:7–16` | 用 Present 合成并复用固定页面计划；旧发布不能证明当前实现符合要求。 | 当前 modules 无该旧 Credits 实现；禁止复用，历史正文待清理。 |
| `docs/design.md:21`、`docs/hot-reload.md:25` | 历史范围继续描述旧鸣谢方案。 | 文件已有历史废止声明；本轮以此记录为准，旧正文待清理。 |
| `src/loader/hook_host.cpp:39`、`:73` 及宿主错误透传 | 既有业务错误后的原指令透传仍是前轮记录的待整改项。 | 本轮不修改驻留桥，不以鸣谢编译和发布证明全项目合规。 |

修改前的源码、词库与相关文档保存在 `回收/20261019-credits-source/`，按原相对路径保留。

## 交付状态

源码修改和静态审查已完成。2026-10-19 08:15:05（Asia/Shanghai）完成统一队列编译、正式文件发布和兼容业务热交接。

- 编译：根 `build.ps1 -Module adapter,semantic,catalog -Publish -Reload -TargetPid 65412`；显式统一使用 MinGW、`.toolchains/x86/w64devkit/bin/cmake.exe`、同目录 `g++.exe`、`build/mingw-x86` 与正式 `package`。一次配置、一次增量构建，没有清理构建树；三个请求目标全部完成。日志保留既有 `GetProcAddress` 到 `GetRGB` 函数指针转换警告，没有编译错误。
- 请求 `a5ccf43f77b4480993ca5f3693b4817d`，批次 `3a8077d74baf4b8c81163a6d107dec37`。已读取 `build/.compile-queue/results/a5ccf43f77b4480993ca5f3693b4817d.json` 和对应批次完整日志，`Success=true`。
- 正式事务 `47b3089b3f5a48fdb39bc09ef77963a3`；已读取 `build/mingw-x86/stage/47b3089b3f5a48fdb39bc09ef77963a3/publication-result.json`，`success=true`。Adapter、Semantic、词库、构建适配和发布清单五件旧文件先移入 `回收/20261019-081505-47b3089b3f5a48fdb39bc09ef77963a3/`，再放入正式位置。Catalog DLL 编译后内容与正式版相同，保持原文件，但因词库变化参与热交接。
- 发布前只读模块清单确认 PID `65412` 加载本项目正式驻留桥和六个业务模块。事务收到 `ReadyToPublish` 和 `Applied`；Catalog 第3代、Semantic 第3代、Adapter 第6代，回执身份与正式文件一致。
- 只读核对正式清单10项 SHA-256，全部一致；正式词库包含26条 `credits.*`。启动器仍为根 `uwcn_launcher.exe`，业务 DLL 和词库位于正式 `package/`，没有平行修复包。

| 正式文件（相对 `package/`） | SHA-256 |
| --- | --- |
| `modules/uwcn_adapter.dll` | `62d2e6fb77372ab83b06450793bee65326cafe562b9865c32a54b17b778a30d9` |
| `modules/uwcn_semantic.dll` | `2d826d31f2a07d6d93386d2e8ab0327496926f237ad34426983d7d2a469bc218` |
| `catalog/zh-CN/main_menu.tsv` | `558d5e2f38b5d03774faa158cb84e59f6168598a20c66d7551ec9dea35af20f7` |
| `profiles/urw-3.89-steam-25939378.json` | `e51c6308dbf87e14979f7ad90daa94011a8bf19af900f8375c804adf64fa46ef` |

Applied 表示模块交接完成，不是视觉验收。没有自行启动游戏、注入、模拟操作、运行产物或测试；旧已打开窗口的原生刷新边界仍以上文为准。
