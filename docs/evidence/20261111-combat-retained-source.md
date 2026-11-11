# 已留存战斗声明的显示语义与消费边界

日期：2026-11-11（Asia/Shanghai）。用户报告战斗句仍显示 `You try to swing Herppa with your kaumolais spear.`，但字体已经变为 Mod 字形。本篇记录既有内存证据、当前静态消费链及本次补齐旧消息语义的范围；源码修改、编译、正式热发布均完成，回执见文末。

## 已确认的活跃消息来源

[运行中只读诊断](20261111-flicker-memory-diagnosis.md) 与 [精简内存摘要](20261111-flicker-memory-summary.json) 已实际读到：PID7980的活跃 MessageFlow 为22，共13条记录；第8条就是用户指出的完整英文句。其 Text 为 `kind=lookup`、`component=message_literal`、空key、空children、空syntax。对当时已加载Catalog的29个叶节点精确查询中，唯一缺项为该整句的 `message.literal.<UTF-8十六进制>` 键。

这份证据指向活跃原生消息窗口，不是 `FE2B0` 文件日志页，也不是字体不能画中文字。该记录已经丢失武器声明模板、动作片段、称呼和物品的语义分解。它没有生成时间戳，因而不能仅凭该快照断言首次生成时刻，也不能据此声称补丁后新生产的声明一定仍有同样问题。

19:53交付新增的四个生产观察点只在原生 `52FF01 / 52FF29 / 52FF4B / 52FF6D` 实际执行时传递来源；不会修改已完成的旧Record。20:19的 [原文显示及闪烁修复](20261111-flicker-original-display-fix.md) 则按用户明确授权，在中文投影失败时显示原文。因此“英文仍在、字体变平滑”与当前消费者一致，不能视作完整中文投影已经成功。

## 热交接为什么保留这个错误

以下是源码中确定的复制关系：

| 位置 | 实际行为 | 对旧声明的影响 |
| --- | --- | --- |
| `native_message_flow.cpp:117,138` | append先复制既有Source，再把当前Text值复制到新Record | Record不再依赖原生产缓冲的后续绑定 |
| `native_message_flow.cpp:240` | snapshot复制冻结Source及其全部Record | 缓存可以另持有相同消息的旧Text |
| `native_ui_scene.cpp:338` | 保存原生缓存时调用MessageFlow snapshot | 只改一个当前handle不能覆盖已保留的消息版本 |
| `native_message_flow.cpp:318-320,353-355` | 热保存写入Text；热恢复原样读回 | 新Hook和词库不会自动迁移旧Text |
| `windows_messages.inc:373` | 重建capture直接采用painting_record().text | 不重新经过声明生产者 |
| `windows_messages.inc:386-405` | borrow投影记录Text；失败则编码原生已接受正文 | 缺模板的旧记录继续显示平滑英文 |

`native_ui_scene` 的语言revision、Host依赖变化通知及HUD失效请求只要求实际原生组件重建；没有从英文记录恢复模板的算法。`windows_messages::values` 的地址关联与现存Flow记录也是不同对象：重新绑定一个生产地址，不会反向改写已经复制的Record或快照。

## 原生声明范围：四族、十条资源分支、九种不同完整句

