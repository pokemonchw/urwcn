# Windows 中文姓名输入同步

日期：2026-10-19。目标为 Steam Build 25939378 的 Windows x86 `urw.exe`，原文件 SHA-256 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`，首选基址 `0x400000`。下文地址均为 RVA。

本次只读静态反汇编原始 PE，没有启动游戏、注入进程、模拟输入、执行或编写测试、运行产物或添加断言。Windows 输入不是直接搬用 Linux 地址。输入实现为 `modules/adapter/native_name_input.inc`，由主代理接入现有 Adapter；本记录不代替编译及正式发布回执。

## 已确认的编辑边界

本轮输入和字符串原始指令汇总保存在 [Windows 姓名输入反汇编](20261019-windows-chinese-input-disassembly.txt)。工作片段为 `build/analysis/windows-getst.asm`、`windows-key-event.asm`、`windows-string.asm` 和 `windows-showtext.asm`；较早完整 Windows PE 反汇编为 `build/hud-right-all-disassembly.txt`，姓名业务原始片段也见 `docs/evidence/20261019-character-profile-disassembly.txt`。这些都是静态数据。

| RVA | 原始指令和语义 | 同步扩展 |
| --- | --- | --- |
| `119AB → 10F5B0` | `E8 00 DC 0F 00`；ECX 颜色、EDX=12，姓名页的 getst 调用 | 仅该原生调用前后开启/关闭 SDL 文本输入；两个整型状态记录作用域及真实提交事件，交由既有模块状态交接。 |
| `D1F70..D1F7F` | 将 SDL_TEXTINPUT.text 从 `5F55604` 复制到 `5F549B8` | 原生仍完整接收并保存 SDL 事件。 |
| `D1F81` | `FF 15 [image+18C238]` 为 SDL_StopTextInput，后续只映射首字节 | 姓名作用域内跳到 `D2083` 的原生 -2 返回，保留完整事件字符串。`D3C0F..D3C17` 确认 getkey 对 -2 直接返回，不读取未写入的 keysym。 |
| `D1C6E/D1CF0` | 同一原生 StopTextInput IAT 调用，处理 Ctrl/Alt | 姓名作用域内仅跨过这六字节调用；其他输入仍重放原调用。 |
| `10F77F` | `83 FB 08 0F 85 86 00 00 00`，旧下划线已经由原生 FillRect 擦除 | 有真实提交时按完整 UTF-8 标量追加到原生 `A49B9A8`；容量来自 getst 原局部 `EBP-B4`。保留12字节上限；不能放入的完整字符不追加。之后进入 `10F8B7` 的原生颜色/坐标恢复及重绘。没有构造按键或投递 SDL 事件。 |
| `10F7FB` | `88 81 [image+A49B9A8]`；原生已确认非空并擦除旧文字 | 将末个完整 UTF-8 字符起点写 NUL，旧单字节姓名仍按一字节删除。 |
| `10F65C/10F7A7/10F8F5` | `8D 04 CD 05 00 00 00` 为原 `strlen*8+5` | 仅在姓名作用域内替换为同一字体的完整字符串宽度+原生5像素边距；原生 x/y/高度/背景色/FillRect 生命周期保留。 |
| `10F6C6 → 10E5A0` | 原生下划线绘制调用，三栈参数 | 从该次原生调用 ECX/EDX 借用光标坐标，经实际 SDL renderer 逻辑/输出/窗口变换设置系统候选区域；不保存 UI 几何。 |
| `D3E00` | `0F B6 86 [image+5F54BC0]` 为 StrUpr 字符读取 | 遇完整 UTF-8 标量时跳过原单字节 toupper/北欧字符重映射，继续原循环。 |
| `D408E` | `0F B6 C1 05 7C FF FF FF` 为 StrLwr 的 MOVZX EAX,CL 与 ADD EAX,-0x84，原 tolower 调用及其栈参数清理已完成，尚未写回字符串 | 从仍未改写的原缓冲识别完整 UTF-8 标量，跨过后续单字节重映射/写回，继续 `D40B8` 原循环；ASCII/原单字节重放这8字节，保留原 tolower 分支。 |

Enter、Escape、TAB 与 `*` 仍由原编辑器处理。真实文本事件恰为 `*` 时进入原随机姓名分支；没有合成动作。原生业务仍检查最少3字节及空格、点、逗号、斜杠、反斜杠、下划线、&、+，以及原文件夹重名分支。常用汉字每字3字节，最多4字；四字节标量最多3字，混输共用12字节。

Windows 使用本机已有 SDL2 的系统输入法 UI，通过 `SDL_IME_SHOW_UI=1` 显示系统候选/组合组件；Mod 不绘制预编辑框。[SDL2 官方提示项](https://wiki.libsdl.org/SDL2/SDL_HINT_IME_SHOW_UI) 确认其默认关闭；[SDL2 2.30.0 Windows 实现](https://github.com/libsdl-org/SDL/blob/release-2.30.0/src/video/windows/SDL_windowskeyboard.c) 的 `WIN_ShouldShowNativeUI` 消费该设置，`WIN_SetTextInputRect` 调用系统组合与候选定位接口。[SDL_TEXTINPUT 契约](https://wiki.libsdl.org/SDL2/SDL_TextInputEvent) 保证事件只含完整 UTF-8 标量。实际系统输入法交互未经运行验收。

## 显示编码与原生所有权

`10E5A0` 将整串复制到 `EBP-130`，`10E5D2` 是复制结束后的 `LEA ECX,[EBP-130]`；`10E260` 与 `10E3E0` 分别在 `10E29D/10E43D` 的 `LEA ECX,[EBP-138]` 前完成复制。三个六字节 LEA 都是完整、位置无关指令。这里将实际 UTF-8 转为现有 Layout 服务的两字节显示传输编码，早于原 `C4/E4/F6 → 8E/84/94` 循环，避免汉字 E4 首字节被改写。原生姓名及存档没有显示 token。

helper `display()` 同时保留既有 token、转换完整 UTF-8，并显式处理原生单字节 Nordic 字符；`measure()` 使用同一显示转换和字体度量。公共软件/renderer 叶子及 showtext 光标推进由主代理接入这些已有传输字符串，不得仅将 UTF-8 字节传给原 ASCII 字形循环。字形在确认的组件绘制调用中同步提交，背景、目标、选择、编辑循环及缓存仍由游戏管理。

## Windows 路径差异和容量证据

Linux 最终路径借用 UTF-8；Windows 使用窄 CRT `_findfirst64i32/_mkdir/fopen`，本轮不补造 UTF-8 ACP 或宽字符路径约定，而保留原 `StrUnicode(D3EF0)` 的 ASCII `0xXX` 编码。`D3F63..D3FF3` 确认每个>=0x80的原字节格式化为4个ASCII字节，普通ASCII字节保留。

`11B8D..11B9B` 将 `SaveFile(image+217A78)` 的原生64字节清零；后一字段位于 `217AB8`，相隔64字节。`11B9E → D3DB0` 为最终 StrUpr，结果复制到原 `EBP-808`。`11BBD push 0x20` 的长度值跨过 `11BC5 → D3EF0`，然后在 `11BCA/11BCB/11BD0` 成为原 `strncpy(SaveFile,encoded,32)` 的第三参数。

本轮只对该最终路径调用中的实际 UTF-8 姓名，把既有栈上复制上限设为48；12原字节即使全部需 `0xXX` 编码也最多48 ASCII字节，仍小于已经清零的64字节槽。ASCII和原单字节姓名保留原32字节上限。之前 `11B59` 的8字节临时分支仍会在 `11B8D` 被清空，没有把它误当作最终路径，也没有扩张 Plr 字段。

后续 `12CDB` 将同一 SaveFile 交给 `_mkdir`；`10BD0:10BFE..10C10` 将完整目录名复制到 `CharacterFile(image+A383C10)`，后一缓冲 `A383C90` 与它相隔128字节。`1C550:1C570..1C581` 同样从 SaveFile 完整复制到 `image+27CEB4`，用于原生角色文件路径。动态路径格式化采用原1024字节临时串；新增最多48字节ASCII目录名不引入显示token或系统代码页解释。载入流程仍枚举实际目录并保存原目录名；保存/加载姓名仍对原 `Plr(image+A32A6E8)` 的 `0x1654` 字节数据直接 fwrite/fread（`16CCF1..16CD03` 等原始调用），姓名的13字节字段和文化字段 `A32A6F5` 未改。

因此 Windows 与 Linux 使用相同UTF-8姓名内容和输入容量，但保留各平台已经确认的路径约定；本轮不宣称已经迁移Linux存档目录。

## 状态和待确认边界

源码提供输入、编辑、大小写、候选区域和路径长度扩展；模块接线、公共绘字/度量接线、编译及正式发布分别由主代理记录。当前已变暗文化/性别面板的纯重建边界仍按旧证据待确认，姓名输入扩展没有重放那些业务函数。没有声称已经运行验收系统候选窗、输入或存档读写。

2026-10-19 本轮静态复查：初版 `native_name_input.inc` 的 lowercase Hook 覆盖 `D4082` 五字节（包含 `PUSH EAX`），违背 SDK 的 inline replay 不调整 ESP 约定。已改到以上 `D408E` 八字节边界；没有改写 ESP，也没有替代原生 ASCII/旧单字节 tolower 行为。D407C 的函数指针装载仅首轮执行，后续原 `D40CB` 直接回到 D4082，故不能把 D407C 当作每字符入口。本次源码已整改，后续编译和正式发布由主代理记录；该问题不是已定位的 Adapter 初始化失败原因。两个 include 的 HookSpec 原字节、长度、绝对操作数与静态 PE 相符，姓名初始化使用的7个SDL导出也均存在于游戏的SDL2.dll导出表。
