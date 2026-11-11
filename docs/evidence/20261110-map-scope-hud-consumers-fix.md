# 地图调用作用域与 HUD 中文消费修正

日期：2026-11-10（Asia/Shanghai）。用户连续提供 HUD 与已知区域地图截图：HUD 的负重／惩罚标签、手持物品、完整地点名显示英文；地图图例和缩放说明已有中文，M/A/C/F3/ESC 按钮及帮助仍为英文。本次只读用户截图、现有日志、源码与磁盘静态反汇编，没有自行测试、运行产物、启动或操作游戏、写测试或断言。兼容业务发布继续使用已授权驻留事务。

## 地图的确定根因

上次 `windows_encyclopedia.inc::windows_map_control` 在 CFDF6 和 CFECB 读取原 CFD10 帧的 `[EBP+4]`，按 E5D06 等游戏返回地址识别六个按钮。帮助同样在 162627 比较原 read_info 的 `[EBP+4] == E3E31`。

但同一版本已分别给六个外层 CFD10 CALL 及 `E3E2C → 162530` 安装 CALL Hook。`src/loader/hook_host.cpp::urwcn_before_route` 将原返回地址存入驻留 Pending，再将游戏栈槽写为 `urwcn_after_bridge`。上述条件不会成立。这是上一实现遗漏的静态桥接语义，不能用源码有译文或 Applied 回执证明翻译已完整进入画面。最新用户截图直接说明图例和缩放的直接调用已经消费了中文，而这两条基于栈返回槽的路径没有消费。

修正复用已安装的完整原 CALL Before/After：六个按钮以 `Scope::known_map_control_first + 实际调用身份` 标识同步作用域；帮助以既有 `native_renderer_component_binding` 的 `map_help=7D9D` 开启同步作用域。CFDF6 绘制、CFECB 字宽及162627帮助记录读取同一真实作用域，After 通过原 token 结束。没有第二次安装同一 Hook，不扫描父帧或祖先，不改变驻留桥。

这些作用域只在原函数实际执行期间存在，没有 UI 坐标、输出行、整页内容或绘制记录。沿用原 Active 标量格式，不新增状态分节或 ABI。CFD10 没有新的输入等待；帮助同样在完整读取返回时结束。已打开地图在现有语言 pending 的完整原帧重建中自然进入新作用域。

进一步审查确认 `native_hud_language.inc::dispatch` 的地图语言等待也在 D1120 帧比较已桥接的 `E5F5E`。本次改为先使用原 `E5EAA/E5EB0` 选择的真实 map owner `5F937B0` 和上下文 `Eh`，再沿 D1120 保存的父 EBP 读取存活 E5990 页帧。原 PE 对 E5990 的直接 CALL 只有 `1591C5`、`17DF30`，这两处没有安装 CALL Hook，其原返回 `1591CA/17DF35` 可用于该已确认父页身份。随后仍通过原 `D19B3` 平衡退出、原 `E5F5E` 重回完整 `E5AC0` 构造，不重跑 E5990 入口业务。已打开的旧帧保存相同真实父 EBP，无需用户关闭地图。

## HUD 的静态消费缺口

词库中的 `hud.label.Carrying/Penalty:/Fatigue/Injury/Starvation/Total:/Bloodloss` 等资源仍存在；此次没有删除或重新生成词库。静态调用链为：

| 位置 | 原语义及此前缺口 |
| --- | --- |
| `FA5AF/FA5D3/FA60D/FA665/FA6BD/FA6F9/FA733 → F8E20` | 原负重和惩罚标签构建器；中间三处 `+` 分隔仍保持原文 |
| `F8E84 → 10E5A0` | 标签实际完整文字调用。原 `dispatch_hud` 因任意外层 `consuming_component()` 为真便不翻译，没有证明这一次实际标签已被借成中文 |
| `F9314..F932B`、`F95C3 → 10E5A0` | 原数量／品质／物品名称表达式已关联到英文缓冲，但 item_text 原来仅 bind_expression，不直接向原文字参数提交中文 |
| `9052C → 8E4F0`、`90588 → 10E910` | 原完整地点表达式的生产与居中文字调用；bind_hud_location 同样仅绑定来源 |
| `native_component_binding.cpp::construct` | 外层 `consuming_component()` 为真时不再构造子组件 |
| `native_component_binding.cpp::finish_event` | 没有当前旧 Root 时不构造组件；因此 bind_source 本身不是实际中文消费承诺 |

