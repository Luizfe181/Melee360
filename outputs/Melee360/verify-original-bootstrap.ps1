param([switch]$CreateMario,[switch]$Match,[switch]$Performance,[switch]$Detailed,[switch]$HideBots,[ValidateRange(1,900)][int]$TimeoutSeconds=45)
$ErrorActionPreference='Stop'
$workspace=(Resolve-Path "$PSScriptRoot\..\..").Path
$scratch=Join-Path $workspace 'work\xenia-test';$package=Join-Path $scratch 'package'
if($Performance -and !$Match){throw 'Performance requires Match'}
if($Detailed -and !$Performance){throw 'Detailed requires Performance'}
if($CreateMario -and $Match){throw 'Choose Mario creation or CPU match, not both'}
$hideFlag=Join-Path $package 'hide-bot-render.flag'
if($HideBots -and !$Match){throw 'HideBots requires Match'}
if(Test-Path $hideFlag){throw 'Hide-bot flag already exists'}
$matchFlag=Join-Path $package 'original-match.flag'
$profileFlag=Join-Path $package 'gx-profile.flag';$detailFlag=Join-Path $package 'gx-profile-detail.flag'
$flag=Join-Path $package 'fighter-bootstrap.flag';$createFlag=Join-Path $package 'fighter-create.flag'
if((Test-Path $flag) -or (Test-Path $createFlag) -or (Test-Path $matchFlag) -or ($Performance -and (Test-Path $profileFlag)) -or ($Detailed -and (Test-Path $detailFlag))){throw 'Diagnostic flags already exist'}
$log=Join-Path $package 'melee360.log';if(Test-Path $log){Remove-Item -LiteralPath $log}
Set-Content -LiteralPath $flag -Value 'isolated original bootstrap test' -Encoding ASCII
if($CreateMario){Set-Content -LiteralPath $createFlag -Value 'original Mario creation test' -Encoding ASCII}
if($Match){if(Test-Path $matchFlag){throw 'Match flag exists'};Set-Content -LiteralPath $matchFlag -Value 'original CPU match'}
if($Performance){Set-Content $profileFlag 'CPU/GX timing'}
if($Detailed){Set-Content $detailFlag 'Detailed CPU wall timings'}
$name=if($Performance){'original-match-profile-runtime'}elseif($Match){'original-match-runtime'}elseif($CreateMario){'fighter-create-runtime'}else{'fighter-pools-runtime'}
$expected=if($Performance){'GX profile: 180 frames presented'}elseif($Match){'Original match render: 900 frames presented'}elseif($CreateMario){'Bootstrap Fighter: original Mario Fighter_Create returned a valid GObj'}else{'Bootstrap Fighter: original players and Fighter pools initialized; no Fighter created'}
if($HideBots){Set-Content -LiteralPath $hideFlag -Value 'CPU render diagnostic'}
$p=$null
try{
 $exe=Join-Path $scratch 'xenia_canary.exe';$config=Join-Path $scratch 'test.toml';$xex=Join-Path $package 'default.xex'
 $p=Start-Process -FilePath $exe -ArgumentList ('"'+$xex+'" --config="'+$config+'" --headless=true') -WorkingDirectory $scratch -WindowStyle Hidden -PassThru
 $passed=$false
 for($i=0;$i -lt $TimeoutSeconds;$i++){Start-Sleep -Milliseconds 1000;if(Test-Path $log){$stream=[IO.File]::Open($log,[IO.FileMode]::Open,[IO.FileAccess]::Read,[IO.FileShare]::ReadWrite);$reader=New-Object IO.StreamReader($stream);try{$text=$reader.ReadToEnd()}finally{$reader.Dispose()};if($text.Contains('FAILED') -or $text.Contains('HSD ASSERT')){throw 'Original bootstrap assertion/failure; see runtime log'};if($text.Contains($expected)){$passed=$true;break}};if($p.HasExited){break}}
 if(!$passed){throw 'Original bootstrap did not reach expected marker'}
 Write-Output $text
}finally{if($HideBots){Remove-Item -LiteralPath $hideFlag -ErrorAction SilentlyContinue};if($Detailed){Remove-Item -LiteralPath $detailFlag -ErrorAction SilentlyContinue};if($Performance){Remove-Item -LiteralPath $profileFlag -ErrorAction SilentlyContinue};if(Test-Path $log){Copy-Item -LiteralPath $log -Destination (Join-Path $PSScriptRoot ('logs\'+$name+'.log')) -Force};if($p -and !$p.HasExited){Stop-Process -Id $p.Id;$p.WaitForExit(5000)|Out-Null};Remove-Item -LiteralPath $flag -ErrorAction SilentlyContinue;if($CreateMario){Remove-Item -LiteralPath $createFlag -ErrorAction SilentlyContinue};if($Match){Remove-Item -LiteralPath $matchFlag -ErrorAction SilentlyContinue}}

