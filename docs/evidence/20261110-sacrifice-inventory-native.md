# 献祭物品选择页漏译

日期：2026-11-10（Asia/Shanghai）。用户两张截图中的标题 `What do you want to sacrifice?` 与底部操作提示的 `sacrifice` 未汉化。本次只阅读截图、源码、磁盘原始 PE 和既有反汇编；未启动或操作游戏、模拟输入、运行测试、创建测试用例或断言。兼容业务热发布沿用已授权的驻留事务。

## 原因与静态依据

原 Windows 3.89.1 PE 为 `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。直接读取只读节确认原文。以下均为 RVA，指令来源为 `build/analysis/windows-3891-native-full.asm`，摘录见同目录 `20261110-sacrifice-inventory-native.asm`。

| 原生边界 | 已确认语义 |
| --- | --- |
| `E8D40` | 原献祭业务入口 |
| `E8DAA / E8DAF` | 依次压入 `1A8A40` 的 `sacrifice` 与 `1A8A4C` 的完整原标题 |
| `E8DD0 → 55060` | 直接调用共用原生物品选择器，七个原栈参数由原调用者清理 |
| `55616..55621` | 原标题复制到原生临时缓冲 |
| `5565B → 116270` | 该缓冲作为参数2进入原生 Panel，使用已有 `inventory.ui` 绑定 |
| `5570A / 5573A / 5576B → 10E5A0` | 原提示前缀、实际操作动词、句号，使用已有完整原生文字调用及光标推进 |
| `E8DFE / E8E03 → 162D40` | 原取消分支仍将同一英文 `sacrifice` 用作原动作参数，不改写 |

此前 `modules/adapter/windows_inventory.inc::bind_text` 的标题与动词范围只包含已确认的 wield、apply，且 `inventory.ui` / `inventory.verb` 缺少献祭两条资源。其他域已有 `action: sacrifice → 献祭`，但该域不是此界面的完整物品提示语义，不能替代本次绑定。

## 修改与原生所有权

`windows_inventory.inc` 仅将已确认的 sacrifice 标题和动词加入既有消费者范围，不增加 Hook、不改变 Hook ID、状态序列化或驻留 ABI。两条资源同步补入 `translations/messages_embedded/values.inventory.zh-CN.tsv` 和词库源码 `catalog/zh-CN/messages.tsv`：

| 资源 | 中文 |
| --- | --- |
| `inventory.ui: What do you want to sacrifice?` | 准备献祭哪件物品？ |
| `inventory.verb: sacrifice` | 献祭的物品 |

底部原三次文字调用依次生成“选择要”“献祭的物品”“。”，保留同一原生文本调用的完整语义。原业务入口、物品掩码、动作值、物品数据和数量不变。

标题和提示复用已有 `native_component_binding` 的 Panel / TextBlock 消费边界，中文通过现有原生双字节编码与完整字形度量接口进入原生居中及光标推进。最终字形在现有组件调用中，按当次原生目标的真实输出密度即时提交；本次没有新增目标、表面扫描、像素跟踪、固定坐标、行槽、整页中文字段或延后文字重放。

既有 `native_parent_cache_language::inventory` 使用存活原生父帧的七个实际参数重建同一 `55060`；常规构建、语言切换及兼容交接后的重建均经过同一标题和动词消费者。本次不增加等待输入或业务动作重放。

## 既有待整改项

- `modules/adapter/native_footer_component.cpp:88` 起仍由 Mod 计算主菜单署名位置、宽度和间隔，影响原生布局所有权，待整改；本次不调用或扩展。
- `modules/adapter/native_ui_scene.cpp:12` 起保留历史 Child / Container 集合及其序列化，完整退役待整改；本次不增加页面集合或遍历回放文本。
- `translations/build-message-catalog.ps1:17` 起仍按旧版绝对字面量地址读取 PE，3.89.1 地址适配待整改；本次不运行该生成器，只同步两条本轮已确认资源键，保留现有其他键。

## 交付状态

源码和两条词库修改已保存，通过根统一队列完成一次配置、一次增量编译及正式兼容热发布。Adapter 重新编译并链接，Catalog 目标完成、DLL 内容未变。保留既有函数指针转换、extern 初始化、缩进与未使用项警告，无编译错误。提交后至本批次完成未继续修改本请求范围的源码。完整请求 JSON、完整批次日志和正式发布 JSON 均已读取。工作区中其他任务的既有修改保留。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `f0a419536709458bbf91960751bec912` |
| 批次 ID | `ea5cf79f9627402895ca5661575a038d` |
| 请求结果 | `build/.compile-queue/results/f0a419536709458bbf91960751bec912.json`，`Success=true` |
| 完整批次日志 | `build/.compile-queue/batches/ea5cf79f9627402895ca5661575a038d.log` |
| 正式事务 | `26921c8a364e424dbb51466c94a66d45`，2026-11-10 17:31:45（Asia/Shanghai）完成 |
| 正式发布结果 | `build/mingw-x86/stage/26921c8a364e424dbb51466c94a66d45/publication-result.json`，`success=true`、运行时 `applied=true` |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧件归档 | `回收/20261110-173143-26921c8a364e424dbb51466c94a66d45/package/`，三件旧文件先移入归档再替换，保留原相对路径，已只读确认存在 |
| 当前进程交接 | Windows PID `364` 返回 `ReadyToPublish`，随后 Catalog 第16代／Adapter 第17代 `Applied` |

| 文件 | SHA-256 |
| --- | --- |
| Adapter，正式件／构建件／Applied 一致 | `84ae4c2b5090485bbb55c72ddf035445658fbc674db31767bb7bd2fd663d4203` |
| Catalog DLL，Applied | `cd5ea4f63e239691176f6bf1e38a1b4c232a0c9c5f8182eb80aacefbfa8e6719` |
| messages.tsv，源码／正式件一致 | `1451e10876db3faea328c7ebefbd4151700b4b000047f80f75a4fb4550c4708a` |

源码修改、产物编译、正式文件发布及当前进程兼容交接均已完成，根 `urwcn_launcher.exe` 继续使用同一正式包，无需重启。没有平行运行副本，未启动、关闭、重启或模拟操作游戏，未运行测试、创建测试用例或断言。Applied 仅证明模块交接，画面由用户验收。
