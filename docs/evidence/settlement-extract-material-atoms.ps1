$ErrorActionPreference='Stop'
$taskExe=[IO.File]::ReadAllBytes('D:/program/steam/steamapps/common/UnRealWorld/urw.exe')
$taskAsm=Get-Content -LiteralPath build/windows-text-disassembly.txt
$taskFunctions=@(0x4b1320,0x4b2b70)
$taskRanges=[Collections.Generic.List[object]]::new();foreach($fn in $taskFunctions){if($fn-ge0x4b1320-and$fn-lt0x4bcf90){$taskRanges.Add($fn)}}
$taskRegs=@{};$taskFields=@{name=0x5915289};$taskBuffers=@{};$taskOrigins=@{};foreach($key in $taskFields.Keys){$taskBuffers[$key]=New-Object 'int[]' 40;for($i=0;$i-lt40;$i++){$taskBuffers[$key][$i]=-1}}
$taskRows=[Collections.Generic.List[object]]::new();$fn=0
$taskDirty=@{}
function Flush-Atoms {
foreach($key in @($taskDirty.Keys)){$vals=$taskBuffers[$key];$end=[Array]::IndexOf($vals,0);$limit=if($key-eq'name'){40}else{10};if($end-gt0-and$end-lt$limit){$good=$true;for($i=0;$i-lt$end;$i++){if($vals[$i]-lt32-or$vals[$i]-gt126){$good=$false}};if($good){$s=[Text.Encoding]::ASCII.GetString([byte[]]$vals[0..($end-1)]);$taskRows.Add([pscustomobject]@{domain=if($key-eq'name'){'material.field'}else{'sound'};source=$s;function_va=('{0:x8}'-f$fn);write_begin=$taskOrigins[$key];write_end=('{0:x8}'-f$taskDirty[$key]);field=$key})}}};$taskDirty.Clear()
}
foreach($line in $taskAsm){if($line-notmatch '^\s*([0-9a-f]+):\s+(?:[0-9a-f]{2}\s+)+\s+([a-z]+)\s*(.*)$'){continue};$va=[Convert]::ToInt64($Matches[1],16);$op=$Matches[2];$operands=$Matches[3];if($taskRanges.Contains($va)){$fn=$va;$taskRegs=@{};foreach($kk in $taskFields.Keys){for($ii=0;$ii-lt40;$ii++){$taskBuffers[$kk][$ii]=-1}}};if($va-lt0x4b1320-or$va-ge0x4bcf90){continue};if($op-eq'call'){Flush-Atoms;$taskRegs=@{};continue};if($op-eq'ret'-or$op.StartsWith('j')){Flush-Atoms};if($op-eq'xor'-and$operands-match '^([a-z0-9]+),\1$'){$taskRegs[$Matches[1]]=New-Object 'byte[]' 16;continue};if($op-notin@('mov','movzx','movsx','movq','movups','movaps')){if($operands-match '^(eax|ebx|ecx|edx|esi|edi),'){$taskRegs.Remove($Matches[1])};continue};if($operands-notmatch '^([^,]+),(.*)$'){continue};$dest=$Matches[1];$source=$Matches[2];$value=$null
if($source-match '^0x([0-9a-f]+)$'){$value=[BitConverter]::GetBytes([Convert]::ToInt64($Matches[1],16))}elseif($source-match '^(?:XMMWORD PTR |QWORD PTR |DWORD PTR |WORD PTR |BYTE PTR )?ds:0x([0-9a-f]+)$'){$a=[Convert]::ToInt64($Matches[1],16);$o=$a-0x400e00;if($o-ge0x18b200-and$o-lt0x1e0000){$value=[byte[]]$taskExe[$o..($o+15)]}}elseif($taskRegs.ContainsKey($source)){$value=$taskRegs[$source]}elseif($source-match '^([abcd])l$' -and $taskRegs.ContainsKey($Matches[1]+'x')){$value=$taskRegs[$Matches[1]+'x']}elseif($source-match '^([abcd])[xl]$' -and $taskRegs.ContainsKey('e'+$Matches[1]+'x')){$value=$taskRegs['e'+$Matches[1]+'x']}
if($op-eq'movzx'-and$null-ne$value){$wide=New-Object 'byte[]' 16;$n=if($source.StartsWith('BYTE')){1}else{2};[Array]::Copy($value,$wide,$n);$value=$wide};if($dest-match '^(eax|ebx|ecx|edx|esi|edi|ax|bx|cx|dx|al|bl|cl|dl|xmm[0-7])$'){if($dest-match '^e([abcd])x$'){$taskRegs.Remove($Matches[1]+'x');$taskRegs.Remove($Matches[1]+'l')}if($null-eq$value){$taskRegs.Remove($dest)}else{$taskRegs[$dest]=$value};continue}
if($dest-notmatch '^(?:(XMMWORD|QWORD|DWORD|WORD|BYTE) PTR )?ds:0x([0-9a-f]+)$'){continue};$addr=[Convert]::ToInt64($Matches[2],16);$size=switch($Matches[1]){'XMMWORD'{16}'QWORD'{8}'DWORD'{4}'WORD'{2}'BYTE'{1}default{if($source-match'^[abcd]l$'){1}elseif($source-match'^[abcd]x$'){2}else{4}}}
foreach($key in $taskFields.Keys){$b=$taskFields[$key];$limit=if($key-eq'name'){40}else{10};if($addr-lt$b-or$addr-ge$b+$limit){continue};if($addr-eq$b){$taskOrigins[$key]=('{0:x8}'-f$va)};for($i=0;$i-lt$size-and$addr-$b+$i-lt$limit;$i++){$taskBuffers[$key][$addr-$b+$i]=if($null-eq$value){-1}else{[int]$value[$i]}};$taskDirty[$key]=$va}
}
$taskRows|Sort-Object domain,source -Unique|Export-Csv -Delimiter "`t" -LiteralPath (Join-Path $PSScriptRoot 'settlement-material-initializer-atoms.tsv') -NoTypeInformation




