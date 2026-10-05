$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH
$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$out=Join-Path $PSScriptRoot 'build\audio-host';New-Item -ItemType Directory -Force $out | Out-Null
& "$vc\bin\cl.exe" /nologo /O2 /EHsc ('/Fo'+$out+'\') ('/Fe'+$out+'\hps.exe') "$PSScriptRoot\src\hps_decode.cpp" "$PSScriptRoot\tests\hps_host.cpp"
if($LASTEXITCODE -ne 0){throw 'HPS compilation failed'}
Push-Location $out
try{& "$out\hps.exe" | Tee-Object "$PSScriptRoot\logs\hps-host.txt";if($LASTEXITCODE -ne 0){throw "HPS tests failed: $LASTEXITCODE"}}finally{Pop-Location}
