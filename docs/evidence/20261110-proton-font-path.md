# Proton 中文乱码：字体路径修正

日期：2026-11-10。仅静态读取截图、已有日志、字体元数据和源码；不启动游戏、不注入、不运行产物或测试。

## 依据与修改

用户截图的启动文字呈现西文字形。`package/uwcn.log`（最后修改 10:19:45）反复记录 `Native dispatch rejected ... status 4`。状态 4 是 `Status::failed`，并非单独的编码错误码。

`modules/render/font_engine.cpp` 原先在 Windows 路径固定读取 `GetWindowsDirectoryW()/Fonts/msyhbd.ttc`。本机 Steam 的 `compatdata/351700/pfx/drive_c/windows/Fonts/` 没有此文件，只有 `msyhbd.ttf`，指向 Proton Experimental 的同名字体。静态读取 name 与 OS/2 表确认 Microsoft YaHei / 微软雅黑、字重 700、独立 TrueType 字面。旧路径在 SHA-256 文件读取阶段必然失败，`module.cpp` 的 `ready()` 随之失败，无法进入 Mod 字形绘制；这解释了一项确定的绘字阻断，不将其外推为所有状态 4 的唯一原因。

修改 `FontEngine::initialize`：依据已存在的 ntdll `wine_get_version` 导出区分 Wine/Proton 与原生 Windows，前者明确读取 `msyhbd.ttf`，后者保持 `msyhbd.ttc`；均使用 face 0。没有字体目录扫描、自动回退、文件复制或 UI 布局变更。SDL_ttf 原生版本函数的磁盘指令及常量仍确认 2.20.2，不更改版本约束。

## 待整改记录

现有宿主对 dispatch 失败仍透传原生绘制的行为，允许显示传输编码的西文字形，与完整中文绘制契约不符；位置为 `src/loader/host.cpp:59` 中记录 `Native dispatch rejected` 的分支。影响是字体服务失败时画面出现乱码。本次修复已确认的文件路径，不为失败分支新增保护、补偿或兜底；宿主失败语义仍按既有实现纠正记录保持待整改状态。

## 编译与正式发布

- 根统一入口：`build.ps1 -Toolchain MinGW -Module render -Publish`。
- 请求 `24c9476b2f3748b3be2d26303a834a0c`；批次 `a72707e5137d458a93401c9d65e1efef`。
- 已读取对应 results JSON 与 batches 日志；`Success=true`、`PublishRequested=true`、`ReloadRequested=false`。既有函数指针转换警告仍存在。
- 正式事务 `fcdfb34690d445bea198c8a6ef31559c`，10:21:32 完成；已替换 `package/modules/uwcn_render.dll` 并更新发布清单。旧文件先按原路径归档至 `回收/20261110-102132-fcdfb34690d445bea198c8a6ef31559c/`。
- 正式 DLL SHA-256：`05a475046efdeb7a250d8bba06fea727ac1197ce7a1bdd643b100362cdc2742b`。
- 只读进程列表未发现游戏进程；未请求运行时应用。源码、编译与正式发布已完成，画面效果未经代理运行验收。
