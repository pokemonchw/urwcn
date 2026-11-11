param([string]$GameBinary='D:/program/steam/steamapps/common/UnRealWorld/urw.exe',
      [switch]$ExistingLiterals)
$ErrorActionPreference='Stop'
$taskRoot=Split-Path $PSScriptRoot -Parent
if(!$ExistingLiterals) {
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
if($ExistingLiterals) {
    # Use the already-authored neutral literal identities when deriving a new
    # display consumer; their legacy addresses do not index a newer game PE.
    foreach($line in [IO.File]::ReadAllLines((Join-Path $taskRoot 'catalog/zh-CN/messages.tsv'))) {
        if($line.StartsWith('message.literal.')) {
            $fields=$line.Split("`t",2)
            $entries[$fields[0]]=$fields[1]
        }
    }
} else {
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
}
foreach($file in Get-ChildItem -LiteralPath (Join-Path $PSScriptRoot 'messages_embedded') -Filter 'literals*.zh-CN.tsv') {
    foreach($line in [IO.File]::ReadAllLines($file.FullName)) {
        if(!$line -or $line.StartsWith('#')) {continue}
        $fields=$line.Split("`t",2)
        $entries['message.literal.'+(Hex-Text $fields[0])]=$fields[1]
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
# F6510's native history body omits the initial colour marker and every @,
# and its F6A68 branch skips the second space in a run. FE2B0 reads that
# unchanged English body from msglog.txt, rather than the original literal.
# Derive exact history identities from the existing literal translations.
function History-Body([string]$text) {
    $body=[Text.StringBuilder]::new()
    for($i=0;$i -lt $text.Length;$i++) {
        if($i -gt 1 -and $text[$i] -eq ' ' -and $text[$i-1] -eq ' ') { $i++ }
        if($i -eq $text.Length) { break }
        if(($i -eq 0 -and '!#&+:=>?_'.Contains($text[$i])) -or $text[$i] -eq '@') { continue }
        [void]$body.Append($text[$i])
    }
    return $body.ToString()
}
# F6664..F6789 applies ASCII sentence case before the history word loop.
# F66E7 preserves decimal points; F6773 keeps the pending capital across the
# exact prefix characters at 1A9F1C. The other native flag preserves case.
function History-Case([string]$text) {
    $body=[Text.StringBuilder]::new()
    $capital=$true
    for($i=0;$i -lt $text.Length;$i++) {
        $character=$text[$i]
        if($capital) {
            if($character -cge 'a' -and $character -cle 'z') { $character=[char]([int]$character-32) }
            $capital='#!+?:&,=_()1234567890 '.Contains($character)
        }
        [void]$body.Append($character)
        if('.!:?'.Contains($character)) {
            $capital=!($character -eq '.' -and $i+1 -lt $text.Length -and
                '0123456789'.Contains($text[$i+1]))
        }
    }
    return $body.ToString()
}
# Resource selection has already resolved PC/other selectors in this source
# inventory. Only entries with no remaining native expansion are whole bodies.
foreach($entry in $resource.entries) {
    if($entry.source -match '[<>{}]|\[[A-Z_]+:|%[-+0-9.*lh]*[diuoxXfFeEgGcs]') { continue }
    $target=History-Body $entry.target
    $entries['message.value.message.history.'+(Hex-Text (History-Body $entry.source))]=$target
    $entries['message.value.message.history.'+(Hex-Text (History-Body (History-Case $entry.source)))]=$target
}
# Existing embedded-literal wording has precedence when a resource contains
# the identical complete English sentence.
foreach($key in @($entries.Keys | Where-Object { $_.StartsWith('message.literal.') })) {
    $literal=[Text.Encoding]::UTF8.GetString([Convert]::FromHexString($key.Substring(16)))
    $target=History-Body $entries[$key]
    $entries['message.value.message.history.'+(Hex-Text (History-Body $literal))]=$target
    $entries['message.value.message.history.'+(Hex-Text (History-Body (History-Case $literal)))]=$target
}
# The native SOUND_NORMAL slot selects one of these complete SND_PRES words.
# Keep the same selected word identity inside the history sentence grammar.
foreach($entry in $resource.entries | Where-Object key -eq 'SND_PRES') {
    $entries['message.value.message.history.sound.'+(Hex-Text $entry.source)]=$entry.target
}
$catalog=[Collections.Generic.List[string]]::new()
$catalog.Add('# Generated from decompiled native message sources and selected resource templates.')
foreach($entry in $entries.GetEnumerator()) {$catalog.Add($entry.Key+"`t"+$entry.Value)}
[IO.File]::WriteAllLines((Join-Path $taskRoot 'catalog/zh-CN/messages.tsv'),$catalog,[Text.UTF8Encoding]::new($false))
Write-Output "Generated catalog/zh-CN/messages.tsv: $($entries.Count) semantic entries."
