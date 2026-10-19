# 2026-10-19 原生高清绘制链改造

用户要求保留高清，在完成原生链改造后再发布。本轮按该要求移除全局像素跟踪与文字记录重放；不交付 800×600 文字放大的降级方案。本文区分源码、编译、正式文件和运行时回执，运行效果仍须以用户反馈为准。

## 源码变化

- `modules/render/native_cache.h/.cpp` 已从活动源码移至 `回收/20261019-native-draw-rework/`；Render 不再订阅通用 SDL 事件，不再读取游戏像素、保存 Paint 或在上传、RenderCopy、Present 时重放文字。
- `modules/render/immediate_text.cpp` 在完整原生文字调用中按目标实际密度光栅化，直接混合到原生 Surface。原生四次描边和一次前景的调用、颜色与顺序保留。
- `modules/render/font_engine.cpp` 只缓存字体度量和相对字形原点的透明度覆盖图，不存 UI 位置、裁剪或顺序。字号从大到小校准，首个完整合格字号即为原规则所需的最大字号；不逐帧校准。
- `modules/adapter/native_targets.cpp` 扩展已有原生主面、上传纹理、背景缓存和按名背景槽；只登记资源身份与整数比例。图集及 BMP 导出工作面保留原坐标域，淡变临时面沿原生实际尺寸创建和释放。
- `modules/adapter/scoped_api.cpp` 转换本次 SDL 调用的矩形，在原生逻辑域完成裁剪并交回原生逻辑结果，随后由 SDL 复制已经绘入的像素。没有内容扫描或延后绘字。
- `modules/adapter/native_raster*.cpp` 接管已确认的整线、原生字形、单点及七个内联读写边界。原生像素格立即映射到实际目标；内联纯整数调用不进入 Host、FXSAVE 或记录系统，保留原有填色和渐变算法。
- `modules/adapter/module.cpp` 保留组件读取、编码和真实度量边界；在已确认主菜单构建或输入重绘边界迁移资源，窗口尺寸事件在原生重建后请求原生主菜单重绘。布局、命中、选择框仍由游戏管理。

静态资源和调用依据见 [高清目标边界](20261019-native-hd-target-boundaries.md)，旧 Hook 退役见 [ABI 1 交接记录](20261019-abi1-hook-retirement.md)，跨代函数别名见 [稳定入口记录](20261019-native-target-stable-gateways.md)。读色使用对应逻辑像素格的精确中心，依据见 [采样记录](20261019-native-raster-sampling-static.txt)。原始错误方案的文档出处见 [文档纠正记录](20261019-document-render-policy.md)。

## 已知范围

本轮汉化范围仍为主菜单七项、条件项额外内容、版本及出品/版权/作者/网站段落。没有把历史关于、设置、先祖等实现算作本轮完成。

原生高清资源的扩展覆盖本轮静态确认的消费链；这不是对所有未解析间接别名的形式化证明。宿主此前已有的错误透传和事务失败语义仍按 [实现纠正记录](20261019-implementation-correction.md) 单独保留待整改状态，本轮不修改驻留 DLL 或宣称已解决。

## 交付状态

