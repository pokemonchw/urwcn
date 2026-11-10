# D1120 当前完整界面归属

静态来源为原始 Windows 3.89.1 PE 与 `build/analysis/windows-3891-native-full.asm`，地址均为 RVA。此次只作静态分析与源码实现，未运行游戏、模拟输入、编写或执行测试、编译。

## 完整直接调用集合

原 PE 一共 36 个直接 `E8 -> D1120`，没有用“剩余全部是 HUD”作推定：

| 实际 CALL | 返回地址 | 当前完整构造归属 |
| --- | --- | --- |
| `F435` | `F43A` | Full：角色性别及之前已接受步骤 |
| `F8CF` | `F8D4` | 原文化选择实际父帧续建及完整预览 |
| `FB3B` | `FB40` | Full：季节及之前已接受步骤 |
| `10779` | `1077E` | Full：场景确认 |
| `10B84` | `10B89` | Full：场景选择 |
| `110C0` | `110C5` | Full：游戏历程 |
| `12255` | `1225A` | Skill confirmation：真实技能父及确认完整构造 |
| `1283A` | `1283F` | Full：头像及之前已接受步骤 |
| `3E1DE` | `3E1E3` | Full：百科完整原构造 |
| `561E8` | `561ED` | Parent：物品完整列表、额外说明及预览 |
| `60EA3` | `60EA8` | Full：原世界地图与实际 legend 输入 |
| `D7BD0` | `D7BD5` | Parent：完整伤势页及实际父 |
| `DF182` | `DF187` | 原祖先实际父帧完整续建 |
| `E0036` | `E003B` | Full：完整法术页 |
| `E0ED2` | `E0ED7` | Full：完整技能页及实际预览 |
| `E46A7` | `E46AC` | Generic：已知地点/区域完整详情纹理及地图父纹理 |
| `E4BD1` | `E4BD6` | Generic：已知地点/区域完整列表纹理及地图父纹理 |
| `E5F59` | `E5F5E` | HUD：原地图浏览实际帧完整续建 |
| `E6CB0` | `E6CB5` | 原角色属性实际父帧完整续建 |
| `FBA25` | `FBA2A` | Generic：第一个 yes/no query panel、完整父、当前 Menu |
| `FBC93` | `FBC98` | Generic：第二个 yes/no query panel、完整父、当前 Menu |
| `FBF56` | `FBF5B` | Parent：数量及真实完整父 |
| `FC390` | `FC395` | Parent：受限数量及真实完整父 |
| `FCE90` | `FCE95` | Parent：完整护甲页 |
| `FEB77` | `FEB7C` | Generic：消息历史完整原生页面与当前 Menu |
| `100640` | `100645` | Parent：命令页、段落帮助、预览和完整父 |
| `100C21` | `100C26` | Parent：定位命令页及完整父 |
| `106B20` | `106B25` | 原设置实际父帧完整续建 |
| `125092` | `125097` | Full：空载入提示及真实主菜单父 |
| `125BE1` | `125BE6` | Full：完整主菜单 |
| `125D00` | `125D05` | Full：新角色流程菜单及真实主菜单父 |
| `1427F5` | `1427FA` | Conversation + Generic：完整双方对话与聊天选项 |
| `147055` | `14705A` | Conversation + Generic：完整 NPC 资料及动作菜单 |
| `1586D0` | `1586D5` | Quest：完整任务详情纹理、上下文、按钮 |
| `1590A3` | `1590A8` | Quest：完整任务列表纹理、原页及按钮 |
| `15D4D2` | `15D4D7` | Parent：完整奖励菜单及真实完整父 |

新增 `native_generic_menu_language::menu(event,rebuilt,selected)` 只消费表中明确标为 Generic 的七处。Full / Skill / Parent 在前，Quest 使用自己的两个已确认调用者。当前实际等待仍留在原 D1120 内；完成构造后，共用协议回到 `D1167` 保存原 menu cache，保留当前选择并按原 software/renderer 分支呈现，没有新 input loop。

## Yes/no 的完整 query panel

两个原函数的 CF790 title 都是空串，真正 query 是 `FB983` / `FBBE2 -> 116270` 的独立原生 Panel。`D1120` 的原 `PUSH ESI` 把完整已接受 query 指针保存在 `EBP-43Ch`。Generic 同步借用该原文，保留当前实际 Menu，先恢复真实 FIRST 父并经 Parent 的实际 Root 所有权选择完整 HUD / Conversation 构造。

随后分别执行原 `FB938..FB988` / `FBB97..FBBE7`：原 sprintf、原 FIRST save、完整 116270 query panel。开始位置在原 F6510 echo 之后，不重复提交业务消息。结束 hook 在 Panel 原 `ADD ESP,24h` 之前，由明确的原 36 字节参数清理返回同步桥。原 Menu 再经完整 CFFB0 consumer、原选择构造消费；没有只刷新空 Menu title 的缺口。两个真实 Panel CALL 也登记完整文本元数据，英文模式的真实 UTF-8 姓名进入相同原生测量/字形生命周期。

## 消息历史完整显示构造

`FEB7C` 的原 owner 是 `FE2B0`，不是一个 HUD 上的短菜单。原前半会读文件、改写 70 条消息记录及世界可见性；重建不能重做这些业务。

`FE2B0` 的实际帧为 `AND ESP,-8; SUB ESP,D4Ch`，随后保存三个寄存器，故同步借用的正文基址为 `(actual parent EBP & -8) - D58h`。只借原逻辑输入：`+14h` 已读记录数、`+18h` 环形末项、`+20h` 总数。新完整原生帧在 `FE2D7` 门控后执行 `FE3C7` 原字体/容量计算；补齐其原本尚待清理的 12 字节参数，再由原 `FE3DF` 清理。

