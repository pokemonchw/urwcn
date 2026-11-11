# 按 P 闪退：现场证据与异常记录

后续更正：用户最终明确是 **Shift+P**。原生输入表确认它进入mode 0角色资料页；本次已修正该页年龄消费者读取未登记的创建期字段这一确定缺陷，并另批编译及正式发布。证据、源码和业务交付回执见[Shift+P 资料页年龄来源修正](20261111-shift-p-profile-age-crash.md)。下文保留按键澄清前的排查和两批Loader诊断交付，不能将小写p搬运分支当作最终故障路径，也不能将诊断发布当作业务修正。

2026-11-11，用户报告游戏闪退，随后明确“我按下了P，然后游戏闪退了”。未启动、关闭、重启、注入或操作游戏，未模拟输入，未执行测试、产物、测试脚本、测试用例或断言。以下只使用磁盘日志、原 PE、既有反编译、源码与编译交付回执。

## 已取得的现场

- Steam `console-linux.txt` 于12:18:34记录游戏停止、移除宿主 PID `3145474`；`gameprocess_log.txt` 记录同批进程退出。Windows PID `468` 的该次游戏已经退出。
- 最近一批业务事务 `a0d546fc14f741f0abd977736303e76d` 于12:14:25完成 Adapter 第8代 Applied。时间相邻不构成根因证据。
- 退出时正式 Adapter SHA-256 为 `ec17fb9d1dceefd74d4469ba77353fc76f07b090920ff36ebf1455ea3685bcc3`；Loader 为 `88bec8e73214b31e8f840aabe5afaf9853df60f8378feeff9d64a5dbfeae67ed`。
- 角色 `msglog.txt` 修改时间为12:18:32.949，末尾两组消息为 `PUSH_INFO` 对应的搬运提示和 `MOVE_NOTHING` 对应的脚边无物品提示。消息没有现实时间戳，不能断言末条就是本次 P 的最后一个执行点。
- `package/urwcn.log` 尾部只有此前模块交接记录，没有异常码、EIP或回溯。已查看系统日志／core目录、`/tmp/dumps`、Wine prefix用户目录及游戏目录，没有取得本次转储。其他时间、其他程序的转储未用于推断本次原因。

记录上述现场时尚未确认是否同时按Shift，当时的结论为根因待定位。后续按用户明确说明转入Shift+P资料页，结论与修正见文首链接；没有通过这些旧日志补造异常地址。

## P 相关原生路径的静态边界

对象为 Windows x86 3.89.1，原 PE SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。下文均为 RVA；只读反汇编来源为 `build/analysis/windows-3891-native-full.asm`，相关原指令已摘录至[静态反汇编](20261111-p-command-crash.asm)，既有完整物品调用者反编译位于 `build/analysis/inventory-20261110/typed-callers-ghidra.c`。

`1642FB..164306` 的原命令分支用 ECX=EDX=0、一个零栈参数调用 `58EB0`。该函数先在 `58EEC→161B00` 取得 `PUSH_INFO`，由 `58EF3→F6510` 显示，再以原空标题／空动词、flags=80h进入 `58F1C→55060`。选择器 `554F9` 的实际空集合返回值为 -3000；`58F26` 识别后在 `58F33→161B00` 取得 `MOVE_NOTHING`，`58F3A→F6510` 显示，随后清空原暂存并经原 cookie 检查返回。

非空集合继续原方向选择和 pack／move物品选择。未把空集合路径补成默认菜单、未替换业务返回值、未略过原消息、未按键值补造保护或回退。两个原消息的正式中文资源均已存在。上述指令只能说明日志所涉路径，不能补出不存在的异常栈。

## 本轮源码：保留原异常处理的现场记录

新增 `src/loader/crash_report.cpp`，由 `src/loader/host.cpp` 初始化，CMake为现有 Loader 链接 Windows `dbghelp`。Host ABI、业务 DLL与原输入动作未改变。

首批正式记录接入两个已确认的 Windows异常接口：

1. 原游戏 CRT 在 `18A64C→18AC05` 设置顶层过滤器。驻留层在其后的首次真实原生 UI事件登记异常记录过滤器，保留并调用之前的游戏过滤器；之前为空时返回 Windows原有 `EXCEPTION_CONTINUE_SEARCH`。记录函数不返回继续执行、不重试、不切语言、不重画，也不吞掉异常。
2. 原游戏 `18A0C4/18A0CD`、`18AB67/18AB71` 会先清空顶层过滤器，再显式调用 `UnhandledExceptionFilter`。因此只设置一个普通顶层过滤器不能覆盖这两条真实路径。驻留层沿原 PE导入名称找到这个实际 IAT项（本 PE为 `18C040`），使用既有 resident import Hook。在 Before读取真实 `EXCEPTION_POINTERS*`、写现场，原函数、参数、调用约定和返回值继续执行。不会通过退役／替换业务模块释放这条驻留路由。

