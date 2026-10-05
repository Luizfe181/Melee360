$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC';$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH;$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path "$PSScriptRoot\..\..\work\melee-base").Path;$out="$PSScriptRoot\build\axfx-host";New-Item -ItemType Directory -Force $out | Out-Null
& "$vc\bin\cl.exe" /nologo /O2 /DLINT ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\') ('/Fe'+$out+'\reverb-hi.exe') "$PSScriptRoot\src\axfx_delay.c" "$PSScriptRoot\src\axfx_reverb_hi.c" "$PSScriptRoot\src\axfx_reverb_hi_probe.c" "$PSScriptRoot\tests\reverb_hi_host.c"
if($LASTEXITCODE){throw 'Reverb compile failed'}
& "$out\reverb-hi.exe"
if($LASTEXITCODE){throw 'Reverb tests failed'}
