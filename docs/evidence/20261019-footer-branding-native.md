# 主界面 03、Byayoi 署名与汉化版本

当前全局语言切换实现已由 canonical footer resource 取代下文 `capture_footer_edge` / `footer_branding` 的临时 Before 方案，详见 [页脚与帮助中性资源](20261019-footer-help-neutral-sources.md)。下文保留原批次的静态及发布历史，不再作为当前组件生命周期说明。

本轮增加 dfcn 原始 03 像素绘，以及 `Byayoi同人社区`、`汉化版本：{value}` 两行。后续按用户位置调整要求，将 03 移至原开发者标识右侧，社区署名放到 03 下方，版本号在署名下一行。原开发者图标、出品、版权、作者和菜单动作沿用原生流程。本记录区分源码、编译、正式发布与运行时应用，不代表视觉验收。

## 原生接入与布局归属

绘制入口为主菜单页脚 `125125 → 112980` 的 Before。该调用提供原图标的实际 y；它位于页脚背景绘制之后、原出品段落 `125137 → 162300` 解析之前。位置调整新增 `12510E → 116270` 的 Before，从原生当前 panel 的 ECX=x、栈参数 width 取得右边界。原始字节、图像尺寸、调用约定和完整控制标记见 [页脚静态证据](20261019-footer-branding-disassembly.txt)。

新增标识采用最新授权的竖排关系：文字列右边缘位于原生 panel 右边界向内 5 个逻辑单位，03 在该列上方居中，图像上沿取原图标本次调用的 y。文字段落从 03 下边缘向下 5 个逻辑单位开始，版本由原生 `<br>` 放在署名下一行。两行完整文本的同源字宽决定列宽；版本行以中文冒号连接版本值，不引入空格分词。没有固定屏幕坐标或逐行位置表，也不宣称游戏存在自动竖排组件 API。

`capture_footer_edge` 只将当前原生 panel 的一个右边界整数挂在既有 footer 作用域的 `allocation`，由 Host 分配并在该次原生页脚结束时由既有 `end` 释放。它不保存页面字段、行位置、像素或绘制序列，`Active` 结构、状态格式和 Host ABI 不变。原生当前 panel 为 x=10、width=780、y=520、height=75，这些数值只作静态证据，不作为新增组件的固定坐标写入源码。已确认原图 y=525、03 高度34及间距5，故本构建的段落首行在564、第二行由原生推进至574，在原生下边界595以内。

`modules/adapter/module.cpp::footer_branding` 在本次调用中构造 `credit + <br> + version`，经过原生编码后交给 `162300` 与 `10EB40`。原生函数执行断行、行距、光标及逐词绘制，既有测宽、描边和即时字形接口继续生效。`native_paragraph.cpp` 的小型包装按已确认 ABI 传 ECX/EDX，压入四个参数后由调用方清栈。随后原出品解析清空临时 token，无需保存或重放页面字段。新增段落作用域随本次原图标调用结束，`Active` 结构与保存格式未改动。

`modules/render/byayoi_sprite.h` 原样复制 `D:/workspace/dfcn/src/byayoi_sprite.inc` 的 34×34 五色素材；没有重新生成角色。`immediate_sprite.cpp` 根据当前原生主面的实际宽高，将每个源像素栅格化为实色块并立即 Blit 到该面，临时 RGBA 与 SDL 源面当场释放。文字同样在原生文字调用中按实际目标密度输出。原生页脚管理画面、背景缓存、复制、上传、重绘和淡入淡出；没有独立 UI 纹理、Present 叠加、全局像素扫描或文字贡献重放。

## 汉化版本

`MainMenu` 首次处理版本字段时，读取正式包的六个业务 DLL 和中文词库，对每个文件取 SHA-256。身份文本以 `uwcn-package-version-v1` 加 LF 开头，按 catalog、semantic、render、layout、main_menu、adapter、中文词库的固定次序追加 `相对路径<TAB>小写SHA256<LF>`。再取整体 SHA-256，按大端数对 `36^5` 取模，编码为五位 `0-9A-Z`，沿 dfcn 的规则确保包含字母和数字。

该五位值是内容短指纹，不是唯一发布编号。初始化不读取文件；首次显示请求生成后只缓存五位版本，任何依赖变化通知都会清空。文件读取发生在当前宿主的同步调用和正式文件交接边界内。主菜单不保存 UI 位置、文本段落或整页内容，Host ABI、启动器和驻留桥无需变更。

## 交付所需的实际双进程范围

发布前只读模块清单确认 PID `45376` 与 `102320` 都加载了本项目 `package/uwcn_loader.dll` 及六个正式业务 DLL。单目标事务不能释放另一进程持有的同一文件。因此统一构建/发布入口的 `TargetPid` 扩为显式 PID 集合，同一批次规范化排序去重；所有指定目标先 Ready，再进行一次旧文件回收和正式替换，最后逐目标 COMMIT 并记录 Applied。没有自动发现或追加目标，也不关闭、重启、重新注入游戏。

## 审查发现与状态

| 文件位置 | 影响 | 本轮状态 |
| --- | --- | --- |
| `main-menu-branding-static.txt:35`、`:44`、`:54` | 旧固定行槽、DisplayPlan、独立纹理及 Present 合成违背当前原生所有权要求。 | 旧实现禁止复用；本轮另以原图标调用、即时图像提交和原生段落接入。历史正文仍待清理。 |
| `main-menu-branding-version-static.txt:16`、`:23`、`:68` | ABI 3 元数据接口、DisplayPlan 和交接说明已不适用于当前重建 ABI 1。 | 当前实现及算法以本记录为准；旧文档待清理。 |
| `main-menu-branding-delivery.txt:4`、`:35`、`:72` | 旧发布事实不能证明当前原生品牌接入已经完成。 | 保留为历史记录，不作本轮交付或合规依据。 |
| `main-menu-static.txt:21`、`:33` | 旧说明保留按字节推进及固定位置整段绘制，与当前测宽/原生段落要求冲突。 | 只采用其中明确指令与 ABI 证据；该旧建议仍待清理。 |

