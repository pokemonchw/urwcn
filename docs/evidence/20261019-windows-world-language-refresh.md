# Windows 世界生成页 Shift+F10 刷新修复

日期：2026-10-19（Asia/Shanghai）。对应用户反馈：随机世界生成界面按 Shift+F10 后仍显示中文。

目标为《不真实的世界》Windows x86 3.89 / Steam Build 25939378，原 EXE SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。以下地址为 RVA；原始反汇编的 VA 使用首选基址 `0x400000`。

## 原因与修正

`modules/adapter/native_language_input.cpp` 已在 `D1CD4` 消费真实快捷键并沿 `D2083` 返回原生非按键结果 `-2`。`module.cpp` 已切换 `chinese_enabled`，并经 `invalidate_windows_creation()` 设置世界页刷新请求。缺口位于 `windows_creation.inc::windows_creation_input()`：这里只处理情境选择、确认和游戏进程，未处理世界页的当前输入等待。

旧实现只在 `60D32` 的放大按钮构建期间检查刷新请求。当前 `D1120` 不因该非按键结果退出，因此单按快捷键不会到达这个构建点；必须等原菜单返回后才有机会刷新。该入口还在按钮绘制中递归重建整页，并重复绘制外层余下按钮。本次移除这一递归入口。原 `CFAF0` 按动作身份查找已登记按钮，不能把重复绘制推断为必然重复登记控件。

现改用已有的 `D12B4` 原生输入返回 Hook，通过 `[EBP+4] == image_base+60EA8` 精确识别世界页。`60EA3 → D1120` 的原 CALL 保持未 Hook，适用于更新前已经打开的页面。刷新发生在真实输入返回边界，保留 EAX 和原生输入控制流，不生成按键或 SDL 事件。

世界当前图例开关是外层 `60B60` 的 EDI。`D1120` 在 `D1123` 分配 `434h` 局部空间，随后 `D1138`、`D1157`、`D1158` 依次保存 EBX、ESI、EDI，因此该值从当前原生帧 `[EBP-440h]` 读取。不能使用已经被输入函数占用的现场 EDI，也不保存原生帧指针。

刷新复用原有 `creation_rebuild(3)`：

1. 完整调用 `60B60` 建立原生栈帧；`60B73 → 60BB8` 绘制原背景和标题。
2. `60C03 → 6109F` 跳过淡变、日志、随机数初始化、缩放／偏移／文化重置、世界生成和随机起点。
3. `6109F..610FB` 绘制当前地图、动态缩放、比例尺及原开关控制的文化图例；`610FB → 60CC2` 进入原菜单初始化和十二个按钮构建。
4. `60E93 → 6113D` 经完整原尾声返回，避开输入等待、地图释放和退出业务。恢复原生当前选择，再沿 `D1189` 对应的工作面复制、`D0650` 高亮和 `10B720` 呈现更新游戏自己的缓存。

正常完成控件构建的 `60E93` 同时清除刷新请求，首次进入已按当前语言构建的页面不再额外重建。十二个控件的原动作和顺序不变；`D1120` 的 `[EBP-430h]` 原选择基线保持原值。`CF790` 不写 `5F54DF0` 输入活动标记，没有新增全局输入状态快照。

文本、度量、按钮宽度、鼠标命中、缓存和呈现仍使用原生调用；没有 Mod 坐标、页面快照、像素跟踪、延后文字重放或额外布局。没有新增 Hook、改变 Host ABI 或状态交接格式。本次只修改 Windows Adapter；Linux 世界页仍以其独立记录为准。

## 静态依据

- `docs/evidence/windows-creation-world-disassembly.txt`：`60B60..6114F` 的完整函数及 `60EA3` 输入调用；`60450` 动态缩放／比例尺；`610BF → E11B0` 图例。
- `docs/evidence/20261019-character-creation-disassembly.txt`：`D1120` 完整 prologue、寄存器保存槽及 `D1189` 原缓存复制。
- `docs/evidence/20261019-language-setup-input-disassembly.txt`：`D12B4` 原输入返回边界。
- `docs/evidence/load-saved-character-menu-init-disassembly.txt`：`CF790` 菜单初始化写入范围。
- `docs/evidence/windows-creation-ghidra.c`：世界页、原菜单输入循环及按钮按原动作身份去重。

旧 [Windows 同步记录](20261019-windows-creation-sync-native.md) 中“下次到达 60D32”是本次修正前的延迟刷新行为，现已更新，不作为当前即时切换的实现说明。既有历史 DisplayPlan／行槽方案及其待整改项仍以 [语言切换记录](20261019-language-toggle.md) 为准，本次不采用这些方案。

## 交付状态

源码修改、静态审查、统一队列编译、正式文件发布及已授权的兼容热加载均已完成。2026-10-19 21:49:18（Asia/Shanghai）的回执如下：

- 调用根 `build.ps1 -Module adapter -Publish -Reload -TargetPid 121728`；使用默认 MinGW、项目 `.toolchains/x86/w64devkit/bin/cmake.exe`、同目录 `g++.exe`、`build/mingw-x86` 和正式 `package`。本次 Adapter 源码提交后至批次结束保持冻结。
- 请求 `c3ee1607252141edb7852323d4994b17`，批次 `13ea90c136d94ce594eb7e4687ed6e54`。已读取对应 `build/.compile-queue/results/<request>.json` 和完整批次日志，`Success=true`；一次配置、一次增量构建。保留既有 SDL 函数地址类型转换警告，无编译错误。
- 正式发布事务 `559148cf474448cc8d925a41f28b47bf`，已读取 `build/mingw-x86/stage/559148cf474448cc8d925a41f28b47bf/publication-result.json`，`success=true`。替换正式 `package/modules/uwcn_adapter.dll` 与 `package/release.json`；旧两件先按原相对路径移入 `回收/20261019-214918-559148cf474448cc8d925a41f28b47bf/`。
- 当前 PID `121728` 返回 `ReadyToPublish` 及 `Applied ... adapter:babdf354c2672146bfa9100d6045de940d888d4bdeef169d7ce56303a772e8c6:3`。正式 Adapter、构建产物及事务暂存三者 SHA-256 相同，且与运行时回执及正式清单一致。

根启动器和驻留桥保持原正式文件，没有建立平行运行副本，也没有要求退出、重启或手动卸载。热发布事务的 Applied 只证明模块交接完成；世界页画面在下一次真实原生输入返回边界消费 pending，本次没有主动触发该边界或进行视觉验收。

未启动游戏、注入新驻留层、模拟输入、运行交付产物进行验证或运行测试；未创建测试用例或断言，也没有新增保护、回退或兜底分支。
