# 2026-10-19 角色创建方式菜单汉化

本次范围为截图中的 `CHARACTER CREATION` 菜单：标题“角色创建”，五个选项为“快速简易”“自定义”“自定义 - 简单”“自定义 - 极易”“退出”。Q/C/E/T/ESC 键帽、原动作和两条空白分隔行保留。

## 原生接入与静态依据

目标为 UnReal World 3.89 / Steam Build 25939378，原 EXE SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。地址均为 RVA。依据见 [边界说明](20261019-character-creation-static.txt)、[原始指令](20261019-character-creation-disassembly.txt)；既有反编译为 `credits-ghidra.c` 的主菜单分支以及 `ancestors-ghidra.c` 对应分支。

- `125CFB → CFFB0` 是本页绘制调用，建立仅覆盖该次调用的作用域。标题和各条英文记录仍由 `CF790/CF990` 构建，Mod 不修改原生数据表。
- `D01A5 → 115E70` 在本页作用域内借入中文标题。原生 flags 4 选择 `1157B0` mode 2，最终由共享 `115A94 → 10E5A0` 绘制。该模式左对齐，不经过按字节计算居中的分支。
- `D031F → 114680` 通过当前原生行 `ESI+0xC8` 的动作身份选择五个文本组件。借入的字符串保留点号及此前的 ASCII 快捷键，中文后缀由 `1149F9 → 10E5A0` 一次消费。键帽仍走原生逐字符循环，中文不会进入该循环。
- 完整中文后缀沿既有安全传输编码、真实字体度量、`10E700` 光标推进和即时高清字形绘制进入当前原生目标。没有新建低分辨率中文字面再放大，也没有页面坐标、行槽、像素贡献记录或延迟重放。

`CF990` 不测字宽；本页无 `|` 后第二字段，故不进入 `D03BB` 的附文偏移路径。原生 mode 8 的选择框使用面板右界与原快捷键前缀计算，`CF790` 已清零按文本宽选择标志，不进入 `D07FB strlen*8`。`D0570` 鼠标命中同样使用原生行位置和面板宽度。故本次不修改选择框或命中几何，也不错误套用仅属于 `CFAF0` 的 `CFC5D` 宽度扩展。

## 已打开页面与语言切换

保留 `125D00 → D1120` 原调用不加 Hook，因此现有 `D12B4` 输入返回边界的 `[EBP+4] == image_base+125D05` 能精确识别本页。首次热加载、依赖更新、尺寸重建或语言切换令本页刷新标记生效；在上述自然边界只执行 `125CFB..125D00` 平衡绘制片段，不重新初始化菜单、不退出输入等待、不重放角色生成业务。

随后复用原生 `D1189` 对应工作面复制、`D0650` 当前选择绘制及 `10B720` 上传呈现。这里复制的是游戏已有像素，原生矩形对象和缓存仍归游戏；没有 Mod 文本重放。当前输入结果与寄存器帧保持原值，原按键动作继续由游戏分派。

共享尾部 `refresh_menu_cache()` 由既有主菜单重绘代码提取，主菜单行为保持原流程。Host ABI、`Active` 结构和 HDA3 状态尾部大小均不变；本页刷新标记属于每代初始化状态，不保存任何页面内容。当前页刷新在下一次原生输入返回边界发生，Applied 回执本身不证明画面已完成刷新。菜单外已经绘出的背景组件保留其自身原生重建时机。

## 现有冲突与范围

`docs/evidence/main-menu-static.txt` 的历史“Scope and Chinese output”段仍要求保留原 `strlen*8` 光标，并在“Footer”段要求按已知位置重画整个字段；这与现行编码、真实字宽和禁止独立排版要求冲突。影响：不能用该旧方案证明本次实现合规；状态：历史证据保留，方案已废止，其活动实现以当前源码及本轮原生边界记录为准。该文件的原始指令仍可作为静态证据。

`docs/hot-reload.md` 的历史 DisplayPlan/行槽方案、宿主错误透传等已记录的未整改项继续分别以 [语言切换记录](20261019-language-toggle.md) 和 [实现纠正记录](20261019-implementation-correction.md) 为准，本次未扩展处理范围。

## 交付状态

源码与词库、统一队列编译、正式文件发布及兼容热加载均已完成。并行聊天的先祖、读取角色和鸣谢改动保持原样，本记录只认领角色创建方式菜单。以下时间均为 2026-10-19 Asia/Shanghai。

