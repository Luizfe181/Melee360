/* Original AX CPU control. DSP execution is deliberately not emulated here. */

#include <dolphin/ax.h>

#include <dolphin/os.h>

#include <string.h>

#include <sysdolphin/baselib/debug.h>

#define ASSERTLINE(line,c) HSD_ASSERTREPORT(line,c,"AX argument validation")

#define ASSERTMSGLINE(line,c,msg) HSD_ASSERTREPORT(line,c,msg)

void __AXRemoveFromStack(AXVPB*);
void __AXPushFreeStack(AXVPB*);
AXVPB* __AXPopCallbackStack(void);
void __AXSetPBDefault(AXVPB*);

static u16 __AXHRTFHistory[128];

u32 __AXClMode;

void AXSetMode(u32 mode)
{
    if (__AXClMode != mode) {
        if (mode == 1) {
            memset(&__AXHRTFHistory, 0, 0x100);
        }
        __AXClMode = mode;
    }
}

u32 AXGetMode(void)
{
    return __AXClMode;
}

static AXVPB* __AXStackHead[AX_PRIORITY_STACKS];
static AXVPB* __AXStackTail[AX_PRIORITY_STACKS];

static AXVPB* __AXCallbackStack;

AXVPB* __AXGetStackHead(u32 priority)
{
    ASSERTLINE(0x3D, priority < AX_PRIORITY_STACKS);
    return __AXStackHead[priority];
}

void __AXServiceCallbackStack(void)
{
    AXVPB* p;
    int old;

    for (p = __AXPopCallbackStack(); p; p = __AXPopCallbackStack()) {
        if (p->callback) {
            p->callback(p);
        }
        old = OSDisableInterrupts();
        __AXRemoveFromStack(p);
        __AXPushFreeStack(p);
        OSRestoreInterrupts(old);
    }
}

void __AXInitVoiceStacks(void)
{
    u32 i;

    __AXCallbackStack = NULL;
    for (i = 0; i < AX_PRIORITY_STACKS; i++) {
        __AXStackHead[i] = __AXStackTail[i] = 0;
    }
}

void __AXAllocInit(void)
{
#ifdef DEBUG
    OSReport("Initializing AXAlloc code module\n");
#endif
    __AXInitVoiceStacks();
}

void __AXAllocQuit(void)
{
#ifdef DEBUG
    OSReport("Shutting down AXAlloc code module\n");
#endif
    __AXInitVoiceStacks();
}

void __AXPushFreeStack(AXVPB* p)
{
    p->next = __AXStackHead[0];
    __AXStackHead[0] = p;
    p->priority = 0;
}

AXVPB* __AXPopFreeStack(void)
{
    AXVPB* p;

    p = (void*) (u32) &__AXStackHead[0]->next;
    if (p) {
        __AXStackHead[0] = p->next;
    }
    return p;
}

void __AXPushCallbackStack(AXVPB* p)
{
    p->next1 = __AXCallbackStack;
    __AXCallbackStack = p;
}

AXVPB* __AXPopCallbackStack(void)
{
    AXVPB* p;

    p = (void*) (u32) &__AXCallbackStack[0];
    if (p) {
        __AXCallbackStack = p->next1;
    }
    return p;
}

void __AXRemoveFromStack(AXVPB* p)
{
    u32 i;
    AXVPB* head;
    AXVPB* tail;

    ASSERTLINE(0xB5, p->priority);
    i = p->priority;
    head = __AXStackHead[i];
    tail = __AXStackTail[i];
    if (head == tail) {
        __AXStackHead[i] = __AXStackTail[i] = 0;
        return;
    }
    if (p == head) {
        __AXStackHead[i] = p->next;
        __AXStackHead[i]->prev = 0;
        return;
    }
    if (p == tail) {
        __AXStackTail[i] = p->prev;
        __AXStackTail[i]->next = 0;
        return;
    }
    head = p->prev;
    tail = p->next;
    head->next = tail;
    tail->prev = head;
}

