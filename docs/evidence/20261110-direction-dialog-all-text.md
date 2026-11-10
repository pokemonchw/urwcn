# 方向／目标选择窗口：全部文本来源提取

日期：2026-11-10，Asia/Shanghai。对象为用户截图中“选择要关闭的门”及其共用方向／目标选择窗口，Windows x86《不真实的世界》3.89.1 / Steam Build 26139145。原 PE SHA-256：`c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。

仅执行磁盘 PE 静态读取、Ghidra 反编译、原指令／源码审阅；不启动、操作或测试游戏，不模拟输入，不运行产物，不创建测试用例、测试脚本或断言。正式业务发布使用既有授权的驻留事务。下文代码地址为 RVA；提取的反汇编与 Ghidra C 使用 VA，须减首选基址 `400000h`。

## 漏译原因及完整调用链

已有 `windows_target_help.inc` 只处理固定 `CHOOSE TARGET` 标题及 `F7B61/F7B6D` 固定正文。截图的原模式为 `06h`，沿另一条 `F7ADE → F7AEF/F7AFB → F7B33` 构建动作说明，原标题也来自调用者，因此现有“选择目标”补丁没有覆盖它。

原 PE `.text` 的相对 E8/E9 目标逐字节枚举，得到：

| 原入口 | CALL 数 | 尾 JMP 数 | 原始语义来源 |
| --- | ---: | ---: | --- |
| `F7820` | 66 | 0 | 30个固定目标分支、30个非空直接动作、3个空标题、3个包装函数 |
| `F8740` | 2 | 0 | `A313E` 开门，`A3387` 关门 |
| `F88C0` | 3 | 0 | `101D3C` 未完工建筑、`11DB2E` 剥皮、`11DC3A` 分割尸体 |
| `F8BC0` | 2 | 0 | `59C7` 设置陷阱、`166281` 挖坑 |

全部文件节未发现以上四入口的绝对地址引用。Ghidra 原引用表与相对目标枚举闭合；普通线性反汇编在跳表数据后漏掉的 `5238 → F7820` 另从确切入口提取。没有推测新的调用者或动作。

`F8740` 在 `F8754` 保存原 ECX 标题到真实 `[EBP-30h]`，`F8803/F8808` 把它作为 EDX 传给模式 `06h` 的 `F7820`。`F88C0` 在 `F88E9` 保存原 ECX 到 `[EBP-4Ch]`，`F8B4C/F8B51` 以模式 `02h` 消费。`F8BC0` 在 `F8BC0` 将原 ECX 转为 EDX，`F8BC5` 同样进入模式 `02h`。

完整原始来源清单：

- [73处调用记录、模式与实参](20261110-direction-dialog-callers.tsv)
- [37种非空动作标题及36种实际动作提示的中英对照](20261110-direction-dialog-texts.tsv)
- 带原实参约定的完整反编译保留在本地 `docs/evidence/20261110-direction-dialog-typed-ghidra.c`，由[只读提取脚本](direction_dialog_Decompile.java)生成；原始 C 按仓库忽略规则不提交，脚本赋予的函数名是本次静态分析名称。
- [完整窗口反汇编](20261110-direction-dialog-native.asm)、[三包装函数反汇编](20261110-direction-dialog-wrappers.asm)、[调用点上下文](20261110-direction-dialog-callers.asm)、[陷阱调用缺失段](20261110-direction-dialog-trap-call.asm)

37种动作覆盖采集植物、陷阱及陷阱坑、下网、辨识植物、拆除、拾取、水源与挤奶、推动物品、建造与施工、开洞、剥树皮、伐树、木材加工、攀爬、观察、生火、踢击、敌人、拴系、瞄准、开关门、剥皮与分割尸体。调试入口 `170D77` 的 `Mihin Sihtaa` 也有确切原来源，译为“选择瞄准位置”；其模式 `10h` 不执行动作正文，因此没有为它补造 `Select ...` 资源。

后续截图暴露了本次直接消费者清单遗漏的 `F7AB6 → 114A20` 生物切换辅助函数。其原串 `[+]Next, or [-]Previous creature` 已完整反编译，新增两段语义及对应的原生字宽扩展；此前“全部已处理”的结论在此更正。当前 `target_help` 资源共81条，详细依据及本次交付状态见[生物切换提示补齐记录](20261110-direction-creature-hint.md)。下文79条及交付批次保留为此前两批的历史记录。

## 全部显示文字与原生消费边界

| 原调用／操作 | 完整原文本及用途 | 处理 |
| --- | --- | --- |
| `F7918 → 116270` | `CHOOSE TARGET`，或调用者标题经 `D3DB0` 转大写 | 固定标题沿既有“选择目标”；37种动作标题按完整语义翻译 |
| `F792F/F7971/F7A01/F7A43 → 114680` | `7`、`9`、`1`、`3` | 保留原数字键帽及动作 |
| `F795A/F799C/F79C7/F7A2C → 114680` | `%c` 生成的原字形索引 `18h/1Bh/1Ah/19h` | 保留上／左／右／下箭头键帽及动作 |
| `F79EA → 114680` | 模式 bit4 存在时显示 `5` | 保留原中心格键帽与选择自身位置的动作 |
| `F7A88 → 114680` | `ESC.Exit` | 沿既有 `ESC.退出`，保留点号键帽语法 |
| `F7AA5 → 114680` | `ENTER.Select`，仅固定目标分支存在 | 沿既有 `ENTER.选择`，保留键帽及实际选择动作 |
| `F7AB6 → 114A20` | `[+]Next, or [-]Previous creature`，仅固定分支有可选生物时存在 | 后续补齐完整辅助函数，见[本行提取与宽度记录](20261110-direction-creature-hint.md) |
| `F7ADE → 10D0` | `Select %s`，`%s` 为原调用者英文动作 | 原格式化及原栈缓冲保持英文；仅下游完整消费转中文 |
| `F7AEF → 162300` | 上项完整 `Select ...` 结果，ECX=1 | 36种完整动作提示，如“请选择要关闭的门。” |
| `F7AFB → 162300` | `with these cursor/numpad keys representing the cardinal directions, or by clicking the location with the mouse.`，ECX=0 | “可使用图示的方向键／数字键选择方向，也可用鼠标点击位置。” |
| `F7B33 → 10EB40` | 上述原生词表的完整段落 | 沿原宽高、行距、颜色和原生换行 |
| `F7B61 → 162300` | `Choose target by pointing and clicking the location by mouse, or`，ECX=1 | 沿既有“用鼠标点击目标位置，或” |
| `F7B6D → 162300` | `by moving the cursor using these cursor/numpad keys.`，ECX=0 | 沿既有“用图示方向键／数字键移动光标来选择目标。” |
| `F7BA9 → 10EB40` | 固定目标帮助段落 | 沿原生完整段落 |

`F78C4` 以 mode bit0 决定固定标题／调用者标题；`F7ACE` 以 bit1 决定动作正文。不存在动态的物品名称、NPC名字、地形名或玩家文本拼接到这些动作标题的来源。固定目标分支传入的 `kutuchk`、`Kuka sihtaa`、`Select zoommap`、`Select pos`、`spotloc` 及原临时缓冲，都被原生 bit0 分支忽略，不冒充显示文字翻译它们。

三个 `04h` 模式调试调用 `175140/17516D/17B355` 明确传入同一个原空串，不显示标题和正文。标题钩子保留这一确定的空语义；`native_hud_command_migration.inc` 补齐其原 MOV EDX 操作数 `17513A/175167/17B34F`，使原生语言重建同样能读取真实空输入。这不是缺失翻译时的回退或默认值。

## 实现与所有权

`modules/adapter/windows_target_help.inc` 扩展现有 `F7918` 标题消费，并新增两个确切原调用 Hook `18505/18506`。`D3DB0` 只复制并转大写；所有37种非空标题都是 ASCII，因此目录身份仅对完整原文本的 `A..Z` 转小写，分别使用 `target_help.heading.<完整原文>` 和 `target_help.prompt.<完整原文>`。没有宽泛单词替换、按画面猜测、未命中保留英文的兜底或新的业务动作。

`catalog/zh-CN/main_menu.tsv` 新增74条资源：37条标题、36条实际动作提示、1条共用方向／鼠标说明；与已有5条固定目标／按钮资源合计79条。完整 `Select select a trap` 等原文也按其确切格式化结果收录；译文使用自然中文“请选择陷阱。”。

新正文经既有传输编码与 `native_paragraph_words` 完整字形词元送入原 `162300`。保持 ECX=1清空／ECX=0追加的原词表生命周期，原 `10EB40` 通过现有 `10EE68` 宽度和 `10EF57` 推进扩展消费完整字形。标题在 `Scope::titled_panel` 内由原 `116270`、`116631`、`11665C` 消费中文字宽和字形；字形按当前原生目标真实输出密度即时提交。没有把 UTF-8 直接塞入按字节布局的 ASCII 路径。

普通进入、已有 `native_hud_language::target_result` 原生输入返回后的完整窗口重建、以及兼容交接，均经过同一组组件文字调用。原方向选择、目标坐标、当前目标、鼠标命中、矩形、背景保存、缓存重建、呈现与淡入淡出保持原有所有者。没有新增固定坐标、行槽表、整页快照、文字贡献序列、像素扫描或 SDL Present 叠字。

## 既有待整改项

| 文件与位置 | 影响 | 状态 |
| --- | --- | --- |
| `modules/adapter/native_footer_component.cpp:88` 起 `paint` | 仍由 Mod 计算主菜单署名位置、间隔与宽度，违反原生布局所有权 | 既有问题，待整改；本次目标窗口不扩展该路径 |
| `modules/adapter/native_ui_scene.cpp:12` 起 `Child/Container`、`:30` 起 `CacheRegion` | 仍保留历史组件集合、矩形与序列化结构，旧方案残留尚未完全退役 | 待整改；本次只使用原生完整窗口构建，不遍历这些集合回放文本 |
| `translations/build-message-catalog.ps1:17` 起 | 仍按旧版绝对字面量地址读取 PE，3.89.1 地址适配未完成 | 待整改；本次直接修改已确认组件词库，不执行该生成器 |

## 交付状态

首批请求 `2ad7b3f7e44449d2a748a3083df7f0b1`、批次 `68e486524de141f3bb245d68c8b28916` 已完成统一队列的一次配置和增量编译，既有函数指针转换、extern 初始化、未使用项和缩进警告保留，无编译错误。正式事务 `2a0bd7b9acf74f3e92a72a14cd58f10e` 在18:48:56返回 PID368 的 Catalog 第2代、Adapter 第3代 `Applied`；旧件先移入 `回收/20261110-184855-2a0bd7b9acf74f3e92a72a14cd58f10e/package/`。实际替换 Adapter、`main_menu.tsv` 与正式清单，Catalog DLL沿用原件并重载新词库。

**首批热更新随后造成用户游戏退出，不能将上述 Applied 视为稳定运行。** 用户明确说明未作任何操作。Steam `gameprocess_log.txt` 与 `console-linux.txt` 记录原 Linux PID3071321于18:48:58退出，紧随首批交接；没有取得这次的异常转储、崩溃 EIP 或调用栈，系统 core 目录及 Wine 用户目录没有对应新转储。

静态复查确认已有完整重建漏了一个必需输入，详见[热更新退出的栈槽复用记录](20261110-direction-dialog-hot-reload-stack.md)。源码已补齐，并完成第二批统一编译与正式文件发布；游戏已退出，本批没有对 PID368请求热加载。没有自行启动或复现游戏。

第二批使用根统一入口：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Publish
```

