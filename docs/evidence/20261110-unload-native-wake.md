# 卸载汉化后先祖列表缺失

用户在上一轮发布后提供截图，确认 Shift+F5 卸载汉化时正文、底栏与控件仍然丢失。上一轮 Applied 只确认模块交接，不证明卸载后的原生重建已执行。

## 静态原因

`src/loader/host.cpp::unload_translation` 先执行英文物化，再退役五个翻译提供模块，保留 Adapter；`src/loader/control_bridge.cpp::wait_bridge` 消耗 Shift+F5 后继续循环等待。Adapter 的 D12B4→DF187 continuation 需要原生 D1C00 返回 -2；驻留等待不返回，故该重建尚未发生。

原 PE 只读反汇编进一步确认：D1CF8 调用 SDL_WaitEvent，D1CFA 进行原生参数清理，返回零时 D1D01 将原事件类型写零，随后到 D1D69。原零事件分支在 D1DA0 返回 D1C80 继续等待，**单独让 SDL 返回零也不会触发 -2**。D2083 是原生非按键返回 -2 的完整寄存器及栈恢复尾段。这些指令在当前安装的 3.89.1 原 PE 已逐段静态阅读。

## 修改

- 驻留层在成功卸载、重新加载或提交业务发布事务后设置单个输入刷新标志；Poll/Wait/WaitTimeout 在控制事务结束后返回零，不取走下一条真实事件，不发送 SDL 事件，不模拟输入。
- Adapter 在 D1D69 的五字节 MOV EAX,[native_event_type] 处接入。只有存在刷新请求且原事件类型为零时消费一次标志，继续原生 D2083。真实非零事件保持原分派。此接口没有新页内容、原生帧指针或像素记录。
- D12B4、DF187 和其余先祖 continuation 沿用上一轮已确认的完整原生重建，五个翻译提供模块卸载后英文路径由仍驻留的 Adapter 和原生字库消费。

原来的通用 Scene/Child 序列与 Mod 署名排版问题仍按 `20261110-ancestors-language-reconstruction.md` 登记为待整改；本次没有将它们视为符合原生 UI 所有权要求。

## 驻留更新限制

现有兼容热发布事务只能替换六个业务模块；build-queue.ps1 明确拒绝对 loader/launcher 使用 -Reload。当前进程已加载的旧 urwcn_loader.dll 无法通过现框架原位迁移。本次更新正式磁盘文件供后续正常启动使用，不能将磁盘发布报告为当前驻留桥已更新；不关闭或重启用户游戏，不另建修复包。

没有启动游戏、运行产物验收、模拟操作、测试、测试脚本或断言。编译只生成交付产物。

## 交付结果

源码修改完成。根 build.ps1 的 MinGW loader,adapter 请求 `d27bbfb4bf014bd6aac16e4b9f743ab6`，批次 `8d75c3090db44edf8e0f5b6d54b8ee2f` 已成功；已读取对应结果 JSON、批次日志及发布事务 JSON。编译存在既有函数指针转换、未使用函数及缩进警告。

正式磁盘发布事务 `721202d2608c401ba29554b9e2ac7f2b` 更新 `package/urwcn_loader.dll`、`package/modules/urwcn_adapter.dll`、`package/release.json`；旧文件在 `回收/20261110-112447-721202d2608c401ba29554b9e2ac7f2b/` 保留原相对路径。此次没有请求 Runtime Applied，当前游戏进程仍使用旧驻留库；修正于后续从根正式启动器正常启动时加载。没有关闭或重启游戏，也不声称当前进程已经修复。
