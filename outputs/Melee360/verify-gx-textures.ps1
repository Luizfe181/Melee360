param([string]$Assets='C:\Users\luizf\Documents\melee_extraido')
$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\Common7\IDE;$vc\VC\bin;"+$env:PATH
$env:INCLUDE="$vc\VC\include;$sdk\Include"
$env:LIB="$vc\VC\lib;$sdk\Lib"
$scratch=Join-Path $PSScriptRoot 'build\host-tests'
New-Item -ItemType Directory -Force $scratch | Out-Null
$exe=Join-Path $scratch 'gx-texture.exe'
& "$vc\VC\bin\cl.exe" /nologo /O2 /EHsc ('/Fo'+$scratch+'\') ('/Fe'+$exe) (Join-Path $PSScriptRoot 'tests\gx_texture_host.cpp') (Join-Path $PSScriptRoot 'src\gx_texture.cpp')
if($LASTEXITCODE -ne 0) {throw 'GX host compilation failed'}
& $exe
if($LASTEXITCODE -ne 0) {throw 'GX format tests failed'}
& 'C:\Users\luizf\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe' (Join-Path $PSScriptRoot 'tests\inspect_menu_textures.py') $Assets $exe (Join-Path $PSScriptRoot 'logs\menu-textures')
if($LASTEXITCODE -ne 0) {throw 'Original menu texture decode failed'}
