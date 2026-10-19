# 姓名输入字段与全局语言唤醒

本记录仅静态读取原 PE 与 `native_name_input.inc`，未运行游戏、测试、编译或模拟输入。原始输入证据另见 `20261019-windows-chinese-input-disassembly.txt`。

当前 Scene 没有独立 NameField source；`native_name_input::State` 只保存真实输入作用域与 SDL 提交标记。不过，活动的原生 `10F5B0` 自己持有完整输入与字段重绘过程，全局切换已经使用的原生 `-2` 返回会使它立刻重画，无须另一个按键。

| 原地址 | 已确认的实际语义 |
| --- | --- |
| `10F5B0` | 完整 getst 输入循环，ECX 为颜色，EDX 为原容量；入口从原 general cursor globals 取得字段 anchor。 |
| `10F5D6/10F5DC/10F5E2/10F5EB` | EBP-B4 容量、EBP-AC 颜色、EBP-A4 原 anchorX、EBP-B8 原 anchorY。 |
| `A49B9A8[64h]` | 实际正在编辑的持久 native buffer；UTF-8 编辑扩展仍写这个对象，不写 Scene 的中文结果。 |
| `10F6A0..10F6AC` | 用原 buffer、原 anchor/color/outline 调完整 `10E5A0` 绘制姓名。 |
| `10F6B1..10F6C6` | 读取刚由 native text consumer 推进的 cursorX，再以同一 Y/颜色绘制原 `_`。没有复制旧宽度。 |
| `10F6CE..10F719` | 原生提交后进入 `D3BF0` 等待。 |
| `D3C0F..D3C17` | `D3BF0` 遇真实 `-2` 直接返回，没有再次等按键。 |
| `10F71E..10F77C` | 返回值放 EBX，原生擦除原 underscore 条；不会改输入 buffer。 |
| `10F77F → 10F80E` | -2 不是 Backspace。 |
| `10F832..10F846` | -2 不是 Esc，也不在可打印字符范围，不 append 字节。 |
| `10F8A3..10F8C3` | -2 不是 Return/Esc；从 EBP-AC/A4 恢复颜色与 anchorX，跳回 `10F6A0` 完整姓名及 underscore 绘制。 |

因此 Shift+F10 的全局原生 `-2` wake 在同一次输入返回中恢复完整字段。实际输入、原容量、Esc/Return/随机名字动作、underscore advance 都继续由原生对象管理，不必重入完整 `10F5B0`，也不必保存低层文字调用或自行画光标。

当前 `119AB → 10F5B0` 的 Before 在设置活动输入状态后同步进入 `Scope::text`，对应 After 由根 dispatch 按同一 event token 退出。中英文姓名正文与原 underscore 因而都在同一已确认 native target 的真实输出密度下消费 Mod 字形和度量；这项密度修正没有新增 NameField source、位置快照或另一套字段绘制循环。

这不等于 Scene 已经持有 NameField 组件：在 `invalidate()` 立即提交重建背景与上述原生循环重画之间，Scene 本身没有该字段的独立 source。若后续要求在 Scene materialization 返回之前也同步完成字段，应将 `10F6A0..10F6CB` 定义为真实输入 owner 的 typed paint 方法，source 绑定实际 `A49B9A8` buffer 与该游戏帧的初始 anchor/color，普通同点也消费它；只由完整原 `10E5A0` 产生正文宽度并推进原 cursor，再消费原 underscore。不能把这个内联区间假称为已有 standalone ABI，也不能调用 whole getst 输入循环。当前尚未新增这种组件或复制输入值到译文快照。
