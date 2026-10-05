$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH
$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$out=Join-Path $PSScriptRoot 'build\gx-copy-host';New-Item -ItemType Directory -Force $out | Out-Null
& "$vc\bin\cl.exe" /nologo /O2 ('/Fo'+$out+'\') ('/Fe'+$out+'\gx-copy.exe') "$PSScriptRoot\tests\gx_copy_codec_host.cpp" "$PSScriptRoot\src\gx_copy_codec.cpp" "$PSScriptRoot\src\gx_texture.cpp"
if($LASTEXITCODE){throw 'GX copy host build failed'}
& "$out\gx-copy.exe" | Tee-Object (Join-Path $PSScriptRoot 'logs\gx-copy-host.txt')
if($LASTEXITCODE){throw 'GX copy codec tests failed'}
