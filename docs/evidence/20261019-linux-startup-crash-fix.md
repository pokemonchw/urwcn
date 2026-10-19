# Linux 启动闪退修复

日期：2026-10-19。用户反馈根启动器启动后闪退。本次只分析用户已经产生的 core、原生 ELF 和源码，不启动游戏、不附加或注入进程、不运行交付产物或测试，不创建测试用例和断言。

后续反馈：用户在本批发布后仍遇到闪退，10:54:05 的新 core 确认后续音频显示键 `ritual` 缺失，详见 [启动词库修复记录](20261019-linux-startup-catalog-crash-fix.md)。本记录的编译发布回执仅说明首轮两处修正已交付，不表示整个启动流程正常。

## 本次崩溃证据

- systemd-coredump：PID `3666934`，时间 `2026-10-19 10:49:23 +08:00`，信号 `SIGABRT`。
- 主程序 SHA256：`4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`，与 Linux profile 一致。
- 崩溃时正式 Adapter SHA256：`9b3743f19f2f1344fc461fe20ba3748cab0f0a866c2ccfdbbe08d91a1d56ab26`。
- 离线调用栈：`std::__throw_out_of_range_fmt` → `startup_message(Frame&) [clone .cold]`（Adapter RVA `0x2521`）→ `uwcn_linux_gateway`（Loader RVA `0x6178`）。没有执行 GDB 的 run、continue 或 call。
- 网关帧地址 `0x7ffee3d03860`，原生 RDI 为 `0x7ffee3d03d60`，该地址保存完整字符串 `Loading audio: ambience`。
- 帧中的 resume 为 `0x5555ab51a018`；主 ELF 基址 `0x5555ab503000`，对应被替换 CALL RVA `0x17013`，位于 `Lataa_Sample(char*)`。
- core 解包和离线摘录保存在本地 `build/analysis/startup-crash-20261019/`，不作为运行交付。

## 根因与修改

`src/linux/adapter.cpp` 的 `startup_message` 先取 `original+15`，再调用 `value.erase(value.find_last_of('.'))`。本次值为 `ambience`，没有点号，位置成为 `std::string::npos`，`erase` 抛出越界异常，进程终止。

原生 ELF 给出明确的字符串语义：

- RVA `0x1de230` 是格式常量 `Loading audio: %s`，前缀恰为 15 字节。
- `Lataa_Sample` 在 `0x16ef0` / `0x16efd` 去除扩展名，在 `0x16f09` / `0x16f16` 去除连字符后缀。`0x16fea` 将已经得到的资源名送入原生格式化，随后 `0x17013` 调用 `initmsg`。
- 另一接入点 `0x16dbc` 位于 `load_sample(char*,char*)`；`0x16d93` 将第一个原生参数（资源名）送入同一格式化常量，不是第二个文件路径参数。

修复直接以 `original+15` 作为同步显示调用的资源名，删除 Mod 的二次扩展名处理和临时字符串。词库已有 `startup.resource.ambience` → `环境音`。原生音频载入、日志、内部资源名及调用顺序保持原有语义，没有新增异常吞掉、保护或回退分支。

## 同次静态审查发现的参数错误

`src/linux/adapter.cpp` 的 `bound` 和 `scenario_title` 为翻译复制了 `Frame`，原七参数 `call` 却通过副本的 `stack()` 读取第七参数。`src/linux/hooks.h` 的 `stack()` 返回 `this+sizeof(Frame)`：只有原始网关帧的这个地址才是原生调用栈，副本后面是 Mod 的临时栈内容。

已确认影响：

- `winbox`（RVA `0x1471a0`）在 `0x147548` 从 `[rsp+0x110]` 读取第七参数，并于 `0x147572` 传给 `SDL_FillRect` 作为颜色；设置、关于、鸣谢、角色创建、村庄标题的调用均需保持此参数。
- `tsub`（RVA `0x1223b0`）在 `0x12242a` 读取原生第七参数，并于 `0x122436` / `0x122440` 作为 `stat_x` / `stat_y` 的数组下标写入。误读副本栈会破坏原生状态或造成越界访问。这是静态确认的另一个缺陷，不将其冒称为本次 SIGABRT 的原因。

修复使七参数调用显式接收原始 `Frame`；翻译后的副本仅提供寄存器参数。两处 `bound` 调用和 `scenario_title` 均传入原始帧，六参数调用独立保留。未修改网关结构、驻留 ABI、游戏布局、输入动作或状态数组。

## 范围与交付状态

源码修改、统一队列编译及正式发布均已完成。本次只修改 Linux Adapter；既有高清原生目标未确认、部分旧页面缓存刷新边界、Linux 运行中模块退役协议，仍按 [Linux 移植记录](20261019-linux-native-port.md) 保持待处理状态，本修复不改变这些结论。

2026-10-19 10:52:25（Asia/Shanghai）执行根入口：

```bash
.toolchains/powershell/pwsh -NoProfile -File ./build.ps1 -Toolchain Linux -Module adapter -Publish
```

- 请求 `68521a0948a641bea2a57aafdd46b201`，批次 `e8b330c3929e4707b2a798e93b7f481e`，发布事务 `602aa18487ca4a868d2db3ab92defbc7`。
- 已读取 `build/.compile-queue/results/68521a0948a641bea2a57aafdd46b201.json`、完整批次 `.log` 及事务 `publication-result.json`；编译、发布均成功，`ReloadRequested=false`。
- 仅进行一次配置和一次 Adapter 增量构建。正式更新 `package/modules/uwcn_adapter.dll` 与 `package/release.json`；根 `uwcn_launcher` 继续加载该正式模块。
- 旧 Adapter、旧清单及发布脚本维护的旧应用菜单链接先移入 `回收/20261019-105225-602aa18487ca4a868d2db3ab92defbc7/`，保留原相对路径。
- 正式 Adapter 与构建产物 SHA256 均为 `15220fa8c0b766fe860709d8ab3817769281f576f9731258bcc4ff2dfc4c9139`，与正式清单一致。回收 Adapter 的哈希与上述崩溃时旧文件一致。
- 根启动器和驻留库哈希保持原值，分别为 `83e27dcf4534c98cb8bc23379be79a507664442c6cea3305999c61a8ea19d2f1`、`91b0a8a5be949bd1874421ea4ff03452bc502230c3c5694d378279d851257173`。

编译和文件身份核对不代表游戏运行效果已确认；没有自行启动游戏、运行产物或测试，没有运行时 Applied 回执。
