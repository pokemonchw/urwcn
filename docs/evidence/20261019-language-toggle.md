# 2026-10-19 全局 Shift+F10 中英文显示切换

本次实现游戏内的全局语言选择：左右 Shift 均可与 F10 组合，每次新的按下切换一次；长按不重复切换，失焦清除本次按压状态。Ctrl/Alt/GUI 组合保持原输入语义。只切换显示，不卸载业务模块、不刷新词库，也不修改英文业务数据、设置选项值或保存动作。

## 源码和静态依据

- `modules/adapter/native_language_input.cpp` 使用两处已确认的原生事件消费边界：`D1CD4` 普通 Poll/Wait、`D26AB` 动画输入。`D1B40` 的文本输入整理保持原生重排，避免提前处理队列后面的快捷键而跳过当前数字小键盘动作。普通输入消费后走原生 `D2083` 非按键唤醒返回，动画消费后走原生零返回，不把快捷键交给菜单或跳过动画。原生排空与 FlushEvents 会丢弃 KEYUP，因此新的 `repeat=0` 按压明确开始新周期。字段、指令和完整输入清点见 [输入依据](20261019-language-input-static.md)。
- `modules/adapter/module.cpp` 在统一 `translate` 边界选择中文或本次原文，原生编码、完整串宽度和即时绘字在两种语言下都继续工作。新增汉化署名仅在中文模式绘制；主菜单重建原面板会清除英文模式下的旧署名。
- 主菜单同步执行既有原生绘图片段、工作缓存复制和选择绘制；关于窗口先由 `10DA60` 恢复原生菜单背景，沿同一菜单重建链更新背景，再由 `10DA10` 保存，最后完整执行原关于函数并仅跳过其输入等待。原生保存/恢复会呈现中间帧，不作无闪烁承诺。
- `modules/adapter/native_language_redraw.cpp` 只在设置输入得到此次非按键唤醒 `-2` 且有语言请求时，沿真实调用帧使用 `D12B4 → D19B3 → 106B25 → 105716` 重建页面；`1057E2 → 10580D` 跳过初始化局部、清选择、重读配置和音频淡出。之后原生重新构建标题、底部、`setupscr` 缓存、正文和控件，保留原选择。没有调用带外层帧依赖的 `native_fragment`，没有合成键盘动作。
- 开场在 `18097D → 1254C0` 开始时固定本次语言，具体引言、诗文及开场版本组件始终使用该值。用户可更新全局选择，后续原生页面使用新模式。这样不会把新语言覆盖到未清理的淡入文字上。旧 HDA2 只显示中文，所以初次热迁移的本次开场语言明确保持中文；不依赖已经错过的入口 Before，也不补发过去的调用。

各界面重绘链、缓存所有权和待确认边界见 [重绘依据](20261019-language-redraw-boundaries.md)。没有固定坐标表、整页文本快照、像素跟踪、延迟文字重放或 Present 叠字。

## 状态交接

Host ABI、ModuleDescriptor schema 和 `Active` 布局保持现有值。Adapter 的状态前缀、原生目标记录保持原格式；新尾部标签为 `HDA3`（`0x33414448`），在 native blob 后追加五个 `u32`：全局中文选择、本次开场中文选择、本次 F10 消费标记、设置重建 pending、设置 rebuilding。后续兼容热更新会保留语言，不自动恢复为中文。

只读核对当前正式前代 `cbb25374c24988bb68b13fa6dfaeabafc7fb078cb5d17185263f733ba9bab785`：`save_state` 的 `69E020AA` 指令写入 `0x32414448`，没有语言尾部，符号表也没有 `chinese_enabled`、`intro_chinese`。并行关于批次 `5e25d3fe9e884bcd89aa97e51230833b` 虽链接了尚未接线的输入 helper，但未重新编译当时的 `module.cpp`，仍是 HDA2。故本次按已发布 HDA2 的确定布局迁移，不为未发布的中间草稿添加假设性分支。前代原始指令另存 [状态反汇编](20261019-language-predecessor-state.txt)。

## 已确认限制和历史冲突

“全局”指游戏内实际消费输入的路径，不注册桌面系统热键。原生明确排空丢弃输入的路径继续丢弃，不重新解释旧事件。

开场当前整段不会原地换掉已经画出的文字；本次语言选择在后续页面生效。启动标题和失败等待画面尚无确认的纯显示重建接口；后续原生进度构建使用新选择。未经接入的其他游戏文本仍显示原文。这些边界不以旧 DisplayPlan 或文字重放补齐。

`docs/hot-reload.md:29` 的 `DisplayPlan.logical_slot`、`:39` 的告别页行槽合成及历史状态/缓存交接方案仍与现行约束冲突，影响和待整改状态已在 [开场诗审查](20261019-intro-poem-native.md) 中记录。本次只采用其 Shift+F10 显示开关语义，不采用其历史绘制方案。宿主错误透传等既有待整改事项仍以 [纠正记录](20261019-implementation-correction.md) 为准。

## 交付状态

源码修改、静态审查、统一队列编译及正式热发布均已完成。2026-10-19 02:47:26（Asia/Shanghai）交付回执如下：

- 调用根 `build.ps1 -Module adapter -Publish -Reload -TargetPid 65412`，使用默认 MinGW、项目 `.toolchains/x86/w64devkit/bin/cmake.exe`、同目录 `g++.exe`、`build/mingw-x86` 和正式 `package`。本次提交的 Adapter 源码在批次完成前保持冻结。
- 请求 `7094f2ee64d4467f89fb89e7f4c7c5ac`，批次 `7c017d006dec426f82e3fdaf46c3ac29`。已读取 `build/.compile-queue/results/7094f2ee64d4467f89fb89e7f4c7c5ac.json` 和完整对应日志；`Success=true`，一次配置、一次增量构建。保留既有 SDL `GetProcAddress` 函数类型转换警告，无编译错误。
- 正式发布事务 `ce5e595dfecb4c8abbb5950d8b005e73`，已读取 `build/mingw-x86/stage/ce5e595dfecb4c8abbb5950d8b005e73/publication-result.json`，`success=true`。替换正式 `package/modules/uwcn_adapter.dll`、构建适配和清单三件；旧件先按原相对路径移入 `回收/20261019-024726-ce5e595dfecb4c8abbb5950d8b005e73/`。没有独立修复包或平行启动目录。
- 当前 PID `65412` 返回 `ReadyToPublish` 和 `Applied`，Adapter 第 5 代。正式 Adapter 的 SHA-256 为 `fdfb8e412106050444d98ba9a4572ffe87da1b6c271d7bad0765a699dd76a5ca`，与 Applied 一致；构建适配 SHA-256 为 `f09d198e00a6c47353c89f7e474fc1e322e0db8cb2a98d11c9ece2ae0a5d5de8`。正式清单十项文件均已只读核对磁盘 SHA-256 一致。
- 根 `uwcn_launcher.exe`、驻留桥和其余业务 DLL 沿用正式文件；并行工作已发布的关于和设置接入被保留。未要求用户关闭、重启或手动卸载。

未启动游戏、重新注入、模拟输入、运行测试或交付产物；未创建测试用例和断言。这里的 Applied 仅确认已授权兼容模块交接，不代替快捷键、画面与视觉效果验收。
