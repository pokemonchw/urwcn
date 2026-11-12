# 消息日志热重建闪退：完整原生栈帧误走裸RET

2026-11-12，用户在日志漏译热发布后报告闪退。该崩溃是汉化代码的确定性栈返回错误，前批Applied只证明模块交接完成，不能证明重建路径正确。本次依据真实转储、相同身份二进制、源码和原生指令离线定位，不启动游戏、不注入验证、不模拟输入、不运行测试或产物。

## 现场与根因

Windows x86《不真实的世界》3.89.1 / Steam Build26139145，原PE SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。游戏基址400000h，下文原生地址使用RVA。

- 17:44:08（Asia/Shanghai）第一现场转储：`package/crashes/20261112-094408-722-p364-t368.dmp`，SHA-256 `f56186f81248b03bbf578aed46709a0004ae75e420112173d28191e44775aea1`。
- 外部监控完整转储及报告：`package/crashes/20261112-094409-535-p364-t368-1/`。`process.dmp` SHA-256 `9ef6bde2c6bd45e8693497a997c93b9594d932df7d16652a99acc3cc10ed03b6`。
- 故障线程368，Windows PID364，异常C0000005，读取地址A9h，EIP=`797311C0`，ESP=`0AD7CBD4`，EBP=`0AD7D928`。Loader基址79640000h，EIP位于其`.data`，不是有效文字绘制代码。
- 最后原生事件21098=`526Ah`，即`native_generic_menu_language::history_input`，inline_before；调用栈为借用原生日志FE2B0、Adapter的history/menu重建，再回到真实FEB7C等待者。
- 转储release清单的Adapter SHA为 `cb364aa68163f6f66cabb2963be94a27aaccbaa0a05afdf4e512ba34be762c14`，与崩溃后正式件及本机符号二进制一致；Loader SHA为 `7342e826539dc75f1254c4c266442a0f231c832adef526592a3b89ce3729d07d`。

FE2B0原函数先保存EBP、对齐ESP到8字节、分配D4Ch局部空间，再保存EBX/ESI/EDI。此前重建调用完整FE2B0，却在FEB77的输入调用前转到 `native_component_calls::urwcn_component_fragment_return`，该函数只有`C3 RET`；此时原函数的寄存器和局部栈尚未退役，栈顶是保存的EDI。

完整转储的决定性数据（`build/analysis/crash-20261112-174408/native-frame.json`）：

| 字段 | 实际值 |
| --- | --- |
| 借用FE2B0的EBP | `0AD7D928` |
| 保存寄存器区 `(EBP & ~7)-D58h` | `0AD7CBD0` |
| `[0AD7CBD0]` 保存的EDI | `797311C0`，与故障EIP完全相同 |
| `[0AD7CBD4]` 保存的ESI | `797311C0` |
| `[0AD7CBD8]` 保存的EBX | `0AD7DE80` |
| `[EBP]` 原调用者EBP | `0AD7D940` |
| `[EBP+4]` 真实返回地址 | `774FFD55`，Adapter+2FD55，即history()中完整FE2B0调用的返回点 |
| Adapter+ A78AE现场字节 | `C3 90 0F 0B`，裸RET |
| 原保存cookie | `6A969156` |
| 按原退栈ESP解出的cookie | `60415A8A`，与原全局cookie一致 |

裸RET从CBD0读出EDI作为地址后，ESP正好变为现场CBD4。原EBP、真实返回点和cookie均仍有效，证据指向错误的返回路径，不是依据异常名称猜测栈溢出，也不是新语法的递归失败。该错误原先已存在于日志完整重建，前批兼容交接触发了该路径。

## 修正

`modules/adapter/native_generic_menu_language.inc:233`：仅将 `Construction::history` 的FEB77续接点从裸RET改为原生 `FEE19`。[原生完整退栈指令](20261112-message-log-rebuild-crash.asm)执行：

```text
FEE19 POP EDI
FEE1A POP ESI
FEE1B POP EBX
FEE1C MOV ECX,[ESP+D48h]
FEE23 XOR ECX,ESP
FEE25 CALL 18A0AE      ; 原函数已有的cookie检查
FEE2A MOV ESP,EBP
FEE2C POP EBP
FEE2D RET
```

