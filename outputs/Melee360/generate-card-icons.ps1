$ErrorActionPreference='Stop'
& "$env:USERPROFILE\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe" "$PSScriptRoot\diagnostics\generate_card_icons.py"
if($LASTEXITCODE -ne 0){throw 'CARD icon helper generation failed'}
