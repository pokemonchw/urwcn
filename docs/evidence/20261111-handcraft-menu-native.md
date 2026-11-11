# 手工制作菜单漏译

日期：2026-11-11。用户截图中 `HANDCRAFT OPTIONS`、13个制作分类和 `ESC.Cancel` 仍为英文。本次只做截图、源码和原生反汇编静态审查，没有启动游戏、模拟操作、运行测试、编写测试用例或断言。兼容业务热发布沿用用户已授权的统一事务。

## 原因与原生边界

这些文字已经存在于 `translations/messages_embedded/values.menu-echo.zh-CN.tsv`、源词库及正式词库，但 `windows_message_menu_echo.inc` 只向消息回显提供相应语义。`modules/adapter/module.cpp::bind_menu_consumer_source` 之前仅为 `HELP AND GAME OPTIONS` 接通了同一原生菜单的标题和动作后缀消费者，没有包含制作菜单。词库存在不等于实际菜单已接入。

静态来源为 `build/analysis/windows-3891-native-full.asm`；原游戏PE及本机正式游戏文件的SHA-256均为 `c6ed73642c1b1cb1f86b818c7586224398c2f0554f6114ced31bc40ff071806d`。相关原始VA指令摘录保存在 [原生调用证据](20261111-handcraft-menu-native.asm)。下表地址使用RVA。

| 原生边界 | 已确认职责 |
| --- | --- |
| `47B00` | 游戏构建真实制作分类，原行表 `619F988`，stride `20C`，动作在 `+C8` |
| `47B94` 至 `48254` 的13次 `10D0` 调用 | 将原分类与实际单字母键写入原行，不改写内部动作 |
| `48324` | 游戏条件成立时添加“模组手工制作选项”，仍消费同一完整标签译文 |
| `48376 → 1002B0` | 以 `HANDCRAFT OPTIONS` 为标题打开原生菜单 |
| `1003B8 → CF790`、`10042B → CF990` | 创建kind 6菜单并复制实际原始行，真实菜单记录 `5F4EF10`，stride `E8` |
| `10048C/10049B → CF990` | 游戏创建空分隔行及动作27的 `ESC.Cancel` |
| `100525 → CFFB0` | 完整原生菜单绘制，背景、行距和排列由游戏管理 |
| `D027F → 10E5A0` | 菜单完整标题消费者 |
| `D031F → 114680`、`1149F9 → 10E5A0` | 原生键帽解析及完整点号后缀显示 |
| `D07FB/D0A49` | 已有完整行文字度量接口，服务原生选择框和命中 |
| `100640 → D1120`，返回 `100645` | 原输入循环及已有菜单语言重建入口 |

## 修改

在 `modules/adapter/module.cpp::bind_menu_consumer_source` 的既有帮助菜单条件中加入完整英文标题 `HANDCRAFT OPTIONS`。两者使用已经确认的同一原生构建、绘制和缓存路径，没有新增Hook、ABI字段或持久化状态。

实际标题绑定 `message_value/menu.title`；动作行只绑定真实点号后的完整标签到 `message_value/menu.label`，保留每一行原键帽前缀。已有资源直接复用：

| 原键 | 原分类 | 中文 |
| --- | --- | --- |
| A | Arrows | 箭矢 |
| B | Building | 建造 |
| C | Clothes | 衣物 |
| F | Fishing | 钓鱼 |
| H | Hafting | 安装柄杆 |
| L | Lumber | 木材 |
| T | Trapping | 设陷阱 |
| R | Transport | 搬运 |
| O | Containers | 容器 |
| U | Utility articles | 日用器具 |
| Y | Tying equipment | 绑扎用品 |
| W | Weapons | 武器 |
| X | Textilecraft | 纺织 |
| ESC | Cancel | 取消 |

表格仅记录静态语义证据，不进入代码，不作为行号、布局或输入映射表。代码按当前原生行本身绑定完整标签，不按上表顺序生成界面。

中文沿已有中性文字资源、编码、完整字宽和原生叶字形调用绘入当前原生目标，复用现有已确认的实际高清密度接口；未将UTF-8直接交给ASCII字节宽度路径。原生UI继续管理居中、行距、选择框、命中、背景、缓存和重绘；没有坐标表、独立DisplayPlan、像素跟踪或文本贡献重放。