原 `FE409` SECOND 保存分支在本次构造跳过，保留原父缓存；原 `FE442..FE47D` 完整全屏 Panel 运行。`FE47D` 的 36 字节参数在明确桥内清理，跳过文件 feof/read/表初始化，给原 `FE673` 真实已接受末项/总数与刚由原字体计算的新容量。原 `FE680..FEA44` 完整环形记录、语法、颜色、paragraph、页号显示循环继续运行。当前 Menu 保留，不重新 CF790；`FEA44` 后使用原正确 cookie/寄存器 epilogue 退出，不进入新 D1120 或父缓存清理。

原 `FE5F8` 的 `strlen * 8` hint 在普通文件输入生命周期按完整真实源度量；`FE86E -> 162300`、`FE9BB -> 10EB40`、`FEA3C -> 10E5A0` 登记实际完整 CALL，英文中的原中文姓名与完整 paragraph 源共用正确 Unicode 范围。这里不新增消息翻译覆盖，不保存输出行或旧位置。

## 两个已知地点/区域纹理菜单

`E4050` 详情拥有实际已接受 `5B0h` record（parent `EBP-A30h`）和 `EBP-A31h` 的 self 输入；后者不能从被绘制循环改写过的 D1120 EBX 猜。重建借真实 EBP / BL，从原 `E413B` 进入完整 texture/header/body/controls/Menu 构造，由该首条指令原生装入 `ESI=SDL_SetRenderTarget`，不借用 D1120 的 RenderPresent import，也不重做原调用参数初始化。该区间没有旧 ESP 局部读取。

`E4960` 列表的原全局 count / records 已接受，完整原函数可重新消费。两个构造只在共用 input entry 跳过新输入；`E46AC` 明确返回同步桥，`E4BD6` 经原 cookie/寄存器 epilogue，跳过最后 owner / rectangle 退休清零。原当前输入因此使用完整新纹理及其原生控件输出。

这两个前景的背后 `5F937B0` 地图也含语言文字。新增 `native_renderer_component_binding::construct_known_map()` 仅借该实际当前 owner 的 MapInputs，直接进入现有完整 `E3D90 / E3EE0` 工厂；该路径不遍历 renderer children，不调用 Scene paint，不回放文字贡献。原工厂负责 allocation、背景、标题、测量、依赖 panel / paragraph、target reset 及纹理替换。Generic 两处均先消费此完整地图工厂，再消费其完整前景，统一完成 View::map。

## 已知地点字段的另一条真实编辑等待

`E4050` 的名称 / 说明字段分别在 `E47E2` / `E4812` 调用 `10F950`，实际返回地址为 `E47E7` / `E4817`。该函数使用自己的 1024 字节原生 ring 槽与 64 字节编辑预算，在实际 `EBP-40h` 保存 buffer，`EBP-28h` 保存 software renderer，`EBP-2Ch` 保存 surface，`EBP-34h/-38h` 保存原生输入坐标，原 CALL 参数继续保存文字颜色和背景 RGB。它不使用 `10F5B0` 的姓名编辑状态。

新增 `51EF` 是真实 `10FB17 -> D3BF0` CALL。仅在该 CALL After 已返回原语言唤醒值 `-2` 且地图语言请求待消费时，同步借 `[10F950.EBP]` 的真实 E4050 父帧，重建完整 known-map 及地点详情。保留当前 10F950 的全部输入和本地 surface / renderer，不执行初始化、初始字符串复制、接受输入或新等待。

字段编辑有一个不能复用 D1120 终点的原生业务边界：名称接受后 `E48BB` 把父 `EBP-A32h` 写为 2，`E4673` 会自动进入说明字段。新增 `5267` 在完整 texture、labels、Menu 及 `5F4EB08` 等 owner 写入已经结束后，在 `E4673` 前纯构造返回；此时最后 CFD10 的 12 字节参数已由 `E4647` 清理。普通路径完整实现原 `CMP BL,2 / JNE` 的两个真实后继 `E4678 / E46A7`，不改变自动编辑动作。

重建之后仍返回原 `-2`：`10FB7C` 的 unsigned `JA` 排除字符接受，经 `10FBE0 -> 10FA10` 回到原完整 prompt 路径。原 `10FA19..10FB17` 自己填背景、绘制当前完整 buffer、绘制光标、构造位置、组合当前新地图及详情、呈现并继续等待；原 ring 和输入预算都不变。该区间没有 ESP 相对局部读取；原 `10FADC` 统一清理尚存的 44 字节参数，原输入循环管理全部后续生命周期。

新增 `5265` 登记真实正文 `10FA4D -> 10E260` 完整 CALL，供已有组件 Unicode 范围和原 software-renderer 字形路径处理接受的 UTF-8 文本。`5266` 替换真实 `10FA77` 的 `strlen*8+2` 光标度量，使用同一完整原 buffer、相同 Unicode 编码范围、实际 `EBP-28h` software renderer 和原 outline=0；只把度量结果交回原 EDX，保留原 `+2` inset，并从 `10FA7E` 继续。文字颜色参数为 `EBP+10h`，背景 packed RGB 为 `EBP+14h`，未将它们误作字体或另建 UI。

## NPC 当前菜单

`14705A` 的真正父页是完整 `1342C0` NPC 背景、名称、资料、双方头像；`1427FA` 还包含实际已接受双方对话，不能直接 HUD + CFFB0。二者委托独立 Conversation 完整语义 owner 重建，再激活、消费原当前 Menu。聊天选项继续用实际原 `EBP-880h` rectangle 保存原 `chatopt`，更新其父缓存 revision；没有抄写布局或重跑聊天业务分支。
