# 按键帮助页正文拉伸：原生上传纹理尺寸修正

日期：2026-11-10。用户提供截图，正文仅剩被放大的搬运、推物品两行，键帽和蓝色章节条纵向拉伸；底栏比例基本正常。这是上一版接入引入的尺寸错误。仅阅读该截图、磁盘 PE、源码与发布日志，不启动、关闭、重启、注入或模拟操作游戏，不运行测试或创建测试用例、断言。

后续 Shift+F10 闪退报告确认需另行纠正本页重建入口的栈深度；该问题与本次纹理尺寸修正分别记录。下文原重建路径已由[语言切换栈修正](20261110-keyboard-help-language-stack-fix.md)更新，旧 Applied 不是该路径正确的证明。

## 已确认的两个不同构造契约

对象仍为 Windows 3.89.1 / Steam Build `26139145`，PE SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。沿 `build/analysis/keyboard-help-3891.asm` 及完整反汇编读取以下指令，地址为 RVA：

| 构造段 | 原生输入 | 含义 |
| --- | --- | --- |
| `103BD5..103BF0` | `PUSH 0x514`、`PUSH 0x320`，调用 `SDL_CreateRGBSurface` | 正文逻辑表面800×1300；已有接入按真实画布密度分配物理表面 |
| `103B5A..103B6D` | `PUSH [EBX+0xC]`、`PUSH [EBX+8]`，调用 `SDL_CreateTexture` | 底栏纹理直接读取对应表面的实际高宽，已经是物理尺寸 |
| `10528F..1052A6` | `PUSH 0x514`、`PUSH 0x320`，调用 `SDL_CreateTexture` | 正文纹理仍传固定逻辑尺寸，不能当成已经扩展的物理尺寸 |
| `1052AC..1052C3` | 从 `[EBP-43C]` 读取真实表面，传 `[surface+0x10]` pitch 与 `[surface+0x14]` pixels | 全纹理上传使用刚绘制完成的物理表面 |
| `105354..105369` | 从 `A44B798` 正文纹理，按原生 `x/y/800/600` 源矩形复制到视口 | 现有接入按纹理密度转换源矩形；所登记的尺寸必须与真实分配一致 |

上一版 `modules/adapter/native_targets.cpp::create_texture` 在 `site==0x1052AC` 时只执行 `textures.emplace(result,help_upload_scale)`，实际 `SDL_CreateTexture` 仍收到800×1300。表面绘制、物理 pitch、纹理实际尺寸和源矩形换算因而不一致。`docs/evidence/20261110-keyboard-help-native.md` 中“正文上传接入同一密度协议”的旧说明仅记录了元数据接入，遗漏实际纹理分配，不能作为正确高清路径的证明；本次明确更正。

## 源码修正与重建

在同一确认返回点 `1052AC`，调用原 `SDL_CreateTexture` 前，将其高宽换成同次原生表面构造提供的 `help_upload_scale.physical_width/physical_height`。既有登记随后使用同一描述。原生上传直接消费同一个物理表面和 pitch，源矩形仍由原输入与密度换算得到。

底栏继续消费它原本提供的物理高宽；滚动视口继续由它自己的原生构造管理。没有增加字体放大、坐标补偿、替代页面、像素扫描、绘制记录或失败回退。译文、按键动作、滚动位置与原始逻辑尺寸不变。

兼容热发布复用现有 `View::keyboard_help` 修订请求：已打开页的真实 `10539B` 输入续点回到完整原生构建段，旧正文纹理、底栏与视口按原 owner 退役后重建。没有新增保存字段或修改驻留 ABI。

## 交付状态

源码已保存，通过项目根统一队列完成一次配置和一次增量构建，只重编 `native_targets.cpp` 并生成 Adapter。命令为：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 368 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `85fded139f3e4002baf2128815afd550` |
| 批次 ID | `3f68874e07c047a09cb427f9ed598908` |
| 队列结果 | `build/.compile-queue/results/85fded139f3e4002baf2128815afd550.json`：`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 批次日志 | `build/.compile-queue/batches/3f68874e07c047a09cb427f9ed598908.log`，已读取全部249行，保留40条既有 SDL 函数指针转换警告，0条编译错误 |
| 正式事务 | `a45c8345ef5a43e8b12a63e009cc4dcb`，2026-11-10 15:48:53（Asia/Shanghai）完成 |
| 正式结果 | `build/mingw-x86/stage/a45c8345ef5a43e8b12a63e009cc4dcb/publication-result.json`：`success=true`、`applied=true` |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/release.json` |
| 旧件归档 | `回收/20261110-154851-a45c8345ef5a43e8b12a63e009cc4dcb/package/`，保留原相对路径 |
| 旧 Adapter SHA-256 | `d08b987f054114903cb19de30f8a593e8140aae393345af47cdddd196ca4a7d0` |
| 新 Adapter SHA-256 | `92e043dcbc92d0846330a1afa1c7c04094d7ffdfd1c70ef9f782e1a4e1da3e75`，构建件、正式件与 Applied 身份一致 |
| 当前进程 | 宿主 PID `2970998`，Windows PID `368`；使用既有 Proton Mono 解释器只读枚举确认 |
| 兼容交接 | `ReadyToPublish` 后 `Applied ... adapter:92e043dcbc92d0846330a1afa1c7c04094d7ffdfd1c70ef9f782e1a4e1da3e75:2`，第2代完成 |

已读取上述请求结果、完整批次日志、正式发布结果、新旧文件身份和末条 `Compatible module transaction applied.` 日志。源码修改、产物编译、正式文件发布和当前进程交接均已完成，无平行交付包；根 `uwcn_launcher.exe` 消费同一正式包，无需退出或重启。没有运行游戏产物、测试、输入模拟或自行画面验收。Applied 证明交接，不作为视觉效果已正确的证明。
