#Requires -Version 7.0
[CmdletBinding()]
param(
    [ValidateSet('launcher','loader','catalog','semantic','render','layout','main_menu','adapter')][string[]]$Module,
    [ValidateSet('MinGW')][string]$Toolchain = 'MinGW',
    [string]$CMakePath = (Join-Path $PSScriptRoot '.toolchains/x86/w64devkit/bin/cmake.exe'),
    [string]$CompilerPath = (Join-Path $PSScriptRoot '.toolchains/x86/w64devkit/bin/g++.exe'),
    [string]$BuildDirectory = (Join-Path $PSScriptRoot 'build/mingw-x86'),
    [switch]$Publish,
    [switch]$Reload,
    [int[]]$TargetPid = 0,
    [string]$PackageDirectory = (Join-Path $PSScriptRoot 'package')
)
$ErrorActionPreference = 'Stop'
$TargetPid = @($TargetPid | Sort-Object -Unique)
if ($Reload) {
    $Publish = $true
    if ($TargetPid.Count -eq 0 -or @($TargetPid | Where-Object { $_ -le 0 }).Count -gt 0 -or !$Module -or $Module -contains 'loader' -or $Module -contains 'launcher') { throw '-Reload requires positive TargetPid values and an explicit compatible business Module set.' }
}
$queue = Join-Path $PSScriptRoot 'build/.compile-queue'
foreach ($part in @('pending','batches','results')) { New-Item -ItemType Directory -Path (Join-Path $queue $part) -Force | Out-Null }
$requestId = [guid]::NewGuid().ToString('N')
$configuration = [ordered]@{
    Toolchain=$Toolchain
    CMakePath=[IO.Path]::GetFullPath($CMakePath)
    CompilerPath=[IO.Path]::GetFullPath($CompilerPath)
    BuildDirectory=[IO.Path]::GetFullPath($BuildDirectory)
    Publish=[bool]$Publish
    Reload=[bool]$Reload
    TargetPid=$TargetPid
    PackageDirectory=[IO.Path]::GetFullPath($PackageDirectory)
}
$configurationText = $configuration | ConvertTo-Json -Compress
$sha = [Security.Cryptography.SHA256]::Create()
$queueKey = ([BitConverter]::ToString($sha.ComputeHash([Text.Encoding]::UTF8.GetBytes($PSScriptRoot.ToLowerInvariant())))).Replace('-','').Substring(0,24)
$sha.Dispose()
$stateMutex = [Threading.Mutex]::new($false, "Local\UWCnQueueState-$queueKey")
$runnerMutex = [Threading.Mutex]::new($false, "Local\UWCnQueueRunner-$queueKey")
$configurationFile = Join-Path $queue 'configuration.json'
$request = [ordered]@{ RequestId=$requestId; Modules=@($Module | Sort-Object -Unique); FullGraph=(!$Module); Configuration=$configuration; SubmittedAt=[DateTimeOffset]::UtcNow.ToString('o') }
$stateMutex.WaitOne() | Out-Null
try {
    if (Test-Path -LiteralPath $configurationFile) {
        $existing = Get-Content -LiteralPath $configurationFile -Raw
        if ($existing.Trim() -ne $configurationText) { throw 'The active compile queue uses different Toolchain/CMakePath/CompilerPath/BuildDirectory/Publish/Reload/TargetPid/PackageDirectory. Wait for it to finish before changing these parameters.' }
    } else { [IO.File]::WriteAllText($configurationFile,$configurationText,[Text.UTF8Encoding]::new($false)) }
    [IO.File]::WriteAllText((Join-Path $queue "pending/$requestId.json"),($request | ConvertTo-Json -Depth 8),[Text.UTF8Encoding]::new($false))
} finally { $stateMutex.ReleaseMutex() }
Write-Host "Queued request $requestId"
$runner = $runnerMutex.WaitOne(0)
try {
    if ($runner) {
        while ($true) {
            $stateMutex.WaitOne() | Out-Null
            try {
                $pending = @(Get-ChildItem -LiteralPath (Join-Path $queue 'pending') -Filter '*.json' | Sort-Object Name)
                if ($pending.Count -eq 0) {
                    Remove-Item -LiteralPath $configurationFile
                    $runnerMutex.ReleaseMutex()
                    $runner=$false
                    break
                }
                $batchId = [guid]::NewGuid().ToString('N')
                $batchDirectory = Join-Path $queue "batches/$batchId"
                New-Item -ItemType Directory -Path $batchDirectory -Force | Out-Null
                $requests = @()
                foreach ($entry in $pending) {
                    $requests += Get-Content -LiteralPath $entry.FullName -Raw | ConvertFrom-Json
                    Move-Item -LiteralPath $entry.FullName -Destination (Join-Path $batchDirectory $entry.Name)
                }
            } finally { $stateMutex.ReleaseMutex() }
            $fullGraph = @($requests | Where-Object FullGraph).Count -gt 0
            $modules = @($requests | ForEach-Object Modules | Sort-Object -Unique)
            $log = Join-Path $queue "batches/$batchId.log"
            $success = $false
            $failure = ''
            $env:UWCN_COMPILE_BATCH = $batchId
            try {
                $options = @{
                    Toolchain=$Toolchain; CMakePath=$configuration.CMakePath; CompilerPath=$configuration.CompilerPath
                    BuildDirectory=$configuration.BuildDirectory; PackageDirectory=$configuration.PackageDirectory
                    Publish=[bool]$Publish; Reload=[bool]$Reload; TargetPid=$TargetPid; BatchId=$batchId
                }
                if (!$fullGraph) { $options.Module=$modules }
                & (Join-Path $PSScriptRoot 'cmake/build-once.ps1') @options *>&1 | Tee-Object -FilePath $log
                $success = $true
            } catch {
                $failure = $_.ToString()
                $failure | Out-File -LiteralPath $log -Append -Encoding utf8
            } finally { Remove-Item Env:UWCN_COMPILE_BATCH }
            foreach ($entry in $requests) {
                $result = [ordered]@{ RequestId=$entry.RequestId; BatchId=$batchId; Success=$success; Error=$failure; Modules=$modules; FullGraph=$fullGraph; Log=$log; PublishRequested=[bool]$Publish; ReloadRequested=[bool]$Reload; TargetPid=$TargetPid; CompletedAt=[DateTimeOffset]::UtcNow.ToString('o') }
                $resultPath=Join-Path $queue "results/$($entry.RequestId).json"
                $resultTemporary="$resultPath.tmp"
                [IO.File]::WriteAllText($resultTemporary,($result | ConvertTo-Json -Depth 8),[Text.UTF8Encoding]::new($false))
                Move-Item -LiteralPath $resultTemporary -Destination $resultPath
            }
        }
    }
    $resultFile = Join-Path $queue "results/$requestId.json"
    while (!(Test-Path -LiteralPath $resultFile)) { Start-Sleep -Milliseconds 200 }
    $completed = Get-Content -LiteralPath $resultFile -Raw | ConvertFrom-Json
    Write-Host "Request $requestId; batch $($completed.BatchId); result $resultFile; log $($completed.Log)"
    if (!$completed.Success) { throw "Compile batch failed: $($completed.Error)" }
} finally {
    if ($runner) { $runnerMutex.ReleaseMutex() }
    $runnerMutex.Dispose(); $stateMutex.Dispose()
}
