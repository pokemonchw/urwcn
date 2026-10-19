# MessageFlow 的共同源、原生视口与等待帧

本文件对应当前 `native_message_source.*`、`native_message_flow.*`、`windows_messages.inc` 与 `windows_message_display.inc`。仅静态读取 PE 和源码，没有运行游戏、输入模拟、测试或编译。原始逐指令证据见 `settlement-message-native-disassembly.txt`、`hud-right-static-rebuild-disassembly.txt`。地址为 RVA；PE 基址为 `400000`。

## 中性生产源

`native_message_source::Text` 保存真实英文 producer 的表达式：明确资源 component/key、实际 typed 数值、模板占位、嵌套资源、原始拼接、实际 replace 和菜单 separator 操作。两语言普通构建都登记。注册表身份是实际 native buffer 地址加该次原英文值；地址复用不会把旧结果当新结果。中文 catalog 输出只在当前 display consumer 投影，不放回 source AST、原英文 queue、日志或内部动作值。

`F65E8` 在原声音提取前绑定实际完整 producer 图与实际展开后的英文输入。原 `F65F2..F67C1` 继续执行声音字段提取、大小写、重复判定及最后英文登记。只有真正被接受的 `F67C3` append 一个共享 MessageFlow record。正常 `F6A45` 和 locale 消费该同一 record 的 AST；英文仍用原函数已处理的实际英文正文。

三个扩大后的 native working buffers 是同步 Host allocation 中的 source/word/history 暂存区。游戏原文字循环负责写入、换行、字词复制和索引；这不是可遍历重画的文字贡献序列。保留原有 capacity 与十五个 operand hook。

## 源窗口由完整原生滚动生命周期退役

`5909/FA33F` 在真实 `116270` consumer 之前建立这个 owner 的完整 `PanelSource`：实际 ECX/EDX、五个 native 参数、原 title 和已确认的 PanelStyle。普通路径从同一 canonical source 调完整 `116270`；locale `Flow.paint` 也先调用该同一背景 constructor，再消费 records。`FA347` 清屏完成协议沿用这份实际 source。这样即使 Scene parent 是旧 frozen Flow，而 child 是后来实际 call 的 live source，后者也先由自己的原生背景清构，不会在旧文字上重复 scroll。没有依赖 Root 恰好空白或另做像素擦字。

`append` 不再创建无背景的缺省 rect source。实际共同 Panel constructor 先建立 owner 是它的 native lifecycle 契约。完整构建、绘制输入及样式都来自该真实 constructor，不根据“当前缺什么”拼造一个 Panel。

`F6020` 的原始指令定义了消息区域中的整行搬移：

| 地址 | 原生输入/行为 |
| --- | --- |
| `F6030..F6053` | 从 `1E6ABC` 取得当前 native lineHeight。 |
| `F6057..F606B` | source.y 为 rect.y + 5 + lineHeight，destination.y 为 rect.y + 5。 |
| `F606E..F607B` | source/destination 高度为 rect.height - lineHeight - 10。 |
| `F6093` | 在游戏自己的目标上执行完整上移 blit。 |
| `F6112` | 原函数填充新底行。 |
| `F6134` | message.x 重新取 rect.x + 5。 |
| `F6151..F6164` | message.y 重新取 rect.y + rect.height - lineHeight - 5。 |

共同组件在 `F6164` 扩展这次完整 native scroll 的 source 生命周期：累计实际 lineHeight，并标识当前实际 message record 的最后 native line phase。原生函数完成该 record 后标为 complete。最后整行又经过 rect.height - 10 的原生滚动距离时，整个 record 已退出该原 copy 内区，后续 append 退役这个完整 record。没有固定 N、文字坐标表、逐字/逐词贡献、surface 扫描或像素比较。新语种重建时同一原函数重新生成这些生命周期；只将真正当前 source 的结果交回实际 InputOwner。

因此 source 列表受当前原生视口和至多一条尚未完成的实际输入 record 限定，不是全会话日志。原 F6510 每条英文输入的复制上限为 `3FC`；单条仍保有完整中性 producer，以便原生函数重新排版。

保留的第一条可以在原视口只剩部分行。重建仍从它的完整中性 record 开始，由每次原 `F6020` 从底行锚点重新排版，再由后续原滚动剔除上部内容。源没有保存旧 message.x/y：`PaginationSeed` 只保留原 `F5B00` caller cursor/color/counter。第一处词绘制之前必经完整 `F6020`；旧英文的消息绘制坐标不能作为新布局起点。第一次分页若在 `F6A38`，则尚未进入该 record 的第一处 scroll/word consumer，组件正确停在已有 source 前缀。

