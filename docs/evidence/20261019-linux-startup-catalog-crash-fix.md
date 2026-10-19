# Linux 启动音频词库缺项导致的闪退

日期：2026-10-19。用户在上一批 Adapter 发布后再次反馈闪退。本次依据该次实际 core、游戏日志、原生 ELF 和本机资源文件静态排查，没有启动游戏、附加进程、运行产物或测试，没有新增测试和断言。

## 新的崩溃证据

- systemd-coredump：PID `3671260`，时间 `2026-10-19 10:54:05 +08:00`，信号 `SIGABRT`。
- 当前正式 Adapter SHA256 为上一批的 `15220fa8c0b766fe860709d8ab3817769281f576f9731258bcc4ff2dfc4c9139`。
- 栈为 `require(Status)`（Adapter RVA `0x2309`）→ `translated`（`0x51cf`）→ `startup_draw`（`0x71a9`）→ `uwcn_linux_gateway`。这是后续中文资源名查询失败，不是上一份 core 的 `erase(npos)` 越界。
- 离线 core 中 `translated` 的 R14 为 `2`，对应 `Status::unavailable`。栈上 TextRequest 为组件 `0x204`（`startup_audio`），原文地址 `0x7ffef72d79d0`，value 地址 `0x7ffef72d79df`；内容分别为 `Loading audio: ritual` 与 `ritual`。
- `modules/semantic/semantic.cpp` 为该组件查询 `startup.resource.ritual`；原正式 `catalog/zh-CN/main_menu.tsv` 没有此键，`modules/catalog/catalog.cpp` 返回 unavailable，随后 Adapter 的 require 抛出异常。
- 游戏自身 `init_log.txt` 记录已载入 `music_ritual.ogg`、开门音、雨声，随后 `audio/ritual.ogg` 已加载成功，最后为 `Loading audio: ritual`。这也将音频文件加载成功与显示词库缺项区分开来。
- 离线 core 及摘录位于本地 `build/analysis/startup-crash-20261019-1054/`。

上一轮修正了扩展名处理和七参数调用，但未完成本机启动音频词库的全量对应，遗漏了本次触发的资源键。上一轮构建发布成功不等于完整启动流程已确认。

## 静态资源清点与修复

原生 `load_samples` 按 `.ogg` / `.wav` 枚举本机文件，并执行其已有 `Lataa_Sample` 名称提取；另有固定的 `load_sample` 资源名调用。依据 ELF 的文件名提取及原生跳过 `smear.wav` 的分支，核对本机文件和现有词库。完整来源与清单见 [Linux 启动音频键静态记录](20261019-linux-startup-audio-keys.txt)。

本机共有 126 个 `.ogg` / `.wav` 文件，排除原生跳过的 `smear.wav` 后得到 102 个目录显示键；42 次硬编码调用提供 29 个唯一键，与目录键并集为 113 项。修复前词库覆盖 109 项，缺失集合恰为下列四项，均不是大小写差异。

本轮在 `catalog/zh-CN/main_menu.tsv` 补齐四个已确认且可达的显示资源键：

| 原生文件 | 原生显示键 | 中文 |
| --- | --- | --- |
| `ritual.ogg` | `startup.resource.ritual` | 仪式乐曲 |
| `ritual2.ogg` | `startup.resource.ritual2` | 仪式乐曲 2 |
| `ritual3.ogg` | `startup.resource.ritual3` | 仪式乐曲 3 |
| `windfly2.ogg` | `startup.resource.windfly2` | 风掠声 2 |

`smear.wav` 被原生已有分支排除，不添加其显示键。保留已有 `music_ritual`、`windfly` 等键，原生资源名、加载业务、日志和 UI 流程保持原样。没有加入未知键替代、异常吞掉或回退逻辑。

并行只读审查还核对了开场 11 行的原生计数、两句开场与版本参数、主菜单 `ListEntries` 行序、页脚版权格式及相关段落/字形桥。所查调用与 ELF、已有词库一致，没有在此范围确认需要追加修复的崩溃点；此结论不等于运行验证。

## 交付状态

词库源码已修改，统一队列增量构建与正式发布已完成。本机高清目标、缓存刷新和 Linux 热发布协议等未完成边界仍见 [Linux 移植记录](20261019-linux-native-port.md)，此次不改变其状态。

2026-10-19 10:56:38（Asia/Shanghai）通过根入口交付：

```bash
.toolchains/powershell/pwsh -NoProfile -File ./build.ps1 -Toolchain Linux -Module catalog -Publish
```

- 请求 `cf0c6c6d96784a79b623a9fde0c57e72`；批次 `1f30069c69094ee08a939ee23cea5c51`；发布事务 `8676727767384a8e907d211540e4e643`。
- 已读取请求结果 JSON、完整批次 `.log` 与事务 `publication-result.json`，构建和发布均成功，未请求 Reload。
- 一次配置、一次 Catalog 增量构建。C++ 源码本轮未改，Catalog 二进制沿用已有文件；正式更新的是 `package/catalog/zh-CN/main_menu.tsv` 和 `package/release.json`。不能把此批描述为重新编译了 Adapter 或换了启动器。
- 正式词库与源词库 SHA256 同为 `9f60f42f7f458d701c0f7748ececfc2c5b89c061be1fdfc835b75fbfbcd8db58`，与发布清单一致；正式文件中已包含全部四项。
- 旧词库、旧清单和发布脚本维护的旧应用菜单链接已先移入 `回收/20261019-105638-8676727767384a8e907d211540e4e643/`，保留原相对路径。回收词库 SHA256 为 `ea54375a733665d28e542b2b68471bbf830620cb4da4a42965c03263c9cb1cd7`。
- 仍使用根 `uwcn_launcher` 与相邻正式 `package/`，没有新建平行运行目录。

没有运行游戏或测试，不能据静态清点、增量构建和发布成功声称实际启动已通过。
