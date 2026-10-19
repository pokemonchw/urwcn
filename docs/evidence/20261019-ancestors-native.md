# 2026-10-19 已故角色列表原生汉化

本次针对用户截图中的先祖列表，接入标题、空列表提示、排序标题、ESC/P/L/J/PgUp/PgDn 按钮后缀、非空选择提示、页码及两条角色统计。姓名和存档中的死亡描述是既有记录内容，原样显示。点击记录后的纪念页及角色死亡分支不属于本次新增接入。

## 原生调用与文本所有权

地址均为 UnReal World 3.89、Steam Build 25939378 的 RVA。静态依据为 `ancestors-disassembly.txt`、`ancestors-row-disassembly.txt`、`ancestors-button-disassembly.txt`、`ancestors-select-disassembly.txt` 与 `ancestors-ghidra.c` 中的原始指令及反编译内容；不采用旧说明里的独立布局建议。

| 字段 | 已确认边界 | 实现 |
| --- | --- | --- |
| 标题 | `DEA14 → 1157B0`，3 个栈参数 | `ESI=-1` 为原生列表模式；借用 `args[1]` 中文，style=1 左对齐，文字通过已有 `115A94`。死亡分支仍用原文。 |
| 空列表、排序标题 | `DEEE6`、`DEF72 → 10E5A0` | 本次调用借用完整中文，原坐标、颜色与描边由游戏给出。 |
| 六种操作按钮 | `DEF21/DEF91/DEFC8/DEFFF/DF03A/DF081 → CFAF0`，2 个栈参数 | 保留原 ASCII 按键前缀及点号，只翻译后缀；共享 `1149F9` 文字与 `CFC5D` 真实后缀宽度接口。键帽、按钮几何、选择与命中仍由原生生成。 |
| 非空选择提示 | `DEEB0 → 10E720`，2 个栈参数 | 提供带原 `[ENTER]` 的完整译文。原生按字节组装完整前后串；编码高位字节不与 ASCII 方括号冲突。`10E862/10E8F2` 进入现有文字与光标度量链；`10E890` 仍绘制原生 ENTER 键帽。 |
| 页码 | `DF0BB → sprintf`，4 个栈参数；`DF115 → 10E5A0` | 使用原生 `args[2]/args[3]` 当前页和总页数，在本次显示缓冲内生成“页码：P / T”。分页出现条件不变。 |
| 当前摘要行 | `DEDA0 → DD400`，2 个栈参数 | 只覆盖原生 detail=0 调用；不接管 `DF36F` detail=1 纪念页调用。 |
| 寿命与冒险天数 | `DD670 → sprintf`，5 个栈参数；`DDA0A` 显示 | 读取本次 `args[3]/args[4]`。在显示叶生成“逝者享年 A 岁，度过了 D 天冒险生涯。”。 |
| 行走距离 | `DD6D6 → sprintf`，4 个栈参数；`DDA30` 显示 | 使用 `args[3]` 的原生整数公里数，保留原 floor 与 CVTTSS2SI 运算。 |

三项统计整数只在本次原生 `DEDA0` 调用期间存续，由已有 `Active` 所有权在调用返回后释放；不保存行号、坐标、裁剪、样式、整页字段或待重放文字。`DD670/DD6D6` 后的原生 toupper 仍处理原英文缓冲，中文直到 `DDA0A/DDA30` 才借给文字调用，避免让高位传输字节进入 ASCII 大小写转换。

中文组件使用 `TextComponent::ancestors_*` 的 `0x900–0x90C` 段，沿已有 Semantic/Catalog/原生编码服务处理。既有鸣谢 `0x700`、创建角色 `0x800` 组件不改号；Host ABI 1、TextRequest 及 Active 布局保持原值。

最终字形即时绘入已确认的原生实际密度目标；宽度使用与绘制相同的字体度量。原生控件、背景、缓存、绘制顺序、输入和生命周期继续运行。没有 Present 叠字、固定坐标/行槽、像素跟踪或延迟文字重放。

## 当前页重建

沿用全局 Shift+F10 选择，在原生 D1120 非按键返回边界使先祖列表重走背景、标题、缓存及列表绘制。原排序数组、分页偏移、选择和游戏输入语义保持。热发布依赖刷新会设置先祖重建请求；当前已打开页面须原生输入循环抵达对应非按键唤醒边界才重建，不以 Applied 回执宣称屏幕已经刷新。详见 [原生重建指令依据](20261019-ancestors-redraw-native.md)。

