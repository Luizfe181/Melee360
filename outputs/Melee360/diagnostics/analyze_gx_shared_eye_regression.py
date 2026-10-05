from pathlib import Path
import hashlib
import json
import re
from PIL import Image, ImageChops

root = Path(__file__).resolve().parents[1] / 'logs/gx-shared-eye'
def samples(name):
    text = (root / (name + '.txt')).read_text(encoding='utf-8-sig')
    if 'GX profile: 180 frames presented' not in text:
        raise ValueError('Missing completion: ' + name)
    return re.findall(r'^Original CPU: .*$', text, re.M)
training = (root / 'training-regression.txt').read_text(encoding='utf-8-sig')
result = {'training_and_existing_probes_passed':
          'GX texture expansion: 45 GPU probes' in training and
          'TLUT reload and texture invalidation passed' in training and
          'GX texture copy: 32 GPU copies' in training and
          'Stage select: returned to original CSS' in training and
          'Menu navigation: page=0' in training and
          'FAILED' not in training and 'HSD ASSERT' not in training,
          'capture_cpu_samples_identical': samples('capture-baseline') == samples('capture-reuse'),
          'images': [],
          'limits': ['180-frame match, not 900-frame long combat',
                     'Two internal render captures, not full-frame deterministic comparison',
                     'Not tested on physical Xbox 360']}
for frame in (1, 60):
    name = f'original-match-{frame:04d}.tga'
    before = Image.open(root / ('capture-baseline-' + name)).convert('RGBA')
    source = root / ('capture-reuse-' + name)
    after = Image.open(source).convert('RGBA')
    if before.size != after.size:
        raise ValueError('Capture dimensions changed')
    changed = sum(a != b for a, b in zip(before.getdata(), after.getdata()))
    after.save(root / f'reuse-frame-{frame:04d}.png')
    result['images'].append({'frame': frame, 'size': after.size, 'changed_pixels': changed,
                            'sha256': hashlib.sha256(source.read_bytes()).hexdigest()})
(root / 'regression.json').write_text(json.dumps(result, indent=2))
print(json.dumps(result, indent=2))
if not result['training_and_existing_probes_passed'] or not result['capture_cpu_samples_identical'] or any(x['changed_pixels'] for x in result['images']):
    raise SystemExit('Shared eye transform has not passed regression')
