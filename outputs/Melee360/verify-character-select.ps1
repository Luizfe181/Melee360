$ErrorActionPreference='Stop'
& (Join-Path $PSScriptRoot 'verify-static-title.ps1')
$exe=Join-Path $PSScriptRoot 'build\host-tests\scene.exe'
$out=Join-Path $PSScriptRoot 'build\host-tests'
$assets='C:\Users\luizf\Documents\melee_extraido'
$header=Get-Content (Join-Path $PSScriptRoot 'src\character_select.h') -Raw
$files=[regex]::Matches($header,'"(Pl[A-Za-z]+Nr.dat)"') | ForEach-Object {$_.Groups[1].Value}
if($files.Count -ne 25){throw 'Expected 25 diagnostic roster entries'}
for($slot=0;$slot -lt 25;$slot++){
    & $exe (Join-Path $assets 'MnSlChr.usd') (Join-Path $out "css-$slot.bin") "@$slot"
    if($LASTEXITCODE -ne 0){throw "CSS slot $slot failed"}
    $result=& $exe (Join-Path $assets $files[$slot]) (Join-Path $out "fighter-$slot.bin") '!'
    if($LASTEXITCODE -ne 0){throw "Model $($files[$slot]) failed"}
    $result | Write-Output
    $expected=if($files[$slot] -eq 'PlSsNr.dat'){2}else{0}
    if(!($result -match " $expected skipped")){throw "Unexpected unsupported mesh count in $($files[$slot])"}
    Write-Output "Validated CSS slot=$slot archive=$($files[$slot]); skipped=$expected"
}
Write-Output '25 original portraits/selections and 25 model archives loaded; Samus has 2 unsupported meshes.'
