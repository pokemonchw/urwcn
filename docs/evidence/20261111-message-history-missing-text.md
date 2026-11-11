# 消息日志固定资源、大小写与动物动态反馈漏译

2026-11-11。用户截图 `codex-clipboard-b942aaf0-aca2-4c70-8101-c64d42503eeb.png`，Windows x86《不真实的世界》3.89.1 / Steam Build 26139145。原 PE SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。下文代码位置为 RVA，原始反汇编为 VA、基址 `00400000`。

## 静态定位

前一轮 `windows_message_log.inc` 已接入原 `FE2B0`，但历史词库只从 embedded literal 派生，不包含 `urw_msg.txt` 等资源里已选定的完整句子，也未模拟原消息的大小写处理。固定消息有现成译文，不是字形缺失。

- `translations/messages/selected-templates.zh-CN.json`：`CANT_PICK_UP`、`DO_FALL_PRONE:PC`、`RISE:PC`、`NOT_TIRED`、`WIELDING_NOTHING`已有完整译文；这批来源此前没有导出历史正文键。
- [原生大小写指令](20261111-message-history-case-native.asm)：`F6664..F6789` 使用原 `toupper`、前缀集合 `#!+?:&,=_()1234567890 `、分句标点 `.!:?` 和小数点后的数字判断。原提示中的 `mod_menudef_*.txt` 实际入日志为 `mod_menudef_*.Txt`；宠物旧版命令提示的 `! key command` 实际为 `! Key command`。旧历史键无法匹配这些原生结果。
- `3633C..36357` 选择 `OUT_OF_ITEMS`、以原 `593C10` 的 `drink` 实参格式化 `%s`，再调用 `F6510`；饮水提示不是一个 embedded literal。原 `urw_msg.txt:258` 为 `!You don't have anything to %s.`，复用 `action/drink → 饮用`。
- `2DF9E → 76C0` 取得原 terrain；`2DFBA` 生成 `There is %s here and `，后续原追加器加入 `you take a closer look at this area.`。词库的 `terrain/field → 田地`进入完整历史句式；截图是 `field`。
- `1431D0`、`143340`、`AD4F0` 和 `1002B0` 已有完整反编译，见 [动物菜单记录](20261111-animal-commands-native.md)。菜单回显是 `#%s: %s` 的完整结果；命名提问由 `AD4F0(actor,6)` 及 `?What do you want to call %s?` 构成。`SOUND_NORMAL` 的可见分支为 `{<npc_sound>}<npc_defdesc> [SND_PRES:<npc_sound>].`；28个 `SND_PRES` 词形已有中文。

只读现有 `AAA/msglog.txt` 进一步确认与截图相同的完整来源：`Cow: I shall name you...`、`the cow`、`the cow called 猫猫`、`the cow called aa` 以及 `猫猫 bellows.`、`Aa bellows.`、`母牛 bellows.`。旧名字已不一定存在于当前动物记录中，不能通过当前专名字段查找来确定历史名字。原文件未改写。

## 实现

`translations/build-message-catalog.ps1 -ExistingLiterals` 为没有未展开标签/格式参数的已选资源导出历史正文，并为 embedded literal 与上述资源添加原生分句大小写身份。原有字面量译文优先于同文资源，原96768项保留原键值；增加972项，总97740项，包括28个声音词形与9个完整语法资源。

`windows_message_history.inc` 在完整历史正文上使用上述已确认构建语法：命名提问、单只/群体动物菜单回显、声音反馈、地形查看和饮水提示。词义只来自原 `npc`、`terrain`、11个原动物菜单标签、原 `drink` 和28个声音选择词。称呼复用原冠词、`%s called %s`、`%s the %s` 及裸专名分支；专名是原日志实参，不查询当前对象、不逐词替换句子。没有新增游戏字段或重入动物动作。

通用 `Grammar` 构造器和完整匹配器仅增加显式来源表及实参解析函数参数，现有 conversation 默认表与解析行为保持。历史使用独立的不可变语法表；表中没有位置、行号、像素或整页内容。