void __AXPushStackHead(AXVPB* p, u32 priority)
{
    ASSERTLINE(0xDF, priority);
    ASSERTLINE(0xE0, priority < AX_PRIORITY_STACKS);
    p->next = __AXStackHead[priority];
    p->prev = 0;
    if (p->next) {
        __AXStackHead[priority]->prev = p;
        __AXStackHead[priority] = p;
    } else {
        __AXStackTail[priority] = p;
        __AXStackHead[priority] = p;
    }
    p->priority = priority;
}

AXVPB* __AXPopStackFromBottom(u32 priority)
{
    AXVPB* p;

    ASSERTLINE(0xF9, priority);
    ASSERTLINE(0xFA, priority < AX_PRIORITY_STACKS);
    p = NULL;
    if (__AXStackHead[priority]) {
        if (__AXStackHead[priority] == __AXStackTail[priority]) {
            p = __AXStackHead[priority];
            __AXStackHead[priority] = __AXStackTail[priority] = 0;
        } else if (__AXStackTail[priority]) {
            p = __AXStackTail[priority];
            __AXStackTail[priority] = p->prev;
            __AXStackTail[priority]->next = 0;
        }
    }
    return p;
}

void AXFreeVoice(AXVPB* p)
{
    int old;

    ASSERTLINE(0x11C, p);
    old = OSDisableInterrupts();
    __AXRemoveFromStack(p);
    if (p->pb.state == 1) {
        p->depop = 1;
    }
    __AXSetPBDefault(p);
    __AXPushFreeStack(p);
    OSRestoreInterrupts(old);
}

AXVPB* AXAcquireVoice(u32 priority, void (*callback)(void*), u32 userContext)
{
    int old;
    AXVPB* p;
    u32 i;

    ASSERTLINE(0x13D, priority);
    ASSERTLINE(0x13E, priority < AX_PRIORITY_STACKS);

    old = OSDisableInterrupts();
    p = __AXPopFreeStack();
    if (p == 0) {
        for (i = 1; i < priority; i++) {
            p = __AXPopStackFromBottom(i);
            if (p) {
                if (p->pb.state == 1) {
                    p->depop = 1;
                }
                if (p->callback != 0) {
                    p->callback(p);
                }
                break;
            }
        }
    }
    if (p) {
        __AXPushStackHead(p, priority);
        p->callback = callback;
        p->userContext = userContext;
        __AXSetPBDefault(p);
    }
    OSRestoreInterrupts(old);
    return p;
}

void AXSetVoicePriority(AXVPB* p, u32 priority)
{
    int old;

    ASSERTLINE(0x17A, p);
    ASSERTLINE(0x17B, priority);
    ASSERTLINE(0x17C, priority < AX_PRIORITY_STACKS);
    old = OSDisableInterrupts();
    __AXRemoveFromStack(p);
    __AXPushStackHead(p, priority);
    OSRestoreInterrupts(old);
}


static __declspec(align(32)) AXPB __AXPB[AX_MAX_VOICES];

static __declspec(align(32)) AXPBITDBUFFER __AXITD[AX_MAX_VOICES];

static __declspec(align(32)) AXPBU __AXUpdates[AX_MAX_VOICES];

static AXVPB __AXVPB[AX_MAX_VOICES];

static u32 __AXMaxDspCycles, __AXRecDspCycles;

typedef char Melee360AXPBLayout[(sizeof(AXPB)==0xC0)?1:-1];

typedef char Melee360AXVPBLayout[(sizeof(AXVPB)==0x1F8)?1:-1];

void __AXSetPBDefault(AXVPB* p)
{
    p->pb.state = 0;
    p->pb.itd.flag = 0;
    p->sync = 0xA4;
    p->updateMS = p->updateCounter = 0;
    p->updateWrite = p->updateData;
    p->pb.update.updNum[0] = p->pb.update.updNum[1] = p->pb.update.updNum[2] =
        p->pb.update.updNum[3] = p->pb.update.updNum[4] = 0;
}

