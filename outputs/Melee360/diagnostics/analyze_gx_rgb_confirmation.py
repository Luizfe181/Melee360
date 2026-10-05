from pathlib import Path
import re,json,statistics
p=Path(__file__).resolve().parents[1]
def read(i,mode):
 t=(p/'logs'/f'gx-rgb-confirm-{i}-{mode}.txt').read_text(encoding='utf-8-sig')
 l=next(l for l in t.splitlines() if l.startswith('GX profile: frames=180 '))
 v={k:float(x) for k,x in re.findall(r'(\w+)=([\d.]+)',l)}
 v['frame_ms']=sum(v[k] for k in ('logic_ms','render_ms','present_ms'))
 return v,re.findall(r'^Original CPU: .*$',t,re.M)
rows=[];cpu=[]
for i in range(1,4):
 a,ca=read(i,'base');b,cb=read(i,'rgb');cpu.extend([ca,cb]);rows.append({'pair':i,'baseline':a,'candidate':b,'reductionPercent':100*(1-b['frame_ms']/a['frame_ms']),'drawCountsIdentical':a['draws']==b['draws']})
r={'pairs':rows,'totalFrames':1080,'allPairsImproved':all(v['reductionPercent']>0 for v in rows),'cpuSamplesIdentical':all(c==cpu[0] for c in cpu),'drawCountsIdentical':all(v['drawCountsIdentical'] for v in rows),'meanPairedReductionPercent':statistics.mean(v['reductionPercent'] for v in rows),'medianPairedReductionPercent':statistics.median(v['reductionPercent'] for v in rows),'aggregateFrameTimeReductionPercent':100*(1-sum(v['candidate']['frame_ms'] for v in rows)/sum(v['baseline']['frame_ms'] for v in rows)),'limit':'Three pairs, fixed A/B order, no statistical confidence interval or console benchmark. Smallest gain may be within host variation.'}
(p/'logs/gx-rgb-confirm-analysis.json').write_text(json.dumps(r,indent=2),encoding='utf-8');print(json.dumps(r,indent=2))
if not r['cpuSamplesIdentical'] or not r['drawCountsIdentical']:raise SystemExit('Runtime changed')
