# 对话参数残留、告别／返回漏译的修正

日期：2026-11-11，Asia/Shanghai。Windows 3.89.1 / Steam Build 26139145。用户截图 `codex-clipboard-b6553a0a-e632-49d6-8e0a-49a15a67f38b.png` 显示自我介绍中出现 `{0}`、`{1}`，告别和返回仍为英文，英文标签字形异常。上一批 `841e5394478c4e9baf03bd6d72ecdf1f` 已发布，但其 Applied 仅证明模块交接，并没有证明这些显示路径正确。此前按调用点数量报告“补齐”的交付结论不充分，本记录更正。

本批只阅读用户截图、原 PE 反编译／反汇编、资源与源码，修改后通过根统一队列生成并发布产物。没有自行启动、关闭、重启、操作或测试游戏，没有输入模拟、测试用例、测试脚本或断言。

## 已确认的原因

### 同一英文结构使用了不同的中文参数顺序，却共用一个译文键

原 `15DFC0` 用 `%s %s` 构造玩家姓名与文化名。此前将它归一化为 `{0} {1}`，中文目标为 `{1}{0}`；它与 NPC＋动作、物品组合、数量＋单位的同样英文结构，全都写到了同一个 `conversation.form + source` 词库键中。生成器后写入的 `{0}{1}` 覆盖了玩家身份应使用的 `{1}{0}`。

与此同时，玩家身份表达式的 `syntax` 仍按原来的中文目标保存为 `{1}`、`{0}`。`native_message_source::project` 依次从游标寻找标记，实际词库的标记顺序已经不同，因而把标记本身当作字面前缀、尾段拼进结果。这与截图的 `我是{0}考莫人路里卡{1}。` 相符。

本批为有实参的完整句式使用 `conversation.form.<kind>.<slots>`，再加完整原句作为词库身份。四种已确认来源分别物化为：

| 原英文结构 | 实参含义 | 正式语义域 | 中文顺序 |
| --- | --- | --- | --- |
| `{0} {1}` | 实际玩家姓名、文化字段 | `conversation.form.p.ap` | `{1}{0}` |
| `{0} {1}` | NPC 描述、动作结果 | `conversation.form.t.ct` | `{0}{1}` |
| `{0} {1}` | 物品组成 | `conversation.form.i.ii` | `{0}{1}` |
| `{0} {1}` | 数值、单位 | `conversation.form.u.vu` | `{0}{1}` |

只修正资源身份，不增加字符串补救、标记清除、回退或兜底分支。原表达式投影器不改，真实人名、文化字段和原生介绍动作也不改。所有有实参的作者句式同步采用同一资源身份规则，避免只对截图中的一句另设替换。

另外，源清单中同一继续按钮有两条不同目标，之前的表达式元数据取第一条、词库取最后一条；本批将两者统一为保留原 `[SPACE]` 标记的同一译文，再由原生成过程去重。

### 菜单词条提取对象与消费者不一致

原 `141F70` 通过 `1427CB/1427E6 → CF990` 加入 `ESC.\"Goodbye\"` 与 `0.Back to chat mode selection`，动作分别仍为 ESC 和0。原生 `D031F → 114680` 的消费者绑定按点号切出后缀。此前词库却只有带前缀的整条原记录，因此查找 `\"Goodbye\"`、`Back to chat mode selection` 都失败。

本批在作者清单的 `native_record` 保留原记录证据，实际 `source/target` 使用消费者真正取得的完整后缀。正式后缀变为 `\"再见\"` 与 `返回交谈方式选择`；键帽、点号、动作、原选项及命中仍由同一个原生 Menu 保持。

静态绘制链还确认：此前 `before_consume` 返回不可用会在 `native_menu_component::lend` 之前结束；因此没有进入 `enter_menu_component` 的 `character_creation_label`，后续 `1149F9` 文本调用也没有启用 `Scope::text`。旧文字于是留在原生位图路径，与同页已接入的中文组件使用了不同的字形路径。本批使这两条已确认后缀正常完成来源解析、借用和原文本作用域，没有新增另一套英文绘制或像素修补。

## 原生缓存恢复时也重新绑定同一个来源

上一版仅在普通菜单回调及当前 `1427FA` 等待重建时绑定，`native_menu_component::paint` 的保留来源物化会跳过回调；其中保存的旧表达式仍使用上面的错误词库身份。

本批让实际 `CFFB0` 的标题和行消费回调也进入物化阶段。`native_menu_component::source()` 返回本次完整消费的真实来源实例：普通构造为活动实例，物化时为当前保留的原 Menu 来源，区别于其输入 owner。聊天行按这个实际实例绑定原 `ESI` 对应的行，聊天方式菜单也绑定该实例。其他菜单族在物化阶段保持原先不重新执行环境绑定的行为。

