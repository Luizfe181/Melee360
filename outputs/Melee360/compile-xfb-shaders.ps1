$ErrorActionPreference='Stop'
$compiler=Join-Path $env:XEDK 'bin\win32\fxc.exe'
foreach($entry in @('VS','PS','PSCheck','PSWhite')){
 $profile=if($entry -eq 'VS'){'vs_3_0'}else{'ps_3_0'}
 & $compiler /nologo /T $profile /E $entry /Vn "Melee360Xfb$entry" /Fh (Join-Path $PSScriptRoot "src\xfb_$entry.h") (Join-Path $PSScriptRoot 'src\xfb_filter.hlsl')
 if($LASTEXITCODE){throw 'XFB shader compilation failed'}
}
