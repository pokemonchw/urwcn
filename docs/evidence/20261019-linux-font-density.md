# Linux 字体模糊：原生目标输出密度修正

日期：2026-10-19。用户提供主菜单截图并反馈“字体极其的糊”。遵循根 AGENTS.md：只读取源码、原 ELF 和本次产物做静态分析，编译用于交付；没有启动游戏、执行产物、注入进程、模拟操作、运行或编写测试、添加断言。

## 原因与原实现状态

原 Linux 移植的 `src/linux/adapter.cpp::glyph_request` 指向 native `screen`，但没有扩展 `initgr` 创建的 800×600 软件面及其上传纹理。`modules/render/module.cpp` 从这个 surface 的实际尺寸计算字形密度，因此中文字形先以 1× 光栅绘入；`RenderDoScreen` 随后上传整张画面并放大至输出。低分辨率笔画已经丢失，改变最终采样过滤不能补回细节。

原 [Linux 移植记录](20261019-linux-native-port.md) 已将这一项列为待整改。本次不能把原先编译、发布成功当作字体质量已经合格，也不能套用 Windows 的高清/DPI 交付结论。

## ELF 静态边界

目标为本机 Steam `urw3-bin`，ELF64 PIE，SHA256 `4bbbef363fe64678ae9674ff9330f3cb0bec813d94379483813de152c164aabe`。下表是该 ELF 的 RVA，来源为本地 `build/analysis/linux-x86_64.asm`、符号表和分段 `objdump`，不是 Windows RVA。

| 原生调用/所有者 | RVA | 已确认关系 |
| --- | --- | --- |
| `initgr` 主 renderer / 可选 logical size | `148AB3`、`148B26` / `148EE3` | renderer 创建后、主纹理创建前完成原生输出配置 |
| 主上传纹理 / `screen` 创建 | `148C2D` / `148C60` | 原参数为逻辑画布尺寸；扩展二者的实际像素密度 |
| BufSurface、SCREENSAVE、SCREENBUFFY、GAMESAVE 创建返回点 | `13BACF`、`13BB81`、`13BBD8`、`13BC2F` | 与 `screen` 同一逻辑画布，转换格式后仍由原生全局所有者持有 |
| MENUBUFFER 创建返回点 | `13BECA` | 原生列表保存/恢复选择区域的像素缓存 |
| named grabsurface 创建返回点 | `13C114` | 原生 799×600 缓存，使用主画布比例；`grabname` 非空标识四个槽中的存活所有者 |
| HeadingBoxSurface / HeadingBoxSoftRen | `13BDBA` / `13BE1C` 附近 | 尺寸来自 headingGui；软件 renderer 必须随其真实 surface 密度设置比例 |
| fade 临时面创建返回点 | `13CF53`、`13D165` | 尺寸已从输入 `screen->w/h` 取得，只登记比例，不再次乘密度；复制均使用 NULL 源/目标矩形 |
| `RenderDoScreen` | `13A250` | 从 `screen` 读取实际 pitch、pixels，NULL 区域上传至主纹理，再由原生 RenderCopy 完整提交 |
| `FlipSurface` / `FlipScreenPortion` | `13A8F0` / `13AA90` | 前者消费实际 pixels/pitch；后者的逻辑源裁剪在本次调用转换为物理源裁剪 |
| `putpix` / `getpix` | `13AF40` / `13B190` | 已确认主画布直接读写；原边界拒绝、打包颜色和 lock 语义保留 |
| `putasc` / `draw_line` | `13B6C0` / `143C20` | 原 8×10 mask 与整数整线运算；立即写入对应物理像素格，不记录写入历史 |

`fontsurface`、`tmpCharSurf`、PELIGRAFIIKKA、HorBoxSurface、地图及图片素材保留原像素域。通用 `surface_putpix/getpix` 的已检查调用用于这些素材或临时字形，不替换成主画布操作。字体服务自身的 SDL 调用仍指向真实库导出。

## 源码修改与所有权

