# 游戏内进程与任务页漏译

2026-11-11，截图 `codex-clipboard-dcd3d80f-0d24-4730-9fca-e501129214e7.png`。
此前 `game_course.*` 仅覆盖开局进程选择页，没有接入游戏内 F5 信息页。本次针对 Windows 3.89.1、Steam Build 26139145，原 PE SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。

## 静态依据

- [页面原始反汇编](20261111-game-task-native.asm)采用 VA，image base 为 `00400000`。本记录后续地址为 RVA。
- [完整调用清单](20261111-game-task-calls.tsv)逐项记载原 CALL 的五字节指令、实际目标和声明目标，共41处；其中 `15D936` 已有 `native_component_binding` 的 `5507` Hook，复用该标识，不重复安装。
- [只读提取脚本](GameTaskDecompile.java)在已有 `inventory3891/urw.exe` Ghidra 工程运行，使用 `-readOnly -noanalysis`，未改写 PE 或数据库。`build/analysis/game-task-20261111/owner.c` 提取完整页面 owner、进程奖励和三类原生文字组件；日志以 `Discarding changes` 结束。首次尝试反编译体积较大的 `159430` 任务构造失败，没有将该次脚本退出码当作完整提取成功；任务来源以同目录 `producers.asm` 和 `strings.tsv` 的磁盘静态字节为据。
- `15DC70` 打开游戏自己的 `taskdata.urw`，每次读取 `A08` 字节，右侧以 `%c.%s` 生成状态键帽和任务名称；当前任务调用 `15D770`。内部文件、顺序、索引和英文记录不变。
- `15D770` 的标题字段为记录偏移4，四条目标说明起于偏移68，四条完成说明起于偏移390，快捷键字段起于偏移6E8，原生循环步长均为200字节。这里列出的是原生源字段，不是 Mod 的坐标或布局表。中文只在实际组件 CALL 中借用。
- `159430..15CBD6` 的全部48种任务构造提供原名称、目标、完成说明及命令。连续字面量区 `1CC8E0..1D7010` 共313项，排除内部图片名 `jarvi_400x300.jpg` 后312项显示来源；另有7个复用技能/任务名称及空说明。所有游戏名显示均用“不真实的世界”。
- `15CBE0` 写文件前在原命令串长度大于54时，将52、53字节写为句点、54字节写为 NUL。新增两条确切截短来源：`p.` 后的推移说明，以及 `[G] or [;] ` 后的相邻拾取说明。未修改原截短动作和保存文件，也没有按不完整前缀推测匹配其他命令。

## 实现与所有权

`modules/adapter/windows_game_tasks.inc` 在原生显示 CALL 提供中文。`module.cpp` 只增加包含、分派和安装；词库源码为 `translations/messages_embedded/values.game-task.zh-CN.tsv`，共349条唯一语义记录，其中348条新增、空命令复用既有键，已同步 `catalog/zh-CN/messages.tsv`。其中345条为任务显示值，3条为既有 `hud.command` 域的实际截短/空命令，1条为双键帽之间的“或”；完整命令描述复用已有 `hud.command`。

- 顶部标题、右侧列表标题、当前任务/任务完成标签、任务标题、快捷键标题、F5/ESC提示，进入原 `F8F80/116270/115E70/10E5A0/114680`。
- 18处解析 CALL 接入完整原生 `162300`；6处段落 CALL 保留原 `10EB40`。中文经既有双字节传输、完整字符分词、中文字宽及推进接口，原生消费者自行折行、测量高度和绘制。
- 原任务名和状态由原生 `%c.%s` 生成；Mod 仅替换句点后的名称，保留空格、x、X等原状态键帽。当前任务正文和完成正文来自同一游戏记录，未保存整页中文字段。
- 普通命令保留原句点前的键帽；双键帽按 `165340` 的实际 `[key] or [key] ` 语法保留两个原键，原 `10E720` 继续完成标记解析、键帽定位和游标推进。描述复用相同命令的中文来源。
- `15D2C0` 的完成标题、奖励说明、三个奖励按钮、后续提示接入原组件；原1/2/3动作、属性/技能修改、法术获取与进程推进不变。奖励 Menu 行绑定原中性来源，供既有 Menu 自身重建消费。
- 41处均为已确认完整 CALL，不增加内联指令覆盖。绘制 CALL 的同步 `begin_native_owner/end_native_owner` 阻止登记为另一套组件位置集合；段落只保留既有原解析器中性输入，没有页面快照或文本重放序列。
- 字形复用已有原生 `screen` 实际输出密度接口，在组件文字调用内立即绘入。顶部居中复用 `F9006` 度量；面板标题复用 `115849/1159C9`；段落复用 `10EECA/10EF57` 及原字形接口；不把 UTF-8 直接交给 ASCII 索引。48个任务名最长中文传输含 NUL 小于原 `115E70` 的108字节局部。

