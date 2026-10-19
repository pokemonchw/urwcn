> 历史记录：下述 17 主题、逐词显示与打开时固定语言描述已由 [百科修复记录](20261019-encyclopedia-complete.md) 的实现取代。旧发布回执保留，不能用作当前覆盖范围或刷新能力的说明。

# 文化信息译文来源与覆盖

本记录对应 Linux 版文化信息汉化。正文来自游戏安装目录 `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/GAME.NFO`，按 CP437 解码读取。游戏原文件未改写。

- `GAME.NFO`：178026 字节，SHA-256 `071f384ad992d0a688833693f207a5cf8a969b4811e5e6603597d189087a4d5d`。
- `gameinfo/urw_scrinfo.txt`：3049 字节，SHA-256 `c9e028d0fd0fe133d21bacb3c2bc708a10312ef4ca7816df89fda89a7499c6ae`。
- 新词库：`catalog/zh-CN/cultures.tsv`。包含 17 个主题标题、158 条正文读取记录、10 种可选文化摘要、65 个原生英文词的显示译名与 10 条界面文案。
- `src/linux/culture_word_keys.inc` 仅列出这 65 个 ASCII 原生词，用于加载显示词库；不保存中文正文、位置或页面布局。

## 主题清单

行号为原文件的 1-based 物理行号；偏移为主题标题首字节的十进制文件偏移。正文键另用具体正文记录的文件偏移，不使用表中的标题偏移。

| 主题键 | 原生主题及别名 | 原文范围 | 标题偏移 |
| --- | --- | --- | --- |
| `cultures` | `CULTURES / CULTURE` | 118–128 | 5456 |
| `eastern_peoples` | `EASTERN PEOPLES` | 285–287 | 13360 |
| `western_peoples` | `WESTERN PEOPLES` | 290–292 | 13455 |
| `kaumo` | `KAUMOLAISET / KAUMO` | 297–313 | 13588 |
| `kiesse` | `KIESSELÄISET / KIESSE` | 318–331 | 14557 |
| `driik` | `DRIIKILÄISET / DRIIK` | 336–350 | 15577 |
| `reemi` | `REEMILÄISET / REEMI` | 355–363 | 16517 |
| `sartola` | `SARTOLAISET / SARTOLA` | 368–381 | 17034 |
| `islanders` | `ISLANDERS` | 386–391 | 17862 |
| `koivula` | `KOIVULAISET / KOIVULA` | 396–406 | 18263 |
| `northern_peoples` | `NORTHERN PEOPLES / NORTHERN TRIBES` | 410–422 | 18825 |
| `kuikka_tribe` | `KUIKKA-TRIBE` | 427–432 | 19451 |
| `owl_tribe` | `OWL-TRIBE` | 435–442 | 19803 |
| `seal_tribe` | `SEAL-TRIBE` | 445–452 | 20216 |
| `njerpez` | `NJERPEZIT / NJERPEZ` | 456–464 | 20598 |
| `language` | `LANGUAGE` | 467–475 | 21303 |
| `language_inflexions` | `LANGUAGE INFLEXIONS` | 478–496 | 21704 |

覆盖文化总述、三大民族分组、十种可选文化、涅尔佩兹人，以及文化命名和词形说明。族名沿用 `main_menu.tsv` 的既有译名；涅尔佩兹一名沿用 `world_hud.tsv`。`ango` 根据本文件 `.ANGO.` 条目所述的长刃尖钩矛译为“安戈钩矛”。语言说明和词形表保留所讲解的原语形式，中文解释其含义；这不是遗漏的界面英文。

## 文本记录与链接身份

`culture.record.<offset>` 的 `offset` 为原生 `fgetstr(...,150,...)` 调用前该正文记录的文件偏移。词库中每条正文前的 `# GAME.NFO:<line>` 注释保留物理行出处。所覆盖的原文正文记录均不超过 149 字节，不发生本次读取容量导致的物理行分片。

每条译文承接原生单次正文调用，保留原来的 `<br>` 标记。中文按短语留有空格，供原生词表与自动折行使用；这些空格不指定坐标、行槽或目标宽度。正文不另建整篇显示计划。

原生百科在绘制与建立链接时将文字转为大写并匹配原始主题表，因此正文保留必要的英文主题词作为链接身份，`culture.word.*` 只在已确认的文字测量和显示边界提供中文。除民族名称之外，也保留 `HUNTING`、`FISHING`、`BLACKSMITH`、`WEAPONS`、`YEAR` 等原本可点击的主题。含变音符号的文化名在普通文化正文中使用同一原生主题已存在的 ASCII 别名 `KIESSE`、`DRIIK`、`REEMI`；语言说明中保留原语词形。

`THE INEHMO` 与 `THE UNREAL WORLD` 仍保留完整原生短语；显示词库中 `THE` 为空字符串，`INEHMO` 为“伊涅赫莫人”，游戏名 `UnReal World` 保留原品牌。`LANGUAGE INFLEXIONS` 在显示时成为“语言 词形变化”，其检索身份仍为英文原主题。

## 公共界面文案

`culture.ui.title/home/exit/keyword/back/keyword_title/launch` 提供百科标题、首页、退出、关键词输入、返回主题以及文化介绍入口文案。按钮原英文位于 `urw3-bin` 的 `0x1e425b`（`HOME.Start page`）、`0x1e426b`（`%c-.Back to "%s"`）、`0x1e427c`（`ESC.Exit`）、`0x1e4285`（`SPACE.Type a keyword`）；百科总标题位于 `0x1e42cb`。

底部帮助来自 `gameinfo/urw_scrinfo.txt:16–19` 的 `.ENCYCLOPEDIA.` 条目，三行说明高亮主题、方向键与 ENTER、鼠标点击，以及自由输入关键词或主题搜索。对应 `culture.ui.help_1/2/3`；没有改动原输入动作或搜索规则。

## 状态

本文只记录词库与静态来源。源码接入、编译产物和正式发布由主任务分别记录，不能以本词库存在认定界面已更新。没有启动游戏、运行产物、测试、编写测试用例或添加断言。
