#include <sysdolphin/baselib/list.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/memory.h>
#include <dolphin/os/OSAlloc.h>
#include <sysdolphin/baselib/id.h>
#include <sysdolphin/baselib/object.h>

int Melee360HsdProbe(void)
{
    HSD_SList* head;
    HSD_SList* second;
    HSD_SList* recycled;
    HSD_ObjAllocData* stats;
    HSD_ObjAllocData limited;
    int values[2] = {17, 29};
    int ok;
    static __declspec(align(32)) unsigned int pool[16];
    void* one;
    long initialFree;
    void* large;
    HSD_Obj* object;
    s32 found;
    initialFree = OSCheckHeap(HSD_GetHeap());
    large = HSD_MemAlloc(1024 * 1024);
    if (!large || ((uintptr_t)large & 31) || OSCheckHeap(0) >= initialFree) return 0;
    HSD_Free(large);
    if (OSCheckHeap(0) != initialFree || HSD_MemAlloc(-1) || HSD_MemAlloc(64 * 1024 * 1024)) return 0;
    *HSD_RandSeedPtr = 1;
    if (HSD_Rand() != 41 || HSD_Rand() != 51235) return 0;
    HSD_ObjSetHeap(0, NULL);
    HSD_ListInitAllocData();
    head = HSD_SListAllocAndPrepend(NULL, &values[0]);
    second = HSD_SListAllocAndAppend(head, &values[1]);
    stats = HSD_SListGetAllocData();
    ok = second == head && head->next != NULL &&
        head->data == &values[0] && head->next->data == &values[1] &&
        head->next->next == NULL && stats->used == 2 && stats->peak == 2;
    second = head->next;
    head = HSD_SListRemove(head);
    ok = ok && head == second && stats->used == 1;
    head = HSD_SListRemove(head);
    ok = ok && head == NULL && stats->used == 0 && stats->free == 2;
    recycled = HSD_SListAlloc();
    ok = ok && recycled == second && recycled->next == NULL && recycled->data == NULL;
    HSD_SListRemove(recycled);
    // Exercise original fixed-pool alignment/exhaustion and number limits.
    HSD_ObjSetHeap(sizeof(pool), pool);
    HSD_ObjAllocInit(&limited, 12, 16);
    HSD_ObjAllocSetNumLimit(&limited, 1);
    HSD_ObjAllocEnableNumLimit(&limited);
    one = HSD_ObjAlloc(&limited);
    ok = ok && one != NULL && ((uintptr_t)one & 15) == 0 && HSD_ObjAlloc(&limited) == NULL;
    if (one) HSD_ObjFree(&limited, one);
    HSD_ObjAllocDisableNumLimit(&limited);
    while ((one = HSD_ObjAlloc(&limited)) != NULL) { }
    ok = ok && limited.used == 4;
    // Remove stack allocator registration before its storage expires.
    _HSD_ObjAllocForgetMemory(NULL, NULL);
    HSD_ObjSetHeap(0, NULL);
    HSD_ListInitAllocData();
    HSD_IDInitAllocData();
    HSD_IDSetup();
    HSD_IDInsertToTable(NULL, 1, &values[0]);
    HSD_IDInsertToTable(NULL, 102, &values[1]);
    ok = ok && HSD_IDGetData(1, &found) == &values[0] && found == 1;
    HSD_IDRemoveByIDFromTable(NULL, 1);
    ok = ok && HSD_IDGetData(1, &found) == NULL && found == 0 && HSD_IDGetData(102, NULL) == &values[1];
    HSD_IDRemoveByIDFromTable(NULL, 102);
    object = hsdNew(&hsdObj);
    ok = ok && object != NULL && hsdObj.head.nb_exist == 1 && hsdObjIsDescendantOf(object, &hsdClass);
    hsdDelete(object);
    ok = ok && hsdObj.head.nb_exist == 0;
    return ok;
}
