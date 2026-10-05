$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH
$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$out=Join-Path $PSScriptRoot 'build\powf-host';New-Item -ItemType Directory -Force $out | Out-Null
& "$vc\bin\cl.exe" /nologo /O2 /c ('/FI'+$PSScriptRoot+'\tests\powf_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/Fo'+$out+'\original-powf.obj') "$base\src\melee\lb\lb_00CE.c"
if($LASTEXITCODE -ne 0){throw 'Original powf compilation failed'}
& "$vc\bin\cl.exe" /nologo /O2 ('/Fo'+$out+'\') ('/Fe'+$out+'\powf.exe') "$PSScriptRoot\tests\powf_host.cpp" "$out\original-powf.obj"
if($LASTEXITCODE -ne 0){throw 'Original powf test link failed'}
& "$out\powf.exe" | Tee-Object (Join-Path $PSScriptRoot 'logs\powf-host.txt')
if($LASTEXITCODE -ne 0){throw 'Original powf tests failed'}
