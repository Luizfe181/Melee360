from pathlib import Path
import re,json,csv,collections
# Regenera os inventarios lexicais; nao substitui analise semantica das paginas.
base=Path(__file__).resolve().parents[3]/'work'/'melee-base'
out=Path(__file__).resolve().parents[1]/'docs'/'decomp'
rows=[];functions=[]
for p in sorted(base.rglob('*')):
 if p.suffix.lower() not in ('.c','.h','.s','.cpp') or '.git' in p.parts:continue
 rel=p.relative_to(base).as_posix();parts=rel.split('/');text=p.read_text(errors='replace');definitions=re.findall(r'^([A-Za-z_][\w\s*]*?)\b([A-Za-z_]\w*)\s*\([^;{}]*\)\s*\{',text,re.M)
 row={'path':rel,'area':'/'.join(parts[:3]) if rel.startswith('src/melee/') else '/'.join(parts[:2]),'bytes':p.stat().st_size,'lines':len(text.splitlines()),'includes':re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)',text,re.M),'functionsHeuristic':[n for _,n in definitions],'asmMarkers':len(re.findall(r'\basm\b|__asm',text)),'nonmatchingMarkers':len(re.findall(r'NON_MATCHING|NOT_IMPLEMENTED|INCLUDE_ASM',text))};rows.append(row)
 functions.extend({'function':name,'path':rel} for _,name in definitions)
(out/'source-inventory.json').write_text(json.dumps(rows,indent=2),encoding='utf8');(out/'function-index.json').write_text(json.dumps(functions,indent=2),encoding='utf8')
with (out/'source-inventory.csv').open('w',newline='',encoding='utf-8-sig') as f:
 w=csv.DictWriter(f,fieldnames=['path','area','bytes','lines','asmMarkers','nonmatchingMarkers']);w.writeheader();w.writerows({k:r[k] for k in w.fieldnames} for r in rows)
print(f'{len(rows)} arquivos, {sum(r["lines"] for r in rows)} linhas, {len(functions)} definicoes aparentes')
