# 战斗选择菜单漏译与完整静态提取

日期：2026-11-11（Asia/Shanghai）。本次以用户的 WEAPON ASPECT 截图为入口，对当前 Windows 3.89.1 原 PE 重新反编译，补齐武器攻击方式、瞄准部位、防御动作和盾牌模式的原生菜单消费者。没有启动游戏、模拟输入、运行测试、编写测试用例或断言。

## 原生证据与范围

目标游戏 `D:/program/steam/steamapps/common/UnRealWorld/urw.exe` 的 SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。两次 Ghidra 12.1.4 静态提取均成功：首批完整9函数、消费者批完整8函数，去掉重复的 `52BFD0 / 5002B0` 后共15个不同函数。分析脚本、数据库和日志保存在 `build/analysis/weapon-aspect-20261111/`；未修改原 PE。

完整控制分支见[分支清单](20261111-combat-menu-branches.md)。本地 `docs/evidence/` 中的原始输出包括业务函数反编译 `20261111-combat-menu-native.c`、消费者反编译 `20261111-combat-menu-consumers.c`、当前原文表 `20261111-combat-menu-strings.tsv`、业务指令 `20261111-combat-menu-producers.asm`、菜单交接指令 `20261111-combat-menu-command.asm`、组件指令 `20261111-combat-menu-component.asm`及调用、数据引用表。依照 README 的仓库收录范围，这些原始提取文件保留在本地，不纳入 Git；本篇和分支清单记录可提交的分析结论及地址。

本次完整范围是 `52C110 / 52E370 / 52F8A0` 三个明确战斗选择 owner 及其帮助、原生菜单消费者，包含不会弹窗、自动复用、取消、精确身体部位和诊断分支；不把整个游戏的所有战斗消息宣称为本次新提取。地址在分支清单中为 VA，本篇下表为 RVA。

| 原生边界 | 本次静态确认 |
| --- | --- |
| `12C676 / 12C744 / 12C814` | 三种武器属性各自不为200才产生B/E/P行；多于一项且没有自动复用才弹窗 |
| `12C8C7 / 12D564 / 12F0D8 / 12FB28 → 1002B0` | 四种菜单；原英文标题分别为 Weapon Aspect、Aiming Zone、Defense Maneuver、Shield mode |
| `1002DB → D3DB0` | 将原始标题复制成大写显示串，是直接查现有大小写敏感词库失败的原因之一 |
| `1003B8 → CF790` | 原生kind6菜单构建 |
| `10041E / 10042B → CF990` | 逐条复制原生上层记录，保留空行和原action；上层stride20C，下层strideE8 |
| `CFA29 / CFA5E` | 将首个竖线后的说明复制到原记录+64，主标签在竖线处终止 |
| `10048C / 10049B` | 原生选择是否添加空分隔行及 ESC.Cancel；不由Mod补行 |
| `100525 → CFFB0` | 原生完整菜单绘制；`D027F / D031F / D03C9`消费标题、带键帽标签、旁注 |
| `100367 / 100547 → 162300` | 同一完整帮助分别用于测高、实际绘制的原生分词 |
| `100381 / 100586 → 10EB40` | 原生段落测高及绘制；返回高度仍由原生代码参与菜单尺寸计算 |
| `100640 → D1120` | 原输入等待；现有 `100645` 父界面完整重建支持语言切换及兼容交接 |

## 文本与实现

`modules/adapter/module.cpp::bind_menu_consumer_source` 原来只有帮助、手工等菜单消费者，战斗词条仅供消息回显。新增 `windows_combat_commands.inc` 在普通原生标题消费时绑定实际菜单的标题、逐条原行及旁注；原生缓存物化时直接使用已绑定来源，不借其它菜单的环境状态。

| 原文或分支 | 中文来源 |
| --- | --- |
| Weapon Aspect；Blunt / Edge / Point | 武器攻击方式；钝击 / 刃击 / 刺击 |
| Aiming Zone；Body / Head / Arms / Legs | 瞄准部位；躯干 / 头部 / 双臂 / 双腿 |
| 特殊目标 neck / skull / thorax / abdomen | 复用原生 BODYPART 资源表达式；中文颈部 / 头颅 / 胸部 / 腹部，原N/S/T/A动作保持 |
| 三种难度旁注 | 原标签经竖线分隔；新增实际旁注域 `menu.aim-annotation` 的较棘手 / 困难 / 非常困难三条 |
| Defense Maneuver；Dodge / Ignore / Defense maneuvers | 防御动作；闪避 / 忽略 / 防御动作 |
| Block with %s；两手各自 Counterstrike with %s | 用%s格挡 / 用%s反击；复用真实物品语义，保留原生34字节截断分支及两点结尾 |
| Shield mode；None / Center / High / Side | 盾牌模式；无 / 中央 / 高处 / 侧面 |
| ESC.Cancel | 取消；原ESC键帽、动作27与取消行为保持 |
| HITOPT_DEATHBLOW / HITOPT_BUTCHERING | `windows_combat_help.inc`将两份完整原文绑定已有消息模板，同时进入原生测高和绘制 |
| 盾牌引言和四种结果提示 | 已有消息字面量及历史译文保持，四种原消息分支均已提取 |
| 友军风险、停止射击、仍尝试射击 | 新补 `12C39A / 12C402 / 12C43C` 三个原sprintf来源；复用既有NPC显示名称及三个已有格式译文 |
| strikeimpact / MOVEDODGE / Dodge_ML / NPCdefend | 已有四个格式来源和译文保持；不改变原诊断显示条件 |

