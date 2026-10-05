from pathlib import Path
import re,json,hashlib
root=Path(__file__).resolve().parents[1];base=root.parents[1]/'work/melee-base/src/sysdolphin/baselib'
plan={
'synth':(['HSD_AudioMalloc','HSD_AudioFree'],['HSD_Synth_804D6018']),
'aobj':(['HSD_AObjInitAllocData','HSD_AObjGetAllocData','_HSD_AObjForgetMemory'],['aobj_alloc_data','endcallback_list']),
'robj':(['HSD_RObjInitAllocData','HSD_RObjGetAllocData','HSD_RvalueObjGetAllocData','_HSD_RObjForgetMemory'],['robj_alloc_data','rvalue_alloc_data','arg_buf','arg_buf_size']),
'mtx':(['HSD_VecInitAllocData','HSD_VecGetAllocData','HSD_MtxInitAllocData','HSD_MtxGetAllocData'],['HSD_Mtx_804C2310','HSD_Mtx_804C233C']),
'shadow':(['HSD_ShadowInitAllocData','HSD_ShadowGetAllocData'],['shadow_alloc_data']),
'tev':(['HSD_RenderInitAllocData','HSD_RenderGetAllocData','HSD_TevRegGetAllocData','HSD_ChanGetAllocData'],['render_alloc_data','tevreg_alloc_data','chan_alloc_data']),
'displayfunc':(['HSD_ZListInitAllocData','_HSD_DispForgetMemory'],['zlist_alloc_data','zlist_top','zlist_bottom','zlist_texedge_top','zlist_texedge_bottom','zlist_texedge_nb','zlist_xlu_top','zlist_xlu_bottom','zlist_xlu_nb'])}
manifest=[]
def qualify(s):return re.sub(r'#include "([^"]+)"',lambda m:'#include <sysdolphin/baselib/'+m.group(1)+'>',s)
for name,(functions,variables) in plan.items():
 original=(base/(name+'.c')).read_text(encoding='utf-8');audit=original
 headers=''.join(line+'\n' for line in original.splitlines() if line.startswith('#include'))
 fragment=qualify(headers)+'\n'
 if name=='displayfunc':fragment+=original[original.index('typedef struct _HSD_ZList'):original.index('HSD_ObjAllocData zlist_alloc_data;')]
 for v in variables:
  m=re.search(r'^(?:static )?[^\n;{}]*\b'+v+r'\s*(?:=[^;]*)?;',original,re.M)
  if not m:raise ValueError(v)
  declaration=m.group(0);fragment+=re.sub(r'^static ','',declaration)+'\n'
  extern='extern '+re.sub(r'^static ','',declaration).split('=')[0].rstrip().rstrip(';')+';'
  audit=audit.replace(declaration,extern,1)
 for f in functions:
  m=re.search(r'^[^\n;{}]*\b'+f+r'\([^;{}]*\)\s*\{',original,re.M);start=m.start();end=original.index('{',start)+1;d=1
  while d:d+=(original[end]=='{')-(original[end]=='}');end+=1
  body=original[start:end];fragment+=body+'\n';audit=audit.replace(body,body[:body.index('{')].rstrip()+';',1)
 (root/'src'/('hsd_pool_'+name+'.c')).write_text(fragment,encoding='utf-8')
 if name=='synth':audit='void Melee360LoadWaitPump(void);\n'+audit.replace('static struct pstHakoHeader_t','__declspec(align(32)) static struct pstHakoHeader_t').replace('static u32 hsd_SynthSFXLoadBuf','__declspec(align(32)) static u32 hsd_SynthSFXLoadBuf').replace('        callback();','        Melee360LoadWaitPump();\n        callback();')
 audit=qualify(audit).replace('static u8 depth_image[] ATTRIBUTE_ALIGN(32)','__declspec(align(32)) static u8 depth_image[]')
 (root/'compat/generated'/('hsd_audit_'+name+'.c')).write_text(audit,encoding='utf-8')
 manifest.append({'source':name+'.c','sha256':hashlib.sha256((base/(name+'.c')).read_bytes()).hexdigest(),'functions':functions,'bodies':'unchanged','state':'original globals shared; static linkage promoted for audit remainder'})
(root/'logs/hsd-runtime-pools-provenance.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')

video=(base/'video.c').read_text(encoding='utf-8')
video=qualify(video).replace('HSD_VIInfo HSD_VIData;','extern HSD_VIInfo HSD_VIData;')
video=video.replace('static u8 garbage[HSD_ANTIALIAS_GARBAGE_SIZE] ATTRIBUTE_ALIGN(32)','__declspec(align(32)) static u8 garbage[HSD_ANTIALIAS_GARBAGE_SIZE]')
(root/'compat/generated/hsd_audit_video.c').write_text(video,encoding='utf-8')

