# 2026-10-19 Linux 随机世界生成页汉化

对应用户地图截图：`RANDOM WORLD GENERATION`、八个带文字的操作按钮、缩放百分比、比例尺标签及公里数，共12项。保留 +、-、C、I、H、R、W、E 键帽和四个方向箭头，数值、地图与起点随机过程、文化数据和输入动作不变。文化图例沿用已经接入的原生 `kulttuuri_info` 十一种文化译名。

## 静态依据

目标为 Linux x86-64 不真实的世界 3.89 / Steam Build 25939378。原 `urw3-bin` SHA-256：`4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。以下均为 ELF RVA，Ghidra 地址扣除 `0x100000`。

复用既有 Ghidra 12.1.2 工程，以 `-readOnly -noanalysis` 提取；没有执行游戏函数。原始本地输出：

- `build/analysis/world-generation-linux-ghidra.c`：`kartta_main`、`rndworld_screen`、`NaytaMittakaava`、`draw`、`edistymisgrafiikka`、`luokartta`、`LIST_ButtonSpotEntry`。
- `build/analysis/world-generation-consumers-linux-ghidra.c`：`LIST_Reset`、`LIST_Position`、`Set_LIST_Position`、`LIST_Go`、`Piirra_Nappain`、`winbox`、`NaytaKartta`、`NaytaAloitusPaikka`、`kulttuuri_info`。
- `build/analysis/world-generation-scale-linux.asm`、`world-generation-screen-linux.asm`：文本参数、原生数值计算和纯重绘片段；按钮度量依据同时见已有 `skills-button-linux.asm`。

首轮导出将 `F5150`（`LIST_ButtonSpotEntry` 内部返回块）误列为函数起点，脚本在已导出上述七个函数后停止；第二轮只使用符号确认的函数起点，完整提取消费者。没有将该脚本错误视为实现验证。

## 文本边界

实现：`src/linux/world_generation.inc`，从 Adapter 安装；SDK 增加 `world_generation_text=0xF02`，Semantic 读取 `world_generation.*` 词条。Host ABI 2 和既有状态序列化不变。

| CALL 点 | 原生目标与内容 |
| --- | --- |
| `7E856` | `1471A0 winbox`：R8 借入“随机世界生成”；第七个参数从原 Frame 栈读取，flags `0x20` 对应 `TekstiPalkki` 的原生左对齐标题。 |
| `7ED4F`、`7ED6A` | `F4F50 LIST_ButtonSpotEntry`：保留原 `+.`、`-.`，后缀为“放大”“缩小”。 |
| `7EE55`、`7EE70`、`7EE8B` | 同一原生按钮构建：文化区域、文化颜色图例、本族文化区域内开局。 |
| `7EEA6`、`7EEC1`、`7EEDC` | 同一原生按钮构建：重新随机选择起点、重新生成世界、进入这个世界开始游戏。 |
| `7BBB1` | `8F80 __sprintf_chk`：格式改为“缩放：%d%%”，R8D 保留原 `100/zoom` 计算值。 |
| `7BC27` | `13E8B0 showtext`：标签“比例尺：”，原生比例线与位置保持。 |
| `7BC69` | `8F80 __sprintf_chk`：格式改为“ = %d 公里”，R8D 保留原 `zoom*10` 计算值。 |

两个数字格式继续使用原生100字节显示缓冲；缩放原值为1、2、4，中文传输串与原生整数格式化结果均小于该容量。原生标题缓冲100字节、按钮副本1024字节也足够容纳完整译文。没有截断、保护、回退、断言或未知词条分支。

中文先经现有 Layout 双字节传输编码。原生 `textwidth:13B460` 使用完整字符真实字宽，`Piirra_Nappain` 的读取与推进扩展在 `145264/145286` 处理完整中文字形；`F50A8/F50C8` 计算前缀和完整按钮宽度，由原生记录、选择与鼠标处理消费。标题和数值仍进入原生 `showtext/textput`，没有把 UTF-8 字节交给 ASCII 字形索引。

字形同步绘入已接入输出密度的原生 `screen`；背景、行高、边框、缓存保存恢复和显示由游戏管理。新代码只记录调用身份、译文键和临时刷新标量，无页面坐标、行槽、整页文本快照、像素扫描或延后重放。

## 旧页刷新与原生所有权

静态发现 `LIST_ButtonSpotEntry:F5048 → F5150` 在动作已经存在时只重画按钮，跳过原生宽度登记。直接在旧页重复画中文会留下英文宽度的鼠标区域；旧背景也可能残留长英文后缀。本次在世界页首次按钮 CALL `7ED4F` 处理重新加载或语言变化：

1. `LIST_Position:F6100` 读取当前选择；`rndworld_screen:7E7F0` 重建原生背景与标题。
2. 进入原生 `7ED00..7ED30` 地图重绘片段。`R15D` 使用外层原生 `kartta_main` 当次值，原来的 `maski==4` 与图例位判断仍在原指令内执行；`R14D=0` 对应原控制流不变值。`7EFE0..7EFF9` 由游戏调用已有文化图例。`7ED2B` 执行原 `Flip` 后仅在重绘片段期间返回桥。
3. 进入原生 `7EC18..7EC61`：原颜色构建、七参数 `LIST_Reset` 和 `LIST_AdvStyle(1,1)`。`7EC5C` 执行原风格调用后仅在片段期间返回桥。
4. 继续外层原来的十二个按钮调用（含四个方向键），由原生重新登记完整尺寸。最后 `7EEDC` 完成后用 `Set_LIST_Position:F6110` 恢复选择；随后的原生 `LIST_Go` 自行保存 `MENUBUFFER`、绘制选择并等待输入。

`src/linux/redraw.S` 的桥保存 R14/R15，提供两个原生片段所需的栈对齐和返回位置。片段边界由原 CALL 钩子返回，没有复制按钮坐标或原页面排版；没有进入 `srand`、`luokartta`、`etsialoituskohta`、存档或额外输入循环。地图重绘只消费原世界、原位置、原缩放和原文化遮罩。刷新标量不跨原生等待，不新增 ABI 状态字段。

热加载发生在已经等待输入的旧 `LIST_Go` 时，不宣称立即重建缓存：下一次用户正常操作让原生控制流重新构建按钮时，整页及命中区才同步更新。Shift+F10 也在下一轮原生控件构建时应用。无需退出、重启、返回主菜单或重新生成世界；没有注入输入或主动运行游戏来触发重建。

## 审查记录与待确认边界

- `src/linux/adapter.cpp` 原安装列表没有本页文本边界，影响为截图全部英文残留。本次新增12项原生显示接入。
- `LIST_ButtonSpotEntry:F5048` 的原生重复动作分支及 Mod 若仅替换字符串的影响如上。本页已用原生列表构建重算选择及命中；没有手写矩形，其他页面仍以各自证据文档记录为准。
- `src/linux/adapter.cpp:glyph_request` 既有阴影预算与非主菜单窗口缩放重建问题仍待整改，参见 [Linux 字体密度记录](20261019-linux-font-density.md)。本次使用现有原生高清目标，不以编译／发布成功视为这些问题已解决。
- 已在输入等待中的旧页即时完整重建边界仍待确认；本次明确接入下一次原生控制构建，不将模块 Applied 当作画面验收。

## 交付状态

源码修改、产物编译和正式热发布均已完成。统一入口为：

```text
.toolchains/powershell/pwsh -NoProfile -Command '& ./build.ps1 -Toolchain Linux -Module catalog,semantic,adapter -Reload -TargetPid 3968932'
```

- 请求：`a51f71facc9341729b6ffaac25c59497`。
- 批次：`feb3cf65bbe14ffbac4d6ec568f86a6b`；完成时间 `2026-10-19 17:34:30 Asia/Shanghai`。
- 发布事务：`32199d2897d343e4b5a5416f6a32fb2f`。
- 正式替换：`package/modules/uwcn_adapter.dll`、`package/modules/uwcn_semantic.dll`、`package/catalog/zh-CN/main_menu.tsv`、Linux profile、`package/release.json` 共五件。Catalog 二进制内容未变化，仍按本次模块集合重新加载词库。
- 旧五件先按原相对路径移入 `回收/20261019-173430-32199d2897d343e4b5a5416f6a32fb2f/`，再更新正式位置。根启动器与驻留桥无需变更，没有建立平行运行包。
- 已读取对应 `build/.compile-queue/results/a51f71facc9341729b6ffaac25c59497.json`、`batches/feb3cf65bbe14ffbac4d6ec568f86a6b.log` 及 `build/linux-x86_64/stage/32199d2897d343e4b5a5416f6a32fb2f/publication-result.json`。请求 `Success=true`，发布 `success=true`、`runtime_requested=true`。
- PID `3968932` 返回 `ReadyToPublish` 后完成正式归档／替换，再返回 `Applied`；Catalog、Semantic、Adapter 均为第2代。
- Adapter SHA-256：`19476e0e4fdecf9751b2574f98a965813b3a11f61eb0cae30b90ffff0ed1553b`；Semantic：`b001e9e7bcfc2136f06e289c21a6fd3da1ae55fec3764975cff67ab9b0d7f21b`。正式清单与运行时回执记录相同身份。
- 对正式 Adapter 的只读反汇编确认 `uwcn_linux_redraw_world_fragment:26742` 为保存 R14/R15、设置图例值、间接调用原生片段、恢复寄存器并返回的桥。没有执行该产物。
- 编译保留 `semantic.cpp:key` 既有 HUD／world 枚举分派警告；新增世界生成组件有明确分派，Adapter 与汇编没有新增编译警告。

没有启动、关闭或重启游戏，没有注入输入、运行测试、编写测试用例或断言。仅执行已授权兼容业务热发布；Applied 表示模块交接完成，当前旧页的下一次原生重建及实际视觉效果未自行验收。
