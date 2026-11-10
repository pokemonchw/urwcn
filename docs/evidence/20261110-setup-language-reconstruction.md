# 设置页语言切换后的底栏、路径和选择状态

用户截图显示：中文设置页有底部说明框、安装目录及“地图网格”选择；切回英文后选项和说明还在，但底部面板、安装目录消失，选择回到 FULLSCREEN。本次只做静态源码与原 PE 指令审查，没有运行游戏或测试。

## 原因与原生边界

`modules/adapter/native_language_redraw.cpp` 上一版本只有先祖页完整 continuation，设置页的 `106B25/1057E2` 两个已确认边界遗漏。`module.cpp::invalidate` 先调用 `native_ui_scene::language_changed` 物化组件集合再处理原生选择。该集合没有完整承接设置页的 `10582A → F210` 底部面板与 `105891 → 10E5A0` 原安装目录，因此单凭它重画正文不足以恢复整个设置页。

`native_ui_scene.cpp::InputView` 保留逻辑菜单句柄；`native_menu_model` 的原生 header 包含 `5F54AB0` 选择字段。Scene 内菜单、动作及缓存物化涉及整块 header，不能据此承诺保持物化前的实际选择。本次不把某一条 activate 写操作当作已证明的最终归零点，而是直接取消设置页切换时的这次 Scene 物化。

既有证据 `20261019-language-redraw-boundaries.md` 的设置段及历史源码 `ec0cfa8:modules/adapter/native_language_redraw.cpp` 已确认完整 continuation。本次对当前安装的 3.89.1 原 PE 只读反汇编再次确认以下边界，原地址与字节一致：

| 边界 | 本次处理 |
| --- | --- |
| `D12B4` | 仅 pending 设置重建、EAX=-2 且真实 `[EBP+4]==base+106B25` 时继续 D19B3，沿原 epilogue 正常退出输入。 |
| `106B25`，`8B F0 83 FE 64` | 设置 ESI 为真实原生选择 `5F54AB0`，在原设置帧中继续 105716。106B20 保持原 CALL，不改变其返回地址。 |
| `105716..1057E2` | 原生背景、全页面板、标题、颜色和上传流程。 |
| `1057E2`，`C6 45 8A 00 33 F6` | 重建时继续 10580D，避开三项局部清零、ESI 清零、1057F0 配置初始化与105804音频淡出。普通首次进入仍执行原指令。 |
| `10580D..1058A5` | 原生解析底部提示，绘制底框，重新取得并显示 `_getcwd` 原路径，再通过 1058A0 保存同名 setupscr。 |
| `1058B0..106B20` | 原生恢复新 setupscr 并构建正文、选项与退出控件；106B0E 把 ESI 写回实际选择，随后原呈现和输入继续。 |

不重新调用整个 105700，不使用依赖外层帧的 native_fragment，不保存帧指针或整页字段，不修改配置值、按键动作或保存流程。路径由原 `_getcwd` 和显示调用重新生成，不建立 Mod 路径快照。

## 语言版本与状态所有权

`invalidate` 使用已接入设置面板的原始 SourceKey `{current root,105752,setup_title}` 识别此页：只读已发生的原生构建身份，未增加页面内容快照。这适用于已观察到该构建入口的页面，不承诺追补旧版本从未发生的 Before。

设置页只递增语言版本并刷新对应语言资源，不遍历物化 Scene 或其旧缓存，不在 continuation 前重画选择或呈现部分画面。原设置构建负责替换 setupscr；其余缓存仍保留旧版本标记，按已有原生恢复边界处理。由此真实选择原值直到106B25都未经过此次Scene重画，随后交回原ESI和106B0E流程。

`State` 仍只有两个 u32。pending 位依次为菜单同步、先祖重建、原生输入退出、设置重建；rebuilding 值1为先祖、2为设置。各自钩子只处理自己的阶段，不更改交接大小或驻留 ABI。全部新增逻辑都在可热更新 Adapter，未修改驻留库、启动器或 SDK。

## 既有不合规部分与过期说明

- `native_ui_scene.cpp::Container/Child/paint/materialize_cache/repaint` 的整页组件序列重建所有权仍在 Mod，不符合当前原生 UI 所有权要求；先前证据已登记，本次设置语言切换不再走它，其余页面待整改。
- `native_footer_component.cpp::paint` 的独立署名排版仍待整改，非本次设置页 F210 原生底栏。
- `20261019-setup-options-native.md` 的“没有确认完整刷新接口”属于早期接入状态；后来的原帧 continuation 已有证据，本次重新接回。
- `20261019-language-redraw-boundaries.md` 描述的旧 Hook 和 pending 编号以本记录及当前源码为准；不能仅因旧文档写“当前源码已包含”便认定前一发布实际接线完整。

没有启动游戏、模拟输入、运行测试、创建测试脚本或断言；兼容热发布仅用于用户已授权的正式业务模块交接，不作为画面验收。

## 交付结果

源码修改完成。根 build.ps1 MinGW Adapter 请求 `3e032215fac74a7b85b2d7ee88caa56d`，批次 `baba5b06374e49d5a20bee591860a231` 成功；已读取请求结果 JSON、批次日志和发布事务 JSON。编译保留既有函数指针转换、初始化、缩进和未使用项警告。

正式发布事务 `56abb975f20e4b0ab08d1bbe027b07d4` 更新 `package/modules/uwcn_adapter.dll` 与 `package/release.json`。旧文件先移入 `回收/20261110-113348-56abb975f20e4b0ab08d1bbe027b07d4/`，保留相对路径。通过现有 Proton 解释器只读枚举确认 Windows PID 为364，使用既有控制事务获得 `ReadyToPublish`、`Applied ... adapter:fbced7dd549dd1d47e3e6108c419a568b5a7724b2a30ae03d4b782b1b41ca07b:3` 回执。

产物编译、正式位置发布及当前进程兼容模块交接已完成，没有改驻留库或重启游戏；原生页面重建后的视觉效果仍须用户验收。
