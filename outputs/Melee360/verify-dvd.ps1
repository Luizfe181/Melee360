& (Join-Path $PSScriptRoot 'generate-dvd-manifest.ps1')
$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH
$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$out=Join-Path $PSScriptRoot 'build\dvd-host';New-Item -ItemType Directory -Force $out | Out-Null
& "$vc\bin\cl.exe" /nologo /O2 /DLINT /c ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\dvd_filesystem.obj') "$PSScriptRoot\src\dvd_filesystem.c"
if($LASTEXITCODE -ne 0){throw "DVD filesystem compilation failed"}
& "$vc\bin\cl.exe" /nologo /O2 /DLINT /c ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\dvd_probe.obj') "$PSScriptRoot\src\dvd_probe.c"
if($LASTEXITCODE -ne 0){throw 'DVD filesystem compilation failed'}
& "$vc\bin\cl.exe" /nologo /O2 /DLINT ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\') ('/Fe'+$out+'\dvd.exe') "$PSScriptRoot\tests\dvd_host.c"  "$out\dvd_filesystem.obj" "$out\dvd_probe.obj"
if($LASTEXITCODE -ne 0){throw 'DVD filesystem test link failed'}
& "$out\dvd.exe" | Tee-Object (Join-Path $PSScriptRoot 'logs\dvd-host.txt')
if($LASTEXITCODE -ne 0){throw 'DVD filesystem tests failed'}
