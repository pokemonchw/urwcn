# 共用语言刷新擦除原生界面：移除不完整的 Scene 重建

本文记录首次共用擦除整改批次。后续原生完整构建覆盖、静态依据、仍未完成项及下一批交付状态见 [继续实现记录](20261110-native-full-language-boundaries.md)；本文“尚未接入”的界面列表是该首次批次的状态。

日期：2026-11-10。对象为 Windows x86《不真实的世界》3.89.1 / Steam Build 26139145。原 PE 为本机安装目录的 `urw.exe`，既有 profile SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。地址均为 RVA，磁盘反汇编按首选基址 `0x400000` 显示。没有运行时复现、游戏启动、输入模拟、测试、测试脚本或断言；原 PE 仅作为数据读取。

## 共用根因与整改

用户连续发现主菜单、技能、先祖、设置、属性及文化选择页在切换后丢失信息。截图中的文化简介文字仍在，原蓝色底板已经消失；原 `F7BA → 3CA90` 内的 `3CAF6 → 116270` 确实先构建完整简介面板，再构建标题、摘要及 F1 动作。

修改前的共用问题：

- `modules/adapter/module.cpp::invalidate` 调用 Scene 重建，再单独画选择并上传/呈现。个别页面绕过该路径，没有解决其它页面的问题。
- `modules/adapter/native_ui_scene.cpp` 原 `paint/repaint` 先恢复根背景，再遍历 `Container::children`；`native_component_binding.cpp::construct` 对没有文字来源的普通面板不登记，单个文字来源也不包含外层数值框、背景和图形。被背景清掉的原生内容无法靠这个集合恢复。
- 同文件原 `language_changed/prepare_cache/materialize_cache/paint_region` 在语言版本不同或原生缓存恢复时又从同一集合重建缓存、分配临时表面并复制部分区域；只停止当前面的重画，缓存仍会再次带回缺失内容。
- 原 `prepare_region` 还从 Mod 菜单模型替换缓存矩形，`native_targets.cpp::blit` 用其替代原调用的矩形及 SDL 输出。这违反布局与缓存由原生 UI 管理的要求。

本次删除上述整页绘制、缓存物化、临时缓存绘制和来源插入重建函数及公开接口；删除原 `rebuild_native_source` 的依赖更新调用。`invalidate` 只更新语言资源并请求原生输入续执行，不清屏、不遍历组件绘制、不提前呈现。缓存恢复只更新原有来源生命周期身份，像素、矩形、裁剪及目标矩形写回均来自原生调用和 SDL。源注册信息不能再触发缓存或页面重画，既有原生缓存也不会因为语言版本改变被组件集合改写。

这是对共用擦除原因的整改，不是所有界面即时切换目标的完成证明。没有为未知页面增加清屏、模拟按键、猜测字段、保护或回退分支。

## 文化选择页完整原生续执行

新接入点的指令已对本机 3.89.1 原 PE 只读反汇编；原始摘录保存在本地 `20261110-culture-native-reconstruction-disassembly.txt`。普通文化菜单构建、英文记录及 `MENULIST.SAV` 文件写读没有改变。

| 原生边界 | 处理及依据 |
| --- | --- |
| `D12B4` | 只有文化刷新请求、原生非按键返回 `-2` 且真实 `[EBP+4]==base+F8D4` 时，转 `D19B3` 退出原 D1120 帧。保留原 `F8CF` CALL，使返回地址可确认。 |
| `F8D4` | 五字节 `8B D8 83 FB 64`，均为完整、可原样重放的指令。重建阶段执行平衡原片段 `12EEC..12F2E`，然后在同一个 F4F0 帧继续 `F675`。不执行当前输入的动作查找。 |
| `12EEC..12F2E` | 原父窗口标题与面板构建，含 `12F0D → 116270` 及原背景模式切换。五个栈参数由 `12F12 ADD ESP,14h` 平衡，没有读取外层 EBP；结束于 `12F29` 原调用的驻留返回边界。没有重入原父函数的资源、光标、输入或角色生成流程。 |
| `12F29 → 10AF90` | 新 CALL Hook，原字节 `E8 62 80 0F 00`。仅文化重建期间跳过这一次部分上传；普通进入保持原调用。Host 既有 fragment 返回处理在跳过原调用后也消费同一个返回边界，无需修改驻留桥。 |
| `F675..F7BF` | 原生取回 `[EBP-78]` 的 EBX 局部，执行完整 CFFB0、从当前真实选择形成英文文化主题，再执行完整 3CA90。简介背景、标题、摘要和 F1 行均由原生函数构建。没有读取旧 Scene 来补画。 |
| `F67D` | 五字节 `A1 <base+5F54AB0>`。原生已经按当前语言重画菜单时清除文化 pending；未来正常进入该页不消费过期请求。 |
| `F819..F8CF` | 原随机选择分支仍由原状态判断。当前人工选择页经 `F8CF` 进入 D1120，保留其原选择与 `[EBP-78]`，不会因语言切换重做随机选族。刷新不进入 `F9D9` 的角色文化写入。 |
| `D1120` | 原 `D1189` 保存完整新页面到真实菜单缓存；原选择、上传及呈现流程随后消费该缓存。Mod 不代替其缓存保存和呈现。 |

