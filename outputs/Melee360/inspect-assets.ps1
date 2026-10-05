param([string]$AssetsRoot = 'C:\Users\luizf\Documents\melee_extraido',
      [string]$SystemRoot = 'C:\Users\luizf\Documents\melee\sys')
$ErrorActionPreference = 'Stop'
function Read-BE32([byte[]]$Bytes, [int]$Offset) {
    if ($Offset -lt 0 -or $Offset + 4 -gt $Bytes.Length) { throw 'FST out of bounds.' }
    return [uint32](([uint32]$Bytes[$Offset] * 16777216) + ([uint32]$Bytes[$Offset+1] * 65536) + ([uint32]$Bytes[$Offset+2] * 256) + $Bytes[$Offset+3])
}
$fst = [IO.File]::ReadAllBytes((Join-Path $SystemRoot 'fst.bin'))
$count = Read-BE32 $fst 8
if ($count -lt 1 -or $count -gt [Math]::Floor($fst.Length / 12)) { throw 'Invalid FST count.' }
$names = [int]$count * 12
$stack = [Collections.Generic.List[object]]::new()
$stack.Add(@{Path=''; End=$count})
$entries = [Collections.Generic.List[object]]::new()
for ($i = 1; $i -lt $count; $i++) {
    while ($stack.Count -gt 1 -and $i -ge $stack[$stack.Count-1].End) { $stack.RemoveAt($stack.Count-1) }
    $word = Read-BE32 $fst ($i * 12)
    $nameOffset = $names + ($word -band 0xFFFFFF)
    if ($nameOffset -ge $fst.Length) { throw 'Invalid FST filename offset.' }
    $endName = $nameOffset
    while ($endName -lt $fst.Length -and $fst[$endName] -ne 0) { $endName++ }
    if ($endName -eq $fst.Length) { throw 'Unterminated FST name.' }
    $name = [Text.Encoding]::ASCII.GetString($fst, $nameOffset, $endName-$nameOffset)
    $relative = if ($stack[$stack.Count-1].Path) { $stack[$stack.Count-1].Path + '/' + $name } else { $name }
    if (($word -shr 24) -ne 0) {
        $endIndex = Read-BE32 $fst ($i*12+8)
        if ($endIndex -le $i -or $endIndex -gt $count) { throw 'Invalid FST directory range.' }
        $stack.Add(@{Path=$relative; End=$endIndex})
    } else {
        $length = Read-BE32 $fst ($i*12+8)
        $local = Join-Path $AssetsRoot $relative
        $file = Get-Item -LiteralPath $local -ErrorAction SilentlyContinue
        $entries.Add([pscustomobject]@{Path=$relative;ExpectedBytes=$length;ActualBytes=if($file){$file.Length}else{$null};Status=if(!$file){'missing'}elseif($file.Length -ne $length){'size-mismatch'}else{'ok'}})
    }
}
$bad = @($entries | Where-Object Status -ne 'ok')
$report = [pscustomobject]@{AssetsRoot=$AssetsRoot;FstEntries=$count;ExpectedFiles=$entries.Count;MissingOrWrongSize=$bad.Count;MainDolSHA1=(Get-FileHash -LiteralPath (Join-Path $SystemRoot 'main.dol') -Algorithm SHA1).Hash;Files=$entries}
New-Item -ItemType Directory -Force (Join-Path $PSScriptRoot 'logs') | Out-Null
$report | ConvertTo-Json -Depth 5 | Set-Content (Join-Path $PSScriptRoot 'logs\assets-verification.json')
Write-Output "FST check: $($entries.Count) expected files, $($bad.Count) missing/wrong sizes."
if ($bad.Count) { $bad | Select-Object -First 15 | Format-Table; throw 'Asset extraction does not match the FST.' }
