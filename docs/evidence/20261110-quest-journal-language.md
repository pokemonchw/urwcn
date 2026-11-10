# 任务日志完整原生构造与语言切换

来源：原始 Windows 3.89.1 PE `urw.exe`、`build/analysis/windows-3891-native-full.asm`。地址均为 RVA；未运行游戏、产物、测试或模拟输入，未编译。源码为 `modules/adapter/native_quest_menu_language.inc`，仅新增此独立实现和本文。

## 原生所有者与真实语义

该原生纹理是任务日志，并非角色创建或头像选择：原资源 `1CC6F8` 是 `QUEST JOURNAL`，`1CC7B0` 是返回任务列表，`1CC7C8` 是地图位置按钮。原 `157D10` 消费完整 `F1E0h` 英文任务记录、原 EDX 显示起点和 flags；`157AF0` 在同一所有者中构造任务 NPC、地点与相关正文。原 `158CE0` 构造任务列表和分页。游戏原生 texture owner 是 RVA `A220EF4`（PE VA `A620EF4`）。

| 活跃等待返回 RVA | 完整原 owner | 接入的原生构造 |
| --- | --- | --- |
| `1586D5` | `157D10` 任务详情 | 借真实存活 EBP，从 `157D75` 完整重建到 `1586D0→D1120`，原 D1120 正常负返回后由 `1586D5` 同步返回 |
| `1590A8` | `158CE0` 非空任务列表 | 借真实存活 EBP，从 `158D3F` 完整重建到 `1590A3→D1120`，原 D1120 正常负返回后由 `1590A8` 同步返回 |
| `159335` | `158CE0` 空任务列表 | 同一 `158D3F` 完整构造走原零 count 分支 `159250`，原无任务正文、说明、纹理提交全部执行，仅跳过 `159330→D3C80` 新等待，在 `159335` 同步返回 |

两个 Menu 等待的事件 EBP 是真实 D1120 帧，其 `[EBP]` 是各原 parent EBP。空列表事件 EBP 是真实 D3C80 帧，其 `[EBP]` 是原 `158CE0` EBP。没有从退休帧或未知祖先猜输入，没有新增持久帧或页面快照。

## 详情：任务数据和整张纹理

静态直接 `CALL 157D10` census 只有 `158FAF` 与 `1591A5`：

- `158FAF` 压入 flags 6，供列表的五条任务摘要构造；该 flags 的 bit 1 使 `15816D→158780` 在 D1120 前按原函数 epilogue 返回。
- `1591A5` 压入 flags 8，供独立详情。只有该调用进入 `1586D0→D1120`。它的 EDX 是原 30 起点，真实值已由原 `157D3B` 写入 `[EBP-1EFD4]`，原 flags 的 bit 3 已在 `[EBP-1EFE0]`。重建读取这两个真正的存活字段，而不复制显示坐标或推定 mode。

原 `157D2A..157D42` 已将按值传入的 `F1E0h` 任务记录完整复制到该原 frame 的 `[EBP-FDEC]`。重建从它的原构造循环 `157D75` 开始，不重新接受、生成或提交任务。桥设置 EBP 为该存活帧，EDI 为真实起点，ECX 为真实 recreate bit，EBX 为原 `157D50` 装入的 SDL_SetRenderTarget IAT `18C288`。

`157D80..157DDD` 按原 flags 销毁旧 texture、创建新 texture、调用原背景 `113090`、原日志标题 `113550` 和原图像生命周期 `10B250`；`157DE2..1580DE` 生成原标题、日期/期限/完成状态与任务对象显示；`158179..158562` 的原 parser 和循环产生完整任务正文；`158577..1586CD` 产生真实 Menu、命中区和两个按钮，并把新 texture 写入原 `5F4EB08 / A1C1CBC` 输出上下文。重建没有只重画文字或保留旧 texture 指针。原布局、大小、换行、图片加载、所有 hit region 仍由这些原生构造负责。

重建的 D1120 只执行原 prologue，并复用 Full 已安装的 `input_entry` 从 `D1159` 走原 `D19B3` epilogue，不进入新输入循环。`1586D5` 五字节原 MOV/CMP 边界改为同步 RET，原 Map locations、Back、texture 退役和业务返回分支不在本次重建执行。普通调用照常重放该 MOV/CMP。

## 列表：保留已接受索引、分页和选择

`158CE0` 仅有原主游戏 caller `17DED9`。首次 `158D2C` 的原 SDL copy 保存 FIRST 父缓存，随后 `158D3A` 隐藏原父窗口；新构造入口在它们之后，既不重复 FIRST 保存，也不改变父窗口生命周期。

`158D3F..158D99` 是完整原 texture 退役、创建、背景与日志标题构造。`158DA3→1587A0` 的原 getter 会重新枚举 `.QST`、筛选任务、改写/排序原 ID 和日期表 `A220690 / A220A90`；这属于本次已接受输入集合的初始化，因此重建跳过这次调用，直接使用仍活 parent `[EBP-42C]` 中的真正 count。随后原 `158DAE` 写回同一个 count；没有将未知输入猜成零。

