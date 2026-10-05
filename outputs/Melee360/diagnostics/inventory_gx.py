"""GX API coverage from original public headers and actual runtime COFF objects.
Symbol presence proves compilation, never semantic completeness or HSD routing.
"""
import argparse, json, re, subprocess, xml.etree.ElementTree as ET
from pathlib import Path

p = argparse.ArgumentParser()
p.add_argument('--base', required=True)
p.add_argument('--project', required=True)
p.add_argument('--dumpbin', required=True)
a = p.parse_args()
base, project = Path(a.base), Path(a.project)
api, inline, definitions = {}, set(), {}
for header in (base/'libs/dolphin/include/dolphin/gx').glob('*.h'):
    source = re.sub(r'/\*.*?\*/|//[^\n]*', '', header.read_text(), flags=re.S)
    for match in re.finditer(r'\b(GX[A-Za-z0-9_]+)\s*\(', source):
        name = match[1]
        if name.isupper():
            continue
        api.setdefault(name, set()).add(header.name)
    inline.update(re.findall(r'static\s+inline\s+\w+\s+(GX\w+)\s*\(', source))
tree = ET.parse(project/'Melee360.vcxproj')
ns = {'m':'http://schemas.microsoft.com/developer/msbuild/2003'}
for group in tree.findall('m:ItemGroup', ns):
    condition = group.get('Condition', '')
    if condition and 'DecompMode' not in condition:
        continue
    for item in group.findall('m:ClCompile', ns):
        if not item.get('Include'):
            continue
        name = Path(item.get('Include').replace('\\','/')).stem
        obj = project/'build/obj/Release/Compat'/f'{name}.obj'
        if not obj.exists():
            raise RuntimeError(f'Missing runtime object {obj}; build first')
        output = subprocess.check_output([a.dumpbin,'/symbols',str(obj)], text=True, errors='replace')
        for symbol in re.findall(r'SECT\d+[^\n]*\bExternal\s+\|\s+(GX\w+)\b', output):
            definitions.setdefault(symbol, set()).add(obj.name)
records = [{'function':name, 'headers':sorted(headers),
            'status':'inline-original' if name in inline else 'compiled-symbol' if name in definitions else 'missing-runtime-symbol',
            'objects':sorted(definitions.get(name,set())), 'complete':None}
           for name,headers in sorted(api.items())]
report = {'scope':'Original public GX headers vs actual Release/Compat objects',
          'warning':'Compiled symbols may support only subsets. No completion percentage can be inferred.',
          'apiFunctions':len(records), 'compiledSymbols':sum(x['status']=='compiled-symbol' for x in records),
          'inlineFunctions':len(inline), 'missingRuntimeSymbols':sum(x['status']=='missing-runtime-symbol' for x in records),
          'functions':records}
(project/'logs/gx-api-inventory.json').write_text(json.dumps(report, indent=2)+'\n')
lines=['# Inventário público GX', '', report['warning'], '',
       '| API | Estado | Objetos runtime |', '| --- | --- | --- |']
for record in records:
    lines.append(f"| {record['function']} | {record['status']} | {', '.join(record['objects'])} |")
(project/'docs/gx-api-inventory.md').write_text('\n'.join(lines)+'\n')
print(json.dumps({k:v for k,v in report.items() if k!='functions'}, indent=2))