void __AXVPBInit(void)
{
    u32 i;
    AXPB* ppb;
    AXPBITDBUFFER* ppbi;
    AXPBU* ppbu;
    AXVPB* pvpb;
    u32* p;

#ifdef DEBUG
    OSReport("Initializing AXVPB code module\n");
#endif
    __AXMaxDspCycles = OS_BUS_CLOCK / 400;
    __AXRecDspCycles = 0U;

#define BUFFER_MEMSET(buffer, size)                                           \
    {                                                                         \
        p = (u32*) &buffer;                                                   \
        for (i = size; i != 0; i--) {                                         \
            *p = 0;                                                           \
            p++;                                                              \
        }                                                                     \
    }

    BUFFER_MEMSET(__AXPB, 0xC00);
    BUFFER_MEMSET(__AXITD, 0x400);
    BUFFER_MEMSET(__AXVPB, 0x1F80);

    for (i = 0; i < AX_MAX_VOICES; i++) {
        ppb = &__AXPB[i];
        ppbi = &__AXITD[i];
        ppbu = &__AXUpdates[i];
        pvpb = &__AXVPB[i];
        ASSERTLINE(0x2F6, (u32) ppb ^ 0x1F);
        ASSERTLINE(0x2F7, (u32) ppbi ^ 0x1F);
        ASSERTLINE(0x2F8, (u32) ppbu ^ 0x1F);
        pvpb->index = i;
        pvpb->updateWrite = pvpb->updateData;
        pvpb->itdBuffer = ppbi;
        __AXSetPBDefault(pvpb);
        if (i == 0x3F) {
            pvpb->pb.nextHi = pvpb->pb.nextLo = ppb->nextHi = ppb->nextLo = 0;
        } else {
            pvpb->pb.nextHi = (u16) ((u32) ((char*) ppb + 0xC0) >> 16);
            pvpb->pb.nextLo = (u16) ((u32) ((char*) ppb + 0xC0));
            ppb->nextHi = (u16) ((u32) ((char*) ppb + 0xC0) >> 16);
            ppb->nextLo = (u16) ((u32) ((char*) ppb + 0xC0));
        }
        pvpb->pb.currHi = (u16) (((u32) ppb) >> 16);
        pvpb->pb.currLo = (u16) ((u32) ppb);
        ppb->currHi = (u16) (((u32) ppb) >> 16);
        ppb->currLo = (u16) ((u32) ppb);
        pvpb->pb.itd.bufferHi = (u16) (((u32) ppbi) >> 16);
        pvpb->pb.itd.bufferLo = (u16) ((u32) ppbi);
        ppb->itd.bufferHi = (u16) (((u32) ppbi) >> 16);
        ppb->itd.bufferLo = (u16) ((u32) ppbi);
        pvpb->pb.update.dataHi = (u16) (((u32) ppbu) >> 16);
        pvpb->pb.update.dataLo = (u16) ((u32) ppbu);
        ppb->update.dataHi = (u16) (((u32) ppbu) >> 16);
        ppb->update.dataLo = (u16) ((u32) ppbu);

        pvpb->priority = 1;
        __AXPushFreeStack(pvpb);
    }
    DCFlushRange(__AXPB, sizeof(__AXPB));
}

void AXSetVoiceState(AXVPB* p, u16 state)
{
    int old;

    old = OSDisableInterrupts();
    p->pb.state = state;
    p->sync |= AX_SYNC_FLAG_COPYSTATE;
    if (state == 0) {
        p->depop = 1;
    }
    OSRestoreInterrupts(old);
}

