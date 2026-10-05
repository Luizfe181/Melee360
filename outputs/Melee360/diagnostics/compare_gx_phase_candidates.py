from pathlib import Path
import json,re
p=Path(__file__).resolve().parents[1]
def read(name):
 t=(p/'logs'/name).read_text(encoding='utf-8-sig')
 line=next(l for l in t.splitlines() if l.startswith('GX profile: frames=180 '))
 v={k:float(n) for k,n in re.findall(r'(\w+)=([\d.]+)',line)}
 v['frame_ms']=sum(v[k] for k in ('logic_ms','render_ms','present_ms'))
 return v,re.findall(r'^Original CPU: .*$',t,re.M)
a,ca=read('gx-phase-baseline.txt'); repeat,cr=read('gx-phase-baseline-repeat.txt')
report={'baseline':a,'baselineRepeat':repeat,'candidates':{}}
for name in ('active','copy'):
 v,c=read('gx-phase-'+name+'.txt')
 report['candidates'][name]={'profile':v,'cpuIdentical':c==ca==cr,'drawsIdentical':v['draws']==a['draws']==repeat['draws'],'reductionPercent':100*(1-v['frame_ms']/a['frame_ms']),'reductionAgainstRepeatPercent':100*(1-v['frame_ms']/repeat['frame_ms'])}
if (p/'logs/gx-snapshots-baseline-repeat.txt').exists():
 a,ca=read('gx-snapshots-baseline.txt'); v,c=read('gx-snapshots-optimized.txt'); repeat,cr=read('gx-snapshots-baseline-repeat.txt')
 report['snapshots']={'baseline':a,'optimized':v,'baselineRepeat':repeat,'cpuIdentical':c==ca==cr,'drawsIdentical':v['draws']==a['draws']==repeat['draws'],'reductionPercent':100*(1-v['frame_ms']/a['frame_ms']),'reductionAgainstRepeatPercent':100*(1-v['frame_ms']/repeat['frame_ms'])}
(p/'logs/gx-phase-candidates-comparison.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
print(json.dumps(report,indent=2))
