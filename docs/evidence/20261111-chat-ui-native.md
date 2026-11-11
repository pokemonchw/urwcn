# 聊天界面的标题、NPC 称谓与聊天菜单漏译

日期：2026-11-11，Asia/Shanghai。用户截图显示顶部 `Chatting with Kaumolais sage`、NPC 面板的 `Kaumolais sage`，以及右侧 `Chat mode` 菜单仍为英文。本次对象为 Windows x86《不真实的世界》3.89.1 / Steam Build 26139145；原 PE SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。以下地址均为 RVA，反汇编文件保留 VA，基址 `400000h`。

仅阅读用户截图、磁盘 PE、Ghidra 反编译及源码，不启动或操作游戏，不注入、模拟输入、运行产物或测试，不写测试用例、测试脚本或断言。兼容业务交接使用用户已经授权的驻留发布事务。

## 原因和完整可见来源

此前 `native_conversation_language.inc` 已支持双方原生对话构造、UTF-8 姓名和语言重建，但名称消费者只做 Unicode 原文转换，没有消费已经存在的 NPC 中性语义来源。右侧 `Chat mode` 的真实 Menu 也没有绑定译文。已有原生构造和重建支持不能证明这些文字已经汉化。

完整函数提取由 [chat_ui_Decompile.java](chat_ui_Decompile.java) 在已有 3.89.1 Ghidra 工程中以 `-readOnly -noanalysis` 执行，声明真实 fastcall 参数后提取 `134150/134200/1342C0/146200/AD4F0/F8F80`；结果保留于本地 `build/analysis/chat-ui-3891-ghidra.c` 和忽略提交的同目录 C 文件。逐指令依据为 [人物面板和标题构造](20261111-chat-ui-panels.asm)、[聊天菜单构造和动作](20261111-chat-ui-menu.asm)、[标题带度量与绘制](20261111-chat-ui-heading.asm)。

| 原生边界 | 已确认语义与本次处理 |
| --- | --- |
| `1342E5 → 1127C0` | 原生对话背景，沿用既有完整 owner 生命周期 |
| `134174 → AD4F0` | 实际 NPC 索引、flags=4，已有语义观察器保留描述、文化与已知姓名的组合 |
| `13418E → 116270` | 原 NPC Panel 的完整名称参数，接入上述原表达式；`Kaumolais sage` 复用已有“考莫智者” |
| `134242 → 116270` | 玩家姓名，沿用既有 Unicode 显示，姓名不改写 |
| `1342F8 → AD4F0` | 顶部标题所用的同一命名函数和 flags=4 |
| `134307 → 10D0` | 原格式 `Chatting with %s`，新增 Hook `18800`，原 sprintf 完成后只绑定原格式与真实 NPC 实参的中性表达式 |
| `134312 → F8F80` | 完整顶部标题消费该表达式，显示“正在与考莫智者交谈”；原栈缓冲保持英文 |
| `F9006`、`F9019 → 10E5A0` | 复用既有完整字宽扩展及标题文字接口，原减半、中心坐标、标题带和描边由原生管理 |
| `146F80 → CF790` | `Chat mode`，kind=6，绑定“交谈方式” |
| `146FAA/146FB9/146FC8/146FD7/146FE6/146FF5 → CF990` | 原 G/A/C/H/D/T 六项，分别绑定“打招呼／问路／下达命令／请求帮助或结伴／交付物品／交易物品” |
| `14702B → CF990` | 原条件出现的 B 项“购买动物”；原动物可交易条件保持 |
| `147037/147046 → CF990` | 原空分隔行保留，`ESC.Exit` 只翻译后缀“退出” |
| `147050 → CFFB0`、`147055 → D1120` | 原完整菜单绘制、等待和动作分派，按键与动作值保持 |

`AD4F0` 的原描述、姓名是否已知、flags=4 的 `%s the %s`／`%s called %s` 组合继续由既有 `windows_message_values::npc_source` 产生完整语义；不是只对截图中的一个英文名字替换。NPC 正式词库的 `Kaumolais sage → 考莫智者` 已存在，本次不新增或猜测 NPC 字段。

## 实现、度量和当前窗口迁移

`windows_conversation_text.inc` 使用已有原生生产者关联的表达式，分别在 NPC Panel 与完整标题 CALL 绑定 `native_message_expression`。原文、业务数据、原 sprintf 和原返回值保持。中文只借用于当次完整组件调用，返回时按既有 token 释放；英文模式仍使用原姓名与既有 Unicode 原文显示。新增格式 Hook 只注册于静态确认的 3.89.1，既有 Hook 编号、驻留 ABI 和序列化格式不变。

`module.cpp::bind_chat_mode_menu` 读取同一真实 Menu 已接受的 header、原行数和 E8 行记录，按每条原记录的点号分出实际键帽与完整标签，给原 Menu 的中性文字资源绑定 `menu.title/menu.label`。原空分隔行来自确切的 `147037`。没有绘制序号、固定行槽或按动作猜文字的替代表；行数、条件、布局、命中和选择均归原生 Menu。

