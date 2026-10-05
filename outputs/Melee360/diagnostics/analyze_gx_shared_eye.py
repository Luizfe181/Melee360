from pathlib import Path
import json
import re

root = Path(__file__).resolve().parents[1] / 'logs/gx-shared-eye'
def read(name):
    text = (root / (name + '.txt')).read_text(encoding='utf-8-sig')
    profiles = [dict(re.findall(r'(\w+)=([\d.]+)', line)) for line in text.splitlines()
                if line.startswith('GX profile: frames=180 ')]
    if len(profiles) != 1:
        raise ValueError(f'{name}: expected one final profile')
    values = {k: float(v) for k, v in profiles[0].items()}
    values['total_ms'] = sum(values[k] for k in ('logic_ms', 'render_ms', 'present_ms'))
    return values, re.findall(r'^Original CPU: .*$', text, re.M)
before, cpu_before = read('baseline-before')
shared, cpu_reuse = read('shared')
after, cpu_after = read('baseline-after')
result = {'scenario': 'Same candidate XEX, Mario/Link CPU, Battlefield, 180 frames, silent headless Xenia',
          'timing': 'CPU wall time including waits; not GPU timestamps or Xbox console FPS',
          'baseline_before': before, 'shared': shared, 'baseline_after': after,
          'cpu_samples_identical': cpu_before == cpu_reuse == cpu_after,
          'draws_identical': before['draws'] == shared['draws'] == after['draws'],
          'upload_reduction_percent': 100 * (1 - shared['uploads'] / before['uploads']),
          'render_reduction_vs_before_percent': 100 * (1 - shared['render_ms'] / before['render_ms']),
          'render_reduction_vs_after_percent': 100 * (1 - shared['render_ms'] / after['render_ms']),
          'baseline_render_drift_percent': 100 * (after['render_ms'] / before['render_ms'] - 1)}
(root / 'analysis.json').write_text(json.dumps(result, indent=2))
print(json.dumps(result, indent=2))
if not result['cpu_samples_identical'] or not result['draws_identical']:
    raise SystemExit('Functional samples/draws changed')
