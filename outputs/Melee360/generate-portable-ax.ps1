$ErrorActionPreference='Stop'
$python=Join-Path $env:USERPROFILE '.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe'
Push-Location (Resolve-Path (Join-Path $PSScriptRoot '..\..'))
try { & $python (Join-Path $PSScriptRoot 'diagnostics\generate_portable_ax.py'); if($LASTEXITCODE){throw 'AX CPU generation failed'} } finally { Pop-Location }