已打开菜单及语言切换使用既有 `native_parent_cache_language::menu` 对 `100645` 的完整父界面与菜单构造路径，继续消费实际header/rows并保留原选择、原输入和业务动作。未重入制作动作，不要求用户退回界面或重启。

## 既有待整改项

- `modules/adapter/native_footer_component.cpp:58` 起的 `paint_text`（特别是79—88行）仍由Mod计算署名宽度、横坐标、图像与段落间隔，影响主菜单汉化署名，违反原生布局所有权要求，待整改。本次未调用或扩展此路径。
- `modules/adapter/native_ui_scene.cpp:12` 起的 `Child/Container` 历史组件集合及其序列化仍保留，完整退役待处理；不能将编译或交付回执视为这些结构已经合规。本次未增加菜单布局或文字贡献，也未遍历其集合重放文字。

## 编译及正式发布

本任务修改完成保存后冻结 `module.cpp`，与同目录日志页任务共享一次 `adapter,catalog` 编译及正式热发布，由日志页任务持有并等待统一队列请求。本任务不重复提交同一份已保存修改。当前游戏只读枚举为宿主PID `3385055`、Windows PID `360`；Proton前缀为 `/home/lulika/.local/share/Steam/steamapps/compatdata/2735482958/pfx`。

源码修改、一次队列配置及增量编译、正式文件替换与运行时兼容交接均已完成。本次菜单本身无需新增词库键，词库及适配新增项属于共享批次的日志页修改。编译保留20条既有函数指针转换、extern初始化、未使用项和缩进警告，无编译错误。

统一编译入口由同目录日志页任务执行，本任务共享同一份已冻结源码的结果，没有重复入队：

```text
.toolchains/powershell/pwsh -NoLogo -NoProfile -NonInteractive -File ./build.ps1 -Toolchain MinGW -Module adapter,catalog -Reload -TargetPid 360 -WinePrefix '/home/lulika/.local/share/Steam/steamapps/compatdata/2735482958/pfx' -WinePath '/home/lulika/.local/share/Steam/steamapps/common/Proton - Experimental/files/bin/wine'
```

| 项目 | 已读取的回执 |
| --- | --- |
| 请求ID | `4098da4a293140d8b9697622da12481c` |
| 批次ID | `6927a43e04494e73a3aa30a86d71ac7c` |
| 请求结果 | `build/.compile-queue/results/4098da4a293140d8b9697622da12481c.json`，`Success=true`、`PublishRequested=true`、`ReloadRequested=true` |
| 完整批次日志 | `build/.compile-queue/batches/6927a43e04494e73a3aa30a86d71ac7c.log` |
| 发布事务 | `c3b60885ec374109a26c208eac78d4ac`，2026-11-11 17:09:58（Asia/Shanghai）完成 |
| 发布结果 | `build/mingw-x86/stage/c3b60885ec374109a26c208eac78d4ac/publication-result.json`，`success=true`、`runtime_requested=true`、PID360 `applied=true` |
| 正式替换 | `package/modules/urwcn_adapter.dll`、`package/catalog/zh-CN/messages.tsv`、`package/profiles/urw-3.89.1-steam-26139145.json`、`package/metadata/build-hour.txt`、`package/release.json` |
| 旧件归档 | `回收/20261111-170956-c3b60885ec374109a26c208eac78d4ac/package/`，五件先移入回收再替换，保留原相对路径 |
| 当前进程交接 | PID360先返回 `ReadyToPublish`，再返回Catalog第3代、Adapter第3代 `Applied` |

```text
Applied c3b60885ec374109a26c208eac78d4ac catalog:bf126890ba7042524fd8a606e94d5390d74bed7b633449f2512c05cd7aa501c0:3 adapter:00b30991882a1138d31c71b5877ca4cd2fde9e6b64a37b536eb9db48ac39d383:3
```

新Adapter的构建文件、正式文件、发布清单及Applied回执的SHA-256均为 `00b30991882a1138d31c71b5877ca4cd2fde9e6b64a37b536eb9db48ac39d383`。已分别完整读取请求JSON、批次日志、发布JSON，并读取归档文件清单及新旧Adapter身份。根 `urwcn_launcher.exe` 继续加载同一正式包，当前进程已完成授权兼容交接，无需重启，没有平行修复包。

本次源码修改、产物编译、正式发布和兼容交接均已完成。未启动、关闭、重启或操作游戏，未运行测试、创建测试用例、测试脚本或断言；Applied只证明业务模块交接，画面由用户验收。既有待整改项仍按上节记录保留。
