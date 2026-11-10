# “选择目标”提示框漏译

日期：2026-11-10（Asia/Shanghai）。用户截图显示 `CHOOSE TARGET`、鼠标／方向键说明及 `ESC.Exit`、`ENTER.Select` 未汉化。本次仅阅读截图、现有源码、磁盘原始 PE 及既有逐指令反汇编；没有启动、操作或模拟输入游戏，没有运行测试、创建测试用例或断言。兼容业务发布沿既有驻留事务，不注入新驻留库。

## 原因及静态依据

Windows 3.89.1 原始 PE SHA-256：`c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。逐指令依据位于 `build/analysis/windows-3891-native-full.asm:305859` 起。现有 `values.menu-echo.zh-CN.tsv` 的 `Select target` 只覆盖列表标题，未接入 `F7820` 的独立提示框。以下地址均为 RVA。

| 原生调用 | 已确认输入和行为 | 本次显示资源 |
| --- | --- | --- |
| `F7918 → 116270` | ECX/EDX 为原生位置，五个栈参数；标题为参数2。`F78C4` 按原模式bit0选择固定标题，`F78DB` 将 `CHOOSE TARGET` 地址压栈；另一路沿原调用者动作标题 | `target_help.title` → 选择目标 |
| `F7A88 → 114680` | 参数0为原 `ESC.Exit` | `target_help.exit` → ESC.退出 |
| `F7AA5 → 114680` | 参数0为原 `ENTER.Select`，原帮助分支实际存在时才调用 | `target_help.select` → ENTER.选择 |
| `F7B61 → 162300` | EDX为完整鼠标说明，ECX=1重置原分词表 | `target_help.mouse` → 用鼠标点击目标位置，或 |
| `F7B6D → 162300` | EDX为完整方向键说明，ECX=0追加同一原分词表 | `target_help.cursor` → 用图示方向键／数字键移动光标来选择目标。 |
| `F7BA9 → 10EB40` | 原生完整段落消费以上两条输入及原生宽高、颜色、outline | 沿用原调用，无另建段落布局 |

原 PE 的五段静态字符串位于 `1A9F64`、`1950C8`、`1A9F80`、`1AA030`、`1AA074`（标题、两按钮、两正文）。标题范围判断读取已确认 `F78DC` 的实际PUSH操作数，不按译文、位置或通用英文搜索匹配；旧3.89证据 `settlement-caller-string-refs.tsv` 中该操作数引用 `1A9F54`，本次不添加未确认地址映射。

## 修改与原生所有权

新增 `modules/adapter/windows_target_help.inc`，Hook ID使用独立 `18500..18504`，接入上表五个完整CALL。`module.cpp` 注册、分发同一组边界。`sdk/text_services.h` 新增 `target_help_text=F08`，`semantic.cpp` 用 `target_help.` 前缀查找 `catalog/zh-CN/main_menu.tsv` 五项资源。宿主 ABI、Adapter交接结构和原输入函数不变。

标题通过已有完整 `116270` 接口进入原生面板，`Scope::titled_panel` 使其 `116631` 宽度和 `11665C` 字形调用消费实际中文度量。按钮保留 `ESC.`／`ENTER.` 原键帽语法：`114680` 继续根据点号解析ASCII键名，`1149F9 → 10E5A0` 一次消费完整中文后缀。方向／数字键九宫格的原CALL、原值及实际输入动作保持。

两段说明通过已有双字节传输编码和 `native_paragraph_words` 逐完整字形词元接入 `162300`；原ECX重置／追加语义不变。`10EE68` 的折行宽度及 `10EF57` 的光标推进已有实际中文字宽扩展，`10EF87 → 10E5A0` 及其叶调用当次输出完整字形。不是把UTF-8直接交给ASCII字节路径。段落宽高、行距、标题居中、背景和缓存均由原生代码消费和管理。

文字翻译通过已有中性 `TextSource` 和原生parser输入绑定，不保存整页中文、屏幕坐标表、字形绘制序列或像素贡献；字体缓存不持有页面内容。字形在既有组件调用中按原生实际目标密度生成并即时绘入，本次没有新增SDL拦截、扫描、延后重放或高清目标路径。

已打开提示框复用 `native_hud_language.inc:394` 起的已确认重建：`F7DD9` 收到原生语言唤醒返回后保留原目标坐标和物品选择，重建父背景并回到 `F78B1`；`F7B49/F7BB6` 在完整帮助段绘制后回到原输入循环。此次新增文本CALL自然随同原生构建再次经过。没有增加输入等待、模拟按键或重跑目标选择业务；模块交接回执不代替用户画面验收。

## 既有待整改项

- `modules/adapter/native_footer_component.cpp:88` 起仍由Mod计算主菜单署名位置、宽度和间隔，影响原生布局所有权，待整改。本次提示框不使用该路径。
- `modules/adapter/native_ui_scene.cpp:12` 起保留历史Child/Container集合及其序列化，完全退役待整改。本次没有添加页面集合或绘制重放。
- `translations/build-message-catalog.ps1:17` 起仍以旧版绝对字面量地址读取PE，3.89.1地址适配待整改。本次不运行该生成器，直接补充已确认组件资源。

## 交付状态

源码及五条词库已完成。通过根统一队列执行一次配置和一次增量编译，Adapter、Catalog、Semantic三个目标均完成；仍有既有函数指针转换、extern初始化、成员初始化、未使用项、缩进及枚举分支警告，无编译错误。完整请求JSON、完整批次日志及正式发布结果均已读取。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,semantic,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求ID | `a5887327445741b4badeadfecc688b5e` |
| 批次ID | `e32fd31af72c4cea8d5662f738669d70` |
| 请求结果 | `build/.compile-queue/results/a5887327445741b4badeadfecc688b5e.json`，`Success=true` |
| 完整批次日志 | `build/.compile-queue/batches/e32fd31af72c4cea8d5662f738669d70.log` |
| 正式事务 | `817b6b45379749dfaa5783184b09708d`，2026-11-10 17:03:09（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/817b6b45379749dfaa5783184b09708d/publication-result.json`，`success=true`、`applied=true` |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/modules/uwcn_catalog.dll`、`package/modules/uwcn_semantic.dll`、`package/catalog/zh-CN/main_menu.tsv`、`package/release.json` |
| 旧件归档 | `回收/20261110-170307-817b6b45379749dfaa5783184b09708d/package/`，先归档再替换，保留原相对路径 |
| 当前进程 | 宿主PID `2974827`、Windows PID `364`，未重启 |
| 兼容交接 | `ReadyToPublish` 后 `Applied`；Catalog、Adapter为第11代，Semantic为第6代 |

| 文件 | SHA-256 |
| --- | --- |
| Adapter，正式件／构建件／Applied一致 | `6dca8970d719bead68513f76433f7a62926dd31468ab7b77d8d367e24d20f8b5` |
| Catalog，正式件／构建件／Applied一致 | `cd5ea4f63e239691176f6bf1e38a1b4c232a0c9c5f8182eb80aacefbfa8e6719` |
| Semantic，正式件／构建件／Applied一致 | `7c12021ae5e19b23f75f9fb7d95cc763224fb3c0ae658ecc4025fff42ede0ae8` |
| main_menu.tsv，源码／正式件一致 | `7af9fa17d8bccab0ac06d1a368fc96bc243c42a5de710e36efb2aee40f70f393` |

源码修改、产物编译、正式位置发布与当前进程兼容交接均已完成，根 `uwcn_launcher.exe` 使用同一正式包。未启动、关闭、重启、注入或模拟操作游戏，未运行测试、创建测试用例或断言。画面未自行验收，Applied仅证明模块交接。
