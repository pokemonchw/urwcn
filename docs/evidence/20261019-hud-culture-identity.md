# 游戏内角色面板民族漏译

日期：2026-10-19。对象：Windows x86《不真实的世界》3.89 / Steam Build 25939378。
用户截图为黄色“路里卡 Kaumolainen”及蓝色标题栏，并明确允许追踪内存、要求自行分析。

## 根因与证据

原属性大页 `E66B0` 的 `E6784 → F9030` 已接入民族翻译，其 `F909D/F90B5`
字宽与绘制钩子也已安装。该路径并非截图标题采用的游戏内角色面板路径。
`20261019-windows-profile-encyclopedia-sync.md` 曾错误声称 HUD 共用此组件，
已在原位置更正。影响是 HUD 姓名能够由既有中文姓名绘制扩展显示，民族仍走原文，
且居中仍以原始字节数乘 8 计算。

已确认的独立原生链（以下均为 RVA，原 PE 首选基址为 `400000`）：

| 边界 | 原生行为 | 本次接入 |
| --- | --- | --- |
| `FA3F2 → 10D0` | 用 `%s %s` 拼接 `Plr.name` 与 `Plr.inhabitant` | 保留原生构建及原文 |
| `FA3F7..FA40D` | 将结果复制至 `[EBP-408]` | 保留原生局部缓冲 |
| `FA493` | `8D 04 CD 00 00 00 00`，`LEA EAX,[ECX*8]` | EAX 提供完整显示字符串的实际逻辑宽度 |
| `FA49A..FA4A6` | 符号处理、除以 2、从原生中心减去半宽 | 完整保留原指令 |
| `FA4D8 → 10E5A0` | 第一面板分支，字符串为第 0 栈参数，shadow=1 | 同步借入译文并进入已有文字作用域 |
| `FA507 → 10E5A0` | 第二面板分支，同一参数语义，shadow=1 | 同上 |

原指令来源为既有 `build/windows-sync-pe.asm:309112..309197`。
原生姓名地址为 `A32A6E8`，文化编号为 `A32A6F5`（`Plr+0xD`），
民族原文为 `A32A6F6`。沿用已经接通的十种 `profile_culture_0..9` 译文；
编号 0 的 `profile.culture_0` 为“考莫人”，无需新增词库或修改内部英文。

## 用户授权的内存诊断

诊断时进程为 121728，映像基址 `005B0000`。以下原始诊断记录保留在本地，
仓库提交本节的分析结论，不提交原始内存地址候选清单：

- `20261019-attribute-culture-live.json`：中文模式为 1；姓名“路里卡”；文化编号 0；
  原生民族 `Kaumolainen`；属性大页三个钩子均存在。内部民族保留英文是设计要求，
  单凭这个字段不能判定显示漏译。
- `20261019-attribute-culture-stack.json`：为稳定读取寄存器与栈，短暂挂起主线程，
  读取后立即恢复。栈顶原生返回点包括 `D1CFA/D3C01/17D0AB`，对应主游戏等待输入。
  文件后段为栈内代码地址候选，不等同于已经回溯验证的调用帧。
- `20261019-attribute-culture-font-cache.json`：只读字体字符串键与度量元数据，
  outline=1 的缓存中存在“路里卡 Kaumolainen”，物理宽度 228、density=3.423333。
  这说明原英文民族组合确实进入过字形生成，区别于只观察内部业务英文。

诊断没有写入游戏内存、注入代码、模拟输入、读取游戏表面/纹理像素或字形 alpha。
缓存未命中不能单独证明某条绘制从未发生；本结论结合原生调用链与缺失接入得出。

## 源码修改与所有权

`modules/adapter/hud_native.inc` 新增三个钩子和 `hud_identity_display`。
原生 `Choose_Name` 排除姓名内的空格，借入时以第一个空格分离姓名和完整民族后缀。
静态边界为 `11A5B` 压入字符 `20`、`11A5D..11A62` 对 `Plr.name` 调用 `strchr`，
`11A67..11A69` 在命中时跳至 `11ADB` 错误分支，`11AE8` 清零通过标志。
原生表 `58E31C`（VA）最后三项为 `of Kuikka-tribe/of Owl-tribe/of Seal-tribe`，
后缀本身含空格，必须整体替换。姓名交由既有 `native_name_input::display` 编码；
文化编号仅选择既有译名。英文模式继续显示
原完整字符串。宽度与两处分支绘制使用同一构建函数和 outline=1。