## 已确认的限制与待整改

- 本次新增文字在正常原生页面构建时使用当前语言。已打开 F5 页的纯重建边界尚未接入：`15D770` 写原生任务模式，末尾还可能调用带任务清零、完成位、奖励和输入的 `15D2C0`；`15DC70` 自身保存背景并在退出时推进完成任务。不能直接重入整函数充当纯重绘。本次未补造当前页字段快照、重放或推测性分支。已打开页切换语言的即时刷新仍待整改，不以编译/发布视为解决。
- `modules/adapter/native_renderer_component_binding.cpp:47` 的历史 `Owner.children`，以及`:570`、`:672` 遍历重画组件，仍违背原生 UI 生命周期所有权要求。影响为旧渲染器所有者仍可能按 Mod 集合重建；状态待整改。本次新软件页面 CALL 不加入该集合。
- `docs/design.md:19` 仍保留固定署名坐标、行槽和 DisplayPlan 的历史建议。虽已加历史错误标记，正文仍待清理；不能作为本次 UI 实现依据。

以上源码和词库修改已完成。编译及正式发布结果在下节追加。全程不启动、关闭、重启、注入或操作游戏，不模拟输入，不运行产物或测试，不创建测试脚本、测试用例或断言，不增加保护、回退或兜底。

## 编译与正式发布

源码修改、产物编译、正式文件发布均已完成；未取得运行时 Applied，也未自行验收画面。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Publish
```

| 项目 | 结果 |
| --- | --- |
| 请求 ID | `6efa8ba2e22241ccb896a9817c535c60` |
| 批次 ID | `4b01ba916b3c48569d8d74abdab34e22` |
| 请求结果 | `build/.compile-queue/results/6efa8ba2e22241ccb896a9817c535c60.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=false`，已读取 |
| 完整批次日志 | `build/.compile-queue/batches/4b01ba916b3c48569d8d74abdab34e22.log`，已读取 |
| 正式发布事务 | `deccbfd7557c4b28adb678e15f17e43a`，2026-11-11 16:55:25（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/deccbfd7557c4b28adb678e15f17e43a/publication-result.json`，`success=true`、`runtime_requested=false`、`runtime_receipts=[]`，已读取 |
| 旧正式文件 | 先移入 `回收/20261111-165525-deccbfd7557c4b28adb678e15f17e43a/package/`，保留原相对路径，已读取四件归档 |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/profiles/urw-3.89.1-steam-26139145.json`、`package/release.json` |

每批一次配置、一次增量构建，使用已有 `build/mingw-x86`。Adapter 重新编译链接成功，Catalog 目标完成、二进制内容不变。既有函数指针转换、extern 初始化、缩进和未使用项警告仍存在，本次新增文件没有编译警告。请求入队至批次完成未改动请求范围源码。

正式 Adapter SHA-256 为 `7edc2c7980bfcc1778c87b52968928cf54a9a86871be799ab2a0079355dd9281`；词库为 `b8cba760554e5ec94fd6527eafb0d1f90433a0f4a9693a839750488964f1d672`；适配文件为 `a615a6b4444f1690ee2a127b34fd4f0c6d2bcb85f9e37fbc2139326c4cff7f98`。正式文件与正式清单一致。编译小时仍为 `2026.11.11.16`，与先前同小时发布值相同，没有替换该时间文件。

发布前只读进程表未见 `urw.exe` 或 `urw3-bin`，因此未请求热加载；没有启动、结束或重启游戏。根 `urwcn_launcher.exe` 继续加载同一正式 `package/`，下次正常构建任务页时消费中文；没有独立修复包或平行运行目录。Linux 分支未作本次页面移植或发布。

修改前源码、词库、profile 和 README 另按原相对路径保存于 `回收/20261111-game-task-source/`。静态比较主词库新增348键、未移除旧键；其余既有工作区修改保留。编译和正式发布不替代视觉验收，也不解决前述已打开页的语言切换重建边界。
