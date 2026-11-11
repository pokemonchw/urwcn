# 动物指令菜单：完整分支、文本来源与汉化接入

2026-11-11，Asia/Shanghai。对象为用户截图中的 `ANIMAL COMMANDS: COW` 原生侧栏菜单，Windows x86《不真实的世界》3.89.1 / Steam Build 26139145。原 PE 为 `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256：`c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。本文地址用 RVA，原始汇编用 VA，基址 `00400000`。

仅做磁盘 PE、原生反编译、反汇编及源码静态分析。没有启动、关闭、重启、注入或模拟操作游戏，没有运行测试、创建测试用例或断言。发布仅使用用户已经授权的驻留兼容业务交接事务；Applied 不是画面验收。

## 提取产物与范围

- [反编译提取脚本](animal_commands_Decompile.java)：在已有 `inventory3891` Ghidra 工程中以 `-readOnly -noanalysis` 提取13个函数，结果为 `build/analysis/animal-commands-20261111/native.c`，运行记录在该目录 `console.log`、`ghidra.log`。两个提取过程均正常结束，丢弃只读程序改动。
- [完整动物菜单及命名函数反汇编](20261111-animal-commands-native.asm)：原 PE 的 `5431D0..544010`；原生通用菜单另存于 `build/analysis/animal-commands-20261111/command-menu.asm`。
- [菜单与提示全文](20261111-animal-command-menu-text.tsv)：17条，包含2个标题、11个动作标签变体和4条提示。记录原生生产者、完整英文、实际词库域和中文。
- [命令反馈资源及递归子资源全文](20261111-animal-command-resources.tsv)：14个资源键、113个分支，包含方向和全部声音选择器；保留实际资源文件、行号、selector、英文与中文。

提取边界覆盖 `143340` 的全部菜单构建与选择分支、`1431D0` 命名、`AD4F0` 动物称呼、`24650/24600/23DF0` 即时进食反馈、`133620` 接受或拒绝攻击指令、`24720` 留下动作入队，以及 `1002B0` 原生菜单与 `F7820` 选择目标接口。进入游戏普通 AI、进食或战斗动作之后的通用业务消息继续使用其已有消息链；本次不重写业务或重入动作来生成显示。

## 入口、距离和群体名单

`146200` 在 `146E48` 经过原生人类/动物分派，在 `146E86` 调用 `143340(actor, mode)`。调用者保留真正动物索引和原模式；`mode == 0` 时才有原来的就近进食、停留、命名选项。原非人类筛选证据也见 `20261020-type35-animal-name-domain.md`。

距离 `d` 来自原生 `ActorX/ActorY` 与玩家位置的两个差值绝对值之最大值。`04B8E0EB == 0` 且 `d < 11` 才设置“可以就近回应”；另一分支令 `d = 50`，不能就近回应。

原函数遍历当前地图对象，筛选对象类型4、有效动物索引、非人类、状态9或owner=-1、与目标相同species。普通地图还要求距离不超过50。这个原名单决定群体模式是否可用；Mod不建立或修改动物名单。

## 全部菜单分支

原函数先清空上层 `619F988`、stride `20C` 的命令表，按条件添加动作。所有表中行号只作为证据，不作为Mod布局或动作映射。

| 原键 | 完整英文标签 | 真实出现条件及后继 | 实际中文 |
| --- | --- | --- | --- |
| E | `Eat now` | `record+524/+528` 至少一个非零，`mode=0`，可以就近回应；选择后调用 `24650(actor)` | 现在进食 |
| E | `Eat now (all)` | 同一原进食条件，已开启群体模式；选择后遍历原名单调用 `24650` | 现在全部进食 |
| A | `Attack` | species=`26A`；不额外增加距离或mode条件；进入原 `F7820(mode=1, empty title)` 选目标 | 攻击 |
| A | `Attack (all)` | 同一species条件，已开启群体模式；先对名单逐个输出原指令，再由原业务分派攻击 | 全部攻击 |
| F | `Follow` | 非群体，`A9790(actor)=0`（state不是9），`record+1DD` bit0置位，`record+1E4` bit200置位 | 跟随 |
| S | `Stay` | 上述非群体与bit0条件，bit200未置位，且`mode=0`、可以就近回应 | 留下 |
| C | `Come` | 上述非群体与bit0条件，bit200未置位，且`d>=3`；可以在远处喊 | 过来 |
| N | `I shall name you...` | `mode=0`、非群体、可以就近回应；选择后调用 `1431D0(actor)` | 我要给你取名…… |
| + | `Group command` | 原名单至少2个，当前非群体；设置原局部群体标志并回到`1434B0`重建原命令表 | 群体命令 |
| - | `Group command off` | 原名单至少2个，当前为群体；清除原标志并重建原命令表 | 关闭群体命令 |
| ESC | `Cancel` | 原`10048C/10049B`添加空分隔行和动作27；取消后按原switch退出 | 取消 |

