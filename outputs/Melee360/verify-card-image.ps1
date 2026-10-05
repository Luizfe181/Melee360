$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\Common7\IDE;$vc\VC\bin;"+$env:PATH
$env:INCLUDE="$vc\VC\include;$sdk\Include"
$env:LIB="$vc\VC\lib;$sdk\Lib"
$scratch=Join-Path $PSScriptRoot 'build\host-tests'
New-Item -ItemType Directory -Force $scratch | Out-Null
$exe=Join-Path $scratch 'card-image.exe'
& "$vc\VC\bin\cl.exe" /nologo /O2 /EHsc ('/Fo'+$scratch+'\') ('/Fe'+$exe) (Join-Path $PSScriptRoot 'tests\card_image_host.cpp') (Join-Path $PSScriptRoot 'src\card_image.cpp')
if($LASTEXITCODE -ne 0) {throw 'Card image compilation failed'}
& $exe
if($LASTEXITCODE -ne 0) {throw 'Virtual card image tests failed'}
