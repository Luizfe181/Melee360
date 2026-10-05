#include <dolphin/dvd.h>
#include <stdio.h>
#include <stdarg.h>
void OSReport(const char* f,...){va_list a;va_start(a,f);vprintf(f,a);va_end(a);}
#include <string.h>
void Melee360DVDPump(void);int Melee360DVDProbe(void);int Melee360DVDSetRoot(const char*);
static int order[8],calls;static DVDFileInfo first,second;
static __declspec(align(32)) unsigned char a[64],b[64];
static void onSecond(s32 n,DVDFileInfo* f){order[calls++]=2;if(n!=32||f!=&second)order[calls-1]=-2;}
static void onFirst(s32 n,DVDFileInfo* f){order[calls++]=1;if(n!=32||f!=&first)order[calls-1]=-1;}
static void chain(s32 n,DVDFileInfo* f){order[calls++]=3;if(n!=32||!DVDFastOpen(DVDConvertPathToEntrynum("PlMr.dat"),f)||!DVDReadAsyncPrio(f,a+32,32,32,onFirst,1))order[calls-1]=-3;}
int main(void){s32 entry;unsigned int len;unsigned char expected[64];FILE* ref;
 if(!Melee360DVDProbe())return 1;entry=DVDConvertPathToEntrynum("PlMr.dat");
 if(!DVDFastOpen(entry,&first)||!DVDFastOpen(entry,&second))return 2;
 if(Melee360DVDSetRoot("missing")||!DVDFastOpen(entry,&first)||DVDFastOpen(0,&first))return 3;
 if(DVDReadAsyncPrio(&first,a+1,32,0,onFirst,1)||DVDReadAsyncPrio(&first,a,31,0,onFirst,1)||DVDReadAsyncPrio(&first,a,32,-4,onFirst,1)||DVDReadAsyncPrio(&first,a,32,0,onFirst,4))return 4;
 if(!DVDReadAsyncPrio(&first,a,32,0,onFirst,3)||DVDFastOpen(entry,&first)||!DVDReadAsyncPrio(&second,b,32,0,onSecond,0)||calls)return 5;
 Melee360DVDPump();if(calls!=1||order[0]!=2||first.cb.state!=DVD_STATE_WAITING)return 6;
 Melee360DVDPump();if(calls!=2||order[1]!=1||memcmp(a,b,32))return 7;
 if(!DVDReadAsyncPrio(&first,a,32,0,chain,1))return 8;Melee360DVDPump();if(calls!=3||order[2]!=3||first.cb.state!=DVD_STATE_WAITING)return 9;
 Melee360DVDPump();if(calls!=4||order[3]!=1)return 10;
 ref=fopen("C:\\Users\\luizf\\Documents\\melee_extraido\\PlMr.dat","rb");if(!ref||fread(expected,1,64,ref)!=64)return 11;fclose(ref);if(memcmp(a,expected,64))return 12;
 len=first.length;if(DVDReadPrio(&first,a,32,len+1,2)!=-1)return 13;
 if(DVDReadPrio(&first,a,32,len-4,2)!=32)return 14;{int i;for(i=4;i<32;++i)if(a[i])return 15;}
 if(!DVDClose(&first)||!DVDClose(&second)||DVDClose(&first))return 16;
 if(!Melee360DVDSetRoot("missing-directory")||DVDCheckDisk()||DVDGetDriveStatus()!=DVD_STATE_NO_DISK||DVDFastOpen(entry,&first))return 17;
 puts("DVD FST mapping, disc ID, byte equality, delayed/priority/reentrant callbacks, bounds/tail padding and missing-media checks passed");return 0;
}
