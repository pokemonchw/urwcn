[CmdletBinding()]
param(
    [string[]]$Module,[string]$Toolchain,[string]$CMakePath,[string]$CompilerPath,[string]$BuildDirectory,[string]$ModuleSourceDirectory,
    [switch]$Publish,[switch]$Reload,[int[]]$TargetPid = 0,[string]$PackageDirectory,[string]$BatchId
)
$ErrorActionPreference = 'Stop'
if (!$BatchId -or $env:UWCN_COMPILE_BATCH -ne $BatchId) { throw 'Compilation must be submitted through root build.ps1 or build-queue.ps1.' }
$projectRoot = Split-Path -Parent $PSScriptRoot
$compilerDirectory = Split-Path -Parent $CompilerPath
$makePath = Join-Path $compilerDirectory $(if ($Toolchain -eq 'Linux') { 'make' } else { 'make.exe' })
$oldPath = $env:PATH
$env:PATH = $compilerDirectory + [IO.Path]::PathSeparator + $oldPath
try {
    $generator = if ($Toolchain -eq 'Linux') { 'Unix Makefiles' } else { 'MinGW Makefiles' }
    $moduleSourceCMake = $ModuleSourceDirectory.Replace('\','/')
    & $CMakePath -S $projectRoot -B $BuildDirectory -G $generator "-DCMAKE_CXX_COMPILER=$CompilerPath" "-DCMAKE_MAKE_PROGRAM=$makePath" "-DUWCN_MODULE_SOURCE_ROOT:PATH=$moduleSourceCMake" '-DCMAKE_BUILD_TYPE=Release'
    if ($LASTEXITCODE -ne 0) { throw "CMake configuration failed with exit code $LASTEXITCODE" }
    $buildArguments = @('--build',$BuildDirectory,'--parallel')
    if ($Module) { $buildArguments += '--target'; $buildArguments += @($Module | ForEach-Object { "uwcn_$_" }) }
    & $CMakePath @buildArguments
    if ($LASTEXITCODE -ne 0) { throw "Incremental compilation failed with exit code $LASTEXITCODE" }
    if ($Publish) {
        $publishArguments = @{ BuildDirectory=$BuildDirectory; PackageDirectory=$PackageDirectory; BatchId=$BatchId; Reload=[bool]$Reload; TargetPid=$TargetPid }
        if ($Module) { $publishArguments.Module=$Module }
        & (Join-Path $projectRoot 'publish.ps1') @publishArguments
    } else { Write-Output 'Compilation complete. Formal delivery files were not published.' }
} finally { $env:PATH=$oldPath }
