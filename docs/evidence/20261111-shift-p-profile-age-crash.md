# Shift+P 资料页闪退：年龄来源误用

2026-11-11。用户先报告按 P 闪退，随后明确“方向窗口出现前就退出，直接退出，只要按shift+p，游戏直接退出”。据此定位到游戏中的角色资料页，静态确认年龄消费者读取了本分支从未登记的创建期来源。源码修正不依赖新增保护、默认来源或忽略错误。

没有自行启动、关闭、重启或操作游戏，没有注入、模拟输入、执行测试、产物、测试脚本或测试用例，没有新增断言。只读用户已有日志、原 PE、源码和编译／发布回执；尚未取得本次崩溃EIP，不把静态缺陷修正写成已运行复现或排除其他错误。

## 正确命令与原生调用

原 PE为 Windows x86 3.89.1，SHA-256 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。下文是 RVA，[原始反汇编摘录](20261111-shift-p-profile-age-crash.asm) 是首选基址 `00400000` 的VA。

`17D716` 用输入字符减20h，`17D722` 读取 `17E3E8` 字节表，`17D729` 从 `17E344` 的DWORD表分派。大写P=50h，对应字节表索引30h；实际 PE中 `17E418` 的字节为11h，DWORD `[17E344+11h*4]` 为VA `57D915`。该分支 `17D91A→103970`，随后 `1039E3` 清ECX，`1039E5→E66B0`，明确是mode 0资料页。

此前日志末尾的 `PUSH_INFO/MOVE_NOTHING` 是普通小写p相关消息，文件没有逐条现实时间戳，不能用来确认用户本次Shift+P的分支。此前沿搬运消息排查未取得异常地址；该方向不再作为本次故障路径。首次记录和两批Loader诊断发布保留在[前一记录](20261111-p-command-crash.md)，不是本次业务修正。

## 已确认的无效来源读取

`E66B0` 在 `E66E5` 将原mode存入EDI。共同的 `E67AF→10D0` 年龄格式调用与后续 `E680E→10E5A0` 文字调用具有两套原生输入：

| 原模式 | 实际年龄构建 | 原 E67AF参数 |
| --- | --- | --- |
| mode非零，创建／属性确认 | `E678D` 读取起始年龄，`E6795` 选择 `You are %d winters old as you start your journeys and adventures.` | 栈0=原显示数组、栈1=`%d`模板、栈2=整数年龄 |
| mode 0，游戏中的资料页 | `E679C→E6610` 生成实际年龄／冒险天数，`E67A2` 选择 `You are %s.` | 栈0=同一原显示数组、栈1=`%s`模板、栈2=E6610返回的英文字符串地址 |

旧 `windows_profile_extras.inc::dispatch_windows_profile` 在 `wp_attribute_age` 的After只处理 `EDI!=0`，调用 `translate(profile_start_age, ...)` 并登记该来源。mode 0不登记该来源，却在共同的 `wp_attribute_age_text` 无条件调用 `note_source_for_consumer(profile_start_age)`。

`native_component_binding.cpp::note_source_for_consumer` 对 `{current native root, component}` 做 `fields.find(...)->second`，没有匹配时解引用end。`E66EE→1127C0` 已为这次资料页建立新root，之前创建页的来源不能成为这个新root的合法来源。mode 0从未登记 `profile_start_age`，所以普通打开资料页的年龄消费者本身就是一条确定的非法读取路径。此问题发生在页面构建期间、原等待输入之前，与方向窗口和按键选择无关。

此外，两模式的栈2分别为整数与字符串指针；不能简单让mode 0也走起始年龄的整数转换。用原文作默认值、跳过年龄行或在find失败时继续绘制均不修正这处语义错误，本轮没有加入这些处理。

## 三个真实年龄生产者与修正

`E6610` 的三处实际sprintf都保留原英文缓冲和分支：

| 原CALL | 模板与实际参数 |
| --- | --- |
| `E6658→10D0` | `%d winters old, and have lived %d days of adventuring life`；栈2为年龄，栈3为原天数字段减一 |
| `E6678→10D0` | `%d winters old, this being the first day of your adventures`；原天数字段等于1时覆盖前一结果，栈2为年龄 |
| `E6698→10D0` | `%d winters old, and have lived one day of adventuring life`；原天数字段等于2时覆盖前一结果，栈2为年龄 |

`windows_profile_extras.inc` 新增独立 `7860..7862` Hook ID，只在这些真实调用After将已完成的英文生产者及实际typed整数绑定到其原缓冲。没有在Mod里重算年龄／天数、遍历存档、重做原模式分支或改写原E6610环形缓冲。

