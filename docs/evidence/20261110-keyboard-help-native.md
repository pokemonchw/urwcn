# 可滚动按键帮助页完整汉化

日期：2026-11-10。用户截图对应 Windows 3.89.1 的按键帮助页。仅阅读用户截图、磁盘 PE 和源码，完成静态分析；没有启动、关闭、重启、注入或模拟操作游戏，没有运行测试、创建测试用例或断言。兼容业务更新使用既有正式热发布事务。

后续用户截图确认本版正文被异常拉伸。下文高清接入记录遗漏了 `1052AC` 的实际纹理分配：该处只有密度登记，仍分配800×1300，不能视为正确接入。错误位置、影响、源码修正及后续交付单独记录于[正文纹理尺寸修正](20261110-keyboard-help-density-fix.md)；下列旧批次 Applied 仅是模块交接历史。

再后续用户报告 Shift+F10 闪退，静态复审确认 `10539B → 103AA2` 重建续接缺少16字节原生待清理参数空间。该项实现缺陷和修正详见[帮助页语言切换栈修正](20261110-keyboard-help-language-stack-fix.md)，下文直接重入 `103AA2` 的旧描述不能作为正确栈契约。

## 原生入口与完整范围

本机原 `urw.exe` SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。以下地址均为 RVA；本地逐指令摘录为 `build/analysis/keyboard-help-3891.asm`，由已保存的完整反汇编提取，未执行游戏。

`103A30..10551D` 是完整帮助页。`103AB5` 创建底栏表面，`103BF0` 创建正文表面；二者由 `SDL_CreateSoftwareRenderer` 当次绘制后上传原生纹理。底栏纹理 owner 为 `61BB644`；正文缓存为 `A44B798`，滚动位置为 `A44B794`，正文的原生缓存判据 `1EBCB0` 是当前传统移动模式值。`105334` 创建可滚动视口，`105354..10538C` 按原矩形提交，`105396 → D3BF0` 等待输入；`1053B3..105486` 原代码继续处理滚轮、方向键、翻页键、空格及滚动上限。

源码 `windows_keyboard_help.inc::text_calls` 接入84个真实文本 CALL，覆盖91项语义资源，包含两种移动模式及全部八章：移动、观察周围、拾取与搬运物品、物品栏与物品使用、互动与制作、战斗、信息与角色资料、帮助与游戏选项。顶部介绍、三段移动说明、地图缩放、两处快捷键引导、末尾寄语和底栏滚动/退出提示均已纳入。表中只有调用点、原生目标、语义键及输入语法，没有屏幕位置、行槽或布局快照。

`164720` 构建英文动作说明，`165340` 将真实键名与英文说明合成；这些业务和共享英文缓冲不变。中文只借给相应完整显示 CALL。`114D20` 的点号、双点号、方括号和双键帽语法分别保留；`114D81..114DA5` 明确处理句点键的 `..`，不能截成单个点号。两个键帽之间的原 ` or ` 单独译成“或”。字母大小写、CTRL/ALT、方向图标和所有原动作标识保持原值。

动作标签中的踢击、拳击、交换武器等按 `164720` 的压缩分支表静态确认：`30 → 164F5D` 为 Kick，`39 → 164F77` 为 Punch，`58 → 164F2F` 为 Exchange wielded weapons。没有按截图外观推测动作。

## 原生度量、标题及高清目标

`162300 → 10EFD0` 继续管理介绍和长说明的分词、折行、行距与返回高度；原调用随后消费该高度。中文沿现有双字节传输编码与逐字符词元接口进入原生解析。`windows_renderer_text.inc` 已确认的 `10F409/10F4FE/10F551` 扩展段落度量；`11511D` 扩展标记文字游标，`10E260 → 10DE90` 的五处叶调用即时绘制真实字形。ASCII 键帽未进入整串字体作用域，继续使用原位图及8单位宽度，不挤压键帽或改变按键语义。

前四章原来将空面板与固定英文标题分别绘制。中文模式在同一真实面板 CALL 内，将该面板当次的 renderer、x、y、width 输入交给游戏已经用于后四章的完整 `115AD0` mode 5，再省去原固定英文标题 CALL；`115B59` 使用现有中文宽度扩展，原生代码完成居中、蓝条和字形提交。没有复制固定坐标或自行计算居中位置。英文沿原调用路径。

`native_targets.cpp` 仅在已确认的两个表面构造返回点 `103ABB/103BF6`，按真实主画布密度扩展它们的光栅域；底栏、正文上传和 `105340` 视口纹理接入同一密度协议。表面创建至对应上传之间没有输入等待，临时 `help_upload_scale` 只传递这次真实构造的密度，不含像素、文本或位置，不作为重放依据。字形按对应软件 renderer 的实际密度生成，当次提交后由游戏缓存已有像素。

底栏原代码直接读表面宽高。`103B05` 的完整原生面板接口保留其实际内缩，将扩展后的光栅尺寸还原为真实构造的逻辑域；`103B97/103BB4` 原 owner 写入点消费相同逻辑宽高。像素上传仍读取真实物理 pitch 和像素地址，没有扫描、比较或记录表面内容。

## 语言切换、卸载与当前页更新

新增 `View::keyboard_help` 复用既有两个整数的语言请求状态，没有增加 Adapter 保存节、修改 HDA8 或驻留 ABI。普通打开页面时，`103BBF` 在语言修订待消费时退役真实旧正文缓存并使原判据失效，游戏随后重建。`103AA2..1052D0` 的同步 parser owner 防止将帮助页临时词元表登记成独立页面资源。

