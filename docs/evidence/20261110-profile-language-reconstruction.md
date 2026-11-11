# 属性确认页切回英文后信息丢失

2026-11-11更正：用户确认Shift+P直接退出，静态发现mode 0共用年龄消费者误读仅非零mode登记的 `profile_start_age`，会解引用缺失来源。该项不在本文mode 1的修正闭环内；实际整数／字符串参数和三个年龄生产者的整改见[Shift+P资料页年龄来源修正](20261111-shift-p-profile-age-crash.md)。

2026-11-10 后续状态：共用 Scene 擦除路径已移除，`invalidate` 不再依赖 Scene 来源识别属性页；属性 continuation 保留，由真实 D1120 调用者身份确认。下文源码描述为该属性修正阶段的记录，最新编译与正式热发布回执及剩余即时刷新限制见 [共用语言重建整改](20261110-common-language-reconstruction.md)。

日期：2026-11-10。对象为 Windows x86《不真实的世界》3.89.1 / Steam Build 26139145；本机原 `urw.exe` SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。下文地址为 RVA，磁盘 PE 反汇编采用首选基址 `0x400000`。只读源码、原 PE 指令和进程身份；未启动游戏、注入、模拟输入、运行游戏产物或测试，未创建测试、断言及猜测性保护或兜底分支。

## 根因与整改范围

截图中英文界面的右侧棕色说明底板、身高和体重的黑色数值框消失，顶部中文姓名变为点阵乱码。

- `modules/adapter/module.cpp::invalidate` 原来只有设置页绕开 Scene 重建。`native_ui_scene.cpp:173` 的 `paint` 先重建背景，再遍历已登记组件；`native_component_binding.cpp:312` 没有文字来源的面板不登记，`:339` 的 `10E5A0` 叶子也不包含其调用者画出的数值框。属性页右侧 `E6BDB → 115E70`、身高体重 `E69F7/E6A9F → 111480` 因此不能靠文字集合恢复。状态：本次属性确认页语言刷新改走完整原生页面构建，不新增 Mod 面板、坐标、页面快照或绘制序列。
- `module.cpp::codec`、`metrics_at_outline`、软件字形叶子的旧英文分支将中文姓名保留为 UTF-8，却按原生字节宽度和点阵字形解释。状态：本次仅属性姓名标题的完整原生调用启用统一 Unicode 编码、度量和即时绘字作用域；原姓名、文化编号、英文文化原文和存档不改。

## 在原有属性帧内重建

`invalidate` 使用当前原生 root 的 `{E6C28, profile_confirm_background}` 来源身份识别 mode 1 属性确认页。该段落的首个语义来自 `E6BEA` 文化背景确认；mode 2 为 `{E6B97, profile_attributes_ready}`，不命中。切换时只推进语言资源版本，跳过通用 Scene/旧缓存物化、部分选择重画和呈现，由原页面构建重建所有像素与原生菜单缓存。

| 原生边界 | 处理与静态依据 |
| --- | --- |
| `D12B4` | 仅 pending 属性刷新、输入结果 `-2` 且 `[EBP+4]==base+E6CB5` 时保存真实 `5F54AB0` 选择，转到原 `D19B3`，完整退出 `D1120` 输入帧。`E6CB0` 保留原 CALL，返回地址未替换。 |
| `E6CB5..E6CBC` | 原 `CMP/JGE/TEST/JS` 自然把 `D19B3` 的 `-1` 结果送到 `E6D03`，不执行 Y/N 动作查找和 `REROLL/REROLL_POS` 写入。未在含相对分支的指令上建立 replay。 |
| `E6D03` | 七字节 `8B 8C 24 7C 04 00 00`，位于 cookie 读取和三次 POP 之前。属性重建阶段令 `ECX=EDI`，在原帧继续 `E66CD`。原模式仍为1，cookie、返回地址及保存寄存器保持。普通返回继续原指令。 |
| `E66CD..E6ADA` | 原背景、四组窗口、姓名、年龄、十一项属性柱条、头像、身高体重及完整数值框构建。`E66CD` 的 PUSH ECX 与高宽及两个空参数共20字节，由 `E66F3 ADD ESP,14h` 平衡；与输入返回的稳态 SP 相同。没有重入 prologue 或角色创建业务。 |
| `E6ADA` | 完整十字节 `MOV [61BBA5C],0`。重建时执行相同清零后继续 `E6B26`，跳过原首次部分上传、淡变状态写入和光标操作。 |
| `E6B26..E6CA6` | 原生重建右侧完整窗口、说明段落及 Y/N 菜单，仍由原函数决定尺寸、颜色、坐标和输入动作。 |
| `E6CA6` | 五字节 `A1 <base+217A70>`；重建时以保存的真实当前选择替代此次 EAX 加载。随后原 `E6CAB` 写回选择，再进入原 `E6CB0 → D1120`；不修改 `REROLL_POS`。 |
| `D1120` | 原 `D1189` 保存完整页面到原菜单缓存，`D1207/D1217` 恢复菜单区域并绘制当前选择，原 `D1225/D124A/D1292` 上传及呈现。 |

