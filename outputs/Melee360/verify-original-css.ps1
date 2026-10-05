$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH
$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$out=Join-Path $PSScriptRoot 'build\css-host';New-Item -ItemType Directory -Force $out | Out-Null
& "$vc\bin\cl.exe" /nologo /O2 /DLINT /c ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\original-css.obj') "$PSScriptRoot\src\original_character_select.c"
if($LASTEXITCODE -ne 0){throw 'Original CSS compilation failed'}
& "$vc\bin\cl.exe" /nologo /O2 ('/Fo'+$out+'\') ('/Fe'+$out+'\css.exe') "$PSScriptRoot\tests\css_host.cpp" "$PSScriptRoot\tests\css_math_host.c" "$out\original-css.obj"
if($LASTEXITCODE -ne 0){throw 'Original CSS test link failed'}
& "$out\css.exe" | Tee-Object (Join-Path $PSScriptRoot 'logs\css-host.txt')
if($LASTEXITCODE -ne 0){throw 'Original CSS tests failed'}
