$ErrorActionPreference='Stop'
$root=Join-Path $PSScriptRoot '../..'
$rows=Get-ChildItem "$root/translations/messages_embedded" -Filter 'values*.tsv' | ForEach-Object {
    foreach($line in Get-Content -LiteralPath $_.FullName) {
        $p=$line -split "`t",3
        if($p.Count -eq 3 -and -not $p[0].StartsWith('#')) {
            [pscustomobject]@{domain=$p[0];source=$p[1];target=$p[2]}
        }
    }
}
function Quote([string]$s) {'"'+$s.Replace('\','\\').Replace('"','\"').Replace("`r",'\r').Replace("`n",'\n')+'"'}
$output=[Collections.Generic.List[string]]::new()
$output.Add('// Exact source atoms from the statically recovered material/name inventories.')
$output.Add('constexpr Atom atoms[]{')
$seen=[Collections.Generic.HashSet[string]]::new([StringComparer]::Ordinal)
foreach($domain in @('crafted-material','material.cut-native','material.animal','material.field','material.word','item','nameatom','menu.recipe','item.alternate')) {
    foreach($row in $rows | Where-Object domain -CEQ $domain | Sort-Object source -CaseSensitive) {
        if($row.source -and -not $row.source.Contains('%') -and $seen.Add($row.source)) {
            $output.Add('    {'+(Quote $row.source)+','+(Quote $domain)+'},')
        }
    }
}
$output.Add('};')
$output.Add('constexpr const char* animals[]{')
foreach($row in $rows | Where-Object domain -CEQ 'material.animal' | Sort-Object source -CaseSensitive -Unique) {
    $output.Add('    '+(Quote $row.source)+',')
}
$output.Add('};')
$output.Add('constexpr const char* trees[]{')
foreach($row in $rows | Where-Object domain -CEQ 'tree' | Sort-Object source -CaseSensitive -Unique) {
    $output.Add('    '+(Quote $row.source)+',')
}
$output.Add('};')
$output.Add('constexpr Pattern crafted_patterns[]{')
# More specific authored literal pieces precede their generic recipe relatives.
foreach($row in $rows | Where-Object domain -CEQ 'crafted-name-format' | Where-Object source -CNE '%s ' | Sort-Object @{Expression={$_.source.Length};Descending=$true},source -Unique) {
    $output.Add('    {'+(Quote $row.source)+'},')
}
$output.Add('};')
$output.Add('constexpr Wood woods[]{')
$woodRows=$rows | Where-Object domain -CEQ 'item.wood'
$trees=$rows | Where-Object domain -CEQ 'tree'
$woodSeen=[Collections.Generic.HashSet[string]]::new([StringComparer]::Ordinal)
$woodFormats=[Collections.Generic.Dictionary[string,string]]::new([StringComparer]::Ordinal)
foreach($wood in $woodRows) {
    foreach($tree in $trees) {
        $name=$wood.source
        $lower=$name.ToLowerInvariant()
        $position=$lower.IndexOf('wooden ')
        $count=6
        if($position -lt 0) {$position=$lower.IndexOf('wood ');$count=4}
        if($position -ge 0) {
            $pattern=$name.Substring(0,$position)+'%s'+$name.Substring($position+$count)
            $name=$name.Substring(0,$position)+$tree.source+$name.Substring($position+$count)
        }
        elseif(($position=$lower.IndexOf(' wood')) -ge 0) {
            $pattern=$name.Substring(0,$position+1)+'%s'
            $name=$name.Substring(0,$position+1)+$tree.source
        }
        else {continue}
        # 451770's final 4D4020 normalizes the whole returned material name.
        $name=$name.ToLowerInvariant()
        $pattern=$pattern.ToLowerInvariant();$woodFormats[$pattern]=$wood.target
        if($woodSeen.Add($name)) {$output.Add('    {'+(Quote $name)+','+(Quote $pattern)+','+(Quote $tree.source)+'},')}
    }
}
$output.Add('};')
[IO.File]::WriteAllLines((Join-Path $root 'modules/adapter/windows_message_crafted_item_atoms.inc'),$output,[Text.UTF8Encoding]::new($false))
$translated=foreach($pattern in $woodFormats.Keys | Sort-Object) {'crafted-wood-format'+"`t"+$pattern+"`t"+$woodFormats[$pattern]}
[IO.File]::WriteAllLines((Join-Path $root 'translations/messages_embedded/values.crafted-wood.zh-CN.tsv'),$translated,[Text.UTF8Encoding]::new($false))
