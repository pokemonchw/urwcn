# 消息日志页漏译

2026-11-11，用户截图 `codex-clipboard-84ecae4d-7545-4d7d-a377-369ef6ac1c0a.png`。对象为 Windows x86《不真实的世界》3.89.1 / Steam Build 26139145；原 PE SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。下文地址为 RVA，附带指令和调用清单使用 VA，基址 `00400000`。

## 原生来源与缺口

- [页面与文件读取原指令](20261111-message-log-native.asm)、[调用指令清单](20261111-message-log-calls.tsv)均从磁盘 PE 提取，没有运行游戏。复用只读 `GameTaskDecompile.java`，在既有 `inventory3891/urw.exe` 工程以 `-readOnly -noanalysis` 提取完整 `FE2B0` 与段落组件；完整 C 和 Ghidra 日志在 `build/analysis/message-log-20261111/`，退出码0，数据库修改已丢弃。
- `F6280` 将英文消息写入角色自己的 `msglog.txt`。既有 `windows_messages.inc` 在写入边界保持英文，并按原 `F6510` 规则去除首字节颜色标记、全部 `@` 和原循环跳过的第二个空格。历史文件未持有原消息的结构化格式实参。
- `FE2B0` 自己读文件、拆分 `| ` 两侧元数据和正文，维护70条原生环形记录；`D4280` 明确去掉 CR/LF。正文数组为 `61A9DB0`，记录步长1024；这些是原生英文数据，不是 Mod 行槽。
- 旧 `native_generic_menu_language.inc` 已安装 `FE5F8/FE86E/FE9BB/FEA3C` 四个接入点，但正文解析、段落和计数分派直接返回，宽度只度量原英文，因此屏幕消息汉化没有覆盖历史查看器。
- 截图中的五种不同正文均有静态来源：聚落发现句已有带颜色标记的字面量译文；图块重载前后已有完整字面量译文；两种帮助菜单回显为原 `1002B0` 的标题、分隔符及选项组合。六行中“设置选项”重复两次。

## 源码与词库

`windows_message_log.inc` 接入原组件：

| 原生位置 | 目标与用途 |
| --- | --- |
| `FE478` | `116270`，标题“消息日志” |
| `FE86E` | `162300`，当前原生记录完整正文 |
| `FE9BB` | `10EB40`，原段落绘制 |
| `FE5F8` | 原 `strlen*8` 度量操作数，后续原 `FE601` 比较与一/二行标志不变 |
| `FEA0B` | 原 `sprintf` 的计数格式，三个原整数实参不变 |
| `FEA3C` | 原完整计数字符串绘制 |
| `FEB38/FEB66` | 原 `CFAF0` 的退出、添加备注按钮，键帽与动作不变 |
| `FEC95` | 原备注输入说明 |

前述四个既有 Hook 保留原 ID、安装位置及字节；generic_menu 交给新消费者处理两个阶段，没有重复安装。其余新增文字接入点均为完整 CALL。标题、正文、计数和提示由原组件同步绘入原目标，使用既有双字节传输、完整字符分词、中文字宽、游标推进及实际输出密度接口。原控件、换行、行距、翻页、背景和缓存仍由游戏管理。新增绘制调用以同步 `begin_native_owner/end_native_owner` 避免登记为另一套位置组件集合。

`translations/build-message-catalog.ps1 -ExistingLiterals` 从已核实的中性 `message.literal.*` 来源派生历史正文身份；其处理与原 `F6510` 的确切正文规则一致，不解析或猜测动态句式。新增 `values.message-log.zh-CN.tsv` 提供5项界面资源和两项完整菜单回显。主词库由96113项增至96768项，新增655项，原键没有删除或改值。历史域共650项，其中648项从既有字面量派生、2项为截图中的完整回显。

`-ExistingLiterals` 是显式数据生成方式，不读取 PE 的旧地址。旧脚本的 `-GameBinary` 模式仍以3.89字面量地址清单读取；当前3.89.1不能直接套用该模式。本轮首次本地生成发现此差异后，已在提交编译前恢复原词库，以显式中性来源方式重新生成；没有把错误生成文件发布或提交编译。此旧模式对新版 PE 的直接读取限制仍待整改。

## 当前页重建

旧重建在 `FEA44` 停止，然后调用空标题 kind-100 Menu 的 `CFFB0`；该路径不会重画此类按钮。现让原生 `FE2B0` 继续完成 `CF790` 和六次 `CFAF0`，在 `FEB77` 的原输入 CALL 前返回。普通输入通过原 `FEB7C` 返回地址及 `D1120` 目标继续，未复制相对 CALL 到异址 trampoline。原局部容量仍在原边界交还真实等待帧。