复用 [完整战斗分支证据](20261111-combat-narrative-branches.md) 的当前Windows 3.89.1静态提取。目标PE SHA-256为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`；既有十二个完整函数包括 `52FCB0 / 4FDCB0 / 561B00 / 52AFC0 / 499BE0 / 560CB0 / 561330 / 55FB00 / 526F70 / 4F6510 / 5601C0 / 5010C0`。原始C、完整指令、引用及当前资源表保留在本地 `docs/evidence/20261111-combat-narrative-*`，本轮不重新执行游戏取证。

四种声明资源共有十条原生分支；UNARMED的ANIMAL与通用分支英文完全相同，因而只有九种不同完整句法。下表的占位名仅表示已经展开的显示片段，不代表可从旧消息恢复原actor、物品编号或攻击选择值。

| 原资源/分支 | 原生完整显示形式 |
| --- | --- |
| WEAPON / PC | `You try {verb} {defender} with your {weapon}.` |
| WEAPON / * | `{attacker} tries {verb} {defender} with {possessive} {weapon}.` |
| WEAPON / HEAR | `You hear sounds of fighting in the {direction}.` |
| UNARMED / PC | `You try {verb} {defender}.` |
| UNARMED / ANIMAL、* | `{attacker} tries {verb} {defender}.` |
| BOW / PC | `You aim your {bow} at {defender} and shoot.` |
| BOW / * | `{attacker} aims {possessive} {bow} at {defender} and shoots.` |
| THROW / PC | `You try to throw your {weapon} at {defender}.` |
| THROW / * | `{attacker} tries to throw {possessive} {weapon} at {defender}.` |

完整逐行原文及译文见本地 `20261111-combat-narrative-resource-text.tsv`。本次显示识别范围由这九种完整形式及其实际显示词法限定，不能因为某句包含 `try`、`swing` 或任意 `with` 就认为它是相同消息。

## 有限显示词法，不反推原生selector

`ATTACK_VERB` 当前有30条实际selector，生成20种不同英文片段：`to stab / to slash / to swing / to shoot / to throw / to punch / to kick / to nip / to snap at / to bite / to claw / to smack / to crush / to ram / to charge / to gore / to savage / to strike / to peck / to scratch`。其中多个动物动作可产生同一个片段。显示消费只使用这个有限原文集合及对应已有中文，不把 `to bite` 反推为BITE、BIG_BITE或PAW，也不改写内部攻击值。

`PP_GEN` 只有 `your / his / her / its` 四种当前输出；`IN_DIR` 有 `north / north-east / east / south-east / south / south-west / west / north-west / unkown direction` 九种当前输出，保留原文件的 `unkown` 拼写作为原文键。消费这些片段不等于恢复角色性别、玩家身份或当前方向。

物品、称呼和专名使用已有显示词法及原文片段，不查当前actor表来寻找Herppa，也不利用当前手持物品来解释旧消息。角色可能已经离开、改名或死亡，武器可能已经更换；旧句中的文字才是该记录的实际输入。`5601C0` 的PC描述分支直接生成 `you`，NPC描述则进入 `4AD4F0`，这些既有原生显示形式可作为词法依据，但不能把裸专名恢复为某个业务实体。

四个声明生产分支只证明第三参数及投射类别决定选用何种资源；本轮证据没有证明旧英文的UNARMED动作绝不与其他攻击片段重合。因此不以推测的合法攻击组合缩窄原文词族，也不复制一套Mod业务判断来推断资源选择。

## 已展开文字不可逆的边界

原生消息只保存显示文字时，业务身份并不总能唯一恢复：

- 裸专名可以与某个常规称呼的文字相同；英文句本身不能证明它原来属于命名人物、命名动物还是普通描述。
- 已有物品显示语法包含 `called {name}`。本轮没有静态依据禁止自定义名字含 ` at `、` with ` 或其他声明分隔文字。仅寻找第一次/最后一次分隔符，不能证明恢复了原来的物品与角色边界。
- 通用裸专名词法可接受任意剩余片段。因此较短的UNARMED句式可能把WEAPON句中的 `with ...` 整段吸收到“目标名”里；把一种规则排在前面，只是一种确定的显示分类顺序，不能证明原生当时选择了该资源。
- 不同selector产生相同英文片段时，即使译文一致，也仍不能声称恢复了原selector。

因此本次机制恢复的是已确认完整显示语法的中文表达，而不是原战斗记录。对于只有展开正文且存在上述文本歧义的情况，不能声称已经无损还原全部历史业务身份，也不能增加某个“Herppa＋kaumolais spear”专用词条冒充通用修复。实际实现对完整匹配和歧义的处理须保持这一边界；用户已授权的投影失败原文显示仍由既有消费者管理。

## 本次消费接入的范围和所有权

本次接入针对两种已经确认的原文消费者：

1. `F6510` 的borrow边界。对当前正在消费的旧声明原文识别已确认显示语法，再进入同一个中文投影、原生编码、测量、分词、分页和字形调用。新生产者已经保有完整模板的Text继续使用其原始语义；旧Flow及其冻结快照无需重跑 `52FCB0`、查询当前战斗对象或重建业务。
2. `FE2B0` 的原文源分类边界。它读取 `msglog.txt` 中已经展开且去除控制字段的正文，使用同一有限声明显示语法。该接入补齐文件日志消费的同类缺项；不把用户本次活跃消息窗口误判为文件日志页。

该方案在实际原文消费时提供显示来源，不改写Record序列化、Source身份、HDA8/Host ABI、原生英文日志文件、输入动作、消息顺序或业务数据。它不要求清除当前消息，不要求重启或重放战斗，也不从当前角色状态猜测历史名字。

新增显示来源不保存UI位置、裁剪、样式或像素贡献，不增加逐像素观察、SDL上传/Present重放或独立布局。测量、换行、分页、背景、消息缓存及重绘生命周期继续进入既有原生组件接口。现有消息来源图与缓存交接的已记录限制，不因本次显示语法增加而变为其他绘制机制的授权。

既有 [翻译失败原文显示及HUD闪烁修复](20261111-flicker-original-display-fix.md) 保留：完整中文投影失败时使用原生已接受正文；HUD同步重建沿原生禁止翻转字段完成完整构建。本次不撤销这项用户授权，也不扩展为其他未授权的容错机制。

## 源码实现与静态审查

`windows_combat_declarations.inc` 的九条完整声明显示式精确对应上表十条资源分支；徒手ANIMAL与通用分支共用同一原文和译文。`windows_combat_declaration_words.inc` 从既有提取表保留ATTACK_VERB的30条、PP_GEN的4条及IN_DIR的9条原文选择结果，复用当前正式词库的模板键，不新增整句或角色组合词条。

先匹配完整显示结构，再消费有限动作／代词／方向和物品／称呼词法。结构已匹配的武器声明，其物品词法解析失败时不继续套用较短徒手式，避免把武器尾部作为裸人名。这个分类顺序处理实际产生式的重叠，不被用来声称恢复了原生业务选择。物品递归使用独立Domain，牵绳、绑定中的称呼也进入历史称呼语法；不会调用普通对话解析器查询当前actor表，也未给任意未知物品添加裸专名分支。

F6510消费只对 `Kind::lookup / TextComponent::message_literal / 空key` 的完整原文进行这项分类；新生产者的结构化来源保持原有投影。完整替换Token使用现有声明模板中的命名标签，中文语序不会改变动态值归属。FE2B0的宽度与正文原本均调用 `windows_message_history::source`，现在经同一显示式构造同一语义源。模块只新增静态语法数据和调用期间的文字表达式，没有新增Hook、持久状态或序列化字段。

截图原文的静态对应为：`WEAPON_ATTACK_DECLARATION` PC模板，`ATTACK_VERB/to swing → 挥击`，`item/kaumolais spear → 考莫长矛`，历史裸专名槽保留 `Herppa`，得到“你试着用考莫长矛挥击Herppa。”。这由已读取的源代码和词库得出，没有执行解析器、测试或游戏画面验收。

既有 `native_renderer_component_binding.cpp:558-585,644-688` 的替换目标和retained children/icons绘制残留继续待清理，影响为旧设计的UI生命周期所有权不符合现约束；已有诊断指出当前未发现其paint调用者，不能把它当成本次已证实执行路径。`native_footer_component.cpp::paint_text` 的署名自行排布和 `docs/design.md` 的旧固定行槽／DisplayPlan文案继续待整改。本次不扩展这些机制。

未运行测试、编写测试脚本、添加断言、启动或操作游戏、注入验证或新增内存采样；静态分析复用已有原始反编译及此前用户授权产生的内存证据。

## 编译、正式发布与回收

源码保存后冻结请求范围，仅由主代理通过根统一队列提交：

```powershell
./build.ps1 -Toolchain MinGW -Module adapter -Publish -Reload -TargetPid 7980
```

一次配置、一次增量构建成功，沿用 `build/mingw-x86`。既有函数指针转换、extern初始化、未使用项及缩进警告保持；本次新增语法文件没有编译诊断。词库及驻留库没有修改，没有运行编译产物作验证。

| 项目 | 已读取的实际回执 |
| --- | --- |
| 请求ID | `918f3ae1c0a54900b97c3307477b772f` |
| 批次ID | `4548fed12b3042ffa43b85fdf42a9199` |
| 请求结果 | `build/.compile-queue/results/918f3ae1c0a54900b97c3307477b772f.json`；Success、PublishRequested、ReloadRequested均为true |
| 完整批次日志 | `build/.compile-queue/batches/4548fed12b3042ffa43b85fdf42a9199.log`，已读取 |
| 发布事务 | `077cd04a1c4740c18f9134219f346df2`，2026-11-11 20:33:37（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/077cd04a1c4740c18f9134219f346df2/publication-result.json`；success=true、PID7980 applied=true |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/release.json` |
| 旧件回收 | `回收/20261111-203336-077cd04a1c4740c18f9134219f346df2/package/`，两件旧文件先回收，保留原相对路径 |
| 当前进程交接 | ReadyToPublish后Adapter第6代Applied |

```text
Applied 077cd04a1c4740c18f9134219f346df2 adapter:df1a244b269872b0d3aabe38b03f0142b0dabca8c1fb846a7b1f5268ba8c6af4:6
```

Adapter的构建产物、正式DLL、发布清单及Applied回执SHA-256一致：`df1a244b269872b0d3aabe38b03f0142b0dabca8c1fb846a7b1f5268ba8c6af4`。已读取实际回收目录中的DLL和旧清单。正常根启动器使用同一正式包，没有平行修复目录，无需重启或重做战斗来安装。

源码修改、产物编译、正式文件发布及兼容交接分别完成。当前窗口与原生缓存的留存声明在下一次原生重建消费时使用本次语法；原记录仍保留英文，并未伪称已反向恢复其业务身份。只执行了用户授权的兼容业务发布事务，没有启动、关闭、重启或操作游戏；Applied证明交接完成，画面待用户验收。原有 `publish.ps1` 修改及已交付的闪烁修复保持原样。
