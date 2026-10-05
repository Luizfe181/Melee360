bool textureInputEnabled(unsigned int i){return i==0?texEnabled:extraTex[i-1].descriptor!=GX_NONE;}
unsigned int nextTexture(unsigned int start){for(unsigned int i=start;i<8;++i)if(textureInputEnabled(i))return i;return 8;}
Format& activeTexFormat(){require(currentTex<8);return currentTex==0?texFormats[activeFormat]:extraTex[currentTex-1].formats[activeFormat];}
Format& activeColorFormat(){return currentColor==0?colorFormats[activeFormat]:extraColor.formats[activeFormat];}
float* activeTexData(){require(currentTex<8);return currentTex==0?pending.uv:pending.extraUV[currentTex-1];}
float* activeColorData(){return currentColor==0?pending.color:pending.color1;}
GXAttrType activeTexDescriptor(){return currentTex==0?texDescriptor:extraTex[currentTex-1].descriptor;}
GXAttrType activeColorDescriptor(){return currentColor==0?colorDescriptor:extraColor.descriptor;}
const u8* activeTexArray(){return currentTex==0?texArray:extraTex[currentTex-1].data;}
const u8* activeColorArray(){return currentColor==0?colorArray:extraColor.data;}
u8 activeTexStride(){return currentTex==0?texStride:extraTex[currentTex-1].stride;}
u8 activeColorStride(){return currentColor==0?colorStride:extraColor.stride;}
void finishTextureInput(){currentTex=nextTexture(currentTex+1);waitingTex=currentTex<8;if(!waitingNormal&&!waitingTex&&!waitingColor)finishVertex();}
void finishColorInput(){if(currentColor==0&&extraColor.descriptor!=GX_NONE){currentColor=1;return;}waitingColor=false;if(!waitingNormal&&!waitingTex)finishVertex();}
ExtraInput* extraInput(GXAttr attr){if(attr==GX_VA_CLR1)return &extraColor;if(attr>=GX_VA_TEX1&&attr<=GX_VA_TEX7)return &extraTex[attr-GX_VA_TEX1];return 0;}
bool extraDescriptor(GXAttr attr,GXAttrType type){ExtraInput* in=extraInput(attr);if(!in)return false;require(!__GXinBegin&&type>=GX_NONE&&type<=GX_INDEX16);in->descriptor=type;return true;}
bool extraArray(GXAttr attr,const void* data,u8 stride){ExtraInput* in=extraInput(attr);if(!in)return false;require(!__GXinBegin&&data&&stride);in->data=(const u8*)data;in->stride=stride;return true;}
bool extraFormat(GXVtxFmt format,GXAttr attr,GXCompCnt count,GXCompType type,u8 frac){
    ExtraInput* in=extraInput(attr);if(!in)return false;
    if(attr==GX_VA_CLR1)require((count==GX_CLR_RGB&&type>=GX_RGB565&&type<=GX_RGBX8)||(count==GX_CLR_RGBA&&type>=GX_RGBA4&&type<=GX_RGBA8));
    else require(count==GX_TEX_ST&&(type==GX_F32||type==GX_U8||type==GX_S8||type==GX_U16||type==GX_S16)&&frac<=31&&(type!=GX_F32||frac==0));
    Format& f=in->formats[format];f.count=count;f.type=type;f.frac=frac;f.set=true;return true;
}
void validateExtraInputs(unsigned int fmt){require(!__GXinBegin&&fmt<8);if(extraColor.descriptor!=GX_NONE)require(extraColor.formats[fmt].set);for(int i=0;i<7;++i)if(extraTex[i].descriptor!=GX_NONE)require(extraTex[i].formats[fmt].set);}
unsigned int extraEncodedSize(const ExtraInput& in,unsigned int fmt,bool color){if(in.descriptor==GX_NONE)return 0;if(in.descriptor==GX_INDEX8)return 1;if(in.descriptor==GX_INDEX16)return 2;return color?colorEncodedBytes(in.formats[fmt].type):(2*positionScalarSize(in.formats[fmt].type));}