void AXSetVoiceMix(AXVPB* p, AXPBMIX* mix)
{
    int old;
    u16 mixerCtrl;
    u16* dst;
    u16* src;

    src = (u16*) mix;
    dst = (u16*) &p->pb.mix;

    old = OSDisableInterrupts();

    {
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
    }
    mixerCtrl = 0;
    if (__AXClMode == 4) {
        if ((mix->vAuxAL != 0) || (mix->vAuxAR != 0)) {
            mixerCtrl |= 1;
        }
        if ((mix->vAuxBL != 0) || (mix->vAuxBR != 0)) {
            mixerCtrl |= 16;
        }
        if ((mix->vDeltaL != 0) || (mix->vDeltaR != 0) ||
            (mix->vDeltaAuxAL != 0) || (mix->vDeltaAuxAR != 0) ||
            (mix->vDeltaAuxAS != 0) || (mix->vDeltaAuxBL != 0) ||
            (mix->vDeltaAuxBR != 0))
        {
            mixerCtrl |= 8;
        }
    } else {
        if ((mix->vAuxAL != 0) || (mix->vAuxAR != 0)) {
            mixerCtrl |= 1;
        }
        if ((mix->vAuxBL != 0) || (mix->vAuxBR != 0)) {
            mixerCtrl |= 2;
        }
        if ((mix->vS != 0) || (mix->vAuxAS != 0) || (mix->vAuxBS != 0)) {
            mixerCtrl |= 4;
        }
        if ((mix->vDeltaL != 0) || (mix->vDeltaR != 0) ||
            (mix->vDeltaS != 0) || (mix->vDeltaAuxAL != 0) ||
            (mix->vDeltaAuxAR != 0) || (mix->vDeltaAuxAS != 0) ||
            (mix->vDeltaAuxBL != 0) || (mix->vDeltaAuxBR != 0) ||
            (mix->vDeltaAuxBS != 0))
        {
            mixerCtrl |= 8;
        }
    }
    p->pb.mixerCtrl = mixerCtrl;
    p->sync |= (AX_SYNC_FLAG_COPYAXPBMIX | AX_SYNC_FLAG_COPYMXRCTRL);
    OSRestoreInterrupts(old);
}

void AXSetVoiceItdOn(AXVPB* p)
{
    int old;

    old = OSDisableInterrupts();
    p->pb.itd.flag = 1;
    p->pb.itd.shiftL = p->pb.itd.shiftR = p->pb.itd.targetShiftL =
        p->pb.itd.targetShiftR = 0;
    p->sync &= ~(AX_SYNC_FLAG_COPYTSHIFT);
    p->sync |= AX_SYNC_FLAG_COPYITD;
    OSRestoreInterrupts(old);
}

void AXSetVoiceItdTarget(AXVPB* p, u16 lShift, u16 rShift)
{
    int old;

    old = OSDisableInterrupts();
    p->pb.itd.targetShiftL = lShift;
    p->pb.itd.targetShiftR = rShift;
    p->sync |= AX_SYNC_FLAG_COPYTSHIFT;
    OSRestoreInterrupts(old);
}

void AXSetVoiceVe(AXVPB* p, AXPBVE* ve)
{
    int old;

    old = OSDisableInterrupts();
    p->pb.ve.currentVolume = ve->currentVolume;
    p->pb.ve.currentDelta = ve->currentDelta;
    p->sync |= AX_SYNC_FLAG_COPYVOL;
    OSRestoreInterrupts(old);
}

void AXSetVoiceVeDelta(AXVPB* p, s16 delta)
{
    int old;

    old = OSDisableInterrupts();
    p->pb.ve.currentDelta = delta;
    p->sync |= AX_SYNC_FLAG_SWAPVOL;
    OSRestoreInterrupts(old);
}

