# 共用消息区动态值来源审计（2026-10-20）

本文件记录静态反编译与源码接入状态，不是运行验证记录。没有运行游戏、注入、测试、测试脚本或断言；本代理未编译或发布。调用地址均为原 PE VA；源码 HookSpec 使用 RVA。

## 已接入的动态构造

实现位于 `modules/adapter/windows_message_values.inc`、`windows_message_value_builders.inc`、`windows_message_value_chains.inc`、`windows_message_value_copies.inc`。保存的是 `native_message_source::Text` 原文来源图。原生函数仍自行选择分支、构造英文、维护槽位并返回；Mod 仅记录其选定词域、格式参数及已经发生的真实复制。显示语言变化时重新投影源图。

| 原生边界 | 当前实现与证据 |
| --- | --- |
| 4AD4F0 NPC 称呼 | 读取真实传入 index/flags 及 record 的类别、性别、幼体、熟识标志；类名使用 npc 词域，+30 专名使用 identity；对应 full C `settlement-dynamic-values-ghidra.c`。 |
| 4ADCA0 普通档案描述 | 记录实际 sprintf 参数、562300 追加片段及561E90实际列表连接；不复制 UI 位置、字宽或原生词缓存。 |
| 4AE750 尸体 | 姓名、体型、实际伤情/腐烂/焚烧描述与剥皮后缀均由当前调用帧子源和真实追加点组合；45189C 返回通知 items 父构造帧。 |
| 440B20 制作结果 | 原生实际格式 `%d %s`、`%s %s`、`%u %s,` 和实际列表连接分支组成源图。 |
| 562E30 / 562ED0 | 原生去重/计数结果决定槽位和计数；源图随实际 slot 写入并使用已选 count、and/comma/more 分支。 |
| 5627A0 消息列表 | 收据42F7C0/42FBC0两条真实复制及追加链；鱼类431131/431158与附近物体507581由 format builders 提供实际源序列；保留原生分隔规则。 |
| 4AAF20 | 返回 AL 人数与 ECX 目的缓冲分别处理；列表子源来自562ED0。 |
| 405340 / 562BD0 / 4D71B0 复制 | 4063A3→EBP-70、406964→EBP-13C、4D8C15→EBP-70 的实际复制完成点绑定。 |
| 4D4EF0 | 七类固定疾病，以及真实 injury noun 表（含尾空格）+`in `+side+4D4600 bodypart；4D5054/4D50CB记录实际选定名词/侧别。 |
| 403550 | 植物状态真实分支与资源构造；5E9B08 status 全局保留其原生产源。 |
| 448D50 | 弓弦固定词及实际格式参数。 |
| 4E1EF0 | 用户地图标记：4E4050 输入→record+10→4E1340 写入 MVMARKER.DAT→4E1DF0 读取→4E1EF0 返回，按用户文字 identity 保留。 |
| 567880 | 原生选出的九种踪迹年龄描述，track-age 精确词域；实际调用567B15。 |
| 4F6F70 | 原生 ECX 文本立即复制到65A8CF8的入口传播，未改变原业务消息。 |
| 战斗记录字段 | 52C110/52E370/52FCB0等实际 producer 返回→record+164武器/+22C部位→攻击/防御记录复制→5E9E88/5E9CE8/5E9C80/5E9DB8/5E9D50/5E9BB0；见 `settlement-tag-source-writers.tsv`。 |
| 4A2436→4A245A | 4076C0→article 的实际返回立即复制 ESP+250，传播后再进入 lowercase。 |
| 464730 | 16个实际sprintf与46522E共用消息出口；实际数量、重量、长度、备选名称、徒手后缀、选中行复制、必需/可选前缀、优选材料/长度/句点。见 `windows_message_requirement_value.inc`，C950..C95E。 |
| 55E3B0 | 每个真实选中bit调用55E2C0的树材源，实际comma append→562930的or列表→原生ring复制，不重选材料。 |
| 4AECB0诊断 | 4AF533/4AF732在进入独立profile之前构造两种共享消息诊断；实际item参数、数值参数进入源图，外层4AF568/4AF763由formats处理。 |

所有原生 CALL 待返回帧及跨原生构造的源图随 save/restore 序列化；instruction hook 使用 inline_before。中间字符串不作为全局“英文值→译文”兜底字典。

## transform 输入逐点审计

`settlement-value-transform-inputs.tsv` 从反编译 HighFunction 的 CALL 输入递归提取 COPY/CAST/PHI/PTRSUB/PTRADD/常量来源，共206条已恢复 CALL 输入；56FE30完整反编译超时，572E79/573187已独立核对原始汇编。

`transform_domain` 仅对已证原始字段按确切调用点选择词域：物品 descriptor+9、flora alternate+31、NPC record+8、文化身份58E38C、睡意58E938..950、姿态49D0E0、reputation、技能、制作配方名。其余已生产对象要求真实 owner 或当前父/标签调用帧子源。

