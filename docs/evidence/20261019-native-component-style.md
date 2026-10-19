# 原生组件样式输入与临时安装

本记录只采用固定 Windows 游戏文件的离线指令：`urw.exe`，SHA-256 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。下表地址均为 RVA；对应反汇编 VA 为 RVA 加首选基址 `0x400000`。没有启动游戏、注入、模拟输入、编译或测试。

`native_component_style.h/.cpp` 只持有普通原生组件构建时读取的样式纯值。Panel/LegacyPanel/Button 的中性 Source 保存这些纯值；语言重绘进入同一完整原生函数期间，Scope 保存调用者 globals，安装该 Source 的值，函数返回后恢复调用者 globals。不持有纹理、像素、文字坐标或绘制贡献记录。

| 类型与字段 | 原生来源 | 消费指令与语义 |
| --- | --- | --- |
| `ButtonStyle::suffix_color` | `[base+61BBAC4]` | `1149E8: push [61BBAC4]`，随后 `1149F9 → 10E5A0` 的 color 参数。 |
| `ButtonStyle::suffix_outline` | `[base+61BBA54]` | `1149D9: push [61BBA54]`，同一完整后缀文字调用的 outline 参数。 |
| `PanelStyle::background_mode` | `[base+61BBAC8]` | `1162F5` 与零比较，和原 flags 共同决定进入原生背景平铺；`1163CC` 与 2 比较，决定原生半透明填充。`115F00/115FED` 是 LegacyPanel 同类读点。只保存原值，不合成或猜测其他取值。 |
| `PanelStyle::title_fill_color` | `[base+A211070]` | `1158AA/1158F7: push [A211070]`；前一个栈槽为原生 alpha，后续 `1158BA/115902 → 10D900` 的 color 参数。 |

Panel `116270` 的标题尾部在 `116698 → 1157B0`；LegacyPanel `115E70` 的标题尾部在 `116253 → 1157B0`。因此捕获 `61BBAC8` 后仍必须捕获公共标题函数读取的 `A211070`，不能把只覆盖前半个函数的反汇编视为全部样式输入。公共标题 `115830 → 115E70` 的嵌套面板继续消费同一安装值。

普通调用已有明确的样式生命期：

```text
10841: mov [base+61BBAC8],1
1085A: call 116270
10867: mov [base+61BBAC8],0

D030F: mov [base+61BBAC4],eax ; eax 来自原生菜单 header 5F54A30
D031A: mov [base+61BBA54],eax ; eax 来自原生菜单 header 5F54A9C
D031F: call 114680
D0327: mov [base+61BBAC4],0
D0331: mov [base+61BBA54],0
```

所以 Source 的样式必须在普通构建入口采集，不能等语言切换后从已经归零的 globals 取值。普通构建消费保留原有调用；Locale paint 仅在原完整函数调用的局部 Scope 内安装 Source 样式。

此范围是软件原生组件 `114680/115E70/116270` 及其公共标题 `1157B0`。其他 renderer 家族的调色板 globals 不属于这些函数的输入，不在这里捕获。`A211068` 在该链中被原生函数写为输出临时值；主目标 `61BBB10` 和 atlas 资源是原生目标/资源所有权，也不作为样式副本。Paragraph、CenteredText、TextBlock 的完整原生 ABI 已显式提供 color/outline，保持原参数，不增加重复的 style。

接口为 `initialize(base)`、`capture_button()`、`capture_panel()`，以及 `ButtonScope(const ButtonStyle&)`、`PanelScope(const PanelStyle&)`。Scope 只安装上表对应的两个 globals，析构恢复进入 Scope 时的原值；样式结构不含回调或代码指针，进入组件持久状态时以对应四个 `u32` 原值序列化。

静态引用审查：typed model 的 source map 持有一个引用，Scene children 各 retain 一个引用；upsert 在存在保留者时创建新版本，旧缓存继续持有原版。Menu 的 snapshot 返回新 handle 的一个所有者引用，Scene cache_saved 直接接管；普通 active native view 的切换先 capture 当前 header/rows 再激活目标。Menu 文本借用在 resolve 成功后才 enter，匹配 CALL After 中 leave 与 release；失败不会进入 Scope。

菜单样式也归入了同一个中性实例：完整 `CFFB0` 在 `D01A5` 调 `115E70`，自身不安装 `61BBAC8/A211070`，两个值也不在原生 `190` header 与 `5AA0` rows 保存区。普通 `CFFB0` 的 `paint_begin` 在 capture 当前原生 header/rows 后，采集这两个 PanelStyle 输入。ButtonStyle 的来源则是原生 header `+10h/+7Ch`，因为 `D0287/D030F/D031A` 明确以这些值取代 ambient globals 后才消费按钮；不把入口时可能已经归零的按钮 globals 误当来源。

Menu locale paint 在整个完整 `CFFB0` 期间安装该实例的 PanelStyle 与 ButtonStyle，返回时恢复调用者的两个样式集合；一个仅属于同步调用的 `painting` 标记让其 `paint_begin` 使用持有的 Source，禁止从当前 ambient globals 重采并污染冻结的实例。普通 `CFFB0` 继续从最新 native header 派生按钮样式并消费同一 canonical 对象。Menu snapshot 和跨模块保存各复制四个样式 `u32`，不持久化调用标记、回调或代码指针。

完整原始切片另存于 `20261019-native-component-style-disassembly.txt`，包含四个完整函数与两个普通调用片段；该文本是只读离线反汇编证据。