- 源码：原生绘制链与稳定入口交接已接入。
- 编译：统一入口 `build.ps1 -Module render,adapter` 已成功。请求 `467214b0b1e04abdaf9682382bcc6b4a`，批次 `7e0bc794bb724f2f93e2ffa4e5867bf4`；已读取请求 JSON 与批次日志。首批请求 `e5b4e53150ac42b28ca1054533155a8c` / 批次 `a29f7468c83c4ef593dc5297dab45a93` 因工具链不接受函数 target 属性 `soft-float` 失败，移除该属性参数后通过。保留 no-sse/no-sse2/no-mmx；不触及浮点状态还须以编译后指令核查为依据。日志中的 FARPROC 到已确认 SDL/TTF cdecl 导出类型转换警告不影响本次编译结果。
- 编译后静态核查：11 个 naked 入口、11 个 helper、4 个内核及其可达 `__divdi3` / `__udivdi3` 未发现 FP/SIMD/FXSAVE；七个 inline helper 不调用 SDL 或 Host。原生寄存器、标志与栈重放核查见 [机器码审查](native-raster-compiled-review-7e0bc794.txt)。Adapter SHA-256 为 `9266c55edb1ed8832995150b64688c2af96f7ab7666d54d20cc8d97d28fb6753`，Render 为 `b231c7117a2fbf6d418ce9e6f971214421163e0e3af8dd8e07dc127dc568d68f`。
- 正式发布：请求 `ff526bd50ade44beb663eaa92ca314ad` / 批次 `3eb7fe79e79d400e903a55595b2291c2` 完成，事务 `70e97bed31a04ea1a4096ae67ebfa897`。已读取队列 JSON、批次日志与 `build/mingw-x86/stage/70e97bed31a04ea1a4096ae67ebfa897/publication-result.json`。正式 `package/modules/uwcn_adapter.dll`、`uwcn_render.dll` 及 `package/release.json` 已替换；旧三文件先按相对路径移入 `回收/20261019-021416-70e97bed31a04ea1a4096ae67ebfa897/`。正式清单十个文件的 SHA-256 均与磁盘匹配。根启动器和驻留 DLL 沿用原文件，不存在备用运行目录。
- 运行时应用：首次热发布在旧模块退役前崩溃，随后游戏进程已不存在；最终正式发布没有请求 Reload，因此没有 Applied 回执。没有自行重启或运行新产物。
- 运行：没有启动游戏、注入、模拟输入、运行产物或测试，没有创建测试用例或断言；不提供未经测量的帧率或响应时间结论。

## 首次热发布中断

请求 `6850be278210403b9894d03df9d18513` / 批次 `9414bd8644bc499a93fb4ad9540e62f3` 使用 `-Publish -Reload -TargetPid 119880`。编译成功，但事务 `618b6f806617492d93322a6c7fa3f0f7` 在旧模块 Prepare 阶段退出，未取得 ReadyToPublish。原正式清单和 DLL 哈希未改变，也尚未创建所列归档目录；新的 Adapter/Render 没有载入该进程。没有 Applied 回执。

系统事件记录旧 `uwcn_render.dll` 在 RVA `4FB58` 发生 `C000001D`，该地址属于 `__gnu_cxx::__trap_terminate_handler()`；现有转储为 `C:/Users/WIN11/AppData/Local/CrashDumps/urw.exe.119880.dmp`。转储中异常类型为 `std::bad_alloc`，已还原旧模块 `save_state(+6028) → NativeCache::save(+FC28) → Resource 序列化(+8D2C) → vector<uint8_t> 扩容 → operator new(+4E67C) → __cxa_throw(+4EF39) → terminate → UD2(+4FB58)`。Host 返回点 `+14F6D` 是第二次、非空输出缓冲区的状态保存。这次热交接触发了旧文字/像素记录序列化的分配失败；不是新绘制桥执行。新 Render 已移除 NativeCache，`save_state` 返回零字节，既不保存也不重建该绘制历史。

发布脚本原 `StreamWriter.Dispose()` 再次 flush 已断开的管道，将无回执错误掩盖为 Dispose 错误。已改为直接写入完整 UTF-8 命令后读取回执，不重复 flush；未添加重试、回退或重新启动操作。错误消息也不再声称尚未创建的目录中已有归档文件。

转储中的旧 `saved` 已有 135,626,353 字节（约129 MiB），Host 的输出 state 又分配同样大小。第二次序列化临时 writer 已写入117,784,999字节，再追加333,696字节 bitmap 时申请235,569,998字节（约225 MiB）新块失败。旧 `save_state` 在 sizing 和实际保存两次调用中都会执行 `cache->save()`，这是本次分配失败的具体调用背景；详细只读证据见 [Prepare 崩溃分析](20261019-prepare-crash-analysis.md)。
