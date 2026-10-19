param([string]$GameDirectory='D:/program/steam/steamapps/common/UnRealWorld')
$ErrorActionPreference='Stop'
$root=Split-Path (Split-Path $PSScriptRoot -Parent) -Parent
# 4B2BF5 reads one 0xAC descriptor; 451690 reads its +0x31 name field.
$bytes=[IO.File]::ReadAllBytes((Join-Path $GameDirectory 'CONSTANT.OBJ'))
$records=for($offset=0;$offset -lt $bytes.Length;$offset+=0xac) {
    $nameEnd=$offset+9;while($bytes[$nameEnd]) {$nameEnd++}
    $materialEnd=$offset+0x31;while($bytes[$materialEnd]) {$materialEnd++}
    [pscustomobject]@{
        index=$offset/0xac;category=$bytes[$offset];id=[BitConverter]::ToInt32($bytes,$offset+4)
        name=[Text.Encoding]::ASCII.GetString($bytes,$offset+9,$nameEnd-$offset-9)
        material=[Text.Encoding]::ASCII.GetString($bytes,$offset+0x31,$materialEnd-$offset-0x31)
    }
}
$records | Export-Csv (Join-Path $PSScriptRoot 'settlement-item-material-fields.tsv') -Delimiter "`t" -NoTypeInformation
$terms=Get-ChildItem (Join-Path $root 'translations/messages_embedded') -Filter 'values*.tsv' |
    Where-Object Name -ne 'values.materials.zh-CN.tsv' |
    ForEach-Object {Import-Csv $_.FullName -Delimiter "`t" -Header domain,source,target}
$domains=@('item','npc','material','nameatom','menu.recipe','quality')
$dictionary=[Collections.Generic.Dictionary[string,string]]::new([StringComparer]::OrdinalIgnoreCase)
foreach($term in $terms) {
    if($term.domain -in $domains -and $term.source -match '^[a-zA-Z][a-zA-Z''-]*$') {$dictionary[$term.source]=$term.target}
}
# This inventories native English first/last-word operands. Translation is
# authored separately and is never obtained by slicing the Chinese full name.
$wordRows=foreach($term in $terms) {
    if($term.domain -in $domains -and $term.source -notmatch '[%{}\d\[\](|/]') {
        $pieces=$term.source.Trim().Split(' ')
        foreach($word in @($pieces[0],$pieces[-1])) {
            if($word) {[pscustomobject]@{word=$word.ToLowerInvariant();source=$term.source;domain=$term.domain;target=$dictionary[$word]}}
        }
    }
}
$wordRows | Sort-Object word,source -Unique | Export-Csv (Join-Path $PSScriptRoot 'settlement-material-word-sources.tsv') -Delimiter "`t" -NoTypeInformation
