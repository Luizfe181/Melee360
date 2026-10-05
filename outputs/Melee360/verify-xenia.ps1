param([string]$XeniaRoot = 'C:\Users\luizf\Downloads\xenia_canary_windows', [switch]$TitlePreview, [switch]$MovieToTitle, [switch]$MenuPreview, [switch]$CharacterPreview, [switch]$AnimationPreview, [switch]$StagePreview, [switch]$TrophiesPreview, [switch]$TrainingPreview, [switch]$SoundPreview, [switch]$ArchivePreview, [switch]$OptionsPreview, [switch]$DataPreview, [string]$PackageRoot,[string]$ConfigSource,[ValidateRange(0,900)][int]$TimeoutSeconds=0)
$ErrorActionPreference = 'Stop'
if(([int]$TitlePreview.IsPresent+[int]$MovieToTitle.IsPresent+[int]$MenuPreview.IsPresent+[int]$CharacterPreview.IsPresent+[int]$AnimationPreview.IsPresent+[int]$StagePreview.IsPresent+[int]$TrophiesPreview.IsPresent+[int]$TrainingPreview.IsPresent+[int]$SoundPreview.IsPresent+[int]$ArchivePreview.IsPresent+[int]$OptionsPreview.IsPresent+[int]$DataPreview.IsPresent) -gt 1) {throw 'Choose one test path.'}
if($DataPreview -or $OptionsPreview -or $ArchivePreview -or $SoundPreview -or $CharacterPreview -or $AnimationPreview -or $StagePreview -or $TrophiesPreview -or $TrainingPreview){$MenuPreview=$true}
$workspace = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path
$scratch = Join-Path $workspace 'work\xenia-test'
New-Item -ItemType Directory -Force $scratch | Out-Null
$exe = Join-Path $scratch 'xenia_canary.exe'
Copy-Item -LiteralPath (Join-Path $XeniaRoot 'xenia_canary.exe') -Destination $exe -Force
$sourceConfig = if($ConfigSource){(Resolve-Path -LiteralPath $ConfigSource).Path}else{Join-Path $XeniaRoot 'xenia-canary.config.toml'}
$config = [IO.File]::ReadAllText($sourceConfig)
if([string]::IsNullOrWhiteSpace($config) -or $config.Contains([string][char]0)){throw 'Invalid Xenia configuration (empty/NUL bytes). Supply a valid -ConfigSource before running probes.'}
$config = $config -replace '(?m)^headless\s*=\s*false', 'headless = true'
# Automated diagnostics stay silent; AX/DMA still process normally.
$config = $config -replace '(?m)^mute\s*=\s*(true|false)', 'mute = true'
$config = $config -replace '(?m)^allow_game_relative_writes\s*=\s*false', 'allow_game_relative_writes = true'
$emulatorLog = (Join-Path $scratch 'xenia.log').Replace('\','/')
$config = $config -replace '(?m)^log_file\s*=\s*"[^"\r\n]*"', ('log_file = "' + $emulatorLog + '"')
# Accurate queries are required by the diagnostic alpha-discard probe only.
$config = $config -replace '(?m)^occlusion_query\s*=\s*"[^"\r\n]*"', 'occlusion_query = "strict"'
$config = $config -replace '(?m)^readback_resolve\s*=\s*"[^"\r\n]*"', 'readback_resolve = "full"'
$config = $config -replace '(?m)^async_shader_compilation\s*=\s*true', 'async_shader_compilation = false'
$configPath = Join-Path $scratch 'test.toml'
[IO.File]::WriteAllText($configPath, $config)
$package = if($PackageRoot){(Resolve-Path -LiteralPath $PackageRoot).Path}else{Join-Path $PSScriptRoot 'package\RGH\Melee360'}
$runtimeLog = Join-Path $package 'melee360.log'
if (!(Test-Path -LiteralPath (Join-Path $package 'default.xex'))) { throw 'Build package-rgh.ps1 first.' }
if (Test-Path -LiteralPath $runtimeLog) {
    $backup = Join-Path $PSScriptRoot ('logs\runtime-before-verification-' + (Get-Date -Format 'yyyyMMdd-HHmmss-fff') + '.log')
    Copy-Item -LiteralPath $runtimeLog -Destination $backup
}
[IO.File]::WriteAllText($runtimeLog, '')
$previewFlag = Join-Path $package 'title-preview.flag'
$verificationFlag = Join-Path $package 'verification.flag'
$menuFlag = Join-Path $package 'menu-preview.flag'
$characterFlag = Join-Path $package 'character-preview.flag'
$animationFlag = Join-Path $package 'animation-preview.flag'
$stageFlag = Join-Path $package 'stage-preview.flag'
$dataFlag=Join-Path $package 'data-preview.flag'
if($DataPreview){if(Test-Path $dataFlag){throw 'Existing data flag'};[IO.File]::WriteAllText($dataFlag,'read-only original records test')}
$optionsFlag=Join-Path $package 'options-preview.flag'
if($OptionsPreview){if(Test-Path $optionsFlag){throw 'Existing options flag'};[IO.File]::WriteAllText($optionsFlag,'original options test')}
$archiveFlag=Join-Path $package 'archive-preview.flag'
if($ArchivePreview){if(Test-Path $archiveFlag){throw 'Existing archive flag'};[IO.File]::WriteAllText($archiveFlag,'archive playback test')}
$effectsFlag=Join-Path $package 'audio-effects-preview.flag'
if($SoundPreview){if(Test-Path $effectsFlag){throw 'Existing effects flag'};[IO.File]::WriteAllText($effectsFlag,'original effects streaming test')}
$soundFlag=Join-Path $package 'sound-preview.flag'
if($SoundPreview){if(Test-Path $soundFlag){throw 'Existing sound flag'};[IO.File]::WriteAllText($soundFlag,'sound playback test')}
$trainingFlag=Join-Path $package 'training-preview.flag'
if($TrainingPreview){if(Test-Path $trainingFlag){throw 'Existing training flag'};[IO.File]::WriteAllText($trainingFlag,'isolated Training frontend test')}
$trophyFlag=Join-Path $package 'trophy-preview.flag'
if($TrophiesPreview){if(Test-Path $trophyFlag){throw 'Existing trophy-preview.flag must be removed first.'};[IO.File]::WriteAllText($trophyFlag,'diagnostic trophies verification')}
if(Test-Path -LiteralPath $stageFlag){throw 'Existing stage-preview.flag must be removed first.'}
if(Test-Path -LiteralPath $menuFlag) {throw 'Existing menu-preview.flag must be removed first.'}
if(Test-Path -LiteralPath $verificationFlag) {throw 'Existing verification.flag must be removed first.'}
if(Test-Path -LiteralPath $previewFlag) {throw 'Remove the existing diagnostic title-preview.flag before verification.'}
[IO.File]::WriteAllText($verificationFlag,'ignore controller during automated verification')
if($TitlePreview) {[IO.File]::WriteAllText($previewFlag,'diagnostic test only')}
if($AnimationPreview){if(Test-Path -LiteralPath $animationFlag){throw 'Existing animation flag must be removed first'};[IO.File]::WriteAllText($animationFlag,'diagnostic loop test')}
if($CharacterPreview){if(Test-Path -LiteralPath $characterFlag){throw 'Existing character flag must be removed first'};[IO.File]::WriteAllText($characterFlag,'diagnostic character test')}
if($MenuPreview) {[IO.File]::WriteAllText($menuFlag,'diagnostic menu navigation test')}
if($StagePreview){[IO.File]::WriteAllText($stageFlag,'diagnostic Battlefield animation test')}
$process = Start-Process -FilePath $exe -ArgumentList ('"' + (Join-Path $package 'default.xex') + '" --config="' + $configPath + '" --headless=true') -WorkingDirectory $scratch -WindowStyle Hidden -PassThru
try {
    $passed = $false
    $deadline = if($TimeoutSeconds){$TimeoutSeconds}elseif($StagePreview -or $TrophiesPreview -or $TrainingPreview -or $SoundPreview){180}elseif($MovieToTitle) {140} else {90}
    for ($attempt = 0; $attempt -lt $deadline; $attempt++) {
        Start-Sleep -Milliseconds 1000
        $logStream=[IO.File]::Open($runtimeLog,[IO.FileMode]::Open,[IO.FileAccess]::Read,[IO.FileShare]::ReadWrite)
        $logReader=New-Object IO.StreamReader($logStream)
        try{$messages=$logReader.ReadToEnd()}finally{$logReader.Dispose()}
        if ($messages.Contains('FAILED') -or $messages.Contains('HSD ASSERT')) { throw 'Guest runtime reported a failed probe.' }
        $drawingPassed = if($TitlePreview) {
            $messages.Contains('Title: first original mesh draw submitted') -and $messages.Contains('Title: animated original scene ready; batches=33 textures=28 skipped=0') -and $messages.Contains('Animation: title 120 updates')
        } else {
            $messages.Contains('Intro: first textured draw submitted') -and $messages.Contains('Intro: video advanced beyond frame 30')
        }
        if($MovieToTitle) {$drawingPassed = $drawingPassed -and $messages.Contains('Intro: movie video stream completed') -and $messages.Contains('Title: first original mesh draw submitted')}
        if($MenuPreview) {$drawingPassed=$messages.Contains('Menu: first original selectable menu draw submitted; root input uses upstream mn_8022DB10') -and $messages.Contains('Menu: file persistence write/rename/readback passed') -and $messages.Contains('Menu: configuration ABI/serialization passed') -and $messages.Contains('Menu navigation: page=13') -and $messages.Contains('Menu navigation: page=20') -and $messages.Contains('Boot: MvOmake15.mth prepared 448x336') -and $messages.Contains('Boot: MvHowto.mth prepared 640x480') -and $messages.Contains('Audio: original swm_15min.hps streaming') -and $messages.Contains('Audio: original howto.hps streaming') -and $messages.Contains('Menu transition: main menu to title')}
        if($CharacterPreview){$drawingPassed=$messages.Contains('Character select: slot=1 name=Mario portrait=original2D; P1=HMN P2-P4=NA') -and $messages.Contains('Character select: slot=11 name=Ness portrait=original2D; P1=HMN P2-P4=NA') -and $messages.Contains('Character select: confirmed') -and $messages.Contains('Character select: confirmation cancelled') -and $messages.Contains('Character select: returned to VS menu') -and $messages.Contains('Menu transition: main menu to title')}
        if($AnimationPreview){$drawingPassed=$messages.Contains('Animation: menu 120 updates') -and $messages.Contains('Animation: title 120 updates') -and $messages.Contains('Menu transition: main menu to title')}
        if($TrophiesPreview){$drawingPassed=$messages.Contains('Trophies: gallery original model loaded') -and $messages.Contains('Trophies: diagnostic lottery acquired Party Ball') -and $messages.Contains('Trophies: collection original models loaded') -and $messages.Contains('Trophies: returned to original trophy menu') -and $messages.Contains('Menu navigation: page=3 selection=0 destination=111') -and $messages.Contains('Trophies: list opened') -and $messages.Contains('Trophies: list closed') -and $messages.Contains('Trophies: gallery selected Party Ball') -and $messages.Contains('Menu navigation: page=0 selection=2 destination=-1')}
        if($DataPreview){$drawingPassed=$messages.Contains('Data records: per-fighter read-only viewer entered') -and $messages.Contains('Data records: original GCI checksum/manifest and statistics validated') -and $messages.Contains('Options: original page=152 loaded') -and $messages.Contains('Menu transition: main menu to title')}
        if($OptionsPreview){$drawingPassed=$messages.Contains('PAD sampling / OS sound settings: cached cadence, input conversion, Mono/Stereo and invalid-value preservation passed') -and $messages.Contains('OS sound mode synchronized with menu setting') -and $messages.Contains('Options: original page=19 loaded') -and $messages.Contains('Options: original page=20 loaded') -and $messages.Contains('Options: per-port rumble setting changed') -and $messages.Contains('Audio: mono output matrix applied') -and $messages.Contains('Audio: stereo output matrix applied') -and $messages.Contains('Menu transition: main menu to title')}
        if($ArchivePreview){$drawingPassed=$messages.Contains('Audio: original swm_15min.hps streaming') -and $messages.Contains('Audio: original howto.hps streaming') -and $messages.Contains('Boot: MvOmake15.mth prepared') -and $messages.Contains('Boot: MvHowto.mth prepared') -and $messages.Contains('Menu archive: video returned') -and $messages.Contains('Menu transition: main menu to title')}
        if($SoundPreview){$drawingPassed=$messages.Contains('Audio effects: PCM -> original Std/Hi/Chorus -> XAudio2 chain enabled') -and $messages.Contains('Audio effects: processed PCM submitted; frame accounting and block carry passed') -and $messages.Contains('Sound test: original MenMainConTs scene loaded') -and $messages.Contains('Sound test: play original id=0 file=opening.hps') -and $messages.Contains('Sound test: play original id=1 file=castle.hps') -and $messages.Contains('Audio: original opening.hps streaming') -and $messages.Contains('Audio: original castle.hps streaming') -and $messages.Contains('Sound test: playback stopped') -and $messages.Contains('Sound test: fade-out completed') -and $messages.Contains('Sound test: returned to Data menu') -and $messages.Contains('Menu transition: main menu to title')}
        if($TrainingPreview){$drawingPassed=$messages.Contains('AXFX standard reverb: impulse, independent channels, predelay wrap, ownership and allocation-failure probes passed') -and $messages.Contains('HSD object pool statistics: live registry report and allocation preservation passed') -and $messages.Contains('Original logic subset: directed intersections, Mario/Link native gravity and Battlefield point sweeps passed; no Fighter created') -and $messages.Contains('Fight setup: Mario human P1, Link CPU level 9 P2, Battlefield, 3 stocks prepared; match runtime NOT started') -and $messages.Contains('Stage select: original MnSlMap models/camera/frames loaded') -and $messages.Contains('Stage select: unavailable stage rejected') -and $messages.Contains('Training: original defaults/human/CPU/training rules probe passed') -and $messages.Contains('Training: original rules/player data prepared for Battlefield; fighter runtime NOT started') -and $messages.Contains('Stage select: returned to original CSS') -and $messages.Contains('Menu navigation: page=0')}
        if($StagePreview){$drawingPassed=$messages.Contains('Battlefield: entered stage animation diagnostic') -and $messages.Contains('Battlefield: variant=0 120 animation updates; skipped_meshes=0') -and $messages.Contains('Battlefield: variant=1 120 animation updates; skipped_meshes=0') -and $messages.Contains('Battlefield: variant=2 120 animation updates; skipped_meshes=0') -and $messages.Contains('Battlefield: variant=3 120 animation updates; skipped_meshes=0') -and $messages.Contains('Battlefield: returned to character select') -and $messages.Contains('Character select: returned to VS menu') -and $messages.Contains('Menu navigation: page=0 selection=1 destination=-1')}
        if ($messages.Contains('AX stereo ramps: original setter, signed deltas, split blocks and 16-bit wrap passed') -and $messages.Contains('VI/XFB: staged buffer/black changes, atomic flush and progressive field probes passed') -and $messages.Contains('VI/XFB: 120 native swaps') -and $messages.Contains('HSD render: original pass lifecycle, native progressive dimensions, RGB/Z24 and full coverage passed') -and $messages.Contains('HSD main heap: original reset, native ownership, allocation and live-reset protection passed') -and $messages.Contains('GX TEV: direct, indirect, vertex routing, original helpers, LOD and Z texture GPU validation passed') -and $messages.Contains('GX texture expansion: 45 GPU probes, 8 units, CI palettes, mip levels, TLUT reload and texture invalidation passed') -and $messages.Contains('GX texture binding: original descriptors, Xenon pointers, tiled RGBA8 and 6 GPU alpha/wrap probes passed') -and $messages.Contains('GX pixel format: RGB8/Z24 native targets, depth-only mask and alpha exclusion passed') -and $messages.Contains('HSD pool lifecycle: original free/forget retains backing memory; isolated cleanup and registry restoration passed') -and $messages.Contains('HSD arena ownership: primary bounds, per-heap live counts and reclaim eligibility passed') -and $messages.Contains('Video settings: native format/progressive queries, persistent preference and original bit masking passed') -and $messages.Contains('FIO / OS memory: native file export, exclusive creation, read-only protection, stale handles and arena capacity probes passed') -and $messages.Contains('Audio effects bridge: identical PCM across HPS partitions, partial final block and exact frame count passed') -and $messages.Contains('AXFX chorus: impulse, ring wrap, fractional modulation and allocation ownership probes passed') -and $messages.Contains('AXFX high reverb: impulse, channels, predelay, crosstalk and allocation ownership probes passed') -and $messages.Contains('GX alpha compare: 8 comparisons at reference boundaries and AND/OR/XOR/XNOR GPU occlusion probes passed') -and $messages.Contains('GX matrix index: per-vertex slots 0/27, display list byte order and current-matrix preservation passed') -and $messages.Contains('FPS overlay: first draw submitted') -and $messages.Contains('FPS overlay: first one-second presentation sample computed') -and $messages.Contains('GX integer positions: S16 direct/indexed negative fractional, S8 and U16 probes passed') -and $messages.Contains('GX topology: quads/strip/fan winding and Xbox draws passed') -and $messages.Contains('HSD heap: owner-aware free, live data preservation and current heap transition passed') -and $messages.Contains('Native original archives: PlCo/Mario/costume/Battlefield relocated') -and $messages.Contains('Xenon cache: native store/flush/invalidate byte preservation probe passed') -and $messages.Contains('Original AXFX delay: impulse/feedback/wrap/ownership/failure probes passed') -and $messages.Contains('120 successful frame presentations') -and
            $messages.Contains('Renderer probe: title joints=16 meshes=13 triangle_vertices=4926 passed') -and
            $messages.Contains('first diagnostic frame presented') -and
            $messages.Contains('Boot: MvOpen.mth prepared') -and
            $drawingPassed -and
            $messages.Contains('ftDataMario found') -and
            $messages.Contains('memory/allocator/list/random/ID/class probes passed') -and
            $messages.Contains('rumble bitfield ABI passed') -and
            $messages.Contains('Game rules layout/bitfield ABI passed') -and
            $messages.Contains('Original GObj scheduler priority/pause/self-delete probes passed') -and
            $messages.Contains('Original portable matrix/vector and Xbox tick clock probes passed') -and
            $messages.Contains('Original CSS core: 25 icon/CKind commits and cursor/token probes passed') -and
            $messages.Contains('DVD filesystem: original FST/ID and deferred Mario read probes passed') -and
            $messages.Contains('Original GX CPU: light attenuation/color and texture tile/mipmap probes passed') -and
            $messages.Contains('Original calendar: epoch/leap/negative/subsecond probes passed') -and
            $messages.Contains('HSD report callback: text/length/reentrancy/reset probes passed') -and
            $messages.Contains('GX Xbox: native blend/depth/color/scissor and GPU fence probes passed') -and
            $messages.Contains('OS alarms/CARD/ARAM: deferred callbacks and persisted byte-exact save probes passed') -and
            $messages.Contains('Audio: XAudio2 engine/master voice initialized') -and
            (!$MenuPreview -or $messages.Contains('Audio: original HPS samples consumed by XAudio2')) -and
            (!$MenuPreview -or $messages.Contains('Menu scheduler: original GObj_RunProcs dispatched 120 active updates'))) { $passed = $true; break }
        if ($process.HasExited) { throw 'Xenia exited before the runtime probes completed.' }
    }
    if(Test-Path -LiteralPath (Join-Path $package 'hsd-aa.flag')){
        $passed = $passed -and $messages.Contains('HSD AA: 120 original screen copies; 242 to 480 filter/scale, original queues and synchronized scaler swaps passed') -and $messages.Contains('GX Z16: 249856 original CPU code roundtrips, 144 GPU equality cases for regular/Z-texture and four compression modes passed')
    }
    $passed = $passed -and $messages.Contains('GX raster: 768 eight-unit UV offset checks and 26 exact GPU coverage cases; points/lines/strip/clipping/cull passed') -and $messages.Contains('GX fog: 10 original table checks and 100 GPU color/depth/range/alpha cases passed; range subpixel accuracy unverified') -and $messages.Contains('GX raster display lists: original byte order, points/lines/strip decoded and submitted')
    $passed = $passed -and $messages.Contains('AX original CPU control: result=1 (voices, priority stealing, parameters, auxiliary rings)')
    $passed = $passed -and $messages.Contains('GX texture copy: 32 GPU copies, 1352 decoded pixels, RGB565/RGB5A3/RGBA8, cropped padded tiles and AA resolve passed')
    $passed = $passed -and $messages.Contains('THP original headers: result=1 (real frame, work size, Huffman/quantization tables and errors)') -and $messages.Contains('AI stream gains: 4 boundary pairs, getters and actual XAudio2 output matrix readback passed') -and $messages.Contains('GX lighting: 7 CPU channel/light arithmetic cases passed; GPU lighting readback pending')
    $passed = $passed -and $messages.Contains('THP native pixels: passed frames=3 entries=2 checked=1843200') -and $messages.Contains('GX texgen: 10 CPU matrix/post/normalize/color cases and 8 projective GPU texture-unit readbacks passed') -and $messages.Contains('GX destination alpha: 4 GPU blend/alpha rejection/depth write readbacks passed') -and $messages.Contains('AI DMA: 32/48 kHz native PCM consumption, DMA callbacks and stop state passed')
    $passed = $passed -and $messages.Contains('OS native threads: real registered worker, handle liveness, stack pages and unregister passed') -and $messages.Contains('OS reset: stable priority, readiness retries, final callbacks and I/O drain passed; image relaunch untested') -and $messages.Contains('GX ZCompLoc: alpha-rejected near depth blocks far draw only in early mode; 3 GPU readbacks passed')
    $passed = $passed -and $messages.Contains('AX PCM consumer: original voice/ARAM, gain, address, end/loop and actual AI playback passed; restricted modes')
    $passed = $passed -and $messages.Contains('AI diagnostics: synthetic playback muted; PCM consumption and callbacks remain active') -and $messages.Contains('AX voice end: NONE/linear/4-tap, 6 boundaries, 32-sample accumulator completion, cleared history and stopped-frame stability passed') -and $messages.Contains('AX linear SRC: 6 fixed vectors, persistent history, fractional phase and split blocks passed') -and $messages.Contains('AX PB updates: original setters, 5 millisecond slots, start/gain/stop, ordering, 64 pairs, reset and invalid offset rejection passed') -and $messages.Contains('AX PB updates live: frame callback schedules 5 slots, queue reset and actual AI consumption passed') -and $messages.Contains('AX envelope: 6 signed vectors, wrap, split blocks and per-voice saturation passed') -and $messages.Contains('AX mixer buses: independent AuxB, 9 lanes, original ring callbacks, 2-frame latency, surround feedback and reinitialization passed') -and $messages.Contains('AX stream context: original type setter, ADPCM history across loop, split boundary and invalid type rejection passed') -and $messages.Contains('AX streaming end: disjoint ring jump, deferred end setter, stop equality and physical ARAM bounds passed') -and $messages.Contains('AX polyphase SRC: 3 banks, 15 fixed vectors, phase/history, split blocks and saturation passed') -and $messages.Contains('AX continuous: two original voices, live mix, real AI consumption, frame callback replace/remove and shutdown passed') -and $messages.Contains('AX ADPCM/SRC: loop history, linear and 4-tap live AI output passed; invalid SRC stops DMA explicitly')
    $passed = $passed -and $messages.Contains('GX RGBA6/dither: 40 GPU readbacks, Bayer parity, six-bit RGB/alpha, destination alpha, rejection and write masks passed; blend/AA unsupported')
    $passed = $passed -and $messages.Contains('Bootstrap heaps: original lbMemory/lbHeap sequence, Stay/HSD/ARAM partitions and allocation/free passed') -and $messages.Contains('Bootstrap common: original lbFile/lbArchive_LoadSymbols and Player/Fighter common globals bound; no Fighter created')
    $passed = $passed -and $messages.Contains('AX depop: original studio fades, signed tails, low-level cutoff and saturated stereo output passed') -and $messages.Contains('GX RGBA6 copy: 28 decoded pixels, RGB filtering with untouched alpha, four clamp modes and quantized regional clear passed')
    $resultName = if($TrainingPreview){'logs\xenia-training-test.log'}elseif($TrophiesPreview){'logs\xenia-trophies-test.log'}elseif($StagePreview){'logs\xenia-stage-test.log'}elseif($TitlePreview) {'logs\xenia-title-test.log'} elseif($MovieToTitle) {'logs\xenia-movie-to-title-test.log'} elseif($AnimationPreview) {'logs\xenia-animation-test.log'} elseif($CharacterPreview) {'logs\xenia-character-test.log'} elseif($MenuPreview) {'logs\xenia-menu-test.log'} else {'logs\xenia-runtime-test.log'}
    Copy-Item -LiteralPath $runtimeLog -Destination (Join-Path $PSScriptRoot $resultName) -Force
    if (!$passed) { throw "Runtime probes did not complete within $deadline seconds." }
    Write-Output $messages
} finally {
    if($DataPreview -and (Test-Path $dataFlag)){Remove-Item -LiteralPath $dataFlag}
    if($OptionsPreview -and (Test-Path $optionsFlag)){Remove-Item -LiteralPath $optionsFlag}
    if($ArchivePreview -and (Test-Path $archiveFlag)){Remove-Item -LiteralPath $archiveFlag}
    if($SoundPreview -and (Test-Path $effectsFlag)){Remove-Item -LiteralPath $effectsFlag}
    if($SoundPreview -and (Test-Path $soundFlag)){Remove-Item -LiteralPath $soundFlag}
    if($TrainingPreview -and (Test-Path $trainingFlag)){Remove-Item -LiteralPath $trainingFlag}
    if($TrophiesPreview -and (Test-Path $trophyFlag)){Remove-Item -LiteralPath $trophyFlag}
    if($StagePreview -and (Test-Path -LiteralPath $stageFlag)){Remove-Item -LiteralPath $stageFlag}
    if (!$process.HasExited) { Stop-Process -Id $process.Id; $process.WaitForExit(5000) | Out-Null }
    if($TitlePreview -and (Test-Path -LiteralPath $previewFlag)) {Remove-Item -LiteralPath $previewFlag}
    if(Test-Path -LiteralPath $verificationFlag) {Remove-Item -LiteralPath $verificationFlag}
    if($AnimationPreview -and (Test-Path -LiteralPath $animationFlag)){Remove-Item -LiteralPath $animationFlag}
    if($CharacterPreview -and (Test-Path -LiteralPath $characterFlag)){Remove-Item -LiteralPath $characterFlag}
    if($MenuPreview -and (Test-Path -LiteralPath $menuFlag)) {Remove-Item -LiteralPath $menuFlag}
}


