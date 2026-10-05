param([string]$Dol='C:\Users\luizf\Documents\melee\sys\main.dol',
      [string]$Destination=(Join-Path $PSScriptRoot 'package\RGH\Melee360\melee360-font.bin'))
$ErrorActionPreference='Stop'
if((Get-FileHash -LiteralPath $Dol -Algorithm SHA1).Hash -ne '08E0BF20134DFCB260699671004527B2D6BB1A45'){throw 'Font offsets require the verified GALE01 1.02 main.dol.'}
$bytes=[IO.File]::ReadAllBytes($Dol)
function U32([int]$At){return ([uint64]$bytes[$At]*16777216+[uint64]$bytes[$At+1]*65536+[uint64]$bytes[$At+2]*256+$bytes[$At+3])}
function Segment([uint64]$Address,[int]$Size){
    for($i=0;$i -lt 18;$i++){
        $start=U32 (0x48+$i*4);$count=U32 (0x90+$i*4);$offset=U32 ($i*4)
        if($Address -ge $start -and $Address+$Size -le $start+$count){
            $at=$offset+$Address-$start;if($at+$Size -gt $bytes.Length){throw 'DOL section exceeds file bounds'}
            $result=New-Object byte[] $Size;[Array]::Copy($bytes,[int]$at,$result,0,$Size);return ,$result
        }
    }throw 'Original font address is outside DOL sections'
}
$metrics=Segment ([Convert]::ToUInt64('8040CB00',16)) (288*2)
$atlas=Segment ([Convert]::ToUInt64('8040CD40',16)) (287*512)
$font=New-Object byte[] ($metrics.Length+$atlas.Length)
[Array]::Copy($metrics,0,$font,0,$metrics.Length);[Array]::Copy($atlas,0,$font,$metrics.Length,$atlas.Length)
New-Item -ItemType Directory -Force (Split-Path $Destination) | Out-Null
[IO.File]::WriteAllBytes($Destination,$font)
Write-Output "Extracted original glyph metrics and 287 I4 glyphs: $($font.Length) bytes; original DOL preserved."
