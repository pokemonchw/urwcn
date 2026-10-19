# 2026-10-19 Linux 技能界面汉化

对应用户角色创建技能页截图。接入技能总标题、三类技能分组、全部30项技能名称、全部11档熟练度、初始与游戏内帮助、剩余点数标签、提升／降低按钮与动态上限说明，以及底部百科标题、概述和F1提示。新增52项技能词条、29项原有百科主题概述；名称与既有百科译名一致。

本页仍使用原生技能索引、数值、天赋星号、进度条、初始值深色区、快捷键、排序、加减点计算及退出条件。原始 `Plr` 技能名、`KaytetytTaidot`、`OptionStageML`、技能初始化数据与英文百科检索身份不改写。

## 静态证据

目标：Linux x86-64 UnReal World 3.89 / Steam Build 25939378。以下地址均为ELF RVA，已扣除Ghidra的 `0x100000` 基址。

| 原始文件 | SHA-256 |
| --- | --- |
| `urw3-bin` | `4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe` |
| `ini_skills.txt` | `cabb393ff1fb571a15cab75454d91403ee5d27bf9e3c8b8a5f989365277b4f0c` |
| `gameinfo/urw_scrinfo.txt` | `c9e028d0fd0fe133d21bacb3c2bc708a10312ef4ca7816df89fda89a7499c6ae` |
| `GAME.NFO` | `071f384ad992d0a688833693f207a5cf8a969b4811e5e6603597d189087a4d5d` |

使用既有Ghidra 12.1.2工程，以 `-readOnly -noanalysis` 提取，没有执行游戏函数。原始输出存于 `build/analysis/`：

- `skills-linux-ghidra.c`：`Piirra_SkillInfo`、`AsetaTaito`、`PIIRRAPOHJA_Taitoruutu`、`SKILLS_Listaa`、`TeeMenulista_Taidot`、`TaitoRuutu`、`taitoteksti_perus`、`SkillDATA`、`character_skills`。
- `skills-options-linux-ghidra.c`：`NaytaOptioRuutu`、`KaytaOptio`、`character_skills`、`GameInfo_Hotspot`、`LIST_ButtonSpotEntry`、`SubScreen`、`showtext_sanataulukko`。
- `skills-linux.asm`、`skills-options-linux.asm`、`skills-button-linux.asm`、`skills-paragraph-linux.asm`、`skills-title-linux.asm`：调用参数、被覆盖指令和原生度量／绘制路径。

`character_skills:1F320` 明确生成30项技能；`ini_skills.txt` 给出同一组英文身份。`AsetaTaito` 将 `Plr+0x20+id*12` 的英文名复制为当次显示副本，并自行规范化 `TEXTILECRAFT`，随后构造 `%c.%s`。本次在这个构造之后借入中文名称，不改技能数据或热键选择。

`taitoteksti_perus:1AD6B0` 从 `SI_taitokuvaus:26EC80` 每100字节一项的11项描述表中选择结果。表内为 unskilled、untrained、amateur、novice、adequate、competent、skilled、talented、expert、master、grandmaster。本次翻译原函数已经选中的描述，不复制或修改等级阈值计算。

## 接入边界

实现位于 `src/linux/skills.inc`，由 `src/linux/adapter.cpp` 安装。SDK增加 `skills_text=0xF01`，Semantic按原生显示身份读取 `skills.*`；Host ABI及状态序列化不变。

