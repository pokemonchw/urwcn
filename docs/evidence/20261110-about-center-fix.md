# 关于正文重建错位修正

用户提供原版与汉化版截图：关于正文中心向右偏移，标题及按钮位置正常。本次只读静态审查，不启动游戏或测试。

原因位于 `modules/adapter/module.cpp::enter_component_paint` 的 TextBlock 分支：将 `context.centered` 设为 1 并保存中心操作数，却让 `context.text_x` 保持 0。`native_component_model.cpp::paint` 已用 `value(anchor.x,width)` 算出原生左边界并交给 `10E5A0`；`draw` 再执行 `center_x + request.x - text_x`，因此把非零左边界重复加到中心。影响所有使用中心锚点重建的 TextBlock，属于既有绘制接入错误，本次整改。

原 EXE 3.89.1 的 RVA `124887..1248A1` 明确为宽度、除二、从 ESI 中心减去半宽并调用 `10E5A0`；版权等调用同样消费左边界。重建路径亦已有同源中文测量和中心操作数求值，无需另加绘制中心补偿。

移除上述 TextBlock 特殊分支。重建文字经原 `10E5A0`、描边及前景调用，直接使用原生文字坐标；原生描边偏移保持。初次原生调用的 `centered_text` 仍保存真实 text_x，不改变其语义。不增加固定坐标、补偿常数、页面快照或重放；不修改业务、输入或缓存生命周期。原生坐标按逻辑像素取整，高清字形仍按实际输出密度生成。

没有新增测试、断言或兜底逻辑。

## 本次交付回执

源码、编译和正式发布分别完成。根 build.ps1 按 MinGW / adapter / Publish / Reload 提交，请求 `5a825de4183d426cb17171f14a6bcbb7`，批次 `caf741fc91db4ff1a3a572eed64bf76a`。已读取对应 results JSON、完整 batches 日志及事务 `c8f51c83882e4f85af6a7df86901c8bd` 的 publication-result.json，全部成功；一次配置、一次增量构建，保留既有编译警告。

正式 `package/modules/uwcn_adapter.dll` 与 `package/release.json` 已替换；旧件先按原路径移入 `回收/20261110-111523-c8f51c83882e4f85af6a7df86901c8bd/`。本机只读进程枚举确认游戏 Windows PID 368，正式模块热发布返回 `ReadyToPublish` 与 `Applied`，Adapter 第2代、哈希 `53dcc87b158a7d8009a1f1a8baf169069a3701d85b2331eb960dfe086cf0b75e`。未创建平行运行副本，没有启动、关闭或重启游戏、注入、模拟输入或运行测试。Applied 仅证明模块交接，画面效果待用户验收。
