struct NativeLight {u32 reserved[3],color;float angle[3],distance[3],position[3],direction[3];};
struct NativeChannel {bool enable;GXColorSrc ambientSource,materialSource;u32 mask;GXDiffuseFn diffuse;GXAttnFn attenuation;};
struct Lighting {unsigned channels;NativeLight lights[8];bool loaded[8];GXColor ambient[2],material[2];NativeChannel controls[4];bool active;};Lighting lighting;
GXAttrType normalDescriptor=GX_NONE;const u8* normalArray;u8 normalStride;Format normalFormats[8];bool waitingNormal;unsigned normalVectorIndex;float sourceBinormal[3],sourceTangent[3];float eyePosition[3],eyeNormal[3];
float dot3(const float* a,const float* b){return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];}
void normalize3(float* a){float length=sqrtf(dot3(a,a));if(length>0)for(int c=0;c<3;++c)a[c]/=length;}
int colorByte(GXColor v,int component){return component==0?v.r:component==1?v.g:component==2?v.b:v.a;}
void applyLighting(){GXVertexTimer vertexTimer(1);if(!lighting.active)return;
 static const bool reuseRgb=GetFileAttributesA("game:\\gx-reuse-rgb-light.flag")!=((DWORD)-1);
 for(unsigned channel=0;channel<lighting.channels;++channel){float* vertex=channel?pending.color1:pending.color;float rgbFactors[8];int incoming[4];for(int c=0;c<4;++c)incoming[c]=(int)floorf(vertex[c]*255+.5f);
  for(int c=0;c<4;++c){const NativeChannel& control=lighting.controls[channel+(c==3?2:0)];int material=control.materialSource==GX_SRC_VTX?incoming[c]:colorByte(lighting.material[channel],c);int sum=control.enable?(control.ambientSource==GX_SRC_VTX?incoming[c]:colorByte(lighting.ambient[channel],c)):255;
   if(control.enable)for(int index=0;index<8;++index)if(control.mask&(1u<<index)){require(lighting.loaded[index]);const NativeLight& light=lighting.lights[index];float factor;
    if(reuseRgb&&c>0&&c<3)factor=rgbFactors[index];else {float direction[3];for(int axis=0;axis<3;++axis)direction[axis]=light.position[axis]-eyePosition[axis];float length2=dot3(direction,direction),length=sqrtf(length2);if(length>0)for(int axis=0;axis<3;++axis)direction[axis]/=length;else memcpy(direction,eyeNormal,12);
    factor=1;if(control.attenuation!=GX_AF_NONE){require(normalDescriptor!=GX_NONE);float cosine=control.attenuation==GX_AF_SPOT?dot3(direction,light.direction):dot3(eyeNormal,direction)>=0?dot3(eyeNormal,light.direction):0;if(cosine<0)cosine=0;
     float numerator=light.angle[0]+light.angle[1]*cosine+light.angle[2]*cosine*cosine;if(numerator<0)numerator=0;
     float distance=control.attenuation==GX_AF_SPOT?length:cosine;float denominator=light.distance[0]+light.distance[1]*distance+light.distance[2]*distance*distance;require(_finite(denominator)&&denominator>0);factor=numerator/denominator;
    }
    if(control.diffuse!=GX_DF_NONE){require(normalDescriptor!=GX_NONE);float diffuse=dot3(direction,eyeNormal);if(control.diffuse==GX_DF_CLAMP&&diffuse<0)diffuse=0;factor*=diffuse;}
    if(reuseRgb&&c==0)rgbFactors[index]=factor;}
    require(_finite(factor));int value=(light.color>>(24-8*c))&255;sum+=(int)floorf(factor*value+.5f);
   }
   if(sum<0)sum=0;if(sum>255)sum=255;vertex[c]=((material*(sum+(sum>>7)))>>8)/255.f;
  }
 }
}
