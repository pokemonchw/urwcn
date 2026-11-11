# 日志旧行淡化破坏高清字形

日期：2026-11-10。用户截图中，底部两行中文完整，上方旧行变成棕色碎块。对象为 Windows x86《不真实的世界》3.89.1 / Steam Build 26139145。依据是原 PE 的离线反汇编 `build/analysis/windows-3891-native-full.asm` 与现有源码，没有启动游戏、输入模拟、运行测试、测试用例或断言。

## 已确认的破坏路径

`F6510` 在 `F67DF` 消费原生 gradient 标志；开启时，`F67EC..F6A1B` 对旧消息执行逐行淡化。原循环在 `F68D5` 读取目标像素，经两次原 `SDL_MapRGB` 与 `F6972/F6976` 比较排除背景和目标色，再由 `F69C7` 写回。循环、背景判定、色阶、条件锁定及标志清零均属于游戏自己的消息组件。

本次修改前，`modules/adapter/native_raster_patches.cpp` 的 `urwcn_nr_read_f68d5` 将原读取改成一个逻辑格的中心采样，`urwcn_nr_write_f69c7` 则把这个单色填入整个物理格。高清中文已在真实目标密度绘入；这对采样/填充会不可逆地抹掉格内字形细节。新行尚未淡化，因此仍然完整。此静态破坏路径与截图吻合；不能据此认定英文历史记录或存档内容也被删除。

既有 `20261019-native-raster-sampling-static.txt` 将 gradient 也列为中心采样的适用路径，该结论对已绘入的高清文字不成立；`native-raster-compiled-review-7e0bc794.txt` 只证明其历史产物的指令与 ABI，不证明字形保真。上述源码两处补丁本轮已退役，不把既有编译或发布视为符合高清原生 UI 要求。

## 修改与原生边界

只修改原生消息淡化循环的尺度操作数，保留其逐像素主体。Mod 不读取、比较或保存消息表面像素，不增加全局扫描、重放、文字快照、绘制序列或另一套消息布局。`F68D5` 与 `F69C7` 恢复原指令，由原游戏按真实物理像素读取、判定和写回。

| 补丁 RVA | 原指令及续点 | 尺度扩展 |
| --- | --- | --- |
| `F67FD` | `CMP EBX,EAX; JA F6A1B`，普通进入 `F6805` | 将原生包含末行的纵向区间映射为完整物理行。 |
| `F682D` | `LEA EDI,[EDX+5]; ADD EAX,EDX`，续 `F6832` | 原生每行起止列映射至同一真实表面。 |
| `F6845` | `MOV EAX,[ESP+30h]; CDQ`，续 `F684A` | 将当前物理行逆映射为原逻辑行序号，保留原色阶速度。 |
| `F6889/F6899` | 原读取前的 `CMP EDI,800 / CMP EBX,600` | 上界改为当前原生表面的真实宽高；原负坐标分支、JL 保留。 |
| `F6984/F698C` | 原写入前的相同两处 CMP | 同一物理上界；原 JGE 保留。 |
| `F69F6` | `CMP EDI,EAX; JBE F6870`，否则 `F69FE` | 原生列循环的包含末列上界映射。 |
| `F6A13` | `CMP EBX,EAX; JBE F6820`，否则 `F6A1B` | 原生行循环的包含末行上界映射。 |

全部补丁覆盖完整指令。三个被覆盖的条件跳转由 naked entry 按真实原目标续接，不把原相对位移抄进 trampoline。四处边界 entry 仅借用并恢复 EAX，CMP 的标志交给原 JL/JGE。其余 entry 复用既有 PUSHFD/PUSHAD 和对齐 cdecl 协议；shade 显式重放 CDQ。

目标来自原 `61BBB10` 主表面，消息矩形仍读原 `61A8CE4`；没有复制固定消息矩形或保存 UI 位置。逻辑画布仍为原生 800×600。映射与已有原生画布的四舍五入边界一致：

```text
edge(c,P,L) = floor((c*P + L/2) / L)
inclusive_last(c,P,L) = edge(c+1,P,L) - 1
logical_row(p,P) = floor(((2*p+1)*600 - 1) / (2*P))
native_row_ordinal = logical_row - native_message_rectangle.y - 4
```

反变换来自 `edge(c) <= p < edge(c+1)`，不是将物理行数直接除以一个取整比例。每个原逻辑行的全部物理像素沿用同一原色阶；原 `F684A..F6869`、颜色夹取和 `SDL_MapRGB` 均继续执行。密度为1时退化为原循环的坐标与行序号。

