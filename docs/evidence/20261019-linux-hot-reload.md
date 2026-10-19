# Linux 热更新实现与交付

日期：2026-10-19。用户要求完成 Linux 热更新。遵循根 AGENTS.md：只读取源码、ELF、反汇编及进程身份，编译仅生成交付物；不启动、关闭、重启游戏，不注入旧进程，不运行产物或测试，不增加测试用例或断言。

## 已整改的原实现

| 原文件与位置 | 影响 | 本次状态 |
| --- | --- | --- |
| `src/linux/host.cpp` 原 `initialize` | 仅启动时 dlopen，无退役、状态交接及发布控制通道 | 替换为 Linux ABI 2 模块事务；旧 ABI 1 进程不能原位升级驻留桥 |
| `src/linux/hooks.cpp` 原 `instruction`、`replace`、`finish` | 回调直接指向业务库，网关只追加，原字节和活跃调用未登记；不能卸载后继续调用 | 按 native site 保存原字节、稳定槽和活跃调用；退役还原原字节，重新登记复用槽；After 重新取当前业务回调 |
| `src/linux/adapter.cpp` 原 `menu_input`、`view_scope`、`intro_scope`、`intro_line`、`poll_language`，`name_input.inc` 原 `name_input`，`culture_info.inc` 原 `culture_browser` | 业务返回地址和局部状态跨原生输入/动画等待，不满足任意界面交接 | 改为短 Before / 驻留原生调用 / 短 After，语义作用域使用可交接状态 |
| `src/linux/adapter.cpp` 原 `empty_save/empty_restore` | 语言、中文编码与原生资源密度元数据无法随卸载保留 | 保存明确的模块状态；不保存页面内容、像素或绘制贡献 |
| `build-queue.ps1` 原 Reload 的 Linux 拒绝分支；`publish.ps1` 原 Send-Control | Linux 无可用的统一队列热发布路径 | 接入同用户 AF_UNIX；沿用单队列、归档、正式替换、多 PID 和回执记录 |
| README、Linux profile 的“热更新未实现” | 已过期的功能边界 | 当前说明已修正；首次移植证据保留历史事实并链接本记录 |

本次不改字体排版或页面重建策略。此前 profile 中其他待确认边界仍保留，包括非主菜单缩放、描边预算和若干页面的纯重绘。热更新 Applied 不代表页面已重绘，也不代表视觉验收。

## 驻留调用与静态证据

目标 ELF 的 SHA-256 为 `4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`，所有 RVA 均相对主 ELF 基址。

- `readelf -Ws` 确认游戏导入 SDL_PollEvent、SDL_WaitEvent、SDL_PeepEvents、SDL_PumpEvents、SDL_Delay、SDL_RenderPresent。驻留层通过原有启动 LD_PRELOAD 拦截这些控制边界；SDL_WaitEventTimeout 也遵守其调用者超时语义。Wait 的内部 40ms 分片只用于检查事务，不向游戏注入事件或返回内部超时。
- `0x15a61a` 是 CreditsScreen 完成栈恢复后的 `JMP 0xf9060`，不是 CALL。新的 tail 网关保留调用者原返回地址，在驻留栈调用 getkeypress；关于页 `0x15ab41` 保持 CALL 语义。重绘期间沿原有 `redrawing_view` 选择跳过等待。
- `0x15b8c0` 的 fadein_teksti 在 `0x15b903` 调用 Flip、`0x15b90d` 调用 SDL_Delay。诗句的这一次原生调用使用驻留分配的字符串参数，直到原生函数返回才释放。它不是页面快照或可重放绘制记录；不保留额外的 UI 位置、裁剪、样式或绘制命令。
- LIST_Go、getst、百科浏览、About/Credits、开场与启动音频作用域均由 `Hooks::around` 执行。驻留的 CallState 只保存作用域标量和当前调用参数；其中不放业务函数地址或业务对象指针。ancestorentry 的嵌套数字状态改为可保存的语义记录。
- 对短调用目标 LIST_Draw、initmsg、LIST_ButtonSpotEntry、link_show、showtext、Piirra_Nappain、winbox、Piirra_Ikkuna、TekstiPalkki、centext、tsub、dstat、renderTextBox、renshowtext、renderwinbox、bestfitPic、CreateMapMainTexture、compile_CultureDialogTexture、CreateGamesizeTex 的 ELF 直接 CALL/JMP 图进行静态追踪，未见通向已记录输入等待或 SDL_Delay 的直接路径。这不是运行验证，也不推断任意间接调用。短 callback、HostApi invoke 和直接 replacement 函数均在执行期间持有驻留业务计数，嵌套 SDL 控制调用不能退役仍在执行的业务。
- `gateway.S` 的原生寄存器保存路径保留。当前 phased 原函数均使用已确认的至多六个 SysV 整数类参数；既有七／八参数文字调用仍走原来的即时短调用路径，不将浮点或栈参数推测为六参数。

## 模块交接

Linux Host ABI 明确升级为 `2`，Windows ABI 继续为 `1`。Linux 的 `uwcn_linux_hooks_v2`、模块描述符与发布清单一致；不将新业务模块说成可在初版驻留层上热加载。六业务模块 ID/掩码仍为 catalog=1/1、semantic=2/2、render=3/4、layout=4/8、main_menu=5/16、adapter=6/32。

