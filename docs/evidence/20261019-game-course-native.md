# 2026-10-19 Linux 游戏进程选择页汉化

对应用户截图 `codex-clipboard-edd7af66-3765-4d6f-9310-802394ac3062.png`。标题为“选择游戏进程”，三项为“不真实的世界”“荒野求生”“进阶冒险”。范围包含三段完整介绍、底部说明、两个已完成标签及全部完成提示；原生博物馆分支的“教学进程”名称也沿同一显示边界接入。共20条词库记录、22处原生文本调用。

## 静态依据

目标为不真实的世界3.89、Steam Build 25939378、Linux x86-64，原 `urw3-bin` SHA-256 为 `4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。以下为 ELF RVA；Ghidra 导出地址需减去其 `0x100000` image base。

- `build/analysis/game-course-linux.asm`：原始 `game_course` 的显示、完成状态分支、输入及任务创建调用。
- `build/analysis/game-course-linux-ghidra.c`：使用已有 Ghidra 12.1.2 工程及 `EquipmentDecompile.java`，以 `-readOnly -noanalysis` 导出 `game_course`、`LIST_ButtonSpotEntry` 和 `LIST_Draw`，没有执行游戏。
- `build/analysis/scenario-selection-linux-ghidra.c`：已有 `draw_campselgfx`、`crtplr_info` 和 `LIST_Go` 反编译；本轮重新阅读并与原指令对照。
- `build/analysis/scenario-selection-input-linux.asm`：原生输入返回、栈布局、菜单缓存及选择框次序。

## 文本与原生 UI

实现为 `src/linux/game_course.inc`，通过 `adapter.cpp` 安装；SDK 新增 `game_course_text=0xC22`，Semantic 将语义键交给 `game_course.*` 词库。未修改已有枚举值、Host ABI 2、state-v1 或驻留库。

| 原生调用位置 | 原生消费者与显示语义 |
| --- | --- |
| `1D618`、`1D648` | `draw_campselgfx` 与七参数 `winbox` 的标题，分别借入 RDI、R8；第七参数仍取原生调用栈。 |
| `1D690/1D69E/1D6AC` | 自由游玩完整说明，原 `SANATAULUKKO_Lisaa` reset/append 保持。 |
| `1D70D/1D71B/1D729` | 荒野求生完整说明，原分词表及折行消费者保持。 |
| `1DA26/1DA34/1DA42` | 进阶冒险完整说明，原 `PELIMUSEO_EDIT` 分支保持。 |
| `1D7D1/1D96E`、`1D807/1D8E6`、`1DA8E` | `LIST_ButtonSpotEntry` 的自由／求生／进阶名称；复制原 `ESC.`、`A.`、`B.` 键帽前缀，再借入中文名称。 |
| `1D9AD`、`1D927` | 原 `showtext` 的两项“已完成”标签，不将不可选标签变为按钮。 |
| `1D840/1D84E/1D85C`、`1D94A` | 通用三条说明、全部完成提示，保留原 `Plr+0x15F8` 完成位分支。 |

原生 `LIST_ButtonSpotEntry:F4F50` 复制完整借入标签至1024字节局部缓冲，调用 `Piirra_Nappain:144FB0` 绘制，再以 `textwidth:13B460` 计算键帽和整个标签宽度。原 ListEntries 保存 `TEXTSPOT` 标识、动作和原生控件矩形，不保存借入字符串指针。因此中文同时进入原生绘制和按钮尺寸／命中宽度；没有只换绘图、仍按英文宽度计算的另一路径。

九条介绍记录仍交给原 `showtext_sanataulukko:13ECE0`；底部仍交给 `crtplr_info(0)`。中文经已有 Layout 双字节编码和 `native_paragraph_words` 完整字符分词，原 `13EEC3`、`13F00F` 与 `13EF3D` 扩展宽度、推进及分词空格。按钮继续使用已有 `1452E3/145264/145286` 完整字符接口。未将 UTF-8 字节交给 ASCII 字形索引。

词库源码静态计数：标题含 NUL 为13字节，带原键帽的最长标签含 NUL 为17字节，已完成标签19字节，最长单条介绍83字节（分词前）。每个中文分词词元为2字节，原词元槽130字节、总容量5000槽；最长一段介绍为97个中文字符。已确认容量足够，不新增截断、断言或兜底。

字形通过既有原生 `screen` 的真实输出密度目标即时提交。Mod 没有新增坐标表、行槽、页面字段快照、DisplayPlan、像素扫描或延后文字重放。原背景、三张图片、透明状态、缓存和呈现继续由游戏管理。内部英文、Esc／A／B 动作及 `Tee_Gamecourse_1/2` 完全保留。

## 已打开页面的重绘

沿用 `F871F` 输入返回 Hook，静态确认的原 `RSP+0x458` 调用返回槽等于 `1D872` 时，识别游戏进程页。`1D86D → LIST_Go` 未 Hook，更新前已打开的页面仍有相同原生返回身份；不扫描运行栈或像素。

1. Adapter 初始加载和依赖变化请求刷新；构建语言与当前语言不一致时也请求刷新。
2. 以原 `LIST_Position:F6100` 保存当前选择，重入 `1D5E3` 开始的显示片段，包含原背景、两次标题、图片、说明、完成分支、`LIST_Reset`、原按钮及底部。
3. 入口位于 `grabscr("gamecourse")` 和姓名复制之后，避免覆盖游戏退出页面时需恢复的原屏幕。片段不依赖原函数姓名局部变量或输入参数。
4. 汇编入口只保存片段使用的 RBP，并提供原生 CALL 对齐；原片段各七参数调用自行平衡栈。`1D868 → LIST_Draw` 完成后，刷新分支返回专用汇编出口，跳过后续 `LIST_Go`、任务创建、Esc 的任务值修改、`FLIP_map_ON` 及 `restorescr`。
5. 仅同步重绘期间，既有 `1BBFC → random(20)` Hook 跳过调用。原 `crtplr_info(0)` 不使用返回值，只有参数2分支消费它；正常首次进入仍调用原随机数。没有伪造随机结果或推进游戏 RNG。
6. `Set_LIST_Position:F6110` 恢复选择，原 `save_menubuf:13D5A0`、`LIST_Highlight:F3F80`、`Flip:13FE50` 按原顺序建立缓存并显示选择。既有外层 Hook 重现原 `MOV ESI,1`，保留真实输入 RAX，继续游戏原输入处理。

新布尔值只表示失效、构建语言和同步重绘状态，不保存页面内容或 UI 位置，不跨输入等待持有业务返回地址。刷新发生于下一次自然 `getkey` 返回，不模拟事件唤醒；Applied 不能视为已获得可见刷新或视觉验收结果。

## 既有待整改记录

- `src/linux/adapter.cpp:83` 的 `glyph_request` 尚未完整传入原生四次阴影预算；`src/linux/native_targets.cpp:321` 的尺寸同步仍限于主菜单，非主菜单途中缩放的完整目标重建边界未普遍确认。影响为阴影占位及缩放密度一致性，状态待整改。本轮沿已确认目标绘制，不把编译或发布视为上述问题已解决。
- `docs/hot-reload.md:25`、`:31`、`:123`、`:125` 仍有历史页面快照、固定布局及 DisplayPlan 叙述，与现行 UI 所有权要求冲突。影响为误导后续接入，状态为历史正文待清理，本轮未采用。
- `catalog/zh-CN/main_menu.tsv:478` 的既有 `profile.heading` 保留英文游戏名。影响为其他角色创建页译名不一致，待后续更正；本轮页面标题、说明和提示均按“不真实的世界”处理。

修改前八份源码、词库、profile 和 README 已按原相对路径保存于 `回收/20261019-game-course-source/`。既有未跟踪文件 `docs/evidence/20261019-crop-growth-analysis.md` 未修改。

## 交付状态

源码及词库修改、统一队列编译、正式文件发布均完成。最终发布时间为2026-10-19 19:04:56（Asia/Shanghai）；发布时游戏已不在运行，下次从根 `uwcn_launcher` 正常启动加载，本轮没有运行时 Applied 回执。

两次均使用 Linux 默认 `/usr/bin/cmake`、`/usr/bin/g++`、`build/linux-x86_64` 和正式 `package/`，模块集合为 catalog、semantic、adapter。每批一次配置及一次增量构建，不清理构建树；提交后至所属批次结束未修改源码。

首批统一入口：

```sh
.toolchains/powershell/pwsh -NoProfile -Command '& ./build.ps1 -Toolchain Linux -Module catalog,semantic,adapter -Publish -Reload -TargetPid 3968932'
```

- 请求 `41ec1075d6c54ce2ad879af2e6c38001`，批次 `c998103a05e543759d4db1941b137962`，事务 `933eb8cc3c8943519c7c5ca4617af356`。
- 编译成功；Semantic 仅有此前 HUD/world 枚举另行分派的15项 `-Wswitch` 警告，新组件无编译警告。
- 实施时只读确认 PID `3968932` 已加载正式 ABI 2 框架；发布时 `/proc/3968932/status` 已不存在。事务在 PREPARE 前失败，`ready=false`、`commit_submitted=false`、`applied=false`，没有替换正式文件。批次总体 `Success=false`，不能称为热发布成功。
- 随后只读进程列表确认无运行中的 `urw3-bin`，没有自行结束、重启或操作游戏。原正式清单仍为先前事务 `1dc2eccb46974ed4a8d688270c15ccf2`。

待首批完整结束、队列空闲后，按当前无运行进程的实际状态提交正式文件发布，未改代码或添加任何自动回退逻辑：

```sh
.toolchains/powershell/pwsh -NoProfile -Command '& ./build.ps1 -Toolchain Linux -Module catalog,semantic,adapter -Publish'
```

- 请求 `a88942beb592460f801a43a89801b7e1`，批次 `807ea451592f41cbbee5e03d54d10cfd`，`Success=true`。沿同一构建树增量构建，没有重复编译源文件。
- 正式事务 `a8000857c37e422597f9cb383a8d3e5a`，`success=true`、`runtime_requested=false`、`runtime_receipts=[]`。未申请热加载，不将正式发布说成运行时生效。
- 正式更新 Adapter、Semantic、主词库、Linux profile、`release.json` 五件。Catalog 二进制内容未变；根启动器和驻留桥无需更换。
- 旧五件先按原相对路径移入 `回收/20261019-190456-a8000857c37e422597f9cb383a8d3e5a/package/`，再替换正式文件；已只读确认归档存在。没有平行运行目录或独立修复包。
- 已读取两份 `build/.compile-queue/results/<请求ID>.json`、两份 `batches/<批次ID>.log` 和各自 `publication-result.json`，完整保留首次失败事实。以下四项源码／构建、正式文件与正式清单哈希一致。

| 正式内容 | SHA-256 |
| --- | --- |
| Adapter | `bf83f60e56968732e0e3ce0bb921dea37355de3bc99ca9065c1b129823efe99c` |
| Semantic | `8b94c33edce299f8bb01c7286b66d82e0d3a3e63bcc37424b825440d00d2dd38` |
| 主词库 | `5e714c6dc628e06a0546670901aaa014f98b434fc898af1b1e60a05514a39dd3` |
| Linux profile | `dee5fea4808967cf802d3e09105508222f967080d2a5444b24ebd5889d2dad68` |

最终 Adapter 的静态反汇编在 `0x285A2` 确认新增片段入口仍为保存 RBP、栈对齐、间接 CALL、栈恢复与 RET；没有运行该产物。编译及发布不替代视觉验收。

全程不启动、关闭或重启游戏，不注入新驻留层，不模拟输入，不运行产物或测试，不编写测试用例、测试脚本或断言，不添加保护、回退、兜底逻辑。兼容业务热发布仅使用项目已授权事务。
