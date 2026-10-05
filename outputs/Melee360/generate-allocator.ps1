$ErrorActionPreference='Stop'
& "$env:USERPROFILE\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe" "$PSScriptRoot\diagnostics\generate_allocator.py"
if($LASTEXITCODE -ne 0){throw 'Allocator generation failed'}
