# 武器攻击方式、瞄准、防御及盾牌：完整原生分支静态提取

日期：2026-11-11（Asia/Shanghai）。范围为用户截图 WEAPON ASPECT 的原生 owner `52C110`、同一战斗选择流程 `52E370` / `52F8A0`，及其文本辅助、上层菜单和最终组件消费者。下文地址均为首选基址 `400000` 的 VA；实现中 RVA 需减去 `400000`。这里的“完整”指这些明确函数的完整反编译与其文本路径，不把游戏其余业务误称为本次全部提取。

## 当前 PE 与提取方式

目标 `D:/program/steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`，Windows x86 3.89.1。没有执行游戏代码、启动或操作游戏、注入、模拟输入、运行产物或测试，未编写测试或断言。

分析工作目录为 `build/analysis/weapon-aspect-20261111/`，下文脚本、数据库、日志及原始输出名均相对此目录。在其 `ghidra/weapon3891` 独立导入当前磁盘 PE。Ghidra 12.1.4 自动分析125秒，首次导入、全部函数提取和项目保存成功，进程退出码0；保存的仅是分析数据库，未修改 PE。`WeaponAspectDecompile.java` 导出 `native.c`，完整9函数为 `52BFD0 / 52C070 / 52C110 / 52E370 / 52F8A0 / 4FFAA0 / 4FFB30 / 500070 / 5002B0`；日志为 `console.log / ghidra.log / script.log`。

随后 `WeaponMenuConsumers.java` 在同一工程使用 `-readOnly -noanalysis` 导出 `consumers.c`，完整8函数为 `4CF790 / 4CF990 / 4CFFB0 / 5002B0 / 5000A0 / 5001C0 / 4FFC60 / 52BFD0`。退出码0，日志末尾明确 `Discarding changes`。声明原生 fastcall 文本接口，原始指令另存 `combat-menu.asm / command-menu.asm / component-menu.asm`。大函数的部分可变参数仍未恢复，完整原实参须读机器指令；不能把反编译省略实参当作函数只接收两参。

`source-references.tsv / consumer-references.tsv` 保存每条原指令的数据引用（含内部标识、数值、重复优化复制片段，不都属于可见文案）；`strings.tsv` 为当前磁盘字节确认的可见原文与资源键；`direct-callers.tsv` 是可执行节逐字节 E8/E9 相对目标枚举，并由 Ghidra引用核对。

## 武器方式：52C110

- 当前参与者、动作、武器槽、目标和投射物由原函数输入及游戏状态决定。攻击准备会清/写原生战斗结构；这些业务字段与操作码不应汉化。
- 仅在有武器、参与者为玩家（原actor比较 `-1`）、没有投射物的近战路径构建武器方式菜单。三个属性字节分别为实际栈 `EBP-864 / -863 / -862`；各自不等于 `0xC8` 时才追加对应选项。
- 可见源：`5B0B18 Blunt` → B / `5B0B20 Edge` → E / `59F8D4 Point` → P。源构建调用为 `52C676 / 52C744 / 52C814`，均以 `%c.%s` 创建上层记录，再写原action `42 / 45 / 50`。原生数量上限、英文行裁剪均保持原语义。
- 可选数量大于1且没有自动复用选择时，`52C8C7 → 5002B0("Weapon Aspect")`，标题当前VA `5B0B30`。只有一个选项时直接使用该项，零项时走取消/失败返回；不能人为生成菜单或默认武器方式。
- 特殊目标状态非零时由 `52C883 → 52BFD0` 追加说明。自动重复状态 `A6122D8`、既有方式 `A6122B0` 和许可字符集合决定是否直接复用；没有合法匹配则继续原本已构建选择，Mod不补行为。
- 返回B/E/P后分别写方式索引0/1/2、内部攻击值0/2/4；内部字串 `BLUNT / EDGE / POINT` 保留。其他返回值跳取消路径 `52D75C` 并由原函数返回0。
- 投掷/射击、NPC攻击不进入该武器方式菜单；使用原生自动评估。投掷/射击内部标识 `THROW / SHOOT`；NPC固有攻击读取内部攻击名，`SQUEEZE`归并`CRUSH`；徒手分支使用 `UNARMED / PUNCH / KICK`，`ATTACK_NOUN:%s`、`ATTACK_NOUN:PUNCH`、`ATTACK_NOUN:KICK`进入原消息资源处理器，不能改成中文内部key。
- 投射攻击的友军风险条件路径会经过三条原可见格式：`!%s osumariski %d%%` / `!%s ei ammu!` / `!%s kokeilee kuitenkin ampua!`，当前VA分别 `5B0AD4 / 5B0AE8 / 5B0AF8`。失败分支可提早返回而不显示后续菜单；名称来自原生NPC显示名称接口。

