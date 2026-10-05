from pathlib import Path
import hashlib
root=Path(__file__).resolve().parents[3];base=root/'work/melee-base/src/melee';out=Path(__file__).resolve().parents[1]/'compat/generated'
def block(text, marker):
 start=text.index(marker);i=text.index('{',start);d=1;j=i+1
 while d:
  d+=(text[j]=='{')-(text[j]=='}');j+=1
 return text[start:j]
s=(base/'mn/mnstagesel.c').read_text(encoding='utf-8');table=s[s.index('static struct StageListInfo'):s.index('ASSERT_SIZE(mnStageSel_803F06D0')].strip();table=table.replace('HSD_JObj*','void*').replace('u8 ','unsigned char ').replace('f32 ','float ')
text='/* Generated from unchanged mnstagesel.c SHA256 '+hashlib.sha256((base/'mn/mnstagesel.c').read_bytes()).hexdigest()+' */\n'+table+';\n'+block(s,'int mnStageSel_8025BC08(')+'\n'+block(s,'void fn_8025A310(')+'\n'
(out/'original_stage_select.inc').write_text(text)
blocks=[]
for path,markers in [('gm/gm_1601.c',['void gm_SetupPlayerDefaults(','void gm_SetupAllPlayerDefaults(','void gm_SetupRulesDefaults(']),('gm/gm_1B03.c',['void gm_801B05F4(','void gm_SetupHumanPlayer(','void gm_SetupCpuPlayer(']),('gm/gm_1884.c',['void gm_80189CDC('])]:
 src=(base/path).read_text(encoding='utf-8');blocks.append('/* '+path+' SHA256 '+hashlib.sha256((base/path).read_bytes()).hexdigest()+' */\n');blocks += [block(src,m)+'\n' for m in markers]
(out/'original_training_rules.inc').write_text(''.join(blocks))
