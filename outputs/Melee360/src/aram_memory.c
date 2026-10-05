#include <dolphin/ar.h>
#include <dolphin/os.h>
#include <stdlib.h>
#include <string.h>
#define SIZE (16u*1024u*1024u)
#define BASE 0x4000u
typedef char arq_request_layout[sizeof(ARQRequest)==32?1:-1];
static unsigned char* memory;static u32* lengths;static u32 count,limit,top=BASE;
typedef struct Job {ARQRequest* request;unsigned int serial;} Job;
static Job jobs[64];static unsigned int serial;
static void require(int condition){if(!condition)__assert(__FILE__,__LINE__,"invalid ARAM request or exhausted ARAM");}
u32 ARInit(u32* stack,u32 entries){if(memory)return BASE;require(stack&&entries);memory=(unsigned char*)calloc(1,SIZE);require(memory!=0);lengths=stack;limit=entries;count=0;top=BASE;return BASE;}
u32 ARGetSize(void){return SIZE;}
u32 ARGetBaseAddress(void){return BASE;}
int ARCheckInit(void){return memory!=0;}
u32 ARAlloc(u32 bytes){u32 result;int token=OSDisableInterrupts();require(memory&&bytes&&!(bytes&31)&&count<limit&&bytes<=SIZE-top);result=top;top+=bytes;lengths[count++]=bytes;OSRestoreInterrupts(token);return result;}
u32 ARFree(u32* bytes){int token=OSDisableInterrupts();u32 length;require(memory&&count);length=lengths[--count];if(bytes)*bytes=length;top-=length;OSRestoreInterrupts(token);return top;}
void ARQInit(void){/* Static queue is already initialized. Do not drop live jobs. */}
void ARQPostRequest(ARQRequest* request,uintptr_t owner,u32 type,u32 priority,u32 source,u32 destination,u32 length,ARQCallback callback){
    int i,slot=-1,token=OSDisableInterrupts();u32 aram=type==ARQ_TYPE_MRAM_TO_ARAM?destination:source;u32 mainAddress=type==ARQ_TYPE_MRAM_TO_ARAM?source:destination;
    require(memory&&request&&(type==0||type==1)&&priority<=1&&length&&!(length&31)&&!(source&31)&&!(destination&31)&&aram>=BASE&&aram<SIZE&&length<=SIZE-aram);
    require(mainAddress&&length<=0xffffffffu-mainAddress);
    for(i=0;i<64;++i){require(jobs[i].request!=request);if(!jobs[i].request)slot=i;}require(slot>=0);
    request->next=0;request->owner=owner;request->type=type;request->priority=priority;request->source=source;request->dest=destination;request->length=length;request->callback=callback;
    jobs[slot].request=request;jobs[slot].serial=++serial;OSRestoreInterrupts(token);
}
void Melee360ARAMPump(void){
    int i,best=-1,token=OSDisableInterrupts();ARQRequest* r;
    for(i=0;i<64;++i)if(jobs[i].request&&(best<0||jobs[i].request->priority>jobs[best].request->priority||(jobs[i].request->priority==jobs[best].request->priority&&jobs[i].serial<jobs[best].serial)))best=i;
    if(best<0){OSRestoreInterrupts(token);return;}r=jobs[best].request;
    if(r->type==ARQ_TYPE_MRAM_TO_ARAM)memcpy(memory+r->dest,(const void*)r->source,r->length);else memcpy((void*)r->dest,memory+r->source,r->length);
    jobs[best].request=0;OSRestoreInterrupts(token);if(r->callback)r->callback(r);
}
unsigned Melee360ARAMPending(void){unsigned result=0;int i,token=OSDisableInterrupts();for(i=0;i<64;++i)if(jobs[i].request)++result;OSRestoreInterrupts(token);return result;}
/* Native DSP consumer access: explicit BE PCM formats, bounded ARAM reads. */
int Melee360ARAMReadPCM(u32 sampleAddress,u16 format,s16* output){
 u32 byteAddress;int token;u16 value;
 if(!output||!memory||(format!=10&&format!=25))return 0;
 if(format==10){if(sampleAddress>=(SIZE/2))return 0;byteAddress=sampleAddress*2;}else byteAddress=sampleAddress;
 if(byteAddress<BASE||byteAddress>=SIZE||(format==10&&byteAddress>SIZE-2))return 0;
 token=OSDisableInterrupts();
 if(format==10){value=(u16)((u16)memory[byteAddress]<<8|memory[byteAddress+1]);*output=(s16)value;}
 else *output=(s16)((s8)memory[byteAddress]*256);
 OSRestoreInterrupts(token);return 1;
}
int Melee360ARAMReadByte(u32 address,u8* output){int token;if(!output||!memory||address<BASE||address>=SIZE)return 0;token=OSDisableInterrupts();*output=memory[address];OSRestoreInterrupts(token);return 1;}
