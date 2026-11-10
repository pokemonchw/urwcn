# 手持物品列表漏译与原生预览

日期：2026-11-10（Asia/Shanghai）。用户截图为 Windows 3.89.1 的手持物品选择页。仅依据截图、原始 PE、`GAME.NFO`、已有反汇编与源码作静态分析。没有启动或操作游戏、模拟输入、运行测试、创建测试用例或断言。兼容业务更新使用既有授权的正式热发布事务。

## 原因与静态边界

原 PE SHA-256：`c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。以下为 RVA，静态来源是 `build/analysis/windows-3891-native-full.asm`。

`58680` 在 `586A7/586AC` 传入原值 `wield` 与标题，`581F0` 最终进入原生 `55060`。原生 `54160` 构建分类、物品行、重量和磨损，`55060` 构建标题、操作提示、分页、筛选和预览；已有菜单分类译文没有接入这些消费者。原 `51770/52640` 的名称与数量语义已经有中文伴随表达式，但物品列表没有接走它们。百科预览之前只覆盖文化与技能两个调用者，且通用物品主题没有摘要资源，不能直接扩大作用域。

| 完整原生调用或指令 | 职责 |
| --- | --- |
| `5565B → 116270` | 实际选择页标题 Panel |
| `5570A/5573A/5576B → 10E5A0` | 原选择提示前缀、实际动词、句号及光标推进 |
| `5434B/548E0 → 1157B0` | 实有物品与无可用物品的原分类条 |
| `5438E/543D6/5440F/544E4/54920 → 10E5A0` | 用途、磨损、重量、使用状态和缺货提示 |
| `5451D → 52640`，`54522..5453B` | 实际数量／名称返回值复制到原 `EBP-808h` 缓冲 |
| `545CF/545FE → 10D0` | 原 `%c.%s` 与 `%c.(%d) %s` 行语义 |
| `54619..54627` | 原完整行40格阈值、保留38格并附两点的文本长度限制 |
| `54690 → CFAF0` | 实际物品动作、键帽、选择框与命中记录构建 |
| `559D2 → 10E5A0`、`559EE`、`559F4 → 114680` | 完整说明、原 ENTER 位置表达式与键帽 |
| `55A23..55EAB → CFAF0` | 全选、取消全选、完成、收起武器、移动、翻页及取消 |
| `55BEC → 10D0` | 原剩余可选数量说明 |
| `55EC7/55EE6/55FB9 → 10D0` | 全部物品、当前分类与全部类别格式源 |
| `55F42/55FEB` | 原居中及右对齐中的 `strlen*8` 宽度操作数 |
| `55F86/55F9E → 10E5A0`、`55FF9/56015 → CFAF0` | 当前分类、分类前缀、全部类别及 TAB 筛选 |
| `F91E7 → 10E5A0` | 原 HUD 指令栏实际 `Wield` 文本 |
| `561E0 → 3CA90` | 已选择物品的百科热点预览，原关键字保留英文 |
| `3CC16/3CC25`、`3CC8A → 10E5A0` | 原预览92格摘要限制及完整显示 |

## 修改与所有权

`modules/adapter/windows_inventory.inc` 接入上述完整原生文字调用。标题和动词仅新增本次已确认的手持语义；公共列表提示、分类和控件使用实际源字符串，物品行使用原构建器的中性表达式。品质、名称、数量、部分选取数量及原未付款／已拿取后缀保持原业务输入。没有整页字段快照、独立布局、坐标／行槽表或动作值改写。

新增 `native_message_expression`、`inventory_item_text` 与 `encyclopedia_preview_summary` 三个资源类型；它们由 Adapter 在原生组件消费前解析，不传给旧 Semantic API 作为新请求。前两个在既有 `TextSource.value` 保存原英文表达式的十六进制序列；不含中文输出、UI位置、裁剪矩形、像素或绘制贡献。既有组件状态序列化结构、驻留 ABI 和游戏内部英文数据未变。

原行长限制与原摘要限制按同一原生常量扩展为完整字形的实际逻辑宽度；两字节字形不会被切半。限制在已确认组件的文字消费边界同步执行，没有提交前叠字或延后重放。物品原键帽前缀单独保留；其完整行宽仍进入现有原生 CFAF0、菜单度量、选择及命中接口。

当前分类的居中和全部类别的右对齐，只替换上述原指令的宽度操作数，后续坐标计算继续执行原代码。ENTER 只将已翻译前缀与原前缀的宽度差交给原 LEA；原位移、键帽尺寸及后续调用保持原生执行，没有抄写原坐标。

`windows_encyclopedia.inc` 将物品调用者接入原热点预览，原主题关键字、F1动作、背景与缓存生命周期不变。`generate_encyclopedia_previews.py` 从已有中文正文首段取首句，展开原链接显示译名，补齐272条缺失主题摘要；既有文化及技能摘要保留。主百科生成器保留这些摘要资源。宽刃刀摘要为“宽刃刀的刀身比普通刀更宽，主要用于制革与战斗。”；伐木斧摘要为“伐木斧用于砍伐大树，也是一种结实的通用斧。”。百科链接统一为“打开《不真实的世界》百科，了解更多”。

普通绘制、已有 `native_parent_cache_language::inventory` 完整重建及兼容交接后的当前菜单重建，均消费同一组原生构建入口。高清字形沿现有实际目标密度与即时组件字形路径提交，像素与缓存仍交给原生 UI。没有新增 SDL 表面／纹理扫描或像素跟踪。

## 既有待整改项

- `modules/adapter/native_footer_component.cpp:88` 起仍由 Mod 计算主菜单署名位置、宽度和间隔，不符合原生布局所有权，待整改；本次物品列表不调用或扩展该路径。
- `modules/adapter/native_ui_scene.cpp:12` 起保留历史 Child/Container 集合及其序列化，完整退役仍待处理；本次完整页重建不遍历其集合回放文本。
- 生成摘要时静态发现，`translations/encyclopedia.zh-CN.tsv` 中 `{SKI POLE}`、`{NETMAKING}`、`{BOWYER}` 三种既有正文引用不在 `GAME.NFO` 原主题别名表中，影响其百科正文链接解析，待独立整改。本次 `encyclopedia-preview-terms.zh-CN.tsv` 仅显式给出这三个摘要显示词的中文，不创建或推测原生主题。

## 交付状态

首批请求 `a24d278d2fe747bb83612e8ba382368b`、批次 `8327e4d249c2477ba52ebd39bf8e30ac` 编译成功，正式事务 `3cccc3dea4c14b16a006abca7d488ba9` 已归档旧件并替换正式文件，但 COMMIT 返回 Adapter 初始化失败，没有取得 Applied。完整请求 JSON、批次日志和正式发布 JSON 均已读取。旧件在 `回收/20261110-164555-3cccc3dea4c14b16a006abca7d488ba9/`。

既有日志将失败定位在 native text hook installation、status=1。静态复查发现 `F91E7` 早已由 `hud_native.inc::hud_command` 接入，本次重复为同一入口申请新 Hook ID；驻留桥在写入任何新指令前拒绝该重复目标。已移除重复 Hook，改在既有 HUD 分发器绑定实际 `Wield` 语义。未修改驻留桥、添加保护或回退，也未重复运行游戏验证。

修正源码通过根统一队列再次完成一次配置与增量编译，保留20条既有函数指针转换、extern初始化、未使用项及缩进警告，无编译错误。完整读取本次请求 JSON、批次日志及正式发布 JSON。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 最终回执 |
| --- | --- |
| 请求 ID | `43450c1ed8a444859e2bc399b772ed9a` |
| 批次 ID | `ad75ba092ab943e6ba7bef78e254d51b` |
| 请求结果 | `build/.compile-queue/results/43450c1ed8a444859e2bc399b772ed9a.json`，`Success=true` |
| 完整批次日志 | `build/.compile-queue/batches/ad75ba092ab943e6ba7bef78e254d51b.log` |
| 正式事务 | `3c4a2a0068894f8ea597f0cc807a9980`，2026-11-10 16:47:08（Asia/Shanghai）完成 |
| 正式结果 | `build/mingw-x86/stage/3c4a2a0068894f8ea597f0cc807a9980/publication-result.json`，`success=true`、`applied=true` |
| 本次替换 | `package/modules/uwcn_adapter.dll`、`package/release.json`；Catalog DLL及两份新词库沿用首批已写入的正式件 |
| 旧件归档 | `回收/20261110-164707-3c4a2a0068894f8ea597f0cc807a9980/package/`，保留原相对路径 |
| 当前进程 | 宿主 PID `2974827`、Windows PID `364`，未重启 |
| 热交接 | `ReadyToPublish` 后 `Applied`，Catalog、Adapter 均为第7代 |

| 正式文件 | SHA-256 |
| --- | --- |
| Adapter，正式件／构建件／Applied相同 | `2fbc7ac7672a7d733bc4c62df2f5ffe15140d014172bf6bbcfaca2608d717971` |
| Catalog，正式件／Applied相同 | `9b431da7e8cdce479f111c50c1af4924feb18088b12ed2a2b5d2701ff40b1a69` |
| cultures.tsv，源码／正式件相同 | `fec0ef02a027e9ace058e1ce5b1a9f6adf30f7bbe1f6a18f8ce8a0e1b1fee777` |
| messages.tsv，源码／正式件相同 | `c79b0b9c98cb29261912183ed40cae35e762f5696d2619776eb5e8aa6445370e` |

源码修改、产物编译、正式位置发布和当前进程兼容交接均已完成。根 `uwcn_launcher.exe` 继续消费同一正式包，没有平行运行副本。没有启动、关闭、重启或模拟操作游戏，未运行测试或创建测试用例、断言。画面由用户验收，Applied 仅证明兼容业务交接。
