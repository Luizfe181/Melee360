extern "C" int Melee360GXRasterProbe(void){
    require(device&&!__GXinBegin);IDirect3DStateBlock9* saved=0;IDirect3DSurface9 *oldTarget=0,*oldDepth=0,*target=0;D3DVIEWPORT9 viewport;
    require(SUCCEEDED(device->CreateStateBlock(D3DSBT_ALL,&saved))&&SUCCEEDED(saved->Capture()));device->GetRenderTarget(0,&oldTarget);device->GetDepthStencilSurface(&oldDepth);device->GetViewport(&viewport);
    float oldGXViewport[6];GXGetViewportv(oldGXViewport);GXCullMode oldCull=(GXCullMode)Melee360GXCullMode();
    u8 oldLine=lineWidth,oldPoint=pointSize;GXTexOffset oldLineOffset=lineOffset,oldPointOffset=pointOffset;
    bool oldLineOffsets[8],oldPointOffsets[8];memcpy(oldLineOffsets,lineTexOffsets,8);memcpy(oldPointOffsets,pointTexOffsets,8);
    TevState oldTev=tev;float first[4],second[4];memcpy(first,alphaFirst,16);memcpy(second,alphaSecond,16);
    IDirect3DTexture9* oldTextures[8];for(int unit=0;unit<8;++unit){oldTextures[unit]=loadedTextures[unit];loadedTextures[unit]=0;GXEnableTexOffsets((GXTexCoordID)unit,0,0);}
    std::vector<Vertex> oldVertices=vertices,oldTriangles=triangleVertices;GXPrimitive oldPrimitive=activePrimitive;unsigned oldExpected=expected;bool oldActive=primitiveActive;
    D3DSURFACE_PARAMETERS params={0};params.Base=1800;require(SUCCEEDED(device->CreateRenderTarget(64,64,D3DFMT_A8R8G8B8,D3DMULTISAMPLE_NONE,0,FALSE,&target,&params)));
    device->SetDepthStencilSurface(0);device->SetRenderTarget(0,target);GXSetViewport(0,0,64,64,0,1);GXSetZMode(GX_FALSE,GX_ALWAYS,GX_FALSE);
    GXSetScissor(0,0,64,64);GXSetCullMode(GX_CULL_NONE);GXSetBlendMode(GX_BM_NONE,GX_BL_ONE,GX_BL_ZERO,GX_LO_COPY);
    device->SetRenderState(D3DRS_COLORWRITEENABLE,15);initializeTev();GXSetTevOp(GX_TEVSTAGE0,GX_PASSCLR);GXSetAlphaCompare(GX_ALWAYS,0,GX_AOP_AND,GX_ALWAYS,0);
    Vertex a;memset(&a,0,sizeof(a));for(unsigned unit=0;unit<8;++unit)vertexTex(a,unit)[2]=1;a.clip[2]=.5f;a.clip[3]=1;for(int c=0;c<4;++c)a.color[c]=a.color1[c]=1;
    unsigned cpuCases=0,gpuCases=0;bool ok=true;
    for(int offset=0;offset<6;++offset)for(unsigned unit=0;unit<8;++unit){
        for(unsigned i=0;i<8;++i)GXEnableTexOffsets((GXTexCoordID)i,i==unit,i==unit);
        GXSetPointSize(48,(GXTexOffset)offset);GXSetLineWidth(48,(GXTexOffset)offset);triangleVertices.clear();expandPoint(a,64,64);
        float delta=textureOffset((GXTexOffset)offset);for(unsigned i=0;i<8;++i){const float* tr=i?triangleVertices[1].extraUV[i-1]:triangleVertices[1].uv;const float* br=i?triangleVertices[5].extraUV[i-1]:triangleVertices[5].uv;
            ok=ok&&tr[0]==(i==unit?delta:0)&&tr[1]==0&&br[0]==(i==unit?delta:0)&&br[1]==(i==unit?delta:0);++cpuCases;}
        Vertex b=a;b.clip[0]=.5f;triangleVertices.clear();expandLine(a,b,64,64);
        for(unsigned i=0;i<8;++i){const float* right=i?triangleVertices[1].extraUV[i-1]:triangleVertices[1].uv;ok=ok&&right[0]==(i==unit?delta:0)&&right[1]==0;++cpuCases;}
    }
    for(unsigned i=0;i<8;++i)GXEnableTexOffsets((GXTexCoordID)i,0,0);
    IDirect3DQuery9* query=0;require(SUCCEEDED(device->CreateQuery(D3DQUERYTYPE_OCCLUSION,&query)));
    const u8 widths[]={0,6,12,48};
    for(int test=0;test<26&&ok;++test){unsigned width=widths[test%4]/6;GXSetLineWidth(widths[test%4],GX_TO_ZERO);GXSetPointSize(widths[test%4],GX_TO_ZERO);
        vertices.clear();expected=1;activePrimitive=GX_POINTS;vertices.push_back(a);unsigned wanted=width*width;
        if(test>=4&&test<12){activePrimitive=GX_LINES;expected=2;vertices.resize(2,a);unsigned axis=test<8?0:1;vertices[0].clip[axis]=-.5f;vertices[1].clip[axis]=.5f;wanted=32*width;}
        else if(test>=12&&test<16){activePrimitive=GX_LINESTRIP;expected=3;vertices.resize(3,a);for(int i=0;i<3;++i)vertices[i].clip[0]=-.5f+i*.5f;wanted=32*width;}
        else if(test>=16&&test<20){vertices[0].clip[3]=2;vertices[0].clip[2]=1;wanted=width*width;}
        else if(test>=20&&test<24){activePrimitive=GX_LINES;expected=2;vertices.resize(2,a);vertices[0].clip[0]=-.5f;vertices[0].clip[2]=-.5f;vertices[1].clip[0]=.5f;wanted=16*width;}
        else if(test==24){GXSetCullMode(GX_CULL_ALL);activePrimitive=GX_TRIANGLES;expected=3;vertices.resize(3,a);vertices[0].clip[0]=-.5f;vertices[0].clip[1]=-.5f;vertices[1].clip[0]=.5f;vertices[1].clip[1]=-.5f;vertices[2].clip[1]=.5f;wanted=0;}
        else if(test==25){GXSetCullMode(GX_CULL_ALL);GXSetPointSize(48,GX_TO_ZERO);wanted=64;}
        device->Clear(0,0,D3DCLEAR_TARGET,0,1,0);require(SUCCEEDED(query->Issue(D3DISSUE_BEGIN)));primitiveActive=true;submit();require(SUCCEEDED(query->Issue(D3DISSUE_END)));
        device->BlockUntilIdle();DWORD pixels=0;HRESULT result;unsigned attempt=0;do{result=query->GetData(&pixels,sizeof(pixels),D3DGETDATA_FLUSH);if(result==S_FALSE)Sleep(1);}while(result==S_FALSE&&++attempt<10000);
        if(result!=S_OK||pixels!=wanted){char message[192];sprintf_s(message,sizeof(message),"GX raster FAILED: case=%d pixels=%u expected=%u result=%08x\n",test,pixels,wanted,result);Melee360Log(message);ok=false;}++gpuCases;
    }
    query->Release();device->SetRenderTarget(0,oldTarget);device->SetDepthStencilSurface(oldDepth);GXSetViewport(oldGXViewport[0],oldGXViewport[1],oldGXViewport[2],oldGXViewport[3],oldGXViewport[4],oldGXViewport[5]);GXSetCullMode(oldCull);saved->Apply();device->SetViewport(&viewport);device->BlockUntilIdle();
    target->Release();saved->Release();oldTarget->Release();if(oldDepth)oldDepth->Release();lineWidth=oldLine;pointSize=oldPoint;lineOffset=oldLineOffset;pointOffset=oldPointOffset;memcpy(lineTexOffsets,oldLineOffsets,8);memcpy(pointTexOffsets,oldPointOffsets,8);
    for(unsigned i=0;i<8;++i)loadedTextures[i]=oldTextures[i];tev=oldTev;memcpy(alphaFirst,first,16);memcpy(alphaSecond,second,16);vertices=oldVertices;triangleVertices=oldTriangles;activePrimitive=oldPrimitive;expected=oldExpected;primitiveActive=oldActive;
    if(ok){char message[192];sprintf_s(message,sizeof(message),"GX raster: %u eight-unit UV offset checks and %u exact GPU coverage cases; points/lines/strip/clipping/cull passed\n",cpuCases,gpuCases);Melee360Log(message);}return ok;
}