## 瞄准与特殊目标：52C110、52C070、52BFD0

- 玩家正常瞄准先清上层菜单，添加B/Body、H/Head%s、A/Arms%s、L/Legs%s。原文VA分别 `5B0B80 / 5B0B88 / 5B0B90 / 5B0B98`；行构建调用 `52CEA4 / 52CF58 / 52D016 / 52D0C9`。
- `%s`由 `52C070` 提供，已完整枚举：参数1 → `| -- tricky`（5B0AA4）；2 → `| -- difficult`（5B0AB0）；3 → `| -- very difficult`（5B0AC0）；其他原生输入得到清空后的空串。头、手臂、腿分别使用原函数内难度变量；投射物会把对应变量从1/2/1改成2/3/3，不应在Mod重算。
- 特殊目标标志 `A6123B8 != 0` 时原函数再次清菜单，替换成四个精确部位（不是在普通四行之上追加）：由原指针 `58E97C / 58E970 / 58E994 / 58E998` 取得 `neck / skull / thorax / abdomen`，组成 `BODYPART:%s`并经`561B00`解析；随后首字母大写，并以 `4FFB30(action=0)`由原英文首字母产生N/S/T/A键。四个追加点 `52D215 / 52D31F / 52D41F / 52D51F`。目标非玩家、非人类时代码还保留 `PAW`→`HOOF`条件转换；这些原key与动作构建必须原样保留，中文只能在接受完成的显示记录消费处生成。
- `52BFD0`参数1读取 `HITOPT_DEATHBLOW`（5B0A7C）；参数2读取 `HITOPT_BUTCHERING`（5B0A90）；0不追加说明。非零的其余值经清空缓冲追加空内容。`52C054 → 4FFC60`将结果追加到原菜单引言缓冲`65A88B8`。原文资源分别为“A deathblow is possible. You try to execute a carefully aimed strike to finish this unconscious victim.”和“Butchering is possible. You try to execute a carefully aimed butchering blow to quickly stun or kill this leashed creature.”。
- 标题 `Aiming Zone`（5B0BA0）经 `52D564 → 5002B0`。自动重复状态非零时复用既有瞄准，不调用菜单。NPC侧按目标状态、投射物、盾牌状态等直接选择瞄准值并跳过该菜单；特殊目标还可直接选原定部位。
- 正常玩家返回B/H/A/L按原分支写身体区和难度；特殊目标N/T/A及其它原选项按跳表映射；返回0/非法普通键进入原取消分支。不得根据中文首字重造键值。
- 末段诊断原文 `strikeimpact %d maxdices: %d` 当前VA `5B0BAC`、引用52D6C9，只有原诊断标志 `A6D28A0 != 0` 才通过`? %s`提交消息。

## 防御：52E370

- 先走原状态、姿态/能力、移动闪避与攻击类型判定。无法行动、无可用防御技能、移动闪避已经结算的路径直接写原业务结果并返回；不弹菜单。NPC通过原评分与随机比较选择躲避/格挡/反击/忽略，也不弹玩家菜单。
- 玩家许可集合初含D/I；对两只手分别读取已持物品并调用原武器有效性判断；非SHIELD的有效物品分别加入`1`/`2`反击键。原生比较两手防御值以及 `A612670` 和SHIELD类型，从实际持物选择一个可格挡对象，再加入B。所有物品名称为原生所选描述+9字段；不能复制业务判定来造行。
- 按原许可集合逐项创建：D → `Dodge`（5B0C80）；B → `Block with %s`（5B0C88）；1、2 → 两个独立`Counterstrike with %s`（5B0CA0）；I → `Ignore`（5B0CC8）。行构建调用分别 `52EC35 / 52ED06 / 52EDD7 / 52EEA8 / 52EF64`。
- 然后添加原空分隔行(action=-1)，以及`?` → `Defense maneuvers`（5B0CD0，构建52F084）。帮助键分别 `DODGE / BLOCK / COUNTERSTRIKE / DEFENSE MANEUVER`，由 `500070`绑定原行；是百科主题标识，不是可译菜单值。
- 标题 `Defense Maneuver`（5B0CF8）经 `52F0D8 → 5002B0`。返回1/2拷贝对应手的原武器和槽位；B用原选中的格挡对象；D写闪避；其他返回由原默认路径置忽略（包括取消）。`?`帮助页由共用菜单内部接管，恢复后仍等待原菜单。
- 完整诊断格式：`MOVEDODGE: %d`（5B0C50、ref52E54E）；`>Dodge_ML(%d): %d`（5B0C60、ref52E621）；`NPCdefend: %s Dge:%d Blk:%d chose:%d`（5B0D0C、ref52F251）。前两项由原诊断标志控制；NPCdefend通过原`5010C0`消息诊断路径。内部DODGE/MOVEDODGE/SHIELD等继续保持英文。

