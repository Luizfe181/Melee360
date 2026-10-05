"""Compare the same 180-frame CPU fight, with captures disabled, in Xenia."""
from pathlib import Path
import json
import re

project = Path(__file__).resolve().parents[1]
def read(name):
    text = (project / 'logs' / name).read_text(encoding='utf-8-sig')
    profiles = [dict(re.findall(r'(\w+)=([\d.]+)', line)) for line in text.splitlines() if line.startswith('GX profile: frames=')]
    result = next(p for p in profiles if p['frames'] == '180')
    result = {k: float(v) if '.' in v else int(v) for k, v in result.items()}
    result['frame_ms'] = sum(result[k] for k in ('logic_ms', 'render_ms', 'present_ms'))
    result['estimated_fps'] = 1000 / result['frame_ms']
    return result, re.findall(r'^Original CPU: .*$', text, re.M)

baseline, baseline_cpu = read('gx-perf-baseline-controlled.txt')
optimized, optimized_cpu = read('gx-perf-optimized-controlled.txt')
report = {'scenario': 'Mario CPU vs Link CPU, Battlefield, first 180 frames, captures disabled, headless Xenia',
          'timing': 'CPU wall time, including GPU waits; not GPU timestamp queries',
          'baseline': baseline, 'optimized': optimized,
          'cpuSamplesIdentical': baseline_cpu == optimized_cpu,
          'frameTimeReductionPercent': 100 * (1 - optimized['frame_ms'] / baseline['frame_ms']),
          'uploadReductionPercent': 100 * (1 - optimized['uploads'] / baseline['uploads'])}
(project / 'logs/gx-cache-performance-comparison.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
print(json.dumps(report, indent=2))
if not report['cpuSamplesIdentical'] or report['frameTimeReductionPercent'] <= 0:
    raise SystemExit('No verified improvement or CPU behavior changed')
