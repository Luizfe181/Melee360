from pathlib import Path
import re,json,hashlib
root=Path(__file__).resolve().parents[1];base=root.parents[1]/'work/melee-base'
def extract(s,name):
 m=re.search(r'^[^\n;{}]*\b'+re.escape(name)+r'\s*\)?\s*\([^;{}]*\)\s*\{',s,re.M)
 if not m:raise ValueError(name)
 a=m.start();b=s.index('{',a)+1;d=1
 while d:d+=(s[b]=='{')-(s[b]=='}');b+=1
 return s[a:b]
file=(base/'src/melee/lb/lbfile.c').read_text();prefix='''#include "../compat/gameplay_boundary.h"
#include <melee/lb/lbfile.h>
#include <dolphin/ar.h>
#include <dolphin/dvd.h>
#include <sysdolphin/baselib/devcom.h>
#include <sysdolphin/baselib/debug.h>
#include <string.h>
#include <stdio.h>
void Melee360DVDPump(void);void Melee360ARAMPump(void);
static bool cancel;
void Melee360LoadWaitPump(void){Melee360DVDPump();Melee360ARAMPump();}
/* Native filesystem name boundary: exact filenames or manifest-backed .usd/.dat. */
char* lbFileGetFullName(const char* basename){static char name[32];size_t length;HSD_ASSERT(0,basename);length=strlen(basename);HSD_ASSERT(0,length<sizeof(name)-5);strcpy(name,basename);if(!strchr(name,'.')){strcat(name,".usd");if(DVDConvertPathToEntrynum(name)<0){strcpy(name,basename);strcat(name,".dat");}}return name;}
'''
functions=['lbFile_8001615C','discIsDone','waitForDisc','lbFile_8001634C','lbFileGetSize','lbFile_800164A4','lbFile_80016580','lbFile_8001668C']
bodies='\n'.join(extract(file,n) for n in functions)
bodies=bodies.replace('lb_800195D0();','Melee360LoadWaitPump();').replace('(dst >= 0x80000000) ? 0x21 : 0x23','(dst >= ARGetSize()) ? 0x21 : 0x23')
bodies=bodies.replace('    cancel = false;', '    OSReport(\"lbFile native wait: %s\\n\", basename);\n    cancel = false;')
(root/'src/original_file_load.c').write_text(prefix+bodies+'\n')
archive=(base/'src/melee/lb/lbarchive.c').read_text();prefix='''#include "../compat/gameplay_boundary.h"
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbfile.h>
#include <melee/lb/lbheap.h>
#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/debug.h>
#include <stdarg.h>
'''
functions=['readArchive','loadArchive','lbArchive_LoadArchive','vLoadSectionsFatal','lbArchive_LoadSymbols']
(root/'src/original_archive_load.c').write_text(prefix+'\n'.join(extract(archive,n) for n in functions)+'\n')
player=(base/'src/melee/pl/player.c').read_text();fighter=(base/'src/melee/ft/fighter.c').read_text();prefix='''#include "../compat/gameplay_boundary.h"
#include <melee/pl/player.h>
#include <melee/pl/types.h>
#include <melee/ft/fighter.h>
#include <melee/ft/types.h>
#include <melee/lb/lbarchive.h>
#include <sysdolphin/baselib/archive.h>
#include <math.h>
#include <sysdolphin/baselib/debug.h>
char str_PdPmdat_start_of_data[] = "PdPm.dat";
char str_plLoadCommonData[] = "plLoadCommonData";
pl_804D6470_t* pl_804D6470;
'''
start=fighter.index('struct Fighter_804D64FC_t* Fighter_804D64FC');end=fighter.index('void Fighter_800679B0',start)
(root/'src/original_common_boot.c').write_text(prefix+fighter[start:end]+extract(player,'Player_80036DD8')+'\n'+extract(fighter,'Fighter_LoadCommonData')+'''
int Melee360OriginalCommonBoot(void){Player_80036DD8();Fighter_LoadCommonData();return pl_804D6470&&p_ftCommonData&&ftPartsTable&&_finite(p_ftCommonData->x260_startShieldHealth)&&p_ftCommonData->x260_startShieldHealth>0;}
''')
(root/'logs/original-load-provenance.json').write_text(json.dumps({'sourceHashes':{n:hashlib.sha256((base/n).read_bytes()).hexdigest() for n in ['src/melee/lb/lbfile.c','src/melee/lb/lbarchive.c','src/melee/pl/player.c','src/melee/ft/fighter.c']},'adaptations':['lbFile wait tick pumps native DVD/ARAM on the owner thread','lbFile RAM/ARAM selection uses actual ARGetSize','filename expansion checks the real manifest, US extension first'],'archiveAndCommonBodies':'unchanged'},indent=2))
