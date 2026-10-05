param([ValidateSet('alarm','card','aram','arena','transform')][string]$Service='alarm')
$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\..\Common7\IDE;$vc\bin;"+$env:PATH
$env:INCLUDE="$vc\include;$sdk\Include";$env:LIB="$vc\lib;$sdk\Lib"
$base=(Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$out=Join-Path $PSScriptRoot ('build\'+$Service+'-host');New-Item -ItemType Directory -Force $out | Out-Null
$source=if($Service -eq 'transform'){'gx_transform.c'}elseif($Service -eq 'alarm'){'os_alarm.c'}elseif($Service -eq 'arena'){'os_arena.c'}elseif($Service -eq 'aram'){'aram_memory.c'}else{'card_filesystem.c'}
& "$vc\bin\cl.exe" /nologo /O2 /DLINT ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\doldecomp\include') ('/I'+$base+'\libs\dolphin\include') ('/Fo'+$out+'\') ('/Fe'+$out+'\test.exe') "$PSScriptRoot\src\$source" "$PSScriptRoot\tests\${Service}_host.c"
if($LASTEXITCODE -ne 0){throw 'Platform services compilation failed'}
Push-Location $out
try{& "$out\test.exe" | Tee-Object "$PSScriptRoot\logs\${Service}-host.txt";if($LASTEXITCODE -ne 0){throw "Platform service test failed: $LASTEXITCODE"}}finally{Pop-Location}
