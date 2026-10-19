# 2026-10-19 Linux 季节选择与肖像提示汉化

对应本次角色创建截图的英文残留：`Choose a season`、四季、`Back` 和底部 `Select a portrait for your character.`。同时补齐同一季节选择步骤的原生难度说明。新增七个语义组件，返回复用 `profile.back`；ENTER、ESC、数字和肖像翻页箭头保留原按键含义。

## 静态依据

目标为 Linux x86-64 UnReal World 3.89 / Steam Build 25939378，`urw3-bin` SHA-256 为 `4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。本轮只读反编译复用 Ghidra 12.1.2 现有项目，参数为 `-readOnly -noanalysis`。下表均为 ELF RVA，Ghidra 输出地址须减去 `0x100000`。

原始本地依据：`build/analysis/season-portrait-linux-ghidra.c`、`portrait-linux-ghidra.c`、`season-menu-linux.asm`、`portrait-picker-linux.asm`、`season-portrait-footer-linux.asm`。前两件确认菜单、词元和段落、按键、肖像选择完整控制流；原指令确认下表 CALL、参数寄存器及长度。

| 边界 | 接入与原生语义 |
| --- | --- |
| `1C3C1 → F5570` | `choose_month` 调用 `LIST_Draw`，仅此次调用建立季节作用域。菜单原英文记录不改写。 |
| `F5617 → 146A30` | 季节作用域中将 R8 标题借入“选择季节”。原 mode 8 对应 flags 4，`Piirra_Ikkuna` 交给 `TekstiPalkki` mode 2，原生左对齐。 |
| `F57D4 → 144FB0` | 根据原生 `ListEntries` 的动作字段（步长 `E8`、字段 `C8`）选出 1/2/3/4/ESC；保留点号前的键帽前缀，中文后缀在原生 `showtext` 完整绘制。 |
| `1C314 → 1AFE00` | RSI 季节说明借入“请选择开始游戏的季节。夏季开局最容易，冬季最困难。”，保留 EDI=1 的原生词表初始化。 |
| `1EFA9 → 1AFE00` | `pick_a_face` 的 RSI 提示借入“请为你的角色选择一幅肖像。”。 |
| `1C3C6 → F8630` | 仅原生季节 `LIST_Go` 的输入生命周期维持季节作用域，用于现有 Shift+F10 原生列表重绘。 |

`LIST_Reset(…,8)` 清零按字宽选择标记 `663F00C`；本页没有调用改变该标志的样式函数，也没有 `|` 后第二字段。原生 `LIST_Highlight` 使用原键帽前缀与面板宽度生成选择框；鼠标仍消费 `LIST_Draw` 建立的原生行位置。空白分隔行的动作是 0，走原有空文本调用，不进入按钮汉化。没有 Mod 坐标或行槽，也不改原生选择框与命中区域。

四季动作原值仍是 ASCII 1–4，原生分支继续写月份 4/6/8/11 与原温度值。快速创建的 `CRTPLR_TAPA==1` 分支仍自动选择夏季，未增加绘制或随机调用。肖像文件、人物姓名、左右箭头、ENTER/ESC 和存档路径保持原流程。

两条底部提示经 `SANATAULUKKO_Lisaa` 进入游戏的词元表，再由原 `crtplr_info → showtext_sanataulukko` 绘制。每个中文字符串的双字节传输编码长度都小于原生 130 字节词元槽容量；没有加截断、补救或回退。现有 `13EEC3`/`13F00F` 段落度量和 `13EA00` 光标扩展使用真实字宽，完整中文不会按 UTF-8 字节乘 8。字形在已接入的原生 screen 输出密度目标内同步提交，原生 UI 管理背景、缓存、阴影、行距和呈现。

## 刷新与未确认边界

当前季节输入期间，Shift+F10 复用现有 `redraw_list`：`LIST_Draw`、`save_menubuf`、原选择高亮和 `Flip`。不重入 `choose_month`、不重新构建原英文选项、不更改选择或推进角色流程。

底部提示在原生构建时消费当时语言。`crtplr_info` 开头始终消耗一次随机数，即使参数为 0，故不能为刷新提示直接重跑。底部纯重绘入口、肖像阶段之前已完成的季节/文化/性别面板即时语言刷新仍待确认；本轮没有制造刷新路径。非主菜单窗口缩放的完整画布重建和阴影预算仍以 [Linux 字体密度记录](20261019-linux-font-density.md) 所列待办为准。

Linux 驻留桥没有运行中业务退役与重新加载协议，根队列拒绝 Linux `-Reload`。本轮可以发布正式文件，但不能把新模块原位加载到已运行的 Linux 游戏。没有关闭、重启、注入或操作该进程。

## 既有约束冲突记录

- `docs/evidence/20261019-character-profile-native.md` 的“64字节词元边界”表述仍待更正；实际为 130 字节槽、最多129有效字节，纯双字节中文最多64字。本轮以原生 `SANATAULUKKO_Lisaa` 的 `0x82` 步长为依据。
- 历史 UI 方案冲突沿用 [文档纠正记录](20261019-document-render-policy.md) 与 [实现纠正记录](20261019-implementation-correction.md) 的状态，不把编译或发布视为这些遗留问题已解决。

## 交付状态

源码、词库、适配说明已修改；统一队列编译和正式发布于 2026-10-19 13:52:38（Asia/Shanghai）完成。

- 入口：根 `build.ps1 -Toolchain Linux -Module adapter,semantic,catalog -Publish`，沿用 `build/linux-x86_64`；一次配置、一次增量构建，没有清理构建树。
- 请求：`f3f7180efe3f4ee9bcd7423923deae52`；批次：`19a32af82e5840af9db84c3b3460f12d`。已读取对应 `build/.compile-queue/results/` JSON 和 `batches/` 完整日志，`Success=true`。
- 发布事务：`050a7d78bc1948288365ecf970ad8568`。已读取 `build/linux-x86_64/stage/050a7d78bc1948288365ecf970ad8568/publication-result.json`，`success=true`、`runtime_requested=false`。
- 正式替换：Adapter、Semantic、`package/catalog/zh-CN/main_menu.tsv`、Linux profile、`package/release.json` 共五件；旧件先按原相对路径移入 `回收/20261019-135238-050a7d78bc1948288365ecf970ad8568/`。Catalog 编译完成且二进制身份未变，词库实际已更新。
- 已只读核对构建/正式 Adapter、Semantic，以及源码/正式词库、profile 的 SHA-256，分别一致并与正式清单相符。根 `uwcn_launcher` 和驻留桥未变，没有平行运行包。
- 编译存在原有 Semantic `key()` 的 HUD/world 枚举 `-Wswitch` 警告；这些组件由现有独立分派处理，无本轮新增组件遗漏或编译错误。

| 正式内容 | SHA-256 |
| --- | --- |
| Adapter | `2baffbd20593ed2ccd747889a27923f5f2422d6fc1c515fd6250f6f6a12499cf` |
| Semantic | `0a64e3af599fdd78b2147816a98b49e656aebfe83d5a027f0d144b4d095959e1` |
| 主词库 | `732b0ea17b51150ff5f408cd6d0d53e53da888c5c74bfd4b7c8bf5afb2ed0990` |
| Linux profile | `e82f8603313e67c2ab01de04e8417bb0dba3025fcedfe1e39b2a777071e267d2` |

发布前只读进程查询显示 Linux 游戏 PID `3783244` 在运行；本轮无运行时 Applied 回执，新文件供下一次正常启动加载。没有将正式文件发布描述为当前画面已刷新。

未启动游戏、运行产物、模拟输入、执行或编写测试、添加断言或推测性的保护/回退分支。静态审查与交付编译不构成视觉验收。