| 调用点 | 内容及原生所有权 |
| --- | --- |
| `107EA8/108325 → 1224C0 SubScreen` | 当次RDI借入“技能”，原背景与标题函数继续执行。 |
| `107F72/10808F/1081AA → 1471A0 winbox` | 三个分组标题只替换R8；第七个参数从原Frame栈读取，原生面板尺寸与背景不变。 |
| `107DB2 → F4F50 LIST_ButtonSpotEntry` | 原ASCII键帽前缀加完整中文技能名同步借入RCX。原按钮绘字、字宽测量、动作与命中区域登记消费同一字符串。 |
| `107BC9 → 8F80 __sprintf_chk` | 替换R8中的熟练度描述，保留原 `(%s)`、原100字节显示缓冲、原等级选择；后续 `107BF0` 绘制及 `107BF8` 度量消费同一显示副本。 |
| `10856A/1087AB → 1B0130 SANATAULUKKO_finfo` | 保留原帮助文件读取，再以GENERAL／INITIAL完整中文重建同一原生词表。 |
| `1E647 → 13E8B0 showtext` | 剩余分配点数标签；右侧数字框保持原格式化与数值。 |
| `1E6A5/1E790 → 1AFE00 SANATAULUKKO_Lisaa` | 保留原追加／重置参数及降低说明出现条件，按 `SKILLIMPROVE_onetime:6691E14`、`SKILLIMPROVE_decok:6691E15` 的原字节值插入动态级数。颜色标签与换行标记交回原段落函数。 |
| `1E723/1E739 → 144FB0 Piirra_Nappain` | 保留 `+.`、`-.` 前缀，只译按钮后缀；没有增加动作或改变点数计算。 |
| `1084CB → 4FE10 GameInfo_Hotspot` | 复用已确认的百科预览作用域。共享 `4FEFE/4FFFB/500D6` 消费中文标题、完整语义概述和F1后缀。原英文关键字照常进入 `GFX.NFO`、主题存在判定与百科跳转。 |

`GAME.NFO` 中30项技能有29个对应主题；原版没有 `AXE` 主题。本次保留原生无主题分支，没有补造斧百科入口。武器对应原版实际检索的装备介绍，例如刀、剑、弓、弩；没有将它们擅自改为其他主题。

## 中文度量与字形

中文进入既有Layout双字节传输编码。复用咒语页的词元转换，命名调整为 `native_paragraph_words`；原标记与ASCII词保留，中文字符成为完整原生词元，标记结束符后不插入空词。每个中文词元为2字节，原词槽容量130字节；页面段落不在Mod中分行。

软件段落 `13EEC3` 已按真实字宽判定换行、`13F00F` 已按真实字宽推进测量光标；此次在 `13EF3D` 原追加空格的 `__memcpy_chk` 调用处，中文词元保留此前 `13EF06` 已复制的NUL，不追加可见西文空格。ASCII词仍执行原复制。测量与绘制沿同一原生分支，保留原行高、颜色、段落背景高度及字符数用于字节复制的语义。

标题沿原 `14709B` 度量扩展居中；按钮沿既有完整字符绘字和推进扩展。`F50A8/F50C8` 原生 `textwidth` 结果写入原 `ListEntries` 的前缀宽及总宽，原选择与鼠标处理消费游戏自己的记录。没有新增固定坐标表、行槽、整页快照或独立布局。

页面使用原生 `screen` 软件画布及菜单缓存，不创建新的页面纹理。沿既有 `src/linux/native_targets.cpp` 确认的画布密度接口，中文字形在原组件文字调用内直接光栅化到真实密度目标。原生UI持有已绘像素、缓存、背景、恢复及呈现生命周期；字形缓存只存编码、Unicode和度量，没有像素扫描、绘制贡献序列或延后文字重放。

## 审查与刷新限制

- 原 `src/linux/adapter.cpp:paragraph_width/paragraph_advance` 只扩展字宽，没有处理 `showtext_sanataulukko:13EF3D` 每词追加西文空格。影响：中文拆词后产生额外间距，并改变原生测量结果。状态：本次在原生复制边界整改，现有ASCII行为保留。
- 原 `src/linux/culture_info.inc:culture_preview_text` 的通用百科显示依赖 `.summary`；`catalog/zh-CN/cultures.tsv` 只有文化简介具备概述。技能页此前未接入该作用域，直接扩大作用域会产生缺词。状态：本次补齐29个已确认技能主题概述，再接入技能页调用；没有对未知主题增加回退。
- `src/linux/adapter.cpp:redraw_language` 未有技能页的完整纯绘制重建路径。`TaitoRuutu` 包含菜单初始化、技能使用、点数变动及等待，不能整体重跑。`SKILLS_Listaa` 的重复动作绘制经 `F5048→F5150` 跳过条目几何登记，因此不能把单独重画文字当成完成中英文切换及命中同步。状态：当前已缓存技能页的即时整页刷新仍待确认；新原生构建完整消费新译文。热加载成功不等于当前截图所有旧像素都已刷新，也不宣称热加载后局部重画已同步所有旧命中宽度。
- `src/linux/adapter.cpp:glyph_request` 既有行高／墨高校准尚未完整传入原生四次阴影预算，非主菜单页面的缩放重建仍见 [Linux字体密度记录](20261019-linux-font-density.md)。状态：既有待整改项，本次不以编译或发布成功视为已解决。
- 历史固定位置重画、DisplayPlan与全局文字重放的冲突仍以 [文档纠正记录](20261019-document-render-policy.md) 和 [实现纠正记录](20261019-implementation-correction.md) 为准，本次没有采用这些路径。

