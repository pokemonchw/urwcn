# 原生百科 LinkTextFlow 的 Source 与 Menu 所有权

本记录为固定 Windows `urw.exe` 的离线反汇编与源码静态审查；SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。地址均为 RVA，反汇编 VA 加 `400000`。没有运行游戏、注入、模拟输入、编译、测试或新增断言。

`3D820` 是完整的原生单条正文 Flow 方法：ECX 是一条原始 `GAME.NFO` record，EDX 是该 topic 的原英文别名/排除串。`3E048/3E04E/3E054` 明确从 `3DD10` 的 `[EBP-5F8]` 和 `[EBP-138]` 传这两个输入；EDX 不是颜色。它自己调用 `162300` 构建词元，完成原生换行与光标推进，并调用 `3D300` 查原英文主题、建链接与原生 Menu 行。

| 原生数据 | 指令依据 | 在扩展模型中的职责 |
| --- | --- | --- |
| `1E23DC/1E209C` | `3D89D/3D8A9` 读起点；`3DA39/3DA48`、`3DB4B/3DB5A` 推进下一行；`3DC48/3DC5A` 写记录结束位置 | 只在整组构建起点捕获一份 context；各 record 后的位置由同一原生方法产生，不保存旧语言的逐 record 坐标。 |
| `2EA818` | `3DA2C/3DB3E` 由原生增加行距；`3D70B/3D777` 消费链接下划线/标签所在行 | 同一组初始 context；继续由原生 Flow 推进。 |
| `2D093C` | `3D8FF` 比较原值，控制短 record 的原生换行标记 | 保存原始输入值，不猜测额外取值。 |
| `A1C1CB4/61BBB3C` | `3D8BB/3D8C1` 从原生起点安装；`3DBA1/3DC13` 原生字绘后继续消费 | 原生当前光标输出，离屏缓存物化返回时恢复调用者的值；不作为持久 source 的逐字/逐行贡献。 |
| `29ADD8 + 1000*200` | `3D36F` 起点，`3D7D0/3D7F2` 每条增加 200、循环至 `30D40`；原 `3CFE0` 从 NFO 构建这张主题表 | 继续由游戏持有原英文检索表，不改写成中文。 |
| `2CBB18 + 100*200` 与 `2D0938` | `3DF39` 计数置 2；`3DF50..3DF5D` 清当前链接名；`3D5B4/3D5D0` 与 `3D7A0..3D7BE` 写原主题身份 | Flow 持有当前英文 Link ID 的原生 schema；缓存 snapshot 独立复制，不保存已编码中文。 |
| `5F54A20+190`、`5F4EF10+5AA0` | 原生 Menu header 和 E8 行；`3D692` append 行数，`3D69A/3D6A8/3D6B5/3D6C0` 写真实命中范围，`3D6CA` 写 action=0 | 同一个 owned `MenuHandle` 承接原生 Flow 的布局结果。语言重建不复制旧链接矩形。 |

普通构建的整组起点在 `3DF74` 原 `mov [61BBB3C],60` 完成后、`3DF7E` 原文件 EOF 查询前。此时 `CF790` 已创建菜单，原生当前链接计数/表已初始化，组初始 context 已确定，尚无正文链接行。`native_link_flow_component::begin` 只捕获这一组的真实输入及 counted source prefix；未计入 count 的旧数组内容不会成为 source。

原生词元不是持久 Source：`3D935/3D93A` 每次以 ECX=1 调 `162300` 从完整 record 输入重新构建，`3D977/3D983` 随后读取游戏的 `82h` stride 原生词元。组件直接复用该完整构建与消费，不保存旧词元位置或事后拼成文字贡献序列。

原 `3DF9C/3DFBE/3E021 → D4280` 的正常读取沿既有桥得到原文件偏移作为 record ID。`append` 复制中性的 `TextSource` 和原 EDX 排除串，`consume` 从同一个 source 借入当前语言的临时字符串，再调用完整 `3D820`。中英文的原生度量/字形作用域由同步服务明确进入退出；临时 fragment 只为满足原生 200 字节输入缓冲的已知 ABI，不含坐标或重放命令，也不持久化。

实际实现还保存同一 record 的原生 English bytes：`29ADD8` 的原主题名含原 `C4` 等单字节，原 `3D300` 继续按这些原值检索。UTF-8 `TextSource::original` 用于资源语义；English 的 `3D820` 输入使用同一 canonical record 的原字节，最终已确认的 word/link 文本边界再通过 native display/measure 编码和高清字形扩展消费。把原始 English 先编码为显示 transport 再交原检索器会改变查找身份，不能这样接。

