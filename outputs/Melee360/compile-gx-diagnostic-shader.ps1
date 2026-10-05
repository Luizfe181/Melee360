$ErrorActionPreference='Stop'
if(!$env:XEDK){throw 'Configure XEDK'}
& (Join-Path $env:XEDK 'bin/win32/fxc.exe') /nologo /T ps_3_0 /E PSDiagnostic /Vn Melee360GXDiagSimplePS /Fh (Join-Path $PSScriptRoot 'src/gx_diag_simple_PS.h') (Join-Path $PSScriptRoot 'src/gx_diag_simple.hlsl')
if($LASTEXITCODE){throw 'Diagnostic shader compilation failed'}
