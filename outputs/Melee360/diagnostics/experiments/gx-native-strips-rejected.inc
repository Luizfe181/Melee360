    // D3D and GX strips share alternating winding. Keep the list path when
    // early-depth emulation needs to process individual triangles.
    static const bool expandStrips=GetFileAttributesA("game:\\gx-expand-strips.flag")!=((DWORD)-1);
    if(activePrimitive==GX_TRIANGLESTRIP&&!expandStrips){
        DWORD enabled=0,write=0;device->GetRenderState(D3DRS_ZENABLE,&enabled);device->GetRenderState(D3DRS_ZWRITEENABLE,&write);
        if(!earlyDepth||!enabled||!write||(!depthTextureActive()&&alphaCannotDiscard())){
            avoidedCopyBytes+=(unsigned __int64)(expected-2)*3*sizeof(Vertex);
            require(SUCCEEDED(drawLate(D3DPT_TRIANGLESTRIP,expected-2,&vertices[0],sizeof(Vertex))));primitiveActive=false;return;
        }
    }

