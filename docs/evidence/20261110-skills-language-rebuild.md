# 技能页切回英文后控件信息丢失：原生构建边界修正

日期：2026-11-10。对象为 Windows x86 不真实的世界 3.89.1 / Steam Build 26139145；本机原 `urw.exe` SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`，与正式 profile 一致。地址均为 RVA；静态反汇编按首选基址 `0x400000` 显示 VA。本次只读源码、文件和原 EXE 指令，没有启动游戏、注入、模拟输入、运行测试或创建测试、断言。

## 根因、影响与整改状态

用户提供的两张技能页截图显示：切回英文后技能名仍在，但进度条、百分比、熟练度、天赋星号、帮助框和点数数字等信息消失。此处不是只更换文字时遗漏翻译，而是完整原生控件没有纳入现有语言重建边界。

- `modules/adapter/native_ui_scene.cpp:173` 的 `paint()` 先重建原生根背景，再绘制已登记的完整组件；`:594` 的 `repaint()` 与 `:604` 的 `language_changed()` 沿此路径更新当前面及原生缓存。旧技能接入只覆盖文字消费者，没有登记原 `Piirra_SkillInfo` 和 `NaytaOptioRuutu` 完整控件，因此背景重建抹去它们后，组件列表无法重新生成条形、数字与其它控件内容。缓存物化采用同一不完整来源，单纯重载模块不会凭空补齐缺失的构建身份。状态：本次补入对应原生控件构建调用；不以发布或编译成功代替用户视觉验收。
- `modules/adapter/windows_skills_spells.inc` 原 `ws_help_paragraph` 仅挂 `E0CBE → 10EB40`，这次高度为 `-1`，实际负责测量。`modules/adapter/native_component_binding.cpp` 的普通段落分支跳过测量调用，后续根据测量高度构建的帮助窗口和正文也没有形成完整组件。因此当前页/缓存重建会丢失整个帮助框。状态：在 `native_component_binding.cpp:254` 将该边界识别为完整 `skill_help`，保留原帮助输入记录，复用原生测量、面板和正文片段。

这些旧接入未按完整原生组件语义消费文本及相关控件，不符合本项目的完整原生显示边界要求；既有编译和交付不构成合规依据。本次整改范围是已确认的技能信息、点数控件及技能帮助面板，不据此宣称所有原生页面均已审查完整。

## 技能信息完整控件

静态原函数 `E03D0..E05DF`，与 Linux 已确认的 `Piirra_SkillInfo` 对应。Windows 调用为 `E0746 → E03D0`，位于 `AsetaTaito` 尾部；`EDX` 是原生行 Y，第一栈参数是原生技能 ID，原调用者清理4字节，函数不读取 `ECX` 输入。

原函数读取原生技能数据，绘制技能进度条和初始值区、百分比、原阈值已选中的熟练度及天赋星号；原数据读址为 `A32AB86`、`A32AAF0`、`A32A992`、`A32A960` 加原技能 ID。已见写入 `61BBAD4` 和 `A2110D0` 属于条形/文字的显示临时状态，不进行技能增减或点数扣除。

本次 `SkillInfoInputs` 只保留这次原函数的技能 ID 与原生 Y 输入，使用根身份、原函数身份和技能 ID 登记一个 `Kind::skill_info`。`native_component_model.cpp:654` 调用完整原函数；数值和星号仍从游戏自己的技能数据产生，中文熟练度仍在原格式化边界生成。没有保存数字文字、逐字位置、像素或另建行槽表。

## 点数完整控件

`11D20..11F03` 为原 `NaytaOptioRuutu` 的完整绘制函数，无调用者参数；两个普通调用为 `E0E2A → 11D20` 和 `1213D → 11D20`。函数从原生剩余点数、允许提升/降低次数读取状态，绘制窗口、数字框、动态限制段落及提升/降低按钮。它只写入文字光标、颜色和描边等 UI 临时字段，不修改点数、技能或按键动作。

本次以根身份和原函数身份登记唯一 `Kind::skill_options`，两个原调用更新同一控件。`native_component_model.cpp` 原样调用 `11D20`；内部原翻译调用继续生成标签和限制段落。`SkillOptionsInputs` 同时保留原窗口样式，绘制使用 `PanelScope`：`11D20` 在首个 `11D4F → 116270` 调用前没有设置 `61BBAC8`，而 `1162F5/1163CC` 实际读取该背景模式，决定纹理背景与半透明填充分支，因此必须保留调用者的真实样式。没有将点数业务计算复制到 Mod，也没有重跑包含输入和加减点操作的整个技能页。

## 帮助面板原生测量、构建与绘制

静态纯绘制片段 `E0CA9..E0D22` 使用已构建的原生帮助词表：

1. `E0CBE → 10EB40` 以高度 `-1` 测量当前语言的完整段落；结果写入 `ESI`。
2. `E0CDF → 115E70` 用 `ESI+25` 生成原帮助窗口及背景；原生负责全部窗口坐标和尺寸。
3. `E0D1A → 10EB40` 按同一 `ESI` 绘制正文，保留原颜色及描边。
4. `E0CE9` 的 `ADD ESP,20h` 平衡此前测量和面板累计栈参数；`E0D1F` 的 `ADD ESP,10h` 平衡正文的四个参数，包括原 `SDL_MapRGBA` 调用留下供正文消费的描边值。

片段不读取外层 `EBP` 局部变量，不进入菜单初始化、等待、技能使用、加减点或文件写入路径。`E0D22` 原本开始设置后续菜单显式行开关，位于纯绘制片段之外。本次仅当 `painting_skill_help()` 为真时，在此边界转入 `urwcn_component_fragment_return()`，从片段的已平衡栈返回；普通原生进入仍执行原指令。

`SkillHelpInputs` 保留原窗口样式，`ParagraphSource` 保留原帮助文件输入的中立语义记录。重建时通过既有中文词元、原生段落解析和度量接口重新生成词表，再执行上述原片段。`urwcn_component_skill_help` 保留 `EBX/ESI/EDI/EBP`，不会依赖任意外层页面局部变量。窗口高度继续来自本次原生测量，没有冻结上次语言的高度或最终文字坐标。

## 登记、序列化及范围

`native_component_binding.cpp:239` 的 `construct()` 在进入完整控件前登记其组件作用域，内部文字消费者仍负责中文显示，但不会重复登记为独立页面字段。物化期间沿既有 `materializing()` 边界禁止重新捕获组件。三个新增 `Kind` 均追加在旧枚举末尾；Writer/Reader 以相同字段顺序读写，旧类型序号不变。瞬时帮助绘制标志不进入跨代状态。

点数控件和帮助片段会使用共享原生段落临时词表。本次在这两个完整组件结束并退出绘制作用域后，经内部 `PaintServices.restore_parser()` 调回既有 `restore_paragraph_builder()`，以当前调用者的中立语义记录恢复同一原生临时词表，避免缓存重建留下另一组件的词表。回调只作为同步内部服务传递，不写入组件或跨代状态；原帮助测量和普通绘制过程继续保留其自然词表及返回高度。`module.cpp:433` 将完整帮助组件纳入原段落文字作用域，中文字元测量和绘制保持一致。

本次没有改变原技能英文身份、角色数据、选项值、加减点动作、输入动作、配置保存或缓存生命周期；没有新增全局像素扫描、文字绘制贡献序列、Present 叠加、整页快照或推测性兜底分支。中文字形继续在对应原生组件调用中提交，原生 UI 管理其度量、排版、面板、缓存及呈现。

## 交付状态

源码修改、只读静态审查、统一队列编译及正式发布完成。原始指令另存于同目录的 `20261110-skills-info-native-disassembly.txt`、`20261110-skills-options-native-disassembly.txt` 和 `20261110-skills-help-native-disassembly.txt`。源码提交后至所属批次结束，没有继续修改该批次源码。

两批均使用根入口：`.toolchains/powershell/pwsh -NoProfile -File ./build.ps1 -Toolchain MinGW -Module adapter -CMakePath /usr/bin/cmake -CompilerPath /home/lulika/.local/share/dfcn-toolchains/mingw-w64-16.2.0/usr/bin/i686-w64-mingw32-g++ -BuildDirectory /home/lulika/workspace/urwcn/build/mingw-x86 -PackageDirectory /home/lulika/workspace/urwcn/package -Publish`。

- 首批请求 `858f044ab2d54043922a78151c61bff1`，批次 `bbaf4a2439974da890fa0cdc0d04240b`，发布事务 `d97beb4ee159419cb709f5f4942051f7`。完成后，最终静态审查确认上述点数窗口背景样式依赖，补齐样式后提交第二批。
- 最终请求 `3bba3d109a38428eb0a98ac59c7a16ad`，批次 `678fb28c378c443c9f56fb5aa4921fd0`，发布事务 `3fbabbb336f24674adc04ca15d6ab29d`，完成时间 `2026-11-10 11:11:38`（Asia/Shanghai）。已读取两次 `build/.compile-queue/results/<请求>.json`、对应 `batches/<批次>.log` 和各自暂存目录的 `publication-result.json`；均为成功，每批一次配置、一次增量编译。编译存在既有函数指针转换、缺少成员初始化、未使用项等警告，没有编译错误。
- 最终正式文件 `package/modules/urwcn_adapter.dll` 与构建产物 SHA-256 一致：`d7eb0b2fe79fd8afbcf7a8cda07fc58f549218345df3e74446979ded28468443`。同时更新正式 `package/release.json`。正常根启动器的正式模块位置已经更新，没有创建平行运行包。
- 两次被替换的旧 Adapter 和清单，分别先移入 `回收/20261110-111034-d97beb4ee159419cb709f5f4942051f7/package/` 与 `回收/20261110-111138-3fbabbb336f24674adc04ca15d6ab29d/package/`，保留原相对路径；已读取归档目录确认旧 DLL 存在。
- 只读进程列表未发现本项目游戏进程，本次没有执行 `-Reload`。发布回执 `runtime_requested=false`、`runtime_receipts=[]`；不宣称运行中旧技能页已经恢复。本次新增控件来源由其原生构建调用登记，不补造旧版已丢失的来源快照。

未启动游戏、运行产物、注入、模拟操作或执行任何测试，未新增测试用例、测试脚本、断言、保护或兜底分支。以上是源码、编译及正式文件交付状态，界面效果尚未由用户验收。
