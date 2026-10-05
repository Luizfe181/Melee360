$ErrorActionPreference='Stop'
$python=Join-Path $env:USERPROFILE '.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe'
Push-Location (Resolve-Path (Join-Path $PSScriptRoot '..\..'))
try { & $python (Join-Path $PSScriptRoot 'diagnostics\generate_portable_thp.py'); if($LASTEXITCODE){throw 'THP CPU generation failed'} } finally { Pop-Location }
