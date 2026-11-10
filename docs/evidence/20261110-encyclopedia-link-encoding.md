# 百科链接表重载编码修正

日期：2026-11-10（Asia/Shanghai）。依据用户提供的百科首页截图、已有 `package/uwcn.log`、源码及 `build/analysis/windows-3891-native-full.asm` 静态分析。没有启动游戏、注入、模拟输入、运行产物、执行或编写测试、添加断言或推测性的保护／回退／兜底。

## 根因及证据

截图中黑字正文已按中文推进，蓝色链接、下划线和选择框却仍使用英文别名宽度。例如 `THE.BEGINNING` 的13字节按原生每字节8逻辑像素计算，符合截图中明显过长的下划线。不是仅有逐词元取整误差。

`package/uwcn.log:2700–2703` 已有两次 Shift+F5 卸载和重载记录，紧接 `2704` 起连续出现 `30984/30985/31014/31015/31016` 的 `status 1`。这些分别是 `we_word_fit / we_pair_fit / we_prefix_width / we_label_width / we_underline`，即换行、链接定位、命中宽度和下划线的中文度量失败。这里只读已有日志，没有为复现而操作游戏。

完整静态调用链如下：

1. `src/loader/host.cpp::unload_translation()` 先设 `kNativeSetTranslation(false)` 并卸载翻译提供库；`reload_translation()` 在 `retire_modules(32)` 保存当前 Adapter 的英文状态，经 `restore_modules(63)` 恢复，再发依赖更新，最后才设 `kNativeSetTranslation(true)`。
2. `modules/adapter/module.cpp::restore_state()` 恢复 `chinese_enabled=false`；`kModuleDependenciesChanged` 随后调用 `initialize_windows_encyclopedia()`，重建链接显示表。
3. 原 `windows_culture_text()` 对明确的中文链接词条调用依赖当前显示语言的 `codec(encode_native)`。英文状态下它转入 `encode_parser_original()`，对中文保留 UTF-8 字节；`windows_encyclopedia_words` 因而持有 UTF-8。重新开启中文只调用 `invalidate()`，没有重新编码这个表。
4. `windows_culture_width()` 直接将表内标签交给 `metrics()`；中文状态下 `layout::decode()` 要求原生双字节 transport，读到 UTF-8 lead 大于 `BF` 即返回 `invalid`。`src/loader/host.cpp::dispatch()` 对这类错误只写日志，`hook_host.cpp::uwcn_inline_dispatch()` 因未取得替换决定而继续原 ASCII 宽度指令。
5. 绘制与度量的区别在 `native_name_input.inc::showtext_copy`：原生 `10E5D2` 的本地文本副本会经 `contains_utf8 → display()` 规范成 transport。字形和 `10E700` 光标因此仍消费中文，而链接度量失败后保留英文 `strlen×8`，造成错位、重复可见及重叠。

`3.89.1` 的 `3D9BC/3DAC7/3D591/3D5FB/3D6AE/3D728` 均与现有 Hook 的指令及参数一致，驻留桥的 `skip_original` 实现正确，不需要更改桥或原生坐标。

## 源码修正

`modules/adapter/windows_encyclopedia.inc::windows_culture_text()` 始终解析中文 culture 资源，供链接显示表及 `translate_culture_back()` 的后退标签／主题标题使用；改为用 `CodecRequest` 明确调用 Layout 的 `encode_native` 服务，编码不再依赖当前显示语言。初始化和依赖刷新均消费同一接口，Adapter 热交接也重新构建该表。后退语义在英文状态下由 `resolve_display_text()` 的原文分支处理，不进入中文资源格式化。没有新增状态字段、Hook、ABI、语言分支或错误回退。

保留逐原生词元累计的度量和完整 `3D820 → 3D300` 原生流程，正文、试排、链接位置、选择框和下划线读取相同 transport 标签。英文主题名、检索、主题历史、输入动作、原生换行及控件／缓存生命周期保持原语义。字形仍在原生文字调用中按照真实目标输出密度即时提交，没有坐标表、行槽、页面快照、DisplayPlan、像素跟踪或延后文字重放。

## 既有审查及待整改状态

- `docs/evidence/20261019-windows-encyclopedia-token-metrics.md` 的逐词元修正确实覆盖了取整差异，但没有覆盖本次 F5 的链接表编码失配。该文及 README 的既有“已修复／已发布”记录不能证明重载状态下度量正确。本次修正该 Windows 编码路径；编译发布与视觉结果仍分开记录。
- `src/linux/culture_info.inc::culture_link_width()` 仍对合并字符串测量，与逐词元推进单位不一致；`culture_tokenize()` 的控制词元空格规则也未同步 Windows。影响 Linux 百科，状态仍为待整改，本次 Windows 修复未修改或发布 Linux 路径。
- `src/loader/host.cpp::dispatch()` 仍在 Adapter 返回度量错误时只写日志并继续原始指令，影响文字与原生度量一致性。状态待整改；本次消除已确认的百科编码错误，没有扩大为推测性的全局保护或回退。
- `modules/adapter/native_footer_component.cpp::paint()` 仍由 Mod 计算署名宽度、x及间隔；`modules/adapter/native_ui_scene.cpp` 的历史 `Child/Container` 及序列化仍未完整退役。影响和待整改状态沿用已有记录；本次不调用或扩展这些旧布局路径。

## 交付状态

源码修正、统一队列产物编译、正式文件发布及兼容业务热交接均已完成，完成时间为2026-11-10 16:18:33（Asia/Shanghai）。已完整读取请求结果 JSON、批次日志与正式发布 JSON，并只读核对构建件、正式件及旧件归档。未运行或做画面验收。

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Publish -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `b03d99aa70bf49c8a7b99692ae4aa043` |
| 批次 ID | `511f662fda534795a06748421e1707cc` |
| 请求结果 | `build/.compile-queue/results/b03d99aa70bf49c8a7b99692ae4aa043.json`；`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 批次日志 | `build/.compile-queue/batches/511f662fda534795a06748421e1707cc.log`；一次配置、一次增量编译及链接完成，保留既有警告，无编译错误 |
| 正式事务 | `d01ecb5d5911434ebb61c4747b14633f` |
| 发布结果 | `build/mingw-x86/stage/d01ecb5d5911434ebb61c4747b14633f/publication-result.json`；`success=true` |
| 正式替换 | `package/modules/uwcn_adapter.dll`、`package/release.json` |
| 旧件归档 | `回收/20261110-161832-d01ecb5d5911434ebb61c4747b14633f/package/`，两件均保留原相对路径 |
| 热交接 | Windows PID `364` 返回 `ReadyToPublish` 后 `Applied`，Adapter第5代；无需退出或重启 |

新 Adapter 的构建件、正式件及 Applied 回执 SHA-256 均为 `e724241351f7bc167b13bbb9c249a63d323eb78061b1d6150197aa6366bbd4f7`；归档旧 Adapter 为 `2f8bb901d3bacfcde6e292a4de5b77b6553753a0f161659612c080db8ac29001`。正式入口仍为根 `uwcn_launcher.exe` 及相邻 `package/`，没有独立修复包或平行运行副本。源码提交编译后至批次完成未继续修改请求范围源码。

Adapter初始化及依赖刷新已重建链接表；现有语言失效通知由原生输入返回边界进入百科完整构造，重新生成正文、链接及控件。没有发送输入或以重启强制刷新。Applied仅证明模块事务完成，不能代替画面验收。
