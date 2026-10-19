# 共用全局消息缓冲区 227 个 CALL 静态审阅

输入是 `settlement-message-call-ledger.tsv` 全部 1,402 个 `4F6510` CALL，取参数 SSA 中含 `65A9288` 或 `65A8CF8` 的全部 227 项，包含被 `embedded_literal` 或 `returned_561b00` 主类别掩盖的同一调用点另一分支。逐项结果保存于 `settlement-global-message-formatter-audit.tsv`。未运行游戏、测试或编译。

原始比对时，220 项的最近原生 `4010D0` 调用已经逐地址对应 `windows_message_formats.inc` 的 entry；包括 `42E4D3 / 42E51C / 42E54E / 43FAD7 / 46918F / 48B532` 六个普通 `65A8CF8` 消息。这是实际 callsite 匹配，不是仅按格式串出现计数。

其余七项均已分类并落实来源：

| 消息 CALL | 实际构造与处理 |
|---|---|
| 4064B6 | 一支为固定 `58D444`；另一支来自漏登的 `4064A9`，格式 `5A9F38:%s%s%s`，参数为 `58D49C` 固定前缀、已绑定的 `EBP-70` 陷阱名、`58D494` 尾句。已交 display 代理补入 formatter 清单、生成源与译文，并已看到源码 entry 落盘。 |
| 56C9BA | 一支为固定 `5D9F80`；另一支来自漏登的 `56C9A6`，格式 `5A9F38`，参数为 `5D9F70:#1st weapon: `、实际 `5915258` descriptor 的 `+9` 名称、空尾。已补 entry；物品名使用已证 descriptor 来源恢复接口。 |
| 56CA49 | 一支为固定 `5D9FA4`；另一支来自漏登的 `56CA35`，同一格式，前缀为 `5D9F94:#2nd weapon: `，物品和空尾同上。已补 entry。 |
| 4E9900 | `4E9320` 祷辞的实际完成文本，prayers 模块 EA00 已接入精确 `prayer.message` 来源；其英文控制字符与引号保留。 |
| 4E9A30 | 同一祷辞的另一原生完成分支，prayers EA01 已接入。两处分支的 3 条 intro 与 13 条 verses 已由 resources 代理完整提取并翻译。 |
| 4F6F90 | `4F6F70` 在函数入口将 ECX 文本复制至 `65A8CF8`，`windows_message_value_chains.inc` 的 `message_wrapper` 已沿真实复制传播来源。 |
| 567476 | 一支为 `56746F -> 561B00` 直接返回；另一支为 `56736F` 的 `5A9F38` 格式，`5D9688:Your ` + 实际 descriptor `5915261` + `5D9660: has burnt out and can't be lighted.`。该 formatter 原已完整注册，未重复新增。 |

原始 TSV 的 `format_registered=False` 记录的是首次比对状态；上述三处新增与四个专门路径的结论以本说明及其实际模块为准。没有将原生分支之外的未知文本当作专名，也没有增加按任意文本猜测来源的处理。

此外，审查 `526F70` 的上游复合正文时独立发现 `527B2B: ATTACK_RESULT: %s%d` 未构图，虽然它后面的 `527B61:? %s` 已在上述 220 项内。这一上游缺口已在 combat 模块 F491、实际 `527B30` 格式化完成点接入；详见 `20261020-combat-message-body.md`。本说明不把最近一次 formatter 的存在等同于其所有上游生产者自动完成。
