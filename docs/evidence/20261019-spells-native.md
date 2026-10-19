# 2026-10-19 Linux 咒语与法术页汉化

对应用户截图中的角色创建咒语页。接入标题、25种咒语的完整名称和简介、初始引导、退出以及底部百科标题／概述／F1提示；同一原生界面在游戏内打开时的普通说明、即时施法说明一并接入。共58条词库记录。截图四项为“通用献祭、熊颅仪式、使树上的松鼠静止、布设野兔套索”。

只改本页显示边界，不改原生咒语编号、已学咒语、即时施法标志、字母动作、ESC、F1或百科英文检索身份。原记录共五个说明槽，本次仅在列表显示边界翻译第0槽简介，其他说明槽和施法过程消息未宣称接入；五槽原始内容与共享读取函数均不改。

## 静态材料

目标为 Linux x86-64 UnReal World 3.89 / Steam Build 25939378。原游戏 SHA-256 为 `4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`；原 `gameinfo/urw_scrinfo.txt` 为 `c9e028d0fd0fe133d21bacb3c2bc708a10312ef4ca7816df89fda89a7499c6ae`。本文地址均为 ELF RVA，Ghidra 的 `0x100000` 基址已扣除。

复用本地 Ghidra 12.1.2 项目，以 `-readOnly -noanalysis` 提取，没有执行游戏函数或游戏产物。原始材料在 `build/analysis/`：

- `spells-linux-ghidra.c`：`CompileMagicSubscreen`、`ComposeRitualList`、`CompileInfoboxRitualList`、`MagicProfile` 和咒语记录构建／名称／简介函数。
- `spells-consumers-linux-ghidra.c`：纹理段落、标题、纹理菜单按钮、百科页脚和屏幕帮助文件读取。
- `spells-controls-linux-ghidra.c`：`render_drawbutton`、`renderTekstiPalkki`、`renshowtext`、`CreateGamesizeTex`、`LIST_AdvStyle`。
- `spells-linux.asm`、`spells-paragraph-linux.asm`、`spells-button-linux.asm`、`spells-title-linux.asm`、`spells-list-input-linux.asm`、`spells-highlight-linux.asm`、`spells-flipper-linux.asm`：原始指令与调用参数。
- `spells-constant-records.json`：由反编译中的常量赋值与 ELF 原始只读数据拼出25条名称及简介，没有调用或模拟执行 `taikakeinoS`。编号160的编译器块复制按只读数据源 `1F9080` 的257字节及末尾常量合并读取。

原生 `taikakeinoS` 在结构 `+0xD` 构建名称，`+0x5D` 开始是每槽400字节的说明；`taikakeino_desc(id,0)` 选择本页简介。25个有名称的编号为9、10、25、40、60、70、80、82、89、90、93、94、100、110、111、115、120、130、135、160、180、190、192、200、225。`ComposeRitualList` 仍按原生已学记录和非空英文名称构建 `RitualList(6692660)`。

## 显示边界

| 原生调用 | 接入内容及保留语义 |
| --- | --- |
| `106777 → 147F10 SubscreenToTexture` | RSI借入中文标题；原纹理与原 `renderTekstiPalkki(mode 5)` 构建不变。 |
| `106834/106870/1068B7 → 1B0130 SANATAULUKKO_finfo` | 保留原文件读取，随后以对应 GENERAL／INSTANT／INITIAL 完整译文重建同一原生词表。原语言文件和主题键不改。 |
| `106CD8 → F5200 LIST_toTex_ButtonSpotEntry` | 根据原动作 `a + index` 读取对应 `RitualList[index]`，R8只借入“原ASCII键帽前缀＋完整中文名称”。原函数自己绘制、计算尺寸、注册动作和命中区域。 |
| `106D38 → F5200` | ESC前缀保留，动作文字译为退出。 |
| `106A9D → 1AFE00 SANATAULUKKO_Lisaa` | 按调用时RBX中的原生列表索引选择简介，仅替换当次RSI显示参数。 |
| `106D03 → 50110 toTex_GameInfo_Hotspot` | 限定同步页脚构建作用域；内部 `501CB/502B9 → toTex_showtext`、`5030C → F5200` 借入中文标题、完整语义概述与F1文字。传给原百科检索和跳转的 `SPELLS` 保持。 |

