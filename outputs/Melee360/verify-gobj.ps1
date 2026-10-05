$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH
$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$out=Join-Path $PSScriptRoot 'build\gobj-host'
New-Item -ItemType Directory -Force $out | Out-Null
$sources=@('tests\gobj_host.cpp','src\gobj_runtime.c','src\hsd_memory.c')|ForEach-Object{Join-Path $PSScriptRoot $_}
foreach($name in @('gobj','gobjproc','gobjplink','gobjgxlink','gobjobject','gobjuserdata','objalloc')){$sources+=Join-Path $base "src\sysdolphin\baselib\$name.c"}
& "$vc\bin\cl.exe" /nologo /O2 ('/FI'+$PSScriptRoot+'\compat\hsd_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\dolphin\include') ('/I'+$base+'\libs\doldecomp\include') ('/Fo'+$out+'\') ('/Fe'+$out+'\gobj.exe') @sources
if($LASTEXITCODE -ne 0){throw 'GObj host compilation failed'}
& "$out\gobj.exe" | Tee-Object (Join-Path $PSScriptRoot 'logs\gobj-host.txt')
if($LASTEXITCODE -ne 0){throw 'GObj checks failed'}
