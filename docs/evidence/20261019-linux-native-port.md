# Linux x86-64 原生移植与本机交付

日期：2026-10-19。本次用户要求在本机编译部署，支持 Linux 原生游戏，并明确要求实现缺失的支持。工作遵循根 `AGENTS.md`：不启动游戏、不注入现有进程、不运行产物或测试、不创建测试用例或断言。

## 本机静态身份

游戏位于 `~/.local/share/Steam/steamapps/common/UnRealWorld/urw3-bin`，2,780,456 字节，ELF64、x86-64、PIE，带普通符号表。Steam App 351700、Build 25939378；Linux depot 351702，manifest 3782365514047820172。

- 主程序 SHA256：`4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。
- ELF Build ID：`9f3b6fb4493bdb4f4375750e71a1f12aafc59add`。
- `readelf -d` 显示依赖 SDL2、SDL2_image、SDL2_mixer、SDL2_net、libstdc++、libm、libgcc_s、libc。
- 原生可写 PT_LOAD 的末端为 RVA `0x0ada89e0`。驻留桥使用主 ELF 基址加 `0x20000000` 的独立 64 KiB 网关区，位于原生段外且处于 rel32 可达范围；地址申请失败直接报告错误，没有扫描或替代注入路径。

所有地址均来自本机 ELF 的 `nm -C -S`、`objdump -d -C -M intel` 和原始文件字节，不能套用 Windows RVA。原始完整反汇编仅在本地 `build/analysis/` 留存。接入调用清单见 [Linux 文本调用表](20261019-linux-text-calls.tsv)。

## 原生接入

`src/linux/host.cpp` 通过用户日后正常启动时的 `LD_PRELOAD` 和 `__libc_start_main` 入口，在原生 main 执行前加载正式模块。没有执行本次生成的启动器。模块服务沿用原有文本协议，但 ELF 描述符使用 EM_X86_64，宿主指针宽度为 64 位；没有宣称与 Windows x86 寄存器帧或驻留桥二进制兼容。

`src/linux/gateway.S` 保存通用寄存器、标志、x87、MXCSR 和 XMM 状态。Hook 仅覆盖已经核对的整条指令或完整 CALL；native 栈参数留在原栈，七参数调用按 SysV AMD64 ABI 传递。内联替换同时实现被覆盖指令的其他效果，例如标题宽度补丁保留 `R14D` 的原生除二运算。

| 原生接口 | Linux RVA | 扩展内容 |
| --- | --- | --- |
| textwidth | `13B460` | 完整传输字符的实际字宽；原 ASCII 8 像素度量保留 |
| textput clone | `13B760` | 本次完整文字调用内即时绘入 native screen；ASCII 原字形与中文轮廓字形分别消费其真实推进量 |
| rentextput / New_rentext | `13DE10` / `13E1B0` | 即时绘入原生 renderer 当前目标，保留原生样式和调用顺序 |
| showtext 光标宽度 | `13EA00..13EA06` | 原生 scr_xpos 的 ADD 消费字宽扩展 |
| centext 折行与末行居中 | `13EB6F..13EB79`、`13EC9C..13ECA2` | 向原生比较、除二及减法提供当前行和词的度量 |
| 原生段落宽度及推进 | `13EEC3..13EECA`、`13F00F..13F016` | 原生 tokenizer、控制标记、换行、行距与光标保存继续执行 |
| 标题居中 | `14709B..1470A1` | 实际字宽，保留原生 R14D 运算 |
| 普通及带按键按钮 | `144FB0` 内部 | 原生背景 tile 数量消费字宽；完整双字节字符进入一次原生文字调用；原生按键、后缀、点击与选择仍归游戏 |
| sink_info 居中 | `127D7C..127D82` | 惩罚栏等的原生居中消费实际字宽 |

沿用 `layout` 模块的双字节传输字母表，排除 C4/E4/F6，适应本机 `showtext` 已确认的西文重映射。没有把 UTF-8 直接交给旧逐字节路径。原始英文行记录和内部数据不改写；中文在相应显示、段落追加或格式化后的显示消费处借用，仅在同步调用中有效。

字形字典仅保存传输字符、Unicode 字形和字体宽度。公共字体缓存仅保存字体/字形的覆盖与度量；没有 UI 坐标、页面快照、裁剪历史或绘制贡献序列，也没有 Present/Copy/上传文字重放或通用像素 Hook。

## 已接入语义与生命周期

- 启动标题、音频初始化、音频设备原生失败提示、开场音乐及原生音频加载显示。源日志继续消费英文；仅 initmsg 的原生绘字调用借用中文。音频加载适配限制在 main 的初始化调用栈，日后业务音频调用不扩大为全局显示替换。
- 开场两句、原生版本和十一句诗文。width 与 fadein 调用使用同一语义编号；淡出、等待、跳过和各次原生灰度调用保留。开场整段采用进入时语言，Shift+F10 的选择在后续页面继续生效。
- 主菜单七项及条件出现的额外内容，原生页脚出品、版权、作者与版本。菜单从 native ListEntries 的索引/动作确定语义，原行、存储、选择与输入不改写。
- 关于、鸣谢、设置的现有译库字段；设置在原格式化之后取显示值，不修改选项值、修改动作或配置保存。Linux 的 Local IP/Port 原生信息保留。
- 创建方式、文化、性别和姓名界面；保留文化内部英文记录、拉丁字符姓名输入规则和原有三种校验分支。在姓名错误的原生段落追加处按已确认的错误文本选择语义。
- 载入角色标题及空存档的两条提示；不重放存档扫描。
- 先祖列表标题、空列表、排序/分页/退出、选择提示、页码，以及年龄、冒险天数和行走距离。三个数字只在一次原生 ancestorentry 行调用中借用；原生 sprintf、取整和英文死亡描述继续执行，纪念页与死亡分支不扩大接入。
- 村庄开局标题、十三条源故事记录、四条介绍及继续按钮。THE VILLAGE、RNDCAMP.1 和原生 story.txt 读取/格式化的对应关系已静态确认；空行和原生 `<br>` 保留。不更改源故事文件或开局业务。
- 已有 HUD 译库对应的负重、惩罚、疲劳、伤势、失血、饥饿、口渴、营养、体温、精力、行动、方向、速度、指令、重复、帮助、手持标题，以及季节、月份、时间、地名释义、地域、日期、比例尺和地图类型。原生 `+` 分隔、姓名、实际数值与动作保留。

Shift+F10 在本机 key_event/kb_hit 的 SDL 事件消费边界处理真实用户按键，左右 Shift 均可，repeat 不重复切换，没有生成输入。主菜单、创建/文化/性别菜单沿 LIST_Draw → 原生菜单缓存 → 原生选择 → Flip 更新；关于和鸣谢沿原函数重建，仅重建期间跳过该页的新输入等待。Mod 没有保存选择框位置或整页字段。

## 字体、待确认边界与待整改状态

后续状态：用户反馈主菜单字体模糊后，已实现原生软件目标的输出密度扩展和主菜单缩放重建；完整静态依据、适用范围、剩余描边/缓存边界及交付状态见 [Linux 字体密度修正](20261019-linux-font-density.md)。下表第一行保留首次移植交付时的事实，不代表后续源码状态。

本机 `SourceHanSans.ttc` 的 `fc-scan` 元数据确认 face 37 为 **Source Han Sans SC Bold**；SHA256 为 `767e21e7b93c2d7d566745eb6496ad04dd73ee5ab85e4b7f54b69efaddbced85`。随正式包放置字体和 OFL 许可证；SDL2_net 来自本机 Steam Runtime，并保留其 copyright。

以下项目明确待处理，不以编译成功代替实现完成：

| 文件/位置 | 影响与状态 |
| --- | --- |
| `src/linux/adapter.cpp` 的 glyph_request、HeadingBoxSoftRen 接入；`modules/render/font_engine.cpp` 的 Linux 字面选择 | 已在现有原生目标即时绘字，但 Linux screen、软件 renderer 到最终输出的高清资源迁移边界尚未完成确认和移植。当前目标的 1× 文字可能随原画面缩放；**不是 Linux 高清交付**，不得套用 Windows 高清/DPI 发布结论。待整改。 |
| Linux 设置正文、姓名阶段已完成/变暗面板、旧载入窗口、先祖页与当前村庄页 | 当前已有缓存随原生构建更新，未补造纯重绘入口或重放业务/输入。待确认。 |
| Linux 驻留/发布分支 | 兼容模块原位退役与加载协议尚未实现，Linux `-Reload` 明确拒绝；没有借用 Windows 的 Applied 回执。待实现。 |
| `docs/evidence/ancestors-static.txt:31` 起的历史 DisplayPlan/组合建议 | 与当前 AGENTS.md 冲突；文件开头已标记历史建议待清理。本移植只使用其可与 ELF 独立核对的语义线索，没有采用布局/快照建议。历史正文清理仍待处理。 |

## 编译与正式发布

统一调用根 `build.ps1 -Toolchain Linux -Publish`。Linux 构建树为 `build/linux-x86_64`；同一个根队列执行配置、增量构建与发布，不另建队列。按用户后续明确的 Linux 独立二进制启动要求，正式入口改为根目录无扩展名的 `uwcn_launcher`；其余正式文件为 `package/uwcn_loader.dll`、`package/modules/`、词库、Linux profile 和 release.json，二进制格式均为 ELF64。启动器由 `src/linux/launcher.cpp` 编译，直接加载相邻正式包并启动本机原生游戏，运行时不依赖 PowerShell 或 Wine。

Linux 发布额外包含正式字体、所需 SDL2_net、许可证、本机游戏路径和 desktop 入口。应用菜单链接指向同一正式启动器，不创建修复包、备用启动器或游戏运行副本。旧件按事务移入根 `回收/` 后才替换。

2026-10-19 10:34:25（Asia/Shanghai）完成本机首次 Linux 正式发布：

- 请求：`7854542ec1764db688c489eaef9a7a85`。
- 批次：`1ce9e17f596244d2866ddf22f353f433`。
- 发布事务：`54a1f1ec1df6434897cc6ff8d9b3af80`。
- 已读取 `build/.compile-queue/results/7854542ec1764db688c489eaef9a7a85.json` 与完整批次日志 `build/.compile-queue/batches/1ce9e17f596244d2866ddf22f353f433.log`；`Success=true`、`FullGraph=true`、`PublishRequested=true`、`ReloadRequested=false`。
- 一次配置和一次构建生成启动器、驻留库及六个业务模块，随后队列内正式发布。日志中的 15 条 semantic key switch 枚举警告源于已有 HUD/world 分发前置分支，未阻止编译；没有为消除警告添加默认语义或兜底分支。
- 根 `uwcn_launcher.exe` 权限为 `0755`；`file`/`readelf` 静态识别全部八个交付二进制为本机 ELF64。驻留入口和模块导出在 ELF 符号表中可见。
- 正式 `package/release.json` 记载的 19 项文件已逐项核对 SHA256，未发现不一致。该项仅检查交付文件身份，没有加载或执行模块。
- 应用菜单链接 `~/.local/share/applications/urwcn.desktop` 指向正式 `package/urwcn.desktop`，其 Exec 为项目根正式启动器；游戏路径文件指向本机 Steam 原生 `urw3-bin`。
- 回收批次目录：`回收/20261019-103425-54a1f1ec1df6434897cc6ff8d9b3af80/`。这是本机首次正式交付，没有被替换的旧运行文件；没有制造旧文件备份或平行运行包。
- 原游戏主程序发布前后的 SHA256 均为上述 Linux 身份，未修改游戏二进制。没有启动游戏、运行交付产物、注入进程、模拟输入或运行测试；没有运行时 Applied 回执或视觉验收结论。

源码修改、产物编译、正式文件发布均已完成；上节明确列出的高清目标、缓存重建和 Linux 热发布能力仍保持各自待处理状态，不因本批次成功改变其实现状态。

## Linux 独立二进制入口更正

用户随后明确要求 Linux 独立二进制启动文件。本次移除 `cmake/linux.cmake` 中启动器的 `.exe` 后缀配置，Linux 正式入口为根 `uwcn_launcher`。`publish.ps1`、Linux profile、desktop 入口、README 和根交付约束同步采用此路径；Windows 仍使用 `uwcn_launcher.exe`。相邻 `package/` 继续提供汉化资源和模块。

2026-10-19 10:41:38（Asia/Shanghai），通过根 `build.ps1 -Toolchain Linux -Module launcher -Publish` 完成一次配置、一次增量构建及正式发布：

- 请求 `ce750da238604ec0b11c8f0b5719fc4c`；批次 `552ad634465d4ea3af71ee4f69043a62`；事务 `39e12140d3f34793a80a03eb2a9d73d7`。
- 已读取对应请求结果 JSON、完整批次日志及 `publication-result.json`，编译和发布均成功。此次仅构建启动器，业务模块未重新构建。
- 旧根 `uwcn_launcher.exe`、旧 Linux profile、desktop 文件和发布清单先移入 `回收/20261019-104138-39e12140d3f34793a80a03eb2a9d73d7/`，保留原相对路径；应用菜单旧链接也记录在同一回收事务下。
- 正式 `uwcn_launcher` 权限为 `0755`，`file` 静态识别为 x86-64 ELF PIE 可执行文件。SHA256 为 `83e27dcf4534c98cb8bc23379be79a507664442c6cea3305999c61a8ea19d2f1`，与正式发布清单一致。清单移除了旧 `.exe` 启动器条目，desktop 的 Exec 指向根 `uwcn_launcher`。
- 源码和构建配置已修改，产物已构建，正式入口已发布。没有执行启动器、游戏、模块或测试，也未请求运行中热更新。