`F5200` 原生列表项存储的是 `TEXTSPOT`／`NOTEXTSPOT` 标记、动作和几何，而非咒语正文。本次未建立自己的列表几何或屏幕行槽，也未改变内存中的英文咒语记录。名称与键帽文字在完整原组件调用期间借入；不在逐字绘制处匹配英语替换。

本页使用mode100的纹理列表。`LIST_ren_Highlight:F5F48..F5FB6`读取原生项的 `+D8`总宽、`+DC`高度和 `+E4`前缀宽，并按 `LIST_AdvStyle(1,1)` 排除键帽区域；这些数值都由原 `F5200` 消费同一中文字宽后保存。没有让原生选择框反过来读取Mod布局。

## 原生中文度量与高清目标

`src/linux/spells.inc` 为本页实现显示调用及已确认的纹理文字度量扩展：

- 中文先经现有 Layout 双字节传输编码。段落把完整中文字符作为原生词元输入，`<br>`保留；`>`自身已推进原生词槽，后面不再插入分词空格，避免产生会终止原生读取的空词。原词槽为130字节，中文字元占2字节。
- `13F3D8` 原 `LEA EDX,[R12+R8*8]` 和随后 `ADD EAX,EBX` 改用同一原生renderer的真实字宽；保留R8中的原字节数，供后续原内存复制使用。
- `13F51A` 保留原 `RDX -= RBX`，以renderer字宽替换随后按字节推进R12的表达式。`13F44A` 对中文词元不追加西文词间空格；原生复制的NUL已存在，ASCII词仍执行原复制。
- `147D93/147EAC` 以renderer实际字宽替换两个标题分支的 `strlen << 3`，保留原生除二、居中与边框计算。
- `145CBA` 接入原 `render_drawbutton` 普通文字光标推进；ASCII键帽及其原贴图分块尺寸仍由原组件计算。
- `F5392/F53B2` 的原字宽调用消费同一个renderer度量，使原生按钮总宽、前缀宽、列表选择与鼠标命中随同一中文文本计算。

`CompileMagicSubscreen:10672D` 调用原 `CreateGamesizeTex`；后者是直接尾调用创建原生800×600目标。只在这次已确认的组件创建作用域扩展到窗口真实输出密度。`CompileInfoboxRitualList:106A65` 的原250×120目标同样在已确认创建点扩展，`InfoboxRect`原逻辑尺寸不改。

原标题／按钮／帮助构建结束恢复窗口目标；说明框在 `106B1A` 恢复窗口目标。原 `LIST_Go → Flipper:13A790` 也在呈现前选择窗口，因此这两个创建边界可以读取窗口输出密度。原生QueryTexture消费者仍得到逻辑尺寸，原生SetRenderTarget选择时应用该目标的实际密度。中文字形通过现有 `rentextput` 替换在当次原组件调用内直接绘入已扩展的目标。

`src/linux/native_targets.cpp`只增加这两个组件的创建识别及资源密度元数据。已绘入的像素、窗口背景、纹理替换、清除、选择、淡入淡出、上传和呈现均由游戏持有。没有像素扫描、绘制贡献序列、页面快照、固定坐标表或延后文字重放；没有把低分辨率中文放大当作高清。

## 审查记录与未确认边界

