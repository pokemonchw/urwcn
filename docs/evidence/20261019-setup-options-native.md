# 设置选项原生汉化

2026-10-19（Asia/Shanghai）。对应用户提供的 SETUP OPTIONS 截图，范围为同一原生设置页的标题、14 项设置、13 条说明、底部两条操作/配置提示及退出标签。截图未显示的全屏 MAXIMIZED、关闭音频或地图光照后的条件分支均沿原生流程处理。安装目录继续显示游戏原 `_getcwd` 的内容；`urw_ini.txt`、按键名和内部配置键保持原语义。

## 原生接入

目标为 UnReal World 3.89 / Steam Build 25939378，EXE SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。现有反编译和原始指令见 `setup-options-ghidra.c`、`setup-options-disassembly.txt`、`setup-options-patches.tsv`、`setup-options-title-text-disassembly.txt`、`setup-options-key-disassembly.txt`、`setup-options-key-text-disassembly.txt`、`setup-options-bottom-disassembly.txt`。

`modules/adapter/setup_text_calls.h` 仅列出 27 个已确认的正文 `10E5A0` 调用地址和语义组件，不含坐标、行槽、颜色或页面字段。每次调用前，动态组件从本次原生已格式化的 `LABEL: value` 取值，中文只借给该次显示参数。音量归整、夜间亮度分档、配置读取、点击后的配置写入及条件隐藏仍由原函数执行；Mod 不再次读取设置或采集整页快照。

语义组件使用 `0x600..0x61E`，其中 `0x601..0x60E` 对应 14 项动态选项。词库包含 `YES/NO/MAXIMIZED/IMPERIAL/METRIC`，以及 `0 (default)` 和 `60 (maximum)` 的显示译名；音量和其他夜间亮度数字保持原生结果，不增加百分号。说明保留原两个前导空格。

| 调用/指令 RVA | 处理 |
| --- | --- |
| `105752 → 116270` | 借入中文标题，保留原尺寸、flags 和面板构建。 |
| `115A94 → 10E5A0` | 仅在上述设置面板作用域启用即时字形。flags `0x30` 经 `116698 → 1157B0 mode=1` 左对齐，不走另两个按字节居中的分支。 |
| `105817/105823 → 162300` | 在原 tokenizer 前替换两条底部提示，保留 reset/append 和 `<br>`。 |
| `10582A → F210`、`F2E5 → 10EB40` | 限定底部段落作用域，复用已有真实字宽、折行及字形绘制扩展。 |
| `105891 → 10E5A0` | 原安装路径绘制保持不变；本次没有对环境路径建立翻译或新快照。 |
| `106AFC → CFAF0` | 借入原 `ESC.` 前缀加中文后缀，保留原键帽、键动作和行注册。 |
| `1149F9 → 10E5A0` | 仅在设置退出按钮作用域即时绘制中文后缀；逐键绘制 `114956` 不接管。 |
| `CFC5D` | 替换原 `LEA EAX,[ECX*8+10]` 的后缀宽度部分，让原生行对象使用同字体实际中文宽度。 |

`CFC5D` 的原字节为 `8D 04 CD 0A 00 00 00`。此时 `[EBP-408]` 已由原函数在点号处截断为 ESC，EDI 仍指向完整借用文本。计算 `(原前缀字节数+1)*8 + 10 + 中文后缀实际宽度`，仅返回 EAX；随后原 `CFC64` 继续写行宽。ESC 的 ASCII 8 单位字格、分隔间距、原生边距、行位置、高度及动作均保留。测量沿用本次按钮的原 outline 值（`5F54A9C`），与后缀绘制一致，不以中文传输 token 数计宽。

## 绘制、缓存和生命周期

中文经过既有原生安全编码，在原 `10E5A0` 的完整文字调用中解码并以实际主面的密度立即绘制，复用 `10E700` 光标真字宽。底部段落复用 `10EE68`、`10EF57` 的真实测量及 `10EF87` 逐词消费。借用字节仅活到原生调用 After，页面像素随后由原生表面和背景缓存管理。没有独立 DisplayPlan、页面坐标表、Present 叠字、像素跟踪或延后文字重放。Host ABI、驻留桥及启动器未改。

