from pathlib import Path
import json,re
p=Path(__file__).resolve().parents[1]
def read(mode):
 t=(p/'logs'/f'gx-copy-candidate-{mode}.txt').read_text(encoding='utf-8-sig')
 def parse(prefix):
  l=next(l for l in t.splitlines() if l.startswith(prefix+' frames=180 '))
  return {k:float(v) for k,v in re.findall(r'(\w+)=([\d.]+)',l)}
 v=parse('GX profile:');d=parse('GX detail:');v['frame_ms']=sum(v[k] for k in ('logic_ms','render_ms','present_ms'));v['copyWithoutMeasuredIdle_ms']=v['copy_ms']-d['idle_ms']
 return {'profile':v,'detail':d},re.findall(r'^Original CPU: .*$',t,re.M)
runs={};cpu=[]
for mode in ('baseline','region','pool','both','baseline-repeat'):
 r,c=read(mode);runs[mode]=r;cpu.append(c)
report={'scenario':'Same XEX, five 180-frame original CPU match runs in Xenia headless','runs':runs,'cpuSamplesIdentical':all(c==cpu[0] for c in cpu),'drawCountsIdentical':len({r['profile']['draws'] for r in runs.values()})==1,'idleCallsMatchCopies':all(r['detail']['idle_calls']==r['profile']['copies'] for r in runs.values()),'shadowUntileBytesBefore':640*480*4,'shadowUntileBytesAfter':256*257*4,'limits':'Nested CPU wall timers; copy minus measured idle is an approximation to non-idle copy work, not GPU execution time. Total FPS improvement is not established against both references.'}
(p/'logs/gx-copy-candidates-analysis.json').write_text(json.dumps(report,indent=2),encoding='utf-8');print(json.dumps(report,indent=2))
if not report['cpuSamplesIdentical'] or not report['drawCountsIdentical']:raise SystemExit('Runtime changed')
