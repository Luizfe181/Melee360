struct VertexOut {float4 position:POSITION;float4 uv:TEXCOORD0;float4 color:COLOR0;};
float4 SceneViewport:register(c0);
VertexOut VS(float4 position:POSITION,float2 uv:TEXCOORD0,float4 color:COLOR0) {
    VertexOut o;o.position=position;o.position.x*=SceneViewport.x;o.uv=float4(uv,position.z,position.w);o.color=color;return o;
}
sampler2D image:register(s0);
float4 PS(VertexOut i):COLOR0 {return tex2D(image,i.uv.xy)*i.color;}

#include "gx_z16.hlsl"
float4 GXDepthNormalization:register(c186);
struct DepthFragment {float4 color:COLOR0;float depth:DEPTH;};
DepthFragment PSQuantized(VertexOut i){DepthFragment o;o.color=PS(i);o.depth=dot(QuantizeEfbDepth(saturate(i.uv.z/i.uv.w)*16777215).xxxx,GXDepthNormalization);return o;}
