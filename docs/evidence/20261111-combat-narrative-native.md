# 战斗宣告漏译修正与正式交付

2026-11-11（Asia/Shanghai）。用户截图中的 `You try to swing Herppa with your kaumolais spear.` 来自原生武器攻击声明。已完整反编译当前 Windows 3.89.1 的12个相关函数，提取并对应原文24节138行、同一攻击函数15个资源键、24个格式调用点及全部文本选择分支；具体范围、原始输出和逐项来源见[完整分支记录](20261111-combat-narrative-branches.md)。不将这些明确函数的完整提取扩大表述为整个游戏已全部覆盖。

## 源码及词库修改

- `modules/adapter/windows_message_combat_body.inc:7`：补齐射击、投掷、武器近战、徒手四路声明的原生局部复制。实际点为 RVA `12FF01 / 12FF29 / 12FF4B / 12FF6D`，均为完整7字节 `LEA EDX,[ESP+268h]`。EAX 是原生已选资源返回，新增 F492—F495 仅把它的语义源传给同一原生目标。四范围没有内部 incoming，复制循环和后续 `52FFD2 → 4FDCB0` 不变。
- `translations/messages_embedded/literals.combat-narrative.zh-CN.tsv`：补齐同函数两条原诊断字面量，攻击方／防御方倒地修正 +20。是否启用诊断仍由原生标志决定。
- `translations/messages_embedded/values.combat-narrative.zh-CN.tsv`：补齐原生诊断技能 `MOVEDODGE` 的显示译文“移动闪避”，以及NPC攻击玩家时原生直接生成的 `npc/you → 你`。人物专名及原内部标识保持原值。
- `catalog/zh-CN/messages.tsv`：使用已有 `translations/build-message-catalog.ps1 -ExistingLiterals` 生成。97743项增至97751项；差异只有8条新增键（2字面量、4原生历史大小写身份、2动态值），没有更改原键值。

武器名、弓、攻击动作、攻击者、目标、PC／人类／动物资源选择和听觉分支全部沿实际原生来源处理。截图句式的中文资源为“你试着用考莫长矛挥击Herppa。”，这只是由已确认资源和截图实参得出的文字说明，不是运行画面验收。没有固定句替换、重新选择攻击动作或另建UI，也未增加断言、测试、保护、回退或兜底分支。

## 边界与既有待整改项

- 本次覆盖实时原生战斗消息来源；`windows_message_history.inc:6` 的 `history_forms` 尚无战斗声明完整动态语法。`FE2B0` 从 `msglog.txt` 重读展开后的英文时没有原模板实参身份，旧记录和新英文记录均不能宣称已被本次四点修复覆盖。历史查看动态战斗文本仍待对应文件消费边界处理，未改写英文日志或反查当前角色来猜历史名字。
- `modules/adapter/native_renderer_component_binding.cpp:47 / 554 / 570 / 672` 保留组件集合、快照及遍历重画机制，侵占原生UI重绘生命周期；影响既有渲染owner，待整改。本次只传递不含位置和像素的文本语义，没有扩展该机制。
- `docs/design.md:19 / 196` 的固定署名行槽和独立 `DisplayPlan` 历史设计仍与当前约束冲突，影响实现依据，待清理。
- `native_footer_component.cpp::paint_text`、`native_ui_scene.cpp` 的既有所有权问题继续按[前次记录](20261111-combat-menu-native.md)保留待整改状态。编译、发布成功不代表上述问题已符合要求。

## 编译、正式发布及回收

源码保存后冻结请求范围，主代理通过唯一队列入口提交；子代理仅做静态反编译和审查，没有编译或运行游戏。

```powershell
./build.ps1 -Toolchain MinGW -Module adapter,catalog -Publish -Reload -TargetPid 7980
```

一次配置、一次增量构建成功。Adapter重新编译链接；Catalog目标完成，DLL沿用原产物，词库数据更新。批次日志有20条既有函数指针转换、extern初始化、未使用项及缩进警告；本次新增战斗文件无编译诊断。没有清理或另建构建树，没有运行产物作验证。

| 项目 | 已读取的实际回执 |
| --- | --- |
| 请求ID | `9204e6c0389d46dc8562b64f48b84f23` |
| 批次ID | `6962fa79072e404faf9e23f8b52430fe` |
| 请求结果 | `build/.compile-queue/results/9204e6c0389d46dc8562b64f48b84f23.json`；Success、PublishRequested、ReloadRequested均为true |
| 完整批次日志 | `build/.compile-queue/batches/6962fa79072e404faf9e23f8b52430fe.log`，已读取 |
| 发布事务 | `9a44aea2d2994d70bcfed63e610da210`，2026-11-11 19:53:53（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/9a44aea2d2994d70bcfed63e610da210/publication-result.json`；success=true，PID7980 applied=true |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧件归档 | `回收/20261111-195348-9a44aea2d2994d70bcfed63e610da210/package/`，已读取三件旧文件清单，保留原相对路径 |
| 当前进程交接 | PID7980返回ReadyToPublish，随后Catalog第3代、Adapter第3代Applied |

```text
Applied 9a44aea2d2994d70bcfed63e610da210 catalog:6bbf0f17ac1614429c8c020629746154e08906e17041c1dc1feb183977bc4aa5:3 adapter:b712d15ec0df459d61f7557fdcd0eb39012e57230c380de7f85bfe09239548df:3
```

Adapter在构建产物、正式文件、清单及Applied回执中的SHA-256均为 `b712d15ec0df459d61f7557fdcd0eb39012e57230c380de7f85bfe09239548df`。词库源码、正式文件及清单中的SHA-256均为 `41ebf056879554168f0f1a2392732710b4349d87b3f0f3621dda709da166d202`。旧件先回收再替换，根 `urwcn_launcher.exe` 继续使用同一正式包，无平行修复包。

源码修改、产物编译、正式文件发布及兼容交接均完成。没有自行启动、关闭、重启或操作游戏，没有测试、注入验证、模拟输入或新测试脚本。仅执行已授权的兼容业务热发布事务；Applied证明交接完成，画面仍由用户验收。工作区已有的 `publish.ps1` 修改未改动，也未归为本次修复。
