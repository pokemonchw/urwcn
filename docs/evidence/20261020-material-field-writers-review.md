# 原生3.89材料字段和尸体名称静态复核

本次仅阅读反编译、反汇编与源码，未编译、测试、运行游戏或注入。

## 字段所有权

物品descriptor长度0xAC；+9是显示基础名称，+0x31（十进制49）是材料/植物备用名字段。不能把两个偏移相混。

- CONSTANT.OBJ的400条初始化记录与4B1320/4B2B70的静态覆写已分别输出`settlement-item-material-fields.tsv`、`settlement-material-initializer-atoms.tsv`。
- `settlement-material-field-writers.tsv`列出精确全局地址refs。DATA引用不是写入证明；436BD3是把5915289作为输入传4BC880，不是copy出口。404E8B同样传给4BDF10作查找，485D91等是字符串比较，57C69A是诊断参数，57C85C是strstr参数。
- 4BCF90的4BD1F5→55FC00读取外置flora `[NAME:]`，4BD1FA后复制至5915289。该字段来源由item.alternate词库处理。
- 51CEC0从输入creature record+8读取类名，最长截为25字符，构造`%s-skin`写+9并将原类名写+0x31。不是proper name +0x30，也不调用4AD4F0。证据`settlement-carcass-descriptor-ghidra.c`。
- 51E9D0复制输入皮革descriptor+0x31（C的acStack_f3相对local124为+0x31），再写新descriptor+0x31，构造`%s leather`/`%s fur`写+9，ID19D/19C。不能以已加`-skin`的+9作为材料名。51E140、51E7B0后续加工名称保留该材料字段。
- 434500为肉块构造器：434548 sprintf(`%s cut`)写+9，ECX原文同时copy至+0x31，category7、ID500/0x1F4。完整C与9个调用者在`settlement-meat-name-builder-ghidra.c`。

## 肉块的全部九个输入来源

| CALL | ECX真实来源 |
| --- | --- |
| 416E45 | 默认creature表61FA328（record+8）复制到ESP+C8 |
| 4AF90B、4AF9B1、4B01D0、4B0276 | 完整creature record复制后的+8 |
| 543047 | 完整creature record复制至EBP-D58后的+8 |
| 421D2D | 6151400 + index*568 + 8 |
| 4C2480 | 传入完整creature record复制至EBP-570后的+8 |
| 51CC66 | 51CAB9调用4AD4F0 flags=1，51CAC0复制至ESP+3FD0；flags1提前返回human或class，绕过known、proper、young分支 |

所以这些肉块名称不包含玩家输入的动物专名。皮革截取只针对class字段，不能把NPC25截断同完整4AD4F0展示语法混为一谈。

## 材料hook控制流审查

4516A1、4516F8、45173D、467AAD、467AE7、467B61、467BE9、467C16、467C3F的覆盖范围为完整原生指令；没有ESP调整。两处原方案需要修改并已反馈根代理：

- 467B0D跨过回边目标467B10；改挂467B10的完整7字节MOV，只有ECX==0记录copy源。
- 467BE1跨过外来join467BE4；改挂467BDB完整6字节strncpy IAT CALL，inline_before读取实际dest/source/count。

strncpy的count是strstr(full," cut")-full，没有复制NUL。实际待写英文身份必须是`string(source,count)+string(destination+count)`，不能只覆盖一个按当前strlen构造的std::string并假定后面终止。根代理已采用实际字节身份，并将语义叶限定为确切prefix；语义lookup须包在concat中，避免bind_copy覆盖叶的原文键。该审查不代替materials模块对其词库完整性的单独台账。

## QST读入hook修正

55751E和57965D原覆盖包含ADD ESP，且后者还跨579660失败分支join。现改为557518/579657完整fclose IAT CALL的inline_before：fread已经返回、EDI或ESP+B1BC仍是实际记录，原fclose继续执行，未重放任何游戏业务。
