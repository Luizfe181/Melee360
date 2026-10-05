param([switch]$AnimationOnly)
$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\Common7\IDE;$vc\VC\bin;"+$env:PATH
$env:INCLUDE="$vc\VC\include;$sdk\Include"
$env:LIB="$vc\VC\lib;$sdk\Lib"
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
& (Join-Path $PSScriptRoot 'generate-original-menu.ps1')
$scratch=Join-Path $PSScriptRoot 'build\host-tests'
New-Item -ItemType Directory -Force $scratch | Out-Null
$common=@('/nologo','/O2','/EHsc',('/I'+$PSScriptRoot+'\compat'),('/I'+$base+'\src'),('/I'+$base+'\libs\dolphin\include'),('/I'+$base+'\libs\doldecomp\include'),('/Fo'+$scratch+'\'))
$sources=@("$PSScriptRoot\tests\animation_host.cpp","$PSScriptRoot\src\hsd_animation.cpp","$base\src\sysdolphin\baselib\fobj.c","$base\src\sysdolphin\baselib\spline.c")
& "$vc\VC\bin\cl.exe" @common ('/Fe'+$scratch+'\animation.exe') @sources
if($LASTEXITCODE -ne 0){throw 'Original animation compilation failed'}
& "$scratch\animation.exe"
if($LASTEXITCODE -ne 0){throw 'Original animation checks failed'}
if($AnimationOnly){return}
& (Join-Path $PSScriptRoot 'extract-menu-font.ps1')
$font=Join-Path $PSScriptRoot 'package\RGH\Melee360\melee360-font.bin'
$sources=@("$PSScriptRoot\tests\scene_host.cpp","$PSScriptRoot\tests\animation_platform_host.cpp","$PSScriptRoot\src\hsd_scene.cpp","$PSScriptRoot\src\gx_mesh.cpp","$PSScriptRoot\src\gx_texture.cpp","$PSScriptRoot\src\hsd_animation.cpp","$base\src\sysdolphin\baselib\fobj.c","$base\src\sysdolphin\baselib\spline.c")
& "$vc\VC\bin\cl.exe" @common ('/Fe'+$scratch+'\original-menu.exe') @sources
if($LASTEXITCODE -ne 0){throw 'Original menu compilation failed'}
for($selection=0;$selection -lt 5;$selection++){
    & "$scratch\original-menu.exe" 'C:\Users\luizf\Documents\melee_extraido\MnMaAll.usd' "$scratch\original-menu-$selection.bin" "#$selection" 'C:\Users\luizf\Documents\melee_extraido\SdMenu.usd' $font
    if($LASTEXITCODE -ne 0){throw "Original menu selection $selection failed"}
}
$pages=@(@(1,4),@(2,5),@(3,3),@(4,5),@(5,5),@(6,3),@(9,3),@(12,10),@(28,3))
foreach($p in $pages){for($selection=0;$selection -lt $p[1];$selection++){
    & "$scratch\original-menu.exe" 'C:\Users\luizf\Documents\melee_extraido\MnMaAll.usd' "$scratch\original-menu-$($p[0])-$selection.bin" "#$($p[0]),$selection" 'C:\Users\luizf\Documents\melee_extraido\SdMenu.usd' $font
    if($LASTEXITCODE -ne 0){throw "Original page $($p[0]) selection $selection failed"}
}}