void AXSetVoiceAddr(AXVPB* p, AXPBADDR* addr)
{
    int old;
    u32* dst;
    u32* src;

    dst = (void*) &p->pb.addr;
    src = (void*) addr;

    old = OSDisableInterrupts();
    {
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
    }
    switch (addr->format) {
    case 0:
        ASSERTMSGLINE(0x4BA, (addr->loopAddressLo & 0xF) > 1,
                      "*** loop address on ADPCM frame header! ***\n");
        ASSERTMSGLINE(0x4BF, (addr->endAddressLo & 0xF) > 1,
                      "*** end address on ADPCM frame header! ***\n");
        ASSERTMSGLINE(0x4C4, (addr->currentAddressLo & 0xF) > 1,
                      "*** current address on ADPCM frame header! ***\n");
        break;
    case 10:
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0x08000000;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        break;
    case 25:
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        *(dst) = 0x01000000;
        dst += 1;
        *(dst) = 0;
        dst += 1;
        break;
    default:
        ASSERTMSGLINE(0x4F0, 0, "unknown addr->formaqt in PB\n");
        break;
    }
    p->sync &= ~(AX_SYNC_FLAG_COPYLOOP | AX_SYNC_FLAG_COPYLOOPADDR |
                 AX_SYNC_FLAG_COPYENDADDR | AX_SYNC_FLAG_COPYCURADDR);
    p->sync |= (AX_SYNC_FLAG_COPYADDR | AX_SYNC_FLAG_COPYADPCM);
    OSRestoreInterrupts(old);
}

void AXSetVoiceLoop(AXVPB* p, u16 loop)
{
    int old;

    old = OSDisableInterrupts();
    p->pb.addr.loopFlag = loop;
    p->sync |= AX_SYNC_FLAG_COPYLOOP;
    OSRestoreInterrupts(old);
}

void AXSetVoiceLoopAddr(AXVPB* p, u32 addr)
{
    int old;

    old = OSDisableInterrupts();
    p->pb.addr.loopAddressHi = (addr >> 0x10U);
    p->pb.addr.loopAddressLo = (addr);
    p->sync |= AX_SYNC_FLAG_COPYLOOPADDR;
    OSRestoreInterrupts(old);
}

void AXSetVoiceEndAddr(AXVPB* p, u32 addr)
{
    int old;

    old = OSDisableInterrupts();
    p->pb.addr.endAddressHi = (addr >> 0x10U);
    p->pb.addr.endAddressLo = (addr);
    p->sync |= AX_SYNC_FLAG_COPYENDADDR;
    OSRestoreInterrupts(old);
}

void AXSetVoiceCurrentAddr(AXVPB* p, u32 addr)
{
    int old;

    old = OSDisableInterrupts();
    p->pb.addr.currentAddressHi = (addr >> 0x10U);
    p->pb.addr.currentAddressLo = (addr);
    p->sync |= AX_SYNC_FLAG_COPYCURADDR;
    OSRestoreInterrupts(old);
}

void AXSetVoiceAdpcm(AXVPB* p, AXPBADPCM* adpcm)
{
    int old;
    u32* dst;
    u32* src;

    dst = (void*) &p->pb.adpcm;
    src = (void*) adpcm;

    old = OSDisableInterrupts();

    {
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
    }
    p->sync |= AX_SYNC_FLAG_COPYADPCM;
    OSRestoreInterrupts(old);
}

void AXSetVoiceSrc(AXVPB* p, AXPBSRC* src_)
{
    int old;
    u16* dst;
    u16* src;

    dst = (void*) &p->pb.src;
    src = (void*) src_;

    old = OSDisableInterrupts();
    {
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
    }
    p->sync &= ~(AX_SYNC_FLAG_COPYRATIO);
    p->sync |= AX_SYNC_FLAG_COPYSRC;
    OSRestoreInterrupts(old);
}

void AXSetVoiceSrcRatio(AXVPB* p, float ratio)
{
    u32 r;
    int old;

    old = OSDisableInterrupts();
    r = 65536.0f * ratio;
    if (r > 0x40000) {
        r = 0x40000;
    }
    p->pb.src.ratioHi = ((u32) r >> 0x10);
    p->pb.src.ratioLo = ((u32) r);
    p->sync |= AX_SYNC_FLAG_COPYRATIO;
    OSRestoreInterrupts(old);
}

void AXSetVoiceAdpcmLoop(AXVPB* p, AXPBADPCMLOOP* adpcmloop)
{
    int old;
    u16* dst;
    u16* src;

    dst = (void*) &p->pb.adpcmLoop;
    src = (void*) adpcmloop;
    old = OSDisableInterrupts();
    {
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
    }
    p->sync |= AX_SYNC_FLAG_COPYADPCMLOOP;
    OSRestoreInterrupts(old);
}

