# 读档进度窗口漏译

日期：2026-11-11，Asia/Shanghai。用户截图为《不真实的世界》Windows 3.89.1 / Steam Build 26139145，显示 `Wait a moment ...`、`Loading 路里卡 Kaumolainen...`。此前启动资源加载接入没有涵盖主菜单返回后的 `17E4C0` 读档路径；旧[启动记录](20261019-startup-loading-native.md)明确排除了该路径，不能据启动汉化已发布认定此窗口完成。

仅阅读用户截图、磁盘 PE、只读 Ghidra 反编译、反汇编及源码。没有启动、关闭、重启或操作游戏，没有注入、模拟输入、执行产物、运行测试、创建测试用例或断言。兼容业务交接使用已授权的驻留事务，编译只生成交付产物。

## 原生证据

原 PE：`/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。本文为 RVA，反汇编为 VA，首选基址 `400000h`。

[只读提取脚本](load_progress_Decompile.java) 在既有 `inventory3891/urw.exe` 工程上以 `-readOnly -noanalysis` 提取 `17E4C0`、`162300`、`10EB40` 三个完整函数，声明两个文本入口及段落绘制器的真实 fastcall 签名。原始完整 C 为 `build/analysis/load-progress-20261111/load-progress-ghidra.c`，控制台和 Ghidra 日志在同目录。三函数提取均成功，进程退出码0；分析数据库改动已丢弃，未改写游戏 PE。[原生指令](20261111-load-character-progress.asm)保存窗口构建至其正常完成等待的全部指令。

| 调用 RVA | 原目标与参数 | 接入内容 |
| --- | --- | --- |
| `17E520` | `116270`，原面板标题为空 | 保留原面板及其生命周期，不新增面板重绘 |
| `17E556` | `10E5A0`，`Wait a moment ...`，字串 `1DC62C` | `load_saved.wait`：请稍候…… |
| `17E6C2` | `10D0`，原 `%s %s`，实参为 `Plr.name` 与 `Plr.inhabitant` | 原身份格式和原生环形缓冲保持 |
| `17E6D4` | `10D0`，`Loading %s ...`，格式 `1DC640` | 原英文局部缓冲保持 |
| `17E6E7` | `162300`，ECX=1，EDX=原完整进度串 | `load_saved.progress`：正在载入{value}…… |
| `17E71C` | `10EB40`，ECX/EDX=原位置，栈为宽、高、颜色、outline | 登记完整原生段落消费者，继续使用原生换行和行距 |
| `17E84E` | `10E5A0`，`Ok!`，字串 `1DC6A8` | `load_saved.ready`：完成！ |

两个 `10E5A0` 调用的栈参数为 text、mapped color、outline，调用者清理12字节；段落调用清理16字节。原 `17E6DC/17E6E2` 提供解析器的实际输入和重置参数，不把返回桥地址或局部变量猜作文字。原名字位于 `A32A6E8`，文化 ID 位于 `A32A6F5`，民族原字串位于 `A32A6F6`；沿用已确认的玩家记录及十文化译名，截图的 `Kaumolainen` 显示为“考莫人”。姓名从原记录解码并保持 Unicode 内容，不按空格拆猜姓名或改写存档。

`17E4C0` 还执行原存档加载、版本迁移、文件处理和后续业务，不能为刷新重入该函数。原 `17E56D/17E72D` 的上传、`17E592/17E752` 的原组件绘制、Present 分支及完成后的 `17E865 → FB7D0` 均保持。没有新增输入、等待或 Present Hook；已有像素继续由原生缓存管理，本次译文在下次普通读档构建中进入窗口。

## 源码及度量

SDK 新增 `TextComponent::load_saved_wait/progress/ready = A03/A04/A05`；Semantic 映射、初始化词汇表和 progress 动态值一同登记；主词库新增三项。Adapter Hook `A04..A07` 仅注册于本轮已取得完整静态证据的 Windows 3.89.1。旧 Hook ID、已有组件数值、宿主 ABI 及模块状态格式保持。

进度在 `17E6E7` 登记完整中性文本来源，动态值为实际文化 ID 和原姓名，复用角色创建完成页已有的身份解析。`native_component_binding` 将当次中文借给原 `162300`，并在原 `17E71C → 10EB40` 中继续消费该来源。Mod 没有保存中文整页或输出行，原身份缓冲、英文格式和游戏内部文化值不改写。

中文经已有安全双字节传输编码进入原生解析器，每字用已有 `native_paragraph_words` 接口成为完整词元。原 `10EE68` 的词宽判断、`10EF57` 的测量推进、`10E700` 的实际绘制光标推进消费现有中文字形度量，`10EEDA` 已有扩展抑制仅用于中文分词的空格。原 `10EF87 → 10E5A0` 及五个 `10DDB0` 完整字串消费者，在原主表面的真实输出密度同步绘字。原行高、段落宽高、坐标、颜色、描边、窗口背景及缓存仍归游戏。

等待提示编码含终止符11字节，完成提示7字节，均在既有 `10E5A0` 的 `0x12C` 文本容量内；动态进度经原生词元接口处理。没有新增截断、回退、兜底、猜测性字段或保护分支，没有新增固定坐标、行槽、DisplayPlan、全局像素跟踪、绘制贡献序列或延后重放。

## 读到的既有待整改项

| 文件与位置 | 影响 | 状态 |
| --- | --- | --- |
| `modules/adapter/module.cpp::enter_component_paint` 的 About 按钮中心例外 | Mod 从 Panel 输入计算按钮中心 | 既有待整改；本批不扩展此例外 |
| `modules/adapter/native_component_binding.cpp:261` 起及 `native_ui_scene.cpp` 历史集合 | 历史组件和 Scene 仍保留布局输入／序列化，不能据其既有发布宣称整页重建全部符合所有权要求 | 既有待整改；本批沿完整原生调用借文，不新增整页重建路径 |
| `modules/adapter/windows_inventory.inc:6` 的 `native_text_limit` | Mod 消费者侧截取前缀并加点号 | 既有待整改；读档进度不调用 |

更多既有位置和状态沿用[确认框记录](20261111-confirmation-all-text.md#既有待整改项)。本轮不将编译或交付成功视为这些问题已整改。

## 交付状态

源码、三条词库和静态证据已保存。通过根入口提交统一队列，一次配置、一次增量编译完成 Adapter、Catalog、Semantic 三个目标；SDK 头文件变化引起的相关源文件按既有依赖重新编译。完整日志保留原有函数指针转换、extern 初始化、未使用项、初始化缺项、缩进及 Semantic 分类分派的枚举警告，没有编译错误。提交后至批次结束未修改所属源码。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,semantic,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 实际回执 |
| --- | --- |
| 请求 ID | `9508bff39d254d729824d1c426c402a0` |
| 批次 ID | `5c85e233350747bd99742f8dc11d1fcf` |
| 请求结果 | `build/.compile-queue/results/9508bff39d254d729824d1c426c402a0.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true`，已读取 |
| 完整批次日志 | `build/.compile-queue/batches/5c85e233350747bd99742f8dc11d1fcf.log`，已完整读取 |
| 正式事务 | `011fc6ba41ae41998349cdf96fd1021e`，2026-11-11 13:18:21（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/011fc6ba41ae41998349cdf96fd1021e/publication-result.json`，`success=true`、当前目标 `applied=true`，已读取 |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`urwcn_catalog.dll`、`urwcn_semantic.dll`，`package/catalog/zh-CN/main_menu.tsv`、新版构建适配和 `package/release.json` |
| 旧件回收 | `回收/20261111-131819-011fc6ba41ae41998349cdf96fd1021e/package/`，六件先归档后替换，保留原相对路径；旧三库及旧词库、适配、清单实际存在 |
| 进程身份 | 宿主 PID `3275331` 仍为原游戏进程；既有 Proton Mono 解释器只读枚举确认 Windows PID `364 urw` |
| 兼容交接 | `ReadyToPublish` 后返回 Catalog 第3代、Semantic 第2代、Adapter 第4代 `Applied` |

| 正式文件 | SHA-256 |
| --- | --- |
| `modules/urwcn_adapter.dll` | `f8baef33a07270a8022225accb3406e29b98f92912d38857c25fff65630fb8f3` |
| `modules/urwcn_catalog.dll` | `63c92de78b550b1092aaa88618aef23dc7f2726699b4baddc5cd3b679f69cb55` |
| `modules/urwcn_semantic.dll` | `917ef8128bae8a3f4379688228518ca8b98ff5873b9e3a5fcc1e4608b5a6d41a` |
| `catalog/zh-CN/main_menu.tsv` | `31626d31e2340ce0ea951871a234f4b9b4997ab19247a9cc958102d77ea29f3b` |

只读核对三份正式库与构建输出一致，正式主词库与源码一致，正式新版构建适配与源码一致；正式清单及 Applied 的库身份与以上一致。正式词库已含三条新增键。根 `urwcn_launcher.exe` 使用同一正式包，没有替换启动器或驻留库，没有平行运行副本。

源码修改、产物编译、正式文件发布及当前进程兼容交接均完成。无需退出重启，译文在下一次正常读档构建时消费；没有强制重入读档业务或替用户触发加载。`Applied` 仅表示模块交接，不表示实际画面已验收；本轮未自行测试。
