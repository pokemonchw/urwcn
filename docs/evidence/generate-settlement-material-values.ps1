$ErrorActionPreference='Stop'
$root=Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$terms=Get-ChildItem (Join-Path $root 'translations/messages_embedded') -Filter 'values*.tsv' |
    Where-Object Name -ne 'values.materials.zh-CN.tsv' |
    ForEach-Object { Import-Csv $_.FullName -Delimiter "`t" -Header domain,source,target }
$words=[Collections.Generic.Dictionary[string,string]]::new([StringComparer]::OrdinalIgnoreCase)
foreach($term in $terms) {
    if($term.domain -in @('item','npc','material','nameatom','menu.recipe','quality') -and $term.source -match '^[a-zA-Z][a-zA-Z''-]*$') {
        $words[$term.source]=$term.target
    }
}
# The game selects an English word before translation. These are translations
# of those complete selected atoms, not slices of a translated item name.
$authored=@'
adventurer=冒险者
aquatic=水生
arctic=北极
axe=斧
basket=篮
bastard=手半
bean=豆
beans=豆
beard=胡须
bearpaw=熊掌
belt=腰带
berry=浆果
bilberries=越橘
bilberry=越橘
birch=桦木
birch-bark=桦皮
bird=鸟
black=黑色
blacksmith=铁匠
blade=刃
block=木块
blunt=钝头
bog=沼泽
bone=骨
boots=靴
bow=弓
bowl=碗
box=盒
boy=男孩
bracelet=手镯
bramble=悬钩子灌木
bread=面包
broad=阔
bronze=青铜
brooch=胸针
browncoat=褐衣
building=建筑
bunk=铺位
bush=灌木
calla=马蹄莲
canteen=水壶
cap=帽
carving=雕刻
ceiling=天花板
cloth=布
comb=梳子
corner=转角
coudes=护肘
craftsman=工匠
cuirass=胸甲
cup=杯
currant=醋栗
currants=醋栗
doorway=门口
dried=风干
driikiläis=德里基
duck=鸭
eagle=鹰
eastern=东方
elder=长者
female=雌性
fish=鱼
fisher's=渔夫的
fishhook=鱼钩
fishing=钓鱼
flat=平
floor=地板
flower=花
flowers=花
foreign=异乡
forest=森林
forester=林地居民
fur=毛皮
gate=门
girl=女孩
golden=金色
grains=谷粒
green=绿色
grey=灰色
grouse=松鸡
guards=护具
habergeon=短锁子甲
haft=柄
hair=毛发
hairy=多毛
hauberk=长锁子甲
hazel=榛
head=头
heavy=重型
helm=头盔
hood=兜帽
hook=钩
horn=角
housewife=主妇
hunter=猎人
hunting=狩猎
inside=内部
iron=铁
islander=岛民
kaumolais=考莫
kiesseläis=基塞
kneecops=护膝
koivulais=科伊武
kota=科塔帐篷
kuikka-tribe=库伊卡部落
lake=湖
lamellar=札甲
leather=皮革
leaves=叶
lily=百合
long=长
long-bearded=长须
loop=绳圈
maid=少女
maiden=少女
mail=锁子甲
marsh=沼泽
meat=肉
mittens=连指手套
mother=母
mug=杯
mushroom=蘑菇
necklace=项链
needle=针
netting=结网
njerpez=涅尔佩兹
noaidi's=诺艾迪的
north-east=东北
north-west=西北
northern=北方
old=年老
oven=烤炉
owl=猫头鹰
owl-tribe=猫头鹰部落
paw-board=夹板
peasant=农民
pendant=吊坠
pipe=管草
pole=长杆
quick-bow=短弓
redlegger=红脚
reed=芦苇
reemiläis=雷米
rerebraces=上臂甲
ring=戒指
ringed=环纹
robber=强盗
rod=杆
root=根
rotten=腐烂
sage=智者
sand=沙
sartolais=萨尔托
sauna=桑拿房
scoop=舀勺
seal=海豹
seal-tribe=海豹部落
seed=种子
seeds=种子
shaft=杆
shaman=萨满
shield=盾
shoes=鞋
shrub=灌木
silver=银
ski=滑雪板
slat=木条
sleeping=睡觉
slender=细长
small=小
smoked=烟熏
snare=套索
socks=袜子
soft=柔软
soup=汤
south-east=东南
south-west=西南
southern=南方
splitting=劈木
spoiled=变质
spruce=云杉
stake=木桩
stew=炖菜
stove=炉灶
string=弦
sword=剑
tellervo's=泰勒尔沃的
trader=商人
trap=陷阱
tree=树
tribesman=部落民
trunk=树干
tub=桶
tufted=凤头
twig=细枝
ukko's=乌科的
vagabond=流浪者
vegetable=蔬菜
wall=墙
wandering=流浪
warrior=战士
western=西方
wide=宽
wild=野生
willow=柳木
with=带有
withe=柔枝
wooden=木制
woodsman=林地猎人
woodsman's=林地猎人的
woollen=羊毛
yellow=黄色
yellowcoat=黄衣
'@
foreach($line in $authored.Split("`n")) {$parts=$line.TrimEnd("`r").Split('=',2);$words[$parts[0]]=$parts[1]}
$rows=[Collections.Generic.Dictionary[string,string]]::new([StringComparer]::Ordinal)
function Add-MaterialValue([string]$domain,[string]$source,[string]$target) {
    $rows[$domain+"`t"+$source]=$domain+"`t"+$source+"`t"+$target
}
foreach($row in (Import-Csv (Join-Path $PSScriptRoot 'settlement-material-word-sources.tsv') -Delimiter "`t")) {
    $source=$row.word;$target=$words[$source]
    if(!$target) {throw "Untranslated native selected word: $source"}
    Add-MaterialValue 'material.word' $source $target
    Add-MaterialValue 'material.word' ($source.Substring(0,1).ToUpperInvariant()+$source.Substring(1)) $target
    Add-MaterialValue 'material.word' $source.ToUpperInvariant() $target
}
$field=[Collections.Generic.Dictionary[string,string]]::new([StringComparer]::OrdinalIgnoreCase)
foreach($term in $terms) {if($term.domain -in @('item','item.alternate','npc','material')) {$field[$term.source]=$term.target}}
foreach($word in @('AXE','BOW','CLUB','CROSSBOW','KNIFE','NET','SHIELD','SPEAR','SWORD')) {$field[$word]=$words[$word]}
$field['unknown']='未知材料';$field['tuntematon']='未知材料'
foreach($row in (Import-Csv (Join-Path $PSScriptRoot 'settlement-item-material-fields.tsv') -Delimiter "`t")) {
    $source=$row.material;$target=$field[$source]
    if(!$target) {throw "Untranslated native material field: $source"}
    Add-MaterialValue 'material.field' $source $target
}
Add-MaterialValue 'material.field' 'unknown' '未知材料'
# 51E9D0 copies the animal material into descriptor +0x31 while constructing
# leather/fur. Other craft material literals are supplied by the same inventory.
foreach($term in $terms) {
    if($term.domain -in @('npc','material','material.animal','item.alternate')) {Add-MaterialValue 'material.field' $term.source $term.target}
}
# 467BDB selects the prefix before " cut". The source node keeps that exact
# semantic operand separately from the pending native unterminated copy.
foreach($term in $terms) {
    if($term.domain -ne 'npc' -or $term.source -match '[%{}|/]') {continue}
    # 467A30 uses flags=4/count=1: stale is suppressed, category 7 uses
    # Spoiled (Rotten belongs to category 5), and 452586 lowercases all text.
    foreach($prefix in @('', 'spoiled ')) {
        $source=$prefix+$term.source.ToLowerInvariant()
        $target=if($prefix){'变质的'+$term.target}else{$term.target}
        Add-MaterialValue 'material.cut' $source $target
        # 467A30 clears the complete 100-byte target before 451650 copies
        # its material. The exact tuntematon guard precedes this strncpy;
        # earlier full-name branches cannot change it back to tuntematon.
        $native=if($source.Length -lt 10){$source+'tuntematon'.Substring($source.Length)}else{$source}
        Add-MaterialValue 'material.cut-native' $native $target
    }
}
[IO.File]::WriteAllLines((Join-Path $root 'translations/messages_embedded/values.materials.zh-CN.tsv'),($rows.GetEnumerator()|Sort-Object Key|ForEach-Object Value),[Text.UTF8Encoding]::new($false))
