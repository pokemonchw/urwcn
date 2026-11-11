# 已知区域地图图例与操作提示漏译

后续用户截图确认：本批次图例与缩放说明已显示中文，但按钮和帮助仍为英文，不能把下列 Applied 回执当作全部文本已正常消费的证明。原实现比较了已经由驻留 CALL 桥替换的父帧返回地址。后续修正及 HUD 回退处理见[地图调用作用域与 HUD 消费修正](20261110-map-scope-hud-consumers-fix.md)。

日期：2026-11-10（Asia/Shanghai）。用户截图的地图标题和文化名称已有中文，但右上地图标记图例、操作按钮、缩放说明和帮助段落仍为英文。此次只读截图、源码、原始 PE 与文本资源，按静态证据修改；没有启动、关闭、重启或模拟操作游戏，没有运行测试、创建测试用例或断言。兼容业务热发布使用已授权的驻留事务。

## 原生证据

对象为 Windows x86《不真实的世界》3.89.1 / Steam Build `26139145`，原 PE 为 `/home/lulika/.local/share/Steam/steamapps/common/UnRealWorld/urw.exe`，SHA-256 为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。下表均为 RVA；本地指令摘录见 `20261110-known-map-untranslated-native.asm`，按 PE 首选基址 `00400000` 显示 VA。

| 边界 | 原生语义 |
| --- | --- |
| `117BFC → E3020` | 初始化时完整构造地图标记图例；紧随其后的 `117C01 → E3A50` 构造文化图例，两个资源各有自己的工厂和 owner |
| `E304F / E3055` | 原 `SDL_CreateRGBSurface` 及返回点，原始目标为 `200×190`；`E3059` 为该表面创建软件 renderer |
| `E3084 → 1166C0` | 图例原生 Panel，栈参数3为 `MAP MARKER INDICATORS` |
| `E3132/E3207/E32D1/E339A/E346F/E351E/E35CD/E36FC/E3859/E38BE/E39E4 → 10E260` | 十一处完整文字调用，栈参数1依次为 You、Village、Cave、Shelter、Your settlement、Trap、Net、Marked location、Quest location、Quest related area、Ordered goods |
| `E39E9..E3A1A` | 读取并销毁旧 `5F8FA80` 纹理，使用完整表面创建并写入同一 owner；后续释放临时表面和软件 renderer |
| `E3D90 → E3E22 → 113430` | 完整已知区域地图工厂的标题消费边界；此后才在 `E5ACF → E3EE0` 中消费标记图例纹理 |
| `E3EE0..E4041` | 原地图合成函数读取 `5F8FA80` 与 `5F8FA78`，自行查询原逻辑尺寸、复制和遮罩 |
| `E5B75 → CF790` | 为当前地图完整构建新的原生 Menu |
| `E5D01/E5D23/E5D51/E5D73/E5D95/E5DB4 → CFD10` | 六个原生按钮，实际动作分别为 `M/A/Q/C/F3/ESC`；Q 按钮保留原条件分支 |
| `CFDF6 → 114D20` | CFD10 内部完整文字绘制调用；此处借用中文不会修改 CFD10 的英文输入和局部存储 |
| `CFEAA / CFECB` | CFD10 计算按键前缀宽度、完整按钮宽度；后续仍由原生指令写入实际命中区 |
| `CFF64/CFF65` | 每个新按钮完成后，由原函数增加真实 Menu count；本页上述不同动作均在新建 Menu 内依次追加 |
| `E5E00 → 10E260`、`E5E4A → 114D20` | 缩放说明与完整 CTRL 按键行 |
| `E3E2C → 162530`、`162627 → 162300` | 从 `gameinfo/urw_scrinfo.txt` 的 `KNOWN_AREAS_MAP` 读取并追加两条原始帮助记录；真实调用者返回地址为 `E3E31` |
| `D42B2..D42CD` | 原读取函数移除 CR/LF，保留第二条记录末尾原空格；资源键与该实际输入一致 |

原标记工厂只读取符号大小、当前原生配色等构造输入，写入自己的纹理 owner，没有输入等待或地图业务修改。它与地图窗口、标记开关和地图数据分别由原函数拥有。

## 修改与所有权

`windows_encyclopedia.inc` 将上述原生文本调用映射到 `culture.map.*` 资源，补入22条译文。表中仅包含原 CALL 身份和语义资源键，没有坐标、输出行槽、译文快照或绘制序列。新增 Hook 为 `79D5..79E0`、`79E8..79F0`，只对本次已确认的 3.89.1 注册，不更改既有编号、驻留 ABI 或交接格式。

