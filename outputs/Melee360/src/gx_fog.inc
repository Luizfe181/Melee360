namespace {
u32 fogRegisters[11];
float unpackFogFloat(u32 value){u32 bits=(value&0xfffff)<<12;float decoded;memcpy(&decoded,&bits,4);return decoded;}
void uploadFog(){
    float coefficients[4]={unpackFogFloat(fogRegisters[6]),(float)(fogRegisters[7]&0xffffff),(float)pow(2.,(int)(fogRegisters[8]&31)),unpackFogFloat(fogRegisters[9])};
    u32 color=fogRegisters[10];float colorType[4]={((color>>16)&255)/255.f,((color>>8)&255)/255.f,(color&255)/255.f,(float)((fogRegisters[9]>>21)&7)};
    float viewport[6];GXGetViewportv(viewport);float range[4]={(float)((fogRegisters[0]>>10)&1),(float)((int)(fogRegisters[0]&1023)-342),viewport[0],viewport[2]},table[12]={0};
    for(unsigned i=0;i<10;++i)table[i]=((fogRegisters[1+i/2]>>((i%2)*12))&4095)/256.f;
    require(SUCCEEDED(setGXPixelConstants(188,coefficients,1))&&SUCCEEDED(setGXPixelConstants(189,colorType,1))&&SUCCEEDED(setGXPixelConstants(190,range,1))&&SUCCEEDED(setGXPixelConstants(191,table,3)));
}
}
extern "C" void Melee360GXWriteFogRegister(u32 value){
    require(!__GXinBegin);unsigned reg=value>>24;require(reg>=0xe8&&reg<=0xf2);fogRegisters[reg-0xe8]=value&0xffffff;
}
