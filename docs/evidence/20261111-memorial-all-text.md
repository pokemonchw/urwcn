# 纪念页与死亡说明的完整文本接入

日期：2026-11-11，Asia/Shanghai。用户截图显示纪念页标题、死亡原因、日期、地点、统计和死亡页脚仍为英文。此前先祖列表明确排除了独立纪念页及死亡分支；本轮将这两个入口全部纳入。

对象为 Windows x86《不真实的世界》3.89.1 / Steam Build `26139145`，磁盘 PE `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。正文地址为 RVA，提取文件用 VA，基址 `400000h`。仅离线反编译、读取磁盘指令、资源及源码；未启动、关闭、重启或操作游戏，未注入、模拟输入、运行产物或测试，未创建测试用例、测试脚本或断言。

## 反编译范围与分支

[memorial_Decompile.java](memorial_Decompile.java) 在已有 Ghidra `inventory3891/urw.exe` 工程中以 `-readOnly -noanalysis` 提取完整函数，声明原生文本、段落、标题及追加器的实际调用约定。反编译和日志保留在 `build/analysis/memorial-20261111/` 及其 `events/`、`producers/`、`leaves/`、`closure/`、`calendar/` 子目录；数据库变更被丢弃，没有改写 PE。原 `sprintf` 部分变参在初次 C 中未恢复，实际栈实参以[原生指令](20261111-memorial-native.asm)为准，不能把缺失的反编译实参当作空字段。

[调用者清单](20261111-memorial-callers.tsv)确认 `DD400` 有四个调用者：`DEA4A` 为死亡入口、`DEDA0` 为列表行、`DF36F` 为点选先祖详情、`1722B3` 为原调试入口。后三者的原 detail 参数分别为 0、1、1；死亡入口也为1。`DE990` 的 `ECX=-1` 来自主菜单 `125E04`，死亡记录号来自 `E754D`。四个 `DD400` 入口共享本轮原生消费者，不只匹配截图中的退出生命原因。

| 完整原函数 | 已提取的实际分支与显示来源 |
| --- | --- |
| `DD400` | 文件存在判断保持；detail=0/1；男／女代词；姓名与文化；短死因；死亡日期；地点与完整死因；年龄、冒险天数、原生 floor 后的公里数。读入 ANC 后临时安装其角色字段，绘制结束恢复原玩家 |
| `DE990` | 先祖列表／死亡入口；从列表进入同一详情；死亡页脚两段、`You are dead.`；详情和死亡入口各有原继续按钮。列表排序、页码、选择、键值、输入不改 |
| `DDC60` | `-100` 溺水，`-107` 冻死，`-112` 冰水昏迷后溺亡，`-101` 饿死，`-102` 缺水，`-103` 退出生命；其余分支中的 `-99` 失血、`-104` 重伤、`-106` 致命伤、`-109` 原病因字段；原“先出血／后昏迷／昏迷中受伤／随后死亡”追加组合。分别保存短死因、详细死因、地点和地域 |
| `DCF10` | 同一原因有 mode 0/1/10 三种语法；非负原因先取得实际攻击者并使用 `AD4F0(flags=4)`；陷阱 `-105`、出血 `-99`、火烧 `-111`、冻伤 `-107`、攀爬／坠落 `-108`、病因 `-109`、治疗伤口 `-110`；原默认 `being hurt`／`was hurt`／`killed by death` 也提取 |
| `AD4F0` | 人类／动物、性别／幼年称谓、已知姓名、姓名加描述、描述加姓名、原冠词；复用已反编译的完整 NPC 词值与语法。专名保持原值，不将整段攻击者描述当作专名 |
| `32EC0`、`D6BF0`、`16BF70` | 追溯 `A32BD68` 的全部实际写入：nausea、stomach burning poisoning、deadly poisoning、poisoning、Burned by fire，以及 `Hurt after %d meters fall`；载入／清零不构造新英文文案 |
| `8A600`、`8A310`、`15E910` | 原季节／月份选择、完整月相短语、1至13的周序数及 last、季节前的周与日、原日期 flags 和调试显示格式。沿用原 calendar 有限词值，不重新计算日期 |
| `8E4F0`、`7520` | 原村落文化前缀、所有地形／聚落名、` at `、完整地名；室内及当前位置分支仍由原函数选择。Your settlement、Small lake、Lake 和256槽地形词值复用既有 terrain 域 |
| `8E420`、`A8F50` | 芬兰语专名与英文释义，原前缀／后缀表连接，用户命名区域的同名双引号分支，原越界文字；复用已有有限地名释义和重复参数语法 |
| `9B040`、`9AD00` | 全部文化地域、中心／八个方位部位、无人区与邻近／远离地域、原 in/on 和 flags；复用原 geography.region 的完整有限词值 |
| `162300`、`10EB40`、`115E70`、`1157B0`、`15DFC0` | 原分词器、段落行高返回、标题带、原生居中与姓名／文化格式。原生坐标、宽高、颜色、描边、行距及后续游标运算有完整 C 和指令依据 |

源文、中文、参数类型和出处保存在[纪念页作者清单](../../translations/messages/memorial.zh-CN.json)。[生成器](../../translations/generate_memorial_sources.py)只物化该清单、已确认的 calendar.season 和 world.month／world.month_phase 有限词值，生成 `windows_memorial_forms.inc`、`values.memorial.zh-CN.tsv` 及正式源词库；196条句式／有限词值不是执行覆盖率或画面验收结论。词库没有只收录截图中的 `quit living`。

`15E910` 的完整 C 确认月份读 `1EA3A0 + index*100`，实际由 `messages/urw_defs.txt:151` 的 `.MONTH_NAME.` 填充：Center、Pearl、Soil、Swidden、Seedtime、Fallow、Hay、Harvest、Fall、Dirt、Dead、Winter month，以及原 `*` 分支的 Unknown month。截图正使用 Swidden month，不能套用旧 calendar.moon 的 january 等值。沿用 world_hud 中已提取的13个月名和4个原时段，物化65种完整月相；不推测新月份。

短死因与详细死因通过相同的、根据原追加指令提取的完整源语法处理；不是逐词替换。`Z` 为死因／受伤事件，`Y/X` 为人称／属格，`J` 为原病因字段，`D/S/M/O` 为原日期／季节／月相／序数，`L` 为 `8E4F0` 的地点构造。既有 `c/k/g/n/v` 分别消费原攻击者描述、文化、地名、专名和数字。已有英文 ANC 不需要重写；专名及数值留在原参数中。

## 原生接入与所有权

新增 [windows_memorial.inc](../../modules/adapter/windows_memorial.inc) 在3.89.1注册以下完整调用，复用现有姓名、短死因及统计 Hook ID；不添加 ABI 或状态分节。

| 原调用 | 本轮处理 |
| --- | --- |
| `DD596 → 115E70`、`DD5AD → 10E5A0` | 中文时把当次真实 x/y/width 交给原 `1157B0` mode 5。该分支自己创建同款 `115E70` 标题带、计算居中并调用 `115A94`；跳过随后旧英文定点标题。`115849` 的既有完整字形度量扩展供原居中公式消费；不复制标题坐标或在 Mod 里计算中心 |
| `DD7AF → 10E5A0` | 从当次 ANC 已安装的原姓名、文化索引和文化名构造名称语义；只翻译文化，姓名保留，支持原中文姓名 |
| `DD82B`、`DDA0A`、`DDA30 → 10E5A0` | 完整短死因和两种统计。列表统计继续使用既有原数字接入；详情使用同一原生完成字符串的类型化语法 |
| `DD8DE`、`DD93A`、`DD9A3 → 162300` | 完整日期句、地点句、详细死因句，仅绑定原完整追加输入；原生 parser 持有自己的词表 |
| `DEAE2`、`DEAEE → 162300` | 死亡页脚两段，保留原 reset/append 次序 |
| `DD900`、`DD9CE`、`DEB40 → 10EB40` | 原段落、宽高和颜色；中文分词只扩展字形边界。原函数计算换行及返回高度，`DD905/DD9DE` 等原指令继续推进下段，不计算自己的段落位置 |
| `DEA82 → 10E5A0`、`DEB72/DF3F2 → 114680` | 死亡状态和两处原继续按钮；继续按键及按钮尺寸由原控件管理 |

中文以既有双字节字形传输进入原生文字函数；测量和最终光栅共用已有字体／输出密度接口。`10E5A0` 的完整文字叶、`10EB40` 的字形宽度和原游标推进、`114680` 的完整字符及控件度量继续使用已确认扩展。字体在原目标实际输出密度下即时提交，原生 surface、上传、显示及缓存持有已画像素。未新增低清文字放大、通用 SDL 像素扫描、文字贡献记录、Present 叠字或延后重放。

`native_component_binding.cpp::construct` 排除 `DD400` 的原生文字／段落调用和死亡页脚，避免把这些字段加进历史组件坐标集合。`begin_native_owner/end_native_owner` 只在当次完整原生标题、文字、段落或按钮调用内抑制嵌套叶加入该集合；计数不保存文字、位置或页面，不跨输入等待。它们的完整重建已由 `native_full_language.inc::before_wait` 的 `DEB7F` 死亡等待和 `DF3FF` 详情等待完成，保持实际原记录号、背景、原生页面及等待协议。只保留原 parser 正在消费的中性输入，没有独立页面快照或 DisplayPlan。

设置、游戏行为、ANC写入、原英文业务字段、随机选择、单位、输入和配置保存均未改动。没有新增缺项兜底、回退、保护分支或推测字段。

## 读到的既有待整改项

| 文件与位置 | 影响及状态 |
| --- | --- |
| `docs/design.md` 的历史先祖段落、`docs/evidence/ancestors-static.txt:31` 起 | 旧版排除纪念页及 DisplayPlan／固定位置建议与本轮范围或现行规范冲突。历史文档已标明过时；本记录取代其纪念页范围结论，历史错误建议正文仍待清理 |
| `modules/adapter/native_component_binding.cpp` 的历史 fields／组件集合、`native_ui_scene.cpp` 的 Child／Container、`native_renderer_component_binding.cpp` 的 Owner.children | 其他页面的历史来源／布局集合及序列化仍待继续审查和退役。本轮纪念页不加入这些坐标组件，不能由本次交付宣称其余页面全部合规 |
| `modules/adapter/native_footer_component.cpp` 的署名间距、`module.cpp::enter_component_paint` 的 About 按钮中心例外 | 既有 Mod 排版仍影响原生所有权，待整改，本轮不调用或扩展 |
| `modules/adapter/windows_inventory.inc::native_text_limit` | 既有消费者侧截取／点号逻辑影响原生截断所有权，待整改；本轮纪念页不使用 |
| `translations/build-message-catalog.ps1::Read-LiteralBytes` | 既有全量生成器仍使用旧版绝对文字地址，3.89.1映射待整改；本轮使用只更新本轮命名空间的纪念页生成器 |
| `translations/messages_embedded/values.calendar.zh-CN.tsv:27` 起及 `windows_message_calendar.inc::moon_call` | 旧 moon 词值列出公历月份，与 `15E910` 实际 MONTH_NAME 资源不符，影响该旧消息来源的月相翻译，待整改；本轮纪念页使用实际13个月名及65种完整月相，不使用错误条目 |

## 编译与正式发布

源码、作者清单、生成词库及3.89.1构建适配已保存。根统一队列完成一次配置、一次增量构建及正式兼容业务热发布；Adapter 四个依赖源文件重新编译并链接，Catalog 目标完成、DLL 内容未变化。完整日志只有既有函数指针转换、extern 初始化、缺失成员初始化、缩进及未使用项警告，没有编译错误。提交后至所属批次完成未修改本请求范围的源码。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 实际回执 |
| --- | --- |
| 请求 ID | `14396d0c70d14591a34b32aa7de8fe58` |
| 批次 ID | `4976348e95c340b0ae66fdea8f8e659d` |
| 请求结果 | `build/.compile-queue/results/14396d0c70d14591a34b32aa7de8fe58.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true`，已读取 |
| 完整日志 | `build/.compile-queue/batches/4976348e95c340b0ae66fdea8f8e659d.log`，已完整读取 |
| 正式事务 | `84f7495233654fa4a62eb75b27db0030`，2026-11-11 14:15:36（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/84f7495233654fa4a62eb75b27db0030/publication-result.json`，`success=true`，目标 `applied=true`，已读取 |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/profiles/urw-3.89.1-steam-26139145.json`、`package/release.json` |
| 旧件回收 | `回收/20261111-141534-84f7495233654fa4a62eb75b27db0030/package/`，四件旧文件先归档后替换，保留原相对路径，均已只读确认存在 |
| 当前进程交接 | 原宿主 PID `3275331 urw.exe` 对应同一 Windows PID `364`；`ReadyToPublish` 后返回 Catalog 第6代、Adapter 第7代 `Applied` |

| 文件 | SHA-256 |
| --- | --- |
| Adapter：正式件／构建输出／Applied 一致 | `fbbd7b73815c5281080240145bcd1a331d8355eebc2bf189f02b5efae78e87cf` |
| messages.tsv：正式件／源码词库一致 | `3e0626de031eabfc1c95334ef0cd8a01c66adc3b408f20b6b3d27aeba2756415` |
| 3.89.1 profile：正式件／源码一致 | `68329b5cf3fabc3436802f1211e7396646ca4c68be5418dd6f828dda14c857e3` |

上述文件身份与正式 `package/release.json` 对应条目一致。根 `uwcn_launcher.exe` 继续消费同一正式包，未创建平行运行副本，未要求用户手动卸载或重启。原 PE SHA-256仍为本记录首段值。

源码修改、产物编译、正式文件发布及当前进程兼容交接分别完成。`Applied` 仅证明模块交接；未运行画面测试、模拟操作或自行启动游戏，未创建测试用例、测试脚本或断言。实际画面待用户查看。
