float4 GXFogParameters:register(c188); // original quantized a, integer B, divisor, c
float4 GXFogColorType:register(c189);
float4 GXFogRange:register(c190); // enable, original pixel center, left, width
float4 GXFogTable[3]:register(c191);
float FogRangeSample(float sample){
    if(sample<.5)return 1;
    float index=sample-1,group=floor(index/4);return Component(GXFogTable[(int)group],index-group*4);
}
float4 ApplyFog(float4 color,float depth,float clipX,float clipW){
    float kind=GXFogColorType.w;if(kind<.5)return color;
    float coordinate=min(16777215,floor(saturate(depth)*16777215+.5));
    float denominator=GXFogParameters.y-floor(coordinate/GXFogParameters.z);
    float distance=GXFogParameters.x==0?0:(GXFogParameters.x*16777216)/max(denominator,.000001);
    if(GXFogRange.x>.5){
        float x=GXFogRange.z+(clipX/clipW+1)*GXFogRange.w*.5;
        // The SDK table samples range correction at 32-pixel intervals.
        // Interpolate stored coefficients; hardware subpixel accuracy remains unverified.
        float sample=clamp(abs(x-GXFogRange.y)/32,0,10),low=floor(sample),high=min(low+1,10);
        distance*=lerp(FogRangeSample(low),FogRangeSample(high),frac(sample));
    }
    float factor=saturate(distance-GXFogParameters.w);
    if(kind>3.5&&kind<4.5)factor=1-exp2(-8*factor);
    else if(kind<5.5&&kind>4.5)factor=1-exp2(-8*factor*factor);
    else if(kind<6.5&&kind>5.5)factor=exp2(-8*(1-factor));
    else if(kind>6.5)factor=exp2(-8*(1-factor)*(1-factor));
    float weight=floor(factor*256+.5);
    color.rgb=floor((floor(saturate(color.rgb)*255+.5)*(256-weight)+floor(GXFogColorType.rgb*255+.5)*weight)/256)/255;
    return color;
}
