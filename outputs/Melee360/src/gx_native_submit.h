#pragma once
#include <xtl.h>
// Private native submission boundary. Original GX/HSD callers stay unchanged.
int Melee360GXNativeOpen(IDirect3DDevice9* device);
void Melee360GXNativeClose();
HRESULT Melee360GXNativeDraw(D3DPRIMITIVETYPE type,unsigned primitives,const void* vertices,unsigned stride);
void Melee360GXNativeReport(unsigned frames);