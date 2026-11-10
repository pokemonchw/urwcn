# 目标选择窗口底部的生物切换提示漏译

用户的新截图中，标题、方向说明和 ESC／ENTER 已为中文，底部仍是 `[+]Next, or [-]Previous creature`。此前[全部文本提取记录](20261110-direction-dialog-all-text.md)枚举了窗口直接文字消费者，却未追入 `F7AB6 → 114A20` 的独立绘制函数，“全部文本已处理”的结论遗漏此分支，在此纠正。

对象为 Windows x86《不真实的世界》3.89.1。原 PE SHA-256：`c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。仅静态读取原 PE、反编译与源码；没有启动、操作或测试游戏，没有注入、模拟输入、测试用例、测试脚本或断言。以下代码地址为 RVA，提取文件保留 VA，基址为 `400000h`。

## 原生来源与显示边界

`F7A90/F7AAD` 只在 mode bit0 为1、原生可选生物数量 `65A9BC0h` 非零时执行 `F7AB6 → 114A20`。全 PE 的 E8/E9 目标枚举只有这一处 CALL，没有尾跳转或绝对函数地址引用。

完整依据：[原函数反汇编](20261110-direction-creature-hint.asm)，Ghidra提取位于本地 `build/analysis/direction-creature-hint-ghidra.c`；[统一只读反编译脚本](direction_dialog_Decompile.java)已加入此函数。

| 原指令／消费者 | 静态确认的语义 |
| --- | --- |
| `114A50..114A62` | 唯一原字面量 `VA 5A9F90`，完整复制 `[+]Next, or [-]Previous creature` 到真实局部缓冲 |
| `114A6F → D4430` | 用原 `[]<>` 语法初始化原生分词，原英文串与分类规则保持 |
| `114AA2 → strtok`、`114AAD` | 原分词序号递增；四个真实词元依次为 `+`、`Next, or `、`-`、`Previous creature` |
| `114B08/114B3D → strstr` | 原 `[%s]`、`<%s>` 区分键帽与普通提示，不按中文重新分类 |
| `114B64 → 10E5A0` | 完整普通提示，实际原串仅为 `Next, or ` 和 `Previous creature` |
| `114B7C/114B7E` | `SUB ECX,EDX / LEA EBX,[EBX+ECX*8]`，原字符串长度推进当前文字 X |
| `114B81/114B87` | 原生保存新的当前 X，供后续键帽及文字使用 |
| `114BF5/114C5C/114CC8` | 原键帽左端、重复中间片及右端，继续由游戏按原 `+`／`-` 长度计算 |
| `114CED → 10E5A0` | 原键帽内的 ASCII `+`／`-`，保持原字形与动作 |

不存在从 NPC 名字、物品名称或玩家内容生成这里提示的原路径。单一原串、两种普通词元及两种键帽的语义闭合。

## 本次修改

`modules/adapter/windows_target_help.inc` 新增 `18507` 的完整文字调用及 `18508` 的原宽度指令边界：

- `target_help.creature.next`：`Next, or ` → `下一个生物，或 `，保留分隔键帽前的末尾空格。
- `target_help.creature.previous`：`Previous creature` → `上一个生物`。

文字调用按原分词器的真实序号 `RVA 5F54BB0`（2或4）标识语义字段，以同一原生 CALL 的两个来源分别进入现有组件接口；序号来自英文输入分词，不是 Mod 绘制计数或页面行号。原英文缓冲、键帽语法及解析结果保持；只有完整文字绘制实参借入中文，并以原生颜色和描边进入既有实际目标密度的字形绘制。

宽度指令从同一真实 `[EBP-40Ch]` 原词元解析同一语义资源，以既有字体度量得到中文逻辑宽度；保留 ECX 的原长度差，只把 EBX 的原 `原X+strlen*8` 扩展为 `原X+实际字宽`。随后原 `114B81/114B87`、下一个键帽构造、原文字起点继续执行。原字体描边在逻辑字格外生成，`font_engine.cpp` 的固定逻辑 advance 不因 outline 改变，测量与当次字形共享同一字宽契约。

没有建立固定坐标／行槽表、缓存中文位置、改变按钮尺寸算法或让原生控件消费 Mod 布局；没有像素跟踪、延后绘制或 Present 叠字。未新增未知文本的保护、回退或兜底。普通原生构建、既有窗口完整语言重建及缓存保存都经过同一函数；上一批补回正文标题栈输入的修正继续保留。

## 已知旧实现边界

此前主窗口直接消费者清单遗漏该辅助绘制函数，影响本行汉化；本次已在原完整调用和度量边界整改。已有 `native_footer_component.cpp:88` 的主菜单署名布局、`module.cpp:475` 的 About 按钮居中例外，以及 `native_ui_scene.cpp:12` 的历史组件集合仍待整改；本次不扩展这些路径。

## 交付状态

源码、两条资源、统一队列编译及正式文件发布均已完成。只读进程记录显示截图所用的宿主 PID3088138 在18:54:01已退出，本次没有执行任何热更新；不推断该退出原因，也不把它归为用户操作。提交本批时没有游戏进程，因此仅请求正式文件发布，没有请求热加载或启动游戏。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Publish
```

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `001e077bfae64a2fa8c2fd4462437bf9` |
| 批次 ID | `1b3b8affce504ce98eac8e04e26c63ba`，`Success=true`，一次配置及增量编译；既有函数指针转换、extern 初始化、未使用项与缩进警告保留，无错误 |
| 正式事务 | `8284aabf6b5540d38d43b9dc96a843b7`，2026-11-10 18:57:41完成，`success=true` |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/catalog/zh-CN/main_menu.tsv`、`package/release.json`；Catalog DLL沿用原编译件 |
| 旧件归档 | `回收/20261110-185741-8284aabf6b5540d38d43b9dc96a843b7/package/`，按原相对路径先移动旧件，再放新件 |
| 运行中交接 | `ReloadRequested=false`、`runtime_requested=false`、`runtime_receipts=[]`，没有请求或取得 Applied |

已完整读取该请求 JSON、完整批次日志和正式 `publication-result.json`。根 `uwcn_launcher.exe` 仍使用同一正式包，没有平行修复目录。

| 文件 | SHA-256 |
| --- | --- |
| Adapter，正式件／构建件一致 | `b255665b40c9efec848e07cca11b5771176f1932f20a81a7eaeed0342c46f17d` |
| main_menu.tsv，源码／正式件一致 | `cb2877cdcec979becf8a66bbf5ff32114ef5415e8133b74491eff3dfe2da7b25` |

没有自行运行游戏或测试；实际画面与行为尚未验收，不把本次编译、正式发布或用户之前的截图当作修正后的运行证明。
