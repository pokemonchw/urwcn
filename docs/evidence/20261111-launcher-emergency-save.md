# 启动器外部异常监控与独立原生格式保存

2026-11-11，Asia/Shanghai。用户明确要求在启动器层捕获游戏／汉化意外闪退、强制保存并记录堆栈，随后明确要求“自己实现一套保存函数，强制保存”。据此新增外部序列化，不采用此前提出的正常时自动存档，也不调用崩溃游戏中的 Save。此例外已按本次授权记入 AGENTS.md；其余禁止代理运行游戏、测试、模拟输入和断言的要求继续有效。

## 实现范围

- `src/launcher/main.cpp`：保留现有创建调试进程和 PE 入口交接；到达入口后不再脱离调试器，初始化远程线程也通过同一调试事件泵完成。主线程仍由原顺序恢复，启动器留在外部直到游戏退出。
- `src/launcher/crash_monitor.cpp`：未处理异常的 second-chance 通知发生于进程销毁前，此时系统暂停目标全部线程；外部读取真正的异常上下文，生成完整可读内存转储、模块表和各线程 StackWalk64 回溯，调用独立保存函数后才交还原异常终止。首次异常仍交给游戏的 VEH／SEH；不吞异常、不伪造异常或强行恢复执行。
- `src/launcher/emergency_save.cpp`：从暂停目标 ReadProcessMemory，按下面列明的原生格式构建角色目录。不执行游戏函数，不改变目标内存、原游戏输入或随机数。源内存和转储保持崩溃瞬间的值；保存所需的玩家位置、文件版本、活动生物永久编号和地图块坐标转换只作用于启动器副本。
- `CMakeLists.txt`：Windows launcher 加入两份实现并链接 dbghelp。驻留 ABI、Loader、业务模块未因本功能变更。Linux 原生入口没有实施此 Windows 调试接口方案。

## 原始对象及静态来源

独立保存仅接纳 Windows x86 3.89.1 / Steam Build 26139145 原 PE：