新增 `windows_profile_age.inc` 在共同 `E67AF` 的After、确认原EDI=0时，用当次实际 `You are %s.` 模板和栈2的已绑定年龄生产者构建完整语义句，登记 `profile_current_age=B49`，只把中文投影写入原本就用于显示的0x400字节局部数组。`module.cpp::resolve_display_text` 让这个明确字段复用既有完整消息表达式解析和编码；不会转入物品截断。四个 authored资源在 `translations/messages_embedded/values.profile-age.zh-CN.tsv`，同步到源 `catalog/zh-CN/messages.tsv`，没有运行按旧版字面量地址工作的全量生成器。

共同的 `E680E` 消费者继续按原EDI选择自己这条原生构建分支已登记的字段：mode 0是 `profile_current_age`，非零仍是 `profile_start_age`。没有按来源是否缺失选择替代值。两语言都记录同一中性来源；英文显示消费原句，中文显示消费实际模板、年龄和天数。

`E67F6` 的完整字宽扩展、随后的原除二／减法居中以及 `E680E` 完整绘字消费同一个原局部数组。继续使用当前真实密度的原生目标、现有即时字形接口与原阴影参数。布局、按钮、鼠标命中、背景、缓存及其生命周期都保留原函数；没有添加固定位置、页面快照、延后文本重放、通用像素扫描、裁剪补丁或新UI。Host ABI、Active结构及HDA8状态布局未改变；新B49只增加原资料字段的语义身份，既有枚举值不移动。

## 审查范围及待整改

这次闭合mode 0、非零模式及E6610全部三种实际模板的构建到消费关系。先前[属性页语言重建记录](20261110-profile-language-reconstruction.md)主要修正mode 1的重建与中文姓名，不能作为mode 0年龄来源完整的依据；该漏项在本记录中明确整改。

既有 `native_ui_scene.cpp:12` 的Child／Container、`native_component_binding.cpp::construct`／`native_component_model.cpp::paint` 的历史组件集合、`native_renderer_component_binding.cpp` 的Owner.children仍待完整退役；独立署名排版、About按钮位置例外和 `windows_inventory.inc::native_text_limit` 仍按前一审查记录待交回原生。此次资料年龄来源不使用这些集合遍历重放页面，不以已编译／发布证明它们合规。

## 编译与正式发布

业务修正源码与四条资源已保存。执行统一根入口 `.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Publish`。所属批次运行期间没有继续修改请求范围源码；只生成与发布产物，没有运行它们。

| 项目 | 实际回执 |
| --- | --- |
| 请求 | `ede516c21a844d45a563b1e899a68a61` |
| 批次 | `e51662e4ee8a458885ca237945dd67a4` |
| 请求结果 | `build/.compile-queue/results/ede516c21a844d45a563b1e899a68a61.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=false` |
| 完整日志 | `build/.compile-queue/batches/e51662e4ee8a458885ca237945dd67a4.log`，已完整读取；一次配置及一次增量构建，Adapter和Catalog均编译完成；警告来自既有函数指针转换、未使用函数／参数、缩进和初始化项 |
| 正式事务 | `e26692be43ca4c26b88fede938659c7f`，2026-11-11 12:44:27（Asia/Shanghai）完成 |
| 发布回执 | `build/mingw-x86/stage/e26692be43ca4c26b88fede938659c7f/publication-result.json`，`success=true`、`runtime_requested=false` |
| 正式更新 | `package/modules/urwcn_adapter.dll`、`package/modules/urwcn_catalog.dll`、`package/catalog/zh-CN/messages.tsv`、`package/release.json` |
| 旧件回收 | `回收/20261111-124427-e26692be43ca4c26b88fede938659c7f/package/`，四件均保留原相对路径 |

已只读计算正式件、构建件／源词库和回收件的SHA-256；正式清单与新文件一致：

| 文件 | 新正式件 SHA-256 | 旧回收件 SHA-256 |
| --- | --- | --- |
| Adapter | `d8d7f180b550cf591e0fb60bcd7156a76d0069ffa4360c48fcff48f974bc90c0` | `ec17fb9d1dceefd74d4469ba77353fc76f07b090920ff36ebf1455ea3685bcc3` |
| Catalog | `a41beaf9004f78b1876d312f866fa5c39605f75d8ee49570cade9fe1d14b8083` | `cd5ea4f63e239691176f6bf1e38a1b4c232a0c9c5f8182eb80aacefbfa8e6719` |
| messages.tsv | `7e4b6fbc7fb3314faf07c7e63f2b8277b447ad574912d66c3e9a9db347a72cae` | `0cfbe2f2a4b78b417eda099b6017dc516c3af246853b4451c0078d195ce27385` |

此前12:37:08发布的Loader仍为 `94a86b0c97e7a8ea35f728b8f9f1d6465d4f5c7b2eaebc4093d7864ab3255434`；该诊断发布与本次年龄来源业务修正明确分开。游戏在发布前已退出，本批不请求Reload，不宣称取得Applied，也没有自行重启游戏。根启动器下次正常使用时加载正式修正；行为与画面尚未运行验收。
