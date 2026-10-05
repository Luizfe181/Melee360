param([string]$MeleeRoot=(Join-Path $PSScriptRoot '..\..\work\melee-base'))
$ErrorActionPreference='Stop'
$path=Join-Path $MeleeRoot 'src\melee\mn\mnmain.c'
$source=[IO.File]::ReadAllText($path)
function Extract-Block([string]$Text,[string]$Marker){
    $start=$Text.IndexOf($Marker);if($start -lt 0){throw "Missing upstream block $Marker"}
    $brace=$Text.IndexOf('{',$start);$depth=1;$end=$brace+1
    while($depth -gt 0 -and $end -lt $Text.Length){if($Text[$end] -eq '{'){$depth++};if($Text[$end] -eq '}'){$depth--};$end++}
    if($depth -ne 0){throw 'Unbalanced source block'}
    return $Text.Substring($start,$end-$start)
}
$header='/* Generated from unchanged upstream mnmain.c; do not edit. SHA256: '+(Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash+" */`r`n"
$text=$header
foreach($marker in @('static inline void decrement_selection(', 'static inline void increment_selection(', 'void mn_8022DB10(')){$text+=(Extract-Block $source $marker)+"`r`n`r`n"}
$target=Join-Path $PSScriptRoot 'compat\generated\mnmain_root.inc'
New-Item -ItemType Directory -Force (Split-Path $target) | Out-Null
[IO.File]::WriteAllText($target,$text)
Write-Output 'Generated unchanged original main-menu input handler and selection helpers.'
$panels=Extract-Block $source 'static AnimLoopSettings mn_803EAE8C'
$triples=[regex]::Matches($panels,'\{\s*([\d.\-]+),\s*([\d.\-]+),\s*([\d.\-]+)\s*\}')
$kinds=Extract-Block $source 'MenuKindData mn_803EB6B0'
$records=[regex]::Matches($kinds,'\{\s*(\w+),\s*(\d+),\s*(\w+),\s*(0x[\da-fA-F]+),\s*(\w+),\s*\}')
if($triples.Count -ne 102 -or $records.Count -ne 34){throw 'Original menu metadata changed; inspect source.'}
$metadata=$header+"struct Melee360OriginalMenuKind {unsigned int labelFrame,count;float idle,hover[10];unsigned int descriptions[10];};`r`nstatic const Melee360OriginalMenuKind Melee360OriginalMenuKinds[34]={`r`n"
for($i=0;$i -lt 34;$i++){
    $record=$records[$i];$loop=$record.Groups[1].Value;$hover=@()
    if($loop -ne 'NULL'){
        $loopBlock=Extract-Block $source ("static AnimLoopSettings "+$loop)
        $frames=[regex]::Matches($loopBlock,'\{\s*([\d.\-]+),\s*([\d.\-]+),\s*([\d.\-]+)\s*\}')
        foreach($f in $frames){$hover+=($f.Groups[3].Value+'f')}
    }
    while($hover.Count -lt 10){$hover+='0.f'}
    $idle=$triples[$i*3+2].Groups[3].Value
    $descriptions=@();$description=$record.Groups[3].Value
    if($description -ne 'NULL'){$descBlock=Extract-Block $source ("static u16 "+$description);foreach($id in [regex]::Matches($descBlock,'0x[0-9a-fA-F]+')){$descriptions+=$id.Value}}
    while($descriptions.Count -lt 10){$descriptions+='0'}
    $metadata+="    {"+$record.Groups[2].Value+','+$record.Groups[4].Value+','+$idle+".f,{"+($hover -join ',')+"},{"+($descriptions -join ',')+"}},`r`n"
}
$metadata+="};`r`n"
# Integer frame literals require a decimal point before the f suffix in MSVC.
$metadata=[regex]::Replace($metadata,'(?<![\w.])(\d+)f\b','$1.f')
[IO.File]::WriteAllText((Join-Path $PSScriptRoot 'compat\generated\menu_metadata.h'),$metadata)
Write-Output 'Generated original label/hover/panel frame tables for all 34 menu kinds.'
$loopPath=Join-Path $MeleeRoot 'src\melee\mn\mn_22EC.c'
$loopSource=[IO.File]::ReadAllText($loopPath)
[IO.File]::WriteAllText((Join-Path $PSScriptRoot 'compat\generated\original_loop.inc'),'/* Unchanged mn_8022ED6C; source SHA256 '+(Get-FileHash $loopPath -Algorithm SHA256).Hash+" */`r`n"+(Extract-Block $loopSource 'float mn_8022ED6C('))
$anim=$header+"struct Melee360OriginalLoop {float start_frame,end_frame,loop_frame;};`r`nstatic const Melee360OriginalLoop Melee360PanelLoops[34][3]={`r`n"
for($i=0;$i -lt 34;$i++){$anim+='    {';for($j=0;$j -lt 3;$j++){$t=$triples[$i*3+$j];$anim+='{'+$t.Groups[1].Value+'f,'+$t.Groups[2].Value+'f,'+$t.Groups[3].Value+'f},'};$anim+="},`r`n"};$anim+="};`r`nstatic const Melee360OriginalLoop Melee360HoverLoops[34][10]={`r`n"
foreach($record in $records){$anim+='    {';$loop=$record.Groups[1].Value;$n=0;if($loop -ne 'NULL'){$lb=Extract-Block $source ('static AnimLoopSettings '+$loop);foreach($t in [regex]::Matches($lb,'\{\s*([\d.\-]+),\s*([\d.\-]+),\s*([\d.\-]+)\s*\}')){$anim+='{'+$t.Groups[1].Value+'f,'+$t.Groups[2].Value+'f,'+$t.Groups[3].Value+'f},';$n++}};while($n -lt 10){$anim+='{0.f,0.f,-0.1f},';$n++};$anim+="},`r`n"};$anim+="};`r`n"
$anim=[regex]::Replace($anim,'(?<![\w.])(\d+)f\b','$1.f')
[IO.File]::WriteAllText((Join-Path $PSScriptRoot 'compat\generated\animation_metadata.h'),$anim)
Write-Output 'Generated original loop helper and complete panel/hover loop ranges.'
