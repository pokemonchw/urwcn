# Windows 初始化阶段 Hook 边界修正

后续运行边界：用户下一次启动已成功记录初始化完成，但随后在文化图例构造时发生独立的文字参数索引错误；转储根因及新的正式事务见 [文化图例文字参数修正](20261020-culture-legend-text-argument-fix.md)。本记录的事务是该次运行之前的交付，不代表启动画面已验收。

用户手动启动后提供了“Mod 初始化未完成，新建的挂起进程已结束”的截图。读取 `package/uwcn.log`，末尾两次均为 `Adapter initialization failed at native text hook installation; status=1`，随后是 Adapter 模块初始化失败。没有自行启动游戏、注入、模拟输入、运行产物或测试，没有新增测试脚本、断言、保护或回退逻辑。

此前正式 Adapter SHA-256 为 `67d9627d0920a83462ac538999658b6a0d29696918eb6727f384fcdf6b1b762a`。以下问题已同时在源码、该正式 DLL 的静态反汇编和原始 EXE 中确认。原 EXE SHA-256 为 `e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`，地址均为 RVA。

## 确定根因

`modules/adapter/windows_message_value_builders.inc:167` 的 `corpse_select_cut_great`（ID `C70C`）错误声明 `site=AE5D2`、操作码 `BA`、五字节绝对地址载入。正式 DLL 的对应初始化代码也包含相同值。

原生指令实际为：

```text
AE5D0  0F 86 97 00 00 00    JBE AE66D
AE5D6  B9 2C 1B 62 0A       MOV ECX, base+A221B2C
AE5DB  2B F9                SUB EDI,ECX
```

`AE5D2` 是前条 `JBE` 的位移内部，其实际五字节是 `97 00 00 00 B9`，必定不同于旧声明的 `BA <绝对地址>`。`src/loader/hook_host.cpp::install_hooks` 在第一轮原始字节核对中返回 `Status::invalid=1`，且该轮校对发生在任何本批 Hook 指令写入之前。这准确对应用户日志中的失败阶段；不是根据截图猜测运行异常。

现将该声明改为 `AE5D6`、`B9`，覆盖完整的五字节 `MOV ECX`。该 ID 的分派仅记录实际 `CARCASS_CUT:GREAT` 中性资源身份，不修改 ECX/EDX；原条件判断、资源选择和后续字符串复制保持原语义。原有 `settlement-global-value-refs.tsv` 已记录正确边界，本次使用该证据纠正声明，没有跳过字节核对。

## 同类静态审查

另在 `A243D` 发现两处相同原生 `LEA EDX,[ESP+250]` 登记：`windows_message_value_copies.inc` 与 `windows_message_format_builders.inc` 使用不同 ID 注册同一指令。它们的原始字节相同，因此不是本次安装阶段 `invalid` 的原因；安装阶段后写入项会覆盖前项。已移除 value_copies 中的重复声明和处理，保留 format_builders 的唯一入口。该点前面真实 `MOV ECX,EAX` 已完成，唯一处理从实际 ECX 来源绑定到原生 ESP+250 缓冲，继续重放原 LEA 和复制循环。

共同组件、Menu、Root、Cache、HUD、renderer 资源、旧页面显示消费及消息伴随源也进行了原始指令、CALL 目标和声明长度的只读复核。没有因大量 Hook 或 IAT 指针的未经证实猜测修改驻留层。

## 冻结来源与交付

共享工作区还有并行消息源码修改，本批使用项目已有 `ModuleSourceDirectory` 入口冻结模块及其引用源码，目录为 `build/.source-snapshots/startup-c70c-a74f8f1fc9bc4d6996b2148be8679da6`。该目录仅是编译输入，不包含平行启动器或修复运行包；继续复用 `build/mingw-x86` 和根队列。快照保存两项修正，并包含冻结时已保存的消息来源接线。消息词库从同一快照的来源表生成，共 67,641 项。

新增伴随消息源的 144 个 Hook 也已针对冻结快照静态核对：123 个 inline、21 个 CALL，原始字节、目标及长度吻合，未发现新增或既有入口重复。没有运行这些入口。

| 阶段 | 请求 ID | 批次 ID | 结果 |
| --- | --- | --- | --- |
| `adapter,catalog` 冻结来源编译 | `6c3c39f6006c4fa6af8ba36db6af48e1` | `d2e1ef3992bd4c2f8923c5a8c2c5bcc0` | `Success=true`，无 Publish/Reload；2026-10-20 01:44:59 +08:00 |
| 相同来源 `adapter,catalog -Publish` | `fa38d9647cc74e3ab9132e44dca540d0` | `a8674075028f4e169b8797da595c6e62` | `Success=true`，正式发布成功，无 Reload；01:46:19 +08:00 |

两批均使用默认 MinGW 工具链及同一 `build/mingw-x86`，各一次配置、一次增量构建；已读取请求结果 JSON 及批次日志。完整编译仍有已记录的 SDL 函数指针转换、缩进、未使用声明和聚合尾部初始化警告。发布批次无需重新编译源码，使用同一冻结产物。

对新产物的只读反汇编确认：`append_builder_hooks` 在 VA `69E2EEA5` 提供 `site=AE5D6`，其 helper 在 `69E08DD1` 写入 `expected[0]=B9`，同时使用 `kind=inline_code`、`byte_count=5` 和实际 image base 重定位。没有加载或运行 DLL。

正式事务 `108be69c6a744d15a13a227e21322faf` 替换 `package/modules/uwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json`。旧三件先移入 `回收/20261020-014619-108be69c6a744d15a13a227e21322faf/package/`，发布回执 `success=true`。Catalog DLL 内容未变，没有替换；根启动器与驻留库未改动。

最终正式 Adapter SHA-256：`598e0052f133ec10df8fa7140b29cf6fd329662658b02535877d2844efef5748`；正式消息词库 SHA-256：`06abded32b1ca7c9433c5de8f988ba385244e83b7b48f91da84f340b2d30be21`。正式文件与本批构建/生成文件摘要一致。

发布前只读进程清单未发现 `urw.exe`。没有发送热加载控制命令，没有 Runtime Applied 回执，没有关闭或重启游戏。修正由根 `uwcn_launcher.exe` 的正常加载路径使用；启动与画面结果仍由用户实际运行提供，不用编译或发布成功代替运行验收。
