namespace {
unsigned int tevProbeCases;
float tevProbeU=.5f,tevProbeV=.5f,tevProbeSpan=0;
float tevExtraUV[7][2];GXColor tevColor1={61,113,181,229};
void drawTevTriangle(GXColor vertex){
GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);
    for(int i=0;i<3;++i){GXPosition3f32(i==1?.2f:i==0?-.2f:0,i==2?.2f:-.2f,-1);GXColor4u8(vertex.r,vertex.g,vertex.b,vertex.a);
        if(extraColor.descriptor!=GX_NONE)GXColor4u8(tevColor1.r,tevColor1.g,tevColor1.b,tevColor1.a);
        if(texEnabled)GXTexCoord2f32(tevProbeU+(i==1?tevProbeSpan:0),tevProbeV);
        for(int t=0;t<7;++t)if(extraTex[t].descriptor!=GX_NONE){if(extraTex[t].descriptor==GX_INDEX8)GXTexCoord1x8(0);else if(extraTex[t].descriptor==GX_INDEX16)GXTexCoord1x16(257);else GXTexCoord2f32(tevExtraUV[t][0],tevExtraUV[t][1]);}
    }GXEnd();
}
bool testTev(IDirect3DQuery9* query,u8 value,int channel,GXColor vertex,bool visible=true){
    tevProbeChannel=(float)channel;GXSetAlphaCompare(GX_EQUAL,value,GX_AOP_AND,GX_ALWAYS,0);
    require(SUCCEEDED(query->Issue(D3DISSUE_BEGIN)));drawTevTriangle(vertex);
    require(SUCCEEDED(query->Issue(D3DISSUE_END)));device->BlockUntilIdle();DWORD pixels=0;HRESULT hr;unsigned int tries=0;
    do{hr=query->GetData(&pixels,4,D3DGETDATA_FLUSH);if(hr==S_FALSE)Sleep(1);}while(hr==S_FALSE&&++tries<10000);
    ++tevProbeCases;if(hr!=S_OK||((pixels!=0)!=visible)){char m[160];sprintf_s(m,sizeof(m),"TEV GPU FAILED: case=%u expected=%u channel=%d pixels=%u HRESULT=%08x\n",tevProbeCases,value,channel,pixels,hr);Melee360Log(m);return false;}return true;
}
void passthroughTev(){initializeTev();GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD0,GX_TEXMAP_NULL,GX_COLOR0A0);GXSetTevOp(GX_TEVSTAGE0,GX_PASSCLR);}

}
extern "C" int Melee360GXTevProbe(void){
    require(device&&!__GXinBegin);TevState saved=tev;float first[4],second[4];memcpy(first,alphaFirst,16);memcpy(second,alphaSecond,16);
    IDirect3DQuery9* query=0;require(SUCCEEDED(device->CreateQuery(D3DQUERYTYPE_OCCLUSION,&query))&&query);bool ok=true;tevProbeCases=0;
    GXColor vertex={37,91,173,211};GXColor registers[4]={{19,43,71,103},{23,59,97,131},{29,67,113,149},{31,79,137,167}};
    // Every input selector, exercising independent RGB and alpha outputs.
    for(int arg=0;arg<16&&ok;++arg){passthroughTev();for(int r=0;r<4;++r)GXSetTevColor((GXTevRegID)r,registers[r]);
        GXColor k={47,89,127,181};GXSetTevKColor(GX_KCOLOR0,k);GXSetTevKColorSel(GX_TEVSTAGE0,GX_TEV_KCSEL_K0);
        GXSetTevColorIn(GX_TEVSTAGE0,GX_CC_ZERO,GX_CC_ZERO,GX_CC_ZERO,(GXTevColorArg)arg);
        for(int c=0;c<3&&ok;++c){u8 expected=arg<8?((u8*)&registers[arg/2])[arg&1?3:c]:arg==8||arg==9?255:arg==10?((u8*)&vertex)[c]:arg==11?vertex.a:arg==12?255:arg==13?128:arg==14?((u8*)&k)[c]:0;ok=testTev(query,expected,c+1,vertex);}
    }
    for(int arg=0;arg<8&&ok;++arg){passthroughTev();for(int r=0;r<4;++r)GXSetTevColor((GXTevRegID)r,registers[r]);GXColor k={47,89,127,181};GXSetTevKColor(GX_KCOLOR0,k);GXSetTevKAlphaSel(GX_TEVSTAGE0,GX_TEV_KASEL_K0_A);
        GXSetTevAlphaIn(GX_TEVSTAGE0,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO,(GXTevAlphaArg)arg);ok=testTev(query,arg<4?registers[arg].a:arg==4?255:arg==5?vertex.a:arg==6?181:0,0,vertex);
    }
    // Chaining and output destinations: all 16 stages, RGB/alpha can target different registers.
    for(int count=1;count<=16&&ok;++count){passthroughTev();GXSetNumTevStages((u8)count);GXColor seed={3,3,3,3};GXSetTevColor(GX_TEVPREV,seed);GXColor one={1,1,1,1};GXSetTevKColor(GX_KCOLOR0,one);
        for(int s=0;s<count;++s){GXSetTevOrder((GXTevStageID)s,GX_TEXCOORD0,GX_TEXMAP_NULL,GX_COLOR0A0);GXSetTevKColorSel((GXTevStageID)s,GX_TEV_KCSEL_K0);GXSetTevKAlphaSel((GXTevStageID)s,GX_TEV_KASEL_K0_A);
            GXSetTevColorIn((GXTevStageID)s,GX_CC_KONST,GX_CC_ZERO,GX_CC_ZERO,GX_CC_CPREV);GXSetTevAlphaIn((GXTevStageID)s,GX_CA_KONST,GX_CA_ZERO,GX_CA_ZERO,GX_CA_APREV);
            GXSetTevColorOp((GXTevStageID)s,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,1,GX_TEVPREV);GXSetTevAlphaOp((GXTevStageID)s,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,1,GX_TEVPREV);
        }ok=testTev(query,(u8)(3+count),0,vertex)&&testTev(query,(u8)(3+count),1,vertex);
    }
    for(int dest=0;dest<4&&ok;++dest){passthroughTev();GXSetNumTevStages(2);GXSetTevColorOp(GX_TEVSTAGE0,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,1,(GXTevRegID)dest);GXSetTevAlphaOp(GX_TEVSTAGE0,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,1,(GXTevRegID)((dest+1)&3));
        GXSetTevColorIn(GX_TEVSTAGE1,GX_CC_ZERO,GX_CC_ZERO,GX_CC_ZERO,(GXTevColorArg)(dest*2));GXSetTevAlphaIn(GX_TEVSTAGE1,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO,(GXTevAlphaArg)((dest+1)&3));
        GXSetTevColorOp(GX_TEVSTAGE1,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,1,GX_TEVREG2);GXSetTevAlphaOp(GX_TEVSTAGE1,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,1,GX_TEVREG1);
        ok=testTev(query,37,1,vertex)&&testTev(query,211,0,vertex);
    }
    // Exact integer add/subtract, three biases, four scales and clamped/unclamped output.
    for(int sub=0;sub<2&&ok;++sub)for(int bias=0;bias<3&&ok;++bias)for(int scale=0;scale<4&&ok;++scale)for(int cl=0;cl<2&&ok;++cl){
        passthroughTev();GXColor a={23,23,23,23},b={179,179,179,179},c={137,137,137,137};GXColorS10 d={-17,-17,-17,-17};GXSetTevColor(GX_TEVPREV,a);GXSetTevColor(GX_TEVREG0,b);GXSetTevColor(GX_TEVREG1,c);GXSetTevColorS10(GX_TEVREG2,d);
        GXSetTevColorIn(GX_TEVSTAGE0,GX_CC_CPREV,GX_CC_C0,GX_CC_C1,GX_CC_C2);GXSetTevAlphaIn(GX_TEVSTAGE0,GX_CA_APREV,GX_CA_A0,GX_CA_A1,GX_CA_A2);
        GXSetTevColorOp(GX_TEVSTAGE0,(GXTevOp)sub,(GXTevBias)bias,(GXTevScale)scale,(GXBool)cl,GX_TEVPREV);GXSetTevAlphaOp(GX_TEVSTAGE0,(GXTevOp)sub,(GXTevBias)bias,(GXTevScale)scale,(GXBool)cl,GX_TEVPREV);
        int factor=scale==3?1:1<<scale;int mixed=(23*256+(179-23)*138)*factor+(scale==3?0:sub?127:128);int value=(-17+(bias==1?128:bias==2?-128:0))*factor+(sub?-(mixed>>8):(mixed>>8));if(scale==3)value>>=1;
        if(cl){if(value<0)value=0;if(value>255)value=255;}else{if(value< -1024)value=-1024;if(value>1023)value=1023;}
        ok=testTev(query,(u8)value,0,vertex)&&testTev(query,(u8)value,1,vertex);
    }
    for(int selection=0;selection<32&&ok;++selection){passthroughTev();
        GXColor ks[4]={{13,31,61,127},{17,37,71,137},{19,43,79,149},{23,47,89,163}};for(int k=0;k<4;++k)GXSetTevKColor((GXTevKColorID)k,ks[k]);
        GXSetTevKColorSel(GX_TEVSTAGE0,(GXTevKColorSel)selection);GXSetTevColorIn(GX_TEVSTAGE0,GX_CC_ZERO,GX_CC_ZERO,GX_CC_ZERO,GX_CC_KONST);
        for(int c=0;c<3&&ok;++c){int expected=selection<8?(int)((8-selection)*255/8.0+.5):selection<12?0:selection<16?((u8*)&ks[selection-12])[c]:((u8*)&ks[(selection-16)%4])[(selection-16)/4];ok=testTev(query,(u8)expected,c+1,vertex);}
        {GXSetTevKAlphaSel(GX_TEVSTAGE0,(GXTevKAlphaSel)selection);GXSetTevAlphaIn(GX_TEVSTAGE0,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO,GX_CA_KONST);int expected=selection<8?(int)((8-selection)*255/8.0+.5):selection<16?0:((u8*)&ks[(selection-16)%4])[(selection-16)/4];ok=ok&&testTev(query,(u8)expected,0,vertex);}
    }
    // All swap components and both packed/per-component comparisons (true and false).
    for(int table=0;table<4&&ok;++table){passthroughTev();GXSetTevSwapModeTable((GXTevSwapSel)table,(GXTevColorChan)table,(GXTevColorChan)((table+1)&3),(GXTevColorChan)((table+2)&3),(GXTevColorChan)((table+3)&3));GXSetTevSwapMode(GX_TEVSTAGE0,(GXTevSwapSel)table,GX_TEV_SWAP0);
        for(int c=0;c<4&&ok;++c)ok=testTev(query,((u8*)&vertex)[(table+c)&3],c==3?0:c+1,vertex);
    }
    for(int op=8;op<16&&ok;++op)for(int equal=0;equal<2&&ok;++equal){passthroughTev();GXColor a={30,50,70,90},b={30,50,70,90},c={11,17,23,29},d={3,5,7,9};if(!equal){b.r=20;b.g=60;b.b=60;b.a=100;}
        GXSetTevColor(GX_TEVPREV,a);GXSetTevColor(GX_TEVREG0,b);GXSetTevColor(GX_TEVREG1,c);GXSetTevColor(GX_TEVREG2,d);
        GXSetTevColorIn(GX_TEVSTAGE0,GX_CC_CPREV,GX_CC_C0,GX_CC_C1,GX_CC_C2);GXSetTevAlphaIn(GX_TEVSTAGE0,GX_CA_APREV,GX_CA_A0,GX_CA_A1,GX_CA_A2);GXSetTevColorOp(GX_TEVSTAGE0,(GXTevOp)op,GX_TB_ZERO,GX_CS_SCALE_1,1,GX_TEVPREV);GXSetTevAlphaOp(GX_TEVSTAGE0,(GXTevOp)op,GX_TB_ZERO,GX_CS_SCALE_1,1,GX_TEVPREV);
        int packedA=op<10?a.r:op<12?a.r+256*a.g:a.r+256*a.g+65536*a.b;int packedB=op<10?b.r:op<12?b.r+256*b.g:b.r+256*b.g+65536*b.b;
        for(int channel=0;channel<4&&ok;++channel){bool pass=op<14?((op&1)?packedA==packedB:packedA>packedB):((op&1)?((u8*)&a)[channel]==((u8*)&b)[channel]:((u8*)&a)[channel]>((u8*)&b)[channel]);ok=testTev(query,((u8*)&d)[channel]+(pass?((u8*)&c)[channel]:0),channel==3?0:channel+1,vertex);}
    }
    // Spatial indirect tests use an original GX-tiled gradient and an independent offset texture.
    IDirect3DTexture9* textures[2]={loadedTextures[0],loadedTextures[1]};GXTexObj descriptors[2]={boundDescriptors[0],boundDescriptors[1]};std::vector<u8> images[2]={boundImages[0],boundImages[1]};bool valid[2]={boundValid[0],boundValid[1]};const u8* sources[2]={boundSources[0],boundSources[1]};float lods[2][4],biases[2];
    static const D3DSAMPLERSTATETYPE samplerStates[]={D3DSAMP_ADDRESSU,D3DSAMP_ADDRESSV,D3DSAMP_MINFILTER,D3DSAMP_MAGFILTER,D3DSAMP_MIPFILTER,D3DSAMP_MAXMIPLEVEL,D3DSAMP_MINMIPLEVEL,D3DSAMP_MIPMAPLODBIAS,D3DSAMP_MAXANISOTROPY};DWORD samplerValues[2][9];
    for(int slot=0;slot<2;++slot){loadedTextures[slot]=0;boundValid[slot]=false;memcpy(lods[slot],textureLod[slot],16);biases[slot]=textureBias[slot];for(int i=0;i<9;++i)device->GetSamplerState(slot,samplerStates[i],&samplerValues[slot][i]);}
    __declspec(align(32)) static u8 gradient[512*4*4],displacement[64];GXTexObj texObj,indObj;
    for(int y=0;y<4;++y)for(int x=0;x<512;++x){unsigned int tile=x/4,index=(y*4+x%4)*2;u8* p=gradient+tile*64;p[index]=199;p[index+1]=(u8)(x%251);p[32+index]=(u8)(y*47);p[33+index]=127;}
    for(int i=0;i<16;++i){displacement[i*2]=64;displacement[i*2+1]=17;displacement[32+i*2]=32;displacement[33+i*2]=96;}
    GXInitTexObj(&texObj,gradient,512,4,GX_TF_RGBA8,GX_CLAMP,GX_CLAMP,0);GXInitTexObjLOD(&texObj,GX_NEAR,GX_NEAR,0,0,0,0,1,GX_ANISO_1);GXLoadTexObj(&texObj,GX_TEXMAP0);
    GXInitTexObj(&indObj,displacement,4,4,GX_TF_RGBA8,GX_CLAMP,GX_CLAMP,0);GXInitTexObjLOD(&indObj,GX_NEAR,GX_NEAR,0,0,0,0,1,GX_ANISO_1);GXLoadTexObj(&indObj,GX_TEXMAP1);
    for(int format=0;format<4&&ok;++format)for(int bias=0;bias<8&&ok;++bias){
        passthroughTev();GXSetNumIndStages(1);GXSetIndTexOrder(GX_INDTEXSTAGE0,GX_TEXCOORD0,GX_TEXMAP1);float m[2][3]={{.5f,0,0},{0,0,0}};GXSetIndTexMtx(GX_ITM_0,m,0);
        GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD0,GX_TEXMAP0,GX_COLOR0A0);GXSetTevOp(GX_TEVSTAGE0,GX_REPLACE);GXSetTevIndirect(GX_TEVSTAGE0,GX_INDTEXSTAGE0,(GXIndTexFormat)format,(GXIndTexBiasSel)bias,GX_ITM_0,GX_ITW_OFF,GX_ITW_OFF,0,0,GX_ITBA_OFF);
        int v=format==0?64:64/(format==1?8:format==2?16:32);if(bias&1)v+=format==0?-128:1;int x=256+v/2;if(x<0)x=0;if(x>511)x=511;ok=testTev(query,(u8)(x%251),1,vertex);
    }
    for(int wrap=0;wrap<7&&ok;++wrap)for(int pos=0;pos<3&&ok;++pos){passthroughTev();GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD0,GX_TEXMAP0,GX_COLOR0A0);GXSetTevOp(GX_TEVSTAGE0,GX_REPLACE);
        GXSetTevIndirect(GX_TEVSTAGE0,GX_INDTEXSTAGE0,GX_ITF_8,GX_ITB_NONE,GX_ITM_OFF,(GXIndTexWrap)wrap,GX_ITW_OFF,0,0,GX_ITBA_OFF);
        int x=288+pos*37;tevProbeU=(x+.25f)/512;if(wrap==6)x=0;else if(wrap)x%=1<<(9-wrap);ok=testTev(query,(u8)(x%251),1,vertex);
    }tevProbeU=.5f;
    for(int id=1;id<=11&&ok;++id){if(id==4||id==8)continue;passthroughTev();GXSetNumIndStages(1);GXSetIndTexOrder(GX_INDTEXSTAGE0,GX_TEXCOORD0,GX_TEXMAP1);float m[2][3]={{.015625f,0,0},{0,0,0}};GXSetIndTexMtx((GXIndTexMtxID)id,m,0);
        GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD0,GX_TEXMAP0,GX_COLOR0A0);GXSetTevOp(GX_TEVSTAGE0,GX_REPLACE);GXSetTevIndirect(GX_TEVSTAGE0,GX_INDTEXSTAGE0,GX_ITF_8,GX_ITB_NONE,(GXIndTexMtxID)id,GX_ITW_OFF,GX_ITW_OFF,0,0,GX_ITBA_OFF);
        int x=id<4?257:id<8?320:352;ok=testTev(query,(u8)(x%251),1,vertex);
    }
    for(int format=0;format<4&&ok;++format)for(int component=1;component<4&&ok;++component)for(int normal=0;normal<2&&ok;++normal){
        passthroughTev();GXSetNumIndStages(1);GXSetIndTexOrder(GX_INDTEXSTAGE0,GX_TEXCOORD0,GX_TEXMAP1);GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD0,GX_TEXMAP_NULL,normal?GX_ALPHA_BUMPN:GX_ALPHA_BUMP);
        GXSetTevIndirect(GX_TEVSTAGE0,GX_INDTEXSTAGE0,(GXIndTexFormat)format,GX_ITB_NONE,GX_ITM_OFF,GX_ITW_OFF,GX_ITW_OFF,0,0,(GXIndTexAlphaSel)component);
        int v=component==1?64:component==2?96:32;v=format==0?v&248:(v<<(format==1?5:format==2?4:3))&255;if(normal)v+=v>>5;
        ok=testTev(query,(u8)v,0,vertex)&&testTev(query,(u8)v,1,vertex);
    }
    // Add previous and then explicitly reset the same stage to direct.
    if(ok){passthroughTev();GXSetNumTevStages(2);for(int s=0;s<2;++s){GXSetTevOrder((GXTevStageID)s,GX_TEXCOORD0,GX_TEXMAP0,GX_COLOR0A0);GXSetTevOp((GXTevStageID)s,GX_REPLACE);}GXSetTevIndirect(GX_TEVSTAGE1,GX_INDTEXSTAGE0,GX_ITF_8,GX_ITB_NONE,GX_ITM_OFF,GX_ITW_OFF,GX_ITW_OFF,1,0,GX_ITBA_OFF);ok=testTev(query,(u8)(511%251),1,vertex);GXSetTevDirect(GX_TEVSTAGE1);ok=ok&&testTev(query,5,1,vertex);}
    // All indirect stage slots and coordinate-scale encodings, with a spatially varying source.
    for(int y=0;y<4;++y)for(int x=0;x<4;++x)displacement[(y*4+x)*2]=(u8)(16+x*32+y*16);
    GXLoadTexObj(&indObj,GX_TEXMAP1);
    for(int slot=0;slot<4&&ok;++slot)for(int axis=0;axis<2&&ok;++axis)for(int scale=0;scale<9&&ok;++scale){
        passthroughTev();GXSetNumIndStages(4);GXSetIndTexOrder((GXIndTexStageID)slot,GX_TEXCOORD0,GX_TEXMAP1);
        GXSetIndTexCoordScale((GXIndTexStageID)slot,(GXIndTexScale)(axis?0:scale),(GXIndTexScale)(axis?scale:0));
        float matrix[2][3]={{.5f,0,0},{0,0,0}};GXSetIndTexMtx(GX_ITM_0,matrix,0);
        GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD0,GX_TEXMAP0,GX_COLOR0A0);GXSetTevOp(GX_TEVSTAGE0,GX_REPLACE);
        GXSetTevIndirect(GX_TEVSTAGE0,(GXIndTexStageID)slot,GX_ITF_8,GX_ITB_NONE,GX_ITM_0,GX_ITW_OFF,GX_ITW_OFF,0,0,GX_ITBA_OFF);
        int x=axis?2:2>>scale,y=axis?2>>scale:2;ok=ok&&testTev(query,(u8)((256+(16+x*32+y*16)/2)%251),1,vertex);
    }
    for(int i=0;i<16;++i)displacement[i*2]=64;GXLoadTexObj(&indObj,GX_TEXMAP1);
    // Exercise the original SDK convenience bodies against the actual shader backend.
    for(int helper=0;helper<12&&ok;++helper){
        passthroughTev();GXSetNumIndStages(1);GXSetIndTexOrder(GX_INDTEXSTAGE0,GX_TEXCOORD0,GX_TEXMAP1);
        float matrix[2][3]={{.5f,0,0},{0,0,0}};GXSetIndTexMtx(GX_ITM_0,matrix,0);int expected=0;
        int count=helper==9?3:helper==11?2:1;GXSetNumTevStages((u8)count);
        for(int stage=0;stage<count;++stage){GXSetTevOrder((GXTevStageID)stage,GX_TEXCOORD0,GX_TEXMAP0,GX_COLOR0A0);GXSetTevOp((GXTevStageID)stage,GX_REPLACE);}
        if(helper<4){int signedOffset=helper&1,replace=helper>>1;GXSetTevIndWarp(GX_TEVSTAGE0,GX_INDTEXSTAGE0,(u8)signedOffset,(u8)replace,GX_ITM_0);expected=(replace?0:256)+(signedOffset?-32:32);if(expected<0)expected=0;}
        else if(helper<9){u16 size=(u16)(16<<(helper-4));GXSetTevIndTile(GX_TEVSTAGE0,GX_INDTEXSTAGE0,size,size,1,1,GX_ITF_8,GX_ITM_0,GX_ITB_NONE,GX_ITBA_OFF);expected=64;}
        else if(helper==9){GXSetTevIndBumpST(GX_TEVSTAGE0,GX_INDTEXSTAGE0,GX_ITM_0);expected=160;}
        else if(helper==10){matrix[0][0]=.015625f;GXSetIndTexMtx(GX_ITM_0,matrix,0);GXSetTevIndBumpXYZ(GX_TEVSTAGE0,GX_INDTEXSTAGE0,GX_ITM_0);expected=255;}
        else{GXSetTevIndWarp(GX_TEVSTAGE0,GX_INDTEXSTAGE0,0,0,GX_ITM_0);GXSetTevIndRepeat(GX_TEVSTAGE1);expected=288;}
        ok=ok&&testTev(query,(u8)(expected%251),1,vertex);
    }
    // Indirect wrapping removes derivatives; unmodified-LOD must preserve the original ones.
    __declspec(align(32)) static u8 lodImage[160];memset(lodImage,0,128);memset(lodImage+128,255,32);
    GXInitTexObj(&texObj,lodImage,8,8,GX_TF_RGB5A3,GX_CLAMP,GX_CLAMP,1);GXInitTexObjLOD(&texObj,GX_NEAR_MIP_NEAR,GX_NEAR,0,1,0,0,1,GX_ANISO_1);GXLoadTexObj(&texObj,GX_TEXMAP0);
    tevProbeSpan=128;
    for(int originalLod=0;originalLod<2&&ok;++originalLod){
        passthroughTev();GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD0,GX_TEXMAP0,GX_COLOR0A0);GXSetTevOp(GX_TEVSTAGE0,GX_REPLACE);
        GXSetTevIndirect(GX_TEVSTAGE0,GX_INDTEXSTAGE0,GX_ITF_8,GX_ITB_NONE,GX_ITM_OFF,GX_ITW_0,GX_ITW_0,0,(GXBool)originalLod,GX_ITBA_OFF);
        ok=ok&&testTev(query,originalLod?255:0,0,vertex);
    }
    tevProbeSpan=0;
    GXInitTexObj(&texObj,gradient,512,4,GX_TF_RGBA8,GX_CLAMP,GX_CLAMP,0);GXInitTexObjLOD(&texObj,GX_NEAR,GX_NEAR,0,0,0,0,1,GX_ANISO_1);GXLoadTexObj(&texObj,GX_TEXMAP0);
    // Independent depth comparisons validate the exported value, without a diagnostic branch in PSDepth.
    DWORD oldZEnable,oldZWrite,oldZFunc,oldHiZ,oldHiZWrite;
    device->GetRenderState(D3DRS_HIZENABLE,&oldHiZ);device->GetRenderState(D3DRS_HIZWRITEENABLE,&oldHiZWrite);
    device->SetRenderState(D3DRS_HIZENABLE,D3DHIZ_DISABLE);device->SetRenderState(D3DRS_HIZWRITEENABLE,D3DHIZ_ENABLE);
    device->GetRenderState(D3DRS_ZENABLE,&oldZEnable);device->GetRenderState(D3DRS_ZWRITEENABLE,&oldZWrite);device->GetRenderState(D3DRS_ZFUNC,&oldZFunc);
    D3DVIEWPORT9 savedViewport;device->GetViewport(&savedViewport);D3DVIEWPORT9 testViewport={0,0,1280,720,0,1};device->SetViewport(&testViewport);
    float originalProjection[7];GXGetProjectionv(originalProjection);const GXTexFmt zFormats[3]={GX_TF_Z8,GX_TF_Z16,GX_TF_Z24X8};
    for(int format=0;format<3&&ok;++format)for(int add=0;add<2&&ok;++add)for(int wrap=0;wrap<2&&ok;++wrap){
        passthroughTev();GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD0,GX_TEXMAP1,GX_COLOR0A0);GXSetTevOp(GX_TEVSTAGE0,GX_REPLACE);
        unsigned int packed=format==0?64:format==1?64*256+17:17*65536+32*256+96,bias=wrap?0xffff00:0x400000,value=(packed+bias+(add?0x400000:0))&0xffffff;
        float projection[4][4]={{1,0,0,0},{0,1,0,0},{0,0,0,-.75f},{0,0,0,1}};GXSetProjection(projection,GX_ORTHOGRAPHIC);
        if(format==0&&!add&&!wrap){
            GXSetZTexture(GX_ZT_DISABLE,GX_TF_Z8,0);require(SUCCEEDED(device->Clear(0,0,D3DCLEAR_ZBUFFER,0,1,0)));
            GXSetZMode(1,GX_ALWAYS,1);tevProbeChannel=0;GXSetAlphaCompare(GX_EQUAL,64,GX_AOP_AND,GX_ALWAYS,0);drawTevTriangle(vertex);device->BlockUntilIdle();
            projection[2][3]=-.7501f;GXSetProjection(projection,GX_ORTHOGRAPHIC);GXSetZMode(1,GX_LESS,0);ok=ok&&testTev(query,64,0,vertex);
            projection[2][3]=-.7499f;GXSetProjection(projection,GX_ORTHOGRAPHIC);GXSetZMode(1,GX_GREATER,0);ok=ok&&testTev(query,64,0,vertex);
            projection[2][3]=-.75f;GXSetProjection(projection,GX_ORTHOGRAPHIC);
        }
        GXSetZTexture(add?GX_ZT_ADD:GX_ZT_REPLACE,zFormats[format],bias);require(SUCCEEDED(device->Clear(0,0,D3DCLEAR_ZBUFFER,0,1,0)));
        GXSetZMode(1,GX_ALWAYS,1);ok=ok&&testTev(query,64,0,vertex);GXSetZMode(1,GX_ALWAYS,1);drawTevTriangle(vertex);device->BlockUntilIdle();
        GXSetZTexture(GX_ZT_DISABLE,zFormats[format],0);
        for(int side=0;side<2&&ok;++side){
            projection[2][3]=(float)((int)value+(side?32:-32))/16777215.f-1.f;GXSetProjection(projection,GX_ORTHOGRAPHIC);
            GXSetZMode(1,side?GX_GREATER:GX_LESS,0);ok=ok&&testTev(query,64,0,vertex);
            GXSetZMode(1,side?GX_LESS:GX_GREATER,0);ok=ok&&testTev(query,64,0,vertex,false);
        }
    }
    device->SetViewport(&savedViewport);GXSetProjectionv(originalProjection);
    device->SetRenderState(D3DRS_ZENABLE,oldZEnable);device->SetRenderState(D3DRS_ZWRITEENABLE,oldZWrite);device->SetRenderState(D3DRS_ZFUNC,oldZFunc);
    device->SetRenderState(D3DRS_HIZENABLE,oldHiZ);device->SetRenderState(D3DRS_HIZWRITEENABLE,oldHiZWrite);
    ExtraInput savedExtraTex[7];memcpy(savedExtraTex,extraTex,sizeof(extraTex));ExtraInput savedExtraColor=extraColor;
    for(int t=0;t<7;++t){GXSetVtxDesc((GXAttr)(GX_VA_TEX1+t),GX_DIRECT);GXSetVtxAttrFmt(GX_VTXFMT0,(GXAttr)(GX_VA_TEX1+t),GX_TEX_ST,GX_F32,0);tevExtraUV[t][0]=((t+1)*50+.25f)/512;tevExtraUV[t][1]=.5f;}
    GXSetVtxDesc(GX_VA_CLR1,GX_DIRECT);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR1,GX_CLR_RGBA,GX_RGBA8,0);
    for(int coord=0;coord<8&&ok;++coord){passthroughTev();GXSetTevOrder(GX_TEVSTAGE0,(GXTexCoordID)coord,GX_TEXMAP0,GX_COLOR0A0);GXSetTevOp(GX_TEVSTAGE0,GX_REPLACE);ok=testTev(query,(u8)((coord?coord*50:256)%251),1,vertex);}
    for(int channel=0;channel<6&&ok;++channel){passthroughTev();GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD0,GX_TEXMAP_NULL,(GXChannelID)channel);for(int c=0;c<4&&ok;++c)ok=testTev(query,((u8*)(channel&1?&tevColor1:&vertex))[c],c==3?0:c+1,vertex);}
    // Indexed extra UV and color/UV display-list byte order.
    float indexedUV[258*2]={0};indexedUV[0]=(305.25f)/512;indexedUV[1]=.5f;indexedUV[514]=(355.25f)/512;indexedUV[515]=.5f;
    for(int indexType=GX_INDEX8;indexType<=GX_INDEX16&&ok;++indexType){GXSetArray(GX_VA_TEX1,indexedUV,8);GXSetVtxDesc(GX_VA_TEX1,(GXAttrType)indexType);passthroughTev();GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD1,GX_TEXMAP0,GX_COLOR0A0);GXSetTevOp(GX_TEVSTAGE0,GX_REPLACE);ok=testTev(query,(u8)((indexType==GX_INDEX8?305:355)%251),1,vertex);}
    GXSetVtxDesc(GX_VA_TEX1,GX_DIRECT);
    u8 display[3+3*(12+8+8*8)]={GX_TRIANGLES,0,3};u8* at=display+3;
    for(int v=0;v<3;++v){float pos[3]={v==1?.2f:v==0?-.2f:0,v==2?.2f:-.2f,-1};memcpy(at,pos,12);at+=12;memcpy(at,&vertex,4);at+=4;memcpy(at,&tevColor1,4);at+=4;float uv[2]={.5f,.5f};memcpy(at,uv,8);at+=8;for(int t=0;t<7;++t){memcpy(at,tevExtraUV[t],8);at+=8;}}
    GXCallDisplayList(display,sizeof(display));char dlReport[180];sprintf_s(dlReport,sizeof(dlReport),"TEV display inputs: vertices=%u color1_r=%.9f expected=%.9f uv7=%.9f expected=%.9f\n",(unsigned int)vertices.size(),vertices[0].color1[0],61/255.f,vertices[0].extraUV[6][0],tevExtraUV[6][0]);Melee360Log(dlReport);require(vertices.size()==3&&fabs(vertices[0].color1[0]-61/255.f)<.000001f&&vertices[0].extraUV[6][0]==tevExtraUV[6][0]);
    memcpy(extraTex,savedExtraTex,sizeof(extraTex));extraColor=savedExtraColor;
    for(int slot=0;slot<2;++slot){releaseTexture(loadedTextures[slot]);loadedTextures[slot]=textures[slot];boundDescriptors[slot]=descriptors[slot];boundImages[slot]=images[slot];boundValid[slot]=valid[slot];boundSources[slot]=sources[slot];memcpy(textureLod[slot],lods[slot],16);textureBias[slot]=biases[slot];for(int i=0;i<9;++i)device->SetSamplerState(slot,samplerStates[i],samplerValues[slot][i]);}
    for(unsigned int i=0;i<textureImages.size();){if(textureImages[i].object==&texObj||textureImages[i].object==&indObj)textureImages.erase(textureImages.begin()+i);else ++i;}
    query->Release();tev=saved;tevProbeChannel=0;memcpy(alphaFirst,first,16);memcpy(alphaSecond,second,16);
    char message[128];sprintf_s(message,sizeof(message),"TEV GPU: %u GPU cases; direct/indirect TEV, 16 stages, 8 UVs, 2 colors and Z texture %s\n",tevProbeCases,ok?"passed":"FAILED");Melee360Log(message);return ok;
}