## 盾牌：52F8A0

- 入口先显示 `#Select how to hold the shield to cover yourself against missile attacks.`（5B0D78），然后原生刷新并创建四项：N/None（5AACC4）、C/Center（5B0DC4）、H/High（5B0DCC）、S/Side（5B0DD4）；调用 `52F924 / 52F9B4 / 52FA44 / 52FAD4`。
- `52FB14 → 5000A0("SHIELD")`把SHIELD帮助主题填给未有帮助主题的有效原行；标题`Shield mode`（5B0DDC）经52FB28调用5002B0。
- 必须保留原版不一致：实际显示None键是N，而返回值switch显式分支是C、D、H、S；N和取消均走默认`52FBEE`清`A72BA95`并原生刷新，不发送那条“正常移动”提示。原跳表`52FC08`指向`52FB73/52FB51/52FB9C/52FBC5/52FBEE`，`52FC1C`选择字节仅C→0、D→1、H→2、S→3，其余→4。Mod不得擅自“修正”为N分支。
- 四个原消息分支都已提取：D：`_You move normally and don't cover behind the shield.`（5B0DE8）；C：`_Holding the shield carefully in front of your center slows your movement.`（5B0E20）；H：`_Holding the shield high restricts your field of vision and slows your movement.`（5B0E70）；S：`_Holding the shield raised by your side it's slightly slower to move.`（5B0EC8）。每个分支保留其位掩码写入和原刷新。

## 实际 UI 消费边界及共用分支

- 上层行数组`659F988`、stride20C，action位于行+ C8。`4FFAA0`是原reset；`4FFB30`支持明确action、或action0从英文label首字母决定原键。原字符截断与原菜单数量由游戏执行。
- `5002B0`先经`5002DB → 4D3DB0`生成标题大写副本；`5003B8 → 4CF790`创建kind6原菜单。存在说明时，`65A88B8`进入`562300`和`50EB40`，原函数根据段落返回高度增大窗口。不能固定坐标/行数重绘说明。
- `50042B → 4CF990`以ECX原action、EDX原完整接受行交给组件。分隔行通过50041E写空行；只有`65A9694==0`才追加空行和`ESC.Cancel`（595CD8，50049B，action1B）。原标题经过大写转换后也必须在显示消费处保留翻译语义，不能用英文大写结果直接要求大小写敏感词库命中。
- `4CF990`先复制完整文本，再按第一个`|`分隔主文和副文。主文进入`634EF10+index*E8`，副文进入`634EF74+index*E8`，action仍在`634EFD8+index*E8`，最后才递增`6354A34`。瞄准副文实际为` -- tricky`等（保留首空格，不含`|`），原组件本身决定副文放置。
- `500525 → 4CFFB0`绘制；`CFFB0`内kind6标题和行仍由原`50E5A0/515E70`文本入口绘制，原菜单管理尺寸、居中、行高、选择、命中、背景、缓存和重绘。汉化只在已确认组件文本消费者接入完整语义及已有中文度量。
- 共用菜单还具有：行带图形时显示`GRAPHICAL PRESENTATION`（5AAD04）；帮助按键或当前行帮助主题存在时打开原百科并从`MENULIST.SAV`恢复原菜单；非ESC选择在共用菜单原出口构建`#%s: %s`（5AAD38），移除`|`副文并经原Message提交；含`NO DISPLAY`时清空回显。上述四个战斗调用在菜单期间把65BBA50置1，但`5002B0`本身仍构建/提交回显，不能因该标志推断无文本构建。空/取消原返回保持原样。`!keydebug / listhotkey %d - %s / LIST_Go() -> / got pos %d`是共用菜单调试通道，`NO DISPLAY`是原消息显示控制标识，`MENULIST.SAV`是原文件名，均不可当作标题翻译。

## 调用者闭合与静态限制

当前可执行节E8/E9枚举：52C110仅从52FD44、530472调用；52E370仅从5303DA调用；52F8A0仅从450CF8、53212A调用；52C070仅52CEE5、52CF98、52D056；52BFD0仅52C883、52D52A。未发现E9到这五入口，Ghidra引用一致。完整consumer文件额外保存所有原函数直接调用者。

本记录不构成游戏画面测试、热加载验证或正式发布结论。已有代码是否满足这些边界由主代理另行静态审查和记录；仅有编译成功不能替代所有权证据。
