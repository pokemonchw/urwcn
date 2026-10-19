# 载入角色窗口的原生文本边界

2026-10-19（Asia/Shanghai）。对应用户截图的 `LOAD SAVED CHARACTER`、`No saved files!`、`Press a key...` 三个字段。本文记录只读静态证据与接入范围，编译和正式发布结果由实际交付回执另列；没有启动游戏、注入运行中的游戏、模拟输入、运行测试或运行交付产物，也没有创建测试用例或断言。

目标为 UnReal World 3.89 / Steam Build 25939378，磁盘 `urw.exe` SHA-256 已只读取得：`e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。本文地址为 RVA，反汇编、Ghidra 输出中的 VA 使用首选基址 `0x400000`。

## 业务与窗口生命周期

主菜单 `125C2B` 先将当前主面保存到原生子窗口背景 `A1C2014`，`125C30 → 124E90` 进入载入角色窗口，返回后 `125C35 → 10DA60` 恢复背景。这与既有主面高清资源及原生背景复制链共用生命周期，不需要另建页面图像或内容快照。

`124E90` 初始化原生菜单并枚举存档目录。`124EE5 → CF790` 传 ECX=0、EDX=`1AFC3C`（原英文标题）；其余五个栈参数依次为原生 x、y、w、h、kind，kind=8。`CF790` 复制标题到原生菜单字段 `5F54A38`、清空行计数并保存 kind 到 `5F54AA4`。本次保留这些原英文内部数据与原尺寸。

原函数扫描目录，并通过原读取调用取得存档头后，用 `124F8D → CF990` 把角色姓名加入原菜单行。数量为零时走截图分支：

1. `124FE7 → CFFB0` 构建面板和标题。
2. `12501E → 10E5A0` 显示无存档提示。
3. `125054 → 10E5A0` 显示按键提示。
4. `12505C → D3C80` 等待原生按键，然后直接返回调用者。

有存档时使用同一标题和面板：原函数追加空行及动作值 `0x1B` 的 `<ESC>.Exit` 行，经 `12508D → CFFB0` 绘制，再由 `125092 → D1120` 处理原选择和输入；选中的目录名由原代码写回其原业务字段。角色姓名、目录、文件内容、行选择和退出动作不因标题翻译而改变。截图没有提出翻译该列表退出行，本轮三字段接入也不借题增加它。

这不是独立的无副作用绘制函数。`124E90` 包含存档枚举、读取和等待输入；不能在语言切换时重入整个函数冒充原生重建。当前证据没有确认供此页单独使用的完整重建边界。处于已绘窗口中切换语言，不代表既有缓存会立即重建；新的译文在下一次正常原生构建中进入本页。

## 标题的真实绘制链

此窗口使用 `115E70`，并非另一种面板函数 `116270`。准确路径为：

`124FE7 / 12508D → CFFB0 → D00E4(kind=8) → D01B7(push flags=4) → D01A5 → 115E70 → 116240(push mode=2) → 116253 → 1157B0 → 1158E4 → 115A94 → 10E5A0`。

`D0404` 是原菜单 kind-2 的跳表，第六项为 `D01B7`。`115E70` 的 flags=4 既不设置 `0x20`，也不设置 `0x80` 或 `0x10`，因此选中标题 mode=2。`1157B0` 通过 `115AA4` 跳表进入 `1158E4`，画原标题框后使用原生左对齐参数。该路径不进入 mode=5/10 的 `strlen × 8` 标题居中分支。

两个 `CFFB0` 调用仅标记本页标题绘制作用域。在该作用域内，共享 `115A94` 当次完整文本参数借入中文；函数之外的其他菜单标题保持自己的流程。此处替换足够晚，上游 `CF790` 和 `115E70` 的复制及非空判断仍消费原英文内部标题；不存在把 UTF-8 字节长度用于原生标题居中的问题。`115A94` 传 ECX=x、EDX=y、栈 `(text, mapped_color, outline=1)`；中文字形接入已有完整文字绘制及实际字宽光标扩展。

## 文本与补丁依据

| 原文字串 RVA | 原文字段 | 已接入中文 |
| --- | --- | --- |
| `1AFC3C` | `LOAD SAVED CHARACTER` | 载入已保存角色 |
| `1AFC54` | `No saved files!` | 没有找到存档！ |
| `1AFC64` | `Press a key...` | 按任意键继续…… |

| 调用 RVA | 原字节 | 原目标 | 作用 |
| --- | --- | --- | --- |
| `124FE7` | `E8 C4 AF FA FF` | `CFFB0` | 无存档分支的面板作用域。 |
| `12508D` | `E8 1E AF FA FF` | `CFFB0` | 有存档分支的同一面板作用域。 |
| `115A94` | `E8 07 8B FF FF` | `10E5A0` | 只在上述作用域借入中文标题，保留共享调用。 |
| `12501E` | `E8 7D 95 FE FF` | `10E5A0` | 无存档提示完整文字调用。 |
| `125054` | `E8 47 95 FE FF` | `10E5A0` | 按键提示完整文字调用。 |

后两个调用均传 ECX=x、EDX=y、栈 `(text, mapped_color, outline=1)`，由调用方清理12字节；调用前没有文本字节长度计算、换行或文本居中。每次翻译只借给这次原生显示调用。借用编码、实际字体度量与即时绘字继续沿已有 `10E5A0` 和 `10E700` 扩展；中文字形在原生主面真实输出密度即时提交。原生面板、行背景、选择框、鼠标命中、输入和表面缓存仍由游戏管理。

源码使用 `TextComponent::load_saved_title/empty/press_key = A00/A01/A02`。Adapter 的 `A00/A01` hook 为上述两个面板作用域，`A02/A03` 为两个正文调用；共享 `115A94` hook 仅在 `Scope::load_saved_panel` 内借入标题。Semantic 和中文 TSV 以三个稳定语义键提供译文，原生菜单标题和菜单全局字段没有改写。安全编码含终止符的长度依次为15、15、17字节，均在原 `10E5A0` 的 `0x12C` 临时文本边界内；没有为此添加截断、猜测性保护或回退分支。

没有新增固定坐标/行槽表、整页字段快照、独立 DisplayPlan、通用像素跟踪、Present 叠字或延后文字重放。字体光栅缓存不保存本页位置与内容序列。

## 可复核的静态文件

- `load-saved-character-disassembly.txt`：包含完整 `124E90..1250DF` 及相邻代码，直接显示两个业务分支和文本参数。
- `load-saved-character-menu-init-disassembly.txt`：`CF790` 原标题复制、kind及状态字段。
- `load-saved-character-title-disassembly.txt`、`load-saved-character-panel-disassembly.txt`：`CFFB0` 入口及 kind分派。
- `load-saved-character-legacy-panel-disassembly.txt`：`115E70..11626B`，flags和标题mode选择。
- `load-saved-character-title-text-disassembly.txt`：`1157B0..115AA2`，mode=2左对齐与完整文字调用。
- `load-saved-character-parent-disassembly.txt`：主菜单保存、进入、恢复路径。
- `load_saved_character_Decompile.java` 与 `load-saved-character-ghidra.c`：离线 Ghidra 提取脚本与完整函数输出。反编译推断的函数原型不替代机器指令中的寄存器/栈契约。

本次独立项目 `build/load-saved-ghidra/uwcn-load-saved` 使用 Ghidra 12.1.4 PUBLIC 和 JDK 25.0.4.1+1，以专用 settings/cache 导入磁盘 EXE。自动分析耗时123秒并成功，七个指定函数均导出，后续分析、项目保存和导入也成功，进程退出码0。日志为 `load-saved-character-ghidra.log`，提取没有编译或运行游戏代码。

完整反编译对照确认：`load-saved-character-ghidra.c:8` 的 `124E90` 保留目录读取和无存档/列表双分支；`:238` 的 `CFFB0` 明确 kind=8 选择 `115E70(flags=4)`；`:379` 的 `115E70` 根据该 flags 选择 mode=2；`:505` 的 `1157B0` 在 mode=2 不执行字符串计数分支；`:645` 的主菜单 case0 使用原背景保存、窗口调用与恢复。Ghidra 个别调用显示省略了寄存器参数，例如 `124E90` 对 `CF790` 的反编译调用没有列出标题寄存器，正文 `10E5A0` 原型也缺坐标/outline；这些参数已由同目录原始指令核对，未把不完整的推断原型用于Hook ABI。

## 读到的历史说明冲突

| 文件及位置 | 影响 | 状态 |
| --- | --- | --- |
| `main-menu-static.txt:21` | 旧说明主张保持英文 `strlen × 8` 光标，即使中文字宽不同。不能用作本页中文字形和度量实现依据。 | 本次不采用；主菜单当前接入和原生字宽扩展以后续重构记录为准，旧说明作为历史静态材料仍待逐段清理。 |
| `main-menu-static.txt:34` | 旧段落建议压掉原文后在已知位置整段绘制，与现行按原生调用消费中文及禁止页面位置方案冲突。 | 本次不采用；该历史实现已由逐词原生消费和即时字形路径替代，历史正文仍待清理，不能视为当前规范。 |

既有宿主错误透传和事务失败语义的待整改状态继续见 `20261019-implementation-correction.md`。本页三字段接入不解决或掩盖该既有问题。

## 编译与正式交付

本轮源码修改已完成：Adapter 的四个调用边界及共享标题分支，SDK 三个组件，Semantic 三键及预加载，中文词库三条，以及构建适配中的 `load_saved_character` 条目。只做静态审查，没有运行游戏、测试、测试用例或断言。

本聊天提交根 `build.ps1 -Module adapter,semantic,catalog -Publish -Reload -TargetPid 65412`，显式采用统一 MinGW 工具链、根 `.toolchains/x86/w64devkit/bin/cmake.exe` 和同目录 `g++.exe`、`build/mingw-x86`、正式 `package/`。请求为 `659d3a71d06b40c5acb66a134407ad9f`，所属批次为 `2d77f726a80f434db75f94dcc3c0d75e`；已读取对应请求 JSON 和批次日志。该批次一次配置、一次增量构建，三个目标均成功；其发布子步骤失败，不能把该请求记成整体成功。

共享工作区的前序批次已先行编译并正式发布本页内容，因此交付按实际回执归属：

- 2026-10-19 08:15:05（Asia/Shanghai），请求 `a5ccf43f77b4480993ca5f3693b4817d`、批次 `3a8077d74baf4b8c81163a6d107dec37`、事务 `47b3089b3f5a48fdb39bc09ef77963a3` 编译并发布 Semantic 和含三条 `load_saved.*` 的词库。PID `65412` 的 Catalog、Semantic 均返回 Applied 第3代。旧正式文件先按原相对路径移入 `回收/20261019-081505-47b3089b3f5a48fdb39bc09ef77963a3/`。
- 08:17:09，请求 `332a1669776c48559b41f0ceeeb1306f`、批次 `22ac1ead4ed94d49bbcafcfffe5bed5c` 重新编译 `module.cpp`，覆盖本页已保存的四个 Hook 及标题分支。事务 `a3cb9e6df32c47f7985f0cc73ae2dd41` 正式发布 Adapter、构建适配和清单，PID `65412` 返回 Adapter 第7代 Applied。旧三件先移入 `回收/20261019-081709-a3cb9e6df32c47f7985f0cc73ae2dd41/`。

已读取这两个前序批次的完整日志、请求 JSON 及 `stage/<事务>/publication-result.json`。保留原有 `GetProcAddress` 函数指针转换编译警告，没有编译错误。只读核对结果：正式 Adapter、Semantic 与构建输出 SHA-256 相同；正式词库与源码相同；正式和源码 profile 的 `load_saved_character` 对象相同；正式清单十项文件哈希均与磁盘一致。旧件归档已实际存在。启动器和驻留桥未替换，没有备用运行目录。

| 本轮正式文件（相对 `package/`） | SHA-256 |
| --- | --- |
| `modules/uwcn_adapter.dll` | `f106a36555b7528cf0e5aa6f22966b25bdd5d7417fbc489e92038c0d5d2252b3` |
| `modules/uwcn_semantic.dll` | `2d826d31f2a07d6d93386d2e8ab0327496926f237ad34426983d7d2a469bc218` |
| `catalog/zh-CN/main_menu.tsv` | `558d5e2f38b5d03774faa158cb84e59f6168598a20c66d7551ec9dea35af20f7` |

本请求在08:17:11的失败事务为 `cc67068d4cee4db3ad31895d8a90ecfd`，其 `changed_files` 仅有其它并行新增的 profile 元数据和清单，业务 DLL 及词库已与正式文件一致。`publish.ps1:103–107` 在 `Reload` 且业务变更集为空时仍发出 mask=0 的 PREPARE；`src/loader/host.cpp:305` 明确拒绝 mask=0，所以返回 `Failed invalid request`。这是已观察到的发布入口缺陷，待单独整改；本轮未添加回退、不重发同一请求、不替换驻留桥，也没有为它另外创建修复包。拒绝发生在文件移动和 COMMIT 之前，此失败事务未改动正式文件、未退役模块、未创建所打印的回收目录。本页所需的源码、产物和正式文件已由以上前序批次交付；不将后续其它页面元数据归为本轮成果。

Applied 证明已完成兼容模块交接，不代表画面验收。已经绘出的旧载入窗口继续由原生缓存管理，待游戏正常再次构建才显示本次中文；本轮没有强制退出等待或重新扫描存档。未自行测试或运行产物。
