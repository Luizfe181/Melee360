$ErrorActionPreference='Stop'
$python=Join-Path $env:USERPROFILE '.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe'
if(!(Test-Path $python)){$python='python.exe'}
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
& $python (Join-Path $PSScriptRoot 'diagnostics\generate_calendar.py') --base $base --project $PSScriptRoot
if($LASTEXITCODE -ne 0){throw 'Calendar generation failed'}