现场包括原异常码、地址、x86寄存器、当前线程最后一次真实原生事件的 ID／phase／token，并调用 `MiniDumpWriteDump(..., MiniDumpNormal, ...)` 保存异常上下文、线程栈及模块信息。每次转储使用 UTC时间、毫秒、PID及TID命名，以 `CREATE_NEW` 创建，不覆盖旧记录。实际创建／写入错误写入现有日志，不另选目录或构造替代现场。

首批正常路径只登记过滤器和三个事件身份标量；不保存页面文字、布局、UI位置、像素、裁剪或绘制序列。诊断文件在同一正式包的 `package/crashes/`，没有平行启动目录或修复包。该记录不能追溯已经退出的进程，也不能保证取得通过原生异常接口之外直接结束进程的现场。

## 12:31 再次按 P 退出与记录盲点整改

用户再次确认“还是按 P 后退出”。Steam记录新进程于12:30:44启动、12:31:04停止；`package/crashes/` 已由新 Loader于12:30:44创建，现有日志也新增初始化成功，但目录为空、没有记录函数的错误回执。没有取得异常码，不能据此判定必然是某一种终止方式。

静态复核明确找到首批记录不能覆盖的原生错误分支：`18A0AE` 比较 ECX与进程cookie，失败跳到 `18A0E7`；`18A0F2` 检查处理器 feature 17h，支持时以 ECX=2直接在 `18A0FE` 执行 `INT 29h`。这发生在原 `UnhandledExceptionFilter` 分支之前。[Microsoft fast-fail文档](https://learn.microsoft.com/en-us/cpp/intrinsics/fastfail?view=msvc-170)明确该路径不调用进程内异常处理器。因此首批仅有顶层过滤器和该IAT观察点的记录不能覆盖这个实际分支。该静态缺口已经确认；本次退出是否经过它仍待现场证据。

当前源码作如下记录接入调整，不修改 P业务或原生失败决定：

- 在真实 `18A0AE` 的完整六字节 `CMP ECX,[cookie]` 指令之前接入既有 resident inline Hook。仅在原比较输入实际不等时记录真实寄存器与原栈返回地址，并生成不带异常流的 `MiniDumpNormal`；不存在异常时不伪造 `EXCEPTION_POINTERS`。随后仍执行原 CMP、原分支及原终止。没有改写cookie、强制相等、取消栈检查、改跳正常返回或恢复运行；这里观察的是原程序已有检查，不新增断言。
- 普通访问异常、页错误、非法指令、栈溢出与不可继续异常改由 `AddVectoredExceptionHandler` 在系统展开调用栈前记录，统一返回 `EXCEPTION_CONTINUE_SEARCH`，原生SEH及终止继续处理。记录名改为 `First-chance`，因为首次通知之后可能由游戏自己处理，不能把所有记录都称为未处理崩溃。通知顺序依据 [Microsoft vectored exception文档](https://learn.microsoft.com/en-us/windows/win32/debug/vectored-exception-handling)。
- 移除本项目的顶层过滤器替换与保留指针，普通游戏过滤器继续由游戏设置；保留已确认的原 `UnhandledExceptionFilter` 显式调用观察点。

上述仍是诊断整改，没有获得新现场、没有确认故障指令，不能当作闪退修复。源码提交统一编译队列后不再改动所属批次源码；第二批正式回执见下文。

## 既有所有权待整改项

本轮静态阅读再次看到以下历史机制，均不因先前编译／Applied而视作合规；本轮诊断没有调用或扩展其布局与重放：

- `modules/adapter/native_ui_scene.cpp:12` 的 Child／Container及 `cache_saved` 复制历史组件集合，仍需完成退役；影响原生UI及缓存所有权。
- `modules/adapter/native_message_flow.h:20` 起的 PanelSource／Record.entry／Source保存面板、矩形、光标与颜色输入；`native_message_flow.cpp:253` 的 `paint` 再遍历记录构造消息。其完整所有权整改待办，不能仅凭英文源表达式名称排除独立页面重建问题。
- `modules/adapter/native_component_binding.cpp` 的 `construct`、`native_component_model.cpp` 的 `paint` 仍有历史组件构建与消费；`native_renderer_component_binding.cpp` 的 Owner.children同样待整改。
- `modules/adapter/windows_inventory.inc:6` 的 `native_text_limit` 仍由 Mod截断文字；`native_footer_component.cpp` 独立署名位置计算及 `module.cpp` About按钮居中例外仍待交回原生布局。

## 交付状态

异常记录源码、Loader产物编译及正式文件发布均已完成。执行根 `.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module loader -Publish`；源文件在所属批次运行期间未修改，没有运行任何产物。

首次请求 `99bca1faec434f848b5191d175f3a5f4`、批次 `a73d2107b2ee4e3b9c3ee533dd087d83` 编译失败：全局初始化函数中的两处类型名漏写 `urwcn::`。该失败未进入发布；已读取请求 JSON与完整日志，在该批次结束后修正命名空间再提交。不是以编译运行游戏或验证崩溃。

| 项目 | 实际回执 |
| --- | --- |
| 成功请求 | `126a379e502c4f7ebdea718f62f794c3` |
| 成功批次 | `d63f907a9ee748688dd1b50229ff0cfc` |
| 请求结果 | `build/.compile-queue/results/126a379e502c4f7ebdea718f62f794c3.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=false` |
| 完整日志 | `build/.compile-queue/batches/d63f907a9ee748688dd1b50229ff0cfc.log`，已读取，只有既有 GetModuleApi函数指针转换警告 |
| 正式事务 | `e702cb85189141c1b34ac4acc9609452`，2026-11-11 12:29:30（Asia/Shanghai）完成 |
| 发布回执 | `build/mingw-x86/stage/e702cb85189141c1b34ac4acc9609452/publication-result.json`，`success=true`、`runtime_requested=false` |
| 正式更新 | `package/urwcn_loader.dll`、`package/release.json` |
| 新 Loader SHA-256 | `c3ab78a96396ae0a480455554cd2b12cdb158094ff89caf17cc123f0fadc0414`，正式件、构建件与清单一致 |
| 旧件回收 | `回收/20261111-122930-e702cb85189141c1b34ac4acc9609452/package/`，保留 Loader和清单原相对路径 |
| 旧 Loader SHA-256 | `88bec8e73214b31e8f840aabe5afaf9853df60f8378feeff9d64a5dbfeae67ed`，已从回收件读取 |

首批Loader的PE导入表已链接 `dbghelp.dll!MiniDumpWriteDump` 和 `SetUnhandledExceptionFilter`，只读检查未执行DLL；首批自设顶层过滤器已由12:31后的诊断整改移除。

第二批仍使用相同根编译入口及 `-Module loader -Publish`，仅接入前述实际cookie检查和首次异常通知：

| 项目 | 实际回执 |
| --- | --- |
| 成功请求 | `96771a4a72e14b4694048bb7e3268289` |
| 成功批次 | `6249cc89e17e4eeeadab8af402f92e59` |
| 请求结果 | `build/.compile-queue/results/96771a4a72e14b4694048bb7e3268289.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=false` |
| 完整日志 | `build/.compile-queue/batches/6249cc89e17e4eeeadab8af402f92e59.log`，已完整读取，Loader编译完成 |
| 正式事务 | `c207b2a3f11a407d891bba5ec41eedb2`，2026-11-11 12:37:08（Asia/Shanghai）完成 |
| 发布回执 | `build/mingw-x86/stage/c207b2a3f11a407d891bba5ec41eedb2/publication-result.json`，`success=true`、`runtime_requested=false` |
| 正式更新 | `package/urwcn_loader.dll`、`package/release.json` |
| 新 Loader SHA-256 | `94a86b0c97e7a8ea35f728b8f9f1d6465d4f5c7b2eaebc4093d7864ab3255434`，正式件、构建件与清单一致 |
| 旧件回收 | `回收/20261111-123708-c207b2a3f11a407d891bba5ec41eedb2/package/`，保留Loader和清单原相对路径 |
| 旧 Loader SHA-256 | `c3ab78a96396ae0a480455554cd2b12cdb158094ff89caf17cc123f0fadc0414`，已从回收件读取 |

只读检查第二批Loader的PE导入表，已链接 `MiniDumpWriteDump` 与 `AddVectoredExceptionHandler`，不再导入本项目原先调用的 `SetUnhandledExceptionFilter`；没有执行该DLL。此驻留层改动不支持现有进程原位替换；发布时游戏已经退出，不请求Reload、不宣称取得Applied，也不自行启动游戏。根 `urwcn_launcher.exe` 下次正常使用时加载正式 `package/urwcn_loader.dll`。转储记录功能尚未运行验收。

这两批诊断没有确认故障指令，也未修改小写p的业务路径。后续根据用户明确的Shift+P转入资料页、修正年龄来源并正式发布的记录单列于文首链接，不把本文件的诊断产物交付作为修复依据。
