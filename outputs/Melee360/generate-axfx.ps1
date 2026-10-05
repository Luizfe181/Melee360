param([string]$MeleeRoot=(Join-Path $PSScriptRoot '..\..\work\melee-base'))
$ErrorActionPreference='Stop'
function Block([string]$text,[string]$marker){$start=$text.IndexOf($marker);if($start -lt 0){throw "Missing $marker"};$brace=$text.IndexOf('{',$start);$end=$brace+1;$depth=1;while($depth -and $end -lt $text.Length){if($text[$end] -eq '{'){$depth++};if($text[$end] -eq '}'){$depth--};$end++};if($depth){throw 'Unbalanced block'};return $text.Substring($start,$end-$start)}
$delay=Join-Path $MeleeRoot 'libs\dolphin\src\dolphin\axfx\delay.c'
$hooks=Join-Path $MeleeRoot 'libs\dolphin\src\dolphin\axfx\axfx.c'
$target=Join-Path $PSScriptRoot 'compat\generated\axfx_original.inc'
$text='/* Generated original blocks. delay.c SHA256: '+(Get-FileHash $delay).Hash+'; axfx.c SHA256: '+(Get-FileHash $hooks).Hash+" */`r`n"
$text+=(Block ([IO.File]::ReadAllText($delay)) 'void AXFXDelayCallback(')+"`r`n"
$text+=(Block ([IO.File]::ReadAllText($hooks)) 'void AXFXSetHooks(')+"`r`n"
[IO.File]::WriteAllText($target,$text)
