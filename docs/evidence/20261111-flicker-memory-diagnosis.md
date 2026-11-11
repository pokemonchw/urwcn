# 静止画面持续闪烁：运行中只读内存诊断

后续状态：用户已明确授权翻译失败显示原文；相关源码修复、编译及正式热发布已完成，见 [修复与交付记录](20261111-flicker-original-display-fix.md)。下文保留修复前的取证现场与当时约束，不表示当前交付状态。

2026-11-11（Asia/Shanghai）。用户明确要求追踪内存，并确认“不操作也持续闪烁”。目标为已运行的《不真实的世界》3.89.1，PID `7980`；EXE 基址 `00810000`，Adapter 基址 `50EC0000`，Catalog 基址 `52720000`。以下原生地址均为 RVA。

## 已定位的原因

当前活跃消息 Flow `22` 的第 `8` 条消息仍以 `lookup/message_literal` 保存整个已展开的动态英文句子：

> You try to swing Herppa with your kaumolais spear.

消息的语义记录没有保留动作、对象和武器的模板分解。重建因此查找整句的 `message.literal.<UTF-8十六进制>` 键；正式词库及进程内已经加载的 Catalog 均不存在该键，返回 `Status::unavailable=2`。这是实际读取到的失败项，不是根据“可能漏译”推测。

HUD 重建先执行多个原生组件，再重建消息。消息失败时，HUD/messages 的 pending 位不会清除；主等待的 `-2` 结果也未被消费。游戏本来就有每 `333ms` 发出 `0x8000` 事件的计时器，这个事件返回 `-2`，于是持续重入同一次未完成的 HUD 重建。

重建中的原生日历面板会在消息重建之前调用 `10B720` 呈现。随后失败返回又进入原生地图重建链，构成重复的中间呈现与后续呈现。当前确定的故障是**消息语义记录导致重建永远失败，而重建已经改变并呈现部分 UI**。没有采集像素，因此不把某个闪烁区域的颜色、范围或每次 Present 的实际视觉内容写成已测得结论。

静态资源和绘制参数进一步解释了消息区为何受影响：`FA2FB` 将 `bg-rpanel.png` 绘入原生 `(472,0)`；资源为 `360×600`，原消息面板两种矩形 `(493,398,305,130)` / `(498,355,296,170)` 均落在该背景范围内。资源的单色透明键为 `(128,255,255)`，不能把整幅资源说成全不透明；消息区对应其内部背景。即使已有 Hook 跳过 `FA308` 的消息面板构建，前面的右栏背景构建仍然存在。日历提前呈现这个阶段，之后消息重建只完成前 7 条，原 `99EF2 → 10B720` 又呈现后续状态。这里是静态绘制链推导，不是对运行画面进行像素采样或逐帧录制。

## 内存证据

可复核的精简记录见 [内存摘要](20261111-flicker-memory-summary.json)。完整原始采样留在 `build/analysis/20261111-flicker-*.json`；未提交全进程转储或画面数据。

| 读取项 | 实际结果 | 结论 |
| --- | --- | --- |
| 第一轮采样 | 20:02:48 起，160 份 | 主面、背景面、上传/地图纹理指针及尺寸均稳定，非反复销毁/创建 |
| 第二轮采样 | 2400 份，8.404 秒 | 25 个不同计时事件，间隔 333ms×19、334ms×5；25 次 HUD constructing 从 0 变 1 |
| `native_language_redraw::state` | pending 恒 `1FFFBFBB`，rebuilding 为 0 | HUD bit25、messages bit27 始终保留 |
| `native_ui_scene::language_revision` | 恒 5 | 不是每次有新语言失效请求 |
| `windows_messages::generated_status` | 2368 份为 2，32 份为 0 | 每轮消息处理前归零，遇到缺键后又返回 unavailable |
| 文本编辑 construction_status | 2400 份均为 0 | 此次失败不在输入回显构建 |
| 实际消息源 | painting handle 22；当前源含 13 条记录 | 读取完整 records vector，而非只根据瞬时指针猜测失败记录 |
| 所有消息的 lookup 叶 | 对已加载 Catalog 精确查询 29 次，28 个存在、1 个缺失 | 唯一缺项是第 8 条整句 literal；与按顺序重建首次失败一致 |
| 原生 `61BBA5C` | 0 | 重建没有整体抑制中间呈现 |
| 原生 `61BBA50` | 周期内从 0 到 1 再回 0 | 与日历面板临时地图模式一致；不单凭此字段归因 |

Adapter 状态偏移来自正式 DLL 的符号表：pending `+39491C`、generated_status `+3943AC`、HUD constructing `+3943A9`、painting handle `+394A80`、painting_source `+394A70`。正式 DLL 首选基址为 `6A8C0000`，按实际模块基址重定位读取。

当前 Flow 的容器布局由正式 DLL 的机器码确认：instances 根字段 `+394A38`；树节点 handle `+10`，records begin/end `+94/+98`；Record 步长 `B0`，Text 在 `+38`。Text 步长 `60`，kind/component 在 `+0/+4`，original/key 为 `+8/+20` 的 24 字节字符串，children vector 在 `+48`。未扫描像素、猜测业务字段或调用目标进程的函数。

## 精确调用链

