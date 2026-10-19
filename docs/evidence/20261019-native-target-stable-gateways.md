# 原生 SDL IAT 的跨代稳定入口

本记录对应 `modules/adapter/native_targets.cpp/.h`，描述稳定入口实现时的静态结论。后续编译、正式发布和运行时回执以 [原生高清交付记录](20261019-native-hd-delivery.md) 为准。

## 已确认的问题

游戏 EXE SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。RVA `125B79` 从 `18C204` 的 SDL_UpperBlit IAT 读取函数地址，保存于主菜单外层 `125A90` 的 ESI。`125BE1 → D1120` 输入等待返回后，`125C2B`、`125C77`、`125DC7` 等分支继续 `call ESI`。

因此，直接把业务 DLL 的 `blit` 地址发布到 IAT，会使新启动或再次进入主菜单的原生帧缓存业务地址。后续卸载旧 adapter 时，只恢复 IAT 无法更新 ESI。此前针对已发布旧驻留 thunk 的 `RetirementRoutes` 只处理旧入口别名，不能覆盖新 IAT 引入的业务地址别名。

## 入口与生命周期

`install()` 使用 VirtualAlloc 创建一块进程寿命代码分配，其中十个入口按 16 字节固定间距排列。每个入口仅有五字节 `E9 rel32`，直接跳到对应 SDL 适配函数；不压栈，不改变寄存器或 flags，不进入 Host Before/After 分发。IAT 只保存这些入口地址。CreateRGBSurface/CreateTexture 适配中的原生返回地址也因此保持不变。

固定槽顺序为 UpperBlit、UpperBlitScaled、FillRect、CreateRGBSurface、ConvertSurface、FreeSurface、CreateTexture、CreateTextureFromSurface、DestroyTexture、RenderCopy。槽顺序是本状态格式的一部分。

保存 adapter 状态时，先记录该代码分配的地址；随后 `remove()` 将十个槽的目标改为原 SDL 导出，再恢复原 IAT。原生帧已缓存的槽地址仍指向可执行的进程内存。`forget()` 只清除本代元数据，不释放这块已对游戏开放的代码。原生资源同样继续由游戏 owner 持有。

Host 在同一主线程 Prepare/Commit 停驻期间执行新代 initialize 和 restore。initialize 会创建临时槽并安装 IAT；在 restore 完成之前，游戏帧不推进，因此这批临时地址不会被游戏缓存。restore 读取保存的旧代码分配地址，将旧槽绑定到新业务函数，令 IAT 再次指向旧槽，然后 VirtualFree 本代初始化临时分配。每次正常跨代交接保留原稳定入口，不产生每代累积的槽分配。

`routes()` 返回稳定槽地址，使此前已经识别的旧驻留 SDL thunk 也直接跳到同一组稳定入口。adapter 保存前仍按现有契约把旧驻留别名显式绑定回原 SDL；新代恢复后再绑定稳定入口。

代码写入使用 VirtualProtect、FlushInstructionCache 并恢复原页属性；IAT 使用原子 DWORD 交换。系统调用错误明确返回失败，不实施自动回滚。本实现不改变 Host ABI 或 loader。

## NGT1 状态格式

该格式在本次修改前从未发布，因此直接扩展同一未发布格式，不增加对未发布旧格式的兼容分支。

| 偏移 | 内容 | 字节数 |
| --- | --- | --- |
| 0 | `0x3154474E`，NGT1 | 4 |
| 4 | canvas：逻辑宽、高、物理宽、高，各 int32 | 16 |
| 20 | 稳定代码分配的进程地址 | 4 |
| 24 | surface 记录数 | 4 |
| 28 | texture 记录数 | 4 |
| 32 | 先 surface、后 texture 的记录 | 每条 20 |

每条资源记录为原生 handle DWORD 加上述四个比例整数，不包含文字、像素或绘制历史。外层 adapter 的 HDA2 仍用 `native_bytes` 指明整个 NGT1 区段长度。只有同一进程的热交接使用这些地址。

首次从正式旧 adapter 迁移时，其状态只有 Active 数组；新代不调用 NGT1 restore，保留本次首次分配的稳定入口。全新启动同样保留首次入口。后续 HDA2 交接则恢复同一稳定入口。

修改前的两个源文件归档在 `回收/20261019-native-target-stable-slots/`，保留原相对路径。没有运行游戏、产物、输入模拟、测试或编译。
