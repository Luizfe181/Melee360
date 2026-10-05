& (Join-Path $PSScriptRoot 'generate-portable-gx.ps1')
$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH
$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$out=Join-Path $PSScriptRoot 'build\gx-cpu-host';New-Item -ItemType Directory -Force $out | Out-Null
& "$vc\bin\cl.exe" /nologo /O2 /DLINT /c ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\portable-gx.obj') "$PSScriptRoot\compat\generated\portable_gx.c"
if($LASTEXITCODE -ne 0){throw "Portable GX compilation failed"}
& "$vc\bin\cl.exe" /nologo /O2 /DLINT /c ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\gx-cpu-probe.obj') "$PSScriptRoot\src\gx_cpu_probe.c"
if($LASTEXITCODE -ne 0){throw 'Original GX CPU compilation failed'}
& "$vc\bin\cl.exe" /nologo /O2 ('/Fo'+$out+'\') ('/Fe'+$out+'\gx-cpu.exe') "$PSScriptRoot\tests\gx_cpu_host.cpp" "$PSScriptRoot\tests\css_math_host.c" "$out\portable-gx.obj" "$out\gx-cpu-probe.obj"
if($LASTEXITCODE -ne 0){throw 'Original GX CPU test link failed'}
& "$out\gx-cpu.exe" | Tee-Object (Join-Path $PSScriptRoot 'logs\gx-cpu-host.txt')
if($LASTEXITCODE -ne 0){throw 'Original GX CPU tests failed'}