真实 page offset 留在 `[EBP-41C]`，原 `158F01` 从它定位已接受任务索引，原循环读取对应英文 `.QST` 任务数据，并按 flags 6 调完整 `157D10` 摘要构造。没有重新排序或生成任务。后续原 `158FDB..159098` 重建 Back、Previous、Next 和原输出 texture 上下文；新纹理和控件全部由原生方法建立。原 count、page offset 与任务记录均保持原语义，菜单回调的 selection 参数保持不变，共同 D1120 重入协议把它写回真实选择字段和该 D1120 的保存字段，再执行原 save/present。

空列表复用真实 count 0，只执行原 `159250..159330` 的两段正文和原纹理呈现。重建不执行 `159335` 之后原关闭、FIRST 恢复或 texture 销毁。原空列表自己的 SDL RenderPresent 仍属于完整构造，原 D3C80 等待与退出动作保持存活，等待用户继续。

## 嵌套显示与业务边界

`CB20` 是现有 NPC 读取器：根据真实 NPC ID 只读当前对象或 `.CRS` 文件，并复制 `568h` 原记录到调用者目标；未调用任务生成、移动对象或 PRNG。`157AF0` 使用原 `116C10` 管理任务 NPC 图像资源、使用 `AE3F0` 格式化 NPC 描述、使用 `8E4F0 / 9B040` 从真实接受的地点产生显示上下文。它们的原显示输出继续进入该 texture 的 native text/component 调用。

`AE3F0` 在 `AE42B..AE469` 会把英文 NPC 记录复制到 499 号原格式化工作记录后清空。重建同步借用并恢复这个静态确认的整个 `568h` 英文工作记录 RVA `5DF9DB8`。这是原语义数据 scratch，未保存 UI 内容、布局或文字贡献。原描述格式化环缓冲按其自身原机制运行。原 `16C10` 的写入限于游戏图像窗口池及其 SDL texture，仍由原图像所有者加载、复用和退役。

不执行 `1591C5→E5990` 任务业务、`1587A0` 的接受列表初始化、详情结果分支、原新等待、退出或任务提交。两处普通构造循环内的资源和英文任务数据读取属于原 UI 构造，不另建替代 UI。

## 父缓存关闭与接线

当前显示是独立全屏 Root，不存在需要单独重建的可见 HUD 或列表边缘。原 `157D92..157DA9 / 158D58..158D6F` 创建 `800×600` texture，`113090` 在 `1131B0` 选择这张原目标，随后 `1131C4..1131D4` 用目标矩形 `{0,0,800,600}` 完整复制原背景。背景资源 `A2110C8` 在 `10C8A3..10C8AD` 原 `IMG_Load` 来自实际 `truegfx/bg-profile.jpg`。这里列原矩形只说明原 native owner 的覆盖范围，Mod 不保存或消费这组坐标。

共同 renderer-menu 的 `D125A→10B480` 显示路径还在 `10B4AE` 选择 renderer target 0，`10B4BB..10B4DB` 先按原 `{0,0,0,255}` SetRenderDrawColor 和 RenderClear 清掉整个 renderer，再于 `10B4EA..10B4FA` 用 `sourceRect=null / destinationRect=null` 完整复制 `A1C1CBC` 指向的新任务日志 texture。这明确排除了透过未知透明度看到旧 HUD 的假设；之后的 `10B3C0` 仅沿原图像窗口生命周期显示当前窗口。原 `158D3A→10B0F0` 的实际资源是通配符 `*`，已隐藏父窗口。详情虽从列表进入，flags 8 构造自己替换该全屏根，因此不在详情前重建被完全遮挡的列表或 HUD。空列表的 `1592E8→10B480 / 159313→SDL_RenderPresent` 使用同一全屏显示协议。

原 `158D32` 已保存 FIRST；非空列表 `15923A→10DAD0`、空列表 `15935D→10DAD0` 分别返回 `15923F / 159362`。现 `native_first_cache_language` 的完整调用者 census 已包含这两个真实父，按 FIRST 自身 language revision 在原恢复后、原 fade/present 前完整重建 HUD 并用原 `10DA10` 重存 FIRST。该机制独立于 `View::hud` pending，因此子任务日志完成语言构造不会让旧语言父缓存被忽略。任务详情关闭先回其真实列表原构造循环；最终列表关闭再经过该既有 FIRST 生命周期。

include 需在 `native_full_language.inc` 后。接口为 `append_hooks(hooks)`、`dispatch(event,result,handled)`、`menu(event,rebuilt,selected)` 与共享 Before wait 聚合中的 `wait(event)`。Menu 回调接在已有明确 owner 回调之后，只有表中两个真实 caller 和 `pending(View::hud)` 才进入构造。完成清除该 View；空列表同样按其真实返回地址承接。新增 IDs `51F0..51F4`；无新增持久状态、状态分节、默认父页或缺源回退。
