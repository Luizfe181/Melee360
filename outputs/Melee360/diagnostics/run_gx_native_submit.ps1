$ErrorActionPreference='Stop'
$project=Split-Path $PSScriptRoot -Parent
$workspace=(Resolve-Path (Join-Path $project '..\..')).Path
$package=Join-Path $workspace 'work\xenia-test\package'
$dir=Join-Path $project 'logs\gx-native-submit'
New-Item -ItemType Directory -Force -Path $dir | Out-Null
if(@(Get-ChildItem -LiteralPath $package -Filter *.flag).Count){throw 'Scratch has flags; preserve them and inspect first'}
if((Get-Content (Join-Path $workspace 'work\xenia-test\test.toml') -Raw) -notmatch '(?m)^mute\s*=\s*true'){throw 'Diagnostic audio must be muted'}
$candidate=Join-Path $project 'build\Release\Compat\default.xex'
$backup=Join-Path $dir 'scratch-before.xex'
Copy-Item -LiteralPath (Join-Path $package 'default.xex') -Destination $backup
$reuseFlag=Join-Path $package 'gx-native-submit.flag'
try {
 Copy-Item -LiteralPath $candidate -Destination (Join-Path $package 'default.xex') -Force
 @{CandidateSha256=(Get-FileHash $candidate).Hash;PreviousSha256=(Get-FileHash $backup).Hash;Mute=$true;Frames=180} | ConvertTo-Json | Set-Content (Join-Path $dir 'manifest.json')
 foreach($name in @('baseline-before','native','baseline-after')) {
  try {
   if($name -eq 'native'){Set-Content -LiteralPath $reuseFlag -Value 'Native vertex buffer page submission'}
   & (Join-Path $project 'verify-original-bootstrap.ps1') -Match -Performance -Detailed -TimeoutSeconds 300 *> (Join-Path $dir ($name+'.txt'))
   if($LASTEXITCODE -and $LASTEXITCODE -ne 0){throw "Test failed: $name"}
   $text=Get-Content (Join-Path $dir ($name+'.txt')) -Raw
   if(!$text.Contains('GX profile: 180 frames presented') -or $text.Contains('FAILED') -or $text.Contains('HSD ASSERT')){throw "Missing successful match marker: $name"}
   if($name -eq 'native' -and !$text.Contains('GX native submit: enabled')){throw 'Native backend did not activate'}
   Write-Output ($text -split "`n" | Where-Object {$_ -like 'GX profile: frames=180 *'})
  } finally {Remove-Item -LiteralPath $reuseFlag -ErrorAction SilentlyContinue}
 }
} finally {Copy-Item -LiteralPath $backup -Destination (Join-Path $package 'default.xex') -Force}
