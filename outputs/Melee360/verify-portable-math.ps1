$ErrorActionPreference='Stop'
& (Join-Path $PSScriptRoot 'generate-portable-mtx.ps1')
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH
$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$out=Join-Path $PSScriptRoot 'build\math-host'
New-Item -ItemType Directory -Force $out | Out-Null
$sources=@('tests\math_host.cpp','src\math_probe.c','src\paired_single_bridge.c','src\float_math_bridge.c','compat\generated\portable_mtx.c')|ForEach-Object{Join-Path $PSScriptRoot $_}
$sources+="$base\libs\dolphin\src\dolphin\pad\Padclamp.c"
& "$vc\bin\cl.exe" /nologo /O2 ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\dolphin\include') ('/I'+$base+'\libs\doldecomp\include') ('/Fo'+$out+'\') ('/Fe'+$out+'\math.exe') @sources
if($LASTEXITCODE -ne 0){throw 'Portable math compilation failed'}
& "$out\math.exe" | Tee-Object (Join-Path $PSScriptRoot 'logs\portable-math-host.txt')
if($LASTEXITCODE -ne 0){throw 'Portable math checks failed'}
