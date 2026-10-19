# 启动文字之前的真实 Root 构造

仅静态读取固定 Windows PE 与当前 Root Hook；没有运行、编译、测试或模拟输入。地址均为 RVA，PE 基址为 `400000`。

正常 main 在 `1807D8` 调完整 graphics/init `117400`，其 `1179B9` 调原 `CreateRGBSurface`、`1179C2` 将返回对象存入共同 main target `61BBB10`。原创建动作本身不是这里的 Root 背景 source。

graphics/init 返回后，main 的 `18083D` 无条件调用完整 `F6180`。该函数的实际顺序为：

| 地址 | 原生行为 |
| --- | --- |
| `F6190` | 设置 `61BBA5C=1`，抑制随后 upload/present。 |
| `F619A` | 无条件完整 `10B9F0` clear。 |
| `F619F` | 原 `E0760` 启动画面。 |
| `F61EE` | 第二次无条件完整 `10B9F0` clear。 |
| `F61FC/F6209` | 原图像 `112980` 与 heading `F8F80`。 |
| `F6258` | 恢复 `61BBA5C=0`。 |
| `F6262` | 第三次无条件完整 `10B9F0` clear。 |
| `F6267..F6274` | 原 cookie 与完整返回。 |

`10B9F0` 在 `10BA00..10BA17` 将原 `1DDAB0` rect、实际 `61BBB10` 与 color=0 交原 FillRect。`10BA20` 才判断 `61BBA5C` 是否跳过后面的提交，因此第一、第二次 suppress=1 仍执行完整 opaque 填充。当前 Root 的 `5304/10B9F6` source 构造与 `native_clear_filled(10BA1D, actual main target, result=0)` 提交已经覆盖这条共同边界。

main 只有等 `F6180` 返回才从 `180842` 设置后续 image 参数，`18084B→112980` 画启动 logo，再到 `180894→10E5A0` 的 startup heading。两者之前已存在最后 `F6262` clear 成功提交的 Root，无须把 logo 误当全屏背景，也无须新增缺省 Root 或 surface 像素反建。

这是正常原生调用顺序和已接 Hook 的静态闭合；不声称原生 SDL 失败时仍完成了背景，也不新增失败兜底。编译与发布由根代理统一处理。
