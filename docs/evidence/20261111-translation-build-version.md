# 汉化版本增加编译时间

2026-11-11。用户要求与 dfcn 一致，在现有汉化版本前增加编译的年、月、日、小时。显示格式为 `yyyy.MM.dd.HH.XXXXX`，其中 `XXXXX` 保留现有五位大写字母数字内容指纹。月份、日期和小时补零。

后续错位修正：用户要求版本标签与号码分行、仍放右侧。版本来源和格式保留，署名文字链改为原生逐行居中；布局修改与仍待整改的外层所有权边界见 [页脚错位记录](20261111-footer-alignment.md)。

## 静态依据与修改

- 本机 `/home/lulika/workspace/dfcn/tools/build.py:715` 的 `stamp_core_version` 将 `build_hour + '.' + 五位指纹` 写入版本槽；`:858`、`:1103` 使用本地 `datetime.now().strftime("%Y.%m.%d.%H")` 取得编译小时。`src/credits.inc:4` 的占位格式为 `0000.00.00.00.00000`。
- `cmake/build-once.ps1` 在统一队列的每个批次开始时取得本地编译小时，成功完成增量编译后写入 `out/build-hour.txt`，内容为13个 ASCII 字符加 LF。时间不在运行时生成，也不取正式发布时间；不发布的编译只修改构建目录。
- `publish.ps1` 将这个文件作为 `metadata/build-hour.txt` 加入既有候选、哈希清单及发布事务。后续仅编译某个业务模块时也发布该批次的编译小时，无需为日期重编 MainMenu。替换已有时间文件时与其他旧交付文件一起先移入根 `回收/` 的事务目录，保留相对路径。
- Windows `modules/main_menu/main_menu.cpp::generate_translation_version` 读取正式 `package/metadata/build-hour.txt`，在原五位包内容指纹前加上编译小时和句点。原六个业务模块及五份词库的 SHA-256 输入、Base36 编码和字母数字混合规则不变。必要文件读取失败沿既有 `Status::unavailable` 返回，没有启动时间、文件时间或旧五位版本回退。
- 继续只缓存最终版本字符串；既有 `kModuleDependenciesChanged` 清空它。`src/loader/host.cpp::restore_modules` 在所有选定模块恢复后通知全部六模块，因此只更新 Adapter 等模块时也会重读新时间及包指纹。
- 继续通过 `TextComponent::translation_version`、Semantic、`main.translation_version` 和既有页脚组件进入原生文字路径。本次没有新增 UI 字段、固定坐标、行槽、文字回放或宿主 ABI。本轮显示修改针对截图中的 Windows 页脚；Linux `src/linux/main_menu.cpp` 仍为原透传实现，不据此宣称新增 Linux 署名显示。

## 既有所有权问题

以下是静态阅读中发现的既有问题，仍待整改，不以本次版本修改、编译或发布视为合规：

| 文件、位置 | 影响 | 状态 |
| --- | --- | --- |
| `modules/adapter/native_footer_component.cpp:97` 起 | Mod 测宽并自行计算署名列宽、横向位置、图文间距，违背布局归原生 UI 的要求；长版本继续经过这条既有路径。 | 本次只改版本来源，页脚布局所有权待整改。 |
| `docs/design.md:19` | 历史说明仍列固定行槽、DisplayPlan 和 ABI 3 元数据路径，不符合当前约束及实现。 | 待清理；不能作为本轮 UI 依据。 |
| `docs/evidence/main-menu-branding-version-static.txt:20` 起 | 历史说明称无编译日期，并保留旧元数据、DisplayPlan 与交接约定。 | 历史记录已标明被后续版本记录取代，正文待清理。 |

## 交付状态

源码修改、统一队列编译及正式文件发布均已完成。根入口如下，没有绕过队列；只执行一次配置与一次 MainMenu 增量编译，完整日志无编译警告或错误：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module main_menu -Publish
```

| 项目 | 实际结果 |
| --- | --- |
| 请求 | `dadadca25265416d9d7d29c437d71e07` |
| 批次 | `87e3ba4a229a4e8598784279b0d6c943` |
| 请求结果 | `build/.compile-queue/results/dadadca25265416d9d7d29c437d71e07.json`：`Success=true`、`PublishRequested=true`、`ReloadRequested=false`，已读取 |
| 完整日志 | `build/.compile-queue/batches/87e3ba4a229a4e8598784279b0d6c943.log`，已读取 |
| 正式事务 | `bc8d6da2bd534128bd670c4ba04f1da5`，2026-11-11 14:31:14（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/bc8d6da2bd534128bd670c4ba04f1da5/publication-result.json`：`success=true`、`runtime_requested=false`，已读取 |
| 正式变更 | `package/modules/urwcn_main_menu.dll`、`package/metadata/build-hour.txt`、`package/release.json` |
| 正式编译小时 | `2026.11.11.14`，从正式时间文件读取 |
| MainMenu SHA-256 | `d69b1e69650ca19ed2fdeede66572b83f2f2acf22a211f46f4ffdf8378e280f1`，正式文件与发布清单一致 |
| 时间文件 SHA-256 | `24b73794f60a00e4e39788ae3605cb45b823deebfa79387030735af5414948c0`，正式文件与发布清单一致 |
| 旧文件回收 | `回收/20261111-143114-bc8d6da2bd534128bd670c4ba04f1da5/package/` 下保留旧 MainMenu DLL 及 `release.json`；时间文件为首次新增 |

只读进程检查中最初存在宿主 PID `3318393`，提交前的最新进程表已无 `urw.exe` 或 `urw3-bin`，Windows 进程枚举也无游戏进程。本次因此只发布正式文件，没有发起驻留热交接，没有 Applied 回执。正式根启动器继续加载同一 `package/`，没有平行修复包。

没有启动、关闭、重启或注入游戏，没有模拟输入、自行测试、编写测试用例、测试脚本或断言；编译仅用于生成交付产物。授权的兼容热发布使用既有驻留事务，Applied 不代表画面验收。
