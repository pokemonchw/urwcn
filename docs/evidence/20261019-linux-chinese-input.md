# Linux 角色姓名中文输入：原生输入、编码及显示边界

日期：2026-10-19。用户要求实现截图角色姓名框的中文输入。目标是 Linux x86-64 Steam `urw3-bin`，SHA256 `4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。Windows 与其他 `getst` 调用者不在本次输入扩展范围内。

遵守根 AGENTS.md：没有启动游戏、运行产物、注入进程、模拟操作、执行或编写测试、添加断言。以下结论来自本地原始 ELF、符号表、反汇编和 Ghidra 反编译；编译仅用于交付。

## 原因和静态依据

原 `key_event` 已接收 SDL_TEXTINPUT，复制完整 UTF-8 后停止输入法，只把首字节或少数北欧字符映射为按键值。`getkey` 继续经 `processed_keysym` 压成单键；`getst` 用 `%c` 追加一个字节、按字节退格、按 `strlen*8` 擦除。因此仅开启 SDL 输入法不足以支持中文。

本地分析文件为 `build/analysis/input-20261019/input-ghidra.c`、`getst.asm`、`key-event.asm`、`choose-name.asm`，其余调用链见 `build/analysis/linux-x86_64.asm`。反编译复用已有导入工程，只读且不重新分析；Ghidra 地址需减去 `0x100000` 得到下表 RVA。

| 原生边界 | 已确认语义与扩展 |
| --- | --- |
| `1E1E4 → getst(1402B0)` | 仅本次姓名输入作用域开启完整 UTF-8 事件消费；颜色、最大长度参数保留。原生 `getst` 仍控制背景、编辑循环和提交/取消。 |
| `F6E7D → strcpy`，`F6E82` | 原生将 SDL_TEXTINPUT.text 复制到 `getkeystring(663EA60)` 后，姓名作用域跳过 StopTextInput 和单字节映射，返回原生 `-2`，沿 `F6E3B` 完整尾声退出。没有构造或投递 SDL 事件。 |
| `F85A2/F85CE` | `getkey` 对 `-2` 直接退出，不读未写入的 SDL_Keysym，也不执行 processed_keysym。 |
| `F6CCA/F6F80` | 姓名作用域内不因 Ctrl/Alt 关闭系统输入法；其他调用者仍执行原 StopTextInput。姓名返回时关闭本次文本输入；后续原生 key_event 自己恢复输入状态。 |
| `1403FF` | 原生已经擦除旧下划线。仅收到真实提交事件时，将完整标量追加到原生 `getst::st(A97E780)`，每次追加占用整个 UTF-8 字符；其余走原 CMP/JNE 的两个后继。 |
| `1404DB` | 原生已确认字符串非空并擦除旧行；按完整 UTF-8 标量找出末字符起点，执行原生 NUL 截尾。原生单字节默认姓名照常删除一字节。 |
| `140481/1406BA/140727` | 原生退格、随机、默认值三个擦除调用只将宽度表达式扩展为字体实测宽度加原生5像素边距；x/y、高度、背景色和原生 FillRect 所有权不变。没有采样或保存额外像素。 |
| `14038B` | 保留原生下划线 showtext；从该次调用的 x/y 与原行高计算系统输入法区域，经实际 renderer 的逻辑/输出/窗口变换提交。没有固定页面坐标、坐标表或持久 UI 几何。 |
| `13E8EF/13E324` | 在 showtext/renshowtext 将字符串复制到各自300字节原生显示缓冲时，将 UTF-8 转为既有两字节字形传输编码，先于 C4/E4/F6 字节重映射。源姓名不改写；该转换不会扩张原 UTF-8 字节长度。 |
| `13B460/13B760/13DE10/13E1B0` | 既有宽度、软件面与 renderer 绘字入口同时消费 UTF-8/显示编码。居中、段落宽度和 showtext 光标的既有扩展因此也使用同一度量。字形即时绘入原生实际密度目标。 |
| `F91F0/F9378` | 原 StrUpr/StrLwr 的字符循环跨过完整 UTF-8 标量，避免将中文首字节 E4 或续字节84/94/99误当作北欧字母重映射。ASCII 与原单字节分支仍执行原函数。 |
| `1E31D` | Choose_Name 最终路径编码处，UTF-8 直接借用当前原生临时字符串；ASCII/旧单字节姓名仍调用原 StrUnicode。避免逐字节 `0x%02x` 扩展后再被32字节 strncpy截断。 |

源码在 `src/linux/native_utf8.inc`、`src/linux/name_input.inc`，由既有 `src/linux/adapter.cpp` 引入。只新增两个输入状态布尔值；提交字符串仍由原生事件缓冲持有。字体字典只保存编码、Unicode字形和度量，不保存页面文字、位置或延后绘制操作。

## 姓名容量、存档与原动作

`Choose_Name:1E1DD` 传最大有效长度12；`1E1E9..1E1F8` 对 `Plr(AC86040)` 执行容量13的 `__stpcpy_chk`，其后的 `Plr+0xD` 已是文化字段。不能把该字段直接扩大或把未确认字节当成姓名尾部。

本次保持有效姓名最多12字节，追加过程只接受放得下的完整字符。常用汉字每字3字节，最多4字；扩展区汉字可能每字4字节，最多3字。中英文混输共用容量。原最小长度判定仍为3字节，所以纯英文至少3字母，单个常用汉字已达到该判定。没有另加姓名规则或兜底分支；原空格、点、逗号、斜杠、反斜杠、下划线、&、+ 检查和重名文件夹检查保留。

原生 Enter 提交、Escape 返回、TAB 和 `*` 随机取名均保留。实际 `*` 文本提交进入原生随机分支，不创建模拟按键。原生随机姓名保持原数据；Backspace 同时识别其已有单字节字符。

`Save:1BF094..1BF0A8` 将原 `Plr` 的0x1654字节直接 fwrite；`load_character:15B105..15B139` 同样 fread 到 Plr，再由 LIST_Entry 复制原姓名。姓名内容保留 UTF-8，存档结构与尺寸未改。`SaveFile` 容量64，最终名称复制上限32；12字节UTF-8可完整进入。`create_objects:1D3BF..1D3E2` 和 `crtplr:1FCAE..1FCC1` 将该路径完整复制到128字节 CharacterFile；载入选择从实际目录名复制 CharacterFile，不从显示字形 token 重建路径。

之前的8字节 SaveFile 临时分支 `1E286..1E2D9` 随即在 `1E2DE..1E2FE` 被原生清空；没有把它误认为最终存档路径，也没有改动该段业务。

Linux 取名帮助使用两个新增词库键，仍进入原来的段落追加与布局调用；Windows 原帮助键保持原样。帮助中的空格保留词元分段，避免把整句中文作为超出原生词元容量的单词提交。

## 系统输入法

本机已确认使用 sdl2-compat 2.32.72 / SDL3。设置 `SDL_IME_IMPLEMENTED_UI=none` 让系统负责组合文字与候选窗口；Mod 不绘制另一套预编辑框。SDL2-compat 的 Start/StopTextInput 与 SetTextInputRect 转发到 SDL3 的窗口输入及 TextInputArea。

依据：[SDL_TEXTINPUT 的完整UTF-8标量契约](https://wiki.libsdl.org/SDL2/SDL_TextInputEvent)、[SDL3 系统IME界面设置](https://wiki.libsdl.org/SDL3/SDL_HINT_IME_IMPLEMENTED_UI)、[锁定版本 sdl2-compat 源码](https://github.com/libsdl-org/sdl2-compat/blob/release-2.32.72/src/sdl2_compat.c)、[SDL 原生候选区域接口](https://wiki.libsdl.org/SDL2/SDL_SetTextInputRect)。候选显示依赖用户已有系统输入法，实际交互未经运行验证。

## 范围与待确认状态

- 本次只授权并接入截图中的角色姓名输入链，其他文本框和 Windows 输入尚未扩展，不称为全游戏中文输入完成。
- `src/linux/adapter.cpp::resize_native_targets` 仍只确认主菜单完整缩放重建；姓名页沿既有原生目标密度绘字，不补造该页缩放生命周期。
- 原生 showtext 描边预算和已经变暗的文化/性别面板刷新仍是既有待整改项，见字体密度、角色创建记录。此次输入修改没有将它们视为已解决。
- Linux 驻留桥尚无模块原位退役/重载协议；不使用 Windows Reload、不注入或重启游戏，不宣称旧进程已应用。
- 历史 `20261019-character-profile-native.md` 的“没有增加中文输入”描述的是当时 Windows 交付；本记录新增 Linux 后续状态，不篡改历史回执。

## 交付状态

源码修改、统一队列编译与正式发布均已完成。2026-10-19 13:16:35（Asia/Shanghai）根入口执行：

```powershell
./build.ps1 -Toolchain Linux -Module adapter,semantic,catalog -Publish
```

- 请求 `61a95de4c76241dbbcb708ede52f1d07`；批次 `0c9e7c4c79684724b3d33d334284ed2f`；发布事务 `e08183efefbc4730932a853298c0f5e1`。
- 已读取对应 `build/.compile-queue/results/61a95de4c76241dbbcb708ede52f1d07.json`、完整 `batches/0c9e7c4c79684724b3d33d334284ed2f.log` 以及该事务的 `publication-result.json`，两份回执均为成功。一次配置、一次增量构建；Adapter、Semantic 重新编译，Catalog 产物已是最新。
- 编译保留 Semantic 原有15项 HUD/world switch 警告，没有新增默认语义或兜底分支来消警告。静态读取 ELF 符号确认新增回调及原模块导出存在，没有执行 ELF。
- 正式替换 `package/modules/uwcn_adapter.dll`、`uwcn_semantic.dll`、词库、Linux profile 和发布清单五件。旧五件已先移入 `回收/20261019-131635-e08183efefbc4730932a853298c0f5e1/package/` 对应相对路径；应用菜单链接亦由原发布流程归档并更新，仍指向同一根启动器。
- 正式 Adapter SHA256：`8d8bb1f383da9f6d0fe67e3216eebb110602e5d5c92a14a3100e8062c995e8db`；Semantic：`7d51cd959860504831e70a8d6773633ea822cf9351854556c494dfc1f18b1cf7`；词库：`2c5644f0b0a3a71c361ea6589c25b02edc05dbcfbd136869864e9d5038a32983`；profile：`160a666bc6b1bdb1609be5a8915cc4adc2b9759c2586336e035c68ab458e2410`。分别与构建产物或源文件、正式清单相符；旧五件已只读确认存在。
- 发布前只读进程列表未发现游戏/启动器。本次没有请求 Reload，无运行时 Applied 回执。下次正常通过根 `uwcn_launcher` 启动加载正式新文件；没有平行运行包。

没有启动游戏、运行产物或测试，输入法交互与画面效果仍待用户实际使用反馈；编译和发布成功不等于运行验收。
