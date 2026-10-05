$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC';$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A';$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH;$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path "$PSScriptRoot\..\..\work\melee-base").Path;$out="$PSScriptRoot\build\runtime-archive-host";New-Item -ItemType Directory -Force $out | Out-Null
& "$vc\bin\cl.exe" /nologo /O2 ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\dolphin\include') ('/I'+$base+'\libs\doldecomp\include') ('/Fo'+$out+'\') ('/Fe'+$out+'\test.exe') "$PSScriptRoot\src\runtime_archive.c" "$base\src\sysdolphin\baselib\archive.c" "$PSScriptRoot\tests\runtime_archive_host.c"
if($LASTEXITCODE){throw 'Archive host build failed'};& "$out\test.exe"|Tee-Object "$PSScriptRoot\logs\runtime-archive-host.txt";if($LASTEXITCODE){throw 'Archive host test failed'}

& "$vc\bin\cl.exe" /nologo /O2 ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\') ('/Fe'+$out+'\cache.exe') "$PSScriptRoot\src\os_cache.c" "$PSScriptRoot\tests\cache_host.c"
if($LASTEXITCODE){throw 'Cache host build failed'};& "$out\cache.exe"|Tee-Object "$PSScriptRoot\logs\cache-host.txt";if($LASTEXITCODE){throw 'Cache host test failed'}
