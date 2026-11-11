# 启动闪退：开场诗淡入循环跳入补丁中间

2026-11-11，Asia/Shanghai。用户报告游戏启动时闪退。本次使用磁盘日志、已有 minidump、游戏原 PE 和源码进行静态定位；没有启动、关闭、重启、注入或操作游戏，没有运行产物或测试，没有新增测试用例、测试脚本、断言、保护或回退逻辑。

## 本次现场

- `package/uwcn.log` 最新异常：`C0000005`，EIP=`00525260`，ESP=`0AD7F3C0`，EBP=`0AD7F3D4`，EAX=0、EBX=1、ECX=2、EDX=0；最后原生事件 ID125、phase=1、token=3442456。
- `package/crashes/20261111-063319-762-p364-t368.dmp` 为北京时间14:33:19.762开始记录的现场，Windows PID364、线程368；转储异常参数确认读取地址 `00000001`。转储头时间为06:33:20 UTC。
- 转储 SHA-256：`250e816d09705938df70a6d3eaae239715328179b17b2c6439fe9ecaf0154a9d`。
- 转储 EBP 链的首个返回地址为 `52544A`，对应原 `125445 -> 125240` 单行诗文淡入调用。后续两帧返回 `796E614E`，位于本次加载的正式驻留库 `796E0000` 内，是原生 CALL 的既有 After 桥；不能把它解释为原 EXE 调用地址。
- ID125 对应 `module.cpp` 的 `intro_story_fade_text`；`sdk/host_abi.h:25` 定义phase=1为After，表明第一次淡入文字调用已返回。EBX=1符合第一次淡入绘制及Delay后回到第二次循环时的现场。
- 转储没有保存 `00525260` 的代码页，因此本次没有取得现场补丁的实际位移字节；以下覆盖范围由当前源码和驻留安装器确定，不将磁盘原指令称为现场改写后的指令。

静态提取结果保存在 `build/analysis/crash-20261111-143319/dump-summary.json` 和 `intro-loop-original.asm`；原始转储保留在原诊断目录。没有创建平行运行目录或修复包。

## 已确认的控制流缺陷

本次对象为 Windows x86《不真实的世界》3.89.1 / Steam Build26139145。游戏原 `urw.exe` SHA-256为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`，与正式适配记录一致。以下为 RVA，原 PE 基址为400000h；完整原指令见[反汇编摘录](20261111-startup-intro-loop-crash.asm)。

```text
125257: 89 55 FC             MOV [EBP-4],EDX
12525A: 89 4D F8             MOV [EBP-8],ECX
12525D: 0F 1F 00             NOP
125260: 8A C3                MOV AL,BL
125262: C0 E0 02             SHL AL,2
...
125285: E8 16 93 FE FF       CALL 10E5A0
...
1252D4: 6A 02                PUSH 2
1252D6: FF D7                CALL EDI
1252D8: 43                   INC EBX
1252D9: 83 C4 04             ADD ESP,4
1252DC: 83 FB 3F             CMP EBX,63
1252DF: 0F 8C 7B FF FF FF    JL 125260
1252E5: A1 10 BB 5B 06       MOV EAX,[base+61BBB10]
```

旧 `modules/adapter/native_wait_language.inc::append_hooks` 将5212h（`intro_story_fade`）从12525D安装为五字节inline JMP，覆盖 `12525D..125261`，包含三字节NOP和两字节MOV。已回收的本次旧正式Adapter也在 `6445E401` 将12525D传给inline_hook，`6472BB6C` 保存原五字节 `0F 1F 00 8A C3`，确认正式DLL包含此声明。`src/loader/hook_host.cpp::install_hooks` 将该段改写为 `E9 + rel32`。原第一次顺序执行进入补丁起点，可以经过桥及原指令；第一次淡入后的 `1252DF -> 125260` 则跳入这个JMP位移的后两个字节，绕过桥并把位移当作指令执行。

本次EIP正是525260，EBX=1，首个原生返回点是52544A，最后事件来自第一次淡入绘制。原125260的MOV只操作寄存器，本身不可能读取地址1。这些现场与补丁覆盖和原分支共同确认该控制流缺陷。此前14:16文化选择页的40F8D6异常是另一个已修正的入口；不能把那次发布视为本次开场循环已修好。

## 本次修正与原生语义

将同一Hook ID5212h移到第一次进入和循环回跳共同使用的 `125260`，覆盖完整五字节 `8A C3 C0 E0 02`（MOV AL,BL / SHL AL,2），原12525D的NOP保留。该段不含相对跳转或调用；驻留trampoline原样执行两条指令，再接原125265，因此保留AL颜色计算、SHL条件标志、PUSH及后续完整文字调用。

普通开场不修改 `intro_story_fade` 的分派，原63次颜色淡入、Delay、定色文字、后续停留和输入仍由原生程序执行。已有同步语言重建仍在 `constructing==Construction::intro` 时续接原定色入口1252E5，此时原x/y已保存且颜色参数尚未入栈；没有新增跳过正常开场、默认选择、异常兜底或页面状态。

静态阅读原125240及1254C0的分支和同文件开场等待接入，确认本次原循环落点正是新补丁起点；这两个原函数中没有分支落入新125260五字节补丁内部。该结论只涉及所读原函数和本次补丁，不宣称整个项目的全部Hook已经审查完成。3.89共享这段业务源码，本地本次仅有3.89.1原PE，完整字节与现场结论只对应3.89.1。

更新3.89.1适配记录，并纠正 `20261110-wait-animation-language.md` 中仍将12525D作为有效接入点的描述。没有新增布局、控件、像素跟踪、字形重放或缓存路径。

本次改变同一ID的HookSpec；现有驻留安装器要求已登记ID的整个HookSpec相同，没有提供该入口的原位迁移。因此不宣称旧进程可热迁移此入口。只读进程表未见 `urw.exe` 或 `urw3-bin`，本批使用正式文件发布，不请求Reload、不取得Applied；没有终止或重启游戏。

## 已发现的既有所有权问题：待整改

| 文件与位置 | 影响与状态 |
| --- | --- |
| `modules/adapter/module.cpp:1117` 起，`intro_story_fade_text / intro_story_settled_text` | 从组件来源取回文字并由Mod重新计算居中x，涉及原生布局所有权；既有来源与布局重建仍待整改。本批只移动机器指令入口，不新增或扩展该机制。 |
| `modules/adapter/native_component_binding.cpp:56` 的fields及构建集合 | 既有组件来源和构建集合的原生UI／缓存所有权仍待审查、退役；不能因本次编译或发布视为合规。 |
| `modules/adapter/native_renderer_component_binding.cpp:42` 的Owner.children及paint_hud | 既有组件遍历仍有生命周期与重建所有权待整改；本批不增加或消费其页面集合。 |

## 编译与正式发布

源码修改、产物编译和正式文件发布均已完成。根入口如下，复用既有构建树，一次配置、一次Adapter增量编译；入队后至批次结束未再修改本请求源码。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Publish
```

