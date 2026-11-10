# 百科无资料等待的原生语言重建

状态：源码完成，等待主代理整合；未编译、未运行游戏、未运行产物、未测试或模拟输入。证据来自 `build/analysis/windows-3891-native-full.asm` 与原始 `urw.exe`。本次独立文件为 `modules/adapter/native_encyclopedia_wait_language.inc`，没有修改共享 Full、HUD、父缓存或已冻结的等待文件。

## 两条原等待及完整构造

| 原等待返回 RVA | 原构造者与完整原生调用 | 真实已接受输入 |
| --- | --- | --- |
| `3E8D1` | `3E680` 原背景 `3E6F0→1127C0`、完整页眉 `3E743→115E70 / 3E75A→10E5A0`、`3E882→116270` 原标题面板、`3E8AF→10E5A0` 原无资料正文、`3E8C4→114680` 原继续按钮 | 存活 `3E680` 帧的原本地标题；原函数已完成 uppercase 和 `*→"` 处理，并已真实查询失败 |
| `3DD0B` | `3DCA0` 的 `3DCB8→116270` 原标题面板、`3DCE9→10E5A0` 原无资料正文、`3DCFE→114680` 原继续按钮；之前完整重建其真实父百科与实际存在的搜索字段 | `3DCA0` 第一个 `PUSH ECX` 保留的原失败查询指针；仍指向存活 `3E2A0` 帧的原本地查询 |

`D3C80` 在入口建立 EBP；实际 `D3D05→D3BF0` Before 回调保留这条真正等待。`[waitEBP+4]` 即表中返回 RVA。首次失败的父帧是 `[waitEBP]`，其 `AND ESP,~7 / SUB ESP,74h / PUSH EBX,ESI,EDI` 给出正文栈基 `(parentEBP&~7)-80h`，原标题在 `+10h`。查询失败的 `3DCA0` 不建立 EBP，仅先 `PUSH ECX`，故原查询指针准确在 `[waitEBP+8]`，其调用者返回地址在 `[waitEBP+0Ch]`，为 `3E653`。

初次失败同步调用原 `3E680`：复用已安装的 Full `encyclopedia_entry` 在 `3E697` 设置原 EDI 并转 `3E6D1`，跳过原历史清空、音乐和窗口隐藏。新 `3E783` 边界把真正已接受的标题写入新原生帧同一本地输入后转 `3E867`，不再次查询、uppercase 或清链接。原面板、正文和按钮完整执行。仅本次构造跳过 `3E8CC` 的新等待，再由 `3E8D1→3E942` 原 cookie/寄存器/帧 epilogue 返回，跳过音乐比较和恢复。普通路径原指令不变。

`3E8D1` 的预期 MOV 操作数取未挂Hook的 `3E6B3` 同资源原指令操作数 `3E6B4`，不新增推定映射，也不在下次重载读取已被驻留JMP改写的自身字节。`3E783` 的原 `XOR EAX,EAX + 11-byte NOP` 共 13 字节，继续点在它之后的原完整面板入口，未截断指令。

## 父百科和已提交搜索文字

`3DD0B` 的原失败查询没有成为成功百科 topic。原 `3E639→3C8A0` 先确认存在性，只有成功才走 `3E404→3DD10`。`3DD10` 在 `3E090..3E0A2` 或 `3E0F0..3E102` 才写原当前 topic `2EA820`。因此父百科必须使用原当前 topic，失败输入只用于失败面板和实际已提交的搜索字段；不得伪造 topic 或把失败输入当成功页面。

新代码调用已有 `native_full_language::encyclopedia(selection)` 完整原生构造，并按同一 native action / 原英文链接身份恢复选择。它沿既有重建边界跳过音乐、history 增加、新 Menu 等待及业务返回分支。新 `3E47E` gate 仅在本次父构造中跳到原 `3E4CA`，跳过中间提交/显示；完整原菜单仍由 `3E110` 构造。随后按原 `D0650(selection,0)` 恢复原选中显示，再重建真实存在的搜索字段，最后执行原 `3DCA0` 整个面板。`3DD06` 仅在该同步构造跳过新等待，随后原 `POP ECX; RET` 正常平衡。

搜索字段由真实原 `3E4F0..3E582` 完整构造，使用 `3E2F5` 原 MapRGB IAT `18C1F8`。该原片段无外部帧局部读取，原生自己创建背景、文字与 cursor globals；借用 Full 的 `encyclopedia_keyword / keyword_prompt_end` 完成 RET。实际 EAX 返回原 MapRGB 色值；文字位置读取该原构造刚产生的 `A1C1CB4 / 61BBB3C`，没有复制坐标常量。

已接受的原失败查询通过原 `10F6AC→10E5A0` 调用点绘制，参数为该完整原字符串、原构造刚返回的色值和原 text style 0。该调用点原有 Full `name_text` hook 仍配对管理英文显示含 UTF-8 输入时的 Unicode scope。新汇编桥在真实参数下方建立自己的同步返回地址；`10F6B1` gate 使用 `ADD ESP,0Ch; RET` 精确回收三个原参数，再恢复桥保存的寄存器。未进入已退休 getst 帧，未调用 getst 初始化、编辑、提交、输入等待或 cursor 绘制。原 getst 在已接受 Enter/Escape 前已经在 `10F74D..10F77C` 清除编辑光标，因此重建已提交文字不重新画光标。

