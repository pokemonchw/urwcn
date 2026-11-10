# 帮助与游戏选项菜单漏译

日期：2026-11-10。用户截图对应 Windows 3.89.1 的 ESC 菜单，标题及全部选项仍显示英文。本次只阅读截图、原生反汇编和源码；没有启动游戏、模拟输入、自行测试、创建测试用例或断言。兼容业务更新使用已经授权的正式热发布事务。

## 原因与原生边界

静态来源为 `build/analysis/windows-3891-native-full.asm`，原 PE SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`，下述地址均为 RVA。

`108730` 从原生 `FFAA0` 清空上层菜单，随后依游戏状态构建实际选项，`108AE0 → 1002B0` 显示菜单。原行表为 `619F988`、stride `20C`，动作在行 `+C8`。`1089D7/1089E7` 依次写入百科标签和 F1 前缀；`108A87/108A97` 同样写入保存标签和 Ctrl+S 前缀。原生构建和条件保持不变。

`windows_message_menu_echo.inc` 之前已从这些实际构建点保存中性消息来源，并有 `menu.title` 和 `menu.label` 译文，但只在 `100846` 等消息回显边界使用。它没有将语义交给真实菜单消费者，词库存在不能证明画面已接入。原证据表基于3.89的只读数据地址；3.89.1的实际指针由当前反汇编确认，不套用旧表的绝对地址。

| 完整原生调用 | 已确认职责 |
| --- | --- |
| `1003B8 → CF790` | 使用实际英文标题构建原生 Menu，kind 为6 |
| `10042B → CF990` | 逐个将上层原始行复制到 `5F4EF10`、stride `E8` 的真实菜单记录 |
| `10048C/10049B → CF990` | 原生空分隔行及 `ESC.Cancel`，动作27 |
| `100525 → CFFB0` | 完整绘制原菜单、背景、标题和各行 |
| `D027F → 10E5A0` | kind 6 的原生标题显示 |
| `D02EC..D02F9`、`D031F → 114680` | 原生先检查行中点号，再用实际动作前缀绘制键帽与后缀 |
| `1149D9..1149F9 → 10E5A0` | 完整点号后缀显示，键帽字母及动作值不进入翻译 |
| `D07FB/D0A49` | 两个原生选择框路径的既有完整行度量扩展 |

## 实现及生命周期

`modules/adapter/module.cpp::bind_menu_consumer_source` 在完整原生菜单消费者上，以原生 header `5F54A38` 的实际英文标题识别这一语义界面，将标题绑定到 `message_value/menu.title`，将每个实际动作行的点号后缀绑定到 `message_value/menu.label`。使用已有 `native_menu_component` 的中性资源接口，原生行及英文数据不改写；当前真实键帽前缀由同一行保留，没有按键、行序或位置映射表。空分隔行不参与翻译。退出项随原业务状态选择“退出游戏”或“退出并选择是否保存”。

标题和标签沿已有语言解析、双字节文字传输、完整原生度量与叶字形调用消费。`D031F` 键帽维持原ASCII解析，中文完整后缀进入原生 `10E5A0` 的字形接口。既有选择框度量解析同一 Menu 的当前语言资源；未只向按字节路径传 UTF-8。高清字形继续在已确认的主表面实际密度及原生组件文字调用中即时生成，沿现有 `native_targets::promote` 主画布所有权提交；没有新增目标、低分辨率文字放大或提交前叠字。

资源在普通原生绘制时绑定并进入已有 Menu 源保存/恢复，缓存物化使用已有资源。已打开的旧英文 Menu 在本次兼容交接后，由现有 `native_parent_cache_language::menu` 对 `100645` 的完整父/菜单构造重新消费同一真实 header/rows，绑定新语义；原有选择及输入循环保留。语言切换也沿这条完整构造路径，不新增输入循环、全页字段快照、DisplayPlan、坐标表、像素跟踪或绘制贡献序列。未修改保存格式、驻留桥、ABI 或 Hook 编号。

词库新增 `menu.label / Cancel / 取消`，同时同步生成词库 `catalog/zh-CN/messages.tsv` 的对应单条UTF-8十六进制键；其他已有译文直接复用。没有对新版PE运行使用旧版固定文字地址的完整词库生成脚本。

## 既有待整改项

- `modules/adapter/native_footer_component.cpp:88` 起的 `paint` 仍由 Mod 计算署名宽度、x及间隔，影响主菜单译者署名，不符合原生布局所有权要求，仍待整改；本次菜单不调用或扩展此路径。
- `modules/adapter/native_ui_scene.cpp:12` 起的 `Child/Container` 历史组件集合及序列化仍保留，完整退役待处理；当前语言更新不遍历其不完整集合重绘。本次不向其增加菜单布局或文字贡献。

## 交付状态

源码与词库修改已保存，通过根统一入口完成一次配置及增量编译；Adapter 重新编译并链接，Catalog 目标完成、DLL内容未变化。保留20条既有函数指针转换、extern初始化、未使用函数/参数及缩进警告，无编译错误。已完整读取请求JSON、批次日志、正式发布JSON及旧件归档。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `6c6487576b98497da149a3e85b3a35c3` |
| 批次 ID | `20987aaafa1a43cda16bb38e6b74ca03` |
| 请求结果 | `build/.compile-queue/results/6c6487576b98497da149a3e85b3a35c3.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 完整批次日志 | `build/.compile-queue/batches/20987aaafa1a43cda16bb38e6b74ca03.log` |
| 正式事务 | `e9a2e0d1a3c84c679a5419b17962f268`，2026-11-10 16:09:42（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/e9a2e0d1a3c84c679a5419b17962f268/publication-result.json`，`success=true`、`applied=true` |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧件归档 | `回收/20261110-160940-e9a2e0d1a3c84c679a5419b17962f268/package/`，保留原相对路径 |
| 当前进程 | 宿主 PID `2974827`，Windows PID `364`；只读进程表与既有 Proton Mono 解释器枚举取得 |
| 热交接 | `ReadyToPublish` 后 `Applied`，Catalog及Adapter均为第2代 |

| 文件身份 | SHA-256 |
| --- | --- |
| 新 Adapter，正式件/构建件/发布清单/Applied一致 | `2f8bb901d3bacfcde6e292a4de5b77b6553753a0f161659612c080db8ac29001` |
| 新 messages.tsv，源码/正式件/发布清单一致 | `cafcf171e05fb57148e4cba2e8ce97d81d5dd44914673da5965ec4cb8ffde013` |
| 已回收的旧 Adapter | `bd0508d45e40937ea993b2810f2ddf871f0e02b80670cc2823752b8569386cd4` |
| 已回收的旧 messages.tsv | `90cc90598990287a811399ebc25fef3482c05b16029e20feac5cb9729f4ed184` |

源码修改、产物编译、正式位置发布及当前进程兼容交接均已完成，根 `uwcn_launcher.exe` 正常入口消费同一正式包，没有平行运行副本。未启动、关闭、重启或模拟操作游戏，未运行测试、创建测试脚本或断言。视觉效果由用户验收，Applied仅证明模块交接。
