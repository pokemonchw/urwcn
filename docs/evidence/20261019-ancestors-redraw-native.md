# 先祖列表的原生重绘 continuation

日期：2026-10-19。对象为 UnReal World 3.89 / Steam Build 25939378；原 EXE SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。本文地址使用 RVA，引用反汇编用首选基址 `0x400000` 显示 VA。依据为保存的原始反汇编、Ghidra 输出和源码的静态阅读；未启动游戏、注入、模拟输入、运行测试、创建测试或断言。本记录不宣称编译、正式发布或画面验收。

## 适用原生分支与输入边界

`125E04 → DE990` 使用 `ECX=-1` 进入列表，`DE9B4` 将该参数保存到 ESI。另一条 `ECX!=-1` 死亡流程不纳入此次重建。列表每次在 `DF160` 原生呈现后，经 `DF169..DF17C` 恢复原生选择，随后由未修改的 `DF182 → D1120` 等待输入；返回地址为 `DF187`。普通 `-1` 只在 `DF18C` 回到输入，不重新构建页面。

沿用设置重绘的 `D12B4` 输入返回边界：仅当先祖重绘 pending 存在、EAX 是原生非按键返回 `-2`，并且真实 D1120 帧 `[EBP+4] == image_base+DF187` 时，设置先祖 rebuilding 并继续到 `D19B3`。此原生 epilogue 清 `menu_input_active`、返回 `-1`、恢复寄存器和正常平衡 D1120 栈；不经会改输入模式的 `D19A9`。没有丢弃真实按键动作，没有构造菜单动作或保持业务模块调用跨越输入等待。

证据：[列表反汇编](ancestors-disassembly.txt) `DF169..DF1BA`；[既有输入返回反汇编](20261019-language-setup-input-disassembly.txt) `D12B4`、`D19B3..D19D0`；[语言输入记录](20261019-language-input-static.md)。`DF182` 必须继续不被 CALL Hook 替换，才能保留该精确原生返回地址。

## 在现有列表帧内重画

`modules/adapter/native_language_redraw.cpp` 新增以下四处边界。直接在尚存的 DE990 原生帧内继续，不调用依赖外层 EBP 的 `native_fragment`，不保存原生 frame 指针或页内容。

| Hook ID | RVA | 原字节 / 原指令 | 本次重建行为 |
| --- | --- | --- | --- |
| `5103` | `DF187` | `8B D0 83 FA FF`，`MOV EDX,EAX; CMP EDX,-1` | 将原生当前选择保存到已有 `[EBP-5AC]`，令 ESI=-1，继续 `DE9DE` |
| `5104` | `DEB84` | `66 0F 6E 05 BC 6A 5E 00`，`MOVD XMM0,[5E6ABC]` | 从已有 `[EBP-5A4]` 读取原生容量到 EAX，继续 `DEBB1` |
| `5105` | `DEBC3` | `E8 A8 EE FF FF`，`CALL DDA70` | 仅此次重建跳过首次索引加载 |
| `5106` | `DEBC8` | `8B 15 A0 AC 35 06`，`MOV EDX,[635ACA0]` | 清本次 rebuilding，继续 `DEC33` |

`DEB84` 的绝对地址操作数按 `image_base+1E6ABC` 写入 expected bytes；`DEBC8` 按 `image_base+5F5ACA0` 写入。两处都没有相对控制流或 ESP 调整；正常路径原样重放完整指令。`DEBC3` 使用现有 CALL hook 和 `skip_original`，不把其相对 CALL 字节拿来 inline replay。`DEA21` 的 `CMP` 后紧接相对 `JE`，因此没有将此处当作 inline replay 入口。

`DE9DE..DEA1C` 执行本页原有 `10B9F0` 清主面、`1127C0` 背景绘制、`1157B0` 标题和 `DD380` 底部面板。已保存的索引数组、页偏移、容量与间距 locals 均不经过首次清零。ESI=-1 使标题文本识别和 `DEA21` 的列表分支成立；后续 `DEC33` 原样将 ESI 重新装载为 SDL_MapRGB 的原生入口。

`10B9F0` 的 [Ghidra 记录](intro-ghidra.c) `clear_native_frame` 确认它使用原生全屏矩形清主面并可能上传、呈现；它不接收新的业务输入。因这里保留游戏自己的清屏/呈现，不能宣称重建没有中间黑帧或闪烁。

