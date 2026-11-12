# 数量选择窗口全部分支与文字

2026-11-12，Windows x86《不真实的世界》3.89.1 / Steam Build 26139145。用户截图中的数量框来自带最小值的 `4FC1D0`，此前物品栏汉化只接入普通数量框 `4FBD80`。本次处理这两套窗口及份数包装器的全部实际分支，不只处理截图中的初始三行。

## 静态提取

磁盘原 PE：`/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`，image base `400000h`。本文地址为VA，适配源码使用RVA。没有修改游戏PE。

[quantity_Decompile.java](quantity_Decompile.java)在既有 `build/analysis/inventory-20261110/ghidra/inventory3891` 工程上以 `-process urw.exe -readOnly -noanalysis` 提取18个完整函数：三个数量入口、八个原生组件／输入消费者、七个业务调用者。最终输出为 `build/analysis/quantity-20261112/complete.c`、`complete-refs.tsv`、`complete-incoming.tsv`；`/tmp/urwcn-quantity-complete-ghidra.log`逐项记录18个Extracted，以Discarding changes结束，工具退出0。最初11函数批次用于定位，最终清单采用18函数批次。

可审阅证据：

- 三个数量入口与原生输入函数的完整反编译保存在本地 `docs/evidence/20261112-quantity-ghidra.c`，按仓库规则不提交原始反编译C；提取脚本可重建该证据。反编译器将安全cookie调用后的EAX标作extraout_EAX；真实返回值、栈清理和分支以原指令为准，没有据该伪变量补造逻辑。
- [原指令和全部调用窗口](20261112-quantity-native.asm)。调用窗口从真实函数入口反汇编后截取末段，未从任意字节开始解码。
- [全部11处调用引用](20261112-quantity-callers.tsv)，包含两个内部转交边界。
- [13项文字／输入语法／内部数据清单](20261112-quantity-texts.tsv)与[原生引用](20261112-quantity-source-refs.tsv)。六项带语言正文，另七项为原数字、键帽、空白、光标或内部标识。
- [新增8处完整CALL](20261112-quantity-calls.tsv)，记录原5字节指令、目标、栈参数数目及语义。

## 所有可见分支

| 原生分支 | 文字与行为 |
| --- | --- |
| 最大值为1 | 两套入口直接返回1，不显示窗口；保持原生判断。 |
| 普通数量初始标题 | `4FBDE8 → 4010D0`以原总数生成 `HOW MANY? (OF TOTAL %d)`；`4FBE1B → 516270`消费完整标题。译为“选择多少？（共%d）”。 |
| 份数专用初始标题 | `4FC160`按原字节复制 `HOW MANY PORTIONS? (MAX. %d)`，传给普通窗口；非空格式覆盖调用为 `4FBDFB → 4010D0`。新增该覆盖的来源绑定，译为“选择几份？（最多%d份）”。不改原栈字符串。 |
| 带最小值初始标题 | `4FC22F → 4010D0`生成相同通用标题，`4FC24D → 515E70`绘制原生Panel。两个调用都补接；该Panel有四个栈参数，标题是参数2。 |
| ENTER | 两套窗口分别在 `4FBE91 / 4FC2BF → 4CFAF0`构建 `ENTER.All`；后缀译为“全部”，原ENTER键帽和动作13保持。原生将选择设为最大值。 |
| 数字按钮 | 原生循环生成1至min(9,最大值)；带最小值入口在minimum非零时跳过低于minimum的数字。`%d`、数字、原循环、坐标、动作31h至39h保持，不生成中文数字或新按钮。 |
| SPACE | 只有最大值大于数字按钮范围时，由 `4FBF3F / 4FC374 → 4CFAF0`构建 `SPACE.Number?`；后缀译为“指定数量”。原动作32保持。 |
| 手动输入重新显示标题 | 两套窗口分别在 `4FBF99 / 4FC3D3`再次用真实最大值生成通用标题，经 `4FBFB8 → 516270`或 `4FC3F1 → 515E70`绘制。份数包装器在此分支也使用原生通用标题，未另改游戏的选择。 |
| 手动输入提示 | `4FC05F / 4FC489 → 50E5A0`的 `Enter amount: `译为“输入数量：”；接着原getst从原文字光标处输入，上限10，原背景采样、文字、下划线光标和删除输入均由原函数管理。 |
| 输入完成／取消 | 原getst返回缓冲由原复制及atoi消费；原ENTER提交、ESC控制值与输入过滤保持。有效数量1至maximum通过，其余原生返回0，不增设输入修复逻辑。 |
| 低于最小值 | `4FC50E..4FC52B`只在已通过1至maximum的数量低于minimum时，将结果设为minimum，并以原值输出 `!The minimum is %d, which is now selected.`。沿既有 `windows_message_formats.inc`的 `FC51F`绑定及 `F6510`消息显示，译文“最少为%d，现已选取该数量。”；原感叹号标记保持。 |
| ESC、空白和缓存 | ESC动作27；空菜单标题、ESC空行、用于原光标／底色操作的空格、`_`光标、`%c`输入语法和 `askcount`缓存名均保持。菜单不接受的原输入继续等待，没有额外正文。 |