退役是这个共同 native source owner 的语义下界：已经由实际原生滚动退役的旧消息不因另一语言较短而从游戏历史复活。两语言的普通显示均消费同一队列，locale 消费当前仍活着的中性 records。保留的整条 record 可由新语言产生不同的行数与分页数，原生函数继续决定其当前视口。`FA33F` 完整原 panel 清除消息矩形，随后真实 `FA347` counter 清零建立新的空 owner/source。Scene root 退休也释放其 owner；没有页面 redraw callback。

分页 counter 的外部控制输入也来自实际写入事件，不能由“值与上次相同”推断没有写入。原 PE 中该绝对字段的直接 byte MOV 写入共 110 处；`native_message_counter_writers.inc` 保留 109 处原指令的 site/opcode/modrm/立即数，另一个 `FA347` 已由完整清屏协议拥有。`5940..59AC` 只是同一原字段的 source generation 观察，不改原值或动作；BL/CL 写入仍由原指令执行。`F5B3D/F5BAE/F5C2B` 在实际 F6510 InputOwner 内是自身分页更新，其余普通写入（包括原值不变的显式 0）均是明确输入。Scene/Flow 同步 materialization 不制造普通输入。下次 accepted record 据实际 generation 消费原控制输入，或继续该共同 owner 当前语言的原生 counter；没有猜测同值写入、默认重置或补救分支。

## 完整 F6510 的明确 paint phase

| Hook | 普通语义 | 同步 locale paint 语义 |
| --- | --- | --- |
| `5900 / F65C2` | 原 `*` 与普通输入的两个实际分支。 | 使用该 record 的原 accepted English，直接到 `F65E8`，不再次展开资源。 |
| `capture / F65E8` | 绑定真实 producer，然后原声音/大小写/重复代码。 | 绑定同 record AST，跳 `F67C3`，不再次执行业务。 |
| `5901 / F67C3` | append 一条实际 accepted record。 | 不 append，继续原初始局部状态。 |
| `5902 / F67DD` | 原 gradient 分支。 | 实现原 EDI=0 后到 `F6A22`，不重复背景淡变。 |
| `5909 / FA33F` | 真实共同 Panel constructor 建立 owner，并由相同 source 调完整 `116270`。 | Flow 自己消费同一 constructor，不另登记 generic Panel child。 |
| `5903 / F5B7F` | 真正 would-wait 分支进入原缓存、按钮与输入。 | 复用原 native counter 进程，已确认的分页阶段只实施原 counter=0，不进入缓存/输入；到所需真实 phase 时同步结束生成帧。 |
| `5906 / F5C31` | 原 named cache clear。 | 到 `F5C3B`，不破坏普通真实等待所持 cache。 |
| `restore_source / F6D8A` | 原声音、Present、英文日志继续一次。 | 提交已确认的 completed cursor 字段，到 `F6EBB`，不调用声音、RNG、日志或 Present。 |

完整 `F6510` prologue/cookie/epilogue、原文字循环、完整 `F6020`、当前语言原生度量与即时字形消费仍执行。不调用带猜测寄存器的中间 fragment，不把声音或日志函数当重建器。

## 等待的真实 InputOwner

令 P 为 F6510 三个 callee-saved push 后的稳定 SP。`F6A38/F6C4F/F6D11` 都在 CALL 前保留八字节，所以 `waitEBP=P-16`。原 `F5B00` 的字段为：

| 位置 | 真实 native 值 |
| --- | --- |
| `[waitEBP]` | F6510 parent EBP。 |
| `[waitEBP+4]` | 游戏返回相位 `F6A3D`、`F6C54` 或 `F6D16`。 |
| `[waitEBP-20h]` | F5B00 保存的 parent EBX。中途等待时是正文 native index。 |
| `[waitEBP-18h]` | 原 general cursorY。 |
| `[waitEBP+24h]` | parent P+14h native color。初始相位随后由原 `F6A4C` 初始化为零。 |

InputOwner 用实际 record ID 与已经真正确认的 wait ordinal 表示继续语义。新语言的完整原生循环走到同 record 的该实际 would-wait，直接取得它新产生的三种返回相位之一、native index、color 与 native working buffers；这些新结果替换原挂起 frame 的上述槽位。没有恢复旧语言字节偏移。

初始 `F6A3D` 相位尚未开始正文，后续原 `F6A4C` 和 `F6A50` 明确初始化 color/index 为零。因此该相位只安装这两个已确认初始值，不保存生成帧尚未使用的原输入指针；真实等待也不会持有生成 record 的 DLL string 地址。

