$ErrorActionPreference='Stop'
$project=Split-Path $PSScriptRoot -Parent
$workspace=(Resolve-Path (Join-Path $project '..\..')).Path
$package=Join-Path $workspace 'work\xenia-test\package'
$dir=Join-Path $project 'logs\render-isolation-current'
if(@(Get-ChildItem -LiteralPath $package -Filter *.flag).Count){throw 'Scratch has flags'}
foreach($hidden in @($false,$true)){
 $name=if($hidden){'long-hidden'}else{'long-visible'}
 Write-Output ('Starting '+$name+' (900 original frames)')
 try{
  Set-Content -LiteralPath (Join-Path $package 'gx-profile.flag') -Value 'Steady combat diagnostic'
  Set-Content -LiteralPath (Join-Path $package 'gx-profile-detail.flag') -Value 'Nested CPU timers'
  & (Join-Path $project 'verify-original-bootstrap.ps1') -Match -HideBots:$hidden -TimeoutSeconds 900 *> (Join-Path $dir ($name+'.txt'))
  $text=Get-Content -LiteralPath (Join-Path $dir ($name+'.txt')) -Raw
  if(!$text.Contains('Original match render: 900 frames presented') -or $text.Contains('FAILED') -or $text.Contains('DMA stopped')){throw ('Long regression failed: '+$name)}
  Write-Output ($text -split "`n" | Where-Object {$_ -like 'GX profile: frames=900 *'})
 }finally{
  Remove-Item -LiteralPath (Join-Path $package 'gx-profile.flag') -ErrorAction SilentlyContinue
  Remove-Item -LiteralPath (Join-Path $package 'gx-profile-detail.flag') -ErrorAction SilentlyContinue
 }
}
Write-Output 'Long render comparisons completed.'
