# 2026-10-19 字体被 Windows 150% 位图放大：启动边界修正

用户报告所有界面一直模糊，并提供 `codex-clipboard-81dfae99-52c4-42fa-9094-9f0e3f95fc6b.png`（681×755）。用户明确说明它是游戏画面的直接局部截图，未再放大。本次修正以该图、系统只读元数据及锁定版本源码为依据；没有运行游戏、产物或测试，没有截图游戏、模拟输入、注入、测试用例或断言。

## 模糊证据与上轮结论更正

原图两个独立字区都具有同一套 1.5 倍线性插值采样网格。下表只分析用户已给图像，不生成字体，也不执行 Mod：

| 字区（包含边界的图像坐标） | 1.49 倍横/纵 RMSE | 1.50 倍横/纵 RMSE | 1.51 倍横/纵 RMSE |
| --- | --- | --- | --- |
| 载入角色：x73–179、y375–400 | 2.661 / 0.836 | 0.181 / 0.195 | 2.444 / 0.789 |
| 设置：x72–132、y455–486 | 1.813 / 1.762 | 0.152 / 0.161 | 1.554 / 1.706 |

RMSE 是 0–255 红通道的拟合误差。两个区域在 1.5 倍下均低于一个灰阶，采样相位差也与区域原点差一致。“置”内部 x113、y473–481 的红通道为 `154,54,191,154,54,191,154,53,190`，可见重复的三行采样周期。字体即时路径使用同尺寸 UpperBlit，本身不执行这次放大。

重新枚举显示器的只读结果为：唯一 HMONITOR=`65537`，`GetScaleFactorForMonitor` 返回 `S_OK`，缩放 **150%**；DPI-unaware 查询进程得到的显示范围是 2560×1440。`Win32_VideoController` 报告物理模式 **3840×2160**。上轮游戏 HWND 元数据已记录 awareness=0、GetDpiForWindow=96，客户区2560×1369。

初步审查曾对游戏 HWND 查得一次100%并据此排除系统缩放；该次没有独立记录和核实 HMONITOR，有效性不足。该排除结论撤回，不能继续引用为100%证据；两次返回不一致的具体原因尚未确认。也不把这次 GetScaleFactorForMonitor 读数混称为 GetDpiForMonitor 的96虚拟值。

原生主菜单外框为190×210，旧转储中的目标配置为1825×1369，再乘1.5后外框约650×719，与截图相符。这只是跨时的辅助证据，转储中的 canvas 配置不证明所有资源已经完成迁移。核心依据是用户原图的二次重采样、用户确认未放大、DPI-unaware 窗口与当前150%显示器缩放。

## 实现与原生边界

`src/launcher/main.cpp` 在 `CreateProcessW` 前设置启动器自身环境 `SDL_WINDOWS_DPI_AWARENESS=permonitorv2`。现有 CreateProcess 的 `lpEnvironment=nullptr`，游戏继承该值。没有写入用户/系统环境、注册表或游戏文件；设置失败沿明确错误返回停止本次启动，没有重试或替代绘制路径。

游戏 `FUN_005800E0` 在 `docs/evidence/intro-ghidra.c:945` 调用 SDL_Init，在1061附近调用 SDL_CreateWindow。SDL 2.30.0 的 `WIN_VideoInit → WIN_InitDPIAwareness` 在此初始化期间读取 hint，所以声明发生在游戏创建窗口之前。启动器既有的 PE 入口停驻、Mod 加载和主线程恢复顺序保持。

这个 hint 关闭 Windows 对 SDL 窗口的位图缩放，保留 SDL 像素坐标语义；没有启用 `SDL_WINDOWS_DPI_SCALING`，也不添加 ALLOW_HIGHDPI flags。原生800×600逻辑域、输入动作、命中、窗口布局与文字预算不在本次改动范围内。原生目标继续根据真实 viewport 建立物理尺寸，字体继续在本次原生文字调用中从轮廓生成并原尺寸提交。

取消系统放大后，保存的普通窗口宽高数值会按物理像素解释，实际窗口大小可能与此前不同；最大化窗口仍由游戏/SDL管理。不能承诺旧的系统放大尺寸保持不变。

该初始化声明无法由现有兼容业务 DLL 热发布追溯到已经创建的 HWND。本次交付修改根启动器，在用户下一次正常启动时生效；代理不关闭或重新启动游戏，不宣称运行中 Applied。

## 尚未由本次解决的范围

本次没有改变字体、hinting、Blended 抗锯齿或名义字号，没有用 Nearest 冒充高清，没有恢复文字记录重放。小窗口最低800×600限制、部分页面密度变化重绘边界及旧缓存迁移等问题仍以 [初步审查](20261019-font-sharpness-audit.txt) 和各界面记录为准；DPI修正不能替代这些原生生命周期工作。

## 交付状态

- 源码：启动前 DPI hint 已接入；字体规范与初步审查的排除结论已更正。
- 修改前源码和文档：保留在 `回收/20261019-font-dpi-source-2d32004169f44e94b81cc25624aa3443/`。
- 编译：统一入口 `build.ps1 -Module launcher -Publish` 已成功。请求 `99b72100d2ee4db587b0f37e494b2f91`，批次 `704b7920c5824cb7b67fe95500ea9d99`；已读取对应请求 JSON 与完整批次日志，`Success=true`。没有编译或执行字体示例、测试工程或游戏。
- 正式发布：2026-10-19 08:39:31（Asia/Shanghai）事务 `41070669c7054afab6885f04174d1757` 成功；已读取暂存目录的 `publication-result.json`。本事务只替换根 `uwcn_launcher.exe` 与 `package/release.json`。旧两件先移入 `回收/20261019-083930-41070669c7054afab6885f04174d1757/`，保留原相对路径。没有发布并行修改中的其他业务模块，也没有另建运行目录。
- 产物身份：正式根启动器与本批编译产物 SHA-256 同为 `aa7af7793590f743f9acba4320ae95e95d481cfafee067e3e8a1dc4f35b01d5a`，正式清单记录相同值。旧启动器 SHA-256 为 `b7190fe371d83de8f5edb190b35a78e915e8c3e143ad445cccfd9787f6a53969`。只读 PE 导入核对确认新文件含 `SetEnvironmentVariableW` 与原 `CreateProcessW`。
- 运行时：`ReloadRequested=false`、`runtime_requested=false`，没有 Applied 回执。该启动声明由下次正常启动的游戏消费；不声称当前已创建窗口已改变。
- 运行：未启动、运行或测试；没有视觉验收结论。

## 官方依据

- [SDL 2.30.0 DPI hint 定义](https://github.com/libsdl-org/SDL/blob/release-2.30.0/include/SDL_hints.h#L2148)：设置时机、关闭系统位图缩放及像素坐标语义。
- [SDL 2.30.0 Windows 视频初始化](https://github.com/libsdl-org/SDL/blob/release-2.30.0/src/video/windows/SDL_windowsvideo.c#L361)：在 WIN_VideoInit 中消费 hint。
- [Microsoft GetScaleFactorForMonitor](https://learn.microsoft.com/en-us/windows/win32/api/shellscalingapi/nf-shellscalingapi-getscalefactorformonitor)：HMONITOR、比例和 HRESULT 的含义。
- [Microsoft GetDpiForMonitor](https://learn.microsoft.com/en-us/windows/win32/api/shellscalingapi/nf-shellscalingapi-getdpiformonitor)：DPI-unaware 调用方可获得虚拟96。
