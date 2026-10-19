# UnReal World 本机游戏分析

分析日期：2026 年 10 月 18 日。目标是 Steam Windows 版 UnReal World 3.89，供 URWCN 汉化 Mod 设计使用。

**结论：已找到背包及物品检视的业务入口、列表行关联和对象描述读取候选，可以围绕 UI 功能与对象数据建立语义汉化。** 翻译应在 UI 字段构建或消费边界生成中文视图，SDL 仅用于最终绘制。原有点阵字体及固定缓冲的限制仍需在中文输出层处理。

## 本机版本和分析范围

| 项目 | 本机证据 |
| --- | --- |
| 安装目录 | `D:\program\steam\steamapps\common\UnRealWorld` |
| Steam App ID | `351700` |
| Steam Build ID | `25939378`，来自 `steamapps/appmanifest_351700.acf` |
| 游戏版本 | `news.txt:4`、`init_log.txt:1` 与 EXE 内嵌字符串均为 `3.89` |
| 主程序 | `urw.exe`，2,249,216 字节，PE Machine `0x014C`，32 位 x86 |
| EXE SHA256 | `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9` |
| 图形库 | `SDL2.dll` 文件版本 2.30.0；日志编译及链接版本也为 2.30.0 |
| 随包字体库 | `SDL2_ttf.dll` 文件版本 2.20.2，32 位；存在于目录不等于被游戏文字路径调用 |
| 字体资源 | 安装树仅发现 `URW.FNT`，未发现 TTF、OTF、TTC |
| 运行记录 | 现存 `debug_renderer.txt` 记录使用 direct3d、缩放质量 2；这是历史日志，未作为当前进程现场 |

本次检查了安装文件、PE 导入、选定代码的静态反汇编和已有日志；没有启动游戏、注入 DLL、抓取运行内存或操作存档。以下 RVA 是本机这个 EXE 的静态定位线索，实际调用频率、参数约定及界面覆盖仍须动态验证。