void AXSetVoiceSrcType(AXVPB* p, u32 type)
{
    int old;
    AXPB* ppb;

    ASSERTLINE(0x35E, p);
    ASSERTLINE(0x35F, type <= AX_SRC_TYPE_4TAP_16K);
    old = OSDisableInterrupts();
    ppb = &p->pb;
    switch (type) {
    case AX_SRC_TYPE_NONE:
        ppb->srcSelect = 2;
        break;
    case AX_SRC_TYPE_LINEAR:
        ppb->srcSelect = 1;
        break;
    case AX_SRC_TYPE_4TAP_8K:
        ppb->srcSelect = 0;
        ppb->coefSelect = 0;
        break;
    case AX_SRC_TYPE_4TAP_12K:
        ppb->srcSelect = 0;
        ppb->coefSelect = 1;
        break;
    case AX_SRC_TYPE_4TAP_16K:
        ppb->srcSelect = 0;
        ppb->coefSelect = 2;
        break;
    }
    p->sync |= AX_SYNC_FLAG_COPYSELECT;
    OSRestoreInterrupts(old);
}

void AXSetVoiceType(AXVPB* p, u16 type)
{
    int old;

    old = OSDisableInterrupts();
    p->pb.type = type;
    p->sync |= AX_SYNC_FLAG_COPYTYPE;
    OSRestoreInterrupts(old);
}

void AXSetVoiceFir(AXVPB* p, AXPBFIR* fir)
{
    int old;

    old = OSDisableInterrupts();
    p->pb.fir.numCoefs = fir->numCoefs;
    p->pb.fir.coefsHi = fir->coefsHi;
    p->pb.fir.coefsLo = fir->coefsLo;
    p->sync |= AX_SYNC_FLAG_COPYFIR;
    OSRestoreInterrupts(old);
}

void AXSetVoiceDpop(AXVPB* p, AXPBDPOP* dpop)
{
    int old;
    u16* dst;
    u16* src;

    dst = (void*) &p->pb.dpop;
    src = (void*) dpop;

    old = OSDisableInterrupts();
    {
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
        *(dst) = *(src);
        dst += 1;
        src += 1;
    }
    p->sync |= AX_SYNC_FLAG_COPYDPOP;
    OSRestoreInterrupts(old);
}

void AXSetVoiceUpdateIncrement(AXVPB* p)
{
    int old;

    old = OSDisableInterrupts();
    p->updateMS++;
    p->sync |= AX_SYNC_FLAG_COPYUPDATE;
    ASSERTMSGLINE(0x431, p->updateMS <= 4, "PB updates cannot exceed 5ms\n");
    OSRestoreInterrupts(old);
}

void AXSetVoiceUpdateWrite(AXVPB* p, u16 param, u16 data)
{
    int old;

    old = OSDisableInterrupts();
    ASSERTMSGLINE(0x43F, p->updateMS <= 4 && param < sizeof(AXPB)/2, "Invalid native PB update\n");
    p->pb.update.updNum[p->updateMS]++;
    p->updateCounter += 2;
    ASSERTMSGLINE(0x43F, p->updateCounter <= 128,
                  "PB update block exceeded 128 words\n");
    *(p->updateWrite) = param;
    p->updateWrite += 1;
    *(p->updateWrite) = data;
    p->updateWrite += 1;
    p->sync |= AX_SYNC_FLAG_COPYUPDATE;
    OSRestoreInterrupts(old);
}

static __declspec(align(32)) long __AXBufferAuxA[3][480];
static __declspec(align(32)) long __AXBufferAuxB[3][480];

