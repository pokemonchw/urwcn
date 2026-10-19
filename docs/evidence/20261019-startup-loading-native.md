# 2026-10-19 启动加载信息接回原生文字链

本记录对应 UnReal World 3.89 / Steam Build 25939378。目标为 `D:\program\steam\steamapps\common\UnRealWorld\urw.exe`，既有静态指纹为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。以下地址均为 RVA；objdump 输出 VA 使用首选基址 `0x400000`。

本轮阅读已有 Ghidra 输出，并只读反汇编启动标题、进度显示器、音频加载调用及外层作用域。没有启动、注入或操作游戏，没有执行产物、测试命令、测试脚本或断言。静态审查不构成运行效果验证。

## 已确认的显示范围

| 原生调用点 | 原目标及原文 | 显示参数来源 |
| --- | --- | --- |
| `180894` | `10E5A0`；`Entering into UnReal World - please wait ... `，字串 `1DC89C` | 原 ECX/EDX 为 10/10，白色，outline 0 |
| `180905` | `123DF0`；`Sound init ... `，字串 `1DC8CC` | 无动态参数 |
| `180941` | `123DF0`；`Could not open audio! -- Press a key to continue --`，字串 `18DED8` | 无动态参数 |
| `C2B5` | `123DF0`；`Loading intro ...`，字串 `18E2F4` | 无动态参数 |
| `B0E0` | `123DF0`；`Loading audio: %s`，格式 `18DE84` | 原 key 在 EDI |
| `B3A6` | `123DF0`；`Loading audio: %s`，格式 `18DE84` | 原局部 key 在 `[EBP-70]` |
| `B016` | `123DF0`；`FAILED TO LOAD: %s`，格式 `18DE58` | 原资源路径在 `[EBP-808]` |
| `B331` | `123DF0`；`FAILED TO LOAD: %s`，格式 `18DE58` | 原资源路径在 `[EBP-870]` |

七个进度调用均通过 ECX 传入原 NUL 结尾英文显示串，无栈参数。标题及 `123E6D → 10E5A0` 的 ABI 均为 ECX=x、EDX=y，栈参数依次是 text、mapped color、outline，调用者清理 12 字节。

音频显示仅在 `180B4D → B3D0`、`180B59 → B3D0` 的原生调用作用域内翻译；片头进度仅在 `180B52 → C1C0` 作用域内翻译。前两者分别使用原 mode 0 和 1，加载、资源键、文件名、表格写入、音量和成功/失败分支均不改写。`B3A6` 的本地 key 保持原大小写：`B360` 的 helper 返回另一个大写结果供内部表使用。完整资源身份清单仍见 [音频静态记录](startup-audio-static.txt)，其既有安装集包含 109 个可见成功 key。

词库现已加入六个启动提示及这 109 个资源名的中文显示项。成功提示按原 key 查找资源译名；失败提示保留原实际资源路径作为参数，便于识别具体文件。`windfly`、`kling`、`music_munni` 等名称按文件名词义翻译，没有播放音频进行听辨；这部分译名不应被描述为已确认音频实际内容。

`17E6CE/17E71C` 的 `Loading %s ...` 属于主菜单返回后的 `17E4C0` 读档路径，不属于本次启动进度。`123DB0` 和其他 `fputs` 调用是日志边界，不新增屏幕译文。

## 原生输入、度量与即时绘字

`123E15` 将输入 ECX 存入 ESI；`123E30..123E3E` 测量英文原串，长度大于 80 时将 `ESI[70]` 写成 NUL；`123E69` 推入 ESI 供 `123E6D` 绘字；`123ED3` 再推入同一 ESI 写入 `init_log.txt`。因此 adapter 不替换 `123DF0` 的 ECX 或原缓冲，而是在已确认的七个调用点依据语义及原参数产生本次译文，只让嵌套的 `123E6D` 借用该字符串。

