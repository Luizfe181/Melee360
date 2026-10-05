extern "C" void GXSetNumChans(u8 count){require(!__GXinBegin&&count<=2);lighting.active=true;lighting.channels=count;}
static void channelColor(GXChannelID channel,GXColor value,GXColor* destination){require(!__GXinBegin&&channel>=0&&channel<=5);unsigned index=channel&1;if(channel!=GX_ALPHA0&&channel!=GX_ALPHA1){destination[index].r=value.r;destination[index].g=value.g;destination[index].b=value.b;}if(channel>=GX_ALPHA0)destination[index].a=value.a;}
extern "C" void GXSetChanAmbColor(GXChannelID channel,GXColor value){channelColor(channel,value,lighting.ambient);}
extern "C" void GXSetChanMatColor(GXChannelID channel,GXColor value){channelColor(channel,value,lighting.material);}
extern "C" void GXSetChanCtrl(GXChannelID channel,GXBool enable,GXColorSrc ambient,GXColorSrc material,u32 mask,GXDiffuseFn diffuse,GXAttnFn attenuation){require(!__GXinBegin&&channel>=0&&channel<=5&&(enable==GX_FALSE||enable==GX_TRUE)&&(ambient==GX_SRC_REG||ambient==GX_SRC_VTX)&&(material==GX_SRC_REG||material==GX_SRC_VTX)&&mask<=255&&diffuse>=GX_DF_NONE&&diffuse<=GX_DF_CLAMP&&attenuation>=GX_AF_SPEC&&attenuation<=GX_AF_NONE);NativeChannel value={enable!=GX_FALSE,ambient,material,mask,attenuation==GX_AF_SPEC?GX_DF_NONE:diffuse,attenuation};lighting.controls[channel<4?channel:channel&1]=value;if(channel>=4)lighting.controls[(channel&1)+2]=value;}
extern "C" void GXLoadLightObjImm(GXLightObj* value,GXLightID id){u32 bit=(u32)id;require(!__GXinBegin&&value&&bit&&bit<=128&&!(bit&(bit-1)));unsigned index=0;while((1u<<index)!=bit)++index;memcpy(&lighting.lights[index],value,sizeof(NativeLight));lighting.loaded[index]=true;}
static bool needsEyeNormal(){for(unsigned c=0;lighting.active&&c<lighting.channels;++c)for(unsigned a=0;a<2;++a){const NativeChannel& value=lighting.controls[c+a*2];if(value.enable&&value.mask)return true;}return false;}
static void emitNormal(float x,float y,float z){
 require(__GXinBegin&&primitiveActive&&waitingNormal&&_finite(x)&&_finite(y)&&_finite(z));float input[3]={x,y,z};
 if(normalVectorIndex==0){GXVertexTimer vertexTimer(3);memcpy(sourceNormal,input,12);if(needsEyeNormal()){require(Melee360GXTransformNormal(matrixEnabled?vertexMatrix:Melee360GXCurrentMatrix(),input,eyeNormal)!=0);normalize3(eyeNormal);}}
 else memcpy(normalVectorIndex==1?sourceBinormal:sourceTangent,input,12);
 ++normalVectorIndex;waitingNormal=normalVectorIndex<(normalFormats[activeFormat].count==GX_NRM_XYZ?1u:3u);if(!waitingNormal&&!waitingColor&&!waitingTex)finishVertex();
}
extern "C" void GXNormal3f32(f32 x,f32 y,f32 z){require(normalDescriptor==GX_DIRECT&&normalFormats[activeFormat].type==GX_F32);emitNormal(x,y,z);}
/* GX normal integers use fixed hardware scales, independently of VAT frac. */
static unsigned normalBytes(GXCompType type){return type==GX_F32?12:type==GX_S16?6:3;}
static void packedNormal(const u8* p,GXCompType type){
 float values[3];require(type==GX_F32||type==GX_S8||type==GX_S16);
 for(unsigned c=0;c<3;++c){if(type==GX_F32)memcpy(&values[c],p+4*c,4);else if(type==GX_S8)values[c]=(signed char)p[c]/64.f;else values[c]=(short)((p[2*c]<<8)|p[2*c+1])/16384.f;}
 emitNormal(values[0],values[1],values[2]);
}
static void indexedNormal(unsigned index,GXAttrType type){unsigned vectorBytes=normalBytes(normalFormats[activeFormat].type),vectors=normalFormats[activeFormat].count==GX_NRM_NBT?3:1,bytes=vectorBytes*vectors;require(normalDescriptor==type&&normalArray&&normalStride>=bytes&&(u32)normalArray<=0xffffffffu-index*normalStride-bytes);for(unsigned i=0;i<vectors;++i)packedNormal(normalArray+index*normalStride+i*vectorBytes,normalFormats[activeFormat].type);}
extern "C" void GXNormal1x8(u8 index){indexedNormal(index,GX_INDEX8);}
extern "C" void GXNormal1x16(u16 index){indexedNormal(index,GX_INDEX16);}
