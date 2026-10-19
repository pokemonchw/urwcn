# 2026-10-19 旧 render 在 Prepare 状态保存期间崩溃

本记录只读解析用户已有转储并反汇编对应旧 DLL；未启动、注入、测试或运行产物。

- 转储：`C:\Users\WIN11\AppData\Local\CrashDumps\urw.exe.119880.dmp`，时间 2026-10-19 02:13:01，异常线程 72996。
- 失败请求：`6850be278210403b9894d03df9d18513`；批次：`9414bd8644bc499a93fb4ad9540e62f3`。
- 转储中的旧 render 加载基址：`0x586A0000`；模块路径为正式 `package/modules/uwcn_render.dll`。
- 对应旧文件现位于 `回收/20261019-021416-70e97bed31a04ea1a4096ae67ebfa897/package/modules/uwcn_render.dll`，SHA256：`0cefb5e1d2e7b19d55db4598e6666af49225e5ec3b39a5accf1eb11ae52f5cf1`。不得用随后发布的新 DLL 解释本转储。

## 已确认调用链

异常为 `0xC000001D`，地址 `0x586EFB58`，即旧 render RVA `0x4FB58` 的 `__gnu_cxx::__trap_terminate_handler()`，实际指令为 `UD2`。它是 C++ 未处理异常进入终止处理器后的结果。

转储栈与旧 DLL 反汇编对应：

1. loader `prepare_transaction` 返回点 RVA `0x14F6D`：调用第二次 `save_state(output, &size)`；第一次 sizing 已完成。
2. render `save_state` 返回点 RVA `0x6028` → `NativeCache::save` 返回点 `0xFC28` → Resource 序列化 lambda 返回点 `0x8D2C`。
3. `vector<uint8_t>::_M_range_insert` 在 RVA `0x77FB` 调用 `operator new`；栈中返回点为 `0x7800`。
4. `operator new` 的 `malloc` 失败分支抛出 `std::bad_alloc`，返回点 `0x4E67C`；栈中异常 typeinfo 为旧 render RVA `0x560EC`（`std::bad_alloc`）。随后 `__cxa_throw` → `std::terminate` → `UD2`。

## 转储中的实际大小

| 对象 | begin / end / capacity end | 已使用字节 | 容量字节 |
| --- | --- | ---: | ---: |
| 首次保存结果 `saved`（地址 `0x586F8028`） | `0x3B626020 / 0x4377DE91 / 0x496CE36E` | 135,626,353 | 235,569,998 |
| 第二次保存的临时 Writer（地址 `0x0ABFE270`） | `0x4CF4F020 / 0x53FA31C7 / 0x53FEFF62` | 117,784,999 | 118,099,778 |

第二次保存正在插入 bitmap 字节范围 `0x24AAF0D0..0x24B00850`，共 **333,696 字节**。Writer 剩余容量不足，vector 按当时已用大小扩容，实际申请 `0x0E0A834E` = **235,569,998 字节（224.657 MiB）**；该分配失败。首次结果尚未释放，Host 也已为第二次输出分配了 135,626,353 字节状态缓冲。这里能确认的是该次连续内存分配失败，不推断机器总物理内存已经耗尽。

旧源码对应 `回收/20261019-native-draw-rework/modules/render/module.cpp:69`：每次 `save_state` 都先执行 `saved=cache->save()`，包括 sizing 和实际输出两次调用。`native_cache.cpp:490` 开始的保存过程逐 Resource、逐 Paint 写入 observed 像素、文字、裁剪记录及 bitmap；`Writer::image` 再将 bitmap 全量插入字节 vector。因此实际输出阶段再次完整序列化，并在替换 `saved` 之前同时保留第一份结果。

失败位置仍在 Prepare 的保存阶段，尚未进入 `enabled=false`、模块卸载或 `ReadyToPublish`；新模块未进入此崩溃调用链。当前新 render 的 `save_state` 返回零字节，旧 NativeCache/Paint 保存路径已从活动源码移除。

后续正式文件发布独立完成：请求 `ff526bd50ade44beb663eaa92ca314ad`，批次 `3eb7fe79e79d400e903a55595b2291c2`，事务 `70e97bed31a04ea1a4096ae67ebfa897`。该次无运行进程、无 `Reload`，也无运行时 `Applied` 回执；本记录不将文件发布视为运行验证。
