# 角色创建完成页的原生中文边界

2026-10-19（Asia/Shanghai）。对应用户截图中的完成标题、含姓名和民族的入世提示、芬兰谚语及来源、继续按钮。目标为 Windows x86《不真实的世界》3.89 / Steam Build 25939378；磁盘 `urw.exe` SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。本文地址均为 RVA，原始反汇编与 Ghidra 输出 VA 需减首选基址 `400000`。

只做源码阅读、磁盘 EXE 静态反汇编与离线反编译。没有启动游戏、注入新驻留层、模拟输入、运行产物或测试；没有创建测试用例、测试工程或断言。正式兼容业务热发布按既有授权使用驻留事务，实际结果见文末回执。

## 原生文本与完整语义

页面属于 `12F80` 角色创建函数的末尾，并非创建方式选择菜单。原生先完成角色业务，然后在 `13187` 调用 `1127C0` 绘制原背景，依次进入下列调用；游戏持有坐标、颜色、居中宽度、按钮与输入。

| 调用 RVA | 目标与实参 | 中文 |
| --- | --- | --- |
| `131D7` | `10E910`，栈 `(800, text, color, 1)` | 角色创建完成。 |
| `13264` | `10E910`，同上 | `{姓名} {民族}即将踏入不真实的世界。` |
| `132EB` | `10E910`，同上 | “世事总会教人些什么，至少也会教人慢慢走。” |
| `13320` | `10E910`，同上 | ——芬兰谚语 |
| `13334` | `114680`，栈 `(text)` | 按任意键继续 |

原字串位于 `1906E4/190704/190728/190774/190788`。`1321E → 10D0` 按原 `%s %s` 拼接 `Plr.name`（`A32A6E8`）与 `Plr.inhabitant`（`A32A6F6`）；`13230 → 10D0` 再按原 `%s is about to enter UnReal World.` 写到 `[EBP-408h]` 的 `400h` 临时区。两次原格式化均保留英文及原值。

只有 `13264` 的完整显示调用借入中文：姓名经既有 `native_name_input::display` 与 `decode_native` 保留中文 UTF-8 及原单字节北欧字母；原民族编号 `A32A6F5` 复用十民族组件，再与完整入世模板组合。截图中的 `Kaumolainen` 是民族“考莫人”，不是姓氏。Mod 不改写姓名、民族字段或原格式化缓冲；英文模式借用同一完整原文的显示编码。借用内存在该原生调用返回的 After 边界释放，无页面内容快照。

五个稳定组件为 `TextComponent::creation_complete_* = F10..F14`，Semantic 与中文 TSV 使用 `creation.complete_*` 五键。只有 enter 词条包含一个动态 `{value}`。`CreationKind::plain_button` 显式区分无动作前缀按钮，原告别页同类按钮保留相同语义；不会给继续提示插入原文前三字节，也不修改原按键动作。

## 原生度量、字形与目标

四个居中调用复用 `Scope::hud_centered`。`10E9FB` 的候选行宽、`10EA74/10EAF8` 的整行宽度及 `10EA95/10EB19 → 10E5A0` 完整文字均接已有真实字体度量。`114680` 继续沿既有原生普通按钮的宽度、字形、光标与背景路径。最终 `10E5A0 → 10DDB0` 当次完整字串在原生主面真实输出密度即时绘制，原生 `10E700` 的推进消费对应字宽。

没有固定坐标或行槽表、整页字段快照、独立 DisplayPlan、通用像素扫描、绘制贡献列表、Present 叠字或延迟重放。原生继续管理居中、行距、按钮几何、缓存与呈现。

本页新确认了 `D3D05` 调用前的高清目标迁移边界：外层 `12F80` 保留 EDI 的 `MapRGB` 函数指针和 ESI 的临时字符串池指针，`D3C80` 已结束主面上传，ESI 为 `PollEvent` 函数；未跨该边界保留主面/pixels 指针。重绘先调用既有 `native_targets::promote()`，随后原生背景、字色及全部文字重新读取当前主面。头文件及早期目标记录中“仅主菜单”的旧边界说明不可当作已覆盖本页的依据；本段与完整反汇编补充其适用范围。

## 已打开页面重建

`1333C → D3C80` 保留原调用不 Hook，因此 `[EBP+4] == image_base+13341` 能识别此页，包括热发布前已打开的窗口。沿既有 `D3D05 → D3BF0` 的 Before 事件，在下一次自然输入循环消费 pending；此事件是 call 的 Before，不是 inline_before。热加载、依赖变化及语言选择通过既有 invalidate 置位，新页面正常绘制标题即清除 pending。

重建完整调用 `12F80`，只在重绘标志下改下列原生续点：

| 原生边界 | 原字节/续点 | 作用 |
| --- | --- | --- |
| `12F96` | `89 0D <base+217ABC>` → `13187` | prologue、cookie 与 EBX/ESI/EDI 保存已完成；跳过角色生成、文件写入、确认等业务。 |
| `D3CDC` | 复用已有 `scenario_redraw_wait` → `D3D0F` | 原生已上传、呈现；在事件清理和阻塞输入之前进入该等待函数的完整 epilogue。 |
| `13341` | `33 C0 0F 1F 40 00` → `133C1` | `13339 ADD ESP,24h` 已清理显示实参；跳过姓名复制、界面状态修改及后续清理，保留完整寄存器恢复/cookie/退栈。 |

