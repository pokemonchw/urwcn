# 文化选择页闪退：原分支进入 inline 补丁中间

2026-11-11，Asia/Shanghai。用户报告游戏闪退，要求自行分析、不询问。使用磁盘日志、已有 minidump、原 PE、源码和静态反汇编定位并修正；未启动、关闭、重启或操作游戏，未注入、模拟输入、运行产物或测试，未编写测试用例、测试脚本或断言。

## 本次现场

- `package/crashes/20261111-061650-060-p364-t368.dmp`：北京时间14:16:50，Windows PID364、线程368，异常 `C0000005`，读取地址 `FFFFFFFF`，EIP=`0040F8D6`，EBX=7、EAX=0、ESP=`0AD7DE98`、EBP=`0AD7DF20`。
- 转储 SHA-256：`e5912b8f0c968efc4fd72874f050d5f90e3903e5f790140409b9c313fa22f3ba`。
- `package/uwcn.log` 末尾记录相同异常及转储成功；最后原生事件 ID20821=`5155h`，为 `native_parent_cache_language::culture_auto`，不是 `culture_input`（后者为5154h）。这个事件位于原文化自动分支入口 `F819`。
- 从实际线程栈读取的 EBP 链返回地址：`412CD1 → 412FF8 → 525D6A → 5809E9 → 58B018 → 58AF15`。`412CD1` 是角色创建控制器调用文化选择 `40F4F0` 后的返回点。不能把它解释为纪念页或此前 Shift+P 资料页崩溃。
- Steam `gameprocess_log.txt` 于14:16:51记录同一宿主PID3275331及本组进程退出。发布前只读进程列表已无 `urw.exe`，没有代理终止或重启行为。

转储只含线程栈和少量系统内存，没有保存游戏代码页，因此没有读到现场补丁的实际五个字节。异常地址、原指令、补丁覆盖范围与原入口足以确认下面的控制流缺陷，不能把静态原字节冒充现场改写字节。

静态提取材料在 `build/analysis/crash-20261111-141650/`：`dump-summary.json`、`culture-loop-original.asm`、`uwcn-log-tail.txt`。原始转储保留在正式包的既有诊断目录，不创建平行运行包。

## 已确认的根因

对象为 Windows x86《不真实的世界》3.89.1 / Steam Build26139145；原 `urw.exe` SHA-256为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。本段地址为 RVA（原PE首选基址400000h）。[原指令摘录](20261111-culture-branch-crash.asm)及既有 `20261110-culture-native-reconstruction-disassembly.txt:276` 均保留如下控制流：

```text
F8CD: EB 07           JMP F8D6      ; 原自动分支已有 EBX
F8CF: E8 ...          CALL D1120    ; 手动菜单输入
F8D4: 8B D8           MOV EBX,EAX
F8D6: 83 FB 64        CMP EBX,100
F8D9: 7D 57           JGE F932
F8DB: 85 DB           TEST EBX,EBX
F8DD: 78 53           JS F932
F8DF: 69 C3 E8...     IMUL EAX,EBX,0E8h
```

旧 `modules/adapter/native_language_redraw.cpp:76` 的 `culture_input_result`（510Bh）从F8D4安装五字节 inline JMP，覆盖 `F8D4..F8D8`，同时吃掉MOV和CMP。`src/loader/hook_host.cpp::install_hooks` 将五字节写为 `E9 + rel32`；F8D6因此处于其位移内部。原自动分支仍从F8CD跳F8D6，于是执行补丁中间的字节，绕过驻留桥和原完整指令。

本次 EIP正是40F8D6，最后事件为自动分支，栈归属文化选择。磁盘原F8D6只是寄存器比较，不访问内存，无法产生本次读取FFFFFFFF。上述现场与控制流一致，确定缺陷在Mod补丁入口，不是原文化数据、姓名、存档或新增纪念页语法。

## 源码修正与原生语义

仅将510Bh移到两条原生分支的共同入口F8D6，覆盖完整 `83 FB 64 7D 57`（CMP/JGE）。F8D4的MOV继续留给原手动输入；自动分支保留自己已有的EBX，不能用此时EAX覆盖它。

驻留inline trampoline原样复制字节，不重定位短JGE，因此普通处理明确按原有符号比较 `int32(EBX)>=100` 分别续接F932或F8DB。这是恢复被替换原指令的两个实际分支，不新增范围保护、默认选择、回退或兜底。F932的CMP、F8DB的TEST都重写条件标志，后续原分支不消费被替换比较的标志。负值仍由原F8DB/F8DD处理，后续随机选择、预览、保存、退出及配置不改。

