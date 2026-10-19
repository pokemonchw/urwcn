# Menu 缓存源与输入对象分离

本轮只修改源码并静态核对原生字段及调用关系，没有运行游戏、测试、编译或新增断言。

## 问题

原 `native_menu_model::snapshot` 冻结了完整原生 `190h` header、`5AA0h` rows 和中性文本绑定。旧 `activate(snapshot)` 会把这些原生字节全部装回共享范围。即使缓存文字源正确，语言切换或 SDL cache materialization 仍可能把快照时的选择、滚动或输入字段写回当前视图。SDL 像素缓存不拥有这些输入状态。

## 实际模型

每个 Menu 实例新增纯 `input_owner` handle。普通 `CF790` 构造的实例拥有自己；缓存 snapshot 保留冻结的中性文字资源与 style，并持有同一个真实逻辑 input owner 的引用。快照不成为新的输入对象。

`activate(source)` 先解析 `input_owner(source)`，捕获当前实际输入，再激活该真实对象。`capture_into(source)` 同样只更新真实对象；因此普通输入变化及原生布局结果不会修改缓存快照的中性源，也不会被旧快照覆盖。

`native_menu_component::paint(source)` 仍执行完整 `CFFB0`。调用期间的同步 `painting_source` 只用于 title/row 资源解析；原生函数读写当前真实 Menu 及其最新输入。调用结束后恢复调用者真实输入对象。这个临时 source handle 不序列化，也不跨等待。

snapshot 对逻辑 input owner 持有一次引用，释放 snapshot 时释放该引用；普通 self owner 不持有自引用。序列化为每实例增加一个 `u32 input_owner`，与原模型和资源一起保存，恢复时不重复增加已保存引用。

## LinkTextFlow 的对应输入所有权

Flow 的原生 link 表是 row index 到英文 link ID 的映射。仅让 Menu 使用最新 selection、同时从冻结 Flow.links 取 ID，仍会在不同语言的链接行重建后错配。

Flow 因此也持有纯 `input_owner` handle：普通对象 self，snapshot retain 同一逻辑 Flow。冻结 records、seed 和语义资源供原生 `3D820` 重新布局；当前 link 表与 Menu 输入属于真实 owner。选中项从当前 owner.links 解析为英文 ID/action，然后由原生重建后的表定位。没有复制过期 selection 或重放旧 link rectangle。Flow 每实例序列化增加一个 `u32` owner。

Scene 对 view 身份的比较须通过 `native_menu_model::input_owner` 归一化；其 source handle 仍保留自身引用及冻结资源身份。完整 native `CFFB0`、`3D820`、`CFD10` 和 `CFAF0` 消费者保持原有布局和输入管理职责。
