# 风景图地形标题原生汉化

日期：2026-11-10（Asia/Shanghai）。用户截图中湖景图片底部的 `Lake` 未汉化。已有 `terrain` 词库包含 `Lake → 湖泊`；此前使用物品页修正的是另一个地点行消费者，未覆盖这个图片记录的标题。本次只阅读用户截图、源码、磁盘原始 PE 和逐指令反汇编，没有启动、操作或模拟输入游戏，没有运行测试、创建测试用例或断言。兼容业务交接使用已授权的驻留发布事务。

## 原生静态依据

安装目录 `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe` 为 3.89.1 / Steam Build 26139145，SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`，首选基址 `0x400000`。下表均为 RVA。磁盘逐指令依据保存于同目录的 `20261110-landscape-caption-producer.asm`、`20261110-landscape-caption-consumer.asm` 和 `20261110-landscape-caption-outline.asm`。

| 边界 | 已确认的原生语义 |
| --- | --- |
| `903CC → 116C10`，`903DA` | 原生按图片文件、标识和组选择图像记录；返回索引乘原生记录步长 `C48`，保存到 ESI |
| `903E2..9040E` | 原生复制实际图片矩形到记录，设置原类型字段 `A385230+ESI=5` |
| `90418 → 7520` | 原地形生产者，已有 `windows_message_geography.inc` 的 terrain 来源观察器 |
| `9041D..90432` | 原返回文字完整复制到原生记录 `A385234+ESI`；该记录继续保存英文 |
| `90434..90456` | 原生保存文字颜色，扫描同一标题并在 `90456` 执行 `LEA EAX,[EDX*8]`，字节为 `8D 04 D5 00 00 00 00` |
| `9045D..90496` | 原生 `CDQ/SUB/SAR` 使用字宽和图片实际矩形计算标题居中位置及纵向位置，写入记录；这些指令保持 |
| `10B3C0..10B457` | 原生遍历图像记录，按原资源和可见状态绘制图片，再绘制同记录的非空标题 |
| `10B44F → 10E3E0` | 完整描边文字调用，EDX 是原记录文字 x；栈参数为 y、完整文字、颜色、原保留字，调用者清理16字节；ESI 指向当前记录矩形，`[ESI+14]` 为原类型字段 |
| `10E3F6..10E41B` | 原文字包装器保存当前 renderer target，再选择主 renderer 的窗口目标 |
| `10E4BB/10E4D1/10E4E5/10E4F9/10E50E → 10E170` | 原生四次描边及一次前景调用，已有 `windows_renderer_text` 的完整字形消费者，使用当前主 renderer 实际比例即时绘制 |

记录地址是已确认的原生字段，不是 Mod 建立的坐标或行槽表。此次新增的两处物理指令以本机 3.89.1 原 PE 为直接依据，仅在 `windows_build::is_3891()` 分支注册。本轮未持有旧版完整 PE 或这两处旧版逐指令记录，不扩展 3.89 的图片标题入口；旧版已有接入保持原范围。

## 源码与生命周期

`modules/adapter/windows_renderer_text.inc` 新增独立 Hook ID `7C10/7C11`，保留既有 Hook 编号、字段、序列化与驻留 ABI。

- 在原生 `90456` 度量边界使用完整 `message_value/terrain` 译文及已有 renderer 度量接口，替换原 `strlen*8` 的 EAX；后续原生中心计算、图片矩形与记录坐标写入继续执行。英文模式执行原指令。
- 在原生 `10B44F` 完整文字调用仅处理已确认的类型5地形图标题，同一原生调用临时借用编码后的完整中文。原生记录中的英文、图片标识、分组、文件名、可见性与业务值保持。原调用返回即释放借用文字，不保留绘制位置、像素或待重放记录。
- 复用原有 `10E3E0` 的四向描边、前景、目标恢复及主 renderer 实际输出密度字形绘制；没有在 SDL 上传、复制或 Present 处添加文字。图片及标题继续由原生 `10B3C0` 在自己的绘图生命周期中消费。
- 语言切换与兼容交接复用 `native_hud_language::rebuild` 的原生 `8FF70` 重建；其 `location_cache` 分支在构建期间进入原生构造，重新计算同一记录标题宽度。没有新建页面快照、重复游戏动作或模拟输入。

词库无需新增或重新生成；本次只编译和发布 Adapter。

## 既有待整改项

- `modules/adapter/native_footer_component.cpp:88` 起仍由 Mod 计算主菜单署名位置、宽度与间隔，影响原生布局所有权，待整改；本次不使用或扩展此路径。
- `modules/adapter/native_ui_scene.cpp:12` 起仍保留历史 Child/Container 集合及其序列化，完整退役待整改；当前这些记录已不授权整页绘制，本次不增加此类集合。
- `modules/adapter/native_renderer_component_binding.cpp:39` 的 Owner 仍保留 children 集合，`paint` 相关历史组件重建路径的完整退役待整改；影响既有 renderer 缓存所有权。本次标题由原生图像记录直接消费，不加入该集合或其重绘路径。

## 交付状态

源码修改已保存，通过根统一队列完成一次配置、一次增量编译与正式兼容热发布。Adapter 目标完成，保留既有函数指针转换、extern 初始化、缩进和未使用项警告，没有编译错误。提交后至所属批次结束未继续修改本次源码。请求 JSON、完整批次日志和正式发布 JSON 均已读取。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `7b31b0218d2541c091244df1346420e1` |
| 批次 ID | `983967fd1bc24b609462077ffc68d208` |
| 请求结果 | `build/.compile-queue/results/7b31b0218d2541c091244df1346420e1.json`，`Success=true` |
| 完整批次日志 | `build/.compile-queue/batches/983967fd1bc24b609462077ffc68d208.log` |
| 正式事务 | `c120ecf5458a483bb625c7af502d452b`，2026-11-10 17:15:37（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/c120ecf5458a483bb625c7af502d452b/publication-result.json`，`success=true`，运行时 `applied=true` |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/release.json` |
| 旧件归档 | `回收/20261110-171536-c120ecf5458a483bb625c7af502d452b/package/`，旧 DLL 与清单先归档再替换，保留原相对路径，已只读确认存在 |
| 兼容交接 | 当前 Windows PID `364` 返回 `ReadyToPublish` 后返回 Adapter 第14代 `Applied` |
| Adapter SHA-256 | 正式件、构建件及 Applied 回执一致：`54c4beb8bb5703ba3cce6a39b785e9bc08c3da884950c2aecd1f942cf6c21f75` |
| 归档旧 Adapter SHA-256 | `a270b2b9ce0d32d4c6df236e3df1753765601287b79015d14f249c2ce476fed2` |

源码修改、产物编译、正式位置发布及当前进程兼容交接均完成，根 `uwcn_launcher.exe` 使用同一正式包，没有独立修复包或平行启动目录。未启动、关闭、重启、注入或模拟操作游戏，没有运行测试或自行验收画面。Applied 仅证明模块交接完成。