按钮的外层 `CFD10` 输入、原生局部英文和 Menu 英文标签保持原值。仅在内部完整 `114D20` 绘制时，按真实 CFD10 父调用身份临时借用中文。`windows_renderer_text.inc` 在同一原帧的 `CFECB` 使用同一完整译文度量，只替换原 `strlen*8` 的宽度；ASCII 按键前缀沿用原单元宽度，后续原生指令继续计算并写入命中区。按钮完成后，将该真实新增 Menu 记录绑定到同一中性英文来源与语义键，供原选择框重绘消费；没有把新按钮加入历史 renderer children，也没有建立另一套布局或输入循环。

图例在 `E3D90` 的实际标题边界同步调用完整原 `E3020`，随后原地图合成消费新 owner。普通进入、当前原帧的语言唤醒及兼容热交接后的完整构造均经过同一边界，旧英文缓存由原工厂自身销毁；不保存或比较纹理像素，不通过 RenderCopy/上传/Present 延后重放文字。

`native_targets.cpp` 将已确认的 `E3055` 原生表面创建返回点接入既有目标密度扩展。原逻辑尺寸、符号与文本位置、Panel 和图例合成仍由原 UI 使用；字体在当次组件文字调用中按该软件 renderer 的真实比例光栅化并即时提交，随后由原生表面和纹理缓存管理结果。各调用继续使用原描边 style，未额外强制字重。

帮助按真实原始文件记录确定语义键，在原 `162300` 构造边界提供中文，并通过既有双字节传输、完整字形度量与原生 `10EFD0` 测量/绘制。面板高度依然由第一遍原测量的返回值驱动，原工厂负责换行、行距和实际背景。两条文件输入记录不代表两行显示，未存储输出行槽。

`catalog/zh-CN/cultures.tsv` 直接加入本次资源；其既有百科生成器保留全部 `culture.map.*` 键，因此不需要另建词库路径。地图业务、原开关值、标记数据、缩放动作、方向和选择输入均保持原语义。

## 既有待整改项

- `modules/adapter/native_renderer_component_binding.cpp:39` 的历史 Owner.children 及 `paint_hud` 遍历构造路径仍保留，影响原生缓存和页面重建所有权，完整退役待整改；本次仅在完整原工厂内重建其真实图例依赖，不增加 children 或独立组件重放。
- `modules/adapter/native_ui_scene.cpp:12` 起仍保留历史 Child/Container 集合及其序列化，完整退役待整改；本次地图沿现有 `native_hud_language.inc::map_result` 返回实际原帧的完整构造，不新增页面集合。
- `modules/adapter/native_footer_component.cpp:88` 起仍由 Mod 计算主菜单署名布局，影响原生布局所有权，待整改；本次不使用或扩展。

## 交付状态

源码与22条词库修改已保存，通过根统一队列完成一次配置、一次增量编译及正式兼容热发布。Adapter 重新编译并链接，Catalog 目标完成、DLL 内容未变。批次日志保留既有函数指针转换、部分初始化、extern 初始化、缩进和未使用项警告，无编译错误。提交后至所属批次完成未修改本次请求范围的源码；完整请求 JSON、359行批次日志及正式发布 JSON 均已读取。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `ac92da110d3b4a8184d55fb3798f8ee7` |
| 批次 ID | `814155b390b44cf3aae239521fef7dc2` |
| 请求结果 | `build/.compile-queue/results/ac92da110d3b4a8184d55fb3798f8ee7.json`，`Success=true` |
| 完整批次日志 | `build/.compile-queue/batches/814155b390b44cf3aae239521fef7dc2.log` |
| 正式事务 | `68dc45f3a59142b0a46496cc8a0ad96f`，2026-11-10 17:43:40（Asia/Shanghai）完成 |
| 正式发布结果 | `build/mingw-x86/stage/68dc45f3a59142b0a46496cc8a0ad96f/publication-result.json`，`success=true`、运行时 `applied=true` |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/cultures.tsv`、`package/release.json` |
| 旧件归档 | `回收/20261110-174338-68dc45f3a59142b0a46496cc8a0ad96f/package/`，三件旧正式文件先归档再替换，保留原相对路径，已只读确认存在 |
| 当前进程交接 | Windows PID `364` 返回 `ReadyToPublish`，随后 Catalog 第18代／Adapter 第20代 `Applied` |

| 文件 | SHA-256 |
| --- | --- |
| Adapter，构建件／正式件／Applied 一致 | `78635708256fbf23eadf5a6dcfbe04580e9028e70a83c65b42ee31e53b001dc2` |
| Catalog DLL，Applied | `cd5ea4f63e239691176f6bf1e38a1b4c232a0c9c5f8182eb80aacefbfa8e6719` |
| cultures.tsv，源码／正式件一致 | `a3718a942156d9518eb990f0230b4d810a758110b8b5863a47dfd2f1d49f0e2c` |

源码修改、产物编译、正式包发布和当前进程兼容交接均已完成。根 `urwcn_launcher.exe` 继续使用同一正式包，无平行运行副本。未启动或操作游戏，未运行测试、创建测试用例或断言；Applied 仅证明模块交接，画面由用户验收。
