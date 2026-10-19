# 2026-10-19 Shift+F10 原生全局输入边界

本记录只涉及输入接入的静态依据。未启动游戏、执行产物、模拟输入或运行测试；没有测试用例、断言、新保护或回退。编译与正式发布状态由本轮交付记录另行记载。

目标为 `D:/program/steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。使用项目已有 `objdump.exe` 只读反汇编。完整 SDL Poll/Wait/Peep IAT 引用及相关函数片段保存在 [反汇编](20261019-language-input-disassembly.txt)。下表均为 RVA，归档反汇编使用首选基址 `0x400000` 的 VA。

## 本轮接入

| Hook ID / RVA | 原指令与读取对象 | 快捷键消费后续点 |
| --- | --- | --- |
| `0x5000 / D1CD4` | `cmp dword ptr [image+5F555F8],300h`，10 字节。普通输入 `D1C00` 的 Poll 与 Wait 成功结果先汇合于此，尚未执行 `D1D16` 的按键解释。 | `D2083`，原生非按键唤醒结果 `-2` 及完整函数 epilogue。 |
| `0x5001 / D26AB` | `mov eax,[image+5F555F8]`，5 字节。动画的 `D25E0` 只在 Poll 返回真实事件后到达。 | `D269B`，原生清 EAX 并返回零；不会进入 `D26DB` 的按键退出与清队列。 |

两个绝对地址操作数按 `image_base + 0x5F555F8` 生成 expected 字节，不能使用首选基址硬编码。两个补丁均无栈调整、相对控制流或被截断的指令。未命中时驻留桥重放原指令，原 CMP 产生自己的 flags；命中时只选择已确认 continuation，不改通用寄存器、事件缓冲或栈。

这些 Hook 使用当前 ABI 1 已有 `HookKind::inline_code` 与驻留 thunk，不重写 SDL 事件 IAT，不替换已经驻留的发布控制桥，也没有业务回调跨 SDL 等待留在栈上。

### 普通输入消费后的原生返回

`D1C00` 没有可用于此处的零返回：若擅自返回零，唯一直接调用者 `D3BF0` 会在 `D3C6E..D3C71` 继续解码未写入的 keysym 局部。不能把这种路径称为 no input。

其既存 `D2083` 路径则先写入返回值 `-2`，再执行当前函数自己的 POP、security-cookie 检查及 EBP epilogue。`D3BF0` 在 `D3C0F..D3C17` 对 `-2` 直接返回，不读取 keysym。该返回本来用于原生 `0x8000` 用户事件；`17CC20` 自身在需要唤醒且没有事件时排入这一事件，证明 `-2` 是既有非按键控制循环语义。Mod 不生成 SDL 事件，仅在实际快捷键已被消费后使用此原生 continuation。

`D3C80` 的 `D3D0A..D3D0D` 对小于 1 的结果回到 `D3D05`，因此关于窗口输入周期可继续。`D1120` 的普通菜单循环也能进入下一次原生输入周期，让各组件已确认的重绘入口处理语言变化；不在 `D1C00` 内继续阻塞并等待另一个用户动作。`D2083` 不修改全局按键/鼠标标记，也不制造按键动作。补充反汇编含唯一直接调用者、完整返回片段及原生唤醒事件构建点。

主菜单的具体无动作链为：`D13C4 → D1866` 搜索原生行键；`CF790` 的 `CF917/CF91D` 已把行 `+C8/+CC` 都置零，`125920` 构建各行时传 `ECX=0`，`CF9BB` 仍只将零写入 `+C8`。因此 `D18A0/D18A4` 的两候选键均不匹配 `-2`，经 `D18C8 → D147D` 保留当前选择，`D1489` 读取尚未提交的零选择标志，`D14E6 → D11CC` 开始下一输入周期。这是已确认主菜单的分支依据，不以未知其他界面的字段外推。设置组件自己的待重绘分支在 `D12B4` 更早处理其原生退出及外层重建，且同时要求本次 `EAX=-2`，不因待重绘状态吞掉真实设置操作。

## 事件字段和按键语义

SDL2 的 [事件定义](https://raw.githubusercontent.com/libsdl-org/SDL/release-2.30.0/include/SDL_events.h) 与 [Keysym 定义](https://raw.githubusercontent.com/libsdl-org/SDL/release-2.30.0/include/SDL_keyboard.h) 给出：type 位于 `+0`，window event 位于 `+12`，key repeat 位于 `+13`，keysym.sym 位于 `+20`，keysym.mod 位于 `+24`。游戏自己的 `D1048` 已按 `byte [ecx+0xD]` 判断 repeat；`D1050` 与 `D1BA9` 按 `0x38` 字节推进事件。`D1D22` 从 `5F5560C` 读 sym，`D1CE0` 从 `5F55610` 读 modifiers，与定义一致。

SDL2 的 [扫描码](https://raw.githubusercontent.com/libsdl-org/SDL/release-2.30.0/include/SDL_scancode.h) 与 [键码和修饰键定义](https://raw.githubusercontent.com/libsdl-org/SDL/release-2.30.0/include/SDL_keycode.h) 给出 F10 为 `0x40000043`，左右 Shift 掩码为 `0x0003`，Ctrl/Alt/GUI 合并为 `0x0FC0`。只接受 Shift 加 F10，锁定键不影响；Ctrl/Alt/GUI 组合不归该快捷键处理。KEYDOWN/KEYUP 为 `0x300/0x301`。

首个非重复按下返回一次 toggle 请求。此后到 F10 抬起为止，重复按下和抬起均由快捷键消费；先松 Shift 不把余下 F10 repeat 交给游戏。游戏已确认的排空及 FlushEvents 会丢弃 KEYUP，因此新的 `repeat=0` 明确开始下一次物理按压并清除上一次 consumed，不能让旧 consumed 无条件吞掉下一次首按。SDL_WINDOWEVENT 的焦点丢失值 `13` 清除该次按压状态，焦点事件继续原生处理。`D1EA9/D1EAE` 对 gain/lost 的 `12/13` 比较提供游戏静态依据。按压状态只有一个可序列化 `u32`，供 Adapter 现有发布状态交接保存；没有按键轮询线程或窗口位置、文字、像素记录。

## 全 EXE 输入清点

全代码段对 Poll/Wait/Peep IAT 的引用已读完，不能把每个 Poll 都称为动作消费者。

- `D1C00` 为普通原生事件解释器；其附属 PEEKEVENT 只查看下一项是否为 TEXTINPUT，不从队列移除快捷键。命中快捷键在该解释之前被消费。
- `D25E0` 为动画非阻塞按键检查，独立于 `D1C00`，已单独接入。
- `D1B40` 以 GETEVENT 提取再 PushEvent，是原生重新排队路径，保持完整原意，不在逐项重排时切换语言。F10 仍排回队列，之后到达 `D1CD4` 或 `D26AB` 才按本次实际输入消费。
- `D0FC0` 的 `D1011` 为 PEEKEVENT；它只统计/整理队列中的 keyup、keydown 和 repeat，不是一次用户动作消费。不得在 peek 时切换，避免同一事件再次被 Poll/Wait 获取时二次切换。
- Poll 调用 `5757B`、`D0F9B`、`D1ABB`、`D1B1B`、`D32F5`、`D3CE6`、`17CBEB`、`180AB5`、`180CE7` 均为直到队列为空的排空循环，不读取事件并执行游戏动作。这些原生丢弃旧输入的路径保持原意，不把已丢弃输入重新解释为快捷键。

本轮输入全局指游戏内上述实际输入消费路径，不登记 Windows 桌面级系统热键。语言开关属于显示业务，不应复用 `src/loader/host.cpp` 的事务总门闩 `enabled`，否则会连作用域与原生密度扩展一起关闭。

### 重新排队阶段不能提前消费后续按键

[原生事件消费者反编译](credits-ghidra.c) 第 1283 行起的 NUMPAD1..9 分支表明：当前按键已经保存在 `DAT_063555F8`，随后调用 `D1B40` 整理队列中的后续事件，再由 `D2139` 返回当前数字小键盘按键。`D1B90` 此时处理的是将来才会消费的队列项，并非当前动作。

如果在 `D1B90` 提前响应后面的 F10 并标记设置重建，当前 NUMPAD 动作返回 `D1120` 时就可能因待重建状态被丢弃。最终实现因此移除这处未发布接入，只保留普通和动画的两个实际消费 Hook。原生重排顺序及当前 NUMPAD 动作不变；设置重建另以本次非按键唤醒值 `-2` 作为必要条件。归档反汇编仍保留 `D1B40`，用于说明为何该边界不应接入，不代表最终补丁包含第三个 Hook。

## 原生缓存关联与历史文档

`docs/hot-reload.md:3` 已标明历史协议。其显示切换、按键重复及失焦要求仍有参考意义；其中 ABI 2/3、DisplayPlan、Footer 交接和在 Present 合成等方案已退役，不能当作本次实现依据。

事件消费只通知显示语言改变。它不保存或重放文本，不拥有原生表面/纹理缓存。语言变化后的即时绘制必须回到各已确认组件的原生构建与绘制生命周期。`modules/adapter/module.cpp` 对活动主菜单的重建使用已确认片段 `125BA3..125BE1`；设置、关于及开场分别使用其已确认的显示生命周期，不能从主菜单片段外推任意窗口重建。各组件缓存的具体生效边界由相应静态依据和本轮显示交付记录说明。