- 原 `src/linux/adapter.cpp:initialize` 只扩展软件段落、软件标题和按钮推进，尚无本页调用；原生纹理段落 `13F3D8/13F51A`、标题 `147D93/147EAC` 和普通按钮 `145CBA` 仍按字节度量。影响是直接传UTF-8／双字节文本会导致宽度、换行和推进错误。状态：本次按上述原生接口整改。
- 原 `src/linux/native_targets.cpp:create_texture` 仅扩展upload与地图作用域，未覆盖本页主纹理和说明纹理。影响是即便能绘出中文，也只会在原小目标中光栅化再放大。状态：本次已为这两个确认目标整改；未宣称扩展其他未知目标。
- `src/linux/adapter.cpp:glyph_request` 的既有逻辑行高／墨高以及原生四次阴影预算尚未完整传入字体校准；非本页其他窗口的缩放重建仍按 `20261019-linux-font-density.md` 记录待整改。本次不以编译或发布成功作为这些旧问题合规的证明。
- 本页中文和密度在原生构建时生效；移动选择后，简介在原 `CompileInfoboxRitualList` 中重建。已缓存主纹理不会因本次热加载立即重画，Shift+F10的即时整页纯刷新边界也尚未确认。`MagicProfile`拥有列表重置、输入等待、音乐和施法选择，不为刷新重入整个函数，不伪造原 `-42` 重建结果或按键。
- 新增临时作用域仅存在于不等待的同步构建调用中，不跨输入等待保存业务栈。已有Adapter状态格式、Host ABI 2、原生编码编号、资源状态格式均保持；新目标使用原有资源身份／密度序列化，不增加UI内容状态。

## 交付状态

源码修改、产物编译、正式文件发布及已授权的兼容热加载均已完成，完成时间为2026-10-19 15:24:45（Asia/Shanghai）。

- 根入口为 `.toolchains/powershell/pwsh -NoProfile -Command '& ./build.ps1 -Toolchain Linux -Module adapter,semantic,catalog -CMakePath /usr/bin/cmake -CompilerPath /usr/bin/g++ -BuildDirectory /home/lulika/workspace/urwcn/build/linux-x86_64 -Publish -Reload -TargetPid 3820329 -PackageDirectory /home/lulika/workspace/urwcn/package'`。提交前保存全部修改，所属批次结束前未继续修改请求源码。
- 请求 `0451b3f091ee422094d2077742db16f6`，批次 `3260ad371d6d4f8f8befa3625744ec65`。已读取对应 `results/<request>.json` 和完整 `batches/<batch>.log`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true`；仅一次配置和一次增量构建。
- Adapter、Catalog、Semantic均编译完成。仅有Semantic原有15项HUD/world枚举分派 `-Wswitch` 警告，无新增咒语组件警告或编译错误；没有添加默认分支掩盖警告。
- 正式事务 `3ad5a3432ad742da9ae40f9992688a57`。已读取 `build/linux-x86_64/stage/3ad5a3432ad742da9ae40f9992688a57/publication-result.json`，`success=true`、`runtime_requested=true`。
- 正式替换Adapter、Semantic、主词库、Linux profile和发布清单五件。旧五件先按原相对路径移入 `回收/20261019-152445-3ad5a3432ad742da9ae40f9992688a57/package/`，已只读确认存在。Catalog二进制未变，因词库更新参加热加载；根启动器与驻留桥保持原正式路径，未建立平行运行包。
- PID `3820329` 返回 `ReadyToPublish` 与 `Applied`，Catalog第4代、Semantic第3代、Adapter第5代。回执表示模块交接成功，不表示当前旧纹理已重建或经过视觉验收。
- 已只读核对下列源码／构建与正式文件SHA-256一致。Adapter、Semantic身份同时出现在Applied回执中。

| 正式内容 | SHA-256 |
| --- | --- |
| Adapter | `361ab737446ebda85ac4ee5e7c2647631cd1d75575255d0aba2dde960b727555` |
| Semantic | `ae55751c7de60caf63dbe86362ebf10e35bf9c0338429e92c805f4d85a991881` |
| 主词库 | `e55652e11e726d5a7ddb1b820a302231e5c5ab95f274aa9e61c4d083586e3db2` |
| Linux profile | `802de350256461a9b557ce4392ca6d4c8a2b8d268ca286f0ab2a6b752c74a398` |

未启动、关闭或重启游戏，未注入运行中的游戏或模拟输入，未运行产物或测试，未创建测试脚本、测试用例或断言，未增加推测性保护、回退或兜底分支。
