# Exact complete messages emitted by PE 3.89 4E9320 at 4E9900/4E9A30.
# Native ritual selection and per-line control prefixes remain in the game.
$taskRoot=Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$bytes=[IO.File]::ReadAllBytes('D:/program/steam/steamapps/common/UnRealWorld/urw.exe')
$sourceRows=@'
200	intro	005a8c08	临睡前，你先用以下诗句向此地及其精灵致意：
200	first	005a8bac	向大地致意，也向
200	middle	005a8bc4	地下的众生致意。
200	middle	005a8be0	请允我在此安卧
200	last	005a8bf8	安然无恙
192	intro	005a8cc0	狩猎前，你献上供品，并用以下诗句祈求森林的眷顾：
192	first	005a8d10	森林啊，请善待我。
192	middle	005a8d28	沼泽啊，请赐我好运。
192	middle	005a8d40	伟大的森林之灵啊，请施恩于我，
192	last	005a8d6c	当我踏上狩猎之途
180	intro	005a8df8	你念出以下诗句，命令鲜血停止流淌：
180	first	005a8d84	止住吧，鲜血，停息吧，鲜血
180	middle	005a8da0	如墙壁般屹立
180	middle	005a8db4	如围栏般坚固
180	middle	005a8dc4	如沼泽中的木桩
180	last	005a8ddc	如苔藓间的小草
'@
$lines=[Collections.Generic.List[string]]::new();$lines.Add("domain`tsource`ttarget")
$evidence=[Collections.Generic.List[string]]::new();$evidence.Add("native_ritual`tline_role`tliteral_va`tnative_message`ttranslation")
foreach($row in ($sourceRows | ConvertFrom-Csv -Delimiter "`t" -Header ritual,role,va,target)) {
    $va=[Convert]::ToInt32($row.va,16);$start=$va-0x400e00;$end=$start
    while($bytes[$end]){$end++}
    $source=[Text.Encoding]::ASCII.GetString($bytes,$start,$end-$start)
    # These are the exact observed branches, not alternative combinations.
    $prefix=switch($row.role){'intro'{'&'};'first'{':"'};default{':'}}
    $suffix=if($row.role -eq 'last'){'."'}else{''}
    $targetSuffix=if($row.role -eq 'last'){'。"'}else{''}
    $source=$prefix+$source+$suffix;$target=$prefix+$row.target+$targetSuffix
    $lines.Add('prayer.message'+"`t"+$source+"`t"+$target)
    $evidence.Add($row.ritual+"`t"+$row.role+"`t"+$row.va+"`t"+$source+"`t"+$target)
}
[IO.File]::WriteAllLines((Join-Path $taskRoot 'translations/messages_embedded/values.prayers.zh-CN.tsv'),$lines,[Text.UTF8Encoding]::new($false))
[IO.File]::WriteAllLines((Join-Path $PSScriptRoot 'settlement-prayer-message-atoms.tsv'),$evidence,[Text.UTF8Encoding]::new($false))
'Exact prayer messages: '+($lines.Count-1)
