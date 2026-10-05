param([string]$SystemRoot='C:\Users\luizf\Documents\melee\sys',[string]$AssetsRoot='C:\Users\luizf\Documents\melee_extraido')
$ErrorActionPreference='Stop'
$python=Join-Path $env:USERPROFILE '.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe'
& $python (Join-Path $PSScriptRoot 'diagnostics\generate_dvd_manifest.py') --sys $SystemRoot --assets $AssetsRoot --project $PSScriptRoot
if($LASTEXITCODE -ne 0){throw 'DVD manifest generation failed'}