生成帧只同步地把自己 F5B00 返回地址指向临时 `add ESP,8; jmp F6EBB` bridge，借用完整原 cookie/epilogue 返回。真实挂起 frame 只保存 EXE 返回 RVA。Host allocation 中的新 source/word/history working buffers 转给真实 parent frame；生成帧不再释放这笔贷款。新语种已经完成整个 record 时是 complete variant：真实 frame 返回 `F6D16` 执行原八字节清理，`F6D19` 跳过该次 scroll，`F6D1E` 回 `F6D8A`，声音/日志仍仅由原普通调用继续一次。

`5904/F5C13` 位于原 Space/Esc 处理和 cache restore 之后，向原 EBX/EDI 与 Y 槽提供新 continuation context，然后原 `F5C16..F5C22` 消费。原输入事件没有被模拟、额外消费或替换；原 ESC skip 状态保留。其他页面的 general cursor/color 在 materialization 结束恢复。

这次真实确认同时把该实际 F6510 call 的 canonical live source 重新交回 Scene。原 cache restore 带回的 frozen `ends_at_wait` source 只属于该已完成的等待；原循环继续绘制剩余正文后，活动 Scene 不再错误地停在这个旧 frozen phase。下一次真 wait 的 snapshot 再冻结实际递增后的 ordinal。

Scene cache snapshot 只冻结中性 source 与真实 wait ordinal，保留实际 InputOwner。旧 frozen wait ordinal 不能选择另一个更新的实际等待；它可以重建自己的 source phase，不能把旧分页字段写回真实输入。

以上等待 ABI 已由另一个代理独立逐指令静态复核。当前交付仍需主代理完成总初始化/序列化接线与统一编译；没有运行结论。此前已只剩 surface 像素、尚未由这个共同 owner 捕获的历史正文无法反建为中性 source，本实现没有扫描或补造它们。

## 首次 native owner 的初始化顺序与边界

PE `.data` 的 RVA 为 `1E2000`，raw size `A200`，virtual size `A45FFE8`。`61A8CE4` 和 `4D8F4F2` 位于加载时清零的虚拟尾。消息矩形的直接写入只有 `F598D`（先清零）、`F599C`（从原 rdata `1DD9B0` 复制 `493,398,305,130`）、`F59AE`（large 变体 `498,355,296,170`）；都属于完整原 `F5830`。没有其它消息宽高 writer。

正常启动的直接调用链为 `1807D8→117400`，其中 `117A1B→F5830` 先初始化共同 UI 数据；main 的 `1809E4→125A90` 是菜单/角色选择，退出态 1 之外由 `1809F4→17E4C0` 进入载入。此函数在 `17E86D` 设置 mode `16`、`17E879` 设置消息 suppress=1，`17E8D2→1038B0` 进入完整共同 UI 绘制。`1038CB` 清屏，`1038DE→FA2A0→FA33F` 建立实际消息 Panel，直到 `17E920` 才 suppress=0 并继续世界处理。

另一共同 UI 调用点 `16ED40` 之前的 `16ED36` 设置 mode `21`。`1038C9` 和 `1038DC` 在这个 mode 同时略过整屏清除与 `FA2A0`，是保留已有 UI owner 的 map-only 更新；随后 `16ED63` 恢复 suppress=0。不能把它当作一次缺少 Panel 的新 Root 构造。

`F6510` 自己只有空输入、suppress=1 和重复抑制三类早退，没有 rect/visible/owner gate。因此“矩形非零”不等于已经证明 opaque Panel 构造，不能凭字段初始化编造源。上述正常进入 engine 的共同 UI 链提供实际 constructor；直接在已运行的旧会话中装入此新 source schema，若尚未实际经过 `FA33F`，则既有 pixels 无法恢复原 Panel/source 输入。该迁移/首次接入边界必须由总发布方案明确处理；本代码没有无 owner 背景、unowned fallback 或像素反建分支。代码不代替尚未发生的原生构造，也不声称所有可能的错误/调试业务调用图均已证明在该首次构造之后。

正常加载链的这项静态证据已由主代理接受。它不授权在旧进程中反推一次已经错过的 constructor：即使旧矩形和表面仍在，也没有该次 `FA33F` 的完整源、原样式和当前中性消息窗口。没有携带本 schema 的旧模块状态不能被称为已经完成迁移；兼容状态转交仅适用于实际捕获并序列化了此 source 的实例。此次改造的源码静态交付不等于运行验证、编译完成或正式发布完成。