原短 record 的控制语法与译文空值分开：`3D8E7..3D92C` 对不足三字节的原 record 追加原生换行标记，保存为 original policy 并照常运行一次原方法；`culture.record.38/127` 等明确为空的中文 continuation 资源表示前段译文已经合并，准备结果没有 fragment，不调用原方法而不增加额外空行。这是已存在的数据语义，不是缺少译文时的 fallback。

普通导航在 topic 读取之后的 `3E110` 中通过 `3E148/3E1A3/3E1BF/3E1D6 → CFAF0` 构建。`CFAF0` 的完整输入为 ECX=action、EDX=x、stack=y/fullLabel；`CFB95 → 114680` 先消费完整文字，之后 `CFBD4` 写原动作，原生自己截出 ASCII 键帽写行。其行的完整显示语义由 typed button Source 持有。`seal` 应在 `3E1DE → D1120` 的 Before 调用，此时这些构建已完成；`3DD10` 返回时尚未构建导航，不能提前 seal。

Locale `paint` 激活明确的 owned Menu，保留它最新的 header 输入，恢复整组 context 与初始 counted prefix，逐条调用同一个完整 `3D820`。由 `3D300` 生成全新的链接矩形后，仅接续原模型中的独立非零 action 行；没有把任何旧 action=0 链接矩形接回。真实 typed button 消费随后按原 action 在这个 owned Menu 中定位当前行，继续原完整控件方法重算它的文字和命中字段，不能使用此前的 row ordinal。选中项通过原英文 Link ID 或原 action 在新原生模型中重定位，保持实际业务动作。

每个独立 action 在 `seal` 时还复制该真实原 row 的中性 Menu label、原 prefix 和 annotation 资源；这些 owned source 随 snapshot 与 plain state 一起保存。重建产生新的 link row 数量后，接续 action 原生行的同一点将这些资源 `bind_row/bind_annotation` 到真实 InputOwner 的新 index，度量与注释不再引用旧 ordinal。资源来自实际普通构造绑定，不能用重建后显示字节补造 English。`CFAF0` 本身直接在 `CFBD4/CFCE5` 写 action/count，不经 `CF990`；它的原 `NOTEXTSPOT/TEXTSPOT` marker 保持在 native English record 中，原分支继续消费 marker。普通完整 ActionButton After 及 locale 的相同方法以 canonical typed `TextSource` 绑定独立的 Menu 度量资源，以该 actual row+64 的原文字段绑定 annotation；没有把完整显示字符串回写为 native marker。

`snapshot` 冻结中性 source、seed 与原生资源 schema，Menu source 也有独立快照；返回 handle 有一个待 cache 接管的引用。Flow 和 Menu 快照均 retain 同一真实逻辑 InputOwner，当前 links/selection 不从冻结缓存恢复。Scene 中同属该 flow 的 typed button 明确重绑定到这个 Menu source 快照，实际 paint/activate 再归真实输入 owner。详见 [Menu 输入所有权](20261019-native-menu-input-owner.md)。保存/恢复只包含 plain metadata、原 source 字符串和原生 schema，回调、临时编码、模块代码地址均不进入状态。

Scene 的普通 Menu child 必须由同层的 Flow owner 替换，后续该 owner 的 `CFFB0` 消费不能另挂一份旧完整 Menu 覆盖新链接结果。实现没有调用 `3DD10`、`3E680`、浏览历史、业务输入等待或页面 redraw callback。它扩展正常源构建与同一原生组件消费，不是文字贡献记录。

`windows_encyclopedia.inc` 已实际接入 `57F1` 的 `3DF74` 源构建 Hook、普通 `we_body` 的 append/consume 与 `we_select_wait` 的 seal；旧 `3E680` 页面重入和相应历史/返回跳转 Hook 已移除。`native_consuming` 表示两语言都在同一完整原生 Flow 中，`line` 只表示中文语义正文：English 保留原词与空格，CJK 的 alias 转换和分词空格规则只作用于中文。原 `3D820` 内的 `162300` 被明确的 parser owner 作用域包围，不再另建一个低层 Paragraph/word Source。

常规标题、帮助和导航两语言都在原构建点绑定真实 English 原文与 culture resource key。BACK 的中性资源为 `culture_back`：original 是原 English suffix，value 是原 English topic，原 ASCII action 与点作为 prefix；投影时才把同一 English topic 解析到当前语言标题，不保存已经译成中文的动态 value。普通输入/帮助/主题状态与 token 所有的 Upper 临时调用状态通过 `save_windows_encyclopedia_state/restore_windows_encyclopedia_state` 以 plain bytes 转交，不保存整页中文或 Mod 布局。

原始完整切片在 `20261019-native-link-flow-disassembly.txt`，包含 `3D300/3D820/3DD10/CFAF0/3E110`；本记录列出的输入、输出、原生 schema 是当前已确认边界。对未知 owner 或字段没有新增 fallback 分支。
