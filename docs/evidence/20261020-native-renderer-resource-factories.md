# 原生 renderer 资源工厂及缓存消费生命周期

本记录来自原始 Windows `urw.exe` 静态反汇编与源码审读。没有运行游戏、产物、注入或测试。

## 文化图例

`E3A50` 是无参数完整资源工厂，普通直接调用点为 `117C01`。它创建原生 200×160 临时表面及局部软件 renderer，调用完整 `1166C0` 和十一处 `10E260`，最后生成真实 `5F8FA78` 纹理并释放临时表面、renderer。局部 EDI 不是长期 renderer owner。

`E3BE7` 读取旧 `5F8FA78`；`E3BF4` 原 `SDL_DestroyTexture` 释放旧纹理；`E3BFD` 清 owner；`E3C0E` 创建新纹理，`E3C15` 写入同 owner。因此统一失效调用完整原工厂时不会额外保留旧纹理。中性资源保留实际原生面板样式、调色板及面板颜色，文字资源与布局属于原工厂模板。

`native_culture_legend::Services` 只开启 `native_renderer_resource` 字形/度量准入，不强制设置整工厂 outline。每个原生 primitive 的本次 style 继续决定字形描边。Scene 语言失效顺序是先更新该全局资源，再物化依赖它的组件源。

## 已知区域地图

这是真实 `5F937B0` 目标，与 world creation 的 `605B0` 地图组件不是同一个 owner。`E3D90` 是完整、无参数的原生 UI 工厂，唯一普通直接调用为 `E5ACA`。`E3DCC` 调用原 `SDL_CreateTexture`，`E3DD2` 的七字节 `MOVAPS xmm0,[1DDAB0]` 是确认的成功返回边界；原五个调用参数仍在栈上。`E3DE8` 写入实际 owner，背景由原 `61BB64C` 静态资源提供。

原 `E3E22→113430` 用 ECX=texture、EDX=title，无栈参数。`E3E2C→162530` 读取 `KNOWN_AREAS_MAP` 的段落源。`E3E4D→10EFD0` 的 height=-1 路径只测量：`10F4EC` 跳过 draw，`10F565..10F58A` 返回高度。`E3E55` 把 EAX 交给 ESI，之后 `E3E71` 的 ESI+20 决定完整原面板高度，`E3EA3` 把同 ESI 交给第二段落。实现重新调用整个工厂，让这些依赖原样计算；不保存旧 ESI、旧译文位置或另建布局表。

中性 source 绑定原生标题资源、原帮助段落源、实际面板样式和动态颜色。普通构造准备标题后原 `113430` 消费同源；帮助记录由原文本构建器接受并成为该工厂的段落源。语言物化时，原帮助调用边界消费保存的中性段落，结束重新物化调用者仍持有的完整 canonical builder，不能以段落字段替换其 compose/count-zero 协议。

`E3EE0..E4041` 无参数、无业务/输入修改。它读取原两开关 `1EBCAC/1EBCAD`，将真实 `5F8FA80`、新 `5F8FA78` 复制到 `5F937B0`，并按原尺寸施加遮罩。普通调用只有 `E5ACF/E61F1/E6209`，后两处先由游戏修改开关。相同 owner 的中性版本保存这两个真实输入；重物化完整调用原 consumer，并恢复调用者开关。原生纹理退休还有 `E6587`/`E6596`，共同真实销毁接口负责通知 source 生命周期。

## HUD headingicons 依赖

原 `FB242→116E20` 是无参数完整复制资源工厂。它读取真实 `61BBAF4`，按原 literal `1AA3B8 = headingicons` 找到 `A3849F8 + index*0xC48` 的原生图片 record，释放旧 record texture，查询新 overlay 尺寸，创建、清空和复制到新 texture，写名字、说明及 mode=2，返回真实 record index。原 `FB250..FB279` 继续通过当前 HUD 全局输入维护 record 的原生矩形。`10B3C0` 后续消费的正是这个 record。

因此只重建 `61BBAF4` 不足以更新 headingicons。实现把完整 `116E20` 作为 overlay source 的实际依赖；普通原调用和语言物化消费同一个 overlay。原 `116EA3` owner 读边界仅在同步物化事务中借出被原函数实际选中的旧资源；完整原函数仍负责名字查找、record 分配和绘制。没有观察通用 `RenderCopy`，也不记录 `10B3C0` 的绘制调用。

`native_targets` 在实际 `116EF2` 创建返回点使用当前输出密度，保持该 record 的原生逻辑尺寸。此扩展不读取旧纹理内容。

## 缓存内真实 owner 的事务

原生软件缓存重建时，renderer 节点后面可能还有完整 Menu/Flow consumer。若单个 renderer paint 立即恢复旧 owner/alias，后续 consumer 会重新取到旧语言纹理。

`begin_native_cache_resources/end_native_cache_resources` 是同步原生资源借用生命周期。整段缓存 Scene 物化期间，新组件纹理、软件 HUD owner、headingicons record 及确认的 `5F4EB08/A1C1CBC` alias 保持安装；所有后续原生 consumer 都读取这些同源资源。结束按相反顺序恢复调用者 owner/alias 并释放临时资源。嵌套缓存各自持有一层事务。这里保存的是资源替换的同步所有权，不是像素、字形绘制贡献或延后重放列表。

中性 Scene/cache snapshot 持有组件版本与输入；输出纹理由原生 owner 构造/消费/退休。组件模型和状态不保存译文、glyph、UI 像素或最终绘制位置。