static void (*__AXCallbackAuxA)(void*, void*);
static void (*__AXCallbackAuxB)(void*, void*);
static void* __AXContextAuxA;
static void* __AXContextAuxB;
static long* __AXAuxADspWrite;
static long* __AXAuxADspRead;
static long* __AXAuxBDspWrite;
static long* __AXAuxBDspRead;
static unsigned long __AXAuxDspWritePosition;
static unsigned long __AXAuxDspReadPosition;
static unsigned long __AXAuxCpuReadWritePosition;

void __AXAuxInit(void)
{
    int i;
    long* pA;
    long* pB;

#ifdef DEBUG
    OSReport("Initializing AXAux code module\n");
#endif
    __AXCallbackAuxA = NULL;
    __AXCallbackAuxB = NULL;
    __AXContextAuxA = 0;
    __AXContextAuxB = 0;
    __AXAuxDspWritePosition = 0;
    __AXAuxDspReadPosition = 1;
    __AXAuxCpuReadWritePosition = 2;
    pA = (long*) &__AXBufferAuxA;
    pB = (long*) &__AXBufferAuxB;
    for (i = 0; i < 3 * 480; i++) {
        *(pA) = 0;
        pA += 1;
        *(pB) = 0;
        pB += 1;
    }
}

void __AXAuxQuit(void)
{
#ifdef DEBUG
    OSReport("Shutting down AXAux code module\n");
#endif
    __AXCallbackAuxA = NULL;
    __AXCallbackAuxB = NULL;
}

void __AXGetAuxAInput(u32* p)
{
    if (__AXCallbackAuxA != NULL) {
        *p = (u32) &__AXBufferAuxA[__AXAuxDspWritePosition][0];
    } else {
        *p = 0;
    }
}

void __AXGetAuxAOutput(u32* p)
{
    *p = (u32) &__AXBufferAuxA[__AXAuxDspReadPosition][0];
}

void __AXGetAuxBInput(u32* p)
{
    if (__AXCallbackAuxB != NULL) {
        *p = (u32) &__AXBufferAuxB[__AXAuxDspWritePosition][0];
    } else {
        *p = 0;
    }
}

void __AXGetAuxBOutput(u32* p)
{
    *p = (u32) &__AXBufferAuxB[__AXAuxDspReadPosition][0];
}

void __AXProcessAux(void)
{
    struct AX_AUX_DATA auxData;

    __AXAuxADspWrite = &__AXBufferAuxA[__AXAuxDspWritePosition][0];
    __AXAuxADspRead = &__AXBufferAuxA[__AXAuxDspReadPosition][0];
    __AXAuxBDspWrite = &__AXBufferAuxB[__AXAuxDspWritePosition][0];
    __AXAuxBDspRead = &__AXBufferAuxB[__AXAuxDspReadPosition][0];
    if (__AXCallbackAuxA) {
        auxData.l = &__AXBufferAuxA[__AXAuxCpuReadWritePosition][0];
        auxData.r = &__AXBufferAuxA[__AXAuxCpuReadWritePosition][160];
        auxData.s = &__AXBufferAuxA[__AXAuxCpuReadWritePosition][320];
        DCInvalidateRange(auxData.l, 0x780);
        __AXCallbackAuxA(&auxData.l, __AXContextAuxA);
        DCFlushRangeNoSync(auxData.l, 0x780);
    }
    if (__AXCallbackAuxB && __AXClMode != 4) {
        auxData.l = &__AXBufferAuxB[__AXAuxCpuReadWritePosition][0];
        auxData.r = &__AXBufferAuxB[__AXAuxCpuReadWritePosition][160];
        auxData.s = &__AXBufferAuxB[__AXAuxCpuReadWritePosition][320];
        DCInvalidateRange(auxData.l, 0x780);
        __AXCallbackAuxB(&auxData.l, __AXContextAuxB);
        DCFlushRangeNoSync(auxData.l, 0x780);
    }
    __AXAuxDspWritePosition += 1;
    __AXAuxDspWritePosition %= 3;
    __AXAuxDspReadPosition += 1;
    __AXAuxDspReadPosition %= 3;
    __AXAuxCpuReadWritePosition += 1;
    __AXAuxCpuReadWritePosition %= 3;
}

