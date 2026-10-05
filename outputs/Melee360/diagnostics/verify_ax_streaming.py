"""Verify actual AI consumption alongside a full original battle regression."""
import argparse, json, re
from pathlib import Path
p=argparse.ArgumentParser()
p.add_argument('log', type=Path)
p.add_argument('--output', type=Path, required=True)
a=p.parse_args()
text=a.log.read_text(encoding='utf-8-sig')
points=[{'frames':int(f),'samplesPlayed':int(s)} for f,s in re.findall(r'AX native progress: frames=(\d+) samples=(\d+)',text)]
monotonic=bool(points) and all(b['frames']>x['frames'] and b['samplesPlayed']>x['samplesPlayed'] for x,b in zip(points,points[1:]))
# Each 160-sample buffer completion clocks the next frame. Snapshot is
# taken before submitting that next buffer, so one frame is outstanding.
clock_consistent=bool(points) and all(x['samplesPlayed']==160*(x['frames']-1) for x in points)
stopped='AX voice blocked:' in text or 'AX native frame: unsupported' in text or 'AI DMA voice error' in text
battle='Original match render: 900 frames presented' in text and 'Original match: 900 scheduler frames completed' in text
report={'source':str(a.log),'scope':'Xenia original Mario/Link battle; not listening verification or all AX modes',
        'points':points,'monotonicConsumption':monotonic,'dmaFrameClockConsistent':clock_consistent,
        'audioStopped':stopped,'battle900Completed':battle,
        'passed':monotonic and clock_consistent and not stopped and battle and points[-1]['frames']>=1000}
a.output.write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({k:v for k,v in report.items() if k!='points'},indent=2))
raise SystemExit(0 if report['passed'] else 1)
