# Authoring inventory for the confirmed native 32-byte caption prefix.
# This script writes immutable translations, never runs the game or an adapter.
$taskRoot=Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$valuePath=Join-Path $taskRoot 'translations/messages_embedded/values.zh-CN.tsv'
$lines=[Collections.Generic.List[string]]::new()
$lookup=[Collections.Generic.Dictionary[string,string]]::new([StringComparer]::Ordinal)
foreach($line in [IO.File]::ReadAllLines($valuePath)) {
    $lines.Add($line);$parts=$line.Split("`t",3)
    if($parts.Length -eq 3) {$lookup[$parts[0]+"`t"+$parts[1]]=$parts[2]}
}
function Add-Value([string]$domain,[string]$source,[string]$target) {
    $key=$domain+"`t"+$source
    if(!$lookup.ContainsKey($key)) {$lines.Add($key+"`t"+$target);$lookup[$key]=$target}
}
foreach($row in Import-Csv (Join-Path $PSScriptRoot 'settlement-npc-finite-compounds.tsv') -Delimiter "`t") {
    $base=$lookup['npc'+"`t"+$row.base]
    $target=switch($row.relation) {
        'base + young' { $base+$(if($row.atom -eq 'puppy'){'幼犬'}else{'幼崽'}) }
        'bull + base' { '雄性'+$base }
        'female + base' { '雌性'+$base }
        'base + sex' { $base+$(if($row.atom -eq 'stag'){'（雄性）'}else{'（雌性）'}) }
    }
    Add-Value 'npc' $row.source $target
    Add-Value 'npc' ($row.source.Substring(0,1).ToUpperInvariant()+$row.source.Substring(1)) $target
}
Add-Value 'npc-debug' '%s (%d),' '%s（%d），'
Add-Value 'npc-debug' '%s (#%d stat %d - bfown %d),' '%s（编号%d，状态%d，所有权%d），'
$requirements=@'
%s * %u	%s×%u
 (of %u)	（共%u）
%s of %s	%s%s
%s %s	%s%s
%s %s * %u	%s%s×%u
%s of %s * %u	%s%s×%u
%s	%s
?(%d) 	？（%d）
, or 	，或
 or 	或
 or by hand	或徒手
You need 	你需要
You may optionally use 	你也可以使用
 - preferably %s.	，最好使用%s。
 (%s).	（%s）。
 - preferably of %s.	，最好选用%s。
.	。
'@
foreach($line in $requirements.Split("`n")) {$p=$line.TrimEnd("`r").Split("`t");Add-Value 'requirement-msg' $p[0] $p[1]}
Add-Value 'list' ' or ' '或'
[IO.File]::WriteAllLines($valuePath,$lines,[Text.UTF8Encoding]::new($false))
foreach($file in Get-ChildItem (Join-Path $taskRoot 'translations/messages_embedded') -Filter 'values*.zh-CN.tsv') {
    if($file.Name -eq 'values.menu-prefix.zh-CN.tsv'){continue}
    foreach($line in [IO.File]::ReadAllLines($file.FullName)) {
        $parts=$line.Split("`t",3)
        if($parts.Length -eq 3 -and !$line.StartsWith('#')) {$lookup[$parts[0]+"`t"+$parts[1]]=$parts[2]}
    }
}

