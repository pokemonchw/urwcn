# 消息翻译失败显示原文及 HUD 闪烁修复

2026-11-11（Asia/Shanghai）。用户在 [内存诊断](20261111-flicker-memory-diagnosis.md) 后明确要求：“修复这个问题，翻译失败也不能造成界面闪烁，应该把文本展示出来”。此要求授权在翻译失败时使用原文，已记录到根 `AGENTS.md`；不扩展为其他故障的回退或测试授权。

## 最终行为与修改

`modules/adapter/windows_messages.inc:385` 的原生 F6510 消息显示边界现在先尝试完整中文投影及编码。投影或译文编码未成功时，取游戏已经接受的 `61A84B8` 正文，经 `decode_parser_original` 和现有 `encode_native` 编码进入同一个原生字宽、逐词、分页、绘制和消息生命周期。

该边界同时用于新消息和现存消息 Flow 的重建。已定位的第 8 条旧战斗消息可以按其原文显示，后续记录继续构建，成功后沿既有完成流程清除 HUD/messages pending；不强行清标志、不丢弃记录、不伪造某个人名/武器组合的词条，也不重新执行战斗业务来恢复历史语义。

三个相关语义保持点：

- `decode_parser_original` 是追加操作，采用原文前先清除失败投影已留下的半句。
- 原生 `F6621..F6662` 已去除声音字段。只有成功译文使用 `translated && sound` 再去除其保留的声音语法；采用原文时不再寻找 `}`，保留完整正文。
- 原文中的中文姓名继续进入现有字符编码及 `profile_identity_unicode` 显示作用域。未将 UTF-8 原始字节直接送进 ASCII 按字节路径。`Display.english`、英文历史构建、分页等待和续接逻辑保持。

`modules/adapter/native_hud_language.inc:173` 在完整 HUD 同步重建前保存原生 `61BBA5C` 并设为 1，覆盖右栏背景、日历、各 HUD 组件及消息构建。消息构建返回后恢复原值，后续现有调用者继续用 `10B720` 提交完整目标。父调用原本已抑制时仍恢复为 1，保持原缓存重建的嵌套语义。未新增 Present Hook、坐标表、像素追踪、文本重放或独立 UI。

静态依据包括诊断中的 `FA2FB` 右栏背景、`103869/10388C` 日历提前提交，以及原生 `10B720` 的禁止翻转判断。由此消除本次已经确认的部分画面提前呈现。

## 静态复核及范围

已交叉阅读修改前后的控制流、声音字段处理、原文混合编码、消息历史和分页分支，以及 HUD 重建的主调用和父缓存调用。HDA8、Active、Display、消息序列化、Hook 描述和 Host ABI 均未改变，可用现有 Adapter 热交接。

本次原文策略用于 F6510 共用消息消费者。未将策略放到全局递归 `native_message_source::project` 的每个语义节点，也未改动文件消息日志的动态语法恢复。原文编码服务本身的错误仍保留原返回边界，未使用未经编码的字节或假成功掩盖它。

相关静态审查另记录：`native_menu_component.cpp:74-97` 和 `native_conversation_language.inc:115-117` 的组件重建仍有独立的翻译失败状态传递；它们不是本次已采样的 F6510 失败路径，本次未修改。诊断已列明的 `native_renderer_component_binding.cpp:558-585,644-688` 退役绘制残留仍待清理；本次修复不构成其符合原生 UI 所有权要求的证明。

## 编译、正式发布与回收

保存并冻结两处产品源码后，由主代理通过根统一队列提交：

```powershell
./build.ps1 -Toolchain MinGW -Module adapter -Publish -Reload -TargetPid 7980
```

一次配置、一次增量构建成功，沿用 `build/mingw-x86`，只编译 Adapter。批次日志的诊断为既有函数指针转换、extern 初始化、未使用项及缩进警告；修改处无新增编译诊断。未运行产物作验证。

| 项目 | 已读取的实际回执 |
| --- | --- |
| 请求 ID | `53e6e3f953e449d19229198576e7a34b` |
| 批次 ID | `26499b438e4f431594016079d207dc12` |
| 请求结果 | `build/.compile-queue/results/53e6e3f953e449d19229198576e7a34b.json`；Success、PublishRequested、ReloadRequested 均为 true |
| 完整批次日志 | `build/.compile-queue/batches/26499b438e4f431594016079d207dc12.log`，已读取 |
| 发布事务 | `ca91390279434fe095db1b67a474d8bf`，20:19:58 完成 |
| 发布结果 | `build/mingw-x86/stage/ca91390279434fe095db1b67a474d8bf/publication-result.json`；success=true，PID7980 applied=true |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/metadata/build-hour.txt`、`package/release.json` |
| 旧件回收 | `回收/20261111-201958-ca91390279434fe095db1b67a474d8bf/package/`，三件文件保留原相对路径 |
| 当前进程交接 | PID7980 返回 ReadyToPublish，随后 Adapter 第4代 Applied |

```text
Applied ca91390279434fe095db1b67a474d8bf adapter:86583b6249697c75dceb79675973a45bab0816ec75a84564d8cee28bbe747c19:4
```

新 Adapter 的构建产物、正式文件、发布清单及 Applied 回执 SHA-256 一致：`86583b6249697c75dceb79675973a45bab0816ec75a84564d8cee28bbe747c19`。归档旧 DLL 为诊断所用的 `b712d15ec0df459d61f7557fdcd0eb39012e57230c380de7f85bfe09239548df`。

源码修改、产物编译、正式文件发布及兼容热交接均完成，当前进程无需重启。没有启动、关闭、重启或模拟操作游戏，没有测试、测试脚本、断言、注入验证或发布后内存采样。Applied 证明交接完成，不代替画面验收。既有 `publish.ps1` 修改未改动，也未归为本次修复。
