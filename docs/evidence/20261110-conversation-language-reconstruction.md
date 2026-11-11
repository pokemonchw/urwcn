# NPC 对话原生构造与语言生命周期（3.89.1）

只读依据是安装目录原 `urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`，完整静态反汇编及按真实函数入口定址的 objdump。本文地址均为 RVA。没有运行游戏、产物或测试，没有创建测试或断言。

实现为 `modules/adapter/native_conversation_language.inc`，Hook IDs `5240..5264`。接口为 `append_hooks`、`dispatch`、`rebuild`、`wait`、`owns(RootRevision)`、`save`、`restore(payload,bytes)`。文件放在 `native_parent_cache_language.inc` 之后；根模块统一接 hook/dispatch、D3C80 真实内部等待 tick，以及私有 UI payload 第 20 节。它不持有宿主帧或 Mod 代码地址。

## 真正的对话语义 owner

完整 NPC 前景由原 `1342C0` 创建，`1342E5 -> 1127C0` 的原背景是 `bg-heritage.jpg`，原目标为 800×600。该真实背景调用成功返回后才建立语义 owner，使用其原生 Root lifetime，而不是从图像或 Scene 子组件猜测。

每个 owner 只保存已接受的 actor ID 和两个 speaker 的逻辑段落，每段保留已接受的完整句子输入。`1339B0` 是 NPC 整句入口，`134350` 是玩家整句入口；它们在进入 word-flow 前收到实际 ECX 字符串。原生输入允许单字节 Nordic 字母及 UTF-8 姓名，语义句子按原 parser 的真实字节替换规则解码为 UTF-8。没有保存输出行、坐标、裁剪、样式、字形、像素或绘制调用。

原完整 `134150` 清 NPC 列，`134200` 清玩家列；在它们真正的 `116270` Panel 构造 CALL 前清对应语义段落。原 word-flow 结束时先对末尾 word 做 fit，再按实际代码增加一个 8 单位的单词间隔。因此保留每个已接受整句的语义边界，不能用 ASCII 空格拼接成一次 flow：拼接会把该空格计入前一 word-fit，使临界位置提前换行。每句仍由原完整 flow 消费。NPC 空输入原直接退出，不接受该边界；玩家空输入仍进入 `134481` 空 draw 和 `1344BA` 的原 +8，因此保留已接受空句。未发生该 speaker 输入时不调用 flow，避免凭空移动原重置游标。

NPC 四处显式逻辑段落边界为 `13867B`、`138D5B`、`138E32`、`140C21`。它们原生执行同样的“当前 X 是否在左原点”比较，必要时原 Y 加一行并复位原 X。正常流程记录逻辑段落分隔；重建中直接进入完整原片段 `13867B..138695`，由原比较和原指令决定是否换行，随后通过 `5264` 平衡返回。Mod 不保存比较结果、原点、行高或输出行槽。

对原四个 speaker 游标字段所有立即数复位写入的静态 census 已闭合：NPC 的 `134336/13520C/135A9E/1368E8/136CBF/138411/138485/13B770/13C7CD/13DDD4/13DF84/13E2AA/140535/140567/1405A0/1413E5/1421A3/1422DB/14232D/142367/14282E` 均由对应完整 `134150` 清列支配；玩家的 `13B83A/13DDB0/13E28E/1421BC/142854` 均由完整 `134200` 清列支配。另四个非初始复位就是上述显式段落边界。不存在以旧源从原点再次绘入的独立 cursor-reset 路径。

`owns(root)` 只查询该真实构造建立的语义 owner。`prune` 按 `native_root_component::revisions()` 的真实资源退役结果回收语义记录，不扫描或遍历 Scene 绘制贡献。

## 完整重建保持同一逻辑 Root

`rebuild()` 调用原完整 `1342C0`。在同步构造阶段，只有它自己的 `1342E5` 原背景 CALL 改为既有 `native_root_component::paint_background(originalRoot)`，重新进入同一个完整 `1127C0` 工厂并保持该 Root；原重复 CALL 跳过，原 caller 的 `ADD ESP,14h` 清理仍执行。后续前景构造一开始就处在同一 owner，F6510 等真实消息资源无需跨 Root 搬迁，也不新建消息回放表。

其原完整调用树为：

| 原调用 | 构造内容 |
| --- | --- |
| `1342E5 -> 1127C0` | 同一个原生背景 owner |
| `1342F8 -> AD4F0`、`134307`、`134312 -> F8F80` | NPC 原始名字、格式与完整标题带 |
| `134317 -> 134200` | 玩家 Panel 与 portrait |
| `13431C -> 134150` | NPC Panel 与 portrait |
| `134330` | NPC Panel 与原原点重置 |
| `1421B7..1421D5` | 玩家 Panel 与原原点重置；只在本次构造跳过 `1421D0 -> 134B60` 业务 |
| `1339B0`、`134350` | 两个 speaker 的完整语义句子交给各自原 word-flow |
| `13867B..138695` | 每个真实段落之间的完整原条件换行 |

所有 Panel、portrait 位置和文字游标重置都执行原指令，没有把它们复制成 Mod 坐标表。完整 NPC factory 本身的标题和背景仍在原调用中消费。

