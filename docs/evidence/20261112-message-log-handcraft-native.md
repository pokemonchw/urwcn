# 消息日志：制作回显、物品、材料与地形漏译

后续现场更正：本批Applied后立即触发日志完整重建的既有裸RET缺陷，导致游戏17:44:08崩溃。完整转储与修正见[日志重建崩溃记录](20261112-message-log-rebuild-crash.md)。下文发布成功仅表示文件及模块交接成功，不能作为重建路径正确或画面验收的证明。

2026-11-12，用户截图 `codex-clipboard-cf0fa110-c8fb-44d9-b0da-29bbd571369a.png`。Windows x86《不真实的世界》3.89.1 / Steam Build 26139145；原磁盘 PE SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。本次只读源码、原资源、现有反编译及磁盘反汇编，不运行游戏或测试。下表使用 VA；适配源码的地址使用 RVA，基址为 `00400000`。

## 缺口与静态来源

前一轮制作业务已接入实时消息来源，但 `FE2B0` 独立读取 `msglog.txt` 的英文正文；文件没有保存原格式实参身份。实时消息已译不能证明旧历史正文已译。截图说明此前对日志覆盖范围仍有遗漏。

| 截图消息 | 已确认的原生来源 | 本次处理 |
| --- | --- | --- |
| HANDCRAFT OPTIONS、ARROWS、BUILDING OPTIONS、WOODEN BUILDING 回显 | `500846` 生成 `#%s: %s`，`5008A2` 去掉竖线旁注，`5008AB → 4F6510`；`4432AB` 可以使用基物品名称 | 完整标题与选项语法；标题、分类、配方来自569个现有静态词源，基物品复用已有完整物品语法，涵盖 Arrow |
| You see a burbot / spruce tree trunk / 30 firewoods here | `507F42` 的 `#You see %s %s.`，物品说明与 here/there 为独立原实参，见 `settlement-formats-implemented-sites.tsv:471` | 完整 here/there 句式；物品冠词、树种、复数、数量复用留存战斗声明使用的静态物品语法，不查询当前世界对象 |
| You pick up the 30 firewoods | `urw_msg.txt:211`，PICK_UP:PC | 完整模板和物品实参，数字保持原值 |
| Nggggh! Spruce tree trunk is too heavy… | `urw_msg.txt:269`，CARRY_TOO_HEAVY:PC | 完整模板和原物品名；不重算重量或搬运结果 |
| (1) You need arrowhead / log * 6 | `464730` 完整反编译 `build/analysis/handcraft-20261112/final.c:7567` 起：`?(%d) `、原需求前缀、D4020返回、已选偏好后缀，`46522E → 4F6510` | 独立序号、材料、数量及原生选择的偏好句式；有限十进制数字语法与现有物品原子 |
| Shelter；Waist deep snow with mediocre crust | `494BC0`；`494EC7 → 55E5F0` 取积雪深度，`494EE3 → 55E810` 取雪壳，`494F22..494F67` 插入 ` with ` | 独立地形及完整雪深／雪壳句式，词义限定为实际 geography.snow / geography.crust 域 |
| Branches bend and curve… as you take a closer look… | `42DBD1/42DBDC` 从 `5925D0` 复制前句；`42DFFC..42E028` 追加 `59280C` 或 `592834`；`42E02F → 4F6510` | 从12个已确认固定前句与两个实际后句生成24个完整正文，加上原生分句大小写后共30个精确历史身份 |

新增[固定地形拼接来源表](20261112-message-log-geography-bodies.tsv)保留原指针和完整英文。原指令保存在 `build/analysis/message-log-20261112-forest.asm`、`build/analysis/message-log-20261112-snow.asm`。需求格式与调用另见既有[格式清单](20261112-handcraft-format-sources.tsv)、[消息清单](20261112-handcraft-message-calls.tsv)。没有套用旧版本地址提取新文本。

## 源码与显示生命周期

`modules/adapter/windows_message_history.inc` 扩展现有完整语法；`windows_message_history_menu_words.inc` 是从既有 `values*.zh-CN.tsv` 的 menu.title / menu.section / menu.label / menu.recipe 提取的不可变词源。表内只含英文、词库域、键与语义类别，没有UI位置、行号或页面内容。已存档物品名称直接消费原历史字符串，复用 `windows_combat_declarations::lexical` 的完整静态词法，不通过当前动物、背包或材料状态补造历史业务对象。

新资源在 `translations/messages_embedded/values.message-history-handcraft.zh-CN.tsv`：16条完整语法译文、30条完整地形正文。调用 `translations/build-message-catalog.ps1 -ExistingLiterals` 生成词库，保留原98931项键值，增加46项至98977项。既有制作修改和词库没有回滚。

