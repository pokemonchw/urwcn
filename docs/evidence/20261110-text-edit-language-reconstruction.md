# 全部 getst 编辑等待的原生语言生命周期

对象为 Windows x86《不真实的世界》3.89.1，原 PE SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。下文地址为 RVA。只读原 PE 和源码，没有启动游戏、运行产物、输入模拟、测试、测试用例或断言。

新增 `modules/adapter/native_text_edit_language.inc`，Hook IDs `52C0..52C7`。接口为 `append_hooks`、`dispatch`、`save`、`restore(payload,bytes)`；无需新的 wait。根模块把 dispatch 放在 Full 之前，include 放在 Generic Menu 之后，并使用私有 payload 第 21 节。已有 `5165 name_text` 与 `5161 name_input_result` 复用，不在同一 CALL 安装第二个 hook。

## 26 个直接调用的完整归属

| getst CALL | 原返回地址 | 实际显示 owner 与当前编辑处理 |
| --- | --- | --- |
| `119AB` | `119B0` | Full：角色姓名，完整 profile / culture / sex / name，原 getst 继续 |
| `3E589` | `3E58E` | Full：百科关键词，完整百科及原关键词 prompt |
| `8B4F2` | `8B4F7` | HUD：秘密 debug 的文件／记录查询参数，非物品命名 |
| `8B80D` | `8B812` | HUD：秘密 debug 的文件／记录查询参数，随后 atoi 与文件处理 |
| `FC08A` | `FC08F` | Parent：数量 More，完整父、数量窗口及原数值 prompt |
| `FC4B4` | `FC4B9` | Parent：有上下界的数量 More，保留原 min/max 与当前编辑 |
| `FECD1` | `FECD6` | 日志 Search：完整日志、原当前 Menu 与独立原搜索 prompt |
| `143221` | `143226` | HUD：给 NPC 命名，实际原文本为 “What do you want to call…” / “Type a name” |
| `16FE9D` | `16FEA2` | HUD：秘密 debug 的实际 `?>` 命令提示 |
| `170187` | `17018C` | HUD：play 参数；保留原内部英文参数与动作 |
| `17064E` | `170653` | HUD：原 debug 条件分支参数 |
| `172E57` | `172E5C` | HUD：原 debug 参数 |
| `1754C2` | `1754C7` | HUD：目标选择返回后的 mc 数字参数 |
| `1776A1` | `1776A6` | HUD：group number 参数 |
| `177801` | `177806` | HUD：另一目标选择后的 mc 参数 |
| `1795C7` | `1795CC` | HUD：原 debug 参数 |
| `17AF18` | `17AF1D` | HUD：teleport 第一参数 |
| `17AF31` | `17AF36` | HUD：teleport 第二参数；两次 getst 间无新 F6510，不能丢第一值及原光标间隔 |
| `17B20C` | `17B211` | HUD：month change 参数 |
| `17B564` | `17B569` | HUD：pass days 参数 |
| `17B602` | `17B607` | HUD：原 debug 参数 |
| `17B651` | `17B656` | HUD：第一字段，之后还有新 F6510 提示 |
| `17B692` | `17B697` | HUD：第二字段；原 `17B683 -> F6510` 只滚动追加，不能把第一字段当清屏丢弃 |
| `17B7A7` | `17B7AC` | HUD：items 参数 |
| `17BDFA` | `17BDFF` | HUD：原 debug 参数 |
| `17C7E2` | `17C7E7` | HUD：原 yes/no 真分支后数字参数，须保留实际 Yes echo 及其原生 endpoint |

这不是新增 debug 翻译范围。现有 `direct_dispatch.zh-CN.tsv` 已包含传送、月份、天数、群体编号、数量等部分提示，现有 direct / format 表也已有 NPC 命名提示；原未接汉化的英文诊断仍按其原文构造。所有参数值、atoi、查询、文件读写及选项动作仍由真实游戏调用继续执行。

`143221` 的父归属不是凭 NPC 字样判断：`1431D0` 唯一 caller 为 `143D40`，所属 `143340` 唯一 caller 为 `146E86`。该分支在 `146E48..146E8B` 返回，早于 `146ED3` 的业务聊天分支及 `146F57 -> 1342C0`。因此当前命名 getst 后方是 HUD。

`8B4F2/8B80D` 的唯一外部调用为秘密 debug 分支 `178A3F/178A5A`，其命令来源由 `16FE91 -> F6510` 的真实 `?>` 提示与 `16FE9D` 输入支配。`8B4A2..8B4B8` 把 `67D2F0` 置 1 包围 `16E470`；原 `FA7B0` 在 `FA7B0/FA7BA` 检查该实际字段后直接跳 `FA85B` 返回，所以 progress 不绘字、不推进文字游标。`16E470` 在 `16E4C7..16ED63` 置 `518F4F2=1`，原 F6510 的 `F65A1` 直接退出，既不追加也不清消息 panel；末尾 `16EDCB -> 16DDD0(ESC)` 不走只在 mode=1 的 `16E0FF` saved 消息。相关原生副作用没有清除已有 canonical prompt，也不重建 FA33F 消息 panel。没有补造空提示或空背景。

## 输入值随真正消息记录构造

每次普通 getst 在原 `10F5C5` 捕获实际 Root、当前 canonical FlowHandle、最后一个真实 `Record.identity`、原 ECX color 与 EDX byte capacity；该原输入字段与这条已接受消息关联。`5165` 观察当前真实输入值，只有最新完整值保留；`10F924` 的原返回边界把该完整值记为已结束字段。空字段与取消前实际显示的字段同样保留，内部返回 buffer、Escape 和 Enter 行为不被改写。