三条诊断格式追加到现有格式表末尾，保持已有Hook ID不变。当前PE的三个格式指针相较旧版各移后10h，已按指令证据加入 `windows_3891_rdata.inc` 的逐项映射，未使用整段地址推算。词库从97740项增加到97743项，原有键值不变。未修改内部英文标识、原生数据、快捷键、动作、难度计算或配置保存。

标题保留原生大写英文副本，中文解析使用原始大小写的语义键；关闭汉化时仍显示原生大写。普通瞄准、特殊目标精确部位、两手反击等均按本次原生接受记录绑定，不在Mod中重建业务选项表。盾牌原版“None显示N、正常移动消息在D分支”的不一致明确保留，没有擅自修正游戏行为。

完整行、旁注与选择框复用 `native_menu_component.cpp::measure_row`、`D07FB / D0A49`、`D03BB` 等接口。帮助复用 `10EE68`换行、`10EF57`推进及`10EF87 → 10E5A0`字形接口；真实主目标`61BBB10`经既有 `native_targets`提供实际物理尺寸，字形在组件调用内按输出密度直接生成。没有新增固定坐标、独立UI、像素追踪、延迟文字重放或低清放大路径。

## 既有待整改项

- `modules/adapter/native_footer_component.cpp:58` 的 `paint_text`，尤其79—86行，仍由Mod计算主菜单署名宽度、间隔和坐标，违反原生布局所有权要求。影响主菜单署名，待整改；本次不调用或扩展此路径。
- `modules/adapter/native_ui_scene.cpp:12 / 17 / 29` 的历史 Child / Container / CacheRegion 状态仍保留，待继续退役。当前注释已禁止其授权额外绘制，本次没有通过它们重放战斗菜单文本。编译或发布成功不代表这些既有问题已经合规。

## 交付状态

源码修改、产物编译、正式文件替换及当前进程的兼容交接均已完成。源码保存后冻结，统一入口为：

```powershell
./build.ps1 -Toolchain MinGW -Module adapter,catalog -Publish -Reload -TargetPid 7980
```

一次配置、一次增量编译成功，0条错误、66条既有函数指针转换、成员初始化、extern初始化、未使用项和缩进警告。新战斗菜单与帮助文件未产生编译诊断。Catalog DLL沿用同一产物；词库数据已更新并随Catalog第2代重新加载。没有运行编译产物或游戏测试。

| 项目 | 已读取的实际回执 |
| --- | --- |
| 请求ID | `12df4ce4514d4061bbfb523c118cdd34` |
| 批次ID | `b88b64b2500947d795c515f63b9385b7` |
| 请求结果 | `build/.compile-queue/results/12df4ce4514d4061bbfb523c118cdd34.json`，Success、PublishRequested、ReloadRequested均为true |
| 批次日志 | `build/.compile-queue/batches/b88b64b2500947d795c515f63b9385b7.log`，已完整读取362行 |
| 发布事务 | `e8fdb40a9a0441c7be23b6351527aa9f`，2026-11-11 19:26:21（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/e8fdb40a9a0441c7be23b6351527aa9f/publication-result.json`，success=true、PID7980 applied=true |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧件归档 | `回收/20261111-192615-e8fdb40a9a0441c7be23b6351527aa9f/package/`，三件旧文件先移入回收，保留原相对路径 |
| 当前进程交接 | PID7980先返回ReadyToPublish，后返回Catalog第2代、Adapter第2代Applied |

```text
Applied e8fdb40a9a0441c7be23b6351527aa9f catalog:6bbf0f17ac1614429c8c020629746154e08906e17041c1dc1feb183977bc4aa5:2 adapter:b6df8bb25b25fe5fb79f9b0bfe08f96b0b6707c42a34f6018744d99307782160:2
```

新Adapter在构建产物、正式文件、发布清单和Applied回执中的SHA-256均为 `b6df8bb25b25fe5fb79f9b0bfe08f96b0b6707c42a34f6018744d99307782160`；新词库在源码、正式文件和清单中的SHA-256均为 `814c7cbe14090cdd62bcfca2bd200dc81cccec373b9f11b69bf43514c8b53750`。已读取回收目录中的三件旧文件清单。根 `urwcn_launcher.exe` 继续使用同一正式包，没有平行修复包。

本次没有启动、关闭、重启或操作游戏；只执行用户明确授权的兼容业务发布事务。Applied证明模块交接完成，画面仍由用户验收，无需为了安装本次更新退出游戏。开工前已存在的 `publish.ps1` 未提交修改原样保留，未归为本次源码修改。
