# 建造选项、子菜单与百科预览漏译

2026-11-12（Asia/Shanghai）。对象为截图中的Windows x86《不真实的世界》3.89.1 / Steam Build 26139145。源码已补接建造选项、木建筑、科塔帐篷三个菜单的实际原生消费者，并补齐两条菜单百科预览调用和图形预览标题。完整范围与逐分支处理见[分支清单](20261112-building-menu-branches.md)。

本记录保留上一阶段实际交付，不表示当时已完成全部业务分支。用户后续指出箭矢及材料说明仍漏译，范围已纠正为所有手工制作后续分支和消息，见[完整业务记录](20261112-handcraft-business-native.md)。

## 静态证据

原PE为 `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256：`c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。当前 `biy_glossary.txt` SHA-256为 `90008ee96f154c51de92b4434b680c13db7ef031055cbbefe49a991e3587ffe7`；`GAME.NFO`为 `071f384ad992d0a688833693f207a5cf8a969b4811e5e6603597d189087a4d5d`。本文地址为RVA，原始反编译和反汇编采用基址400000h的VA。

[building_Decompile.java](building_Decompile.java)在既有 `inventory3891/urw.exe` 工程使用 `-readOnly -noanalysis`，声明菜单、配方、动作、段落和文字的真实fastcall参数。四批共26个不同完整函数，C和逐指令引用表保存在 `build/analysis/building-20261112/{complete,consumers,leaves,button}.c` 及相应 `*-refs.tsv`；四批日志均显示已提取且Discarding changes，退出码0。原PE与数据库没有改写。初次启动工具因其默认设置目录只读而未进入分析，随后将工具自身的XDG设置／缓存目录放入/tmp；这不是游戏故障处理代码。

完整函数包括46980、42AD0、1002B0、3CA90、3CD20、122150、CF790、CF990、CFFB0、FFCC0、FFD60、FFF30、3C8A0、3C970、DF7B0、115E70、163190、40610、40000、40250、FF980、100100、1001C0、1157B0、3E680、CFAF0。原始汇编保留在同目录menu.asm、recipes.asm、command.asm、footer.asm。可提交的[20处CALL字节](20261112-building-menu-calls.tsv)来自磁盘PE，保留实际调用目标。

## 原因与实现

此前上层20C字节记录已有中文语义来源，主要供消息回显；1002B0通过CF990复制成下层E8字节原生Menu后，三个建造标题没有进入 `bind_menu_consumer_source` 的来源绑定分支。词库已有的建造译文因此没有被可见菜单消费。

本次复用相同原生行迁移的既有绑定器，将其命名为 `bind_upper_commands_menu`，供战斗和建造选择器共用。三个标题在原CFFB0标题消费前绑定原生Menu的实际标题、原行及其来源表达式；固定标签用menu.label，动作描述用activity，配方默认地形名用terrain，两处引号覆盖名用menu.recipe。原34字节截断分支与原生句点键帽保留，未新建选项表或布局表。

当前文件的全部31条建造定义均已提取：顶层4条、木建筑16条、科塔帐篷11条。固定菜单／取消／图形标题及百科F1说明合计另12条，逐项列于[43条来源清单](20261112-building-menu-texts.tsv)。木建筑的“天花板与地板”“带窗板的墙”按原引号覆盖名显示；不是简单翻译配方首行。7个实际百科别名对应6个主题，均沿用已有题名、摘要及完整正文资源，见[主题表](20261112-building-menu-topics.tsv)。

原1005B4和1005F8两条3CA90调用分别对应“首个非空主题”和“当前选择主题”。新增既有预览范围的两个Hook ID，令原标题、摘要和F1完整消费者解析该实际主题的中文资源，结束后清除原作用域。原英文主题、GFX.NFO、摘要来源、主题存在性检查和F1动作不改。没有增加持久状态字段或更改交接序列化格式。

重新绘制时，CFAF0可能已经登记动作423h的TEXTSPOT按钮记录。此为本次完整反编译确认的真实分支，绑定器略过该内部标记，继续由3CA90的原F1文字调用负责；不能把TEXTSPOT按普通带句点菜单标签处理。

