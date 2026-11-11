# 不真实的世界 Shift+F5 卸载与重载

日期：2026-11-10。用户明确要求第一次按 Shift+F5 后继续玩原版，第二次重新加载汉化。本记录区分源码、编译、正式发布及运行时应用，不表示运行验收。

## 根因与生命周期

当前 Windows 重构的 `src/loader/control_bridge.cpp` 只驱动外部发布事务，`modules/adapter/native_language_input.cpp` 只处理 Shift+F10；没有 F5 控制入口，也没有手动卸载、重载状态。

外部发布的 HDA7/NGT2 快照包含原生作用域、调用 token、中性组件构造源、菜单和原生资源身份，只能在原生线程短暂停驻时交接。卸载后继续游戏会改变这些身份。`native_targets::remove()` 也只退役网关，不会把已提升密度的原生画布降回原尺寸。因此不能把六库全卸载后放行游戏，再恢复旧快照。

本次采用以下明确边界：

1. 驻留层在真实 SDL 事件消费边界识别左右 Shift+F5，排除 Ctrl/Alt/GUI；新的物理按下提交一次请求，按键重复、释放和失焦由驻留控制处理。Poll、Wait、有限 Timeout 和 Peep GET 保留其他事件与等待语义，Peep ADD/PEEK 不触发动作。SDL2 字段及 `0x38` 事件步长见既有 `20261019-language-input-static.md`。
2. 首次按键在主线程、业务调用计数为零的控制边界，令 Adapter 沿已登记原生组件及缓存构造源同步重建原文，然后逆序 `shutdown/FreeLibrary` 五个实际翻译提供库：catalog、semantic、render、layout、main_menu。驻留 Loader 与原文模式的 Adapter 留驻，游戏继续运行；这不是六个业务 DLL 全部离开进程。Adapter 跟随真实菜单、消息、缓存与资源生命周期，不保存供以后重放的绘制贡献。
3. 原文编码使用已确认的原生 Nordic 字节映射，宽度使用原生每字节八像素推进；软件和 Renderer 文字回到原生字形叶调用，不依赖被卸载的字体、语义和编码服务。F10 不会在五库缺席时重新开启中文。Mod 姓名输入法接管暂停。
4. 第二次按键先保存此刻仍在跟随原生 UI 的 Adapter，再在停驻边界卸载它；从正式 `package/modules/` 按依赖顺序加载最新六库，恢复新鲜的原生作用域及稳定 SDL 网关身份，通知依赖并启用中文、同步重建缓存。不会把首次卸载时的旧 UI 快照恢复到已经变化的界面。
5. 已卸载状态收到显式兼容发布事务时，先完成上述重载，再执行所选模块的 PREPARE/COMMIT，不要求用户先手动加载。

新增 Adapter 操作为 `kNativeSetTranslation=3`、`kNativeTranslationAvailable=4`，输入均为一个 `u32`。没有改变 HostApi、ModuleApi、描述符或 HDA7 的布局，Windows Host ABI 仍为 1。

## 具体边界与待整改项

- 卸载后中文姓名的业务 UTF-8 字节保留，原游戏字形能力不包含 Mod 中文字体，不承诺该状态能正确显示中文姓名。重载恢复 Mod 输入与中文绘制；不改存档姓名或内部英文数据。
- `src/loader/host.cpp` 的实际退役或加载错误会记录失败并返回；现有全局 `enabled` 与完成态只在成功路径推进，失败后不承诺下一次 F5 自动恢复。此错误状态协议仍待整改；本次没有增加自动回滚或兜底。
- `docs/hot-reload.md` 保留的大量历史章节含 Footer 交接、独立 DisplayPlan、旧 ABI 及旧 F5 语义，不能作为当前实现依据。本次仅更新当前说明；历史章节与当前代码的全面文档对齐仍待整改。
- 现有 Windows ABI 1 驻留桥没有原位自替换入口。本次新增驻留控制只能由正常启动加载新版正式 Loader；不能通过兼容业务热发布装进已经运行的旧桥，不宣称该能力已实现。

## 交付状态

源码修改已保存，并通过根入口提交一次配置、一次增量构建及正式发布：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module loader,adapter -Publish
```

- 请求 ID：`449324e334d5400abcba0771a6913fba`。
- 批次 ID：`148c250353cd4b4eb9e6dc6358c93c62`。
- 发布事务：`7ef85aba20214f2ea88c5aeae6986cc6`，2026-11-10 10:43:35（Asia/Shanghai）完成。
- 已读取 `build/.compile-queue/results/449324e334d5400abcba0771a6913fba.json`、对应批次 `.log` 和 `build/mingw-x86/stage/7ef85aba20214f2ea88c5aeae6986cc6/publication-result.json`：编译及发布成功，`PublishRequested=true`、`ReloadRequested=false`、`runtime_requested=false`，没有运行时 Applied 回执。编译保留既有函数指针转换、未用符号、缩进及成员初始化警告。
- 正式更新 `package/urwcn_loader.dll`、`package/modules/urwcn_adapter.dll`、`package/release.json`。这三件旧文件先按原相对路径移入 `回收/20261110-104335-7ef85aba20214f2ea88c5aeae6986cc6/`，目录及旧 DLL 的 SHA-256 均已只读取得。根 `urwcn_launcher.exe` 沿用正式入口，没有平行运行包。
- 正式两件 DLL 的 SHA-256 与本批构建产物一致，也与正式发布清单记录一致。新驻留桥在下一次正常启动时加载；没有向运行中的旧桥注入更新。

| 正式文件 | SHA-256 |
| --- | --- |
| `package/urwcn_loader.dll` | `fdbe982ddc4e787b37a4f4df1cfe9fcb9fb1dbd457d8b04aa31450ebdbd14aad` |
| `package/modules/urwcn_adapter.dll` | `fed6bd6c4ea1981102b360ef8bd2f3be77fc4fa848845b02492fe8ba707bfc8d` |
| `package/release.json` | `d2f2fdf286bf56a4ec1bde1f511f5a719adce862ce4828f8de01cea2a9fc48d6` |

没有启动、注入、关闭或重启游戏，没有模拟输入、运行产物或测试；没有创建测试用例或断言。上述结果是源码、编译和正式文件发布结果，不是运行验收。