以上是可由静态代码直接证明的缺口；本次未读取运行时内存或复现用户操作，不将某一具体 Root／外层组件状态推测为截图唯一原因。

修正 F8E84 的判断，使其根据当前实际文字是否已使用原生中文传输决定是否需翻译；已经借成中文的同一标签不再次按西文字节解码，英文标签则在该完整原调用消费已有词库。原 `+` 字面量保持原值。

F95C3 和90588仍绑定同一中性原始表达式，随后直接解析同一语义并把中文编码借给各自完整原文字调用。物品继续使用现有品质／名称表达式、原单手身份、盾牌实际后缀与完整字形截短；地点继续使用原地形／地点生成表达式，不猜测英文拆词。原始英文缓冲、业务物品数据、游戏状态和配置不修改。原文字调用返回即释放借用。

原生10E5A0的光标推进、10E910居中与折行继续消费已有完整字形度量，最终字形在当次原生目标的实际输出密度即时提交。没有坐标表、整页快照、独立布局、像素扫描或延后文字重放。

## 已知待整改项

- `modules/adapter/native_component_binding.cpp::construct`、`native_component_model.cpp::paint` 仍保留依赖旧 Root／组件图的历史构造接口；这次受影响的实际消费者已直接接入中文，旧图完整退役待整改，不能再次把绑定来源等同于已绘制。
- `modules/adapter/native_ui_scene.cpp:12` 与 `native_renderer_component_binding.cpp:39` 的历史 Child/Container、Owner.children 及序列化仍保留，完整退役待整改；本次不增加页面集合、布局表或组件遍历。
- `modules/adapter/native_footer_component.cpp:88` 的独立署名排版仍待整改，本次不扩展。
- `docs/evidence/20261110-known-map-untranslated-native.md` 与 `20261110-hud-wielded-items-native.md` 的旧交付结论已加后续纠正；旧成功回执只证明交接，不证明用户画面完整。

## 交付状态

源码修改、产物编译、正式包发布和当前进程兼容交接均已完成。两次源码请求分别在修改保存后提交，所属批次完成前未继续修改各自请求范围源码。两个请求结果 JSON、两个完整100行批次日志和两个正式发布 JSON 均已读取；保留既有函数指针转换、extern 初始化、缩进及未使用项警告，没有编译错误。工作区其他任务的既有修改保留。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 范围 | 请求 | 批次 | 正式事务 |
| --- | --- | --- | --- |
| 地图按钮／帮助作用域与 HUD 直接消费 | `095d64c3694b4500b4db63b50a3351d7` | `9494959072de4a138783b443be923224` | `41f2b2f9e6ed44448811701ae9abe9be` |
| 已打开地图的原等待刷新边界 | `56e6b422328d479fb41ee93ad790ef4e` | `e64ee0a8de5148d793f09983ee5a1c17` | `55b64d64f8db469086f64e61b99703cf` |

两个 `build/.compile-queue/results/<请求>.json` 均为 `Success=true`；日志位于 `build/.compile-queue/batches/<批次>.log`。两个 `build/mingw-x86/stage/<正式事务>/publication-result.json` 均为 `success=true`、`runtime_requested=true`、`applied=true`。

最终事务于2026-11-10 17:50:44（Asia/Shanghai）完成，Windows PID `364` 返回 `ReadyToPublish`，随后 Adapter 第23代 `Applied`。正式替换为 `package/modules/urwcn_adapter.dll`、`package/release.json`。旧两件先移入各自批次归档：`回收/20261110-174956-41f2b2f9e6ed44448811701ae9abe9be/package/`、`回收/20261110-175043-55b64d64f8db469086f64e61b99703cf/package/`，保留原相对路径，已只读确认存在。

| 文件 | SHA-256 |
| --- | --- |
| 最终 Adapter，构建件／正式件／Applied 一致 | `75e88ba3f54350ee6feaeb182723652bab57be5f1490f82f0147dfc606cec59d` |
| 第一批 Adapter，Applied | `5939d587af10deeb9549d43a32c1f07fd089fc3e291e5fc7e48842b58ceda9e4` |
| 地图词库，源码／正式件一致，沿用上一批资源 | `a3718a942156d9518eb990f0230b4d810a758110b8b5863a47dfd2f1d49f0e2c` |

根 `urwcn_launcher.exe` 继续使用同一正式包，无平行运行副本。本次没有新增词条、启动或操作游戏、运行测试、写测试或断言。Applied只证明模块交接，用户画面尚待验收；不再次用构建成功替代完整视觉结论。
