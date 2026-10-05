float4 GXEfbDepth:register(c187); // enabled, GXZFmt16
float QuantizeEfbDepth(float z){
 z=min(16777215,floor(z+.5));if(GXEfbDepth.x<.5)return z;
 if(GXEfbDepth.y<.5)return floor(z/256)*256;
 float maximum=GXEfbDepth.y<1.5?3:GXEfbDepth.y<2.5?7:12;
 float exponent=0;
 [unroll]for(int bit=0;bit<12;++bit)if(bit<maximum&&z>=16777216-exp2(23-bit))exponent=bit+1;
 float shift=GXEfbDepth.y<1.5?(exponent==3?7:9-exponent):GXEfbDepth.y<2.5?(exponent==7?4:10-exponent):(exponent==12?0:11-exponent);
 float divisor=exp2(shift),range=GXEfbDepth.y<1.5?16384:GXEfbDepth.y<2.5?8192:4096;
 float mantissa=floor(z/divisor);mantissa-=floor(mantissa/range)*range;
 return (16777216-exp2(24-exponent))+mantissa*divisor;
}
