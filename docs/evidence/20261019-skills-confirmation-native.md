# 2026-10-19 Linux 技能分配确认弹窗汉化

用户截图中技能页的“提升／降低”已汉化，但分配结束后的独立确认弹窗仍显示英文。原 `src/linux/skills.inc:skills_bindings` 仅接入 `TaitoRuutu`、`NaytaOptioRuutu`，漏掉 `option_points` 的四处原生构建调用；本次补齐，复用 `skills_text` 语义组件，不改变 ABI、状态结构或原生业务。

| 原文 | 中文 |
| --- | --- |
| ALL OPTIONS USED | 分配点数已用完 |
| Are you happy with this? | 你对这样的分配满意吗？ |
| Y.Yes. | Y.是。 |
| N.No, undo last and return. | N.否，撤销上次分配并返回。 |

`Y.`、`N.` 是原生键帽前缀，按原字符串复制，继续显示为 Y/N 按钮。没有改动键值、默认选择 N、空白分隔行或原有确认、撤销动作。

## 静态证据

目标为 Linux x86-64《不真实的世界》3.89 / Steam Build 25939378，原 ELF SHA-256 为 `4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。以下均为 ELF RVA；Ghidra 输出减去 `0x100000` 基址。

只读复用已有 Ghidra 工程，通过 `-readOnly -noanalysis` 提取 `option_points`、`LIST_Reset`、`LIST_Entry`、`LIST_Draw`、`LIST_Highlight`、`LIST_Go`、`Piirra_Ikkuna`，输出在本地 `build/analysis/skills-confirmation-linux-ghidra.c`。调用指令记录于 `build/analysis/skills-confirmation-linux.asm`。没有执行原生函数或游戏。

| 调用点 | 原生边界与本次处理 |
| --- | --- |
| `1EAB8 → F4AF0 LIST_Reset` | RSI 标题替换为中文显示参数。原七参数、窗口尺寸、颜色和 mode 6 保留；第七参数仍从原 Frame 栈读取。原函数将标题复制到自己的100字节记录。 |
| `1EACB → F4D00 LIST_Entry` | RSI 提示语借入中文。EDI 仍为 -1，由原生函数标为不可选择，复制到100字节显示槽。 |
| `1EAE6 / 1EB01 → F4D00 LIST_Entry` | RSI 借入原键帽前缀加中文后缀；EDI 仍为 Y/N。字符串由原生函数复制，不留 Mod 指针。 |
| `1EAD5 / 1EB0B → LIST_Entry` | 两个空白分隔行不修改。 |
| `1EAF0 → Set_LIST_Position(3)` | 默认 N 选项不修改。 |
| `1EB10 → LIST_Draw`；`1EB15 → LIST_Go` | 原生绘制、缓存保存／恢复、选择框、鼠标命中、输入与淡出保持。 |
| `1EB21..1EB4C` | N 沿原分支撤销 `SKILLIMPROVE_lastplus` 对应的一次提升并返回技能页，Y 原样返回；未修改点数、初始熟练度或技能数据。 |

原英文常量与内部数据不改写。修改只作用于上述四次原生文本构建参数；同一 `skills_bound` 通过显式 `key_suffix` 标志处理原有加减按钮与新增 Y/N 标签，提示语不走键帽拆分。没有扩大到其他 LIST 调用或对未知字段添加推测性分支。

## 中文度量、绘制与所有权

中文通过现有 Layout 编码和字形接口进入原生显示槽，不将 UTF-8 直接交给 ASCII 路径。标题为14字节编码，问题为22字节，最长的 N 标签含前缀共26字节，均小于100字节原生槽。

`LIST_Draw` 的 mode 6 调用 `Piirra_Ikkuna`，再由 `TekstiPalkki(mode 0)` 绘制标题；说明调用 `showtext`，选项调用 `Piirra_Nappain`。复用已确认的完整字形绘制与光标推进扩展：`13B760`、`13EA00`、`145264`、`145286`、`1452E3`，原生文字度量沿 `13B460` 与标题 `14709B`。游戏负责按钮绘制流程、行距、窗口尺寸与缓存。

`LIST_Reset` 清零 `List+8C` 的按字宽高亮标志，故本窗口选择框使用原面板宽度；`LIST_Highlight` 只对未变的 ASCII 键帽前缀计算偏移。没有第二字段 `|`，未引入中文按字节定位。中文标签进入游戏自己的列表记录，后续原生绘制与测量消费同一字符串。

字形在已接入输出密度的原生 screen 内即时绘制，沿既有原生缓存和上传路径呈现。未新增坐标表、行槽布局、页面快照、像素跟踪或延后文本重放。

## 刷新限制与审查记录

- `src/linux/skills.inc:skills_bindings` 的四处遗漏本次已整改；原技能页交付成功不能视为此弹窗已接入。
- `Piirra_Ikkuna:146A30` 在 `SHOW_TRANSPARENT` 非零分支可能不覆盖旧背景或只做透明混合。仅 `LIST_Draw` 不能作为本窗口完整清除旧字的依据。本次未将其加入 `redraw_language`，没有重入含技能修改与输入等待的 `option_points`、`TaitoRuutu`。已打开的弹窗及其原生显示记录等待原生重新构建；本次热加载不冒充即时刷新。完整纯重建边界待确认。
- `src/linux/adapter.cpp:glyph_request` 的原生阴影预算传递，以及 `src/linux/native_targets.cpp` 的非主菜单缩放重建限制，仍为既有待整改项，见 [Linux 字体密度记录](20261019-linux-font-density.md)。此次没有更改或宣称解决。

## 交付状态

源码和词库修改、统一队列编译、正式文件发布及已授权的兼容热加载均已完成，时间为2026-10-19 16:10:18（Asia/Shanghai）。

- 根入口：`.toolchains/powershell/pwsh -NoProfile -Command '& ./build.ps1 -Toolchain Linux -Module adapter,catalog -CMakePath /usr/bin/cmake -CompilerPath /usr/bin/g++ -BuildDirectory /home/lulika/workspace/urwcn/build/linux-x86_64 -Publish -Reload -TargetPid 3883506 -PackageDirectory /home/lulika/workspace/urwcn/package'`。提交前保存修改，批次完成前未继续修改请求源码。
- 请求 `a5d8a1836e7d4272a702bc9dace6cde7`，批次 `bfe139a87c054baca6feb694bba8bd70`。已读取对应请求、`build/.compile-queue/results/a5d8a1836e7d4272a702bc9dace6cde7.json` 及完整 `build/.compile-queue/batches/bfe139a87c054baca6feb694bba8bd70.log`：`Success=true`，一次配置、一次增量构建，无警告或错误。
- 正式事务 `e207c0753f3b497baf28e4917c13a7b7`；已读取 `build/linux-x86_64/stage/e207c0753f3b497baf28e4917c13a7b7/publication-result.json`，`success=true`、`runtime_requested=true`。正式更新 Adapter、主词库、Linux profile 与发布清单四件；Catalog 二进制未变化，随词库更新参加热交接。
- 四件旧正式文件先按原相对路径移入 `回收/20261019-161018-e207c0753f3b497baf28e4917c13a7b7/package/`，已只读确认文件存在。正式根启动器与驻留桥未改动，没有新增平行运行包。
- PID `3883506` 返回 `ReadyToPublish` 与 `Applied`，Catalog 第4代、Adapter 第3代。此回执证明业务模块交接完成；已经构建的旧弹窗文字仍按前述原生生命周期更新，不作为视觉验收。
- 已只读核对以下源码／构建与正式文件 SHA-256 一致，并与正式发布清单一致。

| 正式内容 | SHA-256 |
| --- | --- |
| Adapter | `3518c25ac23ce8982dfd57236a59485b867617f6df7528a9628e4e59e0b1741a` |
| 主词库 | `0f08f450590cc7eeaca77ee0d8cc4bb5f77f9bf3474f021c2dde14f02b0c1c60` |
| Linux profile | `b6022241589d59ce6ed3a01b642381cde7be9b59af97f9506b81ccb2bb844892` |

遵守项目要求，不启动、关闭或重启游戏，不注入、模拟输入或运行测试，不新增测试用例、断言、保护、回退或兜底逻辑。静态分析、编译和发布回执不代替运行或视觉验收。
