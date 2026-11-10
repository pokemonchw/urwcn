# HUD 手持物品栏漏译

后续用户截图仍显示原英文物品名。本记录的来源表达式已构建，但原 `F95C3` 只绑定组件来源，尚依赖旧组件构造路径提交中文；后续已改为在同一完整原生文字调用直接消费该表达式。修正与后续交付见[地图调用作用域与 HUD 消费修正](20261110-map-scope-hud-consumers-fix.md)。

日期：2026-11-10（Asia/Shanghai）。用户截图显示“手持武器／工具”标题已经汉化，第一手仍显示 `fine broad knife`。此处是右侧 HUD，区别于 `55060/54160` 的物品选择列表。仅作源码、原始 PE 和现有反汇编的静态分析；没有启动、操作游戏、模拟输入、运行测试、创建测试用例或断言。

## 原因与静态依据

原始 PE SHA-256：`c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。以下为 RVA，原始指令见 `build/analysis/windows-3891-native-full.asm:307821` 起。原 `hud_native.inc` 只接入 `F92A5 → 1157B0` 的标题，未接入 `F95C3 → 10E5A0` 的实际物品名称。品质与名称的中性表达式已由 `windows_message_items.inc` 在原 `51770/52640` 构建器中生成，词库已有 `fine → 精良的`、`broad knife → 宽刃刀`，不需要猜测拆词或修改内部物品数据。

| 原生边界 | 静态语义 |
| --- | --- |
| `F92F7 → 3F440` | 按原 EBX=1/2 查询实际手持物；结果为零时走原空手分支 |
| `F930F → 52640` | 以原物品、EDX=1、栈参数0生成完整数量与名称 |
| `F9314..F932B` | 将返回值复制到原显示临时缓冲；在首条 LEA 处关联同一原始表达式 |
| `F9340..F9356` | 原名称达到30格时保留28格并加两点 |
| `F935D → C0190`、`F937C..F93A8` | 原物品记录与 `SHIELD` 类型判断，保持原逻辑执行 |
| `F93AE..F93D7` | 原盾牌名称达到25格时保留23格并加两点 |
| `F93FA/F943F/F947B/F94A0` | 实际追加 ` -- CENTER/HIGH/RIGHT/LEFT` 的源操作数；仅记录原分支真正追加的词 |
| `F9422/F9459/F94BA` | 原盾牌状态写入，仍由已有业务与语言重建分发器管理；本次不改写 |
| `F94E8/F955C → 114680` | 原两手键帽及空手键帽，保持原代码 |
| `F95C3 → 10E5A0` | 共同完整文字调用，原字色与outline=1、目标、位置由游戏提供 |
| `F95C8` | 从调用者ESP+3Ch恢复真实手索引；Before CALL事件ESP包含返回地址，因此读取ESP+40h作为源记录身份 |
| `F95B8` | 空手时传入原 `18D3E8` 的 `-`，按原文消费 |

原 PE 的四个后缀位于 `1AA180/1AA18C/1AA198/1AA1A4`，已从只读节直接读取。译为“——中位／高位／右侧／左侧”。没有根据未确认状态补造文字。

## 修改与所有权

新增 `modules/adapter/windows_wielded.inc`，在原生复制边界保存完整原数量／名称表达式；原英文临时缓冲仍由游戏复制、截短和追加。盾牌分支只选择相应资源类型，后缀边界只保留实际选中的原文输入。在 `F95C3` 将同一条完整语义交给既有原生组件消费。两个手索引作为真实原生记录身份，不是行槽、坐标或绘制次数。

新增 Adapter 自行解析的 `hud_wielded_item_text`、`hud_wielded_shield_text` 两个文本资源标识，不作为新 Semantic API 请求。复用 `windows_inventory` 的表达式编码／读取，原 `MessageText` 和 `TextSource` 序列化格式、HDA8及驻留桥ABI不变。保存的内容是原始英文表达式及原生分支语义，不含中文输出、UI坐标、裁剪、像素或待重放文字。

中文名称在完整消费者内按原 `F9342/F93C3` 的长度操作数和字形实际宽度进行同义截短，再追加本次原分支选中的中文后缀。两点和outline沿原调用，完整双字节字形不被切半。原文模式直接使用游戏本身已完成截短及追加的原始输入。字号、位置、背景、两手键帽、矩形、缓存和重绘均沿原生生命周期；没有新增SDL扫描、固定坐标表、整页快照或提交前叠加。

现有 `native_hud_language::rebuild` 和兼容交接后的原 HUD 重建会自然经过同一组新边界。本次不另建即时刷新入口，也不重算手持物或盾牌状态。字形沿现有组件的实际目标密度即时提交，未新增或宣称未确认的高清目标接口。

## 已知待整改项

- `modules/adapter/native_footer_component.cpp:88` 起仍由Mod计算主菜单署名位置、宽度与间隔，影响原生布局所有权，待整改；本次不扩展该路径。
- `modules/adapter/native_ui_scene.cpp:12` 起仍保存历史Child/Container集合及其序列化，完整退役待整改；本次不添加集合回放或文字重放。
- `translations/build-message-catalog.ps1:17` 起使用旧版绝对字面量地址直接读取PE，缺少3.89.1的已确认地址映射。静态生成时发现无关literal键变化；未编译或发布这次生成结果，已恢复原词库并仅加入本次四条后缀资源。生成器版本适配待整改，本次没有添加推测映射或回退分支。

## 交付状态

源码和四条盾牌后缀词库已完成；通过根统一队列完成一次配置与增量编译，保留既有函数指针转换、extern初始化、缺少成员初始化、未使用项及缩进警告，无编译错误。没有通过编译入口运行游戏或测试。完整请求JSON、完整批次日志和正式发布JSON均已读取。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求ID | `5c561cab57934c6d82e60d6d3cec12ba` |
| 批次ID | `f97c042b00bc4694a75bae7c5616dae1` |
| 请求结果 | `build/.compile-queue/results/5c561cab57934c6d82e60d6d3cec12ba.json`，`Success=true` |
| 完整批次日志 | `build/.compile-queue/batches/f97c042b00bc4694a75bae7c5616dae1.log` |
| 正式事务 | `9d1b0930c92d4f1f837bf16d012ea6a9`，2026-11-10 16:57:04（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/9d1b0930c92d4f1f837bf16d012ea6a9/publication-result.json`，`success=true`、`applied=true` |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/modules/uwcn_catalog.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧件归档 | `回收/20261110-165702-9d1b0930c92d4f1f837bf16d012ea6a9/package/`，先归档再替换，保留原相对路径 |
| 当前进程 | 宿主PID `2974827`、Windows PID `364`，未重启 |
| 热交接 | `ReadyToPublish` 后 `Applied`，Catalog、Adapter均为第10代 |

| 文件 | SHA-256 |
| --- | --- |
| Adapter，正式件／构建件／Applied一致 | `db2e523c5eb01faf81c3f09fc7a98d3cfae53fe865a49563ba9392d5d4c3a167` |
| Catalog，正式件／构建件／Applied一致 | `37f1d11046632de827ababa2e35abce9b8a1fa6214dae4b902710c17ed55a534` |
| messages.tsv，源码／正式件一致 | `69c192b28fe8278bd1ded0820c53d3ebc28ca18ef0f1e9b6aa479d4f83637da6` |

源码修改、产物编译、正式位置发布和当前进程兼容交接均已完成。根 `uwcn_launcher.exe` 继续使用同一正式包，没有独立修复包或平行启动目录。没有启动、关闭、重启、模拟操作游戏，未运行测试或创建测试用例、断言。画面由用户验收；Applied仅证明兼容业务交接。
