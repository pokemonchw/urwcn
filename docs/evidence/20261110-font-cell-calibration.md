# 中文字号：前景字格与原生描边校准修正

日期：2026-11-10。用户提供英文与中文主菜单对比图，反馈中文明显偏小。本轮只读截图、源码、字体和游戏字模等静态资料；不启动游戏、不注入、不模拟输入、不执行产物或测试，不添加测试和断言。

后续更正（2026-11-11）：下文的十行前景格是通用字模存储契约，不能证明每个组件的可清除墨迹范围都有十行。主游戏状态栏在原生框内偏移三行后绘字，其可清除范围只剩九行；此前 `render_request` 的统一十行参数未接入这个组件契约，会允许字形覆盖框底。该处已在源码接入真实框参数，详见 [状态栏修正记录](20261111-hud-condition-native-cell.md)。其余通用校准算法沿用，下文历史交付不代表这处问题已经解决。

## 静态依据与原因

- 当前正式 `package/modules/uwcn_render.dll`、`uwcn_adapter.dll` 均为 Windows PE32，采用 MinGW 发布。上一轮读取的 Linux 字号记录不能替代此包的实际路径。
- `modules/adapter/module.cpp::render_request` 和 `windows_renderer_text.inc` 统一传入前景字格 10、墨迹预算 9。文字测量与即时绘字都进入 `FontEngine::font`。
- 原生 `10BD90` 的字模循环覆盖 8×10 前景格；原 `10E5A0` 在此之外分别以 y−1、y+1、x−1、x+1 调用完整串绘制，再绘前景。已有静态入口见 `rebuild-ui-boundaries.txt:104` 起与 `font-rendering-static.txt:98` 起；3.89.1 文字入口契约见 `20261110-windows-3891-native-contracts.md`。10 是前景字格高度，不能把其误解释为前景加外部描边的总高度。
- 只读解析本机 `URW.FNT`：长度 20480=256×8×10；A–Z 非零 mask 行均为 0..6，小写 g/p/q/y 为 2..7。字格高度与可见字面高度本就不同。
- 只读 fontTools 解析当前 Proton `msyhbd.ttf`，unitsPerEm=1000：国轮廓 y 为 −89..810，载为 −97..849，入为 −80..844，角为 −98..854；竖线为 −284..851。英文降部、竖线、汉字和标点形成的共同基线并集大于单个汉字字面。该轮廓数据用于解释约束错误，不代替运行时非零 alpha 校准，不声称某个固定字号或增大比例。
- 原 `font_engine.cpp::font` 同时要求整个参考集并集 ≤9，以及并集加上下描边 ≤10。描边为 1 时，实际把前景并集压到最多 8 逻辑像素；同时把跨字基线并集误当成单字墨迹预算，使常用汉字进一步缩小。

## 源码修正

`modules/render/font_engine.cpp::FontEngine::font` 对完整固定参考集与完整词库继续逐字读取非零 alpha：单字 `b-a` 受 9 的墨迹上限约束，整个字集 `bottom-top` 受 10 的前景格约束。不在前景格中再预留外部描边。仍从大到小选择一个统一的最大合格字号，不排除 Windows ASCII，不按当前菜单、文本或单字临时选字号。

完整字集并集及原生描边仍共同确定稳定基线；测量和 surface/renderer 即时绘字共享同一字体配置和实际目标密度。原生五次绘制的偏移、顺序、颜色及裁剪保持原义，Render 不额外画描边。不新增 UI 坐标、布局、重放、保护或回退分支，不改变 Host ABI 或驻留桥。

## 文档纠正与待整改

- `docs/font-rendering.md`“固定参考集与字号校准”旧正文把“完整包络及描边必须塞进 10”写成原生要求；该约束来自旧实现，缺乏原生依据，现已纠正。`font-rendering-static.txt`、`20261019-linux-font-size-weight.md` 等日期较早记录保留历史状态，不代表本次校准规则或本次正式发布。
- Linux `src/linux/adapter.cpp::glyph_request` 尚未把原生描边样式传入请求的既有问题，见 `20261019-linux-font-size-weight.md` 的待整改表。本轮修正共享校准算法，不宣称该接口问题已解决，也不将 Windows 产物当作 Linux 交付。

## 编译与正式发布

- 统一入口：`.toolchains/powershell/pwsh -NoProfile -Command '& ./build.ps1 -Toolchain MinGW -Module render -Publish'`。
- 请求 `bf2ef3eda486456eb9c8b23dfcccaac4`；批次 `1ae33c2762df4e3dbc22f11458686d3a`。已读取对应 results JSON 与完整批次日志，`Success=true`、`PublishRequested=true`、`ReloadRequested=false`。一次配置与一次增量构建完成；日志中保留既有 `GetProcAddress` 函数指针转换警告。
- 正式事务 `81784499d67e412a9e6593cd82bbd3f2`，已读取 `build/mingw-x86/stage/81784499d67e412a9e6593cd82bbd3f2/publication-result.json`，`success=true`。
- 已替换正式 `package/modules/uwcn_render.dll` 并更新 `package/release.json`；旧两件先按原相对路径移入 `回收/20261110-110526-81784499d67e412a9e6593cd82bbd3f2/package/`。
- 正式 DLL SHA-256：`92321da0907376fe60dcd1c88026a4b2cc04a4869bfb19f53a0d722c766ea4b5`，与编译输出和正式清单一致。

源码修改、Windows 产物编译与正式文件发布均已完成。本批次未请求运行时加载，回执 `runtime_requested=false`，不能称为运行中的游戏已应用更新。未运行产物或测试，视觉效果未由代理运行验收。
