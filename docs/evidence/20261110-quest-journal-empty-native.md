# 任务日志标题与空任务提示漏译

后续用户报告：本批次的标题与正文汉化已接入，但空任务页的语言切换／卸载刷新存在既有返回地址识别错误，不能将本批次 Applied 当作这两项功能正常的证明。静态根因与后续交付见[任务日志等待修正](20261110-quest-journal-wait-language-fix.md)。

日期：2026-11-10（Asia/Shanghai）。用户截图为 Windows 3.89.1 的任务日志空列表。此前 `native_quest_menu_language.inc` 接入了完整构造和语言切换，但没有给原标题、两段空列表正文绑定中文。此次仅静态阅读截图、源码、磁盘 PE 及反汇编；未启动或操作游戏，未模拟输入、运行测试、创建测试用例或断言。兼容业务热发布使用已授权的驻留事务。

## 已确认的原生边界

原 PE 为 `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。以下为 RVA，逐指令摘录见同目录 `20261110-quest-journal-empty-native.asm`，源为 `build/analysis/windows-3891-native-full.asm`。

| 原生边界 | 静态语义 |
| --- | --- |
| `157DD3 / 158D99 → 113550` | 详情、任务列表共用的原生标题构造；原纹理 owner 为 `A220EF4` |
| `1135AB → 1166C0` | 原标题带完整组件；ECX 为 renderer、EDX 为 x，栈依次为 y、width、height、空标题、flags、color |
| `1135B0..1135C1 → 10E260` | 原版另以固定英文位置绘制 `1CC6F8` 的 `QUEST JOURNAL`，outline=1 |
| `115AD0` 的 mode 5 | 原 `115E3C` 跳转表第5项为 `115B24`；游戏已有的同款标题带组件，`115B24..115B3F` 使用原输入构造同一 `1166C0`，`115B59..115B73` 计算标题居中，`115E20..115E2C` 按原文字调用绘制 |
| `15928B → 10E260` | 原空列表第一行完整文本，参数1指向 `1CC858`，原 style=0 |
| `1592DA → 10E260` | 原空列表第二行完整文本，参数1指向 `1CC888`，原 style=0 |
| `157DA9 / 158D6F → SDL_CreateTexture` | 两处原详情／列表目标创建；实际返回地址 `157DAF / 158D75`，原输入为格式、access、width、height |
| `1592E8 → 10B480`、`159313 → SDL_RenderPresent`、`159330 → D3C80` | 原生提交、呈现与继续等待；保持原生命周期 |

直接从 PE 只读节读取三段完整原文，并加入 `quest.journal` 词库域：

| 原文 | 中文 |
| --- | --- |
| `QUEST JOURNAL` | 任务日志 |
| `You are not currently involved in any quests.` | 你目前没有正在进行的任务。 |
| `Quests may come in your way by talking and interacting with people.` | 与人交谈和互动，可能会获得任务。 |

## 实现与所有权

`modules/adapter/native_quest_menu_language.inc` 在 `1135AB` 借用当次原生 renderer、x、y、width，将中文标题交给原生 `115AD0` mode 5，同步完成原标题带和标题；随后跳过 `1135C1` 那次旧英文标题绘制。标题居中继续执行原生计算，复用 `windows_renderer_text.inc` 的 `115B59` 完整字形度量扩展及 `10E260` 即时字形消费者。Mod 不保存原标题位置或标题带坐标，不另建布局。没有使用会复制整幅 `bg-rpanel.png` 的 `113430`，因此不改变日志湖景背景。

两段正文仅在各自完整原调用中临时借用中文，原英文数据保持，原生 x、y、颜色、style 及文本生命周期继续使用。调用返回立即结束借用。新增 Hook ID 为 `51F5..51F8`，保留既有 ID、HDA8 状态格式和驻留 ABI；这四个新调用点只按本轮已有完整静态依据的 3.89.1 注册。

`modules/adapter/native_targets.cpp` 将两个已确认目标创建返回地址接入既有 `make_component_texture`。由当次原构造参数和真实窗口输出密度建立同一原生目标，并复用既有目标选择、SDL 比例、逻辑尺寸查询、复制及销毁接口。中文字形在已确认的原 `10E260 → 10DE90` 组件文字调用中，按当前 renderer 实际比例光栅化后即时提交；不把低分辨率文字放大冒充高清。没有像素读取／比较／跟踪、中文绘制贡献记录、Present 前叠字或延后文字重放。

既有 `construct`、`menu`、`wait` 继续从存活原生父帧完整重建任务日志。热交接和语言切换自然重建原纹理并消费同一组新边界，不重新生成任务、不改变 count／索引／分页、任务数据、等待及退出动作。未增加持久页面字段、缓存集合或状态分节。

`translations/messages_embedded/values.quests.zh-CN.tsv` 与生成词库 `catalog/zh-CN/messages.tsv` 同步加入三条键。没有运行仍使用旧版绝对文字地址的完整词库生成器。

## 既有待整改项

- `modules/adapter/native_footer_component.cpp:88` 起仍由 Mod 计算主菜单署名布局，影响原生布局所有权，待整改；本次不调用或扩展。
- `modules/adapter/native_ui_scene.cpp:12` 起的历史 Child/Container 集合及其序列化仍保留，完整退役待整改；本次不添加页面快照或组件回放。
- `modules/adapter/native_renderer_component_binding.cpp:39` 起的历史 Owner.children 仍保留，完整退役待整改；本次任务日志由原生构造管理，不加入该集合。
- `translations/build-message-catalog.ps1:17` 起的旧版绝对字面量读取缺少 3.89.1 已确认映射，生成器适配待整改；本次仅同步三条本轮新增值键。

## 交付状态

源码与词库修改已保存，通过根统一队列完成一次配置、一次增量编译和正式兼容热发布。Adapter 重新编译并链接，Catalog 目标完成、DLL 内容未变化。保留既有函数指针转换、extern 初始化、未使用项及缩进警告，无编译错误。提交后至所属批次结束没有继续修改本请求范围的源码。请求 JSON、批次日志、正式发布 JSON 及归档清单均已读取。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `064df6c52eac4f349dae6e64040c1dcd` |
| 批次 ID | `8d2cd80652794f15a22a1f488e47c0dc` |
| 请求结果 | `build/.compile-queue/results/064df6c52eac4f349dae6e64040c1dcd.json`，`Success=true` |
| 完整批次日志 | `build/.compile-queue/batches/8d2cd80652794f15a22a1f488e47c0dc.log` |
| 正式事务 | `c64c8e7557b84a728ea432ab30aeb6ef`，2026-11-10 17:24:42（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/c64c8e7557b84a728ea432ab30aeb6ef/publication-result.json`，`success=true`、运行时 `applied=true` |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧件归档 | `回收/20261110-172440-c64c8e7557b84a728ea432ab30aeb6ef/package/`，三件旧文件先移入归档再替换，保留原相对路径，已只读确认存在 |
| 当前进程交接 | Windows PID `364` 返回 `ReadyToPublish`，随后 Catalog 第14代／Adapter 第15代 `Applied` |

| 文件 | SHA-256 |
| --- | --- |
| Adapter，正式件／构建件／Applied 一致 | `cbcb51f5748b4b6dd003f2ddcb65c376b50fbcc4343b83a3e84a7c0a26b64549` |
| Catalog DLL，正式件／Applied 一致 | `cd5ea4f63e239691176f6bf1e38a1b4c232a0c9c5f8182eb80aacefbfa8e6719` |
| messages.tsv，源码／正式件一致 | `4379b5851b7721b43b1ed7580010974ed60655016116c0cbbd7ef4aaa3e08012` |
| 归档旧 Adapter | `54c4beb8bb5703ba3cce6a39b785e9bc08c3da884950c2aecd1f942cf6c21f75` |

源码修改、产物编译、正式文件发布与当前进程兼容交接均已完成，根 `uwcn_launcher.exe` 继续使用同一正式包，无需重启。未自行启动、关闭、重启或模拟操作游戏，未运行测试或创建测试用例、断言；Applied 仅证明模块交接，画面由用户验收。
