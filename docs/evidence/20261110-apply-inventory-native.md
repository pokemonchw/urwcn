# “使用物品”页与地点地形漏译

日期：2026-11-10（Asia/Shanghai）。用户截图中标题 `What do you want to apply?`、提示动词 `apply` 和底部地点的 `Lake` 保留英文。本次仅阅读截图、源码、磁盘原始PE与既有逐指令反汇编；没有启动、操作或模拟输入游戏，没有运行测试、创建测试用例或断言。正式兼容业务发布使用已授权的驻留事务。

## 原因与静态依据

原始Windows 3.89.1 PE SHA-256为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。以下地址均为RVA，指令出处为 `build/analysis/windows-3891-native-full.asm`。

| 原生边界 | 静态依据与本次处理 |
| --- | --- |
| `58D2B/58D30`，`58D35 → 581F0` | EDX为 `apply`，ECX为 `What do you want to apply?`；原PE只读字符串在 `1960E8/1960F0`。原选择业务、物品掩码和操作值不改写 |
| `5565B → 116270` | 标题原值复制到实际临时缓冲后进入五参数Panel，文字参数2。此前 `windows_inventory.inc:98` 只接受wield标题，本次加入已确认的apply标题，译为“准备使用哪件物品？” |
| `5570A/5573A/5576B → 10E5A0` | 原提示前缀、实际动词及句号。此前动词只接受wield，本次补充apply资源“使用的物品”，组成“选择要使用的物品。” |
| `9052C → 8E4F0` | HUD完整地点上下文生产者，栈参数为原0。此前未进入已有地点表达式范围 |
| `8E61A → 10D0` | 原文化前缀 `%s `；已有identity词库，保留原文化选择 |
| `8E637 → 7520` | 原实际地形返回值；已有terrain词库包含 `Lake → 湖泊`，表达式观察器已覆盖此CALL |
| `8E68A..8E696` | 原分支确实追加 ` at ` 时才关联已有 `calendar.part` 的“，位于” |
| `8E6A3 → 8E420` | 已有地名表达式保留芬兰语原名、原命名地点分支及生成词源释义 |
| `8E6B9 → 10D0` | 原 `%s%s` 组合上述前缀与地点；已有calendar格式表达式保持完整原参数语义 |
| `90531..9054B` | 将 `8E4F0` 返回的同一字符串复制到原 `EBP-D8`；仅在这个已确认边界绑定对应中性表达式 |
| `90588 → 10E910` | 实际完整地点行，参数1为上述原缓冲；改为消费同一完整原生表达式 |

旧 `modules/semantic/world_hud_text.cpp:155` 的world_location分支翻译“at”和地名释义，却用 `display_name(source.substr(0,at))` 原样保留地形前缀，造成截图中的Lake漏译。Windows此次从真实生产者接走完整表达式，避免把文化和地形拼成的前缀再按英文文本猜拆；其他平台的旧world_location入口仍沿旧实现，本次未扩展未经本次确认的入口。

## 修改与原生所有权

`windows_inventory.inc` 的标题／动词范围加入apply，词条同时写入 `translations/messages_embedded/values.inventory.zh-CN.tsv` 和正式词库源码 `catalog/zh-CN/messages.tsv`，共两条。其他列表提示及分类沿原有完整组件入口；键帽与输入动作保持原值。

`windows_message_calendar.inc` 追加独立的 `hud_place_call` 标识，复用原Frame及其序列化，没有改变既有Hook ID、Frame字段、驻留ABI或状态格式。原文化、地形、关系词和地名的真实分支构建同一中性表达式，返回时与原复制目标关联。没有整页中文字段、布局坐标、像素贡献或待重放绘制记录。

`hud_native.inc` 的实际地点行通过 `module.cpp` 中的 `bind_hud_location` 复用已有表达式资源。在完整原 `10E910` 调用中消费，原位置、宽度、颜色、outline、折行、居中及背景缓存由原生组件管理。既有 `hud_center_fit`、`hud_center_line/last`、`hud_center_draw_line/last` 使完整双字节字形的度量、推进与当次绘制一致。字形继续在原生真实目标密度下即时绘入，未添加SDL扫描、像素跟踪、独立布局或提交前叠字。

兼容交接及语言切换复用既有原生父背景和inventory重建：`native_hud_language::rebuild` 调用原 `8FF70`，自然再次经过地点生产者和消费者；`native_parent_cache_language::inventory` 再次经过标题和动词调用。未新增输入等待、模拟按键或游戏业务重放。交接回执不代替画面验收。

## 既有待整改项

- `modules/adapter/native_footer_component.cpp:88` 起仍由Mod计算主菜单署名位置、宽度与间隔，影响原生布局所有权，待整改；本次不使用或扩展此路径。
- `modules/adapter/native_ui_scene.cpp:12` 起保留历史Child/Container集合及其序列化，完整退役待整改；本次不增加页面集合或文字重放。
- `translations/build-message-catalog.ps1:17` 起仍按旧版绝对字面量地址读取PE，3.89.1地址适配待整改。本次不运行该生成器，仅补入两条已确认的inventory资源，保留其他词库键。

## 交付状态

源码修改及两条词库已完成，通过根统一队列完成一次配置及一次增量编译，Adapter、Catalog目标均完成。保留既有函数指针转换、extern初始化、缩进与未使用项警告，无编译错误。提交后至本批次结束未继续修改本次源码；编译只生成交付产物，没有运行游戏或测试。完整请求JSON、完整批次日志与正式发布JSON均已读取。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求ID | `0a12da5c9b064472b8f9c4e26eb8401a` |
| 批次ID | `f82f0d6340a74eb7be99ecea909e7888` |
| 请求结果 | `build/.compile-queue/results/0a12da5c9b064472b8f9c4e26eb8401a.json`，`Success=true` |
| 完整批次日志 | `build/.compile-queue/batches/f82f0d6340a74eb7be99ecea909e7888.log` |
| 正式事务 | `281c084c20704e9eb9c35012a942162f`，2026-11-10 17:09:04（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/281c084c20704e9eb9c35012a942162f/publication-result.json`，`success=true`，运行时 `applied=true` |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json`；Catalog DLL内容未变，显式参与本次交接 |
| 旧件归档 | `回收/20261110-170902-281c084c20704e9eb9c35012a942162f/package/`，先归档再替换，保留原相对路径 |
| 当前进程 | 宿主PID `2974827`、Windows PID `364`，未重启 |
| 兼容交接 | `ReadyToPublish` 后 `Applied`，Catalog、Adapter均为第12代 |

| 文件 | SHA-256 |
| --- | --- |
| Adapter，正式件／构建件／Applied一致 | `a270b2b9ce0d32d4c6df236e3df1753765601287b79015d14f249c2ce476fed2` |
| Catalog，正式件／Applied一致 | `cd5ea4f63e239691176f6bf1e38a1b4c232a0c9c5f8182eb80aacefbfa8e6719` |
| messages.tsv，源码／正式件一致 | `7179534f677f7fb4fd89e6619e6b42f370ad1b043aa630d22332d91ea641b5b6` |

源码修改、产物编译、正式位置发布及当前进程兼容交接均完成，根 `uwcn_launcher.exe` 使用同一正式包。没有独立修复包或平行启动目录，没有启动、关闭、重启、注入或模拟操作游戏，没有运行测试或自行验收画面。Applied仅证明模块交接完成。
