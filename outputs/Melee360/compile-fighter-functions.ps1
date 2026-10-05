$ErrorActionPreference='Stop'
$xedk='C:\Program Files (x86)\Microsoft Xbox 360 SDK'
$env:INCLUDE="$xedk\include\xbox";$env:PATH="$xedk\bin\win32;"+$env:PATH
$base=(Resolve-Path "$PSScriptRoot\..\..\work\melee-base").Path
$out="$PSScriptRoot\build\fighter-functions";New-Item -ItemType Directory -Force $out | Out-Null
$inventory=Get-Content "$PSScriptRoot\logs\gameplay-compile\inventory.json" -Raw|ConvertFrom-Json
$results=@();$count=0
$jobs=@();$inventoryPath="$PSScriptRoot\logs\gameplay-compile\inventory.json"
foreach($workerIndex in 0..3){$jobs+=Start-Job -ArgumentList $inventoryPath,$workerIndex,$xedk,$base,$PSScriptRoot,$out -ScriptBlock {
param($inventoryPath,$workerIndex,$xedk,$base,$projectRoot,$out)
$env:INCLUDE="$xedk\include\xbox";$env:PATH="$xedk\bin\win32;"+$env:PATH
$inventory=Get-Content $inventoryPath -Raw|ConvertFrom-Json;$index=0
foreach($item in $inventory){
 $currentIndex=$index;$index++;if($currentIndex%4 -ne $workerIndex){continue}
 if(!$item.compiled){continue}
 $object=Join-Path $out ([IO.Path]::GetFileName($item.object));$log=$object+'.txt'
 $args=@('/nologo','/c','/TC','/O2','/Gy','/W3','/D_XBOX','/DXBOX','/DLINT','/DDEBUG=1',('/FI'+$projectRoot+'\compat\gameplay_boundary.h'),('/I'+$projectRoot+'\compat'),('/I'+$base+'\src'),('/I'+$base+'\libs\dolphin\include'),('/I'+$base+'\libs\doldecomp\include'),('/I'+[IO.Path]::GetDirectoryName((Join-Path $base $item.source))),('/Fo'+$object))
 if([IO.Path]::GetFileName($item.source) -eq 'lbcardnew.c'){$args+='/FI'+$projectRoot+'\compat\melee\lb\lbcardnew.h'}
 & "$xedk\bin\win32\cl.exe" @args $item.compileSource *> $log
 [pscustomobject]@{compiled=($LASTEXITCODE -eq 0);object=$object;source=$item.source;area=$item.area;log=$log}
}
}}
while(@($jobs|Where-Object State -eq 'Running').Count){Wait-Job -Job $jobs -Any -Timeout 10|Out-Null;$received=@($jobs|Receive-Job);$results+=$received;$count=$results.Count;Write-Output "$count original units compiled with function sections"}
$results+=@($jobs|Receive-Job);$jobs|Remove-Job;$count=$results.Count
$results|ConvertTo-Json|Set-Content "$PSScriptRoot\logs\fighter-functions-inventory.json"
Write-Output "Function sections: $(@($results|Where-Object compiled).Count)/$count; link diagnostic only"
