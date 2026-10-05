from pathlib import Path
import json,re
p=Path(__file__).resolve().parents[1]
def read(name,kind='GX profile:'):
 text=(p/'logs'/name).read_text(encoding='utf-8-sig')
 row=next(l for l in text.splitlines() if l.startswith(kind) and 'frames=180 ' in l)
 v={k:float(x) for k,x in re.findall(r'(\w+)=([\d.]+)',row)}
 return v,re.findall(r'^Original CPU: .*$',text,re.M)
a,ca=read('gx-detail-baseline.txt'); d,cd=read('gx-detail-measured.txt'); b,cb=read('gx-detail-baseline-repeat.txt'); detail,_=read('gx-detail-measured.txt','GX detail:')
for row in (a,b,d):row['frame_ms']=sum(row[k] for k in ('logic_ms','render_ms','present_ms'))
r={'scenario':'180 original CPU frames Mario/Link Battlefield, same XEX, Xenia headless, baseline/detail/baseline', 'baseline':a,'detailRun':d,'baselineRepeat':b,'detail':detail,'cpuSamplesIdentical':ca==cd==cb,'drawCountsIdentical':a['draws']==d['draws']==b['draws'],'detailChangeAgainstBaselinePercent':100*(d['frame_ms']/a['frame_ms']-1),'detailChangeAgainstRepeatPercent':100*(d['frame_ms']/b['frame_ms']-1),'verticesPerFrame':detail['vertices']/180,'drawsPerFrame':d['draws']/180,'scope':'CPU wall time including API blocking. Nested categories; idle covers GX direct/copy, not every subsystem. No GPU timestamp measurement.'}
(p/'logs/gx-detail-analysis.json').write_text(json.dumps(r,indent=2),encoding='utf-8');print(json.dumps(r,indent=2))
if not r['cpuSamplesIdentical'] or not r['drawCountsIdentical']:raise SystemExit('Runtime comparison failed')
