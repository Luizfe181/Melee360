/* Port initialization for logical GObjs. Graphical object destructors are not
 * registered here: JObj/LObj/CObj integration remains a separate boundary. */
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/memory.h>
#include <string.h>
ASSERT_SIZE(HSD_GObj, 0x38);
ASSERT_SIZE(HSD_GObjProc, 0x18);
ASSERT_OFFSET(HSD_GObj, gxlink_prios, 0x20);
static int initialized;
int Melee360GObjRuntimeInit(void)
{
    HSD_GObjLibInitDataType data;
    if(initialized)return 1;
    HSD_GObjSetInitDefaults(&data);
    /* Original gmscene.c match scheduler priority range. */
    data.gproc_pri_max=0x18;
    HSD_GObjInit(&data);
    initialized=1;return 1;
}
static int order[16],count,removed;
static void destroy_probe(void* data) { if(data==&removed)removed++; }
static void callback_early(HSD_GObj* obj) { order[count++]=1; }
static void callback_late(HSD_GObj* obj) { order[count++]=2; }
static void callback_remove(HSD_GObj* obj) { order[count++]=3;HSD_GObjFree(obj); }
int Melee360GObjProbe(void)
{
    HSD_GObj *a,*b,*c;
    u64 paused=0;
    int ok;
    if(!Melee360GObjRuntimeInit())return 0;
    count=removed=0;
    a=GObj_Create(1,0,0);b=GObj_Create(2,1,0);c=GObj_Create(3,2,0);
    if(!a||!b||!c){if(a)HSD_GObjFree(a);if(b)HSD_GObjFree(b);if(c)HSD_GObjFree(c);return 0;}
    HSD_GObj_SetupProc(b,callback_late,1);
    HSD_GObj_SetupProc(a,callback_early,0);
    HSD_GObj_SetupProc(c,callback_remove,2);
    GObj_InitUserData(c,0,destroy_probe,&removed);
    HSD_GObj_RunProcs();
    ok=count==3&&order[0]==1&&order[1]==2&&order[2]==3&&removed==1&&HSD_GObjPLinkHead[2]==0;
    paused=((u64)1)<<1;HSD_GObjLibInitData.unk_2=&paused;
    HSD_GObj_RunProcs();ok=ok&&count==4&&order[3]==1;
    HSD_GObjLibInitData.unk_2=0;
    HSD_GObj_80390C5C(a);HSD_GObj_RunProcs();ok=ok&&count==5&&order[4]==2;
    HSD_GObj_80390C84(a);HSD_GObj_RunProcs();ok=ok&&count==7;
    HSD_GObjFree(a);HSD_GObjFree(b);
    ok=ok&&gobj_alloc_data.used==0&&gobjproc_alloc_data.used==0;
    return ok;
}