actor 从该 owner 的已接受 ID 同步借入原三个读操作：`1342EA` 与 `13415B` 的 MOV ECX，以及 `13419E` 的 IMUL ECX。没有把当前游戏全局 actor 字段写回去，也不重做 `146F0F..146F33` 的 568h NPC 业务记录复制。

原 `AD5A7 -> AD4B0` 会修改 NPC 名字字段和 `+1DCh` 标志，构造期间跳过这项已发生的业务规范化；`AD4F0..ADB6A` 其余代码只做自己的 ring 格式 scratch、大小写和格式选择。原 `13416A/134238` 强制 flip=0 的写入只在同步构造期间跳过，原保存/恢复 flip 的 UI 生命周期继续；原 `133AFD` Delay 与 `133B08` Present 也只在构造期间跳过。普通原生运行的 Delay(3) 保持。

不重执行 `134B60/134C70` 的对话业务生成、随机选择或选项动作。实际 D1120 菜单由各自真实输入 owner 保持。2026-11-11 完整反编译更正：此前把 `134790` 一并列为业务生成不准确；它是已接受交易状态的纯侧栏构造，现按 `141F70` 原条件在完整重建时调用，详见 [全部对话文本记录](20261111-conversation-all-text.md)。

## UTF-8 姓名进入原 word-flow

原 NPC 整句指针保存在 `EBP-80Ch`，玩家整句指针保存在 `EBP-D0h`。在原单字符格式调用之后的 `133A16/1343A6`，从这一真实原输入加原 EBX 读取完整 UTF-8 scalar，编码到该原生 character scratch，再使 EBX 加 `span-1`，原循环的 INC EBX 完成该字符推进。没有长期借出 Mod 字符串，也不根据 transport 的低字节猜 Unicode。

宽度扩展只替换原度量操作数：

| 原范围 | 扩展边界 |
| --- | --- |
| NPC 普通 / 末尾 word-fit | `133A8F/133B3F` 的 MOV Y＋LEA 宽度；原 CMP 与 wrap 分支保留在 hook 外 |
| 玩家 word-fit | `13440F` 的 MOV Y＋LEA 宽度；原 CMP 与 wrap 分支保留在 hook 外 |
| NPC 普通 / 末尾前进 | `133ADD/133B88`，使用实际 word scratch 度量，原 store 与尾部间隔继续 |
| 玩家普通 / 末尾前进 | `134457/1344AD`，使用实际 word scratch 度量，原 clear/store/尾部间隔继续 |

原右边界比较立即数仍位于游戏指令中，Mod 没有复制它们作窗口坐标。每次度量都来自该原 word scratch；四个原 `10E5A0` CALL `133AC0/133B70/13443D/134495` 根据完整实际输入建立 Unicode glyph/metrics scope，文字在这些原组件调用里立即提交。

NPC 标题与双方 Panel 名字在对应完整原显示 CALL 转为可消费的显示编码，同时保留原内部姓名。emote 的 `134E75 -> 10E910` 是完整原 centered-text 调用，真实四个参数为 width、text、color、outline。`134E44 PUSH 1` 的 outline 在中间 SDL MapRGB 的四参数清理后仍留在栈上，故 Hook 元数据保留四参数；Unicode 显示使用 `Scope::hud_centered` 与真实第四参数 outline，不能用默认 outline=0 的 paragraph scope 改写原风格与度量。

## emote 当前等待与两个 named 父恢复

`134D90` 保存 `emotescr`，完整原 Panel、消息和 Continue 后在 `134E91 -> D3C80` 等待。消息格式已完成，真实 owner 的 `EBP-408h` 保持完整已接受英文/UTF-8 输入；mode=0 的原复制循环已经推进 ESI，不能把等待时的 ESI 猜成原字符串。

`wait` 在 D3C80 实际内部 tick 识别 caller `134E96`。先激活真实 named 父 Root 并完整构造其对话页，再同原 name/rect 保存。借仍活 owner EBP 执行 `134DC7` 起的完整原 Panel；`134DFC` 在同步构造中清理该原 36 字节参数后跳到 `134E3F`，复用已接受的原消息 scratch，继续原完整 `10E910` centered text 和 Continue；新 D3C80 不执行，`134E96` 平衡返回。本次显示完成后继续原来的真实等待，不执行新输入。

`native_parent_cache_language` 的 `134E9B` 和 `14281A` 两个真实 named restore 分别属于 emotescr/chatopt 的 NPC 父，明确调用同一个完整 conversation 构造和共同 named 协议，不能裸 HUD。其它已确认 HUD/NPC 二类的共享业务父由 `game_parent()` 按真实 Root owner 选择；缺失逻辑源不变成默认空页或像素/绘制序列补画。

持久化第 20 节仅包含 root ID、actor ID、两个 speaker 的逻辑段落与段内已接受 UTF-8 完整句子；零句与一个空玩家句保持区别。重建 phase、借用指针、真实等待帧、原生 scratch 及调用桥均不持久化。源码、产物编译和正式发布状态必须分别记录。