## 主菜单及其它边界

主菜单在真实 `Scope::menu_input` 请求后，于 D12B4 的原生 `-2` 返回同步执行已确认的 `125BA3..125BE1`。该片段构建完整页脚、菜单框、版本和菜单，栈平衡且不依赖外层局部；原生背景完整保留。恢复真实当前选择及 D1120 的选择局部、重画标记和 EBX 后继续 `D1167`，由原 D1120 自己保存菜单缓存并呈现。没有再使用旧的“补入 Scene 面板再全页物化”路径。

设置、先祖、属性确认仍使用各自已确认的完整原帧 continuation。属性页修正是本次开始前已有的工作区修改，本次保留其源码和双 u32 状态。文化及主菜单请求增加 pending 位；文化重建仅增加一个阶段值，不保存帧指针、页面、布局或绘制贡献。现有 HDA7 序列化字段、枚举原值和 Host ABI 不变。

技能、法术、百科、消息、世界页、关于/鸣谢以及姓名阶段的已完成前序面板等，不能再通过 Scene 统一立即重画。其原生像素与缓存保持，由实际后续原生构建消费所选语言；已存在的独立原生重建路径继续按其实际触发条件工作。当前没有确认一个可以让任意原生页面完整重建、同时不重做业务的公共接口。`docs/rebuild-design.md` 所记“全部已接入界面即时切换”仍未完成，不把逐页 continuation 或保留旧画面声称为该目标完成。

## 既有不合规结构与待整改状态

- `native_ui_scene.cpp:12/17/314` 的 `Child/Container/cache_saved` 及 `save/restore` 仍保留旧组件来源及缓存引用图，用于现有 HDA7 生命周期交接；本次已删除其页面、缓存绘制能力，但完整来源图和大量历史组件绘制 API 尚未整体退役。后续须继续拆分为必要的原生文本绑定与资源身份，不能再接成整页绘制序列。保留格式不代表旧设计合规。
- `native_renderer_component_binding.cpp:632::paint` 及其子组件序列重建仍存在于代码中；本次 Scene 路径已不再调用，不能重新用于通用缓存恢复。全面清理该历史架构仍待整改。
- `native_footer_component.cpp:88::paint` 仍根据 sibling 几何独立安排署名、版本和精灵；原生正常页脚完成时仍调用，违反原生排版所有权，待整改。本次未扩大署名授权。
- `docs/rebuild-design.md` 全局语言切换段及旧公共 UI 交付文档关于 Scene 的完成/所有权表述已失效；README 与设计段首已显式更正。历史发布成功不证明完整性与合规性。

## 交付状态

源码修改、静态审查、统一队列编译、正式文件发布及兼容业务交接均已完成。提交后至批次结束没有继续修改该请求范围源码。根入口为：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

- 请求 `bbe3778896c149cdb46c4f1db83feec9`，批次 `97195fea02d04a98982a858d42d08e9d`。已读取对应 `results/<请求>.json` 和 `batches/<批次>.log`，结果为 `Success=true`。一次配置、一次增量构建，无清理或重复入队。日志含既有函数指针转换、初始化、未使用项、缩进及 extern 警告，无编译错误。
- 发布事务 `6f72917539324bd481ae0f5f75b79328`，2026-11-10 12:07:17（Asia/Shanghai）完成。已读取 `build/mingw-x86/stage/6f72917539324bd481ae0f5f75b79328/publication-result.json`，`success=true`、`runtime_requested=true`。
- 正式替换 `package/modules/uwcn_adapter.dll` 与 `package/release.json`；旧两件先移入 `回收/20261110-120716-6f72917539324bd481ae0f5f75b79328/package/`，保留原相对路径，已读取文件身份。正常根 `uwcn_launcher.exe` 加载路径已更新，无平行修复包。
- 原有 Proton 游戏进程 Windows PID `364` 返回 `ReadyToPublish 6f72917539324bd481ae0f5f75b79328`，随后返回 `Applied 6f72917539324bd481ae0f5f75b79328 adapter:b0a57ce64b3c4d5e146aad30f4eca0950956a75941400063013047c3603d09dd:3`；事务记录 `applied=true`。这是授权的兼容业务模块交接，没有要求用户卸载、重启或切换界面。
- 正式 Adapter 与构建输出 SHA-256 均为 `b0a57ce64b3c4d5e146aad30f4eca0950956a75941400063013047c3603d09dd`，与 Applied 回执一致。

没有启动游戏、关闭/重启游戏、注入、模拟输入、运行产物或测试；没有创建测试用例、脚本、断言、保护或兜底分支。不以编译、发布或 Applied 回执代替用户画面验收，也不宣称任意界面即时语言重建已经完成。
