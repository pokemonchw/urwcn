# 伤口、伤势与疾病界面漏译

日期：2026-11-10（Asia/Shanghai）。用户截图显示伤势窗口的标题、表头、无伤病提示、严重程度、说明、退出按钮和百科预览仍为英文。本次只阅读截图、源码、磁盘原始 PE 和逐指令反汇编；不启动或操作游戏，不运行测试，不创建测试用例或断言。正式文件沿项目队列发布；发布前已无游戏进程，本批未请求运行时交接。

## 静态证据

对象为 Windows x86《不真实的世界》3.89.1 / Steam Build `26139145`。原始 PE：`/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256：`c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。摘录见同目录 `20261110-wounds-native.asm`，其中显示 VA；下表均为 RVA。

| 原生边界 | 已确认的语义及本次处理 |
| --- | --- |
| `D7A71 → FDB00` | 伤势窗口完整框架构造调用；仅在同步调用期间标识伤势标题来源。 |
| `FC676 → F8F80` | 公用框架把完整标题从 ECX 交给原生标题组件；伤势框架内借用“伤口、伤势与疾病”。其他实际调用来源保持原值。 |
| `FDB7A → 10E5A0` | 原生一次提交完整表头 `STATE      WOUND DESCRIPTION             INJURY  TREATED`；替换同一完整资源，不拆分为 Mod 的列或坐标表。 |
| `FDC20/FDC54/FDC88 → 10E5A0` | 原生色条的三条文字；译为“危重／严重／轻微”。色条生成函数 `FDBEC → D6CF0` 保持。 |
| `D794A → 10E5A0` | 原生遍历全部伤病后选择的空状态；译为“你目前没有伤病。” |
| `D766A → 10E5A0` | 原流血标识 `BL` 的完整显示调用，译为“流血”；对应说明同步修改。 |
| `D75A3/D75D7 → D71B0` | 已接入的伤病语义来源，包含伤病类型、身体部位、侧别及原可选后缀；本次复用，不改伤病记录。 |
| `D75B2/D75E7 → 10D0` | 原普通 `%s` 和调试 `#%d - %s (E:%d) (YH:%d)` 两个格式分支；格式化完成后把已有来源绑定到原显示缓冲。调试标量与原格式保留。 |
| `D7634 → 10E5A0` | 完整伤病描述显示调用；消费前述语义来源，使用原 EDI 记录身份，保留原表格的遍历、选区、数值条及颜色。 |
| `D7B6E → CFAF0` | `ESC.Exit` 原按钮构造；保留 `ESC.` 键帽语法、动作和值，仅翻译后缀，并绑定原生 Menu 条目。 |
| `FDBA7 → 162530`、`162627 → 162300` | 按 `.WOUNDS.` 读取 `gameinfo/urw_scrinfo.txt` 的实际文件记录；在伤势说明作用域内以完整英文记录为键提供中文，保留 `<br>`。文件中的重复 `<br>` 使用同一资源。 |
| `FDBDC → 10EB40` | 说明段落的原生完整绘制调用，四个栈参数；沿用原分词、测量、折行、行距及字形推进接口。 |
| `D7B80 → 3CA90` | 原 `INJURIES` 百科预览调用；新增到既有软件预览作用域，复用 `encyclopedia_980` 的标题、摘要与《不真实的世界》百科按钮。英文检索关键字和 F1 动作保持。 |

## 修改与生命周期

新增 `modules/adapter/windows_wounds.inc`，Hook ID 为 `18700..18706` 与 `18710..18715`，经 `module.cpp` 的现有消息扩展注册、分发。`windows_encyclopedia.inc` 在既有 `7980..` 软件预览范围追加 `7983`，说明入口使用 `79F1`。本次新增地址只在已确认的 3.89.1 构建启用。

`catalog/zh-CN/cultures.tsv` 增加 `culture.wounds.*` 的 15 项资源，复用既有 `culture_text` 服务；不改变宿主 ABI、交接格式或内部英文数据。标题沿原 `F9006` 的中文宽度扩展及 `F9019` 的完整字形调用，由原生执行居中。段落先经既有传输编码和完整字形分词，再由游戏原段落函数布局。最终字形沿已接入的原生组件目标及其真实密度同步提交，不增加通用 SDL 像素扫描、贡献列表或延后重放路径。

原生 `D79F0` 的完整语言重建已经位于 `native_parent_cache_language.inc`：`injuries()` 调用原窗口，`injuries_entry/music/seed/input/result` 排除可见性初始化、音乐、随机种子和实际等待等非重绘部分；`menu()` 的实际返回身份 `D7BD5` 接入这一重建。本次复用该流程，因此无需保存整页文字或另建绘制生命周期。热发布回执仅证明模块交接，不表示已观察实际画面。

## 交付状态

源码和静态证据已保存。根入口 `.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Publish` 的请求 `62c856ab8756471d86eca31cd6640d82`、批次 `2ac18979422c4694a0435abc80e0a004` 已成功；已读取对应 `build/.compile-queue/results/62c856ab8756471d86eca31cd6640d82.json` 和 `build/.compile-queue/batches/2ac18979422c4694a0435abc80e0a004.log`。本请求执行一次配置和增量构建，产物内容与此前共享构建批次的正式发布一致，因此发布入口报告 `selected contents are unchanged`，没有重复替换。

实际正式发布来自共享队列请求 `c85e2edc4a2e46e387dd93ef81c7cfc9`、批次 `07af5cb2eb054b37ae0bd7041fd87cc9`、事务 `297822baf52249f2a475eff1f3cb19e5`，已读取该请求结果、批次日志和 `build/mingw-x86/stage/297822baf52249f2a475eff1f3cb19e5/publication-result.json`。记录为 `success=true`、`runtime_requested=false`；替换了 `package/modules/uwcn_adapter.dll`、`package/catalog/zh-CN/cultures.tsv`、共享修改的 `package/catalog/zh-CN/messages.tsv` 及 `package/release.json`。旧文件保留于 `回收/20261110-182457-297822baf52249f2a475eff1f3cb19e5/` 的原相对路径。

正式 `uwcn_adapter.dll` 的 SHA-256 为 `e6bd92a5a1a7a80c7f29b54e177a16278227bbcbdcd13e041bf92b0d7730d361`；正式 `cultures.tsv` 为 `5d5321d3bced38a79616ff514d4eb84cb178bb53121e50eb5f06ffb5b148b286`，均与正式清单相同。磁盘 DLL 包含新增 `wounds.title/header/empty/help.*` 资源引用，编译对象与正式 DLL 的时间晚于本次源码保存。上述为产物及发布的静态核对，不是实际画面验证；没有运行游戏或测试命令。
