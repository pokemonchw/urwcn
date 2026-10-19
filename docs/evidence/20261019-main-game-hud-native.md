# 主游戏界面汉化

2026-10-19，UnReal World 3.89 / Steam Build 25939378。目标 EXE SHA-256：`e0b15bbbe16ffcd95d4ab61f08fe95dea4b95ebe1b3de428dae1d9477a9710d9`。以下地址均为 RVA。

## 源码覆盖

截图右侧的负重、惩罚、疲劳、伤势、饥饿、失血、合计、口渴、营养、体温、精力，以及原生选出的状态、无惩罚提示、行动、朝向、速度、手持武器／工具标题、指令、重复和帮助标签接入中文。原数值、百分比、重量与速度单位、人物姓名、ASCII 键帽和输入动作保持。

上方及下方接入季节、月份阶段、时段、文化地域及方位、地名英文释义、日期、比例尺和地图种类。词素来自原生 `0A3E70` 的256个前缀和55个后缀槽，按原生 `0A8F50` 下划线连接规则组合；例如 `Hirvaskangas "Stag heath"` 显示为 `Hirvaskangas "雄鹿荒原"`。专有地名保持，未改变内部英文词表、命名选择器、存档或地图数据。

`sdk/text_services.h` 新组件使用 `0x10000..0x10005`、`0x10100..0x10108`，避开并行开局页的 `0xC00` 范围。Catalog 显式读取原 main_menu 词库与新增 `hud.tsv`、`world_hud.tsv`；内容版本散列同时包含新词库。Semantic 不接收位置、表面、裁剪、页面快照或缓存。

## 原生文字与测量

- `hud_native.inc` 仅登记原生调用身份。`F8E84`、`F99B0..FA27E`、`10376C/10385B` 等原生 surface 文字调用借用当次译文，沿现有 `10E5A0 → 10DDB0` 即时绘制；`10E700` 更新原生光标。
- 五个 `FEE50` 惩罚栏调用保持原有数字。`FEEB2` 将原 `strlen×8` 替换为真实字宽，后续原生减法、除二和坐标计算照常执行。
- `090270/0902C8/09031A/090588/09076B/09083D → 10E910` 借用完整语义。`10E9FB` 使用当前行与词元真实字宽，`10EA74/10EAF8` 提供行宽；原生分词、折行、居中和行距保持。`0907B3` 只替换比例尺显示副本与度量，并保留原 CDQ/SUB 算术。
- 月份在 `1037BF → 162300` 构建边界翻译，`103816 → 10EB40` 使用既有原生段落度量。文字传输编码避开原生单字节重映射值，不将 UTF-8 直接交给按字节索引的字形循环。
- `F9660/FA394 → 114680` 保留原键帽和分隔符，仅在原生后缀调用翻译。`F92A5 → 1157B0` 是 mode 3 左对齐标题，未添加居中或按钮几何。

## 头像面与高清绘制

行动、朝向和速度实际路径是 `FAA30 → 111560 → 10E260 → 10DE90`。`111560` 不是 `115560`；后者属于另一原生资源函数，静态记录已更正。

新增 renderer 文字操作读取实际 renderer scale，生成对应物理密度字形，当次创建、提交和释放临时字形纹理；不改变原生 target、viewport、clip，不保存绘制位置或延后重放。颜色使用原生 RGB，alpha 固定为原路径的不透明语义。

`10C3B1` 的原生头像 surface 分配按输出密度扩展；`FAA4B` 在首次借用 renderer 前设置真实比例。已有旧目标在此原生整面重建边界迁移 surface、software renderer 和两个所属原生图片纹理。它不拷贝旧 UI 像素，不重新执行游戏动作；之后由原生函数填充、绘图和复制。10个驻留 gateway、NGT1、Active 布局、HDA3 与 Host ABI 1 均未变。

速度原本是静态标题／单位与单独数字两次文字调用。现在 `FAE38` 提供“速度：”（英文模式为 `Speed:`），`FAEFF` 借用原生最终数字字符串并带上原单位。保留两次原生位置、边框、数字前导空格和颜色；不重新计算速度、不搬动数字位置、不靠固定空格安置单位。

## 刷新边界与范围

语言选择仍由既有 `Shift+F10` 控制。新语言在对应原生组件下一次构建时使用。原生 `-2` 输入唤醒不能证明静态 HUD 重建；`FA2A0` 清理游戏/UI状态，`F9200` 写盾牌状态位，`FAA30` 的速度查询含随机数路径。因此未新增整页强制重绘，不将这些函数作为无副作用刷新入口。旧缓存即时刷新仍待确认，详见 `hud-refresh-static.txt`。

本次覆盖截图界面的标签与已确认状态，不声称已汉化任意物品名称、动作消息或事件日志。它们的业务字符串不是本次固定标签映射的输入。

既有不符合约束的内容仍记录为待整改：`docs/hot-reload.md` 中的 DisplayPlan/行槽历史正文，以及 `src/loader/host.cpp`、`src/loader/hook_host.cpp` 中已记录的错误透传与事务失败语义；影响和位置继续见 `20261019-implementation-correction.md` 与开局页记录。本次不采用旧布局/重放方案，也不将编译或发布视为这些问题已整改。

## 交付记录

源码、统一队列编译与正式发布均已完成。并行开局页修改保留在共享源码中，交付包含这些修改。

- 入口：根目录 `build.ps1 -Module adapter,catalog,semantic,render,main_menu -Toolchain MinGW -CMakePath D:\workspace\uwcn\.toolchains\x86\w64devkit\bin\cmake.exe -CompilerPath D:\workspace\uwcn\.toolchains\x86\w64devkit\bin\g++.exe -BuildDirectory D:\workspace\uwcn\build\mingw-x86 -PackageDirectory D:\workspace\uwcn\package -Publish -TargetPid 0`。
- 请求 `f008c0b0630d4758bfa8a32c61051963`，批次 `bb31dbf3f3894011a0ee0da1e1ee6620`，2026-10-19 08:37:36（Asia/Shanghai）完成。对应 results JSON 与 batches 日志已读取，Success 为 true；一次配置、一次增量构建，五个目标均完成。日志保留既有 `SDL_GetRGB` 函数指针转换警告，无编译错误。
- 正式发布事务 `c2785e5465ef495ca21aaa2c03d123f8`。本批次替换 `package/modules/uwcn_main_menu.dll`、`package/modules/uwcn_semantic.dll`、正式 profile 和 `package/release.json` 四件；旧四件先移入 `回收/20261019-083736-c2785e5465ef495ca21aaa2c03d123f8/`，保留原相对路径，归档文件已确认存在。
- Adapter、Catalog、Render 及新增词库已由此前并行批次 `bb5482e7791a4d34a70c869f1c00d807` 发布，本批次产物与正式文件一致，未重复替换。最终 `package/release.json` 的十二项正式文件 SHA-256 已逐项读取核对，均一致；启动器对应项目根目录 `uwcn_launcher.exe`，其余文件对应正式 `package/`。
- 发布前读取到游戏已无运行进程，因此本批次采用离线正式发布，没有请求 Reload，也没有运行时 Applied 回执。文件交付成功不代表已进行游戏运行或视觉验收。

未自行测试、启动游戏、注入、模拟操作或运行产物；没有测试脚本、测试用例或断言。仅进行离线静态分析，编译只生成交付文件。
