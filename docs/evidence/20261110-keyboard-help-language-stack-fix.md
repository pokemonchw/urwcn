# Shift+F10 闪退：帮助页原生重建入口栈修正

日期：2026-11-10。用户报告按 Shift+F10 后游戏直接退出。没有自行启动游戏、重现按键、注入、模拟输入或运行测试；没有新增测试用例、断言、保护或回退分支。

## 现场记录与证据边界

正式 Adapter 为 `92e043dcbc92d0846330a1afa1c7c04094d7ffdfd1c70ef9f782e1a4e1da3e75`。只读 Steam `gameprocess_log.txt` 和 `console-linux.txt` 记录用户在15:54:23启动、15:54:58退出的进程，宿主游戏 PID 为 `2973362`。当前进程表已没有游戏。

系统 coredump 列表没有本次记录，当前 Wine prefix 没有本次 `.dmp` 或异常回溯；`/tmp/dumps` 的唯一转储是15:19的 Steam assert，早于本次退出。游戏日志末尾没有本次故障指令地址。因此下述结论是源码与原生指令之间可直接证明的栈错误，不将其描述为已取得异常栈证明的唯一崩溃原因。

## 已确认错误

上一版 `modules/adapter/windows_keyboard_help.inc::rebuild` 在 `10539B` 的平衡输入返回点直接跳到 `103AA2`。这两个位置的 ESP 契约不同，缺少16字节原生待清理参数空间。

静态对象为 Windows 3.89.1，PE SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。以下均为 RVA，原始指令保留在 `build/analysis/keyboard-help-3891.asm` 和 `windows-3891-native-full.asm`：

| 位置 | 原生指令与栈含义 |
| --- | --- |
| `103A33..103A4C` | 分配 `43C` 字节局部变量后保存 EBX、ESI、EDI，平衡基线为 `EBP-448` |
| `103A82..103A97` | 为已经完成的 SDL blit 压入四个参数，共16字节，尚未清理 |
| `103A9D → 16D110` | 无栈参数的原生调用；其 `16DB32` 是普通 `RET`，不清理上述参数 |
| `103AA2..103AB5` | 在这16字节之下压入8个 CreateRGBSurface 参数，共32字节 |
| `103ABD..103ABE` | 再压入1个 CreateSoftwareRenderer 参数，共4字节 |
| `103AC4` | `ADD ESP,34h`，合并清理16+32+4=52字节，回到原平衡基线 |
| `105377..10539B` | `ADD ESP,20h` 清理视口阶段的8个参数；三个后续原生调用没有待清理参数，输入返回仍在平衡基线 |

从 `10539B` 不作栈转换就跳到 `103AA2`，只新增36字节，随后却移走52字节，使 ESP 高于平衡基线16字节，进入已分配的局部变量区。后续压栈和函数退出会破坏局部值与保存寄存器。这是语言切换及已打开帮助页更新共同使用的错误路径。

驻留 `src/loader/hook_host.cpp::restore_registers` 明确保留 raw ESP，因为 POPAD 不恢复该字段；仅修改 `NativeFrame::esp` 不能修正真实机器栈。本次不修改驻留桥或 ABI。

## 修正与静态复审

新增单一 naked 续接入口 `uwcn_keyboard_help_reconstruct`：先 `SUB ESP,10h`，再间接跳转到已确认的 `103AA2`。16字节是前述已完成 blit 的待清理空间，仅用于恢复栈深度；该区间后续不再读取这些旧参数。普通原生打开路径不经过该续接入口。

`rebuild` 在原有资源退役、滚动位置与颜色/速度输入恢复后，将原生续点交给该入口。原 `103AC4` 保持不变，仍清理52字节，回到 `EBP-448`。中文切英文、英文切中文及同入口的兼容模块更新共用这一真实栈契约，没有语言专用兜底或跳过重建。

静态复审还覆盖输入前 `10537D` 的清栈、退出段 `1054BA..10551D` 的可选资源释放与寄存器弹出、两种正文缓存分支以及首次普通构建。未改写文本、布局、缓存内容或输入动作；没有页面重放。

此前 `20261110-keyboard-help-native.md` 与 `20261110-keyboard-help-density-fix.md` 对“同一原生帧重建”的记录遗漏了该入口的待清理参数契约。此前编译、发布和 Applied 不能证明此路径正确；这项已确认的源代码缺陷在本记录中整改。

## 交付状态

源码修正已保存；根统一入口执行 `build.ps1 -Toolchain MinGW -Module adapter -Publish`，一次配置、一次增量构建，仅重编 `module.cpp` 并生成 Adapter。已读取请求结果及完整100行批次日志，20条既有警告、0条编译错误。

| 项目 | 回执 |
| --- | --- |
| 请求 ID | `aaa1da1ef28740b8bc2f8c50a1d722b5` |
| 批次 ID | `9c6e6d5ee1ac4886935dc0ba72aaf9af` |
| 队列结果 | `build/.compile-queue/results/aaa1da1ef28740b8bc2f8c50a1d722b5.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=false` |
| 批次日志 | `build/.compile-queue/batches/9c6e6d5ee1ac4886935dc0ba72aaf9af.log` |
| 正式事务 | `e1c8d8c67b7b46568b22d3deac425436`，2026-11-10 15:58:25（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/e1c8d8c67b7b46568b22d3deac425436/publication-result.json`：`success=true`、`runtime_requested=false`、无运行时回执 |
| 正式更新 | `package/modules/uwcn_adapter.dll`、`package/release.json` |
| 旧件归档 | `回收/20261110-155825-e1c8d8c67b7b46568b22d3deac425436/package/`，保留原相对路径 |
| 新 Adapter SHA-256 | `bd0508d45e40937ea993b2810f2ddf871f0e02b80670cc2823752b8569386cd4`，正式件、构建件和清单一致 |
| 旧 Adapter SHA-256 | `92e043dcbc92d0846330a1afa1c7c04094d7ffdfd1c70ef9f782e1a4e1da3e75`，已从回收件读取确认 |

只读反汇编最终构建件的 `uwcn_keyboard_help_reconstruct`，`6446F43F` 为 `83 EC 10`（`SUB ESP,10h`），`6446F442` 为 `FF 25 5C F0 66 64`（跳到真实目标变量的间接 `JMP`），没有函数序言或额外返回地址。目标变量由 Hook 登记过程设置为当前游戏基址加 `103AA2`。这项检查读取产物指令，没有运行产物。

源码修改、产物编译与正式位置发布均已完成。发布前后只读进程表没有游戏进程，因此未请求 Reload、未取得 Applied，也没有自行启动、关闭或重启游戏。下一次从根 `uwcn_launcher.exe` 正常启动将加载这份正式文件，无独立修复包。没有自行运行测试或进行崩溃重现验收。
