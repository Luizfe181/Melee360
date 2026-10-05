#include <xtl.h>
extern "C" {
#include <dolphin/os.h>
u32 OSGetPhysicalMemSize(void){MEMORYSTATUS status={0};status.dwLength=sizeof(status);GlobalMemoryStatus(&status);return status.dwTotalPhys;}
int Melee360MemorySizeProbe(void){u32 physical=OSGetPhysicalMemSize(),simulated=OSGetConsoleSimulatedMemSize();void* lo=OSGetArenaLo();void* hi=OSGetArenaHi();return physical>=simulated&&simulated==8u*1024u*1024u&&lo&&hi&&(u32)hi>=(u32)lo&&(u32)hi-(u32)lo<=simulated;}
}
