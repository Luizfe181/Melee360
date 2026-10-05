$ErrorActionPreference='Stop'
& (Join-Path $PSScriptRoot 'generate-axfx.ps1')
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC';$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH
$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$out=Join-Path $PSScriptRoot 'build\axfx-host';New-Item -ItemType Directory -Force $out | Out-Null
& "$vc\bin\cl.exe" /nologo /O2 /DLINT ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\') ('/Fe'+$out+'\test.exe') "$PSScriptRoot\src\axfx_delay.c" "$PSScriptRoot\src\axfx_probe.c" "$PSScriptRoot\tests\axfx_host.c"
if($LASTEXITCODE -ne 0){throw 'AXFX host compilation failed'}
& "$out\test.exe" | Tee-Object "$PSScriptRoot\logs\axfx-host.txt"
if($LASTEXITCODE -ne 0){throw 'AXFX host tests failed'}
