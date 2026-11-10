[CmdletBinding()]
param(
    [string[]]$Module,[string]$Toolchain,[string]$CMakePath,[string]$CompilerPath,[string]$BuildDirectory,[string]$ModuleSourceDirectory,
    [switch]$Publish,[switch]$Reload,[int[]]$TargetPid = 0,[string]$WinePrefix,[string]$WinePath,[string]$PackageDirectory,[string]$BatchId
)
$ErrorActionPreference = 'Stop'
if (!$BatchId -or $env:UWCN_COMPILE_BATCH -ne $BatchId) { throw 'Compilation must be submitted through root build.ps1 or build-queue.ps1.' }
$projectRoot = Split-Path -Parent $PSScriptRoot
$compilerDirectory = Split-Path -Parent $CompilerPath
$makePath = if ($IsLinux) { '/usr/bin/make' } else { Join-Path $compilerDirectory 'make.exe' }
$crossCompile = $IsLinux -and $Toolchain -eq 'MinGW'
$oldPath = $env:PATH
$compilerEnvironment = @{}
try {
    if ($crossCompile) {
        # Match dfcn's explicit toolchain environment for every queue entry.
        foreach ($name in @('CC','CXX','CFLAGS','CXXFLAGS','CPPFLAGS','LDFLAGS','LDLIBS',
                            'PKG_CONFIG','PKG_CONFIG_PATH','PKG_CONFIG_LIBDIR','PKG_CONFIG_SYSROOT_DIR',
                            'GCC_EXEC_PREFIX','COMPILER_PATH','LIBRARY_PATH','CPATH','C_INCLUDE_PATH','CPLUS_INCLUDE_PATH',
                            'CMAKE_TOOLCHAIN_FILE','CMAKE_GENERATOR','CMAKE_GENERATOR_PLATFORM','CMAKE_GENERATOR_TOOLSET')) {
            $compilerEnvironment[$name] = [Environment]::GetEnvironmentVariable($name)
            [Environment]::SetEnvironmentVariable($name,[NullString]::Value)
        }
        $env:PATH = $compilerDirectory + ':/usr/bin:/bin'
    } else {
        $env:PATH = $compilerDirectory + [IO.Path]::PathSeparator + $oldPath
    }
    $generator = if ($IsLinux) { 'Unix Makefiles' } else { 'MinGW Makefiles' }
    $moduleSourceCMake = $ModuleSourceDirectory.Replace('\','/')
    $configureArguments = @('-S',$projectRoot,'-B',$BuildDirectory,'-G',$generator,"-DCMAKE_CXX_COMPILER=$CompilerPath","-DCMAKE_MAKE_PROGRAM=$makePath","-DUWCN_MODULE_SOURCE_ROOT:PATH=$moduleSourceCMake",'-DCMAKE_BUILD_TYPE=Release')
    if ($crossCompile) {
        $configureArguments += "-DCMAKE_TOOLCHAIN_FILE=$(Join-Path $PSScriptRoot 'windows-x86.cmake')"
    }
    Write-Output "Toolchain: $Toolchain; compiler: $CompilerPath; build directory: $BuildDirectory"
    & $CMakePath @configureArguments
    if ($LASTEXITCODE -ne 0) { throw "CMake configuration failed with exit code $LASTEXITCODE" }
    $buildArguments = @('--build',$BuildDirectory,'--parallel')
    if ($Module) { $buildArguments += '--target'; $buildArguments += @($Module | ForEach-Object { "uwcn_$_" }) }
    & $CMakePath @buildArguments
    if ($LASTEXITCODE -ne 0) { throw "Incremental compilation failed with exit code $LASTEXITCODE" }
    if ($Publish) {
        $publishArguments = @{ Toolchain=$Toolchain; BuildDirectory=$BuildDirectory; PackageDirectory=$PackageDirectory; BatchId=$BatchId; Reload=[bool]$Reload; TargetPid=$TargetPid }
        $publishArguments.WinePrefix=$WinePrefix; $publishArguments.WinePath=$WinePath
        if ($Module) { $publishArguments.Module=$Module }
        & (Join-Path $projectRoot 'publish.ps1') @publishArguments
    } else {
        Write-Output "Compilation complete. Build output: $(Join-Path $BuildDirectory 'out')"
        Write-Output 'Formal delivery files were not published. Use -Publish to update them.'
    }
} finally {
    $env:PATH=$oldPath
    foreach ($name in $compilerEnvironment.Keys) {
        [Environment]::SetEnvironmentVariable($name,($compilerEnvironment[$name] ?? [NullString]::Value))
    }
}
