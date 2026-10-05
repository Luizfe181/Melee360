param()
$ErrorActionPreference='Stop'
if(!(Test-Path (Join-Path $PSScriptRoot 'build/css-host/original-css.obj'))){& (Join-Path $PSScriptRoot 'verify-original-css.ps1')}
if(!(Test-Path (Join-Path $PSScriptRoot 'build/training-host/original_stage_select.obj'))){& (Join-Path $PSScriptRoot 'verify-training-stage.ps1')}

$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\Common7\IDE;$vc\VC\bin;"+$env:PATH
$env:INCLUDE="$vc\VC\include;$sdk\Include"
$env:LIB="$vc\VC\lib;$sdk\Lib"
$scratch=Join-Path $PSScriptRoot 'build\host-tests'
New-Item -ItemType Directory -Force $scratch | Out-Null
$exe=Join-Path $scratch 'sound-scene.exe'
$sources=@('tests\scene_host.cpp','src\hsd_scene.cpp','src\gx_mesh.cpp','src\gx_texture.cpp') | ForEach-Object {Join-Path $PSScriptRoot $_}
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$sources+=@("$PSScriptRoot\tests\animation_platform_host.cpp","$PSScriptRoot\src\hsd_animation.cpp","$base\src\sysdolphin\baselib\fobj.c","$base\src\sysdolphin\baselib\spline.c")
$sources+=@("$PSScriptRoot\build\css-host\original-css.obj","$PSScriptRoot\build\training-host\original_stage_select.obj","$PSScriptRoot\tests\css_scene_math_host.c")
& "$vc\VC\bin\cl.exe" /nologo /O2 /EHsc ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\dolphin\include') ('/I'+$base+'\libs\doldecomp\include') ('/Fo'+$scratch+'\') ('/Fe'+$exe) @sources
if($LASTEXITCODE -ne 0){throw 'Static scene compilation failed'}
foreach($frame in @(0,19,60,200)){
    & $exe 'C:\Users\luizf\Documents\melee_extraido\MnMaAll.usd' "$scratch\sound-$frame.bin" "%$frame"
    if($LASTEXITCODE){throw "Sound test scene frame $frame failed"}
}
foreach($pose in @('^20,0,8,15,15,0','^20,1,0,15,15,60','^20,2,10,15,15,120','^152,0,8,0,0,60','^19,0,8,15,15,0','^19,1,8,5,15,60','^19,3,8,0,1,120')){
    & $exe 'C:\Users\luizf\Documents\melee_extraido\MnMaAll.usd' "$scratch\options.bin" $pose
    if($LASTEXITCODE){throw "Options scene $pose failed"}
}