`143B64`写“关闭群体命令”，`143C04`写“群体命令”；以实际汇编和原键值为准。空分隔行仍为空。上层构建器原有的51行容量、34字节截断及`1002B0`的25行限制均未改变；本菜单全部固定动作标签连同原键前缀和` (all)`都在该原限额内，汉化在完整消费者处借用中文，不对中文执行原ASCII字节截断。

如果就近才能执行的选项被距离排除，而仍有可喊出的指令，原函数输出 `?It's too far to respond, but you can still shout these commands.`；对应中文“距离太远，对方无法回应，但你仍可以喊出这些命令。”。若原可执行指令数为0，原远处路径使用 `TALK_FAR_AWAY`，近处路径直接退出。Mod不补造选项。

## 标题与动物名称的全部语义分支

非群体分支在`143C52`调用 `AD4F0(actor,0)`，`143C64`把结果写入 `ANIMAL COMMANDS: %s`。群体分支在`143C6E..143C8D`复制 `ANIMAL GROUP COMMANDS`。`143CAA`打开原生`1002B0`。

已有`windows_message_values::npc_source`按原生动物字段保留完整名称表达式。本次直接把`windows_message_menu_echo::echoes.back().title`交给同一个原Menu的标题资源；这个同步栈保存的是尚未返回的`143CAA`的实际标题输入。没有从大写后的显示标题猜物种，也没有按英文单词重译玩家专名。

| `AD4F0` 原分支 | 可见来源与已有汉化 |
| --- | --- |
| 未知专名的普通动物 | 使用原record+8描述的`npc`词库，例如`cow → 母牛`；不限于截图中的牛 |
| 幼年bit2 | 按species使用`calf/piglet/lamb/puppy/cub`，或完整`%s %s`物种与幼崽组合；中文沿已有完整格式 |
| 成年雄性 | 特定species的`bull %s`、`ram`、`boar`、` stag`，其余仍用原描述 |
| 成年雌性 | 特定species的`female %s`、`sow`、`female dog`、` doe`，其余仍用原描述 |
| known低位已知、flags=0 | 读record+30专名并保留原值；专名即使等于`cow`等词库词也不改为物种译文 |
| 命名提问flags=6 | 原生按known位选择描述、专名、`%s the %s`、`%s called %s`及`the %s`；参数身份沿原AD4F0表达式 |

`1002B0`在`1002DB`调用`D3DB0`生成原生大写标题，并在`1003B8`把自己的真实局部标题交给`CF790`。因此截图的`COW`是标题展示的大写副本。语义源仍是大写之前真正的动物描述/专名；内部英文和玩家姓名数据保持原值。

## 命名、进食、攻击与声音反馈

`1431D0`的完整提问为 `?What do you want to call %s?`，已有`message.format.005b62a4`译为“你想给%s起什么名字？”。`143215`输出`#Type a name: `，已有译文“输入名称: ”。`143221`以color=0、capacity=15调用`10F5B0`。

新增Hook `native_name_input::animal_scope=5414`只覆盖已确认的`143221 → 10F5B0`完整CALL，使用现成姓名输入before/after生命周期。其间复用SDL文本提交、完整UTF-8字符追加和退格、原输入清除宽度、原光标与IME候选框接口。保持原15字节容量及100字节共享输入缓冲；不扩大record+30名字字段，不改记录后继字段。确认和取消均由原CALL返回后停止本次文本输入。没有为动物命名建立另一套编辑控件。

