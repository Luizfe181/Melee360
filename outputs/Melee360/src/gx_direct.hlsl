struct VertexOut {float4 position:POSITION;float4 uv:TEXCOORD0;float4 uv1:TEXCOORD1;float4 uv2:TEXCOORD2;float3 uv3:TEXCOORD3;float3 uv4:TEXCOORD4;float3 uv5:TEXCOORD5;float3 uv6:TEXCOORD6;float3 uv7:TEXCOORD7;float4 color:COLOR0;float4 color1:COLOR1;};
float4 SceneViewport:register(c0);
VertexOut VS(float4 position:POSITION,float3 uv:TEXCOORD0,float4 color:COLOR0,float3 uv1:TEXCOORD1,float3 uv2:TEXCOORD2,float3 uv3:TEXCOORD3,float3 uv4:TEXCOORD4,float3 uv5:TEXCOORD5,float3 uv6:TEXCOORD6,float3 uv7:TEXCOORD7,float4 color1:COLOR1){
 VertexOut o;o.position=position;o.position.x*=SceneViewport.x;o.uv=float4(uv,position.z);o.uv1=float4(uv1,position.w);o.uv2=float4(uv2,o.position.x);o.uv3=uv3;o.uv4=uv4;o.uv5=uv5;o.uv6=uv6;o.uv7=uv7;o.color=color;o.color1=color1;return o;
}
float2 VertexUV(VertexOut i,float n){float3 coord=n<.5?i.uv.xyz:n<1.5?i.uv1.xyz:n<2.5?i.uv2.xyz:n<3.5?i.uv3:n<4.5?i.uv4:n<5.5?i.uv5:n<6.5?i.uv6:i.uv7;return coord.xy/coord.z;}
sampler2D image0:register(s0);
sampler2D image1:register(s1);
sampler2D image2:register(s2);
sampler2D image3:register(s3);
sampler2D image4:register(s4);
sampler2D image5:register(s5);
sampler2D image6:register(s6);
sampler2D image7:register(s7);
float4 GXTextureRoute:register(c2);
float4 GXTextureLod[8]:register(c3);
float4 GXTextureBias[2]:register(c11);
float TextureLod(float2 uv,float4 state,float bias){
    float2 dx=ddx(uv)*state.xy,dy=ddy(uv)*state.xy;
    float rho=max(dot(dx,dx),dot(dy,dy));
    return clamp(.5*log2(max(rho,0.00000001))+bias,state.z,state.w);
}
float4 GXAlphaFirst:register(c0); // comparison0, reference0, operation, enabled
float4 GXAlphaSecond:register(c1); // comparison1, reference1
bool AlphaCompare(float a,float mode,float reference) {
    if(mode<0.5)return false;
    if(mode<1.5)return a<reference;
    if(mode<2.5)return a==reference;
    if(mode<3.5)return a<=reference;
    if(mode<4.5)return a>reference;
    if(mode<5.5)return a!=reference;
    if(mode<6.5)return a>=reference;
    return true;
}
float4 SampleGXWithLod(float2 uv,float2 loduv,float route) {
    float4 sample=tex2Dlod(image0,float4(uv,0,TextureLod(loduv,GXTextureLod[0],GXTextureBias[0].x)));
    if(route>0.5)sample=tex2Dlod(image1,float4(uv,0,TextureLod(loduv,GXTextureLod[1],GXTextureBias[0].y)));
    if(route>1.5)sample=tex2Dlod(image2,float4(uv,0,TextureLod(loduv,GXTextureLod[2],GXTextureBias[0].z)));
    if(route>2.5)sample=tex2Dlod(image3,float4(uv,0,TextureLod(loduv,GXTextureLod[3],GXTextureBias[0].w)));
    if(route>3.5)sample=tex2Dlod(image4,float4(uv,0,TextureLod(loduv,GXTextureLod[4],GXTextureBias[1].x)));
    if(route>4.5)sample=tex2Dlod(image5,float4(uv,0,TextureLod(loduv,GXTextureLod[5],GXTextureBias[1].y)));
    if(route>5.5)sample=tex2Dlod(image6,float4(uv,0,TextureLod(loduv,GXTextureLod[6],GXTextureBias[1].z)));
    if(route>6.5)sample=tex2Dlod(image7,float4(uv,0,TextureLod(loduv,GXTextureLod[7],GXTextureBias[1].w)));
    return sample;
}
float4 SampleGX(float2 uv,float route){return SampleGXWithLod(uv,uv,route);}
#include "gx_tev.hlsl"
#include "gx_fog.hlsl"
float4 Fragment(VertexOut i,out float4 rawTexture) {
    float4 result=ExecuteTev(i,rawTexture);
    if(TevControl.y>.5)result.a=Component(result,TevControl.y-1);
    if(GXAlphaFirst.w>0.5) {
        float alpha=floor(saturate(result.a)*255.0+0.5);
        bool a=AlphaCompare(alpha,GXAlphaFirst.x,GXAlphaFirst.y);
        bool b=AlphaCompare(alpha,GXAlphaSecond.x,GXAlphaSecond.y);
        bool accept=GXAlphaFirst.z<0.5?(a&&b):GXAlphaFirst.z<1.5?(a||b):GXAlphaFirst.z<2.5?(a!=b):(a==b);
        clip(accept?1.0:-1.0);
    }
    return result;
}





