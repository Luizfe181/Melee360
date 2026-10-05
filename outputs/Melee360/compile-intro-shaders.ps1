$ErrorActionPreference = 'Stop'
$compiler = Join-Path $env:XEDK 'bin\win32\fxc.exe'
foreach ($stage in @('VS','PS')) {
    $profile = if($stage -eq 'VS') {'vs_2_0'} else {'ps_2_0'}
    & $compiler /nologo /T $profile /E $stage /Vn "Melee360Intro$stage" /Fh (Join-Path $PSScriptRoot "src\intro_$stage.h") (Join-Path $PSScriptRoot 'src\intro.hlsl')
    if($LASTEXITCODE -ne 0) { throw "Intro $stage shader compilation failed." }
}
foreach ($stage in @('VS','PS')) {
    $profile = if($stage -eq 'VS') {'vs_2_0'} else {'ps_2_0'}
    & $compiler /nologo /T $profile /E $stage /Vn "Melee360Scene$stage" /Fh (Join-Path $PSScriptRoot "src\scene_$stage.h") (Join-Path $PSScriptRoot 'src\scene.hlsl')
    if($LASTEXITCODE -ne 0) { throw "Scene $stage shader compilation failed." }
}

& $compiler /nologo /T ps_3_0 /E PS /Vn Melee360GXDirectPS /Fh (Join-Path $PSScriptRoot 'src\gx_direct_PS.h') (Join-Path $PSScriptRoot 'src\gx_direct.hlsl')
if($LASTEXITCODE -ne 0) {throw 'GX direct alpha shader compilation failed.'}
& $compiler /nologo /T vs_3_0 /E VS /Vn Melee360GXDirectVS /Fh (Join-Path $PSScriptRoot 'src\gx_direct_VS.h') (Join-Path $PSScriptRoot 'src\gx_direct.hlsl')
if($LASTEXITCODE -ne 0){throw 'GX vertex shader compilation failed.'}
& $compiler /nologo /T ps_3_0 /E PSDepth /Vn Melee360GXDirectDepthPS /Fh (Join-Path $PSScriptRoot 'src\gx_direct_depth_PS.h') (Join-Path $PSScriptRoot 'src\gx_direct.hlsl')
if($LASTEXITCODE -ne 0){throw 'GX Z texture shader compilation failed.'}

& $compiler /nologo /T ps_3_0 /E PSQuantized /Vn Melee360GXDirectQuantizedPS /Fh (Join-Path $PSScriptRoot 'src\gx_direct_quantized_PS.h') (Join-Path $PSScriptRoot 'src\gx_direct.hlsl')
if($LASTEXITCODE -ne 0){throw 'GX quantized depth shader compilation failed.'}

& $compiler /nologo /T ps_3_0 /E PSQuantized /Vn Melee360SceneQuantizedPS /Fh (Join-Path $PSScriptRoot 'src\scene_quantized_PS.h') (Join-Path $PSScriptRoot 'src\scene.hlsl')
if($LASTEXITCODE -ne 0){throw 'Scene quantized depth shader compilation failed.'}
& $compiler /nologo /T ps_3_0 /E PSEarlyDepth /Vn Melee360GXEarlyDepthPS /Fh (Join-Path $PSScriptRoot 'src\gx_early_depth_PS.h') (Join-Path $PSScriptRoot 'src\gx_direct.hlsl')
if($LASTEXITCODE -ne 0){throw 'GX early depth shader compilation failed.'}