整次同步构造保存并恢复原 `disable_flip`，完成后通过原 `10B720` 提交；没有新表面缓存，没有重放绘制贡献。

## 真实输入路径和旧状态的精确边界

原 `3E4E8` 是原 Menu 返回字符串的 `CMP AL,20h`，随后 `3E4EA` 决定是否进入 getst。新 hook 覆盖完整八字节 CMP/JNE，记录这条真正接受的 `link / keyword` 语义，再显式转到原 `3E5A7 / 3E4F0`；不拷贝相对 JNE 到 trampoline。原 `3E58E` 还确认真实已接受的 keyword 返回。这不是用查询内容、当前鼠标或选择行推断路径。

第19分节保存 `Input::none/link/keyword`。none仅代表该会话尚未发生原输入生产者；普通失败等待必已通过真实生产者。没有帧指针、query文本、整页字段或布局。HDA8接入后这两种失败路径均完整重建。

旧版本已经停在 `3DD0B` 且没有第 19 分节时，仍活的原帧只保留失败查询，没有 link/keyword 分支历史：

- `3E110` 的原接受 row 曾仅在其 ESI 中，返回时已恢复调用者 ESI，其旧帧已经退休。
- `3E4E8` 看到的空格随后被 `3E58E..3E5A3` 的真正输入覆盖。
- `3E1EF..3E1FB` 允许 `D0430/D0570` 的鼠标命中覆盖 `5F54AB0`，因此它的 action 不是旧实际返回 row 的可靠替代。
- `A49B9A8` 可以保留更早一次 getst 输入；其字符串即使等于当前失败查询，也不能证明当前走 keyword。

独立代理也静态复核了上述不可逆历史。早期研究曾让该旧交接阶段保留unrecorded并等待原构造，但这不能满足全部活动界面即时重建；该分支已退出最终实现。最终HDA8明确拒绝旧HDA7状态，不假设link、不猜false、不读取退休帧，也不把延后刷新声明成完成。

## 外层父缓存与普通关闭

静态 `CALL 3E680` census 有两条，不能只列普通百科包装：

1. `DF8AA`：`DF7B0` 在 `DF86B→10C540` 保存原父 named background，`DF8AF..DF8C4` 原窗口恢复后，经 `DF8ED` 或 `DF935→10C690` 恢复该缓存，再经 `DF8F7 / DF93F→10C4C0` 释放。现有 `native_parent_cache_language` 在这两处真实原恢复前完整构造该父 owner 并重存原名缓存，维持游戏自己的恢复、fade、呈现和释放。其静态 DF7B0 outer caller census 为 `F973,56A70,B0793,D7C02,E0FF3,FB7F8,FCF58,1006F9,100CB5,17DEC5`，对应文化、背包、HUD、伤情、技能、情境/HUD、护甲、命令、定位命令和 HUD。新 no-info 文件没有另建副本或跳过这个恢复。
2. `E017D`：Spells 问号分支直接进入百科。`E0182..E01A7` 还原原窗口标志，`E01A9` 恢复原接受 selection，随后 `E0125 / E0139→DFD7E` 完整重建原 Spells UI；这里没有 DF7B0 named background，因此没有添加一个不存在的父缓存。

`CALL 3DCA0` 的静态 census 只有 `3E64E`；普通 Continue 后 `3DD0B` 原 POP/RET 回 `3E653`，重新显示实际 `2EA820` topic，再进入真实百科等待。本实现没有改变这条业务或输入动作。

## 整合接口

在 `native_full_language.inc` 后 include新文件。聚合调用 `append_hooks(hooks)`、`dispatch(event,result,handled)`、共享 `about_input_tick` Before的 `wait(event)`。dispatch位于Full后；仅在Full未处理时消费其 `encyclopedia_entry` Hook。HDA8第19分节固定调用 `save()/restore(const void*,u32)`；不再读取缺失此节的旧HDA7。

新增 IDs 为 `5230..5237`。没有增加测试、断言、保护分支、虚构默认输入、发布目录或编译请求。
## Hook 重载身份补充

`3E8D1` 的 MOV Hook 验证值从未挂 Hook 的 `3E6B3` 同资源 MOV 操作数（`3E6B4`）读取；原 PE 两处均为 `MOV ECX,5954B8h`。不能在下一代初始化时从已被驻留 JMP 改写的 `3E8D2` 读取期待值，也不重复套用 rdata 地址映射。
## 最终HDA8边界

最终实现只恢复HDA8完整分节，不接受HDA7旧状态。原 `3DCA0` 只有 `3E64E` 一个直接caller，正常HDA8所有路径均先通过 `3E4E8` 捕获实际link/keyword，关键词再由 `3E58E` 确认，当前无结果等待因此消费真实来源。正式文件发布与旧进程应用的区别见 [最终记录](20261110-language-switch-completion.md)。