- 新增 `src/linux/native_targets.cpp/.h`，仅扩展游戏 ELF 中已确认 SDL PLT 调用及四个 native raster 函数。PLT 保留 ENDBR64，替换其七字节 BND JMP；没有修改 SDL 库代码。资源元数据只保存 surface/texture 身份、比例和 texture 所属 renderer，不含文字、UI 位置、裁剪历史或像素内容。
- 复用 `modules/adapter/scoped_api.cpp` 的调用内矩形转换、原生逻辑裁剪和 SDL 像素复制。字体绘制绕过游戏 PLT 的逻辑矩形转换，直接以字形光栅尺寸提交到真实目标。既有像素缓存仍由原生调用创建、覆盖和释放。
- 复用 `modules/adapter/native_raster.cpp` 的整数像素格、原 mask 和整线规则。`getpix` 只执行原生调用要求的单点取样，不扫描、比较或跟踪游戏画面。
- `src/linux/adapter.cpp::glyph_request` 采用原生 10 高约束和 9 高墨迹上限。度量与绘制消费同一实际目标密度；主画布密度变化时清掉传输字形的旧宽度，随后由原生 UI 重新消费字体度量。公共字体缓存有既有容量限制，不保存 UI 位置。
- `cmake/linux.cmake` 将这些实现和 `src/linux/redraw.S` 纳入同一 Adapter 模块，无新运行目录或独立修复包。

原生 800×600 保持最低光栅域：输出更大时使用实际输出密度；输出更小时，游戏继续缩小这一原生画布。未更改游戏设置、逻辑坐标、命中区或输入映射。

## 本机 SDL2-compat 密度来源

本机 `/usr/lib/pkgconfig/sdl2.pc` 和库路径确认使用 **sdl2-compat 2.32.72 / SDL 3.4.16**。不能照搬 Windows SDL2 的临时 SetScale/GetViewport/恢复 GetScale 过程：兼容层 GetScale 包含 logical presentation 比例，但 SetScale 只设置 user scale，直接恢复会叠乘。

此处在已确认的窗口目标边界只读取状态：有原生 logical size 时，读取 GetScale 并与逻辑尺寸相乘，取得输出内容区；否则读取 GetRendererOutputSize。原生 initgr 未设置额外 user scale，主菜单输出路径的目标为窗口。没有修改原生 logical size、viewport、clip 或输入缩放。