1. 同用户控制线程只提交事务。抽象 Unix socket 名为 `NUL + uwcn-<effective UID>-<PID>`，无遗留 socket 文件；SO_PEERCRED 核对同用户。结束进程时关闭监听和客户端，完成等待中的控制回执，回收控制线程。
2. PREPARE 在原生线程且业务计数为零时处理：读取 candidate-files.tsv、核对 SHA-256，以 ELF 文件数据检查 ABI、模块 ID 和 state schema；不 dlopen 暂存候选代码。动态符号不得有 GNU_UNIQUE，动态标志不得有 NODELETE。
3. 按所选模块保存状态；Adapter 保存语言、输入／开场／百科等语义作用域、字形 token 字典和原生资源密度元数据。Layout 的原编码表照原顺序恢复，已写入原生缓存的编码不改号。资源状态只有 Surface/Texture 的实际身份、尺寸比例和 renderer 所属关系，没有像素、文本位置或页面字段。
4. 退役 Adapter 时先还原已登记原生字节；按依赖逆序 shutdown/dlclose 所选模块，并核对原映像是否仍在进程映射中。确实仍映射时报告具体模块，不能将 dlclose 返回值冒充已卸载。业务 ELF 用 `-fno-gnu-unique` 和隐藏内部符号编译，ABI 两个 C 导出保持公开。
5. ReadyToPublish 后，原生线程停留在驻留服务循环。发布器将旧正式文件按原相对路径移入根 `回收/`，再复制候选文件并最后提交 release.json。
6. COMMIT 核对正式文件与已记录候选身份，按依赖顺序加载和恢复所选模块，通知全部业务模块依赖变更，清除可重建的字宽／字体缓存；全部成功后才返回含各模块 SHA-256 和代数的 Applied，并继续当前原生调用。

只要已开始退役，失败或显式 ABORT 就保持驻留等待，报告 `Suspended`；不会放行到已经卸载的业务栈，也没有自动回滚、关闭游戏、原文兜底或平行运行包。使用相同模块集合的显式下一次发布可以重新 PREPARE/COMMIT 原暂停状态。Linux `-Reload` 始终装载明确选择的模块集合，即使磁盘文件未变；这也允许磁盘已发布、运行代数尚未更新的显式重试。未开始退役的候选检查失败则报告 `Running`，原模块未被卸载。

## 使用与迁移

统一入口仍为根 `build.ps1` 或 `build-queue.ps1`。在 PowerShell 7 中执行：

```powershell
./build.ps1 -Toolchain Linux -Module adapter,render -Reload -TargetPid 12345
```

`12345` 为实际游戏 PID 的占位示例；多 PID 按原有数组参数提交。不带 Reload 的 Publish 只更新正式文件，不报告运行时 Applied；不带 Publish 只编译。Linux 正式入口仍是根 `uwcn_launcher`，库位于 `package/uwcn_loader.dll` 与 `package/modules/`，没有新的启动器副本。

开始实施时，读取进程列表确认 PID `3783244` 已在运行原游戏；旧 Linux 驻留层没有控制通道。不能在该旧进程内自升级驻留桥。本次全图正式发布不向其发送 Reload，不替换其已映射的 inode，不关闭、重启或注入它。用户下一次正常启动根启动器会加载 ABI 2；之后兼容业务更新不要求离开当前界面。

## 交付状态

源码修改、全图产物编译与正式文件发布均已完成。使用根入口：

```text
.toolchains/powershell/pwsh -NoProfile -File ./build.ps1 -Toolchain Linux -Publish
```

- 请求：`f4d0e42e5b7f46bc9b7660c5f56cec20`。
- 批次：`347a941f421e48f9b630d2f7fbbddf33`，完成时间 `2026-10-19 14:05:09 Asia/Shanghai`。
- 发布事务：`87ae77e6090c41a8a86cb1271d84d50b`。
- 归档：`回收/20261019-140509-87ae77e6090c41a8a86cb1271d84d50b/`，保留旧驻留库、六个业务库、Linux profile、release.json 共九件原相对路径；桌面入口旧链接也按既有发布规则归档。
- 正式更新：`package/uwcn_loader.dll`、`package/modules/` 下六个模块、Linux profile 与 release.json。根 `uwcn_launcher` 内容未变，继续从相同正式位置加载新版驻留桥。
- 已读取对应 `build/.compile-queue/results/<request-id>.json`、`batches/<batch-id>.log` 和该事务 `publication-result.json`：Success=true、PublishRequested=true、ReloadRequested=false、runtime_requested=false，无运行时回执。编译保留 semantic.cpp 原有枚举分派警告，本次新 Linux 文件未产生编译警告。
- 正式清单 20/20 项 SHA-256 与磁盘一致。六业务 ELF 静态描述符均为 Host ABI 2、EM_X86_64、state schema 1；动态符号中 GNU_UNIQUE 数为零，动态段无 NODELETE；两个 ABI 导出保留。驻留 ELF 已导出七个 SDL 控制边界及 `uwcn_linux_hooks_v2`。
- 驻留产物反汇编确认 `dispatch` 在原生调用返回后重新读取 records 和 After 槽：本批次原生 CALL 位于 loader `0x1700c`，返回经 `0x16f88` 重新读取记录再于 `0x16f9f` 调用当前回调，没有跨等待缓存旧 adapter 函数地址。

最后将“未变化内容跳过发布”的原 Windows 行为保持不变，Linux Reload 才强制提交明确所选模块；这只是根发布脚本调整，不改变本批次非 Reload 发布结果或已编译 ELF。文档交付回执也在批次结束后补入。

未启动游戏、运行产物或测试，不报告运行时 Applied；仍运行旧驻留层的进程没有被升级。
