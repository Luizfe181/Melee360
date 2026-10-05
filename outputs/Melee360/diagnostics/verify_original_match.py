from pathlib import Path
import re,json,sys
root=Path(__file__).resolve().parents[1]
log=Path(sys.argv[1]) if len(sys.argv)>1 else root/'logs/original-match-runtime.log'
text=log.read_text(encoding='utf-8-sig')
pattern=r'Original CPU: frame=(\d+) slot=(\d+) kind=(\d+) ms=(\d+) pos=\(([-\d.]+),([-\d.]+)\) air=(\d+) input=([\da-fA-F]+) enabled=(\d+) damage=([-\d.]+) stocks=(\d+)'
rows=[dict(zip(['frame','slot','kind','state','x','y','air','input','enabled','damage','stocks'],m)) for m in re.findall(pattern,text)]
rendered='Original match render: first original camera passes returned' in text
captures=[{'frame':int(f),'width':int(w),'height':int(h),'nonblack':int(n),'saved':s=='1'} for f,w,h,n,s in re.findall(r'Original render capture: frame=(\d+) size=(\d+)x(\d+) nonblack=(\d+) saved=(\d+)',text)]
report={'source':str(log),'render':'original HSD camera callbacks through native GX' if rendered else 'black background with real-state diagnostic overlay','hardware':'Xenia','sceneEntered':'Original match: scene entered' in text,'scheduler900':'Original match: 900 scheduler frames completed' in text,'renderPresented900':'Original match render: 900 frames presented' in text,'captures':captures,'audioStopped':'AX native frame: unsupported' in text,'fighters':[]}
for slot,kind in [(0,0),(1,6)]:
 samples=[r for r in rows if int(r['slot'])==slot]
 positions={(r['x'],r['y']) for r in samples}
 states={r['state'] for r in samples}
 air={int(r['air']) for r in samples}
 damages=[float(r['damage']) for r in samples]
 result={'slot':slot,'kind':kind,'samples':len(samples),'correctKind':bool(samples) and all(int(r['kind'])==kind for r in samples),'positions':len(positions),'states':len(states),'groundAndAir':air=={0,1},'cpuInputSeen':any(int(r['input'],16)!=0 for r in samples),'maxDamage':max(damages,default=0)}
 result['passed']=result['correctKind'] and len(samples)>=10 and len(positions)>=5 and len(states)>=5 and result['groundAndAir'] and result['cpuInputSeen'] and result['maxDamage']>0
 report['fighters'].append(result)
report['logicPassed']=report['sceneEntered'] and report['scheduler900'] and all(r['passed'] for r in report['fighters']) and 'HSD ASSERT' not in text and 'simulation FAILED' not in text
report['renderRuntimePassed']=rendered and report['renderPresented900'] and report['logicPassed'] and 'presentation FAILED' not in text
(root/'logs/original-match-logic-verification.json').write_text(json.dumps(report,indent=2))
print(json.dumps(report,indent=2))
if not report['renderRuntimePassed']:sys.exit(1)