CALL钩子的真实驻留实现见`src/loader/hook_host.cpp::urwcn_before_route`：被调函数的返回地址会替换为After桥。因此原有`native_text_edit_language`直接比较getst的`[EBP+4] == image+143226`，不能识别这个新带CALL范围的动物输入。后续静态复核据此补入`accepted_caller`，同时用于实际输入entry和语言唤醒重建。两个既定name scope的调用者都建立EBP；原getst的`PUSH EBP / MOV EBP,ESP`保留该父帧，见`build/analysis/animal-commands-20261111/getst-frame.asm`。活动name scope中，父帧自己的未钩选返回地址`143D45`明确标识`143D40 → NameAnimal`，且NameAnimal唯一getst调用就是`143221`，因此恢复其真实语义调用身份`143226`。没有改写返回地址、驻留ABI、序列化格式或按提示文字猜输入类型。其余getst调用仍读取原生直接返回身份。

非空且不是ESC的输入仍由原`143266..143282`写known位及专名，随后原`SOUND_NORMAL`反馈。空或ESC在`1432AF`输出既有`!Canceled. → 已取消。`。这是中文输入接入，不宣称修复此前没有异常地址/转储的“命名后闪退”；该问题的已有未决证据仍保留于`20261111-animal-naming-crash-analysis.txt`，其中中文输入缺口C已由本次修改处理。

进食的`24650`使用`PET_PHRASE:EAT`，随后由`23DF0`实际寻找食物，原返回值选择`RESPONSE_HAPPY`、`RESPONSE_CONFUSED`或经`24600`选择`SOUND_DISAGREEMENT`；寻食过程也可产生`SOUND_HUNGRY`。群体进食重复的是原游戏动作，不由Mod模拟。`23DF0`内的Finnish诊断文本由原debug开关控制，属于已有debug格式消息链，并非此菜单的选项。

攻击选择取消输出`!Canceled.`，空目标选择`GOOF_NO_CREATURE`；实际目标继续由原`133620`决定是否服从。受伤拒绝用`SOUND_WOUNDED_DISAGREEMENT`，普通拒绝用`SOUND_DISAGREEMENT`。F/C共同使用`PET_PHRASE:COME`及`SOUND_AGREEMENT`；S先输出`PET_PHRASE:STAY`，原地图类别分支决定入队留下动作或输出拒绝声音。

`143E02`的人类/actor=-1退化分支还含`I won't do that!`并调用`258B0 → NPC_SAYS`；已提取并记录。原动物入口不接受人类或-1，这不是当前动物菜单可见的拒绝文本，不能把它误列为动物叫声的替代源。动物分支使用上述真正的声音资源；本次没有扩展人类对话功能。

14个资源键为`PET_PHRASE`、`TALK_FAR_AWAY`、`GOOF_NO_CREATURE`、`RESPONSE_HAPPY`、`RESPONSE_CONFUSED`、`SOUND_NORMAL`、`SOUND_HUNGRY`、`SOUND_AGREEMENT`、`SOUND_DISAGREEMENT`、`SOUND_WOUNDED_DISAGREEMENT`、`IN_DIR`、`SND_PRES`、`SND_CONT`、`SND_NOUN`。113条包括20条命令与反馈分支、9条方向、84条声音词形；具体以TSV逐条原资源为准。这些翻译已存在于源词库及正式词库，本次复用而不增加重复键；资源选择、声音播放、标签与业务值仍由游戏决定。

## 原生显示、度量与当前菜单交接

`windows_animal_commands.inc::bind_animal_commands_menu`在`module.cpp::bind_menu_consumer_source`的实际标题消费者处绑定同一原生Menu的标题与原行。行数取真实header+14h，每行取真实E8记录，按原点号分出键帽和完整标签。`Eat now (all)`和`Attack (all)`各自是完整标签词库源；原空行保持。没有按照动作键构造、排列或补齐一个Mod菜单。

原`1002B0 → CF790/CF990 → CFFB0`继续管理窗口、行距、按钮和选择。标题走原kind6的`116270`面板；其居中与宽度接口已有中文字宽扩展。完整键帽标签沿`D031F → 114680 → 10E5A0`，选择框和命中宽度沿`D07FB/D0A49`，中文字形经现有传输编码和完整字宽接口进入真正原生目标。复用现有主表面输出密度与叶字形调用，没有新增SDL像素观察、低清文字放大、坐标表、独立DisplayPlan或Present前叠字。

