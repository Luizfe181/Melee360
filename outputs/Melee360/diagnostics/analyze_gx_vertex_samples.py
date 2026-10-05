from pathlib import Path
import json,re
p=Path(__file__).resolve().parents[1]
def read(name):
 t=(p/'logs'/name).read_text(encoding='utf-8-sig'); lines=t.splitlines()
 def fields(prefix):
  line=next(l for l in lines if l.startswith(prefix) and 'frames=180 ' in l)
  return {k:float(v) for k,v in re.findall(r'(\w+)=([\d.]+)',line)}
 profile=fields('GX profile:');profile['frame_ms']=sum(profile[k] for k in ('logic_ms','render_ms','present_ms'))
 detail=fields('GX detail:')
 samples={}
 for l in lines:
  if l.startswith('GX vertex sample: frames=180 '):
   kind=re.search(r'kind=(\w+)',l).group(1);samples[kind]={k:float(v) for k,v in re.findall(r'(\w+)=([\d.]+)',l)}
 return {'profile':profile,'detail':detail,'samples':samples},re.findall(r'^Original CPU: .*$',t,re.M)
names=('baseline','phase0','phase31','baseline-repeat')
runs={};cpu=[]
for name in names:
 r,c=read('gx-vertex-'+name+'.txt');runs[name]=r;cpu.append(c)
report={'scenario':'Same XEX, Xenia headless, Mario/Link CPU Battlefield, 180 frames per run, baseline/phase0/phase31/baseline','sampling':'One call in 64; offsets 0 and 31; raw estimates include timer overhead; no statistical confidence interval','runs':runs,'cpuSamplesIdentical':all(c==cpu[0] for c in cpu),'drawCountsIdentical':len({r['profile']['draws'] for r in runs.values()})==1,'estimatedMsRanges':{k:[min(runs[n]['samples'][k]['estimated_ms'] for n in ('phase0','phase31')),max(runs[n]['samples'][k]['estimated_ms'] for n in ('phase0','phase31'))] for k in ('position','lighting','texgen','normal')}}
(p/'logs/gx-vertex-samples-analysis.json').write_text(json.dumps(report,indent=2),encoding='utf-8');print(json.dumps(report,indent=2))
if not report['cpuSamplesIdentical'] or not report['drawCountsIdentical']:raise SystemExit('Runtime behavior changed')
