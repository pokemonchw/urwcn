# 百科关键词框中文输入与搜索

2026-11-11，Windows 3.89.1。对象为用户截图中的百科底部原生关键词框。原 PE 为 `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。下表使用 RVA；[原始反汇编](20261111-encyclopedia-chinese-search.asm) 使用首选基址 `00400000` 的 VA。

仅阅读磁盘 PE、原资源与源码，编译用于生成交付产物；没有启动、关闭、重启、操作或注入游戏，没有模拟输入、运行产物或测试，没有编写测试用例、测试脚本或断言。兼容热发布使用既有驻留事务和本项目已授权范围。

## 原因及原生输入所有权

既有 `native_name_input` 只为姓名和地图编辑器开启系统文本输入。百科通过 `3E589→10F5B0` 使用同一个 getst，但此前没有进入该作用域。此次复用已确认的文本事件、UTF-8 编辑、度量与绘制接口。

| 原生边界 | 静态依据与实现 |
| --- | --- |
| `3E582..3E58E` | EDX=30、ECX=原颜色调用 getst，返回为 `3E58E`。保留30字节容量、提交与取消；常用汉字最多10个，混输共用字节容量。 |
| `10F5C5`，既有 `52C0` | getst 已建立原帧；`[EBP+4]` 为真实调用者。只有 `3E58E` 启用百科输入 owner，不依据文字或当前屏幕猜测。 |
| `10F719→D3BF0`，既有 `52C3` | Before/After 均按上述真实 caller 确认 owner；After 可接管热发布前已经在等待的原生编辑器。没有新建输入控件、缓存或原生帧快照。 |
| `D1F81`，既有 `5401` | 原生已将完整 `SDL_TEXTINPUT.text` 复制到 `5F549B8`。沿原 `D2083` 返回 `-2`；getkey 不读未产生的 keysym。复用原姓名输入的 Ctrl/Alt StopTextInput 边界。 |
| `10F77F / 10F7FB` | 将真实完整标量追加到游戏自己的 `A49B9A8`，容量读取该存活帧的 `[EBP-B4]`；按完整 UTF-8 字符退格。普通按键、Enter、Escape及原 flags 下的 `*` 分支继续原流程。 |
| `10F65C / 10F7A7 / 10F8F5` | 复用姓名输入的完整字符串字形度量，仅替换原 `strlen*8+5`；擦除矩形、坐标、颜色和循环由 getst 管理。 |
| `10F6AC / 10F6C6` | 原生完整文字及下划线调用。已有 `10E5D2` 将 UTF-8 转成原显示传输编码；既有 Unicode scope 使英文 UI 中玩家中文仍可绘制。候选区域取真实原光标及 SDL 窗口变换，系统输入法自行显示候选窗。 |
| `10F924`，既有 `52C4` | 原 getst 真实完成时关闭百科文本输入并清理 owner，随后执行原返回流程。 |

`native_name_input::State` 仍是两个 u32；active=3 表示百科，其余既有值不变。没有新增状态节、宿主 ABI、驻留 DLL 或 Loader 修改。输入 owner 只在已确认 3.89.1 上新增。真实文本提交与语言快捷键都使用原 `-2`，所以 `native_full_language.inc` 的百科重建分支与既有姓名分支一致，明确让 `committed` 文本先进入原编辑流程，不把它当作语言唤醒而丢弃。

## 中文查询与原英文主题标识

`3E58E..3E5A1` 把完整 getst 内容复制到存活 `3E2A0` 帧的原查询串。该帧 `SUB ESP,74h` 后保存三个寄存器，查询起点为当时 `[ESP+10h]`，security cookie 位于 `[ESP+7Ch]`；两者相隔108字节，不据此推定源语言的数组声明。普通链接也在 `3E4CF..3E4E2` 复制进同一串。`3E639` 将此查询指针交给 `3E63D→3C8A0`，只有原存在性查询成功后才走 `3E404→3DD10`。失败仍走 `3E64E→3DCA0`，保留原查询与原无资料面板。

新增 `we_keyword_query=79F2`，只 Hook 已确认的 `3E63D` 完整五字节 CALL（`E8 5E E2 FF FF`）。Before 将实际 UTF-8 中文查询按既有 codec 编成相同词典编码，查既有中文标题／链接别名的逆向词典；命中后把原英文别名写入这个原生查询串。原 `A49B9A8` 始终保留玩家输入的 UTF-8；词典没有保存输入、布局、位置、像素或整页内容。

原 `3C8A0` 在 `3C8C6→D3DB0` 大写化，再对原 GAME.NFO 主题索引逐个完整比较；它不是子串、模糊或全文查询。中文沿同样完整主题名语义，不另造结果列表或业务选择。全部447个既有英文别名最长31字节，连 NUL 为32字节；它们本来就沿原链接路径进入同一查询串，且没有接近上述原生栈槽边界。不将 getst 的30字节输入上限误当成该查询字段的长度。

逆向词典在既有百科初始化中从 `src/linux/encyclopedia_links.inc`、`windows_encyclopedia_topics` 和 `catalog/zh-CN/cultures.tsv` 的正式中文词条构建：

| 玩家主题名 | 原标识 |
| --- | --- |
| 世界、世界背景 | `WORLD` |
| 不真实的世界 | `THE UNREAL WORLD` |
| 文化 | `CULTURE` |
| 狩猎 | `HUNTING` |
| 捕鱼 | `FISHING` |

同名既有词条按原主题表顺序采用首个；现有“饥饿”同时用于 `STARVATION` 与营养页别名 `HUNGER`，因此查询“饥饿”进入原表较早的 `STARVATION`；“营养”“营养与饥渴”“口渴”进入营养页。没有凭空添加同义词或二级搜索策略。英文查询及原链接动作继续使用原标识。

显示提示 `culture.ui.help_3` 改为“也可以输入中文或英文主题名进行搜索。”。词库是原生帮助段落构建的输入，行宽与换行仍由游戏和已接入度量管理。

## 高清目标、既有待整改项

输入文字沿原 `10E5A0` 完整调用及原字形叶子同步绘入游戏主软件面 `61BBB10`。既有主面构造 `1179B9/1179C2`、原上传纹理 `A1C2020` 与当前输出密度已接入 `native_targets`，详见[高清目标边界](20261019-native-hd-target-boundaries.md)。本次不新建低清输入表面、不放大低清文字，不保存绘制贡献供上传或呈现时重放。

以下既有路径仍待整改，本次不以编译或发布证明其合规：

- `modules/adapter/native_footer_component.cpp:88` 起由 Mod 计算署名宽度、横向位置与间隔，影响原生布局所有权。
- `modules/adapter/module.cpp:475` 起的 About 按钮 `center_x` 例外由 Mod 计算位置；历史注释不能代替当前约束。
- `modules/adapter/native_ui_scene.cpp:12` 起历史 `Child/Container` 集合及序列化尚未完整退役，影响原生 UI 所有权审查。
- `modules/adapter/windows_inventory.inc:6` 的 `native_text_limit` 及 `:118` 物品长度消费仍由 Mod 截断文字，影响原生文本裁剪所有权。

## 交付状态

源码、统一队列编译、正式文件发布及兼容热交接均完成。根 `build.ps1` 执行一次配置与一次增量编译，Adapter 重新编译并链接，Catalog 目标完成；只有既有函数指针转换、extern 初始化、未使用项与缩进警告，没有编译错误。批次期间没有修改请求范围源码；批次完成后的静态记录修订仅更正查询栈槽的注释与说明，不改变编译逻辑。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 468 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 实际回执 |
| --- | --- |
| 请求 | `a9cbe51338ad483bb314aafd4d8820d8` |
| 批次 | `1ed4da517083412aa1fba11a9370eced` |
| 结果 | `build/.compile-queue/results/a9cbe51338ad483bb314aafd4d8820d8.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 完整日志 | `build/.compile-queue/batches/1ed4da517083412aa1fba11a9370eced.log`，已读取 |
| 正式事务 | `72084f736f944ddba87ccfa28ffc73b7`，2026-11-11 11:57:50（Asia/Shanghai）完成 |
| 发布回执 | `build/mingw-x86/stage/72084f736f944ddba87ccfa28ffc73b7/publication-result.json`，`success=true`，已读取 |
| 当前进程 | 宿主 PID `3145474`，启动于2026-11-11 09:27:53；与前批已确认的 Windows PID `468` 为同一进程 |
| 驻留交接 | PID `468` 收到 `ReadyToPublish` 后提交，Catalog、Adapter 第7代均返回 `Applied` |
| 正式 Adapter／本批构建件／Applied SHA-256 | `706e49aa5bebbf39bbb7f52cbe5f2572eda39462dee65b72b773392fcc787ec3` |
| 正式 cultures.tsv／源码词库 SHA-256 | `8fceaa6511e79cb470ca85f57101c0877a0565d43c46b5834bd09afd8be36ee1` |
| 旧文件回收 | `回收/20261111-115748-72084f736f944ddba87ccfa28ffc73b7/package/`，按原相对路径保留 Adapter DLL、cultures.tsv、release.json |

正式更新 `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/cultures.tsv` 和 `package/release.json`。根 `urwcn_launcher.exe` 继续加载同一正式包，无需重启，没有平行修复包。`Applied` 只证明业务交接完成；没有自行运行输入法、搜索或画面测试，实际交互效果待用户验收。
