import argparse, hashlib, json, re
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--base',required=True);p.add_argument('--project',required=True);a=p.parse_args();base=Path(a.base);project=Path(a.project)
source=base/'src/melee/mn/mncharsel.c';s=source.read_text();clean=re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"',lambda m:' '*len(m[0]),s,flags=re.S);manifest=[]
def record(name,start,end):
 text=s[start:end];manifest.append({'name':name,'line':s[:start].count('\n')+1,'sha256':hashlib.sha256(text.encode()).hexdigest()});return text
def block(marker):
 start=s.index(marker);brace=clean.index('{',start);end=brace+1;depth=1
 while depth:
  if clean[end]=='{':depth+=1
  elif clean[end]=='}':depth-=1
  end+=1
 return start,end
out=['/* Generated original CSS excerpts, not the complete CursorThink/scene. */']
for line in s.splitlines():
 if line.startswith('#define ICONROW') or line.startswith('#define ICONBNDS'):out.append(line)
for marker in ('struct CSSCursorData {','static CSSIcon icons[25 + 1] =','static inline f32 loadStickValue(','static inline void getStickDelta(','static inline s32 getIconOffset(','static inline s32 getPlayerForDoor('):
 start,end=block(marker);text=record(marker,start,end)
 if marker.startswith('struct '):text+=';'
 elif marker.startswith('static CSSIcon'):text+=';'
 out.append(text)
start,end=block('static struct CSSCharModel {');out.append(record('CSSCharModel',start,end).replace('static struct','struct',1)+';')
start=s.index('        cursor->xC = (f32) ((0.0002f * dx)');end=s.index('\n\n',start)
move=record('CursorThink movement',start,end)
start=s.index('                if (25.0f < cursor->x10)');_,end=block('                if (-35.0f > cursor->xC)');clamp=record('CursorThink bounds',start,end)
out.append('static void originalMove(struct CSSCursorData* cursor,f32 dx,f32 dy){\n'+move+'\n'+clamp+'\n}')
start=s.index('if (m2->x8 > icons[i].bound_l');end=s.index('{',start);condition=record('CursorThink icon bounds',start,end)
out.append('static int originalHit(struct CSSCharModel* m2){int i;for(i=0;i<0x19;++i){'+condition+'return i;}return -1;}')
start=s.index('            model->x8 = 2.7f + mnCharSel_804A0BC0');end=s.index('\n',s.index('model->xC = -2.0f',start));follow=record('Token follows hand',start,end)
out.append('static void originalFollow(struct CSSCharModel* model){u8 status=model->x5;'+follow+'}')
marker='    {\n        f32 dx;\n        f32 tx;\n        f32 dy;';start,end=block(marker);smooth=record('Token interpolation',start,end)
out.append('static void originalSmooth(struct CSSCharModel* model)'+smooth)
start=s.index('                                            s32 player_idx;',s.index('void mnCharSel_CursorThink'))
end=s.index(';',s.index('.char_kind',start))+1;confirm=record('CursorThink player/character assignment',start,end)
out.append('static void originalStoreCharacter(int door){'+confirm+'}')
start=s.index('        mnCharSel_804A0BD0[door]->x8 = 3.4f + icons[icon_idx].bound_l;',s.index('s32 mnCharSel_8025FDEC'))
end=s.index('\n\n',start);position=record('Token icon position',start,end)
out.append('static void originalPlaceToken(int door,int icon_idx){'+position+'}')
dest=project/'compat/generated/original_css.inc';dest.write_text('\n\n'.join(out)+'\n')
(project/'logs/original-css-provenance.json').write_text(json.dumps({'source':str(source),'sourceSha256':hashlib.sha256(source.read_bytes()).hexdigest(),'scope':'Unchanged excerpts; helper wrappers/platform aliases separate; complete scene not integrated','excerpts':manifest},indent=2))
print('Generated',len(manifest),'original CSS excerpts.')
