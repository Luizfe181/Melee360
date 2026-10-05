struct In { float2 pos:POSITION; float2 uv:TEXCOORD0; };
struct Out { float4 pos:POSITION; float2 uv:TEXCOORD0; };
Out VS(In v) { Out o; o.pos=float4(v.pos,0,1); o.uv=v.uv; return o; }
sampler image:register(s0);
float4 PS(Out v):COLOR0 { return tex2D(image,v.uv); }
