$ErrorActionPreference = 'Stop'
$xedk = 'C:\Program Files (x86)\Microsoft Xbox 360 SDK'
$env:PATH = "$xedk\bin\win32;"+$env:PATH
$logs = Join-Path $PSScriptRoot 'logs\gameplay-compile'
$inventory = Get-Content (Join-Path $logs 'inventory.json') -Raw | ConvertFrom-Json
$successful = @($inventory | Where-Object compiled)
if (!$successful.Count) { throw 'Run compile-gameplay.ps1 first.' }
$library = Join-Path $PSScriptRoot 'build\gameplay-objects\original-gameplay-partial.lib'
$response = Join-Path $logs 'library-inputs.rsp'
$successful | ForEach-Object { '"'+$_.object+'"' } | Set-Content -Encoding ASCII $response
& "$xedk\bin\win32\lib.exe" /nologo (('/OUT:')+$library) ('@'+$response)
if ($LASTEXITCODE -ne 0) { throw 'XDK diagnostic library creation failed.' }
$symbols = & "$xedk\bin\win32\dumpbin.exe" /symbols $library
if ($LASTEXITCODE -ne 0) { throw 'Symbol inventory failed.' }
$symbols | Set-Content (Join-Path $logs 'library-symbols.txt')
$defined = @{}
$undefined = @{}
foreach ($line in $symbols) {
    if ($line -match '\bExternal\s+\|\s+(\S+)') {
        $name = $Matches[1]
        if ($line -match '\bUNDEF\b') { $undefined[$name]=$true }
        else { $defined[$name]=$true }
    }
}
$missing = @($undefined.Keys | Where-Object { !$defined.ContainsKey($_) } | Sort-Object)
$missing | Set-Content (Join-Path $logs 'external-dependencies.txt')
$warnings = @($inventory | ForEach-Object {
    $unit = $_
    Get-Content -LiteralPath $unit.log | ForEach-Object {
        if ($_ -match 'warning (C\d+):') { [pscustomobject]@{source=$unit.source;code=$Matches[1];message=$_} }
    }
})
$warnings | Export-Csv -NoTypeInformation (Join-Path $logs 'warnings.csv')
$warningSummary = @($warnings | Group-Object code | Sort-Object Count -Descending | ForEach-Object {[pscustomobject]@{code=$_.Name;count=$_.Count}})
$summary = [pscustomobject]@{
    units=$inventory.Count;compiled=$successful.Count;failed=($inventory.Count-$successful.Count)
    externalSymbols=$missing.Count;library=$library;linkedIntoXex=$false
    warnings=$warningSummary
    areas=@($inventory | Group-Object area | ForEach-Object {[pscustomobject]@{area=$_.Name;total=$_.Count;compiled=@($_.Group | Where-Object compiled).Count}})
}
$summary | ConvertTo-Json -Depth 5 | Set-Content (Join-Path $logs 'summary.json')
$summary | ConvertTo-Json -Depth 5
Write-Output 'Partial diagnostic library only. Missing modules, runtime services, ABI and behavioral checks still block executing these scenes.'