日志真实宽度入口 `FE5F8` 与正文入口 `FE86E → 562300` 继续共用 `windows_message_history::source`；后续 `FE9BB → 50EB40` 由原段落消费。沿既有中文传输、字宽和原生组件当次真实输出密度字形路径显示；原生管理70条记录、分页、换行、行距、颜色、按钮、窗口及缓存。本次未新增Hook、驻留ABI或持久状态字段，也没有显示位置表、中文页面快照、像素追踪或延后重放。

## 明确边界与待整改

- 原文件仅保存英文最终正文，本次只识别有静态依据的完整文本语法与有限词源；不是恢复原业务对象，不代表任意外部Mod或全部动态历史消息已经汉化。翻译未命中仍沿用户明确授权的原文显示行为，没有添加其他回退或保护。
- `native_generic_menu_language.inc` 的日志纯语言重建仍复用旧一／二行缓存标志，长记录切换语言后的页面选取精度待整改；本次未扩大此边界。
- 既有 `modules/adapter/native_renderer_component_binding.cpp:47` 的 Owner.children，以及`:570`、`:672` 遍历重画集合，违反原生UI生命周期所有权，影响旧渲染owner重建；待整改。本次日志消费者没有向集合登记新位置。
- 既有 `modules/adapter/native_footer_component.cpp:58`，尤其`:79` 起由Mod计算主菜单署名位置，违反布局所有权，影响主菜单署名，待整改。
- `docs/design.md` 仍保留固定坐标、DisplayPlan及最终Present叠字历史建议，影响设计读者判断；待清理，不作为此次实现依据。

没有启动、关闭、重启或操作游戏，没有注入验证、模拟输入、运行测试或交付产物，没有编写测试脚本、测试工程、测试用例或断言。兼容业务热发布只使用已授权的现有驻留事务。

## 交付状态

源码和98977项词库、产物编译、正式发布及兼容交接均已完成。统一入口：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2735482958/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 已读取的结果 |
| --- | --- |
| 请求ID | `c807326af7da42bebbb27e2b36c6321f` |
| 批次ID | `8bd1702da8e842bdaf779f1f56c5cc06` |
| 请求回执 | `build/.compile-queue/results/c807326af7da42bebbb27e2b36c6321f.json`，Success、PublishRequested、ReloadRequested均为true |
| 完整批次日志 | `build/.compile-queue/batches/8bd1702da8e842bdaf779f1f56c5cc06.log`，已完整读取；一次配置、一次增量构建，Adapter重新编译链接，Catalog目标成功 |
| 正式发布事务 | `bc58643adbab49feba63c6d81259a537`，2026-11-12 17:44:08（Asia/Shanghai）完成 |
| 发布回执 | `build/mingw-x86/stage/bc58643adbab49feba63c6d81259a537/publication-result.json`，success=true，PID364 applied=true |
| 正式替换文件 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧文件回收 | `回收/20261112-174406-bc58643adbab49feba63c6d81259a537/package/`，三件按原相对路径先移入再替换，未覆盖或删除旧件 |
| 现有进程 | 只读确认宿主PID225676仍为原游戏进程；Windows PID364，原驻留桥ReadyToPublish后Catalog、Adapter均第5代Applied |
| Adapter SHA-256 | `cb364aa68163f6f66cabb2963be94a27aaccbaa0a05afdf4e512ba34be762c14`，构建件、正式件、清单与Applied回执一致 |
| 词库 SHA-256 | `55d7c49bb6d0f76d103bb8811b9fa1da2ff049c7948fbaed892d47471680e69b`，源码、正式件与清单一致 |

```text
Applied bc58643adbab49feba63c6d81259a537 catalog:bf126890ba7042524fd8a606e94d5390d74bed7b633449f2512c05cd7aa501c0:5 adapter:cb364aa68163f6f66cabb2963be94a27aaccbaa0a05afdf4e512ba34be762c14:5
```

从请求提交至所属批次完成未继续修改请求范围源码，没有重复提交或清理构建树。编译仍有既有函数指针转换、extern初始化、未使用项与缩进警告，0错误；新增历史语法文件没有编译警告。本批仍属于17时，build-hour保持 `2026.11.12.17`，不作为替换文件。Catalog DLL二进制不变，词库随其第5代加载。

根正常启动器继续使用正式 `package/`，无需重启；没有独立修复包或平行运行目录。Applied只证明已授权兼容交接完成，不代替画面验收；没有运行产物、启动或操作游戏、测试或模拟输入。