## 发现的旧文档冲突

- `docs/evidence/ancestors-static.txt` 原第 34、46–47、212、233、249、258、310–315、335、339–343 行包含短中文 display plan、固定行槽、字段快照、DF127 完整计划与 Present 合成建议；这会夺取原生 UI 的排版/缓存所有权，违反现行约束。现已在文件头标注过期；上述方案不采用，历史正文保留待清理。
- `docs/design.md:19`、`docs/framework-design.md:15`、`docs/hot-reload.md:23` 的历史先祖方案和旧交付路线仍有冲突，状态为待整改，不能作为当前实现依据。当前实现以上述原生调用及本记录为准。
- 既有宿主错误透传及事务失败语义问题仍按 `20261019-implementation-correction.md` 记录，不把本次汉化或编译成功视为全项目合规结论。

## 交付状态

源码修改、统一队列编译和正式热发布均已完成，时间为 2026-10-19 08:17:09（Asia/Shanghai）。没有启动游戏、重新注入、模拟输入、运行产物或测试；没有添加测试用例或断言。

- 根入口命令：`build.ps1 -Module adapter,semantic,catalog -Publish -Reload -TargetPid 65412`。使用默认 MinGW、`.toolchains/x86/w64devkit/bin/cmake.exe`、同目录 `g++.exe`、`build/mingw-x86` 及正式 `package`。提交后本任务源码保持冻结至批次完成。
- 请求 ID：`332a1669776c48559b41f0ceeeb1306f`；批次 ID：`22ac1ead4ed94d49bbcafcfffe5bed5c`。已读取对应 `build/.compile-queue/results/332a1669776c48559b41f0ceeeb1306f.json` 和 `build/.compile-queue/batches/22ac1ead4ed94d49bbcafcfffe5bed5c.log`，`Success=true`。该批次一次配置、一次增量构建；Adapter 的两个源文件重新编译，Catalog/Semantic 目标已是最新。仅保留既有 SDL `GetProcAddress` 转换警告。
- 正式事务：`a3cb9e6df32c47f7985f0cc73ae2dd41`。已读取 `build/mingw-x86/stage/a3cb9e6df32c47f7985f0cc73ae2dd41/publication-result.json`，`success=true`。本事务实际更新 Adapter、构建适配与清单三件；旧件先按原相对路径移入 `回收/20261019-081709-a3cb9e6df32c47f7985f0cc73ae2dd41/`。
- PID `65412` 返回 `ReadyToPublish`、`Applied`，Adapter 第 7 代；正式 `package/modules/uwcn_adapter.dll` 的 SHA-256 为 `f106a36555b7528cf0e5aa6f22966b25bdd5d7417fbc489e92038c0d5d2252b3`，与 Applied 一致。
- 先祖文本服务和词库已随并行前批次 `3a8077d74baf4b8c81163a6d107dec37` 的事务 `47b3089b3f5a48fdb39bc09ef77963a3` 正式发布；其发布记录显示 Semantic/Catalog 第 3 代 Applied，旧件已回收到该事务目录。本批次选择同样三个模块后，只有新 Adapter 内容需要替换，不能将该前批次的编译算作本批次重新编译。当前正式 Semantic SHA-256 为 `2d826d31f2a07d6d93386d2e8ab0327496926f237ad34426983d7d2a469bc218`；词库为 `558d5e2f38b5d03774faa158cb84e59f6168598a20c66d7551ec9dea35af20f7`，包含全部 13 个 `ancestors.*` 条目。两件均与本次正式清单一致。
- 当前正式构建适配 SHA-256 为 `90a7f95be8a4a5d4656892c842105ad97ac9b59517839d38ed4e6d8dbbf5dc75`，与本次清单一致。启动器和驻留桥保持正式路径；没有并行运行包、手动卸载或关闭/重启游戏操作。

本请求返回前队列还执行了一次其他请求的后续增量批次；那不是本请求所属批次。以上成功结论只取本请求结果、对应批次日志、正式发布记录和文件身份。Applied 确认兼容模块交接，不代表画面已在同一时刻刷新或视觉效果经过验收。
