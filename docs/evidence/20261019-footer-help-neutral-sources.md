# 页脚与帮助段落的中性原生资源

本记录仅描述源码和静态指令证据，不代表编译、发布或运行验收。未启动游戏、注入、模拟输入、执行测试或创建断言。Windows PE 为已确认的 Steam 3.89 文件，SHA-256 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`；下列地址均为 RVA。[原始反汇编](20261019-footer-help-neutral-disassembly.txt)使用 PE 首选基址 `400000` 的 VA。

## 主菜单署名

原生 `1250E0..125232` 是完整页脚构建。`12510E→116270` 的输入提供面板位置、宽高和空标题，`125125→112980` 提供原开发者标识及其 y，`125137→162300` 和 `125173→10EB40` 提供出品段落及其原生颜色、outline。之后的版权和作者仍由原有函数构建；该完整区间没有输入等待、菜单动作或 Present。

`native_footer_component::Source` 引用此次普通构建产生的 Panel、Image 和 production Paragraph 的 canonical handles，并拥有 `translation_credit`、`translation_version` 两个中性资源。它不保存父组件的绘制结果，不再次绘制这三个依赖，也不替代它们原有 Scene children。依赖的引用使缓存版本继续持有原构建输入；后续普通构建通过共享对象版本创建新的资源，不覆盖冻结缓存。

`footer.inc::complete_native_footer` 在完整原生调用的 After 绑定这些已完成的对象，普通显示与 locale 均调用同一个 `paint`。新增文本列宽从本次资源度量取得，右边界来自原生 Panel，y 来自原生 Image，间距来自这两个真实输入的差。资产尺寸来自已授权原素材。布局关系沿用已授权署名表达式，不保存最终文字位置或行槽。完整原 `162300` 和 `10EB40` 继续完成 token、换行、行距和文字提交。

共享资源的英文值明确为空，英文模式不构造这两项新增标签及其署名图。临时 parser owner 作用域在原生完整调用结束时释放，并恢复此前原作者段落的中性 builder。保存格式只有 resource ID、真实依赖 handle、英文原文及语义值，没有编码后的中文、像素或绘制贡献。

旧记录 `20261019-footer-branding-native.md` 的 `capture_footer_edge` 与 `footer_branding` Before 入口描述是先前实现；其临时边界不能使新 Scene 在语言切换时重建新增署名。本次由 canonical footer resource 取代，旧记录的发布事实仍仅代表当时批次。

## 技能和法术帮助

`162530` 先解析文件名/节名。找到对应帮助节后，`162651..162676` 直接清理原 token 表和计数；`162627→162300` 接受实际帮助文件正文记录。每条资源使用被接受的正文输入记录序号，序号属于原文件构建过程，不是绘制顺序或屏幕行号。

`windows_skills_spells.inc` 在共享 loader 的入口记录明确帮助类别，在 `162627` 复制实际原英文记录，完整 loader 返回后将这些记录交给共享 canonical Paragraph builder。`skills_help_record` / `spells_help_record` 的语义值为 `help key#record ID`；中文第零记录投影为该帮助资源，后续记录具有明确的空投影契约；英文逐条消费实际原文。共享 prepare 仅省略这两个资源类别的空投影，不省略原生真实空/control 记录。没有保存中文整页或反解已翻译 token。

`11E2C` 与 `11E54` 接收原 `sprintf` 产生的英文限制说明。静态输入分别来自 `1D7F451`、`1D7F452`；新 `skills_limit_improve` / `skills_limit_degrade` 资源保存该实际英文说明与数字值，数字插入属于共享语义投影。

静态审查发现原先共享 parser 的 `parse(1, "")` 不能用作纯 reset：`162369..16239A` 会向表中追加两个 `<br>`，其 literal 为 `19416C`。共享修正改用完整 `1620C0` reset，再按实际 fragments 调用 append；真实空记录仍保留原生双 `<br>` 语义。

## 命名错误

`11A53`、`11B27`、`11CC7` 分别是三个已确认错误 literal 的最后一个 MOVQ 复制点，原英文资源位于 `190328`、`190344`、`190380`。后续 `118EE→162300` 解析 `[EBP-408]` 错误 local，再由 `118FA` 添加重复帮助。

这时 ESI 仅表达成功/失败，不能据其推断错误类别。`windows_profile_error_constructed` 因而在真实错误构建点保存纯 `{component, native_source_rva}`；`118EE` 绑定对应实际英文资源，避免把已中文化 local 当成英文原始输入。状态保存为八字节纯值。输入验证、原选项、姓名值和文件业务均继续由原生流程执行。

## 英文 renderer 待整改边界

审查时 `windows_renderer_text.inc` 的度量与 `10E170` 字形准入仍只检查 `contains_display`。原 renderer model 的 locale 完整调用虽然进入 `hud_renderer_text`，英文度量仍可能走原 ASCII 8 单位路径；部分普通 renderer constructor 则只 prepare，没有进入对应完整消费者作用域。已将精确接口建议交给 renderer 实现者：普通借入和 locale 使用同一显式组件 scope，度量/字形同时识别该 scope；仅中文 transport 的空格处理继续保留其独立契约。本记录不以源码编译成功替代该边界的整改。