`startup_progress` 作用域持有本次调用的临时编码字符串，直到对应 `123DF0` 的 After 释放。嵌套 `Scope::text` 仅在 `10E5A0` 调用期间活动；没有整页字段快照、延迟绘制或等待期间的文本重放。标题同样仅在 `180894` 的文字参数处借入译文。新增作用域沿用现有 `Active` 结构和 Before/原函数/After 调度，不新增驻留 ABI 或持有业务 DLL 调用栈跨越原生等待。

原 `10E5A0` 会将 `C4/E4/F6` 字节重映射，故沿用 layout 的原生安全双字节传输编码，完整字符串进入度量或绘制时先还原 Unicode。原 `10E700` 真实宽度扩展替代字节数乘 8 的光标推进，保留原 cursor_y 写回、cursor_x 后续写回及返回语义。`10E5A0` 的 `[EBP-130]` 文本区至下一局部字段共 `0x12C` 字节；新增借用沿用这个已确认容量契约。

五个完整串输出调用 `10E67C/10E68D/10E69E/10E6AF/10E6D8 → 10DDB0` 继续沿用既有即时绘字服务。原生提供位置、颜色、描边和调用顺序，Render 按当前 `61BBB10` 主面的真实尺寸与原 800×600 逻辑域生成字形，立即写入该面。启动标题与进度的 outline 均为 0；进度原色由 `123E48/4D/52` 的 `0xAB` 参数经 SDL_MapRGB 生成，保留原颜色解释。

## 原生目标及后续生命周期

冷启动的原生 renderer 创建早于 `11796D` 上传纹理和 `1179B9` 主软件面的创建。既有 `native_targets.cpp` 在已确认的上传纹理创建入口获取实际输出密度，并同步扩大后续主面与已登记原生缓存；本次不新增目标表或页面布局。目标及直接读写证据见 [原生高清目标记录](20261019-native-hd-target-boundaries.md)。该既有记录保留的未解析间接别名及迁移范围限制仍然有效，本次不宣称覆盖所有游戏文字族或所有界面 resize 行为。

`123DF0` 原先从 `1DD8A0` 取得 `{5,30,396,11}` 逻辑矩形并清理进度行，原 `123E63/6A` 设置绘字位置。当前 adapter 不保存这些坐标或建立独立行槽；既有原生目标扩展把当次 SDL 矩形转换为实际面坐标。`1808A5/123E7E → 10AF90` 随后上传原生主面的实际 pixels/pitch；`1808DE/123EB7` 的 Present 和原分支保持原样。

已有失败等待仅为 `B01B → D3C80` 和 `180946 → D3C80`；`B331` 路径没有等待。本次不新增这些等待的 hook。`D3C9A → 10AF90` 及等待事件触发的既有原生重绘消费已经含中文的主面；译文缓冲在进度函数返回后即可释放，不需在 `D3CD3/D1E70/D1F48/10B763` 再叠字。

## 旧文档违规与整改

以下行号均对应本次改写前原件，已按原相对路径无覆盖保存到 `回收/20261019-startup-loading-docs/`。旧文档曾记录的编译或发布不使其方案符合当前要求。

| 原文件及原行号 | 问题及影响 | 本次状态 |
| --- | --- | --- |
| `startup-loading-static.txt:20` | 将 x10/y10/width780/height18 和字形预算定义为 Mod 行槽，转移原生布局所有权。 | 删除接入建议，改为借用原文字参数及原生坐标。 |
| `startup-loading-static.txt:28–32` | 改写 Present 并在提交前合成标题，像素不归原生文字调用与缓存管理。 | 撤销该实现说明，原 Present 保持；标题即时写入主面。 |
| `startup-audio-static.txt:150–161` | Present bridge 合成、抑制原文字消费者、固定进度槽、保存标题和进度 DisplayPlan。 | 撤销整组方案，改为原生消费者借文、真实度量及当次绘字。 |
| `startup-audio-static.txt:233–238` | 将旧叠加方案造成的中文丢失当作等待期间继续合成的依据。 | 明确该问题来自已撤销旧方案；当前原生面直接持有中文像素。 |
| `startup-audio-static.txt:253–259` | 在多个等待和窗口事件 Present 处重放加载计划，让 Mod 承担重绘生命周期。 | 删除等待合成要求；本次源码没有这些等待或 Present hook。 |
| `docs/hot-reload.md:31` | 把旧 `LoadingRequest` 和新增驻留桥、离线发布要求当作启动汉化迁移限制，误导当前兼容业务交付。 | 主代理已保存原件到同批回收目录，并改写为现有 ABI 1 通用调用桥、业务及词库发布；本次不修改驻留 DLL。 |