通用标题去掉此前译文中的“件”：同一原生入口还处理长度，原文没有该量词。没有按调用者重新推测单位；前一条原生业务消息继续提供其自己的长度／份数上下文。

## 全部调用者

| 调用VA | 真实来源与入参 |
| --- | --- |
| `4572A7 → 4FBD80` | 物品选择器原库存数量，格式指针为0，位置来自原菜单行矩形。 |
| `4FC1B9 → 4FBD80` | 份数包装器，原份数格式与原最大值。 |
| `4383ED → 4FC160` | 旧配方原 `[portion]`值，进入份数标题。 |
| `438446 → 4FC1D0` | 同一配方的原 `[patch]`值，minimum=1。 |
| `404162 → 4FC1D0` | 磨粉所选原料的原堆叠数量，minimum=0。 |
| `441DF5 → 4FC1D0` | 普通制作配方原批次数上限，minimum=0。 |
| `4473A4 / 4473BB → 4FC1D0` | 绑扎用品截短的两种原长度单位分支，minimum=0；原换算／减一保持。 |
| `469485 → 4FC1D0` | 材料选择的原堆叠数量，minimum=0；后续材料批次限制仍由调用者执行。 |
| `520606 → 4FC1D0` | 纺线的原米制分支，minimum=0，maximum来自原换算及ceil。 |
| `520667 → 4FC1D0` | 纺线的原英尺分支，minimum=3，maximum仍为原值。 |

这些调用者的其它业务消息继续使用各自已接入的语义来源，不将整个全局游戏调度器中的其它窗口归入本数量框。

## 接入、度量和生命周期

`windows_inventory.inc`追加 `18370..18374`五个原生完整文字CALL、`18380..18382`三个格式CALL，不重排已有Hook ID。三个格式只在原sprintf之后将原格式和原signed32操作数绑定到实际目标缓冲；不改英文缓冲、业务字段、保存数据或返回值。完整Panel、按钮和文本调用同步解析同一语义来源并借出原生编码文字，返回后按原token释放。

`515E70`和 `516270`的完整标题继续调用 `5157B0`，原生标题宽度指令 `115B59 / 115D09`消费已有完整字形度量。`CFAF0`继续构建原控件、菜单行、鼠标命中和按钮背景，原后缀度量 `CFC40 / CFC5D`及完整字形推进沿既有接口处理中文；Enter amount使用 `10E5A0`的原光标输出。字形在这些确认的组件调用内按当次原生目标真实密度提交，不经Present叠字或文字重放。

现有 `native_parent_cache_language.inc`已分别以 `FBD80 / FC1D0`的真实最大值、最小值和原构造器管理数量窗口语言重建。原等待 `FBF56 / FC390`、原getst `FC08A / FC4B4`及 `askcount`保存／恢复／释放继续使用原生生命周期。新文字CALL位于相同构造片段，初始构建和语言重建消费相同来源，没有新增页面快照、位置表、行槽、DisplayPlan或私有状态格式。

