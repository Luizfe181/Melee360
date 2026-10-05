$ErrorActionPreference='Stop'
$vc='C:\Program Files (x86)\Microsoft Visual Studio 10.0'
$sdk='C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A'
$env:PATH="$vc\Common7\IDE;$vc\VC\bin;"+$env:PATH
$env:INCLUDE="$vc\VC\include;$sdk\Include"
$env:LIB="$vc\VC\lib;$sdk\Lib"
$scratch=Join-Path $PSScriptRoot 'build\host-tests'
New-Item -ItemType Directory -Force $scratch | Out-Null
$exe=Join-Path $scratch 'mth.exe'
& "$vc\VC\bin\cl.exe" /nologo /O2 /EHsc ('/Fo'+$scratch+'\') ('/Fe'+$exe) (Join-Path $PSScriptRoot 'tests\mth_host.cpp') (Join-Path $PSScriptRoot 'src\mth_decode.cpp')
if($LASTEXITCODE -ne 0){throw 'Movie decoder compilation failed'}
$python='C:\Users\luizf\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe'
foreach($movie in @(@{Name='MvHowto';Frames=@(0,1714,3427)},@{Name='MvOmake15';Frames=@(0,25140,50279)})) {
    $path=Join-Path 'C:\Users\luizf\Documents\melee_extraido' ($movie.Name+'.mth')
    foreach($frame in $movie.Frames){& $exe $path $frame (Join-Path $scratch ($movie.Name+"-$frame.ppm"));if($LASTEXITCODE -ne 0){throw 'Archive frame failed'}}
    & $python (Join-Path $PSScriptRoot 'tests\compare_mth.py') $path ($movie.Frames -join ',') $movie.Name
    if($LASTEXITCODE -ne 0){throw 'Independent gallery decode comparison failed'}
    & $python (Join-Path $PSScriptRoot 'tests\check_mth_packing.py') $path (Join-Path $PSScriptRoot ('logs\'+$movie.Name+'-packing.json'))
    if($LASTEXITCODE -ne 0){throw 'Packed gallery stream failed'}
}
