# 确认框按钮空白：恢复原生完整构建

日期：2026-11-11，Asia/Shanghai。用户截图确认：上一批正文已经显示“确定吗？”，两个按钮却只剩空框。首批 `Applied` 仅证明模块交接；此前[全部确认文本记录](20261111-confirmation-all-text.md)关于当前确认 Menu 可以单靠 `CFFB0` 恢复按钮的结论有误，本记录更正。

对象为 Windows x86《不真实的世界》3.89.1 / Steam Build 26139145；原 PE SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。本文使用 RVA，反汇编使用 VA，基址 `400000h`。只做截图阅读、离线反编译和静态审阅，不启动、关闭、重启或操作游戏，不注入、模拟输入、运行测试或创建测试用例、断言。正式兼容交接使用用户已授权的驻留事务。

## 原生依据与原因

[confirmation_AllText.java](confirmation_AllText.java) 追加五个原生组件函数，当前共取得32个完整函数的 C 输出；巨型调试分派的66处确认调用仍按原指令提取。原始输出位于 `build/analysis/confirmation-20261111/all-text-ghidra.c`，本轮七个核心函数集中在同目录 `buttons-ghidra.c`；原指令见[按钮构建与缓存边界](20261111-confirmation-buttons-native.asm)。

| 原生边界 | 实际行为 |
| --- | --- |
| `CFAF0`，`CFB95 → 114680` | 构建按钮时立即绘制背景、端帽、高亮和文字 |
| `CFBD4..CFC8B` | 保存原动作、位置、原生行宽和命中尺寸；既有中文字宽接口在此消费度量 |
| `CFCAC..CFCE5` | 无点号按钮只向菜单行写内部标识 `NOTEXTSPOT`，不保存可见的 `<Y>es` / `<N>o` |
| `CFFB0`，`CFFF4..D0024` | kind=100 时仅在标题含 `BORDERS` 时画边框；本确认框标题为空，直接跳到 `D03FD`，不绘制按钮 |
| `D03F3` | 原常规 Menu 最后的样式清理写入，空标题提前返回跳过此处 |
| `D1167..D118F`、`D120C..D1217` | 原等待先缓存完整已画屏幕，再按真实选择绘制选择框 |

上一版 `native_generic_menu_language::query` 在 `FB988/FBBE7` 结束重建，尚未运行 `CF790` 和两个 `CFAF0`；随后调用 `native_menu_component::paint`，误把普通 Menu 文字绑定当作按钮恢复。给 `NOTEXTSPOT` 行绑定中文不能令 `CFFB0` 进入不存在的按钮绘制分支。

同时发现 `native_menu_component.cpp` 的 `native_consuming` 只在 `D03F3` 回调结束，空标题提前返回会使它跨越真实调用保持 true，并能随旧模块保存状态传入下一代；这影响后续组件来源登记，随本次生命周期修正处理。

## 源码修正及当前窗口交接

`native_generic_menu_language.inc` 改为执行两个原函数各自的完整纯构建片段：

| 确认框 | 完整原生范围 | 构建内容 |
| --- | --- | --- |
| 普通确认 `FB8A0` | `FB938..FBA25` | 原 `%s` 复制、FIRST 保存、Panel、CF790、两个 CFAF0、空 Esc 行及参数清理 |
| Esc 视为确认 `FBB10` | `FBB97..FBC93` | 同样的原生构建，另保留原空格动作行 |

开始位置在原 `F6510` 提交之后，不重复提交问题、退出、保存、死亡或任务业务。既有同步 Query 桥继续从真实 D1120 帧取得已接受的完整问题和原查询 EBP；原片段仍消费其已确认的 `EBP-70h/-80h` 文本与矩形局部变量，没有新增文本快照或位置表。

新增 `5268/5269` 是 `FBA25/FBC93` 原 CALL 地址上的 inline 边界。重建期间，全部参数已平衡，直接返回同步桥，不进入第二个输入等待。普通构建期间，裸桥执行等价的“压入原 `FBA2A/FBC98` 返回地址，跳到原 `D1120`”，保留原寄存器和 flags。没有在异址重放相对 CALL，也没有把真实 caller 改为 Host After 桥。原等待据此继续识别实际确认 owner，Y/N、Esc、空格和后续结果分支保持。

