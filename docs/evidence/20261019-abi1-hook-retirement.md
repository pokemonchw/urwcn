# ABI 1 已发布像素跟踪入口的单向退役

本记录与 `modules/adapter/abi1_hook_retirement.h` 对应。这里只准备实际源码整改，不代表已编译、已热发布或已消除正式版卡顿。该头文件尚需由 adapter 的 `initialize` 显式接入；本次没有修改 adapter 主文件、Host ABI 或 loader。

## 确切适用对象

- 游戏 EXE SHA-256：`e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`，PE32，首选基址 `0x400000`。实际补丁地址由传入的游戏映像基址加下表 RVA 得到。
- 已发布驻留 DLL：`package/uwcn_loader.dll`，SHA-256 `60553ff6db99e03af1030c9b1e1017a7fac648f3a3c1075c01396d055cda1d8f`，首选基址 `0x63DC0000`。对正式 PE 的静态符号及反汇编确认 `uwcn_call_bridge` RVA 为 `0x198D0`，`uwcn_after_bridge` 为 `0x19910`，`uwcn_inline_bridge` 为 `0x19940`。
- 当前 Host ABI 1 只有 `install_hooks`，没有注销入口。此实现是 adapter 内针对上述已发布格式的单向迁移，不是已有 Host 卸载能力，也不适用于任意 ABI 1 驻留 DLL。
- `src/loader/hook_host.cpp` 中该版 `Slot` 的 x86 字节布局为 `HookSpec[40] + code[4] + original[4]`；thunk 前十字节为 `68 <Slot地址> E9 <bridge相对位移>`。inline 的原指令回放位于 thunk `+16`，随后为跳回原位置的 `E9`。

## 永久退役的 17 个 ID

前四项 ID 为十进制；其余 ID 明确使用十六进制。此清单不是待重新安装的 HookSpec。

| ID | 原生位置 RVA | 恢复的指令字节或 SDL 导出 | 原参数数 |
| --- | --- | --- | --- |
| 50 | `0x10BB04` | `89 0C 82 F6 06 02` | 0 |
| 51 | `0x11454F` | `89 14 81 F6 06 02` | 0 |
| 52 | `0x10BB7D` | `8B 45 FC 48 83 F8 03` | 0 |
| 53 | `0x10BE33` | `89 14 81 F6 07 02` | 0 |
| `0x4000` | `0x18C204` | `SDL_UpperBlit` | 4 |
| `0x4001` | `0x18C1E8` | `SDL_FillRect` | 3 |
| `0x4002` | `0x18C1F4` | `SDL_FreeSurface` | 1 |
| `0x4003` | `0x18C1E0` | `SDL_CreateTextureFromSurface` | 2 |
| `0x4004` | `0x18C21C` | `SDL_UpdateTexture` | 4 |
| `0x4005` | `0x18C228` | `SDL_RenderCopy` | 4 |
| `0x4006` | `0x18C22C` | `SDL_DestroyTexture` | 1 |
| `0x4007` | `0x18C224` | `SDL_RenderClear` | 1 |
| `0x4008` | `0x18C1EC` | `SDL_RenderFillRect` | 2 |
| `0x4009` | `0x18C1C0` | `SDL_RenderDrawPoint` | 3 |
| `0x400A` | `0x18C1F0` | `SDL_CreateRGBSurface` | 8 |
| `0x400B` | `0x18C208` | `SDL_CreateTexture` | 5 |
| `0x400C` | `0x18C17C` | `SDL_UpperBlitScaled` | 4 |

来源是当前 adapter 原四个 inline HookSpec，以及原 `NativeCache::hooks()` 的十三个 IAT HookSpec。inline 补丁必须完整匹配 `E9 rel32` 后填充 `90` 的旧格式；IAT 必须指向旧 thunk。两者都逐项核对旧 thunk 的桥目标、Slot 的全部 40 字节 HookSpec、code 指针及 original 地址；inline 额外核对回放指令与回跳目标。SDL 原地址取游戏已经加载的 `SDL2.dll` 对应导出，不取已改写的 IAT 值。

也接受确切的原始状态：inline 当前字节已等于表中原指令，或 IAT 已等于该 SDL 导出地址。这是新启动和成功迁移后下一代初始化的已知状态，不猜测第三种补丁形式。所有 17 项完成识别后才写入；读不到指定字节或字节不匹配返回 `Status::invalid`，不继续猜补。这里的固定长度进程内读取只用于识别待改写补丁。

## 接入点和写入结果

私有函数为：

```cpp
uwcn::adapter::abi1_retirement::retire_tracking_hooks(
    std::uintptr_t image_base, HMODULE resident_loader, HMODULE sdl,
    RetirementRoutes* routes = nullptr);
```

由新 adapter `initialize` 在 `install_hooks` 之前调用；传入 Host 的 `image_base`、已经加载的 `uwcn_loader.dll` 和 `SDL2.dll` 模块句柄。此次热事务必须同时替换 render 与 adapter。新 adapter 的安装清单不再包含上述 17 个 ID，新 render 也不再返回它们。

对旧 inline，恢复整条原指令序列，停止后续逐像素跳转。对旧 IAT，先将其旧 thunk 的前五字节改为直接跳转原 SDL 导出的 `E9 rel32`，再将原 IAT DWORD 原子替换为 SDL 导出地址。游戏确实会把 IAT 函数地址保存至寄存器后复用，例如游戏 VA `0x4FF3F6` 读取 `SDL_RenderCopy` IAT；所以只恢复 IAT 不能去掉已缓存旧 thunk 的桥开销。直接跳转不修改通用寄存器、flags、参数或返回地址，不进入 Host 的 Before/After 分发。

