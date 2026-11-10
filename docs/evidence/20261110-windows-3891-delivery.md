# 不真实的世界 3.89.1 Windows 构建适配

日期：2026-11-10。用户目录选择后仍收到旧构建指纹拒绝提示。本记录区分源码、编译与正式发布，不表示运行验收。

## 本机原始文件与根因

启动器旁 `uwcn_launcher.ini` 已保存 `Z:\home\lulika\.local\share\Steam\steamapps\common\UnRealWorld`，实际文件存在。只读安装目录和 Steam 清单确认：

| 项目 | 本机证据 |
| --- | --- |
| 主程序 | `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe` |
| 版本 | `news.txt` 首条为 3.89.1；原生版本获取函数 `0x124690` 读取 RVA `0x1AFAC0` 的 `3.89.1\0` |
| Steam Build | `steamapps/appmanifest_351700.acf` 的 `buildid`、`TargetBuildID` 均为 `26139145` |
| SHA-256 | `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d` |
| PE | I386 / PE32，2,249,216 字节，首选基址 `0x400000`，入口 RVA `0x18A7D4` |

旧启动器仅接受 3.89 / Build `25939378` 的 SHA-256 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。因此本次拒绝有明确的版本差异依据，不能归因于目录选择失败，也不能只增加新指纹而不调整原生边界。

## 源码适配

- `src/launcher/main.cpp` 精确接受上述两个 Windows 构建指纹；其他文件仍不启动。拒绝提示显示实际选中的完整文件路径、读取的 SHA-256 和已适配构建，便于区分所选文件。目录选择、配置保存和 `--game` / `--game-dir` 的语义保持。
- `modules/adapter/windows_build.h` 在模块初始化、构造任何原生地址之前，根据已确认的新版原生版本字段选择构建。启动器的精确指纹限制先于模块加载；没有运行时地址搜索或模糊匹配。
- `windows_3891_rdata.inc` 保存 393 个逐项确认的旧数据 RVA。只有列表中的地址在新构建加 `0x10`，不推断整节、所有字符串或 `.data` 的统一位移。模块的旧 RVA 读取及四个原生组件文件消费该表，实际 native 指针仍通过原有 `ptr` 原样消费。
- `windows_message_values.inc` 只迁移四个物理 CALL 点：`BC7A9→BC7B9`、`BCD46→BCD56`、`BEB63→BEB73`、`BEEE2→BEEF2`；各条目的 Hook ID、目标、原寄存器/参数与语义身份不变。
- `native_renderer_component_binding.cpp` 中 `FAAA4`、`E3DD2` 两处 inline 补丁使用新版标签及原生矩形地址；HUD 图像文件名、标签来源身份、原生清屏矩形同步使用相应构建的数据地址。
- 新增 `profiles/urw-3.89.1-steam-26139145.json`。旧 profile 保留，旧词库 key 保留作为语义标识；历史字段仍说明其原始实现构建，新 profile 的 `build_adaptation` 明确物理地址转换。

这些修改只调整已有原生接入点的构建地址。没有新增 UI 排版、坐标表、像素跟踪、文字绘制重放、测试、断言、保护或推测性回退；原生业务、内部英文值、设置动作、布局、输入及缓存生命周期不因此改变。项目既有尚未整改问题仍以原纠正记录为准，不作全部合规或全部完成声明。

## 静态依据

- [CALL 与消息 inline 复核](20261110-windows-3891-hook-review.md)：2513 个唯一 CALL 站点，2509 原址一致，4 个发生已确认迁移；另对消息指令模板的零占位和填充操作数作独立静态解释。
- [原生组件与 ABI 复核](20261110-windows-3891-native-contracts.md)：77 处完整指令、原生资源返回边界、导入、字段及明确的数据操作数变化。
- [原文与资源对照](20261110-windows-3891-resources.md)：原文、格式参数来源、数据引用显式表、全部 744 个格式 key 和外置资源摘要。`GAME.NFO` 及八个消息文件与原资源相同，无需修改词库原文及其文件偏移。

未持有完整旧 PE，未声称新旧 `.text` 或函数体全部相同。静态记录仅证明所列的接入边界；本轮不启动游戏、运行交付产物、注入运行中游戏、模拟操作或执行测试，编译只生成交付产物。没有运行时 Applied 或画面验收结果。

## 编译与正式发布

源码修改已保存；通过根入口 `.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module launcher,adapter -Publish` 提交同一批次，仅做一次配置和增量构建。

- 请求 ID：`026e9aa9a5f542cd8956c99f6907900f`。
- 批次 ID：`d6c8601e49094735ba3946ae893c9d19`。
- 发布事务：`96cb3aa039a248c3a9f13aa55386d34e`，2026-11-10 10:18:08（Asia/Shanghai）完成。
- 已读取 `build/.compile-queue/results/026e9aa9a5f542cd8956c99f6907900f.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=false`；对应批次日志包含两个目标构建成功及正式发布成功回执。编译保留既有函数指针转换、未用符号等警告，没有借此修改无关代码。
- 正式替换根 `uwcn_launcher.exe` 与 `package/modules/uwcn_adapter.dll`，新增正式 `package/profiles/urw-3.89.1-steam-26139145.json` 并更新 `package/release.json`。旧启动器、适配模块和发布清单已先按原路径移入 `回收/20261110-101808-96cb3aa039a248c3a9f13aa55386d34e/`，只读目录记录确认旧件存在。未建立平行运行包。
- 发布前只读进程列表未发现 `urw.exe`、`urw` 或 `urw3-bin`，没有请求 Reload。驻留桥未修改；回执为 `Runtime Applied was not requested.`。本轮不宣称运行时应用或启动/画面验收。

| 正式文件 | SHA-256 |
| --- | --- |
| `uwcn_launcher.exe` | `78695f0440a8edda7d3fba7374d98cc5e9007ec904af8fe44de8ee766528afd0` |
| `package/modules/uwcn_adapter.dll` | `2b1f88b944b467fc114916763f8883b56dd0138ed4a1df30cfc90a967b3c35d0` |
| `package/profiles/urw-3.89.1-steam-26139145.json` | `d6768bb730ffbb07bc98e9452c92c723d8a2a053665cf7cf0b00c2c203e2c235` |
| `package/release.json` | `09120f34a4861ba9f5b6d2b8616f83197ad9e06426060635b09b81e488c2717c` |
