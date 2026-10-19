# 普通消息前半段复制与分支复核

范围：`settlement-message-call-ledger.tsv` 中 `buffer_or_expression` 且 CALL VA 小于 4D0000。该查询有 251 条：123 条实际使用 65A9288 调试格式缓冲、6 条使用 65A8CF8 包装缓冲，均交由独立全局源审查；本次检查其余 122 条、71 个 caller。证据来自完整 caller C、完整原始反汇编、现有格式入口表及新 appended/transfers 模块，不是运行结果。

`settlement-ordinary-pre4d-buffer-audit.tsv` 只记录原始指令窗口中的前一个调用及其 sprintf 注册关系，不能把这张表当作全分支完成证明。另检查从最后 sprintf 到 F6510 之间的直接外来跳转，避免以“最近一个写入”掩盖另一复制分支。

## 已补的真实缺口

1. **44CB1F 的两个资源复制分支。** 44CAB7 和 44CB46 分别调用 561B00，随后先把 EAX 放入 ECX，再在 44CABE / 44CB4D 准备 EBP-408 目的地址，以原生循环复制完整资源结果。这两条路径与 44CAD5..44CB0B 的 598608 枯萎固定句在 44CB0C 合流。固定句已在 `direct_copied.zh-CN.tsv`，资源副本此前没有 owner 绑定。
   `windows_message_audit_copies.inc` 的 F800/F801 分别观察两条六字节 `LEA EDX,[EBP-408]`，从真实 ECX 资源返回传播源图。无中间调用、无新状态、无缓冲修改。
2. **469231 的固定句旁路。** 4691C1..469202 把 59A9BC `:To do this by hand press [esc] to skip the item selection.` 复制到 ESP+EF8，46920B 直接跳 46922A，绕过另一路已经接入的 469222 sprintf。此前词库没有该句，现已加入 `direct_appended.zh-CN.tsv`，使用既有固定完整字面文本读取，无额外挂钩。

旧 ledger 将 598608 的复制分类标在 44CBAA，这是错误的调用归属：44CBAA 实际只消费已经注册的 44CB93 动态 sprintf。真正包含两个资源副本和固定句三路合流的是 44CB1F。最终 ledger 已纠正这两行归属，原始地址证据以上述完整反汇编为准。

## 已有路径及排除理由

- 402C7B / 402D51 的 EBP-478 内容来自已注册 402BE3 资源格式。其间的 4C0AC0 创建物品记录，不改该消息缓冲。
- 40332C 的植物多片段追加、41BF33 的资源复制已在 transfers；42E02F 的地形尾句和 43562E 的食欲尾句已在 appended。
- 43C802 的实际草药效果记录名由 resources 的 `herbal_effect_name` 界面调用识别。
- 44E759 的 A611B78 来自 52AFC0；原生句点追加在 transfers，52AFC0 合成链由 trace 独立处理。
- 456C1C / 456D11 / 456E01 / 456F11 使用同一原生已格式化栈文本。456BC7 / 456BD0 跳到 456BEE 时保留其他已经注册的 456B8E / 456BBA 输出；原生选择资源替代结果的分支直接传该资源返回。之后 6F2C30 的复制及移除起始标记已经在 transfers，458D57 消费此 owner。
- 441535 跳入 4415AA 时保留另一路已注册的 44152D 格式结果，不是未绑定的资源副本。
- 4695EE 跳到 469661 时，缓冲刚由 469583 memset 清零；随后原生非空检查跳过 F6510。实际非空路径均经已注册 469659。
- 45AF85 的稍早字符串由 45AE50 构造；中间随机数和物品状态调用没有复制或追加该消息缓冲。

## 独立全局源审查转交的三个格式入口

trace 提供并经原始 PUSH 确认：4064A9、56C9A6、56CA35 都使用 5A9F38 `%s%s%s`，此前同一 F6510 调用的字面分支使这些真实格式入口遗漏。现已同时更新 `settlement-formats-implemented-sites.tsv` 和其生成器输出 `windows_message_formats.inc` / `settlement-formats-entry-data.inc`：

- 4064A9：58D49C 固定前段、EBP-70 陷阱名 bound、58D494 固定尾段。该陷阱名的生产及 4063C6 副本已经接入。
- 56C9A6：5D9F70 第一把武器前缀、5915261 真实 descriptor+9、58C616 空尾。
- 56CA35：5D9F94 第二把武器前缀、5915261 真实 descriptor+9、58C616 空尾。

四个前后缀译文保存于 `formats.audit.zh-CN.tsv`。武器参数使用已确认 descriptor 地址的 `Kind::descriptor`，空尾使用既有空字符串语义，没有将未知字符串当成专名。

## 静态边界和集成

F800/F801 只覆盖完整 LEA，不包含 ESP 调整或相对控制转移；完整反汇编未见外来跳转进入六字节覆盖内部。循环入口 44CAC6 / 44CB55 位于覆盖后，回边保留。处理器不修改寄存器、EFLAGS、原生英文文本或业务数据。

新模块只需 include、append_hooks、dispatch，无 save/restore 或状态 schema 更改。本分段审阅未编译、测试或启动游戏；根代理随后统一生成词库、编译与正式发布，回执见 `20261020-shared-message-delivery.md`。
