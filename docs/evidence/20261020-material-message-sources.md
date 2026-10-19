# 共用消息中的材料名与剩余直接来源

仅使用当前 Windows 3.89 PE、静态反汇编和随游戏提供的资源，没有执行游戏或测试。

`windows_message_materials.inc` 接入 `451650` 和 `467A30` 的实际分支；原生物品记录、名称模式、选择条件与复制动作保持原值。前者先复制 descriptor 的 `+0x31` 字段（十六进制，即第 49 字节），随后可能改为 `unknown`，或由 `451770` 生成实际植物/食物名称。后者可以选择材料、完整物品名、去掉 ` cut` 的原生片段，以及 `4D4140/4D4190` 已经选出的末词/首词。

| 原生边界 | 来源 |
| --- | --- |
| `4516A1` | `451690` 已复制的 descriptor `+0x31` |
| `4516F8` | 原生确实选中的 `unknown` 常量复制 |
| `45173D` | `451770` 的完整来源图复制 |
| `467AAD` | 完整物品名进入本地 `EBP-40C` |
| `467AE7` | 材料名进入原生 `2130878` |
| `467B10 / 467B61 / 467BE9` | 原生特殊物品、材料为 tuntematon 时的特定物品、original 模式选中完整名称 |
| `467BDB` | 实际 `strncpy(dst,src,count)` 的完整间接调用指令 |
| `467C16 / 467C3F` | 原生选定的末词/首词进入原生材料缓冲 |

`467B10` 位于循环入口，只有原生计数 `ECX=0` 的首轮收集一次来源；保留 `467B22` 的真实回边入口。`467BDB` 是完整六字节 `FF 15` 绝对间接调用。宿主 `src/loader/hook_host.cpp` 将完整指令复制到原生 trampoline 后返回下一指令；这条绝对间接指令不依赖原位置。没有用 `467BE1` 的三字节清栈指令拼接后面的 `467BE4`，因为后者是其他分支的真实跳入点。

原生 `strncpy` 长度为 `strstr(full," cut")-full`，不会写入终止符；从原目标的 `dst+count` 起仍会保留旧内存。接入依据真实三个参数记录本次复制的完整字节身份：`src[0..count)` 加上原 `dst+count` 的终止字符串，不假设旧尾长度或缓冲已清零。语义子节点独立使用实际选择的肉类前缀查询 `material.cut`，外层节点保存完整待写字节身份；不修改原生结果。首末词使用独立 `material.word` 词库，不从已经翻译的中文全名截字。

`extract-settlement-material-inventory.ps1` 读取 `CONSTANT.OBJ` 的 400 条 `0xAC` 记录，输出 `settlement-item-material-fields.tsv`。原生读法见 `4B2BF5..4B2C1D`。`settlement-material-initializer-atoms.tsv` 对应 `4B1320/4B2B70` 的立即数与常量复制写入；`51E9D0` 还将皮毛动物称谓写入同字段。有限词库在 `values.materials.zh-CN.tsv`，逐词来源在 `settlement-material-word-sources.tsv`，译文生成源在 `generate-settlement-material-values.ps1`。这些清单不能替代对动态字段写者的逐项追踪。

全调用账的直接来源复核另发现八条被旧分类误标为 global-buffer 的常量：`5703D5/5703FE/570427/570450/571C88/5782BB/5782EB/57B39B`。实际均为 `MOV ECX, literal; CALL F6510`，已补到 `direct_dispatch.zh-CN.tsv`。`57AFC5` 实际显示当前地图文件标识 `A72B055`，其已确认写者选择 `BIGMAP/ZOOMMAP`；在 `57AFC0` 绑定为原标识来源，保留内部名称。

直接字串词库生成也改为使用与 `message_source_utf8` 一致的 UTF-8 身份。当前全部直接字串的非 ASCII 字节只有 `E4/F6`；旧生成器把 PE 原字节当键，会与显示入口已解码的芬兰语字符不一致。此修改仅涉及词库键的编码。

源码修改和词库生成不代表已编译或已正式发布。

调试命令 `wpdam` 的两个返回值也已区分：`56FE9D -> 50F5B0` 的输入复制到原生 `ESP+20B28`，`57894E / 57896E -> 55FC00` 从实际命令串提取 `[AD:...] / [BD:...]`；没有该字段时原生返回固定 `0`。这两次返回保留原输入身份，不按游戏词条猜译。第二次经 `578978 JMP 57899B` 与固定诊断文字共用消息调用，调用账已补记这一真实分支。
