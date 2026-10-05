$ErrorActionPreference='Stop'
& 'C:\Users\luizf\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe' (Join-Path $PSScriptRoot 'diagnostics\generate_portable_mcc.py')
if($LASTEXITCODE){throw 'MCC generation failed'}
