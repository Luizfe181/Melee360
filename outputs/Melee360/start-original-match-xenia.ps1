param([string]$XeniaRoot='C:\Users\luizf\Downloads\xenia_canary_windows')
$ErrorActionPreference='Stop'
$workspace=(Resolve-Path "$PSScriptRoot\..\..").Path
$source=Join-Path $PSScriptRoot 'package\RGH\Melee360'
if(!(Test-Path (Join-Path $source 'default.xex'))){throw 'Build package is missing'}
$run=Join-Path $workspace ('work\xenia-match-play-'+(Get-Date -Format 'yyyyMMdd-HHmmss-fff'))
$package=Join-Path $run 'package'
New-Item -ItemType Directory -Path $package -Force|Out-Null
# A dedicated run owns its flags/log. Original assets are read through a junction.
New-Item -ItemType Junction -Path (Join-Path $package 'data') -Value (Join-Path $source 'data')|Out-Null
Copy-Item -LiteralPath (Join-Path $source 'default.xex') -Destination $package
Copy-Item -LiteralPath (Join-Path $source 'melee360-font.bin') -Destination $package
$exe=Join-Path $run 'xenia_canary.exe'
Copy-Item -LiteralPath (Join-Path $XeniaRoot 'xenia_canary.exe') -Destination $exe
$config=[IO.File]::ReadAllText((Join-Path $XeniaRoot 'xenia-canary.config.toml'))
$config=$config -replace '(?m)^headless\s*=\s*true','headless = false'
$config=$config -replace '(?m)^allow_game_relative_writes\s*=\s*false','allow_game_relative_writes = true'
$config=$config -replace '(?m)^log_file\s*=\s*"[^"\r\n]*"',('log_file = "'+(Join-Path $run 'xenia.log').Replace('\','/')+'"')
$config=$config -replace '(?m)^readback_resolve\s*=\s*"[^"\r\n]*"','readback_resolve = "full"'
$configPath=Join-Path $run 'match.toml'
[IO.File]::WriteAllText($configPath,$config)
$flag=Join-Path $package 'original-match.flag'
Set-Content -LiteralPath $flag -Value 'Original Mario CPU versus Link CPU, Battlefield'
Write-Host 'Mario CPU vs Link CPU em Battlefield: logica e desenho HSD originais. Preview experimental; materiais/desempenho e audio AX ainda incompletos.'
Write-Host "Log: $package\melee360.log"
$p=$null
try{
 $p=Start-Process -FilePath $exe -ArgumentList ('"'+(Join-Path $package 'default.xex')+'" --config="'+$configPath+'"') -WorkingDirectory $run -WindowStyle Normal -PassThru
 while(!$p.HasExited){Start-Sleep -Milliseconds 500}
}finally{Remove-Item -LiteralPath $flag -ErrorAction SilentlyContinue}
