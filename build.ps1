#Requires -Version 7.0
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
& (Join-Path $PSScriptRoot 'build-queue.ps1') @PSBoundParameters
