# 地图加载进度提示漏译

日期：2026-11-11（Asia/Shanghai）。用户两张截图中，地图加载窗口仍显示 `LOADING MAP ...`。这属于 `FA7B0` 的地图进度组件，此前启动资源进度 `123DF0`、读档进度 `17E4C0` 的汉化没有涵盖它。

本次仅阅读用户截图、磁盘 PE、只读 Ghidra 反编译、反汇编及源码；不启动、关闭或操作游戏，不注入、模拟输入、运行产物或测试，不创建测试用例、测试脚本或断言。兼容业务热交接使用用户已授权的驻留发布事务。

## 静态证据

对象为 Windows x86《不真实的世界》3.89.1 / Steam Build `26139145`。原 PE 为 `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。正文为 RVA，附带[原生指令](20261111-map-loading-native.asm)为 VA，首选基址 `400000h`。

磁盘字符串 `1AA280` 的完整内容为 `LOADING MAP ... `，尾部含一个空格；直接指针引用只有 `FA81F`。只读[提取脚本](map_loading_Decompile.java)在既有 `inventory3891/urw.exe` 工程中以 `-readOnly -noanalysis` 提取完整 `FA7B0` 和 `10E5A0`，声明文字消费者的实际 fastcall 签名，并枚举进度函数的调用者。输出在 `build/analysis/map-loading-20261111/map-loading-ghidra.c`，同目录保存 console 和 Ghidra 日志；提取进程退出码0，数据库修改已丢弃，游戏 PE 未改写。

| 原生边界 | 静态语义与处理 |
| --- | --- |
| `FA7B0..FA7BA` | 原条件变量 `27D2F0` 控制整段进度绘制；原判断保持 |
| `FA7E9 → 111070` | 游戏绘制自己的窗口背景及边框；不改动其参数 |
| `FA80A` | `SDL_MapRGB` 从原主面格式生成原 `AB/AB/AB` 颜色；保持 |
| `FA823 → 10E5A0` | ECX/EDX 为原位置，栈依次为完整 text、color、outline=1；随后原调用者清栈12字节 |
| `FA83B → 10D170` | 原 ECX 进度保存在 ESI 后传给原进度条；保持数值和绘制 |
| `FA853 → 10B770` | 原窗口区域上传与显示；不新增 Hook 或延后叠字 |

`16E470` 中14处调用同一 `FA7B0`，原调用返回点与进度值保持。没有为语言刷新重入地图加载业务，译文由下一次正常进度绘制消费；原进度函数内没有新增输入轮询。

## 源码与原生 UI 所有权

`sdk/text_services.h` 新增 `world_map_loading=10109h`，既有标识、共享结构、Host ABI 和保存格式保持。Semantic 的资源映射及初始化词汇表登记 `world.map_loading`，主词库新增“正在载入地图……”。Adapter 新增 Hook `A10h`，仅在具有本轮完整静态证据的 Windows 3.89.1 注册 `FA823` 的完整文字调用。

原英文常量、地图数据与进度数值不改写。完整译文只借给当次原生文字参数，在该调用 After 释放；没有新增坐标、行槽、窗口布局、像素跟踪、文字贡献序列或 Present 重放。原生位置、颜色、描边、背景、局部上传和缓存生命周期均继续由游戏管理。

`10E5A0` 的完整函数静态确认复制缓冲为300字节，原生会重映射 `C4/E4/F6`；既有 `modules/layout/layout.cpp` 的双字节传输编码避开这三个值。本条译文为8个非 ASCII 字符，含终止符17字节，不新增裁剪或截断逻辑。

原生五个完整串调用 `10E67C/10E68D/10E69E/10E6AF/10E6D8 → 10DDB0` 在同次文字调用中分别提交原描边与前景。已有 `Scope::text` 接入这些消费者以及 `10E700` 的光标推进：宽度来自完整中文字形的逻辑度量，不使用编码字节数乘8。没有将 UTF-8 直接交给原 ASCII 字形索引路径。

`module.cpp::render_request` 使用原主面 `61BBB10` 的实际表面与已确认的原生逻辑域，由既有 Render 按真实输出密度即时光栅化并写入原面。原 `10B770` 随后消费已绘像素；不在上传时重画文本。已确认目标、局部上传与裁剪边界沿用[原生高清目标记录](20261019-native-hd-target-boundaries.md)，其未解析别名及范围限制仍然有效；本次不增加新的目标扩展。

本次没有新增回退、兜底、猜测性字段、保护分支、输入动作或测试。

## 读到的既有待整改项

| 文件与位置 | 影响 | 本批状态 |
| --- | --- | --- |
| `modules/adapter/module.cpp::enter_component_paint` 的 About 按钮中心例外 | Mod 仍从 Panel 输入计算按钮中心，涉及原生布局所有权 | 既有待整改；本次地图提示不使用此例外 |
| `modules/adapter/native_component_binding.cpp` 的历史 `fields`／组件集合、`native_ui_scene.cpp` 历史 Child／Container 集合 | 历史来源与布局输入保留及序列化仍需继续审查退役，不能以已发布认定全部页面重建符合要求 | 既有待整改；本次只借用一个完整文字调用，不新增页面重建 |
| `modules/adapter/windows_hud_map_text.inc::lend_hud_command` 调用 `native_text_limit`，及 `windows_inventory.inc` 的实现 | Mod 消费者侧执行前缀截取和加点号，影响原生截断所有权 | 既有待整改；本次地图提示不调用 |

更多既有问题沿用[读档进度记录](20261111-load-character-progress-native.md)与[确认框记录](20261111-confirmation-all-text.md)。本批编译、发布及模块交接不会消除这些待整改项。

## 交付状态

源码、词库、构建适配及静态证据已保存。根统一入口完成一次配置和一次增量构建，生成 Adapter、Catalog、Semantic 三个目标；SDK 头文件变化引起的依赖源文件由既有构建图重新编译。完整日志保留既有函数指针转换、extern 初始化、缺失成员初始化、缩进、未使用项及 Semantic 分类分派的枚举警告，没有编译错误。提交后至批次完成没有修改所属源码。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,semantic,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 实际回执 |
| --- | --- |
| 请求 ID | `c2859f85d5b543dba566328f706a960d` |
| 批次 ID | `d2fd0757e1bd430b95ef1b0af44a5170` |
| 请求结果 | `build/.compile-queue/results/c2859f85d5b543dba566328f706a960d.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true`，已读取 |
| 完整批次日志 | `build/.compile-queue/batches/d2fd0757e1bd430b95ef1b0af44a5170.log`，已完整读取 |
| 正式事务 | `44f76f8afae1485d89813831f052eb60`，2026-11-11 13:23:44（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/44f76f8afae1485d89813831f052eb60/publication-result.json`，`success=true`、当前目标 `applied=true`，已读取 |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`uwcn_catalog.dll`、`uwcn_semantic.dll`，`package/catalog/zh-CN/main_menu.tsv`、新版构建适配及 `package/release.json` |
| 旧件回收 | `回收/20261111-132342-44f76f8afae1485d89813831f052eb60/package/`，六件先归档后替换，保留原相对路径；六件实际存在 |
| 进程身份 | 只读宿主进程表为原 PID `3275331 urw.exe`；既有 Proton Mono 解释器只读枚举为 Windows PID `364 urw` |
| 兼容交接 | `ReadyToPublish` 后返回 Catalog 第5代、Semantic 第4代、Adapter 第6代 `Applied` |