当前等待使用完整构建产生的新 Menu，并恢复已有选择；不再激活旧查询 Menu 或调用其 `CFFB0`，也不在缓存保存前额外调用 `D0650`。共用协议回到原 `D1167`，由原生先缓存新按钮像素，再执行 `D1217` 的选择框及原 software/renderer 呈现流程。

移除 `bind_query_buttons`：可见标签仅在原 `FB9F5/FBA0E/FBC54/FBC6D → CFAF0` 消费，原构建器自己生成记录、尺寸和命中区。背景、端帽、布局、光标、高亮和缓存均归原生，不抄坐标或循环补画按钮。

`native_menu_component.cpp` 在同步 `CFFB0` 实际返回处结束 `native_consuming`，涵盖已经证实的提前返回；`native_language_redraw.cpp` 在已确认的 `D1120 → getkey` 返回边界 `D12B4` 结束前一 Menu 构建的绘制状态，使首批已保存的错误状态在父界面重建之前退役。没有更改保存格式、驻留桥或 ABI。

中文仍沿既有完整度量、双字节字形推进和真实主表面密度接口即时绘制。本次不增加字形路径、低分辨率放大、SDL 像素跟踪、绘制贡献或 Present 前叠字；词库无需变化。

既有所有权待整改项仍见[首批明确清单](20261111-confirmation-all-text.md#既有待整改项)：主菜单署名位置计算、About 按钮中心例外、历史 Scene/renderer children 和 `native_text_limit` 不因本批编译而视为合规；本批确认框不扩展或调用这些路径。

## 交付状态

源码及静态证据已保存；根统一队列完成一次配置、一次增量编译及正式兼容热发布。本批只请求 Adapter，头文件变化使其关联源文件按依赖重新编译；词库保持首批正式版本。日志保留既有函数指针转换、extern 初始化、未使用项、初始化缺项和缩进警告，无编译错误。提交后至批次完成没有修改所属源码。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 实际回执 |
| --- | --- |
| 请求 ID | `2735ae730453495991cde938012d1a99` |
| 批次 ID | `b977a39a0d0b4998bb7486b0a3f45be4` |
| 请求结果 | `build/.compile-queue/results/2735ae730453495991cde938012d1a99.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 完整批次日志 | `build/.compile-queue/batches/b977a39a0d0b4998bb7486b0a3f45be4.log`，已完整读取 |
| 正式事务 | `9c4b14b4fc2643c78a435fe419767b0a`，2026-11-11 13:09:42（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/9c4b14b4fc2643c78a435fe419767b0a/publication-result.json`，`success=true`、`applied=true`，已读取 |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/release.json` |
| 旧件回收 | `回收/20261111-130940-9c4b14b4fc2643c78a435fe419767b0a/package/`，两件先归档后替换，保留原相对路径 |
| 进程身份 | 宿主 PID `3275331`，既有 Proton Mono 解释器只读枚举得到 Windows PID `364` |
| 兼容交接 | `ReadyToPublish` 后返回 Adapter 第3代 `Applied` |

| 文件身份 | SHA-256 |
| --- | --- |
| 新 Adapter，正式件／构建件／清单／Applied 一致 | `43ce6be6c8907de579277a84959f6e61c20727394c6d3f8d118bb484686abe8c` |
| 已回收旧 Adapter | `7f0bca9acc9f8d0a179340a059dfa90487efe1578d50468babe2d8ec81d60d95` |
| 沿用 messages.tsv，源词库与正式件一致 | `9514d61399b1b302e456e0b125f42c923ebf3863e40c1f449536c3d421a00c44` |

对新 Adapter 只读反汇编确认两条普通输入裸桥均为 `push [原返回地址]` 后 `jmp [D1120目标]`，没有执行额外 CALL、寄存器运算或 flags 运算；未运行该产物。

源码修改、产物编译、正式文件发布及当前进程兼容交接均已完成，根 `urwcn_launcher.exe` 使用同一正式包，没有平行修复目录。未启动或操作游戏，未运行测试或自行验收画面；`Applied` 仅表示模块交接。
