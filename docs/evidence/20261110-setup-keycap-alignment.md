# 设置页 ESC 键帽与“退出”重叠修正

用户提供设置页及 ESC 局部截图，中文“退出”压住键帽右缘。本次只读截图、源码与磁盘 PE 指令，不启动游戏、不注入、不模拟输入、不运行产物或测试，不新增测试、断言、保护或回退逻辑。

## 静态原因

对象为 Windows x86 3.89.1 / Steam Build `26139145`。只读反汇编原 `urw.exe`，地址均为 RVA，关键指令摘录保留于本地 `20261110-setup-keycap-disassembly.txt`；原始反汇编按仓库忽略规则不上传，下文记录必要的指令与语义依据。

- 设置页 `106AFC → CFAF0` 提供原 ESC 动作及 `ESC.` 前缀；`CFB95 → 114680` 绘制完整原生按钮。
- `1146C6..1146CA` 取得点号前字节数 n；`1147D9..11481A` 将右帽置于 `x+8*n+7`，宽度 7，故键帽右缘为 `x+8*n+14`。
- `114833` 令文字游标 ESI 为 `x+8`；`114987` 对每个键名字节执行 `ADD ESI,8`；`1149E5..1149F9` 将完整后缀交给 `10E5A0`，原点为 `x+8*n+16, y+5`。键帽和后缀原有两格间距。
- `module.cpp::enter_component_paint` 原先只将 `Kind::button` 的点号前缀识别为原生动作键帽，把设置退出的 `Kind::action_button` 归入 `Scope::creation_button`。这条作用域既用于普通构建时的组件接入，也用于组件重建。
- `windows_creation.inc::dispatch_windows_creation` 的 `about_button_advance` 对该作用域所有标签执行 `native_button::advance`，未区分 `ESC.后缀`。`native_button.h::advance` 以 TTF 完整前缀宽度差取代每次 8 格推进，导致 ESC 三字母总推进缩短，后缀向左挤进仍按 `8*n` 构建的键帽。
- 同一作用域的 `setup_exit_width` 还按整个 `ESC.后缀` 的 TTF 宽度计算命中宽度；键帽逐字调用也错误进入普通文字绘制作用域。只给中文加固定横向偏移会保留这些错误。

## 源码修改

`modules/adapter/module.cpp::enter_component_paint` 将有点号前缀的 `Kind::action_button` 与 `Kind::button` 一样归入 `Scope::setup_exit`；无点号的动作文字仍用原普通文字作用域。

`modules/adapter/windows_creation.inc::dispatch_windows_creation` 按原 `114680` 的点号语义区分键帽前缀和普通文字：

- 点号按钮的键名字节、8 格推进及逐字原位图路径保留；完整中文后缀仍在 `1149F9` 原生调用内即时绘制。
- 完整命中宽度交回既有 `setup_exit_width` 接口，取原 ASCII 前缀及分隔宽度，再加中文后缀真实宽度；原生 `CFC64` 继续写入行宽。
- 无点号普通按钮沿用既有字体度量、中文字符推进及 `< >` 标记分支；本次没有重写该分支。

`module.cpp` 的共享字符补全也只用于无点号标签，与逐字推进资格一致。没有新增坐标、行槽、布局表、文字重放或 SDL 像素观察；按钮图块、位置、选择、鼠标命中和 ESC 动作仍由同一原生函数管理。未修改驻留 ABI、启动器、字体或游戏配置语义。

## 既有问题与待整改

- 本次整改位置为 `module.cpp::enter_component_paint`、`windows_creation.inc::dispatch_windows_creation`：旧接入将原生 ASCII 键帽宽度交给 TTF，影响动作按钮的后缀位置及命中宽度，违反既定原生按钮语义。
- `modules/adapter/native_ui_scene.cpp::Container/Child/paint/materialize_cache/repaint` 仍由 Mod 保存并遍历整页组件序列，页面重建所有权未符合当前约束，影响其他页面及缓存语言物化；仍待整改。本次不新增此类组件或序列，也不将编译或热发布视为其合规证明。
- `modules/adapter/native_footer_component.cpp::paint` 的独立署名排版仍待整改，非此次设置页退出按钮。
- `modules/adapter/native_button.h::width/advance` 对无点号标签仍将含 `< >` 的原串交给字体测量，而 `windows_creation.inc` 的推进分支单独跳过标记；原串宽度与可见字符宽度的契约仍待整改。本次仅纠正点号键帽，未将无点号按钮现有分支保留等同于完整语义已合规。

## 编译与正式交付

源码修改已保存，静态复审覆盖设置、先祖及直接构建的点号按钮，也覆盖无点号 `<Y>es` / `<N>o` 标记文字路径。

- 根入口：`build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 364`，显式使用当前 Proton 的 `WinePrefix` 与 `WinePath`。
- 请求 `4b0df3aafb0e4ad89791c36c009ccd1f`；批次 `bc06d6fb16bc4e92be160bbffa2f7890`。已读取对应 `results` JSON 与完整批次日志，`Success=true`、`PublishRequested=true`、`ReloadRequested=true`；一次配置、一次增量构建完成，保留既有函数指针转换、未使用符号及缩进警告。
- 正式事务 `729305c35c00466c8c9983df95ebb4d4` 于 2026-11-10 11:39:55（Asia/Shanghai）完成；已读取 `build/mingw-x86/stage/729305c35c00466c8c9983df95ebb4d4/publication-result.json`，`success=true`。
- 已更新正式 `package/modules/uwcn_adapter.dll` 和 `package/release.json`；旧两件先按原相对路径移入 `回收/20261110-113954-729305c35c00466c8c9983df95ebb4d4/`。
- 正式 DLL SHA-256 为 `c516094c9bec91879dd7c31ce078b77dba0c5a4893b74460c097307360dc62f3`，与构建输出和正式清单一致。
- 用现有 Proton Mono 解释器只读枚举确认 Windows PID `364`，既有兼容事务返回 `ReadyToPublish`、`Applied ... adapter:c516094c9bec91879dd7c31ce078b77dba0c5a4893b74460c097307360dc62f3:4`，运行中 Adapter 第 4 代交接完成。

源码修改、产物编译、正式位置发布及当前进程模块交接均已完成；未运行游戏测试或视觉验收，不以 Applied 回执代替画面结果。
