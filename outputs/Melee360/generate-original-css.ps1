$ErrorActionPreference='Stop'
$python=Join-Path $env:USERPROFILE '.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe'
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
& $python (Join-Path $PSScriptRoot 'diagnostics\generate_original_css.py') --base $base --project $PSScriptRoot
if($LASTEXITCODE -ne 0){throw 'Original CSS extraction failed'}
