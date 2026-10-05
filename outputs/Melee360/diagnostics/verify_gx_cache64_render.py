from pathlib import Path
from PIL import Image, ImageChops
import hashlib
import json
import re

project = Path(__file__).resolve().parents[1]
workspace = project.parents[1]
logs = project / 'logs'
original = (logs / 'render-final-match-verification.txt').read_text(encoding='utf-8-sig')
current = (logs / 'original-match-runtime.log').read_text(encoding='utf-8-sig')
samples = lambda text: re.findall(r'^Original CPU: .*$', text, re.M)
logic = json.loads((logs / 'original-match-logic-verification.json').read_text())
report = {'cpu900SamplesIdentical': samples(original) == samples(current),
          'renderRuntimePassed': logic['renderRuntimePassed'], 'captures': []}
for capture in logic['captures']:
    identifier = capture['frame']
    name = f'original-match-{identifier:04d}.tga'
    before = Image.open(workspace / 'work/gx-cache64-baseline-captures' / name).convert('RGB')
    source = workspace / 'work/xenia-test/package' / name
    after = Image.open(source).convert('RGB')
    output = logs / f'gx-cache64-{name[:-4]}.png'
    after.save(output)
    diff = ImageChops.difference(before, after)
    report['captures'].append({'identifier': identifier, 'size': after.size,
        'nonblack': capture['nonblack'], 'saved': capture['saved'],
        'changedPixels': sum(pixel != (0, 0, 0) for pixel in diff.getdata()),
        'image': str(output), 'sha256': hashlib.sha256(source.read_bytes()).hexdigest()})
(logs / 'gx-cache64-render-verification.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
print(json.dumps(report, indent=2))
if not report['cpu900SamplesIdentical'] or not report['renderRuntimePassed'] or len(report['captures']) != 7:
    raise SystemExit('Cache runtime verification failed')

if any(c['changedPixels'] for c in report['captures']):
    raise SystemExit('Capture pixels changed; inspect before publishing')

