# 百科首页原生目录记录恢复

日期：2026-11-10（Asia/Shanghai）。依据用户提供的英文／中文首页对照图，读取本机原始 `GAME.NFO`、译文和 `build/analysis/windows-3891-native-full.asm` 静态分析。没有启动或操作游戏、模拟输入、运行产物、执行或编写测试、添加断言或保护／回退／兜底逻辑。

## 原因与原生边界

前次 [链接编码修正](20261110-encyclopedia-link-encoding.md) 消除了 F5 重载后度量失败，用户新图中的蓝色链接和选择框已经跟随中文；但译文本身早已改变原生目录结构，该次未修正这一独立问题。

原始 `GAME.NFO` 第6–9、11–17、19–25行共18条目录记录，分别用逐行文字、连续空格和 `<br>` 组成两栏／三栏主题组。第6、11、19行是普通分类标题；其余15行包含原生主题链接。没有独立列控件或隐藏的分栏指令。

旧 `translations/encyclopedia.zh-CN.tsv` 的 `6-9 / 11-17 / 19-25` 三条合段译文，把每组分类标题及全部链接改成一条或数条横向句子；`generate_encyclopedia.py` 的 passage continuation 规则随之把后续同组记录置空。`catalog/zh-CN/cultures.tsv::culture.record.80/302/716` 含全部合并内容，`.127/184/234/367..651/789..1055` 则不再输出原有目录行。分类标题中额外添加的 `{WORLD}`、`{CULTURES}` 也使“世界”“文化”成为重复链接。影响为目录压缩、分组及栏目消失；状态：本次资源整改完成。

原生 `3E054 → 3D820` 每条正文记录都进入同一文本流；`3D93A → 162300` 生成词表。`162323..16234E` 接受起始空格，`162488..1624D4` 将连续空格的非末字节保存到词元，末空格只推进词元。原版目录的行与空白属于源文本语义；换行、光标和链接仍由原生方法消费。

中文路径的 `windows_encyclopedia_tokens()` 合并 ASCII 分词空白，`windows_culture_display()` 删除这些空白，`we_space_text` 跳过其额外可见推进。因此只把三条合段拆开、仍写普通 ASCII 排印空格，不能恢复原文的预格式空白。

## 资源修改

将上述三个区块拆回18条独立源记录，保留各条原生 `<br>`、原有空白段落、八个分类与全部33个独立主题链接。分类使用“世界背景／神话传说／自然／文化主题／生计／角色／物品／战斗”；分类标题不再借用主题链接。链接仍保存 `{THE BEGINNING}` 等完整英文身份。

译文以中文全角空格 `U+3000` 表达原有预格式目录的排印空白，分类星号和条目前导点采用全角字符。它们是源记录里的文字字符，随同记录被编码、分词、测量和绘制；没有新增坐标、列宽、行槽表或页面布局代码。全角前导点也不会被 `windows_encyclopedia_match()` 当作多词别名内部的 ASCII `.`，各别名边界保持完整。

`U+3000` 经 Layout 生成完整双字节 transport；现有词元入口保留该字元，原生 `3DBA1 → 10E5A0 → 10E700` 和 `windows_culture_width()` 消费同一真实字体 advance。`FontEngine::text_width()` 使用字体自身的空白字宽，空白无墨但参与原生推进。Catalog从正式词库收集它及全角符号进入字形 repertoire。没有另建制表算法，也没有向选择框、命中区或缓存反写 Mod 布局。

编辑源 `translations/encyclopedia.zh-CN.tsv` 与现有18项 `culture.record.*` 同步。没有运行全量生成器：它当前只保留部分 UI／文化键，而正式词库另含后续补充的主题概述；本次仅沿其已确认 FILE 偏移身份更新首页值，没有删改其他词条、主题索引或链接表。此生成器保留范围问题仍待整改。

这是恢复原版的分组、逐行目录及源空白语义，不代表已运行核验各列像素与英文图完全对齐。字体度量、原生自动折行、行距、链接控件及原生缓存继续拥有输出结果。

最终资源静态复核：18条源译文与对应 FILE 偏移词库值一致，33个完整英文链接身份均有效且不重复。按已确认 transport 编码及花括号转换计算，最长记录为128字节（源身份20／`record.789`），全部低于180字节现有分片界限及200字节原生输入／前缀缓冲。中文和排印空白的分词边界继续由现有编码规则完整传递，没有新增容量分支或测试脚本。

## 既有待整改边界

- 前次 [编码记录](20261110-encyclopedia-link-encoding.md) 的 Linux 合串度量、宿主错误透传、历史 Footer／Scene 结构仍待整改，本次未扩大对应实现。
- `docs/evidence/20261019-encyclopedia-complete.md` 的完整译文及已发布范围不能证明本首页结构正确；旧三条合段虽曾编译发布，仍与该原生目录源结构不符。本次纠正源译文及正式词库，交付状态另记。

## 交付状态

源译文及词库修改已保存，通过根统一队列完成一次配置及增量构建检查，Adapter与Catalog目标均完成。本次仅修改数据，两份DLL沿用已有编译产物、内容未变化，没有重新编译或链接，也未替换DLL正式文件。正式词库及清单发布、兼容业务热交接均已完成，时间为2026-11-10 16:30:36（Asia/Shanghai）。已完整读取请求结果JSON、批次日志、正式发布JSON，并只读核对新旧词库及清单身份。未运行或做画面验收。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Publish -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `2833cdb37c1440589443a147209c740e` |
| 批次 ID | `cd0f9fd63e3448b78b3f206b3de6d09f` |
| 请求结果 | `build/.compile-queue/results/2833cdb37c1440589443a147209c740e.json`；`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 批次日志 | `build/.compile-queue/batches/cd0f9fd63e3448b78b3f206b3de6d09f.log`；两目标完成，无警告或错误 |
| 正式事务 | `8c1d217a4599478ca3ed2afa49b7202e` |
| 发布结果 | `build/mingw-x86/stage/8c1d217a4599478ca3ed2afa49b7202e/publication-result.json`；`success=true` |
| 正式替换 | `package/catalog/zh-CN/cultures.tsv`、`package/release.json` |
| 旧件归档 | `回收/20261110-163035-8c1d217a4599478ca3ed2afa49b7202e/package/`，两件均按原相对路径保留 |
| 热交接 | Windows PID `364` 返回 `ReadyToPublish` 后 `Applied`；Catalog第5代、Adapter第6代，无需退出或重启 |

新词库源码、正式件和发布清单 SHA-256 均为 `dd9f4072b8de45d989a77625b063bbfad1686aa427cf5813a350058e9686aa4e`；归档旧词库为 `3e57922ef476e7f5c36148214fecaebf703406c147c0f0a19ad72c2f09503cba`。正常启动路径仍为根 `urwcn_launcher.exe` 及相邻 `package/`，没有独立修复包或平行副本。提交后至本批结束未继续修改请求范围数据。

已打开的百科通过既有语言失效和原生输入返回边界完整重建，重新读取这些源记录并生成原生链接及控件；没有发送输入或以重启刷新。Applied仅证明发布事务完成，不能代替画面验收。
