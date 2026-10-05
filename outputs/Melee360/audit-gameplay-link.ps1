param([switch]$WithRuntime)
$ErrorActionPreference = 'Stop'
$xedk = 'C:\Program Files (x86)\Microsoft Xbox 360 SDK'
$env:PATH = "$xedk\bin\win32;"+$env:PATH
$env:INCLUDE = "$xedk\include\xbox"
$env:LIB = "$xedk\lib\xbox"
$logs = Join-Path $PSScriptRoot 'logs\gameplay-compile'
$out = Join-Path $PSScriptRoot 'build\gameplay-objects'
$entry = Join-Path $out 'gameplay-link-entry.obj'
& "$xedk\bin\win32\cl.exe" /nologo /c /TC /MT ('/Fo'+$entry) (Join-Path $PSScriptRoot 'diagnostics\gameplay_link_entry.c')
if ($LASTEXITCODE -ne 0) { throw 'Link audit entry compilation failed.' }
$inventory = Get-Content (Join-Path $logs 'inventory.json') -Raw | ConvertFrom-Json
$response = Join-Path $logs 'link-inputs.rsp'
$runtime=@()
if($WithRuntime){
    [xml]$project=Get-Content (Join-Path $PSScriptRoot 'Melee360.vcxproj') -Raw
    $objectDir=Join-Path $PSScriptRoot 'build\obj\Release\Compat'
    foreach($group in $project.Project.ItemGroup){
        $condition=[string]$group.Condition
        if($condition -and $condition -notmatch 'DecompMode'){continue}
        foreach($item in $group.ClCompile){
            if(!$item.Include){continue}
            $name=[IO.Path]::GetFileNameWithoutExtension([string]$item.Include)
            if($name -eq 'main'){continue}
            $path=Join-Path $objectDir "$name.obj"
            if(!(Test-Path $path)){throw "Build Release/Compat before runtime audit: missing $path"}
            $runtime+=Get-Item $path
        }
    }
}
$runtimeNames=@($runtime|ForEach-Object{$_.BaseName})
$selected=@($inventory | Where-Object {
    if(!$_.compiled){return $false}
    if($WithRuntime -and $_.area -eq 'hsd'){
        $name=[IO.Path]::GetFileNameWithoutExtension($_.source)
        if($name -in $runtimeNames -or $name -in @('memory','initialize')){return $false}
    }
    return $true
})
$inputs = @('"'+$entry+'"') + @($selected | ForEach-Object {'"'+$_.object+'"'})+@($runtime|ForEach-Object{'"'+$_.FullName+'"'})
$inputs | Set-Content -Encoding ASCII $response
# No /FORCE, no missing-function stubs, no XEX generation. Preserve working build.
$messages = & "$xedk\bin\win32\link.exe" /nologo /ENTRY:Melee360GameplayLinkAuditEntry /OPT:NOREF /OPT:NOICF ('/OUT:'+(Join-Path $out 'gameplay-link-audit.exe')) ('@'+$response) d3d9.lib xaudio2.lib xmcore.lib xapilib.lib xboxkrnl.lib 2>&1
$code = $LASTEXITCODE
$messages | Set-Content (Join-Path $logs 'link-audit.txt')
$unresolved = @($messages | ForEach-Object { "$PSItem" } | Where-Object {$_ -match 'LNK2001|LNK2019'})
$duplicates = @($messages | ForEach-Object { "$PSItem" } | Where-Object {$_ -match 'LNK2005'})
$names = @($unresolved | ForEach-Object { if ($_ -match 'unresolved external symbol (\S+)') { $Matches[1] } } | Sort-Object -Unique)
$names | Set-Content (Join-Path $logs 'link-missing-symbols.txt')
$summary = [pscustomobject]@{linked=($code -eq 0);exitCode=$code;unresolvedSymbols=$names.Count;unresolvedReferences=$unresolved.Count;duplicateDefinitions=$duplicates.Count;runtimeIncluded=$WithRuntime.IsPresent;packaged=$false}
$summary | ConvertTo-Json | Set-Content (Join-Path $logs 'link-audit-summary.json')
$summary | ConvertTo-Json