文化语言重建仍续接原F675；`native_full_language.inc` 和 `native_parent_cache_language.inc` 的同步文化纯构造仍按同一510Bh续接原F9FD。真实 `D1120` 原调用者返回点仍是F8D4，没有随inline接入点改为F8D6。没有新增布局、坐标、像素、页面字段或绘制重放。

本次移位改变同一Hook ID的HookSpec。现驻留 `install_hooks` 对已登记ID要求整个HookSpec相同，没有卸载迁移接口，因此不能宣称旧进程可原位完成这次入口迁移。游戏已在本次崩溃中退出，本批正式发布不请求Reload、不取得Applied；下次根 `uwcn_launcher.exe` 正常启动时使用更新后的同一正式包。没有要求用户手动卸载、退出或重启仍在运行的游戏。

旧3.89的text地址由现框架共享，本地未取得该旧版PE供本次核对；本次现场及完整字节证据仅对应3.89.1，不将旧版运行表现写成已经确认。

## 其他已发现事项：待整改

| 文件与位置 | 影响与状态 |
| --- | --- |
| `native_language_redraw.cpp` 的文化 `native_menu_input_result` caller判断；`native_parent_cache_language.inc:52`；`src/loader/hook_host.cpp::uwcn_before_route` | 既有F8CF phased CALL替换D1120原返回地址，原 `[EBP+4]==base+F8D4` 识别不能直接成立，影响文化页主动语言重建。独立于本次中间入口崩溃，未在本批扩改，待整改；不因历史Applied视为已正确 |
| `native_component_binding.cpp:56` 的fields及构建集合；`native_ui_scene.cpp` 的Child/Container | 其他界面仍持有历史来源／组件集合，原生UI与缓存所有权审查、退役继续待办；本次入口修正不增加或消费这些集合 |
| `native_renderer_component_binding.cpp:42` 的Owner.children及 `paint_hud`；`module.cpp::enter_component_paint` 的About中心例外 | 历史组件遍历与Mod排版仍待交回原生生命周期和布局，不以本批编译或发布为合规证明 |

## 编译与正式发布

源码及3.89.1适配记录已保存。根统一队列完成一次配置、一次增量编译和正式发布；仅重新编译 `native_language_redraw.cpp.obj` 并链接Adapter，无编译错误或警告。入队后至本批完成未再修改本请求范围的源码。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Publish
```

| 项目 | 实际回执 |
| --- | --- |
| 请求ID | `041682b71b07406499f33973a92d4085` |
| 批次ID | `f2d45eba3d8544f698a06626c6391207` |
| 请求结果 | `build/.compile-queue/results/041682b71b07406499f33973a92d4085.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=false`，已读取 |
| 完整日志 | `build/.compile-queue/batches/f2d45eba3d8544f698a06626c6391207.log`，已完整读取 |
| 正式事务 | `49f2c18df102419d9512d3ef514ed4a0`，北京时间14:22:50完成 |
| 发布回执 | `build/mingw-x86/stage/49f2c18df102419d9512d3ef514ed4a0/publication-result.json`，`success=true`、`runtime_requested=false`，已读取 |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/profiles/urw-3.89.1-steam-26139145.json`、`package/release.json` |
| 旧件回收 | `回收/20261111-142250-49f2c18df102419d9512d3ef514ed4a0/package/`，三件旧文件先归档后替换，保留原相对路径 |

| 文件身份 | SHA-256 |
| --- | --- |
| 新Adapter，正式件／构建输出／清单一致 | `09e754c7b19974fba89aa65dd1f9bb04a8b2d01d39fbbfd71a1c2625834e39da` |
| 旧Adapter，已从回收件读取 | `fbbd7b73815c5281080240145bcd1a331d8355eebc2bf189f02b5efae78e87cf` |
| 新3.89.1适配，源码／正式件／清单一致 | `9ac275b26495589922c30c24f51aeab5a9dff0a7d2c59d3aa9ee625533c53a31` |

源码修正、产物编译和正式文件发布均已完成；没有运行产物或游戏验收。根 `uwcn_launcher.exe` 下次正常启动消费正式Adapter。本批没有运行中交接，不以编译成功或正式文件身份一致宣称游戏已经运行确认。
