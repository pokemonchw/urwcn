# Windows 咒语页底部百科提示补接

用户截图中的底部三行仍为英文：`SPELLS`、法术概述、F1百科提示。静态审查确认，既有 `windows_skills_spells.inc` 仅接入页面主体；`windows_encyclopedia.inc` 的 `F7BA/E0ECA → 3CA90` 是软件版百科提示，未覆盖本页纹理版。Linux 的 `src/linux/spells.inc` 已有对应三处接线，本次只修正 Windows 漏项。

目标为 Windows x86《不真实的世界》3.89 / Steam Build 25939378，PE SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`，首选基址 `0x400000`。下表地址为 RVA。原始指令来自既有只读静态材料 `build/windows-sync-pe.asm`，本次摘录保存在本地 `docs/evidence/20261019-windows-spells-footer-disassembly.txt`；原始游戏提取材料按仓库规则不提交，本文保留调用地址、参数和处理说明。

## 原生显示调用

| 原生调用 | 处理 |
| --- | --- |
| `DFFB9 → 3CD20` | 原 `MagicProfile` 构建底部纹理百科提示，栈参数1个。仅以该同步调用限定 `Scope::spells_footer`，原生返回后的 After 按 token 释放作用域；该函数不等待输入。 |
| `3CE45 → 10E260` | 原生 renderer 标题，栈参数为 y、文本、RGB、outline；只借入 `arguments[1]`，使用 `spells.footer.title`。 |
| `3CF2F → 10E260` | 同一原生文字接口借入 `spells.footer.summary` 完整概述。原函数 `3CE98..3CEA7` 对英文副本执行92字节截断，中文在该截断之后的显示调用生成；不修改源英文或该副本。 |
| `3CFA8 → CFD10` | 栈参数为 x、y、标签；只借入 `arguments[2]`，保留原 `F1.` 前缀，后缀使用 `spells.encyclopedia`，原动作 `EDX=0x423` 不变。 |

三项词库原已存在于 `catalog/zh-CN/main_menu.tsv`，本轮不新增词库记录。正文为“咒语”“咒语既能与精灵等异界生灵沟通，也能以法术影响现实世界。”及“打开 不真实的世界 百科，了解更多”。原 `SPELLS` 主题身份位于 `image+1A67B8`，由原生函数读取，未借用入口 ECX 推测主题，也未改百科跳转和检索。

## 字宽、字形与资源归属

标题和概述经现有 Layout 显示编码进入原 `10E260`；保留其原坐标、颜色和 outline。`Scope::hud_renderer_text` 把当次原描边位传给现有完整串字形输出，文字在原组件调用内立即绘入原目标。

原 `DF995` 创建的 `MagicpageMainTex` 已由 `native_targets.cpp` 登记真实物理密度，`3CD20` 原生 `SetRenderTarget` 选择该目标，现有 renderer 字形接口读取当次实际密度。F1按钮沿原 `CFD10`、`114D20` 构建，既有 `CFEAA/CFECB` 字宽、`114F67` 背景和 `11511D` 光标接口消费完整中文字宽；原生继续管理键帽、尺寸、选择、鼠标命中和缓存。没有新增 Mod 坐标、排版、纹理、像素跟踪或延后文字重放。

本次不改变 Host ABI 1、HDA4 状态格式或原有字段；新增 Scope 仅占用原枚举空位。作用域和借入文字由现有同步调用 token 生命周期释放，不跨输入等待保存页面。

## 审查更正与刷新边界

- `modules/adapter/windows_skills_spells.inc` 原 hook 注册尾部漏掉 `DFFB9/3CE45/3CF2F/3CFA8`，影响为截图底栏三行继续显示英文。状态：本次已补接四处原生调用。
- `docs/evidence/20261019-windows-progress-sync.md` 原“法术”行声称百科说明已覆盖，与上述源码不符；本次更正该历史范围。README 的“全部已接入范围”同样补充此漏项说明，不以此前编译或发布成功证明其已覆盖。
- 已经绘成的主页面底栏仍归原生缓存所有。本次未确认当前法术页的完整纯刷新入口；热加载回执不能证明旧缓存已更新。下次原生重新构建本页时消费三条中文，不重入 `MagicProfile` 的输入、音乐或施法业务，不合成 `-42` 或按键。

未启动游戏、注入运行中的游戏、模拟输入、运行产物或测试；未创建测试脚本、测试用例、断言或推测性的保护／回退／兜底分支。编译仅生成交付产物，正式发布仅使用已有授权的兼容模块事务。

## 交付状态

源码修改、统一队列产物编译、正式文件发布及已授权的兼容业务热加载均已完成。完成时间为2026-10-19 21:00:48（Asia/Shanghai）。未做运行或视觉验收，已有底栏像素的刷新限制仍如上所述。

- 根入口为 `pwsh -NoProfile -File ./build.ps1 -Module adapter -Toolchain MinGW -Publish -Reload -TargetPid 169784`，其余路径采用项目默认值：`.toolchains/x86/w64devkit/bin/cmake.exe`、同目录 `g++.exe`、`build/mingw-x86` 和 `package`。提交后至本批次结束未修改请求范围源码。
- 请求 `9277202f52b749008c2415b24e9b209d`，批次 `af352daa346946b3b1a7b46642ccde82`。已读取对应 `build/.compile-queue/results/<request>.json` 和完整 `batches/<batch>.log`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true`；仅一次配置和一次增量构建。
- Adapter 编译成功。日志包含既有 `native_name_input.inc:81` 五项及 `module.cpp` 的 `SDL_GetRGB` 一项 `-Wcast-function-type` 警告；本次底栏代码没有新增编译警告或错误。
- 正式事务 `9c0b8acc4c9640568e9fe1a3165430eb`。已读取 `build/mingw-x86/stage/9c0b8acc4c9640568e9fe1a3165430eb/publication-result.json`，`success=true`、`runtime_requested=true`。PID `169784` 返回 `ReadyToPublish` 和 `Applied`，Adapter 第2代。
- 正式替换 `package/modules/uwcn_adapter.dll`、`package/profiles/urw-3.89-steam-25939378.json` 和 `package/release.json`。旧三件已先按原相对路径移入 `回收/20261019-210048-9c0b8acc4c9640568e9fe1a3165430eb/package/`，已只读确认存在；根启动器和驻留桥未替换，未建立平行运行包。
- 编译 Adapter 与正式 Adapter 的 SHA-256 一致，为 `38ecdf34ddd8bceac454e959a31a549903fc745210e282cb4e981a108eb86c24`，同值见 Applied 回执。根 profile 与正式 profile 一致，为 `e1390566f1b6d6e3d9c812a3d27d245fbe629225bd004db1922a0f5b9fb8249b`；两值亦见正式发布清单。