首次将这些调用接入已打开的设置页时，现有框架不会追补已经发生的 Before。标题和底部已由 `1058A0 → 10C540` 保存为 `setupscr`；普通选项重绘从 `1058B0` 开始并恢复该缓存。故正文在下一次原生重建时使用中文，既有标题/底部缓存要等原生重新构建设置页才更新。不能把热更 Applied 宣称为当前整页立即刷新。

没有确认可完整刷新此页的独立原生接口。正文重建片段依赖外层 EBP 局部及 EBX/ESI/EDI，不能传给禁止外层帧依赖的 `native_fragment`。本次未加入推测性刷新、模拟输入、强制退出页面或重启游戏。

## 旧说明审查

| 文件及原位置 | 影响 | 状态 |
| --- | --- | --- |
| `setup-options-static.txt:144–145` | 允许复制固定行或独立 measured plan，与原生布局归属冲突。 | 本次不采用；原件归档，活动证据顶部已明确标记失效。 |
| 同文件 `:168–212` | 旧 resident setup 桥、全页 SetupRequest、title_only/complete view、固定退出行槽及 Present 合成描述。 | 旧实现已退役；本次用逐次原生语义和即时字形替代，历史正文仅保留定位，不作为实现依据。 |
| `README.md` 先前的设置页未接入状态 | 旧实现不能代表重建已完成。 | 本次按此记录更新接入范围，发布状态另列。 |

未修改仍待整改的宿主错误透传与事务失败语义；其状态继续见 `20261019-implementation-correction.md`。

## 交付状态

源码接入与静态审查已完成。2026-10-19 02:42（Asia/Shanghai）根 `build.ps1 -Module adapter,semantic,catalog -Publish -Reload -TargetPid 65412` 完成统一队列编译及正式热发布。使用默认 MinGW、`.toolchains/x86/w64devkit/bin/cmake.exe`、同目录 `g++.exe`、`build/mingw-x86` 和正式 `package`，没有平行运行包。

- 请求 ID：`717c3aefe24049b4a7c43a35d9505b96`；批次 ID：`bcd418e7f1574fe98569bea56747dd10`。已读取 `build/.compile-queue/results/717c3aefe24049b4a7c43a35d9505b96.json` 和对应批次完整日志，结果 `Success=true`。批次执行一次配置与一次增量构建；保留既有 SDL `GetProcAddress` 函数指针转换警告，无编译错误。
- 正式发布事务：`80bf73a354c74db594bf27a86fe98fd9`。已读取 `build/mingw-x86/stage/80bf73a354c74db594bf27a86fe98fd9/publication-result.json`，结果 `success=true`。
- 正式替换 Adapter、Semantic、中文词库、构建适配和发布清单共五项；旧件先按原路径移入 `回收/20261019-024201-80bf73a354c74db594bf27a86fe98fd9/`。Catalog DLL 编译内容未变，因词库更新参与重新加载。启动器、驻留桥、Render、Layout 和 MainMenu 沿用正式文件。
- 既有 PID `65412` 返回 `ReadyToPublish` 和 `Applied`，Catalog/Semantic 为第 2 代、Adapter 为第 3 代。正式清单十项文件的 SHA-256 均与磁盘一致，Applied 中三个模块哈希也与正式清单一致。
- 共享工作区同期已有的关于组件改动保留在本批 Adapter/Semantic 中；没有覆盖或回退其他工作的源码。本记录说明设置页接入，关于组件的语义与回执以其专门记录为准。

| 正式文件（相对 package） | SHA-256 |
| --- | --- |
| `modules/uwcn_adapter.dll` | `f877779a922c21cce94c959f485e68a93a37ca23ee8f45ea59a8e2e88bc061c7` |
| `modules/uwcn_semantic.dll` | `4f9ab09511183d48fea1788df12f6ccfba90f61aec0e83a4771d59fae72b91e0` |
| `catalog/zh-CN/main_menu.tsv` | `34de25d2078b8ac627811b12a6277cd2bad275ed14ac634b1d9d65cea3394ed5` |
| `profiles/urw-3.89-steam-25939378.json` | `7cfc0b1772909abf4d49e0afca743a22bb427c3a609f510d430217f6e6cfb569` |

未启动游戏、注入、模拟操作、运行测试或单独运行产物；未创建测试用例和断言。授权热发布仅完成既有进程的兼容模块交接；Applied 不等于视觉验收，也不证明已打开页的标题/底部缓存立即更新。
