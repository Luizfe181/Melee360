"""Preserve original TEV convenience functions, backed by native state setters."""
import argparse
import hashlib
import json
import re
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument('--base', required=True)
parser.add_argument('--project', required=True)
args = parser.parse_args()
base, project = Path(args.base), Path(args.project)
manifest = []
groups = {
    'GXTev.c': ('gx_tev_original_op.inc', ['GXSetTevOp', 'GXSetTevClampMode']),
    'GXBump.c': ('gx_tev_original_helpers.inc', [
        'GXSetTevIndWarp', 'GXSetTevIndTile', 'GXSetTevIndBumpST',
        'GXSetTevIndBumpXYZ', 'GXSetTevIndRepeat']),
}
for filename, (output, names) in groups.items():
    source = base / 'libs/dolphin/src/dolphin/gx' / filename
    text = source.read_text(encoding='utf-8')
    bodies = ['/* Original SDK convenience functions; shader-backed dependencies. */',
              '#define CHECK_GXBEGIN(line,name) require(!__GXinBegin)',
              '#define ASSERTMSGLINE(line,condition,message) do { if(!(condition)) __assert(__FILE__,line,message); } while(0)']
    for name in names:
        match = re.search(r'(?ms)^void ' + name + r'\(.*?^\}', text)
        if not match:
            raise RuntimeError('Missing original function: ' + name)
        original = match.group()
        body = original.replace('GXSetTevIndirect(tev_stage + 1,',
                                'GXSetTevIndirect((GXTevStageID)(tev_stage + 1),')
        body = body.replace('GXSetTevIndirect(tev_stage + 2,',
                            'GXSetTevIndirect((GXTevStageID)(tev_stage + 2),')
        body = re.sub(r',\s*0\);', ', GX_ITBA_OFF);', body)
        if name == 'GXSetTevClampMode':
            # The original release SDK emits no register writes for this
            # obsolete API. Only its debug build deliberately panics.
            bodies.append('#if defined(MELEE360_RETAIL)\n#undef ASSERTMSGLINE\n#define ASSERTMSGLINE(line,condition,message) ((void)0)\n#endif')
        bodies.append(body)
        manifest.append({
            'function': name, 'source': str(source),
            'line': text[:match.start()].count('\n') + 1,
            'fileSha256': hashlib.sha256(source.read_bytes()).hexdigest(),
            'originalBodySha256': hashlib.sha256(original.encode()).hexdigest(),
            'generatedBodySha256': hashlib.sha256(body.encode()).hexdigest(),
            'adaptations': ['native assertion macros outside body'] +
                          (['original release SDK assertion semantics for obsolete hardware API; no invented clamp operation'] if name == 'GXSetTevClampMode' else []) +
                          (['C++ stage enum casts and named alpha-off enum'] if body != original else []),
        })
    bodies.extend(['#undef CHECK_GXBEGIN', '#undef ASSERTMSGLINE'])
    (project / 'src' / output).write_text('\n\n'.join(bodies) + '\n', encoding='utf-8')
(project / 'logs/original-tev-provenance.json').write_text(
    json.dumps(manifest, indent=2) + '\n', encoding='utf-8')
print(f'Preserved {len(manifest)} original TEV convenience functions.')