## 首次交付状态（左侧横排，后续位置调整取代）

源码修改和静态审查已完成。2026-10-19 02:33（Asia/Shanghai）统一队列完成编译与正式发布：

- 调用：根 `build.ps1 -Module adapter,main_menu,render,semantic,catalog -Publish -Reload -TargetPid 45376,102320`。沿用 MinGW、`.toolchains/x86/w64devkit/bin/cmake.exe`、同目录 `g++.exe`、`build/mingw-x86` 和正式 `package`。
- 编译请求：`f43d42b725714136b1a735d66a3b82a1`；批次：`fb72ae7ebb1541b7a6085e2ff6358e7b`。已读取 `build/.compile-queue/results/f43d42b725714136b1a735d66a3b82a1.json` 及对应批次完整日志，结果为成功；只执行一次配置和一次增量构建。既有 SDL/TTF `GetProcAddress` 函数指针类型转换警告仍存在，没有编译错误。
- 正式发布事务：`82446395ac7d4cd0ace5ddcf673dcad1`。已读取 `build/mingw-x86/stage/82446395ac7d4cd0ace5ddcf673dcad1/publication-result.json`，记录 `success=true`。正式替换四个 DLL（Adapter、MainMenu、Render、Semantic）、词库、构建适配和 `package/release.json` 共七项。Catalog DLL 内容未变，词库变化触发其重新加载。
- 七个旧文件先按原相对路径移入 `回收/20261019-023345-82446395ac7d4cd0ace5ddcf673dcad1/`；已只读核对回收清单和正式发布清单。正式清单十项文件的磁盘 SHA-256 全部一致。根 `uwcn_launcher.exe`、驻留桥及 Layout 沿用原文件，没有平行修复包。
- 两个目标均记录 `ReadyToPublish 82446395ac7d4cd0ace5ddcf673dcad1` 及 `Applied 82446395ac7d4cd0ace5ddcf673dcad1`。PID 45376 的 Catalog/Semantic/Adapter 为第 3 代，Render/MainMenu 为第 2 代；PID 102320 的五个交接模块均为第 2 代。回执里的模块哈希与正式清单一致。

| 正式文件（相对 `package/`） | SHA-256 |
| --- | --- |
| `modules/uwcn_adapter.dll` | `fc75cdf95b57276d6d6ba0092407bd3d4398af9236e60f5e9995e6b533a24f04` |
| `modules/uwcn_main_menu.dll` | `b0cfb9e5f913ad3c028addbe5ba1855b64fc00e1f18c08d27a98f94e02339114` |
| `modules/uwcn_render.dll` | `894366d203897346df382886ae896dd8cd46fe5dc8cf690c6bb33f988527a050` |
| `modules/uwcn_semantic.dll` | `ab0e6ead1c1f3d5690dc4351bc5f279eca5b44e2946e55e8504964390ea7c25e` |
| `catalog/zh-CN/main_menu.tsv` | `8fe162a26090aa3911bc1d71d6824d6740b92f004c36e76faee9a6f309599e0f` |
| `profiles/urw-3.89-steam-25939378.json` | `3502b7289ecd6a409644765301b2533e6de5098850a383325c38ed6091be9141` |

未自行启动游戏、注入、模拟输入、运行测试或单独运行产物，未创建测试用例与断言。授权热发布只对既有进程执行兼容业务事务；Applied 证明交接完成，不等于视觉验收。

## 右侧竖排位置调整

源码只修改 `modules/adapter/module.cpp`，复用原图素材、同一个原生段落、字体度量和版本服务。发布前只读清单显示当前 PID `65412` 持有本项目正式包；此前两个进程已不在当前控制管道清单内。本次统一队列、正式替换与回执另行记录如下。

- 源码已保存并完成静态审查；没有增加测试、断言或回退。位置改为读取原生 panel 右边界，上图下文；原生 token 和绘制生命周期继续沿用。
- 根入口 `build.ps1 -Module adapter -Publish -Reload -TargetPid 65412` 于 2026-10-19 02:38（Asia/Shanghai）完成。请求 `00ddf1ed1b5144e49fc5cc6ff8e83627`，批次 `6199b8acaf554f0da99daa5eef7a434c`，一次配置和一次增量构建，结果成功。已读取该请求 JSON 和完整批次日志；只有既有 `GetProcAddress` 转换警告。
- 正式发布事务 `d9d38d74655f416da630db68edd3001b` 替换 `package/modules/uwcn_adapter.dll` 与 `package/release.json`。旧两件先移入 `回收/20261019-023810-d9d38d74655f416da630db68edd3001b/`，保留原相对路径。正式 Adapter SHA-256 为 `50505b80fce7d4c004758d96f3ec0758ea4abf863979030dbb3add188b6133de`；只读核对正式清单十项哈希全部一致。
- 已读取 `build/mingw-x86/stage/d9d38d74655f416da630db68edd3001b/publication-result.json`：PID 65412 返回 `Applied d9d38d74655f416da630db68edd3001b adapter:50505b80fce7d4c004758d96f3ec0758ea4abf863979030dbb3add188b6133de:2`。源码修改、编译和正式热发布均完成；没有启动游戏、注入、模拟操作或运行测试。视觉效果未自行验收。