1. 原生 `17D053/17D058/17D05D` 登记 `17CC20` 回调及 `0x14D`（333ms）间隔。回调在允许且无排队事件时经 `17CC55/17CC5E` 投递 `0x8000`；`D2083` 将其变为 `-2`。该计时器属于游戏原功能。
2. `native_hud_language.inc:321-328` 在主等待结果为 `-2` 且 HUD pending 时调用 `rebuild()`。
3. `rebuild():167-197` 依次调用原 `FA2A0/F90D0/102D10/FF040/103640/8FF70/FAA30`，最后调用 `messages()`。
4. 原日历 `103640` 的 `103869` 检查禁止翻转值；本次为 0，故 `103878` 临时写地图开关 1、`103882` 临时写地图模式 1，`10388C → 10B720`。后者 `10B72A → 10AF90` 上传/清 renderer/复制底图，合成地图和组件后在 `10B763` Present；其后才恢复临时地图标志。此时后续 HUD 组件和消息尚未重建。`FA2A0` 自身的 `FA749` 提交已有 `hud_finished` 跳过，不能误称它是此次中间 Present 的来源。
5. `native_message_flow.cpp:253-302` 按记录顺序绘制。第 8 条在 `windows_messages.inc:385-394` 投影旧 Text，经 `native_message_source.cpp:85` → `modules/semantic/message_text.cpp` 构造整句键，`modules/catalog/catalog.cpp:48` 缺键返回 2。
6. `windows_messages.inc:393` 将结果记为 generated_status，结束该原生消息调用；`consume_flow():131-136` 返回 2，`native_message_flow.cpp:270` 停止后续消息构建。
7. `native_hud_language.inc:195-197` 不清 HUD pending；`:328` 提前返回，未到最后一次完整呈现和 `:337` 的 EAX=0。原主循环仍按 `17D0BD/17D0C2` 进入 `99BE0` 地图重建。下一次 333ms 事件重复全部步骤。

原生完整反汇编及针对性提取留在 `build/analysis/flicker-20261111/`，其中 `native-timer-producer.asm`、`native-main-wait.asm`、`native-hud-date-present.asm`、`native-frame-present.asm` 分别对应以上边界。采样中的 SDL command generation 变化只表示命令刷新次数，不能当作显示帧数。

## 热交接为何没有消除旧消息问题

当前正式 Adapter SHA-256 为 `b712d15ec0df459d61f7557fdcd0eb39012e57230c380de7f85bfe09239548df`，与 [19:53 战斗宣告交付](20261111-combat-narrative-native.md) 一致。

新的 `windows_message_combat_body.inc:72-82` 仅在后续原生声明复制实际执行时调用 `message_bind_copy`。它不重新绑定已经留存在 Flow 里的记录。`native_message_flow.cpp:353-355` 热恢复直接读回旧 `Record.text`；`windows_messages.inc:372-387` 重建再次消费这个 Text，不重新运行原战斗业务生产函数。

交接后 `src/loader/host.cpp:203-211` 发出依赖变化通知，Adapter `module.cpp:1976-1981 → invalidate():634-640 → native_language_redraw.cpp:24-32` 请求各界面重建。因而已存在的错误 literal 图会在新版本下重新暴露，而新增生产 Hook 本身不会修复它。

记录没有生成时间戳，因此不能仅凭此快照断言该句首次生成的具体时刻，或用户首次看到闪烁的时刻。已证实的是当前保留的 Text 身份、实际缺键、失败返回和每轮重建；交接对旧 Text 的保留与失效请求由源码确认。

## 待整改记录

- `modules/adapter/native_hud_language.inc:167-197,321-337`：重建已经修改原生目标并允许中间提交，随后可因消息失败长期保留 pending；影响为本次持续闪烁及反复地图业务重建。待整改，尚未改源码。
- `modules/adapter/native_message_flow.cpp:353-355` 与 `windows_message_combat_body.inc:72-82`：生产语义修正不迁移现存错误 Text；影响为已留存的战斗句继续按整句 literal 查询。诊断时未获原文显示授权，不能擅自添加特定组合词条、跳过旧消息或退回英文。后续用户已明确授权失败时展示原文，显示边界修复见本页顶部链接；原历史 Text 并未被猜测性改造。
- `docs/evidence/20261111-combat-narrative-native.md:16`：既有交付限制只列文件日志历史，未列活跃 HUD 消息图的迁移边界；该遗漏在本记录补明。编译成功和 Applied 不代表旧内存记录已经转换。
- `modules/adapter/native_renderer_component_binding.cpp:558-585,644-688`：仍保留创建替换目标并遍历 retained children/icons 重绘的旧机制，不符合当前原生 UI 所有权要求。当前源码未发现 `paint()` 调用者，`native_ui_scene.cpp:411-413` 不重画 retained components；状态为退役残留、待清理，不把它定为本次已证实执行的原因。

## 操作与交付状态

本次仅使用 `OpenProcess(0x410)`、`ReadProcessMemory` 读取标量、资源头、原有消息语义记录及特定词库键，结合磁盘 DLL 符号与原游戏机器码分析。未暂停线程、设置断点、写目标内存、注入、模拟输入、读取表面/纹理像素、启动/关闭/重启游戏或运行测试；未创建测试或断言。

仅新增本诊断文档与精简证据 JSON。产品源码未修改，未编译，未正式发布；游戏中的闪烁尚未修复。原工作区及其他聊天的修改保持原样。
