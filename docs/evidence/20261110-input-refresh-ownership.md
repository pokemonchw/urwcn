# 输入刷新状态归属整改

用户指出上一轮刷新状态不应保存在驻留层。此意见正确：`host.cpp::input_refresh` 与卸载/重载/提交后的赋值，将界面业务请求保存在不可热替换的驻留库中，现已撤回；`take_input_refresh` 接口一并移除。

刷新 pending、重建阶段、原生调用者识别、一次性消费和先祖 continuation 全部属于 `modules/adapter/native_language_redraw.cpp`，随业务模块保存、交接与恢复。D12B4 原生 -2 已到达时同步清除尚未消费的等待退出请求，覆盖 Shift+F10 直接走原生 -2 的路径。

驻留层只保留稳定的无状态输入返回查询转发：Poll/Wait 控制事务结束后，将真实调用者返回 RVA 交给 Adapter 的 `kNativeInputReturn` 操作，并按返回值退出当前等待。不保存语言、页面或刷新请求，不判断页面地址，不在生命周期事务中写刷新状态。WaitTimeout 不新增返回策略。

Adapter 只对已静态确认的 D1C94（Poll）和 D1CFA（Wait）在 pending bit 2 存在时请求返回零，随后在 D1D69 消费该请求，继续原生 D2083 和先祖完整构建。桥返回前未从 SDL 队列获取下一条真实事件，不伪造事件、不模拟输入、不另建 UI。

上一轮 `20261110-unload-native-wake.md` 中“驻留层保存刷新标志”的修改已被本次取代，不能再作为当前设计说明。通用 Scene/Child 重建与署名排版的已登记不合规部分仍待整改。

已有驻留库没有这项无状态查询转发，现框架不能热替换驻留库；本次仍需更新正式磁盘文件，不能据此宣称当前进程驻留桥已更新。以后页面重建策略与刷新状态的调整均在 Adapter 内完成，无需因该业务状态修改驻留库。没有关闭或重启游戏，没有启动游戏、运行产物验收、模拟输入、测试、测试脚本或断言。

## 交付结果

源码修改完成。根 build.ps1 请求 `e3e380797c9a47f49ed797c9fd7593c5`，批次 `ed8542abbad5442ea83477e3f4c8fbae`，MinGW loader,adapter 编译成功，已读取结果 JSON、批次日志及发布事务 JSON。编译包含既有函数指针转换、初始化、缩进和未使用项警告。

正式磁盘事务 `3ba67415e2214d51a0b29933af3bb3fc` 更新 `package/uwcn_loader.dll`、`package/modules/uwcn_adapter.dll` 和 `package/release.json`；被替换文件归档至 `回收/20261110-112610-3ba67415e2214d51a0b29933af3bb3fc/`。没有 Runtime Applied 回执，当前进程驻留库未迁移。