完整 `F6020` 的原生上移 blit、底行清除、行高、分页、消息来源和历史登记没有改变。业务状态仍为 HDA8，序列化格式与驻留桥 ABI 没有修改；已加载同一正式 HDA8 文件的进程可按既有兼容事务交接。已经被旧采样改写的像素不包含完整笔画，不能宣称热发布会凭空恢复它们；后续文字构建和原生重建使用修正后的路径。

## 交付状态

源码修改及原 PE 静态审查已完成。首批仅编译以供离线指令审查：请求 `a68966f7a2394bbab46829a426ca0d1d`，批次 `c85aadd5044d41db966c466841461b2b`。已读取对应队列结果 JSON 和完整批次日志，`Success=true`、`PublishRequested=false`；一次配置、一次增量构建，只重编 `native_raster_patches.cpp`，保留既有两处 SDL 函数指针转换警告。

编译后只读反汇编保存于 `build/analysis/message-gradient-adapter.asm`。该 DLL SHA-256 为 `5eca8500fa333867506a491889b474228c936e81d30482f2b5c4c74b46ec0261`。逐指令审查范围如下（末端地址不含）：

- `644F7D7D..644F7E01`：整数边界映射及其唯一依赖 `__divdi3`。
- `644F8380..644F8556`：五个循环操作数 helper；仅访问原生表面宽高、矩形 y 及保存的寄存器，不访问像素。
- `644F864A..644F874A`：九个 naked entry、寄存器/flags 恢复、三条明确条件续点及四条物理宽高比较。
- `64528FD0..64529290`：`__divdi3` 与 `__udivdi3`，均为整数叶函数。

上述调用闭包未出现 x87、SSE、MMX、AVX 指令；没有 Host 分派、SDL 调用或字形服务。九个 entry 没有编译器插入的函数序言；五个 cdecl 调用前仍按既有协议将栈对齐，POPAD/POPFD 后才执行覆盖指令对应的 CMP/CDQ。末尾 UD2 均位于无条件 JMP 之后，是 naked 函数的编译器终止填充，不是源码断言。

静态审查完成后，通过同一队列提交正式兼容热发布；没有继续修改源码，第二批为一次配置和一次无源码重编的增量构建：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter -Reload -TargetPid 364 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2517506103/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 正式回执 |
| --- | --- |
| 请求ID | `1ff5324e52ad4a87b35772a129956ef1` |
| 批次ID | `996b90201e06475b97efae6515529be6` |
| 队列结果 | `build/.compile-queue/results/1ff5324e52ad4a87b35772a129956ef1.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 批次日志 | `build/.compile-queue/batches/996b90201e06475b97efae6515529be6.log`，`Built target urwcn_adapter` |
| 正式事务 | `f5a6376c22824995b6b7e6acf218db42`，`publication-result.json success=true` |
| 正式更新 | `package/modules/urwcn_adapter.dll` 与 `package/release.json` |
| 新Adapter SHA-256 | `5eca8500fa333867506a491889b474228c936e81d30482f2b5c4c74b46ec0261`，构建件、正式件、清单与Applied回执一致 |
| 旧件归档 | `回收/20261110-151358-f5a6376c22824995b6b7e6acf218db42/package/`，保留原相对路径 |
| 旧Adapter SHA-256 | `a71c5165fa65c008b7d369d51253d7f4b2bfcbca79b6d5da8aa5cbdadf19e07a` |
| 运行时交接 | Windows PID `364`，`ReadyToPublish` 后 `Applied ... adapter:5eca8500fa333867506a491889b474228c936e81d30482f2b5c4c74b46ec0261:2`，`applied=true` |

只读进程表、Wine进程枚举与 `/proc/2944694/maps` 确认，该进程在发布前加载的 Adapter inode 与当前正式HDA8文件一致；没有向HDA7提交不兼容迁移。旧模块经已有 PREPARE 事务释放后，旧文件先移入回收目录，再复制正式位置，最后 COMMIT。根 `urwcn_launcher.exe` 的正常启动路径已经更新，无独立修复包。

已读取两批请求结果与日志、正式发布结果、正式清单以及新旧文件哈希。源码修改、产物编译、正式文件发布与当前进程兼容交接均已完成；未启动、关闭、重启或模拟操作游戏，没有运行测试、创建测试用例或断言。Applied 仅证明交接，不作为画面验收。