实现位于 `native_language_redraw.cpp/.h`，沿用两个 u32 的状态交接：`pending` 增加属性位，`rebuilding` 低8位为阶段，高位仅在属性重建期间保存实际菜单选择。没有保存原生帧指针、最终文字、位置或绘制内容；`E6CA6` 消费后清除该阶段。新钩子都是可原样重放的完整指令，无 ESP 修改和相对控制转移。不修改驻留桥、启动器或 Host ABI。

## 英文模式中文姓名

`windows_profile_extras.inc::wp_attribute_identity` 在 `E6784 → F9030` 的 Before 已取得原姓名及文化。当英文模式下姓名含 UTF-8 时，进入新增 `Scope::profile_identity_unicode=47`；既有 `profile_panel` 借用作用域仍保留。在这个同步作用域中，`codec` 直接使用既有 Layout 两字节传输，`metrics_at_outline` 使用同一 Render 度量，原四次阴影和前景叶子调用立即绘入真实密度的原生目标。原 `F909D` 的标题字宽扩展及 `F90B5 → 10E5A0` 消费同一串文字，原生继续计算居中和光标推进。

语言选择仍控制文化标签采用原英文或中文；姓名始终保留。统一传输字母表排除了原生 showtext 会改写的 `C4/E4/F6` 字节，不把裸 UTF-8 留在原 ASCII 字形循环。

已有 `native_identity_heading` 在准备来源和原生绘制时均进入相同作用域：`native_component_model::prepare` 仅对该种类成对调用现有 `services.enter/leave`，`enter_component_paint` 依据已存在的 Unicode 姓名前缀开启编码服务。普通原生 Before 的外层 token 不受组件临时 token 清理影响；After 只结束借用，没有再次编码。缓存消费也使用一致编码与绘字，但这不构成对现有 Scene 所有权的合规认可。没有扩大其它英文组件的编码或绘字开关，未改变 `Active` 布局、原枚举值或序列化格式。

## 既有待整改边界

- `native_ui_scene.cpp:12/17/173/538/594` 的 Child、Container、整页组件序列重建和缓存物化仍由 Mod 持有，不符合当前原生 UI 所有权要求；本次属性确认页即时语言刷新不再沿该路径，其余界面待整改。
- `native_footer_component.cpp::paint` 的独立署名排版仍待整改，非本次属性确认页。
- 此次原帧 continuation 限定 mode 1；mode 0 生涯资料及 mode 2 完成提示的完整即时重建接口不在本次整改范围，不据此宣称所有页面刷新已完成。

## 交付状态

源码修改与静态复审完成。2026-11-10 12:00:31（Asia/Shanghai）统一队列编译、正式发布和兼容模块交接分别完成；源码提交到批次结束期间未继续修改该批源码。

- 根入口 `.toolchains/powershell/pwsh -NoProfile -File ./build.ps1 -Toolchain MinGW -Module adapter -Publish -Reload -TargetPid 364`；显式使用 `/usr/bin/cmake`、`/home/lulika/.local/share/dfcn-toolchains/mingw-w64-16.2.0/usr/bin/i686-w64-mingw32-g++`、原 `build/mingw-x86`、正式 `package/`，并指定当前 Proton WinePrefix 与 WinePath。一次配置、一次增量编译，没有清理构建树。
- 请求 `d30613bdff80418bb33a75361966c415`，批次 `b3d9d6fa7c1a4ca1850b0caf426bb375`。已读取对应 `build/.compile-queue/results` JSON 和完整批次日志，`Success=true`、`PublishRequested=true`、`ReloadRequested=true`。保留既有函数指针转换、extern 初始化、未使用项和缩进警告，无编译错误。
- 正式事务 `d5d19db8795d463f98a06b0c1ab2c977`；已读取暂存目录 `publication-result.json`，`success=true`。更新 `package/modules/uwcn_adapter.dll` 与 `package/release.json`；旧两件先按原相对路径移入 `回收/20261110-120029-d5d19db8795d463f98a06b0c1ab2c977/`，已只读确认归档存在。没有平行运行包。
- 正式 Adapter 与构建输出 SHA-256 相同：`117efe76a7cd282b8db2d02bce8640d63ac3001946c5920f7611b72c5211c27b`。正常根启动器使用的正式位置已更新。
- 系统进程表显示原 Linux PID `2832305` 已结束，新运行实例为 Linux PID `2836649`。只读其 WinePrefix 并经现有 Proton Mono 解释器枚举得 Windows PID `364`；未启动或关闭游戏。既有驻留事务返回 `ReadyToPublish`、`Applied ... adapter:117efe76a7cd282b8db2d02bce8640d63ac3001946c5920f7611b72c5211c27b:2`，当前实例 Adapter 第2代交接完成；没有修改驻留桥或重启游戏。

没有运行游戏产物、模拟操作或执行测试；Applied 只证明兼容模块交接，当前页面在原生输入返回时重建，画面效果仍由用户验收。