# Each entry below is an explicit translation of a complete, visible source
# phrase. No unfinished source word contributes its hidden remaining meaning.
$npcPhrases=@'
aquatic	水生的
arctic	北极
beautiful	美丽的
black	黑色
eagle	鹰
elder	年长的
female	雌性
foreign	异乡
forest	森林
forester	林地居民
grey	灰色
hazel	榛
islander	岛民
kaumolais	考莫
driikiläis	德里基
kiesseläis	基耶塞
koivulais	科伊武
reemiläis	雷埃米
sartolais	萨尔托
kuikka-tribe	潜鸟部落
owl-tribe	猫头鹰部落
seal-tribe	海豹部落
vagabond	流浪者
njerpez	涅尔佩兹
wandering	流浪的
wild	野生的
ringed	环斑
tufted	有冠羽的
willow	柳
long	长
long grey	灰色长
long grey bearded	留着灰色长胡子的
long grey bearded old	留着灰色长胡子的老
long-bearded	留着长胡子的
long-bearded old	留着长胡子的老
man	男子
man with	男子，有
man with long	男子，有长
man with long black	男子，有黑色长
old	老
old man	老人
old man with	老人，有
old man with long	老人，有长
old man with long grey	老人，有灰色长
old driikiläis	年老的德里基
old foreign	年老的异乡
old forester	年老的林地居民
old islander	年老的岛民
old kaumolais	年老的考莫
old kiesseläis	年老的基耶塞
old koivulais	年老的科伊武
old kuikka-tribe	年老的潜鸟部落
old njerpez	年老的涅尔佩兹
old owl-tribe	年老的猫头鹰部落
old reemiläis	年老的雷埃米
old sartolais	年老的萨尔托
old seal-tribe	年老的海豹部落
old vagabond	年老的流浪者
old wandering	年老的流浪者
'@
$itemPhrases=@'
barley	大麦
bastard	手半
battleaxe	战斧
bear pipe	熊管草
bearpaw	熊掌
birch-bark	桦皮
black	黑色
black ear	黑耳
block of	一块
blueberry	蓝莓
bog flower	沼泽花
bogbean	睡菜
bone	骨
bone sewing	骨制缝纫
bone tipped	骨镞
broad axe	宽刃斧
broadhead	宽刃
bronze	青铜
bronze ball	青铜球
bronze bear	青铜熊
browncoat	褐衣
burdock	牛蒡
carving axe	刨削斧
clayweed	黏土草
cloudberry	云莓
cranberry	蔓越莓
crowberry	岩高兰
dog pipe	犬管草
fisher's	渔用
flat rye	黑麦薄
fur	毛皮
golden rod	一枝黄花
hairy	有毛的
handaxe	手斧
heather	石南
heavy	重型
hunting	狩猎
iron	铁
iron sewing	铁制缝纫
kaumolais	考莫
kaumolais spear	考莫长矛
lake reed	湖苇
lamellar	札甲
lamellar forearm	札甲前臂
lamellar shin	札甲胫部
leather	皮革
leather forearm	皮革前臂
linen	亚麻
lingonberry	越橘
long mail	加长锁子甲
mail	锁子甲
marsh calla	水芋
meadsweet	蜜香草
milkweed	乳草
mother pipe	母管草
netting	织网
nettle	荨麻
njerpez	涅尔佩兹
noaidi's	诺艾迪的
northern	北方
northern bilberry	北地蓝莓
paw-board	夹爪板
raspberry	覆盆子
redlegger	红脚
ringed	环纹
riverpig	河猪草
roseroot	红景天
sand	沙
shingle	木片
shovel	铲
silver	银
silver bird	银鸟
silver chain	银链
silver sun-symbol	银太阳纹
slender	细
small	小
soft	软
sorrel	酸模
splitting	劈柴
spruce	云杉
stone	石
stonecrop	景天
strawberry	草莓
tellervo's	泰勒沃的
tellervo's gift	泰勒沃的赠礼
trident	三齿鱼叉
turnip	芜菁
ukko's	乌科的
water lily	睡莲
wide	宽
wolf pipe	狼管草
wooden	木制
woodsman's	伐木用
woollen	羊毛
woollen nalbound	羊毛单针编织
yarrow	蓍草
yellow	黄色
yellow fingers	黄指
yellowcoat	黄衣
'@
$lexical=[Collections.Generic.HashSet[string]]::new([StringComparer]::Ordinal)
foreach($entry in $lookup.GetEnumerator()) {
    if($entry.Key.StartsWith("npc`t") -and !$entry.Key.Contains('%')) {[void]$lexical.Add($entry.Key)}
}
$atoms=[IO.File]::ReadAllLines((Join-Path $taskRoot 'modules/adapter/windows_message_crafted_item_atoms.inc'))
$array='atoms'
foreach($line in $atoms) {
    if($line.StartsWith('constexpr const char* animals')){$array='material.animal'}
    if($line.StartsWith('constexpr const char* trees')){$array='tree'}
    if($line.StartsWith('constexpr Pattern')){$array='patterns'}
    if($array -eq 'atoms' -and $line -match '^\s*\{"((?:[^"\\]|\\.)*)","((?:[^"\\]|\\.)*)"\},?$') {
        $source=ConvertFrom-Json ('"'+$Matches[1]+'"');$domain=$Matches[2]
        [void]$lexical.Add($domain+"`t"+$source)
    } elseif($array -in @('material.animal','tree') -and $line -match '^\s*"((?:[^"\\]|\\.)*)",?$') {
        [void]$lexical.Add($array+"`t"+(ConvertFrom-Json ('"'+$Matches[1]+'"')))
    }
}
foreach($source in @('Spoiled ','Rotten ')){[void]$lexical.Add("item`t"+$source)}
$extraPhrases=@'
spoiled	变质的
rotten	腐烂的
stale	不新鲜的
bull	公牛
block	块
block of	一块
slender	细
winter	冬季
clean	刮净的
de-haired	脱毛的
ember-roasted	余烬烤
boiled	水煮
roasted	烤
dried	风干
salted	盐腌
smoked	烟熏
block with	用来格挡
counterstrike	反击
counterstrike with	用来反击
with	带有
with bone	带有骨制
with iron	带有铁制
with no	不带
with wooden	带有木制
bronze bezel	青铜镶座
bronze flower-ornamented	青铜花纹装饰
bronze horse-ornamented	青铜马纹装饰
iron spectacle	铁眼罩
leather shin	皮革胫部
paw-board fox	夹爪板捕狐
slender tree	细树
small bronze	小青铜
stone tipped	石镞
woollen nalbound knee	羊毛单针编织膝部
ceiling and	天花板与
dried fish	鱼干
dried meat	肉干
eastern wall of	东墙
eastern wall of a	东墙
inside of	内部
inside of a	内部
north-east corner of	东北角
north-east corner of a	东北角
north-west corner of	西北角
north-west corner of a	西北角
northern wall of	北墙
northern wall of a	北墙
smoked fish	熏鱼
smoked meat	熏肉
south-east corner of	东南角
south-east corner of a	东南角
south-west corner of	西南角
south-west corner of a	西南角
southern wall of	南墙
southern wall of a	南墙
wall with	墙体，带有
wall with a	墙体，带有
western wall of	西墙
western wall of a	西墙
the	
'@
$editorial=[Collections.Generic.Dictionary[string,string]]::new([StringComparer]::Ordinal)
foreach($text in @($npcPhrases,$itemPhrases,$extraPhrases)) {
    foreach($line in $text.Split("`n")) {$parts=$line.TrimEnd("`r").Split("`t");$editorial[$parts[0]]=$parts[1]}
}
$completePhrases=[Collections.Generic.Dictionary[string,string]]::new([StringComparer]::Ordinal)
foreach($entry in $lookup.GetEnumerator()) {
    $parts=$entry.Key.Split("`t",2)
    if($parts[0] -in @('npc','item','tree','menu.recipe','material.cut','material.cut-native','material.word','material.field','material.animal','crafted-material') -and !$parts[1].Contains('%')) {
        $completePhrases[$parts[1].ToLowerInvariant()]=$entry.Value
    }
}
foreach($entry in $editorial.GetEnumerator()){$completePhrases[$entry.Key]=$entry.Value}
$completePhrases['']=''
# Only material.cut and material.cut-native rows enumerated by native species/quality
# evidence participate. This writes each concrete qualified prefix; it is
# not a runtime word replacement or a cross-product of unrelated names.
foreach($key in $lexical) {
    $parts=$key.Split("`t",2)
    if($parts[0] -in @('material.cut','material.cut-native') -and $parts[1] -cmatch '^(Spoiled|spoiled|stale) (.*)$') {
        $quality=$Matches[1].ToLowerInvariant();$tail=$Matches[2]
        for($n=1;$n -lt $tail.Length;++$n) {
            if($tail[$n] -eq ' ') {
                $phrase=$tail.Substring(0,$n).ToLowerInvariant()
                if($completePhrases.ContainsKey($phrase)) {
                    $completePhrases[$quality+' '+$phrase]=$completePhrases[$quality]+$completePhrases[$phrase]
                }
            }
        }
    }
}
$phrases=@{}
foreach($key in $lexical) {$domain=$key.Split("`t",2)[0];$phrases[$domain]=$completePhrases}
$output=[Collections.Generic.List[string]]::new();$output.Add("domain`tsource`ttarget")
$evidence=[Collections.Generic.List[string]]::new();$evidence.Add("domain`toriginal`tnative_visible_prefix`tcomplete_visible_phrase`ttranslation")
$missing=[Collections.Generic.HashSet[string]]::new([StringComparer]::Ordinal)
$keys=[Collections.Generic.HashSet[string]]::new([StringComparer]::Ordinal)
function Write-Prefix([string]$domain,[string]$source,[int]$length) {
    $prefix=$source.Substring(0,$length)
    $complete=$prefix
    if($source[$length] -ne ' ') {
        $space=$complete.LastIndexOf(' ')
        $complete=if($space -lt 0){''}else{$complete.Substring(0,$space)}
    }
    $complete=$complete.TrimEnd()
    if(!$phrases[$domain].ContainsKey($complete.Trim().ToLowerInvariant())) {
        [void]$missing.Add($domain+"`t"+$complete);return
    }
    $target=$phrases[$domain][$complete.Trim().ToLowerInvariant()]
    # 4AD4F0's species 0x294 uses the gender adjective 'bull elk'; species
    # 0x261's 'bull cub' retains the cattle noun. Keep this native distinction
    # in the finite material.cut spellings as well.
    if($source -match '^(?i)((?:spoiled|stale) )?bull elk' -and
       $complete.Trim() -match '^(?i)((?:spoiled|stale) )?bull$') {
        $quality=([string]$Matches[1]).Trim().ToLowerInvariant()
        $target=$completePhrases[$quality]+'雄性'
    }
    $key='menu.prefix.'+$domain+'/'+$source+"`t"+$prefix
    if($keys.Add($key)) {
        $output.Add($key+"`t"+$target)
        $evidence.Add($domain+"`t"+$source+"`t"+$prefix+"`t"+$complete+"`t"+$target)
    }
}
foreach($key in $lexical) {
    $parts=$key.Split("`t",2)
    if(!$parts[1].Contains('%')) {for($n=0;$n -lt $parts[1].Length;++$n) {Write-Prefix $parts[0] $parts[1] $n}}
}
# Reduced grammar is keyed by the exact full native format, because a visible
# string such as 'cold' may be a whole word in one format and only the start
# of a hyphenated word in another. No runtime phrase matching is performed.
$patterns=[Collections.Generic.HashSet[string]]::new([StringComparer]::Ordinal)
foreach($entry in $lookup.GetEnumerator()) {
    $parts=$entry.Key.Split("`t",2)
    if($parts[0] -in @('crafted-name-format','crafted-wood-format','crafted-animal-format')){[void]$patterns.Add($parts[1])}
}
foreach($pattern in @('%s the %s','%s called %s','%s %s','bull %s','Bull %s','female %s','Female %s','winter %s','slender %s trunk','block of %s wood','Block with %s','Counterstrike with %s')) {[void]$patterns.Add($pattern)}
foreach($pattern in $patterns) {
    for($n=0;$n -lt $pattern.Length;++$n) {
        $prefix=$pattern.Substring(0,$n)
        if($prefix.EndsWith('%')){continue}
        $complete=$prefix
        if($pattern[$n] -ne ' ' -and !$prefix.EndsWith('%s')) {
            $space=$complete.LastIndexOf(' ');$marker=$complete.LastIndexOf('%s')
            if($marker -gt $space){$complete=$complete.Substring(0,$marker+2)}
            else {$complete=if($space -lt 0){''}else{$complete.Substring(0,$space)}}
        }
        $parts=$complete.Split(@('%s'),[StringSplitOptions]::None)
        $target='';$untranslated=$false
        for($part=0;$part -lt $parts.Length;++$part) {
            $phrase=$parts[$part].Trim().ToLowerInvariant()
            if($pattern -eq '%s the %s' -and $part -eq 1){$phrase=''}
            if($pattern -in @('bull %s','Bull %s') -and $phrase -eq 'bull'){$target+='雄性'}
            elseif($pattern -eq '%s called %s' -and $part -eq 1 -and $phrase -eq 'called'){$target+='，名叫'}
            elseif($completePhrases.ContainsKey($phrase)){$target+=$completePhrases[$phrase]}
            else {[void]$missing.Add('format'+"`t"+$phrase);$untranslated=$true}
            if($part -lt $parts.Length-1){$target+='%s'}
        }
        if(!$untranslated) {
            $output.Add('menu.prefix.format/'+$pattern+"`t"+$prefix+"`t"+$target)
            $evidence.Add('format'+"`t"+$pattern+"`t"+$prefix+"`t"+$complete+"`t"+$target)
        }
    }
}
[IO.File]::WriteAllLines((Join-Path $taskRoot 'translations/messages_embedded/values.menu-prefix.zh-CN.tsv'),$output,[Text.UTF8Encoding]::new($false))
[IO.File]::WriteAllLines((Join-Path $PSScriptRoot 'settlement-menu-prefix-translations.tsv'),$evidence,[Text.UTF8Encoding]::new($false))
'Authored exact prefix entries: '+($output.Count-1)
'Complete phrases requiring editorial translation:'
$missing | Sort-Object