普通 `CFFB0` 在实际标题消费者绑定同一完整菜单资源。当前已打开的英文菜单在兼容交接后，`native_generic_menu_language::menu` 的确切 caller `14705A` 在既有完整重建前补绑定该原 Menu 的来源。此步骤必需：`native_menu_component::paint` 同步物化期间不再调用普通 `before_consume` 回调，单独修改普通回调不能更新已经打开的菜单。之后既有 `native_conversation_language::rebuild` 完整重建原背景、双方 Panel、肖像与已接受对话，再由原 `CFFB0/D0650/D1167` 消费当前菜单、选择和缓存。没有重新执行 `146200` 的 NPC 业务复制、随机对话生成、输入或交易动作。

文字经现有双字节显示编码、完整字体度量和实际输出密度字形接口提交到原生主表面；标题复用 `F9006` 的度量操作数扩展，Menu 选择框复用 `D07FB/D0A49`，后缀及键帽仍走原 `114680/10E5A0`。`native_targets::promote` 的实际主表面密度契约继续使用。没有新增低分辨率文字放大、SDL 像素扫描、绘制贡献记录、延后重放或 Present 前叠字。

新增资源位于 `translations/messages_embedded/values.chat-ui.zh-CN.tsv`，共10条，同步追加到正式消费的源词库 `catalog/zh-CN/messages.tsv`；保留已有词库顺序与内容，没有运行依赖旧 PE 文字地址的全量生成脚本。

## 既有待整改项

- `native_footer_component.cpp:88` 起的主菜单署名仍由 Mod 计算字宽、间隔和 x，影响原生布局所有权，待整改；本次聊天不调用该路径。
- `module.cpp` 的 `enter_component_paint` 中 About 按钮中心例外仍从面板输入计算中心，位置约在本次修改前第475行，影响该按钮的布局所有权，待整改；本次不扩展该例外。
- `native_ui_scene.cpp:12` 起的历史 Child/Container 集合及序列化仍保留，完整退役待整改；本次重建使用原完整 conversation/Menu，不遍历该集合绘制页面。
- `native_renderer_component_binding.cpp:39` 起 Owner 的 children 集合及 `paint` 历史组件物化仍保留，影响既有 renderer 缓存所有权，待整改；本次不新增 renderer 子项或走该集合重绘。

## 交付状态

源码和10条源词库修改已保存，通过根统一入口完成一次配置、一次增量编译及正式兼容热发布。Adapter 重新编译和链接，Catalog 目标完成且 DLL 沿用原内容；日志保留20条既有函数指针转换、extern 初始化、未使用项及缩进警告，无编译错误。提交后至所属批次完成，没有继续修改本批源码。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 468 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `9842bbb0e1d24f7da777d403de833d8f` |
| 批次 ID | `def00531ce004dfda542034759e2b9e9` |
| 编译结果 | `build/.compile-queue/results/9842bbb0e1d24f7da777d403de833d8f.json`，`Success=true`，`PublishRequested=true`，`ReloadRequested=true` |
| 完整批次日志 | `build/.compile-queue/batches/def00531ce004dfda542034759e2b9e9.log` |
| 正式事务 | `24d811f7471c49a586b33b6a5e872a3c`，2026-11-11 09:35:49（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/24d811f7471c49a586b33b6a5e872a3c/publication-result.json`，`success=true`，`applied=true` |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧件归档 | `回收/20261111-093548-24d811f7471c49a586b33b6a5e872a3c/package/`，三件先归档再替换，保留原相对路径 |
| 当前进程 | 只读进程表取得宿主 PID `3145474`，已有 Proton Mono 解释器只读枚举得到 Windows PID `468` |
| 兼容交接 | PID `468` 返回 `ReadyToPublish` 后返回 Catalog 第2代和 Adapter 第2代 `Applied` |

已完整读取请求 JSON、批次日志、正式发布 JSON，并读取正式文件、构建件、源词库和旧件的 SHA-256。

| 文件身份 | SHA-256 |
| --- | --- |
| Adapter，正式件／构建件／清单／Applied 一致 | `1a28446a9c072657223e7979074bc3b4b81a9f0aa9974b6b01f39ffbbee3f8bd` |
| messages.tsv，源词库／正式件／清单一致 | `c8b670d7fc349fd346ef323da6e8d3be09a67af78f56e8e87fe537549aec6d53` |
| 已归档旧 Adapter | `b255665b40c9efec848e07cca11b5771176f1932f20a81a7eaeed0342c46f17d` |

源码修改、产物编译、正式位置发布和当前进程兼容交接均完成。根 `uwcn_launcher.exe` 使用同一正式包，没有平行修复目录。没有启动、关闭、重启或操作游戏，没有运行测试或自行验收画面；`Applied` 证明模块交接完成，实际文字和画面由用户验收。
