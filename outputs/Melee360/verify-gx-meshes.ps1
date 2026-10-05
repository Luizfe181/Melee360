param([string]$Assets='C:\Users\luizf\Documents\melee_extraido')
$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\Common7\IDE;$vc\VC\bin;"+$env:PATH
$env:INCLUDE="$vc\VC\include;$sdk\Include"
$env:LIB="$vc\VC\lib;$sdk\Lib"
$scratch=Join-Path $PSScriptRoot 'build\host-tests'
New-Item -ItemType Directory -Force $scratch | Out-Null
$exe=Join-Path $scratch 'gx-mesh.exe'
& "$vc\VC\bin\cl.exe" /nologo /O2 /EHsc ('/Fo'+$scratch+'\') ('/Fe'+$exe) (Join-Path $PSScriptRoot 'tests\gx_mesh_host.cpp') (Join-Path $PSScriptRoot 'src\gx_mesh.cpp')
if($LASTEXITCODE -ne 0) {throw 'GX mesh compilation failed'}
& $exe
if($LASTEXITCODE -ne 0) {throw 'GX mesh tests failed'}
$python='C:\Users\luizf\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe'
$inventory=Join-Path $PSScriptRoot 'logs\menu-geometry.json'
& $python (Join-Path $PSScriptRoot 'tests\inspect_menu_geometry.py') $Assets $inventory
if($LASTEXITCODE -ne 0) {throw 'Menu inventory failed'}
& $python (Join-Path $PSScriptRoot 'tests\check_menu_meshes.py') $Assets $exe $inventory
if($LASTEXITCODE -ne 0) {throw 'Original menu mesh decoding failed'}