| 项目 | 实际回执 |
| --- | --- |
| 请求ID | `e49b80dfce7e43a187ec9726bdbd11e8` |
| 批次ID | `8e7367dcefbf43cbb3d799f42c0d2ce3` |
| 请求结果 | `build/.compile-queue/results/e49b80dfce7e43a187ec9726bdbd11e8.json`：`Success=true`、`PublishRequested=true`、`ReloadRequested=false`，已读取 |
| 完整日志 | `build/.compile-queue/batches/8e7367dcefbf43cbb3d799f42c0d2ce3.log`，已完整读取 |
| 编译结果 | 重新编译 `module.cpp.obj` 并链接Adapter成功；有既有函数指针转换、extern初始化、未使用声明及缩进警告，没有编译错误 |
| 正式事务 | `60d922d474d64cc084d79a8cf2b46877`，北京时间14:36:14完成 |
| 发布回执 | `build/mingw-x86/stage/60d922d474d64cc084d79a8cf2b46877/publication-result.json`：`success=true`、`runtime_requested=false`，已读取 |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/profiles/urw-3.89.1-steam-26139145.json`、`package/release.json` |
| 旧文件回收 | `回收/20261111-143614-60d922d474d64cc084d79a8cf2b46877/package/`，三件旧文件先归档后替换，保留原相对路径 |

| 文件身份 | SHA-256 |
| --- | --- |
| 新Adapter，正式件／构建输出／清单一致 | `721298248397dbcb53ab063372222b47be6f0133bb98fb5ab7966aed1e90888a` |
| 旧Adapter，已从回收件读取 | `09e754c7b19974fba89aa65dd1f9bb04a8b2d01d39fbbfd71a1c2625834e39da` |
| 新3.89.1适配，源码／正式件／清单一致 | `ff3215a85c926fe72526adf213abe53622f432a6120f3abc119d8f8320f792b7` |

对新正式DLL的只读反汇编确认：`append_hooks` 的 `6445E401` 传入125260，后续传入ID5212h及长度5；`6472BB6C` 保存 `8A C3 C0 E0 02`。驻留 `_uwcn_after_bridge` 在.text内偏移514Eh，加节RVA1000h即614Eh，与现场 `796E614E` 的返回地址一致。没有加载或执行DLL。

正式根 `uwcn_launcher.exe` 下次正常启动使用更新后的同一 `package/`。本批不请求Reload、不取得Applied，没有启动或测试游戏；编译成功、静态字节一致及正式发布回执不代表运行验收。
