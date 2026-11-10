# Windows 3.89.1 原生接口与数据地址静态复审

日期：2026-11-10。对象为本机《不真实的世界》Windows x86 3.89.1 / Steam Build `26139145`，`urw.exe` SHA-256：`c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。PE 首选基址仍为 `0x400000`。本文地址为 RVA。

本轮只读取磁盘 PE、现有源码与既有静态说明，使用 objdump 和内联 Python 解析 PE 节表、导入表、原始指令及源码中的已知地址。没有启动游戏、运行交付产物、注入、输入模拟、执行测试、编写测试脚本或断言。本文不表示编译、发布或视觉验收。

## 确定变化及源码修正

以下五个已确认只读数据地址迁移 `+0x10`；这是逐个原生消费者的静态证据，不将整个地址空间视为统一平移。

| 旧 RVA | 3.89.1 RVA | 原生语义与消费位置 | 本轮修改文件 |
| --- | --- | --- | --- |
| `0x1AA240` | `0x1AA250` | 特定 HUD 标签原文 `   +`；`native_component_binding` 用作来源身份判别 | `modules/adapter/native_component_binding.cpp` |
| `0x1AA314` | `0x1AA324` | `0xFAAA4` 读取首个 HUD 标签的两个字节；新版指令为 `66 8B 0D 24 A3 5A 00` | `modules/adapter/native_renderer_component_binding.cpp` |
| `0x1ACAB8` | `0x1ACAC8` | `0x1154EA` 推入 `truetile/gui-arrow.png` 地址，随后 `0x1154EF` 调用原生图像导入 | `modules/adapter/native_targets.cpp` |
| `0x1ACAD0` | `0x1ACAE0` | `0x115547` 推入 `truetile/gui-sndclue.png` 地址，随后 `0x11554C` 调用原生图像导入 | `modules/adapter/native_targets.cpp` |
| `0x1DDAB0` | `0x1DDAC0` | `{0,0,800,600}` 原生矩形；`0x10BA00` 和 `0xE3DD2` 均以 `movaps` 加载新版地址，`0x10BA17` 的 FillRect 使用它 | `modules/adapter/native_root_component.cpp`、`modules/adapter/native_renderer_component_binding.cpp` |

上述原文来源判别、图像文件名参数、清屏矩形读取及两个 inline 补丁操作数改为经 `windows_build::rdata_rva()` 取得对应构建的已确认地址。两个 HUD 图像参数在正常构建与 HUD 高清目标提升两条现有调用链均修改。未变更任何原生业务数据和坐标；矩形仍取自原生只读常量。

旧图像地址在新 PE 中已经指向其他字符串的尾部，旧矩形地址则包含 `{15,85,450,460}`，因此仅把新版哈希加入启动器而保留旧数据地址会产生确定错误。两个 inline 操作数也会与旧预期不符，导致原有安装流程拒绝该构建。

## 指令边界

对以下 `77` 处完整指令的静态对照中，`75` 处与旧源码构造的预期字节一致。余下两处是上表 `0xFAAA4` 和 `0xE3DD2`，指令与地址宽度未变，仅只读数据操作数迁移。

| 范围 | 数量 | 结果 |
| --- | ---: | --- |
| `native_raster_patches.cpp` 整函数/指令补丁 | 11 | 含绝对主表面操作数填充，全部一致 |
| `abi1_hook_retirement.h` 历史 inline 原字节 | 4 | 全部一致 |
| `native_hud_icons.cpp` | 8 | 含方向、覆盖层、活动图标绝对操作数，全部一致 |
| `native_menu_component.cpp` inline | 8 | 构建/绘制提交、行记录、注释起点、选择宽度全部一致 |
| `native_root_component.cpp` inline | 2 | 两处 cookie 读取全部一致 |
| `native_renderer_component_binding.cpp` inline | 7 | 5 处一致，2 处只读数据操作数迁移 |
| `native_ui_cache_owners.cpp` inline | 4 | 三个所有者写入及命名槽写入全部一致 |
| `native_component_binding.cpp` parser inline | 2 | cookie 读取一致 |
| `native_language_input.cpp` inline | 2 | 原生事件缓冲比较/读取一致 |
| `native_component_binding.cpp` HUD summary operand | 17 | 指令、操作数和字段地址全部一致 |
| `native_component_binding.cpp` grammar count capture/clear | 11 | 8 处读取、3 处清零全部一致 |
| `native_renderer_component_model.cpp` marked-update inline | 1 | `0xCFE08` 的 `C7 05 C4 BA 5B 06 00 00 00 00` 一致 |

`native_ui_cache_owners` 中已有的 `40` 个缓存拷贝返回地址，在新版反汇编中仍各自紧接原生 CALL 指令。`native_targets` 的 `15` 个资源构建返回地址也仍紧接原有创建表面/纹理 CALL；导入调用槽和间接寄存器调用形式保持。此项确认原生生命周期边界，未运行这些调用。

## 导入、字段与调用 ABI

新版 PE 导入表确认 `native_targets` 的全部 `13` 个 IAT 槽仍分别导入源码所绑定的同名 SDL 函数，包含 `0x18C204=SDL_UpperBlit`、`0x18C1F0=SDL_CreateRGBSurface`、`0x18C208=SDL_CreateTexture`、`0x18C288=SDL_SetRenderTarget`。另外 `0x18C294=IMG_Load`、`0x18C26C=SDL_GetRenderTarget` 保持。

`native_*.cpp` 中直接以 `base + 固定数据 RVA` 表达的 `58` 处数据地址，在新 PE `.text` 中均仍有相同绝对地址操作数，包括主表面 `0x61BBB10`、点阵掩码 `0xA1BBD28`、颜色 `0xA211068`、菜单和消息字段。`.data` 起点仍为 `0x1E2000`。该项说明原程序仍消费这些字段，不将单纯出现四字节地址视为所有函数体语义相等的证明。

静态检查的组件函数入口仍位于原 RVA，且存在可对应的原生栈帧/寄存器取参指令。例如：

- 背景 `0x1127C0` 在 prologue 后保留 ECX/EDX 的来源；`0x1127E6/0x1127F1` 仍读取 `[EBP+0x10]/[EBP+0x14]` 的宽高，符合现有四个 caller-cleaned 栈槽 wrapper。
- 标题面板 `0x116270` 仍从 ECX/EDX 保存坐标，在 `0x116294` 从 `[EBP+0x10]` 取标题；旧面板 `0x115E70` 入口仍独立存在。
- 按钮 `0x114680` 在 `0x114694` 从 `[EBP+8]` 取标签，同时保留 ECX/EDX 坐标。
- 原生图像取首像素 `0x10BBE0` 入口仍从 `[EBP+8]` 取表面，保留 ECX/EDX 坐标；`0x1154FA..0x115504` 仍以清零的 ECX/EDX 和表面栈参数调用它。
- 文本、段落、HUD、地图及 renderer 组件入口 `0x10E5A0`、`0x10EB40`、`0xF8E20`、`0xFEF00`、`0xF9910`、`0x605B0`、`0x60360`、`0x60450`、`0xCFD10`、`0x1166C0`、`0x10EFD0`、`0x10E260`、`0x113430`、`0x111560` 保持原函数入口形态；其具体调用点完整指令的范围由配套 hook 对照记录覆盖。

本报告不宣称新旧 PE 的全部函数体相同，不确认游戏运行效果，也不对项目中既有原生 UI 所有权整改作整体完成声明。只读数据迁移由精确构建身份和已确认地址映射处理；未增加模糊匹配、运行时搜索或猜测性回退。

## 29 个未迁移导入槽的追加静态清单

逐一解析新版 PE `IMAGE_IMPORT_DESCRIPTOR`、OriginalFirstThunk 与 FirstThunk，以下 `29` 槽的 DLL / 导入名均与既有源码用途、import_slot 绑定和 inline 填充对象一致，保持原 RVA。这里列出的 `0x18C4A8` 与 `0x18C4D8` 是文件 I/O 的 fread/fwrite。

| RVA | 新 PE 导入名 | 现有源码消费处 |
| --- | --- | --- |
| `0x18C178` | SDL2.dll / SDL_ConvertSurface | native_targets |
| `0x18C17C` | SDL2.dll / SDL_UpperBlitScaled | native_targets、abi1_hook_retirement |
| `0x18C18C` | SDL2.dll / SDL_QueryTexture | native_targets |
| `0x18C1C0` | SDL2.dll / SDL_RenderDrawPoint | abi1_hook_retirement |
| `0x18C1D0` | SDL2.dll / SDL_RenderCopyEx | native_hud_icons 的方向图标及分支寄存器 |
| `0x18C1E0` | SDL2.dll / SDL_CreateTextureFromSurface | native_targets、abi1_hook_retirement |
| `0x18C1E4` | SDL2.dll / SDL_SetRenderDrawColor | hud_native、native_renderer_component_binding |
| `0x18C1E8` | SDL2.dll / SDL_FillRect | native_targets、native_root_component、abi1_hook_retirement |
| `0x18C1EC` | SDL2.dll / SDL_RenderFillRect | abi1_hook_retirement |
| `0x18C1F0` | SDL2.dll / SDL_CreateRGBSurface | native_targets、abi1_hook_retirement |
| `0x18C1F4` | SDL2.dll / SDL_FreeSurface | native_targets、abi1_hook_retirement |
| `0x18C204` | SDL2.dll / SDL_UpperBlit | native_targets、abi1_hook_retirement |
| `0x18C208` | SDL2.dll / SDL_CreateTexture | native_targets、abi1_hook_retirement |
| `0x18C21C` | SDL2.dll / SDL_UpdateTexture | abi1_hook_retirement |
| `0x18C220` | SDL2.dll / SDL_CreateSoftwareRenderer | native_targets |
| `0x18C224` | SDL2.dll / SDL_RenderClear | abi1_hook_retirement |
| `0x18C228` | SDL2.dll / SDL_RenderCopy | native_targets、abi1_hook_retirement |
| `0x18C22C` | SDL2.dll / SDL_DestroyTexture | native_targets、abi1_hook_retirement |
| `0x18C238` | SDL2.dll / SDL_StopTextInput | native_name_input |
| `0x18C26C` | SDL2.dll / SDL_GetRenderTarget | native_renderer_component_model/binding、native_hud_icons |
| `0x18C288` | SDL2.dll / SDL_SetRenderTarget | native_targets、native_renderer_component_model/binding、native_hud_icons |
| `0x18C294` | SDL2_image.dll / IMG_Load | native_targets 的原生 HUD 图像来源 |
| `0x18C348` | VCRUNTIME140.dll / strchr | windows_encyclopedia 的链接边界 |
| `0x18C350` | VCRUNTIME140.dll / strstr | windows_encyclopedia、windows_message_menu_echo |
| `0x18C4A8` | api-ms-win-crt-stdio-l1-1-0.dll / fread | native_menu_storage |
| `0x18C4B4` | api-ms-win-crt-stdio-l1-1-0.dll / fclose | windows_message_quest_records |
| `0x18C4D8` | api-ms-win-crt-stdio-l1-1-0.dll / fwrite | native_menu_storage |
| `0x18C4DC` | api-ms-win-crt-stdio-l1-1-0.dll / fgetpos | windows_encyclopedia |
| `0x18C4F0` | api-ms-win-crt-string-l1-1-0.dll / strncpy | windows_message_materials |

另外直接按源码中的 opcode 和 IAT RVA 重建 `14` 处六字节间接 CALL / MOV 预期，在新版 PE 原始指令全部一致：`0xFAFB3`、`0xFAA4B`、`0xD1F81`、`0xD1C6E`、`0xD1CF0`、`0x3D39A`、`0x3D470`、`0x3D52A`、`0x3D4EB`、`0x3D4BD`、`0x431DE`、`0x157518`、`0x179657`、`0x67BDB`。其操作数均为 `0x400000 + 上表原 IAT RVA`。这是额外的文件字节对照，不涉及调用或执行这些导入函数。