`c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。

本地完整反汇编：`build/analysis/windows-3891-native-full.asm`。本次 Ghidra 在已有 `inventory3891` 项目上使用 `-readOnly -noanalysis`，只反编译磁盘 PE，变更全部丢弃；没有运行原 PE。提取结果：

- `build/analysis/emergency-save-20261111.c`：Save、SaveMap、HERBLORE_save、文化与村庄写入、天气写入。
- `build/analysis/emergency-save-dependencies-20261111.c`：save_creatures、save_playermap、村庄索引、原生载入目录枚举。
- `build/analysis/emergency-save-map-20261111.c`：zoomsave 与 DATA 文件。
- `build/analysis/emergency-save-zoom-20261111.c`：dataextract、marker 索引、save_zoommap、局部块分类。
- `build/analysis/emergency-save-index-20261111.c`：ZOOMINDEX 的十二字节记录、首个哨兵及 ordinal 返回值。

Ghidra 对寄存器参数和 C++ ostream 的部分类型推断不完整。天气每次 write 的真实长度、zoomsave 的 ECX/EDX、索引返回 ordinal 均读取原反汇编确认，未使用错误的推断原型执行调用。下表均为首选基址 00400000 的 VA，运行时统一换算成真实 image base + RVA。

| 原生边界 | 写入数据／格式 |
| --- | --- |
| `56DDD0` Save，`56DF24..56DF2E` | `A72A6E8` 的 `1654h` 字节，`<CharacterFile>.URS` |
| `56DE64..56DEC6` | Plr+A88 方向、A8C/A90 位置、1204/1208 局部位置或大地图零值、1634 地图尺度、1218 文件版本 185h |
| `56DFA2..56DFAC` | `59216A8` 的 `82F690h` 字节，角色 OBJ |
| `56DFF1..56DFFB` | `58F9FF8` 的 `10CC0h` 字节，CONSTANT.OBJ |
| `4397B0` | 从 `590ACB8` 起 100 个 `1A8h` 记录，仅写名称字段 +Dh 非空的 HERBLORE 记录 |
| `40CFD0` | 500 个活动 `568h` 生物；依据库存／DATA 的真实引用选择，以永久 ID−1000 写回 CRS 记录，记录日数与所在世界格 |
| `49A760` | 将 DATA 中活动槽引用转换成永久生物编号；每条 `24h`，合计 360000 字节 |
| `48E1B0 / 48E090` | BIGMAP 的 WORLD.DAT / WORLD.PLM 各 `601401h` 字节；DATA.DAT 为 360000 字节 |
| `48E1B0` 原复制 | 世界底图、已知底图、世界 DATA 的驻留副本分别为 `2D86AC8`、`3388450`、`A72BDD0`；局部场景不能将当前局部网格当 WORLD 输出 |
| `4EBC00` dataextract | 局部 5×5 个块，每块 64×64×4 字节网格；原 `C01h` stride，原点 `200+64*chunk`；每条对象 `24h`，块内坐标相对原点 |
| `4ECDE0` save_zoommap | 每块头部世界 x/y 共8字节、四层网格16384字节、2000条对象72000字节，总 `15948h` |
| `4EB810` | ZOOMINDEX 每条12字节，后两项是世界 x/y；记录的 ordinal 对应 ZOOMMAPS 偏移；首条坐标为 −1/−1，非正常地图 |
| `4EC010 / 4EC090` | 10000 个 `9Ch` marker，更新原块坐标、日期和玩家块内位置；已存在 marker 的其余状态保留原快照 |
| `588558..5885D2` | 天气：版本3（4字节）、`A7E6E4C` 起三个DWORD、`A7E6DF8` 的 `44h` 字节、`A7E7028` 的 `BFC8h` 字节 |
| `48C030` | 文化网格 `2182200`，`1800h` 字节 |
| `56E068 / 56E0AE` | MARKER `6422AF8/17CDC0h`、EXTRAMARKER `5790900/15F900h` |
| `48B160 / 48B060` | VIL 每条 `2CA4h` 字节，+8 是村庄 ID；替换同 ID 或追加；−1000 表示没有待写村庄 |
| `124E90 / 124F35..124F8D` | 载入列表按 `<目录>/<同名>.URS` 读取角色，故正式保存保持原 CharacterPath、CharacterFile 和内部姓名 |

旧 3.89 指纹仍可由启动器启动、监控和生成异常转储；本地没有其完整保存函数证据，不能外推上述独立序列化已支持旧版。未命名或尚未构建地图／建立保存目录的角色没有完整可读存档，日志明确记录实际阻断，不补造角色、地图或目录内容。

## 保存事务及含义

异常现场位于 `package/crashes/<UTC毫秒时间>-p<PID>-t<TID>-<序号>/`：

- `process.dmp`：完整可访问内存、线程与地址区域信息。
- `report.txt`：异常码／参数、真实寄存器、模块+RVA、符号可用时的函数名、各线程回溯及其停止原因、逐文件保存结果和提交结果。
- `release.json`：该次正式交付身份副本。
- `save/<原角色目录>/`：先复制原存档全部历史区域和配套文件，再写入独立序列化的当前状态；不会拿旧磁盘副本当作最新进度。

写入数据按原字节布局，并对新写文件 FlushFileBuffers。构建完整后，先将准备好的保存目录复制到游戏目录中的事务暂存位置，再把原角色目录移入项目 `回收/<现场ID>/game-saves/<角色目录>/`，最后以同文件系统 rename 提交整目录到原位置。最终提交前不会出现半份新存档；任何文件操作失败记录实际错误，现场副本及已经归档的原目录保留，不宣称提交成功、不执行自行构造的回退。

`serialization_complete`、`original_save_archived`、`native_save_installed`、`emergency_save_committed` 分开记录。独立序列化保留冻结状态，不执行原 Save 中的交互提示、地图清理／对象删除、文化重建或存档损坏后的业务调整；marker 的其他派生状态取现场现值，未重演 save_zoommap 中的地图地貌业务。文件格式完成不能证明内存业务状态在崩溃前未受损，也不能代替实际读档验收。

访问异常、栈溢出、非法指令、除零及系统交付的 fast-fail second-chance 由同一外部路径捕获，不需要枚举每个汉化钩子。已经执行完的 ExitProcess、外部强杀、断电或监控器本身被结束，没有可供此程序读取的终止前异常现场；仅收到 EXIT_PROCESS 的非零退出码时，`package/launcher.log` 如实记录没有取得异常上下文，不能伪称已取得堆栈或保存。磁盘不足、实际文件占用、跨卷不能 rename 等 OS 错误也按真实结果报告。

接口依据：

- [WaitForDebugEvent：创建进程的线程负责等待及调试句柄生命周期](https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-waitfordebugevent)
- [调试事件暂停目标全部线程，继续事件后才恢复](https://learn.microsoft.com/en-us/windows/win32/debug/debugging-events)
- [MiniDumpWriteDump：建议从单独进程保存崩溃转储](https://learn.microsoft.com/en-us/windows/win32/api/minidumpapiset/nf-minidumpapiset-minidumpwritedump)
- [外部调试器的 ExceptionPointers 位于本进程，ClientPointers 为 FALSE](https://learn.microsoft.com/en-us/windows/win32/api/minidumpapiset/ns-minidumpapiset-minidump_exception_information)
- [StackWalk64 及 DbgHelp 单线程约束](https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-stackwalk64)
- [fast-fail 向调试器提供 second-chance 通知](https://learn.microsoft.com/en-us/cpp/intrinsics/fastfail)

## 已有 UI 所有权问题

本次不调用或扩展页面重建、像素跟踪、文本重放。既有 `modules/adapter/native_ui_scene.cpp:20` 的子组件集合、`native_renderer_component_binding.cpp:42` 的 Owner（`:47` children）、`native_message_flow.cpp:253` 的记录消费、`native_footer_component.cpp:58` 的 Mod 几何及部分 Mod 居中仍有先前记录的原生 UI 所有权待整改项：影响页面重建／布局及缓存所有权，状态均为待整改，不能因本次启动器编译或发布视为合规。此次启动器只读取完整进程崩溃快照，没有在 SDL 或逐像素调用中建立像素贡献记录。

## 交付状态

源码修改、统一队列编译和正式文件发布均完成。执行根入口：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module launcher -Publish
```

