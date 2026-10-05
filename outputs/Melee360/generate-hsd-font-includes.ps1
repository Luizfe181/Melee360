param([string]$Dol='C:\Users\luizf\Documents\melee\sys\main.dol')
$ErrorActionPreference='Stop'
$python=Join-Path $env:USERPROFILE '.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe'
if(!(Test-Path $python)){$python='python.exe'}
& $python (Join-Path $PSScriptRoot 'diagnostics\extract_hsd_fonts.py') --dol $Dol --project $PSScriptRoot
if($LASTEXITCODE -ne 0){throw 'Original HSD font extraction failed'}
