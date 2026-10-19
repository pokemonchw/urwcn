# 2026-10-19 本轮重建交付记录

2026-10-19 纠正：本页的编译与正式发布回执仍是历史事实，但下述“已完成”及原生缓存合规结论撤回。用户随后报告严重卡顿，并明确否定像素与文字记录遍历、重放方案。正式版仍含该机制，尚未整改完成；见 [实现纠正记录](20261019-implementation-correction.md)。

本轮曾编写并发布启动器、驻留模块宿主、六个业务模块及主界面中文输出。编译和正式文件发布的回执如下，但渲染采用了被否定的全局内容记录与重放，不能宣称用户要求的实现已经完成；用户禁止自行测试和运行产物，因此没有运行画面验收或运行时 Applied 结论。

## 实现范围

- 七项主菜单和条件出现的索引 7“额外内容”，保持原菜单项、选择、鼠标命中和动作。
- 原生版本值、出品、版权年份、作者与网站段落；原业务数据和控制标记保持原语义。
- 原组件读取/格式化/消费边界按组件语义翻译，安全编码返回原 UI。真实字体宽度接入原居中、折行和光标推进位置，避免按 UTF-8 字节计宽。
- 当时交付的 Render 保存像素与文字贡献，并在原 RenderCopy 时重建完整源。这是已确认需要移除的违规实现，不是当前设计要求；其历史源码交付不能证明满足原生 UI 所有权。
- 启动器在新建进程精确 PE 入口处交接，模块宿主使用驻留桥、同步租约、状态迁移及兼容业务模块发布协议。统一编译队列合并后续批次；正式文件替换先回收再放入。

游戏标题及制作组图像仍为原生图片，不伪称文本组件。设置、关于、鸣谢、先祖等子窗口内部，以及历史 Byayoi 标识，不列入这次主界面文本链的完成范围。没有页面坐标表、DisplayPlan 或 Present 叠字；驻留 Present 包装只服务通用发布控制。

静态实现依据：

- [原生边界](rebuild-ui-boundaries.txt) 与 [反汇编摘录](rebuild-native-call-disassembly.txt)
- [框架审查](rebuild-framework-audit.txt)
- [字体与原生绘制边界审查纠正](rebuild-font-audit.txt)
- [历史文档冲突与待整改记录](rebuild-compliance-audit.txt)

## 编译回执

两次调用均只通过根 build.ps1，未绕过编译队列，未清理构建树。每批配置一次、增量编译一次，八个目标全部成功。请求期间对应源码保持冻结。

| 用途 | 请求 ID | 批次 ID | 结果 |
| --- | --- | --- | --- |
| 全图编译、静态 PE 检查 | 2d1480c2a8aa43e6b9f2f7563c635a4a | 13c295b5afad442c900803a4b95cf3dc | 成功，未发布 |
| 整理诊断后的全图编译与正式发布 | 92253ed62a7245c89d0889f74deea3b3 | 3701697068ec441bb63d748e63f2c1a4 | 成功，已发布 |

已读取各请求对应的 build/.compile-queue/results/<request-id>.json 和 batches/<batch-id>.log。最终仍有 GetProcAddress 从 FARPROC 到已确认 cdecl 函数签名的编译器转换警告，未关闭警告，也未将编译成功称为零警告。缩进和 HookSpec vector 增长诊断已经处理；后者改为独立接收 render specs 再合并。

静态检查正式 PE 文件为 i386，六模块均导出 uwcn_module_descriptor 和 uwcn_get_module_api，驻留桥导出 uwcn_initialize。导入表仅含 Windows DLL，无额外 MinGW 运行库 DLL、业务模块相互导入。记录见 [正式 PE 信息](rebuild-delivery-pe.txt)。这些是文件读取与反汇编，不是执行或测试产物。

## 正式发布回执

- 事务：3bc905527c2046a88bbf172270de8f74。
- 回执：build/mingw-x86/stage/3bc905527c2046a88bbf172270de8f74/publication-result.json。
- 正式启动器：根 uwcn_launcher.exe。
- 驻留桥：package/uwcn_loader.dll。
- 业务模块：package/modules/uwcn_{catalog,semantic,render,layout,main_menu,adapter}.dll。
- 词库：package/catalog/zh-CN/main_menu.tsv。
- 适配：package/profiles/urw-3.89-steam-25939378.json。
- 发布清单：package/release.json。
- 已按正式清单逐文件读取 SHA-256，十个条目全部一致。

回收事务目录为 回收/20261019-005947-3bc905527c2046a88bbf172270de8f74/。本轮之前没有旧正式二进制，因此该发布事务没有可移动的旧交付物。旧 README 和设计文档已另存于 回收/20261019-rebuild-documentation/，没有删除或覆盖旧交付文件。

没有独立修复包或备用运行目录；构建目录仅含编译输出和发布暂存。正常入口已放到根目录，无须使用 build 中的启动器。

## 运行状态

本次未启动游戏、未注入运行中的游戏、未模拟输入、未执行产物，未编写或运行测试及断言。本次没有 Reload，也没有运行时 Applied 回执。兼容业务模块热发布协议已实现；本轮新 ABI 1 的驻留桥不承诺能替换旧 ABI 3 驻留桥。

源码和正式文件交付完成不等于实际画面已确认。实际启动与视觉效果仍未经运行确认。
