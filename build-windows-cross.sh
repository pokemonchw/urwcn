#!/bin/bash
# Linux -> Windows x86; all compilation and publication belongs to build.ps1.
set -euo pipefail

project_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
powershell="$project_root/.toolchains/powershell/pwsh"

if (( $# == 0 )); then
    set -- -Publish
fi

exec "$powershell" -NoLogo -NoProfile -NonInteractive \
    -File "$project_root/build.ps1" -Toolchain MinGW "$@"
