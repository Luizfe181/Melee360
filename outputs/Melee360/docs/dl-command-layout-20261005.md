# Display-list command layout experiment — 2026-10-05

MANTER: original gameplay, AI, physics, HSD, current display-list translation and full preflight. MANTER A TRADUÇÃO: GX calls, arrays, matrices, texture and D3D submission paths. ADAPTAR (experiment only): count enabled matrix-index bytes once per primitive command rather than scan eight descriptors for every vertex. GXSetVtxDesc cannot change these descriptors inside GXBegin; individual matrix IDs remain live and consumed normally.

Opt-in gx-dl-command-layout.flag preserved the original path in the same executable. No transformed-vertex caching, pointer-only display-list caching, safety-check removal or gameplay modification.

Release/Compat build succeeded. Three 180-frame original Mario/Link CPU Battlefield runs, silent Xenia, no concurrent compilation:

| Run | Render ms/frame |
| --- | ---: |
| Reference before | 312.451 |
| Adaptation | 311.751 |
| Reference after | 316.198 |

Apparent reductions: 0.224% and 1.406%. Reference drift: 1.199%. One run per condition; no demonstrated reliable benefit. Timings are CPU wall time including GPU waits, not GPU timestamps or hardware FPS.

All runs reached the final marker without FAILED/HSD ASSERT. Sampled original CPU lines identical; 203241 draws, 1367 uploads and 345 copies in all runs. These checks do not establish complete visual or gameplay equivalence; no new pixel/probe suite performed because this experiment was not promoted.

Decision: do not activate or retain this adaptation in the production source. Restored gx_display_list.inc to its prior path, preserving detailed profiling. Experimental source: diagnostics/experiments/gx-dl-command-layout-unproven.inc. Experimental binary, logs, manifest and analysis: logs/dl-command-layout. Runner points to the preserved experimental binary for reproducibility, not the restored build.

Modified/created files: experimental .inc; diagnostics/run_dl_command_layout.ps1; diagnostics/analyze_dl_command_layout.py; this report; diagnostic logs. No net behavioral change to the runtime source. The published package and scratch XEX stayed at SHA256 95074C0C2CFC7226F2ABE2E88CBB4975411A1A6FD35054DA0FAE079CCE210738; scratch restored, temporary flags cleaned.

Gain claimed: none. Regression observed in sampled behavior: none. Remaining limitation: very small optimization within a much larger vertex-processing path. Next investigate lighting and texgen helpers, using existing sampling and equivalent outputs before considering batching or native buffers. Do not resume changes to original AI/physics merely for speed.