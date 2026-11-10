#Requires -Version 7.0
<#
.SYNOPSIS
Build through the shared compile queue. Toolchain selects the target platform.
.EXAMPLE
./build.ps1 -Toolchain MinGW
On Linux, cross-compile Windows x86 with the user-local MinGW-w64 16.2.0 toolchain.
.EXAMPLE
./build.ps1 -Toolchain MinGW -Module layout,render
Build the selected Windows modules in one queued batch.
#>
[CmdletBinding()]
param(
    [string[]]$Module,
    [ValidateSet('MinGW','Linux')][string]$Toolchain = $(if ($IsLinux) { 'Linux' } else { 'MinGW' }),
    [string]$CMakePath,
    [string]$CompilerPath,
    [string]$BuildDirectory,
    [string]$ModuleSourceDirectory,
    [switch]$Publish,
    [switch]$Reload,
    [int[]]$TargetPid = 0,
    [string]$PackageDirectory
)
$ErrorActionPreference = 'Stop'
if ($PSBoundParameters.ContainsKey('Module')) {
    $PSBoundParameters.Module = @($Module | ForEach-Object { $_ -split ',' })
}
& (Join-Path $PSScriptRoot 'build-queue.ps1') @PSBoundParameters
