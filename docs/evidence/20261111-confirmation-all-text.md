# 退出、保存与通用确认框的完整文本接入

用户后续截图确认按钮空白。首批关于“当前 Menu 经 CFFB0 就能恢复按钮”的结论有误；完整原生按钮构建和提前返回状态修正见[后续修正记录](20261111-confirmation-buttons-fix.md)。下方首批回执保留为历史交接证据，不能当作按钮画面正确的证明。

日期：2026-11-11，Asia/Shanghai。对象为 Windows x86《不真实的世界》3.89.1 / Steam Build 26139145，原 PE SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。本文使用 RVA；提取清单、反汇编和反编译文件使用 VA，基址 `400000h`。

本轮只读分析磁盘 PE、用户截图及源码，不启动、关闭、重启或操作游戏，不注入、不模拟输入、不运行产物或测试，不创建测试用例、测试脚本或断言。兼容业务发布使用用户已授权的驻留事务。

## 提取范围及确切分支

[confirmation_AllText.java](confirmation_AllText.java) 在已有 Ghidra `inventory3891/urw.exe` 工程上以 `-readOnly -noanalysis` 提取两个通用确认入口及全部调用者，声明真实 fastcall 参数。27 个完整函数的 C 输出位于 `build/analysis/confirmation-20261111/all-text-ghidra.c`，退出和两个确认函数另集中于同目录 `quit-and-confirmation-ghidra.c`。巨型调试分派 `56FE30` 的完整 C 反编译超时，未宣称取得其完整 C；其全部 66 处确认分支通过原指令提取，并包含在完整调用清单中。没有因反编译超时省略这些文案。

[全部调用者](20261111-confirmation-callers.tsv) 共 109 处，来自 25 个原函数；[逐调用指令](20261111-confirmation-call-windows.asm) 与[输入清单](20261111-confirmation-inputs.tsv) 保存实际 ECX 来源。[完整指令文字引用](20261111-confirmation-source-references.tsv) 包含优化复制片段、内部键和二进制候选，不把它们当成独立可见文案。

| 原生输入 | 调用数 | 原输入语义 |
| --- | ---: | --- |
| `FB8A0` | 103 | Y/y 返回真，N 和 Esc 返回假 |
| `FBB10` | 6 | Y/y 和 Esc 返回真，N 和空格返回假 |

107 处调用直接使用原只读文本，共 99 条不同文案；`89E2A` 读取原任务分支内联复制的 `Cancel current task?` / `Take a break?`；`122112` 读取原 `sprintf("Try to treat %s wounds?", …)` 的完整生产者表达式。上述 101 条固定文案全部纳入新源词库，动态治疗确认复用已有 `122104` 格式及原 `PP_GEN:<npc>` 资源来源。

截图对应 `E7580(0)` 的退出流程，完整 C 明确区分：

| 条件与分支 | 原文与译文 |
| --- | --- |
| 首次确认，`E75C9` | `Are you sure?` → 确定吗？ |
| 当前角色可保存，`E7608` | `Save your character?` → 要保存角色吗？ |
| 拒绝保存后，`E7620` | `Do you wish to die?` → 你想死去吗？ |
| 原另一游戏状态，`E75EA` | `Do you really want to quit?` → 确定要退出游戏吗？ |
| 拒绝初次确认或原状态下的退出确认 | 原 `F6510` 提示后返回 0，继续游戏 |
| 保存／拒绝死亡／死亡／退出 | 原条件、返回值、`16DDD0` 保存与 `E73F0` 业务继续照常执行 |

菜单回显和“即将退出／保存角色并退出／取消退出”等原消息来源已有汉化，本轮补齐确认正文及两个按钮，并补齐回答后的 ` Yes` / ` No` 回显。另一个 `2CC30` 退出询问 `Are you sure you want to exit?` 同时覆盖。

同一组件的其他原分支包括采嫩叶／收获、进食／倒空容器、饮水／凿冰、陷阱／冰面／涉水／游泳、攀爬／继续攀爬、剥皮前分割、生火、卸下物品、归还、丢弃、睡眠、取消与中止任务；调试分支原有天气、任务、NPC 和物品询问也逐项处理。文案不参与业务条件判断。

## 实现与原生 UI 所有权

`native_generic_menu_language.inc` 的 `query_panel/query_second_panel` 同时在 `FB983/FBBE2 → 116270` 消费原 ESI 的完整来源。`FB942/FBBA1` 仅通过 `%s` 复制该来源，故不把其无语义栈副本重新归类为另一条静态文本；中文仅借给当次完整 Panel CALL，原栈缓冲和动态格式保持原值。

`windows_inventory.inc` 使用既有完整组件资源接口，在 `FB9F5/FBA0E → CFAF0` 接入普通确认的两个按钮；另在 `FBA71/FBAA6/FBCDE/FBD12 → 10E5A0` 接入两套确认的否定／肯定回显。新增 Hook `18360..18365` 只注册于已静态确认的 3.89.1；既有 Hook ID、模块 ABI 和保存格式不变。两套按钮均保留 `<Y>/<N>` 原高亮语法，实际动作和空 Esc／空格记录仍由原 `CF990` 构造。

