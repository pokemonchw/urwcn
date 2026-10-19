# 2026-10-19 背景槽退役后的悬空表面访问

本次只读解析用户已有转储、Windows 错误事件、正式 DLL 与原生 EXE，没有启动游戏、注入、模拟输入或运行测试。源码修复已保存于 `modules/adapter/native_targets.cpp` 的 `promote()` 命名槽循环，并于2026-10-19 08:36:05（Asia/Shanghai）随共享工作区统一队列完成编译与正式发布。

## 两次实际故障

两份转储均加载正式 Adapter，SHA-256 为 `4779d2b868646dac57e6bc7b4cfceca6d91289a7f428bd225e849e4f28c7e189`。不使用后续编译的地址解释旧故障。

- 2026-10-19 08:23:50，PID 65412：SDL2.dll RVA `F1344`，异常 `C0000005`，读取 `0x39`。原生 `11644C` 从 `61BBB10` 取主面，`116462` 取 `surface->format`，`116465` 调用 SDL_MapRGB，真正返回地址为 `11646B`。format 参数位于异常 ESP+0x50，值 `58128684`，其内容已不是有效像素格式。SDL 走入调色板分支后，以 `EDI=39` 读取颜色数组失败。故障在该面板标题绘字之前；不能据此归因于中文标题的参数或宽度计算。
- 2026-10-19 08:28:33，PID 97408：Adapter RVA `1755B` 的 `replace_surface()`，指令 `mov ecx,[edi+0x18]`，异常读取 `0x17`。`ESI=0E282EE8` 为旧表面，`EDI=FFFFFFFF` 为它的 format；当前迁移的是 `A1C2014` 子窗口背景槽，返回至 `promote()` RVA `18360`。这是无效表面格式被消费的第二个故障点。

转储摘要见 [JSON](20261019-retired-background-crash-dumps.json)，故障二进制片段见 [Adapter 反汇编](20261019-retired-background-fault-disassembly.txt)。两份 minidump 未保存受影响表面本体及分配/释放历史，因此不声称已还原具体的堆地址复用先后顺序。

## 确认的生命周期错误及修正

原生四个命名背景的名字位于 RVA `A1C1AC0+i*0x64`，表面指针位于 `A1C1CC4+i*4`。原始指令见 [原生反汇编](20261019-retired-background-native-disassembly.txt)。

- `10C558..10C569` 以名字长度是否为零选择空槽；恢复入口 `10C690` 同样按名字查找。
- `10C50D..10C51A` 清空命中槽的100字节名字，`10C51F/10C526` 随后调用 SDL_FreeSurface；`10C52C..10C532` 直接返回，**不清除表面指针槽**。
- `10C5EB..10C5FE` 为新背景写入名字，随后原生创建、转换并在 `10C661` 保存新表面。
- 两份转储的四个槽名首字节全部为零，但槽0仍非零：65412 为 `1F0C22F0`，97408 为 `0FDAC3C8`。

修改前 `native_targets.cpp` 的 `promote()` 命名槽循环用 `global<Surface*>(slot)` 是否非零决定是否迁移，错误地把已退役槽当作有效资源。`replace_surface()` 会读取该地址、创建替代面并再次释放旧地址；如果分配器已将旧地址复用于其他原生 owner，就会破坏该 owner 的生命周期。两份转储确认了退役槽残留及失效格式，具体地址复用链受上述转储范围限制。

本次将迁移条件改为原生名字首字节非零，只迁移仍有名字的背景。继续使用原生创建、恢复和释放流程以及原799宽度；不改游戏的残留指针值，不添加空 format 保护、地址去重、替代图像、错误吞掉或兜底分支。

原实现违背原生缓存生命周期的要求，状态为**源码已整改、编译及正式交付已完成、运行效果未验证**。`20261019-native-hd-target-boundaries.md` 关于“四个已存在命名槽”的旧表述不足以界定存活，后续须按本记录的名字占用语义解读。未穷尽的其他资源别名及宿主错误透传仍按既有记录保留，不能视为本次全部解决。

## 交付状态

- 源码：命名槽循环改为原生名字占用判断；本聊天保存后未继续修改该修复。并行界面汉化也修改了同一 Adapter，保留其改动。
- 编译：包含本修复的共享源码由并行聊天通过根 `build.ps1 -Module adapter,catalog,render,semantic -Publish` 提交。沿用项目默认 MinGW、`.toolchains/x86/w64devkit/bin/cmake.exe`、同目录 `g++.exe`、`build/mingw-x86`、正式 `package/`，`Reload=false`、`TargetPid=[0]`。本聊天未重复提交同一份修复。
- 最终请求 `09bad5bc926648c1aeb1ab868b38c005`，批次 `bb5482e7791a4d34a70c869f1c00d807`。已读取对应 results JSON、批次配置与日志：`Success=true`，一次配置、一次增量构建，四个模块目标完成；保留既有 GetProcAddress 函数指针类型转换警告，无编译错误。
- 正式发布事务 `f39646159d51475da114beb3a7bea9c5`。已读取 `build/mingw-x86/stage/<事务>/publication-result.json`：`success=true`，包含四个业务模块、三份词库、构建适配及发布清单。旧正式文件先按相对路径移至 `回收/20261019-083605-f39646159d51475da114beb3a7bea9c5/`；其中旧 Adapter SHA-256 与两份故障转储所对应的正式版本一致。
- 当前正式 Adapter SHA-256：`a70a27724ddc3c5e279398818f658cd6566cf0abe25fd49f3daa06ad0c32a57f`。正式清单12项哈希均与磁盘一致。已静态反汇编正式 DLL：RVA `1EE85/1EE92/1EE9F/1EEAC` 分别比较原生四个名字首字节，仅非零才进入迁移；见 [正式机器码](20261019-retired-background-published-disassembly.txt)。这证明正式产物包含本次修复，不是仅修改源码。
- 前一并行请求 `e92b0043ec6b4a8b9729aa0369e5fc18` / 批次 `3c8c4679427048a99afec79af849014c` 编译成功，但在发布前的独占打开检查中发现旧正式 Adapter 被占用，事务 `5b27641d71854e819c7ed3bcb67df4e6` 未开始移动正式文件。后续上述最终事务成功，不将中间失败算作已发布；当时具体占用者未由本聊天确认。
- 本次正式发布未请求 Reload，无运行时 Applied 回执。根 `uwcn_launcher.exe` 与驻留桥沿用原正式文件；用户正常启动路径已能取得新 Adapter。没有独立修复包或平行运行目录。

未启动游戏、运行产物或测试，未创建测试脚本、用例或断言；实际运行效果尚未验证。
