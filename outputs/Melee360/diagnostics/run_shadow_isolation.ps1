$ErrorActionPreference='Stop'
$project=Split-Path $PSScriptRoot -Parent
$workspace=(Resolve-Path (Join-Path $project '..\..')).Path
$package=Join-Path $workspace 'work\xenia-test\package'
$dir=Join-Path $project 'logs\render-isolation-current'
if(@(Get-ChildItem -LiteralPath $package -Filter *.flag).Count){throw 'Scratch has flags'}
$source=Join-Path $workspace 'work\shadow-diagnostic.xex'
$backup=Join-Path $workspace 'work\before-shadow-isolation.xex'
Copy-Item -LiteralPath (Join-Path $package 'default.xex') -Destination $backup
$tests=@(
 @{Name='shadow-baseline-before';NoShadow=$false;Hide=$false},
 @{Name='no-fighter-shadows';NoShadow=$true;Hide=$false},
 @{Name='hidden-no-fighter-shadows';NoShadow=$true;Hide=$true},
 @{Name='shadow-baseline-after';NoShadow=$false;Hide=$false}
)
try{
 Copy-Item -LiteralPath $source -Destination (Join-Path $package 'default.xex') -Force
 @{XexSha256=(Get-FileHash $source).Hash;Tests=$tests;Mute=$true} | ConvertTo-Json -Depth 4 | Set-Content (Join-Path $dir 'shadow-manifest.json') -Encoding UTF8
 foreach($test in $tests){
  Write-Output ('Starting '+$test.Name)
  try{
   if($test.NoShadow){Set-Content -LiteralPath (Join-Path $package 'hide-bot-shadows.flag') -Value 'Original shadow exclusion during render only'}
   & (Join-Path $project 'verify-original-bootstrap.ps1') -Match -Performance -Detailed -HideBots:$test.Hide -TimeoutSeconds 300 *> (Join-Path $dir ($test.Name+'.txt'))
   $text=Get-Content -LiteralPath (Join-Path $dir ($test.Name+'.txt')) -Raw
   if(!$text.Contains('GX profile: 180 frames presented') -or $text.Contains('FAILED') -or $text.Contains('DMA stopped')){throw ('Shadow diagnostic failed: '+$test.Name)}
   Write-Output ($text -split "`n" | Where-Object {$_ -like 'GX profile: frames=180 *'})
  }finally{Remove-Item -LiteralPath (Join-Path $package 'hide-bot-shadows.flag') -ErrorAction SilentlyContinue}
 }
}finally{Copy-Item -LiteralPath $backup -Destination (Join-Path $package 'default.xex') -Force}
Write-Output 'Shadow comparisons complete; original scratch XEX restored.'
