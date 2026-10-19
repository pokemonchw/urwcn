# Linux 进度同步 Windows

日期：2026-10-19（Asia/Shanghai）。同步基线为 `origin/main` 的 `70fcd90`；Windows 工作区原本已经快进取得该提交，但正式 Windows 模块仍停留在移植前版本。本轮将 Linux 已接入功能映射到 Windows x86 的原生显示接口。目标 PE SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`，地址均为 RVA。

仅进行了源码、PE、原始数据与反编译结果的静态分析。没有启动游戏、注入游戏、模拟输入、运行产物、执行或编写测试、添加断言。正式发布若使用现有驻留桥，只执行已经授权的兼容业务模块事务；发布回执不代表视觉或输入结果已经验收。

## 已同步源码

| 范围 | Windows 接入和共享内容 |
| --- | --- |
| 中文姓名 | `native_name_input.inc` 接入 `119AB → 10F5B0`，保留原12字节容量、姓名字段、输入动作与 Windows `StrUnicode` ASCII目录约定；完整字符退格、系统输入法及原生光标。详见[姓名记录](20261019-windows-chinese-input.md)。 |
| 季节、肖像、属性 | `windows_profile_extras.inc` 的 `FA40` 季节显示、`125F0` 肖像帮助及 `E66B0` 属性构建。原选择、随机数、文化值和属性值不变。 |
| 百科、文化、图例 | `windows_encyclopedia.inc` 使用同一 GAME.NFO 的主题、文件记录和链接身份，中文进入原 `link_show/Lisaa_Linkit`、简介及两套图例显示调用；原关键词与导航动作保留。 |
| 技能 | `windows_skills_spells.inc` 的 `E06A7 → CFAF0` 名称、`E0523 → 10D0` 熟练度、`11E2C/11E54` 点数限制、`E0CA4` 帮助及 `121F5..12239` 确认列表。原升级、降级、熟练度阈值和 Y/N 值不变。 |
| 法术 | 原 `DF960` 页面、`DFC20` 当前描述、`DFF85/DFFEC → CFD10` 原生列表。25项名称与描述、三类帮助、标题和百科说明使用共享词库；原法术ID与施行动作保留。 |
| 世界与开局 | 随机世界12项、情境选择29项、13个情境标题及199条故事、确认问题与按钮、游戏进程20项，均为 Windows 独立反编译确认的调用。详见[开局流程记录](20261019-windows-creation-sync-native.md)。 |
| 告别页 | 原 `E6E90` 内11项标题、谚语、献辞、底部文字与继续按钮；原淡入淡出和退出流程不变。 |

原生排版、居中、折行、行距、按钮背景、选择、命中与缓存仍由游戏管理。新增中文段落分词只为原词表提供完整编码单元，由 `10EB40/10EFD0` 决定每一次折行；原追加的西文分词空格不绘入中文单元。完整字符串度量与最终字形使用同一当次原生目标。详见[renderer度量记录](20261019-windows-renderer-text.md)。

## 原生密度与主菜单重建

`native_targets.cpp` 在已确认创建调用中扩展以下目标的物理密度：`DF995` 的法术页面、`DFC7B` 的当前法术说明、`E3A6F` 的200×160文化图例软件面及 `E3DD2` 的地图主目标。原始逻辑尺寸取自该次原生参数；实际物理尺寸使用既有原生画布输出密度。原 `CreateSoftwareRenderer` 和 `SetRenderTarget` 接口为这些已登记目标设置相应密度，`QueryTexture` 继续向原生控件返回逻辑尺寸，源裁剪矩形沿既有接口转换。

元数据只含原生资源身份、逻辑/物理尺寸和生命周期，不读取或保存UI像素、中文页面或绘制贡献序列。字形在原生组件文字调用中即时绘入，原生UI持有结果及其缓存。`NGT1` 状态格式不变，稳定跳板由10项扩展为13项；208字节仍位于旧 `VirtualAlloc` 分配的同一原生页内，原有10个跳板偏移保持。

静态审查确认原 `modules/adapter/module.cpp` 的 `redraw_menu()` 只执行 `125BA3..125BE1` 的页脚、面板和菜单绘制，没有先重建原背景，旧文字会进入新缓存；该既有实现不能视为符合完整原生重建要求。本轮已整改：先同步执行栈平衡的 `125AA6..125AF5` 原背景与原生纹理缓存退役片段，再执行原页脚/面板/菜单片段，最后复制原菜单缓存和绘制当前选择。`windows_menu_redraw.inc` 仅在此同步重绘期间跳过四处启动业务赋值，正常启动指令保留。About/Credits 沿原有主菜单重建及原页面保存接口更新后方缓存。

新增共享姓名显示编码不改变持久业务数据。原 `10E5A0/10E260/10E3E0` 在自己的副本内转换UTF-8，完整字形和光标度量在对应文字边界处理；`F9030` 的姓名居中同样消费完整字符宽度。HDA4 在已发布 HDA3 的五个整数后追加姓名输入两个整数；Windows Host ABI仍为1。

## 保留边界

告别页已绘制画面的纯刷新入口仍未确认，不能为了切换语言重入带音乐、淡入淡出、等待和退出的整个函数。属性、姓名后方旧面板等页面的纯刷新范围依照各自证据，未补造业务重放；这一限制也存在于已同步的 Linux 进度。Linux 的 Unix socket、ELF启动器和专用音频边界属于该平台实现，Windows 使用现有已确认的启动器、命名管道与驻留桥。

旧正式文件必须先按事务移入根 `回收/`，再更新 `package/`；不创建平行修复包，不更换启动路径。

## 编译与正式发布

首批请求 `140b29ca6f8549ce9dab4d6e412bc326`、批次 `d6810888213746c7a31984d53ae3deca` 因百科标签的 const 指针类型不一致而编译失败，未进入发布；已修正。

第二批请求 `8432b528fc8540508205d1111dc7a17a`、批次 `cfd4a7e3a0274fca8deffcbcb4a718ca` 六业务模块编译完成。事务 `a4775670fb314eaba80de5e14da6d2d1` 返回 ReadyToPublish，旧文件先移入 `回收/20261019-203445-a4775670fb314eaba80de5e14da6d2d1/`，正式文件已替换；COMMIT 返回 Adapter initialization failed，未获得 Applied。已读取请求结果、完整批次日志和 publication-result.json。

对此失败的静态复核确认：`windows_creation.inc` 把已有 `F2E5 → 10EB40` 又以新ID注册，而驻留桥保存着原 `shared_footer_paragraph` ID；新ID校验会把原 E8 字节与已安装的旧桥指令比较并失败。本轮已移除重复注册，改在已确认 `10B6F/110B0 → F210` 建立页脚作用域，复用原F2E5桥。百科新等待桥的返回地址识别同时改为原生等待作用域，保留更新前已打开页的原返回地址识别。

第三批请求 `ea62d212a94a4181a241afb82e094538`、批次 `df05eaadf99743b8b96e071b871a38c3` 修正后编译成功，但事务 `4c6c9d29ad58485698e26cc67d4f2349` 的 PREPARE 返回 transaction state mismatch，尚未替换文件。静态原因是旧驻留层 `src/loader/host.cpp::control_thread` 只接受 idle/applied/cancelled，初始化失败后的 failed 状态不能再进入事务。该旧进程没有驻留层自更新入口，不能宣称能够原位恢复；本次没有注入补丁或关闭游戏。

本轮源码将真实失败分支纳入下一次 PREPARE 的允许状态，沿用原状态保存、退役和提交实现；没有新增回退。`publish.ps1` 同步 Linux 已有的显式 Reload 选择语义：重试时按明确请求的业务模块集合交接，不能仅根据磁盘哈希变更缩小集合，也不能因磁盘文件相同跳过已请求的 Reload。

第四批请求 `f6f25cd6548b4b0da05da537a8d32ed2`、批次 `12193699f9914e95bda09b9c919aff53`，正式发布事务 `7d2d56104040426eb232d15e679fb06d` 成功，把修正后的 Adapter 更新到正式位置；旧 Adapter 及清单先归档至 `回收/20261019-204049-7d2d56104040426eb232d15e679fb06d/`。这次明确不请求热加载。

驻留层修正先通过独立的仅编译请求 `8abd405b039e4792b6d3d0d30fc5be72`、批次 `d0a31f6ef36b44519cafe8199720820f` 生成产物，彼时没有把构建目录产物冒充正式发布。

用户随后明确告知“已关闭”。只读进程身份确认 PID 65832 已退出后，通过统一队列执行最终正式发布：

- 请求 `c07aa98d9adc4c278f14ab4c8a0d6fea`；批次 `bd846ae1a64241938b2c3ce6c3761601`。
- 事务 `696047838c75427b85d0abd25aea02f3`，`Success=true`、`PublishRequested=true`、`ReloadRequested=false`；已读取对应请求结果、完整批次日志和 `publication-result.json`，发布 `success=true`。
- 本批次确认六业务模块及驻留库均为最新构建产物，并更新正式 `package/uwcn_loader.dll`、`package/release.json`。旧两件先移入 `回收/20261019-204113-696047838c75427b85d0abd25aea02f3/`，保留原相对路径。
- 最终驻留库 SHA-256：`5435d04443eb4884d04cf8e6dec4d18e69dfc931c0e2023db8dca693f85f89b5`；Adapter：`decbfab96979a0df64ab788c363f4fb2beb8a985d66700ed86b8e302f306d02b`。
- Catalog：`d628893d4582eb8419cb1379ffcc9ef2419392ac2a24a8b919c0de73071cee44`；Semantic：`c343e6bc82382666e615338481cdfb10750830e72e41c5fccf545a08985ea482`；Main menu：`1a0c92855e4ca0a7d77e6fef411da8a5028a921a8ba0de705c796bcd4e0b0ce5`。
- 中文主词库：`5fe18b13641ea0d838fdc941f998d51f14654110e02be147b6649bf5d4c9bf27`；百科词库：`740fb9747ae06bb8f80d7b10a0a11eedbb7018947de94d97652a654aaa24b86b`；Windows profile：`baeff94016aa0859d55dd066b697e67b9df55d9b5f60008e7f464772284be38c`。

编译保留既有的 Windows `GetProcAddress` 函数类型转换及 Semantic 动态组件 switch 警告；最终发布批次没有编译错误。源码同步、产物编译和正式文件发布均已完成；正式启动路径仍为根 `uwcn_launcher.exe` 与相邻 `package/`。没有平行修复包。用户关闭进程后没有请求或声称 Applied，亦未自行重新启动或测试；下一次正常启动才会加载最终正式文件。
