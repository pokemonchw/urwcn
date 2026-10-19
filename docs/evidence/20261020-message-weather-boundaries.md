# 天气预报的完整原生文本来源

静态来源为 `settlement-weather-forecast-source-ghidra.c`（587AB0）、`settlement-weather-description-ghidra.c`（587300）、`build/windows-sync-pe.asm` 和安装 PE 的只读字符串。未编译、测试或运行游戏。

## 587300 的全部描述分支

此函数通过 582900 向原生 stringstream 追加实际选中的常量，581800 返回完整 std::string。反编译器未显示第四个参数，原始汇编在 587483 明确读取 `[EBP+14]` 并据其符号选择 raining/snowing。

| 原生参数 | 实际分支 | 字符串 VA |
| --- | --- | --- |
| `[EBP+0C] <= -8` | much colder than | 5DCE94 |
| -7 到 -5 | colder than | 5DCEA8 |
| -4 到 -2 | slightly colder than | 5DCEB4 |
| -1 到 1 | about the same as | 5DCECC |
| 2 到 4 | slightly warmer than | 5DCEE0 |
| 5 到 7 | warmer than | 5DCEF8 |
| >= 8 | much warmer than | 5DCF04 |
| 所有温差 | ` now. ` | 5DCF18 |
| `[EBP+10] == 0` | `It won't be ` | 5DCF20 |
| 非零 | `It will be ` | 5DCF30 |
| `[EBP+14] >= 0` / < 0 | raining / snowing | 5DCF3C / 5DCF44 |
| `[EBP+10] < 0` | 不追加标点或强度词 | 5874A9、5874C0、5874DA 直接到 5874EF |
| == 0 或 6 到 12 | 句点 | 59285C |
| 1 到 5 | ` a little.` | 5DCF4C |
| >= 13 | ` a lot.` | 5DCF58 |

由这七种温差、五种降水强度及雨/雪两类构成 70 个完整描述。`generate-settlement-weather-inventory.ps1` 从 PE 读取实际英文常量，枚举上述已确认语法并写出 70 条 `weather.description` 精确词条及证据清单；不枚举任意数字或读取游戏运行状态。负数分支原生没有最后的标点，词条单独保留该区别。

## 587AB0 的两种原生拼接语法

函数先由原生业务计算天气参数。文本部分只存在以下两种结果：

- `[EBP+14] < 12`：587E1B 返回描述；587E31 追加 `5DCF60`（白天），587E3A 追加描述，587E46 追加 `58C8C0` 的一个空格。随后 587E70、587E86、587E8F 追加夜间描述。
- `[EBP+14] >= 12`：先经 587E70、587E86、587E8F 追加 `5DCF88` 的夜间描述，再经 587EC3、587ED9、587EE2 追加 `5DCFB4` 的明天描述；明天前缀本身包含一个开头空格。

587F1D 将 stringstream 提取到 std::string，587F57 移入 `[EBP-40]`。587F72 读取 capacity 到 EDI；587F75、587F78 准备短字符串地址与长字符串指针；587F7B/587F83 选择实际存储；587F86..587F92 原生逐字节复制到 AA41EE0。

新模块只在该最终复制边界读取已经完成的英文表达式，按上述两种精确语法拆为“时间前缀＋完整有限描述＋原生间隔＋时间前缀＋完整有限描述”的中性源图。描述本身通过完整精确词条翻译，不根据参数重新判定温差、雨雪或强度，也不从中文字符串切分。

英文描述最大 54 字节。白天/夜间前缀为 39/41 字节，明天为 34 字节；完整英文结果上界为 `39+54+1+41+54 = 189` 字节（不含 NUL）。该函数没有任意输入文本。两段中文译文、两个五字时段前缀及原生间隔同样是有限文本，最终显示继续使用 F6510 已接入的原生循环及按实际编码长度分配的文本工作存储。

## 两处挂钩和生命周期

| ID | VA / 长度 | 原指令 | 作用 |
| --- | --- | --- | --- |
| EF00 | 587F75 / 6 | `LEA EDX,[EBP-40]; MOV ECX,[EBP-40]` | 在无中间调用的原生复制前，把完整源图及实际英文身份绑定到 AA41EE0 |
| EF01 | 521D8F / 5 | `LEA EDX,[ESP]; SUB EDX,EAX` | 587AB0 返回后，把同一源图绑定到本次栈副本，随后 521DA4 调用 F6510 |

两处覆盖完整指令，没有 ESP 调整或相对控制转移；完整反汇编未见跳入覆盖区间内部的直接分支。587F86 和 521D94 的循环回边均在覆盖范围之外；特意没有跨这些入口。处理器不修改 NativeFrame，复制及原生 flags 生产仍由原指令执行。

该模块无待续调用帧、无可变全局状态，无新增 save/restore 数据。源图保存在已有 `windows_messages::values` 的 owner/英文身份绑定中，沿用既有状态序列化，不改变 HDA7。接入只需 include、append_hooks 和 dispatch；`values.weather.zh-CN.tsv` 使用已有 values 文件扫描。

587AB0 另有 539EB0 对话调用者。本模块在共同返回缓冲绑定中性源，但不修改它的英文缓冲或对话 UI；此次闭合的共用消息消费者为 521D8A → 521D8F → 521DA4。
