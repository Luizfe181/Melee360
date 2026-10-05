$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0';$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\Common7\IDE;$vc\VC\bin;"+$env:PATH;$env:INCLUDE="$vc\VC\include;$sdk\Include";$env:LIB="$vc\VC\lib;$sdk\Lib"
$base=(Resolve-Path (Join-Path $PSScriptRoot '../../work/melee-base')).Path;$out=Join-Path $PSScriptRoot 'build/host-tests'
& "$vc\VC\bin\cl.exe" /nologo /O2 /EHsc "/I$PSScriptRoot\compat" "/I$base\src" "/I$base\libs\dolphin\include" "/I$base\libs\doldecomp\include" "/Fo$out\" "/Fe$out\save-stats.exe" "$PSScriptRoot\tests\save_stats_host.cpp" "$PSScriptRoot\src\save_stats.cpp" "$PSScriptRoot\src\original_save_crypto.cpp"
if($LASTEXITCODE){throw 'Save reader compile failed'}
& "$out\save-stats.exe" "$PSScriptRoot\package\RGH\Melee360\melee360-import.gci"
if($LASTEXITCODE){throw "Save reader tests failed: $LASTEXITCODE"}