借用构建跳过文件重读，消费原70条英文记录，不增加页面中文快照或像素跟踪。全构建已拥有按钮，不再恢复旧 Menu 并以通用消费者重画页脚。没有驻留桥或持久状态格式变更，可用既有兼容事务交接。

## 明确限制与待整改

- 本轮涵盖截图全文、页面文字及已有固定消息字面量的历史显示，不代表整个历史文件的所有动态句式都已汉化。已写入文件的动态消息只剩英文结果，其格式实参没有持久身份；本轮不按英文前缀猜测或补造业务字段。
- 已打开页的语言重建复用原生缓存的一/二行选择标志；它在文件读取时按当前语言实测，但纯语言重建未重新计算此前语言的全部缓存标志。长记录切换语言后的页选取精度仍待整改，原段落本身会按当前中文度量换行。未运行画面验收。
- `native_renderer_component_binding.cpp:47` 的历史 `Owner.children`，以及`:570`、`:672` 遍历重画组件，仍违反原生 UI 生命周期所有权要求，影响旧渲染器所有者的组件集合重建；待整改。本轮新日志调用不加入该集合。
- `docs/design.md:19` 仍保留固定署名坐标和 DisplayPlan 行槽等历史建议；正文清理仍待完成，不能作为本次实现依据。

另保留并合并手工制作菜单任务在 `module.cpp` 的 `HANDCRAFT OPTIONS` 绑定修改。两任务统一使用同一次 `adapter,catalog` 编译和兼容发布。

未启动、关闭、重启或操作游戏，未注入或模拟输入，未运行产物或测试，未编写测试用例、测试脚本、断言、保护、回退或兜底。只读进程身份为宿主PID3385055、Windows PID360，Wine prefix 为 `compatdata/2735482958/pfx`。

## 编译与正式发布

源码修改、产物编译、正式文件发布与兼容运行时交接均已完成；画面尚未自行验收。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 360 -WinePrefix /home/lulika/.local/share/Steam/steamapps/compatdata/2735482958/pfx -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `4098da4a293140d8b9697622da12481c` |
| 批次 ID | `6927a43e04494e73a3aa30a86d71ac7c` |
| 请求结果 | `build/.compile-queue/results/4098da4a293140d8b9697622da12481c.json`，`Success=true`，发布及Reload均为true，已读取 |
| 完整批次日志 | `build/.compile-queue/batches/6927a43e04494e73a3aa30a86d71ac7c.log`，已完整读取 |
| 发布事务 | `c3b60885ec374109a26c208eac78d4ac`，2026-11-11 17:09:58（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/c3b60885ec374109a26c208eac78d4ac/publication-result.json`，`success=true`、`runtime_requested=true`、`applied=true`，已读取 |
| 当前运行代数 | Windows PID360，Catalog第3代、Adapter第3代，`ReadyToPublish`后取得`Applied`，模块SHA与正式清单一致 |
| 旧文件归档 | `回收/20261111-170956-c3b60885ec374109a26c208eac78d4ac/package/`，五件旧正式文件先归档，保留原相对路径 |

一次配置、一次增量构建，沿用 `build/mingw-x86`。Adapter重新编译链接，Catalog目标完成、二进制内容不变。原函数指针转换、extern初始化、缩进及未使用项警告仍存在；本轮新文件无编译警告。从请求入队至批次结束没有修改编译范围文件，没有重复请求。

正式替换五件文件为 `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/profiles/urw-3.89.1-steam-26139145.json`、`package/metadata/build-hour.txt`、`package/release.json`。Adapter SHA-256 为 `00b30991882a1138d31c71b5877ca4cd2fde9e6b64a37b536eb9db48ac39d383`，词库为 `4cd0ad16e1551303adf89685c003335d71feb96d312a3bec7b0964113e195eb7`，适配为 `c2601ed2a4132d84446a006a3edc0f98ea4a76724dd049c5005c4d1f52591041`。编译小时更新为 `2026.11.11.17`。根 `urwcn_launcher.exe` 继续使用同一正式包，没有平行修复包。

已通过现有驻留事务更新当前进程，无需重启。`Applied`证明兼容模块交接完成，不代替日志页的视觉验收，也不消除上节明确记录的待整改项。全过程未操作游戏、运行产物或测试。
