struct Input {float2 pos:POSITION;float2 uv:TEXCOORD0;};
struct Output {float4 pos:POSITION;float2 uv:TEXCOORD0;};
float4 RasterSize:register(c0);
Output VS(Input i){Output o;o.pos=float4(i.pos+float2(-1/RasterSize.x,1/RasterSize.y),0,1);o.uv=i.uv;return o;}
sampler2D source:register(s0);sampler2D previous:register(s1);
float4 SourceRect:register(c0); // xy source origin, zw source physical size
float4 Destination:register(c1); // xy destination width/height, z tile Y, w y-scale reciprocal
float4 Weights:register(c2); // upper/current/lower grouped six-bit coefficients; gamma reciprocal
float4 Limits:register(c3); // top/bottom source row bounds, source width, quantize565
float4 Field:register(c4); // weave enable, parity, source rectangle width, unused
float4 Expected:register(c5); // diagnostic expected byte RGB, tolerance
float4 SampleRow(float2 pixel){
 float2 uv=(float2(pixel.x,clamp(pixel.y,Limits.x,Limits.y))+.5)/SourceRect.zw;
 float4 value=floor(saturate(tex2Dlod(source,float4(uv,0,0)))*255+.5);
 if(Limits.w>.5){float3 q=floor(value.rgb/float3(8,4,8));value.rgb=q*float3(8,4,8)+floor(q/float3(4,16,4));value.a=255;}
 return value;
}
float4 Filter(Output i){
 float2 outPixel=float2(i.uv.x*Destination.x-.5,i.uv.y*32+Destination.z-.5);
 float row=floor(outPixel.y+.5);
 float2 oldUV=float2((outPixel.x+.5)/SourceRect.z,(outPixel.y+.5)/Field.w);
 if(Field.x>.5&&row-floor(row/2)*2!=Field.y)return tex2Dlod(previous,float4(oldUV,0,0));
 float2 pixel=float2(SourceRect.x+(outPixel.x+.5)*Field.z/Destination.x-.5,SourceRect.y+(outPixel.y+.5)*Destination.w-.5);
 pixel=floor(pixel+.5);
 float4 a=SampleRow(pixel+float2(0,-1)),b=SampleRow(pixel),c=SampleRow(pixel+float2(0,1));
 float3 weighted=floor((a.rgb*Weights.x+b.rgb*Weights.y+c.rgb*Weights.z)/64);
 weighted=weighted-floor(weighted/512)*512;weighted=min(weighted,255);

 weighted=floor(pow(weighted/255,Weights.www)*255+.5);
 return float4(weighted/255,b.a/255);
}
float4 PS(Output i):COLOR0{return Filter(i);}
float4 PSCheck(Output i):COLOR0{float4 result=Filter(i);clip(Expected.w-max(max(abs(result.r*255-Expected.x),abs(result.g*255-Expected.y)),abs(result.b*255-Expected.z)));return 1;}

float4 PSWhite(Output i):COLOR0{return 1;}