- 六项组件、semantic 映射和词库先随并行请求 `a5ccf43f77b4480993ca5f3693b4817d`、批次 `3a8077d74baf4b8c81163a6d107dec37` 于 08:15:05 发布。事务 `47b3089b3f5a48fdb39bc09ef77963a3` 返回 `ReadyToPublish`、`Applied`，其中 Catalog、Semantic 均为第 3 代。该事务 stage、当前源码和正式词库 SHA-256 相同；stage、out 和正式 Semantic DLL 相同，且均含六个 `character_creation.*` 标识。
- 本页最终 Adapter 源码保存于 08:16:37；并行请求 `332a1669776c48559b41f0ceeeb1306f`、批次 `22ac1ead4ed94d49bbcafcfffe5bed5c` 随后重新编译 `module.cpp`、`native_language_redraw.cpp`，于 08:17:09 完成事务 `a3cb9e6df32c47f7985f0cc73ae2dd41`。PID `65412` 回执为 `Applied ... adapter:f106a36555b7528cf0e5aa6f22966b25bdd5d7417fbc489e92038c0d5d2252b3:7`。旧正式 Adapter、适配文件和清单先移入 `回收/20261019-081709-a3cb9e6df32c47f7985f0cc73ae2dd41/`，再替换正式位置。
- 本聊天调用根 `build.ps1 -Module adapter,semantic,catalog -Publish -Reload -TargetPid 65412`，请求 `33d3364888ba498da8732acf750d1d05`、批次 `3973da554bad4982bfd1842a8749e8ca`。三个编译目标全部成功且已是最新；但并行批次已发布相同 DLL/词库，因此本次仅剩新增 profile 说明与清单。事务 `db427681cb3542318c4c4990aaa04152` 发出空模块 mask 的 PREPARE，被驻留桥返回 `Failed invalid request`，批次 `Success=false`。没有移动或替换文件，不能把该回执认作本聊天热发布成功。
- 队列空闲后，通过根 `build.ps1 -Module adapter,semantic,catalog -Publish` 补发上述仅元数据差异。请求 `c636c1ee47014a7aa92bac9f6de8f4c5`、批次 `0a51facda4bf474c931420818bcbb6bb`、事务 `b084f1f94c834c58ade7dec3b9d9a7c0` 于 08:17:51 返回成功。只替换正式 `package/profiles/urw-3.89-steam-25939378.json` 和 `package/release.json`；旧两件先移入 `回收/20261019-081751-b084f1f94c834c58ade7dec3b9d9a7c0/`。这次不请求运行时加载，沿用上两项已确认的 Applied 业务模块。

已读取以上请求对应的 `build/.compile-queue/results/<request>.json`、完整批次日志和各 `stage/<transaction>/publication-result.json`。正式清单十个文件的 SHA-256 与磁盘逐项一致；构建产物与正式 Adapter 相同。现有 SDL `GetRGB` 函数类型转换警告仍在，无编译错误。

| 正式内容 | SHA-256 |
| --- | --- |
| Adapter | `f106a36555b7528cf0e5aa6f22966b25bdd5d7417fbc489e92038c0d5d2252b3` |
| Semantic | `2d826d31f2a07d6d93386d2e8ab0327496926f237ad34426983d7d2a469bc218` |
| 词库 | `558d5e2f38b5d03774faa158cb84e59f6168598a20c66d7551ec9dea35af20f7` |
| 构建适配 | `14ccf495f82579497a13a61bbdb3b2754c16c51d98a0d08c4322943e9fe8b178` |

正式启动器仍为根 `uwcn_launcher.exe`，驻留桥仍为 `package/uwcn_loader.dll`，未更换、不要求退出重启，也未建立平行运行包。本聊天提交后的源码保持冻结，后续只补写交付记录。

已观察到的发布脚本问题：`publish.ps1:103–108` 对只含 profile 等元数据差异的 `-Reload` 请求仍发出 mask 0；`src/loader/host.cpp:305` 明确拒绝该值。影响是业务已发布时的后续元数据热发布批次失败。状态：本次使用已有 `-Publish` 路径完成实际剩余文件发布，未改动发布脚本；该分支修正待后续处理。没有以重试、回退或重新注入隐藏失败。

未自行启动游戏、重新注入、模拟输入、运行产物或测试；未创建测试用例或断言。静态审查和编译不代替用户的视觉验收。
