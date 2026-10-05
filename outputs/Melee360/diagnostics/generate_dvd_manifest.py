import argparse,hashlib,json,struct
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--sys',required=True);p.add_argument('--assets',required=True);p.add_argument('--project',required=True);a=p.parse_args()
root,assets,project=Path(a.sys),Path(a.assets),Path(a.project)
fst=(root/'fst.bin').read_bytes();boot=(root/'boot.bin').read_bytes();count=struct.unpack_from('>I',fst,8)[0]
if boot[:6]!=b'GALE01' or len(fst)<count*12:raise RuntimeError('Unexpected disc/FST')
strings=fst[count*12:];stack=[];entries=[];out=['/* Original FST entry numbers; assets stay untouched. */','typedef struct Melee360DVDEntry {const char* path;const char* file;unsigned int offset,length;int directory;} Melee360DVDEntry;','static const Melee360DVDEntry dvdEntries[] = {']
for i in range(count):
 while stack and i>=stack[-1][1]:stack.pop()
 word,offset,length=struct.unpack_from('>III',fst,i*12);start=word&0xffffff;name=strings[start:strings.index(0,start)].decode('ascii') if i else ''
 path='/'.join([s[0] for s in stack if s[0]]+[name]);directory=word>>24
 file=path
 if directory:stack.append((name,length))
 else:
  if not (assets/file).is_file():file=name
  if not (assets/file).is_file() or (assets/file).stat().st_size!=length:raise RuntimeError('Missing or size mismatch: '+path)
 entry={'entry':i,'path':path,'file':file,'offset':offset,'length':length,'directory':directory};entries.append(entry)
 out.append('{'+json.dumps(path)+','+json.dumps(file)+f',{offset}U,{length}U,{directory}'+'},')
out+=['};','static const unsigned char dvdDiskID[32] = {'+','.join(str(b) for b in boot[:32])+'};']
(project/'compat/generated/dvd_manifest.h').write_text('\n'.join(out)+'\n',encoding='utf-8')
(project/'logs/dvd-manifest-provenance.json').write_text(json.dumps({'fstSha256':hashlib.sha256(fst).hexdigest(),'bootSha256':hashlib.sha256(boot).hexdigest(),'entries':entries},indent=2),encoding='utf-8')
print('Original FST manifest:',count,'entries;',sum(not e['directory'] for e in entries),'verified asset sizes')
