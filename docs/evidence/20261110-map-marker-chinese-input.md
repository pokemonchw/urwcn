# 地图自定义标记的中文输入

2026-11-10。对象为用户截图中的 Windows 3.89.1 已知区域地图标记编辑器。原 PE 为 `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。下表地址为 RVA；[原始指令](20261110-map-marker-chinese-input.asm) 使用 VA（基址 `00400000`）。仅静态分析、编译和授权业务发布，没有启动或操作游戏、模拟输入、运行测试、编写测试用例或断言。

## 原因和原生边界

既有中文输入只在 `119AB → 10F5B0` 的角色姓名调用启用。地图使用另一套原生 `10F950` 编辑器，之前虽有文字编码与光标度量接口，但没有文本事件接入，且原退格只删除一字节。

| 原生边界 | 静态依据与本次处理 |
| --- | --- |
| `E47E2/E4812 → 10F950` | 分别编辑标记的第一、第二行；原输入、前值、颜色和坐标参数保持。原返回字符串逐字节复制回原记录，不产生显示 token |
| `10F97D..10F996` | 游戏分配并清空自己的 1024 字节 ring 槽，`[EBP-40h]` 保存本次槽；Mod 不另存输入文字 |
| `10FB99` | 原编辑上限为64字节；中文提交沿用同一预算，仅追加能完整容纳的 UTF-8 标量。常见汉字每行最多21字，可与英文混输；不扩张记录或存档字段 |
| `10FA4D → 10E260`（已有 `5265`） | 在实际完整文字调用启用系统文本输入，借入显示编码和原生 Renderer 文字作用域；返回后释放本次借用。原 ring 中保留 UTF-8 |
| `D1F70..D1F81` | 复用原 `SDL_TEXTINPUT` 完整字符串及既有 `5401`，返回原生 `-2`，不伪造按键或事件。原 Ctrl/Alt 的 StopTextInput 边界在实际编辑期间沿用姓名输入的已确认处理 |
| `10FB17 → D3BF0`（已有 `51EF`） | 在真实 Before 开启输入，在 After 提升热发布前已打开的原生目标；语言重建区分真实文本提交和语言唤醒，保留提交字符串 |
| `10FB4D`（新增 `5410`） | 完整 `CMP EBX,8 / JNE` 的两个分支由回调显式续接。真实提交追加到 ESI 所指原 ring；退格扫描完整 UTF-8 标量后删末字；随后均回 `10FA10` 原完整重绘。普通输入继续 `10FB52/10FB6F` 原路径 |
| `10FA77`（已有 `5266`） | 复用原完整输入串和当前软件 Renderer 的字形度量计算原光标宽度，不按 UTF-8 字节计宽 |
| `10FA7E → 10E260`（新增 `5411`） | 从这次原生下划线、真实目标原点 `[EBP-34h/-38h]` 与原输出矩形的 `y-2` 关系设置系统候选区域；窗口变换仍走既有 SDL 接口。Mod 不绘制预编辑或候选 UI |
| `10FC08`（新增 `5412`） | 原 FreeSurface 间接调用前结束输入状态并关闭系统文本输入，原销毁调用照常执行。Enter、Escape、原 `-42` 双 Escape 哨兵及两行切换全部继续原逻辑 |
| `E1340` 的 `E1400/E1476/E14D6` | 原标记记录按完整 `0x5B0` 字节读取、写入和原位替换，未改写其保存流程；中文作为玩家自己的 UTF-8 内容进入原记录 |

`native_name_input::State` 仍为原有两个 u32：active=1 表示姓名，active=2 表示地图编辑器，committed 表示真实文本事件。没有新增状态分节、宿主 ABI、驻留库或 Loader 修改。新增 Hook 仅对静态确认的 3.89.1 安装；3.89 本次不新增地图输入能力。

## 原生目标和高清绘制

- `10F9CA` 的原 `SDL_CreateRGBSurface`（返回 `10F9D0`）确认 flags=0、宽516、原字体高度+2、深度32、RGBA masks=0。目标扩展接入同一真实构造点，以原逻辑尺寸和当前输出密度分配表面；其后的原软件 Renderer 采用对应密度。
- `10FA98..10FAA1`（新增 `5413`）原来直接把表面的物理 w/h 放进显示目的矩形。此处仅把两项尺寸读数扩展为同一原构造的逻辑宽高，原 x/y、矩形管理、清屏、上传、SDL_RenderCopy、呈现和销毁保持原流程。
- 热交接时已经停在 `10FB17` 的旧原生编辑器，确实持有上一版未扩展、未登记的表面。`native_targets::promote_text_field` 只在该真实 After 边界，按确认的原构造参数及此表面的原逻辑 w/h 创建新目标，更新原帧的两个资源局部，释放旧 Renderer 和表面；下一次 `10FA19` 自行完整清屏重画。没有复制旧像素、扫描表面、保存文字或重放内容。新构造已登记的目标沿用原资源。
- `10FAAE..10FB0A` 原生流程在等待前销毁本轮上传纹理，因此上述资源交接没有借用仍存活的纹理或改变缓存生命周期。
- 最终文字仍由原 `10E260 → 10DE90` 的完整字形调用同步绘入真实目标；既有纹理上传管理已经绘入的像素。`hud_native.inc` 的同一叶调用同时接受明确的 Unicode 作用域，使切到英文界面时玩家中文仍可绘制。没有独立坐标表、输入控件、整页快照、全局像素跟踪或延后绘制贡献。

## 既有待整改项

- `modules/adapter/native_footer_component.cpp:88` 起仍由 Mod 计算署名宽度、位置及间隔，影响原生布局所有权，待整改；本次不扩展。
- `modules/adapter/module.cpp:475` 的 About 按钮居中例外仍由 Mod 计算 center_x，影响原生布局所有权，待整改；历史授权注释不能替代当前约束。
- `modules/adapter/native_ui_scene.cpp:12` 起历史 Child/Container 集合及序列化尚未完整退役，待整改；本次没有借用它们重放输入框。

## 交付状态

源码、静态证据、统一队列编译、正式文件发布和当前进程的兼容热交接均已完成。没有自行运行系统候选窗交互、输入、保存或画面验收。

第一次请求 `641901c8e8fd425db00cd96daf62e9a9`／批次 `01078a0c56004952bed9df15604a3205` 已生成 Adapter，但发布事务 `7ad033beed6f4e5688370948e93e7e3d` 连接旧 Windows PID 364 管道超时。已读取该 result JSON、完整批次日志和 `publication-result.json`：prepare/commit 回执均为空，`ready=false`、`applied=false`，正式文件没有移动；回执中的归档路径仅为预定位置，实际没有创建该归档目录。不能把这个失败批次报告为发布成功。

随后只读进程列表确认当前游戏 Windows PID 为368（Linux PID3071321，18:28:54由用户现有启动流程创建），改用正确 PID 通过同一根队列重试发布；本任务没有启动、关闭或重启游戏。使用命令：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 368 -WinePrefix /home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 最终回执 |
| --- | --- |
| 请求 ID | `5e8c415107af4910a6cdf7ea9865a540` |
| 批次 ID | `4f9f78c701cc47f9ba8693e68f6801d4` |
| 发布事务 | `dbd496d6f5494eabab8b5281b8490ffc` |
| 完成时间 | 2026-11-10 18:38:01（Asia/Shanghai） |
| 队列结果 | `Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 驻留回执 | PID368 `ReadyToPublish` 后返回 Adapter 第2代 `Applied` |
| 正式 Adapter SHA-256 | `5cea79b97e1b5b34226dbbf12b4d7900fa7304dd2137546360bdb51e9dad38bb` |

已读取最终 `build/.compile-queue/results/5e8c415107af4910a6cdf7ea9865a540.json`、`batches/4f9f78c701cc47f9ba8693e68f6801d4.log` 和 `build/mingw-x86/stage/dbd496d6f5494eabab8b5281b8490ffc/publication-result.json`。重试没有源码变更，沿用首批已编译 DLL；没有重复提交等待中的请求或另开构建树。首批保留既有函数指针转换、未初始化成员、extern 初始化、未使用项与缩进警告，无编译错误。

正式更新 `package/modules/urwcn_adapter.dll` 和 `package/release.json`；替换前的旧件已先按原相对路径移入 `回收/20261110-183800-dbd496d6f5494eabab8b5281b8490ffc/package/`。旧 Adapter 的 SHA-256 为 `e6bd92a5a1a7a80c7f29b54e177a16278227bbcbdcd13e041bf92b0d7730d361`；新正式文件与构建输出哈希一致，且与 Applied 回执一致。根启动器的正式加载路径已更新，没有平行修复包或重启要求。Applied 仅证明业务交接成功，实际输入效果由用户验收。
