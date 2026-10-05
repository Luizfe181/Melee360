from pathlib import Path
import hashlib,json
p=Path(__file__).resolve().parents[1]
s=p.parents[1]/'work/melee-base/libs/dolphin/src/dolphin/card/CARDStat.c'
t=s.read_text();start=t.index('static void UpdateIconOffsets(CARDDir* ent, CARDStat* stat)\n{');i=t.index('{',start);depth=1;end=i+1
while depth:
    if t[end]=='{':depth+=1
    if t[end]=='}':depth-=1
    end+=1
(p/'compat/generated/card_icons.inc').write_text('/* Unchanged original CARDStat helper. */\n'+t[start:end]+'\n')
(p/'logs/card-icons-provenance.json').write_text(json.dumps({'source':str(s),'sha256':hashlib.sha256(s.read_bytes()).hexdigest(),'function':'UpdateIconOffsets','unchanged':True},indent=2))