`FA493` 只替换宽度结果，不搬入面板坐标、不改变后续居中运算。
两处绘制通过 `lend_text(...,Scope::text)` 借入，返回时由已有 token 生命周期释放；
高清字形使用既有 `render_request` 读取当前原生表面的真实输出密度，
在原生文字调用内绘入。背景、颜色、布局、缓存、重绘与输入仍由原生 UI 管理。
没有新增 UI 布局表、页面快照、像素扫描、延后文字重放、回退分支或测试。

## 编译与正式发布状态

第一轮只完成源码，未编译发布；用户随后反馈“没修复”。当时正式 Adapter 仍为
`e55fa878111ff1257c8231bbd819ee9c6f9e80c1230cee98df7d9f400fc0fb32`，
运行版本确实没有获得本次修改。共享目录的菜单、背景、缓存与消息区改造持续进行，
直接构建共享 adapter 会纳入其他聊天的在制修改。

第二轮扩展既有根编译入口的可选 `ModuleSourceDirectory`，默认仍为项目根。
它进入同一个队列的配置比较、批次参数及结果记录；每次配置均明确传给 CMake，
后续默认请求会重新采用项目根，不沿用本次快照。Windows 和 Linux 的模块源码及
模块 include 优先读取所选根；launcher/loader、队列、构建目录和正式发布流程不变。
修改文件为根 `build.ps1/build-queue.ps1/CMakeLists.txt`、
`cmake/build-once.ps1/cmake/linux.cmake`。本次只编译 Windows Adapter。

冻结源码位于 `build/.source-snapshots/hud-culture-6c22637/`：从稳定提交
`6c22637f22548a2fdc794cf619a1a5529d0bcfee` 导出 `modules/sdk/src`，
仅覆盖 `modules/adapter/hud_native.inc`。源码清单记录该文件 SHA-256 为
`7a140ca6dc1fcc8fda253c87db3a27e3d3abb29a91a98ad1daed5be3ac596a3a`。
独立静态复核逐一读取 87 个文件，忽略换行符后唯一差异为本次 HUD 修改。
稳定基线有 21:49、22:02 的连续发布记录支持，但旧清单未记录 Git 提交，
不将其表述为已经证明旧 DLL 与该提交全量可复现。`profiles/` 与 `cmake/module.def`
在提交前无改动。没有覆盖其他聊天源码，也没有新建编译队列、构建目录或运行副本。

2026-10-19 23:03:43（Asia/Shanghai）交付回执：

- 根入口：`build.ps1 -Module adapter -ModuleSourceDirectory D:\workspace\uwcn\build\.source-snapshots\hud-culture-6c22637 -Publish`。
- 请求 `86678613a04a4ebba0ab50f3b3dcf027`，批次 `7c37c48420db4d878748c87f507a26d3`。
  已读取对应结果 JSON 和完整批次日志，`Success=true`，一次配置、一次构建，
  沿用 `build/mingw-x86`。日志中 48 项警告均为既有 SDL 函数地址类型转换警告。
- 发布事务 `57348cebb78b4b998c0cecdb4158c851` 的 `publication-result.json`
  为 `success=true`。正式替换 `package/modules/uwcn_adapter.dll` 和 `package/release.json`。
- 旧两件先按原相对路径移入 `回收/20261019-230343-57348cebb78b4b998c0cecdb4158c851/`。
  已核对归档旧 DLL 哈希仍为上述 `e55fa878…`。
- 正式 DLL、构建产物、事务暂存和正式清单的 Adapter SHA-256 一致：
  `9cac9bc16bb60600dfd44765d622b591fc0de8d57a819f809f7e5f300765eaa6`。
- 提交时未检测到 `urw` 进程，因此没有指定 `Reload`，也没有运行时 Applied 回执。
  新文件已经进入根启动器使用的正式路径；本次未启动游戏或进行画面验收。

本次没有运行游戏、运行产物或任何测试，没有新增测试脚本、测试工程或断言。
