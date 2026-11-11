# 先祖列表切换语言后内容丢失

截图显示首次中文页面完整，切回英文后正文、底部背景和控件消失，再切中文也只恢复标题。静态发现 `native_language_redraw.cpp` 已移除先祖页 continuation，仅请求通用菜单选择重绘；`native_ui_scene.cpp::language_changed/repaint` 从保留的组件集合重新生成背景，不能保证包含该页原生 DD380 底栏和全部显示分支。截图与此缺失一致；没有进行运行时复现。

本次重新接入 `20261019-ancestors-redraw-native.md` 已确认的原生 continuation：D12B4 只在原生非按键返回 -2 且调用者为 DF187 时退出输入；DF187 在原 DE990 帧内继续 DE9DE，执行清屏、背景、标题、DD380 底栏及列表完整构建。DEB84 沿用原容量，DEBC3 跳过首次索引读取，DEBC8 继续 DEC33。原排序数组、页偏移、记录数、行距保留在原局部变量，选择交给 DF169..DF17C 恢复。没有增加页面快照、布局表、文本重放或输入模拟。

对当前安装的 3.89.1 原 PE 只读反汇编确认 DE9DE..DEC39、DF169..DF19F 的地址、指令和 continuation 与既有证据一致，rdata 文字位移仍由既有 Windows build 适配处理。State 仍为两个 u32，不更改交接大小。

## 既有不合规设计，待整改

- `modules/adapter/native_ui_scene.cpp` 的 Container/Child、cache_saved、paint、materialize_cache、repaint 保存并重建整页组件序列，语言切换依赖该集合；本页缺失说明它没有完整承接原生构建语义。该整页重建所有权仍在 Mod，违反当前原生 UI 所有权要求。本次接回先祖原生完整构建；通用场景机制尚未完成整改。
- `modules/adapter/native_footer_component.cpp::paint` 从 sibling 几何计算新增署名、版本与精灵位置并自行构造段落，属于 Mod 管理排版，违反当前要求；与本次先祖底栏 DD380 不同，待单独整改。
- `docs/evidence/20261019-ancestors-redraw-native.md` 的状态交接段落描述旧设置 pending 和 request_ancestors 接口，不能作为现接口说明；本次 bit 0 为通用菜单同步、bit 1 为先祖重建，不新增 request_ancestors。

没有启动游戏、模拟输入、运行测试、创建测试脚本或断言；只执行用户授权的兼容业务热发布，视觉效果须由用户验收。

## 交付

Windows Adapter 请求 `7b1fa7db83d8412f80ebc774f8d63d1c`，批次 `74bfd9b85e6a4e97ad8b48de01fe0fd5`，经根 build.ps1 队列完成编译；已读取对应结果 JSON 和批次日志。存在既有类型转换、未使用函数与缩进警告。

正式发布事务 `9e8465074eb74ae895637c95b15ecfab` 更新 `package/modules/urwcn_adapter.dll` 和 `package/release.json`。旧文件保留于 `回收/20261110-111917-9e8465074eb74ae895637c95b15ecfab/`。现有 Proton 进程 Windows PID 368 返回 `ReadyToPublish` 和 `Applied ... adapter:375d7219f005642bf00c27dbbb2a3246daa89cb6614b93b1913bcb7bac95a598:3`；这确认模块交接完成，不等于画面验收。源码修改、产物编译、正式文件发布均已完成。
