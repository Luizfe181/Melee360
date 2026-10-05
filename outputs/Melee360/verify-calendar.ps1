& (Join-Path $PSScriptRoot 'generate-calendar.ps1')
$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH
$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$out=Join-Path $PSScriptRoot 'build\calendar-host';New-Item -ItemType Directory -Force $out | Out-Null
& "$vc\bin\cl.exe" /nologo /O2 /DLINT /c ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\calendar.obj') "$PSScriptRoot\compat\generated\calendar.c"
if($LASTEXITCODE -ne 0){throw "Calendar compilation failed"}
& "$vc\bin\cl.exe" /nologo /O2 /DLINT /c ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\calendar_probe.obj') "$PSScriptRoot\src\calendar_probe.c"
if($LASTEXITCODE -ne 0){throw 'Calendar compilation failed'}
& "$vc\bin\cl.exe" /nologo /O2 ('/Fo'+$out+'\') ('/Fe'+$out+'\calendar.exe') "$PSScriptRoot\tests\calendar_host.cpp"  "$out\calendar.obj" "$out\calendar_probe.obj"
if($LASTEXITCODE -ne 0){throw 'Calendar test link failed'}
& "$out\calendar.exe" | Tee-Object (Join-Path $PSScriptRoot 'logs\calendar-host.txt')
if($LASTEXITCODE -ne 0){throw 'Calendar tests failed'}