本次静态审查未发现新增 startup Hook 的调用点、参数数量或临时字符串生命周期与上述证据冲突。该结论只覆盖这次启动接入，不消除其他历史审查记录中的待整改项，也不代表运行验收。宿主 `src/loader/host.cpp:52/56`、`src/loader/hook_host.cpp:39/73` 的既有错误透传和事务失败语义仍按 [实现纠正记录](20261019-implementation-correction.md) 保留待整改状态；本次未修改驻留层，不把服务返回 Status 当成该问题已解决。

## 编译与正式发布

- 源码：`sdk/text_services.h` 新增六个组件标识；`modules/semantic/semantic.cpp` 处理启动模板及资源显示名称；`catalog/zh-CN/main_menu.tsv` 增加六个模板和 109 个资源词条；`modules/adapter/module.cpp` 增加 12 个已确认调用 Hook。共享结构大小、Host ABI、启动器及驻留 DLL 均未变更。
- 编译：统一入口 `build.ps1 -Module adapter,semantic,catalog -Publish` 成功，请求 ID `b242afcb62004547b0b4653d96b37e3b`，批次 ID `75b21b81284a422da34824c07db04ce6`。已读取 `build/.compile-queue/results/b242afcb62004547b0b4653d96b37e3b.json` 和对应批次日志，均记录成功。既有 GetProcAddress 到已确认 SDL_GetRGB 函数类型的转换警告仍存在，无编译错误。Catalog DLL 重新编译后的哈希与正式文件相同，无需替换该 DLL。
- 正式发布：事务 `649f861069a24a958405a43de02d553e` 已完成，已读取 `build/mingw-x86/stage/649f861069a24a958405a43de02d553e/publication-result.json`。五个旧文件先按原相对路径移入 `回收/20261019-021949-649f861069a24a958405a43de02d553e/`，随后替换正式 `package/modules/uwcn_adapter.dll`、`package/modules/uwcn_semantic.dll`、词库、构建适配和 `package/release.json`。正式清单全部十项的 SHA-256 与磁盘文件相符；根 `uwcn_launcher.exe` 仍是正常启动入口，无平行交付包。
- 运行时应用：发布前只读进程列表未发现 `urw`，未请求 Reload，发布回执为 `Runtime Applied was not requested.`。没有运行时 Applied 或视觉验收结果。本轮未启动游戏、注入运行中的游戏、模拟输入、执行产物或测试，也未编写测试用例或断言。

| 正式替换文件（相对 package） | SHA-256 |
| --- | --- |
| `modules/uwcn_adapter.dll` | `cf0a916907deb28e7332e9f08d27a0db4b848f44e967050f44c4a6c413cd7f7b` |
| `modules/uwcn_semantic.dll` | `7281dc1e38bdcdbee702b91d4cf24f3dfdcfd557e148e6819afb7dd5636a94dd` |
| `catalog/zh-CN/main_menu.tsv` | `65a879001f96bb2fd555310e164b3eb7f56698f3ce1a8ab7731fc70a3a626202` |
| `profiles/urw-3.89-steam-25939378.json` | `3835078d8ea4a92f8869d59282ec10558a6f46d0cfebe2cd3ad76a42d69c5241` |
