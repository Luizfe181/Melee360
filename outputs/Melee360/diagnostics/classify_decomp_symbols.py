"""Classify GALE01 symbol entries by their original linker split, not name guesses."""
from pathlib import Path
from collections import Counter, defaultdict
import bisect
import csv
import json
import re

project = Path(__file__).resolve().parents[1]
base = project.parents[1] / 'work/melee-base'
config = base / 'config/GALE01'
out = project / 'logs/decomp-symbols'
out.mkdir(parents=True, exist_ok=True)
ranges = defaultdict(list)
module = None
for line in (config / 'splits.txt').read_text().splitlines():
    if line and not line[0].isspace() and line.endswith(':'):
        module = line[:-1] if line != 'Sections:' else None
    match = re.match(r'\s*(\S+)\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)', line)
    if match and module:
        section, start, end = match.groups()
        ranges[section].append((int(start, 16), int(end, 16), module))
for entries in ranges.values():
    entries.sort()
    for previous, current in zip(entries, entries[1:]):
        if previous[1] > current[0]:
            raise ValueError(f'Overlapping splits: {previous}, {current}')
starts = {section: [r[0] for r in entries] for section, entries in ranges.items()}

def category(module):
    if module.startswith('melee/mn/'):
        return 'menus'
    if module.startswith('melee/'):
        return 'gameplay'
    if module.startswith('sysdolphin/'):
        return 'HSD'
    if module.startswith('dolphin/'):
        return 'SDK'
    if module.startswith(('MSL/', 'Runtime/', 'MetroTRK/')):
        return 'runtime'
    return 'unassigned'

rows = []
pattern = re.compile(r'^(\S+)\s*=\s*(\S+):0x([0-9A-Fa-f]+);.*?\btype:(function|object|label)\b')
for line_number, line in enumerate((config / 'symbols.txt').read_text().splitlines(), 1):
    match = pattern.match(line)
    if not match:
        continue
    name, section, address, kind = match.groups()
    address_int = int(address, 16)
    candidates = ranges.get(section, [])
    index = bisect.bisect_right(starts.get(section, []), address_int) - 1
    owner = candidates[index][2] if index >= 0 and address_int < candidates[index][1] else ''
    rows.append(dict(name=name, section=section, address=f'0x{address_int:08X}',
                     type=kind, module=owner, category=category(owner), sourceLine=line_number))
fields = ['name', 'section', 'address', 'type', 'module', 'category', 'sourceLine']
for filename, subset in [('all.csv', rows)] + [(c + '.csv', [r for r in rows if r['category'] == c])
        for c in ['gameplay', 'menus', 'HSD', 'SDK', 'runtime', 'unassigned']]:
    with (out / filename).open('w', encoding='utf-8-sig', newline='') as stream:
        writer = csv.DictWriter(stream, fieldnames=fields)
        writer.writeheader()
        writer.writerows(subset)
summary = {}
for c in ['gameplay', 'menus', 'HSD', 'SDK', 'runtime', 'unassigned']:
    subset = [r for r in rows if r['category'] == c]
    summary[c] = {'symbols': len(subset), **dict(Counter(r['type'] for r in subset))}
report = {'version': 'GALE01', 'total': len(rows), 'classification': 'Original section/address ownership from splits.txt',
          'rules': {'gameplay': 'melee/* except mn; includes shared libraries, modes, HUD, effects, trophies, debug and video scenes',
                    'menus': 'melee/mn/* only; related menu logic in gm stays in gameplay',
                    'HSD': 'sysdolphin/*', 'SDK': 'dolphin/*',
                    'runtime': 'MSL/*, Runtime/*, MetroTRK/*',
                    'unassigned': 'No matching half-open split range; no inferred ownership'},
          'categories': summary}
(out / 'summary.json').write_text(json.dumps(report, indent=2), encoding='utf-8')
print(json.dumps(report, indent=2))