| 项目 | 最终状态 |
| --- | --- |
| 源码 | 完成37种标题、36种提示、74条新增资源、三个明确空标题来源及重建栈输入修正 |
| 编译请求 | `eacb35700ff048fc8839d557904fbe86` |
| 编译批次 | `fb635bf0bd8647978ae47f79e3c44576`，一次配置及增量编译，`Success=true`，既有警告保留 |
| 正式事务 | `06a2fe28463743a6b97665b7a4978359`，18:51:15完成，`success=true` |
| 正式位置 | 替换 `package/modules/uwcn_adapter.dll` 与 `package/release.json`；74条词库沿用首批已正式写入的 `package/catalog/zh-CN/main_menu.tsv` |
| 旧件 | 先移入 `回收/20261110-185115-06a2fe28463743a6b97665b7a4978359/package/`，保持原相对路径 |
| 当前进程 | 首批热更后已退出；第二批 `ReloadRequested=false`、`runtime_requested=false`、`runtime_receipts=[]`，没有新的 Applied |
| 正常启动路径 | 根 `uwcn_launcher.exe` 仍加载同一正式 `package/`，无平行修复包；代理未启动游戏 |

已完整读取两批的 `build/.compile-queue/results/<request-id>.json`、`batches/<batch-id>.log` 与各正式暂存事务的 `publication-result.json`。

| 正式文件 | SHA-256 |
| --- | --- |
| Adapter，正式件／构建件一致 | `2c30ef3bf1cbe881474d44a6c605bfb1beca8fd74d46a721a6421d47bc237d47` |
| main_menu.tsv，源码／正式件一致 | `da85d0f91197d75586468f8bf9d41c935dbb656c2e5b73d7e668fabb9973b4ab` |

上述两批的源码、产物编译与正式文件发布均已完成。栈槽修正有原指令依据；尚无代理自行进行的游戏运行或画面验收，不能把编译与正式发布当作运行稳定性证明。后续截图发现的生物切换提示已另外补齐并正式发布，最新文件身份见[后续交付记录](20261110-direction-creature-hint.md)。