float4 GXFramebuffer:register(c195);
float4 DitherFramebuffer(float4 color,float2 pixel){
 if(GXFramebuffer.x>.5&&GXFramebuffer.y>.5){float2 parity=fmod(floor(pixel),2);float rank=(abs(parity.x-parity.y)*2+parity.y);float3 value=floor(color.rgb*255+.5);value=value-floor(value/64)+rank;color.rgb=value/255;}
 return color;
}
float4 PackFramebuffer(float4 color){
 if(GXFramebuffer.x>.5){float4 six=floor(floor(saturate(color)*255+.5)/4);color=(six*4+floor(six/16))/255;}
 return color;
}
float4 GXDestinationAlpha:register(c194);
float4 FinishDestinationAlpha(float4 color){if(GXDestinationAlpha.x>.5)color.a=GXDestinationAlpha.y;return color;}
float4 GXDepthRange:register(c184);
float4 PS(VertexOut i,float2 pixel:VPOS):COLOR0 {float4 raw;float4 color=DitherFramebuffer(Fragment(i,raw),pixel);float z=saturate(GXDepthRange.x+(i.uv.w/i.uv1.w)*(GXDepthRange.y-GXDepthRange.x));return PackFramebuffer(FinishDestinationAlpha(ApplyFog(color,z,i.uv2.w,i.uv1.w)));}
float4 GXZTexture:register(c183);

float4 GXDepthNormalization:register(c186);
struct DepthFragment {float4 color:COLOR0;float depth:DEPTH;};
#include "gx_z16.hlsl"
DepthFragment PSQuantized(VertexOut i,float2 pixel:VPOS){float4 raw;DepthFragment o;o.color=DitherFramebuffer(Fragment(i,raw),pixel);
 float z=saturate(GXDepthRange.x+(i.uv.w/i.uv1.w)*(GXDepthRange.y-GXDepthRange.x));
 o.color=ApplyFog(o.color,z,i.uv2.w,i.uv1.w);o.depth=dot(QuantizeEfbDepth(z*16777215).xxxx,GXDepthNormalization);o.color=PackFramebuffer(FinishDestinationAlpha(o.color));return o;}

float Add24(float a,float b){float low=a-floor(a/4096)*4096+b-floor(b/4096)*4096;float high=floor(a/4096)+floor(b/4096)+floor(low/4096);return low-floor(low/4096)*4096+(high-floor(high/4096)*4096)*4096;}
DepthFragment PSDepth(VertexOut i,float2 pixel:VPOS){
 float4 raw;DepthFragment o;o.color=DitherFramebuffer(Fragment(i,raw),pixel);
 float packed=GXZTexture.y<.5?raw.a:GXZTexture.y<1.5?raw.a*256+raw.r:dot(raw.rgb,float3(65536,256,1));
 float base=min(16777215,floor(saturate(GXDepthRange.x+(i.uv.w/i.uv1.w)*(GXDepthRange.y-GXDepthRange.x))*16777215+.5));
 float value=Add24(packed,GXZTexture.z);if(GXZTexture.x<1.5)value=Add24(value,base);o.color=ApplyFog(o.color,value/16777215,i.uv2.w,i.uv1.w);o.depth=dot(QuantizeEfbDepth(value).xxxx,GXDepthNormalization);o.color=PackFramebuffer(FinishDestinationAlpha(o.color));return o;
}

DepthFragment PSEarlyDepth(VertexOut i){DepthFragment o;o.color=0;float z=saturate(GXDepthRange.x+(i.uv.w/i.uv1.w)*(GXDepthRange.y-GXDepthRange.x));o.depth=dot(QuantizeEfbDepth(z*16777215).xxxx,GXDepthNormalization);return o;}
