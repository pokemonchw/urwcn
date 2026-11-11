# 关于窗口底部按钮横向定位修正

用户对比截图显示：中文正文已居中，底部按钮缩短后仍沿用原版左坐标，向左偏移。解释原生按钮没有居中入口及与项目约束的关系后，用户明确要求“给我挪位置”。本次将该授权仅用于中文模式的“关于”窗口底部按钮；由 Mod 计算这一按钮的横坐标，不将它描述为原生自动居中，也不扩大到其他组件。

## 静态依据

本机 Windows x86 3.89.1 / Steam Build `26139145`，主程序 SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。下述地址均为 RVA，直接读取磁盘 PE 反汇编；未运行游戏或测试。

- `124C31` 置 EDX=365；`124C3B` 以 `LEA ECX,[EDX-30]` 置左坐标335；`124C3E` 调用完整按钮 `114680`。原英文标签为两端含空格的 ` Press a key `，13字节。原生函数没有中心参数。
- `11469B` 将 ECX 存入 `[EBP-A0]`。`1146DD` 提交瓦片数；`114716` 随后取回该左坐标，用于左端帽、中间瓦片、右端帽和文字游标。`114740`、`1147FE` 两端帽宽均为7，`1147A1` 中间瓦片宽为8，故总宽为 `8*n+14`。
- 面板在 `124848 → 116270` 先于按钮构建，实际入参 x=10、width=780。`116371..116383` 的主体填充、`11643E..116448` 的边界计算均消费该原始 x/width；本页 flag `0x82` 中的 `0x80` 只影响标题条分支，不改变主体中心。代码读取该次原生构建已保存的输入，不复制这些坐标常量。
- 普通构建由 `native_component_binding.cpp::construct` 调用 `services.enter`；既有组件重绘由 `native_component_model.cpp::paint` 调用同一入口。`text_context()` 只消费 `Scope::text`，不会将按钮作用域的中心误用于逐字居中。

## 源码修改

- `modules/adapter/module.cpp::enter_component_paint`：仅在中文模式、`Kind::button`、原调用源 `124C3E` 及语义 `about_press_key` 一致时，从同原生 owner 的既有 `124848/about_title` 面板输入读取中心，放入本次 `plain_button` 已有的 `Active.centered/center_x`。
- `module.cpp::dispatch_native/about_button_width`：已有真实文字度量提交原生瓦片数后，仅对上述按钮调用定位修正。
- `modules/adapter/native_button.h::center`：用已提交的实际瓦片数计算按钮总宽，将 `[EBP-A0]` 设为面板中心减去半个按钮总宽；随后原 `114680` 继续绘制完整按钮。背景、文字、端帽一起移动，纵坐标及输入等待保持原值。

未新增页面字段、绘制记录、固定位置常量、重放流程或保存格式。已有组件重绘同样经过该调用边界；英文模式保留原坐标。不修改驻留桥或 Host ABI，不增加测试、断言、保护、回退或猜测分支。

## 既有所有权问题

- `modules/adapter/native_ui_scene.cpp:12` 的 `Child`、`:17` 的 `Container`、`:173` 的 `paint`、`:538` 的 `materialize_cache`、`:594` 的 `repaint` 仍保存并遍历整页组件序列，影响页面和缓存的语言重建，待整改。本次使用现有按钮接入以使旧组件同步取得同一定位修正，没有新增此类序列；本次按钮定位授权不豁免该既有问题。
- `modules/adapter/native_footer_component.cpp:88` 的独立页脚署名排版仍待整改，非本次底部按钮。

源码修改、产物编译、正式文件发布和运行中模块交接分别记录；任何编译或 Applied 回执都不代替用户画面验收。

## 交付状态

源码修改、编译及正式发布分别完成。2026-11-10 11:53:59（Asia/Shanghai）统一队列完成兼容业务热发布。

- 根入口 `build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 364`，显式指定当前 Proton WinePrefix 与 WinePath；一次配置、一次增量构建，没有清理构建树。日志保留既有函数指针转换、未用符号和缩进警告。
- 请求 `e6e4414c01e54f8c8beb6b5047ab931f`；批次 `3d6f51d6961c4bcf9b70865f21ec1c11`。已读取对应 `build/.compile-queue/results` JSON 及完整批次日志，`Success=true`、`PublishRequested=true`、`ReloadRequested=true`。
- 正式事务 `81639f1808c24109878a6d89c852ba4f`；已读取 `build/mingw-x86/stage/81639f1808c24109878a6d89c852ba4f/publication-result.json`，`success=true`。
- 正式 `package/modules/urwcn_adapter.dll` 与 `package/release.json` 已更新。旧两件先按原相对路径移入 `回收/20261110-115358-81639f1808c24109878a6d89c852ba4f/`，静态目录读取确认两件均保留。没有平行运行副本。
- 正式 DLL SHA-256 `8b2ee10d1f8bbf277e31f099dd5df785e3da5ab30e0ca27e0b149c81fc662153`，与构建输出一致。
- 仅通过系统进程表和当前 Proton 的既有 Mono 解释器只读确认 Linux PID `2832305` / Windows PID `364`；既有驻留事务返回 `ReadyToPublish` 和 `Applied ... adapter:8b2ee10d1f8bbf277e31f099dd5df785e3da5ab30e0ca27e0b149c81fc662153:2`，运行中 Adapter 第2代已交接。

没有启动、关闭或重启游戏，没有注入、模拟输入、运行测试、创建测试或断言；只进行了已授权的兼容业务热发布。Applied 只证明模块交接，画面位置由用户验收。
