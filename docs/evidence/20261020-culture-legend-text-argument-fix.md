# 文化图例启动闪退：文字参数索引修正

用户在上一批修正后手动启动并报告闪退。`package/uwcn.log` 新增 `UWCn reconstruction ABI 1 initialized.`，说明此前 Hook 安装拒绝已越过；Windows Application 事件和用户产生的 `urw.exe.185504.dmp` 则记录新的访问异常。本轮只离线读取该转储、日志和原始 PE，没有启动游戏、注入、模拟输入、运行产物或测试，没有写测试、断言、保护或回退。

## 转储和实际根因

出错正式 Adapter SHA-256 为 `598e0052f133ec10df8fa7140b29cf6fd329662658b02535877d2844efef5748`。转储中该 DLL 的实际加载基址为 `57920000`，异常地址 `5792B373`（RVA `B373`），指令是 `MOVZX EDI,BYTE PTR [EAX]`。EAX 为 `FF00C000`，这是 `decode_parser_original` 读取原文首字节；返回地址 `5794080B`（RVA `2080B`）属于 `windows_culture_lend`。完整已提取寄存器见 `20261020-culture-legend-crash-dump.json`。

`modules/adapter/windows_encyclopedia.inc` 的 `we_map_renderer_first` 共用分支错误地把 `e.arguments[2]` 借作文字。这是调用参数的实际含义错误，不是缺少原文字段或解码器需要忽略坏地址。

启动原路径 `117C01 → E3A50` 构建文化图例，首行 `E3AB7 → 10E260` 依次压入 outline、packed color、文字地址、y。完整 `10E260` 接口接收 renderer 在 ECX、x 在 EDX，栈参数为：

| 索引 | 原生参数 |
| --- | --- |
| 0 | y |
| 1 | 完整文字地址 |
| 2 | packed color |
| 3 | outline |

首行原颜色正是 `FF00C000`，与转储中的错误读取地址完全一致。该颜色被当作 `const char*` 传入首字节读取，所以产生 `C0000005`。

## 源码修正与同类复核

将上述共用分支的文字借入参数改为 `e.arguments[1]`，统一覆盖全部 11 行原生调用：`E3AB7/E3AD4/E3AF1/E3B11/E3B2E/E3B4B/E3B68/E3B88/E3BA5/E3BC2/E3BE2`。这些调用的实际压栈顺序逐项核过，不逐行特判，不修改颜色、outline、布局、纹理和原输入。

保留原 renderer 借入作用域。完整图例 factory 的普通构建与语言重建均已通过 `native_culture_legend::Construction` 进入 `Scope::native_renderer_resource`，由各原文字调用消费实际 renderer 和原 outline。没有把图例切到软件 surface 文字路径，也没有固定替代样式。

同类索引另核：`1166C0` 标题为 args3、`111560` 文字为 args2、`116270` 标题为 args2、`10E5A0/114680` 文字为 args0、`CFD10` 文字为 args2、`162300` 来源为 EDX。文化预览、现代法术页脚、HUD 和对应 typed wrapper 未发现另一处同类颜色当文字的确定错误。

## 编译与发布来源

以刚才正式发布的冻结源码 `startup-c70c-a74f8f1fc9bc4d6996b2148be8679da6` 为基础，复制为 `build/.source-snapshots/legend-text-8b5d679d1de14de9b0be53cb4d6a9937`，仅补本次参数索引。相同修正同时保存在工作区源码中。该目录只作编译输入，继续通过根队列和原 `build/mingw-x86` 构建，不生成平行运行包，也不纳入共享工作区的后续并行功能修改。

通过根入口提交 `adapter -ModuleSourceDirectory <上述冻结来源> -Publish`，继续使用默认 MinGW 工具链和同一构建树。请求为 `c1100005feb547708aef27205cc6fc39`，批次为 `39d4091e5ff04bb28911855e09f00df6`。2026-10-20 01:53:33 +08:00 完成，结果 `Success=true`、`PublishRequested=true`、`ReloadRequested=false`。已读取请求 JSON、批次日志及 `publication-result.json`。保留已有 52 项函数指针转换、6 项缩进、6 项聚合尾部初始化、5 项未使用函数、1 项未使用参数及1项 extern 初始化警告，没有零警告或运行成功的声明。

新 DLL 的静态分支 `69E6F10D..69E6F116` 选择 11 个 renderer 行，`69E6F2C0` 取 NativeEvent.arguments，`69E6F2CD` 已生成 `ADD EBX,4`，传入实际 `arguments[1]` 的引用。该机器码也确认正式产物包含索引修正。

正式事务为 `567b54e02ab54b27afae4f84c29ae7ca`，仅替换 `package/modules/uwcn_adapter.dll` 与 `package/release.json`；旧两件先归档至 `回收/20261020-015333-567b54e02ab54b27afae4f84c29ae7ca/package/`。正式 Adapter 与本批构建产物的 SHA-256 均为 `c6c51ba647059f18c4ff987085f51ca5378aa42e678b97fe9a02f711398abdba`。词库、根启动器、驻留层及其他业务库未替换。

发布前只读清单未发现运行中的 `urw.exe`，本批没有运行时控制事务或 Applied 回执。原根启动器的正常加载路径已更新到该 DLL；没有自行启动、关闭或重启游戏，没有运行产物或测试，也不以编译或发布成功代替启动及画面验收。
