# 共同原生 UI 语言源改造

后续更正：用户实际启动发现本记录首批交付的 Adapter 在 Hook 安装阶段失败；本记录中的编译与发布成功不表示该旧版本已能运行。错误为消息来源 `C70C` 的指令地址及操作码，已在后续正式事务 `108be69c6a744d15a13a227e21322faf` 修正。当前文件身份、冻结编译来源及静态证据见 [启动边界修正记录](20261020-startup-native-hook-boundary-fix.md)，下列批次为发现启动错误前的历史交付。

本轮依据 Windows x86 3.89 原 EXE 静态反汇编与源码审读实施。原 EXE SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`，地址均为 RVA。没有启动游戏、注入、模拟输入、运行产物、测试、测试脚本或断言。

## 共同切换协议

`Shift+F10` 仍由共同原生输入处理。全局语言改变后，公共 Scene 失效其中性原生组件源与缓存 generation；组件重新解析所选语言，调用普通显示使用的相同完整原生构造、度量和绘制接口。没有页面识别表或页面重入回调。游戏继续管理排版、控件、选择、命中、原生目标及缓存；字体在当次原生调用中绘入其真实密度目标。

中性源按实际原生 owner、record/action/field 身份管理，保存原文、模板和实际参数，不保存整页译文。Menu、链接 Flow、消息 Flow 的冻结显示源与当前 InputOwner 分开；旧缓存不回灌旧选择、输入内容或旧语言索引。区域缓存按真实缓存槽和完整复制输入引用冻结源，不按像素或几何重叠猜控件归属。

## 审查发现并处理的接线问题

| 位置 | 影响及处理 |
| --- | --- |
| `module.cpp` 的旧 Menu 消费分发 | 新共同处理提前返回，遮蔽主菜单和创建菜单的语义绑定。改为普通消费前的纯 `BeforeConsume` 源绑定；locale 直接消费既存源。 |
| `hud_native.inc` 的 `F8E84` | 多个状态格共用该叶调用，按 site 保存会覆盖，且遗漏数值和条形。改接完整 `F8E20` 与真实原生缓存 record 的更新生命周期。 |
| Culture `E3A50` / `E3D90` | 图例启动纹理与地图窗口拥有独立真实资源。采用完整原生 factory，不把临时 renderer 伪造为长期 owner，也不保存旧段落返回高度。 |
| 消息 `F5B00` / `F6510` | 原分页等待保有原语言字节索引。由新语言的完整原生 UI 循环产生实际恢复相位与工作缓冲，绑定同一真实等待；声音、日志和输入仍由普通调用继续一次。 |
| 原生缓存物化 | 中途恢复旧 renderer owner 会使后续 Menu 消费旧纹理。临时新资源保持至整个原生缓存物化作用域结束，再恢复调用者并退役。 |
| `module.cpp::invalidate` 现代选择框 | 先画 `D0850` 再执行 `10B480` 会把默认 target 上的选择框清掉。按原 `D125A → D1266` 改为先整帧合成，再画现代选择框，最后呈现。软件选择框仍在软件上传前绘制。 |
| `module.cpp::restore_state` 的 Active-only 历史格式 | 旧 `return ok` 会接受没有构造源的已确认初代格式。现明确返回 `unavailable`，不把 Host ABI 相同当作状态迁移已实现。 |
| Windows `profiles/urw-3.89-steam-25939378.json` | 旧说明仍称逐页重绘和 HDA4/NGT1，误导正式交付边界。已更新公共协议；旧各页刷新字段明确标为 historical，并同步正式 profile。 |

## 原生提交模式

`D1E26..D1E7B`、`D1ED1..D1F56` 的共同窗口输入代码已明确选择原生提交模式：`(5F54DF0 && 5F54B94) || 5F55634` 时使用完整 `10B480` 合成，再按原 `10B680` 处理默认 target 与呈现；活动现代菜单的 `D0850` 位于二者之间，与 `D125A → D1266` 相同。其余使用原 `10B720` 软件上传及呈现，软件 `D0650` 在上传前执行。全局失效沿相同字段和完整接口提交，不把软件上传当成现代纹理界面的重建，也不重执 `99BE0` 等世界业务。

## 状态与交付边界

新 UI 源由 HDA7 状态章节保存，原生目标构造源使用 NGT2。此前正式 HDA4/NGT1 仅有资源身份和已有像素，没有本次 Root、组件、消息和缓存构造源；当前框架不能从该旧状态原位补造这些已过去的构造事件。明确返回不可迁移状态，不扫描位图、不以旧像素为中性源，也不宣称有尚未实现的热迁移能力。

本次改造范围为 Windows x86 3.89。Linux 仍保留既有分支，没有把本次 Windows 公共源接线称为 Linux 已完成。姓名字段在同一次原生输入返回后重画，Scene 提交与该字段重画之间的边界见 `20261020-native-name-field-global-wake.md`。

## 编译与正式发布

所有源码保存后，通过根 `build.ps1` 队列实施。两次前置失败分别为 const 迭代器类型不一致及新增 calendar 模块未完整接线，已在后续批次修正；没有运行产物验证。

| 内容 | 请求 | 批次 | 结果 |
| --- | --- | --- | --- |
| `adapter,catalog,semantic,render,layout,main_menu -Publish` | `169fbac5f29d4157b92094499d6f2bfe` | `f3d66480e9ec4f5ead2f6b32af57dd2d` | 编译、链接及正式替换成功，01:28:16 +08:00 |
| 重新生成消息词库后 `catalog -Publish` | `9112933065cd4c14ae4c665a10938e7a` | `3ed7d148ebc24f64bba9579b1ec9584a` | 增量编译及正式词库替换成功，01:29:20 +08:00 |
| 现代选择框及旧格式接收修正后 `adapter -Publish` | `39c869149d71401ea147dfca3a984ac6` | `15a48864305848c8a7c5fc337873bec2` | 编译、链接及正式 Adapter 替换成功，01:32:25 +08:00 |
| 同步适配说明后 `adapter -Publish` | `399b7ef7f1134850bf4ff66e0fa2bcdf` | `9a5dedb955fe49ecb11375403e8440f4` | 增量构建及正式 profile 替换成功，01:33:35 +08:00 |

已读取四批各自 `build/.compile-queue/results/<request>.json`、完整 `batches/<batch>.log` 和发布暂存目录内的 `publication-result.json`。均为 `Success=true`、`PublishRequested=true`、`ReloadRequested=false`。编译仍报告 SDL 动态函数指针转换、未使用函数/参数、消息构建代码缩进、Owner 尾部字段隐式值初始化和 semantic 单键 switch 未逐项枚举的警告；未据这些回执宣称零警告或运行正确。

第一次正式事务为 `f7df02ebdb0e4e039ddee5e726975e8e`，替换 Adapter、Catalog、Semantic、MainMenu、文化词库及清单；Render/Layout 的产物与正式文件内容相同，没有替换。旧六件先归档至 `回收/20261020-012816-f7df02ebdb0e4e039ddee5e726975e8e/package/`；消息词库此前无正式旧件。

消息词库随后从当前直接文字、模板和 `values*.zh-CN.tsv` 生成，共 67,511 项。第二次正式事务为 `525662e36dee46fb9a049e77d692cbbf`，替换 `package/catalog/zh-CN/messages.tsv` 与 `package/release.json`，旧两件先归档至 `回收/20261020-012920-525662e36dee46fb9a049e77d692cbbf/package/`。

第三次正式事务为 `dd624b422acf4a5db91f2686f4304968`，修正后的 Adapter 与清单替换成功，旧两件先归档至 `回收/20261020-013225-dd624b422acf4a5db91f2686f4304968/package/`。第四次正式事务为 `9bfc61f6272b4c629fc469e90f9252a3`，仅替换适配说明与清单，Adapter 内容未变；旧两件先归档至 `回收/20261020-013335-9bfc61f6272b4c629fc469e90f9252a3/package/`。最终清单记录第四批，保留此前各业务库和词库身份。

最终正式 Adapter SHA-256：`67d9627d0920a83462ac538999658b6a0d29696918eb6727f384fcdf6b1b762a`；最终消息词库 SHA-256：`d34102bcac8257c48074f5140c3b1078e7d1806339689925b5de63d8f3d412f2`；Windows profile SHA-256：`5fa3ea344633d038fbd58b47e58a4489c738152dbce5fd5bc99a820743f3c1d7`。源码目录词库/profile 与正式词库/profile、构建 Adapter 与正式 Adapter 的文件摘要分别一致。

发布前只读进程清单未发现 `urw.exe`。没有发送 PREPARE/COMMIT、没有 Runtime Applied 回执；新版本供下一次从根 `uwcn_launcher.exe` 正常启动加载。根启动器和驻留库未替换。没有启动、关闭或重启游戏，没有注入或模拟输入，未测试或宣称已验收画面。
