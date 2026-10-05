/* Count native constant uploads without a CPU shadow cache. The measured
 * shadow-cache experiment was rejected: it increased pipeline CPU cost. */
HRESULT setGXPixelConstants(unsigned first,const float* values,unsigned count){
 if(gxProfile.enabled){++gxProfile.constantRequests;++gxProfile.constantWrites;gxProfile.constantRegisters+=count;}
 return device->SetPixelShaderConstantF(first,values,count);
}
