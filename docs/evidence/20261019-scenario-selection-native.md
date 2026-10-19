# 2026-10-19 Linux 开局情境选择页汉化

对应用户截图 `codex-clipboard-8ffa8007-9151-4e7d-ae2b-f8ccf2875c7e.png`。范围为“选择开局情境”标题、13个情境名称、13条完整简介和两次原生底部提示构建，共29项。第一项游戏名统一为“不真实的世界”；涅尔佩兹人的译名沿用百科。另修正既有 `scenario.press_key` 中残留的英文游戏名，不改其输入动作。

## 静态依据

目标为不真实的世界3.89、Steam Build 25939378、Linux x86-64。原 `urw3-bin` SHA-256 为 `4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。以下地址均为 ELF RVA。

通过原始 ELF 符号、objdump 和既有 Ghidra 12.1.2 工程的 `-readOnly -noanalysis` 反编译确认，没有执行游戏或交付产物。复用已有 `EquipmentDecompile.java` 导出原生函数，未建立测试脚本。

- `build/analysis/scenario-selection-linux-ghidra.c`：`SelectCampaign`、`draw_campselgfx`、`crtplr_info`、`LIST_SpotEntry`、`LIST_Go`。
- `build/analysis/scenario-selection-linux.asm`：情境文件读取、显示构建、选择和故事生成的原始指令。
- `build/analysis/scenario-selection-footer-linux.asm`：底部说明与随机数调用边界。
- `build/analysis/scenario-selection-input-linux.asm`：列表栈布局、菜单缓存、选择框和输入返回边界。
- 安装目录 `RNDCAMP.0` 至 `.12`：前两条记录分别为截图中的名称和简介，仅只读读取。

## 显示接入

实现为 `src/linux/scenario_selection.inc`，由 Linux Adapter 安装。SDK 新增 `scenario_selection_text=0xC20`，Semantic 读取 `scenario.select.*` 词库。Host ABI 2、现有 Scope 数值、状态序列化和原有 Hook 契约不变；不改驻留库。

| 原生调用 | 显示参数与保留的原生行为 |
| --- | --- |
| `1D17B → 1D030 draw_campselgfx` | RDI 借入中文标题；原函数复制到1024字节缓冲，管理背景变暗、透明状态及七参数 `winbox`。 |
| `1D23A → 13E8B0 showtext` | RDX 借入情境名称。`R12D` 在 `1D20B` 读标题前已加一，因此 `R12D-1` 是原 `RNDCAMP` 文件编号。原颜色、阴影和坐标不变。 |
| `1D271 → 1AFE00 SANATAULUKKO_Lisaa` | RSI 借入同一文件编号的完整简介，EDI=1 保留。 |
| `1D2F5/1D303 → 1AFE00` | 两段底部提示，保留原 reset=1 / append=0。 |
| `1D2A7 → 13ECE0`、`1BC66 → 13ECE0` | 仍由原生段落函数决定简介和底部提示的折行、行高、颜色及可用区域。 |

`1D254 → F4E40 LIST_SpotEntry` 完全不改。这页原本使用原生固定矩形作为选择框和鼠标命中区，情境名称直接绘制，不是按名称长度计算尺寸的按钮。Mod 不复制这些坐标，也不让原生命中区消费另一套布局。原 `ListEntries` 占位英文、场景编号、文件名、故事正文数据和选择动作不替换。

中文使用既有 Layout 双字节传输编码；`native_paragraph_words` 将完整中文字符交给原生分词器。每个中文词元为2字节，远小于原130字节词元槽。现有 `13EEC3`、`13F00F` 扩展段落宽度与光标推进，`13EF3D` 去除中文分词用空格的可见宽度；`13B460` 和 `textput` 使用同源完整字符度量与字形。没有把 UTF-8 字节送入 ASCII 字形索引。

静态文本计数：标题含 NUL 为13字节，名称最长27字节，完整简介编码最长59字节，底部两段分别77和43字节；段落分词后每个词元仅含一个完整中文字。后续介绍页继续按钮的名称修正后仍为42字节。以上容量依据不需要截断、断言或猜测性兜底。

字形在已确认的原生 `screen` 真实输出密度目标上同步绘制；背景、缓存、保存恢复与呈现由游戏负责。新增代码不保存 UI 位置、行槽、整页文本、像素或绘制贡献序列。

## 已打开页面的重绘

新增 `F871F` Hook 覆盖独立五字节 `MOV ESI,1`，处于 `LIST_Go` 原 `getkey` 返回之后。该函数保存六个寄存器并分配 `0x428` 字节，原调用返回地址位于当时原生 `RSP+0x458`。只有该值为 `1D365` 时才处理情境选择页；`1D360 → LIST_Go` 保持未 Hook，因此更新前已经打开的页也能识别。这不是运行时栈扫描，只读取静态确认的单一返回槽。

Adapter 新代初始请求刷新，依赖变化也请求刷新；语言与上次构建语言不同时使用同一原生路径：

1. 原 `LIST_Position:F6100` 读取当前选择。
2. 完整进入 `SelectCampaign:1D100` 建立原栈与安全 cookie，执行原背景、标题、原列表构建、文件读取、名称、简介及底部提示。
3. `crtplr_info(0)` 的 `1BBFC → random(20)` 在正常进入时照常执行；仅在同步重绘期间跳过。反编译确认参数0分支不使用该随机返回值，因此重绘不推进 RNG，也不补造返回结果。
4. `1D30A` 原底部绘制完成后，仅在重绘期间继续到 `1D332`，执行原 cookie 检查、栈和寄存器恢复。跳过 `LIST_Go` 输入等待、`Plr+0x9E0` 情境值写入和 `get_camp` 的故事文件生成。
5. 原 `Set_LIST_Position:F6110` 恢复选择；按 `LIST_Go` 的缓存先于选择框的顺序调用原 `save_menubuf`、`LIST_Highlight` 和 `Flip`。原生列表仍持有自己的控件几何。
6. Hook 重现原 `MOV ESI,1`，保留 RAX 的真实输入结果，继续原输入处理。

三个新增布尔值仅描述同步重绘和语言失效，不跨热更新保存页面内容；原状态格式无需迁移。业务回调不跨任何新增输入等待。尚在原 `getkey` 等待的页面会在下一次自然返回时刷新，不模拟事件唤醒，也不将模块 Applied 回执视为页面已完成可见刷新。

## 既有待整改记录

- `src/linux/adapter.cpp:83–90` 的既有字形请求仍未完整传入原生四次阴影预算；非主菜单页面尚未普遍确认随窗口尺寸变化重建所有目标的边界（`src/linux/native_targets.cpp:321` 当前是主菜单同步入口）。影响为阴影占位与中途缩放时的密度一致性；状态仍为待整改，本次使用已确认的原生目标，不以编译或热发布成功视为这些问题已解决。
- `docs/hot-reload.md:25`、`:41`、`:122–125` 保留旧页面字段快照、固定行槽、DisplayPlan 和 Present 合成叙述，与当前原生 UI 所有权要求冲突。影响为可能误导后续实现；状态为历史正文待清理，本次不采用。
- `catalog/zh-CN/main_menu.tsv` 的既有 `profile.heading` 仍含英文游戏名。影响为角色文化选择页译名不统一；状态待后续更正。本次发现的 `scenario.press_key` 已直接改正。

修改前既有源码、词库、profile 和 README 已按原相对路径保存到 `回收/20261019-scenario-selection-source/`。既有未跟踪的 `docs/evidence/20261019-crop-growth-analysis.md` 保持原样。

## 交付状态

源码修改、统一队列编译与正式热发布均完成，交付时间为2026-10-19 17:48:10（Asia/Shanghai）。

统一入口：

```sh
.toolchains/powershell/pwsh -NoProfile -Command '& ./build.ps1 -Toolchain Linux -Module catalog,semantic,adapter -Publish -Reload -TargetPid 3968932'
```

- 请求 `846e89b3d9014f7fa3ac5026a37ca426`，批次 `29750974d1e540b7b6d083a6126f5e32`。`Success=true`；一次配置、一次增量构建，未清理构建树。提交后至批次结束未修改本次源码。
- 使用队列默认 `/usr/bin/cmake`、`/usr/bin/g++`、`build/linux-x86_64` 和正式 `package/`；没有绕过队列或创建平行运行目录。
- 发布事务 `19ab47e7a30c45219a0f9e06ee10036d`，`success=true`、`runtime_requested=true`。PID `3968932` 返回 `ReadyToPublish` 后，先归档再替换，最后返回 `Applied`；Catalog、Semantic、Adapter 均为第3代。
- 正式更新五件：`package/modules/uwcn_adapter.dll`、`package/modules/uwcn_semantic.dll`、`package/catalog/zh-CN/main_menu.tsv`、Linux profile 和 `package/release.json`。Catalog 二进制内容未改变，仍按请求重新加载词库。启动器和驻留库无需更换。
- 旧五件按原相对路径移入 `回收/20261019-174810-19ab47e7a30c45219a0f9e06ee10036d/`，没有覆盖或永久删除旧交付。
- 已读取完整请求结果 `build/.compile-queue/results/846e89b3d9014f7fa3ac5026a37ca426.json`、批次日志 `build/.compile-queue/batches/29750974d1e540b7b6d083a6126f5e32.log` 及事务 `publication-result.json`。编译只有 Semantic 既有 HUD/world 枚举另行分派的 `-Wswitch` 警告，没有编译错误或新增组件警告。

| 正式文件（相对 package） | SHA-256 |
| --- | --- |
| `modules/uwcn_adapter.dll` | `73cd34fc1fe30b9528e4b7fa2698e4aae4ecd4c76bb876ece267b1a3c4853c2c` |
| `modules/uwcn_semantic.dll` | `7ad719e2887557a183234c4d0d89fe54b2dd534a0a321562c202cc423d19a88d` |
| `catalog/zh-CN/main_menu.tsv` | `ea1c28c7b35c0453dabad4fb84bb0c29c61e4461eba3f59524bb9f3f79e8f93e` |
| `profiles/urw-3.89-steam-25939378-linux-x86_64.json` | `95d70c8ebf5597b95478f0363f76d0b75afac9083b74e275d053c435bf78ac45` |

Applied 只证明正式文件和模块交接完成；没有自行取得当前页面已重绘或实际视觉效果的结论。

没有启动游戏、注入新驻留库、模拟操作、运行测试或交付产物；没有编写测试用例、测试脚本、断言、保护或回退逻辑。兼容业务热发布使用项目已授权事务。
