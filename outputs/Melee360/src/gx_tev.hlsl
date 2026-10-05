// Integer-domain TEV interpreter. Floats retain exact integer values within the used range.
float4 TevStages[96]:register(c16);
float4 TevInitial[4]:register(c112);
float4 TevKonst[4]:register(c116);
float4 TevSwap[4]:register(c120);
float4 TevControl:register(c124);
float4 TevIndMatrix[6]:register(c125);
float4 TevIndOrder[4]:register(c131);
float4 TevIndirect[48]:register(c135);
float ByteValue(float x);
float TruncateValue(float v){return v<0?ceil(v):floor(v);}
float2 TruncateValue2(float2 v){return float2(TruncateValue(v.x),TruncateValue(v.y));}
float WrapIndirect(float value,float mode){if(mode<.5)return value;if(mode>5.5)return 0;float period=exp2(9-mode)*128;return value-floor(value/period)*period;}
float Signed24(float v){return v-floor((v+8388608)/16777216)*16777216;}
float2 IndirectUV(int s,VertexOut input,float2 uv,float route,inout float2 previous,inout float bump,out float useOriginalLod){
    float4 a=TevIndirect[s*3],b=TevIndirect[s*3+1],enable=TevIndirect[s*3+2];useOriginalLod=b.w;
    if(enable.y<.5){previous=TruncateValue2(uv*GXTextureLod[(int)route].xy*128);return uv;}
    float2 fixed=TruncateValue2(uv*GXTextureLod[(int)route].xy*128),offset=0;
    if(enable.x<TevControl.z){
        float4 source=TevIndOrder[(int)enable.x];float2 sourceUV=VertexUV(input,source.w);float2 scaled=floor(TruncateValue2(sourceUV*GXTextureLod[(int)source.x].xy*128)/exp2(source.yz));
        float4 raw=floor(saturate(SampleGX(scaled/(GXTextureLod[(int)source.x].xy*128),source.x))*255+.5);float3 values=raw.abg;
        if(a.w>.5)bump=a.w<1.5?values.x:a.w<2.5?values.y:values.z;
        float divisor=a.x<.5?1:a.x<1.5?8:a.x<2.5?16:32;
        float3 biased=float3(a.y-floor(a.y/2)*2,floor(a.y/2)-floor(a.y/4)*2,floor(a.y/4));
        values=floor(values/divisor)+biased*(a.x<.5?-128:1);
        bump=a.x<.5?floor(bump/8)*8:ByteValue(bump*(a.x<1.5?32:a.x<2.5?16:8));
        if(a.z>.5){int matrixIndex=((int)a.z-1)%4;float4 m0=TevIndMatrix[matrixIndex*2],m1=TevIndMatrix[matrixIndex*2+1];
            if(a.z<4)offset=floor(float2(dot(m0.xyz,values),dot(m1.xyz,values))/8);
            else offset=floor(fixed*(a.z<8?values.x:values.y)/256);
            offset=floor(offset*exp2(m0.w));
        }
    }
    float2 wrapped=float2(WrapIndirect(fixed.x,b.x),WrapIndirect(fixed.y,b.y));
    previous=(b.z>.5?previous:float2(0,0))+wrapped+offset;previous=float2(Signed24(previous.x),Signed24(previous.y));
    return previous/(GXTextureLod[(int)route].xy*128);
}
float ByteValue(float x){return x-floor(x/256)*256;}
float3 ByteValue3(float3 x){return x-floor(x/256)*256;}
float Component(float4 v,float c){return c<.5?v.r:c<1.5?v.g:c<2.5?v.b:v.a;}
float4 SwapChannels(float4 v,float4 table){return float4(Component(v,table.x),Component(v,table.y),Component(v,table.z),Component(v,table.w));}
float4 RegisterValue(float n,float4 r0,float4 r1,float4 r2,float4 r3){return n<.5?r0:n<1.5?r1:n<2.5?r2:r3;}
float3 KonstColor(float k){
    if(k<8)return floor((8-k)*255/8+.5).xxx;
    if(k<12)return 0;
    if(k<16)return TevKonst[(int)k-12].rgb;
    float c=floor((k-16)/4),r=k-16-c*4;return Component(TevKonst[(int)r],c).xxx;
}
float KonstAlpha(float k){
    if(k<8)return floor((8-k)*255/8+.5);
    if(k<16)return 0;
    float c=floor((k-16)/4),r=k-16-c*4;return Component(TevKonst[(int)r],c);
}
float3 ColorArg(float n,float4 r0,float4 r1,float4 r2,float4 r3,float4 tex,float4 ras,float3 k){
    if(n<8){float r=floor(n/2);float4 value=RegisterValue(r,r0,r1,r2,r3);return n-r*2<.5?value.rgb:value.aaa;}
    if(n<8.5)return tex.rgb;if(n<9.5)return tex.aaa;if(n<10.5)return ras.rgb;if(n<11.5)return ras.aaa;
    if(n<12.5)return float3(255,255,255);if(n<13.5)return float3(128,128,128);if(n<14.5)return k;return 0;
}
float AlphaArg(float n,float4 r0,float4 r1,float4 r2,float4 r3,float4 tex,float4 ras,float k){
    if(n<4)return RegisterValue(n,r0,r1,r2,r3).a;
    if(n<4.5)return tex.a;if(n<5.5)return ras.a;if(n<6.5)return k;return 0;
}
float Arithmetic(float a,float b,float c,float d,float4 op){
    c+=floor(c/128);d+=op.y<.5?0:op.y<1.5?128:-128;
    float scale=floor(op.z/2),factor=scale<.5?1:scale<1.5?2:scale<2.5?4:1;
    float mixed=floor(((a*256+(b-a)*c)*factor+(scale<2.5?(op.x<.5?128:127):0))/256);
    float value=d*factor+(op.x<.5?mixed:-mixed);if(scale>2.5)value=floor(value/2);
    return value;
}
float3 Arithmetic3(float3 a,float3 b,float3 c,float3 d,float4 op){return float3(Arithmetic(a.r,b.r,c.r,d.r,op),Arithmetic(a.g,b.g,c.g,d.g,op),Arithmetic(a.b,b.b,c.b,d.b,op));}
bool PackedCompare(float op,float3 a,float3 b){
    float v=op-8;bool equal=(v-floor(v/2)*2)>.5;
    if(v<2)return equal?a.r==b.r:a.r>b.r;
    if(v<4)return equal?all(a.rg==b.rg):dot(a.rg,float2(1,256))>dot(b.rg,float2(1,256));
    return equal?all(a==b):dot(a,float3(1,256,65536))>dot(b,float3(1,256,65536));
}
float3 ColorCompare(float op,float3 a,float3 b,float3 c,float3 d){
    if(op<14)return d+(PackedCompare(op,a,b)?c:float3(0,0,0));
    return d+c*(op<14.5?float3(a.r>b.r,a.g>b.g,a.b>b.b):float3(a.r==b.r,a.g==b.g,a.b==b.b));
}
float4 ExecuteTev(VertexOut input,out float4 rawTexture){
    float4 r0=TevInitial[0],r1=TevInitial[1],r2=TevInitial[2],r3=TevInitial[3];float4 output=0;rawTexture=0;float2 previousUV=0;float bump=0;
    [loop] for(int s=0;s<TevControl.x&&s<16;++s){
        float4 ci=TevStages[s*6],ai=TevStages[s*6+1],co=TevStages[s*6+2],ao=TevStages[s*6+3],order=TevStages[s*6+4],sel=TevStages[s*6+5];
        float2 uv=VertexUV(input,order.w);float lod;float2 stageUV=IndirectUV(s,input,uv,order.x,previousUV,bump,lod);
        float4 tex=float4(255,255,255,255);if(order.z>.5)tex=floor(saturate(SampleGXWithLod(stageUV,lod>.5?uv:stageUV,order.x))*255+.5);
        if(order.z>.5)rawTexture=tex;float4 ras=floor(saturate(order.y==1||order.y==3||order.y==5?input.color1:input.color)*255+.5);if(order.y>5.5)ras=0;
        if(order.y==7)ras=bump.xxxx;else if(order.y==8)ras=(bump+floor(bump/32)).xxxx;
        ras=SwapChannels(ras,TevSwap[(int)sel.z]);tex=SwapChannels(tex,TevSwap[(int)sel.w]);
        float3 k=KonstColor(sel.x);float ka=KonstAlpha(sel.y);
        float3 a=ByteValue3(ColorArg(ci.x,r0,r1,r2,r3,tex,ras,k)),b=ByteValue3(ColorArg(ci.y,r0,r1,r2,r3,tex,ras,k)),c=ByteValue3(ColorArg(ci.z,r0,r1,r2,r3,tex,ras,k));
        float3 d=ColorArg(ci.w,r0,r1,r2,r3,tex,ras,k);
        float aa=ByteValue(AlphaArg(ai.x,r0,r1,r2,r3,tex,ras,ka)),ab=ByteValue(AlphaArg(ai.y,r0,r1,r2,r3,tex,ras,ka)),ac=ByteValue(AlphaArg(ai.z,r0,r1,r2,r3,tex,ras,ka)),ad=AlphaArg(ai.w,r0,r1,r2,r3,tex,ras,ka);
        float3 color=co.x<2?Arithmetic3(a,b,c,d,co):ColorCompare(co.x,a,b,c,d);
        float alpha=ao.x<2?Arithmetic(aa,ab,ac,ad,ao):ad+((ao.x<14?PackedCompare(ao.x,a,b):ao.x<14.5?aa>ab:aa==ab)?ac:0);
        bool cc=co.z-floor(co.z/2)*2>.5,ca=ao.z-floor(ao.z/2)*2>.5;
        color=clamp(color,cc?0:-1024,cc?255:1023);alpha=clamp(alpha,ca?0:-1024,ca?255:1023);
        if(co.w<.5)r0.rgb=color;else if(co.w<1.5)r1.rgb=color;else if(co.w<2.5)r2.rgb=color;else r3.rgb=color;
        if(ao.w<.5)r0.a=alpha;else if(ao.w<1.5)r1.a=alpha;else if(ao.w<2.5)r2.a=alpha;else r3.a=alpha;
        output=float4(color,alpha);
    }
    return float4(ByteValue3(output.rgb),ByteValue(output.a))/255;
}




