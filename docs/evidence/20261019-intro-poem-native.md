# 2026-10-19 开场诗接入原生文字链的静态依据

目标为 UnReal World 3.89 / Steam Build 25939378，安装文件 `D:\program\steam\steamapps\common\UnRealWorld\urw.exe`。本轮以只读 PE 字节重新核对下列调用、局部布局指令和全部原文；SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`，与既有反编译归档相同。下列地址均为 RVA；归档反汇编的 VA 使用首选基址 `0x400000`。

本轮没有启动游戏、注入运行中的游戏或模拟输入，也没有运行测试命令、测试脚本或断言。编译仅生成交付产物，授权的兼容业务热发布单独记录在末节。PE 读取、反编译归档审阅及发布 Applied 回执均不构成运行效果或视觉验收。

## 完整显示范围

截图中的 `...into the far North we shall take you.` 是 `18097D → 1254C0` 开场序列的第一句。该序列包含两句引言、原生动态版本字段，以及十一行 First Winter 诗文，共十四个文本字段。`1254C0` 不调用主菜单页脚 `1250E0`，也没有需要补造的按键提示或隐藏字幕。

| 显示身份 | 原文地址 | 完整原文 |
| --- | --- | --- |
| `intro.north` | `1AFFE0` | ...into the far North we shall take you. |
| `intro.roleplaying` | `1B000C` | As far as we can by the means of computer roleplaying... |
| 动态版本 | `1AFAD4` | Version %s |
| `intro.myth_1` | `1AFD80` | There are countless stories, legends and myths about The First Winter. |
| `intro.myth_2` | `1AFDC8` | During The First Winter, the Inehmo became many. |
| `intro.myth_3` | `1AFE00` | Men, wives, children, the heroes and the wise ones walked the Earth. |
| `intro.myth_4` | `1AFE48` | The heroes made the fire, they made the bow and the arrow and they hunted. |
| `intro.myth_5` | `1AFE98` | They made clothes, they made tools and shelters, they made skis, |
| `intro.myth_6` | `1AFEDC` | and they made drums and the kantele. |
| `intro.myth_7` | `1AFF04` | When The First Winter was over, |
| `intro.myth_8` | `1AFF24` | Inehmoes could not understand The Wind singing, |
| `intro.myth_9` | `1AFF54` | nor The Bear and The Forest humming. |
| `intro.myth_10` | `1AFF80` | The wise ones among the people said that The World was no longer real. |
| `intro.myth_11` | `1AFFC8` | The World was Unreal. |

版本参数继续来自 `12473A → 124690` 的现有读取结果。开场调用 `12582F → 124710` 可进入已有 `Scope::version`，复用 `12474C` 格式化、`124793` 中文宽度扩展和 `1247A7` 绘字，保持版本文件、默认值和实际版本语义。`logotext.png` 是原品牌图像；`bg-urwstart.png` 不含需翻译的文字。相邻的制作人员字符串属于其他原生消费者，不扩大本次范围。

## 调用与原始字节

本轮重新读取安装 EXE 后，以下原始字节与 [开场反汇编](intro-disassembly.txt)、[版本反汇编](intro-credits-disassembly.txt) 及 [原补丁清单](intro-patches.tsv) 一致。`125430` 是本轮使用的原生宽度表达式，原补丁清单未列出它。

| 接入点 | 原始字节 | 原生含义 |
| --- | --- | --- |
| `1255EC` | `E8 AF 8F FE FF` | 第一引言调用 `10E5A0`，3 个栈参数 |
| `1256C2` | `E8 D9 8E FE FF` | 第二引言调用 `10E5A0`，3 个栈参数 |
| `12582F` | `E8 DC EE FF FF` | 调用版本/标识函数 `124710`，无栈参数 |
| `1258B5` | `E8 B6 FA FF FF` | 调用十一行诗文函数 `125370`，无栈参数 |
| `125430` | `8D 04 CD 00 00 00 00` | `lea eax,[ecx*8]`：原生字节长度转宽度 |
| `125285` | `E8 16 93 FE FF` | 当前诗句淡入阶段调用 `10E5A0`，3 个栈参数 |
| `12530E` | `E8 8D 92 FE FF` | 当前诗句定色阶段调用 `10E5A0`，3 个栈参数 |

关联指令也重新读取确认：

- `125445` 为 `E8 F6 FD FF FF`，调用单行淡入函数 `125240`，1 个栈参数。
- `12541D..12542F` 为 `8D 4D 90 8D 51 01 8A 01 41 84 C0 75 F9 2B CA 8D 45 90 50`：测量 `[EBP-70]` 原显示副本，并将同一指针推入栈。
- `125437..125443` 为 `B9 90 01 00 00 99 2B C2 8B D6 D1 F8 2B C8`：原生取得中心、对宽度减半、取得当前行 y，再计算左边界。

`10E5A0` 的 ABI 是 `ECX=x`、`EDX=y`，栈参数依次为 NUL 结尾文本、SDL 映射颜色、outline。五个开场文字调用均由原调用者清理 12 字节。第一、第二引言的原生起点分别由调用者设置为 `(250,400)`、`(180,420)`；这是两个左起点，不是居中接口。接入借用译文时保留原 ECX/EDX，不在 Mod 中另建字幕槽或重新居中。

## 十一行诗文的原生居中和显示副本

`125370` 在自己的栈上建立十一项英文指针表；`125400` 按 EDI 索引 0 到 10 取得当前条目，`125410..12541B` 把原文复制到 `[EBP-70]`。这张表和每次复制的英文源数据保持原样。当前行只在已经完成复制、即将进入宽度计算和绘字的 `125430` 边界翻译。

`[EBP-70]` 与 `[EBP-4]` cookie 之间有 `0x6C` 字节，包含 NUL 的本次编码译文须符合该已确认局部容量。本次词库最长诗句的原生传输编码含 NUL 为 47 字节，落在该容量内。`12542F` 已将这个局部地址推入栈；更新局部显示副本后，无需替换已推入的指针或增添其他持久文本存储。EDI 直接给出完整语义身份，不能按英文搜索或通过像素识别推断当前行。

`125430` 的原始 `ECX*8` 由完整中文字符串的真实逻辑宽度替代，结果仍交给原生 EAX。其后的 `125437..125443` 保留：原生给出中心、计算一半宽度，并从中心减去宽度。`125445` 把原生 x/y 和本行显示副本交给 `125240`；下一行的 y 仍由 `12548E` 的原生加 10 和原循环管理。Mod 不保存行号对应坐标、不建立行槽表，也不反向驱动原生布局。

`Scope::intro_story` 可在 `1258B5` 的 Before 建立、After 结束，仅界定这次原生诗文调用。该作用域不持有整页文本。它也向既有 `outline_budget()` 提供原生已确认的 outline 1，确保 `125430` 的宽度测量与后续绘字选择同一字体校准条件。`font_engine.cpp` 的校准按 outline 计算边缘预算；测量时使用 0、绘字时使用 1 会使两处可能选择不同字号，因此不能遗漏这个参数。

`125285` 和 `12530E` 仅需在当次完整字符串绘制期间建立 `Scope::text`，复用既有 `10E67C/10E68D/10E69E/10E6AF/10E6D8 → 10DDB0` 五个完整串输出入口及 `10E700` 光标宽度扩展。前四次的原生描边位移、第五次前景、全局原生颜色和调用顺序继续由 `10E5A0` 提供。

编码继续使用已确认的原生安全双字节传输方式，避开 `10E5A0` 的 `C4/E4/F6` 重映射。编码字节数量不用于最终布局或字形索引；真实宽度及绘字前均解码为完整 UTF-8 字符串。两句引言的借用生命周期仅覆盖各自文字调用，诗文显示副本由原生栈持有，版本继续使用原生格式化缓冲。

## 原生颜色、等待和淡变

- 两句引言分别经历 EBX 0 到 62 的原生灰度阶段，颜色为 `RGB(4*BL,4*BL,4*BL)`，outline 1，每次原生 `SDL_Delay(1)`。第一句保留在原生面中，第二句绘在其下。
- 第一句后的原生等待为超过 3000 ms，第二句后为超过 2000 ms。原 `D25E0` 输入检查、原早退分支均保留。
- `1257B6 → 10D5B0` 淡出已有像素，随后 `1257BB → 10B9F0` 清屏，`1257D7 → 1127C0` 绘背景，`1257E9 → 10D5B0` 淡入背景。无需在淡变内部 Present 前另画中文或手工乘 alpha。
- 原版本行采用 `RGB(238,232,170)`、outline 1。其布局仍由 `124710` 的版本居中表达式产生。
- 每行诗文在 `125240` 中经历 63 次灰度绘字，使用原 `SDL_Delay(2)`，最后以 `RGB(252,252,84)` 定色。已经完成的行留在游戏自己的主面；每行之后由原调用者等待超过 3000 ms 并检查输入。
- 完成十一行返回 1 后，原 `125905 → D3C80` 等待按键；提前离开返回 0 并退出序列。没有额外提示、等待、按键动作、返回值或状态变更。

每次中文绘字即时进入 `61BBB10` 原生主软件面。Render 按这个实际目标的宽高与已确认 800×600 逻辑域确定字形光栅密度，保留目标原生 clipping 和 SDL 混合。字形自身缓存不持有 UI 坐标或页面重放序列。

`10AF90` 上传实际主面 pixels/pitch，后续 Present 消费已经画好的像素。淡变函数 `10D5B0` 在 `10D5DB/10D5DE`、`10D64D/10D650` 读取主面实际宽高创建自己的临时面，原 `10D73C/10D84C` 上传实际 pixels/pitch，原 `10D8E3/10D8ED` 释放临时面。现有 `native_targets.cpp` 在相应创建返回点识别淡变目标；本次不新增目标管理或逐像素跟踪。更多目标依据和已知范围限制见 [原生高清目标记录](20261019-native-hd-target-boundaries.md)。

本轮不修改任何 Present、上传、淡变、事件等待入口。原生目标资源迁移仍受既有已确认范围限制，不能由本次字幕接入推断所有窗口和运行阶段均可迁移。

## 本轮源码与热发布范围

静态审阅当前 `modules/adapter/module.cpp` 可见上述七个 Hook 已登记，`1258B5` 建立 `Scope::intro_story`，`125430` 按原 EDI 选择本行语义、度量并只更新原局部显示副本，两个故事文字调用进入 `Scope::text`。`Active` 结构未改变，新增组件沿用现有 Host ABI 1 服务。原生故事行的真实宽度、outline 预算和五次完整串绘制衔接符合前述证据；本结论不代表运行验收。

兼容业务热发布仅替换业务及正式数据，不补发过去已经执行的原生 Before。如果更新前旧代码已经进入 `125370`，该次调用没有经过新 `1258B5` 的 `intro_story_scope` Before；当前调用不能据此声称已完整切换为中文。完整覆盖应在游戏自然再次进入开场时形成。代理不为验证或补画而重播开场，也不重启游戏；Applied 回执只证明事务应用，不能证明既有画面全部重绘。

`publish.ps1` 原先以 `if (!$Reload)` 排除 profile 候选，导致兼容业务及词库热发布时，随本次接入更新的构建适配元数据不能通过同一事务进入正式位置。本轮源码已让 `profiles/` 与其他候选一起参与原有暂存、哈希、先回收后替换及清单事务，保留原 ABI 和目标指纹。这里记录的是发布路径源码修改，实际编译和发布结果仍须读取所属队列结果、批次日志及发布回执后另行登记。

## 旧文档违规与待整改记录

以下行号对应本轮开始时的 `docs/evidence/intro-static.txt`，原件已保存在 `回收/20261019-intro-poem-source-docs/docs/evidence/intro-static.txt`。其原始地址、英文清单和反汇编仍可用作静态事实，但下列接入建议不符合当前 AGENTS.md。旧编译或发布成功不能作为合规依据。

| 文件与位置 | 影响 | 状态 |
| --- | --- | --- |
| `intro-static.txt:155–157` | 描述将 Present 与清栈替换成驻留桥；不是本轮文字接入所需边界。 | 本轮不采用；现文档已改为保留原 Present。 |
| `intro-static.txt:159–164` | 要求保存已完成行的中文快照并在每次 Present 重组，转移原生面、缓存及重绘所有权。 | 已明确废弃该接入方案；现文档改为原生面持有已绘制像素。 |
| `intro-static.txt:184–190` | 要求在淡出内部 Present 读取 alpha、乘中文颜色并重放两句快照，让 Mod 管理淡变文字层。 | 已明确废弃；中文应在原生面中随原淡变一起处理。 |
| `intro-static.txt:260–267` | 把历史 `native_intro.cpp`、`IntroRequest`、整组字段计划与 Host ABI 2 写作当前实现，和当前 ABI 1 通用调用桥及即时绘字架构不符。 | 历史实现不作本轮接入依据；现文档已撤销该实现及发布记录作为当前依据。 |
| `docs/hot-reload.md:29` | 历史段落仍让 `DisplayPlan.logical_slot` 为原生提供主菜单几何，与原生布局所有权冲突。 | 待整改；文件顶部的历史说明不使这段实现建议成为现行规范，本轮不采用。 |
| `docs/hot-reload.md:39` | 历史退出页仍要求在 Present 前合成中文并自行排布行槽，转移原生绘字与排版生命周期。 | 待整改；不由本轮开场诗接入一并宣称解决。 |
| `docs/hot-reload.md:121` | 仍把旧 `DisplayPlan`、对应渲染资源及 adapter 快照当作跨代交接对象，容易继续授权已撤销的独立显示计划及其缓存生命周期。 | 待整改；本轮只迁移当前既有调用作用域和原生资源身份，不引入旧页面计划。 |

## 编译、正式发布及运行时应用

本轮主代理已完成源码修改与统一队列交付，本记录随后读取请求结果、批次日志、发布回执和正式清单。源码、编译、正式发布与运行时 Applied 分开记录如下：

- 源码：`sdk/text_services.h`、`modules/semantic/semantic.cpp` 和词库提供两句引言及十一行诗文；原生版本复用现有组件。`modules/adapter/module.cpp` 登记上述七个入口；Host ABI、`Active` 布局、驻留 DLL 和启动器未改动。构建适配 profile 增加已确认开场范围与证据，`publish.ps1` 将 profile 元数据纳入同一热发布事务。
- 编译：调用根入口 `build.ps1 -Module adapter,semantic,catalog -Publish -Reload -TargetPid 45376`。请求 ID 为 `2eb2fa5bdb374225ab94ff9f7e585d77`，批次 ID 为 `21c946b80da64d1cbba8c8c5254fc2f0`。`build/.compile-queue/results/2eb2fa5bdb374225ab94ff9f7e585d77.json` 记录 `Success=true`、`PublishRequested=true`、`ReloadRequested=true`；对应批次日志记录一次配置和该批次三个模块构建完成。既有 `GetProcAddress` 到 `SDL_GetRGB` 类型转换警告仍存在，没有编译错误。
- 正式发布：事务 `b01cab8072d74e979b3d72c572993698` 完成。`build/mingw-x86/stage/b01cab8072d74e979b3d72c572993698/publication-result.json` 记录五项正式文件替换：adapter DLL、semantic DLL、中文词库、构建适配 profile 和 `package/release.json`。被替换旧件先按原相对路径移入 `回收/20261019-022426-b01cab8072d74e979b3d72c572993698/`。Catalog DLL 虽重新编译，但内容哈希未变，不需要替换；词库变化仍触发 catalog 模块交接。没有平行修复包或独立运行目录。
- 运行时应用：同一回执记录 `Applied b01cab8072d74e979b3d72c572993698`，catalog、semantic 和 adapter 均为第 2 代，哈希分别与正式清单一致。主代理已只读核对正式清单全部十项的磁盘 SHA-256 一致。此回执证明授权事务已应用到原 PID 45376，不证明当前已显示画面的译文或视觉效果；已进入旧诗文调用的范围限制仍按前节保留。

根目录 `uwcn_launcher.exe` 仍是正常启动入口，`package/uwcn_loader.dll` 和 `package/modules/` 仍是唯一正式交付位置。本轮没有启动或重启游戏、重新注入、模拟操作、执行测试或编写测试用例与断言。

| 正式文件（相对 `package/`） | SHA-256 |
| --- | --- |
| `modules/uwcn_adapter.dll` | `1f08d54b8e27cc354728f7f8bc0fdf755a50f4f8bd33046f74eeda901ddb2d97` |
| `modules/uwcn_semantic.dll` | `7996aeb72a0f4cb1c815152b1034499567361e218271418f4a1a24ddac6153d6` |
| `modules/uwcn_catalog.dll`（内容未变） | `81b8407f805727e23de31f4f71800e8362619474c77ac48bb1bc52324d7c1c98` |
| `catalog/zh-CN/main_menu.tsv` | `446de7946716d49e1727209f8579ce8738ce5594fc7db16f000c1355c951e8c5` |
| `profiles/urw-3.89-steam-25939378.json` | `94e04f938f5fab07553f59b1cfab6e80b66bc8c3dc5765d46b953e2e7b488cf8` |