state=(base/'state.c').read_text(encoding='utf-8')
for v in ['state_z_enable','state_z_func','state_z_update','state_color_update','state_alpha_update']:
    state=re.sub(r'^static ([^;\n]*\b'+v+r');',r'extern \1;',state,flags=re.M)
for n in ['HSD_StateSetZMode','HSD_StateSetColorUpdate','HSD_StateSetAlphaUpdate']:
    m=re.search(r'^void '+n+r'\([^;{}]*\)\s*\{',state,re.M);a=m.start();b=state.index('{',a)+1;d=1
    while d:d+=(state[b]=='{')-(state[b]=='}');b+=1
    body=state[a:b];state=state[:a]+body[:body.index('{')].rstrip()+';'+state[b:]
(root/'compat/generated/hsd_audit_state.c').write_text(qualify(state),encoding='utf-8')

runtimeVideo=qualify((base/'video.c').read_text(encoding='utf-8')).replace('static u8 garbage[HSD_ANTIALIAS_GARBAGE_SIZE] ATTRIBUTE_ALIGN(32)','__declspec(align(32)) static u8 garbage[HSD_ANTIALIAS_GARBAGE_SIZE]')
(root/'src/hsd_video_original.c').write_text(runtimeVideo,encoding='utf-8')

# Particle algorithms stay original; physical FIFO writes become native writes.
particles=qualify((base/'psdisp.c').read_text(encoding='utf-8'))
particles=re.sub(r'GXWGFifo\.(u8|f32)\s*=\s*([^;]+);',lambda m:'Melee360GXRawWrite'+('U8' if m[1]=='u8' else 'F32')+'('+m[2]+');',particles)
particles=re.sub(r'(?m)^([^\r\n;{}]+?)\s+ATTRIBUTE_ALIGN\((\d+)\)',r'__declspec(align(\2)) \1',particles)
particles='void Melee360GXRawWriteU8(unsigned char);\nvoid Melee360GXRawWriteF32(float);\n#define GXBegin Melee360ParticleGXBegin\n'+particles
(root/'compat/generated/hsd_audit_psdisp.c').write_text(particles)
(root/'logs/original-particle-render-provenance.json').write_text(json.dumps({'source':str(base/'psdisp.c'),'sha256':hashlib.sha256((base/'psdisp.c').read_bytes()).hexdigest(),'adaptations':['qualify moved includes','XDK prefix alignment syntax','replace physical FIFO scalar writes with native scalar FIFO consumer','native packet completion instead of a GameCube register address'],'particleAlgorithms':'original bodies preserved; no replacement effect model'},indent=2))

archive_base=base.parents[1]/'melee/lb/lbarchive.c'
archive=archive_base.read_text()
archive=re.sub(r'#include "([^"\n]+)"',lambda m:'#include <melee/lb/'+m.group(1)+'>',archive)
m=re.search(r'^void lbArchive_InitializeDAT\([^;{}]*\)\s*\{',archive,re.M)
a=m.start();b=archive.index('{',a)+1;d=1
while d:d+=(archive[b]=='{')-(archive[b]=='}');b+=1
archive=archive[:a]+archive[a:b].split('{',1)[0].rstrip()+';'+archive[b:]
(root/'compat/generated/hsd_audit_lbarchive.c').write_text(archive)

def remove_native_functions(text,names):
 for name in names:
  m=re.search(r'^[^\n;{}]*\b'+re.escape(name)+r'\s*\)?\s*\([^;{}]*\)\s*\{',text,re.M)
  if not m:raise ValueError(name)
  a=m.start();b=text.index('{',a)+1;depth=1
  while depth:depth+=(text[b]=='{')-(text[b]=='}');b+=1
  text=text[:a]+text[a:b].split('{',1)[0].rstrip()+';'+text[b:]
 return text