官方开发历史记录了 C/C++ 与 SDL、SDL 2 的演进，结合本机 PE 依赖，本项目应围绕原生 x86 程序和自有 UI 分析，无需走 Unreal Engine 的 UObject、FText 或 UMG 路线。[官方开发历史](https://www.unrealworld.fi/urw_devhist.html)

## 文字来源

### 外置消息和说明

`messages/` 共 9 个 TXT，其中 7 个文件合计有 431 个以 `.UPPER_CASE_ID.` 开头的消息段。段数包含定义和辅助内容，不代表 431 个独立句子，也不代表汉化覆盖率。

| 文件 | 消息段数 | 用途与注意点 |
| --- | ---: | --- |
| `urw_msg.txt` | 240 | 通用消息、状态、动作反馈；包含 `%s` 参数及条件分支 |
| `urw_combat.txt` | 114 | 战斗消息，包含攻击者、武器、部位等动态值 |
| `urw_chat.txt` | 34 | 对话及心情分支 |
| `urw_defs.txt` | 20 | 共用文本定义 |
| `urw_sounds.txt` | 13 | 声音描述及音效行为标记 |
| `urw_pronouns.txt` | 9 | 代词与语法辅助 |
| `urw_tags.txt` | 1 | 标签定义 |
| `guide_values.txt`、`urw_uname_flora.txt` | 0 | 动态值说明、未知植物描述等辅助内容 |

这些文件的现有字节均为 ASCII。ASCII 也能被 UTF-8 解码，因此这一结果不能证明原加载器支持中文或 UTF-8。

资源中的内容是有语法的消息模板。例如：

```text
.WOUND_TREATMENT_RESULT.
:After treating the %s you consider it %s.

.WAKE_UP.(who)
[PC::You wake up.]
[*:<npc_defdesc> wakes up.]
```

前者的注释指定两个 `%s` 分别为伤口描述和伤口状态，见 `messages/urw_msg.txt:53`；后者同时含消息 ID、参数、玩家分支和 NPC 描述标签。`messages/guide_values.txt:39` 起还说明了物品数量、品质、容器、原始名称等显示变体。`urw_sounds.txt:117` 附近的 `{<npc_sound>}` 会触发音频，不能作为普通文字删掉。

其他可用文本来源包括：

- `GAME.NFO`：外置百科，含 `.WORLD.` 等主题键、`***` 分隔及 `<br>`；当前文件含非 ASCII 字节且不是合法的严格 UTF-8，需要单独识别编码。
- `gameinfo/urw_scrinfo.txt`：部分界面说明，含 `<br>`、`<green>` 等样式标记。
- `diy_glossary.txt`、`cookery_glossary.txt`、`biy_glossary.txt`、`flora_*.txt`、菜单定义：混合显示内容与游戏规则，不能整文件逐词替换。

### 内嵌和动态文本

EXE 中能直接找到 `Press a key to continue` 等提示、带 `%s` 的消息和对话控制串。官方开发者 Sami 在 2020 年也曾解释，大量文字硬编码，句子会在运行时拼装。因此单靠外置资源或静态字符串列表无法推定全覆盖。[开发者关于语言版本的说明](https://www.unrealworld.fi/forums/index.php?topic=5349.0)

业务建模至少覆盖固定界面字段、事件消息、物品复合名称和长篇百科四类。对象及事件的类型、参数、来源和可见性应在进入最终文字绘制前取得。

## UI 业务和对象数据定位

新增调查以 UI 操作和对象数据流为中心，没有从 SDL 回调捕获原文。以下证据来自 [UI 静态逆向记录](evidence/ui-semantic-analysis.txt)，函数职责仍需动态确认。

### 背包和物品检视

RVA `0x58E30` 同时使用携带物品提示和 `examine (weapon or armour)` 操作说明，调用 `0x55060`。选中行非负时，程序将索引乘 `0x20`，读取 VA `0x006EEDA8` 行表的 `+0x04` 与 `+0x10` 字段；其中 `+0x04` 值被送入 ECX，进入 `0x48EF0`。

`0x48EF0` 再通过 VA `0x0A72ACD0 + index × 4` 取得 handle，调用 `0xC0190` 读取对象描述。函数还使用 `EXAMINE_ITEM_SKILL`、`EXAMINE_ITEM_CLASS`、`EXAMINE_TWO-HANDED_ITEM` 等键，并对不支持类别提示只能检视武器、防具及衣物。这些调用和分支共同支持“装备检视业务入口”的判断，强于单独按屏幕文字命名函数。

上述地址中的 VA 是 PE 首选基址下的静态全局地址，运行时必须先换算为数据 RVA 并加实际模块基址；它们不是已捕获的进程现场地址。

### 列表字段和分类语义

RVA `0x54160` 的列表呈现候选从行记录读取 handle，调用 `0xC0190`，将返回的 `0x2B` 个 DWORD 复制为 `0xAC` 字节局部描述，再读取首字节。RVA `0x54337` 将该分类码送入 `0x48AD0`，其返回标题随后进入 UI 显示消费者 `0x1157B0`。

`0x48AD0` 的分支和静态标题可建立以下映射：

| 分类码 | 原标题 | 可用中文 |
| --- | --- | --- |
| 1 | Weapons | 武器 |
| 2 | Armours & Clothes | 防具与衣物 |
| 3 | Containers | 容器 |
| 5 | Hides & Skins | 毛皮与皮张 |
| 6 | Tools | 工具 |
| 7 | Foods | 食物 |
| 8 | Timber | 木料 |
| 9 | Vehicles | 载具 |
| 10 | Valuables | 贵重物品 |
| 11 | Plants | 植物 |
| 12 | Carcasses | 尸体 |
| 13 | Miscellaneous | 杂项 |
| 14 | Textiles & Yarn | 织物与纱线 |
| 27 | Unpaid | 未付款 |

这可支持第一个语义 PoC：在列表分类标题的 UI 消费边界，以 `category_code` 直接生成中文，无须捕获最终英文。它是界面分类映射，不是完整对象类型枚举；当前分支中 4、15 至 26 走默认，不能据此给未确认值补造含义。

### 对象描述与名称构造

`0xC0190` 以 ECX 接受 handle，栈参数提供输出缓冲，输出固定 `0xAC` 字节，EAX 返回该缓冲。其无效 handle 分支会复制全局暂存区现有内容，因此“返回成功指针”不足以证明对象有效。

描述符的当前观察如下，字段名除已证实的分组用途外均保持临时命名：

| 偏移与宽度 | 静态行为 | 当前标识与限制 |
| --- | --- | --- |
| `+0x00` byte | 列表送入分类标题分支 | `category_code`，UI 分组含义可证 |
| `+0x04` DWORD | 与多种常量比较，参与描述及业务分支 | `code_04`，未证明为全局原型 ID |
| `+0x08` byte | 与类别共同选择描述路径 | `byte_08`，含义待定 |
| `+0x09` 字符串起点 | 作为 `%s` 内容参与构造 | `text_09`，基础显示文本候选；范围和终止约束待查 |
| `+0x31` 字符串起点 | 特定类别和格式位下使用 | `text_31`，另一名称候选；不预判为真名或未鉴定名 |
| `+0x59` byte | 与 1、0xFF 比较，影响路径 | `byte_59`，含义待定 |
| `+0x78` DWORD | 特定格式位下再次送入对象读取器 | `related_handle_78`，不预判为容器或内容 |
| `+0xA5` byte | 符号及低位影响形容词选择 | `packed_adjective_selector_A5`，尚不能直接命名为品质 |
| `+0xA6` byte | 影响文本组合路径 | `byte_A6`，含义待定 |
| `+0xA7` byte | 检视逻辑拆分高低 4 位 | `packed_nibbles_A7`，具体属性待查 |

`0x51770` 从 handle、第二整数和格式标志构造物品显示文本。第二整数大于 1 时改变词形，暂记 `quantity_like`；格式位的完整含义未确定。返回值来自共享环形文本池，不是可长期持有的对象内名称指针。保留原显示时必须在当前 UI 调用中立即复制，不能跨帧缓存其裸指针。

制作需求界面另有候选 `0x64730`，使用设备、材料及物品需求提示，记录步长为 `0x244`。该布局与物品 `0xAC` 描述符不同，不能直接复用同一个结构定义；可作为后续第二类 UI 适配器调查。

## 字体与绘制

### 点阵字体已得到文件和代码的交叉印证

`URW.FNT` 为 20,480 字节，所有字节取值为 0 或 1。按 `256 × 8 × 10` 解释时，ASCII 槽 65、97、48、122 分别能还原 A、a、0、z；样本点阵已保存在 [静态检查记录](evidence/local-inspection.json)。

选定代码进一步印证这一结构：

- 字体文件名字符串 RVA `0x1AC730` 在 RVA `0x117ADA` 被压栈，后续 RVA `0x117AFB` 的读取调用使用长度 `0x5000`，即 20,480 字节。
- RVA `0x10C06E` 从单字节字符索引出发，乘以 80，在字体缓冲区寻址；随后按 8 列、10 行处理像素。
- RVA `0x10E170` 的整串路径先复制 NUL 结尾原文到约 300 字节的栈内区域，再在 RVA `0x10E20C` 逐字节取字符，调用 `0x10DF80`，在 `0x10E224` 每字推进 8 像素。
- 更上层的 `0x10E260` 同样有局部字符串复制，并将单字节 `C4→8E`、`E4→84`、`F6→94` 重映射。这是西文原字节转点阵字码的证据，仍不足以确定所有来源的代码页。

**影响：UTF-8 中文的多个字节会被旧路径当作多个字符索引，且原表没有完整中文字形。** 即便译文指针有效，仍可能显示乱码、错误宽度或越界裁剪。不能通过扩充几个空闲点阵槽解决完整简体中文支持。

### SDL_ttf 不是已证实的原游戏文字入口

主程序普通导入表包含 SDL2、SDL2_image、SDL2_mixer、SDL2_net、MSVC 运行库等，没有 `SDL2_ttf.dll` 或 `TTF_*` 导入；独立使用 pefile 验证了导入和 IAT RVA，并且没有解析出延迟导入。

这一结果不排除动态加载或其他模块路径，但结合已有点阵代码，不能把 Hook `TTF_RenderUTF8_*` 作为默认入口。SDL_ttf 更适合作为 Mod 自己的中文渲染后端候选。

`SDL_RenderCopy` 的参数是 renderer、texture 及源/目标矩形，不包含原文指针。此层不能决定文本对应的 UI 字段或游戏对象；原生 UI 只在这里复制已经绘入的内容。不能由此推导出全局像素跟踪、保存文字位置或在复制时重放中文的方案；中文识别与即时绘字须接入已确认组件的读取和文字绘制调用。[SDL_RenderCopy 官方文档](https://wiki.libsdl.org/SDL2/SDL_RenderCopy)

## 绘制适配的静态线索

| RVA | 已观察到的静态行为 | 后续用途 |
| --- | --- | --- |
| `0x117ADA`、`0x117AFB` | 字体文件名入参、读取 0x5000 字节 | 跟踪字体加载和资源重建 |
| `0x10C040` | 8×10 点阵槽逐像素处理 | 理解旧字体缓存生成方式 |
| `0x10DF80` | 单字节字符索引、字体像素处理和 SDL renderer 调用 | 追踪 renderer 字符路径 |
| `0x10E260` | 整串复制、单字节重映射、偏移绘制后再画主文本 | 绘制适配 wrapper，不能凭此识别业务 UI |
| `0x10E3E0` | 保存及切换 render target，多次调用 `0x10E170` 后还原 | 绘制适配 wrapper，确认目标图层及样式 |
| `0x10E170` | 整串文字候选入口，逐字节交给字符路径 | 动态检查完整文本、坐标和宽度来源 |
| `0x10DDB0`、`0x10DE90` | 其他整串文字候选入口 | 检查软件表面路径及不同样式覆盖 |
| `0x10BD90`、`0x10BF20` | 上述入口调用的字符路径候选 | 分析颜色、位置及 surface 写入 |
| IAT `0x18C228` | `SDL_RenderCopy` | 最终纹理绘制 |
| IAT `0x18C204` | `SDL_UpperBlit` | 软件表面复制 |
| IAT `0x18C1E0` | `SDL_CreateTextureFromSurface` | 中文输出资源生命周期适配 |

这些地址只服务于定位。禁止在尚未确认 ABI 和指令边界时把它们直接作为生产 Hook 配置。`static-disassembly.txt` 左侧指令地址与相对跳转目标为 RVA；绝对寻址操作数仍是 PE 首选基址下的 VA，不能混为运行时地址。

现有证据指向至少两种文字实现：软件 surface 与 SDL renderer。需要逐场景确认是否仍走到这些入口，不能只验证主菜单后就承诺其他界面可用。

静态调用关系可整理为：

```text
0x10E260 → 0x10DE90 → 0x10BF20 → 0x10BE80 → SDL surface/texture
0x10E3E0 → 0x10E170 → 0x10DF80 → SDL_RenderDrawPoint / SDL_RenderCopy
0x10E5A0 附近 wrapper → 0x10DDB0 → 0x10BD90 → surface 像素
```

`0x10E260` 的静态参数候选为 ECX 指向 renderer、EDX 为 x，栈参数为 y、原文指针、颜色和 flags；调用方又负责栈清理。这是混合寄存器传参的逆向线索，不能直接声明成标准 `__fastcall`，也不能把相同签名套给其他候选函数。

约 300 字节区域不是安全复制上限：`0x10E170` 中先复制到 NUL，再搜索 LF 和检查首个 LF 的偏移，不能指望后面的检查保护前面的复制。`0x10E3E0` 的四次偏移绘制加一次正文还意味着低层采集可能把一个语义字符串记录五遍，应在 wrapper 层归并描边等重复调用。

## 显示文本与游戏语义的边界

原文名称可能参与游戏规则，汉化必须保护这一边界：

- `news.txt:113` 起说明，恢复暂停制作会按制作标题和成品名称做通配符匹配。
- `news.txt:552` 起说明，显示为 `Pine stake` 的对象原始名称仍为 `Wooden stake`，其他配方通过 `{Wooden stake}` 匹配；显示生成器还会替换 wood/wooden。
- `menudef_additional.txt:10` 及 `mod_menudef_example.txt:15` 附近说明了菜单命名、ASCII 快捷键和父菜单标记。

因此默认保留内部英文 ID、物品原型名称、配方匹配 token 和存档值；在显示边界形成中文视图。百科主题键、音效标记和菜单操作码也必须与译文分开管理。

配置中的 `[LOGICAL_RESIZE:YES]`、`[SCALE_QUALITY:2]`、`[OLD_HARDWARE_MODE:NO]`、`[RENDER_DRIVER:default]` 还意味着中文排版要适应逻辑坐标、窗口缩放和不同渲染路径。没有发现可直接切换字体或中文语言的配置项。

## 待动态验证的问题

| 问题 | 所需证据 |
| --- | --- |
| UI 的对象关联 | 背包行、handle、描述符及分类标题在同次显示中逐项对应 |
| 物品属性字段 | 多对象及跨 UI 的差分、读写位置与可见性；不凭偏移猜测材料或品质 |
| 共用 getter 的其他用途 | 是否服务配方、排序、交易和存档；只在显示消费边界建立中文视图 |
| 对象和历史事件寿命 | 句柄失效、地址复用、读档与事件后状态变化不会混淆显示 |
| 候选入口是否真实覆盖 UI | 菜单、消息、物品、百科各自的调用栈及传入原文 |
| ABI、寄存器和返回值 | x86 调用前后寄存器、栈平衡、返回值用途与反汇编数据流 |
| 原文编码 | 含西文扩展字符的原始字节、来源文件及实际显示结果；不预设 CP865、CP1252 或 UTF-8 |
| 整句存在于哪一层 | 格式化、标签展开、按行切分、固定缓冲复制的先后关系 |
| 指针是否被持有 | 同步消费、延迟绘制、复制与释放的实际生命周期 |
| 测量和交互区域如何形成 | 列宽、行高、换行、滚动、裁剪、热键与鼠标命中区域 |
| 两种绘制路径的实际使用 | 默认渲染、软件模式与不同 UI 类型的入口覆盖 |

## 复现与证据

使用 Python 3.9 以上运行只读脚本，输出路径必须位于游戏目录之外：

```powershell
python .\tools\inspect_game.py 'D:\program\steam\steamapps\common\UnRealWorld' --output .\docs\evidence\local-inspection.json
```

- [local-inspection.json](evidence/local-inspection.json)：模块哈希、PE 架构、普通导入、候选字节引用、字形样本及消息资源清单。字节匹配结果本身不等于反汇编或运行时调用。
- [static-disassembly.txt](evidence/static-disassembly.txt)：选定窗口的静态反汇编与独立导入验证说明。
- [ui-semantic-analysis.txt](evidence/ui-semantic-analysis.txt)：背包、列表、对象读取、检视和分类分支的静态指令证据。
- [ui-semantic-summary.json](evidence/ui-semantic-summary.json)：分类双层跳转表的索引、分支 RVA 和静态标题清单。
- [inspect_game.py](../tools/inspect_game.py)：标准库脚本，不加载或执行游戏代码。

公开资料用于确认产品和历史；适配必须以本机指纹为准。官网在本次分析日列出 2026 年 10 月 14 日发布的 3.89，而官方下载页的免费旧包是 3.71，不可用旧包偏移推定本机地址。[官网](https://www.unrealworld.fi/)、[官方下载页](https://www.unrealworld.fi/urw_downloads.html)
