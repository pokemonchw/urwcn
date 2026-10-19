# Windows 百科正文与链接的词元度量修正

日期：2026-10-19（Asia/Shanghai）。依据用户提供的“文化”页截图，对 Windows x86《不真实的世界》3.89 / Steam Build 25939378 进行静态分析。用户图中的蓝色链接与黑色正文错位，选择框随链接位置偏移。本文原生地址均为 RVA；完整 PE 指令见本机 `build/windows-sync-pe.asm`，反编译见 `build/windows-sync-profile-encyclopedia.c`。

## 已确认原因与原生边界

- 原生 `3D93A → 162300` 生成词表，`3DBA1 → 10E5A0` 每次绘制一个词元。中文编码扩展把每个完整双字节字符作为一个原生词元，英文主题别名作为完整词元。`10E700..10E70E` 在每次文字调用末尾推进并保存原生光标 `A1C1CB4`。
- `modules/render/font_engine.cpp:318–320` 对每次字宽执行 `lround(physical_width / density_x)`。因此逐词元推进是各词元逻辑宽度之和。
- 修改前 `modules/adapter/windows_encyclopedia.inc:121–124` 的 `windows_culture_width()` 先去掉词元分隔，再合并测量。原生 `3D5FB..3D600` 将这一整串取整的前缀宽度写回光标，随后 `3D78D` 绘制蓝色链接。它与先前逐词元绘制的正文使用了不同的取整粒度，累计差值造成叠字和位置偏移；相同问题影响试排。
- 原生 `3D591` 为链接试排，`3D5FB` 为链接前缀，`3D6AE` 为原生选择框宽度，`3D728` 为下划线终点。既有钩子的寄存器和栈缓冲与 PE 指令一致，问题在宽度计算的消费单位。
- 修改前同文件 `we_space_copy` 的 `3DC2C → 3DC3B` 跳转取消了原生行缓冲的分隔写入；通用 `native_paragraph_words()` 又保留源中已有空格，与链接两端插入的空格叠加。`162488..1624D9` 明确将连续空格的非末空格留在词元内，不能用删掉全部分隔后的整串推导原生消费单位。

## 本次源码修正

`windows_encyclopedia_tokens()` 仅向原生词表提供完整字符和主题别名，并将用于分词的空格规范成单个分隔。`we_space_copy` 保留原 hook 身份，恢复 `3DC2C..3DC38` 对 ASCII 词元之后的原生分隔写入，包括相邻链接别名；双字节中文词元自身已经携带完整边界，继续不向行缓冲额外写入分隔。`we_space_text` 继续取消分词空白的可见绘制。

原生 `16240F..162436` 在 `>` 已结束控制词元并推进词表，因此 `>` 后不再插入分词空格，也去掉此处由链接括号转换生成的分词空格。这样避免 `16248F..16249A` 再次推进产生空词元；`3D9B6` 对空词元会直接结束本次正文调用。控制标记仍由原生处理。

这一边界区分来自实际原生存储：`3D540..3D553` 先将本次行串复制到200字节的前缀局部，再截取链接之前的内容。已有180字节源分片不能容纳逐汉字再向这个缓冲增加一个分隔字节的膨胀。按完整双字节识别中文边界，不建立另一条按宽度断行或容量兜底路径。

`windows_culture_width()` 按原生行缓冲中的完整双字节字符、ASCII 分隔和完整别名识别相同词元，分别消费现有字体度量，再累计每次已经取整的逻辑推进。完整主题名优先按同一完整中文标签测量，包括原英文名内部有空格的主题；不会把链接标签再次拆字。正文、两词试排、链接前缀、原生选择框和下划线消费同一度量单位。

没有建立坐标表、行槽、页面快照、独立排版、像素跟踪或重放记录。原生 UI 继续决定换行、行距、光标、链接身份、选择和鼠标区域，字形在既有原生文字调用内即时绘入。Host ABI 1、HDA4 状态格式及英文主题业务数据保持原义。

## 审查更正与保留边界

- `docs/evidence/20261019-windows-profile-encyclopedia-sync.md` 的“完整百科与文化简介”原称 `3D591/3D5FB/3D6AE` 已同步真实宽度，却遗漏了逐词元与合串取整差异；其 `3DC13/3DC2C` 同时取消可见空白及缓冲分隔的描述不能作为正确分词依据。该旧实现曾编译及发布，不代表符合完整原生文本消费要求。本次 Windows 源码已整改，交付状态单独记录如下。
- 静态审查同时发现 `src/linux/culture_info.inc` 的 `culture_link_width()` 仍对 `culture_display_words()` 合并后的前缀调用 `width()`，存在相同消费单位不一致；该 Linux 路径本次未修改、未编译、未发布，状态为待整改，不能因先前发布记录视为合规。
- 既有已打开百科页的刷新沿原输入返回边界执行原生重建，关键词编辑期间等原编辑返回后重建。热发布 Applied 只说明业务交接，不能证明页面像素已刷新或视觉效果通过验收。

未启动游戏、注入运行中的游戏、模拟输入、执行或编写测试、运行产物、添加断言或推测性的保护／回退／兜底逻辑。编译只用于生成交付产物。

## 交付状态

源码修改、统一队列产物编译、正式文件发布及已授权的兼容业务热加载均已完成，完成时间为2026-10-19 21:40:55（Asia/Shanghai）。未做运行或视觉验收。

- 根入口：`pwsh -NoProfile -File ./build.ps1 -Module adapter -Toolchain MinGW -Publish -Reload -TargetPid 121728`，其他路径均使用项目默认值。提交后至本批次完成没有修改请求范围源码。
- 请求 `78fd1e0c8c954233b25798cc7adcea4c`，批次 `b5dd03bc0c3442bf897d8500e22bc413`。已读取对应请求结果 JSON 和完整批次日志，`Success=true`、`PublishRequested=true`、`ReloadRequested=true`；一次配置及一次增量构建完成。
- Adapter 编译成功，仅有既有 `native_name_input.inc` 与 `module.cpp::initialize` 的六项 `GetProcAddress` 函数类型转换警告，本次百科修改没有新增编译警告或错误。
- 正式事务 `218abb3dc99f4a3f885236cd7fe083d9`；已读取其 `publication-result.json`，`success=true`、`runtime_requested=true`。PID `121728` 返回 `ReadyToPublish` 和 `Applied`，Adapter 第2代。
- 正式替换 `package/modules/uwcn_adapter.dll` 和 `package/release.json`。旧两件先按原相对路径移入 `回收/20261019-214055-218abb3dc99f4a3f885236cd7fe083d9/package/`，已只读确认存在。正式启动路径仍为根启动器及相邻 `package/`。
- 新 Adapter SHA-256 为 `dddef2ee5076287ee40e6872f60c8df6d7d0bf3a8b451fe182d861c029ada8a9`，正式清单及 Applied 回执均记录此值。
