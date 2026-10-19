# Linux 中文字号与字重修正

日期：2026-10-19。用户截图反馈主菜单及页脚中的中文比同排英文小、细。本轮只静态读取源码、字体表、进程身份与发布回执；不启动游戏、不模拟输入、不运行测试、不创建测试用例或断言。编译只生成交付物，兼容业务热发布沿用已授权事务。

## 原因与静态依据

- `src/linux/adapter.cpp::textput/rentextput/width` 在完整原生文本调用中将非 ASCII token 交给 Render，ASCII 继续调用游戏 `putasc/renderasc` 并使用原生 8 像素推进。此前 `modules/render/font_engine.cpp::initialize` 却将轮廓字体的 ASCII 也加入中文字号校准。
- 正式字体文件 SHA256 为 `767e21e7b93c2d7d566745eb6496ad04dd73ee5ab85e4b7f54b69efaddbced85`。`fc-scan` 静态元数据确认 face 37 为 Source Han Sans SC Bold，face 22 为 Source Han Sans SC Heavy；字体 OS/2 表的字重分别为 700、900。使用已有字体文件的原生字面，不增加字体包、模拟粗体或回退字体。
- 对字体 CFF 轮廓和完整已提交词库只读解析：unitsPerEm 为 1000。旧 Bold 全参考集的纵向并集为 `[-284, 868]`，共 1152 字体单位；下界来自英文竖线 `|`。实际交给轮廓字体的非 ASCII 集合为 `[-176, 868]`，共 1044 单位。原校准因未使用的 ASCII 轮廓额外压小了中文。
- Heavy 非 ASCII 集合为 `[-185, 875]`，共 1060 单位。此次静态集合包括 1963 个有轮廓的非 ASCII 字符，仍包含中文标点和词库中的非 ASCII 拉丁字符。此数据说明参考包络差异，不能替代 SDL_ttf 的运行时光栅校准，也不据此声称固定增大百分比或视觉验收。

## 源码修改

1. `FontEngine::initialize` 仅在 Linux 排除 ASCII 校准字符。完整非 ASCII 字集共用稳定字号和基线，不逐行、逐页或逐字选字号。Windows 路径保留原完整参考集。
2. `FontEngine::font` 的 Linux face 改为 22 Heavy，样式仍为 regular，hinting 保持 NORMAL。最大合格字号仍由真实目标密度下的非零 alpha 包络决定；原 9 逻辑像素墨迹上限与 10 高文字区域不变。
3. `src/linux/adapter.cpp::invoke` 在 Render 依赖变更后清除原有字宽缓存，并标记字体失效。`poll_language` 的原生输入轮询返回边界消费标记，在主菜单或 About/Credits 使用已经确认的完整原生重建流程。原背景、页脚、菜单缓存、选择与 SCREENSAVE 都沿既有原生所有者更新；不触发菜单业务或模拟按键。
4. Linux profile 和字体规范同步记录当前字面与校准范围。字体光栅只保存自身覆盖和度量，没有 UI 坐标、页面内容、像素跟踪或延迟重放。

## 既有待整改边界

| 文件与位置 | 影响与状态 |
| --- | --- |
| `src/linux/adapter.cpp::glyph_request` 的 `request.native_line_height=10; request.ink_height=9` | Linux 原生 showtext 的四次阴影调用仍未将描边预算传入校准与外部宽度调用。此既有完整样式包络问题仍待整改；本次不扩大预算，也不声称已完成阴影包络接入。 |
| `src/linux/adapter.cpp::poll_language` 字体刷新分支及 Linux profile 的 pending_boundaries | 本轮自动完整刷新只采用已确认的主菜单、关于和鸣谢边界。其他页面保留游戏缓存，在其原生重建时使用新字体；不补造纯重绘入口。 |
| `publish.ps1` 的 Linux desktop `Name=UnReal World 简体中文` | 现有用户可见标题未使用约定译名“不真实的世界”，待单独整改。本次字体修改不将其视为符合命名约束。 |

## 编译与正式发布

2026-10-19 16:50:06（Asia/Shanghai），统一入口完成本轮编译与正式热发布：

```text
.toolchains/powershell/pwsh -NoProfile -Command '& ./build.ps1 -Toolchain Linux -Module render,adapter -Reload -TargetPid 3950079'
```

- 请求 `0c9a24a2e6b54147970a33361a0162ce`，批次 `9a7ed83befe04a43b613dbae4d9c35bc`。已读取对应请求结果 JSON 和完整批次日志；`Success=true`、`PublishRequested=true`、`ReloadRequested=true`。一次配置、一次增量构建，两个模块编译成功，无编译警告。
- 发布事务 `626f8aabdf574492b5029e96bbe03370`。已读取 `build/linux-x86_64/stage/626f8aabdf574492b5029e96bbe03370/publication-result.json`，`success=true`。
- 正式替换 `package/modules/uwcn_render.dll`、`package/modules/uwcn_adapter.dll`、Linux profile 和 `package/release.json`。旧四件先移入 `回收/20261019-165006-626f8aabdf574492b5029e96bbe03370/package/`，保留相对路径；发布器也按既有规则归档应用菜单旧链接。
- PID `3950079` 先返回 `ReadyToPublish`，提交后返回同一事务 `Applied`：Render 第 2 代、Adapter 第 2 代。未关闭或重启游戏，未注入额外驻留层。
- 正式 Render SHA256：`d244a6349edefdb8f1ea533ca797f19559caa8d68085b341c5027ef60546af63`；正式 Adapter：`b04ce9b09047d8f26e9a546c6c532bfdaa7e4a2a2101c516a57a6ec75706e1a6`；正式 Linux profile：`0c6acb32cfa8576f0a725ac6d2ff886c8a5c9e63c15a513f2bd4cf1f586577e9`。三者分别与构建产物／源码和正式清单相符。

源码修改、产物编译、正式文件发布及兼容模块加载均已完成。主菜单的刷新请求由下一次原生输入轮询返回消费，没有读取运行画面或自行测试；Applied 只证明模块交接，最终视觉效果待用户观察。