既有与约束不一致的代码继续明确列为待整改：`modules/adapter/native_footer_component.cpp:58`及79行起由Mod度量并计算主菜单署名位置；`modules/adapter/module.cpp:488`起About按钮的Mod居中例外；`modules/adapter/native_ui_scene.cpp:12`起的历史Child／Container集合及其序列化。分别影响主菜单布局、About布局和历史组件所有权，未因先前编译／发布而合规。本次数量框改动未扩展这些布局或增加重放。

没有启动、关闭或重启游戏，没有注入验证、输入模拟、测试命令、测试脚本、测试用例或断言。编译仅生成交付产物；已授权的兼容业务热发布也不构成画面验收。

## 交付状态

源码修改、产物编译、正式文件发布及现有游戏进程的兼容模块交接均已完成。源码及译文在入队前保存冻结，批次结束前未修改请求范围源码。统一入口：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2735482958/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 实际回执 |
| --- | --- |
| 请求ID | `8fe75f68e9804a14b9de81b97520f22c` |
| 批次ID | `99726225e4a2442fa0aec652517a8291` |
| 请求结果 | `build/.compile-queue/results/8fe75f68e9804a14b9de81b97520f22c.json`，Success、PublishRequested、ReloadRequested均为true |
| 完整批次日志 | `build/.compile-queue/batches/99726225e4a2442fa0aec652517a8291.log`，已完整读取；一次配置、一次增量构建，Adapter重编译并链接、Catalog目标成功 |
| 正式事务 | `7f0395af5d5d4d32a816cd89a8fbf59c`，2026-11-12 18:07:17（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/7f0395af5d5d4d32a816cd89a8fbf59c/publication-result.json`，success=true、applied=true |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/metadata/build-hour.txt`、`package/release.json` |
| 旧件回收 | `回收/20261112-180715-7f0395af5d5d4d32a816cd89a8fbf59c/package/`，旧四件按原相对路径先移动再替换 |
| 既有进程 | 宿主PID305514，Windows PID364；其原驻留桥返回ReadyToPublish，Catalog、Adapter均第2代Applied |

```text
Applied 7f0395af5d5d4d32a816cd89a8fbf59c catalog:bf126890ba7042524fd8a606e94d5390d74bed7b633449f2512c05cd7aa501c0:2 adapter:4fbc9b55bf321f695e49415c1e56bb050757384190f32c0a13477acb8f00fbeb:2
```

Adapter构建件、正式件、清单及Applied回执SHA-256均为 `4fbc9b55bf321f695e49415c1e56bb050757384190f32c0a13477acb8f00fbeb`；词库源码、正式件及清单均为 `6520e0f2e36c3b9bd804fc6a042975f4c098c6eb5314da6c2d772d15a27005ec`。Catalog DLL沿用现有二进制，新增及修订译文随其第2代加载。构建小时为 `2026.11.12.18`。编译保留20条既有函数指针转换、extern初始化、未使用项和缩进警告，0错误。

首次提交尚未创建请求即被自动审批拒绝，理由是TargetPid364与宿主PID305514不同，目标身份未核实。随后只读检查305514的启动时间、原EXE、模块映射及Wine前缀，并用该前缀既有Proton Mono解释器只读枚举Windows进程：返回 `WINDOWS_PID=364 NAME=urw STARTED=2026-11-12T17:56:56.2630610+08:00`，EXE为同一 `UnRealWorld/urw.exe`；宿主进程启动时间17:56:55，模块来自本项目正式package。`publish.ps1`的Wine命名管道使用Windows PID；核实后重新提交相同统一入口获批，未绕过队列或另建发布路径。

正常根启动器继续使用同一正式package，没有独立修复包或平行运行目录。没有重新启动、关闭或模拟操作游戏；Applied只证明模块交接完成，不代表画面已验收。
