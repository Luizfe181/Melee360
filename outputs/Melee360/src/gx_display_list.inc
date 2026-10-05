namespace {
static unsigned int positionScalarSize(GXCompType type){return type==GX_F32?4:(type==GX_S16||type==GX_U16)?2:1;}
static float decodePositionScalar(const u8* p,GXCompType type,u8 frac){
    if(type==GX_F32){float value;memcpy(&value,p,4);return value;}
    int value=type==GX_S8?(int)(signed char)p[0]:type==GX_U8?(int)p[0]:type==GX_S16?(int)(short)((p[0]<<8)|p[1]):(int)((p[0]<<8)|p[1]);
    return value/(float)(1u<<frac);
}
}
/* CPU execution of primitive-only GX display lists. State opcodes remain
 * unsupported; preflight the complete command stream before any GPU draw. */
static unsigned int encodedColorSize(unsigned int fmt){
    if(!colorEnabled)return 0;
    if(colorDescriptor==GX_INDEX8)return 1;
    if(colorDescriptor==GX_INDEX16)return 2;
    return colorEncodedBytes(colorFormats[fmt].type);
}
static unsigned int encodedTexSize(unsigned int fmt){
    if(!texEnabled)return 0;
    if(texDescriptor==GX_INDEX8)return 1;
    if(texDescriptor==GX_INDEX16)return 2;
    return 2*positionScalarSize(texFormats[fmt].type);
}
extern "C" void GXCallDisplayList(void* list,u32 bytes){
    require(!__GXinBegin&&(list||!bytes));const u8* data=(const u8*)list;
    const bool measure=gxProfile.enabled&&gxProfile.detail;
    if(measure){++displayListProfile.calls;displayListProfile.bytes+=bytes;}
    for(int pass=0;pass<2;++pass){unsigned int at=0;
        GXDetailTimer passTimer(pass?&displayListProfile.executionTicks:&displayListProfile.preflightTicks);
        while(at<bytes){unsigned int op=data[at++];if(op==0)continue;
            unsigned int prim=op&0xf8,fmt=op&7;
            require(prim==GX_TRIANGLES||prim==GX_QUADS||prim==GX_TRIANGLESTRIP||prim==GX_TRIANGLEFAN||prim==GX_LINES||prim==GX_LINESTRIP||prim==GX_POINTS);
            require(bytes-at>=2&&positionEnabled&&posFormats[fmt].set&&(!colorEnabled||colorFormats[fmt].set)&&(!texEnabled||texFormats[fmt].set));
            validateExtraInputs(fmt);unsigned int count=(data[at]<<8)|data[at+1];at+=2;
            require(validPrimitive(prim,count));
            if(measure&&!pass){++displayListProfile.commands;displayListProfile.vertices+=count;}
            unsigned int components=posFormats[fmt].count==GX_POS_XY?2:3;
            unsigned int scalarSize=positionScalarSize(posFormats[fmt].type);
            unsigned int rawPositionSize=components*scalarSize;
            unsigned int psize=posDescriptor==GX_INDEX8?1:posDescriptor==GX_INDEX16?2:rawPositionSize;
            if(posDescriptor!=GX_DIRECT)require(posArray&&posStride>=rawPositionSize);
            unsigned int csize=encodedColorSize(fmt),tsize=encodedTexSize(fmt),stride=matrixIndexBytes()+psize+csize+tsize+(normalDescriptor==GX_NONE?0:normalDescriptor==GX_DIRECT?normalBytes(normalFormats[fmt].type)*(normalFormats[fmt].count==GX_NRM_XYZ?1:3):(normalDescriptor==GX_INDEX8?1:2)*(normalFormats[fmt].count==GX_NRM_NBT3?3:1));
            stride+=extraEncodedSize(extraColor,fmt,true);for(int input=0;input<7;++input)stride+=extraEncodedSize(extraTex[input],fmt,false);require(count<=(bytes-at)/stride);
            if(!pass){for(unsigned int v=0;v<count;++v)for(unsigned m=0;m<matrixIndexBytes();++m){u8 id=data[at+v*stride+m];require(id%3==0&&id<=(matrixEnabled&&m==0?27:60));}at+=count*stride;continue;}
            GXBegin((GXPrimitive)prim,(GXVtxFmt)fmt,(u16)count);
            for(unsigned int i=0;i<count;++i){const u8* p=data+at;for(unsigned m=0;m<matrixIndexBytes();++m)GXTexCoord1u8(*p++);const u8* positionData=p;
                if(posDescriptor!=GX_DIRECT){unsigned int index=posDescriptor==GX_INDEX8?p[0]:(p[0]<<8)|p[1];require((unsigned int)posArray<=0xffffffffu-index*posStride-rawPositionSize);positionData=posArray+index*posStride;}
                float v[3]={0,0,0};for(unsigned int c=0;c<components;++c)v[c]=decodePositionScalar(positionData+c*scalarSize,posFormats[fmt].type,posFormats[fmt].frac);emitPosition(v[0],v[1],v[2]);
                p+=psize;if(normalDescriptor!=GX_NONE){require(normalFormats[fmt].set);unsigned reads=normalDescriptor==GX_DIRECT?(normalFormats[fmt].count==GX_NRM_XYZ?1:3):(normalFormats[fmt].count==GX_NRM_NBT3?3:1);for(unsigned n=0;n<reads;++n){if(normalDescriptor==GX_DIRECT){packedNormal(p,normalFormats[fmt].type);p+=normalBytes(normalFormats[fmt].type);}else if(normalDescriptor==GX_INDEX8){GXNormal1x8(*p++);}else{GXNormal1x16((u16)((p[0]<<8)|p[1]));p+=2;}}}
                if(colorEnabled){if(colorDescriptor==GX_INDEX8)GXColor1x8(p[0]);else if(colorDescriptor==GX_INDEX16)GXColor1x16((u16)((p[0]<<8)|p[1]));else packedColor(p);}
                p+=csize;
                if(extraColor.descriptor!=GX_NONE){const ExtraInput& in=extraColor;
                    if(in.descriptor==GX_INDEX8)GXColor1x8(p[0]);else if(in.descriptor==GX_INDEX16)GXColor1x16((u16)((p[0]<<8)|p[1]));else packedColor(p);p+=extraEncodedSize(in,fmt,true);
                }
                if(texEnabled){if(texDescriptor==GX_INDEX8)GXTexCoord1x8(p[0]);else if(texDescriptor==GX_INDEX16)GXTexCoord1x16((u16)((p[0]<<8)|p[1]));else {const Format f=texFormats[fmt];unsigned scalar=positionScalarSize(f.type);emitTexcoord(decodePositionScalar(p,f.type,f.frac),decodePositionScalar(p+scalar,f.type,f.frac));}}
                p+=tsize;for(int input=0;input<7;++input){const ExtraInput& in=extraTex[input];if(in.descriptor==GX_NONE)continue;
                    if(in.descriptor==GX_INDEX8)GXTexCoord1x8(p[0]);else if(in.descriptor==GX_INDEX16)GXTexCoord1x16((u16)((p[0]<<8)|p[1]));else {const Format f=in.formats[fmt];unsigned scalar=positionScalarSize(f.type);emitTexcoord(decodePositionScalar(p,f.type,f.frac),decodePositionScalar(p+scalar,f.type,f.frac));}p+=extraEncodedSize(in,fmt,false);
                }
                at+=stride;
            }
            portEnd();
        }
    }
}

