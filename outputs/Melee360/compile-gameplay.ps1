param([string[]]$Areas = @('ft','gm','mn','gr','it','mp','pl','cm','if','ef','lb','sfx','hsd','db','ty','vi'), [switch]$RetryFailed)
$ErrorActionPreference = 'Stop'
$base = (Resolve-Path (Join-Path $PSScriptRoot '..\..\work\melee-base')).Path
foreach($area in $Areas){
    $areaRoot=Join-Path $base "src\melee\$area"
    if($area -eq 'hsd'){$areaRoot=Join-Path $base 'src\sysdolphin\baselib'}
    if($area -notmatch '^[a-z]+$' -or !(Test-Path -LiteralPath $areaRoot)){throw "Unknown source area: $area"}
}
if('hsd' -in $Areas){& (Join-Path $PSScriptRoot 'generate-hsd-font-includes.ps1')}
$xedk = 'C:\Program Files (x86)\Microsoft Xbox 360 SDK'
$env:PATH = "$xedk\bin\win32;" + $env:PATH
$env:INCLUDE = "$xedk\include\xbox"
$out = Join-Path $PSScriptRoot 'build\gameplay-objects'
$logs = Join-Path $PSScriptRoot 'logs\gameplay-compile'
New-Item -ItemType Directory -Force $out,$logs | Out-Null
& (Join-Path $PSScriptRoot 'generate-compat-headers.ps1')
$arguments = @('/nologo','/c','/TC','/O2','/W3','/D_XBOX','/DXBOX','/DLINT','/DDEBUG=1',('/FI'+$PSScriptRoot+'\compat\gameplay_boundary.h'),('/I'+$PSScriptRoot+'\compat'),('/I'+$base+'\src'),('/I'+$base+'\libs\dolphin\include'),('/I'+$base+'\libs\doldecomp\include'))
$results = @()
if (Test-Path (Join-Path $logs 'inventory.json')) { $results = @(Get-Content (Join-Path $logs 'inventory.json') -Raw | ConvertFrom-Json) }
foreach ($area in $Areas) {
    $areaRoot = "$base\src\melee\$area"
    if($area -eq 'hsd'){$areaRoot="$base\src\sysdolphin\baselib"}
    if ($area -notmatch '^[a-z]+$' -or !(Test-Path -LiteralPath $areaRoot)) { throw "Unknown source area: $area" }
    $files = Get-ChildItem -LiteralPath $areaRoot -Filter '*.c' -Recurse | Sort-Object FullName
    foreach ($file in $files) {
        $relative = $file.FullName.Substring($base.Length+1)
        if ($RetryFailed -and @($results | Where-Object { $_.source -eq $relative -and $_.compiled }).Count) { continue }
        $id = $relative.Replace('\','_').Replace('.c','')
        $object = Join-Path $out "$id.obj"
        $log = Join-Path $logs "$id.txt"
        $extra = @()
        $sourceText = [IO.File]::ReadAllText($file.FullName)
        $adapted = [regex]::Replace($sourceText, 'static MotionFlags const (\w+)\s*=\s*([^;]+);', {
            param($match)
            '#define '+$match.Groups[1].Value+' ((MotionFlags) ('+([regex]::Replace($match.Groups[2].Value,'\s+',' '))+'))'
        })
        $adapted = [regex]::Replace($adapted, '(?m)^([^\r\n;{}]+?)\s+ATTRIBUTE_ALIGN\((\d+)\)', '__declspec(align($2)) $1')
        $adapted = [regex]::Replace($adapted, 'static u32 const ((?:transition|motion)_flags\d+)\s*=\s*([^;]+);', {
            param($match)
            '#define '+$match.Groups[1].Value+' ((u32) ('+([regex]::Replace($match.Groups[2].Value,'\s+',' '))+'))'
        })
        $adapted = [regex]::Replace($adapted, '\b3\.4028235[eE]\+?38[fF]\b', '3.40282346638528859812e38F')
        if ($file.Name -eq 'dbinit.c') {
            # Native thread diagnostics consume actual queried stack pages. GC
            # linker-array stack labels have no corresponding Xenon symbol ABI.
            $adapted = [regex]::Replace($adapted, 'void db_PrintThreadInfo\(void\)\s*\{.*?\r?\n\}', "void Melee360PrintThreadInfo(void);`r`nvoid db_PrintThreadInfo(void) { Melee360PrintThreadInfo(); }", [Text.RegularExpressions.RegexOptions]::Singleline)
        }
        if ($file.Name -eq 'grheal.c') { $adapted = $adapted.Replace('static size_t const char_id_count = 26;','enum { char_id_count = 26 };') }
        if ($file.Name -eq 'crypt.c') { $adapted = $adapted.Replace('const int md5_bytes = 16;','enum { md5_bytes = 16 };') }
        if ($file.Name -eq 'sobjlib.c') {
            $adapted = [regex]::Replace($adapted, 'GXSetTev(ColorS10|KColor)\(([^,]+),\s*\((GXColorS10|GXColor)\)\s*\{([^}]+)\}\);', {
                param($match)
                '{ '+$match.Groups[3].Value+' melee360_color = {'+$match.Groups[4].Value+'}; GXSetTev'+$match.Groups[1].Value+'('+$match.Groups[2].Value+', melee360_color); }'
            })
        }
        if ($file.Name -eq 'ground.c') { $adapted = $adapted.Replace('const size_t vals_count = 32;','enum { vals_count = 32 };') }
        if ($file.Name -eq 'lbfile.c') {
            $adapted = $adapted.Replace('const int FILE_EXTENSION_LENGTH = 4;','enum { FILE_EXTENSION_LENGTH = 4 };')
            $adapted = $adapted.Replace('const int MAX_BASENAME_LENGTH = MAX_FILENAME_LENGTH - FILE_EXTENSION_LENGTH;','enum { MAX_BASENAME_LENGTH = MAX_FILENAME_LENGTH - FILE_EXTENSION_LENGTH };')
        }
        $compileSource = $file.FullName
        if ($adapted -ne $sourceText) {
            $generated = Join-Path $out 'adapted'
            New-Item -ItemType Directory -Force $generated | Out-Null
            $compileSource = Join-Path $generated "$id.c"
            [IO.File]::WriteAllText($compileSource,"/* Isolated declaration adaptation; original SHA256: $((Get-FileHash $file.FullName).Hash) */`r`n"+$adapted)
            $extra += '/I'+$file.DirectoryName
        }
        if ($file.Name -eq 'lbcardnew.c') { $extra += '/FI'+$PSScriptRoot+'\compat\melee\lb\lbcardnew.h' }
        $messages = & "$xedk\bin\win32\cl.exe" @arguments @extra (('/Fo')+$object) $compileSource 2>&1
        $code = $LASTEXITCODE
        $messages | Set-Content -LiteralPath $log
        $errors = @($messages | ForEach-Object { "$PSItem" } | Where-Object { $_ -match '(fatal error|error C\d+)' })
        $results = @($results | Where-Object { $_.source -ne $relative })
        $results += [pscustomobject]@{source=$relative;compileSource=$compileSource;area=$area;compiled=($code -eq 0);exitCode=$code;sha256=(Get-FileHash -LiteralPath $file.FullName).Hash;errors=$errors;object=$object;log=$log}
    }
    Write-Output "$area : $(@($results | Where-Object {$_.area -eq $area -and $_.compiled}).Count)/$($files.Count) compiled"
    $results | ConvertTo-Json -Depth 5 | Set-Content (Join-Path $logs 'inventory.json')
}
$results | Export-Csv -NoTypeInformation (Join-Path $logs 'inventory.csv')
Write-Output "Compiled $(@($results | Where-Object compiled).Count)/$($results.Count) original translation units. Objects are isolated diagnostics; they are not linked into default.xex."
