# Linux Shift+F10 切换后的旧文字残留

日期：2026-10-19。用户主菜单截图显示中英文重叠，版本与页脚仍为切换前语言。本次只静态读取源码、原生 ELF 和交付文件；编译仅生成交付产物，不启动游戏、不运行产物或测试、不模拟输入、不添加测试和断言。

## 根因和原实现整改

原 `src/linux/adapter.cpp:655` 的 `redraw_language()` 对主菜单直接调用 `LIST_Draw`，没有重建背景、`peli_info` 和 `small_info`。原生主菜单是无框列表，文字调用仅把新字绘到当前画布；旧字仍在，后续 `save_menubuf` 又把叠字存入游戏缓存。版本、出品、版权和作者段落不属于 `LIST_Draw`，也不会随此次调用更新。

同一函数原 `active_view` 分支只重画 About/Credits，没有替换其后方主菜单和 `SCREENSAVE`。关闭窗口时原 `restore_page` 会恢复切换前保存的像素。以上均是已确认生命周期缺口，不能因初版已发布而视为符合完整原生重建要求。本次源码已整改，编译和正式发布状态另列于末节。

## 静态证据

目标为本机 Steam `urw3-bin`，SHA256 `4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。以下是 Linux ELF RVA，依据本地 `objdump -d -C -M intel` 和已有 `build/analysis/linux-x86_64.asm`；本轮相关原始片段存放在 `build/analysis/20261019-linux-language-redraw.asm`，未执行游戏或产物。

| 原生边界 | 静态关系 |
| --- | --- |
| `15CC50..15CC71 → LIST_Reset(F4AF0)` | 第七参数为 0；`F4B33/F4B67` 将该值保存到 `List+84h`。 |
| `LIST_Draw(F5570)` 的 `F55B3..F55C4` | 上述样式为 0 时直接跳到 `F5678` 绘制行，跳过窗口背景分支。`F572F` 只调用 `showtext`。 |
| `UrW_Start` 的 `15CEEB..15CF44` | 读取原生 `winW/winH`，调用 `bestfitPic`、`SlaveDestroy`、`small_info`。背景参数和第七栈参数均由原指令构建。 |
| `15CF44` | 已有结束 Hook 让重绘片段返回，不进入之后文件检查、日志、音乐或 `MakeStartList`。原 `redraw.S` 保持 RBX 和片段 CALL 所需栈对齐。 |
| `peli_info(15CBE0)` | 调用 `small_info(15B6F0)`、原菜单 `winbox` 和 `UrW_Logo`，覆盖页脚和面板后再生成文字及版本。 |
| `LIST_Go` 的 `F865E/F866B`、`F86E0..F86FE` | 按原 `List+94h` 分支保存 `MENUBUFFER`，再读取 `List.Position`、原行 `+E0h` 标记并调用原选择高亮。刷新沿用这些字段，不重置选项或选择。 |
| `save_menubuf(13D5A0) → get_screen(4)` | `13BF7D..13BF91` 从 `screen` 复制到原 `MENUBUFFER`。原输入循环继续用 `restore_menubuf(140250)` 恢复新缓存。 |
| `15CFBE/15CFEF → save_page(13D590)` | UrW_Start 在 Credits/About 之前保存页面。`get_screen(1)` 的 `13BFC0..13BFD4` 写入 `SCREENSAVE`。 |
| `15CFC8/15CFF9 → restore_page(140170)` | 原窗口结束后恢复同一原生页面缓存；需在语言变化时更新缓存内容。 |
| `CreditsScreen(15A440)`、`AboutScreen(15A750)` | 原函数建立窗口和正文；只有已接入的 `15A61A` 尾跳/`15AB41` 输入等待在同步重绘期间跳过。两函数未重建或重置主菜单 List。 |

## 修改后的路径

`rebuild_main_menu()` 进入主菜单文本作用域，依次执行上述背景片段、`peli_info`、`LIST_Draw`、原生菜单缓存保存和当前选择高亮。主菜单语言切换及主菜单密度变化使用同一个重建函数，最后由原 `Flip` 呈现。

About/Credits 切换先执行这一主菜单重建，再调用原 `save_page` 替换 `SCREENSAVE`，然后执行当前原生窗口构建及 `Flip`。关闭窗口时消费的背景因此也使用新语言。该路径只在已确认的主菜单或这两个窗口作用域执行。

没有调用 `MakeStartList` 或 `LIST_Reset`，没有重放菜单业务或输入，没有新增页面坐标、行槽、文字快照、像素扫描或延迟绘字。字体度量和字形仍在原生组件文字调用中即时生成；游戏继续持有画布、菜单缓存、页面缓存及选择位置。

创建/文化/性别菜单的既有列表刷新顺序仅提取到 `redraw_list()`，本轮未扩展其后方缓存刷新。设置、姓名旧面板、载入页、先祖页、当前村庄、百科和告别页的待确认边界继续以 Linux profile 和各页记录为准，不宣称任意已打开页面均已实现完整切换。

Linux `src/linux/host.cpp` 只在正常启动时加载模块，没有运行中退役和重新加载协议；根 `build-queue.ps1` 明确拒绝 Linux Reload。此次仅更新正式文件，不宣称已加载新代码的运行时回执，也不关闭或重启用户游戏。

## 编译与正式交付

2026-10-19 13:09:32（Asia/Shanghai），通过统一根入口 `.toolchains/powershell/pwsh -NoProfile -File ./build.ps1 -Toolchain Linux -Module adapter -Publish` 完成一次配置、一次增量构建和正式发布。

- 请求：`d044f737c0fe4106be294062a4381d64`；批次：`92387b46b82e404784325996296c8c91`。
- 已读取对应 `build/.compile-queue/results/d044f737c0fe4106be294062a4381d64.json` 和完整 `build/.compile-queue/batches/92387b46b82e404784325996296c8c91.log`，`Success=true`、`PublishRequested=true`、`ReloadRequested=false`；本批次无编译警告。
- 发布事务：`01a9c57cdc464d03a02a569b6090fd02`；已读取 `build/linux-x86_64/stage/01a9c57cdc464d03a02a569b6090fd02/publication-result.json`，`success=true`，`runtime_requested=false`，无运行时回执。
- 正式更新 `package/modules/uwcn_adapter.dll`、Linux profile、`package/release.json`。旧三件先移入 `回收/20261019-130932-01a9c57cdc464d03a02a569b6090fd02/package/`，保留相对路径；发布脚本也归档并更新已有应用菜单链接。根启动入口仍为原 `uwcn_launcher`。
- 正式 Adapter SHA256：`fa07a8cba80cc18b66f4973908f77cca314ecf7dd5183aec5eb45da2c3d448f0`，与本次构建产物和发布清单一致；归档旧 Adapter 为 `04c838db3469080b708da0de89cd7b5f039b96b07fc7e69e884ddfebeecc1b5c`。
- 正式 Linux profile SHA256：`f9ba2b7cb0b6e0d0c280cad53d280378538625e131e405f0a46b6e18e84bbb23`，与源码 profile 和发布清单一致。

源码修改、产物编译和正式文件发布均已完成。Linux 当前进程不能原位换入该模块，下次正常启动从正式位置加载。没有运行或测试，视觉结果仍未验收。
