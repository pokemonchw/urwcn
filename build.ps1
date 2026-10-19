#Requires -Version 7.0
[CmdletBinding()]
param(
    [string[]]$Module,
    [ValidateSet('MinGW')][string]$Toolchain = 'MinGW',
    [string]$CMakePath,
    [string]$CompilerPath,
    [string]$BuildDirectory,
    [switch]$Publish,
    [switch]$Reload,
    [int[]]$TargetPid = 0,
    [string]$PackageDirectory
)
$ErrorActionPreference = 'Stop'
& (Join-Path $PSScriptRoot 'build-queue.ps1') @PSBoundParameters
