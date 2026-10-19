#Requires -Version 7.0
[CmdletBinding()]
param(
    [string[]]$Module,
    [Parameter(Mandatory)][string]$BuildDirectory,
    [string]$PackageDirectory = (Join-Path $PSScriptRoot 'package'),
    [Parameter(Mandatory)][string]$BatchId,
    [switch]$Reload,
    [int[]]$TargetPid = 0
)
$ErrorActionPreference = 'Stop'
if ($env:UWCN_COMPILE_BATCH -ne $BatchId) { throw 'Formal publication belongs to the root compile queue batch.' }
$PackageDirectory = [IO.Path]::GetFullPath($PackageDirectory)
$formalRoot = Split-Path -Parent $PackageDirectory
if ($formalRoot -ne [IO.Path]::GetFullPath($PSScriptRoot) -or (Split-Path -Leaf $PackageDirectory) -ne 'package') { throw 'Formal publication is restricted to root uwcn_launcher.exe and package/.' }
$allModules = @('catalog','semantic','render','layout','main_menu','adapter')
if (!$Module) { $Module = @('launcher','loader') + $allModules }
$TargetPid = @($TargetPid | Sort-Object -Unique)
if ($Reload -and ($TargetPid.Count -eq 0 -or @($TargetPid | Where-Object { $_ -le 0 }).Count -gt 0 -or $Module -contains 'loader' -or $Module -contains 'launcher')) { throw 'Reload only accepts compatible business modules and positive target PIDs.' }
$transaction = [guid]::NewGuid().ToString('N')
$stage = Join-Path $BuildDirectory "stage/$transaction"
New-Item -ItemType Directory -Path $stage -Force | Out-Null
$files = [Collections.Generic.List[object]]::new()
function Add-Candidate([string]$Source,[string]$Relative) {
    if (!(Test-Path -LiteralPath $Source -PathType Leaf)) { throw "Candidate source missing: $Source" }
    $destination = Join-Path $stage $Relative
    New-Item -ItemType Directory -Path (Split-Path -Parent $destination) -Force | Out-Null
    Copy-Item -LiteralPath $Source -Destination $destination
    $formal = if ($Relative -eq 'uwcn_launcher.exe') { Join-Path $formalRoot $Relative } else { Join-Path $PackageDirectory $Relative }
    $hash = (Get-FileHash -LiteralPath $destination -Algorithm SHA256).Hash.ToLowerInvariant()
    $changed = !(Test-Path -LiteralPath $formal -PathType Leaf) -or (Get-FileHash -LiteralPath $formal -Algorithm SHA256).Hash.ToLowerInvariant() -ne $hash
    $files.Add([pscustomobject]@{Relative=$Relative; Stage=$destination; Formal=$formal; Hash=$hash; Changed=$changed})
}
foreach ($name in $Module) {
    $relative = if ($name -eq 'launcher') { 'uwcn_launcher.exe' } elseif ($name -eq 'loader') { 'uwcn_loader.dll' } else { "modules/uwcn_$name.dll" }
    $output = if ($name -eq 'launcher') { 'uwcn_launcher.exe' } else { "uwcn_$name.dll" }
    Add-Candidate (Join-Path $BuildDirectory "out/$output") $relative
}
if ($Module -contains 'catalog') {
    foreach ($file in Get-ChildItem -LiteralPath (Join-Path $PSScriptRoot 'catalog') -File -Recurse) {
        $relative = 'catalog/' + [IO.Path]::GetRelativePath((Join-Path $PSScriptRoot 'catalog'),$file.FullName).Replace('\','/')
        Add-Candidate $file.FullName $relative
    }
}
foreach ($file in Get-ChildItem -LiteralPath (Join-Path $PSScriptRoot 'profiles') -File -Recurse) {
    $relative = 'profiles/' + [IO.Path]::GetRelativePath((Join-Path $PSScriptRoot 'profiles'),$file.FullName).Replace('\','/')
    Add-Candidate $file.FullName $relative
}
if (@($files | Where-Object Changed).Count -eq 0) { Write-Output 'Formal publication skipped: selected contents are unchanged.'; return }
$changes = @($files | Where-Object Changed)
$reloadModules = @($allModules | Where-Object { $name=$_; @($changes | Where-Object Relative -eq "modules/uwcn_$name.dll").Count -gt 0 })
if (@($changes | Where-Object { $_.Relative.StartsWith('catalog/') }).Count -gt 0 -and $reloadModules -notcontains 'catalog') { $reloadModules += 'catalog' }
$identities = [ordered]@{}
$currentManifest = Join-Path $PackageDirectory 'release.json'
if (Test-Path -LiteralPath $currentManifest) {
    $previous = Get-Content -LiteralPath $currentManifest -Raw | ConvertFrom-Json
    foreach ($property in $previous.files.PSObject.Properties) { $identities[$property.Name]=$property.Value }
}
foreach ($name in $allModules) {
    $relative = "modules/uwcn_$name.dll"
    $candidate = $files | Where-Object Relative -eq $relative
    if ($candidate) { $identities[$relative]=$candidate.Hash }
    elseif (Test-Path -LiteralPath (Join-Path $PackageDirectory $relative)) { $identities[$relative]=(Get-FileHash -LiteralPath (Join-Path $PackageDirectory $relative) -Algorithm SHA256).Hash.ToLowerInvariant() }
}
foreach ($file in $files | Where-Object { !$_.Relative.StartsWith('modules/') }) { $identities[$file.Relative]=$file.Hash }
$manifest = [ordered]@{ format='uwcn-release-v1'; host_abi=1; transaction=$transaction; compile_batch=$BatchId; changed_modules=$reloadModules; files=$identities }
$manifestSource = Join-Path $stage 'release-source.json'
[IO.File]::WriteAllText($manifestSource,($manifest | ConvertTo-Json -Depth 8),[Text.UTF8Encoding]::new($false))
Add-Candidate $manifestSource 'release.json'
$changes = @($files | Where-Object Changed)
$candidateLines = [Collections.Generic.List[string]]::new()
$candidateLines.Add('UWCN_CANDIDATE_V1')
foreach ($file in $files | Where-Object { $_.Relative -ne 'uwcn_launcher.exe' }) { $candidateLines.Add("$($file.Hash)`t$($file.Relative)") }
[IO.File]::WriteAllLines((Join-Path $stage 'candidate-files.tsv'),$candidateLines,[Text.UTF8Encoding]::new($false))
function Send-Control([int]$ProcessId,[string]$Command) {
    $client = [IO.Pipes.NamedPipeClientStream]::new('.',"uwcn-$ProcessId",[IO.Pipes.PipeDirection]::InOut)
    try {
        $client.Connect(15000)
        $encoding = [Text.UTF8Encoding]::new($false)
        $reader = [IO.StreamReader]::new($client,$encoding,$false,4096,$true)
        $commandBytes = $encoding.GetBytes($Command + "`n")
        $client.Write($commandBytes,0,$commandBytes.Length)
        $client.Flush()
        $response = $reader.ReadLine()
        $reader.Dispose()
        if (!$response) { throw 'Resident control channel closed without a receipt.' }
        return $response
    } finally { $client.Dispose() }
}
$targets = @(
    if ($Reload) {
        foreach ($processId in $TargetPid) {
            [pscustomobject][ordered]@{
                pid=$processId; prepare_receipt=$null; commit_receipt=$null; abort_receipt=$null; abort_error=$null
                ready=$false; commit_submitted=$false; applied=$false
            }
        }
    }
)
$archive = Join-Path $PSScriptRoot ("回收/{0}-{1}" -f (Get-Date -Format 'yyyyMMdd-HHmmss'),$transaction)
$record=[ordered]@{ transaction=$transaction; compile_batch=$BatchId; success=$false; error=$null; archive=$archive; changed_files=@($changes.Relative); runtime_requested=[bool]$Reload; runtime_receipts=$targets }
try {
    if ($Reload) {
        $mask=0
        foreach ($name in $reloadModules) { $mask = $mask -bor (1 -shl [array]::IndexOf($allModules,$name)) }
        foreach ($target in $targets) {
            $target.prepare_receipt=Send-Control $target.pid "PREPARE $transaction $mask $stage"
            if ($target.prepare_receipt -ne "ReadyToPublish $transaction") { throw "Resident prepare failed for PID $($target.pid): $($target.prepare_receipt)" }
            $target.ready=$true
        }
    }
    # Every existing destination is checked before the first old file is moved.
    $locks=[Collections.Generic.List[IDisposable]]::new()
    try {
        foreach ($file in $changes) {
            if (Test-Path -LiteralPath $file.Formal) { $locks.Add([IO.File]::Open($file.Formal,[IO.FileMode]::Open,[IO.FileAccess]::ReadWrite,[IO.FileShare]::None)) }
        }
    } finally { foreach ($fileLock in $locks) { $fileLock.Dispose() } }
    New-Item -ItemType Directory -Path $archive -Force | Out-Null
    foreach ($file in $changes) {
        if (Test-Path -LiteralPath $file.Formal) {
            $relative = [IO.Path]::GetRelativePath($PSScriptRoot,$file.Formal)
            $archived = Join-Path $archive $relative
            New-Item -ItemType Directory -Path (Split-Path -Parent $archived) -Force | Out-Null
            Move-Item -LiteralPath $file.Formal -Destination $archived
        }
    }
    foreach ($file in $changes | Where-Object Relative -ne 'release.json') {
        New-Item -ItemType Directory -Path (Split-Path -Parent $file.Formal) -Force | Out-Null
        Copy-Item -LiteralPath $file.Stage -Destination $file.Formal
    }
    $release = $files | Where-Object Relative -eq 'release.json'
    Copy-Item -LiteralPath $release.Stage -Destination $release.Formal
    if ($Reload) {
        foreach ($target in $targets) {
            $target.commit_submitted=$true
            $target.commit_receipt=Send-Control $target.pid "COMMIT $transaction"
            if (!$target.commit_receipt.StartsWith("Applied $transaction ")) { throw "Resident commit failed for PID $($target.pid): $($target.commit_receipt)" }
            foreach ($name in $reloadModules) {
                $hash=($files | Where-Object Relative -eq "modules/uwcn_$name.dll").Hash
                if ($target.commit_receipt -notmatch [regex]::Escape("$($name):$($hash):")) { throw "Applied receipt for PID $($target.pid) lacks matching identity for $name" }
            }
            $target.applied=$true
        }
    }
    $record.success=$true
} catch {
    $failure=$_.ToString()
    $record.error=$failure
    foreach ($target in $targets | Where-Object { $_.ready -and !$_.commit_submitted }) {
        try {
            $target.abort_receipt=Send-Control $target.pid "ABORT $transaction"
            Write-Warning "Resident transaction cancellation for PID $($target.pid): $($target.abort_receipt)"
        } catch {
            $target.abort_error=$_.ToString()
            Write-Warning "Resident cancellation failed for PID $($target.pid): $($target.abort_error)"
        }
    }
    throw "Publication failed: $failure. Archive location: $archive. No rollback or parallel delivery was created."
} finally {
    [IO.File]::WriteAllText((Join-Path $stage 'publication-result.json'),($record | ConvertTo-Json -Depth 8),[Text.UTF8Encoding]::new($false))
}
$receiptText = if ($Reload) { ($targets | ForEach-Object { "PID $($_.pid): $($_.commit_receipt)" }) -join '; ' } else { 'Runtime Applied was not requested.' }
Write-Output "Formal publication complete: $transaction; archive $archive; $receiptText"
