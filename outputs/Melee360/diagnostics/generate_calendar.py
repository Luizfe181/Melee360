import argparse,hashlib,json,re
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--base',required=True);p.add_argument('--project',required=True);a=p.parse_args()
file=Path(a.base)/'libs/dolphin/src/dolphin/os/OSTime.c';project=Path(a.project);text=file.read_text(encoding='utf-8')
clean=re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"',lambda m:' '*len(m[0]),text,flags=re.S)
out=['/* Original Gregorian calendar conversion; hardware timebase excluded. */','#include <dolphin/os.h>','#include <dolphin/os/OSTime.h>','#include <limits.h>','#define ASSERTLINE(line,condition) do {if(!(condition))__assert(__FILE__,line,#condition);}while(0)']
for name in ('YearDays','LeapYearDays'):out.append(re.search(r'(?ms)^static int '+name+r'\[.*?\};',text).group(0))
manifest=[]
for name in ('IsLeapYear','GetYearDays','GetLeapDays','GetDates','OSTicksToCalendarTime','OSCalendarTimeToTicks'):
 m=re.search(r'(?m)^(?:static\s+)?(?:int|void|OSTime)\s+'+name+r'\s*\([^;{}]*\)\s*\{',clean)
 if not m:raise RuntimeError(name)
 end=m.end();depth=1
 while depth:
  if clean[end]=='{':depth+=1
  elif clean[end]=='}':depth-=1
  end+=1
 body=text[m.start():end];out.append(body);manifest.append({'function':name,'line':text[:m.start()].count('\n')+1,'sourceSha256':hashlib.sha256(file.read_bytes()).hexdigest(),'bodySha256':hashlib.sha256(body.encode()).hexdigest()})
(project/'compat/generated/calendar.c').write_text('\n\n'.join(out)+'\n',encoding='utf-8')
(project/'logs/calendar-provenance.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
print('Extracted six original calendar functions, epoch 2000; RTC boundary separate.')
