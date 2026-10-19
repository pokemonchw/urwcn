# 原生菜单行源、注释和选择框度量

本记录仅来自原始 Windows `urw.exe` 反汇编和源码静态审查；未运行游戏、产物或测试。

`CFFB0` 的原生行 ESI 指向 `5F4EF10 + index*0xE8`。`D036F` 先检查该记录 `+0x64` 注释，`D039D..D03AC` 对原英文标签计字节，`D03BB` 用 `LEA ECX,[EDI*8+15]` 计算注释相对标签的宽度。后续 `D03C2 ADD ECX,[ESI+D0]`、`row+D4-1` 的 y 和 `D03C9→10E5A0` 继续属于原生布局/绘制。

现实现只在 `D03BB` 替换这个宽度操作数，采用同一 Menu source 的原完整行（含真实原 action prefix）解析后的当前语言度量。`D03C2` 之后原指令不变。注释本身在原行构造 `CF990` 完成处由原 `row+0x64` 绑定为 Menu owned original text source；snapshot 复制该中性资源，状态保存 source 字段。`D03C9` 借出这个 source 供完整原 `10E5A0` 消费，并进入两语言一致的原生文字 scope，不新增 Scene leaf 或独立文字节点。

软件选择函数 `D0650` 在 `5F54AAC` 原生模式中于 `D07FB` 执行 `LEA EAX,[ECX*8]`。现代选择函数 `D0850` 对应原生分支的度量位置是 `D0A49`，同样的七字节 LEA。两处刚结束原 strlen，EDX 仍是原 native row 地址 +1，可确认真实记录身份。实现解析同 Menu 的 neutral row source，替换 EAX 的宽度结果；原生填充矩形、描边、目标坐标转换和输入动作保持原流程。现代分支没有另设一套选择框几何。

`114680` 的 action label 路径不同：`1146AA` 从 label+1 找 `.`，`1146C6..1146C8` 的 ESI 是点之前的实际 keycap 字符数；背景 tile 和 cap 消费这一前缀。原 `1149D9..1149F9` 用完整借入标签的 dot 后 suffix 调用 `10E5A0`。因此不能把整译文宽度替换到 keycap 的 ESI。ASCII action prefix 保持原值，完整 suffix 字形/推进由其本次完整原生文字调用消费；`CFAF0` 的完整构造及已有真实度量扩展负责整行布局和命中。

Menu InputOwner 与 frozen source 仍分离：资源 snapshot 不携带旧 selection 写回，普通构造/消费者和语言重建解析同一 neutral source。Flow 重排 action 行时也必须将该原 action 的 label/annotation source 绑定到新的真实原生 row，不能只搬 native record bytes 而把 source 留在旧 index。

`CFAF0` 和现代 `CFD10` 都绕过 `CF990`：前者 `CFBD4` 写 action、`CFCE5` 写新 count；后者 `CFE39` 写 action、`CFF65` 写 count。两者只把原 `NOTEXTSPOT/TEXTSPOT` 标识写进业务 row.label；完整显示标签不是该标识。实现由两个 typed 完整构造器在普通 After 和 locale 完整构造完成后，以已确认 action/record 找到真实行，把构造器自身的中性完整标签交给 `native_menu_component::commit_row`。原 sentinel、action、原生尺寸和命中字段不变。注释仍从同实际 native row 的原始源接受。Flow seal 因而可以保存真实 action 的 label/annotation 资源，再随原生重排重新绑定。
