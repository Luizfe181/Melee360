$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\Common7\IDE;$vc\VC\bin;"+$env:PATH
$env:INCLUDE="$vc\VC\include;$sdk\Include"
$env:LIB="$vc\VC\lib;$sdk\Lib"
$scratch=Join-Path $PSScriptRoot 'build\host-tests'
New-Item -ItemType Directory -Force $scratch | Out-Null
$exe=Join-Path $scratch 'menu.exe'
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
& (Join-Path $PSScriptRoot 'generate-original-menu.ps1')
& "$vc\VC\bin\cl.exe" /nologo /O2 /EHsc ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/Fo'+$scratch+'\') ('/Fe'+$exe) (Join-Path $PSScriptRoot 'tests\menu_host.cpp') (Join-Path $PSScriptRoot 'src\menu_model.cpp') (Join-Path $PSScriptRoot 'src\original_menu_root.cpp')
if($LASTEXITCODE -ne 0){throw 'Menu host compilation failed'}
& $exe | Tee-Object (Join-Path $PSScriptRoot 'logs\menu-host-test.txt')
if($LASTEXITCODE -ne 0){throw "Menu host verification failed ($LASTEXITCODE)"}
