param([ValidateSet('Hidden','Visible','Menu')][string]$Mode='Hidden')
$ErrorActionPreference='Stop'
$package=Join-Path $PSScriptRoot 'package\RGH\Melee360'
$match=Join-Path $package 'original-match.flag'
$hide=Join-Path $package 'hide-bot-render.flag'
if($Mode -eq 'Menu'){
 Remove-Item -LiteralPath $match -ErrorAction SilentlyContinue
 Remove-Item -LiteralPath $hide -ErrorAction SilentlyContinue
}else{
 Set-Content -LiteralPath $match -Value 'Original Mario CPU vs Link CPU on Battlefield' -Encoding ASCII
 if($Mode -eq 'Hidden'){Set-Content -LiteralPath $hide -Value 'Hide CPU Fighter render callbacks only' -Encoding ASCII}
 else{Remove-Item -LiteralPath $hide -ErrorAction SilentlyContinue}
}
Write-Output "Bot render diagnostic: $Mode. Restart default.xex to apply."
