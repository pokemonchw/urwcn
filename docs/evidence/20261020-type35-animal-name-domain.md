# 旧 type35 任务标题的动物称呼来源

仅记录当前 `urw.exe` 的静态证据；没有执行游戏或原生业务函数。标题恢复实现由根代理维护。

## 选择、命名与所有权

- `555130` 在 `5551AB` 调用 `4AD4F0(index, flags=0)`，`5551B2` 转小写，`5553EC` 把该结果写入 `%s in the forest cover`。
- `542D30` 枚举村落候选时排除非人类中 `record+1 == 9` 或 `record+0x60 == -1` 的对象；`543340` 的命名动作只在玩家所有对象的列表中调用 `5431D0`。
- `5431D0` 接受非空、非 ESC 的玩家输入后覆盖 `record+0x30`，并对 `record+0x1dc` OR 3。
- 当前确认的正常所有权写者：`5350D0` 购买后设置 owner=-1；`566F40` 设 state=9 / owner=-1，释放只改 state，未清 owner；`40D800` 地图加载保留非人类的 state=9 / owner=-1。因此没有静态证据支持“命名后普通出售给村民”的反例。

完整 C：`settlement-quest-animal-selection-ghidra.c`、`settlement-npc-ownership-writers-ghidra.c`；字段引用：`settlement-npc-ownership-refs.tsv`。

## 自我介绍不能使普通动物获得已知专名

`539800` 输出自我介绍后仅对 known OR 1，不写 proper-name。它的三个直接 caller 是 `53ED80`、`539890`、`53A520`，均为完整 NPC 对话处理。

- 普通入口 `546200` 在 `546E48` 调用 `4AADD0`。该函数返回 `record.category != 1`；只有返回 0 才继续完整对话 `541F70`，非人类走独立动物命令路径。
- `546200(8)` 是脚本入口。`5413C0` 仅 topic `A613AB8=0` 构建 `[WHO ARE YOU]`；topic=8 的 3/4/5/6/1000 分支是债务、请求、犯罪或抢劫对话。
- 特殊 `4219BD` 确实设置 topic=0，但只有 AI 行为 `record+0x37c == 0x46` 且存在有效任务记录时才到达。
- AI 0x46 的唯一静态立即数 writer 是 `427FDC`，位于 `4275E0`。该函数唯一 caller 为 `56AF9E`。`56AF79` 读取 record 类别，`56AF82..85` 只有 category=1 才进入 `56AF9E`；category=50 走 `429210`，其他类别走 `42A4D0`。因此此特殊 topic0 回访路径仍是人类路径。

证据：`settlement-npc-conversation-type-gates-ghidra.c`、`settlement-npc-introduction-gates-ghidra.c`、`settlement-npc-quest-approach-ghidra.c`、`settlement-remaining-transform-callers-ghidra.c`；最后的 category dispatcher 见原汇编 `56AF40..56AFA6`。

## 初始化与描述清理

`4CECB0` 先调用 `4CE8E0` 清零整个 0x568 record；其中显式将 +0x30 和 +0x1dc 清零，然后选择 species 构造器。动物构造器不写这两个字段。写默认专名的 `4C95D0` 及调用它的构造器是 human；`4C40D0/4C4380/4C4620/4C4C40` 是 category50。`4CECB0` 最后的 `4CE500` 只调整体重等属性，不修改姓名或 known。

`4AD4B0` 是一条真实特殊分支：若 descriptor+8 含 `"' the "`，剥去此前缀并 OR known1。当前 PE 只发现该检测字串，没有发现动物构造器产生该形式的分支。该事实不等价于证明任意历史版本或手工编辑存档从未存在这种描述；不能伪称已读出旧标题生成时的历史快照。

证据：`settlement-npc-initializers-ghidra.c`、`settlement-item-initializers-ghidra.c`、`settlement-npc-name-lifetime-ghidra.c`、`settlement-npc-conversation-type-gates-ghidra.c`。

## 调试编辑器与普通路径区分

`57A8C0` 可把 owner 改成所在村落，`57A8F3/57A904` 可在 owner=-1 与0之间切换，但它们属于 `56FE30` 的隐藏调试命令：

1. `56FE50..6E` 连续读取并要求字符 `'-'`、`'j'`，不匹配立即返回。
2. `579E7F` 要求下一字符 `'0'`，进入生物编辑器。
3. `57A891` 提问 `yhteisoelain?`，`57A8C0` 才改村落 owner；`57A8CD` 提问 `kumppanuus toggle?`，随后 `57A8F3/57A904` 切换 owner。

这些调试消息仍属于共用消息翻译范围；但不能把调试编辑器修改当作普通出售或任务生成的正常语义。原始地址可在 `build/windows-text-disassembly.txt` 复核，函数入口引用见 `settlement-debug-entry-refs.tsv`。
