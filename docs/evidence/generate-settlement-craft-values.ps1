$ErrorActionPreference='Stop'
$root=Join-Path $PSScriptRoot '../..'
$game='D:/program/steam/steamapps/common/UnRealWorld'
$authored=Get-Content "$root/translations/messages_embedded/values.craft-authored.zh-CN.tsv" | ForEach-Object {
    $domain,$source,$target=$_ -split "`t",3
    [pscustomobject]@{domain=$domain;source=$source;target=$target}
}
$items=Import-Csv "$root/translations/messages_embedded/values.zh-CN.tsv" -Delimiter "`t" | Where-Object domain -eq item
$names=@(Get-Content "$PSScriptRoot/settlement-craft-return-literals.txt")+
    @(Import-Csv "$PSScriptRoot/settlement-craft-inline-literals.tsv" -Delimiter "`t" | Where-Object domain -eq craft-requirement | Select-Object -ExpandProperty source)
$text=(Get-Content "$game/diy_glossary.txt","$game/biy_glossary.txt","$game/cookery_glossary.txt" -Raw)-join "`n"
$names+=@([regex]::Matches($text,'\{([^}]+)\}') | ForEach-Object {$_.Groups[1].Value})
$names+=@([regex]::Matches($text,"'([^']+)'") | ForEach-Object {$_.Groups[1].Value} | Where-Object {-not $_.StartsWith('+')})
# 46C8B0's last actual native branch returns base-item record names. Reuse the
# same proven item inventory in this dedicated requirement-name source domain.
$names+=@($items.source)
$generated=[System.Collections.Generic.List[string]]::new()
$unresolved=[System.Collections.Generic.List[string]]::new()
foreach($name in $names | Sort-Object -CaseSensitive -Unique) {
    if($authored | Where-Object {$_.domain -eq 'craft-requirement' -and $_.source -ceq $name}){continue}
    $row=$items | Where-Object source -eq $name | Select-Object -First 1
    if($row){$generated.Add("craft-requirement`t$name`t$($row.target)")}
    else{$unresolved.Add($name)}
}
$generated | Set-Content "$root/translations/messages_embedded/values.craft-items.zh-CN.tsv" -Encoding utf8
[IO.File]::WriteAllLines("$PSScriptRoot/settlement-craft-name-pending.txt",$unresolved,[Text.UTF8Encoding]::new($false))