依据为锁定版本的官方源码：[sdl2-compat 2.32.72 的 RenderGetScale / RenderSetLogicalSize](https://github.com/libsdl-org/sdl2-compat/blob/release-2.32.72/src/sdl2_compat.c)、[兼容层导出映射](https://github.com/libsdl-org/sdl2-compat/blob/release-2.32.72/src/sdl3_syms.h) 和 [SDL 3.4.16 的 logical presentation 实现](https://github.com/libsdl-org/SDL/blob/release-3.4.16/src/render/SDL_render.c)。

## 主菜单缩放后的原生重建

原生窗口事件在 `key_event+0x3E`（`F6D9E`）调用 `CreateMapMainTexture`。保留这一原调用，仅在主菜单的 `LIST_Go → getkey` 作用域更新上述原生所有者。此时原生输入栈保留选择状态，没有借用这些 surface 的 pixels。

密度变化后，将旧所有者位图转移到相应的新原生面，保持 blend、alpha、RGB modulation、color key、RLE 属性；更换主上传纹理，并随 HeadingBoxSoftRen 重建其两个原生持久图标纹理。图标文件名和 color key 规则来自 `lataa_gui` 的 `1461C3..146295`，未引入字体或图片回退路径。

随后执行 `UrW_Start` 已确认的纯背景/页脚片段 `15CEEB..15CF44`：原生 winW/winH、bestfitPic 七参数、small_info；结束处在重绘状态返回，不进入后续文件检查、日志、音乐和业务。`redraw.S` 保留 RBX，按原片段内部 CALL 所需的栈对齐进入，参数和页面坐标仍由原片段构建。

原生 `peli_info → LIST_Draw → save_menubuf → 当前选择 → Flip` 重新生成菜单和文字。本次没有保存一份中文页面，也没有在 RenderCopy/Present 时重新绘字。位图转移本身不产生高清文字；高清字形来自随后原生文字调用的重新光栅化。

## 尚待整改与适用范围

| 文件/位置 | 影响和状态 |
| --- | --- |
| `src/linux/adapter.cpp::resize_native_targets` | 完整缩放重建目前只确认主菜单。其他当前页面保持上一次建立的画布密度，直到下一次主菜单边界；不宣称任意页面缩放均完成高清重建。待继续确认各页生命周期。 |
| `src/linux/native_targets.cpp::replace_surface` | 非当前重建页面的旧缓存只转移已有位图，文字须等该页面原生重建才按新密度生成。禁止把旧像素放大称为重新生成的高清字形。 |
| `src/linux/adapter.cpp::glyph_request` 与 native `showtext` | 原生四次偏移描边和前景调用均保留，但描边预算尚未传入字体校准及外部宽度调用，完整 10 高样式包络尚未完成接入。此项待整改，不能把本次密度修正视为字体规范全部完成。 |
| Linux 驻留/发布协议 | 仍没有运行中退役与重新加载协议，不能使用 Windows Reload 或宣称旧进程已应用。 |

## 编译、静态产物检查与正式发布

编译统一执行根入口：`.toolchains/powershell/pwsh -NoProfile -File ./build.ps1 -Toolchain Linux -Module adapter`。

- 请求 `180e4fe73b374615a79e1e42c1f48e7d`，批次 `690b694174134cad8056113293240dd8`。
- 已读取该请求结果 JSON 和完整批次日志：`Success=true`，`PublishRequested=false`，一次配置、一次增量构建，无编译警告。此批次没有修改正式交付文件。
- 对生成的 ELF 静态读取 `nm/readelf/objdump`：确认创建函数仍从调用者返回地址识别原生创建点；重绘汇编具有预期的 RBX 保存和栈对齐；整数 raster 片段没有 FP/SIMD 指令。没有加载或执行这个 ELF。

2026-10-19 11:25:27（Asia/Shanghai），根入口追加 `-Publish` 完成正式发布：

- 请求 `e2b3e92899af420780c5e5c2936bb7bb`，批次 `3db9387e76884db7aa457f3eb65b1700`，发布事务 `ea183e2e62c94045ab2a32f24243e63c`。
- 已读取请求结果 JSON、完整批次日志和 `build/linux-x86_64/stage/ea183e2e62c94045ab2a32f24243e63c/publication-result.json`；编译与正式发布均成功。本批次一次配置、一次增量构建，复用上一批次已编译的 Adapter 产物。
- 正式替换 `package/modules/uwcn_adapter.dll`、Linux profile 和 `package/release.json`。旧三件先移入 `回收/20261019-112527-ea183e2e62c94045ab2a32f24243e63c/package/`，保留相对路径；应用菜单旧链接也随发布脚本归档。
- 正式 Adapter SHA256 为 `d8658b96afc7d3c48a91a55d1b6c5b5e172c9ad5c0fb9e7cca70cbb3138bf60d`，与构建产物和正式清单一致。正式 profile SHA256 为 `2e4446cd04e35705fc5832d9dd8be52106799e6616adf3e6fa0ee8d816b1fe4f`，与源码 profile 和清单一致。
- 归档旧 Adapter SHA256 为 `15220fa8c0b766fe860709d8ab3817769281f576f9731258bcc4ff2dfc4c9139`，旧件未覆盖或删除。根入口仍为 `uwcn_launcher`，未建立平行运行副本。
- 发布前只读进程列表未发现 `urw3-bin` 或 `uwcn_launcher`。本次没有请求 Reload，没有运行时 Applied 回执；Linux 尚不具备原位热更新协议。正常启动会从正式位置加载本次文件。

源码修改、产物编译和正式文件发布均已完成。没有自行运行或测试，不宣称已经视觉验收；上节剩余边界继续保持待整改状态。