特别更正：55EFF0 plural 的输入确为 ECX，55F00B→55F03F读取该值；441CAB的 PUSH EAX 是稍后 printf 的参数，不是 plural 入参。441CB2输入EBP-140来自44187A→440000所取制作条目`.Name.`字段，使用 menu.recipe 域。

572E57读取用户任意文本，572E79进行原生复数诊断，572E80回显其实际结果。这一条保存原生返回 identity，而不把用户输入按游戏名词猜译。

plural/singular/article/lowercase/encounter返回用单child concat保留已捕获的语义叶，再仅覆盖父节点的实际英文身份。例如grammar完整`leaf/leaves`键不能被返回的`leaves`覆盖，原item词也不能被`an item`覆盖。已与菜单负责人核对实际裁剪图：动态clip只有4F8D89/546809的flags4 NPC（无flags2 article）、三武器descriptor+9的crafted静态语法及外置section；不存在上述长度变化wrapper进入visible_prefix的路径。其它bound行在不裁剪builder或key0原生重写后显示。首字母case变更保持实际UTF-8字节跨度。

## 本轮追踪条目的最终归属

下表区分实际消息构造、业务/独立对话和跨代理负责范围，不以注册Hook数量替代覆盖证据。

| 原待确认项 | 最终结论 |
| --- | --- |
| 46511F | 输入来自464730实际选中需求行复制；整个消息构造已接入，包括所有16个sprintf及非sprintf append分支。 |
| 436A48、46D5C2 | 制作材料名称来自467A30的真实字段/首词/尾词选择，后续构词及descriptor持久化由format builders、materials、crafted items模块处理；values只传播该次已绑定的输入。 |
| 413D25 | 413CB0返回后仅供550720的QST对话body；type38标题独立使用record+8，已由quest records处理。移除本共用消息lower hook。 |
| 539490/53CC90/540360/540610/5413C0 | 文本进入5339B0的独立NPC对话，或534D90动作窗口；未发现该临时lower结果进入4F6510。移除对应lower hook。 |
| 549640 | 六个lower调用构造任务教学SKILL对话body，不是共用消息或QST标题。移除对应hook。 |
| 4AF342/4AF58A/4AF7A2 | 独立profile组件文本；真正共用诊断先在4AF533/4AF732构造并显示。两格式已接，三个profile lower hook移除。 |
| 556480 | 556240生成Old man's punt任务的对话body；type10标题是固定原文。移除该lower hook。 |
| 旧type35标题 | 已按当前原生3.89正常业务证明其有限动物称呼来源，按固定suffix恢复；fresh记录保留实际构造源图。完整证据见 `20261020-type35-animal-name-domain.md` 与quest title文档。 |

18个`transform_domain == item`调用均逐raw确认输入为真实descriptor+9，包括40166B（ESP+89）、432867（EBP-917）、5321C8（EBP-8AF）、54DE24（EBP-EE7）和两个原生scratch/base池。现接入`message_crafted_item_source(descriptor,input,source)`，使用真实+0x93及ID区分库存词和生成名称；没有对未知字符串尝试多个域。跨代理的生成名称完整语法归属crafted items模块，不将它未完成的语法计为values完成。

## 已确认范围外的调用

- 5627A0的538375/53D27A/53D7CA/53E358/54243C五个调用进入5339B0的独立原生对话组件：50E5A0、300宽、5E9798/5E97A0坐标返回。它们不是4F6510共用消息区；已从本消息列表 hook 表移除。证据 `settlement-map-chat-ownership-ghidra.c`。
- 43CFE0的lower用于读取GAME.NFO主题键并写debug_topics.txt；44BDB0中的4D4240截后两词/lower用于装备相容业务比较，不是已确认消息文本生产者。不得以词表命中当显示覆盖。

## NPC 历史字段证据

`settlement-npc-name-lifetime-ghidra.c`与`settlement-npc-name-lifetime-refs.tsv`包含：4AD4B0在描述含`' the `时去掉前缀并OR known bit1；539800在自我介绍后OR bit1；5431D0接受非空非ESC用户名字后OR bits1/2并覆盖record+30。真正的 scratch 初始化为 `settlement-npc-initializers-ghidra.c` 中的4CE8E0。4C1BF0从region/gender名字文件选取默认专名。

新增 `20261020-type35-animal-name-domain.md` 记录正常动物命名与村落目标筛选的不相交证据、自我介绍的人类门、AI回访的人类dispatcher，以及隐藏调试owner编辑器的独立入口。

`settlement-quest-animal-selection-ghidra.c`包含542D30、543140、543340的完整选择条件与调用者。40D1B0/40D650写入证明CRS保存当前记录而非生成时历史快照；type35识别采用上述正常生成域证据，未重新执行原生业务函数。