这使用原函数实际出口，不在Mod中添加断言或保护；没有重跑FEDDA..FEE17的关闭窗口、恢复业务标志等正常退出动作，也不消费新输入。普通日志输入仍走原FEB7C返回点与D1120；原真实等待帧继续存活。原有正文、菜单、按钮、中文度量、原生分页和缓存生命周期保持；前批补入的漏译词库继续保留。没有新增Hook、驻留ABI、持久状态、布局、位置表或重放集合。

## 恢复副本与既有待整改项

外部监控报告 `serialization_complete=1`，恢复副本完整保存在 `package/crashes/20261112-094409-535-p364-t368-1/save/ALICE/`。报告同时明确 `emergency_save_committed=0`：`src/launcher/emergency_save.cpp:306` 附近 `fs::rename(source,recycled)` 返回Permission denied，原角色目录未成功归档，新副本未安装到正式读档目录。不能把已写入副本描述为自动恢复成功。本次未覆盖原角色存档；该目录归档失败仍待整改，没有假设具体占用者或补造保存字段。

已知原生UI所有权缺口继续待整改：`native_renderer_component_binding.cpp:47` 的Owner.children及`:570/:672`遍历重画；`native_footer_component.cpp:58/:79`的署名位置计算；`docs/design.md`保留的DisplayPlan／固定坐标／Present叠字历史建议。本修正没有扩展这些机制，不能因编译或发布视为合规。日志纯语言重建复用旧一／二行分页标志的问题也仍待整改。

## 交付状态

源码修正、产物编译与正式发布均已完成。17:44:29外部监控已记录原进程以C0000005退出；发布前只读进程列表无urw.exe，本批不请求Reload、不取得Applied、不自行启动或重启游戏。

统一入口：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Publish
```

| 项目 | 已读取的实际结果 |
| --- | --- |
| 请求ID | `c822c1b075924bd1ae5a1115ea67868f` |
| 批次ID | `bf69f9fc99e44a50a26a8f529f8421df` |
| 请求回执 | `build/.compile-queue/results/c822c1b075924bd1ae5a1115ea67868f.json`，Success=true、PublishRequested=true、ReloadRequested=false |
| 完整批次日志 | `build/.compile-queue/batches/bf69f9fc99e44a50a26a8f529f8421df.log`，已完整读取；一次配置、一次增量编译，重编Adapter的module.cpp并链接 |
| 正式事务 | `13d91ccaa53149c3a26d3e990bd0b3de`，2026-11-12 17:48:55（Asia/Shanghai）完成 |
| 发布回执 | `build/mingw-x86/stage/13d91ccaa53149c3a26d3e990bd0b3de/publication-result.json`，success=true、runtime_requested=false |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/release.json` |
| 旧文件回收 | `回收/20261112-174855-13d91ccaa53149c3a26d3e990bd0b3de/package/`，两件按原相对路径先移入再替换，未覆盖或删除旧件 |
| 新Adapter SHA-256 | `3e67a1b047f06e62d5609cfa75b827d7fdb7df2875f8968a2970f6f9953bb9c4`，构建件、正式件与清单一致 |
| 回收Adapter SHA-256 | `cb364aa68163f6f66cabb2963be94a27aaccbaa0a05afdf4e512ba34be762c14`，与本次崩溃二进制相同 |

已只读反汇编正式Adapter：原history_input（526Ah）分支在Construction=2时生成`MOV EAX,0FEE19h`并写入resume_rva；普通输入继续生成原输入桥地址。原游戏FEE19退栈字节也与完整转储中一致。此为静态二进制审查，不是运行验证。

从入队到批次完成没有继续修改请求范围源码，没有重复编译或绕开队列。既有函数指针转换、extern初始化、未使用项及缩进警告仍在，0错误。本小时build-hour未变化，既有98977项词库保持正式发布状态。根 `urwcn_launcher.exe` 下次正常启动使用同一正式包；没有独立修复包、平行运行目录或让用户改用构建件。