## 交付状态

源码修改、统一队列编译、正式文件发布与已授权兼容热交接均已完成，时间为2026-10-19 15:30:48（Asia/Shanghai）。

- 根入口 `.toolchains/powershell/pwsh -NoProfile -Command '& ./build.ps1 -Toolchain Linux -Module adapter,semantic,catalog -CMakePath /usr/bin/cmake -CompilerPath /usr/bin/g++ -BuildDirectory /home/lulika/workspace/urwcn/build/linux-x86_64 -Publish -Reload -TargetPid 3883506 -PackageDirectory /home/lulika/workspace/urwcn/package'`。提交前保存修改，所属批次完成前没有继续修改请求源码。
- 请求 `85bfaae38ab649ec998e575e150feb2d`，批次 `85e005aeb2c440edadbb2f31cd0c0753`。已读取 `build/.compile-queue/results/85bfaae38ab649ec998e575e150feb2d.json` 与 `build/.compile-queue/batches/85e005aeb2c440edadbb2f31cd0c0753.log`：`Success=true`，一次配置、一次增量构建，Adapter、Semantic、Catalog均完成。日志保留Semantic既有HUD／世界文本枚举由其他分支分派造成的 `-Wswitch` 警告，无编译错误。
- 正式事务 `2e107b0642174fffb62ba4a2964f426c`；已读取 `build/linux-x86_64/stage/2e107b0642174fffb62ba4a2964f426c/publication-result.json`，`success=true`。替换Adapter、Semantic、两份词库、Linux profile和正式清单六件；Catalog二进制未变化，随词库更新参与热交接。
- 六件旧正式文件均先按相对路径移入 `回收/20261019-153048-2e107b0642174fffb62ba4a2964f426c/package/`，已只读确认，包括被rg默认忽略的两个DLL。应用菜单旧链接也移入同一事务目录。根启动器与驻留库沿用正式路径，没有新增平行运行包。
- PID `3883506` 返回 `ReadyToPublish` 与 `Applied`，Catalog、Semantic、Adapter均为该进程第2代。此回执只表示兼容模块交接完成，前述当前技能页旧缓存与命中宽度的刷新限制仍保留。
- 已只读核对下列源码／构建与正式文件SHA-256一致，并与正式清单对应项一致。

| 正式内容 | SHA-256 |
| --- | --- |
| Adapter | `d1e584f147e4d11b3b36a57cea5fc559bdc382cf23c77ab92a52e543d415ed6b` |
| Semantic | `a410ae8346cfb4f98617497a399e72d65547889436b0a2495cd848589a91b966` |
| 主词库 | `bc510786082afe0b6ae3e218b2a95a4b7b6d784b878c3f884a301b5353cd77e9` |
| 百科词库 | `1a745994683b85ed97325fe2b79cefcc16536e4eb346555c8269b1afd716067d` |
| Linux profile | `a86ccb07ddb894a90c93d0674c42ff007717d4c6212e1d9613851627b5b26f10` |

未启动、关闭或重启游戏，未注入、模拟输入或运行测试；除已授权的兼容业务热交接外，没有自行运行产物。没有新增测试脚本、测试用例、断言、保护或兜底分支。静态审查及编译、发布回执不代替视觉验收。
