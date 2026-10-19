# URWCN · 不真实的世界（UnReal World）简体中文汉化

[![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC_BY--NC--SA_4.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc-sa/4.0/)

URWCN 是 **Byayoi 同人社区**的《不真实的世界》（UnReal World）汉化作品。

社区官网：[byayoi.org](https://byayoi.org/)

项目仓库：[pokemonchw/urwcn](https://github.com/pokemonchw/urwcn)。适配目标为 **UnReal World 3.89 / Steam Build 25939378**，包含 Windows x86 与 Linux x86-64 原生分支。Linux 的接入范围及尚待确认的高清边界见 [Linux 移植记录](docs/evidence/20261019-linux-native-port.md)，下文既有热发布回执属于 Windows。中文在已确认的原生文本构建、格式化和显示边界生成，游戏继续管理布局、控件、输入和缓存，Mod 负责字形绘制；游戏业务、内部英文数据和设置动作保持原有语义。

游戏内按 **Shift+F10** 切换中英文显示。已接入范围、各界面的刷新边界和交付记录见下文。

Linux 角色姓名框已完成中文输入源码、统一队列编译和正式发布：系统输入法提交完整中文，退格删除完整字符，光标和字形沿原生 UI 更新；中英文可混输。原存档姓名容量为12字节，最多容纳4个常用汉字或12个英文字母，混输共用容量；英文姓名仍至少3个字母。旧文件已归档至 `回收/`，下次正常启动加载，未自行运行或测试。其他输入框及 Windows 尚未接入。回执和静态依据见 [中文姓名输入记录](docs/evidence/20261019-linux-chinese-input.md)。

Linux 主菜单切换后的旧文字残留已完成源码修正、队列编译和正式发布：切换先沿原生路径重建背景、页脚和菜单面板，再更新文字、选择及缓存；关于、鸣谢同时更新后方菜单的原生页面缓存。旧正式文件已归档至 `回收/`，下次正常启动加载；未自行运行或测试。依据及回执见 [Linux 切换残留修复](docs/evidence/20261019-linux-language-residue.md)。

## 本机 Linux 原生构建与启动

在 Linux 上通过同一个 PowerShell 7 队列入口编译并正式发布：

```bash
.toolchains/powershell/pwsh -NoProfile -File ./build.ps1 -Toolchain Linux -Publish
```

使用系统 x86-64 GCC、CMake、Make、OpenSSL 开发库、SDL2 和 SDL2_ttf；本机的便携 PowerShell 来自 [PowerShell 官方发行版](https://github.com/PowerShell/PowerShell/releases/tag/v7.6.6)。首次本机发布会从已安装的思源黑体集合复制简体中文 Bold 字面对应的字体文件，以及本机 Steam Runtime 的 SDL2_net 库和第三方许可证。

Linux 正式入口是根目录无扩展名的 **`uwcn_launcher`**，由 C++ 编译为原生 ELF64 可执行文件。直接启动它即可，运行时无需 PowerShell 或 Wine；汉化资源和模块从相邻的 `package/` 加载。发布时安装应用菜单入口 **UnReal World 简体中文**，指向这一份正式启动器；也可在终端执行：

```bash
./uwcn_launcher
```

启动器读取 `package/linux-game-path.txt` 中的本机 Steam 游戏位置，也接受 `--game /完整路径/urw3-bin`。原游戏二进制、业务数据和设置原值保持原样。Linux 已接入运行中业务模块发布协议，支持统一队列的 `-Reload -TargetPid`，详见 [Linux 热更新](docs/evidence/20261019-linux-hot-reload.md)。软件画布、菜单缓存及 Heading 软件目标已接入输出密度扩展，主菜单缩放沿原生构建重绘；其他页面缩放重建与描边预算仍待处理。源码、编译及正式发布状态见 [Linux 字体密度修正](docs/evidence/20261019-linux-font-density.md)。没有启动游戏、运行产物或自行测试。

Linux 热更新使用 ABI 2 驻留桥、同用户 Unix socket 和 `PREPARE → ReadyToPublish → COMMIT → Applied` 事务。业务模块在原生等待期间交接，保留语言、输入状态、中文编码和原生资源元数据；当前页面的已有像素仍按原生重绘时机更新。PowerShell 7 内的调用示例（将 `12345` 换成实际游戏 PID）：

```powershell
./build.ps1 -Toolchain Linux -Module adapter,render -Reload -TargetPid 12345
```

初版 Linux ABI 1 驻留层没有升级入口，无法向已经运行的旧进程原位安装新桥。新桥在用户下一次正常启动正式启动器后生效；之后兼容业务更新无需退出、返回主菜单或手动卸载。本次没有启动、关闭或重启游戏，也没有运行测试；源码、产物、正式发布与运行时状态分别见上述热更新记录。

Linux 启动闪退的两次用户 core 分别确认了音频显示名重复扩展名处理、后续音频显示键缺失；另经静态审查修正了七参数原生调用误读临时栈的问题。源码及正式发布状态分别见 [首轮修复记录](docs/evidence/20261019-linux-startup-crash-fix.md) 和 [启动词库修复记录](docs/evidence/20261019-linux-startup-catalog-crash-fix.md)。未自行启动或测试，不以发布成功代替运行结果。

Linux 退出告别页的标题、克里族谚语、献辞、底部寄语和继续按钮共 11 项已接入原生中文文本路径，完成统一队列编译和正式发布，旧文件已移入 `回收/`；游戏继续管理居中、按钮、背景及淡入淡出。下次正常启动加载，未运行游戏或测试。静态依据、语言刷新限制和发布回执见 [退出告别页记录](docs/evidence/20261019-farewell-native.md)。

## 项目命名与构建

项目名已由 `uwcn` 更名为 `urwcn`，从本仓库克隆时使用 `urwcn` 目录。Linux 启动器为 `uwcn_launcher`，Windows 启动器为 `uwcn_launcher.exe`；`package/uwcn_loader.dll`、`package/modules/uwcn_*.dll` 及内部 ABI、导出名和控制协议保留原名。Linux 库虽然保留 `.dll` 文件名，实际格式为 ELF64。历史证据中的旧项目名及绝对路径保留其记录时的含义。

本仓库提供源码、词库、构建适配和设计/静态证据文档。工具链、构建缓存、本地正式运行包和 `回收/` 中的历史文件不纳入 Git；游戏原始反编译、反汇编及字符串提取文件保留在本地，文档中的相关引用作为分析出处。下文已有交付回执记录的是本地发布状态，不表示仓库包含预编译运行包。

Windows 构建使用 PowerShell 7 和 i686 MinGW C++20 工具链；CMake 最低版本为 3.24。所有编译统一通过根目录队列入口：

```powershell
.\build.ps1 -CMakePath "C:\tools\cmake\bin\cmake.exe" -CompilerPath "C:\tools\w64devkit\bin\g++.exe"
```

`make.exe` 应与 `g++.exe` 位于同一目录。本地已有工具链时也可使用脚本默认的 `.toolchains/x86/w64devkit/bin/`。不带 `-Publish` 仅生成构建产物；需要正式交付时在同一入口添加 `-Publish`，脚本会先将被替换的旧文件移入根 `回收/`，再更新根启动器与 `package/`。使用时启动根 `uwcn_launcher.exe`，可传入 `--game "游戏完整路径"`。

开发与交付约束见 [AGENTS.md](AGENTS.md)。本次更名与首次源码上传未编译、未替换正式运行文件，也未运行游戏或测试。

## 许可与署名

本项目原创内容采用 [CC BY-NC-SA 4.0（署名—非商业性使用—相同方式共享）](https://creativecommons.org/licenses/by-nc-sa/4.0/)，完整条款见 [LICENSE](LICENSE)。使用时须保留署名、遵守非商业限制，分享改编成果时采用相同许可。

汉化组署名与 [DFCN](https://github.com/pokemonchw/dfcn) 一致，均为 **Byayoi 同人社区**；根 `LICENSE` 与 DFCN 使用相同的完整许可文本。原游戏与第三方内容的权利仍归各自权利人。

## 已接入范围与本地交付记录

字体被 Windows 150% 位图放大的启动边界修正已完成源码、统一队列编译和正式发布：根 `uwcn_launcher.exe` 在游戏创建前传入 `SDL_WINDOWS_DPI_AWARENESS=permonitorv2`，由原生 SDL 初始化消费，使字形使用真实输出密度。批次 `704b7920c5824cb7b67fe95500ea9d99`，事务 `41070669c7054afab6885f04174d1757`；旧启动器与发布清单已移入 `回收/`。下次正常启动生效，不追溯改变已有窗口；未自行运行或测试。原图证据、先前100%结论的更正、窗口大小影响及交付回执见 [DPI 启动修正记录](docs/evidence/20261019-font-dpi-startup.md)。

主游戏截图界面已完成源码汉化、统一队列编译和正式发布：状态栏、行动与方位、速度、日历、地域、地名释义、日期、比例尺和底部提示采用中文；人物姓名、原地名、数值和动作保持。对应原生 surface 与头像 renderer 使用真实输出密度字形，布局、控件和缓存由游戏管理。最终批次 `bb31dbf3f3894011a0ee0da1e1ee6620`、事务 `c2785e5465ef495ca21aaa2c03d123f8`；本批次旧四件先移入对应 `回收/`，正式清单十二项哈希一致。当时无运行中的游戏进程，未请求运行时热加载，未自行运行或测试。正式交付状态及旧缓存刷新边界见 [主游戏界面记录](docs/evidence/20261019-main-game-hud-native.md)。

“村庄”开局介绍页已完成源码汉化、统一队列编译和正式发布：标题、说明、完整故事和继续按钮共十九项，沿原生 UI 管理排版与缓存，刷新跳过开局业务和输入等待。最终批次 `bb5482e7791a4d34a70c869f1c00d807`、事务 `f39646159d51475da114beb3a7bea9c5`；旧七件先移入对应 `回收/`，正式清单十二项哈希一致。当时游戏进程已结束，本次未请求运行时热加载，未自行运行或测试。含两次前置失败的完整回执见 [村庄开局介绍页记录](docs/evidence/20261019-scenario-village-native.md)。

角色文化、性别与姓名界面已完成源码修改、统一队列编译和正式热发布：顶部提示、十种文化、选项、姓名标题与规则及三种原生校验提示共25项接入原生 UI。批次 `897d7e0bd3b14dfa9b0491b74fe2b8de`、事务 `d4ba5b9975644057b0e1c1000c695719`；PID `65412` 返回 Adapter 第8代 Applied，旧五件已先移入对应 `回收/`。当前姓名阶段已完成面板的纯重绘接口待确认，既有像素等待原生构建更新；未自行测试。详见 [角色创建阶段交付记录](docs/evidence/20261019-character-profile-native.md)。

截图中的角色创建方式菜单已完成源码汉化、统一队列编译和正式发布：标题及五个选项采用中文，Q/C/E/T/ESC 和原生选择、命中、动作保留。业务随并行批次加载到 PID `65412`（Adapter 第 7 代，Catalog/Semantic 第 3 代）；本聊天最后完成仅适配说明与清单的正式补发，事务 `b084f1f94c834c58ade7dec3b9d9a7c0`。旧正式文件已归档到 `回收/`，未自行运行或测试。含中间失败及准确批次归属的完整回执见 [角色创建菜单记录](docs/evidence/20261019-character-creation-native.md)。

先祖列表已完成源码修改、统一队列编译与正式热发布：标题、空列表、排序/翻页按钮、选择提示、页码及两条统计接入原生 UI。2026-10-19 08:17:09（Asia/Shanghai）批次 `22ac1ead4ed94d49bbcafcfffe5bed5c`、事务 `a3cb9e6df32c47f7985f0cc73ae2dd41` 更新正式 Adapter、构建适配和清单，旧件已移入对应 `回收/`，PID `65412` 返回 Adapter 第 7 代 Applied。当前页等待原生非按键重绘边界，未自行测试或视觉验收；详见 [先祖列表交付记录](docs/evidence/20261019-ancestors-native.md)。

鸣谢页“致谢与贡献者”、全部致谢正文及“按任意键继续”已完成源码接入、统一队列编译和正式热发布，并接入 `Shift+F10` 中英文切换。批次 `3a8077d74baf4b8c81163a6d107dec37`、事务 `47b3089b3f5a48fdb39bc09ef77963a3`；PID `65412` 返回 Applied（Adapter 第6代），旧正式五件已先移入对应 `回收/`。姓名、原生换行、按钮与背景缓存保留，字形在原生调用内即时绘入；未自行运行或测试。静态依据、旧开窗刷新边界和交付回执见 [鸣谢页记录](docs/evidence/20261019-credits-native.md)。

游戏内全局 `Shift+F10` 中英文显示开关已完成源码修改、统一队列编译及正式热发布，PID `65412` 返回 Applied（Adapter 第 5 代）。左右 Shift 均可，长按只切换一次，语言选择随业务热更新保留。主菜单、关于（含后方菜单）和设置沿原生路径重建；开场当前整段保持进入时语言，选择在后续页面生效。语言切换初版批次 `7c017d006dec426f82e3fdaf46c3ac29`、事务 `ce5e595dfecb4c8abbb5950d8b005e73`，旧正式三件已移入对应 `回收/`。静态依据及回执见 [语言切换交付记录](docs/evidence/20261019-language-toggle.md)；未自行运行或测试，不以 Applied 代替视觉验收。

当前源码已移除全局像素跟踪与文字记录重放，改为在原生组件文字调用中立即绘入实际高清目标；原生 UI 继续管理布局、命中、选择和背景缓存。源码、编译、正式发布及运行时回执分别见 [原生高清交付记录](docs/evidence/20261019-native-hd-delivery.md)。没有自行运行游戏或测量响应时间，不以静态审查代替用户的运行反馈。

此前开场闪退已用现有转储定位，空源 Blit 被提前解引用的修复已正式发布；修复后未自行运行。见 [闪退修复记录](docs/evidence/20261019-startup-crash-fix.md) 和 [初版交付回执](docs/evidence/rebuild-delivery.md)。这些回执不构成合规或运行效果结论。

目标为 Windows x86、UnReal World 3.89、Steam Build `25939378`。按已确认组件捕获原生文本，在构建/显示边界翻译，将编码与真实字体度量接入原生 UI，由 Mod 接管最终字形绘制；游戏管理布局、选择、命中、输入、背景和缓存生命周期。仍待整改的宿主错误透传及事务失败语义见 [纠正记录](docs/evidence/20261019-implementation-correction.md)，不将本轮改造视为整个项目全部完成。

当前设计见 [重建设计](docs/rebuild-design.md)，项目约束见 [AGENTS.md](AGENTS.md)，历史文档冲突及待整改状态见 [合规审查](docs/evidence/rebuild-compliance-audit.txt)。

全局像素跟踪及文字记录重放是代理添加的错误方案，不是用户规范。相关设计正文和引用已更正，具体出处与修改前原件见 [文档纠正记录](docs/evidence/20261019-document-render-policy.md)；字体质量要求继续保留在 [字体规范](docs/font-rendering.md)。旧跟踪源码归档于 `回收/20261019-native-draw-rework/`，不参与当前构建。

本轮开始时仅有文档和工具链，原 README 所述 `回收/20261019-001737-mod-code-cleanup-e9eade84/` 实际不存在；未使用旧源码或旧交付物冒充重建。重建前 README 和设计文件已保存在 `回收/20261019-rebuild-documentation/`。

当前源码接入范围：

- Linux 角色属性确认页的年龄、四个分组、十一项属性、身高体重与单位、确认说明和继续／重新生成动作已完成源码、统一队列编译和正式热发布；同一原生函数的属性完成提示一并接入。共享批次 `931761f724724daabc44927a2b541694`、事务 `0dad871b26a14272a5876a06fb28c497`，PID `3820329` 返回三模块第2代 Applied，旧件已移入 `回收/`。顶部民族称呼已补齐并正式热发布：`Kaumolainen` 显示为“考莫人”，全部十种民族复用文化选择译名；补充批次 `a2f7915b918b4e888f9a784a392f70e9`，PID `3820329` 返回 Adapter 第4代 Applied。此前误当姓氏保留的判断已纠正。姓名、数值、单位设置、Yes/No 键帽与 Y/N 动作保留。即时整页刷新边界待确认，已有像素等待原生重建，未自行测试。民族补充的发布状态及完整回执见 [属性确认页记录](docs/evidence/20261019-attribute-confirmation-native.md)。
- Linux 角色创建中的季节菜单标题、春夏秋冬、返回及季节难度说明、肖像选择提示。原数字键、ESC、ENTER、肖像切换和季节业务值保持；当前季节列表支持原生中英文重绘，底部提示及已完成面板沿原生构建时机更新。静态依据和编译、正式发布状态见 [季节与肖像记录](docs/evidence/20261019-season-portrait-native.md)。
- Linux 技能页已接入总标题与三类分组、30项技能、11档熟练度、初始／游戏内帮助、剩余点数、提升／降低及动态限制，并补齐29个原生百科主题的底部概述。原生菜单负责字宽、选择与命中，技能数据、点数和快捷键保持原义。已有缓存的即时整页刷新边界仍待确认；源码、编译和正式发布状态见 [技能页记录](docs/evidence/20261019-skills-native.md)。

- Linux 百科已扩展到 GAME.NFO 全部 312 个主题（原文件 313 处主题记录），608 段完整译文、447 个完整链接名称，涵盖 ANGO、文化、技能、装备、动物等。中文按完整语义翻译，字符与整词链接进入原生换行、度量和绘制；Shift+F10 沿原生构建流程刷新当前百科，关键词编辑结束后再刷新。十种文化简介与地图图例继续保留，地图图例在原生地图重建时更新。首次入场说明与未找到主题提示也已翻译，后者关闭后应用语言变化。源码、编译、正式发布状态见 [百科修复记录](docs/evidence/20261019-encyclopedia-complete.md)。
- 角色文化、性别与姓名界面的顶部提示、十种文化、按钮、性别、姓名标题、初次/重填规则及三种原生姓名错误。原动作、内部文化数据和姓名规则保留；原生文字调用即时绘制中文。姓名阶段已完成的旧面板缓存刷新边界尚待确认，源码、编译与交付状态见 [角色创建阶段记录](docs/evidence/20261019-character-profile-native.md)。
- 载入角色窗口的“载入已保存角色”“没有找到存档！”和“按任意键继续……”。源码、队列编译和正式热发布已完成；标题与两条提示沿原生文字调用绘制，存档扫描、人物名、输入和缓存由游戏管理。旧窗口待正常原生重建更新，交付回执与元数据发布拒绝记录见 [载入角色窗口记录](docs/evidence/20261019-load-saved-character-native.md)。
- 角色创建方式菜单的标题及五个选项，保留 Q/C/E/T/ESC、原英文菜单记录与角色生成动作；沿原生面板、文字和输入返回边界更新当前菜单。静态依据及交付状态见 [角色创建菜单记录](docs/evidence/20261019-character-creation-native.md)。
- 先祖列表标题、空列表提示、排序与翻页按钮、原生 ENTER 选择提示、页码及寿命/冒险天数/行走距离统计；原姓名和存档死亡描述保持，Shift+F10 沿原生列表控制流重建并保留排序、分页与选择。源码、编译及正式交付状态见 [先祖列表记录](docs/evidence/20261019-ancestors-native.md)。

- 七项菜单与条件出现的“额外内容”选项，按原生索引决定语义。
- 版本、出品、版权、作者和网站段落，保留原生动态值、姓名和控制标记。
- 启动标题、音频初始化、开场资源加载、音频加载进度及原生失败提示；109 个已确认音频显示键提供中文名称，失败提示保留实际资源路径。中文在原生文字调用内即时绘入，静态依据与交付状态见 [启动加载记录](docs/evidence/20261019-startup-loading-native.md)。
- 开场两句引言、原生动态版本及十一句“最初之冬”诗文。中文真实字宽进入原生居中计算，文字即时绘入原生主面；逐句灰度、黄色定色、淡出、等待和跳过沿用游戏流程。见 [开场诗记录](docs/evidence/20261019-intro-poem-native.md)。
- 主界面原开发者图标旁的 03 像素绘、Byayoi 同人社区署名及五位汉化内容版本。新增组件锚定该次原生图标调用，两行文字由原生段落管理，图片与字形当场绘入原生目标。源码及本轮交付状态见 [署名记录](docs/evidence/20261019-footer-branding-native.md)。
- 设置页标题、14 项选项及全部说明、底部操作提示和退出标签。中文消费原生当次格式化值，原设置动作、条件隐藏、输入和背景缓存保留；退出命中宽度接入后缀真实字宽。安装路径沿用原显示。接入与热更缓存边界见 [设置页记录](docs/evidence/20261019-setup-options-native.md)。
- 关于页的标题、版本、版权、发行商、更新说明、安装目录标签和按键按钮。实际版本、年份、姓名、网址与路径保留；中文字宽进入原生居中和按钮字符循环，字形当场绘入原生高清面。静态边界和旧窗口刷新限制见 [关于页记录](docs/evidence/20261019-about-native.md)。
- 鸣谢页的标题、24次原生正文构建和按键按钮，保留全部姓名与原生段落控制符；真实字宽接入原生居中、换行、光标与按钮尺寸，中英文切换重建原生窗口及菜单背景。详见 [鸣谢页记录](docs/evidence/20261019-credits-native.md)。
- 已接入读取、测量和即时字形输出；实际原生面和上传纹理按输出密度扩展。复制接口只转换本次矩形并复制已有像素；原生整线、字形和已确认直接读写立即转换逻辑像素格，不记录或重放文字。

历史窗口的旧实现不能视为重建已完成；设置页以本轮原生接入记录为准，关于、鸣谢、先祖等界面仍以各自新接入及交付记录为准。Byayoi 标识以本轮原生页脚接入为准，历史固定行槽方案已废止。新增接入须另行记录已确认的原生边界，禁止照抄旧页面布局。

统一构建入口为根 `build.ps1` / `build-queue.ps1`。正式启动器固定在根目录：Linux 为 `uwcn_launcher`，Windows 为 `uwcn_launcher.exe`；驻留桥和六个业务库分别位于 `package/uwcn_loader.dll`、`package/modules/`。替换旧正式文件前先移入根 `回收/` 的事务目录；没有备用运行包。

Windows 用户启动入口为根 `uwcn_launcher.exe`，默认游戏路径为 `D:\program\steam\steamapps\common\UnRealWorld\urw.exe`；也可传入 `--game "游戏完整路径"`。Windows 启动器核对已确认版本，在新建进程的游戏 PE 入口前装入正式驻留桥和模块，再恢复入口。当前 ABI 1 是本轮新框架，不声称能在历史 ABI 3 驻留桥上原位迁移。

设置页已于批次 `bcd418e7f1574fe98569bea56747dd10`、事务 `80bf73a354c74db594bf27a86fe98fd9` 完成源码接入、统一队列编译和正式发布。Adapter、Semantic、词库、构建适配及发布清单的旧五件先移入 `回收/20261019-024201-80bf73a354c74db594bf27a86fe98fd9/`；正式清单十项 SHA-256 均与磁盘一致，既有进程 `65412` 返回 Applied。启动器与驻留桥沿用原文件。Applied 表示模块交接完成，不代表视觉验收；已经打开的设置页标题和底部缓存，等原生重新构建该页才更新。详见 [设置页交付记录](docs/evidence/20261019-setup-options-native.md)。此前 03 位置调整仍以 [署名交付记录](docs/evidence/20261019-footer-branding-native.md) 为准。

关于页源码、编译及正式交付已完成。本聊天请求 `7f9a3d1faefc447e8a56668a12421316` 的批次为 `5e25d3fe9e884bcd89aa97e51230833b`，正式事务 `0b108e0b4b12449b8987ef9cfcd3800f`；旧 Adapter、构建适配和清单先移入 `回收/20261019-024247-0b108e0b4b12449b8987ef9cfcd3800f/`，PID `65412` 返回 Applied。完整回执及并行增量构建归属见 [关于页交付记录](docs/evidence/20261019-about-native.md)。更新前已打开的旧 About 窗口须原生事件循环抵达已确认边界才刷新，不宣称 Applied 即为视觉验收。

遵守用户要求：不自行启动游戏、注入运行中的游戏、模拟操作、运行产物或测试，不创建测试用例与断言。编译仅生成交付物，编译成功不等于运行效果已确认。
