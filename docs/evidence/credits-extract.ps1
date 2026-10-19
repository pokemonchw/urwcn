[CmdletBinding()]
param(
    [string]$Executable = 'D:\program\steam\steamapps\common\UnRealWorld\urw.exe',
    [string]$Objdump = (Join-Path $PSScriptRoot '..\..\.toolchains\x86\w64devkit\bin\objdump.exe'),
    [switch]$Decompile,
    [string]$Ghidra = 'C:\Users\WIN11\AppData\Local\Programs\dfcn-analysis-tools\ghidra_12.1.4_PUBLIC\support\analyzeHeadless.bat',
    [string]$JavaDirectory = 'C:\Users\WIN11\AppData\Local\Programs\dfcn-analysis-tools\jdk-25.0.4.1+1',
    [string]$ProjectDirectory = (Join-Path $PSScriptRoot '..\..\build\intro-ghidra'),
    [string]$ProjectName = 'uwcn-intro'
)

# Read-only offline extraction of PE bytes and instructions; never runs the EXE.
$creditsImage = [IO.File]::ReadAllBytes($Executable)
$creditsPe = [BitConverter]::ToInt32($creditsImage, 0x3c)
$creditsSectionCount = [BitConverter]::ToUInt16($creditsImage, $creditsPe + 6)
$creditsOptionalSize = [BitConverter]::ToUInt16($creditsImage, $creditsPe + 20)
$creditsSectionTable = $creditsPe + 24 + $creditsOptionalSize
$creditsSections = for ($creditsIndex = 0; $creditsIndex -lt $creditsSectionCount; $creditsIndex++) {
    $creditsSection = $creditsSectionTable + 40 * $creditsIndex
    [pscustomobject]@{
        Rva = [BitConverter]::ToUInt32($creditsImage, $creditsSection + 12)
        Size = [BitConverter]::ToUInt32($creditsImage, $creditsSection + 16)
        Offset = [BitConverter]::ToUInt32($creditsImage, $creditsSection + 20)
    }
}
function Read-CreditsString([uint32]$Rva) {
    $creditsOwner = $creditsSections | Where-Object { $Rva -ge $_.Rva -and $Rva -lt ($_.Rva + $_.Size) } | Select-Object -First 1
    $creditsStart = [int]($creditsOwner.Offset + $Rva - $creditsOwner.Rva)
    $creditsEnd = $creditsStart
    while ($creditsImage[$creditsEnd] -ne 0) { $creditsEnd++ }
    [Text.Encoding]::GetEncoding(28591).GetString($creditsImage, $creditsStart, $creditsEnd - $creditsStart)
}
$creditsFields = @(
    @('Title',0x1af448), @('Introduction1',0x1af460), @('Introduction2',0x1af4b8),
    @('Alexander',0x1af534), @('Andrew',0x1af56c), @('Artemis',0x1af5ac),
    @('Artemiy',0x1af5e8), @('Brian',0x1af624), @('Flap',0x1af664),
    @('Hamsolovski',0x1af6a4), @('Jeremy',0x1af6e4), @('Kerri',0x1af720),
    @('Kuu',0x1af768), @('Lani',0x1af7a0), @('Paulo',0x1af7e0),
    @('Plotinus',0x1af824), @('Rain',0x1af860), @('Scott',0x1af888),
    @('Shawn',0x1af8b0), @('Tommy',0x1af8d8), @('Wickerman',0x1af914),
    @('Countrymen1',0x1af950), @('Countrymen2',0x1af9d0),
    @('PhotoContributors',0x1afa18), @('Veterans',0x1afa60),
    @('PressKey',0x1af438), @('LineBreak',0x19416c)
)
$creditsRows = @("field`trva`toriginal_latin1")
$creditsRows += foreach ($creditsField in $creditsFields) {
    '{0}{1}{2:X8}{1}{3}' -f $creditsField[0], "`t", $creditsField[1], (Read-CreditsString $creditsField[1])
}
[IO.File]::WriteAllLines((Join-Path $PSScriptRoot 'credits-strings.tsv'), $creditsRows, [Text.UTF8Encoding]::new($false))

$creditsRanges = @(
    @('credits-disassembly.txt', 0x5244f0, 0x524690),
    @('credits-menu-disassembly.txt', 0x525920, 0x525ed4),
    @('credits-paragraph-disassembly.txt', 0x50eb40, 0x50efd0),
    @('credits-append-disassembly.txt', 0x5620c0, 0x562540),
    @('credits-title-disassembly.txt', 0x516270, 0x516760),
    @('credits-button-disassembly.txt', 0x514680, 0x514a60),
    @('credits-text-disassembly.txt', 0x50e5a0, 0x50e810),
    @('credits-key-wait-disassembly.txt', 0x4d3bf0, 0x4d3db0),
    @('credits-event-disassembly.txt', 0x4d1c00, 0x4d1fe0),
    @('credits-software-repaint-disassembly.txt', 0x50b720, 0x50b790)
)
foreach ($creditsRange in $creditsRanges) {
    $creditsOutput = & $Objdump -d -Mintel ('--start-address=0x{0:x}' -f $creditsRange[1]) ('--stop-address=0x{0:x}' -f $creditsRange[2]) $Executable
    [IO.File]::WriteAllLines((Join-Path $PSScriptRoot $creditsRange[0]), $creditsOutput, [Text.UTF8Encoding]::new($false))
}
$creditsDump = & $Objdump -s --start-address=0x5af438 --stop-address=0x5afab0 $Executable
[IO.File]::WriteAllLines((Join-Path $PSScriptRoot 'credits-string-bytes.txt'), $creditsDump, [Text.UTF8Encoding]::new($false))
$creditsMenuTable = & $Objdump -s --start-address=0x525ed4 --stop-address=0x525ef4 $Executable
[IO.File]::WriteAllLines((Join-Path $PSScriptRoot 'credits-menu-table.txt'), $creditsMenuTable, [Text.UTF8Encoding]::new($false))
Write-Output ('Offline credits extraction completed from {0}; SHA256 {1}' -f $Executable, (Get-FileHash -LiteralPath $Executable -Algorithm SHA256).Hash.ToLowerInvariant())

if ($Decompile) {
    $creditsProjectPath = [IO.Path]::GetFullPath($ProjectDirectory)
    $env:JAVA_HOME = $JavaDirectory
    $env:GHIDRA_HEADLESS_JAVA_OPTIONS = '-Dapplication.settingsdir={0}\settings -Djava.io.tmpdir={0}\cache' -f $creditsProjectPath
    & $Ghidra $creditsProjectPath $ProjectName -process ([IO.Path]::GetFileName($Executable)) -readOnly -noanalysis -scriptPath $PSScriptRoot -postScript credits_Decompile.java (Join-Path $PSScriptRoot 'credits-ghidra.c') -log (Join-Path $PSScriptRoot 'credits-ghidra.log') -scriptlog (Join-Path $PSScriptRoot 'credits-ghidra-script.log')
    exit $LASTEXITCODE
}