`13187` 后的 `1127C0` 只消费原栈 `[EBP+10h]/[EBP+14h]` 宽高；最末 `PUSH ECX` 填充槽未读取，不依赖跳过代码的 ECX。EDI、ESI 分别在 `131A9/131FF` 重新赋值，未用未初始化的先前角色业务寄存器。临时字符串池的原生索引由原显示格式化正常推进，不保存在 Mod。调用返回后继续外层原输入循环，既有输入返回与最终继续动作不变。Applied 回执只证明兼容模块交接，不能代替此重绘的画面验收；本次未主动触发输入边界。

## 可复核证据及既有待整改项

- `creation-complete-disassembly.txt`：完整 `12F80..133E8` 原生函数。
- `creation-complete-background-disassembly.txt`：`1127C0` 背景函数及实际栈字段。
- `creation-complete-string-bytes.txt`：五条原英文字符串的磁盘字节。
- `creation-complete-ghidra.c`、`creation_complete_Decompile.java`：既有 Windows Ghidra 工程 `-readOnly -noanalysis` 提取的两函数，离线提取退出码0，未修改游戏二进制。
- `credits-key-wait-disassembly.txt`：共享 `D3C80` 的上传、呈现、事件等待及 epilogue。

| 既有文件/位置 | 影响 | 状态 |
| --- | --- | --- |
| `ancestors-static.txt:185–187` | 将 `A72A6F6` 误称第二个姓名字段，要求保留而不译；与文化选择 `F9E1/F9E7` 的编号及民族表写入矛盾，会漏译本页民族。 | 本页不采用；历史正文仍待更正。 |
| `farewell-static.txt:109/128/140` | 已标失效的正文仍描述 Mod 行槽与 Present 合成；不能作为当前字形/布局实现依据。 | 本页采用当次原生调用；历史正文仍待清理。 |
| `native_targets.h:13`、`20261019-native-hd-target-boundaries.md:102` | 旧注释只确认主菜单迁移点，不能证明完成页迁移边界。 | 本记录补充完成页的具体静态依据；原记录保留历史上下文。 |
| `20261019-implementation-correction.md:20–21` | 宿主失败透传及事务失败后的透传语义仍有既有待整改项。 | 本次未扩展宿主及 ABI，不以本页交付宣称这些问题已解决。 |

## 源码、编译和正式交付

源码已接入五字段及完整动态身份、原生重建和 profile，编译与正式发布均完成。2026-10-19 22:02:22（Asia/Shanghai）的实际回执如下：

- 根入口 `build.ps1 -Module adapter,semantic,catalog -Publish -Reload -TargetPid 121728`，统一 MinGW、根 `.toolchains/x86/w64devkit/bin/cmake.exe` 与同目录 `g++.exe`、`build/mingw-x86` 和正式 `package/`。源码提交后至批次完成保持冻结。
- 请求 `f94bdbd49d8742709af7f771502d775c`，批次 `1aec37e7384c47d1bbe74fd2bbe48fd8`。已读取对应 `build/.compile-queue/results/<request>.json` 及完整批次日志，`Success=true`；一次配置、一次增量构建，三个目标均成功。保留既有 SDL 函数指针转换与 Semantic HUD/world 枚举分派警告，无编译错误。
- 正式事务 `9b90629e213143a293c064c1849d57db`，已读取 `build/mingw-x86/stage/<transaction>/publication-result.json`，`success=true`。替换正式 Adapter、Semantic、中文词库、Windows profile 和清单五件；旧五件先按原相对路径移入 `回收/20261019-220222-9b90629e213143a293c064c1849d57db/`，归档已实际存在。
- PID `121728` 返回 `ReadyToPublish` 和 `Applied`：Catalog 第2代、Semantic 第2代、Adapter 第4代。Catalog DLL 编译后与正式旧 DLL 相同，事务仍按所选兼容模块重载，以消费更新词库；该 DLL 不属于五件被替换文件。

| 正式文件（相对 package/） | SHA-256 |
| --- | --- |
| `modules/uwcn_adapter.dll` | `e55fa878111ff1257c8231bbd819ee9c6f9e80c1230cee98df7d9f400fc0fb32` |
| `modules/uwcn_semantic.dll` | `439c4b3be82d1a0f0484f0862bac4a763974ad62357ff9b463ac35246668c78f` |
| `catalog/zh-CN/main_menu.tsv` | `af7b11ec8eb35090ab94e4bc52f703cc0d67f2da40721a356a2a751c802489e7` |
| `profiles/urw-3.89-steam-25939378.json` | `752b372a66b1e61f21d17263f4ea65756008446a7d2aa9b82568acd405691cd2` |

只读核对所得 Adapter、Semantic 的正式文件与构建输出 SHA-256 相同；正式词库、profile 与源码相同，且四项均与正式清单一致。根启动器及驻留桥未替换，没有平行运行副本，没有要求手动卸载或重启。此页 pending 在下一次自然原生输入循环重绘；没有操作游戏或进行视觉验收，Applied 不作为画面结果。本次未运行产物或测试。
