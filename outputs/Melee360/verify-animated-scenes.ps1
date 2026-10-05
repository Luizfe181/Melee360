param([switch]$Menu)
$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\Common7\IDE;$vc\VC\bin;"+$env:PATH
$env:INCLUDE="$vc\VC\include;$sdk\Include"
$env:LIB="$vc\VC\lib;$sdk\Lib"
$scratch=Join-Path $PSScriptRoot 'build\host-tests'
New-Item -ItemType Directory -Force $scratch | Out-Null
$exe=Join-Path $scratch 'animated-scenes.exe'
$sources=@('tests\animated_scenes_host.cpp','src\hsd_scene.cpp','src\original_stage_select.c','src\gx_mesh.cpp','src\gx_texture.cpp') | ForEach-Object {Join-Path $PSScriptRoot $_}
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$sources+=@("$PSScriptRoot\tests\animation_platform_host.cpp","$PSScriptRoot\src\hsd_animation.cpp","$base\src\sysdolphin\baselib\fobj.c","$base\src\sysdolphin\baselib\spline.c")
& "$vc\VC\bin\cl.exe" /nologo /O2 /EHsc ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\dolphin\include') ('/I'+$base+'\libs\doldecomp\include') ('/Fo'+$scratch+'\') ('/Fe'+$exe) @sources
if($LASTEXITCODE -ne 0){throw 'Static scene compilation failed'}
& $exe
if($LASTEXITCODE -ne 0){throw 'Animated scene checks failed'}
