# 不真实的世界主菜单原生面板资源修正

日期：2026-11-10。用户提供截图：中文菜单的原生资源不完整，切换英文后木纹背景框消失，F5 卸载、重载也不能恢复。本次只做静态分析和授权的兼容业务发布，不运行游戏或测试。

## 已确认原因

当前 `modules/adapter/module.cpp` 登记了主菜单页脚、版本内容和菜单行，却遗漏 `125BC5 → 116270` 的完整原生 Panel 构造。新版 3.89.1 PE 的该调用及五个栈参数仍与原证据一致，参见 `main-menu-static.txt` 的 `WINDOW RVA 0x125b6c..0x125c0f`。

该面板是原游戏右侧菜单的木纹大框。原输入宽 190、高 210；截图将这一块裁剪放大，框、Logo 与列表的相对位置吻合。主菜单本身的 `CFFB0` 类型为 0，只绘列表行，不负责这个框。原始图片资源在游戏安装目录存在，所查图像 ABI 和 3.89.1 地址映射没有缺口。

`native_ui_scene.cpp::paint()` 先绘原生背景，再绘已登记组件。漏接的非文字面板没有进入组件来源，因此语言切换时被背景擦除。HDA7 保存和 F5 恢复的仍是缺少该面板的来源图，重载不能凭空恢复它。这是现有原生组件接入不完整，不能以既有编译或发布成功视为合规。

## 修改边界

- 新增 `menu_frame`（ID 6），登记 `125BC5 → 116270`、五个栈参数。通用 `native_component_binding` 捕获实际原生参数和 PanelStyle，标题保持原生空串；面板图片、纹理、布局、背景和绘制仍由完整的原生函数消费。没有把原生坐标复制到 Mod 绘制代码。
- 已运行旧 Scene 的来源不含该组件，单在旧列表末尾追加会令面板覆盖 Logo、文字。`module.cpp` 在真实 `Scope::menu_input` 且来源缺少该面板时，通过原生背景构造与完整 `125BA3..125BE1` 片段取得实际来源顺序；该片段包含页脚、面板、版本和菜单构造，不进入 `D1120` 输入等待、不重入业务。`native_ui_scene.cpp::rebuild_native_source/restore_native_source` 按真实后继组件身份，将唯一缺失面板插入既有父源、缓存区源及同根缓存来源；保留原有菜单快照、选择和其他实例。临时构造容器随后释放。最后 `invalidate(true)` 通过实际原生缓存 owner 重建缓存及当前界面，没有另建页面布局或只修之后的新窗口。
- 本机游戏由 Proton/Wine 运行。统一发布入口原先在 Linux 用宿主 `.NET NamedPipeClientStream` 访问 Windows 管道，不能到达 Wine 的 `\\.\pipe\uwcn-<Windows PID>`。本次增加显式 `WinePrefix`、`WinePath` 队列参数，以当前 Proton 已有的 Wine Mono 11.3.0 `csharp.exe` 解释器收发原 PREPARE/COMMIT/ABORT 协议；没有编译或执行新的控制二进制。只读进程枚举取得宿主 PID `2788603` 对应 Windows PID `368`。
- Wine 暂存路径使用已确认 `z: → /` 映射，PREPARE 消费 `Z:\home\...`。译文、配置保存、选择动作和游戏业务不因此改变。

## 交付状态

源码已保存；统一队列只执行一次配置、一次增量构建，所选目标为 Adapter：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 368 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

- 请求 ID：`180e2113060b43a7b26521b34d7ddb60`。
- 批次 ID：`ca4100a2489e49f3a64695862209f461`。
- 发布事务：`5f47ba2ce89344f38893f48abd7d836c`，2026-11-10 10:58:04（Asia/Shanghai）完成。
- 已读取请求结果 JSON、对应批次日志和 `build/mingw-x86/stage/5f47ba2ce89344f38893f48abd7d836c/publication-result.json`：`Success=true`、`PublishRequested=true`、`ReloadRequested=true`。编译保留既有函数指针转换、未使用符号、缩进和成员初始化警告。
- 驻留层先返回 `ReadyToPublish 5f47ba2ce89344f38893f48abd7d836c`，旧 `package/modules/uwcn_adapter.dll` 与 `package/release.json` 再按原相对路径移入 `回收/20261110-105803-5f47ba2ce89344f38893f48abd7d836c/`，随后替换正式文件并 COMMIT。
- 当前 Windows PID `368` 的真实回执：`Applied 5f47ba2ce89344f38893f48abd7d836c adapter:168133b18b2b9355179863eca2f8732750f59af10fae629f35b89db84027e959:4`。发布记录 `applied=true`，游戏日志追加 `Compatible module transaction applied.`。没有要求手动卸载、返回菜单或重启。
- 正式 Adapter、构建输出与 Applied 回执均为 SHA-256 `168133b18b2b9355179863eca2f8732750f59af10fae629f35b89db84027e959`；正式清单 SHA-256 为 `1851fd3f8f40ba59b898d861d9ab97ee15e74e0f82f909005a744bf75e27f91c`。根启动器和驻留 Loader 沿用正式路径，没有平行运行包。

上述分别是源码、编译、正式文件发布和运行模块代数的结果。Applied 不是画面验收；没有启动、关闭、重启或注入游戏，没有模拟输入、运行游戏产物或测试；没有新增测试用例、断言、像素跟踪或显示重放。
