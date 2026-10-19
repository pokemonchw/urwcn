param([string]$GameBinary='D:/program/steam/steamapps/common/UnRealWorld/urw.exe')
$ErrorActionPreference='Stop'
$taskRoot=Split-Path $PSScriptRoot -Parent
$pe=[IO.File]::ReadAllBytes($GameBinary)
$peHeader=[BitConverter]::ToInt32($pe,0x3c)
$sectionCount=[BitConverter]::ToUInt16($pe,$peHeader+6)
$optionalBytes=[BitConverter]::ToUInt16($pe,$peHeader+20)
$imageBase=[BitConverter]::ToUInt32($pe,$peHeader+52)
$sections=@()
for($index=0;$index -lt $sectionCount;$index++) {
    $offset=$peHeader+24+$optionalBytes+$index*40
    $sections+=@{Rva=[BitConverter]::ToUInt32($pe,$offset+12);Size=[BitConverter]::ToUInt32($pe,$offset+16);Raw=[BitConverter]::ToUInt32($pe,$offset+20)}
}
function Read-LiteralBytes([string]$address) {
    $rva=[Convert]::ToUInt32($address,16)-$imageBase
    $section=$sections | Where-Object {$rva -ge $_.Rva -and $rva -lt ($_.Rva+$_.Size)} | Select-Object -First 1
    $start=$section.Raw+$rva-$section.Rva
    $end=$start
    while($pe[$end] -ne 0) {$end++}
    return ,$pe[$start..($end-1)]
}
function Hex-Bytes([byte[]]$bytes) { return [Convert]::ToHexString($bytes).ToLowerInvariant() }
function Hex-Text([string]$text) { return Hex-Bytes ([Text.Encoding]::UTF8.GetBytes($text)) }
$entries=[Collections.Generic.SortedDictionary[string,string]]::new([StringComparer]::Ordinal)
$entries['message.continue']='按 [空格] 继续'
$entries['message.more']='[空格] 查看后续 -- [ESC] 跳过'
foreach($name in @('direct','branches','branches_remaining','direct_dispatch','direct_copied','direct_appended')) {
    foreach($line in [IO.File]::ReadAllLines((Join-Path $PSScriptRoot "messages_embedded/$name.zh-CN.tsv"))) {
        if(!$line -or $line.StartsWith('#')) {continue}
        $fields=$line.Split("`t",2)
        # The 3.89 embedded-literal inventory uses only E4/F6 above ASCII.
        # message_source_utf8 passes their Unicode UTF-8 spelling to semantic,
        # so the catalog identity must use the same spelling, not PE bytes.
        $literal=[Text.Encoding]::Latin1.GetString((Read-LiteralBytes $fields[0]))
        $entries['message.literal.'+(Hex-Text $literal)]=$fields[1]
    }
}
foreach($file in Get-ChildItem -LiteralPath (Join-Path $PSScriptRoot 'messages_embedded') -Filter 'formats*.zh-CN.tsv') {
    foreach($line in [IO.File]::ReadAllLines($file.FullName)) {
        if(!$line -or $line.StartsWith('#')) {continue}
        $fields=$line.Split("`t",2)
        $entries['message.format.'+$fields[0].ToLowerInvariant()]=$fields[1]
    }
}
$resource=Get-Content -LiteralPath (Join-Path $PSScriptRoot 'messages/selected-templates.zh-CN.json') -Raw | ConvertFrom-Json
foreach($entry in $resource.entries) {
    $entries['message.template.'+$entry.key+'.'+(Hex-Text $entry.source)]=$entry.target
}
foreach($valueFile in Get-ChildItem -LiteralPath (Join-Path $PSScriptRoot 'messages_embedded') -Filter 'values*.zh-CN.tsv') {
foreach($line in [IO.File]::ReadAllLines($valueFile.FullName)) {
    if(!$line -or $line.StartsWith('#') -or $line.StartsWith("domain`tsource`t")) {continue}
    $fields=$line.Split("`t",3)
    $entries['message.value.'+$fields[0]+'.'+(Hex-Text $fields[1])]=$fields[2]
}
}
$catalog=[Collections.Generic.List[string]]::new()
$catalog.Add('# Generated from decompiled native message sources and selected resource templates.')
foreach($entry in $entries.GetEnumerator()) {$catalog.Add($entry.Key+"`t"+$entry.Value)}
[IO.File]::WriteAllLines((Join-Path $taskRoot 'catalog/zh-CN/messages.tsv'),$catalog,[Text.UTF8Encoding]::new($false))
Write-Output "Generated catalog/zh-CN/messages.tsv: $($entries.Count) semantic entries."
