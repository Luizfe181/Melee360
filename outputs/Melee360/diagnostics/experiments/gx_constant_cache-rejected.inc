/* Valid only while the original GX owns the draw pass. Foreign D3D draws and
 * state-block restoration must occur outside this scope. Compare float bits. */
bool constantScope;bool constantValid[256];float constantShadow[256][4];
HRESULT setGXPixelConstants(unsigned first,const float* values,unsigned count){
 require(values&&first<256&&count<=256-first);
 if(gxProfile.enabled)++gxProfile.constantRequests;
 if(!constantScope){if(gxProfile.enabled){++gxProfile.constantWrites;gxProfile.constantRegisters+=count;}return device->SetPixelShaderConstantF(first,values,count);}
 /* Most large groups repeat unchanged between primitives. Compare the full
  * group first; scan individual registers only when at least one changed. */
 if(!memchr(constantValid+first,0,count)&&!memcmp(constantShadow[first],values,count*16))return S_OK;
 unsigned offset=0;
 while(offset<count){
  while(offset<count&&constantValid[first+offset]&&!memcmp(constantShadow[first+offset],values+offset*4,16))++offset;
  if(offset==count)break;unsigned begin=offset++;
  while(offset<count&&(!constantValid[first+offset]||memcmp(constantShadow[first+offset],values+offset*4,16)))++offset;
  HRESULT hr=device->SetPixelShaderConstantF(first+begin,values+begin*4,offset-begin);if(FAILED(hr))return hr;
  memcpy(constantShadow[first+begin],values+begin*4,(offset-begin)*16);memset(constantValid+first+begin,1,offset-begin);
  if(gxProfile.enabled){++gxProfile.constantWrites;gxProfile.constantRegisters+=offset-begin;}
 }return S_OK;
}
void beginConstantScope(bool enabled){constantScope=enabled;memset(constantValid,0,sizeof(constantValid));}
