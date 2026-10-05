$ErrorActionPreference='Stop'
$project=Split-Path $PSScriptRoot -Parent
$workspace=(Resolve-Path (Join-Path $project '..\..')).Path
$package=Join-Path $workspace 'work\xenia-test\package'
$dir=Join-Path $project 'logs\port-review-binding'
if(@(Get-ChildItem -LiteralPath $package -Filter *.flag).Count){throw 'Scratch flags exist'}
$backup=Join-Path $dir 'scratch-before-regression.xex'
Copy-Item -LiteralPath (Join-Path $package 'default.xex') -Destination $backup
$reuseFlag=Join-Path $package 'gx-texture-binding-reuse.flag'
$captureFlag=Join-Path $package 'original-render-capture.flag'
try {
 Copy-Item -LiteralPath (Join-Path $project 'build\Release\Compat\default.xex') -Destination (Join-Path $package 'default.xex') -Force
 try {
  Set-Content -LiteralPath $reuseFlag -Value 'Native bound image reuse regression'
  & (Join-Path $project 'verify-xenia.ps1') -TrainingPreview -PackageRoot $package -ConfigSource (Join-Path $dir 'test-source.toml') -TimeoutSeconds 300 *> (Join-Path $dir 'training-regression.txt')
  Write-Output 'Training and existing GPU/platform probes completed'
 } finally {Remove-Item -LiteralPath $reuseFlag -ErrorAction SilentlyContinue}
 foreach($name in @('capture-baseline','capture-reuse')) {
  try {
   Set-Content -LiteralPath $captureFlag -Value 'Internal GX images for exact pixel comparison; excluded from timing results'
   if($name -eq 'capture-reuse'){Set-Content -LiteralPath $reuseFlag -Value 'Native bound image reuse capture'}
   & (Join-Path $project 'verify-original-bootstrap.ps1') -Match -Performance -TimeoutSeconds 300 *> (Join-Path $dir ($name+'.txt'))
   foreach($frame in @(1,60)){
    $image='original-match-{0:d4}.tga' -f $frame
    Copy-Item -LiteralPath (Join-Path $package $image) -Destination (Join-Path $dir ($name+'-'+$image))
   }
   Write-Output ($name+' completed')
  } finally {
   Remove-Item -LiteralPath $reuseFlag -ErrorAction SilentlyContinue
   Remove-Item -LiteralPath $captureFlag -ErrorAction SilentlyContinue
  }
 }
} finally {Copy-Item -LiteralPath $backup -Destination (Join-Path $package 'default.xex') -Force}