驻留 `Slot`、原分配的 thunk 地址、inline 回放块、`uwcn_after_bridge` 和在途 `Pending` 全部保留。已经进入原 SDL 函数的旧调用仍按原来的 After 返回；新 adapter 须明确接收这 13 个旧 ID 的在途 After，并且不再发给已移除的 Paint 业务。不能把所有旧事件一律返回成功当作热路径成本已消除。本 helper 不改 adapter 的 Active/token/Host 堆字符串状态。

Host `install_hooks` 对已经存在的同 ID 只比对原 HookSpec 后跳过，不会重新写入恢复后的入口。因此这些 ID 在该进程中永久退役，不能被重新登记来恢复旧机制。保留的 Slot 不等于可卸载后重装；新功能若有独立确认的边界，应使用新的 ID。

写代码时按实际页属性暂时改写、刷新指令缓存并恢复原属性；IAT 写入使用已确认四字节对齐的固定位置。系统写入操作失败返回 `Status::failed`。迁移不实施自动回滚；写入开始后失败不承诺全部原子撤销，也不把失败报告成成功。

## 原驻留 SDL 入口别名的后续绑定

游戏主菜单外层 RVA `0x125A90` 在 `0x125B79` 将 `SDL_UpperBlit` 的 IAT 值存入 ESI，并在菜单输入 `0x125BE1 → 0xD1120` 返回后的多个分支继续 `call ESI`（例如 `0x125C2B`、`0x125C77`、`0x125DC7`、`0x125E34`）。因此新实现若在原生 SDL 入口扩展坐标，单改 IAT 会遗漏这个既存别名。旧 thunk 被保留为原地址处的五字节直接跳转入口，供已经缓存它的游戏帧继续使用。

可选输出 `RetirementRoutes` 含 `u32 count` 和最多十三项 `RetirementRoute { u32 id, thunk, original; }`。只有本次通过旧 Slot/桥字节识别的 SDL thunk 才写入记录；新启动和已经恢复原 SDL 的 IAT 不产生记录。所有入口识别完成后、开始实际改写前写入输出，实际系统写操作失败仍返回失败。这些字段只描述当前进程内驻留代码地址及原 SDL 地址，不保存像素、文字或绘制内容。调用者按 count 序列化三 DWORD 条目，在下一代恢复相同进程的别名记录。

`bind_routes(const RetirementRoutes&, std::span<const RouteBinding>)` 接受 `RouteBinding { u32 id, target; }`，也接受 `{ {id,target}, ... }` 列表。它只对记录中同 ID 的旧 thunk 写 `E9 target`，不修改 Slot、回放块、在途 After 或 IAT。空记录或空绑定列表不写入。业务代码主动指定新入口目标；在目标所属业务 DLL 卸载之前，用各条目的 `original` 明确绑定回原 SDL；新代恢复记录后再绑定该代入口。该显式停用步骤是卸载契约，不是自动回退机制。

这类绑定只能在下节确认的同主线程事务停驻边界执行，调用者不能把业务 DLL 地址留在旧 thunk 中后卸载该 DLL。父级接入与序列化尚未在本头中实现。首次旧代迁移与后续代绑定须分开：若新实现已经安装自己的 SDL IAT 入口，后代不能再次无条件调用旧格式迁移函数；它按约定拒绝第三种 IAT 值。已经保存的别名应直接由后代恢复并绑定。

本次扩展前的头文件和本证据副本保存在 `回收/20261019-retirement-routes/`，保留原相对路径。本次仍未编译、发布或运行。

## Commit 安全点与线程证据

`src/loader/host.cpp` 的 `service_control` 只在启动器传入的游戏主线程运行，持有 `gate` 且要求 `active_calls == 0`；Prepare 保存业务纯数据、退役旧业务，随后仍在此主线程等待正式文件替换。Commit 在同一锁内按模块 ID 初始化及恢复状态，然后广播依赖变更。新 adapter 在 ID 6 初始化时执行本迁移，早于依赖广播中的原生重绘。不能仅从 `gate` 推导所有其他原生线程都停止。

对此确切 EXE 的完整导入表和相关指令静态检查没有游戏 `CreateThread`、`SDL_CreateThread`、`_beginthread` / `_beginthreadex`、`GetProcAddress`、`LoadLibrary`、SDL 事件筛选回调注册或 SDL_mixer 用户回调注册入口。SDL 和音频库自身线程不通过本 EXE 的绘制 IAT，也不执行本 EXE 的四个写点。该 EXE 唯一 `SDL_AddTimer` 调用位于 VA `0x57D05D`：参数 interval `0x14D`，callback `0x57CC20`，userdata `0`。

此 timer 回调完整范围为 RVA `0x17CC20..0x17CC78`。它读取全局开关 `0x6354A1F`，以 `SDL_HasEvents(0, 0xFFFF)` 查队列，无事件时构造 `0x8000` 用户事件并调用 `SDL_PushEvent`，最后返回原 interval；它不调用绘制函数或上述四个像素写点。因此该已确认游戏构建在主线程 Commit 停驻时不存在另一个已注册游戏绘制回调执行待改指令的路径。此结论只用于这份 EXE 的这 17 个入口，不扩展成通用多线程卸钩保证。

新启动在游戏入口运行之前初始化 adapter，遇到的是原始字节，函数只识别而不改写。整个实现和证据获取均为源码、PE 与反汇编静态工作，没有编译、运行游戏、运行产物、模拟输入或测试。
