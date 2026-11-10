# 主游戏 HUD 与已知区域地图：文本来源提取及消费接入

## 范围与静态来源

按用户“反编译提取并处理所有会出现在这里的文本”的要求，范围为两张截图对应的主游戏 HUD、已知区域地图，以及从地图打开的地点详情、标记编辑和标记选择窗口。屏幕内消息栏继续使用已有的原生 MessageFlow 全消息来源体系；这份记录不将全游戏业务消息误称为有限的 HUD 标签。

目标为不真实的世界 Windows 3.89.1，Steam build 26139145；PE SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`，image base `0x400000`。以下接入地址均为 RVA；提取文件中的 VA 保留原值。

- 本地反编译 C `docs/evidence/20261110-hud-map-decompiled.c`：50 个 HUD／地图及直接文字来源函数，另加任务记录读取和覆盖 16 种原生任务类型的 15 个构造函数，共 66 个函数。原始提取按项目 `.gitignore` 规则留在本地，仓库提交下列整理后的清单、指令证据及提取脚本。
- [原始调用与候选数据引用](20261110-hud-map-source-references.tsv)：原始候选不等于可显示文本，保留 memcpy 中部引用与被引用的非文本字节，便于复查。
- [完整文本资源清单](20261110-hud-map-text-resources.tsv)：1134 项去重的完整字面量／文件记录，含来源函数、指令引用和消费／保留策略。599 项关联地名词素初始化器，包含英文释义及应保留的芬兰语专名，不能将数量当作新增译文数。任务构造函数中不会直接用于地图的对话文本保留在原始引用文件，不混入有限地图标签清单。
- [全部 39 个指令入口调用及上下文](20261110-hud-command-callers.asm)：相邻调用的上下文有重叠。指令来源为直接文字、原生技能名称、163190 动作描述或 164720 操作说明；`INIT` 仅触发原生“指令”标题分支。
- [新增消费边界的逐指令记录](20261110-hud-map-consumer-boundaries.asm)。提取工具为 [Ghidra 脚本](hud_map_AllText.java) 与 [离线整理脚本](extract-hud-map-text.py)，仅读取 PE／反编译／反汇编和词库，不执行游戏。

## 实际覆盖

| 显示内容 | 原生来源及消费 |
| --- | --- |
| 姓名与文化、负重、各项惩罚及合计 | FA2A0/F8E20；既有 HUD 标签、身份及惩罚度量边界 |
| 饥饿、口渴、营养、体温、精力 | F9910；15FF80 的 9 个营养分支、15F450 的 13 个体温分支，以及 58E938 表的 7 个精力状态 |
| 方向、移动状态、速度 | FAA30、58EA40 的 8 个方向、11 个状态分支；实际完整文本／原生数字绘制调用 |
| 当前指令及重复动作 | F90D0/F91E7；F9600/F9869/F98F1；原生技能、动作、制作需求和物品名称来源 |
| 手持物品、品质、盾牌姿态 | F9200/451770 的完整物品来源语法；F95C3 消费，不对已截断英文猜译 |
| 季节、月份、月相、时段、日期 | 103640、8A310、8A600、15E910、15F8E0；既有 world/calendar 词库与格式来源 |
| 地形、文化领地、地点、地名释义、比例尺 | 8FF70、8E4F0、9AD00、9B040、A8F50、A3E70；地名原生组合，中文在完整来源边界生成 |
| 已知区域地图标题、11 项标记说明、11 个文化名 | E3020/E3A50/E3D90/E5990；既有 culture.map/topic 词库和实际工厂绘制 |
| 六项地图操作、缩放说明、帮助 | E5D01..E5DB4，CFDF6 绘制及 CFECB 命中宽度；`gameinfo/urw_scrinfo.txt` 的 KNOWN_AREAS_MAP 两条实际记录 |
| 标记编辑、选择 | E4050/E4960；两类编辑标题、选择标题、两条说明、颜色说明、编辑／移除／退出按钮，原生颜色快捷键保持原值 |
| 地点详情及任务注记 | E2960/E2850/E4C70；原生任务标题、告知者／消息提供者、地点、铁匠订单、渔网／陷阱地点及今天／昨天／N 天前 |
| 玩家标记、姓名、数字与标准单位符号 | 保留原值；玩家文字在实际原生绘制及度量处支持 Unicode，原有输入动作及单位系统保持原值 |

新增词库 `values.hud-map.zh-CN.tsv` 共 309 项：284 项完整指令入口文字（复用已审阅的动作／技能译名）、20 项地图句式／标签，以及 5 项任务位置说明。另新增 `culture.map.marker.edit_text`、`culture.map.marker.remove` 两个控件资源。现有 HUD、world、culture、calendar、activity、craft-requirement、item 和 MessageFlow 词库继续复用。

## 新接入的语义和生命周期

1. F90D0 在完整输入被接受时已有 `native_hud_language::command`，F91E7 现在消费该完整源。原生 `>26` 留 24 加两点的边界按实际字形宽度扩展；F9869 在重复动作被截短前绑定完整源，F98F1 按原生 `>24` 留 23 加两点的语义消费。英文模式继续走游戏原值。
2. 重复制作描述沿 F97BC/F983C 的实际 6C8B0 返回来源处理：嵌入的需求词进入 craft-requirement，`CONSTANT.OBJ` 的 descriptor+9 进入现有物品名称语法；1639FD 记录原生显式名称复制的来源。`(mod)` 是已确认的模组前缀分支。
3. E2AC8/E2BC6/E2CC6/E2E26/E2FC2 的任务注记、E4F94 的地点、E50E7/E53AF/E53D3 的订单／访问说明保留原始 sprintf、参数及写入。仅记录语义表达式。E2850 返回时的 EDX 是实际 destination-source；由这个真实复制结果绑定原生选中的注记槽，不重做游戏的选槽业务。
   任务位置说明额外追溯了全部 16 种任务的构造函数。`+1F8/+244` 两个位置标签字段的实际非空写者为四条固定说明和 555298 的 `Assumed whereabouts of the %s`；后者消费与 type35 标题相同的非玩家命名生物来源。五项进入 `hud.map.location`，不将未绑定的持久化字段误当作已有完整消息来源。逐项写者见[任务位置字段清单](20261110-hud-map-quest-location-fields.tsv)及[原始写入指令](20261110-hud-map-quest-location-fields.asm)。
4. E41E5/E41F1、E4DA2/E4DBF/E4DDD/E4DFD、E4FA4/E50F7/E53F7 在完整 162300 文本构建边界借入中文。沿现有完整字形词分隔进入原解析器；E4245/E54E2/E5595 的原生 10EFD0 继续负责测量、换行和绘制。地点与标记的最大长度操作数接入已确认的五个 SUB，后续比较、标记预留、`*8+20` 和 300..720 限值均由原生计算。
5. E452D/E461E/E463D/E4B60 按实际 CALL 的同步作用域区分控件。原始英文／玩家文字仍由游戏存入菜单；CFDF6 的字形及 CFECB 的字宽消费同一显示文字，原生选择重绘绑定同一来源。
6. E418E/E49EF 是原生标记子窗口的实际纹理构造返回点，E554D 是地点详情的实际表面构造返回点；在这些已确认目标按真实输出密度栅格化。绘入后的像素、上传及销毁由原生流程管理。没有位置表、整页字段快照、像素扫描或文字贡献重放。

新增实现为 `modules/adapter/windows_hud_map_text.inc`，接入 `module.cpp`；另扩展既有地图按钮、渲染器度量、地点来源与目标密度入口。新增来源复用原 `windows_messages::values` 的语义序列化，没有新增 UI 布局／位置字段；本轮不更改既有 HDA8 状态结构或驻留 ABI。

## 既有不合规实现：待整改

- `modules/adapter/native_ui_scene.cpp:12` 的 Child/Container 集合和序列化仍保留，会使 Mod 持有额外的组件图；完整退役待整改。
- `modules/adapter/native_renderer_component_binding.cpp:39` 起的历史 Owner（children 字段现位于 47 行）、`paint_hud:558` 及 `paint:644` 的子项遍历仍影响原生缓存和重建所有权；完整退役待整改。
- `modules/adapter/native_component_binding.cpp::construct`、`native_component_model.cpp::paint` 仍有依赖历史组件图的构造／绘制接口，退役待整改。不能把来源绑定当作实际绘制完成。
- `modules/adapter/native_footer_component.cpp:88` 的独立署名排版影响原生布局所有权，待整改。

本轮在已确认的原生构建和同步绘制调用接入文字，不扩展上述历史组件集合或独立布局。编译或发布不能据此证明整个项目已符合所有权约束。

## 交付记录

源码修改、统一队列编译及正式文件发布均已完成。最终产物位于 `package/modules/uwcn_adapter.dll`，最终词库位于 `package/catalog/zh-CN/`，正常根启动器使用这些正式文件。

| 阶段 | 请求／批次／结果 |
| --- | --- |
| 初批源码与词库发布 | 请求 `32c2a0bda69d4b3fb5b2a1afdddcadc4`；批次 `f0cadf7c5da94f5889ab39d1ad6bae6d`；事务 `ed688b2a8fc54eb69d28ea9df3a75980`；18:14:11（Asia/Shanghai）PID 364 返回 Applied，catalog／adapter 均为该进程第 2 代 |
| 五项任务位置说明的最终编译 | 请求 `192cae21213f4fffbe56937c521973c2`；批次 `df161b3f17384384afb2e2b2a474adab`；adapter、catalog 编译成功。发布事务 `acf097194fde46dd98a93638ea10f9a6` 的 PREPARE 在连接原驻留管道时超时；随后只读进程列表已无 urw.exe。该事务未提交 COMMIT，未移动正式文件，不能报告 Applied |
| 最终正式文件发布 | 游戏已退出后，通过根队列请求 `c85e2edc4a2e46e387dd93ef81c7cfc9`、批次 `07af5cb2eb054b37ae0bd7041fd87cc9`，执行 `-Toolchain MinGW -Module adapter,catalog -Publish`；事务 `297822baf52249f2a475eff1f3cb19e5` 于18:24:57成功。最后一批未请求运行中交接，没有最终 Applied 回执 |

已读取上述请求结果 JSON、完整批次日志和发布事务回执。最终旧 Adapter、cultures.tsv、messages.tsv、release.json 先移入 `回收/20261110-182457-297822baf52249f2a475eff1f3cb19e5/package/`，再替换正式位置；没有备用运行包。驻留桥和启动器未由本任务替换。

最终正式文件 SHA-256（已与本批 release.json 对照；两份词库的源码／正式文件哈希一致）：

- Adapter：`e6bd92a5a1a7a80c7f29b54e177a16278227bbcbdcd13e041bf92b0d7730d361`
- Catalog DLL：`cd5ea4f63e239691176f6bf1e38a1b4c232a0c9c5f8182eb80aacefbfa8e6719`
- messages.tsv：`48b95c9f5bb1a65ad0f01b3113220b3d2e3d228296261afae156cef5229f2a39`
- cultures.tsv：`5d5321d3bced38a79616ff514d4eb84cb178bb53121e50eb5f06ffb5b148b286`

编译保留既有的函数指针转换、extern 初始化、未使用函数和缩进警告；没有本任务新增编译错误。工作区其他任务的修改保留，不以本记录声称它们已经完成语义或视觉验收。

遵守禁止自行测试的要求：未启动／关闭／重启游戏、未注入、未模拟输入、未执行产物做验证，未创建测试用例或断言；唯一运行中动作是既有授权的兼容模块发布事务。静态来源清单、编译成功和初批 Applied 均不代表最终画面验收。
