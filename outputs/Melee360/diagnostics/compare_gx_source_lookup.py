from pathlib import Path
import re,json
project=Path(__file__).resolve().parents[1]
def read(name):
 text=(project/'logs'/name).read_text(encoding='utf-8-sig')
 profiles=[dict(re.findall(r'(\w+)=([\d.]+)',line)) for line in text.splitlines() if line.startswith('GX profile: frames=')]
 row=next(r for r in profiles if r['frames']=='180')
 row={k:float(v) if '.' in v else int(v) for k,v in row.items()}
 row['frame_ms']=sum(row[k] for k in ['logic_ms','render_ms','present_ms'])
 row['estimated_fps']=1000/row['frame_ms']
 return row,re.findall(r'^Original CPU: .*$',text,re.M)
before,cpu=read('gx-source-lookup-baseline.txt')
after,cpu_after=read('gx-source-lookup-optimized.txt')
repeat,cpu_repeat=read('gx-source-lookup-baseline-repeat.txt')
report={'scenario':'Same XEX, 180 original Mario/Link CPU frames, Battlefield, headless Xenia, no captures, A/B/A order',
 'baseline':before,'optimized':after,'baselineRepeat':repeat,'cpuSamplesIdentical':cpu==cpu_after==cpu_repeat,
 'drawCountsIdentical':before['draws']==after['draws']==repeat['draws'],
 'frameTimeReductionPercent':100*(1-after['frame_ms']/before['frame_ms']),
 'frameTimeReductionAgainstRepeatPercent':100*(1-after['frame_ms']/repeat['frame_ms'])}
(project/'logs/gx-source-lookup-comparison.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
print(json.dumps(report,indent=2))
if not report['cpuSamplesIdentical'] or not report['drawCountsIdentical'] or min(report['frameTimeReductionPercent'],report['frameTimeReductionAgainstRepeatPercent'])<=0:
 raise SystemExit('No consistent performance improvement or CPU/draw behavior changed')
