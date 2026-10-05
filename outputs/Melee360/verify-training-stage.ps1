$ErrorActionPreference='Stop'
$python='C:\Users\luizf\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe'
& $python "$PSScriptRoot\diagnostics\generate_training_stage.py";if($LASTEXITCODE){throw 'Generator failed'}
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC';$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A';$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH;$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path "$PSScriptRoot\..\..\work\melee-base").Path;$out="$PSScriptRoot\build\training-host";New-Item -ItemType Directory -Force $out | Out-Null
& "$vc\bin\cl.exe" /nologo /O2 /DLINT ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\') ('/Fe'+$out+'\test.exe') "$PSScriptRoot\src\original_training.c" "$PSScriptRoot\src\original_stage_select.c" "$PSScriptRoot\tests\training_stage_host.c"
if($LASTEXITCODE){throw 'Training host compilation failed'}
& "$out\test.exe" | Tee-Object "$PSScriptRoot\logs\training-host.txt";if($LASTEXITCODE){throw 'Training host test failed'}
