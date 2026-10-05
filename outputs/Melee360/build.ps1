param([ValidateSet('None','Raw','Compat')][string]$DecompMode = 'None',
      [ValidateSet('Debug','Release')][string]$Configuration = 'Debug')
$ErrorActionPreference = 'Stop'
if ($DecompMode -eq 'Compat') { & (Join-Path $PSScriptRoot 'generate-compat-headers.ps1'); & (Join-Path $PSScriptRoot 'generate-axfx.ps1'); & 'C:\Users\luizf\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe' (Join-Path $PSScriptRoot 'diagnostics\generate_training_stage.py'); if($LASTEXITCODE){throw 'Training/SSS generator failed'} }
if ($DecompMode -eq 'Compat') { & (Join-Path $PSScriptRoot 'generate-original-menu.ps1') }
if ($DecompMode -eq 'Compat') { & (Join-Path $PSScriptRoot 'generate-original-css.ps1') }
if ($DecompMode -eq 'Compat') { & (Join-Path $PSScriptRoot 'generate-card-icons.ps1') }
if ($DecompMode -eq 'Compat') { & (Join-Path $PSScriptRoot 'generate-portable-mtx.ps1') ; & (Join-Path $PSScriptRoot 'generate-portable-gx.ps1'); & (Join-Path $PSScriptRoot 'generate-portable-ax.ps1'); & (Join-Path $PSScriptRoot 'generate-portable-thp.ps1'); & (Join-Path $PSScriptRoot 'generate-portable-mcc.ps1'); & (Join-Path $PSScriptRoot 'generate-dvd-manifest.ps1'); & (Join-Path $PSScriptRoot 'generate-calendar.ps1'); & (Join-Path $PSScriptRoot 'generate-allocator.ps1') }
if ($DecompMode -eq 'Compat') { & (Join-Path $PSScriptRoot 'compile-intro-shaders.ps1') }
if (!(Test-Path "$env:XEDK\bin\win32\cl.exe")) { throw 'XEDK must point to the installed Xbox 360 SDK.' }
$builder = 'C:\Windows\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe'
$logs = Join-Path $PSScriptRoot 'logs'
New-Item -ItemType Directory -Force $logs | Out-Null
& $builder (Join-Path $PSScriptRoot 'Melee360.vcxproj') /t:Rebuild "/p:Configuration=$Configuration" '/p:Platform=Xbox 360' "/p:DecompMode=$DecompMode" /verbosity:minimal "/flp:logfile=$logs\$Configuration-$DecompMode.log;verbosity=normal"
if ($LASTEXITCODE -ne 0) { throw "Build $DecompMode failed; see logs/$Configuration-$DecompMode.log" }

