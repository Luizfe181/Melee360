$ErrorActionPreference='Stop'
& "$PSScriptRoot\audit-fighter-create.ps1" -MarioLink -HsdMainHeap *> "$PSScriptRoot\logs\runtime-library-build.txt"
$report=Get-Content "$PSScriptRoot\logs\fighter-create-mario-link-hsd-main-heap-summary.json" -Raw|ConvertFrom-Json
if(!$report.linked -or $report.unresolvedSymbols -or $report.duplicates){throw 'Original runtime library audit failed; inspect runtime-library-build.txt'}
