param([switch]$FunctionSections,[switch]$MarioLink,[switch]$HsdMainHeap)
$ErrorActionPreference='Stop'
$xedk='C:\Program Files (x86)\Microsoft Xbox 360 SDK';$env:PATH="$xedk\bin\win32;"+$env:PATH;$env:INCLUDE="$xedk\include\xbox";$env:LIB="$xedk\lib\xbox"
$base=(Resolve-Path "$PSScriptRoot\..\..\work\melee-base").Path;$out=if($FunctionSections){"$PSScriptRoot\build\fighter-create-functions-audit"}else{"$PSScriptRoot\build\fighter-create-audit"};if($HsdMainHeap){$out+='-hsd-main-heap'};New-Item -ItemType Directory -Force $out | Out-Null
$entry="$out\entry.obj"
$entrySource=if($MarioLink){"$PSScriptRoot\diagnostics\mario_link_link_entry.c"}else{"$PSScriptRoot\diagnostics\fighter_create_link_entry.c"}
if($HsdMainHeap){
    if(!$MarioLink){throw 'HsdMainHeap requires MarioLink'}
    $auditEntry="$out\hsd-entry.c"
    @"
#define Melee360FighterCreateLinkEntry M360OriginalFightEntry
#include "$($entrySource.Replace('\','/'))"
#undef Melee360FighterCreateLinkEntry
#include <sysdolphin/baselib/initialize.h>
void Melee360FighterCreateLinkEntry(void){void *lo,*hi;HSD_GetNextArena(&lo,&hi);HSD_CreateMainHeap(lo,hi);M360OriginalFightEntry();}
"@ | Set-Content -Encoding ASCII $auditEntry
    $entrySource=$auditEntry

}
& "$xedk\bin\win32\cl.exe" /nologo /c /TC /MT /DLINT /DDEBUG=1 /D_XBOX ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\dolphin\include') ('/I'+$base+'\libs\doldecomp\include') ('/Fo'+$entry) $entrySource *> "$out\entry-compile.txt"
if($LASTEXITCODE){throw 'Fighter entry compile failed'}
[xml]$project=Get-Content "$PSScriptRoot\Melee360.vcxproj" -Raw;$runtime=@()
foreach($group in $project.Project.ItemGroup){$condition=[string]$group.Condition;if($condition -and $condition -notmatch 'DecompMode'){continue};foreach($item in $group.ClCompile){if(!$item.Include){continue};$name=[IO.Path]::GetFileNameWithoutExtension([string]$item.Include);if($name -eq 'main'){continue};$runtime+=Get-Item "$PSScriptRoot\build\obj\Release\Compat\$name.obj"}}
# HSD render/heap now supplied by runnable native objects; no duplicate audit fragment.
$names=@($runtime|ForEach-Object{$_.BaseName})+@('lbmemory');$inventoryPath=if($FunctionSections){"$PSScriptRoot\logs\fighter-functions-inventory.json"}else{"$PSScriptRoot\logs\gameplay-compile\inventory.json"};$inv=Get-Content $inventoryPath -Raw|ConvertFrom-Json
$selected=@($inv|Where-Object{if(!$_.compiled){return $false};$name=[IO.Path]::GetFileNameWithoutExtension($_.source);return !($name -in $names -or ($_.area -eq 'hsd' -and $name -in @('memory','initialize','video')))})
# Link the remaining original bodies against the exact shared runtime pools.
# Generated remainders omit only functions already supplied by native objects.
& "$env:USERPROFILE\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe" "$PSScriptRoot\diagnostics\generate_hsd_runtime_pools.py"
if($LASTEXITCODE){throw 'HSD pool generation failed'}
$poolModules=@('aobj','displayfunc','mtx','robj','shadow','tev','state','synth','lbarchive','lbfile','lbarq','gmvs','ifall','player','fighter','psdisp')
$remainderObjects=@{}
foreach($module in $poolModules){
    $remainderObject="$out\hsd-remainder-$module.obj"
    & "$xedk\bin\win32\cl.exe" /nologo /c /TC /MT /DLINT /DDEBUG=1 /D_XBOX ('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h') ('/I'+$PSScriptRoot+'\compat') ('/I'+$base+'\src') ('/I'+$base+'\libs\dolphin\include') ('/I'+$base+'\libs\doldecomp\include') ('/Fo'+$remainderObject) "$PSScriptRoot\compat\generated\hsd_audit_$module.c" *> "$out\hsd-remainder-$module-compile.txt"
    if($LASTEXITCODE){Get-Content "$out\hsd-remainder-$module-compile.txt";throw 'HSD remainder compile failed'}
    $remainderObjects[$module]=$remainderObject
}
$selected=@($selected|ForEach-Object{
    $module=[IO.Path]::GetFileNameWithoutExtension($_.source)
    if($remainderObjects.ContainsKey($module)){
        [pscustomobject]@{object=$remainderObjects[$module]}
    }else{$_}
})
# Inventories record absolute locations at compilation time. After moving the
# workspace, resolve only its known project-relative object suffix; validate
# every file instead of rewriting historical provenance or trusting old paths.
$selected=@($selected|ForEach-Object{
    $object=[string]$_.object
    if(!(Test-Path -LiteralPath $object)){
        $marker='\outputs\Melee360\'
        $offset=$object.IndexOf($marker,[StringComparison]::OrdinalIgnoreCase)
        if($offset -lt 0){throw "Cannot relocate inventory object: $object"}
        $object=Join-Path $PSScriptRoot $object.Substring($offset+$marker.Length)
        if(!(Test-Path -LiteralPath $object)){throw "Inventory object missing after relocation: $object"}
    }
    [pscustomobject]@{object=$object}
})
$selected|ForEach-Object{'"'+$_.object+'"'}|Set-Content -Encoding ASCII "$out\library.rsp"
& "$xedk\bin\win32\lib.exe" /nologo ('/OUT:'+$out+'\gameplay.lib') ('@'+$out+'\library.rsp');if($LASTEXITCODE){throw 'Fighter dependency library failed'}
$inputs=@('"'+$entry+'"')+@($runtime|ForEach-Object{'"'+$_.FullName+'"'})+@('"'+$out+'\gameplay.lib"');$inputs|Set-Content -Encoding ASCII "$out\link.rsp"
$messages=& "$xedk\bin\win32\link.exe" /nologo /ENTRY:Melee360FighterCreateLinkEntry /OPT:REF /OPT:ICF ('/OUT:'+$out+'\link-only.exe') ('@'+$out+'\link.rsp') d3d9.lib xnet.lib xgraphics.lib xaudio2.lib xmcore.lib xapilib.lib xboxkrnl.lib 2>&1;$code=$LASTEXITCODE
$reportName=if($FunctionSections){'fighter-create-functions'}else{'fighter-create'}
if($MarioLink){$reportName+='-mario-link'}
if($HsdMainHeap){$reportName+='-hsd-main-heap'}
$messages|Set-Content "$PSScriptRoot\logs\$reportName-link.txt"
$unresolved=@($messages|ForEach-Object{if("$_" -match 'unresolved external symbol (\S+)'){$Matches[1]}}|Sort-Object -Unique)
$unresolved|Set-Content "$PSScriptRoot\logs\$reportName-missing.txt"
[pscustomobject]@{linked=($code -eq 0);unresolvedSymbols=$unresolved.Count;duplicates=@($messages|Where-Object{"$_" -match 'LNK2005'}).Count;path=$(if($HsdMainHeap){'Original HSD heap/render initialization -> Fighter_FirstInitialize -> Fighter_Create(Mario/Link)'}elseif($MarioLink){'Original setup -> Fighter_FirstInitialize -> Fighter_Create(Mario) -> Fighter_Create(Link)'}else{'Fighter_FirstInitialize_80067A84 -> Fighter_Create(Mario)'});hsdMainHeap=$HsdMainHeap.IsPresent;executed=$false;packaged=$false}|ConvertTo-Json|Tee-Object "$PSScriptRoot\logs\$reportName-summary.json"

