import json
from collections import defaultdict
from pathlib import Path
root=Path(__file__).resolve().parents[1]; logs=root/'logs/gameplay-compile'
names=(logs/'link-missing-symbols.txt').read_text(encoding='utf-8-sig').splitlines()
groups=defaultdict(list)
for name in names:
 if name.startswith(('GX','__GX')): group='GX / renderizador e descritores'
 elif name.startswith(('AX','AI','AR')): group='Audio / DSP / ARAM'
 elif name.startswith('CARD'): group='Memory card'
 elif name.startswith('DVD'): group='DVD / arquivos assincronos'
 elif name.startswith('VI'): group='Video / apresentacao GameCube'
 elif name.startswith(('FIO','MCC')): group='Ferramentas host / comunicacao GameCube'
 elif name.startswith('THP'): group='Video THP original'
 elif name.startswith('HSD'): group='Inicializacao / memoria / render HSD'
 elif name.startswith('PAD'): group='Configuracao PAD GameCube'
 else: group='OS / CPU / cache / depuracao'
 groups[group].append(name)
old=set((logs/'baseline-745-symbols.txt').read_text(encoding='utf-8-sig').splitlines()); new=set(names)
result={'unresolved':len(names),'baseline745StillMissing':len(old & new),'baseline745NoLongerMissing':len(old-new),'newVs745':len(new-old),'groups':{k:{'count':len(v),'symbols':v} for k,v in sorted(groups.items())}}
(logs/'remaining-symbol-groups.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({k:len(v) for k,v in groups.items()},ensure_ascii=False)); print('Baseline:',len(old & new),len(old-new),len(new-old))
