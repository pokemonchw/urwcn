# Linux 退出告别页汉化

对应截图的 `YOU ARE LEAVING UNREAL WORLD - A FINAL REMINDER...` 页面。本次翻译标题、四句引文、克里族署名、献辞、三句底部寄语及按键按钮，共 11 项。原生背景、颜色、描边、布局、输入等待、音乐及退出行为保持。

## 静态依据

目标为本机 Linux x86-64、UnReal World 3.89 / Steam Build `25939378`，`urw3-bin` SHA-256：`4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。地址均为 ELF RVA，不沿用 Windows PE 地址。

使用现有 Ghidra 12.1.2 项目，以 `-readOnly -noanalysis` 反编译 `endgame`、`showtext`、`centext`、`Piirra_Nappain`、`winbox`、`TekstiPalkki`，并与 ELF 原始指令核对。原始输出在本地 `build/analysis/farewell-linux-ghidra.c`；Ghidra 基址 `0x100000` 须从输出地址扣除。原始反汇编在 `build/analysis/farewell-linux.asm`。这是读取二进制的静态分析，没有调用游戏函数或执行交付产物。

`main` 在 `A8F0` 调用 `endgame(10E790)`。原函数依次启动音乐、绘制背景与外框标题、淡入、绘制正文和按钮、`Flip`、`getkeypress`、淡出及退出；`10EAD0 → urw_quit(10E630)` 不返回。不能为语言切换重新调用整段 `endgame`。

| 原生完整文本调用 | 文本身份 | 接入参数 |
| --- | --- | --- |
| `10E81E → 1471A0 winbox` | 标题 | 第五参数 R8；原生七参数调用的第七参数仍从原始栈读取 |
| `10E960 → 13E8B0 showtext` | 最后一棵树 | 第三参数 RDX |
| `10E977 → 13E8B0` | 最后一条河 | RDX |
| `10E98E → 13E8B0` | 最后一条鱼 | RDX |
| `10E9A5 → 13E8B0` | 金钱不能充饥 | RDX |
| `10E9BC → 13E8B0` | 克里族谚语署名 | RDX |
| `10E9F5 → 13EA90 centext` | 献给原住民族及其社群 | 第四参数 RCX |
| `10EA27 → 13E8B0` | 热爱大地 | RDX |
| `10EA59 → 13E8B0` | 亘古不息的生命力 | RDX |
| `10EA8B → 13E8B0` | 倾听、追随、看见与感受 | RDX |
| `10EAA1 → 144FB0 Piirra_Nappain` | 按任意键继续 | 第三参数 RDX |

五条引文在原生栈上由常量块拼装；语义身份由上述调用地址确认，不扫描临时字符串。Mod 仅在当次完整调用中借入中文传输字符串，不回写这些栈字段或游戏英文源数据。

## 度量、编码及原生所有权

- `winbox` 的标题复制边界为 100 字节；该页样式 `0x20` 进入 `TekstiPalkki` 的原生左对齐分支。标题经现有七参数转发调用，不改变背景及标题框几何。
- `showtext` 的本地文字边界为 300 字节，保留 `E4/F6/C4` 的西文字节重映射及四次原生阴影调用；现有双字节传输编码排除这三个字节。`13EA00` 的光标推进使用实际字符度量，最终 `textput` 在当前原生 screen 上同步绘制中文。
- `centext` 的行缓冲及词缓冲各为 1024 字节，保留其 `tokinit/tokget`、空格拼接、换行与 `GuiLINEHEIGHT`。既有 `13EB6F` / `13EC9C` 扩展分别向原生行宽比较及末行居中提供实际宽度；本次在其完整入口提供献辞，不接管居中坐标。
- 按钮译文没有原生的 `.`、`<` 或 `>` 控制符；`1452E3` 既有扩展以实际宽度计算原生 8 像素背景块数量，`145264` 将完整双字节字符交给原生文字调用，`145286` 按字宽推进。按钮背景、原生光标和等待键值仍由游戏管理。
- 字形走已经接入的 screen 输出密度路径，在当次原生文字调用中生成并立即绘入。原生 `Flip`、缓存及淡变处理其已经持有的像素。本次没有新增固定坐标、行槽、页面快照、像素跟踪或 Present/Copy 文字重放。

文本身份扩展在 `sdk/text_services.h`，词条映射在 `modules/semantic/semantic.cpp`，译文在 `catalog/zh-CN/main_menu.tsv`；Linux 的 11 项绑定在 `src/linux/adapter.cpp`。没有新增保护、截断、回退、断言或测试逻辑。

词条静态盘点：标题传输串为 39 字节加 NUL，小于原生 100 字节标题边界；献辞为 41 字节加 NUL；最长底部寄语为 54 字节加 NUL，小于 `showtext` 的 300 字节边界；按钮为 12 字节加 NUL。计数依据是 ASCII 单字节、中文与非 ASCII 标点双字节传输规则，没有执行 Mod 或字体测量程序。

## 已知边界及历史冲突

- 本次针对本机 Linux 正式包，没有新增 Windows 告别页适配。
- 告别页在原生构建时消费所选语言；其输入等待中没有确认纯绘制重建入口，Shift+F10 不重绘已经绘入的告别页。不得通过重进退出函数、模拟输入或延后叠字补造刷新。
- `src/linux/adapter.cpp` 的既有 `glyph_request` 尚未将原生四向阴影预算传入字体校准；非主菜单页面的 resize 完整重建也仍待确认。这些既有待办已列于 Linux profile，不以本次编译发布宣称解决。
- `docs/evidence/farewell-static.txt` 的 `Original display ABI and geometry` 段落中提出 Mod-owned Chinese line slots，`Present and wait-for-key boundaries` 段落提出 Present composition / bridges compose；前者会转移排版所有权，后者会绕过原生即时绘制生命周期。文件开头已明确标记失效设计及影响，历史建议正文清理待办。本次仅参考其页面语义线索，Linux ABI、缓冲与生命周期独立反编译确认，未采用这些旧方案。

Linux 运行中模块退役和加载协议尚未实现，本次不使用 `-Reload`，也不自行关闭或重启游戏。正式文件发布与正在运行的进程是否更新分别记录。

## 交付状态

源码修改、产物编译与正式文件发布均已完成。2026-10-19 12:52:49（Asia/Shanghai），通过根 `build.ps1 -Toolchain Linux -Module adapter,semantic,catalog -Publish` 完成一次配置、一次增量构建及队列内正式发布：

- 请求 `c63f8e01b3f946eca686ea2c46f0ed8d`；批次 `c6e0b6954b364227bec10a2ee04f6fdf`；发布事务 `a50eb7c87a744ae3be8370ae694af18a`。
- 已读取 `build/.compile-queue/results/c63f8e01b3f946eca686ea2c46f0ed8d.json`、完整批次日志 `build/.compile-queue/batches/c6e0b6954b364227bec10a2ee04f6fdf.log` 及该事务的 `publication-result.json`；编译结果 `Success=true`，发布结果 `success=true`，`ReloadRequested=false`。
- 正式更新 `package/modules/uwcn_adapter.dll`、`package/modules/uwcn_semantic.dll`、`package/catalog/zh-CN/main_menu.tsv`、Linux profile 和 `package/release.json`。catalog 模块也已重新编译，但二进制内容与原正式文件相同，未替换。上述三个模块、词库和 profile 的五项 SHA-256 均与正式清单一致。
- 五件被替换的正式文件先移入 `回收/20261019-125249-a50eb7c87a744ae3be8370ae694af18a/`，保留原相对路径，再放入新文件。发布脚本同步既有应用菜单链接；根正式入口仍为 `uwcn_launcher`，启动器与驻留库未重新编译。
- 编译保留原有 HUD/world 前置分发相关的 15 条 switch 枚举警告；本次新增的告别页语义均已显式映射，没有添加默认语义或兜底分支来消除警告。
- Linux 尚无运行中热加载协议。本次正式发布未更新正在运行的进程，没有运行时 Applied 回执；下次由根启动器正常启动时加载正式文件。

禁止自行测试的要求已遵守：没有启动游戏、注入进程、模拟输入、运行产物、运行测试、编写测试用例或添加断言。编译和静态文件身份核对不构成视觉验收。