## 缓存、排序、分页与选择

`DEB84..DEBB0` 的首次容量和间距计算被跳过。`DEBB1..DEBBE` 仍在原生调用点以其原缓存名字指针 `1A6638` 和参数 0 调用 `10C540`；`DEBB8` 写回的是读取到的原容量。本次实际新绘出的背景、标题和底部由游戏自己的同名缓存保存流程替换。没有读取、比较、记录或重放原生像素。

同名缓存生命周期已确认于 [缓存反汇编](20261019-language-setup-cache-disassembly.txt)：`10C570..10C597` 比较名字，`10C5AD..10C5B4` 经 `10C4C0` 释放原缓存，`10C5C0..10C687` 在原槽保存新原生面。因此后续排序、分页和从纪念页返回所用的 `10C690` 恢复源也包含新标题；不能只重画当前主面而留下旧缓存标题。

首次索引读取 `DEBC3 → DDA70` 被跳过，随后 `DEBC8..DEC32` 的索引枚举和原始顺序复制也被跳过。以下原生状态留在原帧中：

- 当前排序数组 `[EBP-4D0]`，以及 P 操作用的原始顺序数组 `[EBP-598]`。
- 当前页偏移 `[EBP-59C]`、实际记录数 `[EBP-5A0]`、页容量 `[EBP-5A4]`、起始行位置 `[EBP-5B0]`、行间距 `[EBP-5B4]`。
- 已有选择恢复 local `[EBP-5AC]`。原纪念页返回也使用它；新重建只在进入时把原生当前选择 `[5F54AB0]` 放入该 local，由原 `DF169..DF17C` 统一恢复并重置 local。

从 `DEC33` 起继续完整原生列表循环：原控件初始化、记录行、空列表或选择提示、排序控件、条件分页控件和页码、上传、绘制记录处理、呈现及输入。L/J/P 排序和翻页动作分派没有改变。重画中的记录行继续走原有 DD400 数据读取和显示生命周期，不另设记录快照或行槽。

## 状态交接与调用联动

`State` 仍仅为 `pending`、`rebuilding` 两个 `u32`，HDA3 后缀大小与既有五个整数排列不变。bit 0 保持原设置重建语义，bit 1 标识先祖列表；旧的值 0/1 因此仍保持已发布设置标记的含义。`request()` 同时请求设置与先祖重建；新增 `request_ancestors()` 供 adapter 的 invalidate 路径仅请求该页。新页面自然首次到 `DEB84` 时清该页 pending，因为这一页标题与背景已经按当前文本版本构建；设置初始化仅清自己的 bit。

主 adapter 须在 `invalidate()` 中调用 `request_ancestors()`，覆盖热发布依赖更新和已接入的窗口重建通知。`DEA14` 标题调用用原生 ESI=-1 判定列表分支；行文本使用 `DEDA0` 的短调用作用域。因此旧版本已打开的列表也能在这条原生 continuation 中重新遇到所有已接入文本调用，无须补造过去未发生的整页 Before 事件。

热发布事务 `Applied` 与当前像素重建是两个不同事实。现有 `src/loader/control_bridge.cpp` 的 `wait_bridge` 会在无 SDL 事件时持续等待，不保证立刻返回原生 `D1C00`；本次不修改驻留等待桥、不发送模拟事件。pending 会在后续上述真实非按键返回边界被消费；Shift+F10 消费路径已有原生 `-2` 返回。不得仅凭模块事务成功宣称已打开画面在同一时刻刷新。本页以外的纪念页、死亡分支即时重建不在此记录中确认。

## 过期依据登记

`docs/evidence/ancestors-static.txt` 中原“短 Chinese display plan”、固定七行条目、DF127 构建完整计划及 Present 叠绘等段落描述的是旧方案：其位置包括 `Scope and call lifetime`、`Saved source correspondence review` 及 `ABI 3 source migration correspondence`。这些设计违反当前 AGENTS 的原生 UI 所有权、禁止行槽/整页快照和延迟重放要求，不能作为当前实现获准的依据。原机器指令、调用 ABI、原生数据位置仍可独立引用；旧实现叙述属于待由页面迁移记录修订的过期文档。本记录确认的实现只在原有原生帧中执行重建，并不恢复上述旧方案。
