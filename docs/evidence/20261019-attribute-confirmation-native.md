# 2026-10-19 Linux 角色属性确认页汉化

对应用户截图中的角色属性确认页。新增年龄句子、外貌／心智／身体素质／体格四个分组、十一项属性、身高体重标签和单位、右侧确认说明、继续／重新生成动作；同一原生函数 mode 2 的属性说明与继续提示也已接入。共新增25个语义组件、33条词库记录，其中单位组件消费9种已确认原生后缀。

顶部由 `plrnam(0)` 将姓名与民族称呼拼接后传给 `FullSubScreen`。首轮错误地将 `Kaumolainen` 当作姓氏保留，漏译了民族；用户指出后，补充确认了文化编号与 `CULTURE_INHABITANT` 的原生关联，在本页标题显示边界接入全部十种民族的现有译名。截图对应“路里卡 考莫人”，保留用户姓名和原内部民族数据。按钮的 `<Y>es.` / `<N>o.` 原键帽前缀、Y/N 动作与空白分隔行保持，中文仅替换点号后的动作文字。

## 静态依据与原生调用

目标为 Linux x86-64 UnReal World 3.89 / Steam Build 25939378。原游戏 SHA-256：`4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。所有地址为 ELF RVA；Ghidra 地址减去 image base `0x100000`。

本地原始材料为 `build/analysis/attributes-linux-ghidra.c`、`attributes-consumers-linux-ghidra.c`、`attributes-linux.asm`，并复用 `season-portrait-linux-ghidra.c` 的 `LIST_Reset`、`LIST_Draw`、`LIST_Go`、`LIST_Highlight`、词元与段落反编译。只读 Ghidra 调用使用 `-readOnly -noanalysis`，没有运行游戏。

| 原生边界 | 接入语义 |
| --- | --- |
| `10D610 → 1225E0` | 在 `FullSubScreen` 的 RDI 借入“原姓名＋中文民族称呼”，复用 `profile.culture_0..9`。`FullSubScreen → TekstiPalkki(mode 5)` 使用现有完整中文标题居中、度量和即时绘字路径。 |
| `10D641 → 8F80` | 原生 `__sprintf_chk` 接收 R8 中已经选定的年龄。在原1024字节显示缓冲构建中文，再交给 `10D66D → textwidth` 与 `10D692 → showtext`，原生居中消费同一译文。仅原非零 mode 的开局年龄分支；mode 0 的生涯描述保持。 |
| `10D4C9/10D4F8/10D80D/10D88A → 1471A0` | 四个 `winbox` 标题位于 R8；七参数调用从原 Frame 读取第七参数。原尺寸、颜色、背景及标题绘制路径保留。 |
| `10D6B7/10D6DC/10D701/10D726/10D74B/10D770/10D795/10D7BA/10D7DF/10D834/10D859 → 108880` | `desced_stat` 的 RDX 标签借入中文；ECX 属性值、原生 `showtext` 及后续 `statbar` 完整保留。 |
| `10D8FD/10D981 → 13E8B0` | 身高、体重标签的 RDX 显示副本。 |
| `10D95E/10D9DA → 146ED0` | `TekstiPalkki` 的 RCX 数值文本只翻译单位后缀，保留原数字字符串。原生 `UnitString_Length(float,0x29)` 与 `UnitString_Weight(float,1)` 完成换算、取整和精度选择。 |
| `10DB12/10DB20 → 1AFE00` | 文化背景确认与属性满意度说明，进入原 `SANATAULUKKO_Lisaa` 词表和 `showtext_sanataulukko` 段落。 |
| `10DA8A/10DA98 → 1AFE00` | mode 2 的属性说明与任意键继续提示，输入仍由原 `getkeypress` 消费。 |
| `10DBD7 → F5570`，共享 `F57D4 → 144FB0` | 限定属性确认菜单绘制作用域，按原生行 `+C8` 的 Y/N 动作选择译文，保留键帽前缀。 |
| `10DBE7 → F8630` | 原 `LIST_Go` 等待期间维持属性菜单语义作用域；没有更改输入结果或 REROLL。 |

`UnitString_Length` 明确构建 `in/ft/cm/m`；`UnitString_Weight` 明确构建 `lb/lbs/oz/kg/g`。只在本页两个最终显示调用翻译这些后缀，不改通用单位函数、配置值、数字、角色数据或存档。

民族补充的本地依据为 `build/analysis/attribute-culture-linux-ghidra.c` 与 `attribute-culture-linux.asm`。`choose_culture` 在 `1C0BF` 把选择编号写入 `Plr+0xD (AC8604D)`；`1C0D6` 读取 `CULTURE_INHABITANT (2641C0)` 的对应指针，`1C0DF` 将民族称呼复制到 `Plr+0xE`，容量18字节。`plrnam:1ACCD1..1ACD2C` 以 `%s %s` 拼接 `Plr` 姓名和 `Plr+0xE` 民族称呼，`Choose_Name` 的原规则禁止姓名中含空格。因此仅在最终标题调用取原文本第一个空格前的完整姓名，并按文化编号借入译文，不改 `plrnam`、原字符串、文化编号、姓名或存档。此前“姓氏”判断没有追溯到该构建链，现已纠正。

`desced_stat` 先 `showtext`，再按原参数调用 `statbar`，没有按标签字节数推算柱条位置。`TekstiPalkki` mode 4 为左对齐；四个分组及顶部姓名仍沿现有原生标题路径。现有 `textwidth`、`14709B` 标题度量、`13EA00` 光标、`13EEC3/13F00F` 段落扩展与 `13B760` 即时字形输出继续处理双字节传输编码，未将 UTF-8 直接投入原 ASCII 字形索引。

确认说明按语义短句提供词元，其中“你的角色属性如下。”与“你对这些属性满意吗？”之间使用原词元分隔空格。提示词元均不超过15个中文字元、30字节传输编码，低于原生130字节槽；换行由游戏段落宽度决定，没有坐标、行槽或整页内容快照。

本菜单为 mode 0。`LIST_Reset` 清零 `List+8C` 的按字宽选择标志；`LIST_AdvStyle(1,0)` 只写 `List+7C/+80` 的文字样式，不启用字宽选择。`LIST_Highlight` 的前缀偏移继续消费未变的 ASCII 键帽，选择框长度取原面板宽度。无第二字段 `|`，不需要给它新增字宽调用。没有让原生选择或鼠标命中消费 Mod 布局。

字形在原生调用中立即绘入已接入真实输出密度的 screen；图像、窗口、柱条、背景缓存、上传和呈现继续由游戏持有。没有全局像素扫描、文字贡献序列或延后重放。

## 刷新边界与既有待整改项

本页按原生构建时的语言生成文本。`draw_profile(1)` 包含菜单重置、输入等待和 `REROLL/REROLL_POS` 修改；上层 `character_creation` 还包含随机身高体重、随机属性、文件与角色流程。不能为了刷新直接重入这两个完整函数。

mode 0 的 `LIST_Draw` 也不负责擦除旧背景，单独调用它不能完成中英文切换。此次没有把属性作用域加入现有 `redraw_language` 列表重画分支。即时整页纯刷新边界仍待确认；热加载 Applied 只表示业务交接，不代表截图中的已有像素立即更新。后续原生页面重建会消费新中文，无需卸载模块或更换启动路径。

既有事项继续记录：

- `src/linux/adapter.cpp` 的 `glyph_request` 固定使用原生逻辑行高/墨高，原 `showtext` 四次阴影的完整预算尚未传入字体校准；`src/linux/native_targets.cpp` 只有主菜单已确认完整缩放重建边界。影响为非主菜单中途缩放后的旧目标密度与描边预算；状态仍待整改，见 `20261019-linux-font-density.md`，本次未宣称解决。
- `docs/evidence/20261019-character-profile-native.md` “64字节词元边界”表述不准确，原生槽为130字节；本次按实际槽与本次译文长度接入，该历史表述待更正。
- `docs/evidence/20261019-season-portrait-native.md` 的 Linux 无热更新协议描述属于 ABI 1 时的历史交付状态。当前正式驻留桥已为 ABI 2，当前能力以 `20261019-linux-hot-reload.md` 为准，不把旧结论套用到本次。

## 交付状态

源码修改、统一队列编译、正式文件发布和已授权兼容热加载均已完成，完成时间为 2026-10-19 14:57:32（Asia/Shanghai）。

- 本次与同仓库百科任务协调共享源码冻结及全部构建参数，由百科任务执行一次根 `build.ps1 -Toolchain Linux -Module adapter,semantic,catalog -Publish -Reload -TargetPid 3820329`。使用 `/usr/bin/cmake`、`/usr/bin/g++`、原 `build/linux-x86_64` 和正式 `package/`，本任务未重复提交请求。
- 共享请求 `6ed8389c1e084851adcfe40037a7bddd`，批次 `931761f724724daabc44927a2b541694`。本任务已读取对应请求 JSON、结果 JSON 与完整批次日志，`Success=true`、`PublishRequested=true`、`ReloadRequested=true`。一次配置、一次增量构建，三个目标完成；仅有 Semantic 原有 HUD/world 枚举分派 `-Wswitch` 警告，无新增属性组件遗漏或编译错误。
- 正式事务 `0dad871b26a14272a5876a06fb28c497`。已读取 `build/linux-x86_64/stage/0dad871b26a14272a5876a06fb28c497/publication-result.json`：`success=true`、`runtime_requested=true`。
- 本批次替换 Adapter、Semantic、主词库、文化百科词库、Linux profile、发布清单六件。旧六件先按原相对路径移入 `回收/20261019-145732-0dad871b26a14272a5876a06fb28c497/package/`，本任务已只读确认文件存在。Catalog 产物身份未变化，仍因词库更新参加热加载。根启动器与驻留桥未替换，没有平行运行包。
- PID `3820329` 返回 `ReadyToPublish` 与 `Applied`，Catalog、Semantic、Adapter 均为第2代。此回执证明模块已交接，当前属性页原有像素仍受上文原生重建边界限制，不作为视觉验收。
- 已只读核对 Adapter、Semantic 的构建/正式文件及主词库、Linux profile 的源码/正式文件 SHA-256，分别一致，并与正式清单、热加载回执对应身份相符。

| 正式内容 | SHA-256 |
| --- | --- |
| Adapter | `492e5569f40c8e459d8ae616250788317a9df0c8896ef0e0af458f838f72d0a1` |
| Semantic | `99925faa8dbf5d4f34062695bdc05785e373c75ed3acfc6ed646fbd0ccd24db0` |
| 主词库 | `e58ff526f600a3835f6fbadbcfe48c2e07301831f0cd1d465cb0489a0e4f6bd9` |
| Linux profile | `de3cfe4b8c3910d7c1cc755264b0e98c6f48a02b2a60457bf84d6463ede14038` |

### 民族称呼补充交付

2026-10-19 15:15:20（Asia/Shanghai）完成民族称呼遗漏修复的源码修改、队列编译和正式热发布。复用原十个文化译名，不增加词库或语义 ABI；此前错误保留民族英文的结论已在本文开头更正。

- 根入口 `build.ps1 -Toolchain Linux -Module adapter -Publish -Reload -TargetPid 3820329`，显式沿用 `/usr/bin/cmake`、`/usr/bin/g++`、`build/linux-x86_64`、正式 `package/`。提交前源码已保存，批次结束前未继续修改。
- 请求 `80dfa14455d34f8ebbb0e90244adf873`；批次 `a2f7915b918b4e888f9a784a392f70e9`。已读取请求结果和完整批次日志：`Success=true`，一次配置和一次增量构建，无警告或错误。
- 正式事务 `54020cbb707c43d084e8e5b9a9490cd9`，已读取 `build/linux-x86_64/stage/54020cbb707c43d084e8e5b9a9490cd9/publication-result.json`：`success=true`。旧 Adapter、Linux profile 和发布清单三件先移入 `回收/20261019-151520-54020cbb707c43d084e8e5b9a9490cd9/package/`，本任务已只读确认。
- PID `3820329` 返回 `ReadyToPublish` 和 Adapter 第4代 `Applied`。正式 Adapter 的 SHA-256 为 `2771d4272fe201b5d80188fae5107e1df101b1d8cc0447753cb7d1ce71f138e2`，构建文件、正式文件、发布清单和回执一致；Linux profile 为 `a5e3c657517e6eb88db910a16a5489a93ebfefcb1ea3958a37df79ad93230bf3`，源码、正式文件与清单一致。
- 本补充只在原生标题构建调用生成“原姓名＋中文民族”，当前已绘出的旧标题仍等待原生重建，未增加整页重放或输入操作。

未启动、关闭或重启游戏，未注入或模拟输入，未运行产物或测试，未写测试用例或断言，未添加推测性保护、回退或兜底分支。