archive=remove_native_functions(archive,['lbArchive_LoadArchive','lbArchive_LoadSymbols'])
(root/'compat/generated/hsd_audit_lbarchive.c').write_text(archive)
for module,area,functions,variables in [
 ('ifall','if',[],[]),
 ('gmvs','gm',[],[]),
 ('lbarq','lb',[],[]),
 ('lbfile','lb',['lbFileGetFullName','lbFile_8001634C','lbFileGetSize','lbFile_800164A4','lbFile_80016580','lbFile_8001668C'],[]),
 ('player','pl',['Player_80036DD8'],['str_PdPmdat_start_of_data','str_plLoadCommonData','pl_804D6470']),
 ('fighter','ft',['Fighter_LoadCommonData'],['Fighter_804D64FC','gCrowdConfig','Fighter_804D6504','Fighter_804D6508','Fighter_804D650C','Fighter_804D6510','Fighter_804D6514','Fighter_804D6518','Fighter_804D651C','Fighter_804D6520','Fighter_804D6524','Fighter_SmashChargeShakeTable','Fighter_GrabMashShake','Fighter_804D6530','Fighter_804D6534','Fighter_804D6538','Fighter_804D653C','Fighter_804D6540','ftPartsTable','Fighter_804D6548','Fighter_804D654C','Fighter_804D6550','p_ftCommonData'])]:
 text=(base.parents[1]/('melee/'+area+'/'+module+'.c')).read_text()
 text=re.sub(r'#include "([^"\n]+)"',lambda m:'#include <melee/'+area+'/'+m.group(1)+'>',text)
 text=remove_native_functions(text,functions)
 if module=='ifall':
  text='#include <sysdolphin/baselib/debug.h>\n'+text
  for call in ['loadScene(&scene);','ifAll_802F370C(scene);','ifAll_804A0FD8.gobj = createCamera(scene->cameras[0].desc);','createLight(scene);','ifStatus_802F7134();','ifStatus_802F66A4();','ifStock_802FAEC4();','ifTime_Reset();','if_802F7E24();','ifMagnify_802FC870();','un_802FE260();','un_802FD704();','un_802FD4C8();','un_802FF1B4();','un_802FF498();']:
   text=text.replace('    '+call,'    OSReport("Original HUD stage: '+call.split('(')[0]+'\\n");\n    '+call+'\n    OSReport("Original HUD returned: '+call.split('(')[0]+'\\n");')
 if module=='gmvs':
  for call in ['ifAll_802F390C();','lbBgFlash_Init(0xFF);','fn_80171AD4();','Stage_80225074(fn_8016E5C0(arg0));','fn_8016E730(tmp);','ifTime_CreateTimers();','ifStatus_802F665C(tmp->rules.x0_3);']:
   text=text.replace('    '+call,'    OSReport("Original VS stage: '+call.split('(')[0]+'\\n");\n    '+call+'\n    OSReport("Original VS returned: '+call.split('(')[0]+'\\n");')
 if module=='lbarq':
  text='void Melee360ARAMPump(void);\n'+text.replace('    return arg0->state;','    Melee360ARAMPump();\n    return arg0->state;')
 if module=='fighter':
  for call in ['ftData_8008572C(input->internal_id);','Fighter_UnkInitLoad_80068914(gobj, input);','efAsync_LoadSync(ftData_UnkBytePerCharacter[fp->kind]);','ftData_80085820(fp->kind, fp->costume_id);','Fighter_UnkUpdateCostumeJoint_800686E4(gobj);','ftData_80085B10(fp);','ftParts_80074E58(fp);','ftParts_SetupParts(gobj);','ftAnim_80070308(gobj);','ftCo_800C884C(gobj);','Fighter_80068E64(gobj);','ftParts_800749CC(gobj);','ftAnim_8007077C(gobj);','ftCo_8009CF84(fp);','ftAnim_8006FE48(gobj);','Fighter_UnkUpdateVecFromBones_8006876C(fp);','ftCo_8009F578(fp);','Fighter_Create_Inline2(gobj);','ftColl_8007B320(gobj);','Fighter_Spawn(gobj);']:
   text=text.replace('    '+call,'    '+call+'\n    OSReport("Fighter create returned: '+call.split('(')[0]+'\\n");')
   text=text.replace('    '+call,'    OSReport("Fighter create stage: '+call.split('(')[0]+'\\n");\n    '+call)

 if module=='lbfile':
  text=text.replace('    waitForDisc();','    waitForDisc();\n    OSReport("Original lbFile wait completed\\n");')
  text='void Melee360LoadWaitPump(void);\n'+text.replace('lb_800195D0();','Melee360LoadWaitPump();')
  text=text.replace('    *size = lbFileGetSize(basename);','    OSReport("Original loadFile: %s heap=%d\\n", basename, heap_id);\n    *size = lbFileGetSize(basename);',1)
  text=text.replace('    lbFile_80016580(basename, *dst, size, lbFile_8001615C, 0);','    OSReport("Original loadFile allocation: %p bytes=%u\\n", *dst, (unsigned)*size);\n    lbFile_80016580(basename, *dst, size, lbFile_8001615C, 0);')
  text=text.replace('const int FILE_EXTENSION_LENGTH = 4;','enum { FILE_EXTENSION_LENGTH = 4 };').replace('const int MAX_BASENAME_LENGTH = MAX_FILENAME_LENGTH - FILE_EXTENSION_LENGTH;','enum { MAX_BASENAME_LENGTH = MAX_FILENAME_LENGTH - FILE_EXTENSION_LENGTH };')
 for variable in variables:
  m=re.search(r'^[^\n;{}]*\b'+variable+r'\b[^;\n]*;',text,re.M)
  if not m:raise ValueError(variable)
  declaration=m.group(0);extern='extern '+declaration.split('=')[0].rstrip().rstrip(';')+';'
  text=text.replace(declaration,extern,1)
 (root/'compat/generated'/('hsd_audit_'+module+'.c')).write_text(text)
