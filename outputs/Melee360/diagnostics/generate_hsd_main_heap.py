from pathlib import Path
import re, hashlib, json
project=Path(__file__).resolve().parents[1]
source=project.parents[1]/'work/melee-base/src/sysdolphin/baselib/initialize.c'
s=source.read_text(encoding='utf-8')
def extract(name):
    matches=list(re.finditer(r'^(?:static )?(?:void|OSHeapHandle|HSD_RenderPass) '+name+r'\([^;{]*\)\s*\{',s,re.M))
    if len(matches)!=1: raise ValueError(name)
    start=matches[0].start(); end=s.index('{',start)+1; depth=1
    while depth:
        depth+=(s[end]=='{')-(s[end]=='}');end+=1
    return s[start:end]
headers=s[:s.index('static void HSD_DVDInit(void);')]
headers=re.sub(r'#include "([^"]+)"',lambda m: '#include <sysdolphin/baselib/'+m.group(1)+'>',headers)
text='/* Link-only original heap lifecycle; never compiled into the runnable XEX. */\n'+headers
text+='\nstatic void* hsd_heap_next_arena_lo;\nstatic void* hsd_heap_next_arena_hi;\nstatic volatile OSHeapHandle current_heap=-1;\nstatic void HSD_ObjInit(void);\nstatic HSD_RenderPass current_render_pass;\nstatic int current_pix_fmt;\nstatic int current_z_fmt=GX_ZC_MID;\n'
names=['HSD_GetCurrentRenderPass','HSD_StartRender']
for name in names: text+=extract(name)+'\n'
(project/'compat/generated/original_hsd_main_heap.c').write_text(text,encoding='utf-8')
(project/'logs/hsd-main-heap-provenance.json').write_text(json.dumps({'source':str(source),'sha256':hashlib.sha256(source.read_bytes()).hexdigest(),'functions':names,'bodies':'unchanged','adaptations':['qualify relative baselib include paths after relocation'],'scope':'compile/link audit only; private state not initialized for execution'},indent=2))
print('Generated unchanged HSD heap lifecycle bodies')
