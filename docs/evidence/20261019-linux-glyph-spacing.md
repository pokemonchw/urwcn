# Linux Heavy 中文字距修正

日期：2026-10-19。对应用户截图 `codex-clipboard-733c873d-58fe-4109-8b90-35dcea8bec55.png`，反馈开局情境选择页文字在加粗后粘连。本次只静态读取源码、原 ELF 和发布回执；不启动游戏、模拟操作、运行产物或测试，不编写测试用例、断言、保护或回退分支。编译用于交付，兼容业务热发布使用项目已授权事务。

## 原因与原生边界

- `modules/render/font_engine.cpp::font` 已使用思源黑体 Heavy face 22；`measure` 返回按目标密度换算的字体宽度。修改前 Linux Adapter 将这个宽度直接作为每个非 ASCII 字符的推进量，没有为加粗后的中文增加字距。
- 对本机已记录 SHA-256 的 Linux `urw3-bin` 只读反汇编：`showtext:0x13e8b0` 在 `0x13ea48/0x13ea58` 绘制上下阴影，在 `0x13ea67/0x13ea76` 绘制左右阴影（原 x−1 / x+1），最后在 `0x13e9b3` 绘制前景。描边继续占用相邻字之间的横向空间；这些调用及其颜色、位置、次数不修改。
- 软件文字原生边界为 `textwidth:0x13b460`、`textput:0x13b760`，renderer 为 `rentextput:0x13de10` 和 `New_rentext:0x13e1b0`。现有完整串扩展将非 ASCII token 交给同密度的字体服务，ASCII 仍由原生字形绘制并推进8逻辑像素。
- 原生居中 `0x13eb6f/0x13ec9c`、段落宽度与推进 `0x13eec3/0x13f00f`、标题 `0x14709b`、按钮 `0x1452e3/0x145286` 和光标 `0x13ea00` 已消费 Adapter 的完整字符串度量。renderer 对应边界由 `src/linux/spells.inc::renderer_text_width` 提供统一宽度，不应漏改这一条路径。

## 源码修改

1. `src/linux/adapter.cpp:93` 新增共享 `glyph_advance`，返回实测逻辑宽度加 **2逻辑像素**。这是本次针对 Heavy 字重的字距调整，不是更改字体自身宽度或创建页面坐标。逻辑字距随已有原生目标密度进入输出；例如2倍输出时，相邻字符起点额外拉开4输出像素。
2. 软件面度量缓存、软件面绘制、renderer 绘制以及 `src/linux/spells.inc:33` 的 renderer 测量全部使用这一推进量。末字符保留完整字符格，与原生逐字累加语义一致；原生折行、居中、按钮和光标获得与绘制相同的宽度。
3. 字号、字重、基线、阴影顺序和 ASCII 字格不变。词库不插入空格，原生中文分词用的空格不作为额外可见字距。没有字形拉伸、页面坐标表、UI 布局副本或延迟重放。
4. `src/linux/adapter.cpp::invoke` 将 Adapter 自身变更位32与 Render 变更位4一并纳入字体失效；沿已确认的主菜单、关于和鸣谢完整重建边界消费。截图中的情境选择页沿已有 `scenario_selection_refresh` 和 `LIST_Go:0xf871f` 输入返回流程重建背景、文本、菜单缓存及当前选择，不模拟输入。
5. Linux profile 和字体规范同步记录字距规则。变更前源码与规范保存在 `回收/20261019-linux-glyph-spacing-source/`，保留原相对路径；此前未提交的情境汉化及其他修改保持。

## 既有待整改边界

- `src/linux/adapter.cpp:88` 的 `glyph_request` 仍未将原生阴影样式传入完整包络校准。当前字距补充了横向字符间隔，不能替代纵向描边预算或整串外缘包络；此项继续待整改。
- `src/linux/native_targets.cpp::synchronize_main_menu` 仍只在已确认的主菜单边界完成随窗口尺寸变化的整页目标重建；其他页面中途缩放的一致性继续待确认。不会为本次字距增加全局像素跟踪或文本重放。
- `publish.ps1` 的 Linux desktop 显示名仍为 `UnReal World 简体中文`，未采用约定译名“不真实的世界”；此既有标题问题仍待整改，本次不将其视为符合命名要求。

## 交付状态

源码修改、统一队列编译和正式热发布均已完成，时间为2026-10-19 17:53:32（Asia/Shanghai）。本次仅编译发布 Adapter，Render 二进制与驻留 ABI 不变。

```sh
.toolchains/powershell/pwsh -NoProfile -Command '& ./build.ps1 -Toolchain Linux -Module adapter -Reload -TargetPid 3968932'
```

- 请求 `45824ee3dbde4f669be81e93b8118274`，批次 `b66e2889c81f4b9aa71cffa8a0421ed8`。已读取对应 `build/.compile-queue/results/45824ee3dbde4f669be81e93b8118274.json` 和完整 `build/.compile-queue/batches/b66e2889c81f4b9aa71cffa8a0421ed8.log`：`Success=true`，一次配置、一次增量构建，无编译警告。提交后至批次结束没有修改请求范围源码。
- 事务 `97e9ca724cee46ac9d33a98b17328397`，已读取 `build/linux-x86_64/stage/97e9ca724cee46ac9d33a98b17328397/publication-result.json`：`success=true`。PID `3968932` 返回同一事务的 `ReadyToPublish` 和 `Applied`，Adapter 第4代已加载。
- 正式更新 `package/modules/uwcn_adapter.dll`、Linux profile 与 `package/release.json`。旧三件先按原相对路径移入 `回收/20261019-175332-97e9ca724cee46ac9d33a98b17328397/`；发布器同时归档应用菜单旧链接。旧 Adapter SHA-256 为 `73cd34fc1fe30b9528e4b7fa2698e4aae4ecd4c76bb876ece267b1a3c4853c2c`。
- 新正式 Adapter SHA-256 为 `bf3207cc2c0cd61beb21ed891732d1f50b27cd4dbd6cf5eaf9c83396f0dcb334`，与构建产物、正式清单和 Applied 回执一致；正式 Linux profile SHA-256 为 `8a01df9948a8c815b473ef9b62bd62d984670c3a1c746492f4b1cc95d68aa331`，与源码和正式清单一致。

Applied 证明正式文件和兼容业务模块交接完成，不能替代实际画面验收。当前情境选择页在下一次正常原生输入返回时消费已有刷新标记；没有模拟事件、读取运行画面、关闭或重启游戏，也没有自行运行测试。
