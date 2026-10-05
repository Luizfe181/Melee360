param([string]$AssetsRoot = 'C:\Users\luizf\Documents\melee_extraido')
$ErrorActionPreference = 'Stop'
$vc = 'C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC'
$sdk = 'C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH = "C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE;$vc\bin;" + $env:PATH
$env:INCLUDE = "$vc\include;$sdk\Include"
$env:LIB = "$vc\lib;$sdk\Lib"
$base = (Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
$scratch = Join-Path $PSScriptRoot 'build\host-tests'
New-Item -ItemType Directory -Force $scratch | Out-Null
$common = @('/nologo', ('/I' + (Join-Path $PSScriptRoot 'compat')), ('/I' + (Join-Path $base 'src')), ('/I' + (Join-Path $base 'libs\dolphin\include')), ('/I' + (Join-Path $base 'libs\doldecomp\include')), ('/Fo' + $scratch + '\'))
$core = @((Join-Path $PSScriptRoot 'tests\core_host.cpp'))
foreach ($name in @('hsd_memory','hsd_probe','asset_archive')) { $core += Join-Path $PSScriptRoot "src\$name.c" }
foreach ($name in @('archive','random','list','objalloc','class','object','hash','id')) { $core += Join-Path $base "src\sysdolphin\baselib\$name.c" }
& "$vc\bin\cl.exe" @common /FIhsd_boundary.h ('/Fe' + (Join-Path $scratch 'core.exe')) @core
if ($LASTEXITCODE -ne 0) { throw 'Host core test compilation failed.' }
& (Join-Path $scratch 'core.exe') (Join-Path $AssetsRoot 'PlMr.dat') | Tee-Object (Join-Path $PSScriptRoot 'logs\hsd-host-test.txt')
if ($LASTEXITCODE -ne 0) { throw 'Host core test failed.' }
$pad = @((Join-Path $PSScriptRoot 'tests\pad_host.cpp'), (Join-Path $PSScriptRoot 'src\pad_hsd.c'), (Join-Path $base 'src\sysdolphin\baselib\controller.c'), (Join-Path $base 'src\sysdolphin\baselib\rumble.c'))
& "$vc\bin\cl.exe" @common ('/Fe' + (Join-Path $scratch 'pad.exe')) @pad
if ($LASTEXITCODE -ne 0) { throw 'Host pad test compilation failed.' }
& (Join-Path $scratch 'pad.exe') | Tee-Object (Join-Path $PSScriptRoot 'logs\pad-host-test.txt')
if ($LASTEXITCODE -ne 0) { throw 'Host pad test failed.' }
