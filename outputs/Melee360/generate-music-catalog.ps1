$ErrorActionPreference='Stop'
$base=(Resolve-Path (Join-Path $PSScriptRoot '../../work/melee-base')).Path
$audio=[IO.File]::ReadAllText((Join-Path $base 'src/melee/lb/lbaudio_ax.c'))
$source=[IO.File]::ReadAllText((Join-Path $base 'src/melee/mn/mnsoundtest.c'))
$hps=[regex]::Match($audio,'(?s)static const char\* hps_files\[\] = \{(.*?)\};')
$files=@([regex]::Matches($hps.Groups[1].Value,'"([^"]+\.hps)"') | ForEach-Object {$_.Groups[1].Value})
$orderBlock=[regex]::Match($source,'(?s)u8 text_ids\[\] = \{(.*?)\};')
$order=@([regex]::Matches($orderBlock.Groups[1].Value,'0x[0-9A-Fa-f]+') | ForEach-Object {[Convert]::ToInt32($_.Value.Substring(2),16)})
$dataBlock=[regex]::Match($source,'(?s)soundtest_data data_2\[\] = \{(.*?)\};')
$rows=@([regex]::Matches($dataBlock.Groups[1].Value,'\{\s*(0x[0-9A-Fa-f]+),\s*(0x[0-9A-Fa-f]+)\s*\}') | ForEach-Object {,@([Convert]::ToInt32($_.Groups[1].Value.Substring(2),16),[Convert]::ToInt32($_.Groups[2].Value.Substring(2),16))})
if($files.Count-ne99-or$order.Count-ne80-or$rows.Count-ne80){throw 'Original catalog layout changed; inspect the source.'}
$ids=@();$texts=@();foreach($index in $order){if($index-ge$rows.Count-or$rows[$index][1]-ge$files.Count){throw 'Invalid original catalog reference'};$texts+=$rows[$index][0];$ids+=$rows[$index][1]}
$lines=@('/* Original hps_files and mnsoundtest text_ids/data_2; generated, upstream preserved. */','#ifndef MELEE360_MUSIC_CATALOG_H','#define MELEE360_MUSIC_CATALOG_H','static const char* const Melee360MusicFiles[]={')
$lines+=@($files | ForEach-Object {'    "'+$_+'",'})
$lines+=@('};','enum {Melee360MusicCount=sizeof(Melee360MusicFiles)/sizeof(Melee360MusicFiles[0]),Melee360MusicTrackBase=100};',('static const unsigned char Melee360SoundTrackIds[]={'+($ids -join ',')+'};'),('static const unsigned short Melee360SoundTextIds[]={'+($texts -join ',')+'};'),'enum {Melee360SoundTrackCount=sizeof(Melee360SoundTrackIds)};','#endif')
[IO.File]::WriteAllLines((Join-Path $PSScriptRoot 'src/music_catalog.h'),$lines)
Write-Output 'Original catalog generated: 99 HPS entries, 80 Sound Test entries.'