| 项目 | 实际回执 |
| --- | --- |
| 请求 ID | `a4c0c6f5a05a458b92d85fcd3345dd79` |
| 批次 ID | `3ff791f74fa4486f8168b557948e94cb` |
| 请求结果 | `build/.compile-queue/results/a4c0c6f5a05a458b92d85fcd3345dd79.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=false`，已读取 |
| 批次日志 | `build/.compile-queue/batches/3ff791f74fa4486f8168b557948e94cb.log`，已完整读取 |
| 编译 | 一次配置和一次增量构建；三份 launcher C++ 源码编译、链接成功，本批无编译警告／错误；未运行产物 |
| 正式事务 | `969e579fdf2942b49e7a9c3b1c77c08f`，北京时间 2026-11-11 17:51:24 完成 |
| 发布结果 | `build/mingw-x86/stage/969e579fdf2942b49e7a9c3b1c77c08f/publication-result.json`，`success=true`、`runtime_requested=false`，已读取 |
| 正式替换 | 根 `urwcn_launcher.exe`、`package/release.json` |
| 旧件回收 | `回收/20261111-175124-969e579fdf2942b49e7a9c3b1c77c08f/`，保留根启动器与 package 清单的原相对路径 |
| 新启动器 SHA-256 | `52c2abf1c247235e0afa5d4ee55e0f0a14cedadc226f33ff657c74e5f00b0f86`，正式件、构建输出与发布清单一致 |
| 旧启动器 SHA-256 | `dbf7a2464f6da022c932e7dbb2b88503bf71bf5f98fad941e090e32f91c99182`，已从回收件读取 |

对正式 PE 的只读导入表检查确认链接 `dbghelp.dll!MiniDumpWriteDump / StackWalk64` 及 `WaitForDebugEvent / ContinueDebugEvent / ReadProcessMemory / DebugSetProcessKillOnExit`；没有加载或执行此 EXE。没有因本功能重编或替换 Loader、Adapter 等业务库。

首批结束后，静态复核补齐原生世界坐标域要求：`4ECDE0` 明确以 `x<C00h/y<800h` 访问世界，独立保存副本在计算块坐标前拒绝损坏的越界值，不将其参与有符号加减或提交到存档。没有编写或运行坐标测试。该源码修改另批提交同一入口，最终正式件以第二批为准：

| 项目 | 第二批实际回执 |
| --- | --- |
| 请求 ID | `940562193b014151bbc3d04c32720aff` |
| 批次 ID | `b34da6b328314dbeb0751d780c8f29fc` |
| 请求结果 | `build/.compile-queue/results/940562193b014151bbc3d04c32720aff.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=false`，已读取 |
| 日志 | `build/.compile-queue/batches/b34da6b328314dbeb0751d780c8f29fc.log`，已完整读取；一次配置与一次增量编译／链接成功，无警告／错误 |
| 正式事务 | `76e8f2fa6c364438b735836aec7ea32c`，北京时间 17:53:26 完成 |
| 发布结果 | `build/mingw-x86/stage/76e8f2fa6c364438b735836aec7ea32c/publication-result.json`，`success=true`、`runtime_requested=false`，已读取 |
| 正式替换 | 根 `urwcn_launcher.exe`、`package/release.json` |
| 回收 | `回收/20261111-175326-76e8f2fa6c364438b735836aec7ea32c/`，保留原相对路径 |
| 最终启动器 SHA-256 | `707d56da57872190ab92cf57f74c4821869af337efe96794de770670e527cfd7`，正式件、构建输出与发布清单一致 |
| 第二批回收启动器 SHA-256 | `52c2abf1c247235e0afa5d4ee55e0f0a14cedadc226f33ff657c74e5f00b0f86`，已从回收件读取，即首批正式件 |

当前已有游戏进程由此前会退出的旧启动器创建，不能凭磁盘替换追溯建立调试会话；本批没有请求热加载，没有注入、操作、关闭或重启该进程。下次用户正常使用根启动器时，由这份正式入口从进程创建起持续监控。

源码在请求所属批次执行期间保持冻结，批次结束后只补录文档。没有启动、重启、关闭、注入或操作当前游戏，没有运行产物、测试或创建测试用例、测试脚本、断言。外部异常捕获、保存及实际读档均未运行验收；编译和正式发布不作为运行成功的证据。