图形配方的1004C8／100682两条115E70调用分别负责初次及再次绘制预览标题。新增menu.label的GRAPHICAL PRESENTATION →“图形预览”一项，同步生成97752项的messages.tsv；其它既有键值未改。完整原生CALL同步借用中文，调用前后进入／结束native owner，不登记额外的逐字段位置集合。

## 原生UI与限制

原菜单自身继续管理行顺序、快捷键、按钮、选择框、命中、输入、窗口、背景、淡入淡出和缓存。行测量及选择框复用D07FB／D0A49等既有完整字宽接口，标题复用115849／1159C9接口，字形通过原组件文字消费者在61BBB10真实输出密度下立即绘制。Mod不保存像素贡献、不追踪全局像素、不在Present前排版或重放文本，也不新增低清放大路径。

翻译失败显示原文继续使用已有明确授权的显示语义，本次没有添加保护、回退或推测性兜底。只读提取、源码审阅和正式产物编译不构成游戏运行验收。未启动游戏、注入验证、模拟操作、运行产物或测试，没有创建测试用例、测试工程、测试脚本或断言。

本次审阅仍确认既有 `modules/adapter/native_footer_component.cpp:58` 的paint_text，尤其79行开始按宽度、gap和logo计算主菜单署名位置，违反原生布局所有权；影响主菜单署名，状态为待整改。本次菜单修正不调用或扩展此路径，编译和发布不表示该既有问题已合规。

## 交付状态

源码修改、产物编译、正式文件发布及当前游戏的兼容模块交接均已完成。源码保存后冻结至所属批次结束；只有文档在取得回执后补记。统一入口：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2735482958/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 已读取的实际结果 |
| --- | --- |
| 请求ID | `896917ca8fd54f1b8a69fa4ed7c8d41b` |
| 批次ID | `2ac141eda129467cab6285786e3455e9` |
| 请求结果 | `build/.compile-queue/results/896917ca8fd54f1b8a69fa4ed7c8d41b.json`，Success、PublishRequested、ReloadRequested均为true |
| 完整批次日志 | `build/.compile-queue/batches/2ac141eda129467cab6285786e3455e9.log`，已完整读取102行；一次配置、一次增量构建，Adapter重编译链接、Catalog目标成功，0错误、20条既有警告 |
| 正式发布事务 | `362c4e905d9b48fcb023cc52bab7502d`；2026-11-12 17:05:58（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/362c4e905d9b48fcb023cc52bab7502d/publication-result.json`，success=true、PID364 applied=true |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/metadata/build-hour.txt`、`package/release.json` |
| 旧文件回收 | `回收/20261112-170556-362c4e905d9b48fcb023cc52bab7502d/package/`，按原相对路径先归档再放入新件 |
| 运行进程 | 宿主PID225676；只读模块映射确认加载本项目正式package；既有Proton Mono解释器只读枚举得到Windows PID364 |
| 驻留桥回执 | 先ReadyToPublish，后Catalog、Adapter均为第2代Applied；未启动、关闭或重启游戏，未注入验证或模拟输入 |

```text
Applied 362c4e905d9b48fcb023cc52bab7502d catalog:bf126890ba7042524fd8a606e94d5390d74bed7b633449f2512c05cd7aa501c0:2 adapter:13509a37a073ee8f5131f9dd6c63e713d11261d98aa56b3733d0e77cf47298c4:2
```

新Adapter在构建件、正式件、清单与Applied回执中的SHA-256均为 `13509a37a073ee8f5131f9dd6c63e713d11261d98aa56b3733d0e77cf47298c4`。新词库在源码、正式件与清单中的SHA-256均为 `05aebbe7ccca8761c0edc4a03fe5bf84828381a6e516818812a980bca0c3375c`。Catalog DLL内容沿用原产物，词库随第2代Catalog加载；构建小时为 `2026.11.12.17`。根urwcn_launcher.exe及驻留桥继续使用同一正式包，没有平行修复包。编译保留既有函数指针转换、extern初始化、未使用项和缩进警告；没有运行测试。Applied证明业务模块交接完成，不作为画面验收。