首批曾在实际 `D1120` 等待返回处给旧 Y/N 行绑定来源，但查询真实行保存的是内部 `NOTEXTSPOT`，kind=100、空标题的 `CFFB0` 不绘制按钮。该错误刷新路径已按[后续修正记录](20261111-confirmation-buttons-fix.md)改为执行确认 owner 自己的完整 Panel、CF790、CFAF0 和空动作构建，结束于原输入之前；原业务不重进。

中文继续经过既有双字节显示编码、Panel 的完整文本度量、`CFC5D` 按钮行宽、`1146DD/1148E9/11498A` 按钮字形及推进、`D07FB/D0A49` 选择框度量和原完整文字绘制接口。原生拥有按钮背景、尺寸、布局、选择、命中、行距、光标及缓存生命周期；字形在已确认的主表面真实输出密度中即时生成。没有新增坐标表、行槽、页面中文快照、DisplayPlan、像素跟踪、绘制贡献或 Present 前叠字。

新 `literals.confirmation.zh-CN.tsv` 保存 101 条实际原文与译文；`values.confirmation.zh-CN.tsv` 保存两条带原空格的回答。`build-message-catalog.ps1` 增加读取 `literals*.zh-CN.tsv` 的文本身份入口，便于以后按 UTF-8 原文重建键，不依赖旧 PE 地址。本批仅同步这 103 条至 `catalog/zh-CN/messages.tsv`，没有对新 PE 执行基于旧地址的全量生成。

## 既有待整改项

| 文件与位置 | 影响 | 状态 |
| --- | --- | --- |
| `native_footer_component.cpp:88` 起 | Mod 计算主菜单署名间隔和 x | 待整改，本批不调用 |
| `module.cpp::enter_component_paint` 的 About 按钮中心例外，约第484行 | Mod 从 Panel 输入计算按钮中心 | 待整改，本批不扩展 |
| `native_ui_scene.cpp:12` 起 | 历史 Child/Container 集合及序列化尚未完整退役 | 待整改，本批不据其重绘确认页面 |
| `native_renderer_component_binding.cpp:39` 起 | Owner children 和历史物化仍保留 | 待整改，本批不新增 renderer 子项 |
| `windows_inventory.inc:6` 的 `native_text_limit` | 消费者侧自行截前缀、加点号 | 待整改，本批确认文案不调用 |

## 交付状态

源码、词库和静态证据已保存；根统一队列完成一次配置、一次增量编译及正式兼容热发布。Adapter 重新编译并链接，Catalog 目标完成、DLL 内容沿用。完整日志保留既有函数指针转换、extern 初始化、未使用项和缩进警告，无编译错误。提交后至批次结束没有修改该批源码。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 实际回执 |
| --- | --- |
| 请求 ID | `019483e4602a485ca1052c469ff29b99` |
| 批次 ID | `712c0c80e93b4a1a977901cca2fd5d54` |
| 请求结果 | `build/.compile-queue/results/019483e4602a485ca1052c469ff29b99.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 完整批次日志 | `build/.compile-queue/batches/712c0c80e93b4a1a977901cca2fd5d54.log`，已完整读取 |
| 正式事务 | `56367fc547fb4f68beac37a6bed25c76`，2026-11-11 13:01:21（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/56367fc547fb4f68beac37a6bed25c76/publication-result.json`，`success=true`、`applied=true`，已读取 |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧文件回收 | `回收/20261111-130119-56367fc547fb4f68beac37a6bed25c76/package/`，三件先归档后替换，保留原相对路径 |
| 当前进程身份 | 只读宿主进程表取得 PID `3275331`，既有 Proton Mono 解释器只读枚举取得 Windows PID `364` |
| 兼容交接 | PID `364` 返回 `ReadyToPublish` 后返回 Catalog、Adapter 第2代 `Applied` |

| 文件身份 | SHA-256 |
| --- | --- |
| 新 Adapter，正式件／构建件／清单／Applied 一致 | `7f0bca9acc9f8d0a179340a059dfa90487efe1578d50468babe2d8ec81d60d95` |
| 新 messages.tsv，源词库／正式件／清单一致 | `9514d61399b1b302e456e0b125f42c923ebf3863e40c1f449536c3d421a00c44` |
| 已回收旧 Adapter | `d8d7f180b550cf591e0fb60bcd7156a76d0069ffa4360c48fcff48f974bc90c0` |
| 已回收旧 messages.tsv | `7e4b6fbc7fb3314faf07c7e63f2b8277b447ad574912d66c3e9a9db347a72cae` |

源码修改、产物编译、正式文件发布与兼容交接均完成。根 `urwcn_launcher.exe` 继续消费同一正式包，没有平行修复目录。未启动或操作游戏、运行测试或自行验收画面；`Applied` 仅证明模块交接。
