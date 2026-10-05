/* Native TEV state. FIFO register setters are translated to shader constants. */
namespace {
struct TevStage {float color[4],alpha[4],colorOp[4],alphaOp[4],order[4],select[4];};
struct TevState {TevStage stage[16];float reg[4][4],konst[4][4],swap[4][4],indMatrix[6][4],indOrder[4][4],indirect[16][3][4],zTexture[4];unsigned int count,indCount;};
TevState tev;float tevProbeChannel;
bool depthTextureActive(){return tev.zTexture[0]!=0;}
void initializeTev(){
    memset(&tev,0,sizeof(tev));tev.count=1;
    for(int s=0;s<16;++s){TevStage& t=tev.stage[s];
        t.color[0]=GX_CC_ZERO;t.color[1]=GX_CC_TEXC;t.color[2]=s?GX_CC_CPREV:GX_CC_RASC;t.color[3]=GX_CC_ZERO;
        t.alpha[0]=GX_CA_ZERO;t.alpha[1]=GX_CA_TEXA;t.alpha[2]=s?GX_CA_APREV:GX_CA_RASA;t.alpha[3]=GX_CA_ZERO;
        t.colorOp[2]=t.alphaOp[2]=1; // packed scale*2+clamp
        t.order[1]=GX_COLOR0A0;t.order[2]=1;
    }
    for(int i=0;i<4;++i)for(int c=0;c<4;++c)tev.swap[i][c]=(float)c;
}
void uploadTev(){
    uploadFog();
    int compression=Melee360GXDepthCompression();float efbDepth[4]={compression>=0?1.f:0.f,(float)compression,0,0};require(SUCCEEDED(setGXPixelConstants(187,efbDepth,1)));device->SetPixelShader(tev.zTexture[0]?psDepth:compression>=0?psQuant:ps);float depthNormalization[4]={1.0f/16777215.0f,0,0,0};require(SUCCEEDED(setGXPixelConstants(186,depthNormalization,1)));
    require(SUCCEEDED(setGXPixelConstants(16,(const float*)tev.stage,96)));
    require(SUCCEEDED(setGXPixelConstants(112,(const float*)tev.reg,4)));
    require(SUCCEEDED(setGXPixelConstants(116,(const float*)tev.konst,4)));
    require(SUCCEEDED(setGXPixelConstants(120,(const float*)tev.swap,4)));
    require(SUCCEEDED(setGXPixelConstants(125,(const float*)tev.indMatrix,6)));
    require(SUCCEEDED(setGXPixelConstants(131,(const float*)tev.indOrder,4)));
    require(SUCCEEDED(setGXPixelConstants(135,(const float*)tev.indirect,48)));
    for(unsigned int s=0;s<tev.count;++s)if(tev.indirect[s][2][1]&&((tev.indirect[s][0][2]!=0)||(tev.indirect[s][0][3]!=0)))require(tev.indirect[s][2][0]<tev.indCount);
    float count[4]={(float)tev.count,tevProbeChannel,(float)tev.indCount,0};require(SUCCEEDED(setGXPixelConstants(124,count,1)));
    D3DVIEWPORT9 viewport;require(SUCCEEDED(device->GetViewport(&viewport)));float depthRange[4]={viewport.MinZ,viewport.MaxZ,1.0f/16777215.0f,0};
    require(SUCCEEDED(setGXPixelConstants(183,tev.zTexture,1))&&SUCCEEDED(setGXPixelConstants(184,depthRange,1)));
}
TevStage& checkedStage(GXTevStageID s){require(!__GXinBegin&&s>=0&&s<16);return tev.stage[s];}
void setOp(float* dest,GXTevOp op,GXTevBias bias,GXTevScale scale,GXBool clamp,GXTevRegID reg){
    require((op==0||op==1||(op>=8&&op<=15))&&bias>=0&&bias<=2&&scale>=0&&scale<=3&&clamp<=1&&reg>=0&&reg<=3);
    dest[0]=(float)op;dest[1]=(float)bias;dest[2]=(float)(scale*2+clamp);dest[3]=(float)reg;
}
}
extern "C" void GXSetNumIndStages(u8 n){require(!__GXinBegin&&n<=4);tev.indCount=n;}
extern "C" void GXSetIndTexOrder(GXIndTexStageID s,GXTexCoordID coord,GXTexMapID map){
    require(!__GXinBegin&&s>=0&&s<4&&map>=0&&map<8&&coord>=GX_TEXCOORD0&&coord<=GX_TEXCOORD7);tev.indOrder[s][0]=(float)map;tev.indOrder[s][3]=(float)coord;
}
extern "C" void GXSetIndTexCoordScale(GXIndTexStageID s,GXIndTexScale a,GXIndTexScale b){
    require(!__GXinBegin&&s>=0&&s<4&&a>=0&&a<=8&&b>=0&&b<=8);tev.indOrder[s][1]=(float)a;tev.indOrder[s][2]=(float)b;
}
extern "C" void GXSetIndTexMtx(GXIndTexMtxID id,f32 matrix[2][3],s8 exponent){
    require(!__GXinBegin&&matrix&&((id>=1&&id<=3)||(id>=5&&id<=7)||(id>=9&&id<=11))&&exponent>=-17&&exponent<=46);
    unsigned int index=(id-1)&3;for(int row=0;row<2;++row){for(int c=0;c<3;++c){require(matrix[row][c]>-2097152&&matrix[row][c]<2097152);int value=((int)(matrix[row][c]*1024))&2047;if(value>=1024)value-=2048;tev.indMatrix[index*2+row][c]=(float)value;}tev.indMatrix[index*2+row][3]=(float)exponent;}
}
extern "C" void GXSetTevIndirect(GXTevStageID stage,GXIndTexStageID ind,GXIndTexFormat format,GXIndTexBiasSel bias,GXIndTexMtxID matrix,GXIndTexWrap ws,GXIndTexWrap wt,GXBool add,GXBool lod,GXIndTexAlphaSel alpha){
    checkedStage(stage);require(ind>=0&&ind<4&&format>=0&&format<4&&bias>=0&&bias<8&&((matrix>=0&&matrix<=3)||(matrix>=5&&matrix<=7)||(matrix>=9&&matrix<=11))&&ws>=0&&ws<=6&&wt>=0&&wt<=6&&add<=1&&lod<=1&&alpha>=0&&alpha<4);
    float* a=tev.indirect[stage][0];a[0]=(float)format;a[1]=(float)bias;a[2]=(float)matrix;a[3]=(float)alpha;
    float* b=tev.indirect[stage][1];b[0]=(float)ws;b[1]=(float)wt;b[2]=(float)add;b[3]=(float)lod;
    tev.indirect[stage][2][0]=(float)ind;tev.indirect[stage][2][1]=(ind||format||bias||matrix||ws||wt||add||lod||alpha)?1.0f:0.0f;
}
extern "C" void GXSetTevDirect(GXTevStageID stage){GXSetTevIndirect(stage,GX_INDTEXSTAGE0,GX_ITF_8,GX_ITB_NONE,GX_ITM_OFF,GX_ITW_OFF,GX_ITW_OFF,0,0,GX_ITBA_OFF);}
extern "C" void GXSetNumTevStages(u8 n){require(!__GXinBegin&&n>=1&&n<=16);tev.count=n;}
extern "C" void GXSetZTexture(GXZTexOp op,GXTexFmt fmt,u32 bias){
    if(__GXinBegin||op<GX_ZT_DISABLE||op>GX_ZT_REPLACE||(fmt!=GX_TF_Z8&&fmt!=GX_TF_Z16&&fmt!=GX_TF_Z24X8)||bias>0xffffff){char msg[160];sprintf_s(msg,sizeof(msg),"GX Z texture: begin=%u op=%u fmt=%u bias=%u\n",__GXinBegin,op,fmt,bias);Melee360Log(msg);}
    require(!__GXinBegin&&op>=GX_ZT_DISABLE&&op<=GX_ZT_REPLACE&&(fmt==GX_TF_Z8||fmt==GX_TF_Z16||fmt==GX_TF_Z24X8)&&bias<=0xffffff);
    tev.zTexture[0]=(float)op;tev.zTexture[1]=fmt==GX_TF_Z8?0.0f:fmt==GX_TF_Z16?1.0f:2.0f;tev.zTexture[2]=(float)bias;
}
extern "C" void GXSetTevColorIn(GXTevStageID s,GXTevColorArg a,GXTevColorArg b,GXTevColorArg c,GXTevColorArg d){
    TevStage& t=checkedStage(s);require(a>=0&&a<=15&&b>=0&&b<=15&&c>=0&&c<=15&&d>=0&&d<=15);
    t.color[0]=(float)a;t.color[1]=(float)b;t.color[2]=(float)c;t.color[3]=(float)d;
}
extern "C" void GXSetTevAlphaIn(GXTevStageID s,GXTevAlphaArg a,GXTevAlphaArg b,GXTevAlphaArg c,GXTevAlphaArg d){
    TevStage& t=checkedStage(s);require(a>=0&&a<=7&&b>=0&&b<=7&&c>=0&&c<=7&&d>=0&&d<=7);
    t.alpha[0]=(float)a;t.alpha[1]=(float)b;t.alpha[2]=(float)c;t.alpha[3]=(float)d;
}
extern "C" void GXSetTevColorOp(GXTevStageID s,GXTevOp op,GXTevBias bias,GXTevScale scale,GXBool clamp,GXTevRegID reg){setOp(checkedStage(s).colorOp,op,bias,scale,clamp,reg);}
extern "C" void GXSetTevAlphaOp(GXTevStageID s,GXTevOp op,GXTevBias bias,GXTevScale scale,GXBool clamp,GXTevRegID reg){setOp(checkedStage(s).alphaOp,op,bias,scale,clamp,reg);}
extern "C" void GXSetTevColorS10(GXTevRegID id,GXColorS10 c){
    require(!__GXinBegin&&id>=0&&id<4&&c.r>=-1024&&c.r<=1023&&c.g>=-1024&&c.g<=1023&&c.b>=-1024&&c.b<=1023&&c.a>=-1024&&c.a<=1023);
    tev.reg[id][0]=(float)c.r;tev.reg[id][1]=(float)c.g;tev.reg[id][2]=(float)c.b;tev.reg[id][3]=(float)c.a;
}
extern "C" void GXSetTevColor(GXTevRegID id,GXColor c){GXColorS10 s={(s16)c.r,(s16)c.g,(s16)c.b,(s16)c.a};GXSetTevColorS10(id,s);}
extern "C" void GXSetTevKColor(GXTevKColorID id,GXColor c){
    require(!__GXinBegin&&id>=0&&id<4);tev.konst[id][0]=(float)c.r;tev.konst[id][1]=(float)c.g;tev.konst[id][2]=(float)c.b;tev.konst[id][3]=(float)c.a;
}
extern "C" void GXSetTevKColorSel(GXTevStageID s,GXTevKColorSel k){require(k>=0&&k<=31);checkedStage(s).select[0]=(float)k;}
extern "C" void GXSetTevKAlphaSel(GXTevStageID s,GXTevKAlphaSel k){require(k>=0&&k<=31);checkedStage(s).select[1]=(float)k;}
extern "C" void GXSetTevSwapMode(GXTevStageID s,GXTevSwapSel ras,GXTevSwapSel tex){require(ras>=0&&ras<4&&tex>=0&&tex<4);TevStage& t=checkedStage(s);t.select[2]=(float)ras;t.select[3]=(float)tex;}
extern "C" void GXSetTevSwapModeTable(GXTevSwapSel s,GXTevColorChan r,GXTevColorChan g,GXTevColorChan b,GXTevColorChan a){
    require(!__GXinBegin&&s>=0&&s<4&&r>=0&&r<4&&g>=0&&g<4&&b>=0&&b<4&&a>=0&&a<4);
    tev.swap[s][0]=(float)r;tev.swap[s][1]=(float)g;tev.swap[s][2]=(float)b;tev.swap[s][3]=(float)a;
}
#include "gx_tev_original_op.inc"


#include "gx_tev_original_helpers.inc"