| 正式文件 | SHA-256 |
| --- | --- |
| `modules/uwcn_adapter.dll` | `13d35a89f33c79353016faefc1320df28151e791787401176d135f334f0d5f89` |
| `modules/uwcn_catalog.dll` | `800163383c47b5be9d3e33b36ba067b264dd89d9d169abf59f035bb4837b9bb2` |
| `modules/uwcn_semantic.dll` | `df9e91dd0d77d88f01a856c20b49a6b893fcfc05e288173ca146f11b50ce7517` |
| `catalog/zh-CN/main_menu.tsv` | `cd950ea9c051e56d4c55cf8ef23ff762c9b59c57c6339482804961752a6cf064` |
| `profiles/urw-3.89.1-steam-26139145.json` | `51afdfda839305ea1d2ab6adc81b20485f33fb738aae0fb02fde7d744e18f371` |

只读核对三份正式库与构建输出一致，正式词库和新版构建适配与源码一致，发布清单全部16项身份与磁盘一致。根 `uwcn_launcher.exe` 继续使用同一正式包，启动器及驻留库不需要替换，没有平行运行副本。

源码修改、产物编译、正式文件发布和当前进程兼容交接均完成。无需重启，译文由下一次正常地图加载进度绘制消费；没有强制重入加载业务。`Applied` 只证明模块交接，实际画面待用户验收，本轮未自行测试。