Flow 每次 append 都会产生新的 immutable handle，但原旧消息和字段像素仍可见。因此 handle 变化只更新真实来源身份，绝不当作新提示清屏。字段按消息 `Record.identity` 保存。`native_message_flow::Services.completed` 在完整 `consume` 成功、确认没有真实中途 pagination target 之后调用 `after_message(handle,record)`；该字段执行完整原 getst 纯构造，然后才消费下一条原 F6510 消息。下一条原 `F6020` 自己滚动已经绘入的字段像素。没有在页面完成后统一叠加字段，也没有保存输出行或绘制序列。

原 `F6020` 的 `F6069` 读取 panel 与字体行高，`F6093` 复制原 native viewport，`F6112` 只清底行，静态上确实不是清整个消息 panel。这解释了为何 `17B651 -> 17B683 -> 17B692` 必须保留第一字段。字段退休跟随真实 current canonical records 的退休与 clear；Root 退役后回收整个语义 owner。

对缓存 consumer 的源码复核：当前 Flow::paint 唯一外部入口为 `native_hud_language::messages`，参数为实际 current source 或真实 `waiting_source`。Scene 保留的冻结 snapshots 没有绘制入口；本修改没有增加 snapshot/Scene 重放路径。真实等待尚未返回时不可能接受后续普通消息，故 waiting source 对应的记录仍属于当前有效输入 source。

`17C7E2` 必经 `FB8A0` 的 true 分支，原 `FBA91..FBAAE` 用实际 completed message cursor 绘入 Yes echo。该接受结果作为其 prompt 的语义标记保存，重建走同一完整原片段，随后原字段构造继续；没有重新询问 yes/no 或重执其业务动作。

第 21 节仅保存 Root、FlowHandle、Record identity、接受的 Yes 结果、完整 UTF-8 输入值、原输入 color/capacity，以及当前逻辑输入值。它不保存 UI 位置、原生帧地址、Mod 地址、输出行、裁剪、像素或绘制贡献。

## 完整原 getst 纯构造与真实编辑续点

已结束字段重新进入完整 `10F5B0` 的原 prologue、原当前原点读取与背景采样。`10F605` 只跳过共享 buffer 的 memset CALL，原 `10F60A ADD ESP,0C` 仍清其三个原参数；`10F60D` 通过 `SUB ESP,12` 桥进入 `10F687`，保留被跳过的第二 memset 所属原 `10F68E ADD ESP,0C` 栈形状。两处共享输入缓冲、初始名字种子、输入 flag 与 IME 不被重新初始化。

既有 `5165` 在原 `10F6AC -> 10E5A0` 借入该已接受完整值。原 `10F6B1` 直接从 showtext 的真实新 native X 读取 ESI，`10F6C6` 在该位置绘入原光标，并非读取当前共享 buffer 的 strlen。原 `10F719` 不取新输入而提供原 Enter 值；`10F71E..10F77F` 继续原本地 scratch 与光标擦除，再经既有 `5404 edit_dispatch` 进入原 `10F924` 平衡 epilogue。`10F930` 的共享输入 flag 清零只在这次纯构造跳过。当前原始编辑 buffer 不被覆盖，先前输入的完整新 endpoint 却由原 UI 正常生成。

当前字段的语言唤醒仍在真实 `5161 / 10F71E` 处理。完整 HUD 和 canonical prompt/前字段重建之后，读取 `native_message_flow::current_state` 的实际新 native cursor；不能抄旧输入原点，因为 Flow::paint 有意恢复调用者一般游标。随后借当前仍活 getst EBP 执行原 `10F5C5..10F60D` setup：原 color/capacity 进入不变，原代码写回自己的输入原点及背景采样。该短入口仍执行 `10F5CD PUSH EDI`，返回桥明确 `POP EDI; RET`，不动真实外层保存的 EBX/ESI。最后恢复原 `-A4/-B8/-AC -> ESI/EDI/EBX`，续接原 `10F6A0`，原真实输入循环重画当前值、光标并呈现。

## 日志搜索完整父及 prompt

`FECD6` 的真实 `[getst.EBP]` 是原 FE2B0 owner EBP；其正文栈为 `(owner & ~7)-D58`。复用 `native_generic_menu_language::history(event)` 完整构造真实当前日志窗口，保留 readCount、lastSlot、total 和游戏自己的 70 条记录。当前 Menu 保留、重新激活并由完整 native paint 构造，选择来自原 `FEBAF` 已写入的真实正文 `+1C`，交原 D0650 重建选择。

独立搜索 prompt 完整执行原 `FEBCB..FECCA`：原填充、command/body、Search caption、原输入 cursor 设置及 MapRGB 都在该片段；它不读取旧 EBP 或旧 ESP 的输入值，只用自己的临时矩形 scratch。桥提供 128 字节原生栈，片段内参数由原 ADD ESP 清理，`FECCA` 平衡返回。真正复制搜索字串、修改 filter 和搜索动作在 `FECD6` 之后，不重执行。原 getst setup 消费这一完整 prompt 的新原点，然后继续同一个编辑等待。

源码完成不代表编译或正式发布。本文件对应批次只做静态实现与交叉审查，构建和交付由根代理统一记录。
