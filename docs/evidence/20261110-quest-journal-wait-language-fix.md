# 任务日志空页语言切换与卸载刷新修正

日期：2026-11-10（Asia/Shanghai）。用户报告已汉化的任务日志空页中，Shift+F10 不能切回英文，Shift+F5 卸载也没有恢复原文。此次只读现有日志、源码、原始 PE 静态反汇编；未操作游戏、模拟输入、运行测试、创建测试用例或断言。

## 根因

`package/urwcn.log` 已记录用户触发的 `Shift+F5: translation unloaded ...` 与 `latest translation modules ... reloaded`。这证明日志中的卸载／重载动作执行过，不能将画面仍为中文直接判为没有识别按键。现有日志没有这些行的独立时间戳，不将其作为逐次按键或本次画面验收的证明。

`modules/adapter/native_quest_menu_language.inc` 原 `wait` 在共同 `D3D05 → D3BF0` 的 Before 回调读取 `[D3C80.EBP+4]`，要求等于游戏原返回地址 `159335`。

但同一文件早已给 `159330 → D3C80` 安装完整 CALL Hook。`src/loader/hook_host.cpp:46` 起的 `urwcn_before_route` 将真实返回地址保存到驻留 Pending，并将游戏栈的该返回地址改成 `urwcn_after_bridge`。因此原 `wait` 的识别条件不成立，F10、F5 和兼容发布产生的语言 pending 无法在空任务页消费。此前证据记录中将此栈字段当作未被桥接的游戏地址，结论有误。

## 静态依据与修正

原始 Windows 3.89.1 PE SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。地址均为 RVA，摘录见同目录 `20261110-quest-journal-wait-language-fix.asm`，来源为 `build/analysis/windows-3891-native-full.asm`。

| 边界 | 已确认的原生语义 |
| --- | --- |
| `17DED9 → 158CE0` | 任务日志列表的唯一原直接 CALL，原返回为 `17DEDE`；项目未给此 CALL 安装 Hook |
| `158CE0..158CE9` | 原 `PUSH EBP; MOV EBP,ESP` 建立真实列表父帧 |
| `158DB4 / 158DBA` | 将任务日志 owner 的实际 texture 写入原输出 `A1C1CBC`，上下文 `A1C2010` 写为 `10h` |
| `158DC4..158DCC` | 原 count 为零时跳入 `159250` 空列表构造 |
| `159330 → D3C80` | `158CE0` 中唯一直接调用 D3C80 的位置，位于空列表分支 |
| `D3C80..D3C83` | 原等待帧保存真实父 EBP；CALL 桥替换返回地址，不替换这个父 EBP |
| `D3D05 → D3BF0`、`D3D0A..D3D0D` | 原等待每轮调用点；非正按键结果继续原等待，而不退出任务日志 |
| `D3BFC → D1C00`、`D3C0F..D3C17` | 原输入的 `-2` 唤醒值直接返回到同一等待循环 |

新的 `wait` 先按游戏自己选择的输出 texture 与 `10h` 上下文识别任务日志资源，随后在这个已确认的 D3C80 等待帧中，读取其保存的真实列表父 EBP，并使用父帧未被 Hook 的原返回 `17DEDE` 识别空列表构造。原生输出身份是共同等待入口的语义区分，不保存该 texture 或建立资源镜像。它不再读取已经被桥接的 `159335` 栈槽。此父／子关系由完整调用点及两个原 prologue 直接确认，不扫描祖先链、不按未知字段猜测界面，不新增默认父页或缺源回退。

重建仍使用同一存活父帧的原 count、任务索引、分页和原纹理构造；中文／英文在原显示边界选择。原 D3C80 等待、F10 输入消费和 Loader 的 F5 卸载／重载动作保持。没有新增页面快照、坐标、像素记录、组件遍历或文字重放。

没有新增 Hook、Scope、保存字段、状态分节或 ABI，也不改变既有驻留 Hook 描述。已打开的旧等待帧仍保存此真实父 EBP，因此兼容 Adapter 热交接后即可由其下一轮原输入调用消费，不要求关闭当前页面、手动卸载或重启。

## 既有待整改项

- `modules/adapter/native_footer_component.cpp:88` 起仍由 Mod 计算主菜单署名布局，影响原生布局所有权，待整改；本次不扩展。
- `modules/adapter/native_ui_scene.cpp:12` 与 `native_renderer_component_binding.cpp:39` 起的历史 Child/Container、Owner.children 集合及序列化完整退役仍待整改；本次不添加集合或页面重放。
- 其他已接入页面中，`modules/adapter/native_full_language.inc:253` 的空读档等待、`native_encyclopedia_wait_language.inc:119` 的空内容等待等仍直接比较已安装 CALL Hook 的 D3C80 返回槽。这些同类来源识别问题待逐个按真实原生父帧审查整改，本次未改写其他页面的构造路径。

## 交付状态

源码修改已保存，通过根统一队列完成一次配置、一次增量编译与正式兼容热发布。Adapter 重新编译并链接；保留既有函数指针转换、extern 初始化、未使用项与缩进警告，无编译错误。提交后至所属批次结束没有继续修改本请求范围的源码。已读取请求 JSON、完整批次日志、正式发布 JSON 和旧件归档清单。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `63a3d33c885d4efeb0d92c47e1f02cc4` |
| 批次 ID | `9f603b7badc94cd5974fd23f9e5c13d2` |
| 请求结果 | `build/.compile-queue/results/63a3d33c885d4efeb0d92c47e1f02cc4.json`，`Success=true` |
| 完整批次日志 | `build/.compile-queue/batches/9f603b7badc94cd5974fd23f9e5c13d2.log` |
| 正式事务 | `c7055a3e3eb94eeaa867913bbdde73af`，2026-11-10 17:32:02（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/c7055a3e3eb94eeaa867913bbdde73af/publication-result.json`，`success=true`、运行时 `applied=true` |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/release.json` |
| 旧件归档 | `回收/20261110-173201-c7055a3e3eb94eeaa867913bbdde73af/package/`，两件旧文件先归档再替换，保留原相对路径，已只读确认存在 |
| 兼容交接 | Windows PID `364` 返回 `ReadyToPublish`，随后 Adapter 第18代 `Applied` |
| Adapter，正式件／构建件／Applied 一致 | `daa6f5ad248980c95120e73e55ce5cc44d522df5e3711de6c2fa73213b08141a` |
| 归档旧 Adapter | `84ae4c2b5090485bbb55c72ddf035445658fbc674db31767bb7bd2fd663d4203` |

源码修改、产物编译、正式文件发布及当前进程兼容交接均已完成。根 `urwcn_launcher.exe` 继续使用同一正式包，没有独立修复包或平行启动目录，无需重启。未启动、关闭、重启、模拟操作游戏，未运行测试或创建测试用例、断言；Applied 仅证明模块交接完成，快捷键行为和画面由用户验收。
