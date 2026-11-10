# Wine / Windows 切回英文菜单错配

静态审查：`modules/adapter/native_menu_component.cpp` 的 `paint` 原来调用 `activate(handle)`；`native_menu_model.cpp` 的 `activate` 将快照映射到 input_owner，安装可变记录，而 source_handle 仍使用快照文字绑定。缓存源记录和文字绑定可能属于不同构建时刻，造成旧菜单与当前菜单混绘。原实现不符合原生组件完整语义消费要求，已整改此处。

本次由 CFFB0 原生列表绘制消费源自身的原生 header/rows，绘制结束恢复调用者真实原生记录；重绘入口和提交钩子在物化期间不再把临时记录捕获回输入模型。排版、窗口、选择与缓存仍由已有原生调用管理。没有新增坐标、像素扫描、文字贡献序列、测试或断言。

初次误按 Linux 提交请求 da6f526ce2e246ae9c49729a1fe29409，批次 f01c2d13bce04fdda961ef599350894a：编译成功，发布因缺少根 Linux 启动器失败，部分文件已写入。确认用户使用 Wine/Windows 后已撤回本次 Linux 源码改动，由 Windows 正式发布替换误写 Adapter，旧文件归档保存。

Windows 请求 94cff62228fb4f00a4530161d60da197，批次 e40ef74d8b294db49f57715e5b0346a3：已读取请求结果和批次日志，成功；有既有未使用函数、类型转换和成员初始化警告。事务 09d5e284206f4652b4d9dde0d3f2401d 已发布 package/modules/uwcn_adapter.dll 和 package/release.json；旧文件位于 回收/20261110-103124-09d5e284206f4652b4d9dde0d3f2401d/。正式 Adapter 静态文件类型为 Windows PE32。

源码修改、Windows 编译、正式文件发布完成；没有运行时加载回执，不声称当前游戏进程已更新。没有启动游戏、模拟输入、运行产物或测试，视觉效果待用户验收。
