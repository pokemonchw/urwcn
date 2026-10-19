$ErrorActionPreference='Stop'
$lines=Get-Content "$PSScriptRoot/settlement-requirement-descriptors-ghidra.c"
$records=[System.Collections.Generic.List[object]]::new()
$memory=@{};$branch='initial'
function Save-Branch {
    foreach($entry in @(@(0x21308e0,'craft-requirement'),@(0x2130944,'craft-requirement-description'))) {
        $start=[int]$entry[0];$bytes=[System.Collections.Generic.List[byte]]::new()
        for($offset=0;$offset -lt 100;$offset++) {
            if(-not $memory.ContainsKey($start+$offset)){break}
            $b=$memory[$start+$offset]
            if($b -eq 0){break}
            $bytes.Add($b)
        }
        if($bytes.Count){$records.Add([pscustomobject]@{domain=$entry[1];source=[Text.Encoding]::ASCII.GetString($bytes.ToArray());branch=$branch})}
    }
}
foreach($line in $lines) {
    if($line -match '^/\* Function 0046c8b0'){Save-Branch;break}
    if($line -match '^\s*case ([^:]+):'){Save-Branch;$memory=@{};$branch=$Matches[1]}
    if($line -match '^\s*if \(DAT_02130a7c == ([^)]+)\)'){Save-Branch;$memory=@{};$branch=$Matches[1]}
    if($line -notmatch '^\s*(?:_?DAT_|uRam)(02130[89][0-9a-f]{2})(?:_(\d+))?(?:\._(\d+)_(\d+)_)?\s*=\s*(.*);$'){continue}
    $addr=[Convert]::ToInt32($Matches[1],16)+[int]$Matches[2]+[int]$Matches[3]
    $size=$Matches[4];$expression=$Matches[5];$payload=$null
    if($expression -match "^'(.*)'$") {
        $char=$Matches[1]
        $payload=if($char -eq '\0') {@([byte]0)} elseif($char -eq "\'") {@([byte]39)} else {@([byte][char]$char)}
    } elseif($expression -match '^CONCAT\d(\d)\([^,]+,(?:0x|&DAT_)([0-9a-f]+)\)$') {
        $width=[int]$Matches[1];$number=[Convert]::ToUInt64($Matches[2],16)
        $payload=[BitConverter]::GetBytes($number)[0..($width-1)]
    } elseif($expression -match '^CONCAT\d(\d)\([^,]+,(\d+)\)$') {
        $width=[int]$Matches[1];$number=[uint64]$Matches[2]
        $payload=[BitConverter]::GetBytes($number)[0..($width-1)]
    } elseif($expression -match '(?:<< 8|& 0xffffff00)$') {
        $payload=@([byte]0)
    } elseif($expression -match '^(?:0x([0-9a-f]+)|(0))$') {
        $number=if($Matches[1]){[Convert]::ToUInt64($Matches[1],16)}else{[uint64]0}
        $width=if($size){[int]$size}else{8}
        $payload=[BitConverter]::GetBytes($number)[0..($width-1)]
    }
    if($null -ne $payload){for($i=0;$i -lt $payload.Count;$i++){$memory[$addr+$i]=[byte]$payload[$i]}}
}
$records | Sort-Object domain,source -Unique | Export-Csv "$PSScriptRoot/settlement-craft-inline-literals.tsv" -NoTypeInformation -Delimiter "`t" -Encoding utf8
$all=Get-Content "$PSScriptRoot/settlement-requirement-descriptors-ghidra.c" -Raw
[regex]::Matches($all,'return "([^"]+)";') | ForEach-Object {$_.Groups[1].Value.Replace("\'","'")} | Sort-Object -Unique | Set-Content "$PSScriptRoot/settlement-craft-return-literals.txt" -Encoding utf8
