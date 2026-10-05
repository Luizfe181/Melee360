$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH
$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$out=Join-Path $PSScriptRoot 'build\allocator-host';New-Item -ItemType Directory -Force $out | Out-Null
& "$env:USERPROFILE\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe" "$PSScriptRoot\diagnostics\generate_allocator.py"
if($LASTEXITCODE -ne 0){throw 'Allocator generation failed'}
& "$vc\bin\cl.exe" /nologo /O2 /DLINT /c ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\allocator.obj') "$PSScriptRoot\compat\generated\os_allocator.c"
if($LASTEXITCODE -ne 0){throw 'Allocator compilation failed'}
& "$vc\bin\cl.exe" /nologo /O2 ('/Fo'+$out+'\') ('/Fe'+$out+'\allocator.exe') "$PSScriptRoot\tests\allocator_host.cpp"  "$out\allocator.obj"
if($LASTEXITCODE -ne 0){throw 'Allocator test link failed'}
& "$out\allocator.exe" | Tee-Object (Join-Path $PSScriptRoot 'logs\allocator-host.txt')
if($LASTEXITCODE -ne 0){throw 'Allocator tests failed'}