`windows_message_log.inc` 的 `FE5F8` 真实宽度操作数和 `FE86E → 162300` 真实正文消费者使用同一个语义源。仍沿 `native_text_resource`、原生传输编码、实际中文字宽、原段落与已有真实目标密度字形接口同步绘制。70条记录、布局、翻页、缓存、窗口和按钮由原游戏管理。没有新增Hook、驻留ABI、持久状态字段或延后重放路径，可用既有兼容事务交接。

## 明确边界与待整改

- 本次语法覆盖上述静态构建来源，不代表所有资源展开后的历史句式均已接入。普通日志没有保存原格式实参身份，不能把解析后的结构宣称为取回原业务对象。
- 裸专名恰好与原物种描述完全相同时，旧日志文本本身无法区分两者，例如专名 `Cow` 与未命名动物描述 `Cow`。本次沿原描述的精确词义及裸专名分支消费文本，仍不能恢复这种已丢失的身份；该历史歧义待原生产者身份持久化设计确认，不能宣称全部历史专名无歧义。截图中的 `猫猫`、`Aa/aa`、`母牛` 均作为独立姓名实参保留。
- `native_generic_menu_language.inc:362` 的纯语言重建跳过文件重读，复用原生一/二行缓存标志；长记录切换语言的页选择问题仍待整改。正常读取的宽度与正文现已共享本次来源。
- `native_renderer_component_binding.cpp:47` 的 `Owner.children`，及 `:570`、`:672` 遍历组件重画，仍违反原生UI生命周期所有权，影响既有渲染owner重建；待整改。本次继续使用日志原组件的同步 native-owner 调用，没有向该集合添加新位置记录。
- `docs/design.md:19` 等历史固定坐标/DisplayPlan建议仍与当前约束冲突，影响设计读者判断；待清理，不能作为此次实现依据。

没有启动、关闭、重启或操作游戏，没有注入、模拟输入、运行测试或产物，没有新增测试、断言、保护、回退或兜底逻辑。只读源码、磁盘PE、既有反编译和日志，并生成静态词库；编译仅生成交付产物。

## 编译、正式发布与交接

源码修改、产物编译、正式文件发布及兼容业务交接均已完成。2026-11-11 17:55:44（Asia/Shanghai）完成，未运行画面验收。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 360 -WinePrefix /home/lulika/.local/share/Steam/steamapps/compatdata/2735482958/pfx -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 已读取回执 |
| --- | --- |
| 请求 | `b2e3b9ff748d4f90a091f0d47b937550` |
| 批次 | `521f941d15094037836402a7ccd4374d` |
| 请求结果 | `build/.compile-queue/results/b2e3b9ff748d4f90a091f0d47b937550.json`，Success=true，PublishRequested=true，ReloadRequested=true |
| 完整批次日志 | `build/.compile-queue/batches/521f941d15094037836402a7ccd4374d.log`，已完整读取 |
| 发布事务 | `ab00072e8ddf4ce5b58f07a7fb7d9056` |
| 发布结果 | `build/mingw-x86/stage/ab00072e8ddf4ce5b58f07a7fb7d9056/publication-result.json`，success=true，当前进程applied=true |
| 当前进程 | 宿主PID3385055、Windows PID360；ReadyToPublish后Catalog第4代、Adapter第6代Applied |
| 正式文件 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧件回收 | `回收/20261111-175542-ab00072e8ddf4ce5b58f07a7fb7d9056/package/`，三件旧文件先移入回收，保留原相对路径 |
| Adapter SHA-256 | `0ed81a8da6f18c998cbab643c175ca9eda16930682d95a0a3ab07b4e2f9ce658`，构建文件、正式文件、清单及Applied相同 |
| 词库 SHA-256 | `7eff2a7d604eef7c6d16bcec028a397d0441f895cdb6654356997915b1db6773`，源码词库、正式文件及清单相同 |

本请求一次配置、一次增量构建，沿用`build/mingw-x86`，没有清理或新建编译树。Adapter重新编译链接，Catalog目标完成、二进制未变，词库数据正式更新。原函数指针转换、extern初始化、未使用项及缩进警告继续存在；新历史文件没有编译警告。从请求提交至所属批次结束没有修改请求范围源码，没有重复提交编译请求。

根`urwcn_launcher.exe`继续使用同一正式包，无需重启；没有创建平行修复目录。Applied仅证明本次兼容交接完成，画面仍待用户查看，上述待整改项继续保留。