当前已打开的菜单在授权交接/语言唤醒后，既有`native_parent_cache_language::menu`识别真实D1120 caller `100645`，经`command`调用完整原`1002B0`构建。`command_storage`恢复同一真实source_menu，普通`CFFB0`再次经过本次消费者绑定；不依赖被`materializing()`排除的历史绘制回调。`echoes`和类型化动物来源沿既有兼容序列化保存；本次没有新增持久化字段、驻留ABI或文本快照。选择及输入保持原生，不重入`143340`、命名、喂食或攻击动作来刷新菜单。

## 既有所有权问题，仍待整改

- `modules/adapter/native_ui_scene.cpp:12..20`的Child/Container历史组件集合及后续缓存语义冻结仍保留，影响完整原生UI/缓存所有权整改；待退役。本次未新增页面组件集合或遍历它重放文字，不能用本次编译/发布证明旧集合合规。
- `modules/adapter/native_footer_component.cpp:58..88`，尤其79..87，仍由Mod计算署名宽度、位置和间隔，影响主菜单署名布局；待整改。本次动物菜单不新增或调用该署名布局。

## 编译与正式交付

初批请求`c46486c1aa9a450cb7165cd4706d4ddc`、批次`837037e2ec7847f5924d1f3cdb59eb33`已编译发布为第4代，事务`27adfcb3eebc4eb8a9f4790dd23dd9d7`。随后静态复核发现上述CALL返回身份问题，修改`native_text_edit_language.inc`后另提交最终修正请求。初批请求JSON、完整批次日志与发布JSON均已读取；初批源码不代表下表的最终正式版本。初批旧件位于`回收/20261111-173709-27adfcb3eebc4eb8a9f4790dd23dd9d7/package/`。

两个请求各自在源码保存后冻结请求范围，通过同一根入口各执行一次配置、一次增量编译和串行正式发布。两次批次运行期间均未继续修改其Adapter源码；第二次针对实际新增修正，没有重复提交同一份修改，没有运行编译产物作验证：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 360 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2735482958/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 已读取回执 |
| --- | --- |
| 请求 | `8e4ac8ef9cdb43a9b3d7e828ffc688d6` |
| 批次 | `a00350d35fa14cd59a8fd508d43db7a0` |
| 请求结果 | `build/.compile-queue/results/8e4ac8ef9cdb43a9b3d7e828ffc688d6.json`，Success=true，PublishRequested=true，ReloadRequested=true |
| 完整编译日志 | `build/.compile-queue/batches/a00350d35fa14cd59a8fd508d43db7a0.log` |
| 发布事务 | `391810f39a6f43029cf2964a0b70edb5`，2026-11-11 17:41:15（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/391810f39a6f43029cf2964a0b70edb5/publication-result.json`，success=true，runtime_requested=true，applied=true |
| 正式文件 | `package/modules/urwcn_adapter.dll`、`package/release.json` |
| 旧件归档 | `回收/20261111-174114-391810f39a6f43029cf2964a0b70edb5/package/`，保留原相对路径，先移入回收再替换 |
| 当前进程 | 宿主PID3385055、Windows PID360，原驻留业务事务先ReadyToPublish，后Adapter第5代Applied |
| Adapter SHA-256 | `cdae5ba01f9d7cc5209eb4e4967edcab3aa11b5cf688d554dbf07d034cb538f4`，构建文件、正式文件及Applied回执一致；本批回收的第4代为`fac9d97538f8ed6771a3ca576ff28558da8f593a384aa8887a735b972a79fe2b` |

编译保留既有函数指针转换、extern初始化、未使用项及缩进警告，没有编译错误。词库本来已有以上译文，未要求编译/发布Catalog，也未替换启动器或驻留Loader。根`urwcn_launcher.exe`继续使用相同正式包，无平行交付目录。

本次源码修改、产物编译、正式发布与兼容业务交接均已完成。未启动游戏、未模拟输入、未运行测试；用户画面验收尚未执行。