void AXRegisterAuxACallback(void (*callback)(void*, void*), void* context)
{
    __AXCallbackAuxA = callback;
    __AXContextAuxA = context;
}

void AXRegisterAuxBCallback(void (*callback)(void*, void*), void* context)
{
    __AXCallbackAuxB = callback;
    __AXContextAuxB = context;
}


// .bss
static __declspec(align(32)) struct _AXSPB __AXStudio;

// .sbss
static long __AXSpbAL;
static long __AXSpbAR;
static long __AXSpbAS;
static long __AXSpbAAL;
static long __AXSpbAAR;
static long __AXSpbAAS;
static long __AXSpbABL;
static long __AXSpbABR;
static long __AXSpbABS;

u32 __AXGetStudio(void)
{
    return (u32) &__AXStudio;
}

void __AXDepopFade(long* hostSum, long* dspVolume, s16* dspDelta)
{
    int frames;
    long delta;

    frames = *hostSum / 160;

    if (frames) {
        delta = *hostSum / 160;
        if (delta > 0x14) {
            delta = 0x14;
        }
        if (delta < -0x14) {
            delta = -0x14;
        }
        *dspVolume = *hostSum;
        *hostSum -= delta * 0xA0;
        *dspDelta = delta * -1;
        return;
    }
    *hostSum = 0;
    *dspVolume = 0;
    *dspDelta = 0;
}

void __AXPrintStudio(void)
{
    __AXDepopFade(&__AXSpbAL, (void*) &__AXStudio.dpopLHi,
                  &__AXStudio.dpopLDelta);
    __AXDepopFade(&__AXSpbAR, (void*) &__AXStudio.dpopRHi,
                  &__AXStudio.dpopRDelta);
    __AXDepopFade(&__AXSpbAS, (void*) &__AXStudio.dpopSHi,
                  &__AXStudio.dpopSDelta);
    __AXDepopFade(&__AXSpbAAL, (void*) &__AXStudio.dpopALHi,
                  &__AXStudio.dpopALDelta);
    __AXDepopFade(&__AXSpbAAR, (void*) &__AXStudio.dpopARHi,
                  &__AXStudio.dpopARDelta);
    __AXDepopFade(&__AXSpbAAS, (void*) &__AXStudio.dpopASHi,
                  &__AXStudio.dpopASDelta);
    __AXDepopFade(&__AXSpbABL, (void*) &__AXStudio.dpopBLHi,
                  &__AXStudio.dpopBLDelta);
    __AXDepopFade(&__AXSpbABR, (void*) &__AXStudio.dpopBRHi,
                  &__AXStudio.dpopBRDelta);
    __AXDepopFade(&__AXSpbABS, (void*) &__AXStudio.dpopBSHi,
                  &__AXStudio.dpopBSDelta);
    DCFlushRange(&__AXStudio, sizeof(__AXStudio));
}

void __AXSPBInit(void)
{
#ifdef DEBUG
    OSReport("Initializing AXSPB code module\n");
#endif
    __AXSpbAL = __AXSpbAR = __AXSpbAS = __AXSpbAAL = __AXSpbAAR = __AXSpbAAS =
        __AXSpbABL = __AXSpbABR = __AXSpbABS = 0;
}

void __AXSPBQuit(void)
{
#ifdef DEBUG
    OSReport("Shutting down AXSPB code module\n");
#endif
}

void __AXDepopVoice(AXPB* p)
{
    __AXSpbAL += p->dpop.aL;
    __AXSpbAAL += p->dpop.aAuxAL;
    __AXSpbABL += p->dpop.aAuxBL;
    __AXSpbAR += p->dpop.aR;
    __AXSpbAAR += p->dpop.aAuxAR;
    __AXSpbABR += p->dpop.aAuxBR;
    __AXSpbAS += p->dpop.aS;
    __AXSpbAAS += p->dpop.aAuxAS;
    __AXSpbABS += p->dpop.aAuxBS;
}

