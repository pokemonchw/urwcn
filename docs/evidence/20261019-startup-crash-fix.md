# 开场闪退：现有转储定位与修复

## 实际故障

用户启动初版后发生闪退。Windows Application Error 记录时间为 2026-10-19 01:03:50，进程 urw.exe，PID 85736；故障模块 SDL2.dll 2.30.0，RVA 0xF7578，异常 0xC0000005。

分析只读取已有 `C:/Users/WIN11/AppData/Local/CrashDumps/urw.exe.85736.dmp`、日志、正式二进制与源码，没有再次启动游戏。转储的关键寄存器、事件参数和调用链保存在 [崩溃记录](20261019-crash-dump-analysis.json)。

故障指令为 SDL_LockSurface 的 `mov eax,[ebx+0x1c]`；EBX=0，异常读取地址为 0x1C。上层是 Render 的 read_surface / synchronize。原生事件为 Before、id=0x4000、SDL_UpperBlit，四参为 `{NULL, NULL, 0x0CE3C8A0, NULL}`，原返回地址为 urw.exe+0x10D6FE，上层返回为 +0x1257BB。

原游戏 +0x1257B4 显式执行 `XOR EDX,EDX`，把空源传给 +0x10D5B0 的开场过渡。该函数在 +0x10D6F8 调用 SDL_UpperBlit，然后继续临时黑色表面的 alpha 过渡。详细调用字节见 [原生边界补充](rebuild-ui-boundaries.txt) 与 [反汇编](rebuild-native-call-disassembly.txt)。没有证据将其归因为图片缺失。

SDL 原 UpperBlit 在解引用前拒绝空源/空目标并返回参数错误。旧 Mod 却在原调用之前执行 synchronize(src)，再调用不接受空指针的 SDL_LockSurface，改变了这条原生错误返回路径并制造崩溃。

## 修改原则

只修正 Render 的 Blit Before 顺序：原 SDL 会拒绝的空 surface 不进入内容同步，不创建缓存待处理项，不跳过原调用，不伪造图像或返回值。仍让 SDL 自己产生原参数错误，游戏随后继续原过渡逻辑。

此处处理依据是本次实际转储、原游戏指令与 SDL 公共函数实现，不是推测性的缺失处理。Adapter 的参数与原调用一致，驻留桥机器码与栈布局一致，本次没有依据修改它们。

## 交付状态

源码已修改：modules/render/native_cache.cpp 的 Blit Before 分支在同步前保留原 SDL 空参数错误路径。详细静态依据见 [Render 修复说明](rebuild-startup-null-blit-static.txt)。

统一入口 `build.ps1 -Module render -Publish` 已完成一次配置和一次增量编译，无编译错误或警告。本次请求 ID 为 `840882315a9e48b183b2ee0fd8eddf3b`，批次 ID 为 `479b8470fec547d5bf956095f10b8da5`。已读取该请求的 results JSON 与对应 batches 日志，Success=true，PublishRequested=true，ReloadRequested=false。

正式发布事务为 `f393468595b449258265890ebf6f5f37`。只替换 package/modules/uwcn_render.dll 和 package/release.json；旧文件先按原相对路径移入 `回收/20261019-011330-f393468595b449258265890ebf6f5f37/`。已读取 publication-result.json，确认正式发布完成；正式清单十个条目的 SHA-256 与磁盘文件全部一致。

- 新 Render SHA-256：`0cefb5e1d2e7b19d55db4598e6666af49225e5ec3b39a5accf1eb11ae52f5cf1`。
- 回收旧 Render SHA-256：`f0de1a009d159e8a937bd9377cf3c9de4e4de0a9877fe2a470b245dcc9740578`，与初版清单一致。

正常入口仍为根 uwcn_launcher.exe。没有另建运行副本。本次无运行时 Applied 回执；代理未启动游戏、未执行产物或测试，未创建测试与断言。修复后实际运行效果尚未确认。
