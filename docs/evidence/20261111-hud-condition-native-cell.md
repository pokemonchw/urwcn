# 状态栏中文包络与原生清除范围

用户截图显示“营养良好”下方还有绿色笔画，体温、精力框底也有残留；此前只解释饥饿／口渴为状态条，没有处理这些异常。本轮以静态代码、原游戏 PE、URW.FNT 及用户截图追查，没有启动游戏、读取进程画面或内存、模拟操作、执行产物、运行测试、创建测试用例或断言。兼容业务热发布另列回执。

对象是不真实的世界 Windows x86 3.89.1 / Steam build 26139145。PE SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`；URW.FNT SHA-256 为 `4fbe9f69319d8dc01f0dfdd765d5019239995317f21230e56adc980fde83ebbb`。以下为 RVA，原始反汇编为基址 `00400000` 的 VA。

## 静态原因

`F9910` 中营养、体温、精力的宽版／紧凑版各有一处 `111480` 框构造，随后进入 `10E5A0` 完整文字调用。原始指令见 [状态栏及框构造反汇编](20261111-hud-condition-native-cell.asm)。

| 原生框 CALL | 对应文字 CALL | 实际协议 |
| --- | --- | --- |
| F9F1B / F9F57 | F9F70 | 营养 |
| F9FFE / FA05A | FA074 | 体温 |
| FA17A / FA268 | FA27E | 精力 |

六个框均通过原栈提供宽度、高度 13 及第三个未消费的 pending word。`111480` 清除内区 `[frame_y+1, frame_y+height-1)`，即十一行；外框底线在 `frame_y+12`。后续原文字原点是 `frame_y+3`，shadow 参数为零。因此从这个原点起，能够被下次原生更新完整清除的高度是九行。

原 `10BD90` 字模存储格为 8×10，但 URW.FNT 的全部 256 个字形实际墨迹只在行 0..7，8、9 行为空。原英文状态不会覆盖框底。现有 `module.cpp::render_request` 却对这三个组件始终提供 `native_line_height=10, ink_height=9`；`FontEngine::font` 允许完整字集共同包络达十行，`surface_text` 也在十行内放置基线。因此中文包络可以进入不被内区清除的框底一行。单字墨迹预算为九，不能代替完整字集共同包络的范围约束。

这是一处已确认的组件度量接入缺口，能够产生框底笔画和残影；不能仅凭它断言截图里所有状态条变形或整块位移都有同一原因。

## 源码修正

`modules/adapter/hud_native.inc` 在上表六个真实框 CALL 接收当次 EDX 与栈中 height，只借用该原生内区的 exclusive bottom。随后对应的三个状态文字 CALL 用这个 bottom 减去本次实际文字 EDX，得到可用高度，立即清除临时 bottom，开启同 token 的 `hud_condition` 作用域。

`modules/adapter/module.cpp::render_request` 在该文字调用内向既有测量和即时绘字接口提交同一可用高度；其余文字样式保持原参数。字体校准仍使用完整字集和真实目标密度，不按当前句子的紧包围盒移动基线。没有增加裁剪补丁或另画背景；框、文字原点、原生光标、输入、数值、状态选择、缓存与清除仍走原函数。

临时的一个底边和一个字格高度不序列化、不进入字形缓存；没有三个字段的位置表、页面快照、像素追踪或延后文字重放。`Active` 的结构大小、HDA8、Host ABI 和驻留桥未改变。普通 `F9910` 更新及现有完整原函数重建均经过这些内部 CALL。

## 待确认及既有待整改项

- 截图还表现出状态条／框相对静态标签的位移。现行 `scoped::fill`、原生 line 参数桥、主目标密度与 F9910 布局操作数经过静态追查，尚未取得能够解释这一现象的独立证据；该项保持待确认，不按截图补造坐标修正。
- `docs/evidence/20261110-font-cell-calibration.md` 的“统一十行”结论已加本组件例外；`docs/font-rendering.md` 增加实际清除范围要求。这处原生度量缺口在本批源码整改，编译或 Applied 不能代替画面确认。
- 既有 `native_ui_scene.cpp` 的 Child/Container、`native_component_binding.cpp::construct`／`native_component_model.cpp::paint` 的历史组件图、`native_renderer_component_binding.cpp` 的 Owner.children，以及 `native_footer_component.cpp` 独立署名排版仍按此前审查记录待整改。本次未扩展这些机制，也不将其视为合规。

## 编译与正式发布

源码修改、Adapter 产物编译、正式文件发布及当前进程兼容交接均已完成。通过根统一入口执行一次配置、一次增量构建；入队至所属批次结束未修改提交范围源码。日志保留既有函数指针转换、extern 初始化、未使用项及缩进警告，无编译错误。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 468 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 实际回执 |
| --- | --- |
| 请求 | `094ae1df0d2946c8a5133abe78ee43c5` |
| 批次 | `d8c7ff9a412b4cbbbeeb4881c4159d75` |
| 结果 | `build/.compile-queue/results/094ae1df0d2946c8a5133abe78ee43c5.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 完整日志 | `build/.compile-queue/batches/d8c7ff9a412b4cbbbeeb4881c4159d75.log`，已完整读取 |
| 正式事务 | `a0d546fc14f741f0abd977736303e76d`，2026-11-11 12:14:25（Asia/Shanghai）完成 |
| 正式文件 | `package/modules/uwcn_adapter.dll`、`package/release.json` |
| Adapter SHA-256 | `ec17fb9d1dceefd74d4469ba77353fc76f07b090920ff36ebf1455ea3685bcc3`，与构建件、清单及 Applied 回执相同 |
| 旧件回收 | `回收/20261111-121424-a0d546fc14f741f0abd977736303e76d/package/`，保留 Adapter 与清单原相对路径 |
| 旧 Adapter SHA-256 | `706e49aa5bebbf39bbb7f52cbe5f2572eda39462dee65b72b773392fcc787ec3` |
| 驻留交接 | Windows PID 468，Adapter 第 8 代 `Applied` |

请求 JSON、全部批次日志、正式 `publication-result.json`、发布清单和新旧文件身份均已读取。Applied 仅证明兼容模块交接，不是用户画面完整性结论；未运行游戏验证或测试，上述整块位移仍待确认。
