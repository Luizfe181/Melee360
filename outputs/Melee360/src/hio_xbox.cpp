#include <xtl.h>
#include <stdio.h>
#include <vector>
#include "platform_log.h"
extern "C" {
#include <dolphin/types.h>
#include <dolphin/hio.h>
}
namespace {
const u32 MAGIC=0x4d334849;SOCKET connection=INVALID_SOCKET;HIOCallback interruptCallback,completion;std::vector<u32> mailbox;bool pumping,netReady;
bool wire(void* data,int bytes,bool transmit){char* p=(char*)data;while(bytes){int count=transmit?send(connection,p,bytes,0):recv(connection,p,bytes,0);if(count<=0){closesocket(connection);connection=INVALID_SOCKET;mailbox.clear();return false;}p+=count;bytes-=count;}return true;}
bool rpc(u32 operation,u32 address,void* data,u32 bytes,u32 value){if(connection==INVALID_SOCKET)return false;u32 request[5]={htonl(MAGIC),htonl(operation),htonl(address),htonl(bytes),htonl(value)};if(!wire(request,20,true)||(operation==2&&!wire(data,(int)bytes,true)))return false;u32 reply[4];if(!wire(reply,16,false))return false;for(int i=0;i<4;++i)reply[i]=ntohl(reply[i]);if(reply[0]!=MAGIC||reply[2]>128||reply[3]>(operation==1?bytes:0)){closesocket(connection);connection=INVALID_SOCKET;return false;}for(u32 i=0;i<reply[2];++i){u32 message;if(!wire(&message,4,false))return false;mailbox.push_back(ntohl(message));}if(reply[3]&&!wire(data,(int)reply[3],false))return false;return reply[1]==1&&(operation!=1||reply[3]==bytes);}
bool connectHost(){if(connection!=INVALID_SOCKET)return true;FILE* file=fopen("game:\\mcc-host.cfg","rb");if(!file)return false;char address[64]={0};unsigned port=0;int parsed=fscanf(file,"%63s %u",address,&port);fclose(file);if(parsed!=2||port<1||port>65535)return false;u32 ip=inet_addr(address);if(ip==INADDR_NONE)return false;if(!netReady){XNetStartupParams params={0};params.cfgSizeOfStruct=sizeof(params);params.cfgFlags=XNET_STARTUP_BYPASS_SECURITY;if(XNetStartup(&params))return false;WSADATA data;if(WSAStartup(MAKEWORD(2,2),&data)){XNetCleanup();return false;}netReady=true;}connection=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);if(connection==INVALID_SOCKET)return false;DWORD timeout=2000;setsockopt(connection,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(timeout));setsockopt(connection,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout,sizeof(timeout));sockaddr_in endpoint={0};endpoint.sin_family=AF_INET;endpoint.sin_addr.s_addr=ip;endpoint.sin_port=htons((u16)port);if(connect(connection,(sockaddr*)&endpoint,sizeof(endpoint))){closesocket(connection);connection=INVALID_SOCKET;return false;}return rpc(0,0,0,0,0);}
bool transfer(u32 address,void* data,s32 bytes,bool write){return bytes>=0&&data&&address<=0x20000u&&(u32)bytes<=0x20000u-address&&rpc(write?2:1,address,data,(u32)bytes,0);}
}
extern "C" BOOL HIOEnumDevices(HIOEnumCallback callback){if(!callback||!connectHost())return FALSE;callback(0);return TRUE;}
extern "C" BOOL HIOInit(s32 channel,HIOCallback callback){if(channel!=0||!callback||!connectHost())return FALSE;interruptCallback=callback;return TRUE;}
extern "C" BOOL HIORead(u32 address,void* data,s32 bytes){return transfer(address,data,bytes,false)?TRUE:FALSE;}
extern "C" BOOL HIOWrite(u32 address,void* data,s32 bytes){return transfer(address,data,bytes,true)?TRUE:FALSE;}
extern "C" BOOL HIOReadMailbox(u32* word){if(!word||mailbox.empty())return FALSE;*word=mailbox[0];mailbox.erase(mailbox.begin());return TRUE;}
extern "C" BOOL HIOWriteMailbox(u32 word){return rpc(3,0,0,0,word)?TRUE:FALSE;}
extern "C" BOOL HIOReadStatus(u32* status){if(!status||!rpc(4,0,0,0,0))return FALSE;*status=mailbox.empty()?0:1;return TRUE;}
extern "C" BOOL HIOReadAsync(u32 address,void* data,s32 bytes,HIOCallback callback){if(completion||!callback||!transfer(address,data,bytes,false))return FALSE;completion=callback;return TRUE;}
extern "C" BOOL HIOWriteAsync(u32 address,void* data,s32 bytes,HIOCallback callback){if(completion||!callback||!transfer(address,data,bytes,true))return FALSE;completion=callback;return TRUE;}
extern "C" void Melee360HIOPump(void){if(pumping||connection==INVALID_SOCKET)return;pumping=true;rpc(4,0,0,0,0);if(completion){HIOCallback callback=completion;completion=0;callback();}unsigned budget=128;while(budget--&&!mailbox.empty()&&interruptCallback)interruptCallback();pumping=false;Sleep(1);}
extern "C" void Melee360HIOClose(void){if(connection!=INVALID_SOCKET)closesocket(connection);connection=INVALID_SOCKET;interruptCallback=completion=0;mailbox.clear();if(netReady){WSACleanup();XNetCleanup();netReady=false;}}
