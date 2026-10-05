extern "C" int Melee360GXFogProbe(void){
    require(device&&!__GXinBegin);IDirect3DStateBlock9* saved=0;IDirect3DSurface9 *oldTarget=0,*oldDepth=0,*target=0;D3DVIEWPORT9 viewport;
    require(SUCCEEDED(device->CreateStateBlock(D3DSBT_ALL,&saved))&&SUCCEEDED(saved->Capture()));device->GetRenderTarget(0,&oldTarget);device->GetDepthStencilSurface(&oldDepth);device->GetViewport(&viewport);
    float oldGXViewport[6];GXGetViewportv(oldGXViewport);u32 oldFog[11];memcpy(oldFog,fogRegisters,sizeof(oldFog));
    TevState oldTev=tev;float first[4],second[4];memcpy(first,alphaFirst,16);memcpy(second,alphaSecond,16);IDirect3DTexture9* oldImage=loadedTextures[0];loadedTextures[0]=0;
    D3DSURFACE_PARAMETERS params={0};params.Base=1800;require(SUCCEEDED(device->CreateRenderTarget(64,64,D3DFMT_A8R8G8B8,D3DMULTISAMPLE_NONE,0,FALSE,&target,&params)));
    IDirect3DTexture9* image=0;require(SUCCEEDED(device->CreateTexture(64,64,1,0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&image,0)));
    device->SetDepthStencilSurface(0);device->SetRenderTarget(0,target);GXSetViewport(0,0,64,64,0,1);device->SetRenderState(D3DRS_ZENABLE,FALSE);device->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);device->SetRenderState(D3DRS_SCISSORTESTENABLE,FALSE);device->SetRenderState(D3DRS_COLORWRITEENABLE,15);
    initializeTev();GXSetTevOp(GX_TEVSTAGE0,GX_PASSCLR);GXSetAlphaCompare(GX_ALWAYS,0,GX_AOP_AND,GX_ALWAYS,0);
    GXFogAdjTable table;float projection[4][4]={{1,0,0,0},{0,1,0,0},{0,0,0,-1},{0,0,-1,0}};
    GXInitFogAdjTable(&table,640,projection);const u16 expectedTable[]={257,261,267,275,286,298,312,327,344,362};bool ok=true;unsigned cpu=0,gpu=0;
    for(int i=0;i<10;++i){ok=ok&&table.r[i]==expectedTable[i];++cpu;}
    GXColor black={0,0,0,0};GXSetFogRangeAdj(GX_FALSE,0,0);
    const GXFogType kinds[]={GX_FOG_NONE,GX_FOG_LIN,GX_FOG_EXP,GX_FOG_EXP2,GX_FOG_REVEXP,GX_FOG_REVEXP2};const float distances[]={1,2,4,8,16,32,64};
    for(int test=0;test<100&&ok;++test){int path=test<84?(test/42):0,mode=test<84?(test%42)/7:1;float distance=test<84?distances[test%7]:8;
        bool range=test>=84&&test<98;float rangeFactor=range&&(test&1)?2.f:1.f;
        for(int i=0;i<10;++i)table.r[i]=(u16)(rangeFactor*256);GXSetFogRangeAdj(range?GX_TRUE:GX_FALSE,0,range?&table:0);
        GXFogType kind=kinds[mode];if(test>=98)kind=GX_FOG_NONE;GXSetFog(kind,2,16,1,64,black);
        // Invert the original perspective projection to obtain an independent expected eye distance.
        float z=64*(distance-1)/(distance*63);u32 z24=(u32)floor(z*16777215+.5f);if(z24>0xffffff)z24=0xffffff;GXSetZTexture(path?GX_ZT_REPLACE:GX_ZT_DISABLE,GX_TF_Z24X8,(z24-0xffffff)&0xffffff);
        Vertex quad[6];memset(quad,0,sizeof(quad));const float xy[6][2]={{-.25f,.25f},{.25f,.25f},{-.25f,-.25f},{-.25f,-.25f},{.25f,.25f},{.25f,-.25f}};
        for(int v=0;v<6;++v){for(unsigned unit=0;unit<8;++unit)vertexTex(quad[v],unit)[2]=1;quad[v].clip[0]=xy[v][0];quad[v].clip[1]=xy[v][1];quad[v].clip[2]=path?.5f:z;quad[v].clip[3]=1;for(int c=0;c<3;++c)quad[v].color[c]=1;quad[v].color[3]=128/255.f;}
        device->Clear(0,0,D3DCLEAR_TARGET,0,1,0);bindDirectPipeline();require(SUCCEEDED(device->DrawPrimitiveUP(D3DPT_TRIANGLELIST,2,quad,sizeof(Vertex))));
        require(SUCCEEDED(device->Resolve(D3DRESOLVE_RENDERTARGET0,0,image,0,0,0,0,1.f,0,0)));device->BlockUntilIdle();D3DLOCKED_RECT lock;require(SUCCEEDED(image->LockRect(0,&lock,0,D3DLOCK_READONLY)));
        u8 pixel[4]={0};RECT region={32,32,33,33};XGUntileTextureLevel(64,64,0,XGGetGpuFormat(D3DFMT_A8R8G8B8),0,pixel,4,0,lock.pBits,&region);unsigned actual=pixel[1];bool alpha=pixel[0]==128||pixel[3]==128;image->UnlockRect(0);
        float amount=(distance*rangeFactor-2)/14;if(amount<0)amount=0;if(amount>1)amount=1;
        if(kind==GX_FOG_NONE)amount=0;else if(kind==GX_FOG_EXP)amount=1-powf(2,-8*amount);else if(kind==GX_FOG_EXP2)amount=1-powf(2,-8*amount*amount);
        else if(kind==GX_FOG_REVEXP)amount=powf(2,-8*(1-amount));else if(kind==GX_FOG_REVEXP2)amount=powf(2,-8*(1-amount)*(1-amount));
        unsigned wanted=(unsigned)floor(255*(256-floor(amount*256+.5f))/256);int error=(int)actual-(int)wanted;
        if(error<-2||error>2||!alpha){char message[192];sprintf_s(message,sizeof(message),"GX fog FAILED: case=%d mode=%d path=%d actual=%u expected=%u alpha=%d\n",test,(int)kind,path,actual,wanted,alpha);Melee360Log(message);ok=false;}++gpu;
    }
    device->SetRenderTarget(0,oldTarget);device->SetDepthStencilSurface(oldDepth);GXSetViewport(oldGXViewport[0],oldGXViewport[1],oldGXViewport[2],oldGXViewport[3],oldGXViewport[4],oldGXViewport[5]);saved->Apply();device->SetViewport(&viewport);device->BlockUntilIdle();
    image->Release();target->Release();saved->Release();oldTarget->Release();if(oldDepth)oldDepth->Release();memcpy(fogRegisters,oldFog,sizeof(oldFog));tev=oldTev;memcpy(alphaFirst,first,16);memcpy(alphaSecond,second,16);loadedTextures[0]=oldImage;
    if(ok){char message[192];sprintf_s(message,sizeof(message),"GX fog: %u original table checks and %u GPU color/depth/range/alpha cases passed; range subpixel accuracy unverified\n",cpu,gpu);Melee360Log(message);}return ok;
}