这一改变只更新真实 Menu 的中性文字资源；不激活另一份输入 owner，不改 native records、样式、选择、布局或缓存像素，不遍历页面绘制贡献。状态序列化结构、驻留 ABI、Hook 编号和调用点均不变。旧聊天缓存重新被原生完整 Menu 消费时，使用修正后的资源身份和后缀。

## 问候的原生条件

截图当前正文是“你在想什么？”。最初回应直接称“问候缺失”超出了这张截图能单独证明的内容。`141060` 的完整反编译表明：只有实际 NPC `+231h` 标记的 bit0 为0时才消费 `GREET`／晨间／夜间及久别问候；之后原生设置 `|5`，再按原条件消费 `GREET_QUERY`。因此不能因为本次没有早安，就在 Mod 中强制补出问候或改标记。

本批静态核对了问候完整格式、`unfamiliar %s` 的身份域、`tribesman/tribeswoman` 词值和 `p` 实参消费链，保留全部原分支。没有重新运行问候业务生成，也没有自行验证游戏画面。

## 修改文件与原始依据

- `translations/generate_conversation_sources.py`：有实参句式的语义键加入真实种类及实参类型，原文不再单独决定不同语法的译文身份。
- `translations/messages/conversation.zh-CN.json`：两个菜单后缀与原记录证据、继续按钮目标；原任务／台词分支仍保留。
- `modules/adapter/windows_conversation_forms.inc`、`translations/messages_embedded/values.conversation.zh-CN.tsv`、`catalog/zh-CN/messages.tsv`：按上述来源重新物化。2275个产生式、2272个去重资源键。
- `modules/adapter/native_menu_component.h/.cpp`、`module.cpp`、`windows_conversation_sources.inc`：本次实际 Menu 来源及其原生物化消费绑定。
- 原 `15DFC0`、`1427CB/1427E6` 的逐指令依据见 [原生文字边界](20261111-conversation-native-boundaries.asm)，正文入口与资源全引用见 [完整提取记录](20261111-conversation-all-text.md)。原 `141060` 完整反编译为本地 `build/analysis/conversation-20261111/00541060.c`，未运行原函数。

此前记录的 footer、About 按钮中心、历史 Scene／renderer children 及 `native_text_limit` 布局所有权问题仍待整改，详见完整提取记录对应表；本批不以已经发布为其合规依据。

## 交付状态

修正源码、生成资源与静态说明已保存；根统一队列完成一次配置、一次增量编译及正式兼容热发布。Adapter 及头文件依赖的组件重新编译、链接，Catalog 目标完成；日志保留既有函数指针转换、结构字段初始化、extern、未使用项及缩进警告，无编译错误。入队至所属批次结束未继续修改该批源码。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 468 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求 | `e0cc0a2438f1495398a7095fd9c226fd` |
| 批次 | `73b5db1a72f9488c89932d80b51e2bc1` |
| 编译结果 | `build/.compile-queue/results/e0cc0a2438f1495398a7095fd9c226fd.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 完整日志 | `build/.compile-queue/batches/73b5db1a72f9488c89932d80b51e2bc1.log` |
| 正式事务 | `0227d9411af74d8ea558e961e0c1adf1`，2026-11-11 10:47:00（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/0227d9411af74d8ea558e961e0c1adf1/publication-result.json`，`success=true`、`applied=true` |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧件归档 | `回收/20261111-104658-0227d9411af74d8ea558e961e0c1adf1/package/`，三件先归档后替换，保留原相对路径 |
| 当前进程 | 只读枚举仍为 Windows PID `468`，对应宿主 PID `3145474` |
| 兼容交接 | 收到 `ReadyToPublish` 后提交，Catalog、Adapter 第5代返回 `Applied` |

已完整读取请求 JSON、全部批次日志、正式发布 JSON 与清单，读取正式件、构建件、源词库和旧件哈希：

| 文件身份 | SHA-256 |
| --- | --- |
| Adapter 正式件／构建件／清单／Applied | `728b2f404d790717746cd14612fd6073f252b59f05cb3aa59823f31c8d430c52` |
| messages.tsv 源词库／正式件／清单 | `7c37db4445c4d07d4214b68222042f8e030336fe878ee3303ce91eb05a8f0861` |
| 已归档旧 Adapter | `49b7bcb4ece44d05a0e8b8106b02780cd525a21eb684c99e1d02c612118f8113` |
| 已归档旧 messages.tsv | `e2d572743984c6ba94406f2c1e1be8fcaf0d9ca553b7f1de16b3ce430244d5b3` |

源码修正、产物编译、正式文件发布和当前进程兼容交接完成，根 `uwcn_launcher.exe` 继续使用同一正式包，无需重启。没有自行测试画面；本次 Applied 仅作为交接回执，不作为“画面已正确”或“全部分支已运行验收”的证明。