在已经打开的帮助页，`10539B` 接收原输入函数返回；若语言修订待消费，按 `1054BA..1054EC` 的实际释放协议退役视口、可选正文 renderer 和可选正文表面，并调用完整 `113400` 清理底栏。滚动位置写回原游戏同一 owner；恢复 `103A43..103A6A` 的原颜色输入及原速度值后，回到 `103AA2`，由同一原生帧重做完整底栏、正文和视口。`1052E2` 随后再次保存原速度值，原退出流程仍负责恢复。没有递归输入循环、页面字段快照、另一套布局或模拟按键。

## 静态审查发现的既有待整改项

- `modules/adapter/native_footer_component.cpp:88` 的 `paint` 仍由 Mod 计算署名列宽、x、gap、图文间隔并提交独立署名排版，影响主菜单译者署名，仍待整改。本页不调用它，也不把现有编译或发布视为该设计合规的证明。
- `modules/adapter/native_ui_scene.cpp:12` 的 `Child/Container` 及其序列化仍保存历史组件注册结构；当前 `language_changed` 已明确只推进修订，未再遍历该不完整集合重画页面。历史结构的彻底退役仍待处理。本页不向该结构添加帮助页组件或文字序列，全部刷新来自上述完整原生构建段。
- 该接入面向截图对应的 Windows 原生界面；本轮没有移植 Linux 按键帮助，不将 Windows 发布外推为 Linux 已完成。

## 交付状态

首批请求 `7f6f094f6d7e4cf1a3b9c12c6132ed2d`、批次 `db95fdc03f974afbb3957452fff7dfd0` 已完成一次配置和增量编译，Adapter、Catalog、Semantic 产物均生成。正式事务 `8ba32fa1280a43fa9486778af3868c4c` 已将旧件归档至 `回收/20261110-152800-8ba32fa1280a43fa9486778af3868c4c/` 并替换正式文件，但 COMMIT 的 Adapter 初始化被拒绝，`applied=false`、批次 `Success=false`，不能称为热交接完成。

只读日志确认失败在 `native text hook installation; status=1`。静态复审发现本页原先使用 `B800/B900` Hook ID，和 `windows_message_formats.inc:7` 从 `B600` 开始的900余条记录重叠；驻留 `hook_host.cpp:125` 会拒绝同一 ID 的不同 spec，且在任何新指令写入前完成全部验证。已将本页移入独立的 `18000/18100/18110` ID 区间；不是更改游戏地址、放宽指纹验证或加入兜底。驻留 `host.cpp:179` 对已退役模块保留原保存状态，支持以既有事务继续提交修正版，无需用户重启。

修正版经同一根队列完成，未绕过队列另行编译或运行产物：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,semantic,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 最终回执 |
| --- | --- |
| 请求 ID | `c2b0fc611cb64d8bbfe0d3cd5d003ef1` |
| 批次 ID | `80480fce8aec493893353af35000c4fd` |
| 队列结果 | `results/c2b0fc611cb64d8bbfe0d3cd5d003ef1.json`：`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 批次日志 | `batches/80480fce8aec493893353af35000c4fd.log`：一次配置、一次增量构建，三个目标均完成 |
| 正式事务 | `b4875c2e08204ee7b7405fb76c68363b`，2026-11-10 15:29:18（Asia/Shanghai）完成 |
| 正式结果 | `build/mingw-x86/stage/b4875c2e08204ee7b7405fb76c68363b/publication-result.json`：`success=true`、`applied=true` |
| 修正版替换文件 | `package/modules/urwcn_adapter.dll`、`package/release.json` |
| 修正版旧件归档 | `回收/20261110-152917-b4875c2e08204ee7b7405fb76c68363b/package/`，保留原相对路径 |
| 全部本轮正式更新 | Adapter、Catalog、Semantic 三个业务库、`package/catalog/zh-CN/main_menu.tsv` 及发布清单；首批已发布的词库和两库在修正版事务重新加载 |
| 当前进程 | 宿主 PID `2944694`，Windows PID `364`；已有 Proton Mono 解释器只读枚举取得，无新控制二进制 |
| 当前交接 | `ReadyToPublish` 后 `Applied`，Catalog、Semantic、Adapter 均为第3代 |

正式文件、构建件、发布清单和 Applied 回执使用相同身份：

| 正式文件 | SHA-256 |
| --- | --- |
| `package/modules/urwcn_adapter.dll` | `d08b987f054114903cb19de30f8a593e8140aae393345af47cdddd196ca4a7d0` |
| `package/modules/urwcn_catalog.dll` | `9313e505e5046220745f3c3aa47e3095e75dbc05a3aa5dfec6c9766b67217869` |
| `package/modules/urwcn_semantic.dll` | `9ba9ba515c98078f6b4107c1fede213c68e5b5301b74c80417207c100da9081f` |
| `package/catalog/zh-CN/main_menu.tsv` | `8d5fdc0e46c3fb8b93494acb91a2a7349aebb1cf1e86d0abe0b1810c727e87c4` |

已读取两批请求结果、完整批次日志、两次正式发布结果、归档文件和最终身份；末条游戏日志为 `Compatible module transaction applied.`。既有函数指针转换、extern 初始化、未使用参数/函数及缩进警告仍存在，没有放宽编译规则。源码修改、产物编译、正式文件发布与当前进程兼容交接均已完成，根 `urwcn_launcher.exe` 正常入口消费同一正式包，无平行运行副本。未启动、关闭、重启或模拟操作游戏；未运行测试、创建测试脚本或断言。Applied 仅证明模块交接，不代表画面验收。
