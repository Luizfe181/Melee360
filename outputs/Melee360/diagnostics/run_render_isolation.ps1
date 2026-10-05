param([ValidateRange(1,3600)][int]$BudgetSeconds=3300)
$ErrorActionPreference='Stop'
$project=Split-Path $PSScriptRoot -Parent
$workspace=(Resolve-Path (Join-Path $project '..\..')).Path
$package=Join-Path $workspace 'work\xenia-test\package'
$logDir=Join-Path $project 'logs\render-isolation-current'
New-Item -ItemType Directory -Path $logDir -Force | Out-Null
$tests=@(
 @{Name='baseline-before';Flags=@();Detailed=$false;Hide=$false},
 @{Name='detail-visible';Flags=@();Detailed=$true;Hide=$false},
 @{Name='vertex-phase0';Flags=@('gx-profile-vertex.flag');Detailed=$true;Hide=$false},
 @{Name='vertex-phase31';Flags=@('gx-profile-vertex.flag','gx-profile-vertex-alt.flag');Detailed=$true;Hide=$false},
 @{Name='detail-hidden';Flags=@();Detailed=$true;Hide=$true},
 @{Name='no-draw';Flags=@('gx-diag-no-draw.flag');Detailed=$true;Hide=$false},
 @{Name='simple-shader';Flags=@('gx-diag-simple-shader.flag');Detailed=$true;Hide=$false},
 @{Name='white-textures';Flags=@('gx-diag-white-textures.flag');Detailed=$true;Hide=$false},
 @{Name='no-copy';Flags=@('gx-diag-no-copy.flag');Detailed=$true;Hide=$false},
 @{Name='baseline-after';Flags=@();Detailed=$false;Hide=$false}
)
if(@(Get-ChildItem -LiteralPath $package -Filter *.flag).Count){throw 'Scratch already has diagnostic flags'}
$started=Get-Date
$hash=(Get-FileHash (Join-Path $package 'default.xex')).Hash
@{Started=$started.ToString('o');XexSha256=$hash;BudgetSeconds=$BudgetSeconds;Tests=$tests} | ConvertTo-Json -Depth 5 | Set-Content (Join-Path $logDir 'manifest.json') -Encoding UTF8
foreach($test in $tests){
 if(((Get-Date)-$started).TotalSeconds -ge $BudgetSeconds){throw 'Test time budget reached'}
 Write-Output ('Starting '+$test.Name)
 try{
  foreach($flag in $test.Flags){Set-Content -LiteralPath (Join-Path $package $flag) -Value 'Controlled render isolation diagnostic' -Encoding ASCII}
  & (Join-Path $project 'verify-original-bootstrap.ps1') -Match -Performance -Detailed:$test.Detailed -HideBots:$test.Hide -TimeoutSeconds 300 *> (Join-Path $logDir ($test.Name+'.txt'))
  $log=Get-Content -LiteralPath (Join-Path $logDir ($test.Name+'.txt')) -Raw
  if(!$log.Contains('GX profile: 180 frames presented') -or $log.Contains('FAILED') -or $log.Contains('DMA stopped')){throw ('Runtime check failed: '+$test.Name)}
  Write-Output ($log -split "`n" | Where-Object {$_ -like 'GX profile: frames=180 *'})
 }finally{foreach($flag in $test.Flags){Remove-Item -LiteralPath (Join-Path $package $flag) -ErrorAction SilentlyContinue}}
}
if((Get-FileHash (Join-Path $package 'default.xex')).Hash -ne $hash){throw 'XEX changed during comparison'}
Write-Output 'Render isolation matrix completed.'
