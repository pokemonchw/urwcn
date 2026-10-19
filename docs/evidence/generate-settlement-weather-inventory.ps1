$ErrorActionPreference='Stop'
$root=Join-Path $PSScriptRoot '../..'
$bytes=[IO.File]::ReadAllBytes('D:/program/steam/steamapps/common/UnRealWorld/urw.exe')
$pe=[BitConverter]::ToInt32($bytes,0x3c)
$sectionCount=[BitConverter]::ToUInt16($bytes,$pe+6)
$sections=$pe+24+[BitConverter]::ToUInt16($bytes,$pe+20)
function NativeString([uint32]$va) {
    $rva=$va-0x400000
    for($i=0;$i -lt $sectionCount;$i++) {
        $entry=$sections+40*$i
        $sectionRva=[BitConverter]::ToUInt32($bytes,$entry+12)
        $size=[BitConverter]::ToUInt32($bytes,$entry+16)
        if($rva -ge $sectionRva -and $rva -lt $sectionRva+$size) {
            $start=$rva-$sectionRva+[BitConverter]::ToUInt32($bytes,$entry+20)
            $end=$start
            while($bytes[$end]) {$end++}
            return [Text.Encoding]::GetEncoding(1252).GetString($bytes,$start,$end-$start)
        }
    }
}
# All seven mutually exclusive temperature append branches in 587300.
$temperatures=@(
    @(0x5dce94,'比现在冷得多。'),
    @(0x5dcea8,'比现在冷。'),
    @(0x5dceb4,'比现在稍冷。'),
    @(0x5dcecc,'与现在差不多。'),
    @(0x5dcee0,'比现在稍暖。'),
    @(0x5dcef8,'比现在暖。'),
    @(0x5dcf04,'比现在暖得多。')
)
# The negative native value has no final punctuation; preserve that branch.
$precipitation=@(
    @('negative',0x5dcf30,0,'会下',''),
    @('zero',0x5dcf20,0x59285c,'不会下','。'),
    @('one_to_five',0x5dcf30,0x5dcf4c,'会下小','。'),
    @('six_to_twelve',0x5dcf30,0x59285c,'会下','。'),
    @('over_twelve',0x5dcf30,0x5dcf58,'会下大','。')
)
$types=@(@(0x5dcf3c,'雨'),@(0x5dcf44,'雪'))
$rows=[Collections.Generic.List[string]]::new()
$evidence=[Collections.Generic.List[string]]::new()
$evidence.Add("temperature_va`tprecipitation_branch`ttype_va`tsource`ttarget")
foreach($temperature in $temperatures) {
    foreach($level in $precipitation) {
        foreach($type in $types) {
            $suffix=if($level[2]) {NativeString $level[2]} else {''}
            $source=(NativeString $temperature[0])+(NativeString 0x5dcf18)+(NativeString $level[1])+(NativeString $type[0])+$suffix
            $target=$temperature[1]+$level[3]+$type[1]+$level[4]
            $rows.Add("weather.description`t$source`t$target")
            $evidence.Add(('{0:X8}' -f $temperature[0])+"`t"+$level[0]+"`t"+('{0:X8}' -f $type[0])+"`t$source`t$target")
        }
    }
}
foreach($period in @(@(0x5dcf60,'白天气温将'),@(0x5dcf88,'夜间气温将'),@(0x5dcfb4,'明天气温将'))) {
    $rows.Add("weather.period`t"+(NativeString $period[0])+"`t"+$period[1])
}
[IO.File]::WriteAllLines((Join-Path $root 'translations/messages_embedded/values.weather.zh-CN.tsv'),$rows,[Text.UTF8Encoding]::new($false))
[IO.File]::WriteAllLines((Join-Path $PSScriptRoot 'settlement-weather-description-inventory.tsv'),$evidence,[Text.UTF8Encoding]::new($false))
