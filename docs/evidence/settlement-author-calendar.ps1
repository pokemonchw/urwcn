# Static PE 3.89 calendar vocabulary. No calendar/game state is simulated.
$taskRoot=Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
$bytes=[IO.File]::ReadAllBytes('D:/program/steam/steamapps/common/UnRealWorld/urw.exe')
$lines=[Collections.Generic.List[string]]::new();$lines.Add("domain`tsource`ttarget")
$fixed=@'
calendar.ordinal	%d	第%d
calendar.ordinal	last	最后一
calendar.part	on 	在
calendar.part	 at 	，位于
calendar.format	day %d of %s week before %s	%s前的%s周，第%d天
calendar.format	%s of month:%d	%s日，月份：%d
calendar.format	in %s, during %s, on %s	在%s，%s，%s
calendar.format	%s, %s, %s	%s，%s，%s
calendar.format	in %s, during %s	在%s，%s
calendar.format	%s, %s	%s，%s
calendar.format	%s 	%s
calendar.format	%s%s	%s%s
calendar.season	winter season	冬季
calendar.season	midwinter point	仲冬时节
calendar.season	midwinter	仲冬
calendar.season	latter winter	冬末
calendar.season	summer season	夏季
calendar.season	midsummer point	仲夏时节
calendar.season	midsummer	仲夏
calendar.season	latter summer	夏末
'@
foreach($line in $fixed.Split("`n")) {$lines.Add($line.TrimEnd("`r"))}
$months=@('','一月','二月','三月','四月','五月','六月','七月','八月','九月','十月','十一月','十二月')
$evidence=[Collections.Generic.List[string]]::new();$evidence.Add("native_month_slot`tsource`ttranslation")
for($month=0;$month -lt 13;++$month) {
    # 55E910 selects DAT_005EA3A0 + month*100. The first slot is native BSS.
    $offset=0x1e0800+(0x5ea3a0-0x5e2000)+$month*100;$end=$offset
    while($bytes[$end]){$end++}
    $name=[Text.Encoding]::ASCII.GetString($bytes,$offset,$end-$offset)
    foreach($phase in @(@('',''),@('beginning of ','初'),@('early ','上旬'),@('late ','下旬'),@('end of ','末'))) {
        $target=$months[$month]+$phase[1]
        if($month -eq 0) {
            $target=switch($phase[0]) {''{''};'beginning of '{'开始时'};'early '{'初期'};'late '{'后期'};'end of '{'结束时'}}
        }
        $source=$phase[0]+$name;$lines.Add('calendar.moon'+"`t"+$source+"`t"+$target)
         $evidence.Add($month.ToString()+"`t"+$source+"`t"+$target)
    }
}
[IO.File]::WriteAllLines((Join-Path $taskRoot 'translations/messages_embedded/values.calendar.zh-CN.tsv'),$lines,[Text.UTF8Encoding]::new($false))
[IO.File]::WriteAllLines((Join-Path $PSScriptRoot 'settlement-calendar-month-atoms.tsv'),$evidence,[Text.UTF8Encoding]::new($false))
'Calendar semantic entries: '+($lines.Count-1)

