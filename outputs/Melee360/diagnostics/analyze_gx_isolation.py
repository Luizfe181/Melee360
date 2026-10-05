from pathlib import Path
import re,json
p=Path(__file__).resolve().parents[1]
def read(mode):
 t=(p/'logs'/f'gx-isolation-{mode}.txt').read_text(encoding='utf-8-sig')
 def parse(prefix):
  l=next(l for l in t.splitlines() if l.startswith(prefix+' frames=180 '))
  return {k:float(v) for k,v in re.findall(r'(\w+)=([\d.]+)',l)}
 a=parse('GX profile:');a['frame_ms']=sum(a[k] for k in ('logic_ms','render_ms','present_ms'))
 return {'profile':a,'detail':parse('GX detail:')},re.findall(r'^Original CPU: .*$',t,re.M)
results={};cpu=[]
for mode in ('baseline','simple-shader','no-draw','white-textures','no-copy','baseline-repeat'):
 r,c=read(mode);results[mode]=r;cpu.append(c)
a=results['baseline']['profile']['frame_ms'];b=results['baseline-repeat']['profile']['frame_ms']
for mode,r in results.items():
 r['reductionAgainstFirstPercent']=100*(1-r['profile']['frame_ms']/a)
 r['reductionAgainstRepeatPercent']=100*(1-r['profile']['frame_ms']/b)
report={'runs':results,'totalFrames':1080,'cpuSamplesIdentical':all(c==cpu[0] for c in cpu),'submittedPacketCountsIdentical':len({r['profile']['draws'] for r in results.values()})==1,'vertexCountsIdentical':len({r['detail']['vertices'] for r in results.values()})==1,'limits':'Counterfactual diagnostics deliberately alter pictures. No-draw retains GX packet counters but omits DrawPrimitiveUP. No-copy substitutes neutral pixels and also changes cache behavior. Not a valid performance optimization or measured GPU timestamp.'}
(p/'logs/gx-isolation-analysis.json').write_text(json.dumps(report,indent=2),encoding='utf-8');print(json.dumps(report,indent=2))
if not report['cpuSamplesIdentical'] or not report['vertexCountsIdentical']:raise SystemExit('Original runtime changed')
