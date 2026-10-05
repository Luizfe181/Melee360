param([string]$Movie = 'C:\Users\luizf\Documents\melee_extraido\MvOpen.mth',
      [string]$Python = 'C:\Users\luizf\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe')
$ErrorActionPreference = 'Stop'
$vc = 'C:\Program Files (x86)\Microsoft Visual Studio 10.0'
$windowsSdk = 'C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH = "$vc\Common7\IDE;$vc\VC\bin;" + $env:PATH
$env:INCLUDE = "$vc\VC\include;$windowsSdk\Include"
$env:LIB = "$vc\VC\lib;$windowsSdk\Lib"
$scratch = Join-Path $PSScriptRoot 'build\host-tests'
New-Item -ItemType Directory -Force $scratch | Out-Null
$exe = Join-Path $scratch 'mth.exe'
& "$vc\VC\bin\cl.exe" /nologo /O2 /EHsc ('/Fo' + $scratch + '\') ('/Fe' + $exe) (Join-Path $PSScriptRoot 'tests\mth_host.cpp') (Join-Path $PSScriptRoot 'src\mth_decode.cpp')
if($LASTEXITCODE -ne 0) { throw 'Portable decoder host compilation failed.' }
$results = foreach($frame in @(0,900,1800,3035)) {
    & $exe $Movie $frame (Join-Path $scratch "intro-$frame.ppm")
    if($LASTEXITCODE -ne 0) { throw "Frame $frame decode test failed." }
}
$results | Tee-Object (Join-Path $PSScriptRoot 'logs\mth-host-test.txt')
& $exe $Movie all (Join-Path $scratch 'intro-all-last.ppm') | Tee-Object (Join-Path $PSScriptRoot 'logs\mth-all-frames.txt')
if($LASTEXITCODE -ne 0) { throw 'Complete movie decode failed.' }
& $Python (Join-Path $PSScriptRoot 'tests\compare_mth.py') $Movie
if($LASTEXITCODE -ne 0) { throw 'Independent decoder image comparison failed.' }
