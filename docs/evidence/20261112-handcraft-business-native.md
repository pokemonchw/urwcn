# 手工制作全部后续分支与消息来源

2026-11-12，Windows x86《不真实的世界》3.89.1 / Steam Build 26139145。用户要求包含选项执行后的全部分支和消息，上一阶段仅完成建造菜单，错误地排除了施工、材料选择和制作结果；这一范围判断已更正。本次从 HANDCRAFT OPTIONS 入口继续追踪其全部分类、实际配方、业务调度、共享材料流程、制作结果和中断输出。

## 反编译和逐项提取

原 PE：`/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。以下函数和 CALL 地址均为 VA；适配源码的挂接地址为 RVA（VA−400000h）。数据来自磁盘文件和只读 Ghidra 工程，未运行游戏。

[handcraft_Decompile.java](handcraft_Decompile.java)为 Message、ResourceMessage、PhysicalRequirement、原生菜单及组件声明已确认的参数。最后一批完整提取72个不同函数，同时输出逐指令引用和调用参数常量／合流来源：`build/analysis/handcraft-20261112/final.c`、`final-refs.tsv`、`final-operands.tsv`；日志 `/tmp/urwcn-handcraft-final-ghidra.log`逐个列出72个 Extracted 并以 Discarding changes结束，工具退出0。命令使用既有 `inventory3891/urw.exe`、`-process urw.exe -readOnly -noanalysis -scriptPath docs/evidence -postScript handcraft_Decompile.java`。函数范围见[72个函数](20261112-handcraft-functions.tsv)。上阶段26个菜单／百科组件函数仍作为对应消费者证据使用。

中间 auxiliary 批次在已提取9个函数后，因传入的004D5120不属于函数而结束；不能用该批工具退出码证明完整。该地址未用作挂接依据；遗漏的有效函数随后由 leaves、guards和最终72函数批次重新提取。所有最终清单采用 final 输出，不把先前误查的503970、505700计入本次业务范围。

已保存的可审阅清单：

| 清单 | 范围 |
| --- | --- |
| [业务分支](20261112-handcraft-branches.md) | 13分类、模组／自定义分类及共享流程的实际分流 |
| [21个菜单标题](20261112-handcraft-menu-titles.tsv) | 全部固定手工制作子菜单标题，另补11个原先缺失的标题身份 |
| [120条配方](20261112-handcraft-recipes.tsv) | 当前原生文件中的89条DIY、31条BIY；保留原文件、行号、分类和显示来源 |
| [配方附注](20261112-handcraft-recipe-annotations.tsv) | 38处真实引号附注／名称覆盖；带+的附注按原前导空格语法处理 |
| [182处消息调用](20261112-handcraft-message-calls.tsv) | 每处F6510调用的函数、地址、当前PE字面来源和原参数证据 |
| [91条字面正文](20261112-handcraft-literal-texts.tsv) | 上述调用经参数常量／MULTIEQUAL合流提取的不同非空正文及实际译文 |
| [30条资源正文](20261112-handcraft-resource-texts.tsv) | 所有已确认561B00资源键及其已选资源模板；含继续制作、品质下降、成品、等待加工、原料无效、材料不足、体能和中断询问 |
| [47条默认材料说明](20261112-handcraft-requirement-descriptions.tsv) | 46BBF0完整选择器的全部非空说明及译文，不只箭头一项 |
| [181条格式来源](20261112-handcraft-format-sources.tsv) | NativeFormat实参常量／合流格式；明确区分消息、原生显示消费者、持久物品名和内部文件／数值语法 |
| [15处完整CALL](20261112-handcraft-calls.tsv) | 新增／扩展的菜单、材料窗口、耗时窗口和消息格式边界，保留原5字节指令与目标 |

182处只计本次72个函数内的直接消息CALL。共享消息／询问／物品／方向窗口的已有完整消费者继续处理其参数，不把时间推进期间任意世界事件递归算成手工制作专属业务。清单中的91、30、47是来源类别，不能相加作为不同屏幕行数；一个消息CALL可以接受多个原生分支。

## 本次漏译原因与修正

1. 上层制作行已有语义来源，下层菜单仅按少数标题绑定，ARROWS及其它子菜单因此仍显示英文。现将绑定接到所有35个已登记1002B0入口共同经过的100525→CFFB0完整绘制调用，读取其真实20C上层行来源并绑定真实E8下层行。标题采用该原生调用已保留的Echo来源，配方、动作和自定义分类保留各自的语义。另补11个固定子菜单标题的实际menu.title身份。同步绘制标志只阻止旧标题绑定器覆盖这些来源，没有新增行表、位置表或序列化字段。ESC、空行、原34字节截断、原生竖线旁注及F1动作423h保持原语义。

2. 截图说明来自独立46BBF0，而非4633B0已有说明构建器。468AC0仅在该材料记录的说明为空时调用它，把所选默认说明复制进原记录，再于469182用`?(`、说明、`)`构造消息并于46918F输出。原代码只查说明指针的普通绑定，该选择器的文本没有对应来源。现在已确认的469182格式实参3使用`craft-requirement-description`完整语义；全部47条已具译文，其中补入33条当前PE原文，保留14条既有译文。完整括号正文另有47条日志身份。

3. 464730材料窗口的标题、介绍段落和实际要求行，488840工作窗口的任务标题、耗时、进度／继续进度、体力消耗九种选择值、取消及可稍后继续说明，现接入各自完整原生Panel、Words、Paragraph、ShowText。耗时只解析原生893A3..894CB实际生成的数字、分隔符、hour/hours/minutes/seconds及数值调试后缀；不重算时间、不生成进度。656个大写任务／配方显示别名和381个大写物品别名来自现有词汇及已确认标题。`REPAIR WORN-OUT %s`是4439C4的真实标题语法，单独保留原物品操作数。

4. 446564拆除成功格式缺少语义来源，现接入实际地形名参数；4628B3原生调试分支的材料名称格式也缺少来源，现接入原整数与451770返回的完整物品名。新条目追加在格式表尾，保留已有Hook ID。

5. 520CD5、521B97、521BC3将沤制植物、晾干的沤制植物、干动物肌腱的名称保存到原生descriptor+9。现为这些确切生成语法及451770随后使用的首字母大小写变体提供显示解析；动物使用既有类名清单，植物使用既有材料词汇，原描述符和存档继续保留英文。解析进入已有物品名称来源，供后续材料、成品与资源标签消息消费。

6. 完整体能阻止分支还暴露8个未译的固定动作操作数（制作箭矢、弓弦、渔网、装柄、拆柄、沤制、晾干、制作物品）。它们和563840返回的相关动作名共补入22个确切action身份，用于原PHYSREQ模板、身体部位要求及“缓慢且困难”消息；不重算受伤、姿势或可用肢体。

原生文件中的所有配方标签、38处引号附注、91条直接字面正文和30条资源正文均已逐项对应既有或新增译文。原选择、批量／产率／数量、损耗、品质、材料偏好、地形条件、施工记录、取消／暂停／继续及完成状态均仍由游戏执行。

## UI所有权与限制

本次在真实组件文字调用中同步提供完整文本，沿既有编码、完整字宽和中文字形接口按原生目标真实输出密度绘制。原生UI管理换行、居中、字距、按钮、光标、选择框、鼠标命中、背景、表面缓存与淡入淡出。未增加坐标、行槽、DisplayPlan、全局像素跟踪、像素贡献集合或延后文本重放。翻译失败显示原文继续使用用户此前明确授权的显示行为，本次未添加其它保护或兜底。

审阅仍发现既有 `modules/adapter/native_footer_component.cpp:58`，尤其79行起由Mod计算主菜单署名宽度、间隔和位置，违反原生布局所有权，影响主菜单署名，待整改；`modules/adapter/native_ui_scene.cpp:12`起的Child／Container历史组件集合和序列化仍保留，完整退役待整改。本次没有扩展这些集合或调用其文字重放，不能将本次编译／发布当作既有实现已合规。

没有启动游戏、注入运行验证、模拟输入、运行测试或产物，没有创建测试脚本、测试工程、测试用例或断言。静态提取和编译不构成画面验收。

## 交付状态

源码修改、产物编译、正式文件发布及既有进程的兼容业务交接均已完成。源码及98931项词库保存后冻结，所属批次结束前没有继续修改请求范围源码；本节在回执后补记。统一入口：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2735482958/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 实际结果 |
| --- | --- |
| 请求ID | `1163de786c9347dd91ef34dfd82842ca` |
| 批次ID | `7bd97379fd8b4cb7b78acacf0f1eeb50` |
| 请求结果 | `build/.compile-queue/results/1163de786c9347dd91ef34dfd82842ca.json`，Success、PublishRequested、ReloadRequested均为true |
| 完整日志 | `build/.compile-queue/batches/7bd97379fd8b4cb7b78acacf0f1eeb50.log`，已完整读取；一次配置、一次增量编译，Adapter重编译并链接，Catalog目标成功 |
| 正式发布事务 | `96d8b924341449fabf5b05390f158823`，2026-11-12 17:36:30（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/96d8b924341449fabf5b05390f158823/publication-result.json`，success=true，PID364 applied=true |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧文件回收 | `回收/20261112-173628-96d8b924341449fabf5b05390f158823/package/`，三件按原相对路径先移入再替换，未覆盖或删除旧件 |
| 现有进程 | 宿主PID225676、Windows PID364；只读确认仍为原进程，使用用户已授权的原驻留桥事务 |
| 驻留桥回执 | ReadyToPublish后Catalog、Adapter均为第3代Applied；未启动、关闭、重启游戏或进行运行验证 |

```text
Applied 96d8b924341449fabf5b05390f158823 catalog:bf126890ba7042524fd8a606e94d5390d74bed7b633449f2512c05cd7aa501c0:3 adapter:fc865d2fec04aca3e1649a10a22f41d86aaeda3232803c71bc4423ac17e252c7:3
```

Adapter在构建件、正式件、release清单及Applied回执中的SHA-256均为 `fc865d2fec04aca3e1649a10a22f41d86aaeda3232803c71bc4423ac17e252c7`；98931项词库在源码、正式件与清单中的SHA-256均为 `ec929e3d4afdcae20caeaef514d7b84171f4dc22388714299c4247124c96f4d4`。本批与前批同属17时，`metadata/build-hour.txt`仍为2026.11.12.17，不作为本批替换或回收文件。Catalog DLL沿用现有二进制，词库随其第3代加载。

根正常启动器继续加载同一正式package，没有独立修复包或平行运行副本。编译保留20条既有函数指针转换、extern初始化、未使用项和缩进警告，0错误。已读取请求JSON、完整批次日志、正式发布JSON、发布清单和回收文件清单；Applied仅证明兼容模块交接完成，不代表代理自行做过游戏或画面验收。
