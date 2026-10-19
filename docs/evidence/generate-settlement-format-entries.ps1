$rows=Import-Csv "$PSScriptRoot/settlement-formats-implemented-sites.tsv" -Delimiter "`t" | Sort-Object callsite,@{Expression={if($_.format_va -eq '00000000'){'ffffffff'}else{$_.format_va}}} -Unique
$lines=foreach($r in $rows) {
    $domains=$r.parameter_domains -split ';'
    $stringIndex=0
    $word=2
    $parameters=foreach($m in [regex]::Matches($r.format,'%[-+ #0]*(?:\d+|\*)?(?:\.(?:\d*|\*))?(?:I64|[hlLzjt])*[diuoxXfFeEgGaAcspn%]')) {
        $conversion=$m.Value
        $last=$conversion[-1]
        if($last -eq '%'){continue}
        $tag='nullptr'
        $kind=switch($last) {
            'd' {if($conversion -match 'ld$'){'signed_long32'}else{'signed32'}}
            'i' {'signed32'}
            'u' {'unsigned32'}
            'f' {'real64'}
            'c' {'character'}
            's' {'domain'}
        }
        if($last -eq 's') {
            $domain=$domains[$stringIndex++]
            if($domain -eq 'bound'){$kind='bound'}
            elseif($domain -eq 'control'){$kind='control'}
            elseif($domain.StartsWith('literal:')){$kind='literal';$tag='"format.'+$domain.Substring(8)+'"'}
            else{$tag='"'+$domain+'"'}
        }
        '{'+$word+',"'+$conversion+'",Kind::'+$kind+','+$tag+'}'
        $word+= $(if($kind -eq 'real64'){2}else{1})
    }
    $site=[Convert]::ToUInt32($r.callsite,16)-0x400000
    if($r.format_va -eq '00000000'){$format=0;$key='nullptr'}
    else{$format=[Convert]::ToUInt32($r.format_va,16)-0x400000;$key='"format.'+$r.format_va+'"'}
    '    {0x'+$site.ToString('x')+',0x'+$format.ToString('x')+','+$key+',{'+($parameters -join ',')+'}},'
}
$data="const Entry entries[]{`r`n"+($lines -join "`r`n")+"`r`n};"
$path=Join-Path $PSScriptRoot '../../modules/adapter/windows_message_formats.inc'
$code=Get-Content $path -Raw
$code=[regex]::Replace($code,'(?s)const Entry entries\[\]\{.*?\r?\n\};',$data)
Set-Content $path $code -Encoding utf8
Set-Content "$PSScriptRoot/settlement-formats-entry-data.inc" $data -Encoding utf8
"Generated $($rows.Count) records at $(@($rows.callsite|Sort-Object -Unique).Count) distinct sites."
