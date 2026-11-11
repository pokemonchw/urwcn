# 主菜单汉化署名错位与版本分行

2026-11-11。用户截图显示 Byayoi 署名、长版本和原版权重叠，随后明确要求仍放右侧，版本标签与号码分行，并指出右侧仍有空白。本轮不启动、关闭、重启或注入游戏，不读取进程画面或游戏内存、不模拟输入、不运行产物或测试，不创建测试用例、测试脚本或断言。只读进程清单与既有兼容发布协议用于确定交付目标。

对象为 Windows x86 不真实的世界 3.89.1 / Steam Build 26139145。原 PE 为 `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。以下使用 RVA；[磁盘原生指令](20261111-footer-alignment.asm)使用基址 `00400000` 的 VA。

## 原因与本轮修改

原 `native_footer_component.cpp::paint` 对两行分别测宽，以最长行确定整列左边缘，再把社区署名与版本一起交给左对齐的 `10EB40`。这会使新增日期后的长版本向左扩展，侵入原版权范围；较短的社区署名也不与上方图像共用中心。该路径与版本来源修改相互独立，不能以此前编译成功证明排版正确。

- `main.translation_version` 改为 `汉化版本<br>{value}`。完整编译小时及五位指纹保留，不截短版本。加上社区署名后共有三个语义段。
- 新增署名组件进入完整原 `10E910` 居中排版函数。Mod 不保存行坐标或逐行调用文字绘制器；原生分词、行宽比较、行距推进、逐行居中及 `10E5A0` 的描边/光标/即时字形链继续执行。三行与图像使用同一个中心。文本测量与原生绘字期间使用同一 outline 作用域。
- `10E93C → D4430` 以空格分词，因此临时输入将已有 `<br>` 语义标记隔成独立词元。原 `10E910` 不识别该标记；仅在新增 `footer_centered` 作用域内，已有 `10E9FB` 度量扩展将 `<br>` 投影为空的下行起始词，并使原 `10EA01` 比较进入完整原生换行分支。`10EA61..10EACB` 原有流程完成当前行居中、绘制、读取 `1E6ABC` 行距、推进与复制空的下行起点。普通候选词和其他居中文字组件沿既有度量语义；没有生成输入或增加假设性失败分支。
- 外层锚点不再锁在开发者页脚面板的右边缘，改取当次原生 Root 的实际宽度及原有图文间距。`125AA7/125AAC → 125AD9 → 1127C0` 明确提供原生背景高、宽；Root 已持有这次实际构造输入，源码不写入截图像素或固定页面坐标。版本拆行也减少了这条既有自然宽度路径向左扩展的距离。
- 原出品、版权、作者、图标和菜单动作保持各自原生调用。新增资源的普通构造与语言重绘仍使用同一个 `paint`；组件保存格式、Source handles、Host ABI、驻留桥和 HookSpec 不变，可使用既有兼容业务热发布事务。

## 审查发现和仍待整改项

本次完成三行语义、原生逐行居中和右侧锚点修正，不宣称整个旧页脚框架已符合原生所有权要求。

| 文件与位置 | 影响 | 状态 |
| --- | --- | --- |
| 修改前 `modules/adapter/native_footer_component.cpp:97` 起 | Mod 测宽并自行决定自然列宽、外层锚点及图文间距，原版权未参与同一个原生分配过程。 | 行内排版改为完整原生 `10E910`；当前 `paint_text:61..87` 的外层自然宽度与图像锚点仍是旧署名机制的布局归属欠项。原生跨组件区域分配接口尚未确认，继续待整改，不以本轮发布认定合规。 |
| `docs/design.md:19`、历史 `main-menu-branding-static.txt` | 固定行槽、DisplayPlan、Present 合成与当前约束冲突。 | 历史正文仍待清理；不得复用。 |
| `20261019-footer-help-neutral-sources.md` 的署名部分 | 记载的两行、`162300/10EB40` 新增段落链已不适用于本次三行署名。 | 本次文字链以本记录为准；不据历史发布事实推定本次效果。 |

没有新增固定坐标表、行槽表、页面中文快照、字形延后重放、像素跟踪、Present 叠字、保护或回退。字体缓存仍只持有字形及其度量/覆盖，不持有 UI 位置。

## 交付状态

源码修改、Windows 产物编译、正式文件发布和当前进程兼容交接均已完成。统一队列执行一次配置和一次增量构建，提交后至所属批次结束没有修改提交范围源码。完整日志保留既有函数指针转换、extern 初始化、成员初始化、未使用项及缩进警告，没有编译错误。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 352 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 实际回执 |
| --- | --- |
| 请求 | `4548b01021054ea68af1b563e1d6f75b` |
| 批次 | `1320bcfb775042e3b5a4740dab6850d7` |
| 请求结果 | `build/.compile-queue/results/4548b01021054ea68af1b563e1d6f75b.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true`，已读取 |
| 完整日志 | `build/.compile-queue/batches/1320bcfb775042e3b5a4740dab6850d7.log`，已完整读取 |
| 正式事务 | `42e02acdf5754308af132df55cf62b61`，2026-11-11 14:56:30（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/42e02acdf5754308af132df55cf62b61/publication-result.json`，`success=true`、`runtime_requested=true`，已读取 |
| 正式变更 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/main_menu.tsv`、`package/release.json` |
| Adapter SHA-256 | `f7389dddbeeb274f52c9238e10abc19862b158b6297741e99925e8ed60566cee` |
| 中文主词库 SHA-256 | `1048498bcab5da3ec07872ce9ca56404dd33e7fd60a28572aad6daa5537bcad7` |
| 旧件回收 | `回收/20261111-145628-42e02acdf5754308af132df55cf62b61/package/` 下保留上述三个旧文件的原相对路径，已读取清单 |
| 当前目标 | 宿主 PID `3327255 urw.exe`；既有 Proton Mono 解释器只读枚举为 Windows PID `352 urw`；宿主模块映射确认其加载本项目正式包 |
| 驻留交接 | `ReadyToPublish 42e02acdf5754308af132df55cf62b61`，随后返回 Catalog 第2代及 Adapter 第2代的 `Applied` |

正式 Adapter 与词库身份已只读核对发布清单，Adapter 与 Applied 中哈希一致。Catalog DLL 内容未变，词库变化使 Catalog 在同一事务内重新加载。编译小时仍为 `2026.11.11.14`，文件内容未变，因此本次未替换时间文件。原正式根启动器及驻留库沿用，没有平行修复包。Sprite 的目标域同时改取既有原生主面构造输入，与文字使用相同密度来源。

Applied 只证明兼容业务交接，不代表画面验收或上节所有权欠项已整改。没有自行测试、启动/关闭/重启/注入游戏、模拟输入或运行交付产物。
