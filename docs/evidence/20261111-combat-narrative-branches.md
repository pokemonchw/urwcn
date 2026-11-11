# 战斗宣告及同一原生 owner 的完整文本分支

日期：2026-11-11（Asia/Shanghai）。入口是用户截图中的 `You try to swing Herppa with your kaumolais spear.`。这不是新的独立固定句，而是 `WEAPON_ATTACK_DECLARATION` 的 PC 分支，由原生 `ATTACK_VERB:BLUNT`、防御者名称和武器名称组合而成。

本次静态目标为 `D:/program/steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。使用既有 Ghidra 12.1.4 工程，以 `-readOnly -noanalysis` 提取；未执行游戏、测试、注入或模拟输入。原 PE 与 Ghidra 工程均未写回。

## 提取范围和原始证据

当前 PE 完整提取十二个函数：`52FCB0`（本次文本 owner）、`4FDCB0`（可见/听觉消息交接）、`561B00`（消息资源）、`52AFC0`（投射结果）、`499BE0`（开场视野更新）、`560CB0`（资源选择）、`561330`（动态标签展开）、`55FB00`（成对标记提取）、`526F70`（战斗结果正文）、`4F6510`（原生消息显示）、`5601C0`（动态值）、`5010C0`（原生诊断消息）。

- [新增四点指令边界及 incoming](20261111-combat-narrative-declaration-incoming.tsv)
- [owner 内既有全部格式绑定](20261111-combat-narrative-format-bindings.txt)

以下原始提取物保留在本地 `docs/evidence/`，按仓库惯例不纳入Git；下文保留其分支结论、来源地址及实现对应：

- 完整反编译：`20261111-combat-narrative-native.c`
- 完整指令及逐字节 incoming：`20261111-combat-narrative-native.asm`
- 所有数据引用：`20261111-combat-narrative-references.tsv`
- 当前原生资源原文、全部分支及既有译文：`20261111-combat-narrative-resource-text.tsv`

Ghidra 脚本与最终日志位于 `build/analysis/combat-narrative-20261111/`。反编译 C 的局部变量名称仅供理解；接入偏移和输入寄存器以实际指令为准。`52FCB0` 先对 ESP 作 8 字节对齐，因此不能用反编译局部名或固定 EBP 偏移代替实际 `ESP+268h`。

本篇穷举的是该 owner 的文本分支、声明依赖及直接显示链；没有把整个游戏的全部业务函数宣称为本次重新提取。`52C110 / 52E370` 的菜单和取消子分支已另行完整提取于 [战斗菜单分支](20261111-combat-menu-branches.md)。

## 攻击声明四路与提前退出

原函数使用 ECX 为攻击者、EDX 为第二参数；`[EBP+8]` 为第三参数，`[EBP+C]` 为目标。目标值1000由原版转换为-1。`52FD1A..52FD23` 在第五参数非零且第二参数为零时直接退出；`52FD44 → 52C110` 返回零时也直接退出。两条路径均尚未构建声明，Mod 不补消息。

| 原生条件 | 资源键及当前资源地址 | 资源返回后复制点 | 实际来源与目标 |
| --- | --- | --- | --- |
| 第三参数非零，`A612584==3`，`A61263C!=0` | `BOW_ATTACK_DECLARATION`，`5B0F2C` | `52FF01` | EAX → ESP+268h |
| 第三参数非零，`A612584==3`，`A61263C==0` | `THROW_ATTACK_DECLARATION`，`5B0F44` | `52FF29` | EAX → ESP+268h |
| 第三参数非零，`A612584!=3` | `WEAPON_ATTACK_DECLARATION`，`5B0F60` | `52FF4B` | EAX → ESP+268h |
| 第三参数为零 | `UNARMED_ATTACK_DECLARATION`，`5B0F10` | `52FF6D` | EAX → ESP+268h |

四个点全部为完整7字节 `8D 94 24 68 02 00 00`，即 `LEA EDX,[ESP+268h]`。逐字节 incoming 输出没有指向四个范围内部的引用；原生复制循环回边落在其后的 `52FF10 / 52FF32 / 52FF54 / 52FF76`，没有覆盖回边或 ESP 调整。

本次 `windows_message_combat_body.inc` 的 F492—F495 在这四个实际复制点传递已有消息来源图，目标为观察时的 `frame.esp+0x268`，来源为 `frame.eax`。原生继续完成 NUL 终止复制。声明仍在 `52FFC6` 从同一目标装入 EDX，在 `52FFD2 → 4FDCB0` 消费；ECX 是 `A611FA0` 的实际攻击者，第三参数是原生空串。没有在 Mod 中选择攻击类别、构建业务数据或替换输入动作。

声明生成后还有独立分支：若防御者 `A611F80==-1` 且原生 `499F40` 判断攻击者坐标不可见，`52FFB2` 读取 `CANT_SEE_ATTACKER` 并在 `52FFB9 → 4F6510` 显示；该分支不使用局部声明，也不调用 `4FDCB0`。其资源和显示来源已由 `windows_message_resources.inc` 与原消息消费者处理。

## 资源选择及全部动态输入

当前四种声明资源共有10个实际分支：武器 PC、*、HEAR；徒手 PC、ANIMAL、*；弓 PC、*；投掷 PC、*。不为无 HEAR 的三种声明补造 HEAR。`560CB0` 按原生选择条件读取实际行，并单独搜索实际 `[HEAR:]` 行；`561B00` 保留正文 `A624EB0` 与听觉文本 `A6248B8`，展开标签及嵌套资源。既有 `windows_message_resources.inc` 在 `561B9B / 561BA7 / 5613D4 / 561C79 / 561D7A / 561E74` 等实际调用和完成点承接已执行结果；Mod 不再次运行选择算法。

| 声明输入 | `5601C0` 确认的实际来源 | 已有接入 |
| --- | --- | --- |
| `attack_aspect` | `5E9E20`，由 `52FE90` 从 `A612740` 复制 | 保持 POINT、BLUNT、动物攻击等原控制值；交给原生嵌套资源选择 |
| `attack_weapon` | `5E9E88`，由 `52FE70` 从 `A6126DC` 复制 | `windows_message_value_copies.inc` 的战斗记录与字段来源；`windows_message_values.inc` 的 bound 值 |
| `attack_bow` | `5E9CE8`，`52FE2C → 452640` 后在 `52FE31` 复制 | 同文件 `12FE31` 已有原生物品来源 |
| `attacker` / `defender` | `A611FA0 / A611F80` | PC、人类性别、ANIMAL仍由 `5601C0` 生成原控制值，原生资源选择 |
| `*_desc` | NPC 分支 `560B17 → 4AD4F0(actor,0)` | 已有NPC来源捕获；保留专有名字 |
| `*_defdesc` / `the` | NPC 分支 `560BE1 → 4AD4F0(actor,2)` | 已有NPC来源捕获；保留定冠词语义 |
| PC 的 `*_desc / *_ind / *_defdesc` | `560AE7 / 560B44 / 560BB0` 直接 `MOV [A6C6AA8],00756F79h`，即 `you`，不调用NPC命名 | `npc/you` 词条有确切静态依据；不修改原控制值PC |
| `npc_direction` | `5601C0` 的独立分支调用 `49B690` 和 `55EBA0` | 原生方向值再进入 `IN_DIR` 选择 |

原生 `<attacker>` 的PC值由actor=-1生成；NPC记录kind1及kind32保留原生性别选择，其他kind生成ANIMAL。`_desc`、`_ind`、`_defdesc` 对PC直接写 `you` 的分支与上述NPC调用分支均已提取。不能把所有动态角色名当作PC，也不能对普通人名作整句正则替换。

资源清单由当前游戏 `messages/` 原文件提取，而后按现有 `selected-templates.zh-CN.tsv` 精确列出对应译文，共24节138行：

| 资源集合 | 当前实际分支数 |
| --- | --- |
| `ATTACK_VERB` | 30 |
| `ATTACK_NOUN` | 18 |
| `ATTACK_HITS` | 25 |
| 四种攻击声明 | 10 |
| 本 owner 的其他11种消息资源 | 14 |
| `PP_GEN / PP_OBJ / PP_SUBJ` | 各4，共12 |
| `IN_DIR` | 9 |
| `WEAPON_CLASS_BONUS` | 6 |
| `HANDMODE_PEN` | 14 |

`ATTACK_VERB` 全部30个selector为：POINT、EDGE、BLUNT、SHOOT、THROW、PUNCH、KICK、NIP、SNAP、BITE、RIP、SMACK、CRUSH、BIG_BITE、HOOF_KICK、RAM、CHARGE、ANTLER*、CLAW、SAVAGE、SNAKEBITE、PECK、SCRATCH、PAW、SQUEEZE、HORN、HOOF、TUSK、ANTLER、BEAK。原生没有通用 `*` 动词行，未补造该行；ANTLER* 和 ANTLER 两个实际分支都保留。NOUN的通用 `*` 行属于原生实际资源，保留其“攻击”译文。

资源表同时保留 `native_line`，包括 `urw_combat.txt:493` 原本缺少末尾 `]` 的 `MISSILE_WILD/*` 行。原生读取器按是否存在 `]` 决定移除末尾字符，现有译文来源与其实际正文一致；本次没有改写原游戏资源的语法。

## 52FCB0 同一 owner 的其他全部文本分支

该函数直接引用15个不同消息资源键；下表加上四种声明就是完整15项。四个加成键由原生delta和防御动作分支选择，Mod仍只观察原生实际返回资源。

| 原生选择/调用 | 原资源 | 原生条件或区别 | 既有来源通路 |
| --- | --- | --- | --- |
| `52FFAD / 52FFB2` | `CANT_SEE_ATTACKER` | 玩家为目标且看不到攻击者，绕过普通声明 | resource → `4F6510` |
| `5300D3 / 5300D8` | `MISSILE_WILD` | 投射结果早退段，`A6122B8 < A6122A4` | resource → `4FDCB0` |
| `530150 / 530155` | `CANT_THROW_THAT_FAR` | 未击中且无阻挡/碰撞分支、玩家攻击、`A611B60!=0`；先设置原生who值 | resource → `4F6510` |
| `53034F / 530367` | `MISSILE_ACCIDENTAL_TARGET_BEHIND` | 实际目标改变，`A6122CC!=0` | resource → `4FDCB0` |
| `530362 / 530367` | `MISSILE_ACCIDENTAL_TARGET` | 实际目标改变，`A6122CC==0` | resource → `4FDCB0` |
| `530748 / 53074D` | `WC_BONUS_DEFENDER_WINS` | delta<0，任一方是玩家，防御动作10或12，第三参数>0 | resource → `4F6510` |
| `5307A1 / 53074D` | `WC_BONUS_DODGE` | delta<0，任一方是玩家，防御动作11，第三参数>0 | resource → `4F6510` |
| `530793 / 5307B1` | `WC_BONUS_ATTACKER` | delta>0，任一方是玩家，防御动作不是10/12，第三参数>0 | resource → `4F6510` |
| `5307AC / 5307B1` | `WC_BONUS_ATTACKER_WINS` | delta>0，任一方是玩家，防御动作10或12，第三参数>0 | resource → `4F6510` |
| `530A9B / 530AA0` | `TWO-HANDED_PENALTY` | 原生单手惩罚非零且原目标参数==-1；先构建原生item和var值 | resource → `4F6510` |
| `531061 / 531066` | `CANT_THROW_PAST_CONTOUR` | 后续投射结果段，`A611B68!=0`；先设置原生who值 | resource → `4F6510` |

投射早退、改变目标两路在 `5300A1 / 53031A` 向 `A611B78` 追加句点，再经 `5300B9 / 530333 → 4FDCB0`。已有 `windows_message_transfers.inc` 覆盖 `52AFC0` 的四种投射结果初选、最终全局复制和两个句点点位。本次完整重新提取 `52AFC0`，包括 `MISSILE_INFERIOR / MARGINAL / GOOD / SUPERIOR` 四种实际结果，保持原生随机和业务计算。

后续 `531005 → 526F70` 战斗结果正文已由 `windows_message_combat_body.inc` 的F400—F491承接；本次完整重新提取该函数作为交接证据，既有55个来源观察点的逐分支说明见 [20261020-combat-message-body.md](20261020-combat-message-body.md)。本次新增F492—F495只处理此前漏掉的声明局部复制。

`531324 → 451770` 返回实际物品名，`53133A → 4010D0` 以 `+The %s breaks!` 格式化同一局部缓冲，再 `531349 → 4F6510`。已有format绑定的 `%s` 为bound物品来源。`5312F1` 的 `[no head]` 是传给 `44D910` 的原生物品操作标志，不是对用户显示的句子；保留该业务值。

## 全部格式和诊断输出

`52FCB0` 有24个已绑定格式调用点、17种不同格式模板（含7个 `? %s` 包装点、2个相同WPMOD格式点）。以下为完整列表，均在 `windows_message_formats.inc`：

| 当前调用VA | 原格式 |
| --- | --- |
| `53019E` | `MISSILE olento_osuma - OGImpact: %d` |
| `530202` | `MISSILE olento_osuma - NewImpact: %d (OGI %d+KE %d / 2)` |
| `5305C2` | `A-SKILL:%s(%d) D-SKILL:%s(%d)` |
| `5305F8 / 5306EA / 530B2A / 530B89 / 530C06 / 530D43 / 530DC7` | `? %s` |
| `530671 / 5306B5` | `>WPMOD: A:%d D:%d = %d` |
| `53087C` | `>OUTNUMBERED BY %d NPCs` |
| `530931` | `ZonePenalty: %d` |
| `5309AC` | `>HANDPENALTY:%d` |
| `5309EC` | `DEFENDER ZonePenalty: %d` |
| `530A8C` | `%d`（原生var输入） |
| `530ABE` | `>DEFENDER HANDPENALTY:%d` |
| `530AF5` | `>A_BONUS:%d D_BONUS:%d` |
| `530B54` | `>A_PEN:%d D_PEN:%d` |
| `530BD1` | `>EML_sync A_PEN:%d D_PEN:%d` |
| `530D0E` | `Puolustus Ignore: SUCCESS (%d) BOOST` |
| `530D92` | `Puolustus Ignore: SUCCESS NOW %d` |
| `53133A` | `+The %s breaks!` |

上述旧版格式标识继续保持原值；当前PE实际指针偏移由已有 `windows_3891_rdata.inc` 逐项映射，未套用整段地址平移。`A-SKILL` 的两个 `%s` 为skill域，包含原生内部动作 `MOVEDODGE`；只翻译显示值，不改记录里的动作标识。

另有两条非格式诊断字面量：`5308CB` 的 `prone modifier: Attacker +20` 与 `530903` 的 `prone modifier: Defender +20`，均交给 `5010C0`。该原生函数只在 `A6D28A0!=0` 时暂时清除原显示抑制标志，以 `? %s` 包装后进入 `4F6510`，随后还原标志。已有公共格式边界承接包装，本次词库补齐两条已确认字面量；没有启用原本关闭的诊断模式。

## 原生可见、听觉和消息显示生命周期

`4FDCB0` 经实际指令确认的签名是 `__fastcall(int actor, char* text, char* hearing)`：ECX为actor，EDX为text，第三参数在入口栈上。此前C反编译工具推断参数不全时，不能把ECX误当字符串。

- 原显示抑制 `518F4F2!=0`：不显示，清理原临时听力值后退出。
- actor==-1：`4FDCE8` 起复制text到原生局部正文，再交 `4F6510`。
- NPC/动物：先按显式hearing或资源 `A6248B8` 复制原生听觉局部；FORCE_HEAR、ALWAYS_HEAR、DATAPOS_TARGET各分支仍由原生判断。
- 可见：`4FDECD` 起把实际text复制到 `A80EB70`，随后 `4F6510`。
- 不可见：原生计算距离、听力、特殊标志；通过条件且听觉正文非空时，`4FDFB2` 起复制实际听觉局部到 `A80EB70`，再调用原生方向处理和 `4F6510`。距离不满足或正文为空时原生不显示。

以上七个实际复制点均已有 `windows_message_hearing.inc` 来源传递，且没有新增状态判断。`4F6510` 的截断、分页、消息记录、绘制和颜色选择仍归游戏；Mod只沿既有已确认消息消费者提供来源。

历史文件消费者 `FE2B0` 是另一条边界：它重读原生 `msglog.txt` 的已展开英文正文，原模板及动态来源身份没有随英文行保留。`windows_message_history.inc:6` 的现有 `history_forms` 只覆盖已列明的命名、动物指令等有限动态语法，没有攻击声明的完整动态语法。因此本次四个新复制点解决实时原生消息构建的来源丢失，不能据此宣称 `FE2B0` 中的任意旧记录或新写入英文记录均已得到同样语义。影响及状态：历史查看中的动态战斗句尚待按其已确认文件消费边界处理；本次未修改该历史语法，也未补造反查当前角色状态来推断历史名字的路径。参见既有 [历史消息边界说明](20261111-message-history-missing-text.md)。

## 所有权与交付说明

本次新增点不持有UI位置、裁剪、字形布局或整页文本，也不拦截SDL纹理/表面去追踪像素或重放贡献。来源图供实际原生文本消费者使用，原生测量、换行、居中、输入、缓存和重绘流程保持既有所有权。既有 `native_footer_component.cpp::paint_text` 与 `native_ui_scene.cpp` 的历史待整改项仍按 [战斗菜单证据](20261111-combat-menu-native.md) 记录，本次不扩展它们；编译/发布不会改变其待整改状态。

本篇记录静态证据和源码映射，不把静态提取称为游戏验证。产物编译、正式发布、回收路径及请求/批次回执由本次主交付记录另行列出。
